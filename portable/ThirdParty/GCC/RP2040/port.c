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

#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "rp2040_config.h"
#अन्तर्भाव "hardware/clocks.h"
#अन्तर्भाव "hardware/exception.h"

/*
 * LIB_PICO_MULTICORE == 1, if we are linked with pico_multicore (note that
 * the non SMP FreeRTOS_Kernel is not linked with pico_multicore itself). We
 * use this flag to determine if we need multi-core functionality.
 */
#यदि ( LIB_PICO_MULTICORE == 1 )
    #अन्तर्भाव "pico/multicore.h"
#यदि_अन्तः /* LIB_PICO_MULTICORE */

/* Constants required to manipulate the NVIC. */
#परिभाषय पत्तनम्_NVIC_SYSTICK_CTRL_REG             ( *( ( चञ्चल uint32_t * ) 0xe000e010 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_आरोपय_REG             ( *( ( चञ्चल uint32_t * ) 0xe000e014 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG    ( *( ( चञ्चल uint32_t * ) 0xe000e018 ) )
#परिभाषय पत्तनम्_NVIC_INT_CTRL_REG                 ( *( ( चञ्चल uint32_t * ) 0xe000ed04 ) )
#परिभाषय पत्तनम्_NVIC_SHPR3_REG                    ( *( ( चञ्चल uint32_t * ) 0xe000ed20 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_CLK_BIT              ( 1UL << 2UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_INT_BIT              ( 1UL << 1UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_ENABLE_BIT           ( 1UL << 0UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_गणनम्_FLAG_BIT       ( 1UL << 16UL )
#परिभाषय पत्तनम्_NVIC_PENDSVSET_BIT                ( 1UL << 28UL )
#परिभाषय पत्तनम्_MIN_व्यवधानम्_प्राथमिकता            ( 255UL )
#परिभाषय पत्तनम्_NVIC_PENDSV_PRI                   ( पत्तनम्_MIN_व्यवधानम्_प्राथमिकता << 16UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_PRI                  ( पत्तनम्_MIN_व्यवधानम्_प्राथमिकता << 24UL )

/* Constants required to set up the initial stack. */
#परिभाषय पत्तनम्_INITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#परिभाषय पत्तनम्_MAX_24_BIT_सङ्ख्या                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#यदि_अपरिभाषितम् पत्तनम्_MISSED_COUNTS_गुणकः
    #परिभाषय पत्तनम्_MISSED_COUNTS_गुणकः    ( 45UL )
#यदि_अन्तः

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#यदि_परिभाषितम् config_TASK_RETURN_स्थानाङ्कः
    #परिभाषय पत्तनम्_TASK_RETURN_स्थानाङ्कः    config_TASK_RETURN_स्थानाङ्कः
#अन्यथा
    #परिभाषय पत्तनम्_TASK_RETURN_स्थानाङ्कः    prvTaskExitError
#यदि_अन्तः

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
शून्य v_पत्तनम्_सज्जता_Timer_व्यवधानम्( शून्य );

/*
 * Exception handlers.
 */
शून्य x_पत्तनम्_Pend_SVHandler( शून्य ) __attribute__( ( naked ) );
शून्य x_पत्तनम्_Sys_Tick_Handler( शून्य );
शून्य v_पत्तनम्_SVCHandler( शून्य );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
स्थिर शून्य v_पत्तनम्_Start_First_Task( शून्य ) __attribute__( ( naked ) );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

/*-----------------------------------------------------------*/

/* Each task maintains its own interrupt status in the critical nesting
 * variable. This is initialized to 0 to allow vPortEnter/ExitCritical
 * to be called before the scheduler is started */
#यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    स्थिर UBaseType_t uxCriticalNesting;
#अन्यथा /* #if ( configNUMBER_OF_CORES == 1 ) */
UBaseType_t uxCriticalNestings[ config_सङ्ख्या_सम्बन्धि_CORES ] = { 0 };
#यदि_अन्तः /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

#यदि ( configSUPPORT_PICO_SYNC_INTEROP == 1 || config_सङ्ख्या_सम्बन्धि_CORES > 1 )
    #अन्तर्भाव "hardware/irq.h"
