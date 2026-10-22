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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Constants required to manipulate the NVIC. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL       ( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e010 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು       ( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e014 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SHPR3_REG          ( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed20 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK        0x00000004
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_INT        0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE     0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ  ( 255UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSV_PRI         ( ( ( uint32_t ) ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ ) << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_PRI        ( ( ( uint32_t ) ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ ) << 24UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_VECTACTIVE_ಮುಖವಾಡ         ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPCCR                   ( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASPEN_AND_LSPEN_ಬಿಟ್ಟುಗಳು    ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_XPSR            ( 0x01000000 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_EXC_RETURN      ( 0xfffffffd )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_TASK_RETURN_ವಿಳಾಸ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    config_TASK_RETURN_ವಿಳಾಸ
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    prvTaskExitError
#ಆದರೆ_ಅಂತ್ಯ

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆರಂಭ_ವಿಳಾಸ_ಮುಖವಾಡ    ( ( ರಾಶಿ_Type_t ) 0xfffffffeUL )

/* The priority used by the kernel is assigned to a variable to make access
 * from inline assembler easier. */
ಸ್ಥಿರಾಂಕ uint32_t ul_Kernel_ಆದ್ಯತೆ = ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ಸ್ಥಿರ uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

/*
 * Setup the timer to generate the tick interrupts.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*
 * Exception handlers.
 */
ಶೂನ್ಯ SysTick_Handler( ಶೂನ್ಯ );

/*
 * Functions defined in port_asm.asm.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_VFP( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

/* This exists purely to allow the const to be used from within the
 * port_asm.asm assembly file. */
ಸ್ಥಿರಾಂಕ uint32_t ul_Max_Syscall_ಅಡಚಣೆ_ಆದ್ಯತೆ_Const = config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_XPSR;                                    /* xPSR */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ ) & ಪೋರ್ಟ್_ಆರಂಭ_ವಿಳಾಸ_ಮುಖವಾಡ; /* PC */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ;             /* LR */

    /* Save code space by skipping register initialisation. */
    px_ತುದಿ_ದ_ರಾಶಿ -= 5;                            /* R12, R3, R2 and R1. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_EXC_RETURN;

    px_ತುದಿ_ದ_ರಾಶಿ -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    ಗಾಗಿ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
     * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
    configASSERT( ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ ) );

    /* Make PendSV and SysTick the lowest priority interrupts. */
    *( ಪೋರ್ಟ್_NVIC_SHPR3_REG ) |= ಪೋರ್ಟ್_NVIC_PENDSV_PRI;
    *( ಪೋರ್ಟ್_NVIC_SHPR3_REG ) |= ಪೋರ್ಟ್_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Initialise the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    v_ಪೋರ್ಟ್_Enable_VFP();

    /* Lazy save always. */
    *( ಪೋರ್ಟ್_FPCCR ) |= ಪೋರ್ಟ್_ASPEN_AND_LSPEN_ಬಿಟ್ಟುಗಳು;

    /* Start the first task. */
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should not get here! */
    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ )
{
    /* Set a PendSV to request a context switch. */
    *( ಪೋರ್ಟ್_NVIC_INT_CTRL ) = ಪೋರ್ಟ್_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
    ulCriticalNesting++;
    __DSB();
    __ISB();

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ಆದರೆ( ulCriticalNesting == 1 )
    {
        configASSERT( ( ( *( ಪೋರ್ಟ್_NVIC_INT_CTRL ) ) & ಪೋರ್ಟ್_VECTACTIVE_ಮುಖವಾಡ ) == 0 );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    ಆದರೆ( ulCriticalNesting == 0 )
    {
        ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ SysTick_Handler( ಶೂನ್ಯ )
{
    uint32_t ulDummy;

    ulDummy = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();
    traceISR_ENTER();
    {
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();
            /* Pend a context switch. */
            *( ಪೋರ್ಟ್_NVIC_INT_CTRL ) = ಪೋರ್ಟ್_NVIC_PENDSVSET;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            traceISR_EXIT();
        }
    }
    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ulDummy );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    /* Configure SysTick to interrupt at the requested rate. */
    *( ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು ) = ( configCPU_CLOCK_HZ / config_TICK_ದರ_HZ ) - 1UL;
    *( ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL ) = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK | ಪೋರ್ಟ್_NVIC_SYSTICK_INT | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE;
}