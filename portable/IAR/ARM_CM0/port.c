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
#ضمن "intrinsics.h"

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Prototype of all Interrupt Service Routines (ISRs). */
تعريفنوع فراغ ( * پورټ_ISR_t )( فراغ );

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
#تعریف_کړه پورټ_NVIC_PEND_SYSTICK_سېټ_بټ         ( 1UL << 26UL )
#تعریف_کړه پورټ_NVIC_PEND_SYSTICK_CLEAR_بټ       ( 1UL << 25UL )
#تعریف_کړه پورټ_MIN_مداخله_لومړیتوب            ( 255UL )
#تعریف_کړه پورټ_NVIC_PENDSV_PRI                   ( پورټ_MIN_مداخله_لومړیتوب << 16UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_PRI                  ( پورټ_MIN_مداخله_لومړیتوب << 24UL )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#تعریف_کړه پورټ_SCB_VTOR_REG                      ( *( ( پورټ_ISR_t ** ) 0xe000ed08 ) )
#تعریف_کړه پورټ_ویکټور_شاخص_PENDSV               ( 14 )

/* Constants required to set up the initial stack. */
#تعریف_کړه پورټ_INITIAL_XPSR                      ( 0x01000000 )

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساكن UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/* The systick is a 24-bit counter. */
#تعریف_کړه پورټ_MAX_24_بټ_شمېره    ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#که_نه_تعریف_شوی پورټ_MISSED_COUNTS_ضریب
    #تعریف_کړه پورټ_MISSED_COUNTS_ضریب    ( 94UL )
#د_که_پای

/* The number of SysTick increments that make up one tick period. */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulTimerCountsForOneTick = 0;
#د_که_پای /* configUSE_TICKLESS_IDLE */

/* The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer. */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t x_اعظمي_Possible_Suppressed_Ticks = 0;
#د_که_پای /* configUSE_TICKLESS_IDLE */

/* Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only. */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulStoppedTimerCompensation = 0;
#د_که_پای /* configUSE_TICKLESS_IDLE */

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#که_نه_تعریف_شوی configSYSTICK_CLOCK_HZ
    #تعریف_کړه configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کړه پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG    ( پورټ_NVIC_SYSTICK_CLK_بټ )
