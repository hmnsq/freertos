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

#جے_تعریف_شدہ config_CLINT_ادھار_پتہ
    #warning "The configCLINT_BASE_ADDRESS constant has been deprecated.  configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS directly in place of configCLINT_BASE_ADDRESS.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#جے_انت

#جے_بنا_تعریف config_MTIME_ادھار_پتہ
    #warning "configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#جے_انت

#جے_بنا_تعریف config_MTIMECMP_ادھار_پتہ
    #warning "configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#جے_انت

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#جے_تعریف_شدہ config_TASK_RETURN_پتہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    config_TASK_RETURN_پتہ
#وإلا
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    prvTaskExitError
#جے_انت

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
 * to use a statically allocated array as the interrupt stack.  Alternative leave
 * configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
 * linker variable names __freertos_irq_stack_top has the same value as the top
 * of the stack used by main.  Using the linker script method will repurpose the
 * stack that was used by main before the scheduler was started for use as the
 * interrupt stack after the scheduler has started. */
#جے_تعریف_شدہ config_ISR_ڈھیر_ناپ_الفاظ
ساكن __attribute__( ( aligned( 16 ) ) ) ڈھیر_Type_t xISRStack[ config_ISR_ڈھیر_ناپ_الفاظ ] = { 0 };
ثابت ڈھیر_Type_t x_ISRStack_چوٹی = ( ڈھیر_Type_t ) &( xISRStack[ config_ISR_ڈھیر_ناپ_الفاظ & ~پورٹ_BYTE_ALIGNMENT_نقاب ] );

/* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
 * the task stacks, and so will legitimately appear in many positions within
 * the ISR stack. */
    #تعریف_کرو پورٹ_ISR_ڈھیر_FILL_BYTE    0xee
#وإلا
    خارجي ثابت uint32_t __freertos_irq_stack_top[];
    ثابت ڈھیر_Type_t x_ISRStack_چوٹی = ( ڈھیر_Type_t ) __freertos_irq_stack_top;
