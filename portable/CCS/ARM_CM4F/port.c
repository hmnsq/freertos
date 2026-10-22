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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

#यदि_अपरिभाषितम् __TI_VFP_SUPPORT__
    #दोषः This पत्तनम् can only be प्रयुक्तम् when the project options are configured गन्तव्यम् enable hardware floating point support.
#यदि_अन्तः

#यदि ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता == 0 )
    #दोषः config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता must not be समुच्चयः गन्तव्यम् 0.  See http: /*www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
#यदि_अन्तः

/* Constants required to manipulate the core.  Registers first... */
#परिभाषय पत्तनम्_NVIC_SYSTICK_CTRL_REG             ( *( ( चञ्चल uint32_t * ) 0xe000e010 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_आरोपय_REG             ( *( ( चञ्चल uint32_t * ) 0xe000e014 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG    ( *( ( चञ्चल uint32_t * ) 0xe000e018 ) )
#परिभाषय पत्तनम्_NVIC_SHPR3_REG                    ( *( ( चञ्चल uint32_t * ) 0xe000ed20 ) )
/* ...then bits in the registers. */
#परिभाषय पत्तनम्_NVIC_SYSTICK_CLK_BIT              ( 1UL << 2UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_INT_BIT              ( 1UL << 1UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_ENABLE_BIT           ( 1UL << 0UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_गणनम्_FLAG_BIT       ( 1UL << 16UL )
#परिभाषय पत्तनम्_NVIC_PENDSVCLEAR_BIT              ( 1UL << 27UL )
#परिभाषय पत्तनम्_NVIC_PEND_SYSTICK_समुच्चयः_BIT         ( 1UL << 26UL )
#परिभाषय पत्तनम्_NVIC_PEND_SYSTICK_CLEAR_BIT       ( 1UL << 25UL )

#परिभाषय पत्तनम्_MIN_व्यवधानम्_प्राथमिकता            ( 255UL )
#परिभाषय पत्तनम्_NVIC_PENDSV_PRI                   ( ( ( uint32_t ) पत्तनम्_MIN_व्यवधानम्_प्राथमिकता ) << 16UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_PRI                  ( ( ( uint32_t ) पत्तनम्_MIN_व्यवधानम्_प्राथमिकता ) << 24UL )

/* Constants required to check the validity of an interrupt priority. */
#परिभाषय पत्तनम्_FIRST_USER_व्यवधानम्_सङ्ख्या       ( 16 )
#परिभाषय पत्तनम्_NVIC_IP_REGISTERS_विस्थापनम्_16       ( 0xE000E3F0 )
#परिभाषय पत्तनम्_AIRCR_REG                         ( *( ( चञ्चल uint32_t * ) 0xE000ED0C ) )
#परिभाषय पत्तनम्_MAX_8_BIT_मानम्                   ( ( uint8_t ) 0xff )
#परिभाषय पत्तनम्_शिखरम्_BIT_सम्बन्धि_BYTE                   ( ( uint8_t ) 0x80 )
#परिभाषय पत्तनम्_MAX_PRIGROUP_द्वयङ्काः                 ( ( uint8_t ) 7 )
#परिभाषय पत्तनम्_प्राथमिकता_गणः_आवरणम्               ( 0x07UL << 8UL )
#परिभाषय पत्तनम्_PRIGROUP_सरणम्                    ( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#परिभाषय पत्तनम्_VECTACTIVE_आवरणम्                   ( 0xFFUL )

/* Constants required to manipulate the VFP. */
#परिभाषय पत्तनम्_FPCCR                             ( ( चञ्चल uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#परिभाषय पत्तनम्_ASPEN_AND_LSPEN_द्वयङ्काः              ( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#परिभाषय पत्तनम्_INITIAL_XPSR                      ( 0x01000000 )
#परिभाषय पत्तनम्_INITIAL_EXC_RETURN                ( 0xfffffffd )

/* The systick is a 24-bit counter. */
#परिभाषय पत्तनम्_MAX_24_BIT_सङ्ख्या                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#परिभाषय पत्तनम्_MISSED_COUNTS_गुणकः              ( 94UL )

