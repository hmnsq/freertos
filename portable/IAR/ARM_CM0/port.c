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
#అన్తర్భావ "intrinsics.h"

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* Prototype of all Interrupt Service Routines (ISRs). */
రకనిర్వచనం శూన్య ( * పోర్టు_ISR_t )( శూన్య );

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
#నిర్వచించు పోర్టు_NVIC_PEND_SYSTICK_సమితి_బిట్టు         ( 1UL << 26UL )
#నిర్వచించు పోర్టు_NVIC_PEND_SYSTICK_CLEAR_బిట్టు       ( 1UL << 25UL )
#నిర్వచించు పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత            ( 255UL )
#నిర్వచించు పోర్టు_NVIC_PENDSV_PRI                   ( పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత << 16UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_PRI                  ( పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత << 24UL )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#నిర్వచించు పోర్టు_SCB_VTOR_REG                      ( *( ( పోర్టు_ISR_t ** ) 0xe000ed08 ) )
#నిర్వచించు పోర్టు_సదిశ_సూచీ_PENDSV               ( 14 )

/* Constants required to set up the initial stack. */
#నిర్వచించు పోర్టు_INITIAL_XPSR                      ( 0x01000000 )

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
స్థిర UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/* The systick is a 24-bit counter. */
#నిర్వచించు పోర్టు_MAX_24_బిట్టు_సంఖ్య    ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#నిర్వచితం_కాకపోతే పోర్టు_MISSED_COUNTS_గుణకం
    #నిర్వచించు పోర్టు_MISSED_COUNTS_గుణకం    ( 94UL )
#అయితే_ముగింపు

/* The number of SysTick increments that make up one tick period. */
#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    స్థిర uint32_t ulTimerCountsForOneTick = 0;
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/* The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer. */
#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    స్థిర uint32_t x_గరిష్ఠ_Possible_Suppressed_Ticks = 0;
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/* Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only. */
#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    స్థిర uint32_t ulStoppedTimerCompensation = 0;
#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#నిర్వచితం_కాకపోతే configSYSTICK_CLOCK_HZ
    #నిర్వచించు configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG    ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు )
#లేకపోతే
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG    ( 0 )
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
శూన్య x_పోర్టు_Sys_Tick_Handler( శూన్య );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
బాహ్య శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

/*
 * FreeRTOS handlers implemented in assembly.
 */