#यदि_अन्तः /* ( configSUPPORT_PICO_SYNC_INTEROP == 1 || configNUMBER_OF_CORES > 1 ) */
#यदि ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    #अन्तर्भाव "pico/lock_core.h"
    #अन्तर्भाव "event_groups.h"
    #यदि config_SUPPORT_STATIC_आवण्टनम्
        स्थिर Static_Event_गणः_t x_Static_Event_गणः;
        #परिभाषय p_Event_गणः    ( &x_Static_Event_गणः )
    #यदि_अन्तः /* configSUPPORT_STATIC_ALLOCATION */
    स्थिर Event_गणः_Handle_t x_Event_गणः;
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
        स्थिर Event_द्वयङ्काः_t ux_Cross_Core_Event_द्वयङ्काः;
        स्थिर spin_तालकम्_t * px_Cross_Core_Spin_तालकम्; /* protects uxCrossCoreEventBits */
    #यदि_अन्तः
#यदि_अन्तः /* configSUPPORT_PICO_SYNC_INTEROP */

/*
 * The number of SysTick increments that make up one tick period.
 */
#यदि ( configUSE_TICKLESS_IDLE == 1 )
    स्थिर uint32_t ulTimerCountsForOneTick = 0;
#यदि_अन्तः /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#यदि ( configUSE_TICKLESS_IDLE == 1 )
    स्थिर uint32_t x_अधिकतमम्_Possible_Suppressed_Ticks = 0;
#यदि_अन्तः /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#यदि ( configUSE_TICKLESS_IDLE == 1 )
    स्थिर uint32_t ulStoppedTimerCompensation = 0;
#यदि_अन्तः /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#परिभाषय INVALID_PRIMARY_CORE_अङ्कः    0xffu
/* The primary core number (the own which has the SysTick handler) */
स्थिर uint8_t uc_Primary_Core_अङ्कः = INVALID_PRIMARY_CORE_अङ्कः;

/* Note: portIS_FREE_RTOS_CORE() also returns false until the scheduler is started */
#यदि ( config_सङ्ख्या_सम्बन्धि_CORES != 1 )
    #परिभाषय पत्तनम्_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_अङ्कः != INVALID_PRIMARY_CORE_अङ्कः )
#अन्यथा
    #परिभाषय पत्तनम्_IS_FREE_RTOS_CORE()    ( uc_Primary_Core_अङ्कः == get_core_अङ्कः() )
