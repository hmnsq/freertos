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
#تعریف_کن MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

/* MPU includes. */
#ضمن "mpu_wrappers.h"
#ضمن "mpu_syscall_numbers.h"

/* Portasm includes. */
#ضمن "portasm.h"

#لغو_تعریف MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
تعريفنوع فراغ ( * پورت_ISR_t )( فراغ );

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#تعریف_کن پورت_NVIC_SYSTICK_CTRL_REG             ( *( ( متطاير uint32_t * ) 0xe000e010 ) )
#تعریف_کن پورت_NVIC_SYSTICK_بارگیری_REG             ( *( ( متطاير uint32_t * ) 0xe000e014 ) )
#تعریف_کن پورت_NVIC_SYSTICK_CURRENT_مقدار_REG    ( *( ( متطاير uint32_t * ) 0xe000e018 ) )
#تعریف_کن پورت_NVIC_SHPR3_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed20 ) )
#تعریف_کن پورت_NVIC_SHPR2_REG                    ( *( ( متطاير uint32_t * ) 0xe000ed1c ) )
#تعریف_کن پورت_NVIC_SYSTICK_ENABLE_بیت           ( 1UL << 0UL )
#تعریف_کن پورت_NVIC_SYSTICK_INT_بیت              ( 1UL << 1UL )
#تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت              ( 1UL << 2UL )
#تعریف_کن پورت_NVIC_SYSTICK_شمار_FLAG_بیت       ( 1UL << 16UL )
#تعریف_کن پورت_NVIC_PEND_SYSTICK_CLEAR_بیت       ( 1UL << 25UL )
#تعریف_کن پورت_NVIC_PEND_SYSTICK_مجموعه_بیت         ( 1UL << 26UL )
#تعریف_کن پورت_MIN_وقفه_اولویت            ( 255UL )
#تعریف_کن پورت_NVIC_PENDSV_PRI                   ( پورت_MIN_وقفه_اولویت << 16UL )
#تعریف_کن پورت_NVIC_SYSTICK_PRI                  ( پورت_MIN_وقفه_اولویت << 24UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#تعریف_کن پورت_SCB_VTOR_REG                      ( *( ( پورت_ISR_t ** ) 0xe000ed08 ) )
#تعریف_کن پورت_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( متطاير uint32_t * ) 0xe000ed24 ) )
#تعریف_کن پورت_SCB_MEM_FAULT_ENABLE_بیت          ( 1UL << 16UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#تعریف_کن پورت_وکتور_شاخص_SVC       ( 11 )
#تعریف_کن پورت_وکتور_شاخص_PENDSV    ( 14 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#تعریف_کن پورت_PSR_پشته_PADDING_ماسک              ( 1UL << 9UL )
#تعریف_کن پورت_EXC_RETURN_پشته_قاب_TYPE_ماسک    ( 1UL << 4UL )

/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#تعریف_کن پورت_جابه_جایی_مقصد_LR     ( 5 )
#تعریف_کن پورت_جابه_جایی_مقصد_PC     ( 6 )
#تعریف_کن پورت_جابه_جایی_مقصد_PSR    ( 7 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#تعریف_کن پورت_MPU_TYPE_REG                            ( *( ( متطاير uint32_t * ) 0xe000ed90 ) )
#تعریف_کن پورت_MPU_CTRL_REG                            ( *( ( متطاير uint32_t * ) 0xe000ed94 ) )

#تعریف_کن پورت_MPU_RBAR_REG                            ( *( ( متطاير uint32_t * ) 0xe000ed9c ) )
#تعریف_کن پورت_MPU_RASR_REG                            ( *( ( متطاير uint32_t * ) 0xe000eda0 ) )

/* MPU Region Attribute and Size Register (RASR) bitmasks. */
#تعریف_کن پورت_MPU_RASR_AP_BITMASK                     ( 0x7UL << 24UL )
#تعریف_کن پورت_MPU_RASR_S_C_B_BITMASK                  ( 0x7UL )
#تعریف_کن پورت_MPU_RASR_S_C_B_LOCATION                 ( 16UL )
#تعریف_کن پورت_MPU_RASR_اندازه_BITMASK                   ( 0x1FUL << 1UL )
#تعریف_کن پورت_MPU_RASR_REGION_ENABLE_BITMASK          ( 0x1UL )