బాహ్య శూన్య x_పోర్టు_Pend_SVHandler( శూన్య );
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_శిఖరం_యొక్క_దొంతర--;                                   /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_XPSR;                 /* xPSR */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;           /* PC */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) prvTaskExitError; /* LR */
    px_శిఖరం_యొక్క_దొంతర -= 5;                                /* R12, R3, R2 and R1. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;     /* R0 */
    px_శిఖరం_యొక్క_దొంతర -= 8;                                /* R11..R4. */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvTaskExitError( శూన్య )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    పోర్టు_DISABLE_INTERRUPTS();

    కొరకు( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
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
    #ఒకవేళ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        /* Point pxVectorTable to the interrupt vector table. Systems without
         * a VTOR register provide the value zero in the VTOR register and
         * the vector table itself is located at the address 0x00000000. */
        స్థిరరాశి పోర్టు_ISR_t * స్థిరరాశి px_సదిశ_పట్టిక = పోర్టు_SCB_VTOR_REG;

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
        configASSERT( px_సదిశ_పట్టిక[ పోర్టు_సదిశ_సూచీ_PENDSV ] == x_పోర్టు_Pend_SVHandler );
    }
    #అయితే_ముగింపు /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts. */
    పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_PENDSV_PRI;
    పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_పోర్టు_అమరిక_Timer_అంతరాయం();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Should not get here! */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Yield( శూన్య )
{
    /* Set a PendSV to request a context switch. */
    పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    పోర్టు_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    ఒకవేళ( uxCriticalNesting == 0 )
    {
        పోర్టు_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

శూన్య x_పోర్టు_Sys_Tick_Handler( శూన్య )
{
    uint32_t ul_మునుపటి_ముసుగు;

    ul_మునుపటి_ముసుగు = పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_గమ్యం_SCHEDULER();
            /* Pend a context switch. */
            పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET;
        }
        లేకపోతే
        {
            traceISR_EXIT();
        }
    }
    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ul_మునుపటి_ముసుగు );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__weak శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_రేటు_HZ );
        x_గరిష్ఠ_Possible_Suppressed_Ticks = పోర్టు_MAX_24_బిట్టు_సంఖ్య / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = పోర్టు_MISSED_COUNTS_గుణకం / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

    /* Stop and reset the SysTick. */
    పోర్టు_NVIC_SYSTICK_CTRL_REG = 0UL;
    పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_రేటు_HZ ) - 1UL;
    పోర్టు_NVIC_SYSTICK_CTRL_REG = ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు | పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు );
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )

    __weak శూన్య v_పోర్టు_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_సమయం )
    {
        uint32_t ul_Reload_విలువ, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ఎడమ;
        TickType_t x_Modifiable_Idle_సమయం;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ఒకవేళ( x_Expected_Idle_సమయం > x_గరిష్ఠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_సమయం = x_గరిష్ఠ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __disable_interrupt();
        __DSB();
        __ISB();

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ఒకవేళ( e_Task_Confirm_Sleep_బహుళకం_స్థితి() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the __disable_interrupt()
             * call above. */
            __enable_interrupt();
        }
        లేకపోతే
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            పోర్టు_NVIC_SYSTICK_CTRL_REG = ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_ఎడమ = పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG;

            ఒకవేళ( ul_Sys_Tick_Decrements_ఎడమ == 0 )
            {
                ul_Sys_Tick_Decrements_ఎడమ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_విలువ = ul_Sys_Tick_Decrements_ఎడమ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_సమయం - 1UL ) );

            ఒకవేళ( ( పోర్టు_NVIC_INT_CTRL_REG & పోర్టు_NVIC_PEND_SYSTICK_సమితి_బిట్టు ) != 0 )
            {
                పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PEND_SYSTICK_CLEAR_బిట్టు;
                ul_Reload_విలువ -= ulTimerCountsForOneTick;
            }

            ఒకవేళ( ul_Reload_విలువ > ulStoppedTimerCompensation )
            {
                ul_Reload_విలువ -= ulStoppedTimerCompensation;
            }

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
                __DSB();
                __WFI();
                __ISB();
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_సమయం );

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
            పోర్టు_NVIC_SYSTICK_CTRL_REG = ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు );

            /* Determine whether the SysTick has already counted to zero. */
            ఒకవేళ( ( పోర్టు_NVIC_SYSTICK_CTRL_REG & పోర్టు_NVIC_SYSTICK_లెక్క_FLAG_బిట్టు ) != 0 )
            {
                uint32_t ul_Calculated_ఎక్కించు_విలువ;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_ఎక్కించు_విలువ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_విలువ - పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                ఒకవేళ( ( ul_Calculated_ఎక్కించు_విలువ <= ulStoppedTimerCompensation ) || ( ul_Calculated_ఎక్కించు_విలువ > ulTimerCountsForOneTick ) )
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
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ఎడమ = పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG;
                #ఒకవేళ ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG != పోర్టు_NVIC_SYSTICK_CLK_బిట్టు )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    ఒకవేళ( ul_Sys_Tick_Decrements_ఎడమ == 0 )
                    {
                        ul_Sys_Tick_Decrements_ఎడమ = ul_Reload_విలువ;
                    }
                }
                #అయితే_ముగింపు /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_సమయం * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ఎడమ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;
            పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు | పోర్టు_NVIC_SYSTICK_INT_బిట్టు | పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;
            #ఒకవేళ ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG == పోర్టు_NVIC_SYSTICK_CLK_బిట్టు )
            {
                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ulTimerCountsForOneTick - 1UL;
            }
            #లేకపోతే
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు | పోర్టు_NVIC_SYSTICK_INT_బిట్టు;

                ఒకవేళ( ( పోర్టు_NVIC_SYSTICK_CTRL_REG & పోర్టు_NVIC_SYSTICK_లెక్క_FLAG_బిట్టు ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0;
                }

                పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ulTimerCountsForOneTick - 1UL;
                పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు | పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;
            }
            #అయితే_ముగింపు /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_అడుగు_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __enable_interrupt();
        }
    }

#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */
