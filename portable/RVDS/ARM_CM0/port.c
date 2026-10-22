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

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* Constants required to manipulate the NVIC. */
#تعریف_کن پورت_NVIC_SYSTICK_CTRL_REG             ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#تعریف_کن پورت_NVIC_SYSTICK_بارگیری_REG             ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#تعریف_کن پورت_NVIC_SYSTICK_CURRENT_مقدار_REG    ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#تعریف_کن پورت_NVIC_INT_CTRL_REG                 ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کن پورت_NVIC_SHPR3_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
#تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت              ( 1UL << 2UL )
#تعریف_کن پورت_NVIC_SYSTICK_INT_بیت              ( 1UL << 1UL )
#تعریف_کن پورت_NVIC_SYSTICK_ENABLE_بیت           ( 1UL << 0UL )
#تعریف_کن پورت_NVIC_SYSTICK_شمار_FLAG_بیت       ( 1UL << 16UL )
#تعریف_کن پورت_NVIC_PENDSVSET_بیت                ( 1UL << 28UL )
#تعریف_کن پورت_NVIC_PEND_SYSTICK_مجموعه_بیت         ( 1UL << 26UL )
#تعریف_کن پورت_NVIC_PEND_SYSTICK_CLEAR_بیت       ( 1UL << 25UL )
#تعریف_کن پورت_MIN_وقفه_اولویت            ( 255UL )
#تعریف_کن پورت_NVIC_PENDSV_PRI                   ( پورت_MIN_وقفه_اولویت << 16UL )
#تعریف_کن پورت_NVIC_SYSTICK_PRI                  ( پورت_MIN_وقفه_اولویت << 24UL )

/* Constants required to set up the initial stack. */
#تعریف_کن پورت_INITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#تعریف_کن پورت_MAX_24_بیت_عدد                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#اگر_تعریف_نشده پورت_MISSED_COUNTS_ضریب
    #تعریف_کن پورت_MISSED_COUNTS_ضریب    ( 94UL )
#پایان_اگر

/* Constants used with memory barrier intrinsics. */
#تعریف_کن پورت_SY_پر_READ_WRITE    ( 15 )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#اگر_تعریف_نشده configSYSTICK_CLOCK_HZ
    #تعریف_کن configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت_CONFIG    ( پورت_NVIC_SYSTICK_CLK_بیت )
#وإلا
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت_CONFIG    ( 0 )
#پایان_اگر

/* Legacy macro for backward compatibility only.  This macro used to be used to
 * replace the function that configures the clock used to generate the tick
 * interrupt (prvSetupTimerInterrupt()), but now the function is declared weak so
 * the application writer can override it by simply defining a function of the
 * same name (vApplicationSetupTickInterrupt()). */
#اگر_تعریف_نشده configOVERRIDE_DEFAULT_TICK_CONFIGURATION
    #تعریف_کن configOVERRIDE_DEFAULT_TICK_CONFIGURATION    0
#پایان_اگر

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساكن UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/* The number of SysTick increments that make up one tick period. */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulTimerCountsForOneTick = 0;
#پایان_اگر /* configUSE_TICKLESS_IDLE */

/* The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer. */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t x_بیشینه_Possible_Suppressed_Ticks = 0;
#پایان_اگر /* configUSE_TICKLESS_IDLE */

/* Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulStoppedTimerCompensation = 0;
#پایان_اگر /* configUSE_TICKLESS_IDLE */

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ );

/*
 * Exception handlers.
 */
