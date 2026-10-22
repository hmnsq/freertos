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

#که_تعریف_شوی config_CLINT_بنسټ_پته
    #warning "The configCLINT_BASE_ADDRESS constant has been deprecated. configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS directly in place of configCLINT_BASE_ADDRESS. See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#د_که_پای

#که_نه_تعریف_شوی config_MTIME_بنسټ_پته
    #warning "configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h. If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#د_که_پای

#که_نه_تعریف_شوی config_MTIMECMP_بنسټ_پته
    #warning "configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h. If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#د_که_پای

/* Let the user override the pre-loading of the initial RA. */
#که_تعریف_شوی config_TASK_RETURN_پته
    #تعریف_کړه پورټ_TASK_RETURN_پته    config_TASK_RETURN_پته
#وإلا
    #تعریف_کړه پورټ_TASK_RETURN_پته    0
#د_که_پای

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
 * to use a statically allocated array as the interrupt stack.  Alternative leave
 * configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
 * linker variable names __freertos_irq_stack_top has the same value as the top
 * of the stack used by main.  Using the linker script method will repurpose the
 * stack that was used by main before the scheduler was started for use as the
 * interrupt stack after the scheduler has started. */
#که_تعریف_شوی config_ISR_ډېری_اندازه_ټکي
ساكن __attribute__( ( aligned( 16 ) ) ) ډېری_Type_t xISRStack[ config_ISR_ډېری_اندازه_ټکي ] = { 0 };
ثابت ډېری_Type_t x_ISRStack_سر = ( ډېری_Type_t ) &( xISRStack[ config_ISR_ډېری_اندازه_ټکي & ~پورټ_BYTE_ALIGNMENT_ماسک ] );

/* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
 * the task stacks, and so will legitimately appear in many positions within
 * the ISR stack. */
    #تعریف_کړه پورټ_ISR_ډېری_FILL_BYTE    0xee
#وإلا
    خارجي ثابت uint32_t __freertos_irq_stack_top[];
    ثابت ډېری_Type_t x_ISRStack_سر = ( ډېری_Type_t ) __freertos_irq_stack_top;