#यदि_अन्तः

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_शिखरम्_सम्बन्धि_राशिः--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_XPSR;                        /* xPSR */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;                  /* PC */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_TASK_RETURN_स्थानाङ्कः; /* LR */
    px_शिखरम्_सम्बन्धि_राशिः -= 5;                                       /* R12, R3, R2 and R1. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters;            /* R0 */
    px_शिखरम्_सम्बन्धि_राशिः -= 8;                                       /* R11..R4. */

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvTaskExitError( शून्य )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ). */
    panic_unsupported();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_SVCHandler( शून्य )
{
    /* This function is no longer used, but retained for backward
     * compatibility. */
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Start_First_Task( शून्य )
{
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
        __asm चञ्चल (
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
    #अन्यथा /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm चञ्चल (
            "    .syntax unified                    \n"
            #यदि config_RESET_राशिः_POINTER
                "   ldr  r0, =0xE000ED08            \n" /* Use the NVIC offset register to locate the stack. */
                "   ldr r0, [r0]                    \n"
                "   ldr r0, [r0]                    \n"
                "   msr msp, r0                     \n" /* Set the msp back to the start of the stack. */
            #यदि_अन्तः /* configRESET_STACK_POINTER */
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
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

#यदि ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    स्थिर शून्य prvFIFOInterruptHandler()
    {
        /* We must remove the contents (which we don't care about)
         * to clear the IRQ */
        multicore_fifo_drain();

        /* And explicitly clear any other IRQ flags. */
        multicore_fifo_clear_irq();

        #यदि ( config_सङ्ख्या_सम्बन्धि_CORES != 1 )
            पत्तनम्_YIELD_FROM_ISR( pdTRUE );
        #नोचेद्यदि ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
            आधारः_Type_t x_Higher_प्राथमिकता_Task_Woken = pdFALSE;
            uint32_t ulSave = spin_तालकम्_blocking( px_Cross_Core_Spin_तालकम् );
            Event_द्वयङ्काः_t ul_द्वयङ्काः = ux_Cross_Core_Event_द्वयङ्काः;
            ux_Cross_Core_Event_द्वयङ्काः &= ~ul_द्वयङ्काः;
            spin_unlock( px_Cross_Core_Spin_तालकम्, ulSave );
            x_Event_गणः_समुच्चयः_द्वयङ्काः_From_ISR( x_Event_गणः, ul_द्वयङ्काः, &x_Higher_प्राथमिकता_Task_Woken );
            पत्तनम्_YIELD_FROM_ISR( x_Higher_प्राथमिकता_Task_Woken );
        #यदि_अन्तः /* configNUMBER_OF_CORES != 1 */
    }
#यदि_अन्तः /* if ( LIB_PICO_MULTICORE == 1 ) && ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

/*
 * See header file for description.
 */
    स्थिर आधारः_Type_t x_पत्तनम्_Start_Scheduler_On_Core()
    {
        यदि( uc_Primary_Core_अङ्कः == get_core_अङ्कः() )
        {
            /* Start the timer that generates the tick ISR.  Interrupts are disabled
             * here already. */
            v_पत्तनम्_सज्जता_Timer_व्यवधानम्();

            /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
            पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_SYSTICK_PRI;
            #यदि ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
                exception_समुच्चयः_exclusive_handler( SYSTICK_EXCEPTION, x_पत्तनम्_Sys_Tick_Handler );
            #यदि_अन्तः
        }

        पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_PENDSV_PRI;

        #यदि ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_समुच्चयः_exclusive_handler( PENDSV_EXCEPTION, x_पत्तनम्_Pend_SVHandler );
            exception_समुच्चयः_exclusive_handler( SVCALL_EXCEPTION, v_पत्तनम्_SVCHandler );
        #यदि_अन्तः

        /* Install FIFO handler to receive interrupt from other core */
        multicore_fifo_clear_irq();
        multicore_fifo_drain();
        uint32_t ulIRQNum = SIO_IRQ_PROC0 + get_core_अङ्कः();
        irq_समुच्चयः_प्राथमिकता( ulIRQNum, पत्तनम्_MIN_व्यवधानम्_प्राथमिकता );
        irq_समुच्चयः_exclusive_handler( ulIRQNum, prvFIFOInterruptHandler );
        irq_समुच्चयः_enabled( ulIRQNum, 1 );

        /* Start the first task. */
        v_पत्तनम्_Start_First_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext( पत्तनम्_GET_CORE_ID() );
        prvTaskExitError();

        /* Should not get here. */
        प्रत्यागम 0;
    }

    स्थिर शून्य prv_Disable_Interrupts_And_पत्तनम्_Start_Scheduler_On_Core( शून्य )
    {
        पत्तनम्_DISABLE_INTERRUPTS();
        x_पत्तनम्_Start_Scheduler_On_Core();
    }

/*
 * See header file for description.
 */
    आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
    {
        configASSERT( uc_Primary_Core_अङ्कः == INVALID_PRIMARY_CORE_अङ्कः );

        /* No one else should use these! */
        spin_तालकम्_claim( configSMP_SPINLOCK_0 );
        spin_तालकम्_claim( configSMP_SPINLOCK_1 );

        uc_Primary_Core_अङ्कः = configTICK_CORE;
        configASSERT( get_core_अङ्कः() == 0 ); /* we must be started on core 0 */
        multicore_reset_core1();
        multicore_launch_core1( prv_Disable_Interrupts_And_पत्तनम्_Start_Scheduler_On_Core );

        x_पत्तनम्_Start_Scheduler_On_Core();

        /* Should not get here! */
        प्रत्यागम 0;
    }

#अन्यथा /* if ( configNUMBER_OF_CORES > 1 ) */

/*
 * See header file for description.
 */
    आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
    {
        /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
        पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_PENDSV_PRI;
        पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_SYSTICK_PRI;

        #यदि ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 )
            exception_समुच्चयः_exclusive_handler( PENDSV_EXCEPTION, x_पत्तनम्_Pend_SVHandler );
            exception_समुच्चयः_exclusive_handler( SYSTICK_EXCEPTION, x_पत्तनम्_Sys_Tick_Handler );
            exception_समुच्चयः_exclusive_handler( SVCALL_EXCEPTION, v_पत्तनम्_SVCHandler );
        #यदि_अन्तः

        /* Start the timer that generates the tick ISR.  Interrupts are disabled
         * here already. */
        v_पत्तनम्_सज्जता_Timer_व्यवधानम्();

        /* Initialise the critical nesting count ready for the first task. */
        uxCriticalNesting = 0;

        uc_Primary_Core_अङ्कः = get_core_अङ्कः();
        #यदि ( LIB_PICO_MULTICORE == 1 )
            #यदि ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
                multicore_fifo_clear_irq();
                multicore_fifo_drain();
                uint32_t irq_अङ्कः = SIO_IRQ_PROC0 + get_core_अङ्कः();
                irq_समुच्चयः_प्राथमिकता( irq_अङ्कः, पत्तनम्_MIN_व्यवधानम्_प्राथमिकता );
                irq_समुच्चयः_exclusive_handler( irq_अङ्कः, prvFIFOInterruptHandler );
                irq_समुच्चयः_enabled( irq_अङ्कः, 1 );
            #यदि_अन्तः
        #यदि_अन्तः

        /* Start the first task. */
        v_पत्तनम्_Start_First_Task();

        /* Should never get here as the tasks will now be executing!  Call the task
         * exit error function to prevent compiler warnings about a static function
         * not being called in the case that the application writer overrides this
         * functionality by defining configTASK_RETURN_ADDRESS. Call
         * vTaskSwitchContext() so link time optimization does not remove the
         * symbol. */
        vTaskSwitchContext();
        prvTaskExitError();

        /* Should not get here! */
        प्रत्यागम 0;
    }
#यदि_अन्तः /* if ( configNUMBER_OF_CORES > 1 ) */

/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( पत्तनम्_GET_CORE_ID() == 1000UL );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Yield( शून्य )
{
    /* Set a PendSV to request a context switch. */
    पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __asm चञ्चल ( "dsb" ::: "memory" );
    __asm चञ्चल ( "isb" );
}

/*-----------------------------------------------------------*/

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    शून्य v_पत्तनम्_Enter_Critical( शून्य )
    {
        पत्तनम्_DISABLE_INTERRUPTS();
        uxCriticalNesting++;
        __asm चञ्चल ( "dsb" ::: "memory" );
        __asm चञ्चल ( "isb" );
    }
#यदि_अन्तः /* #if ( configNUMBER_OF_CORES == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    शून्य v_पत्तनम्_Exit_Critical( शून्य )
    {
        configASSERT( uxCriticalNesting );
        uxCriticalNesting--;

        यदि( uxCriticalNesting == 0 )
        {
            पत्तनम्_ENABLE_INTERRUPTS();
        }
    }
#यदि_अन्तः /* #if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/

uint32_t ul_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR( शून्य )
{
    __asm चञ्चल (
        " mrs r0, PRIMASK    \n"
        " cpsid i            \n"
        " bx lr                "
        ::: "memory"
        );
}
/*-----------------------------------------------------------*/

शून्य v_Clear_व्यवधानम्_आवरणम्_From_ISR( __attribute__( ( अप्रयुक्तम् ) ) uint32_t ul_आवरणम् )
{
    __asm चञ्चल (
        " msr PRIMASK, r0    \n"
        " bx lr                "
        ::: "memory"
        );
}

/*-----------------------------------------------------------*/

शून्य vYieldCore( पूर्णाङ्क xCoreID )
{
    /* Remove warning if configASSERT is not defined.
     * xCoreID is not used in this function due to this is a dual-core system. The yielding core must be different from the current core. */
    ( शून्य ) xCoreID;

    configASSERT( xCoreID != ( पूर्णाङ्क ) पत्तनम्_GET_CORE_ID() );

    #यदि config_सङ्ख्या_सम्बन्धि_CORES != 1

        /* Non blocking, will cause interrupt on other core if the queue isn't already full,
         * in which case an IRQ must be pending */
        sio_hw->fifo_wr = 0;
    #यदि_अन्तः
}

/*-----------------------------------------------------------*/

शून्य x_पत्तनम्_Pend_SVHandler( शून्य )
{
    /* This is a naked function. */
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
        __asm चञ्चल
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
            #यदि पत्तनम्_USE_DIVIDER_SAVE_RESTORE
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
            #यदि_अन्तः /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #यदि पत्तनम्_USE_DIVIDER_SAVE_RESTORE
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
            #अन्यथा /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                    \n" /* Go back for the low registers that are not automatically restored. */
            #यदि_अन्तः /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                  \n"     /* Pop low registers.  */
            "                                       \n"
            "   bx r3                               \n"
            "   .align 4                            \n"
            "pxCurrentTCBConst2: .word pxCurrentTCB \n"
        );
    #अन्यथा /* if ( configNUMBER_OF_CORES == 1 ) */
        __asm चञ्चल
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
            #यदि पत्तनम्_USE_DIVIDER_SAVE_RESTORE

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
            #यदि_अन्तः /* portUSE_DIVIDER_SAVE_RESTORE */
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
            #यदि पत्तनम्_USE_DIVIDER_SAVE_RESTORE
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
            #अन्यथा /* if portUSE_DIVIDER_SAVE_RESTORE */
                "   subs r0, r0, #32                   \n" /* Go back for the low registers that are not automatically restored. */
            #यदि_अन्तः /* portUSE_DIVIDER_SAVE_RESTORE */
            "   ldmia r0!, {r4-r7}                 \n"     /* Pop low registers.  */
            "                                      \n"
            "   bx r3                              \n"
            "                                      \n"
            "   .align 4                           \n"
            "ulAsmLocals2:                         \n"
            "   .word 0xD0000000                   \n" /* SIO */
            "   .word pxCurrentTCBs                \n"
        );
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES == 1 ) */
}
/*-----------------------------------------------------------*/

