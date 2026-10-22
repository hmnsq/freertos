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
* Implementation of functions defined in portable.h for the ARM CM0 port.
*----------------------------------------------------------*/

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* Constants required to manipulate the NVIC. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG             ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e010 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG             ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e014 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e018 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_INT_CTRL_REG                 ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed04 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SHPR3_REG                    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed20 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್              ( 1UL << 2UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್              ( 1UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್           ( 1UL << 0UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್       ( 1UL << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್                ( 1UL << 28UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_ಗಣ_ಬಿಟ್         ( 1UL << 26UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_CLEAR_ಬಿಟ್       ( 1UL << 25UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ            ( 255UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSV_PRI                   ( ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_PRI                  ( ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ << 24UL )

/* Constants required to set up the initial stack. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_24_ಬಿಟ್_ಸಂಖ್ಯೆ                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_MISSED_COUNTS_ಗುಣಕ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MISSED_COUNTS_ಗುಣಕ    ( 94UL )
#ಆದರೆ_ಅಂತ್ಯ

/* Constants used with memory barrier intrinsics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE    ( 15 )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configSYSTICK_CLOCK_HZ
    #ವ್ಯಾಖ್ಯಾನಿಸು configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG    ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
#ಇಲ್ಲದಿದ್ದರೆ
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG    ( 0 )
#ಆದರೆ_ಅಂತ್ಯ

/* Legacy macro for backward compatibility only.  This macro used to be used to
 * replace the function that configures the clock used to generate the tick
 * interrupt (prvSetupTimerInterrupt()), but now the function is declared weak so
 * the application writer can override it by simply defining a function of the
 * same name (vApplicationSetupTickInterrupt()). */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configOVERRIDE_DEFAULT_TICK_CONFIGURATION
    #ವ್ಯಾಖ್ಯಾನಿಸು configOVERRIDE_DEFAULT_TICK_CONFIGURATION    0
#ಆದರೆ_ಅಂತ್ಯ

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ಸ್ಥಿರ UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/* The number of SysTick increments that make up one tick period. */
#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    ಸ್ಥಿರ uint32_t ulTimerCountsForOneTick = 0;
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/* The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer. */
#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    ಸ್ಥಿರ uint32_t x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks = 0;
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/* Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    ಸ್ಥಿರ uint32_t ulStoppedTimerCompensation = 0;
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*
 * Exception handlers.
 */
ಶೂನ್ಯ x_ಪೋರ್ಟ್_Pend_SVHandler( ಶೂನ್ಯ );
ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ );
ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler( ಶೂನ್ಯ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

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
    px_ತುದಿ_ದ_ರಾಶಿ--;                                   /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_XPSR;                 /* xPSR */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;           /* PC */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) prvTaskExitError; /* LR */
    px_ತುದಿ_ದ_ರಾಶಿ -= 5;                                /* R12, R3, R2 and R1. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;     /* R0 */
    px_ತುದಿ_ದ_ರಾಶಿ -= 8;                                /* R11..R4. */

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
    configASSERT( uxCriticalNesting == ~0UL );
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    ಗಾಗಿ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler( ಶೂನ್ಯ )
{
    /* This function is no longer used, but retained for backward
     * compatibility. */
}
/*-----------------------------------------------------------*/

__asm ಶೂನ್ಯ prv_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ pxCurrentTCB;

    PRESERVE8

    /* The MSP stack is not reset as, unlike on M3/4 parts, there is no vector
     * table offset register that can be used to locate the initial stack value.
     * Not all M0 parts have the application vector table at address 0. */
/* *INDENT-OFF* */

    ldr r3, = pxCurrentTCB /* Obtain location of pxCurrentTCB. */
    ldr r1, [ r3 ]
    ldr r0, [ r1 ]         /* The first item in pxCurrentTCB is the task top of stack. */
    adds r0, # 32          /* Discard everything up to r0. */
    msr psp, r0            /* This is now the new top of stack to use in the task. */
    movs r0, # 2           /* Switch to the psp stack. */
    msr CONTROL, r0
    isb
    ತೆಗೆ_2 { r0 - r5 } /* Pop the registers that are saved automatically. */
    mov lr, r5 /* lr is now in r5. */
    ತೆಗೆ_2 { r3 } /* The return address is now in r3. */
    ತೆಗೆ_2 { r2 } /* Pop and discard the XPSR. */
    cpsie i /* The first task has its context and interrupts can be enabled. */
    bx r3 /* Finally, jump to the user defined task code. */

    ALIGN
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
    ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_PENDSV_PRI;

    ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    prv_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should not get here! */
    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ )
{
    /* Set a PendSV to request a context switch. */
    ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __dsb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );
    __isb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
    __dsb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );
    __isb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    ಆದರೆ( uxCriticalNesting == 0 )
    {
        ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

__asm uint32_t ul_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( ಶೂನ್ಯ )
{
/* *INDENT-OFF* */
    mrs r0, PRIMASK
    cpsid i
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

__asm ಶೂನ್ಯ v_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( uint32_t ul_ಮುಖವಾಡ )
{
/* *INDENT-OFF* */
    msr PRIMASK, r0
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

__asm ಶೂನ್ಯ x_ಪೋರ್ಟ್_Pend_SVHandler( ಶೂನ್ಯ )
{
    ಬಾಹ್ಯ vTaskSwitchContext
    ಬಾಹ್ಯ pxCurrentTCB

/* *INDENT-OFF* */
    PRESERVE8

    mrs r0, psp

    ldr r3, = pxCurrentTCB /* Get the location of the current TCB. */
    ldr r2, [ r3 ]

    subs r0, # 32  /* Make space for the remaining low registers. */
    str r0, [ r2 ] /* Save the new top of stack. */
    stmia r0 !, { r4 - r7 } /* Store the low registers that are not saved automatically. */
    mov r4, r8 /* Store the high registers. */
    mov r5, r9
    mov r6, r10
    mov r7, r11
    stmia r0 !, { r4 - r7 }

    ತಳ್ಳು { r3, r14 }
    cpsid i
    bl vTaskSwitchContext
    cpsie i
    ತೆಗೆ_2 { r2, r3 } /* lr goes in r3. r2 now holds tcb pointer. */

    ldr r1, [ r2 ]
    ldr r0, [ r1 ] /* The first item in pxCurrentTCB is the task top of stack. */
    adds r0, # 16  /* Move to the high registers. */
    ldmia r0 !, { r4 - r7 } /* Pop the high registers. */
    mov r8, r4
    mov r9, r5
    mov r10, r6
    mov r11, r7

    msr psp, r0   /* Remember the new top of stack for the task. */

    subs r0, # 32 /* Go back for the low registers that are not automatically restored. */
    ldmia r0 !, { r4 - r7 } /* Pop low registers.  */

    bx r3
    ALIGN
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ )
{
    uint32_t ul_ಹಿಂದಿನ_ಮುಖವಾಡ;

    ul_ಹಿಂದಿನ_ಮುಖವಾಡ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();
            /* Pend a context switch. */
            ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            traceISR_EXIT();
        }
    }
    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ul_ಹಿಂದಿನ_ಮುಖವಾಡ );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
#ಆದರೆ ( configOVERRIDE_DEFAULT_TICK_CONFIGURATION == 0 )

    __weak ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
    {
        /* Calculate the constants required to configure the tick interrupt. */
        #ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
        {
            ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_ದರ_HZ );
            x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks = ಪೋರ್ಟ್_MAX_24_ಬಿಟ್_ಸಂಖ್ಯೆ / ulTimerCountsForOneTick;
            ulStoppedTimerCompensation = ಪೋರ್ಟ್_MISSED_COUNTS_ಗುಣಕ / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

        /* Stop and clear the SysTick. */
        ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = 0UL;
        ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;

        /* Configure SysTick to interrupt at the requested rate. */
        ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_ದರ_HZ ) - 1UL;
        ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configOVERRIDE_DEFAULT_TICK_CONFIGURATION */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )

    __weak ಶೂನ್ಯ v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ಸಮಯ )
    {
        uint32_t ul_Reload_ಮೌಲ್ಯ, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ಎಡ;
        TickType_t x_Modifiable_Idle_ಸಮಯ;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ಆದರೆ( x_Expected_Idle_ಸಮಯ > x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ಸಮಯ = x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __disable_irq();
        __dsb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );
        __isb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ಆದರೆ( e_Task_Confirm_Sleep_ಬಹುಲಕ_ಸ್ಥಿತಿ() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the __disable_irq()
             * call above. */
            __enable_irq();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_ಎಡ = ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG;

            ಆದರೆ( ul_Sys_Tick_Decrements_ಎಡ == 0 )
            {
                ul_Sys_Tick_Decrements_ಎಡ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_ಮೌಲ್ಯ = ul_Sys_Tick_Decrements_ಎಡ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_ಸಮಯ - 1UL ) );

            ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_INT_CTRL_REG & ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_ಗಣ_ಬಿಟ್ ) != 0 )
            {
                ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_CLEAR_ಬಿಟ್;
                ul_Reload_ಮೌಲ್ಯ -= ulTimerCountsForOneTick;
            }

            ಆದರೆ( ul_Reload_ಮೌಲ್ಯ > ulStoppedTimerCompensation )
            {
                ul_Reload_ಮೌಲ್ಯ -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ul_Reload_ಮೌಲ್ಯ;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;

            /* Restart SysTick. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_ಸಮಯ = x_Expected_Idle_ಸಮಯ;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_ಸಮಯ );

            ಆದರೆ( x_Modifiable_Idle_ಸಮಯ > 0 )
            {
                __dsb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );
                __wfi();
                __isb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_ಸಮಯ );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the __disable_irq() call above. */
            __enable_irq();
            __dsb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );
            __isb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __disable_irq();
            __dsb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );
            __isb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ );

            /* Determine whether the SysTick has already counted to zero. */
            ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG & ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್ ) != 0 )
            {
                uint32_t ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_ಮೌಲ್ಯ - ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                ಆದರೆ( ( ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ <= ulStoppedTimerCompensation ) || ( ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ = ( ulTimerCountsForOneTick - 1UL );
                }

                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_ಸಮಯ - 1UL;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ಎಡ = ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG;
                #ಆದರೆ ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG != ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    ಆದರೆ( ul_Sys_Tick_Decrements_ಎಡ == 0 )
                    {
                        ul_Sys_Tick_Decrements_ಎಡ = ul_Reload_ಮೌಲ್ಯ;
                    }
                }
                #ಆದರೆ_ಅಂತ್ಯ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_ಸಮಯ * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ಎಡ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
            #ಆದರೆ ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG == ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
            {
                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ulTimerCountsForOneTick - 1UL;
            }
            #ಇಲ್ಲದಿದ್ದರೆ
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್;

                ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG & ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0;
                }

                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ulTimerCountsForOneTick - 1UL;
                ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
            }
            #ಆದರೆ_ಅಂತ್ಯ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_ಹೆಜ್ಜೆ_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __enable_irq();
        }
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/
