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
#د_که_پای /* LIB_PICO_MULTICORE */

/* Constants required to manipulate the NVIC. */
#تعریف_کړه پورټ_NVIC_SYSTICK_CTRL_REG             ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#تعریف_کړه پورټ_NVIC_SYSTICK_بارول_REG             ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#تعریف_کړه پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG    ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#تعریف_کړه پورټ_NVIC_INT_CTRL_REG                 ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کړه پورټ_NVIC_SHPR3_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
#تعریف_کړه پورټ_NVIC_SYSTICK_CLK_بټ              ( 1UL << 2UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_INT_بټ              ( 1UL << 1UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_ENABLE_بټ           ( 1UL << 0UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_شمېر_FLAG_بټ       ( 1UL << 16UL )
#تعریف_کړه پورټ_NVIC_PENDSVSET_بټ                ( 1UL << 28UL )
#تعریف_کړه پورټ_MIN_مداخله_لومړیتوب            ( 255UL )
#تعریف_کړه پورټ_NVIC_PENDSV_PRI                   ( پورټ_MIN_مداخله_لومړیتوب << 16UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_PRI                  ( پورټ_MIN_مداخله_لومړیتوب << 24UL )

/* Constants required to set up the initial stack. */
#تعریف_کړه پورټ_INITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#تعریف_کړه پورټ_MAX_24_بټ_شمېره                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#که_نه_تعریف_شوی پورټ_MISSED_COUNTS_ضریب
    #تعریف_کړه پورټ_MISSED_COUNTS_ضریب    ( 45UL )
#د_که_پای

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#که_تعریف_شوی config_TASK_RETURN_پته
    #تعریف_کړه پورټ_TASK_RETURN_پته    config_TASK_RETURN_پته
#وإلا
    #تعریف_کړه پورټ_TASK_RETURN_پته    prvTaskExitError
#د_که_پای

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورټ_تیاری_Timer_مداخله( فراغ );

/*
 * Exception handlers.
 */