/* For strict compliance with the Cortex-M spec the task start address should
 * have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#परिभाषय पत्तनम्_START_स्थानाङ्कः_आवरणम्                ( ( राशिः_Type_t ) 0xfffffffeUL )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#यदि_अपरिभाषितम् configSYSTICK_CLOCK_HZ
    #परिभाषय configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #परिभाषय पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG    ( पत्तनम्_NVIC_SYSTICK_CLK_BIT )
#अन्यथा
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #परिभाषय पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG    ( 0 )
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
शून्य x_पत्तनम्_Sys_Tick_Handler( शून्य );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
बाह्य शून्य v_पत्तनम्_Start_First_Task( शून्य );

/*
 * Turn the VFP on.
 */
बाह्य शून्य v_पत्तनम्_Enable_VFP( शून्य );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

/*-----------------------------------------------------------*/

/* Required to allow portasm.asm access the configMAX_SYSCALL_INTERRUPT_PRIORITY
 * setting. */
ध्रुव uint32_t ul_Max_Syscall_व्यवधानम्_प्राथमिकता = config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता;

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
स्थिर UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

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

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#यदि ( configASSERT_DEFINED == 1 )
    स्थिर uint8_t uc_Max_Sys_Call_प्राथमिकता = 0;
    स्थिर uint32_t ulMaxPRIGROUPValue = 0;
    स्थिर ध्रुव चञ्चल uint8_t * ध्रुव pc_व्यवधानम्_प्राथमिकता_Registers = ( uint8_t * ) पत्तनम्_NVIC_IP_REGISTERS_विस्थापनम्_16;
