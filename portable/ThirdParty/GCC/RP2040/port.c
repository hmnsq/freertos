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

#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "rp2040_config.h"
#ضمن "hardware/clocks.h"
#ضمن "hardware/exception.h"

/*
 * LIB_PICO_MULTICORE == 1, if we are linked with pico_multicore (note that
 * the non SMP FreeRTOS_Kernel is not linked with pico_multicore itself). We
 * use this flag to determine if we need multi-core functionality.
 */
#إذا ( LIB_PICO_MULTICORE == 1 )
    #ضمن "pico/multicore.h"
#جيڪڏهن_پورو /* LIB_PICO_MULTICORE */

/* Constants required to manipulate the NVIC. */
#وصف_ڪريو پورٽ_NVIC_SYSTICK_CTRL_REG             ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_ڀريو_REG             ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG    ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#وصف_ڪريو پورٽ_NVIC_INT_CTRL_REG                 ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#وصف_ڪريو پورٽ_NVIC_SHPR3_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ              ( 1UL << 2UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_INT_ٻٽو_انگ              ( 1UL << 1UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_ENABLE_ٻٽو_انگ           ( 1UL << 0UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_ڳڻپ_FLAG_ٻٽو_انگ       ( 1UL << 16UL )
#وصف_ڪريو پورٽ_NVIC_PENDSVSET_ٻٽو_انگ                ( 1UL << 28UL )
#وصف_ڪريو پورٽ_MIN_مداخلت_ترجيح            ( 255UL )
#وصف_ڪريو پورٽ_NVIC_PENDSV_PRI                   ( پورٽ_MIN_مداخلت_ترجيح << 16UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_PRI                  ( پورٽ_MIN_مداخلت_ترجيح << 24UL )

/* Constants required to set up the initial stack. */
#وصف_ڪريو پورٽ_INITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#وصف_ڪريو پورٽ_MAX_24_ٻٽو_انگ_عدد                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#جيڪڏهن_وصف_نه_ٿيل پورٽ_MISSED_COUNTS_ضرب_ڪندڙ
    #وصف_ڪريو پورٽ_MISSED_COUNTS_ضرب_ڪندڙ    ( 45UL )
#جيڪڏهن_پورو

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#جيڪڏهن_وصف_ٿيل config_TASK_RETURN_پتو
    #وصف_ڪريو پورٽ_TASK_RETURN_پتو    config_TASK_RETURN_پتو
#وإلا
    #وصف_ڪريو پورٽ_TASK_RETURN_پتو    prvTaskExitError
#جيڪڏهن_پورو

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورٽ_تياري_Timer_مداخلت( فراغ );

/*
 * Exception handlers.
 */
فراغ x_پورٽ_Pend_SVHandler( فراغ ) __attribute__( ( naked ) );
فراغ x_پورٽ_Sys_Tick_Handler( فراغ );
فراغ v_پورٽ_SVCHandler( فراغ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ساكن فراغ v_پورٽ_شروعات_پهريون_Task( فراغ ) __attribute__( ( naked ) );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. This is initialized to 0 to allow vPortEnter/ExitCritical
 * to be called before the scheduler is started */
#إذا ( config_عدد_جو_CORES == 1 )
    ساكن UBaseType_t uxCriticalNesting;
#وإلا /* #if ( configNUMBER_OF_CORES == 1 ) */
UBaseType_t uxCriticalNestings[ config_عدد_جو_CORES ] = { 0 };
#جيڪڏهن_پورو /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

#إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 || config_عدد_جو_CORES > 1 )
    #ضمن "hardware/irq.h"
#جيڪڏهن_پورو /* ( configSUPPORT_PICO_SYNC_INTEROP == 1 || configNUMBER_OF_CORES > 1 ) */
#إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    #ضمن "pico/lock_core.h"
    #ضمن "event_groups.h"
    #إذا config_SUPPORT_STATIC_ورهاست
        ساكن Static_Event_گروهه_t x_Static_Event_گروهه;
        #وصف_ڪريو p_Event_گروهه    ( &x_Static_Event_گروهه )
    #جيڪڏهن_پورو /* configSUPPORT_STATIC_ALLOCATION */
    ساكن Event_گروهه_Handle_t x_Event_گروهه;
    #إذا ( config_عدد_جو_CORES == 1 )
        ساكن Event_بٽ_t ux_Cross_Core_Event_بٽ;
        ساكن spin_تالو_t * px_Cross_Core_Spin_تالو; /* protects uxCrossCoreEventBits */
    #جيڪڏهن_پورو
#جيڪڏهن_پورو /* configSUPPORT_PICO_SYNC_INTEROP */

/*
 * The number of SysTick increments that make up one tick period.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulTimerCountsForOneTick = 0;
#جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t x_وڌ_کان_وڌ_Possible_Suppressed_Ticks = 0;
#جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulStoppedTimerCompensation = 0;
#جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#وصف_ڪريو INVALID_PRIMARY_CORE_انگ    0xffu
/* The primary core number (the own which has the SysTick handler) */
ساكن uint8_t uc_Primary_Core_انگ = INVALID_PRIMARY_CORE_انگ;

/* Note: portIS_FREE_RTOS_CORE() also returns false until the scheduler is started */
#إذا ( config_عدد_جو_CORES != 1 )
    #وصف_ڪريو پورٽ_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_انگ != INVALID_PRIMARY_CORE_انگ )
#وإلا
    #وصف_ڪريو پورٽ_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_انگ == get_core_انگ() )
#جيڪڏهن_پورو

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_چوٽي_جو_ڍير--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_XPSR;                        /* xPSR */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ;                  /* PC */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_TASK_RETURN_پتو; /* LR */
    px_چوٽي_جو_ڍير -= 5;                                       /* R12, R3, R2 and R1. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters;            /* R0 */
    px_چوٽي_جو_ڍير -= 8;                                       /* R11..R4. */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvTaskExitError( فراغ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ). */
    panic_unsupported();
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_SVCHandler( فراغ )
{
    /* This function is no longer used, but retained for backward
     * compatibility. */
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_شروعات_پهريون_Task( فراغ )
{
    #إذا ( config_عدد_جو_CORES == 1 )
        __asm متطاير (
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
    #وإلا /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm متطاير (
            "    .syntax unified                    \n"
            #إذا config_RESET_ڍير_اشارو
                "   ldr  r0, =0xE000ED08            \n" /* Use the NVIC offset register to locate the stack. */
                "   ldr r0, [r0]                    \n"
                "   ldr r0, [r0]                    \n"
                "   msr msp, r0                     \n" /* Set the msp back to the start of the stack. */
            #جيڪڏهن_پورو /* configRESET_STACK_POINTER */
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
    #جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#إذا ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    ساكن فراغ prvFIFOInterruptHandler()
    {
        /* We must remove the contents (which we don't care about)
         * to clear the IRQ */
        multicore_fifo_drain();

        /* And explicitly clear any other IRQ flags. */
        multicore_fifo_clear_irq();

        #إذا ( config_عدد_جو_CORES != 1 )
            پورٽ_YIELD_FROM_ISR( pdTRUE );
        #وإلاإذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
            بنياد_Type_t x_Higher_ترجيح_Task_Woken = pdFALSE;
            uint32_t ulSave = spin_تالو_blocking( px_Cross_Core_Spin_تالو );
            Event_بٽ_t ul_بٽ = ux_Cross_Core_Event_بٽ;
            ux_Cross_Core_Event_بٽ &= ~ul_بٽ;
            spin_unlock( px_Cross_Core_Spin_تالو, ulSave );
            x_Event_گروهه_سيٽ_بٽ_From_ISR( x_Event_گروهه, ul_بٽ, &x_Higher_ترجيح_Task_Woken );
            پورٽ_YIELD_FROM_ISR( x_Higher_ترجيح_Task_Woken );
        #جيڪڏهن_پورو /* configNUMBER_OF_CORES != 1 */
    }
#جيڪڏهن_پورو /* if ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */

#إذا ( config_عدد_جو_CORES > 1 )

/*
 * See header file for description.
 */
    ساكن بنياد_Type_t x_پورٽ_شروعات_Scheduler_On_Core()
    {
        إذا( uc_Primary_Core_انگ == get_core_انگ() )
        {
            /* Start the timer that generates the tick ISR.  Interrupts are disabled
             * here already. */
            v_پورٽ_تياري_Timer_مداخلت();

            /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
            پورٽ_NVIC_SHPR3_REG |= پورٽ_NVIC_SYSTICK_PRI;
            #إذا ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
                exception_سيٽ_exclusive_handler( SYSTICK_EXCEPTION, x_پورٽ_Sys_Tick_Handler );
            #جيڪڏهن_پورو
        }

        پورٽ_NVIC_SHPR3_REG |= پورٽ_NVIC_PENDSV_PRI;

        #إذا ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_سيٽ_exclusive_handler( PENDSV_EXCEPTION, x_پورٽ_Pend_SVHandler );
            exception_سيٽ_exclusive_handler( SVCALL_EXCEPTION, v_پورٽ_SVCHandler );
        #جيڪڏهن_پورو

        /* Install FIFO handler to receive interrupt from other core */
        multicore_fifo_clear_irq();
        multicore_fifo_drain();
        uint32_t ulIRQNum = SIO_IRQ_PROC0 + get_core_انگ();
        irq_سيٽ_ترجيح( ulIRQNum, پورٽ_MIN_مداخلت_ترجيح );
        irq_سيٽ_exclusive_handler( ulIRQNum, prvFIFOInterruptHandler );
        irq_سيٽ_enabled( ulIRQNum, 1 );

        /* Start the first task. */
        v_پورٽ_شروعات_پهريون_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext( پورٽ_GET_CORE_ID() );
        prvTaskExitError();

        /* Should not get here. */
        أرجع 0;
    }

    ساكن فراغ prv_Disable_Interrupts_And_پورٽ_شروعات_Scheduler_On_Core( فراغ )
    {
        پورٽ_DISABLE_INTERRUPTS();
        x_پورٽ_شروعات_Scheduler_On_Core();
    }

/*
 * See header file for description.
 */
    بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
    {
        configASSERT( uc_Primary_Core_انگ == INVALID_PRIMARY_CORE_انگ );

        /* No one else should use these! */
        spin_تالو_claim( configSMP_SPINLOCK_0 );
        spin_تالو_claim( configSMP_SPINLOCK_1 );

        uc_Primary_Core_انگ = configTICK_CORE;
        configASSERT( get_core_انگ() == 0 ); /* we must be started on core 0 */
        multicore_reset_core1();
        multicore_launch_core1( prv_Disable_Interrupts_And_پورٽ_شروعات_Scheduler_On_Core );

        x_پورٽ_شروعات_Scheduler_On_Core();

        /* Should not get here! */
        أرجع 0;
    }

#وإلا /* if ( configNUMBER_OF_CORES > 1 ) */

/*
 * See header file for description.
 */
    بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
    {
        /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
        پورٽ_NVIC_SHPR3_REG |= پورٽ_NVIC_PENDSV_PRI;
        پورٽ_NVIC_SHPR3_REG |= پورٽ_NVIC_SYSTICK_PRI;

        #إذا ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_سيٽ_exclusive_handler( PENDSV_EXCEPTION, x_پورٽ_Pend_SVHandler );
            exception_سيٽ_exclusive_handler( SYSTICK_EXCEPTION, x_پورٽ_Sys_Tick_Handler );
            exception_سيٽ_exclusive_handler( SVCALL_EXCEPTION, v_پورٽ_SVCHandler );
        #جيڪڏهن_پورو

        /* Start the timer that generates the tick ISR.  Interrupts are disabled
         * here already. */
        v_پورٽ_تياري_Timer_مداخلت();

        /* Initialise the critical nesting count ready for the first task. */
        uxCriticalNesting = 0;

        uc_Primary_Core_انگ = get_core_انگ();
        #إذا ( LIB_PICO_MULTICORE == 1 )
            #إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
                multicore_fifo_clear_irq();
                multicore_fifo_drain();
                uint32_t irq_انگ = SIO_IRQ_PROC0 + get_core_انگ();
                irq_سيٽ_ترجيح( irq_انگ, پورٽ_MIN_مداخلت_ترجيح );
                irq_سيٽ_exclusive_handler( irq_انگ, prvFIFOInterruptHandler );
                irq_سيٽ_enabled( irq_انگ, 1 );
            #جيڪڏهن_پورو
        #جيڪڏهن_پورو

        /* Start the first task. */
        v_پورٽ_شروعات_پهريون_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext();
        prvTaskExitError();

        /* Should not get here! */
        أرجع 0;
    }
#جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES > 1 ) */

/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( پورٽ_GET_CORE_ID() == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Yield( فراغ )
{
    /* Set a PendSV to request a context switch. */
    پورٽ_NVIC_INT_CTRL_REG = پورٽ_NVIC_PENDSVSET_ٻٽو_انگ;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __asm متطاير ( "dsb" ::: "memory" );
    __asm متطاير ( "isb" );
}

/*-----------------------------------------------------------*/

#إذا ( config_عدد_جو_CORES == 1 )
    فراغ v_پورٽ_Enter_Critical( فراغ )
    {
        پورٽ_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
        __asm متطاير ( "dsb" ::: "memory" );
        __asm متطاير ( "isb" );
    }
#جيڪڏهن_پورو /* #if ( configNUMBER_OF_CORES == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_عدد_جو_CORES == 1 )
    فراغ v_پورٽ_Exit_Critical( فراغ )
    {
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        إذا( uxCriticalNesting == 0 )
        {
            پورٽ_ENABLE_INTERRUPTS();
        }
    }
#جيڪڏهن_پورو /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

uint32_t ul_سيٽ_مداخلت_نقاب_From_ISR( فراغ )
{
    __asm متطاير (
        " mrs r0, PRIMASK    \n"
        " cpsid i            \n"
        " bx lr                "
        ::: "memory"
        );
}
/*-----------------------------------------------------------*/

فراغ v_Clear_مداخلت_نقاب_From_ISR( __attribute__( ( اڻ_استعمال_ٿيل ) ) uint32_t ul_نقاب )
{
    __asm متطاير (
        " msr PRIMASK, r0    \n"
        " bx lr                "
        ::: "memory"
        );
}

/*-----------------------------------------------------------*/

فراغ vYieldCore( صحيح xCoreID )
{
    /* Remove warning if configASSERT is not defined.
     * xCoreID is not used in this function due to this is a dual-core system. The yielding core must be different from the current core. */
    ( فراغ ) xCoreID;

    configASSERT( xCoreID != ( صحيح ) پورٽ_GET_CORE_ID() );

    #إذا config_عدد_جو_CORES != 1

        /* Non blocking, will cause interrupt on other core if the queue isn't already full,
         * in which case an IRQ must be pending */
        sio_hw->fifo_wr = 0;
    #جيڪڏهن_پورو
}

/*-----------------------------------------------------------*/

فراغ x_پورٽ_Pend_SVHandler( فراغ )
{
    /* This is a naked function. */
    #إذا ( config_عدد_جو_CORES == 1 )
        __asm متطاير
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
            #إذا پورٽ_USE_DIVIDER_SAVE_RESTORE
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
            #جيڪڏهن_پورو /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #إذا پورٽ_USE_DIVIDER_SAVE_RESTORE
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
            #وإلا /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                    \n" /* Go back for the low registers that are not automatically restored. */
            #جيڪڏهن_پورو /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                  \n"     /* Pop low registers.  */
            "                                       \n"
            "   bx r3                               \n"
            "   .align 4                            \n"
            "pxCurrentTCBConst2: .word pxCurrentTCB \n"
        );
    #وإلا /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm متطاير
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
            #إذا پورٽ_USE_DIVIDER_SAVE_RESTORE

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
            #جيڪڏهن_پورو /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #إذا پورٽ_USE_DIVIDER_SAVE_RESTORE
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
            #وإلا /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                   \n" /* Go back for the low registers that are not automatically restored. */
            #جيڪڏهن_پورو /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                 \n"     /* Pop low registers.  */
            "                                      \n"
            "   bx r3                              \n"
            "                                      \n"
            "   .align 4                           \n"
            "ulAsmLocals2:                         \n"
            "   .word 0xD0000000                   \n" /* SIO */
            "   .word pxCurrentTCBs                \n"
        );
    #جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

فراغ x_پورٽ_Sys_Tick_Handler( فراغ )
{
    uint32_t ul_اڳيون_نقاب;

    ul_اڳيون_نقاب = taskENTER_CRITICAL_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_منزل_SCHEDULER();
            /* Pend a context switch. */
            پورٽ_NVIC_INT_CTRL_REG = پورٽ_NVIC_PENDSVSET_ٻٽو_انگ;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    taskEXIT_CRITICAL_FROM_ISR( ul_اڳيون_نقاب );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) فراغ v_پورٽ_تياري_Timer_مداخلت( فراغ )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #إذا ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( clock_get_hz( clk_sys ) / config_TICK_شرح_HZ );
        x_وڌ_کان_وڌ_Possible_Suppressed_Ticks = پورٽ_MAX_24_ٻٽو_انگ_عدد / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورٽ_MISSED_COUNTS_ضرب_ڪندڙ;
    }
    #جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */

    /* Stop and reset the SysTick. */
    پورٽ_NVIC_SYSTICK_CTRL_REG = 0UL;
    پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورٽ_NVIC_SYSTICK_ڀريو_REG = ( clock_get_hz( clk_sys ) / config_TICK_شرح_HZ ) - 1UL;
    پورٽ_NVIC_SYSTICK_CTRL_REG = پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ | پورٽ_NVIC_SYSTICK_INT_ٻٽو_انگ | پورٽ_NVIC_SYSTICK_ENABLE_ٻٽو_انگ;
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) فراغ v_پورٽ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت )
    {
        uint32_t ul_Reload_قدر, ulCompleteTickPeriods, ulCompletedSysTickDecrements;
        TickType_t x_Modifiable_Idle_وقت;

        /* Make sure the SysTick reload value does not overflow the counter. */
        إذا( x_Expected_Idle_وقت > x_وڌ_کان_وڌ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_وقت = x_وڌ_کان_وڌ_Possible_Suppressed_Ticks;
        }

        /* Stop the SysTick momentarily.  The time the SysTick is stopped for
         * is accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        پورٽ_NVIC_SYSTICK_CTRL_REG &= ~پورٽ_NVIC_SYSTICK_ENABLE_ٻٽو_انگ;

        /* Calculate the reload value required to wait xExpectedIdleTime
         * tick periods.  -1 is used because this code will execute part way
         * through one of the tick periods. */
        ul_Reload_قدر = پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG + ( ulTimerCountsForOneTick * ( x_Expected_Idle_وقت - 1UL ) );

        إذا( ul_Reload_قدر > ulStoppedTimerCompensation )
        {
            ul_Reload_قدر -= ulStoppedTimerCompensation;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm متطاير ( "cpsid i" ::: "memory" );
        __asm متطاير ( "dsb" );
        __asm متطاير ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_گهڻائي_حالت() == eAbortSleep )
        {
            /* Restart from whatever is left in the count register to complete
             * this tick period. */
            پورٽ_NVIC_SYSTICK_ڀريو_REG = پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG;

            /* Restart SysTick. */
            پورٽ_NVIC_SYSTICK_CTRL_REG |= پورٽ_NVIC_SYSTICK_ENABLE_ٻٽو_انگ;

            /* Reset the reload register to the value required for normal tick
             * periods. */
            پورٽ_NVIC_SYSTICK_ڀريو_REG = ulTimerCountsForOneTick - 1UL;

            /* Re-enable interrupts - see comments above the cpsid instruction()
             * above. */
            __asm متطاير ( "cpsie i" ::: "memory" );
        }
        وإلا
        {
            /* Set the new reload value. */
            پورٽ_NVIC_SYSTICK_ڀريو_REG = ul_Reload_قدر;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

            /* Restart SysTick. */
            پورٽ_NVIC_SYSTICK_CTRL_REG |= پورٽ_NVIC_SYSTICK_ENABLE_ٻٽو_انگ;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_وقت = x_Expected_Idle_وقت;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_وقت );

            إذا( x_Modifiable_Idle_وقت > 0 )
            {
                __asm متطاير ( "dsb" ::: "memory" );
                __asm متطاير ( "wfi" );
                __asm متطاير ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_وقت );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  see comments above
             * __disable_interrupt() call above. */
            __asm متطاير ( "cpsie i" ::: "memory" );
            __asm متطاير ( "dsb" );
            __asm متطاير ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm متطاير ( "cpsid i" ::: "memory" );
            __asm متطاير ( "dsb" );
            __asm متطاير ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            پورٽ_NVIC_SYSTICK_CTRL_REG = ( پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ | پورٽ_NVIC_SYSTICK_INT_ٻٽو_انگ );

            /* Determine if the SysTick clock has already counted to zero and
             * been set back to the current reload value (the reload back being
             * correct for the entire expected idle time) or if the SysTick is yet
             * to count to zero (in which case an interrupt other than the SysTick
             * must have brought the system out of sleep mode). */
            إذا( ( پورٽ_NVIC_SYSTICK_CTRL_REG & پورٽ_NVIC_SYSTICK_ڳڻپ_FLAG_ٻٽو_انگ ) != 0 )
            {
                uint32_t ul_Calculated_ڀريو_قدر;

                /* The tick interrupt is already pending, and the SysTick count
                 * reloaded with ulReloadValue.  Reset the
                 * portNVIC_SYSTICK_LOAD_REG with whatever remains of this tick
                 * period. */
                ul_Calculated_ڀريو_قدر = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_قدر - پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long. */
                إذا( ( ul_Calculated_ڀريو_قدر < ulStoppedTimerCompensation ) || ( ul_Calculated_ڀريو_قدر > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_ڀريو_قدر = ( ulTimerCountsForOneTick - 1UL );
                }

                پورٽ_NVIC_SYSTICK_ڀريو_REG = ul_Calculated_ڀريو_قدر;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_وقت - 1UL;
            }
            وإلا
            {
                /* Something other than the tick interrupt ended the sleep.
                 * Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_وقت * ulTimerCountsForOneTick ) - پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورٽ_NVIC_SYSTICK_ڀريو_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG
             * again, then set portNVIC_SYSTICK_LOAD_REG back to its standard
             * value. */
            پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;
            پورٽ_NVIC_SYSTICK_CTRL_REG |= پورٽ_NVIC_SYSTICK_ENABLE_ٻٽو_انگ;
            v_Task_قدم_Tick( ulCompleteTickPeriods );
            پورٽ_NVIC_SYSTICK_ڀريو_REG = ulTimerCountsForOneTick - 1UL;

            /* Exit with interrupts enabled. */
            __asm متطاير ( "cpsie i" ::: "memory" );
        }
    }

#جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */

#إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( config_SUPPORT_PICO_وقت_INTEROP == 1 )
    ساكن TickType_t prv_Get_Ticks_منزل_Wait_Before( absolute_وقت_t t )
    {
        int64_t xDelay = absolute_وقت_diff_us( get_absolute_وقت(), t );
        ثابت uint32_t ulTickPeriod = 1000000 / config_TICK_شرح_HZ;

        xDelay -= ulTickPeriod;

        إذا( xDelay >= ulTickPeriod )
        {
            أرجع xDelay / ulTickPeriod;
        }

        أرجع 0;
    }
#جيڪڏهن_پورو /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( configSUPPORT_PICO_TIME_INTEROP == 1 ) */

#إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    uint32_t ul_پورٽ_تالو_Get_Current_Owner_Id()
    {
        إذا( پورٽ_IS_FREE_RTOS_CORE() )
        {
            uint32_t exception = __get_current_exception();

            إذا( !exception )
            {
                أرجع ( uintptr_t ) xTaskGetCurrentTaskHandle();
            }

            /* Note: since ROM as at 0x00000000, these can't be confused with
             * valid task handles (pointers) in RAM */
            /* We make all exception handler/core combinations distinct owners */
            أرجع get_core_انگ() + exception * 2;
        }

        /* Note: since ROM as at 0x00000000, this can't be confused with
         * valid task handles (pointers) in RAM */
        أرجع get_core_انگ();
    }

    ساكن مضمن Event_بٽ_t prv_Get_Event_گروهه_ٻٽو_انگ( spin_تالو_t * spin_تالو )
    {
        uint32_t ul_ٻٽو_انگ;

        #إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
            ul_ٻٽو_انگ = 1u << ( spin_تالو_get_انگ( spin_تالو ) & 0x7u );
        #وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
            /* Avoid potential use of SIO divider for % here out of abundance of caution */
            ul_ٻٽو_انگ = spin_تالو_get_انگ( spin_تالو );
            إذا (ul_ٻٽو_انگ >= 24) ul_ٻٽو_انگ -= 24;
            ul_ٻٽو_انگ = 1u << ul_ٻٽو_انگ;
        #جيڪڏهن_پورو /* configTICK_TYPE_WIDTH_IN_BITS */
        أرجع ( Event_بٽ_t ) ul_ٻٽو_انگ;
    }

    ساكن مضمن Event_بٽ_t prv_Get_All_Event_گروهه_بٽ()
    {
        #إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
            أرجع ( Event_بٽ_t ) 0xffu;
        #وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
            أرجع ( Event_بٽ_t ) 0xffffffu;
        #جيڪڏهن_پورو /* configTICK_TYPE_WIDTH_IN_BITS */
    }

    فراغ v_پورٽ_تالو_اندروني_Spin_Unlock_With_Wait( بنية تالو_core * px_تالو,
                                              uint32_t ulSave )
    {
        configASSERT( !پورٽ_CHECK_IF_اندريون_ISR() );
        configASSERT( px_تالو->spin_تالو_2 );

        إذا( !پورٽ_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_تالو->spin_تالو_2, ulSave );
            __wfe();
        }
        وإلا
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
            spin_unlock( px_تالو->spin_تالو_2, ulSave);
            x_Event_گروهه_Wait_بٽ( x_Event_گروهه, prv_Get_Event_گروهه_ٻٽو_انگ( px_تالو->spin_تالو_2 ),
                                 pdTRUE, pdFALSE, پورٽ_MAX_DELAY );
        }
    }

    فراغ v_پورٽ_تالو_اندروني_Spin_Unlock_With_Notify( بنية تالو_core * px_تالو,
                                                uint32_t ulSave )
    {
        Event_بٽ_t ux_بٽ = prv_Get_Event_گروهه_ٻٽو_انگ( px_تالو->spin_تالو_2 );

        إذا( پورٽ_IS_FREE_RTOS_CORE() )
        {
            #إذا LIB_PICO_MULTICORE
                /* signal an event in case a regular core is waiting */
                __sev();
            #جيڪڏهن_پورو
            spin_unlock( px_تالو->spin_تالو_2, ulSave );

            إذا( !پورٽ_CHECK_IF_اندريون_ISR() )
            {
                x_Event_گروهه_سيٽ_بٽ( x_Event_گروهه, ux_بٽ );
            }
            وإلا
            {
                بنياد_Type_t x_Higher_ترجيح_Task_Woken = pdFALSE;
                x_Event_گروهه_سيٽ_بٽ_From_ISR( x_Event_گروهه, ux_بٽ, &x_Higher_ترجيح_Task_Woken );
                پورٽ_YIELD_FROM_ISR( x_Higher_ترجيح_Task_Woken );
            }
        }
        وإلا
        {
            __sev();
            #إذا ( config_عدد_جو_CORES == 1 )
                إذا( px_Cross_Core_Spin_تالو != px_تالو->spin_تالو_2 )
                {
                    spin_تالو_unsafe_blocking( px_Cross_Core_Spin_تالو );
                    ux_Cross_Core_Event_بٽ |= ux_بٽ;
                    spin_unlock_unsafe( px_Cross_Core_Spin_تالو );
                }
                وإلا
                {
                    ux_Cross_Core_Event_بٽ |= ux_بٽ;
                }

                /* This causes fifo irq on the other (FreeRTOS) core which will do the set the event bits */
                sio_hw->fifo_wr = 0;
            #جيڪڏهن_پورو /* configNUMBER_OF_CORES == 1 */
            spin_unlock( px_تالو->spin_تالو_2, ulSave );
        }
    }

    bool x_پورٽ_تالو_اندروني_Spin_Unlock_With_بهترين_Effort_Wait_Or_Timeout( بنية تالو_core * px_تالو,
                                                                 uint32_t ulSave,
                                                                 absolute_وقت_t uxUntil )
    {
        configASSERT( !پورٽ_CHECK_IF_اندريون_ISR() );
        configASSERT( px_تالو->spin_تالو_2 );

        /* note no need to check LIB_PICO_MULTICORE, as this is always returns true if that is not defined */
        إذا( !پورٽ_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_تالو->spin_تالو_2, ulSave );
            أرجع بهترين_effort_wfe_or_timeout( uxUntil );
        }
        وإلا
        {
            configASSERT( پورٽ_IS_FREE_RTOS_CORE() );

            TickType_t ux_Ticks_منزل_Wait = prv_Get_Ticks_منزل_Wait_Before( uxUntil );

            إذا( ux_Ticks_منزل_Wait )
            {
                /* See comment in vPortLockInternalSpinUnlockWithWait for detail
                 * about possible race conditions */
                spin_unlock( px_تالو->spin_تالو_2, ulSave );
                x_Event_گروهه_Wait_بٽ( x_Event_گروهه,
                                     prv_Get_Event_گروهه_ٻٽو_انگ( px_تالو->spin_تالو_2 ), pdTRUE,
                                     pdFALSE, ux_Ticks_منزل_Wait );
            }
            وإلا
            {
                spin_unlock( px_تالو->spin_تالو_2, ulSave );
            }

            إذا( وقت_reached( uxUntil ) )
            {
                أرجع true;
            }
            وإلا
            {
                /* We do not want to hog the core */
                پورٽ_YIELD();
                /* We aren't sure if we've reached the timeout yet; the caller will check */
                أرجع false;
            }
        }
    }

    #إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* runs before main */
        ساكن فراغ __attribute__( ( constructor ) ) prvRuntimeInitializer( فراغ )
        {
            /* This must be done even before the scheduler is started, as the spin lock
             * is used by the overrides of the SDK wait/notify primitives */
            #إذا ( config_عدد_جو_CORES == 1 )
                px_Cross_Core_Spin_تالو = spin_تالو_instance( ايندڙ_striped_spin_تالو_انگ() );
            #جيڪڏهن_پورو /* configNUMBER_OF_CORES == 1 */

            /* The event group is not used prior to scheduler init, but is initialized
             * here to since it logically belongs with the spin lock */
            #إذا ( config_SUPPORT_STATIC_ورهاست == 1 )
                x_Event_گروهه = x_Event_گروهه_Create_Static( &x_Static_Event_گروهه );
            #وإلا

                /* Note that it is slightly dubious calling this here before the scheduler is initialized,
                 * however the only thing it touches is the allocator which then calls vPortEnterCritical
                 * and vPortExitCritical, and allocating here saves us checking the one time initialized variable in
                 * some rather critical code paths */
                x_Event_گروهه = x_Event_گروهه_Create();
            #جيڪڏهن_پورو /* configSUPPORT_STATIC_ALLOCATION */
        }
    #جيڪڏهن_پورو /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */
#جيڪڏهن_پورو /* configSUPPORT_PICO_SYNC_INTEROP */

#إذا ( config_SUPPORT_PICO_وقت_INTEROP == 1 )
    فراغ x_پورٽ_Sync_اندروني_Yield_Until_Before( absolute_وقت_t t )
    {
        TickType_t ux_Ticks_منزل_Wait = prv_Get_Ticks_منزل_Wait_Before( t );

        إذا( ux_Ticks_منزل_Wait )
        {
            vTaskDelay( ux_Ticks_منزل_Wait );
        }
    }
#جيڪڏهن_پورو /* configSUPPORT_PICO_TIME_INTEROP */
