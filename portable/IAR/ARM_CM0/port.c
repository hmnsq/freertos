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

/* IAR includes. */
#अन्तर्भाव "intrinsics.h"

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* Prototype of all Interrupt Service Routines (ISRs). */
प्रकारनिर्देश शून्य ( * पत्तनम्_ISR_t )( शून्य );

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
#परिभाषय पत्तनम्_NVIC_PEND_SYSTICK_समुच्चयः_BIT         ( 1UL << 26UL )
#परिभाषय पत्तनम्_NVIC_PEND_SYSTICK_CLEAR_BIT       ( 1UL << 25UL )
#परिभाषय पत्तनम्_MIN_व्यवधानम्_प्राथमिकता            ( 255UL )
#परिभाषय पत्तनम्_NVIC_PENDSV_PRI                   ( पत्तनम्_MIN_व्यवधानम्_प्राथमिकता << 16UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_PRI                  ( पत्तनम्_MIN_व्यवधानम्_प्राथमिकता << 24UL )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#परिभाषय पत्तनम्_SCB_VTOR_REG                      ( *( ( पत्तनम्_ISR_t ** ) 0xe000ed08 ) )
#परिभाषय पत्तनम्_सदिशम्_सूचकांक_PENDSV               ( 14 )

/* Constants required to set up the initial stack. */
#परिभाषय पत्तनम्_INITIAL_XPSR                      ( 0x01000000 )

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
स्थिर UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/* The systick is a 24-bit counter. */
#परिभाषय पत्तनम्_MAX_24_BIT_सङ्ख्या    ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#यदि_अपरिभाषितम् पत्तनम्_MISSED_COUNTS_गुणकः
    #परिभाषय पत्तनम्_MISSED_COUNTS_गुणकः    ( 94UL )
#यदि_अन्तः

/* The number of SysTick increments that make up one tick period. */
#यदि ( configUSE_TICKLESS_IDLE == 1 )
    स्थिर uint32_t ulTimerCountsForOneTick = 0;
#यदि_अन्तः /* configUSE_TICKLESS_IDLE */

/* The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer. */
#यदि ( configUSE_TICKLESS_IDLE == 1 )
    स्थिर uint32_t x_अधिकतमम्_Possible_Suppressed_Ticks = 0;
#यदि_अन्तः /* configUSE_TICKLESS_IDLE */

/* Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only. */
#यदि ( configUSE_TICKLESS_IDLE == 1 )
    स्थिर uint32_t ulStoppedTimerCompensation = 0;
#यदि_अन्तः /* configUSE_TICKLESS_IDLE */

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
 * Used to catch tasks that attempt to return from their implementing function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

/*
 * FreeRTOS handlers implemented in assembly.
 */
बाह्य शून्य x_पत्तनम्_Pend_SVHandler( शून्य );
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
    px_शिखरम्_सम्बन्धि_राशिः--;                                   /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_XPSR;                 /* xPSR */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;           /* PC */
    px_शिखरम्_सम्बन्धि_राशिः--;
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) prvTaskExitError; /* LR */
    px_शिखरम्_सम्बन्धि_राशिः -= 5;                                /* R12, R3, R2 and R1. */
    *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters;     /* R0 */
    px_शिखरम्_सम्बन्धि_राशिः -= 8;                                /* R11..R4. */

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
    /* An application can install FreeRTOS interrupt handlers in one of the
     * following ways:
     * 1. Direct Routing - Install the function xPortPendSVHandler for PendSV
     *    interrupt.
     * 2. Indirect Routing - Install separate handler for PendSV interrupt and
     *    route program control from that handler to xPortPendSVHandler function.
     *
     * Applications that use Indirect Routing must set
     * configCHECK_HANDLER_INSTALLATION to 0 in their FreeRTOSConfig.h. Direct
     * routing, which is validated here when configCHECK_HANDLER_INSTALLATION
     * is 1, should be preferred when possible. */
    #यदि ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        /* Point pxVectorTable to the interrupt vector table. Systems without
         * a VTOR register provide the value zero in the VTOR register and
         * the vector table itself is located at the address 0x00000000. */
        ध्रुव पत्तनम्_ISR_t * ध्रुव px_सदिशम्_सारणी = पत्तनम्_SCB_VTOR_REG;

        /* Validate that the application has correctly installed the FreeRTOS
         * handler for PendSV interrupt. We do not check the installation of the
         * SysTick handler because the application may choose to drive the RTOS
         * tick using a timer other than the SysTick timer by overriding the
         * weak function vPortSetupTimerInterrupt().
         *
         * Assertion failures here indicate incorrect installation of the
         * FreeRTOS handler. For help installing the FreeRTOS handler, see
         * https://www.freertos.org/Why-FreeRTOS/FAQs.
         *
         * Systems with a configurable address for the interrupt vector table
         * can also encounter assertion failures or even system faults here if
         * VTOR is not set correctly to point to the application's vector table. */
        configASSERT( px_सदिशम्_सारणी[ पत्तनम्_सदिशम्_सूचकांक_PENDSV ] == x_पत्तनम्_Pend_SVHandler );
    }
    #यदि_अन्तः /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts. */
    पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_PENDSV_PRI;
    पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_पत्तनम्_सज्जता_Timer_व्यवधानम्();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

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

शून्य v_पत्तनम्_Yield( शून्य )
{
    /* Set a PendSV to request a context switch. */
    पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    पत्तनम्_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
    __DSB();
    __ISB();
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
    uint32_t ul_Previous_आवरणम्;

    ul_Previous_आवरणम् = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();
            /* Pend a context switch. */
            पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET;
        }
        अन्यथा
        {
            traceISR_EXIT();
        }
    }
    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ul_Previous_आवरणम् );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__weak शून्य v_पत्तनम्_सज्जता_Timer_व्यवधानम्( शून्य )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #यदि ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_दरः_HZ );
        x_अधिकतमम्_Possible_Suppressed_Ticks = पत्तनम्_MAX_24_BIT_सङ्ख्या / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = पत्तनम्_MISSED_COUNTS_गुणकः / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #यदि_अन्तः /* configUSE_TICKLESS_IDLE */

    /* Stop and reset the SysTick. */
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = 0UL;
    पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_दरः_HZ ) - 1UL;
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT | पत्तनम्_NVIC_SYSTICK_ENABLE_BIT );
}
/*-----------------------------------------------------------*/

#यदि ( configUSE_TICKLESS_IDLE == 1 )

    __weak शून्य v_पत्तनम्_Suppress_Ticks_And_Sleep( TickType_t xExpectedIdleTime )
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
        __disable_interrupt();
        __DSB();
        __ISB();

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        यदि( e_Task_Confirm_Sleep_बहुलकम्_स्थितिः() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the __disable_interrupt()
             * call above. */
            __enable_interrupt();
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
                __DSB();
                __WFI();
                __ISB();
            }

            configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the __disable_interrupt() call above. */
            __enable_interrupt();
            __DSB();
            __ISB();

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __disable_interrupt();
            __DSB();
            __ISB();

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
            __enable_interrupt();
        }
    }

#यदि_अन्तः /* configUSE_TICKLESS_IDLE */
