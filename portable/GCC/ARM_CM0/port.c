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
#تعریف_کړه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* MPU includes. */
#ضمن "mpu_wrappers.h"
#ضمن "mpu_syscall_numbers.h"

/* Portasm includes. */
#ضمن "portasm.h"

#تعریف_لغوه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
تعريفنوع فراغ ( * پورټ_ISR_t )( فراغ );

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#تعریف_کړه پورټ_NVIC_SYSTICK_CTRL_REG             ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#تعریف_کړه پورټ_NVIC_SYSTICK_بارول_REG             ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#تعریف_کړه پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG    ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#تعریف_کړه پورټ_NVIC_SHPR3_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
#تعریف_کړه پورټ_NVIC_SHPR2_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed1c ) )
#تعریف_کړه پورټ_NVIC_SYSTICK_ENABLE_بټ           ( 1UL << 0UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_INT_بټ              ( 1UL << 1UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_CLK_بټ              ( 1UL << 2UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_شمېر_FLAG_بټ       ( 1UL << 16UL )
#تعریف_کړه پورټ_NVIC_PEND_SYSTICK_CLEAR_بټ       ( 1UL << 25UL )
#تعریف_کړه پورټ_NVIC_PEND_SYSTICK_سېټ_بټ         ( 1UL << 26UL )
#تعریف_کړه پورټ_MIN_مداخله_لومړیتوب            ( 255UL )
#تعریف_کړه پورټ_NVIC_PENDSV_PRI                   ( پورټ_MIN_مداخله_لومړیتوب << 16UL )
#تعریف_کړه پورټ_NVIC_SYSTICK_PRI                  ( پورټ_MIN_مداخله_لومړیتوب << 24UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#تعریف_کړه پورټ_SCB_VTOR_REG                      ( *( ( پورټ_ISR_t ** ) 0xe000ed08 ) )
#تعریف_کړه پورټ_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( متطاير uint32_t * ) 0xe000ed24 ) )
#تعریف_کړه پورټ_SCB_MEM_FAULT_ENABLE_بټ          ( 1UL << 16UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#تعریف_کړه پورټ_ویکټور_شاخص_SVC       ( 11 )
#تعریف_کړه پورټ_ویکټور_شاخص_PENDSV    ( 14 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#تعریف_کړه پورټ_PSR_ډېری_PADDING_ماسک              ( 1UL << 9UL )
#تعریف_کړه پورټ_EXC_RETURN_ډېری_چوکاټ_TYPE_ماسک    ( 1UL << 4UL )

/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#تعریف_کړه پورټ_دننه_واټن_منزل_LR     ( 5 )
#تعریف_کړه پورټ_دننه_واټن_منزل_PC     ( 6 )
#تعریف_کړه پورټ_دننه_واټن_منزل_PSR    ( 7 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#تعریف_کړه پورټ_MPU_TYPE_REG                            ( *( ( متطاير uint32_t * ) 0xe000ed90 ) )
#تعریف_کړه پورټ_MPU_CTRL_REG                            ( *( ( متطاير uint32_t * ) 0xe000ed94 ) )

#تعریف_کړه پورټ_MPU_RBAR_REG                            ( *( ( متطاير uint32_t * ) 0xe000ed9c ) )
#تعریف_کړه پورټ_MPU_RASR_REG                            ( *( ( متطاير uint32_t * ) 0xe000eda0 ) )

/* MPU Region Attribute and Size Register (RASR) bitmasks. */
#تعریف_کړه پورټ_MPU_RASR_AP_BITMASK                     ( 0x7UL << 24UL )
#تعریف_کړه پورټ_MPU_RASR_S_C_B_BITMASK                  ( 0x7UL )
#تعریف_کړه پورټ_MPU_RASR_S_C_B_LOCATION                 ( 16UL )
#تعریف_کړه پورټ_MPU_RASR_اندازه_BITMASK                   ( 0x1FUL << 1UL )
#تعریف_کړه پورټ_MPU_RASR_REGION_ENABLE_BITMASK          ( 0x1UL )

/* MPU Region Base Address Register (RBAR) bitmasks. */
#تعریف_کړه پورټ_MPU_RBAR_پته_BITMASK                ( 0xFFFFFF00UL )
#تعریف_کړه پورټ_MPU_RBAR_REGION_شمېره_VALID_BITMASK    ( 0x1UL << 4UL )
#تعریف_کړه پورټ_MPU_RBAR_REGION_شمېره_BITMASK          ( 0x0000000FUL )

/* MPU Control Register (MPU_CTRL) bitmasks. */
#تعریف_کړه پورټ_MPU_CTRL_ENABLE_BITMASK                 ( 0x1UL )
#تعریف_کړه پورټ_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK ( 0x1UL << 2UL ) /* PRIVDEFENA bit. */

