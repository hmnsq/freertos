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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "portmacro.h"

/* Standard includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "string.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_CLINT_ਅਧਾਰ_ਪਤਾ
    #warning "The configCLINT_BASE_ADDRESS constant has been deprecated.  configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS are currently being derived from the (possibly 0) configCLINT_BASE_ADDRESS setting.  Please update to define configMTIME_BASE_ADDRESS and configMTIMECMP_BASE_ADDRESS directly in place of configCLINT_BASE_ADDRESS.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_MTIME_ਅਧਾਰ_ਪਤਾ
    #warning "configMTIME_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtime register then set configMTIME_BASE_ADDRESS to the mapped address.  Otherwise set configMTIME_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_MTIMECMP_ਅਧਾਰ_ਪਤਾ
    #warning "configMTIMECMP_BASE_ADDRESS must be defined in FreeRTOSConfig.h.  If the target chip includes a memory-mapped mtimecmp register then set configMTIMECMP_BASE_ADDRESS to the mapped address.  Otherwise set configMTIMECMP_BASE_ADDRESS to 0.  See www.FreeRTOS.org/Using-FreeRTOS-on-RISC-V.html"
#ਜੇ_ਅੰਤ

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_TASK_RETURN_ਪਤਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    config_TASK_RETURN_ਪਤਾ
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    prvTaskExitError
#ਜੇ_ਅੰਤ

/* The stack used by interrupt service routines.  Set configISR_STACK_SIZE_WORDS
 * to use a statically allocated array as the interrupt stack.  Alternative leave
 * configISR_STACK_SIZE_WORDS undefined and update the linker script so that a
 * linker variable names __freertos_irq_stack_top has the same value as the top
 * of the stack used by main.  Using the linker script method will repurpose the
 * stack that was used by main before the scheduler was started for use as the
 * interrupt stack after the scheduler has started. */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_ISR_ਢੇਰ_ਮਾਪ_ਸ਼ਬਦ
ਸਥਿਰ __attribute__( ( aligned( 16 ) ) ) ਢੇਰ_Type_t xISRStack[ config_ISR_ਢੇਰ_ਮਾਪ_ਸ਼ਬਦ ] = { 0 };
ਅਚਲ ਢੇਰ_Type_t x_ISRStack_ਸਿਖਰ = ( ਢੇਰ_Type_t ) &( xISRStack[ config_ISR_ਢੇਰ_ਮਾਪ_ਸ਼ਬਦ & ~ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ] );

/* Don't use 0xa5 as the stack fill bytes as that is used by the kernel for
 * the task stacks, and so will legitimately appear in many positions within
 * the ISR stack. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE    0xee
#ਨਹੀਂਤਾਂ
    ਬਾਹਰੀ ਅਚਲ uint32_t __freertos_irq_stack_top[];
    ਅਚਲ ਢੇਰ_Type_t x_ISRStack_ਸਿਖਰ = ( ਢੇਰ_Type_t ) __freertos_irq_stack_top;
#ਜੇ_ਅੰਤ

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* Used to program the machine timer compare register. */
uint64_t ull_ਅਗਲਾ_ਸਮਾਂ = 0ULL;
ਅਚਲ uint64_t * pull_ਅਗਲਾ_ਸਮਾਂ = &ull_ਅਗਲਾ_ਸਮਾਂ;
ਅਚਲ size_t uxTimerIncrementsForOneTick = ( size_t ) ( ( configCPU_CLOCK_HZ ) / ( config_TICK_ਦਰ_HZ ) ); /* Assumes increment won't go over 32-bits. */
ਅਸਥਿਰ uint64_t * pull_Machine_Timer_Compare_ਰਜਿਸਟਰ = ਨਿਰਾ;

/* Holds the critical nesting value - deliberately non-zero at start up to
 * ensure interrupts are not accidentally enabled before the scheduler starts. */
size_t xCriticalNesting = ( size_t ) 0xaaaaaaaa;
size_t * pxCriticalNesting = &xCriticalNesting;

