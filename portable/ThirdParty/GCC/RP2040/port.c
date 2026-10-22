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

#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "rp2040_config.h"
#شامل "hardware/clocks.h"
#شامل "hardware/exception.h"

/*
 * LIB_PICO_MULTICORE == 1, if we are linked with pico_multicore (note that
 * the non SMP FreeRTOS_Kernel is not linked with pico_multicore itself). We
 * use this flag to determine if we need multi-core functionality.
 */
#اگر ( LIB_PICO_MULTICORE == 1 )
    #شامل "pico/multicore.h"
#اگر_ختم /* LIB_PICO_MULTICORE */

/* Constants required to manipulate the NVIC. */
#تعریف_کرو پورٹ_NVIC_SYSTICK_CTRL_REG             ( *( ( متلون uint32_t * ) 0xe000e010 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_بھرو_REG             ( *( ( متلون uint32_t * ) 0xe000e014 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG    ( *( ( متلون uint32_t * ) 0xe000e018 ) )
#تعریف_کرو پورٹ_NVIC_INT_CTRL_REG                 ( *( ( متلون uint32_t * ) 0xe000ed04 ) )
#تعریف_کرو پورٹ_NVIC_SHPR3_REG                    ( *( ( متلون uint32_t * ) 0xe000ed20 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ              ( 1UL << 2UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ              ( 1UL << 1UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ           ( 1UL << 0UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_گنتی_FLAG_ثنائی_ہندسہ       ( 1UL << 16UL )
#تعریف_کرو پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ                ( 1UL << 28UL )
#تعریف_کرو پورٹ_MIN_مداخلت_ترجیح            ( 255UL )
#تعریف_کرو پورٹ_NVIC_PENDSV_PRI                   ( پورٹ_MIN_مداخلت_ترجیح << 16UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_PRI                  ( پورٹ_MIN_مداخلت_ترجیح << 24UL )

/* Constants required to set up the initial stack. */
#تعریف_کرو پورٹ_INITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#تعریف_کرو پورٹ_MAX_24_ثنائی_ہندسہ_نمبر                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#اگر_غیر_تعریف_شدہ پورٹ_MISSED_COUNTS_ضربی_عدد
    #تعریف_کرو پورٹ_MISSED_COUNTS_ضربی_عدد    ( 45UL )
#اگر_ختم

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#اگر_تعریف_شدہ config_TASK_RETURN_پتہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    config_TASK_RETURN_پتہ
#ورنہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    prvTaskExitError
#اگر_ختم

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
خالی v_پورٹ_تیاری_Timer_مداخلت( خالی );

/*
 * Exception handlers.
 */
خالی x_پورٹ_Pend_SVHandler( خالی ) __attribute__( ( naked ) );
خالی x_پورٹ_Sys_Tick_Handler( خالی );
خالی v_پورٹ_SVCHandler( خالی );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ساکن خالی v_پورٹ_آغاز_پہلا_Task( خالی ) __attribute__( ( naked ) );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساکن خالی prvTaskExitError( خالی );

/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. This is initialized to 0 to allow vPortEnter/ExitCritical
 * to be called before the scheduler is started */
#اگر ( config_نمبر_کا_CORES == 1 )
    ساکن UBaseType_t uxCriticalNesting;
#ورنہ /* #if ( configNUMBER_OF_CORES == 1 ) */
UBaseType_t uxCriticalNestings[ config_نمبر_کا_CORES ] = { 0 };
#اگر_ختم /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

#اگر ( configSUPPORT_PICO_SYNC_INTEROP == 1 || config_نمبر_کا_CORES > 1 )
    #شامل "hardware/irq.h"
