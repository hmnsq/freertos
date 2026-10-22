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
#شامل "FreeRTOS.h"
#شامل "task.h"

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
#تعریف_کرو پورٹ_NVIC_PEND_SYSTICK_سیٹ_ثنائی_ہندسہ         ( 1UL << 26UL )
#تعریف_کرو پورٹ_NVIC_PEND_SYSTICK_CLEAR_ثنائی_ہندسہ       ( 1UL << 25UL )
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
    #تعریف_کرو پورٹ_MISSED_COUNTS_ضربی_عدد    ( 94UL )
#اگر_ختم

/* Constants used with memory barrier intrinsics. */
#تعریف_کرو پورٹ_SY_بھرا_READ_WRITE    ( 15 )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#اگر_غیر_تعریف_شدہ configSYSTICK_CLOCK_HZ
    #تعریف_کرو configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG    ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ )
#ورنہ
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG    ( 0 )
#اگر_ختم

/* Legacy macro for backward compatibility only.  This macro used to be used to
 * replace the function that configures the clock used to generate the tick
 * interrupt (prvSetupTimerInterrupt()), but now the function is declared weak so
 * the application writer can override it by simply defining a function of the
 * same name (vApplicationSetupTickInterrupt()). */
#اگر_غیر_تعریف_شدہ configOVERRIDE_DEFAULT_TICK_CONFIGURATION
    #تعریف_کرو configOVERRIDE_DEFAULT_TICK_CONFIGURATION    0
#اگر_ختم

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساکن UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/* The number of SysTick increments that make up one tick period. */
#اگر ( configUSE_TICKLESS_IDLE == 1 )
    ساکن uint32_t ulTimerCountsForOneTick = 0;
#اگر_ختم /* configUSE_TICKLESS_IDLE */

/* The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer. */
#اگر ( configUSE_TICKLESS_IDLE == 1 )
    ساکن uint32_t x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks = 0;
#اگر_ختم /* configUSE_TICKLESS_IDLE */

/* Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#اگر ( configUSE_TICKLESS_IDLE == 1 )
    ساکن uint32_t ulStoppedTimerCompensation = 0;
#اگر_ختم /* configUSE_TICKLESS_IDLE */

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
خالی v_پورٹ_تیاری_Timer_مداخلت( خالی );

/*
 * Exception handlers.
 */
خالی x_پورٹ_Pend_SVHandler( خالی );
خالی x_پورٹ_Sys_Tick_Handler( خالی );
خالی v_پورٹ_SVCHandler( خالی );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ساکن خالی prv_پورٹ_آغاز_پہلا_Task( خالی );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساکن خالی prvTaskExitError( خالی );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_چوٹی_کا_ڈھیر--;                                   /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_XPSR;                 /* xPSR */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;           /* PC */
    px_چوٹی_کا_ڈھیر--;
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) prvTaskExitError; /* LR */
    px_چوٹی_کا_ڈھیر -= 5;                                /* R12, R3, R2 and R1. */
    *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;     /* R0 */
    px_چوٹی_کا_ڈھیر -= 8;                                /* R11..R4. */

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