#جے_انت

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورٹ_تیاری_Timer_رکاوٹ( فراغ ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ull_اگلا_ویلا = 0ULL;
ثابت uint64_t * pull_اگلا_ویلا = &ull_اگلا_ویلا;
ثابت size_t uxTimerIncrementsForOneTick = ( size_t ) ( ( configCPU_CLOCK_HZ ) / ( config_TICK_شرح_HZ ) ); /* Assumes increment won't go over 32-bits. */
متطاير uint64_t * pull_Machine_Timer_Compare_رجسٹر = عدم;

/* Holds the critical nesting value - deliberately non-zero at start up to
 * ensure interrupts are not accidentally enabled before the scheduler starts. */
size_t xCriticalNesting = ( size_t ) 0xaaaaaaaa;
size_t * pxCriticalNesting = &xCriticalNesting;

/* Used to catch tasks that attempt to return from their implementing function. */
size_t x_Task_Return_پتہ = ( size_t ) پورٹ_TASK_RETURN_پتہ;

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
 * stack checking.  A problem in the ISR stack will trigger an assert, not call
 * the stack overflow hook function (because the stack overflow hook is specific
 * to a task stack, not the ISR stack). */
#إذا defined( config_ISR_ڈھیر_ناپ_الفاظ ) && ( config_CHECK_FOR_ڈھیر_حد_توں_ودھ > 2 )
    #warning "This path not tested, or even compiled yet."

    ساكن ثابت uint8_t uc_Expected_ڈھیر_بائٹاں[] =
    {
        پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, \
        پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, \
        پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, \
        پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, \
        پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE, پورٹ_ISR_ڈھیر_FILL_BYTE
    }; \

    #تعریف_کرو پورٹ_CHECK_ISR_ڈھیر()    configASSERT( ( memcmp( ( فراغ * ) xISRStack, ( فراغ * ) uc_Expected_ڈھیر_بائٹاں, حجم( uc_Expected_ڈھیر_بائٹاں ) ) == 0 ) )
#وإلا /* if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 ) */
    /* Define the function away. */
    #تعریف_کرو پورٹ_CHECK_ISR_ڈھیر()
#جے_انت /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

ساكن فراغ prvTaskExitError( فراغ )
{
    متطاير uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( xCriticalNesting == ~0UL );
    پورٹ_DISABLE_INTERRUPTS();

    طالما( ulDummy == 0 )
    {
        /* This file calls prvTaskExitError() after the scheduler has been
         * started to remove a compiler warning about the function being
         * defined but never called.  ulDummy is used purely to quieten other
         * warnings about code appearing after this function is called - making
         * ulDummy volatile makes the compiler think the function could return
         * and therefore not output an 'unreachable code' warning for code that
         * appears after it. */
    }
}
/*-----------------------------------------------------------*/

#إذا ( config_MTIME_ادھار_پتہ != 0 ) && ( config_MTIMECMP_ادھار_پتہ != 0 )

    فراغ v_پورٹ_تیاری_Timer_رکاوٹ( فراغ )
    {
        uint32_t ul_Current_ویلا_بلند, ul_Current_ویلا_کم;
        متطاير uint32_t * ثابت pul_ویلا_بلند = ( uint32_t * ) ( ( config_MTIME_ادھار_پتہ ) + 4UL ); /* 8-byte type so high 32-bit word is 4 bytes up. */
        متطاير uint32_t * ثابت pul_ویلا_کم = ( uint32_t * ) ( config_MTIME_ادھار_پتہ );
        متطاير uint32_t ulHartId;

        __asm متطاير ( "csrr %0, 0xf14" : "=r" ( ulHartId ) ); /* 0xf14 is HART ID. */

        pull_Machine_Timer_Compare_رجسٹر = ( متطاير uint64_t * ) ( config_MTIMECMP_ادھار_پتہ + ( ulHartId * حجم( uint64_t ) ) );

        افعل
        {
            ul_Current_ویلا_بلند = *pul_ویلا_بلند;
            ul_Current_ویلا_کم = *pul_ویلا_کم;
        } طالما( ul_Current_ویلا_بلند != *pul_ویلا_بلند );

        ull_اگلا_ویلا = ( uint64_t ) ul_Current_ویلا_بلند;
        ull_اگلا_ویلا <<= 32ULL; /* High 4-byte word is 32-bits up. */
        ull_اگلا_ویلا |= ( uint64_t ) ul_Current_ویلا_کم;
        ull_اگلا_ویلا += ( uint64_t ) uxTimerIncrementsForOneTick;
        *pull_Machine_Timer_Compare_رجسٹر = ull_اگلا_ویلا;

        /* Prepare the time to use after the next tick interrupt. */
        ull_اگلا_ویلا += ( uint64_t ) uxTimerIncrementsForOneTick;
    }

#جے_انت /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    خارجي فراغ x_پورٹ_شروع_پہلا_Task( فراغ );

    #إذا ( configASSERT_DEFINED == 1 )
    {
        /* Check alignment of the interrupt stack - which is the same as the
         * stack that was being used by main() prior to the scheduler being
         * started. */
        configASSERT( ( x_ISRStack_چوٹی & پورٹ_BYTE_ALIGNMENT_نقاب ) == 0 );

        #جے_تعریف_شدہ config_ISR_ڈھیر_ناپ_الفاظ
        {
            memset( ( فراغ * ) xISRStack, پورٹ_ISR_ڈھیر_FILL_BYTE, حجم( xISRStack ) );
        }
        #جے_انت /* configISR_STACK_SIZE_WORDS */
    }
    #جے_انت /* configASSERT_DEFINED */

    /* If there is a CLINT then it is ok to use the default implementation
     * in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
     * configure whichever clock is to be used to generate the tick interrupt. */
    v_پورٹ_تیاری_Timer_رکاوٹ();

    #إذا ( ( config_MTIME_ادھار_پتہ != 0 ) && ( config_MTIMECMP_ادھار_پتہ != 0 ) )
    {
        /* Enable mtime and external interrupts.  1<<7 for timer interrupt,
         * 1<<11 for external interrupt.  _RB_ What happens here when mtime is
         * not present as with pulpino? */
        __asm متطاير ( "csrs 0x304, %0" ::"r" ( 0x880 ) ); /* 0x304 is mie. */
    }
    #جے_انت /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

    x_پورٹ_شروع_پہلا_Task();

    /* Should not get here as after calling xPortStartFirstTask() only tasks
     * should be executing. */
    أرجع pdFAIL;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    /* Not implemented. */
    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/
