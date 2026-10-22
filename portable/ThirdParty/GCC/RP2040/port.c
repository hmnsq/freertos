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

#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "rp2040_config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hardware/clocks.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hardware/exception.h"

/*
 * LIB_PICO_MULTICORE == 1, if we are linked with pico_multicore (note that
 * the non SMP FreeRTOS_Kernel is not linked with pico_multicore itself). We
 * use this flag to determine if we need multi-core functionality.
 */
#ਜੇ ( LIB_PICO_MULTICORE == 1 )
    #ਅਨ੍ਤਰ੍ਭਾਵ "pico/multicore.h"
#ਜੇ_ਅੰਤ /* LIB_PICO_MULTICORE */

/* Constants required to manipulate the NVIC. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG             ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e010 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG             ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e014 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG    ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e018 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_INT_CTRL_REG                 ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed04 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SHPR3_REG                    ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed20 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ              ( 1UL << 2UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ              ( 1UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ           ( 1UL << 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ਗਿਣਤੀ_FLAG_ਦੋਆਧਾਰੀ_ਅੰਕ       ( 1UL << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ                ( 1UL << 28UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ            ( 255UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSV_PRI                   ( ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_PRI                  ( ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ << 24UL )

/* Constants required to set up the initial stack. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_24_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੰਖਿਆ                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_MISSED_COUNTS_ਗੁਣਕ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MISSED_COUNTS_ਗੁਣਕ    ( 45UL )
#ਜੇ_ਅੰਤ

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_TASK_RETURN_ਪਤਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    config_TASK_RETURN_ਪਤਾ
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    prvTaskExitError
#ਜੇ_ਅੰਤ

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );

/*
 * Exception handlers.
 */
ਖਾਲੀ x_ਪੋਰਟ_Pend_SVHandler( ਖਾਲੀ ) __attribute__( ( naked ) );
ਖਾਲੀ x_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ );
ਖਾਲੀ v_ਪੋਰਟ_SVCHandler( ਖਾਲੀ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ਸਥਿਰ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ ) __attribute__( ( naked ) );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. This is initialized to 0 to allow vPortEnter/ExitCritical
 * to be called before the scheduler is started */
#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    ਸਥਿਰ UBaseType_t uxCriticalNesting;
#ਨਹੀਂਤਾਂ /* #if ( configNUMBER_OF_CORES == 1 ) */
UBaseType_t uxCriticalNestings[ config_ਸੰਖਿਆ_ਦਾ_CORES ] = { 0 };
#ਜੇ_ਅੰਤ /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

#ਜੇ ( configSUPPORT_PICO_SYNC_INTEROP == 1 || config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )
    #ਅਨ੍ਤਰ੍ਭਾਵ "hardware/irq.h"
#ਜੇ_ਅੰਤ /* ( configSUPPORT_PICO_SYNC_INTEROP == 1 || configNUMBER_OF_CORES > 1 ) */
#ਜੇ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    #ਅਨ੍ਤਰ੍ਭਾਵ "pico/lock_core.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "event_groups.h"
    #ਜੇ config_SUPPORT_STATIC_ਵੰਡ
        ਸਥਿਰ Static_Event_ਸਮੂਹ_t x_Static_Event_ਸਮੂਹ;
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ p_Event_ਸਮੂਹ    ( &x_Static_Event_ਸਮੂਹ )
    #ਜੇ_ਅੰਤ /* configSUPPORT_STATIC_ALLOCATION */
    ਸਥਿਰ Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ;
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
        ਸਥਿਰ Event_ਬਿੱਟ_t ux_Cross_Core_Event_ਬਿੱਟ;
        ਸਥਿਰ spin_ਤਾਲਾ_t * px_Cross_Core_Spin_ਤਾਲਾ; /* protects uxCrossCoreEventBits */
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* configSUPPORT_PICO_SYNC_INTEROP */

/*
 * The number of SysTick increments that make up one tick period.
 */
#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )
    ਸਥਿਰ uint32_t ulTimerCountsForOneTick = 0;
#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )
    ਸਥਿਰ uint32_t x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks = 0;
#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )
    ਸਥਿਰ uint32_t ulStoppedTimerCompensation = 0;
#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INVALID_PRIMARY_CORE_ਅੰਕ    0xffu
/* The primary core number (the own which has the SysTick handler) */
ਸਥਿਰ uint8_t uc_Primary_Core_ਅੰਕ = INVALID_PRIMARY_CORE_ਅੰਕ;