#وإلا
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #تعریف_کړه پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG    ( 0 )
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
فراغ x_پورټ_Sys_Tick_Handler( فراغ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
خارجي فراغ v_پورټ_پیل_لومړی_Task( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*
 * FreeRTOS handlers implemented in assembly.
 */
خارجي فراغ x_پورټ_Pend_SVHandler( فراغ );
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_سر_د_ډېری--;                                   /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_سر_د_ډېری = پورټ_INITIAL_XPSR;                 /* xPSR */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ;           /* PC */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) prvTaskExitError; /* LR */
    px_سر_د_ډېری -= 5;                                /* R12, R3, R2 and R1. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;     /* R0 */
    px_سر_د_ډېری -= 8;                                /* R11..R4. */

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvTaskExitError( فراغ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    پورټ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
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
    #إذا ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        /* Point pxVectorTable to the interrupt vector table. Systems without
         * a VTOR register provide the value zero in the VTOR register and
         * the vector table itself is located at the address 0x00000000. */
        ثابت پورټ_ISR_t * ثابت px_ویکټور_جدول = پورټ_SCB_VTOR_REG;

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
        configASSERT( px_ویکټور_جدول[ پورټ_ویکټور_شاخص_PENDSV ] == x_پورټ_Pend_SVHandler );
    }
    #د_که_پای /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts. */
    پورټ_NVIC_SHPR3_REG |= پورټ_NVIC_PENDSV_PRI;
    پورټ_NVIC_SHPR3_REG |= پورټ_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_پورټ_تیاری_Timer_مداخله();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    v_پورټ_پیل_لومړی_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Yield( فراغ )
{
    /* Set a PendSV to request a context switch. */
    پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ )
{
    پورټ_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    إذا( uxCriticalNesting == 0 )
    {
        پورټ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

فراغ x_پورټ_Sys_Tick_Handler( فراغ )
{
    uint32_t ul_پخوانی_ماسک;

    ul_پخوانی_ماسک = پورټ_سېټ_مداخله_ماسک_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_منزل_SCHEDULER();
            /* Pend a context switch. */
            پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PENDSVSET;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ul_پخوانی_ماسک );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__weak فراغ v_پورټ_تیاری_Timer_مداخله( فراغ )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #إذا ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ );
        x_اعظمي_Possible_Suppressed_Ticks = پورټ_MAX_24_بټ_شمېره / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورټ_MISSED_COUNTS_ضریب / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #د_که_پای /* configUSE_TICKLESS_IDLE */

    /* Stop and reset the SysTick. */
    پورټ_NVIC_SYSTICK_CTRL_REG = 0UL;
    پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورټ_NVIC_SYSTICK_بارول_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    پورټ_NVIC_SYSTICK_CTRL_REG = ( پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG | پورټ_NVIC_SYSTICK_INT_بټ | پورټ_NVIC_SYSTICK_ENABLE_بټ );
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    __weak فراغ v_پورټ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وخت )
    {
        uint32_t ul_Reload_ارزښت, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_کیڼ;
        TickType_t x_Modifiable_Idle_وخت;

        /* Make sure the SysTick reload value does not overflow the counter. */
        إذا( x_Expected_Idle_وخت > x_اعظمي_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_وخت = x_اعظمي_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __disable_interrupt();
        __DSB();
        __ISB();

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_ډېرپېښ_حالت() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the __disable_interrupt()
             * call above. */
            __enable_interrupt();
        }
        وإلا
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            پورټ_NVIC_SYSTICK_CTRL_REG = ( پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG | پورټ_NVIC_SYSTICK_INT_بټ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_کیڼ = پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG;

            إذا( ul_Sys_Tick_Decrements_کیڼ == 0 )
            {
                ul_Sys_Tick_Decrements_کیڼ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_ارزښت = ul_Sys_Tick_Decrements_کیڼ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_وخت - 1UL ) );

            إذا( ( پورټ_NVIC_INT_CTRL_REG & پورټ_NVIC_PEND_SYSTICK_سېټ_بټ ) != 0 )
            {
                پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PEND_SYSTICK_CLEAR_بټ;
                ul_Reload_ارزښت -= ulTimerCountsForOneTick;
            }

            إذا( ul_Reload_ارزښت > ulStoppedTimerCompensation )
            {
                ul_Reload_ارزښت -= ulStoppedTimerCompensation;
            }

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
                __DSB();
                __WFI();
                __ISB();
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_وخت );

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
            پورټ_NVIC_SYSTICK_CTRL_REG = ( پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG | پورټ_NVIC_SYSTICK_INT_بټ );

            /* Determine whether the SysTick has already counted to zero. */
            إذا( ( پورټ_NVIC_SYSTICK_CTRL_REG & پورټ_NVIC_SYSTICK_شمېر_FLAG_بټ ) != 0 )
            {
                uint32_t ul_Calculated_بارول_ارزښت;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_بارول_ارزښت = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_ارزښت - پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                إذا( ( ul_Calculated_بارول_ارزښت <= ulStoppedTimerCompensation ) || ( ul_Calculated_بارول_ارزښت > ulTimerCountsForOneTick ) )
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
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_کیڼ = پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG;
                #إذا ( پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG != پورټ_NVIC_SYSTICK_CLK_بټ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    إذا( ul_Sys_Tick_Decrements_کیڼ == 0 )
                    {
                        ul_Sys_Tick_Decrements_کیڼ = ul_Reload_ارزښت;
                    }
                }
                #د_که_پای /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_وخت * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_کیڼ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورټ_NVIC_SYSTICK_بارول_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG = 0UL;
            پورټ_NVIC_SYSTICK_CTRL_REG = پورټ_NVIC_SYSTICK_CLK_بټ | پورټ_NVIC_SYSTICK_INT_بټ | پورټ_NVIC_SYSTICK_ENABLE_بټ;
            #إذا ( پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG == پورټ_NVIC_SYSTICK_CLK_بټ )
            {
                پورټ_NVIC_SYSTICK_بارول_REG = ulTimerCountsForOneTick - 1UL;
            }
            #وإلا
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                پورټ_NVIC_SYSTICK_CTRL_REG = پورټ_NVIC_SYSTICK_CLK_بټ | پورټ_NVIC_SYSTICK_INT_بټ;

                إذا( ( پورټ_NVIC_SYSTICK_CTRL_REG & پورټ_NVIC_SYSTICK_شمېر_FLAG_بټ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG = 0;
                }

                پورټ_NVIC_SYSTICK_بارول_REG = ulTimerCountsForOneTick - 1UL;
                پورټ_NVIC_SYSTICK_CTRL_REG = پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG | پورټ_NVIC_SYSTICK_INT_بټ | پورټ_NVIC_SYSTICK_ENABLE_بټ;
            }
            #د_که_پای /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_ګام_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __enable_interrupt();
        }
    }

#د_که_پای /* configUSE_TICKLESS_IDLE */