#यदि_अन्तः /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */

    /* Offset added to account for the way the MCU uses the stack on entry/exit
     * of interrupts, and to ensure alignment. */
    px_शिखरम्_सम्बन्धि_राशिः--;

    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_XPSR;                                    /* xPSR */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( ( राशिः_Type_t ) px_संहिता ) & पत्तनम्_START_स्थानाङ्कः_आवरणम्; /* PC */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) prvTaskExitError;                    /* LR */

    /* Save code space by skipping register initialisation. */
    px_शिखरम्_सम्बन्धि_राशिः -= 5;                            /* R12, R3, R2 and R1. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
     * own exec return value. */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_EXC_RETURN;

    px_शिखरम्_सम्बन्धि_राशिः -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvTaskExitError( शून्य )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    पत्तनम्_DISABLE_INTERRUPTS();

    प्रति( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    #यदि ( configASSERT_DEFINED == 1 )
    {
        चञ्चल uint8_t uc_Original_प्राथमिकता;
        चञ्चल uint32_t ul_Implemented_Prio_द्वयङ्काः = 0;
        चञ्चल uint8_t * ध्रुव puc_First_User_प्राथमिकता_पञ्जिकाकोशः = ( uint8_t * ) ( पत्तनम्_NVIC_IP_REGISTERS_विस्थापनम्_16 + पत्तनम्_FIRST_USER_व्यवधानम्_सङ्ख्या );
        चञ्चल uint8_t uc_Max_प्राथमिकता_मानम्;

        /* Determine the maximum priority from which ISR safe FreeRTOS API
         * functions can be called.  ISR safe functions are those that end in
         * "FromISR".  FreeRTOS maintains separate thread and ISR API functions to
         * ensure interrupt entry is as fast and simple as possible.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_प्राथमिकता = *puc_First_User_प्राथमिकता_पञ्जिकाकोशः;

        /* Determine the number of priority bits available.  First write to all
         * possible bits. */
        *puc_First_User_प्राथमिकता_पञ्जिकाकोशः = पत्तनम्_MAX_8_BIT_मानम्;

        /* Read the value back to see how many bits stuck. */
        uc_Max_प्राथमिकता_मानम् = *puc_First_User_प्राथमिकता_पञ्जिकाकोशः;

        /* Use the same mask on the maximum system call priority. */
        uc_Max_Sys_Call_प्राथमिकता = config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता & uc_Max_प्राथमिकता_मानम्;

        /* Check that the maximum system call priority is nonzero after
         * accounting for the number of priority bits supported by the
         * hardware. A priority of 0 is invalid because setting the BASEPRI
         * register to 0 unmasks all interrupts, and interrupts with priority 0
         * cannot be masked using BASEPRI.
         * See https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
        configASSERT( uc_Max_Sys_Call_प्राथमिकता );

        /* Check that the bits not implemented in hardware are zero in
         * configMAX_SYSCALL_INTERRUPT_PRIORITY. */
        configASSERT( ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता & ( ~uc_Max_प्राथमिकता_मानम् ) ) == 0U );

        /* Calculate the maximum acceptable priority group value for the number
         * of bits read back. */

        यावत्( ( uc_Max_प्राथमिकता_मानम् & पत्तनम्_शिखरम्_BIT_सम्बन्धि_BYTE ) == पत्तनम्_शिखरम्_BIT_सम्बन्धि_BYTE )
        {
            ul_Implemented_Prio_द्वयङ्काः++;
            uc_Max_प्राथमिकता_मानम् <<= ( uint8_t ) 0x01;
        }

        यदि( ul_Implemented_Prio_द्वयङ्काः == 8 )
        {
            /* When the hardware implements 8 priority bits, there is no way for
            * the software to configure PRIGROUP to not have sub-priorities. As
            * a result, the least significant bit is always used for sub-priority
            * and there are 128 preemption priorities and 2 sub-priorities.
            *
            * This may cause some confusion in some cases - for example, if
            * configMAX_SYSCALL_INTERRUPT_PRIORITY is set to 5, both 5 and 4
            * priority interrupts will be masked in Critical Sections as those
            * are at the same preemption priority. This may appear confusing as
            * 4 is higher (numerically lower) priority than
            * configMAX_SYSCALL_INTERRUPT_PRIORITY and therefore, should not
            * have been masked. Instead, if we set configMAX_SYSCALL_INTERRUPT_PRIORITY
            * to 4, this confusion does not happen and the behaviour remains the same.
            *
            * The following assert ensures that the sub-priority bit in the
            * configMAX_SYSCALL_INTERRUPT_PRIORITY is clear to avoid the above mentioned
            * confusion. */
            configASSERT( ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता & 0x1U ) == 0U );
            ulMaxPRIGROUPValue = 0;
        }
        अन्यथा
        {
            ulMaxPRIGROUPValue = पत्तनम्_MAX_PRIGROUP_द्वयङ्काः - ul_Implemented_Prio_द्वयङ्काः;
        }

        /* Shift the priority group value back to its position within the AIRCR
         * register. */
        ulMaxPRIGROUPValue <<= पत्तनम्_PRIGROUP_सरणम्;
        ulMaxPRIGROUPValue &= पत्तनम्_प्राथमिकता_गणः_आवरणम्;

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_First_User_प्राथमिकता_पञ्जिकाकोशः = uc_Original_प्राथमिकता;
    }
    #यदि_अन्तः /* configASSERT_DEFINED */

    /* Make PendSV and SysTick the lowest priority interrupts. */
    पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_PENDSV_PRI;
    पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_पत्तनम्_सज्जता_Timer_व्यवधानम्();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Ensure the VFP is enabled - it should be anyway. */
    v_पत्तनम्_Enable_VFP();

    /* Lazy save always. */
    *( पत्तनम्_FPCCR ) |= पत्तनम्_ASPEN_AND_LSPEN_द्वयङ्काः;

    /* Start the first task. */
    v_पत्तनम्_Start_First_Task();

    /* Should not get here! */
    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    पत्तनम्_DISABLE_INTERRUPTS();
    uxCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    यदि( uxCriticalNesting == 1 )
    {
        configASSERT( ( पत्तनम्_NVIC_INT_CTRL_REG & पत्तनम्_VECTACTIVE_आवरणम् ) == 0 );
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    यदि( uxCriticalNesting == 0 )
    {
        पत्तनम्_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

शून्य x_पत्तनम्_Sys_Tick_Handler( शून्य )
{
    /* The SysTick runs at the lowest interrupt priority, so when this interrupt
     * executes all interrupts must be unmasked.  There is therefore no need to
     * save and then restore the interrupt mask value as its value is already
     * known. */
    ( शून्य ) पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();

            /* A context switch is required.  Context switching is performed in
             * the PendSV interrupt.  Pend the PendSV interrupt. */
            पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT;
        }
        अन्यथा
        {
            traceISR_EXIT();
        }
    }
    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( 0 );
}
/*-----------------------------------------------------------*/