शून्य x_पत्तनम्_Sys_Tick_Handler( शून्य )
{
    uint32_t ul_Previous_आवरणम्;

    ul_Previous_आवरणम् = taskENTER_CRITICAL_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();
            /* Pend a context switch. */
            पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT;
        }
        अन्यथा
        {
            traceISR_EXIT();
        }
    }
    taskEXIT_CRITICAL_FROM_ISR( ul_Previous_आवरणम् );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__( ( weak ) ) शून्य v_पत्तनम्_सज्जता_Timer_व्यवधानम्( शून्य )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #यदि ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( clock_get_hz( clk_sys ) / config_TICK_दरः_HZ );
        x_अधिकतमम्_Possible_Suppressed_Ticks = पत्तनम्_MAX_24_BIT_सङ्ख्या / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = पत्तनम्_MISSED_COUNTS_गुणकः;
    }
    #यदि_अन्तः /* configUSE_TICKLESS_IDLE */

    /* Stop and reset the SysTick. */
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = 0UL;
    पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ( clock_get_hz( clk_sys ) / config_TICK_दरः_HZ ) - 1UL;
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT | पत्तनम्_NVIC_SYSTICK_INT_BIT | पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;
}
/*-----------------------------------------------------------*/

#यदि ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) शून्य v_पत्तनम्_Suppress_Ticks_And_Sleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_Reload_मानम्, ulCompleteTickPeriods, ulCompletedSysTickDecrements;
        TickType_t xModifiableIdleTime;

        /* Make sure the SysTick reload value does not overflow the counter. */
        यदि( xExpectedIdleTime > x_अधिकतमम्_Possible_Suppressed_Ticks )
        {
            xExpectedIdleTime = x_अधिकतमम्_Possible_Suppressed_Ticks;
        }

        /* Stop the SysTick momentarily.  The time the SysTick is stopped for
         * is accounted for as best it can be, but using the tickless mode will
         * inevitably result in some tiny drift of the time maintained by the
         * kernel with respect to calendar time. */
        पत्तनम्_NVIC_SYSTICK_CTRL_REG &= ~पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;

        /* Calculate the reload value required to wait xExpectedIdleTime
         * tick periods.  -1 is used because this code will execute part way
         * through one of the tick periods. */
        ul_Reload_मानम् = पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );

        यदि( ul_Reload_मानम् > ulStoppedTimerCompensation )
        {
            ul_Reload_मानम् -= ulStoppedTimerCompensation;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm चञ्चल ( "cpsid i" ::: "memory" );
        __asm चञ्चल ( "dsb" );
        __asm चञ्चल ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        यदि( e_Task_Confirm_Sleep_बहुलकम्_स्थितिः() == eAbortSleep )
        {
            /* Restart from whatever is left in the count register to complete
             * this tick period. */
            पत्तनम्_NVIC_SYSTICK_आरोपय_REG = पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG;

            /* Restart SysTick. */
            पत्तनम्_NVIC_SYSTICK_CTRL_REG |= पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;

            /* Reset the reload register to the value required for normal tick
             * periods. */
            पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ulTimerCountsForOneTick - 1UL;

            /* Re-enable interrupts - see comments above the cpsid instruction()
             * above. */
            __asm चञ्चल ( "cpsie i" ::: "memory" );
        }
        अन्यथा
        {
            /* Set the new reload value. */
            पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ul_Reload_मानम्;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;

            /* Restart SysTick. */
            पत्तनम्_NVIC_SYSTICK_CTRL_REG |= पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            xModifiableIdleTime = xExpectedIdleTime;
            configPRE_SLEEP_PROCESSING( xModifiableIdleTime );

            यदि( xModifiableIdleTime > 0 )
            {
                __asm चञ्चल ( "dsb" ::: "memory" );
                __asm चञ्चल ( "wfi" );
                __asm चञ्चल ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  see comments above
             * __disable_interrupt() call above. */
            __asm चञ्चल ( "cpsie i" ::: "memory" );
            __asm चञ्चल ( "dsb" );
            __asm चञ्चल ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm चञ्चल ( "cpsid i" ::: "memory" );
            __asm चञ्चल ( "dsb" );
            __asm चञ्चल ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            पत्तनम्_NVIC_SYSTICK_CTRL_REG = ( पत्तनम्_NVIC_SYSTICK_CLK_BIT | पत्तनम्_NVIC_SYSTICK_INT_BIT );

            /* Determine if the SysTick clock has already counted to zero and
             * been set back to the current reload value (the reload back being
             * correct for the entire expected idle time) or if the SysTick is yet
             * to count to zero (in which case an interrupt other than the SysTick
             * must have brought the system out of sleep mode). */
            यदि( ( पत्तनम्_NVIC_SYSTICK_CTRL_REG & पत्तनम्_NVIC_SYSTICK_गणनम्_FLAG_BIT ) != 0 )
            {
                uint32_t ul_Calculated_आरोपय_मानम्;

                /* The tick interrupt is already pending, and the SysTick count
                 * reloaded with ulReloadValue.  Reset the
                 * portNVIC_SYSTICK_LOAD_REG with whatever remains of this tick
                 * period. */
                ul_Calculated_आरोपय_मानम् = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_मानम् - पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long. */
                यदि( ( ul_Calculated_आरोपय_मानम् < ulStoppedTimerCompensation ) || ( ul_Calculated_आरोपय_मानम् > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_आरोपय_मानम् = ( ulTimerCountsForOneTick - 1UL );
                }

                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ul_Calculated_आरोपय_मानम्;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
            }
            अन्यथा
            {
                /* Something other than the tick interrupt ended the sleep.
                 * Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG
             * again, then set portNVIC_SYSTICK_LOAD_REG back to its standard
             * value. */
            पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;
            पत्तनम्_NVIC_SYSTICK_CTRL_REG |= पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;
            v_Task_चरणः_Tick( ulCompleteTickPeriods );
            पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ulTimerCountsForOneTick - 1UL;

            /* Exit with interrupts enabled. */
            __asm चञ्चल ( "cpsie i" ::: "memory" );
        }
    }

#यदि_अन्तः /* configUSE_TICKLESS_IDLE */

#यदि ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( configSUPPORT_PICO_TIME_INTEROP == 1 )
    स्थिर TickType_t prv_Get_Ticks_गन्तव्यम्_Wait_Before( absolute_time_t t )
    {
        int64_t xDelay = absolute_time_diff_us( get_absolute_time(), t );
        ध्रुव uint32_t ulTickPeriod = 1000000 / config_TICK_दरः_HZ;

        xDelay -= ulTickPeriod;

        यदि( xDelay >= ulTickPeriod )
        {
            प्रत्यागम xDelay / ulTickPeriod;
        }

        प्रत्यागम 0;
    }
#यदि_अन्तः /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) || ( configSUPPORT_PICO_TIME_INTEROP == 1 ) */

#यदि ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
    uint32_t ul_पत्तनम्_तालकम्_Get_Current_Owner_Id()
    {
        यदि( पत्तनम्_IS_FREE_RTOS_CORE() )
        {
            uint32_t exception = __get_current_exception();

            यदि( !exception )
            {
                प्रत्यागम ( uintptr_t ) xTaskGetCurrentTaskHandle();
            }

            /* Note: since ROM as at 0x00000000, these can't be confused with
             * valid task handles (pointers) in RAM */
            /* We make all exception handler/core combinations distinct owners */
            प्रत्यागम get_core_अङ्कः() + exception * 2;
        }

        /* Note: since ROM as at 0x00000000, this can't be confused with
         * valid task handles (pointers) in RAM */
        प्रत्यागम get_core_अङ्कः();
    }

    स्थिर अन्तःस्थ Event_द्वयङ्काः_t prv_Get_Event_गणः_Bit( spin_तालकम्_t * spin_तालकम् )
    {
        uint32_t ulBit;

        #यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
            ulBit = 1u << ( spin_तालकम्_get_अङ्कः( spin_तालकम् ) & 0x7u );
        #नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
            /* Avoid potential use of SIO divider for % here out of abundance of caution */
            ulBit = spin_तालकम्_get_अङ्कः( spin_तालकम् );
            यदि (ulBit >= 24) ulBit -= 24;
            ulBit = 1u << ulBit;
        #यदि_अन्तः /* configTICK_TYPE_WIDTH_IN_BITS */
        प्रत्यागम ( Event_द्वयङ्काः_t ) ulBit;
    }

    स्थिर अन्तःस्थ Event_द्वयङ्काः_t prv_Get_All_Event_गणः_द्वयङ्काः()
    {
        #यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
            प्रत्यागम ( Event_द्वयङ्काः_t ) 0xffu;
        #नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
            प्रत्यागम ( Event_द्वयङ्काः_t ) 0xffffffu;
        #यदि_अन्तः /* configTICK_TYPE_WIDTH_IN_BITS */
    }

    शून्य v_पत्तनम्_तालकम्_आन्तरिकम्_Spin_Unlock_With_Wait( संरचना तालकम्_core * px_तालकम्,
                                              uint32_t ulSave )
    {
        configASSERT( !पत्तनम्_CHECK_IF_अन्तर्_ISR() );
        configASSERT( px_तालकम्->spin_तालकम्_2 );

        यदि( !पत्तनम्_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_तालकम्->spin_तालकम्_2, ulSave );
            __wfe();
        }
        अन्यथा
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
            spin_unlock( px_तालकम्->spin_तालकम्_2, ulSave);
            x_Event_गणः_Wait_द्वयङ्काः( x_Event_गणः, prv_Get_Event_गणः_Bit( px_तालकम्->spin_तालकम्_2 ),
                                 pdTRUE, pdFALSE, पत्तनम्_MAX_DELAY );
        }
    }

    शून्य v_पत्तनम्_तालकम्_आन्तरिकम्_Spin_Unlock_With_Notify( संरचना तालकम्_core * px_तालकम्,
                                                uint32_t ulSave )
    {
        Event_द्वयङ्काः_t ux_द्वयङ्काः = prv_Get_Event_गणः_Bit( px_तालकम्->spin_तालकम्_2 );

        यदि( पत्तनम्_IS_FREE_RTOS_CORE() )
        {
            #यदि LIB_PICO_MULTICORE
                /* signal an event in case a regular core is waiting */
                __sev();
            #यदि_अन्तः
            spin_unlock( px_तालकम्->spin_तालकम्_2, ulSave );

            यदि( !पत्तनम्_CHECK_IF_अन्तर्_ISR() )
            {
                x_Event_गणः_समुच्चयः_द्वयङ्काः( x_Event_गणः, ux_द्वयङ्काः );
            }
            अन्यथा
            {
                आधारः_Type_t x_Higher_प्राथमिकता_Task_Woken = pdFALSE;
                x_Event_गणः_समुच्चयः_द्वयङ्काः_From_ISR( x_Event_गणः, ux_द्वयङ्काः, &x_Higher_प्राथमिकता_Task_Woken );
                पत्तनम्_YIELD_FROM_ISR( x_Higher_प्राथमिकता_Task_Woken );
            }
        }
        अन्यथा
        {
            __sev();
            #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
                यदि( px_Cross_Core_Spin_तालकम् != px_तालकम्->spin_तालकम्_2 )
                {
                    spin_तालकम्_unsafe_blocking( px_Cross_Core_Spin_तालकम् );
                    ux_Cross_Core_Event_द्वयङ्काः |= ux_द्वयङ्काः;
                    spin_unlock_unsafe( px_Cross_Core_Spin_तालकम् );
                }
                अन्यथा
                {
                    ux_Cross_Core_Event_द्वयङ्काः |= ux_द्वयङ्काः;
                }

                /* This causes fifo irq on the other (FreeRTOS) core which will do the set the event bits */
                sio_hw->fifo_wr = 0;
            #यदि_अन्तः /* configNUMBER_OF_CORES == 1 */
            spin_unlock( px_तालकम्->spin_तालकम्_2, ulSave );
        }
    }

    bool x_पत्तनम्_तालकम्_आन्तरिकम्_Spin_Unlock_With_Best_Effort_Wait_Or_Timeout( संरचना तालकम्_core * px_तालकम्,
                                                                 uint32_t ulSave,
                                                                 absolute_time_t uxUntil )
    {
        configASSERT( !पत्तनम्_CHECK_IF_अन्तर्_ISR() );
        configASSERT( px_तालकम्->spin_तालकम्_2 );

        /* note no need to check LIB_PICO_MULTICORE, as this is always returns true if that is not defined */
        यदि( !पत्तनम्_IS_FREE_RTOS_CORE() )
        {
            spin_unlock( px_तालकम्->spin_तालकम्_2, ulSave );
            प्रत्यागम best_effort_wfe_or_timeout( uxUntil );
        }
        अन्यथा
        {
            configASSERT( पत्तनम्_IS_FREE_RTOS_CORE() );

            TickType_t ux_Ticks_गन्तव्यम्_Wait = prv_Get_Ticks_गन्तव्यम्_Wait_Before( uxUntil );

            यदि( ux_Ticks_गन्तव्यम्_Wait )
            {
                /* See comment in vPortLockInternalSpinUnlockWithWait for detail
                 * about possible race conditions */
                spin_unlock( px_तालकम्->spin_तालकम्_2, ulSave );
                x_Event_गणः_Wait_द्वयङ्काः( x_Event_गणः,
                                     prv_Get_Event_गणः_Bit( px_तालकम्->spin_तालकम्_2 ), pdTRUE,
                                     pdFALSE, ux_Ticks_गन्तव्यम्_Wait );
            }
            अन्यथा
            {
                spin_unlock( px_तालकम्->spin_तालकम्_2, ulSave );
            }

            यदि( time_reached( uxUntil ) )
            {
                प्रत्यागम true;
            }
            अन्यथा
            {
                /* We do not want to hog the core */
                पत्तनम्_YIELD();
                /* We aren't sure if we've reached the timeout yet; the caller will check */
                प्रत्यागम false;
            }
        }
    }

    #यदि ( configSUPPORT_PICO_SYNC_INTEROP == 1 )
        /* runs before main */
        स्थिर शून्य __attribute__( ( constructor ) ) prvRuntimeInitializer( शून्य )
        {
            /* This must be done even before the scheduler is started, as the spin lock
             * is used by the overrides of the SDK wait/notify primitives */
            #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
                px_Cross_Core_Spin_तालकम् = spin_तालकम्_instance( अग्र_striped_spin_तालकम्_अङ्कः() );
            #यदि_अन्तः /* configNUMBER_OF_CORES == 1 */

            /* The event group is not used prior to scheduler init, but is initialized
             * here to since it logically belongs with the spin lock */
            #यदि ( config_SUPPORT_STATIC_आवण्टनम् == 1 )
                x_Event_गणः = x_Event_गणः_Create_Static( &x_Static_Event_गणः );
            #अन्यथा

                /* Note that it is slightly dubious calling this here before the scheduler is initialized,
                 * however the only thing it touches is the allocator which then calls vPortEnterCritical
                 * and vPortExitCritical, and allocating here saves us checking the one time initialized variable in
                 * some rather critical code paths */
                x_Event_गणः = x_Event_गणः_Create();
            #यदि_अन्तः /* configSUPPORT_STATIC_ALLOCATION */
        }
    #यदि_अन्तः /* if ( configSUPPORT_PICO_SYNC_INTEROP == 1 ) */
#यदि_अन्तः /* configSUPPORT_PICO_SYNC_INTEROP */

#यदि ( configSUPPORT_PICO_TIME_INTEROP == 1 )
    शून्य x_पत्तनम्_Sync_आन्तरिकम्_Yield_Until_Before( absolute_time_t t )
    {
        TickType_t ux_Ticks_गन्तव्यम्_Wait = prv_Get_Ticks_गन्तव्यम्_Wait_Before( t );

        यदि( ux_Ticks_गन्तव्यम्_Wait )
        {
            vTaskDelay( ux_Ticks_गन्तव्यम्_Wait );
        }
    }
#यदि_अन्तः /* configSUPPORT_PICO_TIME_INTEROP */