/* Expected value of the portMPU_TYPE register. */
#تعریف_کړه پورټ_EXPECTED_MPU_TYPE_ارزښت                 ( 0x8UL << 8UL ) /* 8 DREGION unified. */

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#تعریف_کړه پورټ_ایستل_لومړی_پته_FROM_RBAR( rbar ) \
    ( ( rbar ) & پورټ_MPU_RBAR_پته_BITMASK )

/* Extract size of the MPU region as encoded in the
 * RASR (Region Attribute and Size Register) value. */
#تعریف_کړه پورټ_ایستل_REGION_اندازه_FROM_RASR( rasr ) \
    ( 1 << ( ( ( ( rasr ) & پورټ_MPU_RASR_اندازه_BITMASK ) >> 1 )+ 1 ) )

/* Does addr lies within [start, end] address range? */
#تعریف_کړه پورټ_IS_پته_WITHIN_RANGE( addr, پیل, پای_ټکی ) \
    ( ( ( addr ) >= ( پیل ) ) && ( ( addr ) <= ( پای_ټکی ) ) )

/* Is the access request satisfied by the available permissions? */
#تعریف_کړه پورټ_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#تعریف_کړه پورټ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کړه پورټ_جمع_کړه_UINT32_WILL_ډکېدنه( a, b )    ( ( a ) > ( پورټ_UINT32_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#تعریف_کړه پورټ_MAX_24_بټ_شمېره       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#تعریف_کړه پورټ_MISSED_COUNTS_ضریب    ( 94UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#تعریف_کړه پورټ_INITIAL_XPSR    ( 0x01000000 )

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
#تعریف_کړه پورټ_INITIAL_EXC_RETURN    ( 0xfffffffdUL )

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#تعریف_کړه پورټ_CONTROL_PRIVILEGED_ماسک         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#تعریف_کړه پورټ_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#تعریف_کړه پورټ_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#که_نه_تعریف_شوی configSYSTICK_CLOCK_HZ
    #تعریف_کړه configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کړه پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG    ( پورټ_NVIC_SYSTICK_CLK_بټ )
#وإلا
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #تعریف_کړه پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG    ( 0 )
#د_که_پای

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#که_تعریف_شوی config_TASK_RETURN_پته
    #تعریف_کړه پورټ_TASK_RETURN_پته    config_TASK_RETURN_پته
#وإلا
    #تعریف_کړه پورټ_TASK_RETURN_پته    prvTaskExitError
#د_که_پای

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#تعریف_کړه پورټ_PRELOAD_REGISTERS    1

/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
ساكن فراغ prvTaskExitError( فراغ );

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    ساكن فراغ prv_تیاری_MPU( فراغ ) PRIVILEGED_FUNCTION;

#د_که_پای /* configENABLE_MPU */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
فراغ v_پورټ_تیاری_Timer_مداخله( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
بنسټ_Type_t x_پورټ_Is_Inside_مداخله( فراغ );

/**
 * @brief Yield the processor.
 */
فراغ v_پورټ_Yield( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
فراغ v_پورټ_Enter_Critical( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
فراغ v_پورټ_Exit_Critical( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
فراغ SysTick_Handler( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
پورټ_DONT_DISCARD فراغ v_پورټ_SVCHandler_C( uint32_t * pul_Caller_ډېری_پته ) PRIVILEGED_FUNCTION;

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    فراغ vSystemCallEnter( uint32_t * pul_Task_ډېری,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_شمېره ) PRIVILEGED_FUNCTION;

#د_که_پای /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    فراغ vRequestSystemCallExit( فراغ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#د_که_پای /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    فراغ vSystemCallExit( uint32_t * pul_System_Call_ډېری,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#د_که_پای /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    بنسټ_Type_t x_پورټ_Is_Task_Privileged( فراغ ) PRIVILEGED_FUNCTION;

#د_که_پای /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_معلومات ساكن بنسټ_Type_t xSchedulerRunning = pdFALSE;

#د_که_پای

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
PRIVILEGED_معلومات ساكن متطاير uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_معلومات ساكن uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_معلومات ساكن uint32_t x_اعظمي_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_معلومات ساكن uint32_t ulStoppedTimerCompensation = 0;

#د_که_پای /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) فراغ v_پورټ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وخت )
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
        __asm متطاير ( "cpsid i" ::: "memory" );
        __asm متطاير ( "dsb" );
        __asm متطاير ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_ډېرپېښ_حالت() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm متطاير ( "cpsie i" ::: "memory" );
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
                __asm متطاير ( "dsb" ::: "memory" );
                __asm متطاير ( "wfi" );
                __asm متطاير ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_وخت );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm متطاير ( "cpsie i" ::: "memory" );
            __asm متطاير ( "dsb" );
            __asm متطاير ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm متطاير ( "cpsid i" ::: "memory" );
            __asm متطاير ( "dsb" );
            __asm متطاير ( "isb" );

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
            __asm متطاير ( "cpsie i" ::: "memory" );
        }
    }

#د_که_پای /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) فراغ v_پورټ_تیاری_Timer_مداخله( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #إذا ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ );
        x_اعظمي_Possible_Suppressed_Ticks = پورټ_MAX_24_بټ_شمېره / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورټ_MISSED_COUNTS_ضریب / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #د_که_پای /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    پورټ_NVIC_SYSTICK_CTRL_REG = پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG;
    پورټ_NVIC_SYSTICK_CURRENT_ارزښت_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورټ_NVIC_SYSTICK_بارول_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_شرح_HZ ) - 1UL;
    پورټ_NVIC_SYSTICK_CTRL_REG = پورټ_NVIC_SYSTICK_CLK_بټ_CONFIG | پورټ_NVIC_SYSTICK_INT_بټ | پورټ_NVIC_SYSTICK_ENABLE_بټ;
}