/* MPU Region Base Address Register (RBAR) bitmasks. */
#تعریف_کن پورت_MPU_RBAR_آدرس_BITMASK                ( 0xFFFFFF00UL )
#تعریف_کن پورت_MPU_RBAR_REGION_عدد_VALID_BITMASK    ( 0x1UL << 4UL )
#تعریف_کن پورت_MPU_RBAR_REGION_عدد_BITMASK          ( 0x0000000FUL )

/* MPU Control Register (MPU_CTRL) bitmasks. */
#تعریف_کن پورت_MPU_CTRL_ENABLE_BITMASK                 ( 0x1UL )
#تعریف_کن پورت_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK ( 0x1UL << 2UL ) /* PRIVDEFENA bit. */

/* Expected value of the portMPU_TYPE register. */
#تعریف_کن پورت_EXPECTED_MPU_TYPE_مقدار                 ( 0x8UL << 8UL ) /* 8 DREGION unified. */

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#تعریف_کن پورت_استخراج_اولی_آدرس_FROM_RBAR( rbar ) \
    ( ( rbar ) & پورت_MPU_RBAR_آدرس_BITMASK )

/* Extract size of the MPU region as encoded in the
 * RASR (Region Attribute and Size Register) value. */
#تعریف_کن پورت_استخراج_REGION_اندازه_FROM_RASR( rasr ) \
    ( 1 << ( ( ( ( rasr ) & پورت_MPU_RASR_اندازه_BITMASK ) >> 1 )+ 1 ) )

/* Does addr lies within [start, end] address range? */
#تعریف_کن پورت_IS_آدرس_WITHIN_RANGE( addr, شروع, انتها ) \
    ( ( ( addr ) >= ( شروع ) ) && ( ( addr ) <= ( انتها ) ) )

/* Is the access request satisfied by the available permissions? */
#تعریف_کن پورت_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#تعریف_کن پورت_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کن پورت_جمع_کن_UINT32_WILL_سرریز( a, b )    ( ( a ) > ( پورت_UINT32_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#تعریف_کن پورت_MAX_24_بیت_عدد       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#تعریف_کن پورت_MISSED_COUNTS_ضریب    ( 94UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#تعریف_کن پورت_INITIAL_XPSR    ( 0x01000000 )

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
#تعریف_کن پورت_INITIAL_EXC_RETURN    ( 0xfffffffdUL )

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#تعریف_کن پورت_CONTROL_PRIVILEGED_ماسک         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#تعریف_کن پورت_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#تعریف_کن پورت_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#اگر_تعریف_نشده configSYSTICK_CLOCK_HZ
    #تعریف_کن configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت_CONFIG    ( پورت_NVIC_SYSTICK_CLK_بیت )
#وإلا
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #تعریف_کن پورت_NVIC_SYSTICK_CLK_بیت_CONFIG    ( 0 )
#پایان_اگر

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#اگر_تعریف_شده config_TASK_RETURN_آدرس
    #تعریف_کن پورت_TASK_RETURN_آدرس    config_TASK_RETURN_آدرس
#وإلا
    #تعریف_کن پورت_TASK_RETURN_آدرس    prvTaskExitError
#پایان_اگر

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#تعریف_کن پورت_PRELOAD_REGISTERS    1

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
    ساكن فراغ prv_راهاندازی_MPU( فراغ ) PRIVILEGED_FUNCTION;

#پایان_اگر /* configENABLE_MPU */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
پایه_Type_t x_پورت_Is_Inside_وقفه( فراغ );

/**
 * @brief Yield the processor.
 */