#اگر_ختم /* ( configSUPPORT_PICO_SYNC_INTEROP == 1 || configNUMBER_OF_CORES > 1 ) */
#اگر ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    #شامل "pico/lock_core.h"
    #شامل "event_groups.h"
    #اگر config_SUPPORT_STATIC_تخصیص
        ساکن Static_Event_گروہ_t x_Static_Event_گروہ;
        #تعریف_کرو p_Event_گروہ    ( &x_Static_Event_گروہ )
    #اگر_ختم /* configSUPPORT_STATIC_ALLOCATION */
    ساکن Event_گروہ_Handle_t x_Event_گروہ;
    #اگر ( config_نمبر_کا_CORES == 1 )
        ساکن Event_بٹ_t ux_Cross_Core_Event_بٹ;
        ساکن spin_تالا_t * px_Cross_Core_Spin_تالا; /* protects uxCrossCoreEventBits */
    #اگر_ختم
#اگر_ختم /* configSUPPORT_PICO_SYNC_INTEROP */

/*
 * The number of SysTick increments that make up one tick period.
 */
#اگر ( configUSE_TICKLESS_IDLE == 1 )
    ساکن uint32_t ulTimerCountsForOneTick = 0;
#اگر_ختم /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#اگر ( configUSE_TICKLESS_IDLE == 1 )
    ساکن uint32_t x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks = 0;
#اگر_ختم /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#اگر ( configUSE_TICKLESS_IDLE == 1 )
    ساکن uint32_t ulStoppedTimerCompensation = 0;
#اگر_ختم /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#تعریف_کرو INVALID_PRIMARY_CORE_عدد    0xffu
/* The primary core number (the own which has the SysTick handler) */
ساکن uint8_t uc_Primary_Core_عدد = INVALID_PRIMARY_CORE_عدد;

/* Note: portIS_FREE_RTOS_CORE() also returns false until the scheduler is started */
#اگر ( config_نمبر_کا_CORES != 1 )
    #تعریف_کرو پورٹ_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_عدد != INVALID_PRIMARY_CORE_عدد )
#ورنہ
    #تعریف_کرو پورٹ_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_عدد == get_core_عدد() )
#اگر_ختم

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_چوٹی_کا_ڈھیر--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_XPSR;                        /* xPSR */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;                  /* PC */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_TASK_RETURN_پتہ; /* LR */
    px_چوٹی_کا_ڈھیر -= 5;                                       /* R12, R3, R2 and R1. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;            /* R0 */
    px_چوٹی_کا_ڈھیر -= 8;                                       /* R11..R4. */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