/*-----------------------------------------------------------*/

ساكن فراغ prvTaskExitError( فراغ )
{
    متطاير uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    پورټ_DISABLE_INTERRUPTS();

    طالما( ulDummy == 0 )
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

#إذا ( configENABLE_MPU == 1 )

    ساكن uint32_t prv_Get_MPURegion_اندازه_Setting( uint32_t ul_Actual_اندازه_دننه_بایټونه )
    {
        uint32_t ul_Region_اندازه, ul_Return_ارزښت = 7UL;

        /* 256 is the smallest region size, 31 is the largest valid value for
         * ulReturnValue. */
        لكل( ul_Region_اندازه = 256UL; ul_Return_ارزښت < 31UL; ( ul_Region_اندازه <<= 1UL ) )
        {
            إذا( ul_Actual_اندازه_دننه_بایټونه <= ul_Region_اندازه )
            {
                اكسر;
            }
            وإلا
            {
                ul_Return_ارزښت++;
            }
        }

        /* Shift the code by one before returning so it can be written directly
         * into the correct bit position of the attribute register. */
        أرجع( ul_Return_ارزښت << 1UL );
    }

#د_که_پای /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    ساكن فراغ prv_تیاری_MPU( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
            * exported from linker scripts. */
            خارجي uint32_t * __privileged_functions_start__;
            خارجي uint32_t * __privileged_functions_end__;
            خارجي uint32_t * __FLASH_segment_start__;
            خارجي uint32_t * __FLASH_segment_end__;
            خارجي uint32_t * __privileged_sram_start__;
            خارجي uint32_t * __privileged_sram_end__;

        #وإلا /* if defined( __ARMCC_VERSION ) */

            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __privileged_functions_start__[];
            خارجي uint32_t __privileged_functions_end__[];
            خارجي uint32_t __FLASH_segment_start__[];
            خارجي uint32_t __FLASH_segment_end__[];
            خارجي uint32_t __privileged_sram_start__[];
            خارجي uint32_t __privileged_sram_end__[];

        #د_که_پای /* defined( __ARMCC_VERSION ) */

        /* Ensure that the MPU is present. */
        configASSERT( پورټ_MPU_TYPE_REG == پورټ_EXPECTED_MPU_TYPE_ارزښت );

        /* Check that the MPU is present. */
        إذا( پورټ_MPU_TYPE_REG == پورټ_EXPECTED_MPU_TYPE_ارزښت )
        {
            /* Setup privileged flash as Read Only so that privileged tasks can
             * read it but not modify. */
            پورټ_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                 ( پورټ_MPU_RBAR_REGION_شمېره_VALID_BITMASK ) |
                                 ( پورټ_PRIVILEGED_FLASH_REGION ) );

            پورټ_MPU_RASR_REG = ( ( پورټ_MPU_REGION_PRIV_RO_UNPRIV_NA ) |
                                 ( ( configS_C_B_FLASH & پورټ_MPU_RASR_S_C_B_BITMASK ) << پورټ_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                 ( پورټ_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup unprivileged flash as Read Only by both privileged and
             * unprivileged tasks. All tasks can read it but no-one can modify. */
            پورټ_MPU_RBAR_REG = ( ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                 ( پورټ_MPU_RBAR_REGION_شمېره_VALID_BITMASK ) |
                                 ( پورټ_UNPRIVILEGED_FLASH_REGION ) );

            پورټ_MPU_RASR_REG = ( ( پورټ_MPU_REGION_PRIV_RO_UNPRIV_RO ) |
                                 ( ( configS_C_B_FLASH & پورټ_MPU_RASR_S_C_B_BITMASK ) << پورټ_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                 ( پورټ_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup RAM containing kernel data for privileged access only. */
            پورټ_MPU_RBAR_REG = ( ( uint32_t ) __privileged_sram_start__ ) | /* Base address. */
                                 ( پورټ_MPU_RBAR_REGION_شمېره_VALID_BITMASK ) |
                                 ( پورټ_PRIVILEGED_RAM_REGION );

            پورټ_MPU_RASR_REG = ( ( پورټ_MPU_REGION_PRIV_RW_UNPRIV_NA ) |
                                 ( پورټ_MPU_REGION_EXECUTE_NEVER ) |
                                 ( ( configS_C_B_SRAM & پورټ_MPU_RASR_S_C_B_BITMASK ) << پورټ_MPU_RASR_S_C_B_LOCATION ) |
                                 prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __privileged_sram_end__ - ( uint32_t ) __privileged_sram_start__ ) |
                                 ( پورټ_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Enable MPU with privileged background access i.e. unmapped
             * regions have privileged access. */
            پورټ_MPU_CTRL_REG |= ( پورټ_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK |
                                  پورټ_MPU_CTRL_ENABLE_BITMASK );
        }
    }

#د_که_پای /* configENABLE_MPU */

/*-----------------------------------------------------------*/

فراغ v_پورټ_Yield( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PENDSVSET_بټ;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm متطاير ( "dsb" ::: "memory" );
    __asm متطاير ( "isb" );
}

/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ ) /* PRIVILEGED_FUNCTION */
{
    پورټ_DISABLE_INTERRUPTS();
    ulCriticalNesting++;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm متطاير ( "dsb" ::: "memory" );
    __asm متطاير ( "isb" );
}

/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ ) /* PRIVILEGED_FUNCTION */
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    إذا( ulCriticalNesting == 0 )
    {
        پورټ_ENABLE_INTERRUPTS();
    }
}

/*-----------------------------------------------------------*/

فراغ SysTick_Handler( فراغ ) /* PRIVILEGED_FUNCTION */
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
            پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PENDSVSET_بټ;
        }
        وإلا
        {
            traceISR_EXIT();
        }
    }

    پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ul_پخوانی_ماسک );
}

