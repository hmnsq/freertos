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
#وصف_ڪريو پورٽ_NVIC_SYSTICK_CTRL_REG             ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_ڀريو_REG             ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG    ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#وصف_ڪريو پورٽ_NVIC_INT_CTRL_REG                 ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#وصف_ڪريو پورٽ_NVIC_SHPR3_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ              ( 1UL << 2UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_INT_ٻٽو_انگ              ( 1UL << 1UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_ENABLE_ٻٽو_انگ           ( 1UL << 0UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_ڳڻپ_FLAG_ٻٽو_انگ       ( 1UL << 16UL )
#وصف_ڪريو پورٽ_NVIC_PENDSVSET_ٻٽو_انگ                ( 1UL << 28UL )
#وصف_ڪريو پورٽ_NVIC_PEND_SYSTICK_سيٽ_ٻٽو_انگ         ( 1UL << 26UL )
#وصف_ڪريو پورٽ_NVIC_PEND_SYSTICK_CLEAR_ٻٽو_انگ       ( 1UL << 25UL )
#وصف_ڪريو پورٽ_MIN_مداخلت_ترجيح            ( 255UL )
#وصف_ڪريو پورٽ_NVIC_PENDSV_PRI                   ( پورٽ_MIN_مداخلت_ترجيح << 16UL )
#وصف_ڪريو پورٽ_NVIC_SYSTICK_PRI                  ( پورٽ_MIN_مداخلت_ترجيح << 24UL )

/* Constants required to set up the initial stack. */
#وصف_ڪريو پورٽ_INITIAL_XPSR                      ( 0x01000000 )

/* The systick is a 24-bit counter. */
#وصف_ڪريو پورٽ_MAX_24_ٻٽو_انگ_عدد                 ( 0xffffffUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
 * occurred while the SysTick counter is stopped during tickless idle
 * calculations. */
#جيڪڏهن_وصف_نه_ٿيل پورٽ_MISSED_COUNTS_ضرب_ڪندڙ
    #وصف_ڪريو پورٽ_MISSED_COUNTS_ضرب_ڪندڙ    ( 94UL )
#جيڪڏهن_پورو

/* Constants used with memory barrier intrinsics. */
#وصف_ڪريو پورٽ_SY_ڀريل_READ_WRITE    ( 15 )

/* Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register. */
#جيڪڏهن_وصف_نه_ٿيل configSYSTICK_CLOCK_HZ
    #وصف_ڪريو configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #وصف_ڪريو پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ_CONFIG    ( پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ )
#وإلا
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #وصف_ڪريو پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ_CONFIG    ( 0 )
#جيڪڏهن_پورو

/* Legacy macro for backward compatibility only.  This macro used to be used to
 * replace the function that configures the clock used to generate the tick
 * interrupt (prvSetupTimerInterrupt()), but now the function is declared weak so
 * the application writer can override it by simply defining a function of the
 * same name (vApplicationSetupTickInterrupt()). */
#جيڪڏهن_وصف_نه_ٿيل configOVERRIDE_DEFAULT_TICK_CONFIGURATION
    #وصف_ڪريو configOVERRIDE_DEFAULT_TICK_CONFIGURATION    0
#جيڪڏهن_پورو

/* Each task maintains its own interrupt status in the critical nesting
 * variable. */
ساكن UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/* The number of SysTick increments that make up one tick period. */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulTimerCountsForOneTick = 0;
#جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */

/* The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer. */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t x_وڌ_کان_وڌ_Possible_Suppressed_Ticks = 0;
#جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */

/* Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#إذا ( configUSE_TICKLESS_IDLE == 1 )
    ساكن uint32_t ulStoppedTimerCompensation = 0;
#جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
فراغ v_پورٽ_تياري_Timer_مداخلت( فراغ );

/*
 * Exception handlers.
 */
فراغ x_پورٽ_Pend_SVHandler( فراغ );
فراغ x_پورٽ_Sys_Tick_Handler( فراغ );
فراغ v_پورٽ_SVCHandler( فراغ );

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
ساكن فراغ prv_پورٽ_شروعات_پهريون_Task( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /* Simulate the stack frame as it would be created by a context switch
     * interrupt. */
    px_چوٽي_جو_ڍير--;                                   /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
    *px_چوٽي_جو_ڍير = پورٽ_INITIAL_XPSR;                 /* xPSR */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ;           /* PC */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) prvTaskExitError; /* LR */
    px_چوٽي_جو_ڍير -= 5;                                /* R12, R3, R2 and R1. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters;     /* R0 */
    px_چوٽي_جو_ڍير -= 8;                                /* R11..R4. */

    أرجع px_چوٽي_جو_ڍير;
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
    پورٽ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_SVCHandler( فراغ )
{
    /* This function is no longer used, but retained for backward
     * compatibility. */
}
/*-----------------------------------------------------------*/