/* Note: portIS_FREE_RTOS_CORE() also returns false until the scheduler is started */
#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES != 1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_ਅੰਕ != INVALID_PRIMARY_CORE_ਅੰਕ )
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_ਅੰਕ == get_core_ਅੰਕ() )
#ਜੇ_ਅੰਤ

/*
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_XPSR;                        /* xPSR */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;                  /* PC */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ; /* LR */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 5;                                       /* R12, R3, R2 and R1. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;            /* R0 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 8;                                       /* R11..R4. */

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ). */
    panic_unsupported();
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_SVCHandler( ਖਾਲੀ )
{
    /* This function is no longer used, but retained for backward
     * compatibility. */
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ )
{
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
        __asm ਅਸਥਿਰ (
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
    #ਨਹੀਂਤਾਂ /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm ਅਸਥਿਰ (
            "    .syntax unified                    \n"
            #ਜੇ config_RESET_ਢੇਰ_ਸੂਚਕ
                "   ldr  r0, =0xE000ED08            \n" /* Use the NVIC offset register to locate the stack. */
                "   ldr r0, [r0]                    \n"
                "   ldr r0, [r0]                    \n"
                "   msr msp, r0                     \n" /* Set the msp back to the start of the stack. */
            #ਜੇ_ਅੰਤ /* configRESET_STACK_POINTER */
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
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#ਜੇ ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    ਸਥਿਰ ਖਾਲੀ prvFIFOInterruptHandler()
    {
        /* We must remove the contents (which we don't care about)
         * to clear the IRQ */
        multicore_fifo_drain();

        /* And explicitly clear any other IRQ flags. */
        multicore_fifo_clear_irq();

        #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES != 1 )
            ਪੋਰਟ_YIELD_FROM_ISR( pdTRUE );
        #ਜਾਂਜੇ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
            ਅਧਾਰ_Type_t x_Higher_ਤਰਜੀਹ_Task_Woken = pdFALSE;
            uint32_t ulSave = spin_ਤਾਲਾ_blocking( px_Cross_Core_Spin_ਤਾਲਾ );
            Event_ਬਿੱਟ_t ul_ਬਿੱਟ = ux_Cross_Core_Event_ਬਿੱਟ;
            ux_Cross_Core_Event_ਬਿੱਟ &= ~ul_ਬਿੱਟ;
            spin_unlock( px_Cross_Core_Spin_ਤਾਲਾ, ulSave );
            x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_From_ISR( x_Event_ਸਮੂਹ, ul_ਬਿੱਟ, &x_Higher_ਤਰਜੀਹ_Task_Woken );
            ਪੋਰਟ_YIELD_FROM_ISR( x_Higher_ਤਰਜੀਹ_Task_Woken );
        #ਜੇ_ਅੰਤ /* configNUMBER_OF_CORES != 1 */
    }
#ਜੇ_ਅੰਤ /* if ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

/*
 * See header file for description.
 */
    ਸਥਿਰ ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler_On_Core()
    {
        ਜੇ( uc_Primary_Core_ਅੰਕ == get_core_ਅੰਕ() )
        {
            /* Start the timer that generates the tick ISR.  Interrupts are disabled
             * here already. */
            v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

            /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
            ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_SYSTICK_PRI;
            #ਜੇ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
                exception_ਸੈੱਟ_exclusive_handler( SYSTICK_EXCEPTION, x_ਪੋਰਟ_Sys_Tick_Handler );
            #ਜੇ_ਅੰਤ
        }

        ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_PENDSV_PRI;

        #ਜੇ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_ਸੈੱਟ_exclusive_handler( PENDSV_EXCEPTION, x_ਪੋਰਟ_Pend_SVHandler );
            exception_ਸੈੱਟ_exclusive_handler( SVCALL_EXCEPTION, v_ਪੋਰਟ_SVCHandler );
        #ਜੇ_ਅੰਤ

        /* Install FIFO handler to receive interrupt from other core */
        multicore_fifo_clear_irq();
        multicore_fifo_drain();
        uint32_t ulIRQNum = SIO_IRQ_PROC0 + get_core_ਅੰਕ();
        irq_ਸੈੱਟ_ਤਰਜੀਹ( ulIRQNum, ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ );
        irq_ਸੈੱਟ_exclusive_handler( ulIRQNum, prvFIFOInterruptHandler );
        irq_ਸੈੱਟ_enabled( ulIRQNum, 1 );

        /* Start the first task. */
        v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext( ਪੋਰਟ_GET_CORE_ID() );
        prvTaskExitError();

        /* Should not get here. */
        ਵਾਪਸ 0;
    }

    ਸਥਿਰ ਖਾਲੀ prv_Disable_Interrupts_And_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler_On_Core( ਖਾਲੀ )
    {
        ਪੋਰਟ_DISABLE_INTERRUPTS();
        x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler_On_Core();
    }

/*
 * See header file for description.
 */
    ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
    {
        configASSERT( uc_Primary_Core_ਅੰਕ == INVALID_PRIMARY_CORE_ਅੰਕ );

        /* No one else should use these! */
        spin_ਤਾਲਾ_claim( configSMP_SPINLOCK_0 );
        spin_ਤਾਲਾ_claim( configSMP_SPINLOCK_1 );

        uc_Primary_Core_ਅੰਕ = configTICK_CORE;
        configASSERT( get_core_ਅੰਕ() == 0 ); /* we must be started on core 0 */
        multicore_reset_core1();
        multicore_launch_core1( prv_Disable_Interrupts_And_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler_On_Core );

        x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler_On_Core();

        /* Should not get here! */
        ਵਾਪਸ 0;
    }

#ਨਹੀਂਤਾਂ /* if ( configNUMBER_OF_CORES > 1 ) */

/*
 * See header file for description.
 */
    ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
    {
        /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
        ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_PENDSV_PRI;
        ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_SYSTICK_PRI;

        #ਜੇ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_ਸੈੱਟ_exclusive_handler( PENDSV_EXCEPTION, x_ਪੋਰਟ_Pend_SVHandler );
            exception_ਸੈੱਟ_exclusive_handler( SYSTICK_EXCEPTION, x_ਪੋਰਟ_Sys_Tick_Handler );
            exception_ਸੈੱਟ_exclusive_handler( SVCALL_EXCEPTION, v_ਪੋਰਟ_SVCHandler );
        #ਜੇ_ਅੰਤ

        /* Start the timer that generates the tick ISR.  Interrupts are disabled
         * here already. */
        v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

        /* Initialise the critical nesting count ready for the first task. */
        uxCriticalNesting = 0;

        uc_Primary_Core_ਅੰਕ = get_core_ਅੰਕ();
        #ਜੇ ( LIB_PICO_MULTICORE == 1 )
            #ਜੇ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
                multicore_fifo_clear_irq();
                multicore_fifo_drain();
                uint32_t irq_ਅੰਕ = SIO_IRQ_PROC0 + get_core_ਅੰਕ();
                irq_ਸੈੱਟ_ਤਰਜੀਹ( irq_ਅੰਕ, ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ );
                irq_ਸੈੱਟ_exclusive_handler( irq_ਅੰਕ, prvFIFOInterruptHandler );
                irq_ਸੈੱਟ_enabled( irq_ਅੰਕ, 1 );
            #ਜੇ_ਅੰਤ
        #ਜੇ_ਅੰਤ

        /* Start the first task. */
        v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext();
        prvTaskExitError();

        /* Should not get here! */
        ਵਾਪਸ 0;
    }
#ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES > 1 ) */

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ਪੋਰਟ_GET_CORE_ID() == 1000UL );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ )
{
    /* Set a PendSV to request a context switch. */
    ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __asm ਅਸਥਿਰ ( "dsb" ::: "memory" );
    __asm ਅਸਥਿਰ ( "isb" );
}