فراغ v_پورت_Yield( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
فراغ v_پورت_Enter_Critical( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
فراغ v_پورت_Exit_Critical( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
فراغ SysTick_Handler( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
پورت_DONT_DISCARD فراغ v_پورت_SVCHandler_C( uint32_t * pul_Caller_پشته_آدرس ) PRIVILEGED_FUNCTION;

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    فراغ vSystemCallEnter( uint32_t * pul_Task_پشته,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_عدد ) PRIVILEGED_FUNCTION;

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    فراغ vRequestSystemCallExit( فراغ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    فراغ vSystemCallExit( uint32_t * pul_System_Call_پشته,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#إذا ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    پایه_Type_t x_پورت_Is_Task_Privileged( فراغ ) PRIVILEGED_FUNCTION;

#پایان_اگر /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_داده ساكن پایه_Type_t xSchedulerRunning = pdFALSE;

#پایان_اگر

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
PRIVILEGED_داده ساكن متطاير uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_داده ساكن uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_داده ساكن uint32_t x_بیشینه_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_داده ساكن uint32_t ulStoppedTimerCompensation = 0;

#پایان_اگر /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#إذا ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) فراغ v_پورت_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_زمان )
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
        __asm متطاير ( "cpsid i" ::: "memory" );
        __asm متطاير ( "dsb" );
        __asm متطاير ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        إذا( e_Task_Confirm_Sleep_نما_وضعیت() == eAbortSleep )
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
                __asm متطاير ( "dsb" ::: "memory" );
                __asm متطاير ( "wfi" );
                __asm متطاير ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_زمان );

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
            __asm متطاير ( "cpsie i" ::: "memory" );
        }
    }

#پایان_اگر /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) فراغ v_پورت_راهاندازی_Timer_وقفه( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #إذا ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_نرخ_HZ );
        x_بیشینه_Possible_Suppressed_Ticks = پورت_MAX_24_بیت_عدد / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = پورت_MISSED_COUNTS_ضریب / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #پایان_اگر /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت_CONFIG;
    پورت_NVIC_SYSTICK_CURRENT_مقدار_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    پورت_NVIC_SYSTICK_بارگیری_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_نرخ_HZ ) - 1UL;
    پورت_NVIC_SYSTICK_CTRL_REG = پورت_NVIC_SYSTICK_CLK_بیت_CONFIG | پورت_NVIC_SYSTICK_INT_بیت | پورت_NVIC_SYSTICK_ENABLE_بیت;
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
    پورت_DISABLE_INTERRUPTS();

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

    ساكن uint32_t prv_Get_MPURegion_اندازه_Setting( uint32_t ul_Actual_اندازه_درون_بایتها )
    {
        uint32_t ul_Region_اندازه, ul_Return_مقدار = 7UL;

        /* 256 is the smallest region size, 31 is the largest valid value for
         * ulReturnValue. */
        لكل( ul_Region_اندازه = 256UL; ul_Return_مقدار < 31UL; ( ul_Region_اندازه <<= 1UL ) )
        {
            إذا( ul_Actual_اندازه_درون_بایتها <= ul_Region_اندازه )
            {
                اكسر;
            }
            وإلا
            {
                ul_Return_مقدار++;
            }
        }

        /* Shift the code by one before returning so it can be written directly
         * into the correct bit position of the attribute register. */
        أرجع( ul_Return_مقدار << 1UL );
    }

#پایان_اگر /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    ساكن فراغ prv_راهاندازی_MPU( فراغ ) /* PRIVILEGED_FUNCTION */
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

        #پایان_اگر /* defined( __ARMCC_VERSION ) */

        /* Ensure that the MPU is present. */
        configASSERT( پورت_MPU_TYPE_REG == پورت_EXPECTED_MPU_TYPE_مقدار );

        /* Check that the MPU is present. */
        إذا( پورت_MPU_TYPE_REG == پورت_EXPECTED_MPU_TYPE_مقدار )
        {
            /* Setup privileged flash as Read Only so that privileged tasks can
             * read it but not modify. */
            پورت_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                 ( پورت_MPU_RBAR_REGION_عدد_VALID_BITMASK ) |
                                 ( پورت_PRIVILEGED_FLASH_REGION ) );

            پورت_MPU_RASR_REG = ( ( پورت_MPU_REGION_PRIV_RO_UNPRIV_NA ) |
                                 ( ( configS_C_B_FLASH & پورت_MPU_RASR_S_C_B_BITMASK ) << پورت_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                 ( پورت_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup unprivileged flash as Read Only by both privileged and
             * unprivileged tasks. All tasks can read it but no-one can modify. */
            پورت_MPU_RBAR_REG = ( ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                 ( پورت_MPU_RBAR_REGION_عدد_VALID_BITMASK ) |
                                 ( پورت_UNPRIVILEGED_FLASH_REGION ) );

            پورت_MPU_RASR_REG = ( ( پورت_MPU_REGION_PRIV_RO_UNPRIV_RO ) |
                                 ( ( configS_C_B_FLASH & پورت_MPU_RASR_S_C_B_BITMASK ) << پورت_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                 ( پورت_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup RAM containing kernel data for privileged access only. */
            پورت_MPU_RBAR_REG = ( ( uint32_t ) __privileged_sram_start__ ) | /* Base address. */
                                 ( پورت_MPU_RBAR_REGION_عدد_VALID_BITMASK ) |
                                 ( پورت_PRIVILEGED_RAM_REGION );

            پورت_MPU_RASR_REG = ( ( پورت_MPU_REGION_PRIV_RW_UNPRIV_NA ) |
                                 ( پورت_MPU_REGION_EXECUTE_NEVER ) |
                                 ( ( configS_C_B_SRAM & پورت_MPU_RASR_S_C_B_BITMASK ) << پورت_MPU_RASR_S_C_B_LOCATION ) |
                                 prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __privileged_sram_end__ - ( uint32_t ) __privileged_sram_start__ ) |
                                 ( پورت_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Enable MPU with privileged background access i.e. unmapped
             * regions have privileged access. */
            پورت_MPU_CTRL_REG |= ( پورت_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK |
                                  پورت_MPU_CTRL_ENABLE_BITMASK );
        }
    }

#پایان_اگر /* configENABLE_MPU */

/*-----------------------------------------------------------*/

فراغ v_پورت_Yield( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm متطاير ( "dsb" ::: "memory" );
    __asm متطاير ( "isb" );
}

/*-----------------------------------------------------------*/

فراغ v_پورت_Enter_Critical( فراغ ) /* PRIVILEGED_FUNCTION */
{
    پورت_DISABLE_INTERRUPTS();
    ulCriticalNesting++;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm متطاير ( "dsb" ::: "memory" );
    __asm متطاير ( "isb" );
}

/*-----------------------------------------------------------*/

فراغ v_پورت_Exit_Critical( فراغ ) /* PRIVILEGED_FUNCTION */
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    إذا( ulCriticalNesting == 0 )
    {
        پورت_ENABLE_INTERRUPTS();
    }
}

/*-----------------------------------------------------------*/

فراغ SysTick_Handler( فراغ ) /* PRIVILEGED_FUNCTION */
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

فراغ v_پورت_SVCHandler_C( uint32_t * pul_Caller_پشته_آدرس ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
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

        #پایان_اگر /* defined( __ARMCC_VERSION ) */

    #پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    uint32_t ulPC;
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_پشته_آدرس[ پورت_جابه_جایی_مقصد_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    بدل( ucSVCNumber )
    {
        حالة پورت_SVC_شروع_SCHEDULER:
            /* Setup the context of the first task so that the first task starts
             * executing. */
            v_Restore_Context_از_اولی_Task();
            اكسر;

    #إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        حالة پورت_SVC_RAISE_PRIVILEGE:
            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            إذا( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            اكسر;

    #پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #إذا ( configENABLE_MPU == 1 )

        حالة پورت_SVC_YIELD:
            v_پورت_Yield();
            اكسر;

    #پایان_اگر /* configENABLE_MPU == 1 */

        افتراضي:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vSystemCallEnter( uint32_t * pul_Task_پشته,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_عدد ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        خارجي UBaseType_t uxSystemCallImplementations[ رقم_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_پشته;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ثابت uint32_t ul_Hardware_Saved_Exception_قاب_اندازه = 8;

        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __syscalls_flash_start__;
            خارجي uint32_t * __syscalls_flash_end__;

        #وإلا

            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __syscalls_flash_start__[];
            خارجي uint32_t __syscalls_flash_end__[];

        #پایان_اگر /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_پشته[ پورت_جابه_جایی_مقصد_PC ];
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
            ( pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته == عدم ) &&
            ( uxSystemCallImplementations[ uc_System_Call_عدد ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_پشته = pxMpuSettings->x_System_Call_پشته_Info.pul_System_Call_پشته;

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_پشته = pul_System_Call_پشته - ul_Hardware_Saved_Exception_قاب_اندازه;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_قاب_اندازه; i++ )
            {
                pul_System_Call_پشته[ i ] = pul_Task_پشته[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.ul_Link_ثبات_At_System_Call_مدخل = pul_Task_پشته[ پورت_جابه_جایی_مقصد_LR ];

            /* Use the pulSystemCallStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_System_Call_پشته ) );

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_PC ] = uxSystemCallImplementations[ uc_System_Call_عدد ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته = pul_Task_پشته + ul_Hardware_Saved_Exception_قاب_اندازه;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            إذا( ( pul_Task_پشته[ پورت_جابه_جایی_مقصد_PSR ] & پورت_PSR_پشته_PADDING_ماسک ) == پورت_PSR_پشته_PADDING_ماسک )
            {
                pxMpuSettings->ulTaskFlags |= پورت_پشته_قاب_HAS_PADDING_FLAG;
            }
            وإلا
            {
                pxMpuSettings->ulTaskFlags &= ( ~پورت_پشته_قاب_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_PSR ] &= ( ~پورت_PSR_پشته_PADDING_ماسک );

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

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vRequestSystemCallExit( فراغ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm متطاير ( "svc %0 \n" ::"i" ( پورت_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    فراغ vSystemCallExit( uint32_t * pul_System_Call_پشته,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        خارجي TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_پشته;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ثابت uint32_t ul_Hardware_Saved_Exception_قاب_اندازه = 8;

        #إذا defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            خارجي uint32_t * __privileged_functions_start__;
            خارجي uint32_t * __privileged_functions_end__;

        #وإلا

            /* Declaration when these variable are exported from linker scripts. */
            خارجي uint32_t __privileged_functions_start__[];
            خارجي uint32_t __privileged_functions_end__[];

        #پایان_اگر /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_پشته[ پورت_جابه_جایی_مقصد_PC ];
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
            ( pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته != عدم ) )
        {
            pul_Task_پشته = pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته;

            /* Make space on the task stack for the stack frame. */
            pul_Task_پشته = pul_Task_پشته - ul_Hardware_Saved_Exception_قاب_اندازه;

            /* Copy the stack frame. */
            لكل( i = 0; i < ul_Hardware_Saved_Exception_قاب_اندازه; i++ )
            {
                pul_Task_پشته[ i ] = pul_System_Call_پشته[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm متطاير ( "msr psp, %0" : : "r" ( pul_Task_پشته ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_پشته[ پورت_جابه_جایی_مقصد_PC ] = pxMpuSettings->x_System_Call_پشته_Info.ul_Link_ثبات_At_System_Call_مدخل;

            /* Ensure that LR has a valid value.*/
            pul_Task_پشته[ پورت_جابه_جایی_مقصد_LR ] = pxMpuSettings->x_System_Call_پشته_Info.ul_Link_ثبات_At_System_Call_مدخل;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            إذا( ( pxMpuSettings->ulTaskFlags & پورت_پشته_قاب_HAS_PADDING_FLAG ) == پورت_پشته_قاب_HAS_PADDING_FLAG )
            {
                pul_Task_پشته[ پورت_جابه_جایی_مقصد_PSR ] |= پورت_PSR_پشته_PADDING_ماسک;
            }
            وإلا
            {
                pul_Task_پشته[ پورت_جابه_جایی_مقصد_PSR ] &= ( ~پورت_PSR_پشته_PADDING_ماسک );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_پشته_Info.pul_Task_پشته = عدم;

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

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    پایه_Type_t x_پورت_Is_Task_Privileged( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        پایه_Type_t xTaskIsPrivileged = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

        إذا( ( xTaskMpuSettings->ulTaskFlags & پورت_TASK_IS_PRIVILEGED_FLAG ) == پورت_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        أرجع xTaskIsPrivileged;
    }

#پایان_اگر /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                         TaskFunction_t px_کد,
                                         فراغ * pvParameters,
                                         پایه_Type_t x_پیاپی_Privileged,
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
        xMPUSettings->ulContext[ 13 ] = ( uint32_t ) پورت_TASK_RETURN_آدرس; /* LR. */
        xMPUSettings->ulContext[ 14 ] = ( uint32_t ) px_کد;                  /* PC. */
        xMPUSettings->ulContext[ 15 ] = پورت_INITIAL_XPSR;                     /* xPSR. */

        xMPUSettings->ulContext[ 16 ] = ( uint32_t ) ( px_بالاترین_از_پشته - 8 ); /* PSP with the hardware saved stack. */
        إذا( x_پیاپی_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= پورت_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) پورت_INITIAL_CONTROL_PRIVILEGED; /* CONTROL. */
        }
        وإلا
        {
            xMPUSettings->ulTaskFlags &= ( ~پورت_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) پورت_INITIAL_CONTROL_UNPRIVILEGED; /* CONTROL. */
        }
        xMPUSettings->ulContext[ 18 ] = پورت_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */

        #إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته = &( xMPUSettings->x_System_Call_پشته_Info.ul_System_Call_پشته_میانگیر[ config_SYSTEM_CALL_پشته_اندازه - 1 ] );
            xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_پشته_Info.pul_System_Call_پشته ) &
                                                                                     ( uint32_t ) ( ~( پورت_BYTE_ALIGNMENT_ماسک ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_پشته_Info.pul_Task_پشته = عدم;
        }
        #پایان_اگر /* configUSE_MPU_WRAPPERS_V1 == 0 */

        أرجع &( xMPUSettings->ulContext[ 19 ] );
    }

#وإلا /* configENABLE_MPU */

    پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                         TaskFunction_t px_کد,
                                         فراغ * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #إذا ( پورت_PRELOAD_REGISTERS == 0 )
        {
            px_بالاترین_از_پشته--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_بالاترین_از_پشته = پورت_INITIAL_XPSR;                        /* xPSR. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد;                  /* PC. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_TASK_RETURN_آدرس; /* LR. */
            px_بالاترین_از_پشته -= 5;                                       /* R12, R3, R2 and R1. */
            *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters;            /* R0. */
            px_بالاترین_از_پشته -= 9;                                       /* R11..R4, EXC_RETURN. */
            *px_بالاترین_از_پشته = پورت_INITIAL_EXC_RETURN;
        }
        #وإلا /* portPRELOAD_REGISTERS */
        {
            px_بالاترین_از_پشته--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_بالاترین_از_پشته = پورت_INITIAL_XPSR;                        /* xPSR. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد;                  /* PC. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_TASK_RETURN_آدرس; /* LR. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x12121212UL;            /* R12. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x03030303UL;            /* R3. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x02020202UL;            /* R2. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x01010101UL;            /* R1. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters;            /* R0. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x11111111UL;            /* R11. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x10101010UL;            /* R10. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x09090909UL;            /* R09. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x08080808UL;            /* R08. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x07070707UL;            /* R07. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x06060606UL;            /* R06. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x05050505UL;            /* R05. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = ( پشته_Type_t ) 0x04040404UL;            /* R04. */
            px_بالاترین_از_پشته--;
            *px_بالاترین_از_پشته = پورت_INITIAL_EXC_RETURN;                  /* EXC_RETURN. */
        }
        #پایان_اگر /* portPRELOAD_REGISTERS */

        أرجع px_بالاترین_از_پشته;
    }

#پایان_اگر /* configENABLE_MPU */

/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ ) /* PRIVILEGED_FUNCTION */
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
        ثابت پورت_ISR_t * ثابت px_وکتور_جدول = پورت_SCB_VTOR_REG;

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
        configASSERT( px_وکتور_جدول[ پورت_وکتور_شاخص_SVC ] == SVC_Handler );
        configASSERT( px_وکتور_جدول[ پورت_وکتور_شاخص_PENDSV ] == PendSV_Handler );
    }
    #پایان_اگر /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
     * the highest priority. */
    پورت_NVIC_SHPR3_REG |= پورت_NVIC_PENDSV_PRI;
    پورت_NVIC_SHPR3_REG |= پورت_NVIC_SYSTICK_PRI;
    پورت_NVIC_SHPR2_REG = 0;

    #إذا ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_راهاندازی_MPU();
    }
    #پایان_اگر /* configENABLE_MPU */

    /* Start the timer that generates the tick ISR. Interrupts are disabled
     * here already. */
    v_پورت_راهاندازی_Timer_وقفه();

    /* Initialize the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    #إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #پایان_اگر

    /* Start the first task. */
    v_شروع_اولی_Task();

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

فراغ v_پورت_انتها_Scheduler( فراغ ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}

/*-----------------------------------------------------------*/

#إذا ( configENABLE_MPU == 1 )

    فراغ v_پورت_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ثابت بنية x_حافظه_REGION * ثابت xRegions,
                                    پشته_Type_t * px_Bottom_از_پشته,
                                    config_پشته_عمق_TYPE ux_پشته_عمق )
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

        #پایان_اگر /* defined( __ARMCC_VERSION ) */

        int32_t l_شاخص;
        uint32_t ul;

        إذا( xRegions == عدم )
        {
            /* No MPU regions are specified so allow access to all RAM. */
            xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                ( ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
                  ( پورت_MPU_RBAR_REGION_عدد_VALID_BITMASK ) |
                  ( پورت_پشته_REGION ) );                   /* Region number. */

            xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                ( ( پورت_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                  ( پورت_MPU_REGION_EXECUTE_NEVER ) |
                  ( ( configS_C_B_SRAM & پورت_MPU_RASR_S_C_B_BITMASK ) << پورت_MPU_RASR_S_C_B_LOCATION ) |
                  ( prv_Get_MPURegion_اندازه_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
                  ( پورت_MPU_RASR_REGION_ENABLE_BITMASK ) );


            /* Invalidate user configurable regions. */
            لكل( ul = 1UL; ul <= پورت_رقم_CONFIGURABLE_REGIONS; ul++ )
            {
                xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | پورت_MPU_RBAR_REGION_عدد_VALID_BITMASK );
                xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
            }
        }
        وإلا
        {
            /* This function is called automatically when the task is created - in
             * which case the stack region parameters will be valid.  At all other
             * times the stack parameters will not be valid and it is assumed that the
             * stack region has already been configured. */
            إذا( ux_پشته_عمق > 0 )
            {
                /* Define the region that allows access to the stack. */
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                    ( ( ( uint32_t ) px_Bottom_از_پشته ) |
                      ( پورت_MPU_RBAR_REGION_عدد_VALID_BITMASK ) |
                      ( پورت_پشته_REGION ) ); /* Region number. */

                xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                    ( ( پورت_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                      ( پورت_MPU_REGION_EXECUTE_NEVER ) |
                      ( prv_Get_MPURegion_اندازه_Setting( ux_پشته_عمق * ( uint32_t ) حجم( پشته_Type_t ) ) ) |
                      ( ( configS_C_B_SRAM & پورت_MPU_RASR_S_C_B_BITMASK ) << پورت_MPU_RASR_S_C_B_LOCATION ) |
                      ( پورت_MPU_RASR_REGION_ENABLE_BITMASK ) );
            }

            l_شاخص = 0;

            لكل( ul = 1UL; ul <= پورت_رقم_CONFIGURABLE_REGIONS; ul++ )
            {
                إذا( ( xRegions[ l_شاخص ] ).ul_درازی_درون_بایتها > 0UL )
                {
                    /* Translate the generic region definition contained in
                     * xRegions into the CM0+ specific MPU settings that are then
                     * stored in xMPUSettings. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR =
                        ( ( uint32_t ) xRegions[ l_شاخص ].pv_پایه_آدرس ) |
                        ( پورت_MPU_RBAR_REGION_عدد_VALID_BITMASK ) |
                        ( ul - 1UL ); /* Region number. */

                    xMPUSettings->xRegionsSettings[ ul ].ulRASR =
                        ( prv_Get_MPURegion_اندازه_Setting( xRegions[ l_شاخص ].ul_درازی_درون_بایتها ) ) |
                        ( xRegions[ l_شاخص ].ulParameters ) |
                        ( پورت_MPU_RASR_REGION_ENABLE_BITMASK );
                }
                وإلا
                {
                    /* Invalidate the region. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | پورت_MPU_RBAR_REGION_عدد_VALID_BITMASK );
                    xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
                }

            l_شاخص++;
        }
    }
}

#پایان_اگر /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    پایه_Type_t x_پورت_Is_Authorized_مقصد_Access_میانگیر( ثابت فراغ * pv_میانگیر,
                                                size_t x_میانگیر_درازی,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_میانگیر_شروع_آدرس, ul_میانگیر_انتها_آدرس;
        uint32_t ul_Region_شروع, ul_Region_اندازه, ul_Region_انتها;
        uint32_t ulMPURegionAccessPermissions;
        پایه_Type_t xAccessGranted = pdFALSE;
        ثابت xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( عدم ); /* Calling task's MPU settings. */

        إذا( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        وإلا إذا( ( xTaskMpuSettings->ulTaskFlags & پورت_TASK_IS_PRIVILEGED_FLAG ) == پورت_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        وإلا
        {
            إذا( پورت_جمع_کن_UINT32_WILL_سرریز( ( ( uint32_t ) pv_میانگیر ), ( ( uint32_t ) x_میانگیر_درازی - 1UL ) ) == pdFALSE )
            {
                ul_میانگیر_شروع_آدرس = ( uint32_t ) pv_میانگیر;
                ul_میانگیر_انتها_آدرس = ( ( ( uint32_t ) pv_میانگیر ) + ( uint32_t ) x_میانگیر_درازی - 1UL );

                لكل( i = 0; i < پورت_مجموع_رقم_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    إذا( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                          پورت_MPU_RASR_REGION_ENABLE_BITMASK ) == پورت_MPU_RASR_REGION_ENABLE_BITMASK )
                    {
                        ul_Region_شروع = پورت_استخراج_اولی_آدرس_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR );
                        ul_Region_اندازه = پورت_استخراج_REGION_اندازه_FROM_RASR( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR );
                        ul_Region_انتها = ul_Region_شروع + ul_Region_اندازه;

                        إذا( پورت_IS_آدرس_WITHIN_RANGE( ul_میانگیر_شروع_آدرس,
                                                         ul_Region_شروع,
                                                         ul_Region_انتها ) &&
                            پورت_IS_آدرس_WITHIN_RANGE( ul_میانگیر_انتها_آدرس,
                                                         ul_Region_شروع,
                                                         ul_Region_انتها ) )
                        {
                            ulMPURegionAccessPermissions = xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                                                           پورت_MPU_RASR_AP_BITMASK;

                            إذا( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
                            {
                                إذا( ( ulMPURegionAccessPermissions == پورت_MPU_REGION_PRIV_RW_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == پورت_MPU_REGION_PRIV_RO_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == پورت_MPU_REGION_PRIV_RW_UNPRIV_RW ) )
                                {
                                    xAccessGranted = pdTRUE;
                                    اكسر;
                                }
                            }
                            وإلا إذا( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
                            {
                                إذا( ulMPURegionAccessPermissions == پورت_MPU_REGION_PRIV_RW_UNPRIV_RW )
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

#پایان_اگر /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_Is_Inside_وقفه( فراغ )
{
    uint32_t ul_Current_وقفه;
    پایه_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm متطاير ( "mrs %0, ipsr" : "=r" ( ul_Current_وقفه )::"memory" );

    إذا( ul_Current_وقفه == 0 )
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

    فراغ v_پورت_Grant_Access_مقصد_Kernel_Object( TaskHandle_t x_داخلی_Task_Handle,
                                         int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_مدخل_شاخص, ul_Access_Control_List_مدخل_بیت;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_مدخل_شاخص = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object / پورت_ACL_مدخل_اندازه_بیتها );
        ul_Access_Control_List_مدخل_بیت = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object % پورت_ACL_مدخل_اندازه_بیتها );

        xTaskMpuSettings = xTaskGetMPUSettings( x_داخلی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_مدخل_شاخص ] |= ( 1U << ul_Access_Control_List_مدخل_بیت );
    }

#پایان_اگر /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    فراغ v_پورت_Revoke_Access_مقصد_Kernel_Object( TaskHandle_t x_داخلی_Task_Handle,
                                          int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_مدخل_شاخص, ul_Access_Control_List_مدخل_بیت;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_مدخل_شاخص = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object / پورت_ACL_مدخل_اندازه_بیتها );
        ul_Access_Control_List_مدخل_بیت = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object % پورت_ACL_مدخل_اندازه_بیتها );

        xTaskMpuSettings = xTaskGetMPUSettings( x_داخلی_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_مدخل_شاخص ] &= ~( 1U << ul_Access_Control_List_مدخل_بیت );
    }

#پایان_اگر /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        پایه_Type_t x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_مدخل_شاخص, ul_Access_Control_List_مدخل_بیت;
            پایه_Type_t xAccessGranted = pdFALSE;
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

                ul_Access_Control_List_مدخل_شاخص = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object / پورت_ACL_مدخل_اندازه_بیتها );
                ul_Access_Control_List_مدخل_بیت = ( ( uint32_t ) l_داخلی_شاخص_از_Kernel_Object % پورت_ACL_مدخل_اندازه_بیتها );

                إذا( ( xTaskMpuSettings->ulTaskFlags & پورت_TASK_IS_PRIVILEGED_FLAG ) == پورت_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                وإلا
                {
                    إذا( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_مدخل_شاخص ] & ( 1U << ul_Access_Control_List_مدخل_بیت ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            أرجع xAccessGranted;
        }

    #وإلا /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        پایه_Type_t x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( int32_t l_داخلی_شاخص_از_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( فراغ ) l_داخلی_شاخص_از_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            أرجع pdTRUE;
        }

    #پایان_اگر /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#پایان_اگر /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/