__asm فراغ prv_پورٽ_شروعات_پهريون_Task( فراغ )
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
    ڪڍو { r0 - r5 } /* Pop the registers that are saved automatically. */
    mov lr, r5 /* lr is now in r5. */
    ڪڍو { r3 } /* The return address is now in r3. */
    ڪڍو { r2 } /* Pop and discard the XPSR. */
    cpsie i /* The first task has its context and interrupts can be enabled. */
    bx r3 /* Finally, jump to the user defined task code. */

    ALIGN
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    /* Make PendSV, CallSV and SysTick the same priority as the kernel. */
    پورٽ_NVIC_SHPR3_REG |= پورٽ_NVIC_PENDSV_PRI;

    پورٽ_NVIC_SHPR3_REG |= پورٽ_NVIC_SYSTICK_PRI;

    /* Start the timer that generates the tick ISR.  Interrupts are disabled
     * here already. */
    v_پورٽ_تياري_Timer_مداخلت();

    /* Initialise the critical nesting count ready for the first task. */
    uxCriticalNesting = 0;

    /* Start the first task. */
    prv_پورٽ_شروعات_پهريون_Task();

    /* Should not get here! */
    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Yield( فراغ )
{
    /* Set a PendSV to request a context switch. */
    پورٽ_NVIC_INT_CTRL_REG = پورٽ_NVIC_PENDSVSET_ٻٽو_انگ;

    /* Barriers are normally not required but do ensure the code is completely
     * within the specified behaviour for the architecture. */
    __dsb( پورٽ_SY_ڀريل_READ_WRITE );
    __isb( پورٽ_SY_ڀريل_READ_WRITE );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enter_Critical( فراغ )
{
    پورٽ_DISABLE_INTERRUPTS();
    uxCriticalNesting++;
    __dsb( پورٽ_SY_ڀريل_READ_WRITE );
    __isb( پورٽ_SY_ڀريل_READ_WRITE );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;

    إذا( uxCriticalNesting == 0 )
    {
        پورٽ_ENABLE_INTERRUPTS();
    }
}
/*-----------------------------------------------------------*/

__asm uint32_t ul_سيٽ_مداخلت_نقاب_From_ISR( فراغ )
{
/* *INDENT-OFF* */
    mrs r0, PRIMASK
    cpsid i
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

__asm فراغ v_Clear_مداخلت_نقاب_From_ISR( uint32_t ul_نقاب )
{
/* *INDENT-OFF* */
    msr PRIMASK, r0
    bx lr
/* *INDENT-ON* */
}
/*-----------------------------------------------------------*/

__asm فراغ x_پورٽ_Pend_SVHandler( فراغ )
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

    ڌڪو { r3, r14 }
    cpsid i
    bl vTaskSwitchContext
    cpsie i
    ڪڍو { r2, r3 } /* lr goes in r3. r2 now holds tcb pointer. */

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

فراغ x_پورٽ_Sys_Tick_Handler( فراغ )
{
    uint32_t ul_اڳيون_نقاب;

    ul_اڳيون_نقاب = پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR();
    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        إذا( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_منزل_SCHEDULER();
            /* Pend a context switch. */
            پورٽ_NVIC_INT_CTRL_REG = پورٽ_NVIC_PENDSVSET_ٻٽو_انگ;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }
    پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( ul_اڳيون_نقاب );
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
#إذا ( configOVERRIDE_DEFAULT_TICK_CONFIGURATION == 0 )

    __weak فراغ v_پورٽ_تياري_Timer_مداخلت( فراغ )
    {
        /* Calculate the constants required to configure the tick interrupt. */
        #إذا ( configUSE_TICKLESS_IDLE == 1 )
        {
            ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ );
            x_وڌ_کان_وڌ_Possible_Suppressed_Ticks = پورٽ_MAX_24_ٻٽو_انگ_عدد / ulTimerCountsForOneTick;
            ulStoppedTimerCompensation = پورٽ_MISSED_COUNTS_ضرب_ڪندڙ / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
        }
        #جيڪڏهن_پورو /* configUSE_TICKLESS_IDLE */

        /* Stop and clear the SysTick. */
        پورٽ_NVIC_SYSTICK_CTRL_REG = 0UL;
        پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

        /* Configure SysTick to interrupt at the requested rate. */
        پورٽ_NVIC_SYSTICK_ڀريو_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
        پورٽ_NVIC_SYSTICK_CTRL_REG = ( پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ_CONFIG | پورٽ_NVIC_SYSTICK_INT_ٻٽو_انگ | پورٽ_NVIC_SYSTICK_ENABLE_ٻٽو_انگ );
    }

#جيڪڏهن_پورو /* configOVERRIDE_DEFAULT_TICK_CONFIGURATION */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    __weak فراغ v_پورٽ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت )
    {
        uint32_t ul_Reload_قدر, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_کاٻو;
        TickType_t x_Modifiable_Idle_وقت;

        /* Make sure the SysTick reload value does not overflow the counter. */
        إذا( x_Expected_Idle_وقت > x_وڌ_کان_وڌ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_وقت = x_وڌ_کان_وڌ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __disable_irq();
        __dsb( پورٽ_SY_ڀريل_READ_WRITE );
        __isb( پورٽ_SY_ڀريل_READ_WRITE );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_گهڻائي_حالت() == eAbortSleep )
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
            پورٽ_NVIC_SYSTICK_CTRL_REG = ( پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ_CONFIG | پورٽ_NVIC_SYSTICK_INT_ٻٽو_انگ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_کاٻو = پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG;

            إذا( ul_Sys_Tick_Decrements_کاٻو == 0 )
            {
                ul_Sys_Tick_Decrements_کاٻو = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_قدر = ul_Sys_Tick_Decrements_کاٻو + ( ulTimerCountsForOneTick * ( x_Expected_Idle_وقت - 1UL ) );

            إذا( ( پورٽ_NVIC_INT_CTRL_REG & پورٽ_NVIC_PEND_SYSTICK_سيٽ_ٻٽو_انگ ) != 0 )
            {
                پورٽ_NVIC_INT_CTRL_REG = پورٽ_NVIC_PEND_SYSTICK_CLEAR_ٻٽو_انگ;
                ul_Reload_قدر -= ulTimerCountsForOneTick;
            }

            إذا( ul_Reload_قدر > ulStoppedTimerCompensation )
            {
                ul_Reload_قدر -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            پورٽ_NVIC_SYSTICK_ڀريو_REG = ul_Reload_قدر;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

            /* Restart SysTick. */
            پورٽ_NVIC_SYSTICK_CTRL_REG |= پورٽ_NVIC_SYSTICK_ENABLE_ٻٽو_انگ;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_وقت = x_Expected_Idle_وقت;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_وقت );

            إذا( x_Modifiable_Idle_وقت > 0 )
            {
                __dsb( پورٽ_SY_ڀريل_READ_WRITE );
                __wfi();
                __isb( پورٽ_SY_ڀريل_READ_WRITE );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_وقت );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the __disable_irq() call above. */
            __enable_irq();
            __dsb( پورٽ_SY_ڀريل_READ_WRITE );
            __isb( پورٽ_SY_ڀريل_READ_WRITE );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __disable_irq();
            __dsb( پورٽ_SY_ڀريل_READ_WRITE );
            __isb( پورٽ_SY_ڀريل_READ_WRITE );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            پورٽ_NVIC_SYSTICK_CTRL_REG = ( پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ_CONFIG | پورٽ_NVIC_SYSTICK_INT_ٻٽو_انگ );

            /* Determine whether the SysTick has already counted to zero. */
            إذا( ( پورٽ_NVIC_SYSTICK_CTRL_REG & پورٽ_NVIC_SYSTICK_ڳڻپ_FLAG_ٻٽو_انگ ) != 0 )
            {
                uint32_t ul_Calculated_ڀريو_قدر;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_ڀريو_قدر = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_قدر - پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                إذا( ( ul_Calculated_ڀريو_قدر <= ulStoppedTimerCompensation ) || ( ul_Calculated_ڀريو_قدر > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_ڀريو_قدر = ( ulTimerCountsForOneTick - 1UL );
                }

                پورٽ_NVIC_SYSTICK_ڀريو_REG = ul_Calculated_ڀريو_قدر;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_وقت - 1UL;
            }
            وإلا
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_کاٻو = پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG;
                #إذا ( پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ_CONFIG != پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    إذا( ul_Sys_Tick_Decrements_کاٻو == 0 )
                    {
                        ul_Sys_Tick_Decrements_کاٻو = ul_Reload_قدر;
                    }
                }
                #جيڪڏهن_پورو /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_وقت * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_کاٻو;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                پورٽ_NVIC_SYSTICK_ڀريو_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;
            پورٽ_NVIC_SYSTICK_CTRL_REG = پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ | پورٽ_NVIC_SYSTICK_INT_ٻٽو_انگ | پورٽ_NVIC_SYSTICK_ENABLE_ٻٽو_انگ;
            #إذا ( پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ_CONFIG == پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ )
            {
                پورٽ_NVIC_SYSTICK_ڀريو_REG = ulTimerCountsForOneTick - 1UL;
            }
            #وإلا
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                پورٽ_NVIC_SYSTICK_CTRL_REG = پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ | پورٽ_NVIC_SYSTICK_INT_ٻٽو_انگ;

                إذا( ( پورٽ_NVIC_SYSTICK_CTRL_REG & پورٽ_NVIC_SYSTICK_ڳڻپ_FLAG_ٻٽو_انگ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    پورٽ_NVIC_SYSTICK_CURRENT_قدر_REG = 0;
                }

                پورٽ_NVIC_SYSTICK_ڀريو_REG = ulTimerCountsForOneTick - 1UL;
                پورٽ_NVIC_SYSTICK_CTRL_REG = پورٽ_NVIC_SYSTICK_CLK_ٻٽو_انگ_CONFIG | پورٽ_NVIC_SYSTICK_INT_ٻٽو_انگ | پورٽ_NVIC_SYSTICK_ENABLE_ٻٽو_انگ;
            }
            #جيڪڏهن_پورو /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_قدم_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __enable_irq();
        }
    }

#جيڪڏهن_پورو /* #if configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/