ساکن خالی prvTaskExitError( خالی )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ). */
    panic_unsupported();
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_SVCHandler( خالی )
{
    /* This function is no longer used, but retained for backward
     * compatibility. */
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_آغاز_پہلا_Task( خالی )
{
    #اگر ( config_نمبر_کا_CORES == 1 )
        __asm متلون (
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
    #ورنہ /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm متلون (
            "    .syntax unified                    \n"
            #اگر config_RESET_ڈھیر_اشارہ_گر
                "   ldr  r0, =0xE000ED08            \n" /* Use the NVIC offset register to locate the stack. */
                "   ldr r0, [r0]                    \n"
                "   ldr r0, [r0]                    \n"
                "   msr msp, r0                     \n" /* Set the msp back to the start of the stack. */
            #اگر_ختم /* configRESET_STACK_POINTER */
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
    #اگر_ختم /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#اگر ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    ساکن خالی prvFIFOInterruptHandler()
    {
        /* We must remove the contents (which we don't care about)
         * to clear the IRQ */
        multicore_fifo_drain();

        /* And explicitly clear any other IRQ flags. */
        multicore_fifo_clear_irq();

        #اگر ( config_نمبر_کا_CORES != 1 )
            پورٹ_YIELD_FROM_ISR( pdTRUE );
        #وگرنہ_اگر ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
            بنیاد_Type_t x_Higher_ترجیح_Task_Woken = pdFALSE;
            uint32_t ulSave = spin_تالا_blocking( px_Cross_Core_Spin_تالا );
            Event_بٹ_t ul_بٹ = ux_Cross_Core_Event_بٹ;
            ux_Cross_Core_Event_بٹ &= ~ul_بٹ;
            spin_unlock( px_Cross_Core_Spin_تالا, ulSave );
            x_Event_گروہ_سیٹ_بٹ_From_ISR( x_Event_گروہ, ul_بٹ, &x_Higher_ترجیح_Task_Woken );
            پورٹ_YIELD_FROM_ISR( x_Higher_ترجیح_Task_Woken );
        #اگر_ختم /* configNUMBER_OF_CORES != 1 */
    }
#اگر_ختم /* if ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */

#اگر ( config_نمبر_کا_CORES > 1 )

/*
 * See header file for description.
 */
    ساکن بنیاد_Type_t x_پورٹ_آغاز_Scheduler_On_Core()
    {
        اگر( uc_Primary_Core_عدد == get_core_عدد() )
        {
            /* Start the timer that generates the tick ISR.  Interrupts are disabled
             * here already. */
            v_پورٹ_تیاری_Timer_مداخلت();

            /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
            پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_SYSTICK_PRI;
            #اگر ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
                exception_سیٹ_exclusive_handler( SYSTICK_EXCEPTION, x_پورٹ_Sys_Tick_Handler );
            #اگر_ختم
        }

        پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_PENDSV_PRI;

        #اگر ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_سیٹ_exclusive_handler( PENDSV_EXCEPTION, x_پورٹ_Pend_SVHandler );
            exception_سیٹ_exclusive_handler( SVCALL_EXCEPTION, v_پورٹ_SVCHandler );
        #اگر_ختم

        /* Install FIFO handler to receive interrupt from other core */
        multicore_fifo_clear_irq();
        multicore_fifo_drain();
        uint32_t ulIRQNum = SIO_IRQ_PROC0 + get_core_عدد();
        irq_سیٹ_ترجیح( ulIRQNum, پورٹ_MIN_مداخلت_ترجیح );
        irq_سیٹ_exclusive_handler( ulIRQNum, prvFIFOInterruptHandler );
        irq_سیٹ_enabled( ulIRQNum, 1 );

        /* Start the first task. */
        v_پورٹ_آغاز_پہلا_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext( پورٹ_GET_CORE_ID() );
        prvTaskExitError();

        /* Should not get here. */
        واپس 0;
    }

    ساکن خالی prv_Disable_Interrupts_And_پورٹ_آغاز_Scheduler_On_Core( خالی )
    {
        پورٹ_DISABLE_INTERRUPTS();
        x_پورٹ_آغاز_Scheduler_On_Core();
    }

/*
 * See header file for description.
 */
    بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
    {
        configASSERT( uc_Primary_Core_عدد == INVALID_PRIMARY_CORE_عدد );

        /* No one else should use these! */
        spin_تالا_claim( configSMP_SPINLOCK_0 );
        spin_تالا_claim( configSMP_SPINLOCK_1 );

        uc_Primary_Core_عدد = configTICK_CORE;
        configASSERT( get_core_عدد() == 0 ); /* we must be started on core 0 */
        multicore_reset_core1();
        multicore_launch_core1( prv_Disable_Interrupts_And_پورٹ_آغاز_Scheduler_On_Core );

        x_پورٹ_آغاز_Scheduler_On_Core();

        /* Should not get here! */
        واپس 0;
    }

#ورنہ /* if ( configNUMBER_OF_CORES > 1 ) */

/*
 * See header file for description.
 */
    بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
    {
        /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
        پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_PENDSV_PRI;
        پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_SYSTICK_PRI;

        #اگر ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_سیٹ_exclusive_handler( PENDSV_EXCEPTION, x_پورٹ_Pend_SVHandler );
            exception_سیٹ_exclusive_handler( SYSTICK_EXCEPTION, x_پورٹ_Sys_Tick_Handler );
            exception_سیٹ_exclusive_handler( SVCALL_EXCEPTION, v_پورٹ_SVCHandler );
        #اگر_ختم

        /* Start the timer that generates the tick ISR.  Interrupts are disabled
         * here already. */
        v_پورٹ_تیاری_Timer_مداخلت();

        /* Initialise the critical nesting count ready for the first task. */
        uxCriticalNesting = 0;

        uc_Primary_Core_عدد = get_core_عدد();
        #اگر ( LIB_PICO_MULTICORE == 1 )
            #اگر ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
                multicore_fifo_clear_irq();
                multicore_fifo_drain();
                uint32_t irq_عدد = SIO_IRQ_PROC0 + get_core_عدد();
                irq_سیٹ_ترجیح( irq_عدد, پورٹ_MIN_مداخلت_ترجیح );
                irq_سیٹ_exclusive_handler( irq_عدد, prvFIFOInterruptHandler );
                irq_سیٹ_enabled( irq_عدد, 1 );
            #اگر_ختم
        #اگر_ختم

        /* Start the first task. */
        v_پورٹ_آغاز_پہلا_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext();
        prvTaskExitError();

        /* Should not get here! */
        واپس 0;
    }
#اگر_ختم /* if ( configNUMBER_OF_CORES > 1 ) */

/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( پورٹ_GET_CORE_ID() == 1000UL );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Yield( خالی )
{
    /* Set a PendSV to request a context switch. */
    پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __asm متلون ( "dsb" ::: "memory" );
    __asm متلون ( "isb" );
}

/*-----------------------------------------------------------*/

#اگر ( config_نمبر_کا_CORES == 1 )
    خالی v_پورٹ_Enter_Critical( خالی )
    {
        پورٹ_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
        __asm متلون ( "dsb" ::: "memory" );
        __asm متلون ( "isb" );
    }
#اگر_ختم /* #if ( configNUMBER_OF_CORES == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_نمبر_کا_CORES == 1 )
    خالی v_پورٹ_Exit_Critical( خالی )
    {
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        اگر( uxCriticalNesting == 0 )
        {
            پورٹ_ENABLE_INTERRUPTS();
        }
    }
#اگر_ختم /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

uint32_t ul_سیٹ_مداخلت_نقاب_From_ISR( خالی )
{
    __asm متلون (
        " mrs r0, PRIMASK    \n"
        " cpsid i            \n"
        " bx lr                "
        ::: "memory"
        );
}
/*-----------------------------------------------------------*/

خالی v_Clear_مداخلت_نقاب_From_ISR( __attribute__( ( غیر_مستعمل ) ) uint32_t ul_نقاب )
{
    __asm متلون (
        " msr PRIMASK, r0    \n"
        " bx lr                "
        ::: "memory"
        );
}

/*-----------------------------------------------------------*/

خالی vYieldCore( صحیح xCoreID )
{
    /* Remove warning if configASSERT is not defined.
     * xCoreID is not used in this function due to this is a dual-core system. The yielding core must be different from the current core. */
    ( خالی ) xCoreID;

    configASSERT( xCoreID != ( صحیح ) پورٹ_GET_CORE_ID() );

    #اگر config_نمبر_کا_CORES != 1

        /* Non blocking, will cause interrupt on other core if the queue isn't already full,
         * in which case an IRQ must be pending */
        sio_hw->fifo_wr = 0;
    #اگر_ختم
}

/*-----------------------------------------------------------*/

خالی x_پورٹ_Pend_SVHandler( خالی )
{
    /* This is a naked function. */
    #اگر ( config_نمبر_کا_CORES == 1 )
        __asm متلون
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
            #اگر پورٹ_USE_DIVIDER_SAVE_RESTORE
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
            #اگر_ختم /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #اگر پورٹ_USE_DIVIDER_SAVE_RESTORE
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
            #ورنہ /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                    \n" /* Go back for the low registers that are not automatically restored. */
            #اگر_ختم /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                  \n"     /* Pop low registers.  */
            "                                       \n"
            "   bx r3                               \n"
            "   .align 4                            \n"
            "pxCurrentTCBConst2: .word pxCurrentTCB \n"
        );
    #ورنہ /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm متلون
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
            #اگر پورٹ_USE_DIVIDER_SAVE_RESTORE

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
            #اگر_ختم /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #اگر پورٹ_USE_DIVIDER_SAVE_RESTORE
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
            #ورنہ /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                   \n" /* Go back for the low registers that are not automatically restored. */
            #اگر_ختم /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                 \n"     /* Pop low registers.  */
            "                                      \n"
            "   bx r3                              \n"
            "                                      \n"
            "   .align 4                           \n"
            "ulAsmLocals2:                         \n"
            "   .word 0xD0000000                   \n" /* SIO */
            "   .word pxCurrentTCBs                \n"
        );
    #اگر_ختم /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

خالی x_پورٹ_Sys_Tick_Handler( خالی )
{
    uint32_t ul_پچھلا_نقاب;

    ul_پچھلا_نقاب = taskENTER_CRITICAL_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        اگر( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_مقصد_SCHEDULER();
            /* Pend a context switch. */
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ;
        }
        ورنہ
        {
            traceISR_EXIT();
        }
    }
    taskEXIT_CRITICAL_FROM_ISR( ul_پچھلا_نقاب );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) خالی v_پورٹ_تیاری_Timer_مداخلت( خالی )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #اگر ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( clock_get_hz( clk_sys ) / config_TICK_شرح_HZ );
        x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks = پورٹ_MAX_24_ثنائی_ہندسہ_نمبر / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورٹ_MISSED_COUNTS_ضربی_عدد;
    }
    #اگر_ختم /* configUSE_TICKLESS_IDLE */

    /* Stop and reset the SysTick. */
    پورٹ_NVIC_SYSTICK_CTRL_REG = 0UL;
    پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورٹ_NVIC_SYSTICK_بھرو_REG = ( clock_get_hz( clk_sys ) / config_TICK_شرح_HZ ) - 1UL;
    پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;
}
/*-----------------------------------------------------------*/

