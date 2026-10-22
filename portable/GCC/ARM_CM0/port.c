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
#నిర్వచించు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

/* MPU includes. */
#అన్తర్భావ "mpu_wrappers.h"
#అన్తర్భావ "mpu_syscall_numbers.h"

/* Portasm includes. */
#అన్తర్భావ "portasm.h"

#నిర్వచనం_రద్దు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
రకనిర్వచనం శూన్య ( * పోర్టు_ISR_t )( శూన్య );

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CTRL_REG             ( *( ( అస్థిర uint32_t * ) 0xe000e010 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG             ( *( ( అస్థిర uint32_t * ) 0xe000e014 ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG    ( *( ( అస్థిర uint32_t * ) 0xe000e018 ) )
#నిర్వచించు పోర్టు_NVIC_SHPR3_REG                    ( *( ( అస్థిర uint32_t * ) 0xe000ed20 ) )
#నిర్వచించు పోర్టు_NVIC_SHPR2_REG                    ( *( ( అస్థిర uint32_t * ) 0xe000ed1c ) )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు           ( 1UL << 0UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_INT_బిట్టు              ( 1UL << 1UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు              ( 1UL << 2UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_లెక్క_FLAG_బిట్టు       ( 1UL << 16UL )
#నిర్వచించు పోర్టు_NVIC_PEND_SYSTICK_CLEAR_బిట్టు       ( 1UL << 25UL )
#నిర్వచించు పోర్టు_NVIC_PEND_SYSTICK_సమితి_బిట్టు         ( 1UL << 26UL )
#నిర్వచించు పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత            ( 255UL )
#నిర్వచించు పోర్టు_NVIC_PENDSV_PRI                   ( పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత << 16UL )
#నిర్వచించు పోర్టు_NVIC_SYSTICK_PRI                  ( పోర్టు_MIN_అంతరాయం_ప్రాధాన్యత << 24UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#నిర్వచించు పోర్టు_SCB_VTOR_REG                      ( *( ( పోర్టు_ISR_t ** ) 0xe000ed08 ) )
#నిర్వచించు పోర్టు_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( అస్థిర uint32_t * ) 0xe000ed24 ) )
#నిర్వచించు పోర్టు_SCB_MEM_FAULT_ENABLE_బిట్టు          ( 1UL << 16UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#నిర్వచించు పోర్టు_సదిశ_సూచీ_SVC       ( 11 )
#నిర్వచించు పోర్టు_సదిశ_సూచీ_PENDSV    ( 14 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#నిర్వచించు పోర్టు_PSR_దొంతర_PADDING_ముసుగు              ( 1UL << 9UL )
#నిర్వచించు పోర్టు_EXC_RETURN_దొంతర_చట్రం_TYPE_ముసుగు    ( 1UL << 4UL )

/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_LR     ( 5 )
#నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_PC     ( 6 )
#నిర్వచించు పోర్టు_స్థానభ్రంశం_గమ్యం_PSR    ( 7 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#నిర్వచించు పోర్టు_MPU_TYPE_REG                            ( *( ( అస్థిర uint32_t * ) 0xe000ed90 ) )
#నిర్వచించు పోర్టు_MPU_CTRL_REG                            ( *( ( అస్థిర uint32_t * ) 0xe000ed94 ) )

#నిర్వచించు పోర్టు_MPU_RBAR_REG                            ( *( ( అస్థిర uint32_t * ) 0xe000ed9c ) )
#నిర్వచించు పోర్టు_MPU_RASR_REG                            ( *( ( అస్థిర uint32_t * ) 0xe000eda0 ) )

/* MPU Region Attribute and Size Register (RASR) bitmasks. */
#నిర్వచించు పోర్టు_MPU_RASR_AP_BITMASK                     ( 0x7UL << 24UL )
#నిర్వచించు పోర్టు_MPU_RASR_S_C_B_BITMASK                  ( 0x7UL )
#నిర్వచించు పోర్టు_MPU_RASR_S_C_B_LOCATION                 ( 16UL )
#నిర్వచించు పోర్టు_MPU_RASR_కొలత_BITMASK                   ( 0x1FUL << 1UL )
#నిర్వచించు పోర్టు_MPU_RASR_REGION_ENABLE_BITMASK          ( 0x1UL )

/* MPU Region Base Address Register (RBAR) bitmasks. */
#నిర్వచించు పోర్టు_MPU_RBAR_చిరునామా_BITMASK                ( 0xFFFFFF00UL )
#నిర్వచించు పోర్టు_MPU_RBAR_REGION_సంఖ్య_VALID_BITMASK    ( 0x1UL << 4UL )
#నిర్వచించు పోర్టు_MPU_RBAR_REGION_సంఖ్య_BITMASK          ( 0x0000000FUL )

/* MPU Control Register (MPU_CTRL) bitmasks. */
#నిర్వచించు పోర్టు_MPU_CTRL_ENABLE_BITMASK                 ( 0x1UL )
#నిర్వచించు పోర్టు_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK ( 0x1UL << 2UL ) /* PRIVDEFENA bit. */

/* Expected value of the portMPU_TYPE register. */
#నిర్వచించు పోర్టు_EXPECTED_MPU_TYPE_విలువ                 ( 0x8UL << 8UL ) /* 8 DREGION unified. */

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#నిర్వచించు పోర్టు_వెలికితీయి_మొదటి_చిరునామా_FROM_RBAR( rbar ) \
    ( ( rbar ) & పోర్టు_MPU_RBAR_చిరునామా_BITMASK )

/* Extract size of the MPU region as encoded in the
 * RASR (Region Attribute and Size Register) value. */
#నిర్వచించు పోర్టు_వెలికితీయి_REGION_కొలత_FROM_RASR( rasr ) \
    ( 1 << ( ( ( ( rasr ) & పోర్టు_MPU_RASR_కొలత_BITMASK ) >> 1 )+ 1 ) )

/* Does addr lies within [start, end] address range? */
#నిర్వచించు పోర్టు_IS_చిరునామా_WITHIN_RANGE( addr, ప్రారంభం, చివర ) \
    ( ( ( addr ) >= ( ప్రారంభం ) ) && ( ( addr ) <= ( చివర ) ) )

/* Is the access request satisfied by the available permissions? */
#నిర్వచించు పోర్టు_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#నిర్వచించు పోర్టు_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#నిర్వచించు పోర్టు_కూడు_UINT32_WILL_అధికప్రవాహం( a, b )    ( ( a ) > ( పోర్టు_UINT32_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#నిర్వచించు పోర్టు_MAX_24_బిట్టు_సంఖ్య       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#నిర్వచించు పోర్టు_MISSED_COUNTS_గుణకం    ( 94UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#నిర్వచించు పోర్టు_INITIAL_XPSR    ( 0x01000000 )

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
#నిర్వచించు పోర్టు_INITIAL_EXC_RETURN    ( 0xfffffffdUL )

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#నిర్వచించు పోర్టు_CONTROL_PRIVILEGED_ముసుగు         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#నిర్వచించు పోర్టు_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#నిర్వచించు పోర్టు_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#నిర్వచితం_కాకపోతే configSYSTICK_CLOCK_HZ
    #నిర్వచించు configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG    ( పోర్టు_NVIC_SYSTICK_CLK_బిట్టు )
#లేకపోతే
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #నిర్వచించు పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG    ( 0 )
#అయితే_ముగింపు

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#నిర్వచితమైతే config_TASK_RETURN_చిరునామా
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    config_TASK_RETURN_చిరునామా
#లేకపోతే
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    prvTaskExitError
#అయితే_ముగింపు

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#నిర్వచించు పోర్టు_PRELOAD_REGISTERS    1

/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

#ఒకవేళ ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    స్థిర శూన్య prv_అమరిక_MPU( శూన్య ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* configENABLE_MPU */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
పునాది_Type_t x_పోర్టు_Is_Inside_అంతరాయం( శూన్య );

/**
 * @brief Yield the processor.
 */
శూన్య v_పోర్టు_Yield( శూన్య ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
శూన్య v_పోర్టు_Enter_Critical( శూన్య ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
శూన్య v_పోర్టు_Exit_Critical( శూన్య ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
శూన్య SysTick_Handler( శూన్య ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
పోర్టు_DONT_DISCARD శూన్య v_పోర్టు_SVCHandler_C( uint32_t * pul_Caller_దొంతర_చిరునామా ) PRIVILEGED_FUNCTION;

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    శూన్య vSystemCallEnter( uint32_t * pul_Task_దొంతర,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_సంఖ్య ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    శూన్య vRequestSystemCallExit( శూన్య ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    శూన్య vSystemCallExit( uint32_t * pul_System_Call_దొంతర,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ఒకవేళ ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య ) PRIVILEGED_FUNCTION;

#అయితే_ముగింపు /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_దత్తాంశం స్థిర పునాది_Type_t xSchedulerRunning = pdFALSE;

#అయితే_ముగింపు

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
PRIVILEGED_దత్తాంశం స్థిర అస్థిర uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_దత్తాంశం స్థిర uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_దత్తాంశం స్థిర uint32_t x_గరిష్ఠ_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_దత్తాంశం స్థిర uint32_t ulStoppedTimerCompensation = 0;

#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) శూన్య v_పోర్టు_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_సమయం )
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
        __asm అస్థిర ( "cpsid i" ::: "memory" );
        __asm అస్థిర ( "dsb" );
        __asm అస్థిర ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ఒకవేళ( e_Task_Confirm_Sleep_బహుళకం_స్థితి() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm అస్థిర ( "cpsie i" ::: "memory" );
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
                __asm అస్థిర ( "dsb" ::: "memory" );
                __asm అస్థిర ( "wfi" );
                __asm అస్థిర ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_సమయం );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm అస్థిర ( "cpsie i" ::: "memory" );
            __asm అస్థిర ( "dsb" );
            __asm అస్థిర ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm అస్థిర ( "cpsid i" ::: "memory" );
            __asm అస్థిర ( "dsb" );
            __asm అస్థిర ( "isb" );

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
            __asm అస్థిర ( "cpsie i" ::: "memory" );
        }
    }

#అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) శూన్య v_పోర్టు_అమరిక_Timer_అంతరాయం( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #ఒకవేళ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_రేటు_HZ );
        x_గరిష్ఠ_Possible_Suppressed_Ticks = పోర్టు_MAX_24_బిట్టు_సంఖ్య / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = పోర్టు_MISSED_COUNTS_గుణకం / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #అయితే_ముగింపు /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG;
    పోర్టు_NVIC_SYSTICK_CURRENT_విలువ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    పోర్టు_NVIC_SYSTICK_ఎక్కించు_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_రేటు_HZ ) - 1UL;
    పోర్టు_NVIC_SYSTICK_CTRL_REG = పోర్టు_NVIC_SYSTICK_CLK_బిట్టు_CONFIG | పోర్టు_NVIC_SYSTICK_INT_బిట్టు | పోర్టు_NVIC_SYSTICK_ENABLE_బిట్టు;
}

/*-----------------------------------------------------------*/

స్థిర శూన్య prvTaskExitError( శూన్య )
{
    అస్థిర uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    పోర్టు_DISABLE_INTERRUPTS();

    అయితే( ulDummy == 0 )
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

#ఒకవేళ ( configENABLE_MPU == 1 )

    స్థిర uint32_t prv_Get_MPURegion_కొలత_Setting( uint32_t ul_Actual_కొలత_లోపల_బైట్లు )
    {
        uint32_t ul_Region_కొలత, ul_Return_విలువ = 7UL;

        /* 256 is the smallest region size, 31 is the largest valid value for
         * ulReturnValue. */
        కొరకు( ul_Region_కొలత = 256UL; ul_Return_విలువ < 31UL; ( ul_Region_కొలత <<= 1UL ) )
        {
            ఒకవేళ( ul_Actual_కొలత_లోపల_బైట్లు <= ul_Region_కొలత )
            {
                ఆపు;
            }
            లేకపోతే
            {
                ul_Return_విలువ++;
            }
        }

        /* Shift the code by one before returning so it can be written directly
         * into the correct bit position of the attribute register. */
        తిరిగి( ul_Return_విలువ << 1UL );
    }

#అయితే_ముగింపు /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    స్థిర శూన్య prv_అమరిక_MPU( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        #ఒకవేళ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
            * exported from linker scripts. */
            బాహ్య uint32_t * __privileged_functions_start__;
            బాహ్య uint32_t * __privileged_functions_end__;
            బాహ్య uint32_t * __FLASH_segment_start__;
            బాహ్య uint32_t * __FLASH_segment_end__;
            బాహ్య uint32_t * __privileged_sram_start__;
            బాహ్య uint32_t * __privileged_sram_end__;

        #లేకపోతే /* if defined( __ARMCC_VERSION ) */

            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __privileged_functions_start__[];
            బాహ్య uint32_t __privileged_functions_end__[];
            బాహ్య uint32_t __FLASH_segment_start__[];
            బాహ్య uint32_t __FLASH_segment_end__[];
            బాహ్య uint32_t __privileged_sram_start__[];
            బాహ్య uint32_t __privileged_sram_end__[];

        #అయితే_ముగింపు /* defined( __ARMCC_VERSION ) */

        /* Ensure that the MPU is present. */
        configASSERT( పోర్టు_MPU_TYPE_REG == పోర్టు_EXPECTED_MPU_TYPE_విలువ );

        /* Check that the MPU is present. */
        ఒకవేళ( పోర్టు_MPU_TYPE_REG == పోర్టు_EXPECTED_MPU_TYPE_విలువ )
        {
            /* Setup privileged flash as Read Only so that privileged tasks can
             * read it but not modify. */
            పోర్టు_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                 ( పోర్టు_MPU_RBAR_REGION_సంఖ్య_VALID_BITMASK ) |
                                 ( పోర్టు_PRIVILEGED_FLASH_REGION ) );

            పోర్టు_MPU_RASR_REG = ( ( పోర్టు_MPU_REGION_PRIV_RO_UNPRIV_NA ) |
                                 ( ( configS_C_B_FLASH & పోర్టు_MPU_RASR_S_C_B_BITMASK ) << పోర్టు_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_కొలత_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                 ( పోర్టు_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup unprivileged flash as Read Only by both privileged and
             * unprivileged tasks. All tasks can read it but no-one can modify. */
            పోర్టు_MPU_RBAR_REG = ( ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                 ( పోర్టు_MPU_RBAR_REGION_సంఖ్య_VALID_BITMASK ) |
                                 ( పోర్టు_UNPRIVILEGED_FLASH_REGION ) );

            పోర్టు_MPU_RASR_REG = ( ( పోర్టు_MPU_REGION_PRIV_RO_UNPRIV_RO ) |
                                 ( ( configS_C_B_FLASH & పోర్టు_MPU_RASR_S_C_B_BITMASK ) << పోర్టు_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_కొలత_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                 ( పోర్టు_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup RAM containing kernel data for privileged access only. */
            పోర్టు_MPU_RBAR_REG = ( ( uint32_t ) __privileged_sram_start__ ) | /* Base address. */
                                 ( పోర్టు_MPU_RBAR_REGION_సంఖ్య_VALID_BITMASK ) |
                                 ( పోర్టు_PRIVILEGED_RAM_REGION );

            పోర్టు_MPU_RASR_REG = ( ( పోర్టు_MPU_REGION_PRIV_RW_UNPRIV_NA ) |
                                 ( పోర్టు_MPU_REGION_EXECUTE_NEVER ) |
                                 ( ( configS_C_B_SRAM & పోర్టు_MPU_RASR_S_C_B_BITMASK ) << పోర్టు_MPU_RASR_S_C_B_LOCATION ) |
                                 prv_Get_MPURegion_కొలత_Setting( ( uint32_t ) __privileged_sram_end__ - ( uint32_t ) __privileged_sram_start__ ) |
                                 ( పోర్టు_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Enable MPU with privileged background access i.e. unmapped
             * regions have privileged access. */
            పోర్టు_MPU_CTRL_REG |= ( పోర్టు_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK |
                                  పోర్టు_MPU_CTRL_ENABLE_BITMASK );
        }
    }

#అయితే_ముగింపు /* configENABLE_MPU */

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Yield( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm అస్థిర ( "dsb" ::: "memory" );
    __asm అస్థిర ( "isb" );
}

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    పోర్టు_DISABLE_INTERRUPTS();
    ulCriticalNesting++;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm అస్థిర ( "dsb" ::: "memory" );
    __asm అస్థిర ( "isb" );
}

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    ఒకవేళ( ulCriticalNesting == 0 )
    {
        పోర్టు_ENABLE_INTERRUPTS();
    }
}

/*-----------------------------------------------------------*/

శూన్య SysTick_Handler( శూన్య ) /* PRIVILEGED_FUNCTION */
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
            పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు;
        }
        లేకపోతే
        {
            traceISR_EXIT();
        }
    }

    పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ul_మునుపటి_ముసుగు );
}

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_SVCHandler_C( uint32_t * pul_Caller_దొంతర_చిరునామా ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        #ఒకవేళ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __syscalls_flash_start__;
            బాహ్య uint32_t * __syscalls_flash_end__;

        #లేకపోతే

            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __syscalls_flash_start__[];
            బాహ్య uint32_t __syscalls_flash_end__[];

        #అయితే_ముగింపు /* defined( __ARMCC_VERSION ) */

    #అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    uint32_t ulPC;
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_దొంతర_చిరునామా[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    ఎంపిక( ucSVCNumber )
    {
        స్థితి పోర్టు_SVC_ప్రారంభం_SCHEDULER:
            /* Setup the context of the first task so that the first task starts
             * executing. */
            v_Restore_Context_యొక్క_మొదటి_Task();
            ఆపు;

    #ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        స్థితి పోర్టు_SVC_RAISE_PRIVILEGE:
            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            ఒకవేళ( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            ఆపు;

    #అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #ఒకవేళ ( configENABLE_MPU == 1 )

        స్థితి పోర్టు_SVC_YIELD:
            v_పోర్టు_Yield();
            ఆపు;

    #అయితే_ముగింపు /* configENABLE_MPU == 1 */

        అప్రమేయ:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}

/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    శూన్య vSystemCallEnter( uint32_t * pul_Task_దొంతర,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_సంఖ్య ) /* PRIVILEGED_FUNCTION */
    {
        బాహ్య TaskHandle_t pxCurrentTCB;
        బాహ్య UBaseType_t uxSystemCallImplementations[ అంకె_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_దొంతర;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        స్థిరరాశి uint32_t ul_Hardware_Saved_Exception_చట్రం_కొలత = 8;

        #ఒకవేళ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __syscalls_flash_start__;
            బాహ్య uint32_t * __syscalls_flash_end__;

        #లేకపోతే

            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __syscalls_flash_start__[];
            బాహ్య uint32_t __syscalls_flash_end__[];

        #అయితే_ముగింపు /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ];
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
        ఒకవేళ( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర == ఖాళీ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_సంఖ్య ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_దొంతర = pxMpuSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర;

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_దొంతర = pul_System_Call_దొంతర - ul_Hardware_Saved_Exception_చట్రం_కొలత;

            /* Copy the stack frame. */
            కొరకు( i = 0; i < ul_Hardware_Saved_Exception_చట్రం_కొలత; i++ )
            {
                pul_System_Call_దొంతర[ i ] = pul_Task_దొంతర[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_దొంతర_Info.ul_Link_రిజిస్టరు_At_System_Call_నమోదు = pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_LR ];

            /* Use the pulSystemCallStack in thread mode. */
            __asm అస్థిర ( "msr psp, %0" : : "r" ( pul_System_Call_దొంతర ) );

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ] = uxSystemCallImplementations[ uc_System_Call_సంఖ్య ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర = pul_Task_దొంతర + ul_Hardware_Saved_Exception_చట్రం_కొలత;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            ఒకవేళ( ( pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] & పోర్టు_PSR_దొంతర_PADDING_ముసుగు ) == పోర్టు_PSR_దొంతర_PADDING_ముసుగు )
            {
                pxMpuSettings->ulTaskFlags |= పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG;
            }
            లేకపోతే
            {
                pxMpuSettings->ulTaskFlags &= ( ~పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] &= ( ~పోర్టు_PSR_దొంతర_PADDING_ముసుగు );

            /* Raise the privilege for the duration of the system call. */
            __asm అస్థిర
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

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    శూన్య vRequestSystemCallExit( శూన్య ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm అస్థిర ( "svc %0 \n" ::"i" ( పోర్టు_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    శూన్య vSystemCallExit( uint32_t * pul_System_Call_దొంతర,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        బాహ్య TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_దొంతర;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        స్థిరరాశి uint32_t ul_Hardware_Saved_Exception_చట్రం_కొలత = 8;

        #ఒకవేళ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __privileged_functions_start__;
            బాహ్య uint32_t * __privileged_functions_end__;

        #లేకపోతే

            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __privileged_functions_start__[];
            బాహ్య uint32_t __privileged_functions_end__[];

        #అయితే_ముగింపు /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ];
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
        ఒకవేళ( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర != ఖాళీ ) )
        {
            pul_Task_దొంతర = pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర;

            /* Make space on the task stack for the stack frame. */
            pul_Task_దొంతర = pul_Task_దొంతర - ul_Hardware_Saved_Exception_చట్రం_కొలత;

            /* Copy the stack frame. */
            కొరకు( i = 0; i < ul_Hardware_Saved_Exception_చట్రం_కొలత; i++ )
            {
                pul_Task_దొంతర[ i ] = pul_System_Call_దొంతర[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm అస్థిర ( "msr psp, %0" : : "r" ( pul_Task_దొంతర ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PC ] = pxMpuSettings->x_System_Call_దొంతర_Info.ul_Link_రిజిస్టరు_At_System_Call_నమోదు;

            /* Ensure that LR has a valid value.*/
            pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_LR ] = pxMpuSettings->x_System_Call_దొంతర_Info.ul_Link_రిజిస్టరు_At_System_Call_నమోదు;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            ఒకవేళ( ( pxMpuSettings->ulTaskFlags & పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG ) == పోర్టు_దొంతర_చట్రం_HAS_PADDING_FLAG )
            {
                pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] |= పోర్టు_PSR_దొంతర_PADDING_ముసుగు;
            }
            లేకపోతే
            {
                pul_Task_దొంతర[ పోర్టు_స్థానభ్రంశం_గమ్యం_PSR ] &= ( ~పోర్టు_PSR_దొంతర_PADDING_ముసుగు );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర = ఖాళీ;

            /* Drop the privilege before returning to the thread mode. */
            __asm అస్థిర
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

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    పునాది_Type_t x_పోర్టు_Is_Task_Privileged( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        పునాది_Type_t xTaskIsPrivileged = pdFALSE;
        స్థిరరాశి xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ ); /* Calling task's MPU settings. */

        ఒకవేళ( ( xTaskMpuSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        తిరిగి xTaskIsPrivileged;
    }

#అయితే_ముగింపు /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                         TaskFunction_t px_సంకేతం,
                                         శూన్య * pvParameters,
                                         పునాది_Type_t x_నిరంతరం_Privileged,
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
        xMPUSettings->ulContext[ 13 ] = ( uint32_t ) పోర్టు_TASK_RETURN_చిరునామా; /* LR. */
        xMPUSettings->ulContext[ 14 ] = ( uint32_t ) px_సంకేతం;                  /* PC. */
        xMPUSettings->ulContext[ 15 ] = పోర్టు_INITIAL_XPSR;                     /* xPSR. */

        xMPUSettings->ulContext[ 16 ] = ( uint32_t ) ( px_శిఖరం_యొక్క_దొంతర - 8 ); /* PSP with the hardware saved stack. */
        ఒకవేళ( x_నిరంతరం_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= పోర్టు_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) పోర్టు_INITIAL_CONTROL_PRIVILEGED; /* CONTROL. */
        }
        లేకపోతే
        {
            xMPUSettings->ulTaskFlags &= ( ~పోర్టు_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) పోర్టు_INITIAL_CONTROL_UNPRIVILEGED; /* CONTROL. */
        }
        xMPUSettings->ulContext[ 18 ] = పోర్టు_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */

        #ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర = &( xMPUSettings->x_System_Call_దొంతర_Info.ul_System_Call_దొంతర_బఫరు[ config_SYSTEM_CALL_దొంతర_కొలత - 1 ] );
            xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_దొంతర_Info.pul_System_Call_దొంతర ) &
                                                                                     ( uint32_t ) ( ~( పోర్టు_BYTE_ALIGNMENT_ముసుగు ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_దొంతర_Info.pul_Task_దొంతర = ఖాళీ;
        }
        #అయితే_ముగింపు /* configUSE_MPU_WRAPPERS_V1 == 0 */

        తిరిగి &( xMPUSettings->ulContext[ 19 ] );
    }

#లేకపోతే /* configENABLE_MPU */

    దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                         TaskFunction_t px_సంకేతం,
                                         శూన్య * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #ఒకవేళ ( పోర్టు_PRELOAD_REGISTERS == 0 )
        {
            px_శిఖరం_యొక్క_దొంతర--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_XPSR;                        /* xPSR. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;                  /* PC. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_TASK_RETURN_చిరునామా; /* LR. */
            px_శిఖరం_యొక్క_దొంతర -= 5;                                       /* R12, R3, R2 and R1. */
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;            /* R0. */
            px_శిఖరం_యొక్క_దొంతర -= 9;                                       /* R11..R4, EXC_RETURN. */
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_EXC_RETURN;
        }
        #లేకపోతే /* portPRELOAD_REGISTERS */
        {
            px_శిఖరం_యొక్క_దొంతర--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_XPSR;                        /* xPSR. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;                  /* PC. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_TASK_RETURN_చిరునామా; /* LR. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x12121212UL;            /* R12. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x03030303UL;            /* R3. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x02020202UL;            /* R2. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x01010101UL;            /* R1. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;            /* R0. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x11111111UL;            /* R11. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x10101010UL;            /* R10. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x09090909UL;            /* R09. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x08080808UL;            /* R08. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x07070707UL;            /* R07. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x06060606UL;            /* R06. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x05050505UL;            /* R05. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x04040404UL;            /* R04. */
            px_శిఖరం_యొక్క_దొంతర--;
            *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_EXC_RETURN;                  /* EXC_RETURN. */
        }
        #అయితే_ముగింపు /* portPRELOAD_REGISTERS */

        తిరిగి px_శిఖరం_యొక్క_దొంతర;
    }

#అయితే_ముగింపు /* configENABLE_MPU */

/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య ) /* PRIVILEGED_FUNCTION */
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
    #ఒకవేళ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        స్థిరరాశి పోర్టు_ISR_t * స్థిరరాశి px_సదిశ_పట్టిక = పోర్టు_SCB_VTOR_REG;

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
        configASSERT( px_సదిశ_పట్టిక[ పోర్టు_సదిశ_సూచీ_SVC ] == SVC_Handler );
        configASSERT( px_సదిశ_పట్టిక[ పోర్టు_సదిశ_సూచీ_PENDSV ] == PendSV_Handler );
    }
    #అయితే_ముగింపు /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
     * the highest priority. */
    పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_PENDSV_PRI;
    పోర్టు_NVIC_SHPR3_REG |= పోర్టు_NVIC_SYSTICK_PRI;
    పోర్టు_NVIC_SHPR2_REG = 0;

    #ఒకవేళ ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_అమరిక_MPU();
    }
    #అయితే_ముగింపు /* configENABLE_MPU */

    /* Start the timer that generates the tick ISR. Interrupts are disabled
     * here already. */
    v_పోర్టు_అమరిక_Timer_అంతరాయం();

    /* Initialize the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    #ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #అయితే_ముగింపు

    /* Start the first task. */
    v_ప్రారంభం_మొదటి_Task();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    vTaskSwitchContext();
    prvTaskExitError();

    /* Should not get here. */
    తిరిగి 0;
}

/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}

/*-----------------------------------------------------------*/

#ఒకవేళ ( configENABLE_MPU == 1 )

    శూన్య v_పోర్టు_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    స్థిరరాశి నిర్మాణం x_జ్ఞాపకం_REGION * స్థిరరాశి xRegions,
                                    దొంతర_Type_t * px_Bottom_యొక్క_దొంతర,
                                    config_దొంతర_లోతు_TYPE ux_దొంతర_లోతు )
    {
        #ఒకవేళ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            బాహ్య uint32_t * __SRAM_segment_start__;
            బాహ్య uint32_t * __SRAM_segment_end__;
            బాహ్య uint32_t * __privileged_sram_start__;
            బాహ్య uint32_t * __privileged_sram_end__;

        #లేకపోతే
            /* Declaration when these variable are exported from linker scripts. */
            బాహ్య uint32_t __SRAM_segment_start__[];
            బాహ్య uint32_t __SRAM_segment_end__[];
            బాహ్య uint32_t __privileged_sram_start__[];
            బాహ్య uint32_t __privileged_sram_end__[];

        #అయితే_ముగింపు /* defined( __ARMCC_VERSION ) */

        int32_t l_సూచీ;
        uint32_t ul;

        ఒకవేళ( xRegions == ఖాళీ )
        {
            /* No MPU regions are specified so allow access to all RAM. */
            xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                ( ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
                  ( పోర్టు_MPU_RBAR_REGION_సంఖ్య_VALID_BITMASK ) |
                  ( పోర్టు_దొంతర_REGION ) );                   /* Region number. */

            xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                ( ( పోర్టు_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                  ( పోర్టు_MPU_REGION_EXECUTE_NEVER ) |
                  ( ( configS_C_B_SRAM & పోర్టు_MPU_RASR_S_C_B_BITMASK ) << పోర్టు_MPU_RASR_S_C_B_LOCATION ) |
                  ( prv_Get_MPURegion_కొలత_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
                  ( పోర్టు_MPU_RASR_REGION_ENABLE_BITMASK ) );


            /* Invalidate user configurable regions. */
            కొరకు( ul = 1UL; ul <= పోర్టు_అంకె_CONFIGURABLE_REGIONS; ul++ )
            {
                xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | పోర్టు_MPU_RBAR_REGION_సంఖ్య_VALID_BITMASK );
                xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
            }
        }
        లేకపోతే
        {
            /* This function is called automatically when the task is created - in
             * which case the stack region parameters will be valid.  At all other
             * times the stack parameters will not be valid and it is assumed that the
             * stack region has already been configured. */
            ఒకవేళ( ux_దొంతర_లోతు > 0 )
            {
                /* Define the region that allows access to the stack. */
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                    ( ( ( uint32_t ) px_Bottom_యొక్క_దొంతర ) |
                      ( పోర్టు_MPU_RBAR_REGION_సంఖ్య_VALID_BITMASK ) |
                      ( పోర్టు_దొంతర_REGION ) ); /* Region number. */

                xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                    ( ( పోర్టు_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                      ( పోర్టు_MPU_REGION_EXECUTE_NEVER ) |
                      ( prv_Get_MPURegion_కొలత_Setting( ux_దొంతర_లోతు * ( uint32_t ) పరిమాణం( దొంతర_Type_t ) ) ) |
                      ( ( configS_C_B_SRAM & పోర్టు_MPU_RASR_S_C_B_BITMASK ) << పోర్టు_MPU_RASR_S_C_B_LOCATION ) |
                      ( పోర్టు_MPU_RASR_REGION_ENABLE_BITMASK ) );
            }

            l_సూచీ = 0;

            కొరకు( ul = 1UL; ul <= పోర్టు_అంకె_CONFIGURABLE_REGIONS; ul++ )
            {
                ఒకవేళ( ( xRegions[ l_సూచీ ] ).ul_నిడివి_లోపల_బైట్లు > 0UL )
                {
                    /* Translate the generic region definition contained in
                     * xRegions into the CM0+ specific MPU settings that are then
                     * stored in xMPUSettings. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR =
                        ( ( uint32_t ) xRegions[ l_సూచీ ].pv_పునాది_చిరునామా ) |
                        ( పోర్టు_MPU_RBAR_REGION_సంఖ్య_VALID_BITMASK ) |
                        ( ul - 1UL ); /* Region number. */

                    xMPUSettings->xRegionsSettings[ ul ].ulRASR =
                        ( prv_Get_MPURegion_కొలత_Setting( xRegions[ l_సూచీ ].ul_నిడివి_లోపల_బైట్లు ) ) |
                        ( xRegions[ l_సూచీ ].ulParameters ) |
                        ( పోర్టు_MPU_RASR_REGION_ENABLE_BITMASK );
                }
                లేకపోతే
                {
                    /* Invalidate the region. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | పోర్టు_MPU_RBAR_REGION_సంఖ్య_VALID_BITMASK );
                    xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
                }

            l_సూచీ++;
        }
    }
}

#అయితే_ముగింపు /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( స్థిరరాశి శూన్య * pv_బఫరు,
                                                size_t x_బఫరు_నిడివి,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_బఫరు_ప్రారంభం_చిరునామా, ul_బఫరు_చివర_చిరునామా;
        uint32_t ul_Region_ప్రారంభం, ul_Region_కొలత, ul_Region_చివర;
        uint32_t ulMPURegionAccessPermissions;
        పునాది_Type_t xAccessGranted = pdFALSE;
        స్థిరరాశి xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ ); /* Calling task's MPU settings. */

        ఒకవేళ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        లేకపోతే ఒకవేళ( ( xTaskMpuSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        లేకపోతే
        {
            ఒకవేళ( పోర్టు_కూడు_UINT32_WILL_అధికప్రవాహం( ( ( uint32_t ) pv_బఫరు ), ( ( uint32_t ) x_బఫరు_నిడివి - 1UL ) ) == pdFALSE )
            {
                ul_బఫరు_ప్రారంభం_చిరునామా = ( uint32_t ) pv_బఫరు;
                ul_బఫరు_చివర_చిరునామా = ( ( ( uint32_t ) pv_బఫరు ) + ( uint32_t ) x_బఫరు_నిడివి - 1UL );

                కొరకు( i = 0; i < పోర్టు_మొత్తం_అంకె_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    ఒకవేళ( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                          పోర్టు_MPU_RASR_REGION_ENABLE_BITMASK ) == పోర్టు_MPU_RASR_REGION_ENABLE_BITMASK )
                    {
                        ul_Region_ప్రారంభం = పోర్టు_వెలికితీయి_మొదటి_చిరునామా_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR );
                        ul_Region_కొలత = పోర్టు_వెలికితీయి_REGION_కొలత_FROM_RASR( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR );
                        ul_Region_చివర = ul_Region_ప్రారంభం + ul_Region_కొలత;

                        ఒకవేళ( పోర్టు_IS_చిరునామా_WITHIN_RANGE( ul_బఫరు_ప్రారంభం_చిరునామా,
                                                         ul_Region_ప్రారంభం,
                                                         ul_Region_చివర ) &&
                            పోర్టు_IS_చిరునామా_WITHIN_RANGE( ul_బఫరు_చివర_చిరునామా,
                                                         ul_Region_ప్రారంభం,
                                                         ul_Region_చివర ) )
                        {
                            ulMPURegionAccessPermissions = xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                                                           పోర్టు_MPU_RASR_AP_BITMASK;

                            ఒకవేళ( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
                            {
                                ఒకవేళ( ( ulMPURegionAccessPermissions == పోర్టు_MPU_REGION_PRIV_RW_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == పోర్టు_MPU_REGION_PRIV_RO_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == పోర్టు_MPU_REGION_PRIV_RW_UNPRIV_RW ) )
                                {
                                    xAccessGranted = pdTRUE;
                                    ఆపు;
                                }
                            }
                            లేకపోతే ఒకవేళ( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
                            {
                                ఒకవేళ( ulMPURegionAccessPermissions == పోర్టు_MPU_REGION_PRIV_RW_UNPRIV_RW )
                                {
                                    xAccessGranted = pdTRUE;
                                    ఆపు;
                                }
                            }
                        }
                    }
                }
            }
        }

        తిరిగి xAccessGranted;
    }

#అయితే_ముగింపు /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_Is_Inside_అంతరాయం( శూన్య )
{
    uint32_t ul_Current_అంతరాయం;
    పునాది_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm అస్థిర ( "mrs %0, ipsr" : "=r" ( ul_Current_అంతరాయం )::"memory" );

    ఒకవేళ( ul_Current_అంతరాయం == 0 )
    {
        xReturn = pdFALSE;
    }
    లేకపోతే
    {
        xReturn = pdTRUE;
    }

    తిరిగి xReturn;
}

/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    శూన్య v_పోర్టు_Grant_Access_గమ్యం_Kernel_Object( TaskHandle_t x_అంతర్గత_Task_Handle,
                                         int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
        ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

        xTaskMpuSettings = xTaskGetMPUSettings( x_అంతర్గత_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] |= ( 1U << ul_Access_Control_List_నమోదు_బిట్టు );
    }

#అయితే_ముగింపు /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    శూన్య v_పోర్టు_Revoke_Access_గమ్యం_Kernel_Object( TaskHandle_t x_అంతర్గత_Task_Handle,
                                          int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
        ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

        xTaskMpuSettings = xTaskGetMPUSettings( x_అంతర్గత_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] &= ~( 1U << ul_Access_Control_List_నమోదు_బిట్టు );
    }

#అయితే_ముగింపు /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_నమోదు_సూచీ, ul_Access_Control_List_నమోదు_బిట్టు;
            పునాది_Type_t xAccessGranted = pdFALSE;
            స్థిరరాశి xMPU_SETTINGS * xTaskMpuSettings;

            ఒకవేళ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            లేకపోతే
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ఖాళీ ); /* Calling task's MPU settings. */

                ul_Access_Control_List_నమోదు_సూచీ = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object / పోర్టు_ACL_నమోదు_కొలత_బిట్లు );
                ul_Access_Control_List_నమోదు_బిట్టు = ( ( uint32_t ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object % పోర్టు_ACL_నమోదు_కొలత_బిట్లు );

                ఒకవేళ( ( xTaskMpuSettings->ulTaskFlags & పోర్టు_TASK_IS_PRIVILEGED_FLAG ) == పోర్టు_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                లేకపోతే
                {
                    ఒకవేళ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_నమోదు_సూచీ ] & ( 1U << ul_Access_Control_List_నమోదు_బిట్టు ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            తిరిగి xAccessGranted;
        }

    #లేకపోతే /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        పునాది_Type_t x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( int32_t l_అంతర్గత_సూచీ_యొక్క_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( శూన్య ) l_అంతర్గత_సూచీ_యొక్క_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            తిరిగి pdTRUE;
        }

    #అయితే_ముగింపు /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#అయితే_ముగింపు /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/
