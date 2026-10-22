/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: MIT AND BSD-3-Clause
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

/*----------------------------------------------------------------------
 * Implementation of functions defined in portable.h for the RP2040 port.
 *----------------------------------------------------------------------*/

#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "rp2040_config.h"
#ಅನ್ತರ್ಭಾವ "hardware/clocks.h"
#ಅನ್ತರ್ಭಾವ "hardware/exception.h"

/*
 * LIB_PICO_MULTICORE == 1, if we are linked with pico_multicore (note that
 * the non SMP FreeRTOS_Kernel is not linked with pico_multicore itself). We
 * use this flag to determine if we need multi-core functionality.
 */
#ಆದರೆ ( LIB_PICO_MULTICORE == 1 )
    #ಅನ್ತರ್ಭಾವ "pico/multicore.h"
#ಆದರೆ_ಅಂತ್ಯ /* LIB_PICO_MULTICORE */

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
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MISSED_COUNTS_ಗುಣಕ    ( 45UL )
#ಆದರೆ_ಅಂತ್ಯ

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_TASK_RETURN_ವಿಳಾಸ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    config_TASK_RETURN_ವಿಳಾಸ
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    prvTaskExitError
#ಆದರೆ_ಅಂತ್ಯ

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*
 * Exception handlers.
 */
ಶೂನ್ಯ x_ಪೋರ್ಟ್_Pend_SVHandler( ಶೂನ್ಯ ) __attribute__( ( naked ) );
ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ );
ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler( ಶೂನ್ಯ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ಸ್ಥಿರ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ ) __attribute__( ( naked ) );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. This is initialized to 0 to allow vPortEnter/ExitCritical
 * to be called before the scheduler is started */
#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
    ಸ್ಥಿರ UBaseType_t uxCriticalNesting;
#ಇಲ್ಲದಿದ್ದರೆ /* #if ( configNUMBER_OF_CORES == 1 ) */
UBaseType_t uxCriticalNestings[ config_ಸಂಖ್ಯೆ_ದ_CORES ] = { 0 };
#ಆದರೆ_ಅಂತ್ಯ /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

#ಆದರೆ ( configSUPPORT_PICO_SYNC_INTEROP == 1 || config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
    #ಅನ್ತರ್ಭಾವ "hardware/irq.h"
#ಆದರೆ_ಅಂತ್ಯ /* ( configSUPPORT_PICO_SYNC_INTEROP == 1 || configNUMBER_OF_CORES > 1 ) */
#ಆದರೆ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    #ಅನ್ತರ್ಭಾವ "pico/lock_core.h"
    #ಅನ್ತರ್ಭಾವ "event_groups.h"
    #ಆದರೆ config_SUPPORT_STATIC_ಹಂಚಿಕೆ
        ಸ್ಥಿರ Static_Event_ಗುಂಪು_t x_Static_Event_ಗುಂಪು;
        #ವ್ಯಾಖ್ಯಾನಿಸು p_Event_ಗುಂಪು    ( &x_Static_Event_ಗುಂಪು )
    #ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_STATIC_ALLOCATION */
    ಸ್ಥಿರ Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು;
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
        ಸ್ಥಿರ Event_ಬಿಟ್ಟುಗಳು_t ux_Cross_Core_Event_ಬಿಟ್ಟುಗಳು;
        ಸ್ಥಿರ spin_ಬೀಗ_t * px_Cross_Core_Spin_ಬೀಗ; /* protects uxCrossCoreEventBits */
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_PICO_SYNC_INTEROP */

/*
 * The number of SysTick increments that make up one tick period.
 */
#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    ಸ್ಥಿರ uint32_t ulTimerCountsForOneTick = 0;
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    ಸ್ಥಿರ uint32_t x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks = 0;
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    ಸ್ಥಿರ uint32_t ulStoppedTimerCompensation = 0;
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#ವ್ಯಾಖ್ಯಾನಿಸು INVALID_PRIMARY_CORE_ಅಂಕೆ    0xffu
/* The primary core number (the own which has the SysTick handler) */
ಸ್ಥಿರ uint8_t uc_Primary_Core_ಅಂಕೆ = INVALID_PRIMARY_CORE_ಅಂಕೆ;