/*-----------------------------------------------------------*/

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
    {
        ਪੋਰਟ_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
        __asm ਅਸਥਿਰ ( "dsb" ::: "memory" );
        __asm ਅਸਥਿਰ ( "isb" );
    }
#ਜੇ_ਅੰਤ /* #if ( configNUMBER_OF_CORES == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
    {
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        ਜੇ( uxCriticalNesting == 0 )
        {
            ਪੋਰਟ_ENABLE_INTERRUPTS();
        }
    }
#ਜੇ_ਅੰਤ /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

uint32_t ul_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( ਖਾਲੀ )
{
    __asm ਅਸਥਿਰ (
        " mrs r0, PRIMASK    \n"
        " cpsid i            \n"
        " bx lr                "
        ::: "memory"
        );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( __attribute__( ( ਅਣਵਰਤਿਆ ) ) uint32_t ul_ਨਕਾਬ )
{
    __asm ਅਸਥਿਰ (
        " msr PRIMASK, r0    \n"
        " bx lr                "
        ::: "memory"
        );
}

/*-----------------------------------------------------------*/

ਖਾਲੀ vYieldCore( ਪੂਰਨ xCoreID )
{
    /* Remove warning if configASSERT is not defined.
     * xCoreID is not used in this function due to this is a dual-core system. The yielding core must be different from the current core. */
    ( ਖਾਲੀ ) xCoreID;

    configASSERT( xCoreID != ( ਪੂਰਨ ) ਪੋਰਟ_GET_CORE_ID() );

    #ਜੇ config_ਸੰਖਿਆ_ਦਾ_CORES != 1

        /* Non blocking, will cause interrupt on other core if the queue isn't already full,
         * in which case an IRQ must be pending */
        sio_hw->fifo_wr = 0;
    #ਜੇ_ਅੰਤ
}

/*-----------------------------------------------------------*/

ਖਾਲੀ x_ਪੋਰਟ_Pend_SVHandler( ਖਾਲੀ )
{
    /* This is a naked function. */
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
        __asm ਅਸਥਿਰ
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
            #ਜੇ ਪੋਰਟ_USE_DIVIDER_SAVE_RESTORE
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
            #ਜੇ_ਅੰਤ /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #ਜੇ ਪੋਰਟ_USE_DIVIDER_SAVE_RESTORE
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
            #ਨਹੀਂਤਾਂ /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                    \n" /* Go back for the low registers that are not automatically restored. */
            #ਜੇ_ਅੰਤ /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                  \n"     /* Pop low registers.  */
            "                                       \n"
            "   bx r3                               \n"
            "   .align 4                            \n"
            "pxCurrentTCBConst2: .word pxCurrentTCB \n"
        );
    #ਨਹੀਂਤਾਂ /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm ਅਸਥਿਰ
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
            #ਜੇ ਪੋਰਟ_USE_DIVIDER_SAVE_RESTORE

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
            #ਜੇ_ਅੰਤ /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #ਜੇ ਪੋਰਟ_USE_DIVIDER_SAVE_RESTORE
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
            #ਨਹੀਂਤਾਂ /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                   \n" /* Go back for the low registers that are not automatically restored. */
            #ਜੇ_ਅੰਤ /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                 \n"     /* Pop low registers.  */
            "                                      \n"
            "   bx r3                              \n"
            "                                      \n"
            "   .align 4                           \n"
            "ulAsmLocals2:                         \n"
            "   .word 0xD0000000                   \n" /* SIO */
            "   .word pxCurrentTCBs                \n"
        );
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