/* Used to catch tasks that attempt to return from their implementing function. */
size_t x_Task_Return_ਪਤਾ = ( size_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ;

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
 * stack checking.  A problem in the ISR stack will trigger an assert, not call
 * the stack overflow hook function (because the stack overflow hook is specific
 * to a task stack, not the ISR stack). */
#ਜੇ defined( config_ISR_ਢੇਰ_ਮਾਪ_ਸ਼ਬਦ ) && ( config_CHECK_FOR_ਢੇਰ_ਉਛਾਲ > 2 )
    #warning "This path not tested, or even compiled yet."

    ਸਥਿਰ ਅਚਲ uint8_t uc_Expected_ਢੇਰ_ਬਾਈਟਾਂ[] =
    {
        ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, \
        ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, \
        ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, \
        ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, \
        ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE
    }; \

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHECK_ISR_ਢੇਰ()    configASSERT( ( memcmp( ( ਖਾਲੀ * ) xISRStack, ( ਖਾਲੀ * ) uc_Expected_ਢੇਰ_ਬਾਈਟਾਂ, ਆਕਾਰ( uc_Expected_ਢੇਰ_ਬਾਈਟਾਂ ) ) == 0 ) )
#ਨਹੀਂਤਾਂ /* if defined( configISR_STACK_SIZE_WORDS ) && ( configCHECK_FOR_STACK_OVERFLOW > 2 ) */
    /* Define the function away. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHECK_ISR_ਢੇਰ()
#ਜੇ_ਅੰਤ /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ )
{
    ਅਸਥਿਰ uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( xCriticalNesting == ~0UL );
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    ਜਦੋਂ( ulDummy == 0 )
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

#ਜੇ ( config_MTIME_ਅਧਾਰ_ਪਤਾ != 0 ) && ( config_MTIMECMP_ਅਧਾਰ_ਪਤਾ != 0 )

    ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
    {
        uint32_t ul_Current_ਸਮਾਂ_ਉੱਚਾ, ul_Current_ਸਮਾਂ_ਨੀਵਾਂ;
        ਅਸਥਿਰ uint32_t * ਅਚਲ pul_ਸਮਾਂ_ਉੱਚਾ = ( uint32_t * ) ( ( config_MTIME_ਅਧਾਰ_ਪਤਾ ) + 4UL ); /* 8-byte type so high 32-bit word is 4 bytes up. */
        ਅਸਥਿਰ uint32_t * ਅਚਲ pul_ਸਮਾਂ_ਨੀਵਾਂ = ( uint32_t * ) ( config_MTIME_ਅਧਾਰ_ਪਤਾ );
        ਅਸਥਿਰ uint32_t ulHartId;

        __asm ਅਸਥਿਰ ( "csrr %0, 0xf14" : "=r" ( ulHartId ) ); /* 0xf14 is HART ID. */

        pull_Machine_Timer_Compare_ਰਜਿਸਟਰ = ( ਅਸਥਿਰ uint64_t * ) ( config_MTIMECMP_ਅਧਾਰ_ਪਤਾ + ( ulHartId * ਆਕਾਰ( uint64_t ) ) );

        ਕਰੋ
        {
            ul_Current_ਸਮਾਂ_ਉੱਚਾ = *pul_ਸਮਾਂ_ਉੱਚਾ;
            ul_Current_ਸਮਾਂ_ਨੀਵਾਂ = *pul_ਸਮਾਂ_ਨੀਵਾਂ;
        } ਜਦੋਂ( ul_Current_ਸਮਾਂ_ਉੱਚਾ != *pul_ਸਮਾਂ_ਉੱਚਾ );

        ull_ਅਗਲਾ_ਸਮਾਂ = ( uint64_t ) ul_Current_ਸਮਾਂ_ਉੱਚਾ;
        ull_ਅਗਲਾ_ਸਮਾਂ <<= 32ULL; /* High 4-byte word is 32-bits up. */
        ull_ਅਗਲਾ_ਸਮਾਂ |= ( uint64_t ) ul_Current_ਸਮਾਂ_ਨੀਵਾਂ;
        ull_ਅਗਲਾ_ਸਮਾਂ += ( uint64_t ) uxTimerIncrementsForOneTick;
        *pull_Machine_Timer_Compare_ਰਜਿਸਟਰ = ull_ਅਗਲਾ_ਸਮਾਂ;

        /* Prepare the time to use after the next tick interrupt. */
        ull_ਅਗਲਾ_ਸਮਾਂ += ( uint64_t ) uxTimerIncrementsForOneTick;
    }

#ਜੇ_ਅੰਤ /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ਬਾਹਰੀ ਖਾਲੀ x_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

    #ਜੇ ( configASSERT_DEFINED == 1 )
    {
        /* Check alignment of the interrupt stack - which is the same as the
         * stack that was being used by main() prior to the scheduler being
         * started. */
        configASSERT( ( x_ISRStack_ਸਿਖਰ & ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) == 0 );

        #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_ISR_ਢੇਰ_ਮਾਪ_ਸ਼ਬਦ
        {
            memset( ( ਖਾਲੀ * ) xISRStack, ਪੋਰਟ_ISR_ਢੇਰ_FILL_BYTE, ਆਕਾਰ( xISRStack ) );
        }
        #ਜੇ_ਅੰਤ /* configISR_STACK_SIZE_WORDS */
    }
    #ਜੇ_ਅੰਤ /* configASSERT_DEFINED */

    /* If there is a CLINT then it is ok to use the default implementation
     * in this file, otherwise vPortSetupTimerInterrupt() must be implemented to
     * configure whichever clock is to be used to generate the tick interrupt. */
    v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    #ਜੇ ( ( config_MTIME_ਅਧਾਰ_ਪਤਾ != 0 ) && ( config_MTIMECMP_ਅਧਾਰ_ਪਤਾ != 0 ) )
    {
        /* Enable mtime and external interrupts.  1<<7 for timer interrupt,
         * 1<<11 for external interrupt.  _RB_ What happens here when mtime is
         * not present as with pulpino? */
        __asm ਅਸਥਿਰ ( "csrs 0x304, %0" ::"r" ( 0x880 ) ); /* 0x304 is mie. */
    }
    #ਜੇ_ਅੰਤ /* ( configMTIME_BASE_ADDRESS != 0 ) && ( configMTIMECMP_BASE_ADDRESS != 0 ) */

    x_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should not get here as after calling xPortStartFirstTask() only tasks
     * should be executing. */
    ਵਾਪਸ pdFAIL;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented. */
    ਲਈ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/