/* Note: portIS_FREE_RTOS_CORE() also returns false until the scheduler is started */
#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES != 1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_ಅಂಕೆ != INVALID_PRIMARY_CORE_ಅಂಕೆ )
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_ಅಂಕೆ == get_core_ಅಂಕೆ() )
#ಆದರೆ_ಅಂತ್ಯ

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_ತುದಿ_ದ_ರಾಶಿ--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_XPSR;                        /* xPSR */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;                  /* PC */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ; /* LR */
    px_ತುದಿ_ದ_ರಾಶಿ -= 5;                                       /* R12, R3, R2 and R1. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;            /* R0 */
    px_ತುದಿ_ದ_ರಾಶಿ -= 8;                                       /* R11..R4. */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ). */
    panic_unsupported();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler( ಶೂನ್ಯ )
{
    /* This function is no longer used, but retained for backward
     * compatibility. */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ )
{
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
        __asm ಅಸ್ಥಿರ (
            "   .syntax unified             \n"
            "   ldr  r2, pxCurrentTCBConst1 \n" /* Obtain location of pxCurrentTCB. */
            "   ldr  r3, [r2]               \n"
            "   ldr  r0, [r3]               \n" /* The first item in pxCurrentTCB is the task top of stack. */
            "   adds r0, #32                \n" /* Discard everything up to r0. */
            "   msr  psp, r0                \n" /* This is now the new top of stack to use in the task. */
            "   movs r0, #2                 \n" /* Switch to the psp stack. */
            "   msr  CONTROL, r0            \n"
            "   isb                         \n"
            "   pop  {r0-r5}                \n" /* Pop the registers that are saved automatically. */
            "   mov  lr, r5                 \n" /* lr is now in r5. */
            "   pop  {r3}                   \n" /* Return address is now in r3. */
            "   pop  {r2}                   \n" /* Pop and discard XPSR. */
            "   cpsie i                     \n" /* The first task has its context and interrupts can be enabled. */
            "   bx   r3                     \n" /* Finally, jump to the user defined task code. */
            "   .align 4                       \n"
            "pxCurrentTCBConst1: .word pxCurrentTCB\n"
            );
    #ಇಲ್ಲದಿದ್ದರೆ /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm ಅಸ್ಥಿರ (
            "    .syntax unified                    \n"
            #ಆದರೆ config_RESET_ರಾಶಿ_ಸೂಚಕ
                "   ldr  r0, =0xE000ED08            \n" /* Use the NVIC offset register to locate the stack. */
                "   ldr r0, [r0]                    \n"
                "   ldr r0, [r0]                    \n"
                "   msr msp, r0                     \n" /* Set the msp back to the start of the stack. */
            #ಆದರೆ_ಅಂತ್ಯ /* configRESET_STACK_POINTER */
                "   adr r1, ulAsmLocals             \n" /* Get the location of the current TCB for the current core. */
                "   ldmia r1!, {r2, r3}             \n"
                "   ldr r2, [r2]                    \n" /* r2 = Core number */
                "   lsls r2, #2                     \n"
                "   ldr r3, [r3, r2]                \n" /* r3 = pxCurrentTCBs[get_core_num()] */
                "   ldr  r0, [r3]                   \n" /* The first item in pxCurrentTCB is the task top of stack. */
                "   adds r0, #32                    \n" /* Discard everything up to r0. */
                "   msr  psp, r0                    \n" /* This is now the new top of stack to use in the task. */
                "   movs r0, #2                     \n" /* Switch to the psp stack. */
                "   msr  CONTROL, r0                \n"
                "   isb                             \n"
                "   pop  {r0-r5}                    \n" /* Pop the registers that are saved automatically. */
                "   mov  lr, r5                     \n" /* lr is now in r5. */
                "   pop  {r3}                       \n" /* Return address is now in r3. */
                "   pop  {r2}                       \n" /* Pop and discard XPSR. */
                "   cpsie i                         \n" /* The first task has its context and interrupts can be enabled. */
                "   bx   r3                         \n" /* Finally, jump to the user defined task code. */
                "                                   \n"
                "     .align 4                      \n"
                "ulAsmLocals:                       \n"
                "    .word 0xD0000000               \n" /* SIO */
                "    .word pxCurrentTCBs            \n"
            );
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    ಸ್ಥಿರ ಶೂನ್ಯ prvFIFOInterruptHandler()
    {
        /* We must remove the contents (which we don't care about)
         * to clear the IRQ */
        multicore_fifo_drain();

        /* And explicitly clear any other IRQ flags. */
        multicore_fifo_clear_irq();

        #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES != 1 )
            ಪೋರ್ಟ್_YIELD_FROM_ISR( pdTRUE );
        #ಅಥವಾಆದರೆ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
            ತಳ_Type_t x_Higher_ಆದ್ಯತೆ_Task_Woken = pdFALSE;
            uint32_t ulSave = spin_ಬೀಗ_blocking( px_Cross_Core_Spin_ಬೀಗ );
            Event_ಬಿಟ್ಟುಗಳು_t ul_ಬಿಟ್ಟುಗಳು = ux_Cross_Core_Event_ಬಿಟ್ಟುಗಳು;
            ux_Cross_Core_Event_ಬಿಟ್ಟುಗಳು &= ~ul_ಬಿಟ್ಟುಗಳು;
            spin_unlock( px_Cross_Core_Spin_ಬೀಗ, ulSave );
            x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_From_ISR( x_Event_ಗುಂಪು, ul_ಬಿಟ್ಟುಗಳು, &x_Higher_ಆದ್ಯತೆ_Task_Woken );
            ಪೋರ್ಟ್_YIELD_FROM_ISR( x_Higher_ಆದ್ಯತೆ_Task_Woken );
        #ಆದರೆ_ಅಂತ್ಯ /* configNUMBER_OF_CORES != 1 */
    }
#ಆದರೆ_ಅಂತ್ಯ /* if ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

/*
 * See header file for description.
 */
    ಸ್ಥಿರ ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler_On_Core()
    {
        ಆದರೆ( uc_Primary_Core_ಅಂಕೆ == get_core_ಅಂಕೆ() )
        {
            /* Start the timer that generates the tick ISR.  Interrupts are disabled
             * here already. */
            v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

            /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
            ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_PRI;
            #ಆದರೆ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
                exception_ಗಣ_exclusive_handler( SYSTICK_EXCEPTION, x_ಪೋರ್ಟ್_Sys_Tick_Handler );
            #ಆದರೆ_ಅಂತ್ಯ
        }

        ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_PENDSV_PRI;

        #ಆದರೆ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_ಗಣ_exclusive_handler( PENDSV_EXCEPTION, x_ಪೋರ್ಟ್_Pend_SVHandler );
            exception_ಗಣ_exclusive_handler( SVCALL_EXCEPTION, v_ಪೋರ್ಟ್_SVCHandler );
        #ಆದರೆ_ಅಂತ್ಯ

        /* Install FIFO handler to receive interrupt from other core */
        multicore_fifo_clear_irq();
        multicore_fifo_drain();
        uint32_t ulIRQNum = SIO_IRQ_PROC0 + get_core_ಅಂಕೆ();
        irq_ಗಣ_ಆದ್ಯತೆ( ulIRQNum, ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ );
        irq_ಗಣ_exclusive_handler( ulIRQNum, prvFIFOInterruptHandler );
        irq_ಗಣ_enabled( ulIRQNum, 1 );

        /* Start the first task. */
        v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext( ಪೋರ್ಟ್_GET_CORE_ID() );
        prvTaskExitError();

        /* Should not get here. */
        ಹಿಂತಿರುಗಿ 0;
    }

    ಸ್ಥಿರ ಶೂನ್ಯ prv_Disable_Interrupts_And_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler_On_Core( ಶೂನ್ಯ )
    {
        ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
        x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler_On_Core();
    }