ساکن خالی prvTaskExitError( خالی )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    پورٹ_DISABLE_INTERRUPTS();

    برائے( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_SVCHandler( خالی )
{
    /* This function is no longer used, but retained for backward
     * compatibility. */
}
/*-----------------------------------------------------------*/

__asm خالی prv_پورٹ_آغاز_پہلا_Task( خالی )
{
    خارجی pxCurrentTCB;

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
    نکالو { r0 - r5 } /* Pop the registers that are saved automatically. */
    mov lr, r5 /* lr is now in r5. */
    نکالو { r3 } /* The return address is now in r3. */
    نکالو { r2 } /* Pop and discard the XPSR. */
    cpsie i /* The first task has its context and interrupts can be enabled. */
    bx r3 /* Finally, jump to the user defined task code. */

    ALIGN
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_PENDSV_PRI;

    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_پورٹ_تیاری_Timer_مداخلت();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    prv_پورٹ_آغاز_پہلا_Task();

    /* Should not get here! */
    واپس 0;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Yield( خالی )
{
    /* Set a PendSV to request a context switch. */
    پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __dsb( پورٹ_SY_بھرا_READ_WRITE );
    __isb( پورٹ_SY_بھرا_READ_WRITE );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Enter_Critical( خالی )
{
    پورٹ_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
    __dsb( پورٹ_SY_بھرا_READ_WRITE );
    __isb( پورٹ_SY_بھرا_READ_WRITE );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Exit_Critical( خالی )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    اگر( uxCriticalNesting == 0 )
    {
        پورٹ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

__asm uint32_t ul_سیٹ_مداخلت_نقاب_From_ISR( خالی )
{
/* *INDENT-OFF* */
    mrs r0, PRIMASK
    cpsid i
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

__asm خالی v_Clear_مداخلت_نقاب_From_ISR( uint32_t ul_نقاب )
{
/* *INDENT-OFF* */
    msr PRIMASK, r0
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

__asm خالی x_پورٹ_Pend_SVHandler( خالی )
{
    خارجی vTaskSwitchContext
    خارجی pxCurrentTCB

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

    ڈالو { r3, r14 }
    cpsid i
    bl vTaskSwitchContext
    cpsie i
    نکالو { r2, r3 } /* lr goes in r3. r2 now holds tcb pointer. */

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

خالی x_پورٹ_Sys_Tick_Handler( خالی )
{
    uint32_t ul_پچھلا_نقاب;

    ul_پچھلا_نقاب = پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR();
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
    پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( ul_پچھلا_نقاب );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
#اگر ( configOVERRIDE_DEFAULT_TICK_CONFIGURATION == 0 )

    __weak خالی v_پورٹ_تیاری_Timer_مداخلت( خالی )
    {
        /* Calculate the constants required to configure the tick interrupt. */
        #اگر ( configUSE_TICKLESS_IDLE == 1 )
        {
            ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ );
            x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks = پورٹ_MAX_24_ثنائی_ہندسہ_نمبر / ulTimerCountsForOneTick;
            ulStoppedTimerCompensation = پورٹ_MISSED_COUNTS_ضربی_عدد / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
        }
        #اگر_ختم /* configUSE_TICKLESS_IDLE */

        /* Stop and clear the SysTick. */
        پورٹ_NVIC_SYSTICK_CTRL_REG = 0UL;
        پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

        /* Configure SysTick to interrupt at the requested rate. */
        پورٹ_NVIC_SYSTICK_بھرو_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
        پورٹ_NVIC_SYSTICK_CTRL_REG = ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ );
    }

#اگر_ختم /* configOVERRIDE_DEFAULT_TICK_CONFIGURATION */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TICKLESS_IDLE == 1 )

    __weak خالی v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت )
    {
        uint32_t ul_Reload_قدر, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_بایاں;
        TickType_t x_Modifiable_Idle_وقت;

        /* Make sure the SysTick reload value does not overflow the counter. */
        اگر( x_Expected_Idle_وقت > x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_وقت = x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __disable_irq();
        __dsb( پورٹ_SY_بھرا_READ_WRITE );
        __isb( پورٹ_SY_بھرا_READ_WRITE );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        اگر( e_Task_Confirm_Sleep_منوال_حالت() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the __disable_irq()
             * call above. */
            __enable_irq();
        }
        ورنہ
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            پورٹ_NVIC_SYSTICK_CTRL_REG = ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_بایاں = پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG;

            اگر( ul_Sys_Tick_Decrements_بایاں == 0 )
            {
                ul_Sys_Tick_Decrements_بایاں = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_قدر = ul_Sys_Tick_Decrements_بایاں + ( ulTimerCountsForOneTick * ( x_Expected_Idle_وقت - 1UL ) );

            اگر( ( پورٹ_NVIC_INT_CTRL_REG & پورٹ_NVIC_PEND_SYSTICK_سیٹ_ثنائی_ہندسہ ) != 0 )
            {
                پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PEND_SYSTICK_CLEAR_ثنائی_ہندسہ;
                ul_Reload_قدر -= ulTimerCountsForOneTick;
            }

            اگر( ul_Reload_قدر > ulStoppedTimerCompensation )
            {
                ul_Reload_قدر -= ulStoppedTimerCompensation;
            }

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
                __dsb( پورٹ_SY_بھرا_READ_WRITE );
                __wfi();
                __isb( پورٹ_SY_بھرا_READ_WRITE );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_وقت );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the __disable_irq() call above. */
            __enable_irq();
            __dsb( پورٹ_SY_بھرا_READ_WRITE );
            __isb( پورٹ_SY_بھرا_READ_WRITE );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __disable_irq();
            __dsb( پورٹ_SY_بھرا_READ_WRITE );
            __isb( پورٹ_SY_بھرا_READ_WRITE );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            پورٹ_NVIC_SYSTICK_CTRL_REG = ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ );

            /* Determine whether the SysTick has already counted to zero. */
            اگر( ( پورٹ_NVIC_SYSTICK_CTRL_REG & پورٹ_NVIC_SYSTICK_گنتی_FLAG_ثنائی_ہندسہ ) != 0 )
            {
                uint32_t ul_Calculated_بھرو_قدر;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_بھرو_قدر = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_قدر - پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                اگر( ( ul_Calculated_بھرو_قدر <= ulStoppedTimerCompensation ) || ( ul_Calculated_بھرو_قدر > ulTimerCountsForOneTick ) )
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
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_بایاں = پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG;
                #اگر ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG != پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    اگر( ul_Sys_Tick_Decrements_بایاں == 0 )
                    {
                        ul_Sys_Tick_Decrements_بایاں = ul_Reload_قدر;
                    }
                }
                #اگر_ختم /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_وقت * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_بایاں;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورٹ_NVIC_SYSTICK_بھرو_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;
            پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;
            #اگر ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG == پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ )
            {
                پورٹ_NVIC_SYSTICK_بھرو_REG = ulTimerCountsForOneTick - 1UL;
            }
            #ورنہ
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ;

                اگر( ( پورٹ_NVIC_SYSTICK_CTRL_REG & پورٹ_NVIC_SYSTICK_گنتی_FLAG_ثنائی_ہندسہ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0;
                }

                پورٹ_NVIC_SYSTICK_بھرو_REG = ulTimerCountsForOneTick - 1UL;
                پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;
            }
            #اگر_ختم /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_قدم_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __enable_irq();
        }
    }

#اگر_ختم /* #if configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/