ਖਾਲੀ x_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ )
{
    uint32_t ul_ਪਿਛਲਾ_ਨਕਾਬ;

    ul_ਪਿਛਲਾ_ਨਕਾਬ = taskENTER_CRITICAL_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();
            /* Pend a context switch. */
            ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ;
        }
        ਨਹੀਂਤਾਂ
        {
            traceISR_EXIT();
        }
    }
    taskEXIT_CRITICAL_FROM_ISR( ul_ਪਿਛਲਾ_ਨਕਾਬ );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #ਜੇ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( clock_get_hz( clk_sys ) / config_TICK_ਦਰ_HZ );
        x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks = ਪੋਰਟ_MAX_24_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੰਖਿਆ / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = ਪੋਰਟ_MISSED_COUNTS_ਗੁਣਕ;
    }
    #ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

    /* Stop and reset the SysTick. */
    ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = 0UL;
    ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ( clock_get_hz( clk_sys ) / config_TICK_ਦਰ_HZ ) - 1UL;
    ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;
}
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) ਖਾਲੀ v_ਪੋਰਟ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ਸਮਾਂ )
    {
        uint32_t ul_Reload_ਮੁੱਲ, ulCompleteTickPeriods, ulCompletedSysTickDecrements;
        TickType_t x_Modifiable_Idle_ਸਮਾਂ;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ਜੇ( x_Expected_Idle_ਸਮਾਂ > x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ਸਮਾਂ = x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks;
        }

        /* Stop the SysTick momentarily.  The time the SysTick is stopped for
         * is accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG &= ~ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;

        /* Calculate the reload value required to wait xExpectedIdleTime
         * tick periods.  -1 is used because this code will execute part way
         * through one of the tick periods. */
        ul_Reload_ਮੁੱਲ = ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG + ( ulTimerCountsForOneTick * ( x_Expected_Idle_ਸਮਾਂ - 1UL ) );

        ਜੇ( ul_Reload_ਮੁੱਲ > ulStoppedTimerCompensation )
        {
            ul_Reload_ਮੁੱਲ -= ulStoppedTimerCompensation;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm ਅਸਥਿਰ ( "cpsid i" ::: "memory" );
        __asm ਅਸਥਿਰ ( "dsb" );
        __asm ਅਸਥਿਰ ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ਜੇ( e_Task_Confirm_Sleep_ਬਹੁਲਕ_ਸਥਿਤੀ() == eAbortSleep )
        {
            /* Restart from whatever is left in the count register to complete
             * this tick period. */
            ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG;

            /* Restart SysTick. */
            ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG |= ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;

            /* Reset the reload register to the value required for normal tick
             * periods. */
            ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ulTimerCountsForOneTick - 1UL;

            /* Re-enable interrupts - see comments above the cpsid instruction()
             * above. */
            __asm ਅਸਥਿਰ ( "cpsie i" ::: "memory" );
        }
        ਨਹੀਂਤਾਂ
        {
            /* Set the new reload value. */
            ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ul_Reload_ਮੁੱਲ;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0UL;

            /* Restart SysTick. */
            ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG |= ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_ਸਮਾਂ = x_Expected_Idle_ਸਮਾਂ;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_ਸਮਾਂ );

            ਜੇ( x_Modifiable_Idle_ਸਮਾਂ > 0 )
            {
                __asm ਅਸਥਿਰ ( "dsb" ::: "memory" );
                __asm ਅਸਥਿਰ ( "wfi" );
                __asm ਅਸਥਿਰ ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_ਸਮਾਂ );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  see comments above
             * __disable_interrupt() call above. */
            __asm ਅਸਥਿਰ ( "cpsie i" ::: "memory" );
            __asm ਅਸਥਿਰ ( "dsb" );
            __asm ਅਸਥਿਰ ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm ਅਸਥਿਰ ( "cpsid i" ::: "memory" );
            __asm ਅਸਥਿਰ ( "dsb" );
            __asm ਅਸਥਿਰ ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ );

            /* Determine if the SysTick clock has already counted to zero and
             * been set back to the current reload value (the reload back being
             * correct for the entire expected idle time) or if the SysTick is yet
             * to count to zero (in which case an interrupt other than the SysTick
             * must have brought the system out of sleep mode). */
            ਜੇ( ( ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG & ਪੋਰਟ_NVIC_SYSTICK_ਗਿਣਤੀ_FLAG_ਦੋਆਧਾਰੀ_ਅੰਕ ) != 0 )
            {
                uint32_t ul_Calculated_ਲੱਦੋ_ਮੁੱਲ;

                /* The tick interrupt is already pending, and the SysTick count
                 * reloaded with ulReloadValue.  Reset the
                 * portNVIC_SYSTICK_LOAD_REG with whatever remains of this tick
                 * period. */
                ul_Calculated_ਲੱਦੋ_ਮੁੱਲ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_ਮੁੱਲ - ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long. */
                ਜੇ( ( ul_Calculated_ਲੱਦੋ_ਮੁੱਲ < ulStoppedTimerCompensation ) || ( ul_Calculated_ਲੱਦੋ_ਮੁੱਲ > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_ਲੱਦੋ_ਮੁੱਲ = ( ulTimerCountsForOneTick - 1UL );
                }

                ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ul_Calculated_ਲੱਦੋ_ਮੁੱਲ;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_ਸਮਾਂ - 1UL;
            }
            ਨਹੀਂਤਾਂ
            {
                /* Something other than the tick interrupt ended the sleep.
                 * Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_ਸਮਾਂ * ulTimerCountsForOneTick ) - ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG
             * again, then set portNVIC_SYSTICK_LOAD_REG back to its standard
             * value. */
            ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0UL;
            ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG |= ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;
            v_Task_ਕਦਮ_Tick( ulCompleteTickPeriods );
            ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ulTimerCountsForOneTick - 1UL;

            /* Exit with interrupts enabled. */
            __asm ਅਸਥਿਰ ( "cpsie i" ::: "memory" );
        }
    }

#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

#ਜੇ ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( config_SUPPORT_PICO_ਸਮਾਂ_INTEROP == 1 )
    ਸਥਿਰ TickType_t prv_Get_Ticks_ਮੰਜ਼ਿਲ_Wait_Before( absolute_ਸਮਾਂ_t t )
    {
        int64_t xDelay = absolute_ਸਮਾਂ_diff_us( get_absolute_ਸਮਾਂ(), t );
        ਅਚਲ uint32_t ulTickPeriod = 1000000 / config_TICK_ਦਰ_HZ;

        xDelay -= ulTickPeriod;

        ਜੇ( xDelay >= ulTickPeriod )
        {
            ਵਾਪਸ xDelay / ulTickPeriod;
        }

        ਵਾਪਸ 0;
    }
#ਜੇ_ਅੰਤ /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( configSUPPORT_PICO_TIME_INTEROP == 1 ) */

#ਜੇ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    uint32_t ul_ਪੋਰਟ_ਤਾਲਾ_Get_Current_Owner_Id()
    {
        ਜੇ( ਪੋਰਟ_IS_FREE_RTOS_CORE() )
        {
            uint32_t exception = __get_current_exception();

            ਜੇ( !exception )
            {
                ਵਾਪਸ ( uintptr_t ) xTaskGetCurrentTaskHandle();
            }

            /* Note: since ROM as at 0x00000000, these can't be confused with
             * valid task handles (pointers) in RAM */
            /* We make all exception handler/core combinations distinct owners */
            ਵਾਪਸ get_core_ਅੰਕ() + exception * 2;
        }

        /* Note: since ROM as at 0x00000000, this can't be confused with
         * valid task handles (pointers) in RAM */
        ਵਾਪਸ get_core_ਅੰਕ();
    }

    ਸਥਿਰ ਸਤਰਅੰਦਰ Event_ਬਿੱਟ_t prv_Get_Event_ਸਮੂਹ_ਦੋਆਧਾਰੀ_ਅੰਕ( spin_ਤਾਲਾ_t * spin_ਤਾਲਾ )
    {
        uint32_t ul_ਦੋਆਧਾਰੀ_ਅੰਕ;

        #ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
            ul_ਦੋਆਧਾਰੀ_ਅੰਕ = 1u << ( spin_ਤਾਲਾ_get_ਅੰਕ( spin_ਤਾਲਾ ) & 0x7u );
        #ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
            /* Avoid potential use of SIO divider for % here out of abundance of caution */
            ul_ਦੋਆਧਾਰੀ_ਅੰਕ = spin_ਤਾਲਾ_get_ਅੰਕ( spin_ਤਾਲਾ );
            ਜੇ (ul_ਦੋਆਧਾਰੀ_ਅੰਕ >= 24) ul_ਦੋਆਧਾਰੀ_ਅੰਕ -= 24;
            ul_ਦੋਆਧਾਰੀ_ਅੰਕ = 1u << ul_ਦੋਆਧਾਰੀ_ਅੰਕ;
        #ਜੇ_ਅੰਤ /* configTICK_TYPE_WIDTH_IN_BITS */
        ਵਾਪਸ ( Event_ਬਿੱਟ_t ) ul_ਦੋਆਧਾਰੀ_ਅੰਕ;
    }

    ਸਥਿਰ ਸਤਰਅੰਦਰ Event_ਬਿੱਟ_t prv_Get_All_Event_ਸਮੂਹ_ਬਿੱਟ()
    {
        #ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
            ਵਾਪਸ ( Event_ਬਿੱਟ_t ) 0xffu;
        #ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
            ਵਾਪਸ ( Event_ਬਿੱਟ_t ) 0xffffffu;
        #ਜੇ_ਅੰਤ /* configTICK_TYPE_WIDTH_IN_BITS */
    }

    ਖਾਲੀ v_ਪੋਰਟ_ਤਾਲਾ_ਅੰਦਰੂਨੀ_Spin_Unlock_With_Wait( ਬਣਤਰ ਤਾਲਾ_core * px_ਤਾਲਾ,
                                              uint32_t ulSave )
    {
        configASSERT( !ਪੋਰਟ_CHECK_IF_ਵਿੱਚ_ISR() );
        configASSERT( px_ਤਾਲਾ->spin_ਤਾਲਾ_2 );

        ਜੇ( !ਪੋਰਟ_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_ਤਾਲਾ->spin_ਤਾਲਾ_2, ulSave );
            __wfe();
        }
        ਨਹੀਂਤਾਂ
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
            spin_unlock( px_ਤਾਲਾ->spin_ਤਾਲਾ_2, ulSave);
            x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ( x_Event_ਸਮੂਹ, prv_Get_Event_ਸਮੂਹ_ਦੋਆਧਾਰੀ_ਅੰਕ( px_ਤਾਲਾ->spin_ਤਾਲਾ_2 ),
                                 pdTRUE, pdFALSE, ਪੋਰਟ_MAX_DELAY );
        }
    }

    ਖਾਲੀ v_ਪੋਰਟ_ਤਾਲਾ_ਅੰਦਰੂਨੀ_Spin_Unlock_With_Notify( ਬਣਤਰ ਤਾਲਾ_core * px_ਤਾਲਾ,
                                                uint32_t ulSave )
    {
        Event_ਬਿੱਟ_t ux_ਬਿੱਟ = prv_Get_Event_ਸਮੂਹ_ਦੋਆਧਾਰੀ_ਅੰਕ( px_ਤਾਲਾ->spin_ਤਾਲਾ_2 );

        ਜੇ( ਪੋਰਟ_IS_FREE_RTOS_CORE() )
        {
            #ਜੇ LIB_PICO_MULTICORE
                /* signal an event in case a regular core is waiting */
                __sev();
            #ਜੇ_ਅੰਤ
            spin_unlock( px_ਤਾਲਾ->spin_ਤਾਲਾ_2, ulSave );

            ਜੇ( !ਪੋਰਟ_CHECK_IF_ਵਿੱਚ_ISR() )
            {
                x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ( x_Event_ਸਮੂਹ, ux_ਬਿੱਟ );
            }
            ਨਹੀਂਤਾਂ
            {
                ਅਧਾਰ_Type_t x_Higher_ਤਰਜੀਹ_Task_Woken = pdFALSE;
                x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_From_ISR( x_Event_ਸਮੂਹ, ux_ਬਿੱਟ, &x_Higher_ਤਰਜੀਹ_Task_Woken );
                ਪੋਰਟ_YIELD_FROM_ISR( x_Higher_ਤਰਜੀਹ_Task_Woken );
            }
        }
        ਨਹੀਂਤਾਂ
        {
            __sev();
            #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
                ਜੇ( px_Cross_Core_Spin_ਤਾਲਾ != px_ਤਾਲਾ->spin_ਤਾਲਾ_2 )
                {
                    spin_ਤਾਲਾ_unsafe_blocking( px_Cross_Core_Spin_ਤਾਲਾ );
                    ux_Cross_Core_Event_ਬਿੱਟ |= ux_ਬਿੱਟ;
                    spin_unlock_unsafe( px_Cross_Core_Spin_ਤਾਲਾ );
                }
                ਨਹੀਂਤਾਂ
                {
                    ux_Cross_Core_Event_ਬਿੱਟ |= ux_ਬਿੱਟ;
                }

                /* This causes fifo irq on the other (FreeRTOS) core which will do the set the event bits */
                sio_hw->fifo_wr = 0;
            #ਜੇ_ਅੰਤ /* configNUMBER_OF_CORES == 1 */
            spin_unlock( px_ਤਾਲਾ->spin_ਤਾਲਾ_2, ulSave );
        }
    }

    bool x_ਪੋਰਟ_ਤਾਲਾ_ਅੰਦਰੂਨੀ_Spin_Unlock_With_ਉੱਤਮ_Effort_Wait_Or_Timeout( ਬਣਤਰ ਤਾਲਾ_core * px_ਤਾਲਾ,
                                                                 uint32_t ulSave,
                                                                 absolute_ਸਮਾਂ_t uxUntil )
    {
        configASSERT( !ਪੋਰਟ_CHECK_IF_ਵਿੱਚ_ISR() );
        configASSERT( px_ਤਾਲਾ->spin_ਤਾਲਾ_2 );

        /* note no need to check LIB_PICO_MULTICORE, as this is always returns true if that is not defined */
        ਜੇ( !ਪੋਰਟ_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_ਤਾਲਾ->spin_ਤਾਲਾ_2, ulSave );
            ਵਾਪਸ ਉੱਤਮ_effort_wfe_or_timeout( uxUntil );
        }
        ਨਹੀਂਤਾਂ
        {
            configASSERT( ਪੋਰਟ_IS_FREE_RTOS_CORE() );

            TickType_t ux_Ticks_ਮੰਜ਼ਿਲ_Wait = prv_Get_Ticks_ਮੰਜ਼ਿਲ_Wait_Before( uxUntil );

            ਜੇ( ux_Ticks_ਮੰਜ਼ਿਲ_Wait )
            {
                /* See comment in vPortLockInternalSpinUnlockWithWait for detail
                 * about possible race conditions */
                spin_unlock( px_ਤਾਲਾ->spin_ਤਾਲਾ_2, ulSave );
                x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ( x_Event_ਸਮੂਹ,
                                     prv_Get_Event_ਸਮੂਹ_ਦੋਆਧਾਰੀ_ਅੰਕ( px_ਤਾਲਾ->spin_ਤਾਲਾ_2 ), pdTRUE,
                                     pdFALSE, ux_Ticks_ਮੰਜ਼ਿਲ_Wait );
            }
            ਨਹੀਂਤਾਂ
            {
                spin_unlock( px_ਤਾਲਾ->spin_ਤਾਲਾ_2, ulSave );
            }

            ਜੇ( ਸਮਾਂ_reached( uxUntil ) )
            {
                ਵਾਪਸ true;
            }
            ਨਹੀਂਤਾਂ
            {
                /* We do not want to hog the core */
                ਪੋਰਟ_YIELD();
                /* We aren't sure if we've reached the timeout yet; the caller will check */
                ਵਾਪਸ false;
            }
        }
    }

    #ਜੇ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* runs before main */
        ਸਥਿਰ ਖਾਲੀ __attribute__( ( constructor ) ) prvRuntimeInitializer( ਖਾਲੀ )
        {
            /* This must be done even before the scheduler is started, as the spin lock
             * is used by the overrides of the SDK wait/notify primitives */
            #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
                px_Cross_Core_Spin_ਤਾਲਾ = spin_ਤਾਲਾ_instance( ਅਗਲਾ_striped_spin_ਤਾਲਾ_ਅੰਕ() );
            #ਜੇ_ਅੰਤ /* configNUMBER_OF_CORES == 1 */

            /* The event group is not used prior to scheduler init, but is initialized
             * here to since it logically belongs with the spin lock */
            #ਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 )
                x_Event_ਸਮੂਹ = x_Event_ਸਮੂਹ_Create_Static( &x_Static_Event_ਸਮੂਹ );
            #ਨਹੀਂਤਾਂ

                /* Note that it is slightly dubious calling this here before the scheduler is initialized,
                 * however the only thing it touches is the allocator which then calls vPortEnterCritical
                 * and vPortExitCritical, and allocating here saves us checking the one time initialized variable in
                 * some rather critical code paths */
                x_Event_ਸਮੂਹ = x_Event_ਸਮੂਹ_Create();
            #ਜੇ_ਅੰਤ /* configSUPPORT_STATIC_ALLOCATION */
        }
    #ਜੇ_ਅੰਤ /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */
#ਜੇ_ਅੰਤ /* configSUPPORT_PICO_SYNC_INTEROP */

#ਜੇ ( config_SUPPORT_PICO_ਸਮਾਂ_INTEROP == 1 )
    ਖਾਲੀ x_ਪੋਰਟ_Sync_ਅੰਦਰੂਨੀ_Yield_Until_Before( absolute_ਸਮਾਂ_t t )
    {
        TickType_t ux_Ticks_ਮੰਜ਼ਿਲ_Wait = prv_Get_Ticks_ਮੰਜ਼ਿਲ_Wait_Before( t );

        ਜੇ( ux_Ticks_ਮੰਜ਼ਿਲ_Wait )
        {
            vTaskDelay( ux_Ticks_ਮੰਜ਼ਿਲ_Wait );
        }
    }
#ਜੇ_ਅੰਤ /* configSUPPORT_PICO_TIME_INTEROP */