/*
 * See header file for description.
 */
    ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
    {
        configASSERT( uc_Primary_Core_ಅಂಕೆ == INVALID_PRIMARY_CORE_ಅಂಕೆ );

        /* No one else should use these! */
        spin_ಬೀಗ_claim( configSMP_SPINLOCK_0 );
        spin_ಬೀಗ_claim( configSMP_SPINLOCK_1 );

        uc_Primary_Core_ಅಂಕೆ = configTICK_CORE;
        configASSERT( get_core_ಅಂಕೆ() == 0 ); /* we must be started on core 0 */
        multicore_reset_core1();
        multicore_launch_core1( prv_Disable_Interrupts_And_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler_On_Core );

        x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler_On_Core();

        /* Should not get here! */
        ಹಿಂತಿರುಗಿ 0;
    }

#ಇಲ್ಲದಿದ್ದರೆ /* if ( configNUMBER_OF_CORES > 1 ) */

/*
 * See header file for description.
 */
    ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
    {
        /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
        ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_PENDSV_PRI;
        ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_PRI;

        #ಆದರೆ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_ಗಣ_exclusive_handler( PENDSV_EXCEPTION, x_ಪೋರ್ಟ್_Pend_SVHandler );
            exception_ಗಣ_exclusive_handler( SYSTICK_EXCEPTION, x_ಪೋರ್ಟ್_Sys_Tick_Handler );
            exception_ಗಣ_exclusive_handler( SVCALL_EXCEPTION, v_ಪೋರ್ಟ್_SVCHandler );
        #ಆದರೆ_ಅಂತ್ಯ

        /* Start the timer that generates the tick ISR.  Interrupts are disabled
         * here already. */
        v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

        /* Initialise the critical nesting count ready for the first task. */
        uxCriticalNesting = 0;

        uc_Primary_Core_ಅಂಕೆ = get_core_ಅಂಕೆ();
        #ಆದರೆ ( LIB_PICO_MULTICORE == 1 )
            #ಆದರೆ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
                multicore_fifo_clear_irq();
                multicore_fifo_drain();
                uint32_t irq_ಅಂಕೆ = SIO_IRQ_PROC0 + get_core_ಅಂಕೆ();
                irq_ಗಣ_ಆದ್ಯತೆ( irq_ಅಂಕೆ, ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ );
                irq_ಗಣ_exclusive_handler( irq_ಅಂಕೆ, prvFIFOInterruptHandler );
                irq_ಗಣ_enabled( irq_ಅಂಕೆ, 1 );
            #ಆದರೆ_ಅಂತ್ಯ
        #ಆದರೆ_ಅಂತ್ಯ

        /* Start the first task. */
        v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext();
        prvTaskExitError();

        /* Should not get here! */
        ಹಿಂತಿರುಗಿ 0;
    }
#ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES > 1 ) */

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ಪೋರ್ಟ್_GET_CORE_ID() == 1000UL );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ )
{
    /* Set a PendSV to request a context switch. */
    ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __asm ಅಸ್ಥಿರ ( "dsb" ::: "memory" );
    __asm ಅಸ್ಥಿರ ( "isb" );
}

/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
    {
        ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
        __asm ಅಸ್ಥಿರ ( "dsb" ::: "memory" );
        __asm ಅಸ್ಥಿರ ( "isb" );
    }
#ಆದರೆ_ಅಂತ್ಯ /* #if ( configNUMBER_OF_CORES == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
    {
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        ಆದರೆ( uxCriticalNesting == 0 )
        {
            ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
        }
    }
#ಆದರೆ_ಅಂತ್ಯ /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

