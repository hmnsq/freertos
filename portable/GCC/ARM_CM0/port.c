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
#परिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

/* MPU includes. */
#अन्तर्भाव "mpu_wrappers.h"
#अन्तर्भाव "mpu_syscall_numbers.h"

/* Portasm includes. */
#अन्तर्भाव "portasm.h"

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
प्रकारनिर्देश शून्य ( * पत्तनम्_ISR_t )( शून्य );

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#परिभाषय पत्तनम्_NVIC_SYSTICK_CTRL_REG             ( *( ( चञ्चल uint32_t * ) 0xe000e010 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_आरोपय_REG             ( *( ( चञ्चल uint32_t * ) 0xe000e014 ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG    ( *( ( चञ्चल uint32_t * ) 0xe000e018 ) )
#परिभाषय पत्तनम्_NVIC_SHPR3_REG                    ( *( ( चञ्चल uint32_t * ) 0xe000ed20 ) )
#परिभाषय पत्तनम्_NVIC_SHPR2_REG                    ( *( ( चञ्चल uint32_t * ) 0xe000ed1c ) )
#परिभाषय पत्तनम्_NVIC_SYSTICK_ENABLE_BIT           ( 1UL << 0UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_INT_BIT              ( 1UL << 1UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_CLK_BIT              ( 1UL << 2UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_गणनम्_FLAG_BIT       ( 1UL << 16UL )
#परिभाषय पत्तनम्_NVIC_PEND_SYSTICK_CLEAR_BIT       ( 1UL << 25UL )
#परिभाषय पत्तनम्_NVIC_PEND_SYSTICK_समुच्चयः_BIT         ( 1UL << 26UL )
#परिभाषय पत्तनम्_MIN_व्यवधानम्_प्राथमिकता            ( 255UL )
#परिभाषय पत्तनम्_NVIC_PENDSV_PRI                   ( पत्तनम्_MIN_व्यवधानम्_प्राथमिकता << 16UL )
#परिभाषय पत्तनम्_NVIC_SYSTICK_PRI                  ( पत्तनम्_MIN_व्यवधानम्_प्राथमिकता << 24UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#परिभाषय पत्तनम्_SCB_VTOR_REG                      ( *( ( पत्तनम्_ISR_t ** ) 0xe000ed08 ) )
#परिभाषय पत्तनम्_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( चञ्चल uint32_t * ) 0xe000ed24 ) )
#परिभाषय पत्तनम्_SCB_MEM_FAULT_ENABLE_BIT          ( 1UL << 16UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#परिभाषय पत्तनम्_सदिशम्_सूचकांक_SVC       ( 11 )
#परिभाषय पत्तनम्_सदिशम्_सूचकांक_PENDSV    ( 14 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#परिभाषय पत्तनम्_PSR_राशिः_PADDING_आवरणम्              ( 1UL << 9UL )
#परिभाषय पत्तनम्_EXC_RETURN_राशिः_FRAME_TYPE_आवरणम्    ( 1UL << 4UL )

/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_LR     ( 5 )
#परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_PC     ( 6 )
#परिभाषय पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR    ( 7 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#परिभाषय पत्तनम्_MPU_TYPE_REG                            ( *( ( चञ्चल uint32_t * ) 0xe000ed90 ) )
#परिभाषय पत्तनम्_MPU_CTRL_REG                            ( *( ( चञ्चल uint32_t * ) 0xe000ed94 ) )

#परिभाषय पत्तनम्_MPU_RBAR_REG                            ( *( ( चञ्चल uint32_t * ) 0xe000ed9c ) )
#परिभाषय पत्तनम्_MPU_RASR_REG                            ( *( ( चञ्चल uint32_t * ) 0xe000eda0 ) )

/* MPU Region Attribute and Size Register (RASR) bitmasks. */
#परिभाषय पत्तनम्_MPU_RASR_AP_BITMASK                     ( 0x7UL << 24UL )
#परिभाषय पत्तनम्_MPU_RASR_S_C_B_BITMASK                  ( 0x7UL )
#परिभाषय पत्तनम्_MPU_RASR_S_C_B_LOCATION                 ( 16UL )
#परिभाषय पत्तनम्_MPU_RASR_आकार_BITMASK                   ( 0x1FUL << 1UL )
#परिभाषय पत्तनम्_MPU_RASR_REGION_ENABLE_BITMASK          ( 0x1UL )

/* MPU Region Base Address Register (RBAR) bitmasks. */
#परिभाषय पत्तनम्_MPU_RBAR_स्थानाङ्कः_BITMASK                ( 0xFFFFFF00UL )
#परिभाषय पत्तनम्_MPU_RBAR_REGION_सङ्ख्या_VALID_BITMASK    ( 0x1UL << 4UL )
#परिभाषय पत्तनम्_MPU_RBAR_REGION_सङ्ख्या_BITMASK          ( 0x0000000FUL )

/* MPU Control Register (MPU_CTRL) bitmasks. */
#परिभाषय पत्तनम्_MPU_CTRL_ENABLE_BITMASK                 ( 0x1UL )
#परिभाषय पत्तनम्_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK ( 0x1UL << 2UL ) /* PRIVDEFENA bit. */