#यदि ( configUSE_TICKLESS_IDLE == 1 )

    #निर्देशः WEAK( v_पत्तनम्_Suppress_Ticks_And_Sleep )
    शून्य v_पत्तनम्_Suppress_Ticks_And_Sleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_Reload_मानम्, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_वामः;
        TickType_t xModifiableIdleTime;

        /* Make sure the SysTick reload value does not overflow the counter. */
        यदि( xExpectedIdleTime > x_अधिकतमम्_Possible_Suppressed_Ticks )
        {
            xExpectedIdleTime = x_अधिकतमम्_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm( "    cpsid i" );
        __asm( "    dsb" );
        __asm( "    isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        यदि( e_Task_Confirm_Sleep_बहुलकम्_स्थितिः() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm( "    cpsie i" );
        }
        अन्यथा
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            पत्तनम्_NVIC_SYSTICK_CTRL_REG = ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_वामः = पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG;

            यदि( ul_Sys_Tick_Decrements_वामः == 0 )
            {
                ul_Sys_Tick_Decrements_वामः = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_मानम् = ul_Sys_Tick_Decrements_वामः + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );

            यदि( ( पत्तनम्_NVIC_INT_CTRL_REG & पत्तनम्_NVIC_PEND_SYSTICK_समुच्चयः_BIT ) != 0 )
            {
                पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PEND_SYSTICK_CLEAR_BIT;
                ul_Reload_मानम् -= ulTimerCountsForOneTick;
            }

            यदि( ul_Reload_मानम् > ulStoppedTimerCompensation )
            {
                ul_Reload_मानम् -= ulStoppedTimerCompensation;
            }

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
                __asm( "    dsb" );
                __asm( "    wfi" );
                __asm( "    isb" );
            }

            configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm( "    cpsie i" );
            __asm( "    dsb" );
            __asm( "    isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm( "    cpsid i" );
            __asm( "    dsb" );
            __asm( "    isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            पत्तनम्_NVIC_SYSTICK_CTRL_REG = ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT );

            /* Determine whether the SysTick has already counted to zero. */
            यदि( ( पत्तनम्_NVIC_SYSTICK_CTRL_REG & पत्तनम्_NVIC_SYSTICK_गणनम्_FLAG_BIT ) != 0 )
            {
                uint32_t ul_Calculated_आरोपय_मानम्;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_आरोपय_मानम् = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_मानम् - पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                यदि( ( ul_Calculated_आरोपय_मानम् <= ulStoppedTimerCompensation ) || ( ul_Calculated_आरोपय_मानम् > ulTimerCountsForOneTick ) )
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
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_वामः = पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG;
                #यदि ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG != पत्तनम्_NVIC_SYSTICK_CLK_BIT )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    यदि( ul_Sys_Tick_Decrements_वामः == 0 )
                    {
                        ul_Sys_Tick_Decrements_वामः = ul_Reload_मानम्;
                    }
                }
                #यदि_अन्तः /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_वामः;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;
            पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT | पत्तनम्_NVIC_SYSTICK_INT_BIT | पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;
            #यदि ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG == पत्तनम्_NVIC_SYSTICK_CLK_BIT )
            {
                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ulTimerCountsForOneTick - 1UL;
            }
            #अन्यथा
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT | पत्तनम्_NVIC_SYSTICK_INT_BIT;

                यदि( ( पत्तनम्_NVIC_SYSTICK_CTRL_REG & पत्तनम्_NVIC_SYSTICK_गणनम्_FLAG_BIT ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0;
                }

                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ulTimerCountsForOneTick - 1UL;
                पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT | पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;
            }
            #यदि_अन्तः /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_चरणः_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm( "    cpsie i" );
        }
    }

