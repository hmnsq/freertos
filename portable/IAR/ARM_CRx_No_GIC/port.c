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

/* Standard includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

#ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #ਜੇ ( configMAX_PRIORITIES > 32 )
        #ਗਲਤੀ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION can only be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 when configMAX_PRIORITIES is less than or equal ਮੰਜ਼ਿਲ 32.  It is very rare that a system requires ਹੋਰ than 10 ਮੰਜ਼ਿਲ 15 difference priorities as tasks that share a ਤਰਜੀਹ will time ਟੁਕੜਾ.
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ
    #ਗਲਤੀ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ() must be defined ਵਿੱਚ_2 FreeRTOSConfig.h ਮੰਜ਼ਿਲ call the function that sets ਉੱਪਰ the tick ਰੁਕਾਵਟ.
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_CLEAR_TICK_ਰੁਕਾਵਟ
    #ਗਲਤੀ config_CLEAR_TICK_ਰੁਕਾਵਟ must be defined ਵਿੱਚ_2 FreeRTOSConfig.h ਮੰਜ਼ਿਲ clear which ever ਰੁਕਾਵਟ was ਵਰਤਿਆ ਮੰਜ਼ਿਲ generate the tick ਰੁਕਾਵਟ.
#ਜੇ_ਅੰਤ

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_FLOATING_ਬਿੰਦੂ_CONTEXT    ( ( ਢੇਰ_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_SPSR                 ( ( ਢੇਰ_Type_t ) 0x1f ) /* System mode, ARM mode, IRQ enabled FIQ enabled. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਦੋਆਧਾਰੀ_ਅੰਕ               ( ( ਢੇਰ_Type_t ) 0x20 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਪਤਾ           ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APSR_ਬਹੁਲਕ_ਬਿੱਟ_ਨਕਾਬ          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APSR_USER_ਬਹੁਲਕ               ( 0x10 )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_TASK_RETURN_ਪਤਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    config_TASK_RETURN_ਪਤਾ
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    prvTaskExitError
#ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Restore_Task_Context( ਖਾਲੀ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
ਅਸਥਿਰ uint32_t ulCriticalNesting = 9999UL;

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
ਅਸਥਿਰ uint32_t ul_ਪੋਰਟ_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
ਅਸਥਿਰ uint32_t ul_ਪੋਰਟ_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
ਅਸਥਿਰ uint32_t ul_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting = 0UL;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਨਿਰਾ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਨਿਰਾ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਨਿਰਾ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_INITIAL_SPSR;

    ਜੇ( ( ( uint32_t ) px_ਕੋਡ & ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਪਤਾ ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ |= ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਦੋਆਧਾਰੀ_ਅੰਕ;
    }

    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Next the return address, which in this case is the start of the task. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Next all the registers other than the stack pointer. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ; /* R14 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x12121212;              /* R12 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x11111111;              /* R11 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x10101010;              /* R10 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x09090909;              /* R9 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x08080808;              /* R8 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x07070707;              /* R7 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x06060606;              /* R6 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x05050505;              /* R5 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x04040404;              /* R4 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x03030303;              /* R3 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x02020202;              /* R2 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x01010101;              /* R1 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;            /* R0 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_CRITICAL_NESTING;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_FLOATING_ਬਿੰਦੂ_CONTEXT;

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting == ~0UL );
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    ਲਈ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm ਅਸਥਿਰ ( "MRS %0, APSR" : "=r" ( ulAPSR ) );

    ulAPSR &= ਪੋਰਟ_APSR_ਬਹੁਲਕ_ਬਿੱਟ_ਨਕਾਬ;
    configASSERT( ulAPSR != ਪੋਰਟ_APSR_USER_ਬਹੁਲਕ );

    ਜੇ( ulAPSR != ਪੋਰਟ_APSR_USER_ਬਹੁਲਕ )
    {
        /* Start the timer that generates the tick ISR. */
        ਪੋਰਟ_DISABLE_INTERRUPTS();
        config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ();

        /* Start the first task executing. */
        v_ਪੋਰਟ_Restore_Task_Context();
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( ਖਾਲੀ ) prvTaskExitError;
    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ਜੇ( ulCriticalNesting == 1 )
    {
        configASSERT( ul_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    ਜੇ( ulCriticalNesting > ਪੋਰਟ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ਜੇ( ulCriticalNesting == ਪੋਰਟ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            ਪੋਰਟ_ENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ FreeRTOS_Tick_Handler( ਖਾਲੀ )
{
    uint32_t ul_ਰੁਕਾਵਟ_ਸਥਿਤੀ;

    ul_ਰੁਕਾਵਟ_ਸਥਿਤੀ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();

    /* Increment the RTOS tick. */
    ਜੇ( xTaskIncrementTick() != pdFALSE )
    {
        ul_ਪੋਰਟ_Yield_Required = pdTRUE;
    }

    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ul_ਰੁਕਾਵਟ_ਸਥਿਤੀ );

    config_CLEAR_TICK_ਰੁਕਾਵਟ();
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU( ਖਾਲੀ )
{
    uint32_t ulInitialFPSCR = 0;

    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ul_ਪੋਰਟ_Task_Has_FPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    __asm ਅਸਥਿਰ ( "FMXR  FPSCR, %0" ::"r" ( ulInitialFPSCR ) );
}
/*-----------------------------------------------------------*/
