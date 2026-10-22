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
#ਅਨ੍ਤਰ੍ਭਾਵ "intrinsics.h"

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* Prototype of all Interrupt Service Routines (ISRs). */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ ( * ਪੋਰਟ_ISR_t )( ਖਾਲੀ );

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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PEND_SYSTICK_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ         ( 1UL << 26UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PEND_SYSTICK_CLEAR_ਦੋਆਧਾਰੀ_ਅੰਕ       ( 1UL << 25UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ            ( 255UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSV_PRI                   ( ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_PRI                  ( ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ << 24UL )

/* Constants used to check the installation of the FreeRTOS interrupt handlers. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCB_VTOR_REG                      ( *( ( ਪੋਰਟ_ISR_t ** ) 0xe000ed08 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_PENDSV               ( 14 )

/* Constants required to set up the initial stack. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_XPSR                      ( 0x01000000 )

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ਸਥਿਰ UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/* The systick is a 24-bit counter. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_24_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੰਖਿਆ    ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_MISSED_COUNTS_ਗੁਣਕ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MISSED_COUNTS_ਗੁਣਕ    ( 94UL )
#ਜੇ_ਅੰਤ

/* The number of SysTick increments that make up one tick period. */
#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )
    ਸਥਿਰ uint32_t ulTimerCountsForOneTick = 0;
#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

/* The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer. */
#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )
    ਸਥਿਰ uint32_t x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks = 0;
#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

/* Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only. */
#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )
    ਸਥਿਰ uint32_t ulStoppedTimerCompensation = 0;
#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configSYSTICK_CLOCK_HZ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG    ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ )
#ਨਹੀਂਤਾਂ
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG    ( 0 )
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
ਖਾਲੀ x_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

/*
 * FreeRTOS handlers implemented in assembly.
 */
ਬਾਹਰੀ ਖਾਲੀ x_ਪੋਰਟ_Pend_SVHandler( ਖਾਲੀ );
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;                                   /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_XPSR;                 /* xPSR */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;           /* PC */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) prvTaskExitError; /* LR */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 5;                                /* R12, R3, R2 and R1. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;     /* R0 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 8;                                /* R11..R4. */

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    ਲਈ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
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
    #ਜੇ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        /* Point pxVectorTable to the interrupt vector table. Systems without
         * a VTOR register provide the value zero in the VTOR register and
         * the vector table itself is located at the address 0x00000000. */
        ਅਚਲ ਪੋਰਟ_ISR_t * ਅਚਲ px_ਸਦਿਸ਼_ਸਾਰਣੀ = ਪੋਰਟ_SCB_VTOR_REG;

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
        configASSERT( px_ਸਦਿਸ਼_ਸਾਰਣੀ[ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_PENDSV ] == x_ਪੋਰਟ_Pend_SVHandler );
    }
    #ਜੇ_ਅੰਤ /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts. */
    ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_PENDSV_PRI;
    ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should not get here! */
    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ )
{
    /* Set a PendSV to request a context switch. */
    ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    ਪੋਰਟ_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
    __DSB();
    __ISB();
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    ਜੇ( uxCriticalNesting == 0 )
    {
        ਪੋਰਟ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ x_ਪੋਰਟ_Sys_Tick_Handler( ਖਾਲੀ )
{
    uint32_t ul_ਪਿਛਲਾ_ਨਕਾਬ;

    ul_ਪਿਛਲਾ_ਨਕਾਬ = ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();
            /* Pend a context switch. */
            ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET;
        }
        ਨਹੀਂਤਾਂ
        {
            traceISR_EXIT();
        }
    }
    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ul_ਪਿਛਲਾ_ਨਕਾਬ );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__weak ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    /* Calculate the constants required to configure the tick interrupt. */
    #ਜੇ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_ਦਰ_HZ );
        x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks = ਪੋਰਟ_MAX_24_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੰਖਿਆ / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = ਪੋਰਟ_MISSED_COUNTS_ਗੁਣਕ / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

    /* Stop and reset the SysTick. */
    ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = 0UL;
    ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_ਦਰ_HZ ) - 1UL;
    ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ );
}
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )

    __weak ਖਾਲੀ v_ਪੋਰਟ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ਸਮਾਂ )
    {
        uint32_t ul_Reload_ਮੁੱਲ, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ਖੱਬਾ;
        TickType_t x_Modifiable_Idle_ਸਮਾਂ;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ਜੇ( x_Expected_Idle_ਸਮਾਂ > x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ਸਮਾਂ = x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __disable_interrupt();
        __DSB();
        __ISB();

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ਜੇ( e_Task_Confirm_Sleep_ਬਹੁਲਕ_ਸਥਿਤੀ() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the __disable_interrupt()
             * call above. */
            __enable_interrupt();
        }
        ਨਹੀਂਤਾਂ
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_ਖੱਬਾ = ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG;

            ਜੇ( ul_Sys_Tick_Decrements_ਖੱਬਾ == 0 )
            {
                ul_Sys_Tick_Decrements_ਖੱਬਾ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_ਮੁੱਲ = ul_Sys_Tick_Decrements_ਖੱਬਾ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_ਸਮਾਂ - 1UL ) );

            ਜੇ( ( ਪੋਰਟ_NVIC_INT_CTRL_REG & ਪੋਰਟ_NVIC_PEND_SYSTICK_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ ) != 0 )
            {
                ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PEND_SYSTICK_CLEAR_ਦੋਆਧਾਰੀ_ਅੰਕ;
                ul_Reload_ਮੁੱਲ -= ulTimerCountsForOneTick;
            }

            ਜੇ( ul_Reload_ਮੁੱਲ > ulStoppedTimerCompensation )
            {
                ul_Reload_ਮੁੱਲ -= ulStoppedTimerCompensation;
            }

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
                __DSB();
                __WFI();
                __ISB();
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_ਸਮਾਂ );

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
            ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ );

            /* Determine whether the SysTick has already counted to zero. */
            ਜੇ( ( ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG & ਪੋਰਟ_NVIC_SYSTICK_ਗਿਣਤੀ_FLAG_ਦੋਆਧਾਰੀ_ਅੰਕ ) != 0 )
            {
                uint32_t ul_Calculated_ਲੱਦੋ_ਮੁੱਲ;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_ਲੱਦੋ_ਮੁੱਲ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_ਮੁੱਲ - ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                ਜੇ( ( ul_Calculated_ਲੱਦੋ_ਮੁੱਲ <= ulStoppedTimerCompensation ) || ( ul_Calculated_ਲੱਦੋ_ਮੁੱਲ > ulTimerCountsForOneTick ) )
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
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ਖੱਬਾ = ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG;
                #ਜੇ ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG != ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    ਜੇ( ul_Sys_Tick_Decrements_ਖੱਬਾ == 0 )
                    {
                        ul_Sys_Tick_Decrements_ਖੱਬਾ = ul_Reload_ਮੁੱਲ;
                    }
                }
                #ਜੇ_ਅੰਤ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_ਸਮਾਂ * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ਖੱਬਾ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0UL;
            ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;
            #ਜੇ ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG == ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ )
            {
                ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ulTimerCountsForOneTick - 1UL;
            }
            #ਨਹੀਂਤਾਂ
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ;

                ਜੇ( ( ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG & ਪੋਰਟ_NVIC_SYSTICK_ਗਿਣਤੀ_FLAG_ਦੋਆਧਾਰੀ_ਅੰਕ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0;
                }

                ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ulTimerCountsForOneTick - 1UL;
                ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;
            }
            #ਜੇ_ਅੰਤ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_ਕਦਮ_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __enable_interrupt();
        }
    }

#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */
