/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2025 Arm Limited and/or its affiliates
 * <open-source-office@arm.com>
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

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers. That should only be done when
 * task.h is included from an application file. */
#تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

/* MPU includes. */
#شامل "mpu_wrappers.h"
#شامل "mpu_syscall_numbers.h"

/* Portasm includes. */
#شامل "portasm.h"

#تعریف_منسوخ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
قسمتعریف خالی ( * پورٹ_ISR_t )( خالی );

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#تعریف_کرو پورٹ_NVIC_SYSTICK_CTRL_REG             ( *( ( متلون uint32_t * ) 0xe000e010 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_بھرو_REG             ( *( ( متلون uint32_t * ) 0xe000e014 ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG    ( *( ( متلون uint32_t * ) 0xe000e018 ) )
#تعریف_کرو پورٹ_NVIC_SHPR3_REG                    ( *( ( متلون uint32_t * ) 0xe000ed20 ) )
#تعریف_کرو پورٹ_NVIC_SHPR2_REG                    ( *( ( متلون uint32_t * ) 0xe000ed1c ) )
#تعریف_کرو پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ           ( 1UL << 0UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ              ( 1UL << 1UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ              ( 1UL << 2UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_گنتی_FLAG_ثنائی_ہندسہ       ( 1UL << 16UL )
#تعریف_کرو پورٹ_NVIC_PEND_SYSTICK_CLEAR_ثنائی_ہندسہ       ( 1UL << 25UL )
#تعریف_کرو پورٹ_NVIC_PEND_SYSTICK_سیٹ_ثنائی_ہندسہ         ( 1UL << 26UL )
#تعریف_کرو پورٹ_MIN_مداخلت_ترجیح            ( 255UL )
#تعریف_کرو پورٹ_NVIC_PENDSV_PRI                   ( پورٹ_MIN_مداخلت_ترجیح << 16UL )
#تعریف_کرو پورٹ_NVIC_SYSTICK_PRI                  ( پورٹ_MIN_مداخلت_ترجیح << 24UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#تعریف_کرو پورٹ_SCB_VTOR_REG                      ( *( ( پورٹ_ISR_t ** ) 0xe000ed08 ) )
#تعریف_کرو پورٹ_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( متلون uint32_t * ) 0xe000ed24 ) )
#تعریف_کرو پورٹ_SCB_MEM_FAULT_ENABLE_ثنائی_ہندسہ          ( 1UL << 16UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#تعریف_کرو پورٹ_سمتیہ_اشاریہ_SVC       ( 11 )
#تعریف_کرو پورٹ_سمتیہ_اشاریہ_PENDSV    ( 14 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#تعریف_کرو پورٹ_PSR_ڈھیر_PADDING_نقاب              ( 1UL << 9UL )
#تعریف_کرو پورٹ_EXC_RETURN_ڈھیر_چوکھٹا_TYPE_نقاب    ( 1UL << 4UL )

/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#تعریف_کرو پورٹ_انحراف_مقصد_LR     ( 5 )
#تعریف_کرو پورٹ_انحراف_مقصد_PC     ( 6 )
#تعریف_کرو پورٹ_انحراف_مقصد_PSR    ( 7 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#تعریف_کرو پورٹ_MPU_TYPE_REG                            ( *( ( متلون uint32_t * ) 0xe000ed90 ) )
#تعریف_کرو پورٹ_MPU_CTRL_REG                            ( *( ( متلون uint32_t * ) 0xe000ed94 ) )

#تعریف_کرو پورٹ_MPU_RBAR_REG                            ( *( ( متلون uint32_t * ) 0xe000ed9c ) )
#تعریف_کرو پورٹ_MPU_RASR_REG                            ( *( ( متلون uint32_t * ) 0xe000eda0 ) )

/* MPU Region Attribute and Size Register (RASR) bitmasks. */
#تعریف_کرو پورٹ_MPU_RASR_AP_BITMASK                     ( 0x7UL << 24UL )
#تعریف_کرو پورٹ_MPU_RASR_S_C_B_BITMASK                  ( 0x7UL )
#تعریف_کرو پورٹ_MPU_RASR_S_C_B_LOCATION                 ( 16UL )
#تعریف_کرو پورٹ_MPU_RASR_سائز_BITMASK                   ( 0x1FUL << 1UL )
#تعریف_کرو پورٹ_MPU_RASR_REGION_ENABLE_BITMASK          ( 0x1UL )

/* MPU Region Base Address Register (RBAR) bitmasks. */
#تعریف_کرو پورٹ_MPU_RBAR_پتہ_BITMASK                ( 0xFFFFFF00UL )
#تعریف_کرو پورٹ_MPU_RBAR_REGION_نمبر_VALID_BITMASK    ( 0x1UL << 4UL )
#تعریف_کرو پورٹ_MPU_RBAR_REGION_نمبر_BITMASK          ( 0x0000000FUL )

/* MPU Control Register (MPU_CTRL) bitmasks. */
#تعریف_کرو پورٹ_MPU_CTRL_ENABLE_BITMASK                 ( 0x1UL )
#تعریف_کرو پورٹ_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK ( 0x1UL << 2UL ) /* PRIVDEFENA bit. */

/* Expected value of the portMPU_TYPE register. */
#تعریف_کرو پورٹ_EXPECTED_MPU_TYPE_قدر                 ( 0x8UL << 8UL ) /* 8 DREGION unified. */

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#تعریف_کرو پورٹ_نکالو_پہلا_پتہ_FROM_RBAR( rbar ) \
    ( ( rbar ) & پورٹ_MPU_RBAR_پتہ_BITMASK )

/* Extract size of the MPU region as encoded in the
 * RASR (Region Attribute and Size Register) value. */
#تعریف_کرو پورٹ_نکالو_REGION_سائز_FROM_RASR( rasr ) \
    ( 1 << ( ( ( ( rasr ) & پورٹ_MPU_RASR_سائز_BITMASK ) >> 1 )+ 1 ) )

/* Does addr lies within [start, end] address range? */
#تعریف_کرو پورٹ_IS_پتہ_WITHIN_RANGE( addr, آغاز, انتہا ) \
    ( ( ( addr ) >= ( آغاز ) ) && ( ( addr ) <= ( انتہا ) ) )

/* Is the access request satisfied by the available permissions? */
#تعریف_کرو پورٹ_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#تعریف_کرو پورٹ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کرو پورٹ_جوڑو_UINT32_WILL_حد_سے_تجاوز( a, b )    ( ( a ) > ( پورٹ_UINT32_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#تعریف_کرو پورٹ_MAX_24_ثنائی_ہندسہ_نمبر       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#تعریف_کرو پورٹ_MISSED_COUNTS_ضربی_عدد    ( 94UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#تعریف_کرو پورٹ_INITIAL_XPSR    ( 0x01000000 )

/**
 * @brief Initial EXC_RETURN value.
 *
 *     FF         FF         FF         FD
 * 1111 1111  1111 1111  1111 1111  1111 1101
 *
 * Bit[3] - 1 --> Return to the Thread mode.
 * Bit[2] - 1 --> Restore registers from the process stack.
 * Bit[1] - 0 --> Reserved, 0.
 * Bit[0] - 0 --> Reserved, 1.
 */
#تعریف_کرو پورٹ_INITIAL_EXC_RETURN    ( 0xfffffffdUL )

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#تعریف_کرو پورٹ_CONTROL_PRIVILEGED_نقاب         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#تعریف_کرو پورٹ_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#تعریف_کرو پورٹ_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#اگر_غیر_تعریف_شدہ configSYSTICK_CLOCK_HZ
    #تعریف_کرو configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG    ( پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ )
#ورنہ
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #تعریف_کرو پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG    ( 0 )
#اگر_ختم

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#اگر_تعریف_شدہ config_TASK_RETURN_پتہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    config_TASK_RETURN_پتہ
#ورنہ
    #تعریف_کرو پورٹ_TASK_RETURN_پتہ    prvTaskExitError
#اگر_ختم

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#تعریف_کرو پورٹ_PRELOAD_REGISTERS    1

/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
ساکن خالی prvTaskExitError( خالی );

#اگر ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    ساکن خالی prv_تیاری_MPU( خالی ) PRIVILEGED_FUNCTION;

#اگر_ختم /* configENABLE_MPU */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
خالی v_پورٹ_تیاری_Timer_مداخلت( خالی ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
بنیاد_Type_t x_پورٹ_Is_Inside_مداخلت( خالی );

/**
 * @brief Yield the processor.
 */
خالی v_پورٹ_Yield( خالی ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
خالی v_پورٹ_Enter_Critical( خالی ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
خالی v_پورٹ_Exit_Critical( خالی ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
خالی SysTick_Handler( خالی ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
پورٹ_DONT_DISCARD خالی v_پورٹ_SVCHandler_C( uint32_t * pul_Caller_ڈھیر_پتہ ) PRIVILEGED_FUNCTION;

#اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    خالی vSystemCallEnter( uint32_t * pul_Task_ڈھیر,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_نمبر ) PRIVILEGED_FUNCTION;

#اگر_ختم /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    خالی vRequestSystemCallExit( خالی ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#اگر_ختم /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    خالی vSystemCallExit( uint32_t * pul_System_Call_ڈھیر,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#اگر_ختم /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#اگر ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    بنیاد_Type_t x_پورٹ_Is_Task_Privileged( خالی ) PRIVILEGED_FUNCTION;

#اگر_ختم /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_ڈیٹا ساکن بنیاد_Type_t xSchedulerRunning = pdFALSE;

#اگر_ختم

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
PRIVILEGED_ڈیٹا ساکن متلون uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

#اگر ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_ڈیٹا ساکن uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_ڈیٹا ساکن uint32_t x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_ڈیٹا ساکن uint32_t ulStoppedTimerCompensation = 0;

#اگر_ختم /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#اگر ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) خالی v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت )
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
        __asm متلون ( "cpsid i" ::: "memory" );
        __asm متلون ( "dsb" );
        __asm متلون ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        اگر( e_Task_Confirm_Sleep_منوال_حالت() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm متلون ( "cpsie i" ::: "memory" );
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
                __asm متلون ( "dsb" ::: "memory" );
                __asm متلون ( "wfi" );
                __asm متلون ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_وقت );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
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
            __asm متلون ( "cpsie i" ::: "memory" );
        }
    }

#اگر_ختم /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) خالی v_پورٹ_تیاری_Timer_مداخلت( خالی ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #اگر ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ );
        x_زیادہ_سے_زیادہ_Possible_Suppressed_Ticks = پورٹ_MAX_24_ثنائی_ہندسہ_نمبر / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورٹ_MISSED_COUNTS_ضربی_عدد / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #اگر_ختم /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG;
    پورٹ_NVIC_SYSTICK_CURRENT_قدر_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورٹ_NVIC_SYSTICK_بھرو_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    پورٹ_NVIC_SYSTICK_CTRL_REG = پورٹ_NVIC_SYSTICK_CLK_ثنائی_ہندسہ_CONFIG | پورٹ_NVIC_SYSTICK_INT_ثنائی_ہندسہ | پورٹ_NVIC_SYSTICK_ENABLE_ثنائی_ہندسہ;
}

/*-----------------------------------------------------------*/

ساکن خالی prvTaskExitError( خالی )
{
    متلون uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    پورٹ_DISABLE_INTERRUPTS();

    جب( ulDummy == 0 )
    {
        /* This file calls prvTaskExitError() after the scheduler has been
         * started to remove a compiler warning about the function being
         * defined but never called.  ulDummy is used purely to quieten other
         * warnings about code appearing after this function is called - making
         * ulDummy volatile makes the compiler think the function could return
         * and therefore not output an 'unreachable code' warning for code that
         * appears after it. */
    }
}

/*-----------------------------------------------------------*/

#اگر ( configENABLE_MPU == 1 )

    ساکن uint32_t prv_Get_MPURegion_سائز_Setting( uint32_t ul_Actual_سائز_اندر_بائٹیں )
    {
        uint32_t ul_Region_سائز, ul_Return_قدر = 7UL;

        /* 256 is the smallest region size, 31 is the largest valid value for
         * ulReturnValue. */
        برائے( ul_Region_سائز = 256UL; ul_Return_قدر < 31UL; ( ul_Region_سائز <<= 1UL ) )
        {
            اگر( ul_Actual_سائز_اندر_بائٹیں <= ul_Region_سائز )
            {
                توڑو;
            }
            ورنہ
            {
                ul_Return_قدر++;
            }
        }

        /* Shift the code by one before returning so it can be written directly
         * into the correct bit position of the attribute register. */
        واپس( ul_Return_قدر << 1UL );
    }

#اگر_ختم /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#اگر ( configENABLE_MPU == 1 )

    ساکن خالی prv_تیاری_MPU( خالی ) /* PRIVILEGED_FUNCTION */
    {
        #اگر defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
            * exported from linker scripts. */
            خارجی uint32_t * __privileged_functions_start__;
            خارجی uint32_t * __privileged_functions_end__;
            خارجی uint32_t * __FLASH_segment_start__;
            خارجی uint32_t * __FLASH_segment_end__;
            خارجی uint32_t * __privileged_sram_start__;
            خارجی uint32_t * __privileged_sram_end__;

        #ورنہ /* if defined( __ARMCC_VERSION ) */

            /* Declaration when these variable are exported from linker scripts. */
            خارجی uint32_t __privileged_functions_start__[];
            خارجی uint32_t __privileged_functions_end__[];
            خارجی uint32_t __FLASH_segment_start__[];
            خارجی uint32_t __FLASH_segment_end__[];
            خارجی uint32_t __privileged_sram_start__[];
            خارجی uint32_t __privileged_sram_end__[];

        #اگر_ختم /* defined( __ARMCC_VERSION ) */

        /* Ensure that the MPU is present. */
        configASSERT( پورٹ_MPU_TYPE_REG == پورٹ_EXPECTED_MPU_TYPE_قدر );

        /* Check that the MPU is present. */
        اگر( پورٹ_MPU_TYPE_REG == پورٹ_EXPECTED_MPU_TYPE_قدر )
        {
            /* Setup privileged flash as Read Only so that privileged tasks can
             * read it but not modify. */
            پورٹ_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                 ( پورٹ_MPU_RBAR_REGION_نمبر_VALID_BITMASK ) |
                                 ( پورٹ_PRIVILEGED_FLASH_REGION ) );

            پورٹ_MPU_RASR_REG = ( ( پورٹ_MPU_REGION_PRIV_RO_UNPRIV_NA ) |
                                 ( ( configS_C_B_FLASH & پورٹ_MPU_RASR_S_C_B_BITMASK ) << پورٹ_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_سائز_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                 ( پورٹ_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup unprivileged flash as Read Only by both privileged and
             * unprivileged tasks. All tasks can read it but no-one can modify. */
            پورٹ_MPU_RBAR_REG = ( ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                 ( پورٹ_MPU_RBAR_REGION_نمبر_VALID_BITMASK ) |
                                 ( پورٹ_UNPRIVILEGED_FLASH_REGION ) );

            پورٹ_MPU_RASR_REG = ( ( پورٹ_MPU_REGION_PRIV_RO_UNPRIV_RO ) |
                                 ( ( configS_C_B_FLASH & پورٹ_MPU_RASR_S_C_B_BITMASK ) << پورٹ_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_سائز_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                 ( پورٹ_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup RAM containing kernel data for privileged access only. */
            پورٹ_MPU_RBAR_REG = ( ( uint32_t ) __privileged_sram_start__ ) | /* Base address. */
                                 ( پورٹ_MPU_RBAR_REGION_نمبر_VALID_BITMASK ) |
                                 ( پورٹ_PRIVILEGED_RAM_REGION );

            پورٹ_MPU_RASR_REG = ( ( پورٹ_MPU_REGION_PRIV_RW_UNPRIV_NA ) |
                                 ( پورٹ_MPU_REGION_EXECUTE_NEVER ) |
                                 ( ( configS_C_B_SRAM & پورٹ_MPU_RASR_S_C_B_BITMASK ) << پورٹ_MPU_RASR_S_C_B_LOCATION ) |
                                 prv_Get_MPURegion_سائز_Setting( ( uint32_t ) __privileged_sram_end__ - ( uint32_t ) __privileged_sram_start__ ) |
                                 ( پورٹ_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Enable MPU with privileged background access i.e. unmapped
             * regions have privileged access. */
            پورٹ_MPU_CTRL_REG |= ( پورٹ_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK |
                                  پورٹ_MPU_CTRL_ENABLE_BITMASK );
        }
    }

#اگر_ختم /* configENABLE_MPU */

/*-----------------------------------------------------------*/

خالی v_پورٹ_Yield( خالی ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm متلون ( "dsb" ::: "memory" );
    __asm متلون ( "isb" );
}

/*-----------------------------------------------------------*/

خالی v_پورٹ_Enter_Critical( خالی ) /* PRIVILEGED_FUNCTION */
{
    پورٹ_DISABLE_INTERRUPTS();
    ulCriticalNesting++;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm متلون ( "dsb" ::: "memory" );
    __asm متلون ( "isb" );
}

/*-----------------------------------------------------------*/

خالی v_پورٹ_Exit_Critical( خالی ) /* PRIVILEGED_FUNCTION */
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    اگر( ulCriticalNesting == 0 )
    {
        پورٹ_ENABLE_INTERRUPTS();
    }
}

/*-----------------------------------------------------------*/

خالی SysTick_Handler( خالی ) /* PRIVILEGED_FUNCTION */
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

خالی v_پورٹ_SVCHandler_C( uint32_t * pul_Caller_ڈھیر_پتہ ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        #اگر defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجی uint32_t * __syscalls_flash_start__;
            خارجی uint32_t * __syscalls_flash_end__;

        #ورنہ

            /* Declaration when these variable are exported from linker scripts. */
            خارجی uint32_t __syscalls_flash_start__[];
            خارجی uint32_t __syscalls_flash_end__[];

        #اگر_ختم /* defined( __ARMCC_VERSION ) */

    #اگر_ختم /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    uint32_t ulPC;
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_ڈھیر_پتہ[ پورٹ_انحراف_مقصد_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    انتخاب( ucSVCNumber )
    {
        حالت پورٹ_SVC_آغاز_SCHEDULER:
            /* Setup the context of the first task so that the first task starts
             * executing. */
            v_Restore_Context_کا_پہلا_Task();
            توڑو;

    #اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        حالت پورٹ_SVC_RAISE_PRIVILEGE:
            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            اگر( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            توڑو;

    #اگر_ختم /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #اگر ( configENABLE_MPU == 1 )

        حالت پورٹ_SVC_YIELD:
            v_پورٹ_Yield();
            توڑو;

    #اگر_ختم /* configENABLE_MPU == 1 */

        طےشدہ:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}

/*-----------------------------------------------------------*/

#اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    خالی vSystemCallEnter( uint32_t * pul_Task_ڈھیر,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_نمبر ) /* PRIVILEGED_FUNCTION */
    {
        خارجی TaskHandle_t pxCurrentTCB;
        خارجی UBaseType_t uxSystemCallImplementations[ عدد_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ڈھیر;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ثابت uint32_t ul_Hardware_Saved_Exception_چوکھٹا_سائز = 8;

        #اگر defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجی uint32_t * __syscalls_flash_start__;
            خارجی uint32_t * __syscalls_flash_end__;

        #ورنہ

            /* Declaration when these variable are exported from linker scripts. */
            خارجی uint32_t __syscalls_flash_start__[];
            خارجی uint32_t __syscalls_flash_end__[];

        #اگر_ختم /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_PC ];
        pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );

        /* Checks:
         * 1. SVC is raised from the system call section (i.e. application is
         *    not raising SVC directly).
         * 2. pxMpuSettings->xSystemCallStackInfo.pulTaskStack must be NULL as
         *    it is non-NULL only during the execution of a system call (i.e.
         *    between system call enter and exit).
         * 3. System call is not for a kernel API disabled by the configuration
         *    in FreeRTOSConfig.h.
         * 4. We do not need to check that ucSystemCallNumber is within range
         *    because the assembly SVC handler checks that before calling
         *    this function.
         */
        اگر( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر == تہی ) &&
            ( uxSystemCallImplementations[ uc_System_Call_نمبر ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ڈھیر = pxMpuSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر;

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ڈھیر = pul_System_Call_ڈھیر - ul_Hardware_Saved_Exception_چوکھٹا_سائز;

            /* Copy the stack frame. */
            برائے( i = 0; i < ul_Hardware_Saved_Exception_چوکھٹا_سائز; i++ )
            {
                pul_System_Call_ڈھیر[ i ] = pul_Task_ڈھیر[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج = pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_LR ];

            /* Use the pulSystemCallStack in thread mode. */
            __asm متلون ( "msr psp, %0" : : "r" ( pul_System_Call_ڈھیر ) );

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ڈھیر[ پورٹ_انحراف_مقصد_PC ] = uxSystemCallImplementations[ uc_System_Call_نمبر ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ڈھیر[ پورٹ_انحراف_مقصد_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = pul_Task_ڈھیر + ul_Hardware_Saved_Exception_چوکھٹا_سائز;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            اگر( ( pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_PSR ] & پورٹ_PSR_ڈھیر_PADDING_نقاب ) == پورٹ_PSR_ڈھیر_PADDING_نقاب )
            {
                pxMpuSettings->ulTaskFlags |= پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG;
            }
            ورنہ
            {
                pxMpuSettings->ulTaskFlags &= ( ~پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ڈھیر[ پورٹ_انحراف_مقصد_PSR ] &= ( ~پورٹ_PSR_ڈھیر_PADDING_نقاب );

            /* Raise the privilege for the duration of the system call. */
            __asm متلون
            (
                " .syntax unified     \n"
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " bics r0, r1         \n" /* Clear nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
            );
        }
    }

#اگر_ختم /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    خالی vRequestSystemCallExit( خالی ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm متلون ( "svc %0 \n" ::"i" ( پورٹ_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#اگر_ختم /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    خالی vSystemCallExit( uint32_t * pul_System_Call_ڈھیر,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        خارجی TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ڈھیر;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ثابت uint32_t ul_Hardware_Saved_Exception_چوکھٹا_سائز = 8;

        #اگر defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجی uint32_t * __privileged_functions_start__;
            خارجی uint32_t * __privileged_functions_end__;

        #ورنہ

            /* Declaration when these variable are exported from linker scripts. */
            خارجی uint32_t __privileged_functions_start__[];
            خارجی uint32_t __privileged_functions_end__[];

        #اگر_ختم /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ڈھیر[ پورٹ_انحراف_مقصد_PC ];
        pxMpuSettings = xTaskGetMPUSettings( pxCurrentTCB );

        /* Checks:
         * 1. SVC is raised from the privileged code (i.e. application is not
         *    raising SVC directly). This SVC is only raised from
         *    vRequestSystemCallExit which is in the privileged code section.
         * 2. pxMpuSettings->xSystemCallStackInfo.pulTaskStack must not be NULL -
         *    this means that we previously entered a system call and the
         *    application is not attempting to exit without entering a system
         *    call.
         */
        اگر( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر != تہی ) )
        {
            pul_Task_ڈھیر = pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر;

            /* Make space on the task stack for the stack frame. */
            pul_Task_ڈھیر = pul_Task_ڈھیر - ul_Hardware_Saved_Exception_چوکھٹا_سائز;

            /* Copy the stack frame. */
            برائے( i = 0; i < ul_Hardware_Saved_Exception_چوکھٹا_سائز; i++ )
            {
                pul_Task_ڈھیر[ i ] = pul_System_Call_ڈھیر[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm متلون ( "msr psp, %0" : : "r" ( pul_Task_ڈھیر ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_PC ] = pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج;

            /* Ensure that LR has a valid value.*/
            pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_LR ] = pxMpuSettings->x_System_Call_ڈھیر_Info.ul_Link_رجسٹر_At_System_Call_اندراج;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            اگر( ( pxMpuSettings->ulTaskFlags & پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG ) == پورٹ_ڈھیر_چوکھٹا_HAS_PADDING_FLAG )
            {
                pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_PSR ] |= پورٹ_PSR_ڈھیر_PADDING_نقاب;
            }
            ورنہ
            {
                pul_Task_ڈھیر[ پورٹ_انحراف_مقصد_PSR ] &= ( ~پورٹ_PSR_ڈھیر_PADDING_نقاب );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = تہی;

            /* Drop the privilege before returning to the thread mode. */
            __asm متلون
            (
                " .syntax unified     \n"
                " mrs r0, control     \n" /* Obtain current control value. */
                " movs r1, #1         \n" /* r1 = 1. */
                " orrs r0, r1         \n" /* Set nPRIV bit. */
                " msr control, r0     \n" /* Write back new control value. */
                ::: "r0", "r1", "memory"
            );
        }
    }

#اگر_ختم /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#اگر ( configENABLE_MPU == 1 )

    بنیاد_Type_t x_پورٹ_Is_Task_Privileged( خالی ) /* PRIVILEGED_FUNCTION */
    {
        بنیاد_Type_t xTaskIsPrivileged = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( تہی ); /* Calling task's MPU settings. */

        اگر( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        واپس xTaskIsPrivileged;
    }

#اگر_ختم /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#اگر ( configENABLE_MPU == 1 )

    ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                         TaskFunction_t px_رمز,
                                         خالی * pvParameters,
                                         بنیاد_Type_t x_تسلسل_Privileged,
                                         xMPU_SETTINGS * xMPUSettings ) /* PRIVILEGED_FUNCTION */
    {
        xMPUSettings->ulContext[ 0 ] = 0x04040404; /* r4. */
        xMPUSettings->ulContext[ 1 ] = 0x05050505; /* r5. */
        xMPUSettings->ulContext[ 2 ] = 0x06060606; /* r6. */
        xMPUSettings->ulContext[ 3 ] = 0x07070707; /* r7. */
        xMPUSettings->ulContext[ 4 ] = 0x08080808; /* r8. */
        xMPUSettings->ulContext[ 5 ] = 0x09090909; /* r9. */
        xMPUSettings->ulContext[ 6 ] = 0x10101010; /* r10. */
        xMPUSettings->ulContext[ 7 ] = 0x11111111; /* r11. */

        xMPUSettings->ulContext[ 8 ] = ( uint32_t ) pvParameters;            /* r0. */
        xMPUSettings->ulContext[ 9 ] = 0x01010101;                           /* r1. */
        xMPUSettings->ulContext[ 10 ] = 0x02020202;                           /* r2. */
        xMPUSettings->ulContext[ 11 ] = 0x03030303;                           /* r3. */
        xMPUSettings->ulContext[ 12 ] = 0x12121212;                           /* r12. */
        xMPUSettings->ulContext[ 13 ] = ( uint32_t ) پورٹ_TASK_RETURN_پتہ; /* LR. */
        xMPUSettings->ulContext[ 14 ] = ( uint32_t ) px_رمز;                  /* PC. */
        xMPUSettings->ulContext[ 15 ] = پورٹ_INITIAL_XPSR;                     /* xPSR. */

        xMPUSettings->ulContext[ 16 ] = ( uint32_t ) ( px_چوٹی_کا_ڈھیر - 8 ); /* PSP with the hardware saved stack. */
        اگر( x_تسلسل_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= پورٹ_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) پورٹ_INITIAL_CONTROL_PRIVILEGED; /* CONTROL. */
        }
        ورنہ
        {
            xMPUSettings->ulTaskFlags &= ( ~پورٹ_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) پورٹ_INITIAL_CONTROL_UNPRIVILEGED; /* CONTROL. */
        }
        xMPUSettings->ulContext[ 18 ] = پورٹ_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */

        #اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر = &( xMPUSettings->x_System_Call_ڈھیر_Info.ul_System_Call_ڈھیر_بفر[ config_SYSTEM_CALL_ڈھیر_سائز - 1 ] );
            xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ڈھیر_Info.pul_System_Call_ڈھیر ) &
                                                                                     ( uint32_t ) ( ~( پورٹ_BYTE_ALIGNMENT_نقاب ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_ڈھیر_Info.pul_Task_ڈھیر = تہی;
        }
        #اگر_ختم /* configUSE_MPU_WRAPPERS_V1 == 0 */

        واپس &( xMPUSettings->ulContext[ 19 ] );
    }

#ورنہ /* configENABLE_MPU */

    ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                         TaskFunction_t px_رمز,
                                         خالی * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #اگر ( پورٹ_PRELOAD_REGISTERS == 0 )
        {
            px_چوٹی_کا_ڈھیر--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_XPSR;                        /* xPSR. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;                  /* PC. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_TASK_RETURN_پتہ; /* LR. */
            px_چوٹی_کا_ڈھیر -= 5;                                       /* R12, R3, R2 and R1. */
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;            /* R0. */
            px_چوٹی_کا_ڈھیر -= 9;                                       /* R11..R4, EXC_RETURN. */
            *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_EXC_RETURN;
        }
        #ورنہ /* portPRELOAD_REGISTERS */
        {
            px_چوٹی_کا_ڈھیر--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_XPSR;                        /* xPSR. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) px_رمز;                  /* PC. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_TASK_RETURN_پتہ; /* LR. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x12121212UL;            /* R12. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x03030303UL;            /* R3. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x02020202UL;            /* R2. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x01010101UL;            /* R1. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) pvParameters;            /* R0. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x11111111UL;            /* R11. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x10101010UL;            /* R10. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x09090909UL;            /* R09. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x08080808UL;            /* R08. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x07070707UL;            /* R07. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x06060606UL;            /* R06. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x05050505UL;            /* R05. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t ) 0x04040404UL;            /* R04. */
            px_چوٹی_کا_ڈھیر--;
            *px_چوٹی_کا_ڈھیر = پورٹ_INITIAL_EXC_RETURN;                  /* EXC_RETURN. */
        }
        #اگر_ختم /* portPRELOAD_REGISTERS */

        واپس px_چوٹی_کا_ڈھیر;
    }

#اگر_ختم /* configENABLE_MPU */

/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی ) /* PRIVILEGED_FUNCTION */
{
    /* An application can install FreeRTOS interrupt handlers in one of the
     * following ways:
     * 1. Direct Routing - Install the functions SVC_Handler and PendSV_Handler
     *    for SVCall and PendSV interrupts respectively.
     * 2. Indirect Routing - Install separate handlers for SVCall and PendSV
     *    interrupts and route program control from those handlers to
     *    SVC_Handler and PendSV_Handler functions.
     *
     * Applications that use Indirect Routing must set
     * configCHECK_HANDLER_INSTALLATION to 0 in their FreeRTOSConfig.h. Direct
     * routing, which is validated here when configCHECK_HANDLER_INSTALLATION
     * is 1, should be preferred when possible. */
    #اگر ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ثابت پورٹ_ISR_t * ثابت px_سمتیہ_جدول = پورٹ_SCB_VTOR_REG;

        /* Validate that the application has correctly installed the FreeRTOS
         * handlers for SVCall and PendSV interrupts. We do not check the
         * installation of the SysTick handler because the application may
         * choose to drive the RTOS tick using a timer other than the SysTick
         * timer by overriding the weak function vPortSetupTimerInterrupt().
         *
         * Assertion failures here indicate incorrect installation of the
         * FreeRTOS handlers. For help installing the FreeRTOS handlers, see
         * https://www.freertos.org/Why-FreeRTOS/FAQs.
         *
         * Systems with a configurable address for the interrupt vector table
         * can also encounter assertion failures or even system faults here if
         * VTOR is not set correctly to point to the application's vector table. */
        configASSERT( px_سمتیہ_جدول[ پورٹ_سمتیہ_اشاریہ_SVC ] == SVC_Handler );
        configASSERT( px_سمتیہ_جدول[ پورٹ_سمتیہ_اشاریہ_PENDSV ] == PendSV_Handler );
    }
    #اگر_ختم /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
     * the highest priority. */
    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_PENDSV_PRI;
    پورٹ_NVIC_SHPR3_REG |= پورٹ_NVIC_SYSTICK_PRI;
    پورٹ_NVIC_SHPR2_REG = 0;

    #اگر ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_تیاری_MPU();
    }
    #اگر_ختم /* configENABLE_MPU */

    /* Start the timer that generates the tick ISR. Interrupts are disabled
     * here already. */
    v_پورٹ_تیاری_Timer_مداخلت();

    /* Initialize the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    #اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #اگر_ختم

    /* Start the first task. */
    v_آغاز_پہلا_Task();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    vTaskSwitchContext();
    prvTaskExitError();

    /* Should not get here. */
    واپس 0;
}

/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}

/*-----------------------------------------------------------*/

#اگر ( configENABLE_MPU == 1 )

    خالی v_پورٹ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ثابت ساخت x_حافظہ_REGION * ثابت xRegions,
                                    ڈھیر_Type_t * px_Bottom_کا_ڈھیر,
                                    config_ڈھیر_گہرائی_TYPE ux_ڈھیر_گہرائی )
    {
        #اگر defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجی uint32_t * __SRAM_segment_start__;
            خارجی uint32_t * __SRAM_segment_end__;
            خارجی uint32_t * __privileged_sram_start__;
            خارجی uint32_t * __privileged_sram_end__;

        #ورنہ
            /* Declaration when these variable are exported from linker scripts. */
            خارجی uint32_t __SRAM_segment_start__[];
            خارجی uint32_t __SRAM_segment_end__[];
            خارجی uint32_t __privileged_sram_start__[];
            خارجی uint32_t __privileged_sram_end__[];

        #اگر_ختم /* defined( __ARMCC_VERSION ) */

        int32_t l_اشاریہ;
        uint32_t ul;

        اگر( xRegions == تہی )
        {
            /* No MPU regions are specified so allow access to all RAM. */
            xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                ( ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
                  ( پورٹ_MPU_RBAR_REGION_نمبر_VALID_BITMASK ) |
                  ( پورٹ_ڈھیر_REGION ) );                   /* Region number. */

            xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                ( ( پورٹ_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                  ( پورٹ_MPU_REGION_EXECUTE_NEVER ) |
                  ( ( configS_C_B_SRAM & پورٹ_MPU_RASR_S_C_B_BITMASK ) << پورٹ_MPU_RASR_S_C_B_LOCATION ) |
                  ( prv_Get_MPURegion_سائز_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
                  ( پورٹ_MPU_RASR_REGION_ENABLE_BITMASK ) );


            /* Invalidate user configurable regions. */
            برائے( ul = 1UL; ul <= پورٹ_عدد_CONFIGURABLE_REGIONS; ul++ )
            {
                xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | پورٹ_MPU_RBAR_REGION_نمبر_VALID_BITMASK );
                xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
            }
        }
        ورنہ
        {
            /* This function is called automatically when the task is created - in
             * which case the stack region parameters will be valid.  At all other
             * times the stack parameters will not be valid and it is assumed that the
             * stack region has already been configured. */
            اگر( ux_ڈھیر_گہرائی > 0 )
            {
                /* Define the region that allows access to the stack. */
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                    ( ( ( uint32_t ) px_Bottom_کا_ڈھیر ) |
                      ( پورٹ_MPU_RBAR_REGION_نمبر_VALID_BITMASK ) |
                      ( پورٹ_ڈھیر_REGION ) ); /* Region number. */

                xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                    ( ( پورٹ_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                      ( پورٹ_MPU_REGION_EXECUTE_NEVER ) |
                      ( prv_Get_MPURegion_سائز_Setting( ux_ڈھیر_گہرائی * ( uint32_t ) حجم( ڈھیر_Type_t ) ) ) |
                      ( ( configS_C_B_SRAM & پورٹ_MPU_RASR_S_C_B_BITMASK ) << پورٹ_MPU_RASR_S_C_B_LOCATION ) |
                      ( پورٹ_MPU_RASR_REGION_ENABLE_BITMASK ) );
            }

            l_اشاریہ = 0;

            برائے( ul = 1UL; ul <= پورٹ_عدد_CONFIGURABLE_REGIONS; ul++ )
            {
                اگر( ( xRegions[ l_اشاریہ ] ).ul_لمبائی_اندر_بائٹیں > 0UL )
                {
                    /* Translate the generic region definition contained in
                     * xRegions into the CM0+ specific MPU settings that are then
                     * stored in xMPUSettings. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR =
                        ( ( uint32_t ) xRegions[ l_اشاریہ ].pv_بنیاد_پتہ ) |
                        ( پورٹ_MPU_RBAR_REGION_نمبر_VALID_BITMASK ) |
                        ( ul - 1UL ); /* Region number. */

                    xMPUSettings->xRegionsSettings[ ul ].ulRASR =
                        ( prv_Get_MPURegion_سائز_Setting( xRegions[ l_اشاریہ ].ul_لمبائی_اندر_بائٹیں ) ) |
                        ( xRegions[ l_اشاریہ ].ulParameters ) |
                        ( پورٹ_MPU_RASR_REGION_ENABLE_BITMASK );
                }
                ورنہ
                {
                    /* Invalidate the region. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | پورٹ_MPU_RBAR_REGION_نمبر_VALID_BITMASK );
                    xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
                }

            l_اشاریہ++;
        }
    }
}

#اگر_ختم /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    بنیاد_Type_t x_پورٹ_Is_Authorized_مقصد_Access_بفر( ثابت خالی * pv_بفر,
                                                size_t x_بفر_لمبائی,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_بفر_آغاز_پتہ, ul_بفر_انتہا_پتہ;
        uint32_t ul_Region_آغاز, ul_Region_سائز, ul_Region_انتہا;
        uint32_t ulMPURegionAccessPermissions;
        بنیاد_Type_t xAccessGranted = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( تہی ); /* Calling task's MPU settings. */

        اگر( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        ورنہ اگر( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ورنہ
        {
            اگر( پورٹ_جوڑو_UINT32_WILL_حد_سے_تجاوز( ( ( uint32_t ) pv_بفر ), ( ( uint32_t ) x_بفر_لمبائی - 1UL ) ) == pdFALSE )
            {
                ul_بفر_آغاز_پتہ = ( uint32_t ) pv_بفر;
                ul_بفر_انتہا_پتہ = ( ( ( uint32_t ) pv_بفر ) + ( uint32_t ) x_بفر_لمبائی - 1UL );

                برائے( i = 0; i < پورٹ_کل_عدد_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    اگر( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                          پورٹ_MPU_RASR_REGION_ENABLE_BITMASK ) == پورٹ_MPU_RASR_REGION_ENABLE_BITMASK )
                    {
                        ul_Region_آغاز = پورٹ_نکالو_پہلا_پتہ_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR );
                        ul_Region_سائز = پورٹ_نکالو_REGION_سائز_FROM_RASR( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR );
                        ul_Region_انتہا = ul_Region_آغاز + ul_Region_سائز;

                        اگر( پورٹ_IS_پتہ_WITHIN_RANGE( ul_بفر_آغاز_پتہ,
                                                         ul_Region_آغاز,
                                                         ul_Region_انتہا ) &&
                            پورٹ_IS_پتہ_WITHIN_RANGE( ul_بفر_انتہا_پتہ,
                                                         ul_Region_آغاز,
                                                         ul_Region_انتہا ) )
                        {
                            ulMPURegionAccessPermissions = xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                                                           پورٹ_MPU_RASR_AP_BITMASK;

                            اگر( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
                            {
                                اگر( ( ulMPURegionAccessPermissions == پورٹ_MPU_REGION_PRIV_RW_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == پورٹ_MPU_REGION_PRIV_RO_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == پورٹ_MPU_REGION_PRIV_RW_UNPRIV_RW ) )
                                {
                                    xAccessGranted = pdTRUE;
                                    توڑو;
                                }
                            }
                            ورنہ اگر( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
                            {
                                اگر( ulMPURegionAccessPermissions == پورٹ_MPU_REGION_PRIV_RW_UNPRIV_RW )
                                {
                                    xAccessGranted = pdTRUE;
                                    توڑو;
                                }
                            }
                        }
                    }
                }
            }
        }

        واپس xAccessGranted;
    }

#اگر_ختم /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_Is_Inside_مداخلت( خالی )
{
    uint32_t ul_Current_مداخلت;
    بنیاد_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm متلون ( "mrs %0, ipsr" : "=r" ( ul_Current_مداخلت )::"memory" );

    اگر( ul_Current_مداخلت == 0 )
    {
        xReturn = pdFALSE;
    }
    ورنہ
    {
        xReturn = pdTRUE;
    }

    واپس xReturn;
}

/*-----------------------------------------------------------*/

#اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    خالی v_پورٹ_Grant_Access_مقصد_Kernel_Object( TaskHandle_t x_اندرونی_Task_Handle,
                                         int32_t l_اندرونی_اشاریہ_کا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object / پورٹ_ACL_اندراج_سائز_بٹ );
        ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object % پورٹ_ACL_اندراج_سائز_بٹ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_اندرونی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] |= ( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ );
    }

#اگر_ختم /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    خالی v_پورٹ_Revoke_Access_مقصد_Kernel_Object( TaskHandle_t x_اندرونی_Task_Handle,
                                          int32_t l_اندرونی_اشاریہ_کا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object / پورٹ_ACL_اندراج_سائز_بٹ );
        ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object % پورٹ_ACL_اندراج_سائز_بٹ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_اندرونی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] &= ~( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ );
    }

#اگر_ختم /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#اگر ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        بنیاد_Type_t x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_اندرونی_اشاریہ_کا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_اندراج_اشاریہ, ul_Access_Control_List_اندراج_ثنائی_ہندسہ;
            بنیاد_Type_t xAccessGranted = pdFALSE;
            ثابت xMPU_SETTINGS * xTaskMpuSettings;

            اگر( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            ورنہ
            {
                xTaskMpuSettings = xTaskGetMPUSettings( تہی ); /* Calling task's MPU settings. */

                ul_Access_Control_List_اندراج_اشاریہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object / پورٹ_ACL_اندراج_سائز_بٹ );
                ul_Access_Control_List_اندراج_ثنائی_ہندسہ = ( ( uint32_t ) l_اندرونی_اشاریہ_کا_Kernel_Object % پورٹ_ACL_اندراج_سائز_بٹ );

                اگر( ( xTaskMpuSettings->ulTaskFlags & پورٹ_TASK_IS_PRIVILEGED_FLAG ) == پورٹ_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                ورنہ
                {
                    اگر( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_اندراج_اشاریہ ] & ( 1U << ul_Access_Control_List_اندراج_ثنائی_ہندسہ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            واپس xAccessGranted;
        }

    #ورنہ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        بنیاد_Type_t x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_اندرونی_اشاریہ_کا_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( خالی ) l_اندرونی_اشاریہ_کا_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            واپس pdTRUE;
        }

    #اگر_ختم /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#اگر_ختم /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/