/* Expected value of the portMPU_TYPE register. */
#परिभाषय पत्तनम्_EXPECTED_MPU_TYPE_मानम्                 ( 0x8UL << 8UL ) /* 8 DREGION unified. */

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#परिभाषय पत्तनम्_EXTRACT_FIRST_स्थानाङ्कः_FROM_RBAR( rbar ) \
    ( ( rbar ) & पत्तनम्_MPU_RBAR_स्थानाङ्कः_BITMASK )

/* Extract size of the MPU region as encoded in the
 * RASR (Region Attribute and Size Register) value. */
#परिभाषय पत्तनम्_EXTRACT_REGION_आकार_FROM_RASR( rasr ) \
    ( 1 << ( ( ( ( rasr ) & पत्तनम्_MPU_RASR_आकार_BITMASK ) >> 1 )+ 1 ) )

/* Does addr lies within [start, end] address range? */
#परिभाषय पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( addr, start, अन्तः_2 ) \
    ( ( ( addr ) >= ( start ) ) && ( ( addr ) <= ( अन्तः_2 ) ) )

/* Is the access request satisfied by the available permissions? */
#परिभाषय पत्तनम्_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#परिभाषय पत्तनम्_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#परिभाषय पत्तनम्_सङ्कलय_UINT32_WILL_अतिप्रवाहः( a, b )    ( ( a ) > ( पत्तनम्_UINT32_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#परिभाषय पत्तनम्_MAX_24_BIT_सङ्ख्या       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#परिभाषय पत्तनम्_MISSED_COUNTS_गुणकः    ( 94UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#परिभाषय पत्तनम्_INITIAL_XPSR    ( 0x01000000 )

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
#परिभाषय पत्तनम्_INITIAL_EXC_RETURN    ( 0xfffffffdUL )

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#परिभाषय पत्तनम्_CONTROL_PRIVILEGED_आवरणम्         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#परिभाषय पत्तनम्_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#परिभाषय पत्तनम्_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#यदि_अपरिभाषितम् configSYSTICK_CLOCK_HZ
    #परिभाषय configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #परिभाषय पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG    ( पत्तनम्_NVIC_SYSTICK_CLK_BIT )
#अन्यथा
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #परिभाषय पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG    ( 0 )
#यदि_अन्तः

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#यदि_परिभाषितम् config_TASK_RETURN_स्थानाङ्कः
    #परिभाषय पत्तनम्_TASK_RETURN_स्थानाङ्कः    config_TASK_RETURN_स्थानाङ्कः
#अन्यथा
    #परिभाषय पत्तनम्_TASK_RETURN_स्थानाङ्कः    prvTaskExitError
#यदि_अन्तः

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#परिभाषय पत्तनम्_PRELOAD_REGISTERS    1

/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
स्थिर शून्य prvTaskExitError( शून्य );

