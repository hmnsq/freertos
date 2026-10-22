/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the RISC-V port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "portmacro.h"

/* Standard includes. */
#ضمن "string.h"

#جيڪڏهن_وصف_ٿيل config_CLINT_بنياد_پتو
    #warning "The configCLINT_BASE_ADDRESS constant has been deprecated. configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS directly in place of configCLINT_BASE_ADDRESS. See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_MTIME_بنياد_پتو
    #warning "configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h. If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_MTIMECMP_بنياد_پتو
    #warning "configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h. If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#جيڪڏهن_پورو

/* Let the user override the pre-loading of the initial RA. */
#جيڪڏهن_وصف_ٿيل config_TASK_RETURN_پتو
    #وصف_ڪريو پورٽ_TASK_RETURN_پتو    config_TASK_RETURN_پتو
#وإلا
    #وصف_ڪريو پورٽ_TASK_RETURN_پتو    0
#جيڪڏهن_پورو

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
 * to use a statically allocated array as the interrupt stack.  Alternative leave
 * configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
 * linker variable names __freertos_irq_stack_top has the same value as the top
 * of the stack used by main.  Using the linker script method will repurpose the
 * stack that was used by main before the scheduler was started for use as the
 * interrupt stack after the scheduler has started. */
#جيڪڏهن_وصف_ٿيل config_ISR_ڍير_سائيز_لفظ
ساكن __attribute__( ( aligned( 16 ) ) ) ڍير_Type_t xISRStack[ config_ISR_ڍير_سائيز_لفظ ] = { 0 };
ثابت ڍير_Type_t x_ISRStack_چوٽي = ( ڍير_Type_t ) &( xISRStack[ config_ISR_ڍير_سائيز_لفظ & ~پورٽ_BYTE_ALIGNMENT_نقاب ] );

/* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
 * the task stacks, and so will legitimately appear in many positions within
 * the ISR stack. */
    #وصف_ڪريو پورٽ_ISR_ڍير_FILL_BYTE    0xee
#وإلا
    خارجي ثابت uint32_t __freertos_irq_stack_top[];
    ثابت ڍير_Type_t x_ISRStack_چوٽي = ( ڍير_Type_t ) __freertos_irq_stack_top;