فراغ x_پورټ_Pend_SVHandler( فراغ ) __attribute__( ( naked ) );
فراغ x_پورټ_Sys_Tick_Handler( فراغ );
فراغ v_پورټ_SVCHandler( فراغ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ساكن فراغ v_پورټ_پیل_لومړی_Task( فراغ ) __attribute__( ( naked ) );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. This is initialized to 0 to allow vPortEnter/ExitCritical
 * to be called before the scheduler is started */
#إذا ( config_شمېره_د_CORES == 1 )
    ساكن UBaseType_t uxCriticalNesting;
#وإلا /* #if ( configNUMBER_OF_CORES == 1 ) */
UBaseType_t uxCriticalNestings[ config_شمېره_د_CORES ] = { 0 };
#د_که_پای /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

#إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 || config_شمېره_د_CORES > 1 )
    #ضمن "hardware/irq.h"
#د_که_پای /* ( configSUPPORT_PICO_SYNC_INTEROP == 1 || configNUMBER_OF_CORES > 1 ) */
#إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    #ضمن "pico/lock_core.h"
    #ضمن "event_groups.h"
    #إذا config_SUPPORT_STATIC_ویش
        ساكن Static_Event_ډله_t x_Static_Event_ډله;
        #تعریف_کړه p_Event_ډله    ( &x_Static_Event_ډله )
    #د_که_پای /* configSUPPORT_STATIC_ALLOCATION */
    ساكن Event_ډله_Handle_t x_Event_ډله;
    #إذا ( config_شمېره_د_CORES == 1 )
        ساكن Event_بټونه_t ux_Cross_Core_Event_بټونه;
        ساكن spin_قلف_t * px_Cross_Core_Spin_قلف; /* protects uxCrossCoreEventBits */
    #د_که_پای
#د_که_پای /* configSUPPORT_PICO_SYNC_INTEROP */

/*
 * The number of SysTick increments that make up one tick period.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulTimerCountsForOneTick = 0;
#د_که_پای /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t x_اعظمي_Possible_Suppressed_Ticks = 0;
#د_که_پای /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulStoppedTimerCompensation = 0;
#د_که_پای /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#تعریف_کړه INVALID_PRIMARY_CORE_عدد    0xffu
/* The primary core number (the own which has the SysTick handler) */
ساكن uint8_t uc_Primary_Core_عدد = INVALID_PRIMARY_CORE_عدد;

/* Note: portIS_FREE_RTOS_CORE() also returns false until the scheduler is started */
#إذا ( config_شمېره_د_CORES != 1 )
    #تعریف_کړه پورټ_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_عدد != INVALID_PRIMARY_CORE_عدد )
#وإلا
    #تعریف_کړه پورټ_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_عدد == get_core_عدد() )
#د_که_پای

/*
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_سر_د_ډېری--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_سر_د_ډېری = پورټ_INITIAL_XPSR;                        /* xPSR */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ;                  /* PC */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_TASK_RETURN_پته; /* LR */
    px_سر_د_ډېری -= 5;                                       /* R12, R3, R2 and R1. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;            /* R0 */
    px_سر_د_ډېری -= 8;                                       /* R11..R4. */

    أرجع px_سر_د_ډېری;
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

فراغ v_پورټ_SVCHandler( فراغ )
{
    /* This function is no longer used, but retained for backward
     * compatibility. */
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پیل_لومړی_Task( فراغ )
{
    #إذا ( config_شمېره_د_CORES == 1 )
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
            #إذا config_RESET_ډېری_اشاره_ګر
                "   ldr  r0, =0xE000ED08            \n" /* Use the NVIC offset register to locate the stack. */
                "   ldr r0, [r0]                    \n"
                "   ldr r0, [r0]                    \n"
                "   msr msp, r0                     \n" /* Set the msp back to the start of the stack. */
            #د_که_پای /* configRESET_STACK_POINTER */
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
    #د_که_پای /* if ( configNUMBER_OF_CORES == 1 ) */
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

        #إذا ( config_شمېره_د_CORES != 1 )
            پورټ_YIELD_FROM_ISR( pdTRUE );
        #وإلاإذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
            بنسټ_Type_t x_Higher_لومړیتوب_Task_Woken = pdFALSE;
            uint32_t ulSave = spin_قلف_blocking( px_Cross_Core_Spin_قلف );
            Event_بټونه_t ul_بټونه = ux_Cross_Core_Event_بټونه;
            ux_Cross_Core_Event_بټونه &= ~ul_بټونه;
            spin_unlock( px_Cross_Core_Spin_قلف, ulSave );
            x_Event_ډله_سېټ_بټونه_From_ISR( x_Event_ډله, ul_بټونه, &x_Higher_لومړیتوب_Task_Woken );
            پورټ_YIELD_FROM_ISR( x_Higher_لومړیتوب_Task_Woken );
        #د_که_پای /* configNUMBER_OF_CORES != 1 */
    }
#د_که_پای /* if ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */

#إذا ( config_شمېره_د_CORES > 1 )

/*
 * See header file for description.
 */
    ساكن بنسټ_Type_t x_پورټ_پیل_Scheduler_On_Core()
    {
        إذا( uc_Primary_Core_عدد == get_core_عدد() )
        {
            /* Start the timer that generates the tick ISR.  Interrupts are disabled
             * here already. */
            v_پورټ_تیاری_Timer_مداخله();

            /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
            پورټ_NVIC_SHPR3_REG |= پورټ_NVIC_SYSTICK_PRI;
            #إذا ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
                exception_سېټ_exclusive_handler( SYSTICK_EXCEPTION, x_پورټ_Sys_Tick_Handler );
            #د_که_پای
        }

        پورټ_NVIC_SHPR3_REG |= پورټ_NVIC_PENDSV_PRI;

        #إذا ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_سېټ_exclusive_handler( PENDSV_EXCEPTION, x_پورټ_Pend_SVHandler );
            exception_سېټ_exclusive_handler( SVCALL_EXCEPTION, v_پورټ_SVCHandler );
        #د_که_پای

        /* Install FIFO handler to receive interrupt from other core */
        multicore_fifo_clear_irq();
        multicore_fifo_drain();
        uint32_t ulIRQNum = SIO_IRQ_PROC0 + get_core_عدد();
        irq_سېټ_لومړیتوب( ulIRQNum, پورټ_MIN_مداخله_لومړیتوب );
        irq_سېټ_exclusive_handler( ulIRQNum, prvFIFOInterruptHandler );
        irq_سېټ_enabled( ulIRQNum, 1 );

        /* Start the first task. */
        v_پورټ_پیل_لومړی_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext( پورټ_GET_CORE_ID() );
        prvTaskExitError();

        /* Should not get here. */
        أرجع 0;
    }

    ساكن فراغ prv_Disable_Interrupts_And_پورټ_پیل_Scheduler_On_Core( فراغ )
    {
        پورټ_DISABLE_INTERRUPTS();
        x_پورټ_پیل_Scheduler_On_Core();
    }

/*
 * See header file for description.
 */
    بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
    {
        configASSERT( uc_Primary_Core_عدد == INVALID_PRIMARY_CORE_عدد );

        /* No one else should use these! */
        spin_قلف_claim( configSMP_SPINLOCK_0 );
        spin_قلف_claim( configSMP_SPINLOCK_1 );

        uc_Primary_Core_عدد = configTICK_CORE;
        configASSERT( get_core_عدد() == 0 ); /* we must be started on core 0 */
        multicore_reset_core1();
        multicore_launch_core1( prv_Disable_Interrupts_And_پورټ_پیل_Scheduler_On_Core );

        x_پورټ_پیل_Scheduler_On_Core();

        /* Should not get here! */
        أرجع 0;
    }

#وإلا /* if ( configNUMBER_OF_CORES > 1 ) */

/*
 * See header file for description.
 */
    بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
    {
        /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
        پورټ_NVIC_SHPR3_REG |= پورټ_NVIC_PENDSV_PRI;
        پورټ_NVIC_SHPR3_REG |= پورټ_NVIC_SYSTICK_PRI;

        #إذا ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_سېټ_exclusive_handler( PENDSV_EXCEPTION, x_پورټ_Pend_SVHandler );
            exception_سېټ_exclusive_handler( SYSTICK_EXCEPTION, x_پورټ_Sys_Tick_Handler );
            exception_سېټ_exclusive_handler( SVCALL_EXCEPTION, v_پورټ_SVCHandler );
        #د_که_پای

        /* Start the timer that generates the tick ISR.  Interrupts are disabled
         * here already. */
        v_پورټ_تیاری_Timer_مداخله();

        /* Initialise the critical nesting count ready for the first task. */
        uxCriticalNesting = 0;

        uc_Primary_Core_عدد = get_core_عدد();
        #إذا ( LIB_PICO_MULTICORE == 1 )
            #إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
                multicore_fifo_clear_irq();
                multicore_fifo_drain();
                uint32_t irq_عدد = SIO_IRQ_PROC0 + get_core_عدد();
                irq_سېټ_لومړیتوب( irq_عدد, پورټ_MIN_مداخله_لومړیتوب );
                irq_سېټ_exclusive_handler( irq_عدد, prvFIFOInterruptHandler );
                irq_سېټ_enabled( irq_عدد, 1 );
            #د_که_پای
        #د_که_پای

        /* Start the first task. */
        v_پورټ_پیل_لومړی_Task();

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
#د_که_پای /* if ( configNUMBER_OF_CORES > 1 ) */

/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( پورټ_GET_CORE_ID() == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Yield( فراغ )
{
    /* Set a PendSV to request a context switch. */
    پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PENDSVSET_بټ;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __asm متطاير ( "dsb" ::: "memory" );
    __asm متطاير ( "isb" );
}

/*-----------------------------------------------------------*/

#إذا ( config_شمېره_د_CORES == 1 )
    فراغ v_پورټ_Enter_Critical( فراغ )
    {
        پورټ_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
        __asm متطاير ( "dsb" ::: "memory" );
        __asm متطاير ( "isb" );
    }
#د_که_پای /* #if ( configNUMBER_OF_CORES == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_شمېره_د_CORES == 1 )
    فراغ v_پورټ_Exit_Critical( فراغ )
    {
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        إذا( uxCriticalNesting == 0 )
        {
            پورټ_ENABLE_INTERRUPTS();
        }
    }
#د_که_پای /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

uint32_t ul_سېټ_مداخله_ماسک_From_ISR( فراغ )
{
    __asm متطاير (
        " mrs r0, PRIMASK    \n"
        " cpsid i            \n"
        " bx lr                "
        ::: "memory"
        );
}
/*-----------------------------------------------------------*/

فراغ v_Clear_مداخله_ماسک_From_ISR( __attribute__( ( ناکارول_شوی ) ) uint32_t ul_ماسک )
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

    configASSERT( xCoreID != ( صحيح ) پورټ_GET_CORE_ID() );

    #إذا config_شمېره_د_CORES != 1

        /* Non blocking, will cause interrupt on other core if the queue isn't already full,
         * in which case an IRQ must be pending */
        sio_hw->fifo_wr = 0;
    #د_که_پای
}

/*-----------------------------------------------------------*/

فراغ x_پورټ_Pend_SVHandler( فراغ )
{
    /* This is a naked function. */
    #إذا ( config_شمېره_د_CORES == 1 )
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
            #إذا پورټ_USE_DIVIDER_SAVE_RESTORE
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
            #د_که_پای /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #إذا پورټ_USE_DIVIDER_SAVE_RESTORE
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
            #د_که_پای /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #إذا پورټ_USE_DIVIDER_SAVE_RESTORE

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
            #د_که_پای /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #إذا پورټ_USE_DIVIDER_SAVE_RESTORE
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
            #د_که_پای /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                 \n"     /* Pop low registers.  */
            "                                      \n"
            "   bx r3                              \n"
            "                                      \n"
            "   .align 4                           \n"
            "ulAsmLocals2:                         \n"
            "   .word 0xD0000000                   \n" /* SIO */
            "   .word pxCurrentTCBs                \n"
        );
    #د_که_پای /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

فراغ x_پورټ_Sys_Tick_Handler( فراغ )
{
    uint32_t ul_پخوانی_ماسک;

    ul_پخوانی_ماسک = taskENTER_CRITICAL_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_منزل_SCHEDULER();
            /* Pend a context switch. */
            پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PENDSVSET_بټ;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    taskEXIT_CRITICAL_FROM_ISR( ul_پخوانی_ماسک );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) فراغ v_پورټ_تیاری_Timer_مداخله( فراغ )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #إذا ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( clock_get_hz( clk_sys ) / config_TICK_شرح_HZ );
        x_اعظمي_Possible_Suppressed_Ticks = پورټ_MAX_24_بټ_شمېره / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورټ_MISSED_COUNTS_ضریب;
    }
    #د_که_پای /* configUSE_TICKLESS_IDLE */

    /* Stop and reset the SysTick. */
    پورټ_NVIC_SYSTICK_CTRL_REG = 0UL;
    پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورټ_NVIC_SYSTICK_بارول_REG = ( clock_get_hz( clk_sys ) / config_TICK_شرح_HZ ) - 1UL;
    پورټ_NVIC_SYSTICK_CTRL_REG = پورټ_NVIC_SYSTICK_CLK_بټ | پورټ_NVIC_SYSTICK_INT_بټ | پورټ_NVIC_SYSTICK_ENABLE_بټ;
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) فراغ v_پورټ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وخت )
    {
        uint32_t ul_Reload_ارزښت, ulCompleteTickPeriods, ulCompletedSysTickDecrements;
        TickType_t x_Modifiable_Idle_وخت;

        /* Make sure the SysTick reload value does not overflow the counter. */
        إذا( x_Expected_Idle_وخت > x_اعظمي_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_وخت = x_اعظمي_Possible_Suppressed_Ticks;
        }

        /* Stop the SysTick momentarily.  The time the SysTick is stopped for
         * is accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        پورټ_NVIC_SYSTICK_CTRL_REG &= ~پورټ_NVIC_SYSTICK_ENABLE_بټ;

        /* Calculate the reload value required to wait xExpectedIdleTime
         * tick periods.  -1 is used because this code will execute part way
         * through one of the tick periods. */
        ul_Reload_ارزښت = پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG + ( ulTimerCountsForOneTick * ( x_Expected_Idle_وخت - 1UL ) );

        إذا( ul_Reload_ارزښت > ulStoppedTimerCompensation )
        {
            ul_Reload_ارزښت -= ulStoppedTimerCompensation;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm متطاير ( "cpsid i" ::: "memory" );
        __asm متطاير ( "dsb" );
        __asm متطاير ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_ډېرپېښ_حالت() == eAbortSleep )
        {
            /* Restart from whatever is left in the count register to complete
             * this tick period. */
            پورټ_NVIC_SYSTICK_بارول_REG = پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG;

            /* Restart SysTick. */
            پورټ_NVIC_SYSTICK_CTRL_REG |= پورټ_NVIC_SYSTICK_ENABLE_بټ;

            /* Reset the reload register to the value required for normal tick
             * periods. */
            پورټ_NVIC_SYSTICK_بارول_REG = ulTimerCountsForOneTick - 1UL;

            /* Re-enable interrupts - see comments above the cpsid instruction()
             * above. */
            __asm متطاير ( "cpsie i" ::: "memory" );
        }
        وإلا
        {
            /* Set the new reload value. */
            پورټ_NVIC_SYSTICK_بارول_REG = ul_Reload_ارزښت;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG = 0UL;

            /* Restart SysTick. */
            پورټ_NVIC_SYSTICK_CTRL_REG |= پورټ_NVIC_SYSTICK_ENABLE_بټ;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_وخت = x_Expected_Idle_وخت;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_وخت );

            إذا( x_Modifiable_Idle_وخت > 0 )
            {
                __asm متطاير ( "dsb" ::: "memory" );
                __asm متطاير ( "wfi" );
                __asm متطاير ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_وخت );

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
            پورټ_NVIC_SYSTICK_CTRL_REG = ( پورټ_NVIC_SYSTICK_CLK_بټ | پورټ_NVIC_SYSTICK_INT_بټ );

            /* Determine if the SysTick clock has already counted to zero and
             * been set back to the current reload value (the reload back being
             * correct for the entire expected idle time) or if the SysTick is yet
             * to count to zero (in which case an interrupt other than the SysTick
             * must have brought the system out of sleep mode). */
            إذا( ( پورټ_NVIC_SYSTICK_CTRL_REG & پورټ_NVIC_SYSTICK_شمېر_FLAG_بټ ) != 0 )
            {
                uint32_t ul_Calculated_بارول_ارزښت;

                /* The tick interrupt is already pending, and the SysTick count
                 * reloaded with ulReloadValue.  Reset the
                 * portNVIC_SYSTICK_LOAD_REG with whatever remains of this tick
                 * period. */
                ul_Calculated_بارول_ارزښت = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_ارزښت - پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long. */
                إذا( ( ul_Calculated_بارول_ارزښت < ulStoppedTimerCompensation ) || ( ul_Calculated_بارول_ارزښت > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_بارول_ارزښت = ( ulTimerCountsForOneTick - 1UL );
                }

                پورټ_NVIC_SYSTICK_بارول_REG = ul_Calculated_بارول_ارزښت;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_وخت - 1UL;
            }
            وإلا
            {
                /* Something other than the tick interrupt ended the sleep.
                 * Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_وخت * ulTimerCountsForOneTick ) - پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورټ_NVIC_SYSTICK_بارول_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG
             * again, then set portNVIC_SYSTICK_LOAD_REG back to its standard
             * value. */
            پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG = 0UL;
            پورټ_NVIC_SYSTICK_CTRL_REG |= پورټ_NVIC_SYSTICK_ENABLE_بټ;
            v_Task_ګام_Tick( ulCompleteTickPeriods );
            پورټ_NVIC_SYSTICK_بارول_REG = ulTimerCountsForOneTick - 1UL;

            /* Exit with interrupts enabled. */
            __asm متطاير ( "cpsie i" ::: "memory" );
        }
    }

#د_که_پای /* configUSE_TICKLESS_IDLE */

#إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( config_SUPPORT_PICO_وخت_INTEROP == 1 )
    ساكن TickType_t prv_Get_Ticks_منزل_Wait_Before( absolute_وخت_t t )
    {
        int64_t xDelay = absolute_وخت_diff_us( get_absolute_وخت(), t );
        ثابت uint32_t ulTickPeriod = 1000000 / config_TICK_شرح_HZ;

        xDelay -= ulTickPeriod;

        إذا( xDelay >= ulTickPeriod )
        {
            أرجع xDelay / ulTickPeriod;
        }

        أرجع 0;
    }
#د_که_پای /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( configSUPPORT_PICO_TIME_INTEROP == 1 ) */

#إذا ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    uint32_t ul_پورټ_قلف_Get_Current_Owner_Id()
    {
        إذا( پورټ_IS_FREE_RTOS_CORE() )
        {
            uint32_t exception = __get_current_exception();

            إذا( !exception )
            {
                أرجع ( uintptr_t ) xTaskGetCurrentTaskHandle();
            }

            /* Note: since ROM as at 0x00000000, these can't be confused with
             * valid task handles (pointers) in RAM */
            /* We make all exception handler/core combinations distinct owners */
            أرجع get_core_عدد() + exception * 2;
        }

        /* Note: since ROM as at 0x00000000, this can't be confused with
         * valid task handles (pointers) in RAM */
        أرجع get_core_عدد();
    }

    ساكن مضمن Event_بټونه_t prv_Get_Event_ډله_بټ( spin_قلف_t * spin_قلف )
    {
        uint32_t ul_بټ;

        #إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
            ul_بټ = 1u << ( spin_قلف_get_عدد( spin_قلف ) & 0x7u );
        #وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
            /* Avoid potential use of SIO divider for % here out of abundance of caution */
            ul_بټ = spin_قلف_get_عدد( spin_قلف );
            إذا (ul_بټ >= 24) ul_بټ -= 24;
            ul_بټ = 1u << ul_بټ;
        #د_که_پای /* configTICK_TYPE_WIDTH_IN_BITS */
        أرجع ( Event_بټونه_t ) ul_بټ;
    }

    ساكن مضمن Event_بټونه_t prv_Get_All_Event_ډله_بټونه()
    {
        #إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
            أرجع ( Event_بټونه_t ) 0xffu;
        #وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
            أرجع ( Event_بټونه_t ) 0xffffffu;
        #د_که_پای /* configTICK_TYPE_WIDTH_IN_BITS */
    }

    فراغ v_پورټ_قلف_دننی_Spin_Unlock_With_Wait( بنية قلف_core * px_قلف,
                                              uint32_t ulSave )
    {
        configASSERT( !پورټ_CHECK_IF_دننه_ISR() );
        configASSERT( px_قلف->spin_قلف_2 );

        إذا( !پورټ_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_قلف->spin_قلف_2, ulSave );
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
            spin_unlock( px_قلف->spin_قلف_2, ulSave);
            x_Event_ډله_Wait_بټونه( x_Event_ډله, prv_Get_Event_ډله_بټ( px_قلف->spin_قلف_2 ),
                                 pdTRUE, pdFALSE, پورټ_MAX_DELAY );
        }
    }

    فراغ v_پورټ_قلف_دننی_Spin_Unlock_With_Notify( بنية قلف_core * px_قلف,
                                                uint32_t ulSave )
    {
        Event_بټونه_t ux_بټونه = prv_Get_Event_ډله_بټ( px_قلف->spin_قلف_2 );

        إذا( پورټ_IS_FREE_RTOS_CORE() )
        {
            #إذا LIB_PICO_MULTICORE
                /* signal an event in case a regular core is waiting */
                __sev();
            #د_که_پای
            spin_unlock( px_قلف->spin_قلف_2, ulSave );

            إذا( !پورټ_CHECK_IF_دننه_ISR() )
            {
                x_Event_ډله_سېټ_بټونه( x_Event_ډله, ux_بټونه );
            }
            وإلا
            {
                بنسټ_Type_t x_Higher_لومړیتوب_Task_Woken = pdFALSE;
                x_Event_ډله_سېټ_بټونه_From_ISR( x_Event_ډله, ux_بټونه, &x_Higher_لومړیتوب_Task_Woken );
                پورټ_YIELD_FROM_ISR( x_Higher_لومړیتوب_Task_Woken );
            }
        }
        وإلا
        {
            __sev();
            #إذا ( config_شمېره_د_CORES == 1 )
                إذا( px_Cross_Core_Spin_قلف != px_قلف->spin_قلف_2 )
                {
                    spin_قلف_unsafe_blocking( px_Cross_Core_Spin_قلف );
                    ux_Cross_Core_Event_بټونه |= ux_بټونه;
                    spin_unlock_unsafe( px_Cross_Core_Spin_قلف );
                }
                وإلا
                {
                    ux_Cross_Core_Event_بټونه |= ux_بټونه;
                }

                /* This causes fifo irq on the other (FreeRTOS) core which will do the set the event bits */
                sio_hw->fifo_wr = 0;
            #د_که_پای /* configNUMBER_OF_CORES == 1 */
            spin_unlock( px_قلف->spin_قلف_2, ulSave );
        }
    }

    bool x_پورټ_قلف_دننی_Spin_Unlock_With_غوره_Effort_Wait_Or_Timeout( بنية قلف_core * px_قلف,
                                                                 uint32_t ulSave,
                                                                 absolute_وخت_t uxUntil )
    {
        configASSERT( !پورټ_CHECK_IF_دننه_ISR() );
        configASSERT( px_قلف->spin_قلف_2 );

        /* note no need to check LIB_PICO_MULTICORE, as this is always returns true if that is not defined */
        إذا( !پورټ_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_قلف->spin_قلف_2, ulSave );
            أرجع غوره_effort_wfe_or_timeout( uxUntil );
        }
        وإلا
        {
            configASSERT( پورټ_IS_FREE_RTOS_CORE() );

            TickType_t ux_Ticks_منزل_Wait = prv_Get_Ticks_منزل_Wait_Before( uxUntil );

            إذا( ux_Ticks_منزل_Wait )
            {
                /* See comment in vPortLockInternalSpinUnlockWithWait for detail
                 * about possible race conditions */
                spin_unlock( px_قلف->spin_قلف_2, ulSave );
                x_Event_ډله_Wait_بټونه( x_Event_ډله,
                                     prv_Get_Event_ډله_بټ( px_قلف->spin_قلف_2 ), pdTRUE,
                                     pdFALSE, ux_Ticks_منزل_Wait );
            }
            وإلا
            {
                spin_unlock( px_قلف->spin_قلف_2, ulSave );
            }

            إذا( وخت_reached( uxUntil ) )
            {
                أرجع true;
            }
            وإلا
            {
                /* We do not want to hog the core */
                پورټ_YIELD();
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
            #إذا ( config_شمېره_د_CORES == 1 )
                px_Cross_Core_Spin_قلف = spin_قلف_instance( بل_striped_spin_قلف_عدد() );
            #د_که_پای /* configNUMBER_OF_CORES == 1 */

            /* The event group is not used prior to scheduler init, but is initialized
             * here to since it logically belongs with the spin lock */
            #إذا ( config_SUPPORT_STATIC_ویش == 1 )
                x_Event_ډله = x_Event_ډله_Create_Static( &x_Static_Event_ډله );
            #وإلا

                /* Note that it is slightly dubious calling this here before the scheduler is initialized,
                 * however the only thing it touches is the allocator which then calls vPortEnterCritical
                 * and vPortExitCritical, and allocating here saves us checking the one time initialized variable in
                 * some rather critical code paths */
                x_Event_ډله = x_Event_ډله_Create();
            #د_که_پای /* configSUPPORT_STATIC_ALLOCATION */
        }
    #د_که_پای /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */
#د_که_پای /* configSUPPORT_PICO_SYNC_INTEROP */

#إذا ( config_SUPPORT_PICO_وخت_INTEROP == 1 )
    فراغ x_پورټ_Sync_دننی_Yield_Until_Before( absolute_وخت_t t )
    {
        TickType_t ux_Ticks_منزل_Wait = prv_Get_Ticks_منزل_Wait_Before( t );

        إذا( ux_Ticks_منزل_Wait )
        {
            vTaskDelay( ux_Ticks_منزل_Wait );
        }
    }
#د_که_پای /* configSUPPORT_PICO_TIME_INTEROP */