#यदि ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    स्थिर शून्य prv_सज्जता_MPU( शून्य ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* configENABLE_MPU */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
शून्य v_पत्तनम्_सज्जता_Timer_व्यवधानम्( शून्य ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
आधारः_Type_t x_पत्तनम्_Is_Inside_व्यवधानम्( शून्य );

/**
 * @brief Yield the processor.
 */
शून्य v_पत्तनम्_Yield( शून्य ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
शून्य v_पत्तनम्_Enter_Critical( शून्य ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
शून्य v_पत्तनम्_Exit_Critical( शून्य ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
शून्य SysTick_Handler( शून्य ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
पत्तनम्_DONT_DISCARD शून्य v_पत्तनम्_SVCHandler_C( uint32_t * pul_Caller_राशिः_स्थानाङ्कः ) PRIVILEGED_FUNCTION;

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    शून्य vSystemCallEnter( uint32_t * pul_Task_राशिः,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_सङ्ख्या ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    शून्य vRequestSystemCallExit( शून्य ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    शून्य vSystemCallExit( uint32_t * pul_System_Call_राशिः,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#यदि ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य ) PRIVILEGED_FUNCTION;

#यदि_अन्तः /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_दत्त स्थिर आधारः_Type_t xSchedulerRunning = pdFALSE;

#यदि_अन्तः

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
PRIVILEGED_दत्त स्थिर चञ्चल uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

#यदि ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_दत्त स्थिर uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_दत्त स्थिर uint32_t x_अधिकतमम्_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_दत्त स्थिर uint32_t ulStoppedTimerCompensation = 0;

#यदि_अन्तः /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#यदि ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) शून्य v_पत्तनम्_Suppress_Ticks_And_Sleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_Reload_मानम्, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_वामः;
        TickType_t xModifiableIdleTime;

        /* Make sure the SysTick reload value does not overflow the counter. */
        यदि( xExpectedIdleTime > x_अधिकतमम्_Possible_Suppressed_Ticks )
        {
            xExpectedIdleTime = x_अधिकतमम्_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm चञ्चल ( "cpsid i" ::: "memory" );
        __asm चञ्चल ( "dsb" );
        __asm चञ्चल ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        यदि( e_Task_Confirm_Sleep_बहुलकम्_स्थितिः() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm चञ्चल ( "cpsie i" ::: "memory" );
        }
        अन्यथा
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            पत्तनम्_NVIC_SYSTICK_CTRL_REG = ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_वामः = पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG;

            यदि( ul_Sys_Tick_Decrements_वामः == 0 )
            {
                ul_Sys_Tick_Decrements_वामः = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_मानम् = ul_Sys_Tick_Decrements_वामः + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );

            यदि( ( पत्तनम्_NVIC_INT_CTRL_REG & पत्तनम्_NVIC_PEND_SYSTICK_समुच्चयः_BIT ) != 0 )
            {
                पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PEND_SYSTICK_CLEAR_BIT;
                ul_Reload_मानम् -= ulTimerCountsForOneTick;
            }

            यदि( ul_Reload_मानम् > ulStoppedTimerCompensation )
            {
                ul_Reload_मानम् -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ul_Reload_मानम्;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;

            /* Restart SysTick. */
            पत्तनम्_NVIC_SYSTICK_CTRL_REG |= पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            xModifiableIdleTime = xExpectedIdleTime;
            configPRE_SLEEP_PROCESSING( xModifiableIdleTime );

            यदि( xModifiableIdleTime > 0 )
            {
                __asm चञ्चल ( "dsb" ::: "memory" );
                __asm चञ्चल ( "wfi" );
                __asm चञ्चल ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm चञ्चल ( "cpsie i" ::: "memory" );
            __asm चञ्चल ( "dsb" );
            __asm चञ्चल ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm चञ्चल ( "cpsid i" ::: "memory" );
            __asm चञ्चल ( "dsb" );
            __asm चञ्चल ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            पत्तनम्_NVIC_SYSTICK_CTRL_REG = ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT );

            /* Determine whether the SysTick has already counted to zero. */
            यदि( ( पत्तनम्_NVIC_SYSTICK_CTRL_REG & पत्तनम्_NVIC_SYSTICK_गणनम्_FLAG_BIT ) != 0 )
            {
                uint32_t ul_Calculated_आरोपय_मानम्;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_आरोपय_मानम् = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_मानम् - पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                यदि( ( ul_Calculated_आरोपय_मानम् <= ulStoppedTimerCompensation ) || ( ul_Calculated_आरोपय_मानम् > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_आरोपय_मानम् = ( ulTimerCountsForOneTick - 1UL );
                }

                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ul_Calculated_आरोपय_मानम्;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
            }
            अन्यथा
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_वामः = पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG;
                #यदि ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG != पत्तनम्_NVIC_SYSTICK_CLK_BIT )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    यदि( ul_Sys_Tick_Decrements_वामः == 0 )
                    {
                        ul_Sys_Tick_Decrements_वामः = ul_Reload_मानम्;
                    }
                }
                #यदि_अन्तः /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_वामः;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;
            पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT | पत्तनम्_NVIC_SYSTICK_INT_BIT | पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;
            #यदि ( पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG == पत्तनम्_NVIC_SYSTICK_CLK_BIT )
            {
                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ulTimerCountsForOneTick - 1UL;
            }
            #अन्यथा
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT | पत्तनम्_NVIC_SYSTICK_INT_BIT;

                यदि( ( पत्तनम्_NVIC_SYSTICK_CTRL_REG & पत्तनम्_NVIC_SYSTICK_गणनम्_FLAG_BIT ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0;
                }

                पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ulTimerCountsForOneTick - 1UL;
                पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT | पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;
            }
            #यदि_अन्तः /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_चरणः_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm चञ्चल ( "cpsie i" ::: "memory" );
        }
    }

#यदि_अन्तः /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) शून्य v_पत्तनम्_सज्जता_Timer_व्यवधानम्( शून्य ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #यदि ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_दरः_HZ );
        x_अधिकतमम्_Possible_Suppressed_Ticks = पत्तनम्_MAX_24_BIT_सङ्ख्या / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = पत्तनम्_MISSED_COUNTS_गुणकः / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #यदि_अन्तः /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG;
    पत्तनम्_NVIC_SYSTICK_CURRENT_मानम्_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    पत्तनम्_NVIC_SYSTICK_आरोपय_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_दरः_HZ ) - 1UL;
    पत्तनम्_NVIC_SYSTICK_CTRL_REG = पत्तनम्_NVIC_SYSTICK_CLK_BIT_CONFIG | पत्तनम्_NVIC_SYSTICK_INT_BIT | पत्तनम्_NVIC_SYSTICK_ENABLE_BIT;
}

/*-----------------------------------------------------------*/

स्थिर शून्य prvTaskExitError( शून्य )
{
    चञ्चल uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    पत्तनम्_DISABLE_INTERRUPTS();

    यावत्( ulDummy == 0 )
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

#यदि ( configENABLE_MPU == 1 )

    स्थिर uint32_t prv_Get_MPURegion_आकार_Setting( uint32_t ul_Actual_आकार_अन्तर्_अष्टकानि )
    {
        uint32_t ul_Region_आकार, ul_Return_मानम् = 7UL;

        /* 256 is the smallest region size, 31 is the largest valid value for
         * ulReturnValue. */
        प्रति( ul_Region_आकार = 256UL; ul_Return_मानम् < 31UL; ( ul_Region_आकार <<= 1UL ) )
        {
            यदि( ul_Actual_आकार_अन्तर्_अष्टकानि <= ul_Region_आकार )
            {
                भङ्ग;
            }
            अन्यथा
            {
                ul_Return_मानम्++;
            }
        }

        /* Shift the code by one before returning so it can be written directly
         * into the correct bit position of the attribute register. */
        प्रत्यागम( ul_Return_मानम् << 1UL );
    }

#यदि_अन्तः /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    स्थिर शून्य prv_सज्जता_MPU( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        #यदि defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
            * exported from linker scripts. */
            बाह्य uint32_t * __privileged_functions_start__;
            बाह्य uint32_t * __privileged_functions_end__;
            बाह्य uint32_t * __FLASH_segment_start__;
            बाह्य uint32_t * __FLASH_segment_end__;
            बाह्य uint32_t * __privileged_sram_start__;
            बाह्य uint32_t * __privileged_sram_end__;

        #अन्यथा /* if defined( __ARMCC_VERSION ) */

            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __privileged_functions_start__[];
            बाह्य uint32_t __privileged_functions_end__[];
            बाह्य uint32_t __FLASH_segment_start__[];
            बाह्य uint32_t __FLASH_segment_end__[];
            बाह्य uint32_t __privileged_sram_start__[];
            बाह्य uint32_t __privileged_sram_end__[];

        #यदि_अन्तः /* defined( __ARMCC_VERSION ) */

        /* Ensure that the MPU is present. */
        configASSERT( पत्तनम्_MPU_TYPE_REG == पत्तनम्_EXPECTED_MPU_TYPE_मानम् );

        /* Check that the MPU is present. */
        यदि( पत्तनम्_MPU_TYPE_REG == पत्तनम्_EXPECTED_MPU_TYPE_मानम् )
        {
            /* Setup privileged flash as Read Only so that privileged tasks can
             * read it but not modify. */
            पत्तनम्_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                 ( पत्तनम्_MPU_RBAR_REGION_सङ्ख्या_VALID_BITMASK ) |
                                 ( पत्तनम्_PRIVILEGED_FLASH_REGION ) );

            पत्तनम्_MPU_RASR_REG = ( ( पत्तनम्_MPU_REGION_PRIV_RO_UNPRIV_NA ) |
                                 ( ( configS_C_B_FLASH & पत्तनम्_MPU_RASR_S_C_B_BITMASK ) << पत्तनम्_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                 ( पत्तनम्_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup unprivileged flash as Read Only by both privileged and
             * unprivileged tasks. All tasks can read it but no-one can modify. */
            पत्तनम्_MPU_RBAR_REG = ( ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                 ( पत्तनम्_MPU_RBAR_REGION_सङ्ख्या_VALID_BITMASK ) |
                                 ( पत्तनम्_UNPRIVILEGED_FLASH_REGION ) );

            पत्तनम्_MPU_RASR_REG = ( ( पत्तनम्_MPU_REGION_PRIV_RO_UNPRIV_RO ) |
                                 ( ( configS_C_B_FLASH & पत्तनम्_MPU_RASR_S_C_B_BITMASK ) << पत्तनम्_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                 ( पत्तनम्_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup RAM containing kernel data for privileged access only. */
            पत्तनम्_MPU_RBAR_REG = ( ( uint32_t ) __privileged_sram_start__ ) | /* Base address. */
                                 ( पत्तनम्_MPU_RBAR_REGION_सङ्ख्या_VALID_BITMASK ) |
                                 ( पत्तनम्_PRIVILEGED_RAM_REGION );

            पत्तनम्_MPU_RASR_REG = ( ( पत्तनम्_MPU_REGION_PRIV_RW_UNPRIV_NA ) |
                                 ( पत्तनम्_MPU_REGION_EXECUTE_NEVER ) |
                                 ( ( configS_C_B_SRAM & पत्तनम्_MPU_RASR_S_C_B_BITMASK ) << पत्तनम्_MPU_RASR_S_C_B_LOCATION ) |
                                 prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __privileged_sram_end__ - ( uint32_t ) __privileged_sram_start__ ) |
                                 ( पत्तनम्_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Enable MPU with privileged background access i.e. unmapped
             * regions have privileged access. */
            पत्तनम्_MPU_CTRL_REG |= ( पत्तनम्_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK |
                                  पत्तनम्_MPU_CTRL_ENABLE_BITMASK );
        }
    }

#यदि_अन्तः /* configENABLE_MPU */

/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Yield( शून्य ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm चञ्चल ( "dsb" ::: "memory" );
    __asm चञ्चल ( "isb" );
}

/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enter_Critical( शून्य ) /* PRIVILEGED_FUNCTION */
{
    पत्तनम्_DISABLE_INTERRUPTS();
    ulCriticalNesting++;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm चञ्चल ( "dsb" ::: "memory" );
    __asm चञ्चल ( "isb" );
}

/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य ) /* PRIVILEGED_FUNCTION */
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    यदि( ulCriticalNesting == 0 )
    {
        पत्तनम्_ENABLE_INTERRUPTS();
    }
}

/*-----------------------------------------------------------*/

शून्य SysTick_Handler( शून्य ) /* PRIVILEGED_FUNCTION */
{
    uint32_t ul_Previous_आवरणम्;

    ul_Previous_आवरणम् = पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR();

    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        यदि( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();
            /* Pend a context switch. */
            पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT;
        }
        अन्यथा
        {
            traceISR_EXIT();
        }
    }

    पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ul_Previous_आवरणम् );
}

/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_SVCHandler_C( uint32_t * pul_Caller_राशिः_स्थानाङ्कः ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        #यदि defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __syscalls_flash_start__;
            बाह्य uint32_t * __syscalls_flash_end__;

        #अन्यथा

            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __syscalls_flash_start__[];
            बाह्य uint32_t __syscalls_flash_end__[];

        #यदि_अन्तः /* defined( __ARMCC_VERSION ) */

    #यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    uint32_t ulPC;
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_राशिः_स्थानाङ्कः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    विकल्प( ucSVCNumber )
    {
        पक्ष पत्तनम्_SVC_START_SCHEDULER:
            /* Setup the context of the first task so that the first task starts
             * executing. */
            v_Restore_Context_सम्बन्धि_First_Task();
            भङ्ग;

    #यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        पक्ष पत्तनम्_SVC_RAISE_PRIVILEGE:
            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            यदि( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            भङ्ग;

    #यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #यदि ( configENABLE_MPU == 1 )

        पक्ष पत्तनम्_SVC_YIELD:
            v_पत्तनम्_Yield();
            भङ्ग;

    #यदि_अन्तः /* configENABLE_MPU == 1 */

        स्वभाव:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}

/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    शून्य vSystemCallEnter( uint32_t * pul_Task_राशिः,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_सङ्ख्या ) /* PRIVILEGED_FUNCTION */
    {
        बाह्य TaskHandle_t pxCurrentTCB;
        बाह्य UBaseType_t uxSystemCallImplementations[ अङ्कः_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_राशिः;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ध्रुव uint32_t ul_Hardware_Saved_Exception_Frame_आकार = 8;

        #यदि defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __syscalls_flash_start__;
            बाह्य uint32_t * __syscalls_flash_end__;

        #अन्यथा

            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __syscalls_flash_start__[];
            बाह्य uint32_t __syscalls_flash_end__[];

        #यदि_अन्तः /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ];
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
        यदि( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः == रिक्त ) &&
            ( uxSystemCallImplementations[ uc_System_Call_सङ्ख्या ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_राशिः = pxMpuSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः;

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_राशिः = pul_System_Call_राशिः - ul_Hardware_Saved_Exception_Frame_आकार;

            /* Copy the stack frame. */
            प्रति( i = 0; i < ul_Hardware_Saved_Exception_Frame_आकार; i++ )
            {
                pul_System_Call_राशिः[ i ] = pul_Task_राशिः[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_राशिः_Info.ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः = pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_LR ];

            /* Use the pulSystemCallStack in thread mode. */
            __asm चञ्चल ( "msr psp, %0" : : "r" ( pul_System_Call_राशिः ) );

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ] = uxSystemCallImplementations[ uc_System_Call_सङ्ख्या ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः = pul_Task_राशिः + ul_Hardware_Saved_Exception_Frame_आकार;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            यदि( ( pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] & पत्तनम्_PSR_राशिः_PADDING_आवरणम् ) == पत्तनम्_PSR_राशिः_PADDING_आवरणम् )
            {
                pxMpuSettings->ulTaskFlags |= पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG;
            }
            अन्यथा
            {
                pxMpuSettings->ulTaskFlags &= ( ~पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] &= ( ~पत्तनम्_PSR_राशिः_PADDING_आवरणम् );

            /* Raise the privilege for the duration of the system call. */
            __asm चञ्चल
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

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    शून्य vRequestSystemCallExit( शून्य ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm चञ्चल ( "svc %0 \n" ::"i" ( पत्तनम्_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    शून्य vSystemCallExit( uint32_t * pul_System_Call_राशिः,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        बाह्य TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_राशिः;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ध्रुव uint32_t ul_Hardware_Saved_Exception_Frame_आकार = 8;

        #यदि defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __privileged_functions_start__;
            बाह्य uint32_t * __privileged_functions_end__;

        #अन्यथा

            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __privileged_functions_start__[];
            बाह्य uint32_t __privileged_functions_end__[];

        #यदि_अन्तः /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ];
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
        यदि( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः != रिक्त ) )
        {
            pul_Task_राशिः = pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः;

            /* Make space on the task stack for the stack frame. */
            pul_Task_राशिः = pul_Task_राशिः - ul_Hardware_Saved_Exception_Frame_आकार;

            /* Copy the stack frame. */
            प्रति( i = 0; i < ul_Hardware_Saved_Exception_Frame_आकार; i++ )
            {
                pul_Task_राशिः[ i ] = pul_System_Call_राशिः[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm चञ्चल ( "msr psp, %0" : : "r" ( pul_Task_राशिः ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PC ] = pxMpuSettings->x_System_Call_राशिः_Info.ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः;

            /* Ensure that LR has a valid value.*/
            pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_LR ] = pxMpuSettings->x_System_Call_राशिः_Info.ul_Link_पञ्जिकाकोशः_At_System_Call_प्रविष्टिः;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            यदि( ( pxMpuSettings->ulTaskFlags & पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG ) == पत्तनम्_राशिः_FRAME_HAS_PADDING_FLAG )
            {
                pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] |= पत्तनम्_PSR_राशिः_PADDING_आवरणम्;
            }
            अन्यथा
            {
                pul_Task_राशिः[ पत्तनम्_विस्थापनम्_गन्तव्यम्_PSR ] &= ( ~पत्तनम्_PSR_राशिः_PADDING_आवरणम् );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_राशिः_Info.pul_Task_राशिः = रिक्त;

            /* Drop the privilege before returning to the thread mode. */
            __asm चञ्चल
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

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    आधारः_Type_t x_पत्तनम्_Is_Task_Privileged( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        आधारः_Type_t xTaskIsPrivileged = pdFALSE;
        ध्रुव xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( रिक्त ); /* Calling task's MPU settings. */

        यदि( ( xTaskMpuSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        प्रत्यागम xTaskIsPrivileged;
    }

#यदि_अन्तः /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                         TaskFunction_t px_संहिता,
                                         शून्य * pvParameters,
                                         आधारः_Type_t x_सततम्_Privileged,
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
        xMPUSettings->ulContext[ 13 ] = ( uint32_t ) पत्तनम्_TASK_RETURN_स्थानाङ्कः; /* LR. */
        xMPUSettings->ulContext[ 14 ] = ( uint32_t ) px_संहिता;                  /* PC. */
        xMPUSettings->ulContext[ 15 ] = पत्तनम्_INITIAL_XPSR;                     /* xPSR. */

        xMPUSettings->ulContext[ 16 ] = ( uint32_t ) ( px_शिखरम्_सम्बन्धि_राशिः - 8 ); /* PSP with the hardware saved stack. */
        यदि( x_सततम्_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= पत्तनम्_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) पत्तनम्_INITIAL_CONTROL_PRIVILEGED; /* CONTROL. */
        }
        अन्यथा
        {
            xMPUSettings->ulTaskFlags &= ( ~पत्तनम्_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) पत्तनम्_INITIAL_CONTROL_UNPRIVILEGED; /* CONTROL. */
        }
        xMPUSettings->ulContext[ 18 ] = पत्तनम्_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */

        #यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः = &( xMPUSettings->x_System_Call_राशिः_Info.ul_System_Call_राशिः_बफर[ config_SYSTEM_CALL_राशिः_आकार - 1 ] );
            xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_राशिः_Info.pul_System_Call_राशिः ) &
                                                                                     ( uint32_t ) ( ~( पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_राशिः_Info.pul_Task_राशिः = रिक्त;
        }
        #यदि_अन्तः /* configUSE_MPU_WRAPPERS_V1 == 0 */

        प्रत्यागम &( xMPUSettings->ulContext[ 19 ] );
    }

#अन्यथा /* configENABLE_MPU */

    राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                         TaskFunction_t px_संहिता,
                                         शून्य * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #यदि ( पत्तनम्_PRELOAD_REGISTERS == 0 )
        {
            px_शिखरम्_सम्बन्धि_राशिः--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_XPSR;                        /* xPSR. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;                  /* PC. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_TASK_RETURN_स्थानाङ्कः; /* LR. */
            px_शिखरम्_सम्बन्धि_राशिः -= 5;                                       /* R12, R3, R2 and R1. */
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters;            /* R0. */
            px_शिखरम्_सम्बन्धि_राशिः -= 9;                                       /* R11..R4, EXC_RETURN. */
            *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_EXC_RETURN;
        }
        #अन्यथा /* portPRELOAD_REGISTERS */
        {
            px_शिखरम्_सम्बन्धि_राशिः--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_XPSR;                        /* xPSR. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) px_संहिता;                  /* PC. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) पत्तनम्_TASK_RETURN_स्थानाङ्कः; /* LR. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x12121212UL;            /* R12. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x03030303UL;            /* R3. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x02020202UL;            /* R2. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x01010101UL;            /* R1. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) pvParameters;            /* R0. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x11111111UL;            /* R11. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x10101010UL;            /* R10. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x09090909UL;            /* R09. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x08080808UL;            /* R08. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x07070707UL;            /* R07. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x06060606UL;            /* R06. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x05050505UL;            /* R05. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t ) 0x04040404UL;            /* R04. */
            px_शिखरम्_सम्बन्धि_राशिः--;
            *px_शिखरम्_सम्बन्धि_राशिः = पत्तनम्_INITIAL_EXC_RETURN;                  /* EXC_RETURN. */
        }
        #यदि_अन्तः /* portPRELOAD_REGISTERS */

        प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
    }

#यदि_अन्तः /* configENABLE_MPU */

/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य ) /* PRIVILEGED_FUNCTION */
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
    #यदि ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ध्रुव पत्तनम्_ISR_t * ध्रुव px_सदिशम्_सारणी = पत्तनम्_SCB_VTOR_REG;

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
        configASSERT( px_सदिशम्_सारणी[ पत्तनम्_सदिशम्_सूचकांक_SVC ] == SVC_Handler );
        configASSERT( px_सदिशम्_सारणी[ पत्तनम्_सदिशम्_सूचकांक_PENDSV ] == PendSV_Handler );
    }
    #यदि_अन्तः /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
     * the highest priority. */
    पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_PENDSV_PRI;
    पत्तनम्_NVIC_SHPR3_REG |= पत्तनम्_NVIC_SYSTICK_PRI;
    पत्तनम्_NVIC_SHPR2_REG = 0;

    #यदि ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_सज्जता_MPU();
    }
    #यदि_अन्तः /* configENABLE_MPU */

    /* Start the timer that generates the tick ISR. Interrupts are disabled
     * here already. */
    v_पत्तनम्_सज्जता_Timer_व्यवधानम्();

    /* Initialize the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    #यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #यदि_अन्तः

    /* Start the first task. */
    vStartFirstTask();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    vTaskSwitchContext();
    prvTaskExitError();

    /* Should not get here. */
    प्रत्यागम 0;
}

/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}

/*-----------------------------------------------------------*/

#यदि ( configENABLE_MPU == 1 )

    शून्य v_पत्तनम्_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ध्रुव संरचना x_स्मृतिः_REGION * ध्रुव xRegions,
                                    राशिः_Type_t * px_Bottom_सम्बन्धि_राशिः,
                                    config_राशिः_गभीरता_TYPE ux_राशिः_गभीरता )
    {
        #यदि defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __SRAM_segment_start__;
            बाह्य uint32_t * __SRAM_segment_end__;
            बाह्य uint32_t * __privileged_sram_start__;
            बाह्य uint32_t * __privileged_sram_end__;

        #अन्यथा
            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __SRAM_segment_start__[];
            बाह्य uint32_t __SRAM_segment_end__[];
            बाह्य uint32_t __privileged_sram_start__[];
            बाह्य uint32_t __privileged_sram_end__[];

        #यदि_अन्तः /* defined( __ARMCC_VERSION ) */

        int32_t l_सूचकांक;
        uint32_t ul;

        यदि( xRegions == रिक्त )
        {
            /* No MPU regions are specified so allow access to all RAM. */
            xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                ( ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
                  ( पत्तनम्_MPU_RBAR_REGION_सङ्ख्या_VALID_BITMASK ) |
                  ( पत्तनम्_राशिः_REGION ) );                   /* Region number. */

            xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                ( ( पत्तनम्_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                  ( पत्तनम्_MPU_REGION_EXECUTE_NEVER ) |
                  ( ( configS_C_B_SRAM & पत्तनम्_MPU_RASR_S_C_B_BITMASK ) << पत्तनम्_MPU_RASR_S_C_B_LOCATION ) |
                  ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
                  ( पत्तनम्_MPU_RASR_REGION_ENABLE_BITMASK ) );


            /* Invalidate user configurable regions. */
            प्रति( ul = 1UL; ul <= पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS; ul++ )
            {
                xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | पत्तनम्_MPU_RBAR_REGION_सङ्ख्या_VALID_BITMASK );
                xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
            }
        }
        अन्यथा
        {
            /* This function is called automatically when the task is created - in
             * which case the stack region parameters will be valid.  At all other
             * times the stack parameters will not be valid and it is assumed that the
             * stack region has already been configured. */
            यदि( ux_राशिः_गभीरता > 0 )
            {
                /* Define the region that allows access to the stack. */
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                    ( ( ( uint32_t ) px_Bottom_सम्बन्धि_राशिः ) |
                      ( पत्तनम्_MPU_RBAR_REGION_सङ्ख्या_VALID_BITMASK ) |
                      ( पत्तनम्_राशिः_REGION ) ); /* Region number. */

                xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                    ( ( पत्तनम्_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                      ( पत्तनम्_MPU_REGION_EXECUTE_NEVER ) |
                      ( prv_Get_MPURegion_आकार_Setting( ux_राशिः_गभीरता * ( uint32_t ) परिमाण( राशिः_Type_t ) ) ) |
                      ( ( configS_C_B_SRAM & पत्तनम्_MPU_RASR_S_C_B_BITMASK ) << पत्तनम्_MPU_RASR_S_C_B_LOCATION ) |
                      ( पत्तनम्_MPU_RASR_REGION_ENABLE_BITMASK ) );
            }

            l_सूचकांक = 0;

            प्रति( ul = 1UL; ul <= पत्तनम्_अङ्कः_CONFIGURABLE_REGIONS; ul++ )
            {
                यदि( ( xRegions[ l_सूचकांक ] ).ul_दीर्घता_अन्तर्_अष्टकानि > 0UL )
                {
                    /* Translate the generic region definition contained in
                     * xRegions into the CM0+ specific MPU settings that are then
                     * stored in xMPUSettings. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR =
                        ( ( uint32_t ) xRegions[ l_सूचकांक ].pv_आधारः_स्थानाङ्कः ) |
                        ( पत्तनम्_MPU_RBAR_REGION_सङ्ख्या_VALID_BITMASK ) |
                        ( ul - 1UL ); /* Region number. */

                    xMPUSettings->xRegionsSettings[ ul ].ulRASR =
                        ( prv_Get_MPURegion_आकार_Setting( xRegions[ l_सूचकांक ].ul_दीर्घता_अन्तर्_अष्टकानि ) ) |
                        ( xRegions[ l_सूचकांक ].ulParameters ) |
                        ( पत्तनम्_MPU_RASR_REGION_ENABLE_BITMASK );
                }
                अन्यथा
                {
                    /* Invalidate the region. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | पत्तनम्_MPU_RBAR_REGION_सङ्ख्या_VALID_BITMASK );
                    xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
                }

            l_सूचकांक++;
        }
    }
}

#यदि_अन्तः /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( ध्रुव शून्य * pv_बफर,
                                                size_t x_बफर_दीर्घता,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_बफर_Start_स्थानाङ्कः, ul_बफर_अन्तः_स्थानाङ्कः;
        uint32_t ulRegionStart, ul_Region_आकार, ul_Region_अन्तः;
        uint32_t ulMPURegionAccessPermissions;
        आधारः_Type_t xAccessGranted = pdFALSE;
        ध्रुव xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( रिक्त ); /* Calling task's MPU settings. */

        यदि( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        अन्यथा यदि( ( xTaskMpuSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        अन्यथा
        {
            यदि( पत्तनम्_सङ्कलय_UINT32_WILL_अतिप्रवाहः( ( ( uint32_t ) pv_बफर ), ( ( uint32_t ) x_बफर_दीर्घता - 1UL ) ) == pdFALSE )
            {
                ul_बफर_Start_स्थानाङ्कः = ( uint32_t ) pv_बफर;
                ul_बफर_अन्तः_स्थानाङ्कः = ( ( ( uint32_t ) pv_बफर ) + ( uint32_t ) x_बफर_दीर्घता - 1UL );

                प्रति( i = 0; i < पत्तनम्_योग_अङ्कः_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    यदि( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                          पत्तनम्_MPU_RASR_REGION_ENABLE_BITMASK ) == पत्तनम्_MPU_RASR_REGION_ENABLE_BITMASK )
                    {
                        ulRegionStart = पत्तनम्_EXTRACT_FIRST_स्थानाङ्कः_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR );
                        ul_Region_आकार = पत्तनम्_EXTRACT_REGION_आकार_FROM_RASR( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR );
                        ul_Region_अन्तः = ulRegionStart + ul_Region_आकार;

                        यदि( पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ul_बफर_Start_स्थानाङ्कः,
                                                         ulRegionStart,
                                                         ul_Region_अन्तः ) &&
                            पत्तनम्_IS_स्थानाङ्कः_WITHIN_RANGE( ul_बफर_अन्तः_स्थानाङ्कः,
                                                         ulRegionStart,
                                                         ul_Region_अन्तः ) )
                        {
                            ulMPURegionAccessPermissions = xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                                                           पत्तनम्_MPU_RASR_AP_BITMASK;

                            यदि( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
                            {
                                यदि( ( ulMPURegionAccessPermissions == पत्तनम्_MPU_REGION_PRIV_RW_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == पत्तनम्_MPU_REGION_PRIV_RO_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == पत्तनम्_MPU_REGION_PRIV_RW_UNPRIV_RW ) )
                                {
                                    xAccessGranted = pdTRUE;
                                    भङ्ग;
                                }
                            }
                            अन्यथा यदि( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
                            {
                                यदि( ulMPURegionAccessPermissions == पत्तनम्_MPU_REGION_PRIV_RW_UNPRIV_RW )
                                {
                                    xAccessGranted = pdTRUE;
                                    भङ्ग;
                                }
                            }
                        }
                    }
                }
            }
        }

        प्रत्यागम xAccessGranted;
    }

#यदि_अन्तः /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Is_Inside_व्यवधानम्( शून्य )
{
    uint32_t ul_Current_व्यवधानम्;
    आधारः_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm चञ्चल ( "mrs %0, ipsr" : "=r" ( ul_Current_व्यवधानम् )::"memory" );

    यदि( ul_Current_व्यवधानम् == 0 )
    {
        xReturn = pdFALSE;
    }
    अन्यथा
    {
        xReturn = pdTRUE;
    }

    प्रत्यागम xReturn;
}

/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    शून्य v_पत्तनम्_Grant_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t x_आन्तरिकम्_Task_Handle,
                                         int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
        ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

        xTaskMpuSettings = xTaskGetMPUSettings( x_आन्तरिकम्_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] |= ( 1U << ul_Access_Control_List_प्रविष्टिः_Bit );
    }

#यदि_अन्तः /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    शून्य v_पत्तनम्_Revoke_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t x_आन्तरिकम्_Task_Handle,
                                          int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
        ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

        xTaskMpuSettings = xTaskGetMPUSettings( x_आन्तरिकम्_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] &= ~( 1U << ul_Access_Control_List_प्रविष्टिः_Bit );
    }

#यदि_अन्तः /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_प्रविष्टिः_सूचकांक, ul_Access_Control_List_प्रविष्टिः_Bit;
            आधारः_Type_t xAccessGranted = pdFALSE;
            ध्रुव xMPU_SETTINGS * xTaskMpuSettings;

            यदि( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            अन्यथा
            {
                xTaskMpuSettings = xTaskGetMPUSettings( रिक्त ); /* Calling task's MPU settings. */

                ul_Access_Control_List_प्रविष्टिः_सूचकांक = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object / पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );
                ul_Access_Control_List_प्रविष्टिः_Bit = ( ( uint32_t ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object % पत्तनम्_ACL_प्रविष्टिः_आकार_द्वयङ्काः );

                यदि( ( xTaskMpuSettings->ulTaskFlags & पत्तनम्_TASK_IS_PRIVILEGED_FLAG ) == पत्तनम्_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                अन्यथा
                {
                    यदि( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_प्रविष्टिः_सूचकांक ] & ( 1U << ul_Access_Control_List_प्रविष्टिः_Bit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            प्रत्यागम xAccessGranted;
        }

    #अन्यथा /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        आधारः_Type_t x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( int32_t l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( शून्य ) l_आन्तरिकम्_सूचकांक_सम्बन्धि_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            प्रत्यागम pdTRUE;
        }

    #यदि_अन्तः /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#यदि_अन्तः /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/