#यदि_अन्तः /* configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
#निर्देशः WEAK( v_पत्तनम्_सज्जता_Timer_व्यवधानम् )
शून्य v_पत्तनम्_सज्जता_Timer_व्यवधानम्( शून्य )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #यदि ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_दरः_HZ );
        x_अधिकतमम्_Possible_Suppressed_Ticks = पत्तनम्_MAX_24_BIT_सङ्ख्या / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = पत्तनम्_MISSED_COUNTS_गुणकः / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #यदि_अन्तः /* configUSE_TICKLESS_IDLE */

    /* Stop and clear the SysTick. */
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = 0UL;
    पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_दरः_HZ ) - 1UL;
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT | पत्तनम्_NVIC_SYSTICK_ENABLE_BIT );
}
/*-----------------------------------------------------------*/

#यदि ( configASSERT_DEFINED == 1 )

    शून्य v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता( शून्य )
    {
        बाह्य uint32_t ul_पत्तनम्_Get_IPSR( शून्य );
        uint32_t ul_Current_व्यवधानम्;
        uint8_t uc_Current_प्राथमिकता;

        ul_Current_व्यवधानम् = ul_पत्तनम्_Get_IPSR();

        /* Is the interrupt number a user defined interrupt? */
        यदि( ul_Current_व्यवधानम् >= पत्तनम्_FIRST_USER_व्यवधानम्_सङ्ख्या )
        {
            /* Look up the interrupt's priority. */
            uc_Current_प्राथमिकता = pc_व्यवधानम्_प्राथमिकता_Registers[ ul_Current_व्यवधानम् ];

            /* The following assertion will fail if a service routine (ISR) for
             * an interrupt that has been assigned a priority above
             * configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
             * function.  ISR safe FreeRTOS API functions must *only* be called
             * from interrupts that have been assigned a priority at or below
             * configMAX_SYSCALL_INTERRUPT_PRIORITY.
             *
             * Numerically low interrupt priority numbers represent logically high
             * interrupt priorities, therefore the priority of the interrupt must
             * be set to a value equal to or numerically *higher* than
             * configMAX_SYSCALL_INTERRUPT_PRIORITY.
             *
             * Interrupts that  use the FreeRTOS API must not be left at their
             * default priority of  zero as that is the highest possible priority,
             * which is guaranteed to be above configMAX_SYSCALL_INTERRUPT_PRIORITY,
             * and  therefore also guaranteed to be invalid.
             *
             * FreeRTOS maintains separate thread and ISR API functions to ensure
             * interrupt entry is as fast and simple as possible.
             *
             * The following links provide detailed information:
             * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
             * https://www.freertos.org/Why-FreeRTOS/FAQs */
            configASSERT( uc_Current_प्राथमिकता >= uc_Max_Sys_Call_प्राथमिकता );
        }

        /* Priority grouping:  The interrupt controller (NVIC) allows the bits
         * that define each interrupt's priority to be split between bits that
         * define the interrupt's pre-emption priority bits and bits that define
         * the interrupt's sub-priority.  For simplicity all bits must be defined
         * to be pre-emption priority bits.  The following assertion will fail if
         * this is not the case (if some bits represent a sub-priority).
         *
         * If the application only uses CMSIS libraries for interrupt
         * configuration then the correct setting can be achieved on all Cortex-M
         * devices by calling NVIC_SetPriorityGrouping( 0 ); before starting the
         * scheduler.  Note however that some vendor specific peripheral libraries
         * assume a non-zero priority group setting, in which cases using a value
         * of zero will result in unpredictable behaviour. */
        configASSERT( ( पत्तनम्_AIRCR_REG & पत्तनम्_प्राथमिकता_गणः_आवरणम् ) <= ulMaxPRIGROUPValue );
    }

#यदि_अन्तः /* configASSERT_DEFINED */