#د_که_پای

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورټ_تیاری_Timer_مداخله( فراغ ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ull_بل_وخت = 0ULL;
ثابت uint64_t * pull_بل_وخت = &ull_بل_وخت;
ثابت size_t uxTimerIncrementsForOneTick = ( size_t ) ( ( configCPU_CLOCK_HZ ) / ( config_TICK_شرح_HZ ) ); /* Assumes increment won't go over 32-bits. */
متطاير uint64_t * pull_Machine_Timer_Compare_ثبتوونکی = عدم;

/* Holds the critical nesting value - deliberately non-zero at start up to
 * ensure interrupts are not accidentally enabled before the scheduler starts. */
size_t xCriticalNesting = ( size_t ) 0xaaaaaaaa;
size_t * pxCriticalNesting = &xCriticalNesting;

/* Used to catch tasks that attempt to return from their implementing function. */
size_t x_Task_Return_پته = ( size_t ) پورټ_TASK_RETURN_پته;

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
 * stack checking.  A problem in the ISR stack will trigger an assert, not call
 * the stack overflow hook function (because the stack overflow hook is specific
 * to a task stack, not the ISR stack). */
#إذا defined( config_ISR_ډېری_اندازه_ټکي ) && ( config_CHECK_FOR_ډېری_ډکېدنه > 2 )
    #warning "This path not tested, or even compiled yet."

    ساكن ثابت uint8_t uc_Expected_ډېری_بایټونه[] =
    {
        پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, \
        پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, \
        پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, \
        پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, \
        پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE, پورټ_ISR_ډېری_FILL_BYTE
    }; \

    #تعریف_کړه پورټ_CHECK_ISR_ډېری()    configASSERT( ( memcmp( ( فراغ * ) xISRStack, ( فراغ * ) uc_Expected_ډېری_بایټونه, حجم( uc_Expected_ډېری_بایټونه ) ) == 0 ) )
#وإلا /* if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 ) */
    /* Define the function away. */
    #تعریف_کړه پورټ_CHECK_ISR_ډېری()
#د_که_پای /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

#إذا ( config_MTIME_بنسټ_پته != 0 ) && ( config_MTIMECMP_بنسټ_پته != 0 )

    فراغ v_پورټ_تیاری_Timer_مداخله( فراغ )
    {
        uint32_t ul_Current_وخت_لوړ, ul_Current_وخت_ټیټ;
        متطاير uint32_t * ثابت pul_وخت_لوړ = ( متطاير uint32_t * ثابت ) ( ( config_MTIME_بنسټ_پته ) + 4UL ); /* 8-byte type so high 32-bit word is 4 bytes up. */
        متطاير uint32_t * ثابت pul_وخت_ټیټ = ( متطاير uint32_t * ثابت ) ( config_MTIME_بنسټ_پته );
        متطاير uint32_t ulHartId;

        __asm متطاير ( "csrr %0, mhartid" : "=r" ( ulHartId ) );

        pull_Machine_Timer_Compare_ثبتوونکی = ( متطاير uint64_t * ) ( config_MTIMECMP_بنسټ_پته + ( ulHartId * حجم( uint64_t ) ) );

        افعل
        {
            ul_Current_وخت_لوړ = *pul_وخت_لوړ;
            ul_Current_وخت_ټیټ = *pul_وخت_ټیټ;
        } طالما( ul_Current_وخت_لوړ != *pul_وخت_لوړ );

        ull_بل_وخت = ( uint64_t ) ul_Current_وخت_لوړ;
        ull_بل_وخت <<= 32ULL; /* High 4-byte word is 32-bits up. */
        ull_بل_وخت |= ( uint64_t ) ul_Current_وخت_ټیټ;
        ull_بل_وخت += ( uint64_t ) uxTimerIncrementsForOneTick;
        *pull_Machine_Timer_Compare_ثبتوونکی = ull_بل_وخت;

        /* Prepare the time to use after the next tick interrupt. */
        ull_بل_وخت += ( uint64_t ) uxTimerIncrementsForOneTick;
    }

#د_که_پای /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    خارجي فراغ x_پورټ_پیل_لومړی_Task( فراغ );

    #إذا ( configASSERT_DEFINED == 1 )
    {
        /* Check alignment of the interrupt stack - which is the same as the
         * stack that was being used by main() prior to the scheduler being
         * started. */
        configASSERT( ( x_ISRStack_سر & پورټ_BYTE_ALIGNMENT_ماسک ) == 0 );

        #که_تعریف_شوی config_ISR_ډېری_اندازه_ټکي
        {
            memset( ( فراغ * ) xISRStack, پورټ_ISR_ډېری_FILL_BYTE, حجم( xISRStack ) );
        }
        #د_که_پای /* configISR_STACK_SIZE_WORDS */
    }
    #د_که_پای /* configASSERT_DEFINED */

    /* If there is a CLINT then it is ok to use the default implementation
     * in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
     * configure whichever clock is to be used to generate the tick interrupt. */
    v_پورټ_تیاری_Timer_مداخله();

    #إذا ( ( config_MTIME_بنسټ_پته != 0 ) && ( config_MTIMECMP_بنسټ_پته != 0 ) )
    {
        /* Enable mtime and external interrupts.  1<<7 for timer interrupt,
         * 1<<11 for external interrupt.  _RB_ What happens here when mtime is
         * not present as with pulpino? */
        __asm متطاير ( "csrs mie, %0" ::"r" ( 0x880 ) );
    }
    #د_که_پای /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

    x_پورټ_پیل_لومړی_Task();

    /* Should not get here as after calling xPortStartFirstTask() only tasks
     * should be executing. */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented. */
    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/
