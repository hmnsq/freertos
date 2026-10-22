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

#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "rp2040_config.h"
#అన్తర్భావ "hardware/clocks.h"
#అన్తర్భావ "hardware/exception.h"

/*
 * LIB_PICO_MULTICORE == 1, if we are linked with pico_multicore (note that
 * the non SMP FreeRTOS_Kernel is not linked with pico_multicore itself). We
 * use this flag to determine if we need multi-core functionality.
 */
#ఒకవేళ ( LIB_PICO_MULTICORE == 1 )
    #అన్తర్భావ "pico/multicore.h"
#అయితే_ముగింపు /* LIB_PICO_MULTICORE */

/* Constants required to manipulate the NVIC. */
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CTRL_REG             ( *( ( అస్థిర uint32_t * ) 0xe000e010 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG             ( *( ( అస్థిర uint32_t * ) 0xe000e014 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG    ( *( ( అస్థిర uint32_t * ) 0xe000e018 ) )
#నిర్వచించు పోర్టు_NVIC_INT_CTRL_REG                 ( *( ( అస్థిర uint32_t * ) 0xe000ed04 ) )
#నిర్వచించు పోర్టు_NVIC_SHPR3_REG                    ( *( ( అస్థిర uint32_t * ) 0xe000ed20 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు              ( 1UL << 2UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_INT_బిట్టు              ( 1UL << 1UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు           ( 1UL << 0UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_లెక్క_FLAG_బిట్టు       ( 1UL << 16UL )
#నిర్వచించు పోర్టు_NVIC_PENDSVSET_బిట్టు                ( 1UL << 28UL )
#నిర్వచించు పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత            ( 255UL )
#నిర్వచించు పోర్టు_NVIC_PENDSV_PRI                   ( పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత << 16UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_PRI                  ( పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత << 24UL )

/* Constants required to set up the initial stack. */
#నిర్వచించు పోర్టు_INITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#నిర్వచించు పోర్టు_MAX_24_బిట్టు_సంఖ్య                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#నిర్వచితం_కాకపోతే పోర్టు_MISSED_COUNTS_గుణకం
    #నిర్వచించు పోర్టు_MISSED_COUNTS_గుణకం    ( 45UL )
#అయితే_ముగింపు

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#నిర్వచితమైతే config_TASK_RETURN_చిరునామా
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    config_TASK_RETURN_చిరునామా
#లేకపోతే
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    prvTaskExitError
#అయితే_ముగింపు

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య );

/*
 * Exception handlers.
 */
శూన్య x_పోర్టు_Pend_SVHandler( శూన్య ) __attribute__( ( naked ) );
శూన్య x_పోర్టు_Sys_Tick_Handler( శూన్య );
శూన్య v_పోర్టు_SVCHandler( శూన్య );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
స్థిర శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య ) __attribute__( ( naked ) );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. This is initialized to 0 to allow vPortEnter/ExitCritical
 * to be called before the scheduler is started */
#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
    స్థిర UBaseType_t uxCriticalNesting;
#లేకపోతే /* #if ( configNUMBER_OF_CORES == 1 ) */
UBaseType_t uxCriticalNestings[ config_సంఖ్య_యొక్క_CORES ] = { 0 };
#అయితే_ముగింపు /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

#ఒకవేళ ( configSUPPORT_PICO_SYNC_INTEROP == 1 || config_సంఖ్య_యొక్క_CORES > 1 )
    #అన్తర్భావ "hardware/irq.h"
#అయితే_ముగింపు /* ( configSUPPORT_PICO_SYNC_INTEROP == 1 || configNUMBER_OF_CORES > 1 ) */
#ఒకవేళ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    #అన్తర్భావ "pico/lock_core.h"
    #అన్తర్భావ "event_groups.h"
    #ఒకవేళ config_SUPPORT_STATIC_కేటాయింపు
        స్థిర Static_Event_సమూహం_t x_Static_Event_సమూహం;
        #నిర్వచించు p_Event_సమూహం    ( &x_Static_Event_సమూహం )
    #అయితే_ముగింపు /* configSUPPORT_STATIC_ALLOCATION */
    స్థిర Event_సమూహం_Handle_t x_Event_సమూహం;
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
        స్థిర Event_బిట్లు_t ux_Cross_Core_Event_బిట్లు;
        స్థిర spin_తాళం_t * px_Cross_Core_Spin_తాళం; /* protects uxCrossCoreEventBits */
    #అయితే_ముగింపు
#అయితే_ముగింపు /* configSUPPORT_PICO_SYNC_INTEROP */

/*
 * The number of SysTick increments that make up one tick period.
 */
#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    స్థిర uint32_t ulTimerCountsForOneTick = 0;
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    స్థిర uint32_t x_గరిష్ఠ_Possible_Suppressed_Ticks = 0;
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    స్థిర uint32_t ulStoppedTimerCompensation = 0;
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#నిర్వచించు INVALID_PRIMARY_CORE_అంకె    0xffu
/* The primary core number (the own which has the SysTick handler) */
స్థిర uint8_t uc_Primary_Core_అంకె = INVALID_PRIMARY_CORE_అంకె;

/* Note: portIS_FREE_RTOS_CORE() also returns false until the scheduler is started */
#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES != 1 )
    #నిర్వచించు పోర్టు_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_అంకె != INVALID_PRIMARY_CORE_అంకె )
#లేకపోతే
    #నిర్వచించు పోర్టు_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_అంకె == get_core_అంకె() )
#అయితే_ముగింపు

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_శిఖరం_యొక్క_దొంతర--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_XPSR;                        /* xPSR */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;                  /* PC */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_TASK_RETURN_చిరునామా; /* LR */
    px_శిఖరం_యొక్క_దొంతర -= 5;                                       /* R12, R3, R2 and R1. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;            /* R0 */
    px_శిఖరం_యొక్క_దొంతర -= 8;                                       /* R11..R4. */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvTaskExitError( శూన్య )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ). */
    panic_unsupported();
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_SVCHandler( శూన్య )
{
    /* This function is no longer used, but retained for backward
     * compatibility. */
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య )
{
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
        __asm అస్థిర (
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
    #లేకపోతే /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm అస్థిర (
            "    .syntax unified                    \n"
            #ఒకవేళ config_RESET_దొంతర_సూచిక
                "   ldr  r0, =0xE000ED08            \n" /* Use the NVIC offset register to locate the stack. */
                "   ldr r0, [r0]                    \n"
                "   ldr r0, [r0]                    \n"
                "   msr msp, r0                     \n" /* Set the msp back to the start of the stack. */
            #అయితే_ముగింపు /* configRESET_STACK_POINTER */
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
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    స్థిర శూన్య prvFIFOInterruptHandler()
    {
        /* We must remove the contents (which we don't care about)
         * to clear the IRQ */
        multicore_fifo_drain();

        /* And explicitly clear any other IRQ flags. */
        multicore_fifo_clear_irq();

        #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES != 1 )
            పోర్టు_YIELD_FROM_ISR( pdTRUE );
        #లేదావేళ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
            పునాది_Type_t x_Higher_ప్రాధాన్యత_Task_Woken = pdFALSE;
            uint32_t ulSave = spin_తాళం_blocking( px_Cross_Core_Spin_తాళం );
            Event_బిట్లు_t ul_బిట్లు = ux_Cross_Core_Event_బిట్లు;
            ux_Cross_Core_Event_బిట్లు &= ~ul_బిట్లు;
            spin_unlock( px_Cross_Core_Spin_తాళం, ulSave );
            x_Event_సమూహం_సమితి_బిట్లు_From_ISR( x_Event_సమూహం, ul_బిట్లు, &x_Higher_ప్రాధాన్యత_Task_Woken );
            పోర్టు_YIELD_FROM_ISR( x_Higher_ప్రాధాన్యత_Task_Woken );
        #అయితే_ముగింపు /* configNUMBER_OF_CORES != 1 */
    }
#అయితే_ముగింపు /* if ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

/*
 * See header file for description.
 */
    స్థిర పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler_On_Core()
    {
        ఒకవేళ( uc_Primary_Core_అంకె == get_core_అంకె() )
        {
            /* Start the timer that generates the tick ISR.  Interrupts are disabled
             * here already. */
            v_పోర్టు_అమరిక_Timer_అంతరాయం();

            /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
            పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_SYSTICK_PRI;
            #ఒకవేళ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
                exception_సమితి_exclusive_handler( SYSTICK_EXCEPTION, x_పోర్టు_Sys_Tick_Handler );
            #అయితే_ముగింపు
        }

        పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_PENDSV_PRI;

        #ఒకవేళ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_సమితి_exclusive_handler( PENDSV_EXCEPTION, x_పోర్టు_Pend_SVHandler );
            exception_సమితి_exclusive_handler( SVCALL_EXCEPTION, v_పోర్టు_SVCHandler );
        #అయితే_ముగింపు

        /* Install FIFO handler to receive interrupt from other core */
        multicore_fifo_clear_irq();
        multicore_fifo_drain();
        uint32_t ulIRQNum = SIO_IRQ_PROC0 + get_core_అంకె();
        irq_సమితి_ప్రాధాన్యత( ulIRQNum, పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత );
        irq_సమితి_exclusive_handler( ulIRQNum, prvFIFOInterruptHandler );
        irq_సమితి_enabled( ulIRQNum, 1 );

        /* Start the first task. */
        v_పోర్టు_ప్రారంభం_మొదటి_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext( పోర్టు_GET_CORE_ID() );
        prvTaskExitError();

        /* Should not get here. */
        తిరిగి 0;
    }

    స్థిర శూన్య prv_Disable_Interrupts_And_పోర్టు_ప్రారంభం_Scheduler_On_Core( శూన్య )
    {
        పోర్టు_DISABLE_INTERRUPTS();
        x_పోర్టు_ప్రారంభం_Scheduler_On_Core();
    }

/*
 * See header file for description.
 */
    పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
    {
        configASSERT( uc_Primary_Core_అంకె == INVALID_PRIMARY_CORE_అంకె );

        /* No one else should use these! */
        spin_తాళం_claim( configSMP_SPINLOCK_0 );
        spin_తాళం_claim( configSMP_SPINLOCK_1 );

        uc_Primary_Core_అంకె = configTICK_CORE;
        configASSERT( get_core_అంకె() == 0 ); /* we must be started on core 0 */
        multicore_reset_core1();
        multicore_launch_core1( prv_Disable_Interrupts_And_పోర్టు_ప్రారంభం_Scheduler_On_Core );

        x_పోర్టు_ప్రారంభం_Scheduler_On_Core();

        /* Should not get here! */
        తిరిగి 0;
    }

#లేకపోతే /* if ( configNUMBER_OF_CORES > 1 ) */

/*
 * See header file for description.
 */
    పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
    {
        /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
        పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_PENDSV_PRI;
        పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_SYSTICK_PRI;

        #ఒకవేళ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_సమితి_exclusive_handler( PENDSV_EXCEPTION, x_పోర్టు_Pend_SVHandler );
            exception_సమితి_exclusive_handler( SYSTICK_EXCEPTION, x_పోర్టు_Sys_Tick_Handler );
            exception_సమితి_exclusive_handler( SVCALL_EXCEPTION, v_పోర్టు_SVCHandler );
        #అయితే_ముగింపు

        /* Start the timer that generates the tick ISR.  Interrupts are disabled
         * here already. */
        v_పోర్టు_అమరిక_Timer_అంతరాయం();

        /* Initialise the critical nesting count ready for the first task. */
        uxCriticalNesting = 0;

        uc_Primary_Core_అంకె = get_core_అంకె();
        #ఒకవేళ ( LIB_PICO_MULTICORE == 1 )
            #ఒకవేళ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
                multicore_fifo_clear_irq();
                multicore_fifo_drain();
                uint32_t irq_అంకె = SIO_IRQ_PROC0 + get_core_అంకె();
                irq_సమితి_ప్రాధాన్యత( irq_అంకె, పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత );
                irq_సమితి_exclusive_handler( irq_అంకె, prvFIFOInterruptHandler );
                irq_సమితి_enabled( irq_అంకె, 1 );
            #అయితే_ముగింపు
        #అయితే_ముగింపు

        /* Start the first task. */
        v_పోర్టు_ప్రారంభం_మొదటి_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext();
        prvTaskExitError();

        /* Should not get here! */
        తిరిగి 0;
    }
#అయితే_ముగింపు /* if ( configNUMBER_OF_CORES > 1 ) */

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( పోర్టు_GET_CORE_ID() == 1000UL );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Yield( శూన్య )
{
    /* Set a PendSV to request a context switch. */
    పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __asm అస్థిర ( "dsb" ::: "memory" );
    __asm అస్థిర ( "isb" );
}

/*-----------------------------------------------------------*/

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
    శూన్య v_పోర్టు_Enter_Critical( శూన్య )
    {
        పోర్టు_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
        __asm అస్థిర ( "dsb" ::: "memory" );
        __asm అస్థిర ( "isb" );
    }
#అయితే_ముగింపు /* #if ( configNUMBER_OF_CORES == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
    శూన్య v_పోర్టు_Exit_Critical( శూన్య )
    {
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        ఒకవేళ( uxCriticalNesting == 0 )
        {
            పోర్టు_ENABLE_INTERRUPTS();
        }
    }
#అయితే_ముగింపు /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

uint32_t ul_సమితి_అంతరాయం_ముసుగు_From_ISR( శూన్య )
{
    __asm అస్థిర (
        " mrs r0, PRIMASK    \n"
        " cpsid i            \n"
        " bx lr                "
        ::: "memory"
        );
}
/*-----------------------------------------------------------*/

శూన్య v_Clear_అంతరాయం_ముసుగు_From_ISR( __attribute__( ( వాడని ) ) uint32_t ul_ముసుగు )
{
    __asm అస్థిర (
        " msr PRIMASK, r0    \n"
        " bx lr                "
        ::: "memory"
        );
}

/*-----------------------------------------------------------*/

శూన్య vYieldCore( పూర్ణాంకం xCoreID )
{
    /* Remove warning if configASSERT is not defined.
     * xCoreID is not used in this function due to this is a dual-core system. The yielding core must be different from the current core. */
    ( శూన్య ) xCoreID;

    configASSERT( xCoreID != ( పూర్ణాంకం ) పోర్టు_GET_CORE_ID() );

    #ఒకవేళ config_సంఖ్య_యొక్క_CORES != 1

        /* Non blocking, will cause interrupt on other core if the queue isn't already full,
         * in which case an IRQ must be pending */
        sio_hw->fifo_wr = 0;
    #అయితే_ముగింపు
}

/*-----------------------------------------------------------*/

శూన్య x_పోర్టు_Pend_SVHandler( శూన్య )
{
    /* This is a naked function. */
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
        __asm అస్థిర
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
            #ఒకవేళ పోర్టు_USE_DIVIDER_SAVE_RESTORE
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
            #అయితే_ముగింపు /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #ఒకవేళ పోర్టు_USE_DIVIDER_SAVE_RESTORE
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
            #లేకపోతే /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                    \n" /* Go back for the low registers that are not automatically restored. */
            #అయితే_ముగింపు /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                  \n"     /* Pop low registers.  */
            "                                       \n"
            "   bx r3                               \n"
            "   .align 4                            \n"
            "pxCurrentTCBConst2: .word pxCurrentTCB \n"
        );
    #లేకపోతే /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm అస్థిర
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
            #ఒకవేళ పోర్టు_USE_DIVIDER_SAVE_RESTORE

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
            #అయితే_ముగింపు /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #ఒకవేళ పోర్టు_USE_DIVIDER_SAVE_RESTORE
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
            #లేకపోతే /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                   \n" /* Go back for the low registers that are not automatically restored. */
            #అయితే_ముగింపు /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                 \n"     /* Pop low registers.  */
            "                                      \n"
            "   bx r3                              \n"
            "                                      \n"
            "   .align 4                           \n"
            "ulAsmLocals2:                         \n"
            "   .word 0xD0000000                   \n" /* SIO */
            "   .word pxCurrentTCBs                \n"
        );
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

శూన్య x_పోర్టు_Sys_Tick_Handler( శూన్య )
{
    uint32_t ul_మునుపటి_ముసుగు;

    ul_మునుపటి_ముసుగు = taskENTER_CRITICAL_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_గమ్యం_SCHEDULER();
            /* Pend a context switch. */
            పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు;
        }
        లేకపోతే
        {
            traceISR_EXIT();
        }
    }
    taskEXIT_CRITICAL_FROM_ISR( ul_మునుపటి_ముసుగు );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( clock_get_hz( clk_sys ) / config_TICK_రేటు_HZ );
        x_గరిష్ఠ_Possible_Suppressed_Ticks = పోర్టు_MAX_24_బిట్టు_సంఖ్య / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = పోర్టు_MISSED_COUNTS_గుణకం;
    }
    #అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

    /* Stop and reset the SysTick. */
    పోర్టు_NVIC_SYSTICK_CTRL_REG = 0UL;
    పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ( clock_get_hz( clk_sys ) / config_TICK_రేటు_HZ ) - 1UL;
    పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు | పోర్టు_NVIC_SYSTICK_INT_బిట్టు | పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) శూన్య v_పోర్టు_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_సమయం )
    {
        uint32_t ul_Reload_విలువ, ulCompleteTickPeriods, ulCompletedSysTickDecrements;
        TickType_t x_Modifiable_Idle_సమయం;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ఒకవేళ( x_Expected_Idle_సమయం > x_గరిష్ఠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_సమయం = x_గరిష్ఠ_Possible_Suppressed_Ticks;
        }

        /* Stop the SysTick momentarily.  The time the SysTick is stopped for
         * is accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        పోర్టు_NVIC_SYSTICK_CTRL_REG &= ~పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;

        /* Calculate the reload value required to wait xExpectedIdleTime
         * tick periods.  -1 is used because this code will execute part way
         * through one of the tick periods. */
        ul_Reload_విలువ = పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG + ( ulTimerCountsForOneTick * ( x_Expected_Idle_సమయం - 1UL ) );

        ఒకవేళ( ul_Reload_విలువ > ulStoppedTimerCompensation )
        {
            ul_Reload_విలువ -= ulStoppedTimerCompensation;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm అస్థిర ( "cpsid i" ::: "memory" );
        __asm అస్థిర ( "dsb" );
        __asm అస్థిర ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ఒకవేళ( e_Task_Confirm_Sleep_బహుళకం_స్థితి() == eAbortSleep )
        {
            /* Restart from whatever is left in the count register to complete
             * this tick period. */
            పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG;

            /* Restart SysTick. */
            పోర్టు_NVIC_SYSTICK_CTRL_REG |= పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;

            /* Reset the reload register to the value required for normal tick
             * periods. */
            పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ulTimerCountsForOneTick - 1UL;

            /* Re-enable interrupts - see comments above the cpsid instruction()
             * above. */
            __asm అస్థిర ( "cpsie i" ::: "memory" );
        }
        లేకపోతే
        {
            /* Set the new reload value. */
            పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ul_Reload_విలువ;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;

            /* Restart SysTick. */
            పోర్టు_NVIC_SYSTICK_CTRL_REG |= పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_సమయం = x_Expected_Idle_సమయం;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_సమయం );

            ఒకవేళ( x_Modifiable_Idle_సమయం > 0 )
            {
                __asm అస్థిర ( "dsb" ::: "memory" );
                __asm అస్థిర ( "wfi" );
                __asm అస్థిర ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_సమయం );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  see comments above
             * __disable_interrupt() call above. */
            __asm అస్థిర ( "cpsie i" ::: "memory" );
            __asm అస్థిర ( "dsb" );
            __asm అస్థిర ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm అస్థిర ( "cpsid i" ::: "memory" );
            __asm అస్థిర ( "dsb" );
            __asm అస్థిర ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            పోర్టు_NVIC_SYSTICK_CTRL_REG = ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు | పోర్టు_NVIC_SYSTICK_INT_బిట్టు );

            /* Determine if the SysTick clock has already counted to zero and
             * been set back to the current reload value (the reload back being
             * correct for the entire expected idle time) or if the SysTick is yet
             * to count to zero (in which case an interrupt other than the SysTick
             * must have brought the system out of sleep mode). */
            ఒకవేళ( ( పోర్టు_NVIC_SYSTICK_CTRL_REG & పోర్టు_NVIC_SYSTICK_లెక్క_FLAG_బిట్టు ) != 0 )
            {
                uint32_t ul_Calculated_ఎక్కించు_విలువ;

                /* The tick interrupt is already pending, and the SysTick count
                 * reloaded with ulReloadValue.  Reset the
                 * portNVIC_SYSTICK_LOAD_REG with whatever remains of this tick
                 * period. */
                ul_Calculated_ఎక్కించు_విలువ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_విలువ - పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long. */
                ఒకవేళ( ( ul_Calculated_ఎక్కించు_విలువ < ulStoppedTimerCompensation ) || ( ul_Calculated_ఎక్కించు_విలువ > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_ఎక్కించు_విలువ = ( ulTimerCountsForOneTick - 1UL );
                }

                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ul_Calculated_ఎక్కించు_విలువ;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_సమయం - 1UL;
            }
            లేకపోతే
            {
                /* Something other than the tick interrupt ended the sleep.
                 * Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_సమయం * ulTimerCountsForOneTick ) - పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG
             * again, then set portNVIC_SYSTICK_LOAD_REG back to its standard
             * value. */
            పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;
            పోర్టు_NVIC_SYSTICK_CTRL_REG |= పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;
            v_Task_అడుగు_Tick( ulCompleteTickPeriods );
            పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ulTimerCountsForOneTick - 1UL;

            /* Exit with interrupts enabled. */
            __asm అస్థిర ( "cpsie i" ::: "memory" );
        }
    }

#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

#ఒకవేళ ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( config_SUPPORT_PICO_సమయం_INTEROP == 1 )
    స్థిర TickType_t prv_Get_Ticks_గమ్యం_Wait_Before( absolute_సమయం_t t )
    {
        int64_t xDelay = absolute_సమయం_diff_us( get_absolute_సమయం(), t );
        స్థిరరాశి uint32_t ulTickPeriod = 1000000 / config_TICK_రేటు_HZ;

        xDelay -= ulTickPeriod;

        ఒకవేళ( xDelay >= ulTickPeriod )
        {
            తిరిగి xDelay / ulTickPeriod;
        }

        తిరిగి 0;
    }
#అయితే_ముగింపు /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( configSUPPORT_PICO_TIME_INTEROP == 1 ) */

#ఒకవేళ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    uint32_t ul_పోర్టు_తాళం_Get_Current_Owner_Id()
    {
        ఒకవేళ( పోర్టు_IS_FREE_RTOS_CORE() )
        {
            uint32_t exception = __get_current_exception();

            ఒకవేళ( !exception )
            {
                తిరిగి ( uintptr_t ) xTaskGetCurrentTaskHandle();
            }

            /* Note: since ROM as at 0x00000000, these can't be confused with
             * valid task handles (pointers) in RAM */
            /* We make all exception handler/core combinations distinct owners */
            తిరిగి get_core_అంకె() + exception * 2;
        }

        /* Note: since ROM as at 0x00000000, this can't be confused with
         * valid task handles (pointers) in RAM */
        తిరిగి get_core_అంకె();
    }

    స్థిర అంతఃవరుస Event_బిట్లు_t prv_Get_Event_సమూహం_బిట్టు( spin_తాళం_t * spin_తాళం )
    {
        uint32_t ul_బిట్టు;

        #ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
            ul_బిట్టు = 1u << ( spin_తాళం_get_అంకె( spin_తాళం ) & 0x7u );
        #లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
            /* Avoid potential use of SIO divider for % here out of abundance of caution */
            ul_బిట్టు = spin_తాళం_get_అంకె( spin_తాళం );
            ఒకవేళ (ul_బిట్టు >= 24) ul_బిట్టు -= 24;
            ul_బిట్టు = 1u << ul_బిట్టు;
        #అయితే_ముగింపు /* configTICK_TYPE_WIDTH_IN_BITS */
        తిరిగి ( Event_బిట్లు_t ) ul_బిట్టు;
    }

    స్థిర అంతఃవరుస Event_బిట్లు_t prv_Get_All_Event_సమూహం_బిట్లు()
    {
        #ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
            తిరిగి ( Event_బిట్లు_t ) 0xffu;
        #లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
            తిరిగి ( Event_బిట్లు_t ) 0xffffffu;
        #అయితే_ముగింపు /* configTICK_TYPE_WIDTH_IN_BITS */
    }

    శూన్య v_పోర్టు_తాళం_అంతర్గత_Spin_Unlock_With_Wait( నిర్మాణం తాళం_core * px_తాళం,
                                              uint32_t ulSave )
    {
        configASSERT( !పోర్టు_CHECK_IF_లోపల_ISR() );
        configASSERT( px_తాళం->spin_తాళం_2 );

        ఒకవేళ( !పోర్టు_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_తాళం->spin_తాళం_2, ulSave );
            __wfe();
        }
        లేకపోతే
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
            spin_unlock( px_తాళం->spin_తాళం_2, ulSave);
            x_Event_సమూహం_Wait_బిట్లు( x_Event_సమూహం, prv_Get_Event_సమూహం_బిట్టు( px_తాళం->spin_తాళం_2 ),
                                 pdTRUE, pdFALSE, పోర్టు_MAX_DELAY );
        }
    }

    శూన్య v_పోర్టు_తాళం_అంతర్గత_Spin_Unlock_With_Notify( నిర్మాణం తాళం_core * px_తాళం,
                                                uint32_t ulSave )
    {
        Event_బిట్లు_t ux_బిట్లు = prv_Get_Event_సమూహం_బిట్టు( px_తాళం->spin_తాళం_2 );

        ఒకవేళ( పోర్టు_IS_FREE_RTOS_CORE() )
        {
            #ఒకవేళ LIB_PICO_MULTICORE
                /* signal an event in case a regular core is waiting */
                __sev();
            #అయితే_ముగింపు
            spin_unlock( px_తాళం->spin_తాళం_2, ulSave );

            ఒకవేళ( !పోర్టు_CHECK_IF_లోపల_ISR() )
            {
                x_Event_సమూహం_సమితి_బిట్లు( x_Event_సమూహం, ux_బిట్లు );
            }
            లేకపోతే
            {
                పునాది_Type_t x_Higher_ప్రాధాన్యత_Task_Woken = pdFALSE;
                x_Event_సమూహం_సమితి_బిట్లు_From_ISR( x_Event_సమూహం, ux_బిట్లు, &x_Higher_ప్రాధాన్యత_Task_Woken );
                పోర్టు_YIELD_FROM_ISR( x_Higher_ప్రాధాన్యత_Task_Woken );
            }
        }
        లేకపోతే
        {
            __sev();
            #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
                ఒకవేళ( px_Cross_Core_Spin_తాళం != px_తాళం->spin_తాళం_2 )
                {
                    spin_తాళం_unsafe_blocking( px_Cross_Core_Spin_తాళం );
                    ux_Cross_Core_Event_బిట్లు |= ux_బిట్లు;
                    spin_unlock_unsafe( px_Cross_Core_Spin_తాళం );
                }
                లేకపోతే
                {
                    ux_Cross_Core_Event_బిట్లు |= ux_బిట్లు;
                }

                /* This causes fifo irq on the other (FreeRTOS) core which will do the set the event bits */
                sio_hw->fifo_wr = 0;
            #అయితే_ముగింపు /* configNUMBER_OF_CORES == 1 */
            spin_unlock( px_తాళం->spin_తాళం_2, ulSave );
        }
    }

    bool x_పోర్టు_తాళం_అంతర్గత_Spin_Unlock_With_ఉత్తమ_Effort_Wait_Or_Timeout( నిర్మాణం తాళం_core * px_తాళం,
                                                                 uint32_t ulSave,
                                                                 absolute_సమయం_t uxUntil )
    {
        configASSERT( !పోర్టు_CHECK_IF_లోపల_ISR() );
        configASSERT( px_తాళం->spin_తాళం_2 );

        /* note no need to check LIB_PICO_MULTICORE, as this is always returns true if that is not defined */
        ఒకవేళ( !పోర్టు_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_తాళం->spin_తాళం_2, ulSave );
            తిరిగి ఉత్తమ_effort_wfe_or_timeout( uxUntil );
        }
        లేకపోతే
        {
            configASSERT( పోర్టు_IS_FREE_RTOS_CORE() );

            TickType_t ux_Ticks_గమ్యం_Wait = prv_Get_Ticks_గమ్యం_Wait_Before( uxUntil );

            ఒకవేళ( ux_Ticks_గమ్యం_Wait )
            {
                /* See comment in vPortLockInternalSpinUnlockWithWait for detail
                 * about possible race conditions */
                spin_unlock( px_తాళం->spin_తాళం_2, ulSave );
                x_Event_సమూహం_Wait_బిట్లు( x_Event_సమూహం,
                                     prv_Get_Event_సమూహం_బిట్టు( px_తాళం->spin_తాళం_2 ), pdTRUE,
                                     pdFALSE, ux_Ticks_గమ్యం_Wait );
            }
            లేకపోతే
            {
                spin_unlock( px_తాళం->spin_తాళం_2, ulSave );
            }

            ఒకవేళ( సమయం_reached( uxUntil ) )
            {
                తిరిగి true;
            }
            లేకపోతే
            {
                /* We do not want to hog the core */
                పోర్టు_YIELD();
                /* We aren't sure if we've reached the timeout yet; the caller will check */
                తిరిగి false;
            }
        }
    }

    #ఒకవేళ ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* runs before main */
        స్థిర శూన్య __attribute__( ( constructor ) ) prvRuntimeInitializer( శూన్య )
        {
            /* This must be done even before the scheduler is started, as the spin lock
             * is used by the overrides of the SDK wait/notify primitives */
            #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
                px_Cross_Core_Spin_తాళం = spin_తాళం_instance( తదుపరి_striped_spin_తాళం_అంకె() );
            #అయితే_ముగింపు /* configNUMBER_OF_CORES == 1 */

            /* The event group is not used prior to scheduler init, but is initialized
             * here to since it logically belongs with the spin lock */
            #ఒకవేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 )
                x_Event_సమూహం = x_Event_సమూహం_Create_Static( &x_Static_Event_సమూహం );
            #లేకపోతే

                /* Note that it is slightly dubious calling this here before the scheduler is initialized,
                 * however the only thing it touches is the allocator which then calls vPortEnterCritical
                 * and vPortExitCritical, and allocating here saves us checking the one time initialized variable in
                 * some rather critical code paths */
                x_Event_సమూహం = x_Event_సమూహం_Create();
            #అయితే_ముగింపు /* configSUPPORT_STATIC_ALLOCATION */
        }
    #అయితే_ముగింపు /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */
#అయితే_ముగింపు /* configSUPPORT_PICO_SYNC_INTEROP */

#ఒకవేళ ( config_SUPPORT_PICO_సమయం_INTEROP == 1 )
    శూన్య x_పోర్టు_Sync_అంతర్గత_Yield_Until_Before( absolute_సమయం_t t )
    {
        TickType_t ux_Ticks_గమ్యం_Wait = prv_Get_Ticks_గమ్యం_Wait_Before( t );

        ఒకవేళ( ux_Ticks_గమ్యం_Wait )
        {
            vTaskDelay( ux_Ticks_గమ్యం_Wait );
        }
    }
#అయితే_ముగింపు /* configSUPPORT_PICO_TIME_INTEROP */