#اگر ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) خالی v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت )
    {
        uint32_t ul_Reload_قدر, ulCompleteTickPeriods, ulCompletedSysTickDecrements;
        TickType_t x_Modifiable_Idle_وقت;

        /* Make sure the SysTick reload value does not overflow the counter. */
        اگر( x_Expected_Idle_وقت > x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_وقت = x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks;
        }

        /* Stop the SysTick momentarily.  The time the SysTick is stopped for
         * is accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        پورٹ_NVIC_SYSTICK_CTRL_REG &= ~پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;

        /* Calculate the reload value required to wait xExpectedIdleTime
         * tick periods.  -1 is used because this code will execute part way
         * through one of the tick periods. */
        ul_Reload_قدر = پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG + ( ulTimerCountsForOneTick * ( x_Expected_Idle_وقت - 1UL ) );

        اگر( ul_Reload_قدر > ulStoppedTimerCompensation )
        {
            ul_Reload_قدر -= ulStoppedTimerCompensation;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm متلون ( "cpsid i" ::: "memory" );
        __asm متلون ( "dsb" );
        __asm متلون ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        اگر( e_Task_Confirm_Sleep_منوال_حالت() == eAbortSleep )
        {
            /* Restart from whatever is left in the count register to complete
             * this tick period. */
            پورٹ_NVIC_SYSTICK_بھرو_REG = پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG;

            /* Restart SysTick. */
            پورٹ_NVIC_SYSTICK_CTRL_REG |= پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;

            /* Reset the reload register to the value required for normal tick
             * periods. */
            پورٹ_NVIC_SYSTICK_بھرو_REG = ulTimerCountsForOneTick - 1UL;

            /* Re-enable interrupts - see comments above the cpsid instruction()
             * above. */
            __asm متلون ( "cpsie i" ::: "memory" );
        }
        ورنہ
        {
            /* Set the new reload value. */
            پورٹ_NVIC_SYSTICK_بھرو_REG = ul_Reload_قدر;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

            /* Restart SysTick. */
            پورٹ_NVIC_SYSTICK_CTRL_REG |= پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_وقت = x_Expected_Idle_وقت;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_وقت );

            اگر( x_Modifiable_Idle_وقت > 0 )
            {
                __asm متلون ( "dsb" ::: "memory" );
                __asm متلون ( "wfi" );
                __asm متلون ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_وقت );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  see comments above
             * __disable_interrupt() call above. */
            __asm متلون ( "cpsie i" ::: "memory" );
            __asm متلون ( "dsb" );
            __asm متلون ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm متلون ( "cpsid i" ::: "memory" );
            __asm متلون ( "dsb" );
            __asm متلون ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            پورٹ_NVIC_SYSTICK_CTRL_REG = ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ );

            /* Determine if the SysTick clock has already counted to zero and
             * been set back to the current reload value (the reload back being
             * correct for the entire expected idle time) or if the SysTick is yet
             * to count to zero (in which case an interrupt other than the SysTick
             * must have brought the system out of sleep mode). */
            اگر( ( پورٹ_NVIC_SYSTICK_CTRL_REG & پورٹ_NVIC_SYSTICK_گنتی_FLAG_ثنائی_ہندسہ ) != 0 )
            {
                uint32_t ul_Calculated_بھرو_قدر;

                /* The tick interrupt is already pending, and the SysTick count
                 * reloaded with ulReloadValue.  Reset the
                 * portNVIC_SYSTICK_LOAD_REG with whatever remains of this tick
                 * period. */
                ul_Calculated_بھرو_قدر = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_قدر - پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long. */
                اگر( ( ul_Calculated_بھرو_قدر < ulStoppedTimerCompensation ) || ( ul_Calculated_بھرو_قدر > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_بھرو_قدر = ( ulTimerCountsForOneTick - 1UL );
                }

                پورٹ_NVIC_SYSTICK_بھرو_REG = ul_Calculated_بھرو_قدر;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_وقت - 1UL;
            }
            ورنہ
            {
                /* Something other than the tick interrupt ended the sleep.
                 * Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_وقت * ulTimerCountsForOneTick ) - پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورٹ_NVIC_SYSTICK_بھرو_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG
             * again, then set portNVIC_SYSTICK_LOAD_REG back to its standard
             * value. */
            پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;
            پورٹ_NVIC_SYSTICK_CTRL_REG |= پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;
            v_Task_قدم_Tick( ulCompleteTickPeriods );
            پورٹ_NVIC_SYSTICK_بھرو_REG = ulTimerCountsForOneTick - 1UL;

            /* Exit with interrupts enabled. */
            __asm متلون ( "cpsie i" ::: "memory" );
        }
    }

#اگر_ختم /* configUSE_TICKLESS_IDLE */

#اگر ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( config_SUPPORT_PICO_وقت_INTEROP == 1 )
    ساکن TickType_t prv_Get_Ticks_مقصد_Wait_Before( absolute_وقت_t t )
    {
        int64_t xDelay = absolute_وقت_diff_us( get_absolute_وقت(), t );
        ثابت uint32_t ulTickPeriod = 1000000 / config_TICK_شرح_HZ;

        xDelay -= ulTickPeriod;

        اگر( xDelay >= ulTickPeriod )
        {
            واپس xDelay / ulTickPeriod;
        }

        واپس 0;
    }
#اگر_ختم /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( configSUPPORT_PICO_TIME_INTEROP == 1 ) */

#اگر ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    uint32_t ul_پورٹ_تالا_Get_Current_Owner_Id()
    {
        اگر( پورٹ_IS_FREE_RTOS_CORE() )
        {
            uint32_t exception = __get_current_exception();

            اگر( !exception )
            {
                واپس ( uintptr_t ) xTaskGetCurrentTaskHandle();
            }

            /* Note: since ROM as at 0x00000000, these can't be confused with
             * valid task handles (pointers) in RAM */
            /* We make all exception handler/core combinations distinct owners */
            واپس get_core_عدد() + exception * 2;
        }

        /* Note: since ROM as at 0x00000000, this can't be confused with
         * valid task handles (pointers) in RAM */
        واپس get_core_عدد();
    }

    ساکن اندرونی Event_بٹ_t prv_Get_Event_گروہ_ثنائی_ہندسہ( spin_تالا_t * spin_تالا )
    {
        uint32_t ul_ثنائی_ہندسہ;

        #اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
            ul_ثنائی_ہندسہ = 1u << ( spin_تالا_get_عدد( spin_تالا ) & 0x7u );
        #وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
            /* Avoid potential use of SIO divider for % here out of abundance of caution */
            ul_ثنائی_ہندسہ = spin_تالا_get_عدد( spin_تالا );
            اگر (ul_ثنائی_ہندسہ >= 24) ul_ثنائی_ہندسہ -= 24;
            ul_ثنائی_ہندسہ = 1u << ul_ثنائی_ہندسہ;
        #اگر_ختم /* configTICK_TYPE_WIDTH_IN_BITS */
        واپس ( Event_بٹ_t ) ul_ثنائی_ہندسہ;
    }

    ساکن اندرونی Event_بٹ_t prv_Get_All_Event_گروہ_بٹ()
    {
        #اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
            واپس ( Event_بٹ_t ) 0xffu;
        #وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
            واپس ( Event_بٹ_t ) 0xffffffu;
        #اگر_ختم /* configTICK_TYPE_WIDTH_IN_BITS */
    }

    خالی v_پورٹ_تالا_اندرونی_Spin_Unlock_With_Wait( ساخت تالا_core * px_تالا,
                                              uint32_t ulSave )
    {
        configASSERT( !پورٹ_CHECK_IF_اندر_ISR() );
        configASSERT( px_تالا->spin_تالا_2 );

        اگر( !پورٹ_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_تالا->spin_تالا_2, ulSave );
            __wfe();
        }
        ورنہ
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
            spin_unlock( px_تالا->spin_تالا_2, ulSave);
            x_Event_گروہ_Wait_بٹ( x_Event_گروہ, prv_Get_Event_گروہ_ثنائی_ہندسہ( px_تالا->spin_تالا_2 ),
                                 pdTRUE, pdFALSE, پورٹ_MAX_DELAY );
        }
    }

    خالی v_پورٹ_تالا_اندرونی_Spin_Unlock_With_Notify( ساخت تالا_core * px_تالا,
                                                uint32_t ulSave )
    {
        Event_بٹ_t ux_بٹ = prv_Get_Event_گروہ_ثنائی_ہندسہ( px_تالا->spin_تالا_2 );

        اگر( پورٹ_IS_FREE_RTOS_CORE() )
        {
            #اگر LIB_PICO_MULTICORE
                /* signal an event in case a regular core is waiting */
                __sev();
            #اگر_ختم
            spin_unlock( px_تالا->spin_تالا_2, ulSave );

            اگر( !پورٹ_CHECK_IF_اندر_ISR() )
            {
                x_Event_گروہ_سیٹ_بٹ( x_Event_گروہ, ux_بٹ );
            }
            ورنہ
            {
                بنیاد_Type_t x_Higher_ترجیح_Task_Woken = pdFALSE;
                x_Event_گروہ_سیٹ_بٹ_From_ISR( x_Event_گروہ, ux_بٹ, &x_Higher_ترجیح_Task_Woken );
                پورٹ_YIELD_FROM_ISR( x_Higher_ترجیح_Task_Woken );
            }
        }
        ورنہ
        {
            __sev();
            #اگر ( config_نمبر_کا_CORES == 1 )
                اگر( px_Cross_Core_Spin_تالا != px_تالا->spin_تالا_2 )
                {
                    spin_تالا_unsafe_blocking( px_Cross_Core_Spin_تالا );
                    ux_Cross_Core_Event_بٹ |= ux_بٹ;
                    spin_unlock_unsafe( px_Cross_Core_Spin_تالا );
                }
                ورنہ
                {
                    ux_Cross_Core_Event_بٹ |= ux_بٹ;
                }

                /* This causes fifo irq on the other (FreeRTOS) core which will do the set the event bits */
                sio_hw->fifo_wr = 0;
            #اگر_ختم /* configNUMBER_OF_CORES == 1 */
            spin_unlock( px_تالا->spin_تالا_2, ulSave );
        }
    }

    bool x_پورٹ_تالا_اندرونی_Spin_Unlock_With_بہترین_Effort_Wait_Or_Timeout( ساخت تالا_core * px_تالا,
                                                                 uint32_t ulSave,
                                                                 absolute_وقت_t uxUntil )
    {
        configASSERT( !پورٹ_CHECK_IF_اندر_ISR() );
        configASSERT( px_تالا->spin_تالا_2 );

        /* note no need to check LIB_PICO_MULTICORE, as this is always returns true if that is not defined */
        اگر( !پورٹ_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_تالا->spin_تالا_2, ulSave );
            واپس بہترین_effort_wfe_or_timeout( uxUntil );
        }
        ورنہ
        {
            configASSERT( پورٹ_IS_FREE_RTOS_CORE() );

            TickType_t ux_Ticks_مقصد_Wait = prv_Get_Ticks_مقصد_Wait_Before( uxUntil );

            اگر( ux_Ticks_مقصد_Wait )
            {
                /* See comment in vPortLockInternalSpinUnlockWithWait for detail
                 * about possible race conditions */
                spin_unlock( px_تالا->spin_تالا_2, ulSave );
                x_Event_گروہ_Wait_بٹ( x_Event_گروہ,
                                     prv_Get_Event_گروہ_ثنائی_ہندسہ( px_تالا->spin_تالا_2 ), pdTRUE,
                                     pdFALSE, ux_Ticks_مقصد_Wait );
            }
            ورنہ
            {
                spin_unlock( px_تالا->spin_تالا_2, ulSave );
            }

            اگر( وقت_reached( uxUntil ) )
            {
                واپس true;
            }
            ورنہ
            {
                /* We do not want to hog the core */
                پورٹ_YIELD();
                /* We aren't sure if we've reached the timeout yet; the caller will check */
                واپس false;
            }
        }
    }

    #اگر ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* runs before main */
        ساکن خالی __attribute__( ( constructor ) ) prvRuntimeInitializer( خالی )
        {
            /* This must be done even before the scheduler is started, as the spin lock
             * is used by the overrides of the SDK wait/notify primitives */
            #اگر ( config_نمبر_کا_CORES == 1 )
                px_Cross_Core_Spin_تالا = spin_تالا_instance( اگلا_striped_spin_تالا_عدد() );
            #اگر_ختم /* configNUMBER_OF_CORES == 1 */

            /* The event group is not used prior to scheduler init, but is initialized
             * here to since it logically belongs with the spin lock */
            #اگر ( config_SUPPORT_STATIC_تخصیص == 1 )
                x_Event_گروہ = x_Event_گروہ_Create_Static( &x_Static_Event_گروہ );
            #ورنہ

                /* Note that it is slightly dubious calling this here before the scheduler is initialized,
                 * however the only thing it touches is the allocator which then calls vPortEnterCritical
                 * and vPortExitCritical, and allocating here saves us checking the one time initialized variable in
                 * some rather critical code paths */
                x_Event_گروہ = x_Event_گروہ_Create();
            #اگر_ختم /* configSUPPORT_STATIC_ALLOCATION */
        }
    #اگر_ختم /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */
#اگر_ختم /* configSUPPORT_PICO_SYNC_INTEROP */

#اگر ( config_SUPPORT_PICO_وقت_INTEROP == 1 )
    خالی x_پورٹ_Sync_اندرونی_Yield_Until_Before( absolute_وقت_t t )
    {
        TickType_t ux_Ticks_مقصد_Wait = prv_Get_Ticks_مقصد_Wait_Before( t );

        اگر( ux_Ticks_مقصد_Wait )
        {
            vTaskDelay( ux_Ticks_مقصد_Wait );
        }
    }
#اگر_ختم /* configSUPPORT_PICO_TIME_INTEROP */