فراغ x_پورت_Pend_SVHandler( فراغ );
فراغ x_پورت_Sys_Tick_Handler( فراغ );
فراغ v_پورت_SVCHandler( فراغ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ساكن فراغ prv_پورت_شروع_اولی_Task( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_بالاترین_از_پشته--;                                   /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_بالاترین_از_پشته = پورت_INITIAL_XPSR;                 /* xPSR */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد;           /* PC */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) prvTaskExitError; /* LR */
    px_بالاترین_از_پشته -= 5;                                /* R12, R3, R2 and R1. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters;     /* R0 */
    px_بالاترین_از_پشته -= 8;                                /* R11..R4. */

    أرجع px_بالاترین_از_پشته;
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
    پورت_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورت_SVCHandler( فراغ )
{
    /* This function is no longer used, but retained for backward
     * compatibility. */
}
/*-----------------------------------------------------------*/

__asm فراغ prv_پورت_شروع_اولی_Task( فراغ )
{
    خارجي pxCurrentTCB;

    PRESERVE8

    /* The MSP stack is not reset as, unlike on M3/4 parts, there is no vector
     * table offset register that can be used to locate the initial stack value.
     * Not all M0 parts have the application vector table at address 0. */
/* *INDENT-OFF* */

    ldr r3, = pxCurrentTCB /* Obtain location of pxCurrentTCB. */
    ldr r1, [ r3 ]
    ldr r0, [ r1 ]         /* The first item in pxCurrentTCB is the task top of stack. */
    adds r0, # 32          /* Discard everything up to r0. */
    msr psp, r0            /* This is now the new top of stack to use in the task. */
    movs r0, # 2           /* Switch to the psp stack. */
    msr CONTROL, r0
    isb
    برداشت { r0 - r5 } /* Pop the registers that are saved automatically. */
    mov lr, r5 /* lr is now in r5. */
    برداشت { r3 } /* The return address is now in r3. */
    برداشت { r2 } /* Pop and discard the XPSR. */
    cpsie i /* The first task has its context and interrupts can be enabled. */
    bx r3 /* Finally, jump to the user defined task code. */

    ALIGN
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
    پورت_NVIC_SHPR3_REG |= پورت_NVIC_PENDSV_PRI;

    پورت_NVIC_SHPR3_REG |= پورت_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_پورت_راهاندازی_Timer_وقفه();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    prv_پورت_شروع_اولی_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Yield( فراغ )
{
    /* Set a PendSV to request a context switch. */
    پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __dsb( پورت_SY_پر_READ_WRITE );
    __isb( پورت_SY_پر_READ_WRITE );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Enter_Critical( فراغ )
{
    پورت_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
    __dsb( پورت_SY_پر_READ_WRITE );
    __isb( پورت_SY_پر_READ_WRITE );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Exit_Critical( فراغ )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    إذا( uxCriticalNesting == 0 )
    {
        پورت_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

__asm uint32_t ul_مجموعه_وقفه_ماسک_From_ISR( فراغ )
{
/* *INDENT-OFF* */
    mrs r0, PRIMASK
    cpsid i
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

__asm فراغ v_Clear_وقفه_ماسک_From_ISR( uint32_t ul_ماسک )
{
/* *INDENT-OFF* */
    msr PRIMASK, r0
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

__asm فراغ x_پورت_Pend_SVHandler( فراغ )
{
    خارجي vTaskSwitchContext
    خارجي pxCurrentTCB

/* *INDENT-OFF* */
    PRESERVE8

    mrs r0, psp

    ldr r3, = pxCurrentTCB /* Get the location of the current TCB. */
    ldr r2, [ r3 ]

    subs r0, # 32  /* Make space for the remaining low registers. */
    str r0, [ r2 ] /* Save the new top of stack. */
    stmia r0 !, { r4 - r7 } /* Store the low registers that are not saved automatically. */
    mov r4, r8 /* Store the high registers. */
    mov r5, r9
    mov r6, r10
    mov r7, r11
    stmia r0 !, { r4 - r7 }

    افزودن { r3, r14 }
    cpsid i
    bl vTaskSwitchContext
    cpsie i
    برداشت { r2, r3 } /* lr goes in r3. r2 now holds tcb pointer. */

    ldr r1, [ r2 ]
    ldr r0, [ r1 ] /* The first item in pxCurrentTCB is the task top of stack. */
    adds r0, # 16  /* Move to the high registers. */
    ldmia r0 !, { r4 - r7 } /* Pop the high registers. */
    mov r8, r4
    mov r9, r5
    mov r10, r6
    mov r11, r7

    msr psp, r0   /* Remember the new top of stack for the task. */

    subs r0, # 32 /* Go back for the low registers that are not automatically restored. */
    ldmia r0 !, { r4 - r7 } /* Pop low registers.  */

    bx r3
    ALIGN
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

فراغ x_پورت_Sys_Tick_Handler( فراغ )
{
    uint32_t ul_قبلی_ماسک;

    ul_قبلی_ماسک = پورت_مجموعه_وقفه_ماسک_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_مقصد_SCHEDULER();
            /* Pend a context switch. */
            پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورت_CLEAR_وقفه_ماسک_FROM_ISR( ul_قبلی_ماسک );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
#إذا ( configOVERRIDE_DEFAULT_TICK_CONFIGURATION == 0 )

    __weak فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ )
    {
        /* Calculate the constants required to configure the tick interrupt. */
        #إذا ( configUSE_TICKLESS_IDLE == 1 )
        {
            ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_نرخ_HZ );
            x_بیشینه_Possible_Suppressed_Ticks = پورت_MAX_24_بیت_عدد / ulTimerCountsForOneTick;
            ulStoppedTimerCompensation = پورت_MISSED_COUNTS_ضریب / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
        }
        #پایان_اگر /* configUSE_TICKLESS_IDLE */

        /* Stop and clear the SysTick. */
        پورت_NVIC_SYSTICK_CTRL_REG = 0UL;
        پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;

        /* Configure SysTick to interrupt at the requested rate. */
        پورت_NVIC_SYSTICK_بارگیری_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_نرخ_HZ ) - 1UL;
        پورت_NVIC_SYSTICK_CTRL_REG = ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت | پورت_NVIC_SYSTICK_ENABLE_بیت );
    }

#پایان_اگر /* configOVERRIDE_DEFAULT_TICK_CONFIGURATION */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    __weak فراغ v_پورت_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_زمان )
    {
        uint32_t ul_Reload_مقدار, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_چپ;
        TickType_t x_Modifiable_Idle_زمان;

        /* Make sure the SysTick reload value does not overflow the counter. */
        إذا( x_Expected_Idle_زمان > x_بیشینه_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_زمان = x_بیشینه_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __disable_irq();
        __dsb( پورت_SY_پر_READ_WRITE );
        __isb( پورت_SY_پر_READ_WRITE );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_نما_وضعیت() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the __disable_irq()
             * call above. */
            __enable_irq();
        }
        وإلا
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            پورت_NVIC_SYSTICK_CTRL_REG = ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_چپ = پورت_NVIC_SYSTICK_CURRENT_مقدار_REG;

            إذا( ul_Sys_Tick_Decrements_چپ == 0 )
            {
                ul_Sys_Tick_Decrements_چپ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_مقدار = ul_Sys_Tick_Decrements_چپ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_زمان - 1UL ) );

            إذا( ( پورت_NVIC_INT_CTRL_REG & پورت_NVIC_PEND_SYSTICK_مجموعه_بیت ) != 0 )
            {
                پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PEND_SYSTICK_CLEAR_بیت;
                ul_Reload_مقدار -= ulTimerCountsForOneTick;
            }

            إذا( ul_Reload_مقدار > ulStoppedTimerCompensation )
            {
                ul_Reload_مقدار -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            پورت_NVIC_SYSTICK_بارگیری_REG = ul_Reload_مقدار;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;

            /* Restart SysTick. */
            پورت_NVIC_SYSTICK_CTRL_REG |= پورت_NVIC_SYSTICK_ENABLE_بیت;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_زمان = x_Expected_Idle_زمان;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_زمان );

            إذا( x_Modifiable_Idle_زمان > 0 )
            {
                __dsb( پورت_SY_پر_READ_WRITE );
                __wfi();
                __isb( پورت_SY_پر_READ_WRITE );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_زمان );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the __disable_irq() call above. */
            __enable_irq();
            __dsb( پورت_SY_پر_READ_WRITE );
            __isb( پورت_SY_پر_READ_WRITE );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __disable_irq();
            __dsb( پورت_SY_پر_READ_WRITE );
            __isb( پورت_SY_پر_READ_WRITE );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            پورت_NVIC_SYSTICK_CTRL_REG = ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت );

            /* Determine whether the SysTick has already counted to zero. */
            إذا( ( پورت_NVIC_SYSTICK_CTRL_REG & پورت_NVIC_SYSTICK_شمار_FLAG_بیت ) != 0 )
            {
                uint32_t ul_Calculated_بارگیری_مقدار;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_بارگیری_مقدار = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_مقدار - پورت_NVIC_SYSTICK_CURRENT_مقدار_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                إذا( ( ul_Calculated_بارگیری_مقدار <= ulStoppedTimerCompensation ) || ( ul_Calculated_بارگیری_مقدار > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_بارگیری_مقدار = ( ulTimerCountsForOneTick - 1UL );
                }

                پورت_NVIC_SYSTICK_بارگیری_REG = ul_Calculated_بارگیری_مقدار;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_زمان - 1UL;
            }
            وإلا
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_چپ = پورت_NVIC_SYSTICK_CURRENT_مقدار_REG;
                #إذا ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG != پورت_NVIC_SYSTICK_CLK_بیت )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    إذا( ul_Sys_Tick_Decrements_چپ == 0 )
                    {
                        ul_Sys_Tick_Decrements_چپ = ul_Reload_مقدار;
                    }
                }
                #پایان_اگر /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_زمان * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_چپ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورت_NVIC_SYSTICK_بارگیری_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;
            پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت | پورت_NVIC_SYSTICK_INT_بیت | پورت_NVIC_SYSTICK_ENABLE_بیت;
            #إذا ( پورت_NVIC_SYSTICK_CLK_بیت_CONFIG == پورت_NVIC_SYSTICK_CLK_بیت )
            {
                پورت_NVIC_SYSTICK_بارگیری_REG = ulTimerCountsForOneTick - 1UL;
            }
            #وإلا
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت | پورت_NVIC_SYSTICK_INT_بیت;

                إذا( ( پورت_NVIC_SYSTICK_CTRL_REG & پورت_NVIC_SYSTICK_شمار_FLAG_بیت ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0;
                }

                پورت_NVIC_SYSTICK_بارگیری_REG = ulTimerCountsForOneTick - 1UL;
                پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت | پورت_NVIC_SYSTICK_ENABLE_بیت;
            }
            #پایان_اگر /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_گام_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __enable_irq();
        }
    }

#پایان_اگر /* #if configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/