/*-----------------------------------------------------------*/

فراغ v_پورټ_SVCHandler_C( uint32_t * pul_Caller_ډېری_پته ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __syscalls_flash_start__;
            خارجي uint32_t * __syscalls_flash_end__;

        #وإلا

            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __syscalls_flash_start__[];
            خارجي uint32_t __syscalls_flash_end__[];

        #د_که_پای /* defined( __ARMCC_VERSION ) */

    #د_که_پای /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    uint32_t ulPC;
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_ډېری_پته[ پورټ_دننه_واټن_منزل_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    بدل( ucSVCNumber )
    {
        حالة پورټ_SVC_پیل_SCHEDULER:
            /* Setup the context of the first task so that the first task starts
             * executing. */
            v_Restore_Context_د_لومړی_Task();
            اكسر;

    #إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        حالة پورټ_SVC_RAISE_PRIVILEGE:
            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            إذا( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            اكسر;

    #د_که_پای /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #إذا ( configENABLE_MPU == 1 )

        حالة پورټ_SVC_YIELD:
            v_پورټ_Yield();
            اكسر;

    #د_که_پای /* configENABLE_MPU == 1 */

        افتراضي:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vSystemCallEnter( uint32_t * pul_Task_ډېری,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_شمېره ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        خارجي UBaseType_t uxSystemCallImplementations[ عدد_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ډېری;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ثابت uint32_t ul_Hardware_Saved_Exception_چوکاټ_اندازه = 8;

        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __syscalls_flash_start__;
            خارجي uint32_t * __syscalls_flash_end__;

        #وإلا

            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __syscalls_flash_start__[];
            خارجي uint32_t __syscalls_flash_end__[];

        #د_که_پای /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ډېری[ پورټ_دننه_واټن_منزل_PC ];
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
        إذا( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ډېری_Info.pul_Task_ډېری == عدم ) &&
            ( uxSystemCallImplementations[ uc_System_Call_شمېره ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ډېری = pxMpuSettings->x_System_Call_ډېری_Info.pul_System_Call_ډېری;

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ډېری = pul_System_Call_ډېری - ul_Hardware_Saved_Exception_چوکاټ_اندازه;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_چوکاټ_اندازه; i++ )
            {
                pul_System_Call_ډېری[ i ] = pul_Task_ډېری[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ډېری_Info.ul_Link_ثبتوونکی_At_System_Call_ثبت = pul_Task_ډېری[ پورټ_دننه_واټن_منزل_LR ];

            /* Use the pulSystemCallStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_System_Call_ډېری ) );

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ډېری[ پورټ_دننه_واټن_منزل_PC ] = uxSystemCallImplementations[ uc_System_Call_شمېره ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ډېری[ پورټ_دننه_واټن_منزل_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ډېری_Info.pul_Task_ډېری = pul_Task_ډېری + ul_Hardware_Saved_Exception_چوکاټ_اندازه;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            إذا( ( pul_Task_ډېری[ پورټ_دننه_واټن_منزل_PSR ] & پورټ_PSR_ډېری_PADDING_ماسک ) == پورټ_PSR_ډېری_PADDING_ماسک )
            {
                pxMpuSettings->ulTaskFlags |= پورټ_ډېری_چوکاټ_HAS_PADDING_FLAG;
            }
            وإلا
            {
                pxMpuSettings->ulTaskFlags &= ( ~پورټ_ډېری_چوکاټ_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ډېری[ پورټ_دننه_واټن_منزل_PSR ] &= ( ~پورټ_PSR_ډېری_PADDING_ماسک );

            /* Raise the privilege for the duration of the system call. */
            __asm متطاير
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

#د_که_پای /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vRequestSystemCallExit( فراغ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm متطاير ( "svc %0 \n" ::"i" ( پورټ_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#د_که_پای /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vSystemCallExit( uint32_t * pul_System_Call_ډېری,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ډېری;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ثابت uint32_t ul_Hardware_Saved_Exception_چوکاټ_اندازه = 8;

        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __privileged_functions_start__;
            خارجي uint32_t * __privileged_functions_end__;

        #وإلا

            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __privileged_functions_start__[];
            خارجي uint32_t __privileged_functions_end__[];

        #د_که_پای /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ډېری[ پورټ_دننه_واټن_منزل_PC ];
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
        إذا( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ډېری_Info.pul_Task_ډېری != عدم ) )
        {
            pul_Task_ډېری = pxMpuSettings->x_System_Call_ډېری_Info.pul_Task_ډېری;

            /* Make space on the task stack for the stack frame. */
            pul_Task_ډېری = pul_Task_ډېری - ul_Hardware_Saved_Exception_چوکاټ_اندازه;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_چوکاټ_اندازه; i++ )
            {
                pul_Task_ډېری[ i ] = pul_System_Call_ډېری[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_Task_ډېری ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ډېری[ پورټ_دننه_واټن_منزل_PC ] = pxMpuSettings->x_System_Call_ډېری_Info.ul_Link_ثبتوونکی_At_System_Call_ثبت;

            /* Ensure that LR has a valid value.*/
            pul_Task_ډېری[ پورټ_دننه_واټن_منزل_LR ] = pxMpuSettings->x_System_Call_ډېری_Info.ul_Link_ثبتوونکی_At_System_Call_ثبت;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            إذا( ( pxMpuSettings->ulTaskFlags & پورټ_ډېری_چوکاټ_HAS_PADDING_FLAG ) == پورټ_ډېری_چوکاټ_HAS_PADDING_FLAG )
            {
                pul_Task_ډېری[ پورټ_دننه_واټن_منزل_PSR ] |= پورټ_PSR_ډېری_PADDING_ماسک;
            }
            وإلا
            {
                pul_Task_ډېری[ پورټ_دننه_واټن_منزل_PSR ] &= ( ~پورټ_PSR_ډېری_PADDING_ماسک );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ډېری_Info.pul_Task_ډېری = عدم;

            /* Drop the privilege before returning to the thread mode. */
            __asm متطاير
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

#د_که_پای /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    بنسټ_Type_t x_پورټ_Is_Task_Privileged( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        بنسټ_Type_t xTaskIsPrivileged = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

        إذا( ( xTaskMpuSettings->ulTaskFlags & پورټ_TASK_IS_PRIVILEGED_FLAG ) == پورټ_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        أرجع xTaskIsPrivileged;
    }

#د_که_پای /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                         TaskFunction_t px_کوډ,
                                         فراغ * pvParameters,
                                         بنسټ_Type_t x_پرلپسې_Privileged,
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
        xMPUSettings->ulContext[ 13 ] = ( uint32_t ) پورټ_TASK_RETURN_پته; /* LR. */
        xMPUSettings->ulContext[ 14 ] = ( uint32_t ) px_کوډ;                  /* PC. */
        xMPUSettings->ulContext[ 15 ] = پورټ_INITIAL_XPSR;                     /* xPSR. */

        xMPUSettings->ulContext[ 16 ] = ( uint32_t ) ( px_سر_د_ډېری - 8 ); /* PSP with the hardware saved stack. */
        إذا( x_پرلپسې_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= پورټ_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) پورټ_INITIAL_CONTROL_PRIVILEGED; /* CONTROL. */
        }
        وإلا
        {
            xMPUSettings->ulTaskFlags &= ( ~پورټ_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) پورټ_INITIAL_CONTROL_UNPRIVILEGED; /* CONTROL. */
        }
        xMPUSettings->ulContext[ 18 ] = پورټ_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */

        #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_ډېری_Info.pul_System_Call_ډېری = &( xMPUSettings->x_System_Call_ډېری_Info.ul_System_Call_ډېری_بفر[ config_SYSTEM_CALL_ډېری_اندازه - 1 ] );
            xMPUSettings->x_System_Call_ډېری_Info.pul_System_Call_ډېری = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ډېری_Info.pul_System_Call_ډېری ) &
                                                                                     ( uint32_t ) ( ~( پورټ_BYTE_ALIGNMENT_ماسک ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_ډېری_Info.pul_Task_ډېری = عدم;
        }
        #د_که_پای /* configUSE_MPU_WRAPPERS_V1 == 0 */

        أرجع &( xMPUSettings->ulContext[ 19 ] );
    }

#وإلا /* configENABLE_MPU */

    ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                         TaskFunction_t px_کوډ,
                                         فراغ * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #إذا ( پورټ_PRELOAD_REGISTERS == 0 )
        {
            px_سر_د_ډېری--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_سر_د_ډېری = پورټ_INITIAL_XPSR;                        /* xPSR. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ;                  /* PC. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_TASK_RETURN_پته; /* LR. */
            px_سر_د_ډېری -= 5;                                       /* R12, R3, R2 and R1. */
            *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;            /* R0. */
            px_سر_د_ډېری -= 9;                                       /* R11..R4, EXC_RETURN. */
            *px_سر_د_ډېری = پورټ_INITIAL_EXC_RETURN;
        }
        #وإلا /* portPRELOAD_REGISTERS */
        {
            px_سر_د_ډېری--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_سر_د_ډېری = پورټ_INITIAL_XPSR;                        /* xPSR. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ;                  /* PC. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_TASK_RETURN_پته; /* LR. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x12121212UL;            /* R12. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x03030303UL;            /* R3. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x02020202UL;            /* R2. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x01010101UL;            /* R1. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters;            /* R0. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x11111111UL;            /* R11. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x10101010UL;            /* R10. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x09090909UL;            /* R09. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x08080808UL;            /* R08. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x07070707UL;            /* R07. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x06060606UL;            /* R06. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x05050505UL;            /* R05. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = ( ډېری_Type_t ) 0x04040404UL;            /* R04. */
            px_سر_د_ډېری--;
            *px_سر_د_ډېری = پورټ_INITIAL_EXC_RETURN;                  /* EXC_RETURN. */
        }
        #د_که_پای /* portPRELOAD_REGISTERS */

        أرجع px_سر_د_ډېری;
    }

#د_که_پای /* configENABLE_MPU */

/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ ) /* PRIVILEGED_FUNCTION */
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
    #إذا ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ثابت پورټ_ISR_t * ثابت px_ویکټور_جدول = پورټ_SCB_VTOR_REG;

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
        configASSERT( px_ویکټور_جدول[ پورټ_ویکټور_شاخص_SVC ] == SVC_Handler );
        configASSERT( px_ویکټور_جدول[ پورټ_ویکټور_شاخص_PENDSV ] == PendSV_Handler );
    }
    #د_که_پای /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
     * the highest priority. */
    پورټ_NVIC_SHPR3_REG |= پورټ_NVIC_PENDSV_PRI;
    پورټ_NVIC_SHPR3_REG |= پورټ_NVIC_SYSTICK_PRI;
    پورټ_NVIC_SHPR2_REG = 0;

    #إذا ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_تیاری_MPU();
    }
    #د_که_پای /* configENABLE_MPU */

    /* Start the timer that generates the tick ISR. Interrupts are disabled
     * here already. */
    v_پورټ_تیاری_Timer_مداخله();

    /* Initialize the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    #إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #د_که_پای

    /* Start the first task. */
    v_پیل_لومړی_Task();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    vTaskSwitchContext();
    prvTaskExitError();

    /* Should not get here. */
    أرجع 0;
}

/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}

/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    فراغ v_پورټ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ثابت بنية x_حافظه_REGION * ثابت xRegions,
                                    ډېری_Type_t * px_Bottom_د_ډېری,
                                    config_ډېری_ژوروالی_TYPE ux_ډېری_ژوروالی )
    {
        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __SRAM_segment_start__;
            خارجي uint32_t * __SRAM_segment_end__;
            خارجي uint32_t * __privileged_sram_start__;
            خارجي uint32_t * __privileged_sram_end__;

        #وإلا
            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __SRAM_segment_start__[];
            خارجي uint32_t __SRAM_segment_end__[];
            خارجي uint32_t __privileged_sram_start__[];
            خارجي uint32_t __privileged_sram_end__[];

        #د_که_پای /* defined( __ARMCC_VERSION ) */

        int32_t l_شاخص;
        uint32_t ul;

        إذا( xRegions == عدم )
        {
            /* No MPU regions are specified so allow access to all RAM. */
            xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                ( ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
                  ( پورټ_MPU_RBAR_REGION_شمېره_VALID_BITMASK ) |
                  ( پورټ_ډېری_REGION ) );                   /* Region number. */

            xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                ( ( پورټ_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                  ( پورټ_MPU_REGION_EXECUTE_NEVER ) |
                  ( ( configS_C_B_SRAM & پورټ_MPU_RASR_S_C_B_BITMASK ) << پورټ_MPU_RASR_S_C_B_LOCATION ) |
                  ( prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
                  ( پورټ_MPU_RASR_REGION_ENABLE_BITMASK ) );


            /* Invalidate user configurable regions. */
            لكل( ul = 1UL; ul <= پورټ_عدد_CONFIGURABLE_REGIONS; ul++ )
            {
                xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | پورټ_MPU_RBAR_REGION_شمېره_VALID_BITMASK );
                xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
            }
        }
        وإلا
        {
            /* This function is called automatically when the task is created - in
             * which case the stack region parameters will be valid.  At all other
             * times the stack parameters will not be valid and it is assumed that the
             * stack region has already been configured. */
            إذا( ux_ډېری_ژوروالی > 0 )
            {
                /* Define the region that allows access to the stack. */
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                    ( ( ( uint32_t ) px_Bottom_د_ډېری ) |
                      ( پورټ_MPU_RBAR_REGION_شمېره_VALID_BITMASK ) |
                      ( پورټ_ډېری_REGION ) ); /* Region number. */

                xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                    ( ( پورټ_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                      ( پورټ_MPU_REGION_EXECUTE_NEVER ) |
                      ( prv_Get_MPURegion_اندازه_Setting( ux_ډېری_ژوروالی * ( uint32_t ) حجم( ډېری_Type_t ) ) ) |
                      ( ( configS_C_B_SRAM & پورټ_MPU_RASR_S_C_B_BITMASK ) << پورټ_MPU_RASR_S_C_B_LOCATION ) |
                      ( پورټ_MPU_RASR_REGION_ENABLE_BITMASK ) );
            }

            l_شاخص = 0;

            لكل( ul = 1UL; ul <= پورټ_عدد_CONFIGURABLE_REGIONS; ul++ )
            {
                إذا( ( xRegions[ l_شاخص ] ).ul_اوږدتیا_دننه_بایټونه > 0UL )
                {
                    /* Translate the generic region definition contained in
                     * xRegions into the CM0+ specific MPU settings that are then
                     * stored in xMPUSettings. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR =
                        ( ( uint32_t ) xRegions[ l_شاخص ].pv_بنسټ_پته ) |
                        ( پورټ_MPU_RBAR_REGION_شمېره_VALID_BITMASK ) |
                        ( ul - 1UL ); /* Region number. */

                    xMPUSettings->xRegionsSettings[ ul ].ulRASR =
                        ( prv_Get_MPURegion_اندازه_Setting( xRegions[ l_شاخص ].ul_اوږدتیا_دننه_بایټونه ) ) |
                        ( xRegions[ l_شاخص ].ulParameters ) |
                        ( پورټ_MPU_RASR_REGION_ENABLE_BITMASK );
                }
                وإلا
                {
                    /* Invalidate the region. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | پورټ_MPU_RBAR_REGION_شمېره_VALID_BITMASK );
                    xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
                }

            l_شاخص++;
        }
    }
}

#د_که_پای /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    بنسټ_Type_t x_پورټ_Is_Authorized_منزل_Access_بفر( ثابت فراغ * pv_بفر,
                                                size_t x_بفر_اوږدتیا,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_بفر_پیل_پته, ul_بفر_پای_ټکی_پته;
        uint32_t ul_Region_پیل, ul_Region_اندازه, ul_Region_پای_ټکی;
        uint32_t ulMPURegionAccessPermissions;
        بنسټ_Type_t xAccessGranted = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

        إذا( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        وإلا إذا( ( xTaskMpuSettings->ulTaskFlags & پورټ_TASK_IS_PRIVILEGED_FLAG ) == پورټ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        وإلا
        {
            إذا( پورټ_جمع_کړه_UINT32_WILL_ډکېدنه( ( ( uint32_t ) pv_بفر ), ( ( uint32_t ) x_بفر_اوږدتیا - 1UL ) ) == pdFALSE )
            {
                ul_بفر_پیل_پته = ( uint32_t ) pv_بفر;
                ul_بفر_پای_ټکی_پته = ( ( ( uint32_t ) pv_بفر ) + ( uint32_t ) x_بفر_اوږدتیا - 1UL );

                لكل( i = 0; i < پورټ_ټول_عدد_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    إذا( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                          پورټ_MPU_RASR_REGION_ENABLE_BITMASK ) == پورټ_MPU_RASR_REGION_ENABLE_BITMASK )
                    {
                        ul_Region_پیل = پورټ_ایستل_لومړی_پته_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR );
                        ul_Region_اندازه = پورټ_ایستل_REGION_اندازه_FROM_RASR( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR );
                        ul_Region_پای_ټکی = ul_Region_پیل + ul_Region_اندازه;

                        إذا( پورټ_IS_پته_WITHIN_RANGE( ul_بفر_پیل_پته,
                                                         ul_Region_پیل,
                                                         ul_Region_پای_ټکی ) &&
                            پورټ_IS_پته_WITHIN_RANGE( ul_بفر_پای_ټکی_پته,
                                                         ul_Region_پیل,
                                                         ul_Region_پای_ټکی ) )
                        {
                            ulMPURegionAccessPermissions = xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                                                           پورټ_MPU_RASR_AP_BITMASK;

                            إذا( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
                            {
                                إذا( ( ulMPURegionAccessPermissions == پورټ_MPU_REGION_PRIV_RW_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == پورټ_MPU_REGION_PRIV_RO_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == پورټ_MPU_REGION_PRIV_RW_UNPRIV_RW ) )
                                {
                                    xAccessGranted = pdTRUE;
                                    اكسر;
                                }
                            }
                            وإلا إذا( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
                            {
                                إذا( ulMPURegionAccessPermissions == پورټ_MPU_REGION_PRIV_RW_UNPRIV_RW )
                                {
                                    xAccessGranted = pdTRUE;
                                    اكسر;
                                }
                            }
                        }
                    }
                }
            }
        }

        أرجع xAccessGranted;
    }

#د_که_پای /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/

بنسټ_Type_t x_پورټ_Is_Inside_مداخله( فراغ )
{
    uint32_t ul_Current_مداخله;
    بنسټ_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_مداخله )::"memory" );

    إذا( ul_Current_مداخله == 0 )
    {
        xReturn = pdFALSE;
    }
    وإلا
    {
        xReturn = pdTRUE;
    }

    أرجع xReturn;
}

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورټ_Grant_Access_منزل_Kernel_Object( TaskHandle_t x_دننی_Task_Handle,
                                         int32_t l_دننی_شاخص_د_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ثبت_شاخص, ul_Access_Control_List_ثبت_بټ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ثبت_شاخص = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object / پورټ_ACL_ثبت_اندازه_بټونه );
        ul_Access_Control_List_ثبت_بټ = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object % پورټ_ACL_ثبت_اندازه_بټونه );

        xTaskMpuSettings = xTaskGetMPUSettings( x_دننی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ثبت_شاخص ] |= ( 1U << ul_Access_Control_List_ثبت_بټ );
    }

#د_که_پای /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورټ_Revoke_Access_منزل_Kernel_Object( TaskHandle_t x_دننی_Task_Handle,
                                          int32_t l_دننی_شاخص_د_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ثبت_شاخص, ul_Access_Control_List_ثبت_بټ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ثبت_شاخص = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object / پورټ_ACL_ثبت_اندازه_بټونه );
        ul_Access_Control_List_ثبت_بټ = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object % پورټ_ACL_ثبت_اندازه_بټونه );

        xTaskMpuSettings = xTaskGetMPUSettings( x_دننی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ثبت_شاخص ] &= ~( 1U << ul_Access_Control_List_ثبت_بټ );
    }

#د_که_پای /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        بنسټ_Type_t x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_دننی_شاخص_د_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ثبت_شاخص, ul_Access_Control_List_ثبت_بټ;
            بنسټ_Type_t xAccessGranted = pdFALSE;
            ثابت xMPU_SETTINGS * xTaskMpuSettings;

            إذا( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            وإلا
            {
                xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

                ul_Access_Control_List_ثبت_شاخص = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object / پورټ_ACL_ثبت_اندازه_بټونه );
                ul_Access_Control_List_ثبت_بټ = ( ( uint32_t ) l_دننی_شاخص_د_Kernel_Object % پورټ_ACL_ثبت_اندازه_بټونه );

                إذا( ( xTaskMpuSettings->ulTaskFlags & پورټ_TASK_IS_PRIVILEGED_FLAG ) == پورټ_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                وإلا
                {
                    إذا( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ثبت_شاخص ] & ( 1U << ul_Access_Control_List_ثبت_بټ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            أرجع xAccessGranted;
        }

    #وإلا /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        بنسټ_Type_t x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( int32_t l_دننی_شاخص_د_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( فراغ ) l_دننی_شاخص_د_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            أرجع pdTRUE;
        }

    #د_که_پای /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#د_که_پای /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/