#جيڪڏهن_پورو

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورٽ_تياري_Timer_مداخلت( فراغ ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ull_ايندڙ_وقت = 0ULL;
ثابت uint64_t * pull_ايندڙ_وقت = &ull_ايندڙ_وقت;
ثابت size_t uxTimerIncrementsForOneTick = ( size_t ) ( ( configCPU_CLOCK_HZ ) / ( config_TICK_شرح_HZ ) ); /* Assumes increment won't go over 32-bits. */
متطاير uint64_t * pull_Machine_Timer_Compare_رجسٽر = عدم;

/* Holds the critical nesting value - deliberately non-zero at start up to
 * ensure interrupts are not accidentally enabled before the scheduler starts. */
size_t xCriticalNesting = ( size_t ) 0xaaaaaaaa;
size_t * pxCriticalNesting = &xCriticalNesting;

/* Used to catch tasks that attempt to return from their implementing function. */
size_t x_Task_Return_پتو = ( size_t ) پورٽ_TASK_RETURN_پتو;

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
 * stack checking.  A problem in the ISR stack will trigger an assert, not call
 * the stack overflow hook function (because the stack overflow hook is specific
 * to a task stack, not the ISR stack). */
#إذا defined( config_ISR_ڍير_سائيز_لفظ ) && ( config_CHECK_FOR_ڍير_حد_کان_مٿي > 2 )
    #warning "This path not tested, or even compiled yet."

    ساكن ثابت uint8_t uc_Expected_ڍير_بائيٽون[] =
    {
        پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, \
        پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, \
        پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, \
        پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, \
        پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE, پورٽ_ISR_ڍير_FILL_BYTE
    }; \

    #وصف_ڪريو پورٽ_CHECK_ISR_ڍير()    configASSERT( ( memcmp( ( فراغ * ) xISRStack, ( فراغ * ) uc_Expected_ڍير_بائيٽون, حجم( uc_Expected_ڍير_بائيٽون ) ) == 0 ) )
#وإلا /* if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 ) */
    /* Define the function away. */
    #وصف_ڪريو پورٽ_CHECK_ISR_ڍير()
#جيڪڏهن_پورو /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

#إذا ( config_MTIME_بنياد_پتو != 0 ) && ( config_MTIMECMP_بنياد_پتو != 0 )

    فراغ v_پورٽ_تياري_Timer_مداخلت( فراغ )
    {
        uint32_t ul_Current_وقت_مٿاهون, ul_Current_وقت_هيٺيون;
        متطاير uint32_t * ثابت pul_وقت_مٿاهون = ( متطاير uint32_t * ثابت ) ( ( config_MTIME_بنياد_پتو ) + 4UL ); /* 8-byte type so high 32-bit word is 4 bytes up. */
        متطاير uint32_t * ثابت pul_وقت_هيٺيون = ( متطاير uint32_t * ثابت ) ( config_MTIME_بنياد_پتو );
        متطاير uint32_t ulHartId;

        __asm متطاير ( "csrr %0, mhartid" : "=r" ( ulHartId ) );

        pull_Machine_Timer_Compare_رجسٽر = ( متطاير uint64_t * ) ( config_MTIMECMP_بنياد_پتو + ( ulHartId * حجم( uint64_t ) ) );

        افعل
        {
            ul_Current_وقت_مٿاهون = *pul_وقت_مٿاهون;
            ul_Current_وقت_هيٺيون = *pul_وقت_هيٺيون;
        } طالما( ul_Current_وقت_مٿاهون != *pul_وقت_مٿاهون );

        ull_ايندڙ_وقت = ( uint64_t ) ul_Current_وقت_مٿاهون;
        ull_ايندڙ_وقت <<= 32ULL; /* High 4-byte word is 32-bits up. */
        ull_ايندڙ_وقت |= ( uint64_t ) ul_Current_وقت_هيٺيون;
        ull_ايندڙ_وقت += ( uint64_t ) uxTimerIncrementsForOneTick;
        *pull_Machine_Timer_Compare_رجسٽر = ull_ايندڙ_وقت;

        /* Prepare the time to use after the next tick interrupt. */
        ull_ايندڙ_وقت += ( uint64_t ) uxTimerIncrementsForOneTick;
    }

#جيڪڏهن_پورو /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    خارجي فراغ x_پورٽ_شروعات_پهريون_Task( فراغ );

    #إذا ( configASSERT_DEFINED == 1 )
    {
        /* Check alignment of the interrupt stack - which is the same as the
         * stack that was being used by main() prior to the scheduler being
         * started. */
        configASSERT( ( x_ISRStack_چوٽي & پورٽ_BYTE_ALIGNMENT_نقاب ) == 0 );

        #جيڪڏهن_وصف_ٿيل config_ISR_ڍير_سائيز_لفظ
        {
            memset( ( فراغ * ) xISRStack, پورٽ_ISR_ڍير_FILL_BYTE, حجم( xISRStack ) );
        }
        #جيڪڏهن_پورو /* configISR_STACK_SIZE_WORDS */
    }
    #جيڪڏهن_پورو /* configASSERT_DEFINED */

    /* If there is a CLINT then it is ok to use the default implementation
     * in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
     * configure whichever clock is to be used to generate the tick interrupt. */
    v_پورٽ_تياري_Timer_مداخلت();

    #إذا ( ( config_MTIME_بنياد_پتو != 0 ) && ( config_MTIMECMP_بنياد_پتو != 0 ) )
    {
        /* Enable mtime and external interrupts.  1<<7 for timer interrupt,
         * 1<<11 for external interrupt.  _RB_ What happens here when mtime is
         * not present as with pulpino? */
        __asm متطاير ( "csrs mie, %0" ::"r" ( 0x880 ) );
    }
    #جيڪڏهن_پورو /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

    x_پورٽ_شروعات_پهريون_Task();

    /* Should not get here as after calling xPortStartFirstTask() only tasks
     * should be executing. */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented. */
    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/
