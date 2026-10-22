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
* Implementation of functions defined in portable.h for the ARM CM4F port.
*----------------------------------------------------------*/

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Constants required to manipulate the NVIC. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CTRL       ( ( ਅਸਥਿਰ uint32_t * ) 0xe000e010 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ       ( ( ਅਸਥਿਰ uint32_t * ) 0xe000e014 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SHPR3_REG          ( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed20 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK        0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_INT        0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ENABLE     0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ  ( 255UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSV_PRI         ( ( ( uint32_t ) ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_PRI        ( ( ( uint32_t ) ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) << 24UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_VECTACTIVE_ਨਕਾਬ         ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPCCR                   ( ( ਅਸਥਿਰ uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASPEN_AND_LSPEN_ਬਿੱਟ    ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_XPSR            ( 0x01000000 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_EXC_RETURN      ( 0xfffffffd )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_TASK_RETURN_ਪਤਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    config_TASK_RETURN_ਪਤਾ
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    prvTaskExitError
#ਜੇ_ਅੰਤ

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਤਾ_ਨਕਾਬ    ( ( ਢੇਰ_Type_t ) 0xfffffffeUL )

/* The priority used by the kernel is assigned to a variable to make access
 * from inline assembler easier. */
ਅਚਲ uint32_t ul_Kernel_ਤਰਜੀਹ = ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ਸਥਿਰ uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

/*
 * Setup the timer to generate the tick interrupts.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/*
 * Exception handlers.
 */
ਖਾਲੀ SysTick_Handler( ਖਾਲੀ );

/*
 * Functions defined in port_asm.asm.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Enable_VFP( ਖਾਲੀ );
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

/* This exists purely to allow the const to be used from within the
 * port_asm.asm assembly file. */
ਅਚਲ uint32_t ul_Max_Syscall_ਰੁਕਾਵਟ_ਤਰਜੀਹ_Const = config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_XPSR;                                    /* xPSR */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ( ਢੇਰ_Type_t ) px_ਕੋਡ ) & ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਤਾ_ਨਕਾਬ; /* PC */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ;             /* LR */

    /* Save code space by skipping register initialisation. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 5;                            /* R12, R3, R2 and R1. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_EXC_RETURN;

    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

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
    configASSERT( ulCriticalNesting == ~0UL );
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    ਲਈ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( ( config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) );

    /* Make PendSV and SysTick the lowest priority interrupts. */
    *( ਪੋਰਟ_NVIC_SHPR3_REG ) |= ਪੋਰਟ_NVIC_PENDSV_PRI;
    *( ਪੋਰਟ_NVIC_SHPR3_REG ) |= ਪੋਰਟ_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Initialise the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    v_ਪੋਰਟ_Enable_VFP();

    /* Lazy save always. */
    *( ਪੋਰਟ_FPCCR ) |= ਪੋਰਟ_ASPEN_AND_LSPEN_ਬਿੱਟ;

    /* Start the first task. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should not get here! */
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

ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ )
{
    /* Set a PendSV to request a context switch. */
    *( ਪੋਰਟ_NVIC_INT_CTRL ) = ਪੋਰਟ_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    ਪੋਰਟ_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
    __DSB();
    __ISB();

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ਜੇ( ulCriticalNesting == 1 )
    {
        configASSERT( ( ( *( ਪੋਰਟ_NVIC_INT_CTRL ) ) & ਪੋਰਟ_VECTACTIVE_ਨਕਾਬ ) == 0 );
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    ਜੇ( ulCriticalNesting == 0 )
    {
        ਪੋਰਟ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ SysTick_Handler( ਖਾਲੀ )
{
    uint32_t ulDummy;

    ulDummy = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();
    traceISR_ENTER();
    {
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();
            /* Pend a context switch. */
            *( ਪੋਰਟ_NVIC_INT_CTRL ) = ਪੋਰਟ_NVIC_PENDSVSET;
        }
        ਨਹੀਂਤਾਂ
        {
            traceISR_EXIT();
        }
    }
    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    /* Configure SysTick to interrupt at the requested rate. */
    *( ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ ) = ( configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ ) - 1UL;
    *( ਪੋਰਟ_NVIC_SYSTICK_CTRL ) = ਪੋਰਟ_NVIC_SYSTICK_CLK | ਪੋਰਟ_NVIC_SYSTICK_INT | ਪੋਰਟ_NVIC_SYSTICK_ENABLE;
}