uint32_t ul_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( ಶೂನ್ಯ )
{
    __asm ಅಸ್ಥಿರ (
        " mrs r0, PRIMASK    \n"
        " cpsid i            \n"
        " bx lr                "
        ::: "memory"
        );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( __attribute__( ( ಬಳಸದ ) ) uint32_t ul_ಮುಖವಾಡ )
{
    __asm ಅಸ್ಥಿರ (
        " msr PRIMASK, r0    \n"
        " bx lr                "
        ::: "memory"
        );
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ vYieldCore( ಪೂರ್ಣಾಂಕ xCoreID )
{
    /* Remove warning if configASSERT is not defined.
     * xCoreID is not used in this function due to this is a dual-core system. The yielding core must be different from the current core. */
    ( ಶೂನ್ಯ ) xCoreID;

    configASSERT( xCoreID != ( ಪೂರ್ಣಾಂಕ ) ಪೋರ್ಟ್_GET_CORE_ID() );

    #ಆದರೆ config_ಸಂಖ್ಯೆ_ದ_CORES != 1

        /* Non blocking, will cause interrupt on other core if the queue isn't already full,
         * in which case an IRQ must be pending */
        sio_hw->fifo_wr = 0;
    #ಆದರೆ_ಅಂತ್ಯ
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ x_ಪೋರ್ಟ್_Pend_SVHandler( ಶೂನ್ಯ )
{
    /* This is a naked function. */
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
        __asm ಅಸ್ಥಿರ
        (
            "   .syntax unified                     \n"
            "   mrs r0, psp                         \n"
            "                                       \n"
            "   ldr r3, pxCurrentTCBConst2          \n" /* Get the location of the current TCB. */
            "   ldr r2, [r3]                        \n"
            "                                       \n"
            "   subs r0, r0, #32                    \n" /* Make space for the remaining low registers. */
            "   str r0, [r2]                        \n" /* Save the new top of stack. */
            "   stmia r0!, {r4-r7}                  \n" /* Store the low registers that are not saved automatically. */
            "   mov r4, r8                          \n" /* Store the high registers. */
            "   mov r5, r9                          \n"
            "   mov r6, r10                         \n"
            "   mov r7, r11                         \n"
            "   stmia r0!, {r4-r7}                  \n"
            #ಆದರೆ ಪೋರ್ಟ್_USE_DIVIDER_SAVE_RESTORE
                "   movs r2, #0xd                   \n" /* Store the divider state. */
                "   lsls r2, #28                    \n"

                /* We expect that the divider is ready at this point (which is
                 * necessary to safely save/restore), because:
                 * a) if we have not been interrupted since we entered this method,
                 *    then >8 cycles have clearly passed, so the divider is done
                 * b) if we were interrupted in the interim, then any "safe" - i.e.
                 *    does the right thing in an IRQ - use of the divider should
                 *    have waited for any in-process divide to complete, saved and
                 *    then fully restored the result, thus the result is ready in
                 *    that case too. */
                "   ldr r4, [r2, #0x60]             \n" /* SIO_DIV_UDIVIDEND_OFFSET */
                "   ldr r5, [r2, #0x64]             \n" /* SIO_DIV_UDIVISOR_OFFSET */
                "   ldr r6, [r2, #0x74]             \n" /* SIO_DIV_REMAINDER_OFFSET */
                "   ldr r7, [r2, #0x70]             \n" /* SIO_DIV_QUOTIENT_OFFSET */

                /* We actually save the divider state in the 4 words below
                 * our recorded stack pointer, so as not to disrupt the stack
                 * frame expected by debuggers - this is addressed by
                 * portEXTRA_STACK_SIZE */
                "   subs r0, r0, #48                \n"
                "   stmia r0!, {r4-r7}              \n"
            #ಆದರೆ_ಅಂತ್ಯ /* portUSE_DIVIDER_SAVE_RESTORE */
            "   push {r3, r14}                      \n"
            "   cpsid i                             \n"
            "   bl vTaskSwitchContext               \n"
            "   cpsie i                             \n"
            "   pop {r2, r3}                        \n" /* lr goes in r3. r2 now holds tcb pointer. */
            "                                       \n"
            "   ldr r1, [r2]                        \n"
            "   ldr r0, [r1]                        \n" /* The first item in pxCurrentTCB is the task top of stack. */
            "   adds r0, r0, #16                    \n" /* Move to the high registers. */
            "   ldmia r0!, {r4-r7}                  \n" /* Pop the high registers. */
            "   mov r8, r4                          \n"
            "   mov r9, r5                          \n"
            "   mov r10, r6                         \n"
            "   mov r11, r7                         \n"
            "                                       \n"
            "   msr psp, r0                         \n" /* Remember the new top of stack for the task. */
            "                                       \n"
            #ಆದರೆ ಪೋರ್ಟ್_USE_DIVIDER_SAVE_RESTORE
                "   movs r2, #0xd                       \n" /* Pop the divider state. */
                "   lsls r2, #28                        \n"
                "   subs r0, r0, #48                    \n" /* Go back for the divider state */
                "   ldmia r0!, {r4-r7}                  \n" /* Pop the divider state. */

                /* Note always restore via SIO_DIV_UDIVI*, because we will overwrite the
                 * results stopping the calculation anyway, however the sign of results
                 * is adjusted by the h/w at read time based on whether the last started
                 * division was signed and the inputs' signs differed */
                "   str r4, [r2, #0x60]                 \n" /* SIO_DIV_UDIVIDEND_OFFSET */
                "   str r5, [r2, #0x64]                 \n" /* SIO_DIV_UDIVISOR_OFFSET */
                "   str r6, [r2, #0x74]                 \n" /* SIO_DIV_REMAINDER_OFFSET */
                "   str r7, [r2, #0x70]                 \n" /* SIO_DIV_QUOTIENT_OFFSET */
            #ಇಲ್ಲದಿದ್ದರೆ /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                    \n" /* Go back for the low registers that are not automatically restored. */
            #ಆದರೆ_ಅಂತ್ಯ /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                  \n"     /* Pop low registers.  */
            "                                       \n"
            "   bx r3                               \n"
            "   .align 4                            \n"
            "pxCurrentTCBConst2: .word pxCurrentTCB \n"
        );
    #ಇಲ್ಲದಿದ್ದರೆ /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm ಅಸ್ಥಿರ
        (
            "   .syntax unified                     \n"
            "   mrs r1, psp                         \n"
            "                                       \n"
            "   adr    r0, ulAsmLocals2             \n" /* Get the location of the current TCB for the current core. */
            "   ldmia r0!, {r2, r3}                 \n"
            "   ldr r0, [r2]                        \n" /* r0 = Core number */
            "   lsls r0, r0, #2                     \n"
            "   adds r3, r0                         \n" /* r3 = &pxCurrentTCBs[get_core_num()] */
            "   ldr    r0, [r3]                     \n" /* r0 = pxCurrentTCB */
            "                                       \n"
            "   subs r1, r1, #32                    \n" /* Make space for the remaining low registers. */
            "   str r1, [r0]                        \n" /* Save the new top of stack. */
            "   stmia r1!, {r4-r7}                  \n" /* Store the low registers that are not saved automatically. */
            "   mov r4, r8                          \n" /* Store the high registers. */
            "   mov r5, r9                          \n"
            "   mov r6, r10                         \n"
            "   mov r7, r11                         \n"
            "   stmia r1!, {r4-r7}                  \n"
            #ಆದರೆ ಪೋರ್ಟ್_USE_DIVIDER_SAVE_RESTORE

                /* We expect that the divider is ready at this point (which is
                 * necessary to safely save/restore), because:
                 * a) if we have not been interrupted since we entered this method,
                 *    then >8 cycles have clearly passed, so the divider is done
                 * b) if we were interrupted in the interim, then any "safe" - i.e.
                 *    does the right thing in an IRQ - use of the divider should
                 *    have waited for any in-process divide to complete, saved and
                 *    then fully restored the result, thus the result is ready in
                 *    that case too. */
                "   ldr r4, [r2, #0x60]             \n" /* SIO_DIV_UDIVIDEND_OFFSET */
                "   ldr r5, [r2, #0x64]             \n" /* SIO_DIV_UDIVISOR_OFFSET */
                "   ldr r6, [r2, #0x74]             \n" /* SIO_DIV_REMAINDER_OFFSET */
                "   ldr r7, [r2, #0x70]             \n" /* SIO_DIV_QUOTIENT_OFFSET */

                /* We actually save the divider state in the 4 words below
                 * our recorded stack pointer, so as not to disrupt the stack
                 * frame expected by debuggers - this is addressed by
                 * portEXTRA_STACK_SIZE */
                "   subs r1, r1, #48                \n"
                "   stmia r1!, {r4-r7}              \n"
            #ಆದರೆ_ಅಂತ್ಯ /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldr r0, [r2]                        \n" /* r0 = Core number */
            "   push {r3, r14}                      \n"
            "   cpsid i                             \n"
            "   bl vTaskSwitchContext               \n"
            "   cpsie i                             \n"
            "   pop {r2, r3}                        \n" /* lr goes in r3. r2 now holds tcb pointer. */
            "                                       \n"
            "   ldr r1, [r2]                        \n"
            "   ldr r0, [r1]                        \n" /* The first item in pxCurrentTCB is the task top of stack. */
            "   adds r0, r0, #16                    \n" /* Move to the high registers. */
            "   ldmia r0!, {r4-r7}                  \n" /* Pop the high registers. */
            "    mov r8, r4                         \n"
            "    mov r9, r5                         \n"
            "    mov r10, r6                        \n"
            "    mov r11, r7                        \n"
            "                                       \n"
            "   msr psp, r0                         \n" /* Remember the new top of stack for the task. */
            "                                       \n"
            #ಆದರೆ ಪೋರ್ಟ್_USE_DIVIDER_SAVE_RESTORE
                "   movs r2, #0xd                       \n" /* Pop the divider state. */
                "   lsls r2, #28                        \n"
                "   subs r0, r0, #48                    \n" /* Go back for the divider state */
                "   ldmia r0!, {r4-r7}                  \n" /* Pop the divider state. */

                /* Note always restore via SIO_DIV_UDIVI*, because we will overwrite the
                 * results stopping the calculation anyway, however the sign of results
                 * is adjusted by the h/w at read time based on whether the last started
                 * division was signed and the inputs' signs differed */
                "   str r4, [r2, #0x60]                \n" /* SIO_DIV_UDIVIDEND_OFFSET */
                "   str r5, [r2, #0x64]                \n" /* SIO_DIV_UDIVISOR_OFFSET */
                "   str r6, [r2, #0x74]                \n" /* SIO_DIV_REMAINDER_OFFSET */
                "   str r7, [r2, #0x70]                \n" /* SIO_DIV_QUOTIENT_OFFSET */
            #ಇಲ್ಲದಿದ್ದರೆ /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                   \n" /* Go back for the low registers that are not automatically restored. */
            #ಆದರೆ_ಅಂತ್ಯ /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                 \n"     /* Pop low registers.  */
            "                                      \n"
            "   bx r3                              \n"
            "                                      \n"
            "   .align 4                           \n"
            "ulAsmLocals2:                         \n"
            "   .word 0xD0000000                   \n" /* SIO */
            "   .word pxCurrentTCBs                \n"
        );
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sys_Tick_Handler( ಶೂನ್ಯ )
{
    uint32_t ul_ಹಿಂದಿನ_ಮುಖವಾಡ;

    ul_ಹಿಂದಿನ_ಮುಖವಾಡ = taskENTER_CRITICAL_FROM_ISR();
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
    taskEXIT_CRITICAL_FROM_ISR( ul_ಹಿಂದಿನ_ಮುಖವಾಡ );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( clock_get_hz( clk_sys ) / config_TICK_ದರ_HZ );
        x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks = ಪೋರ್ಟ್_MAX_24_ಬಿಟ್_ಸಂಖ್ಯೆ / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = ಪೋರ್ಟ್_MISSED_COUNTS_ಗುಣಕ;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

    /* Stop and reset the SysTick. */
    ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = 0UL;
    ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ( clock_get_hz( clk_sys ) / config_TICK_ದರ_HZ ) - 1UL;
    ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) ಶೂನ್ಯ v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ಸಮಯ )
    {
        uint32_t ul_Reload_ಮೌಲ್ಯ, ulCompleteTickPeriods, ulCompletedSysTickDecrements;
        TickType_t x_Modifiable_Idle_ಸಮಯ;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ಆದರೆ( x_Expected_Idle_ಸಮಯ > x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ಸಮಯ = x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks;
        }

        /* Stop the SysTick momentarily.  The time the SysTick is stopped for
         * is accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG &= ~ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;

        /* Calculate the reload value required to wait xExpectedIdleTime
         * tick periods.  -1 is used because this code will execute part way
         * through one of the tick periods. */
        ul_Reload_ಮೌಲ್ಯ = ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG + ( ulTimerCountsForOneTick * ( x_Expected_Idle_ಸಮಯ - 1UL ) );

        ಆದರೆ( ul_Reload_ಮೌಲ್ಯ > ulStoppedTimerCompensation )
        {
            ul_Reload_ಮೌಲ್ಯ -= ulStoppedTimerCompensation;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm ಅಸ್ಥಿರ ( "cpsid i" ::: "memory" );
        __asm ಅಸ್ಥಿರ ( "dsb" );
        __asm ಅಸ್ಥಿರ ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ಆದರೆ( e_Task_Confirm_Sleep_ಬಹುಲಕ_ಸ್ಥಿತಿ() == eAbortSleep )
        {
            /* Restart from whatever is left in the count register to complete
             * this tick period. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG;

            /* Restart SysTick. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;

            /* Reset the reload register to the value required for normal tick
             * periods. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ulTimerCountsForOneTick - 1UL;

            /* Re-enable interrupts - see comments above the cpsid instruction()
             * above. */
            __asm ಅಸ್ಥಿರ ( "cpsie i" ::: "memory" );
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
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
                __asm ಅಸ್ಥಿರ ( "dsb" ::: "memory" );
                __asm ಅಸ್ಥಿರ ( "wfi" );
                __asm ಅಸ್ಥಿರ ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_ಸಮಯ );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  see comments above
             * __disable_interrupt() call above. */
            __asm ಅಸ್ಥಿರ ( "cpsie i" ::: "memory" );
            __asm ಅಸ್ಥಿರ ( "dsb" );
            __asm ಅಸ್ಥಿರ ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm ಅಸ್ಥಿರ ( "cpsid i" ::: "memory" );
            __asm ಅಸ್ಥಿರ ( "dsb" );
            __asm ಅಸ್ಥಿರ ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ );

            /* Determine if the SysTick clock has already counted to zero and
             * been set back to the current reload value (the reload back being
             * correct for the entire expected idle time) or if the SysTick is yet
             * to count to zero (in which case an interrupt other than the SysTick
             * must have brought the system out of sleep mode). */
            ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG & ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್ ) != 0 )
            {
                uint32_t ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ;

                /* The tick interrupt is already pending, and the SysTick count
                 * reloaded with ulReloadValue.  Reset the
                 * portNVIC_SYSTICK_LOAD_REG with whatever remains of this tick
                 * period. */
                ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_ಮೌಲ್ಯ - ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long. */
                ಆದರೆ( ( ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ < ulStoppedTimerCompensation ) || ( ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ > ulTimerCountsForOneTick ) )
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
                /* Something other than the tick interrupt ended the sleep.
                 * Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_ಸಮಯ * ulTimerCountsForOneTick ) - ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG
             * again, then set portNVIC_SYSTICK_LOAD_REG back to its standard
             * value. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
            v_Task_ಹೆಜ್ಜೆ_Tick( ulCompleteTickPeriods );
            ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ulTimerCountsForOneTick - 1UL;

            /* Exit with interrupts enabled. */
            __asm ಅಸ್ಥಿರ ( "cpsie i" ::: "memory" );
        }
    }

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

#ಆದರೆ ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( config_SUPPORT_PICO_ಸಮಯ_INTEROP == 1 )
    ಸ್ಥಿರ TickType_t prv_Get_Ticks_ಗಮ್ಯ_Wait_Before( absolute_ಸಮಯ_t t )
    {
        int64_t xDelay = absolute_ಸಮಯ_diff_us( get_absolute_ಸಮಯ(), t );
        ಸ್ಥಿರಾಂಕ uint32_t ulTickPeriod = 1000000 / config_TICK_ದರ_HZ;

        xDelay -= ulTickPeriod;

        ಆದರೆ( xDelay >= ulTickPeriod )
        {
            ಹಿಂತಿರುಗಿ xDelay / ulTickPeriod;
        }

        ಹಿಂತಿರುಗಿ 0;
    }
#ಆದರೆ_ಅಂತ್ಯ /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( configSUPPORT_PICO_TIME_INTEROP == 1 ) */

#ಆದರೆ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    uint32_t ul_ಪೋರ್ಟ್_ಬೀಗ_Get_Current_Owner_Id()
    {
        ಆದರೆ( ಪೋರ್ಟ್_IS_FREE_RTOS_CORE() )
        {
            uint32_t exception = __get_current_exception();

            ಆದರೆ( !exception )
            {
                ಹಿಂತಿರುಗಿ ( uintptr_t ) xTaskGetCurrentTaskHandle();
            }

            /* Note: since ROM as at 0x00000000, these can't be confused with
             * valid task handles (pointers) in RAM */
            /* We make all exception handler/core combinations distinct owners */
            ಹಿಂತಿರುಗಿ get_core_ಅಂಕೆ() + exception * 2;
        }

        /* Note: since ROM as at 0x00000000, this can't be confused with
         * valid task handles (pointers) in RAM */
        ಹಿಂತಿರುಗಿ get_core_ಅಂಕೆ();
    }

    ಸ್ಥಿರ ಸಾಲೊಳಗೆ Event_ಬಿಟ್ಟುಗಳು_t prv_Get_Event_ಗುಂಪು_ಬಿಟ್( spin_ಬೀಗ_t * spin_ಬೀಗ )
    {
        uint32_t ul_ಬಿಟ್;

        #ಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
            ul_ಬಿಟ್ = 1u << ( spin_ಬೀಗ_get_ಅಂಕೆ( spin_ಬೀಗ ) & 0x7u );
        #ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
            /* Avoid potential use of SIO divider for % here out of abundance of caution */
            ul_ಬಿಟ್ = spin_ಬೀಗ_get_ಅಂಕೆ( spin_ಬೀಗ );
            ಆದರೆ (ul_ಬಿಟ್ >= 24) ul_ಬಿಟ್ -= 24;
            ul_ಬಿಟ್ = 1u << ul_ಬಿಟ್;
        #ಆದರೆ_ಅಂತ್ಯ /* configTICK_TYPE_WIDTH_IN_BITS */
        ಹಿಂತಿರುಗಿ ( Event_ಬಿಟ್ಟುಗಳು_t ) ul_ಬಿಟ್;
    }

    ಸ್ಥಿರ ಸಾಲೊಳಗೆ Event_ಬಿಟ್ಟುಗಳು_t prv_Get_All_Event_ಗುಂಪು_ಬಿಟ್ಟುಗಳು()
    {
        #ಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
            ಹಿಂತಿರುಗಿ ( Event_ಬಿಟ್ಟುಗಳು_t ) 0xffu;
        #ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
            ಹಿಂತಿರುಗಿ ( Event_ಬಿಟ್ಟುಗಳು_t ) 0xffffffu;
        #ಆದರೆ_ಅಂತ್ಯ /* configTICK_TYPE_WIDTH_IN_BITS */
    }

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಬೀಗ_ಆಂತರಿಕ_Spin_Unlock_With_Wait( ರಚನೆ ಬೀಗ_core * px_ಬೀಗ,
                                              uint32_t ulSave )
    {
        configASSERT( !ಪೋರ್ಟ್_CHECK_IF_ಒಳ_ISR() );
        configASSERT( px_ಬೀಗ->spin_ಬೀಗ_2 );

        ಆದರೆ( !ಪೋರ್ಟ್_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_ಬೀಗ->spin_ಬೀಗ_2, ulSave );
            __wfe();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* The requirement (from the SDK) on this implementation is that this method
             * should always wake up from a corresponding call to vPortLockInternalSpinUnlockWithNotify
             * that happens after this method is called.
             *
             * The moment that we unlock the spin lock, we need to be sure that
             * there is no way that we end up blocking in xEventGroupWaitBits,
             * despite the fact that other tasks can now run, if the corresponding
             * unlock has occurred.
             *
             * Previously the RP2xxx ports used to attempt to disable IRQs until the
             * task actually (potentially) became blocked by hooking the IRQ re-enable
             * when xEventGroupWaitBits completes (or switches tasks), but this
             * was a broken hack, in that IRQs are re-enabled at other points during
             * that call.
             *
             * This deferred IRQ enable is not actually needed, because all we
             * care about is that:
             *
             * Even in the presence of other tasks acquiring then releasing
             * the lock, between the interrupt_enable and the xEventGroupWaitBits,
             * the corresponding bit will still be set.
             *
             * This is the case, even any intervening blocked lock (which
             * clears the event bit) will need to unlock it before we proceed,
             * which will set the event bit again.
             *
             * The multiplexing down of multiple spin lock numbers to fewer
             * event bits does not cause a possible race condition,
             * but it does mean that a task waiting for lock A can be
             * blocked by a task B which owns another lock.
             *
             * This could be fixed by using an array of event groups, however
             * since the SDK spin locks are generally intended for very short
             * term usage anyway, and rarely nested except in exotic cases
             * like video output, we'll leave it as one event group for now
             */
            spin_unlock( px_ಬೀಗ->spin_ಬೀಗ_2, ulSave);
            x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು( x_Event_ಗುಂಪು, prv_Get_Event_ಗುಂಪು_ಬಿಟ್( px_ಬೀಗ->spin_ಬೀಗ_2 ),
                                 pdTRUE, pdFALSE, ಪೋರ್ಟ್_MAX_DELAY );
        }
    }

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಬೀಗ_ಆಂತರಿಕ_Spin_Unlock_With_Notify( ರಚನೆ ಬೀಗ_core * px_ಬೀಗ,
                                                uint32_t ulSave )
    {
        Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು = prv_Get_Event_ಗುಂಪು_ಬಿಟ್( px_ಬೀಗ->spin_ಬೀಗ_2 );

        ಆದರೆ( ಪೋರ್ಟ್_IS_FREE_RTOS_CORE() )
        {
            #ಆದರೆ LIB_PICO_MULTICORE
                /* signal an event in case a regular core is waiting */
                __sev();
            #ಆದರೆ_ಅಂತ್ಯ
            spin_unlock( px_ಬೀಗ->spin_ಬೀಗ_2, ulSave );

            ಆದರೆ( !ಪೋರ್ಟ್_CHECK_IF_ಒಳ_ISR() )
            {
                x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು( x_Event_ಗುಂಪು, ux_ಬಿಟ್ಟುಗಳು );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                ತಳ_Type_t x_Higher_ಆದ್ಯತೆ_Task_Woken = pdFALSE;
                x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_From_ISR( x_Event_ಗುಂಪು, ux_ಬಿಟ್ಟುಗಳು, &x_Higher_ಆದ್ಯತೆ_Task_Woken );
                ಪೋರ್ಟ್_YIELD_FROM_ISR( x_Higher_ಆದ್ಯತೆ_Task_Woken );
            }
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            __sev();
            #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
                ಆದರೆ( px_Cross_Core_Spin_ಬೀಗ != px_ಬೀಗ->spin_ಬೀಗ_2 )
                {
                    spin_ಬೀಗ_unsafe_blocking( px_Cross_Core_Spin_ಬೀಗ );
                    ux_Cross_Core_Event_ಬಿಟ್ಟುಗಳು |= ux_ಬಿಟ್ಟುಗಳು;
                    spin_unlock_unsafe( px_Cross_Core_Spin_ಬೀಗ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    ux_Cross_Core_Event_ಬಿಟ್ಟುಗಳು |= ux_ಬಿಟ್ಟುಗಳು;
                }

                /* This causes fifo irq on the other (FreeRTOS) core which will do the set the event bits */
                sio_hw->fifo_wr = 0;
            #ಆದರೆ_ಅಂತ್ಯ /* configNUMBER_OF_CORES == 1 */
            spin_unlock( px_ಬೀಗ->spin_ಬೀಗ_2, ulSave );
        }
    }

    bool x_ಪೋರ್ಟ್_ಬೀಗ_ಆಂತರಿಕ_Spin_Unlock_With_ಉತ್ತಮ_Effort_Wait_Or_Timeout( ರಚನೆ ಬೀಗ_core * px_ಬೀಗ,
                                                                 uint32_t ulSave,
                                                                 absolute_ಸಮಯ_t uxUntil )
    {
        configASSERT( !ಪೋರ್ಟ್_CHECK_IF_ಒಳ_ISR() );
        configASSERT( px_ಬೀಗ->spin_ಬೀಗ_2 );

        /* note no need to check LIB_PICO_MULTICORE, as this is always returns true if that is not defined */
        ಆದರೆ( !ಪೋರ್ಟ್_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_ಬೀಗ->spin_ಬೀಗ_2, ulSave );
            ಹಿಂತಿರುಗಿ ಉತ್ತಮ_effort_wfe_or_timeout( uxUntil );
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            configASSERT( ಪೋರ್ಟ್_IS_FREE_RTOS_CORE() );

            TickType_t ux_Ticks_ಗಮ್ಯ_Wait = prv_Get_Ticks_ಗಮ್ಯ_Wait_Before( uxUntil );

            ಆದರೆ( ux_Ticks_ಗಮ್ಯ_Wait )
            {
                /* See comment in vPortLockInternalSpinUnlockWithWait for detail
                 * about possible race conditions */
                spin_unlock( px_ಬೀಗ->spin_ಬೀಗ_2, ulSave );
                x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು( x_Event_ಗುಂಪು,
                                     prv_Get_Event_ಗುಂಪು_ಬಿಟ್( px_ಬೀಗ->spin_ಬೀಗ_2 ), pdTRUE,
                                     pdFALSE, ux_Ticks_ಗಮ್ಯ_Wait );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                spin_unlock( px_ಬೀಗ->spin_ಬೀಗ_2, ulSave );
            }

            ಆದರೆ( ಸಮಯ_reached( uxUntil ) )
            {
                ಹಿಂತಿರುಗಿ true;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* We do not want to hog the core */
                ಪೋರ್ಟ್_YIELD();
                /* We aren't sure if we've reached the timeout yet; the caller will check */
                ಹಿಂತಿರುಗಿ false;
            }
        }
    }

    #ಆದರೆ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* runs before main */
        ಸ್ಥಿರ ಶೂನ್ಯ __attribute__( ( constructor ) ) prvRuntimeInitializer( ಶೂನ್ಯ )
        {
            /* This must be done even before the scheduler is started, as the spin lock
             * is used by the overrides of the SDK wait/notify primitives */
            #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
                px_Cross_Core_Spin_ಬೀಗ = spin_ಬೀಗ_instance( ಮುಂದಿನ_striped_spin_ಬೀಗ_ಅಂಕೆ() );
            #ಆದರೆ_ಅಂತ್ಯ /* configNUMBER_OF_CORES == 1 */

            /* The event group is not used prior to scheduler init, but is initialized
             * here to since it logically belongs with the spin lock */
            #ಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 )
                x_Event_ಗುಂಪು = x_Event_ಗುಂಪು_Create_Static( &x_Static_Event_ಗುಂಪು );
            #ಇಲ್ಲದಿದ್ದರೆ

                /* Note that it is slightly dubious calling this here before the scheduler is initialized,
                 * however the only thing it touches is the allocator which then calls vPortEnterCritical
                 * and vPortExitCritical, and allocating here saves us checking the one time initialized variable in
                 * some rather critical code paths */
                x_Event_ಗುಂಪು = x_Event_ಗುಂಪು_Create();
            #ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_STATIC_ALLOCATION */
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */
#ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_PICO_SYNC_INTEROP */

#ಆದರೆ ( config_SUPPORT_PICO_ಸಮಯ_INTEROP == 1 )
    ಶೂನ್ಯ x_ಪೋರ್ಟ್_Sync_ಆಂತರಿಕ_Yield_Until_Before( absolute_ಸಮಯ_t t )
    {
        TickType_t ux_Ticks_ಗಮ್ಯ_Wait = prv_Get_Ticks_ಗಮ್ಯ_Wait_Before( t );

        ಆದರೆ( ux_Ticks_ಗಮ್ಯ_Wait )
        {
            vTaskDelay( ux_Ticks_ಗಮ್ಯ_Wait );
        }
    }
#ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_PICO_TIME_INTEROP */
