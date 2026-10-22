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
#घोषणा MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "task.h"

/* MPU includes. */
#समावेश "mpu_wrappers.h"
#समावेश "mpu_syscall_numbers.h"

/* Portasm includes. */
#समावेश "portasm.h"

#अघोषित MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
प्रकार व्योम ( * portISR_t )( व्योम );

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#घोषणा portNVIC_SYSTICK_CTRL_REG             ( *( ( अस्थिर uint32_t * ) 0xe000e010 ) )
#घोषणा portNVIC_SYSTICK_LOAD_REG             ( *( ( अस्थिर uint32_t * ) 0xe000e014 ) )
#घोषणा port_NVIC_SYSTICK_CURRENT_मूल्य_REG    ( *( ( अस्थिर uint32_t * ) 0xe000e018 ) )
#घोषणा portNVIC_SHPR3_REG                    ( *( ( अस्थिर uint32_t * ) 0xe000ed20 ) )
#घोषणा portNVIC_SHPR2_REG                    ( *( ( अस्थिर uint32_t * ) 0xe000ed1c ) )
#घोषणा portNVIC_SYSTICK_ENABLE_BIT           ( 1UL << 0UL )
#घोषणा portNVIC_SYSTICK_INT_BIT              ( 1UL << 1UL )
#घोषणा portNVIC_SYSTICK_CLK_BIT              ( 1UL << 2UL )
#घोषणा port_NVIC_SYSTICK_गिनती_FLAG_BIT       ( 1UL << 16UL )
#घोषणा portNVIC_PEND_SYSTICK_CLEAR_BIT       ( 1UL << 25UL )
#घोषणा portNVIC_PEND_SYSTICK_SET_BIT         ( 1UL << 26UL )
#घोषणा portMIN_INTERRUPT_PRIORITY            ( 255UL )
#घोषणा portNVIC_PENDSV_PRI                   ( portMIN_INTERRUPT_PRIORITY << 16UL )
#घोषणा portNVIC_SYSTICK_PRI                  ( portMIN_INTERRUPT_PRIORITY << 24UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#घोषणा portSCB_VTOR_REG                      ( *( ( portISR_t ** ) 0xe000ed08 ) )
#घोषणा portSCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( अस्थिर uint32_t * ) 0xe000ed24 ) )
#घोषणा portSCB_MEM_FAULT_ENABLE_BIT          ( 1UL << 16UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#घोषणा port_VECTOR_सूचकांक_SVC       ( 11 )
#घोषणा port_VECTOR_सूचकांक_PENDSV    ( 14 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#घोषणा port_PSR_ढेर_PADDING_MASK              ( 1UL << 9UL )
#घोषणा port_EXC_RETURN_ढेर_FRAME_TYPE_MASK    ( 1UL << 4UL )

/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#घोषणा portOFFSET_TO_LR     ( 5 )
#घोषणा portOFFSET_TO_PC     ( 6 )
#घोषणा portOFFSET_TO_PSR    ( 7 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#घोषणा portMPU_TYPE_REG                            ( *( ( अस्थिर uint32_t * ) 0xe000ed90 ) )
#घोषणा portMPU_CTRL_REG                            ( *( ( अस्थिर uint32_t * ) 0xe000ed94 ) )

#घोषणा portMPU_RBAR_REG                            ( *( ( अस्थिर uint32_t * ) 0xe000ed9c ) )
#घोषणा portMPU_RASR_REG                            ( *( ( अस्थिर uint32_t * ) 0xe000eda0 ) )

/* MPU Region Attribute and Size Register (RASR) bitmasks. */
#घोषणा portMPU_RASR_AP_BITMASK                     ( 0x7UL << 24UL )
#घोषणा portMPU_RASR_S_C_B_BITMASK                  ( 0x7UL )
#घोषणा portMPU_RASR_S_C_B_LOCATION                 ( 16UL )
#घोषणा port_MPU_RASR_आकार_BITMASK                   ( 0x1FUL << 1UL )
#घोषणा portMPU_RASR_REGION_ENABLE_BITMASK          ( 0x1UL )

/* MPU Region Base Address Register (RBAR) bitmasks. */
#घोषणा portMPU_RBAR_ADDRESS_BITMASK                ( 0xFFFFFF00UL )
#घोषणा port_MPU_RBAR_REGION_संख्या_VALID_BITMASK    ( 0x1UL << 4UL )
#घोषणा port_MPU_RBAR_REGION_संख्या_BITMASK          ( 0x0000000FUL )

/* MPU Control Register (MPU_CTRL) bitmasks. */
#घोषणा portMPU_CTRL_ENABLE_BITMASK                 ( 0x1UL )
#घोषणा portMPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK ( 0x1UL << 2UL ) /* PRIVDEFENA bit. */

/* Expected value of the portMPU_TYPE register. */
#घोषणा port_EXPECTED_MPU_TYPE_मूल्य                 ( 0x8UL << 8UL ) /* 8 DREGION unified. */

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#घोषणा portEXTRACT_FIRST_ADDRESS_FROM_RBAR( rbar ) \
    ( ( rbar ) & portMPU_RBAR_ADDRESS_BITMASK )

/* Extract size of the MPU region as encoded in the
 * RASR (Region Attribute and Size Register) value. */
#घोषणा port_EXTRACT_REGION_आकार_FROM_RASR( rasr ) \
    ( 1 << ( ( ( ( rasr ) & port_MPU_RASR_आकार_BITMASK ) >> 1 )+ 1 ) )

/* Does addr lies within [start, end] address range? */
#घोषणा portIS_ADDRESS_WITHIN_RANGE( addr, start, end ) \
    ( ( ( addr ) >= ( start ) ) && ( ( addr ) <= ( end ) ) )

/* Is the access request satisfied by the available permissions? */
#घोषणा portIS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#घोषणा portUINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#घोषणा portADD_UINT32_WILL_OVERFLOW( a, b )    ( ( a ) > ( portUINT32_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#घोषणा port_MAX_24_BIT_संख्या       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#घोषणा portMISSED_COUNTS_FACTOR    ( 94UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#घोषणा portINITIAL_XPSR    ( 0x01000000 )

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
#घोषणा portINITIAL_EXC_RETURN    ( 0xfffffffdUL )

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#घोषणा portCONTROL_PRIVILEGED_MASK         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#घोषणा portINITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#घोषणा portINITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#अगर_अघोषित configSYSTICK_CLOCK_HZ
    #घोषणा configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #घोषणा portNVIC_SYSTICK_CLK_BIT_CONFIG    ( portNVIC_SYSTICK_CLK_BIT )
#अन्यथा
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #घोषणा portNVIC_SYSTICK_CLK_BIT_CONFIG    ( 0 )
#पूर्ण_अगर

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#अगर_घोषित configTASK_RETURN_ADDRESS
    #घोषणा portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#अन्यथा
    #घोषणा portTASK_RETURN_ADDRESS    prvTaskExitError
#पूर्ण_अगर

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#घोषणा portPRELOAD_REGISTERS    1

/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
अटल व्योम prvTaskExitError( व्योम );

#अगर ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    अटल व्योम prvSetupMPU( व्योम ) PRIVILEGED_FUNCTION;

#पूर्ण_अगर /* configENABLE_MPU */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
व्योम vPortSetupTimerInterrupt( व्योम ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
BaseType_t xPortIsInsideInterrupt( व्योम );

/**
 * @brief Yield the processor.
 */
व्योम vPortYield( व्योम ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
व्योम vPortEnterCritical( व्योम ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
व्योम vPortExitCritical( व्योम ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
व्योम SysTick_Handler( व्योम ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
portDONT_DISCARD व्योम vPortSVCHandler_C( uint32_t * pul_Caller_ढेर_Address ) PRIVILEGED_FUNCTION;

#अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    व्योम vSystemCallEnter( uint32_t * pul_Task_ढेर,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_संख्या ) PRIVILEGED_FUNCTION;

#पूर्ण_अगर /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    व्योम vRequestSystemCallExit( व्योम ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#पूर्ण_अगर /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    व्योम vSystemCallExit( uint32_t * pul_System_Call_ढेर,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#पूर्ण_अगर /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#अगर ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    BaseType_t xPortIsTaskPrivileged( व्योम ) PRIVILEGED_FUNCTION;

#पूर्ण_अगर /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_तथ्य अटल BaseType_t xSchedulerRunning = pdFALSE;

#पूर्ण_अगर

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
PRIVILEGED_तथ्य अटल अस्थिर uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

#अगर ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_तथ्य अटल uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_तथ्य अटल uint32_t xMaximumPossibleSuppressedTicks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_तथ्य अटल uint32_t ulStoppedTimerCompensation = 0;

#पूर्ण_अगर /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#अगर ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) व्योम vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
    {
        uint32_t ul_Reload_मूल्य, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_बायाँ;
        TickType_t xModifiableIdleTime;

        /* Make sure the SysTick reload value does not overflow the counter. */
        अगर( xExpectedIdleTime > xMaximumPossibleSuppressedTicks )
        {
            xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm अस्थिर ( "cpsid i" ::: "memory" );
        __asm अस्थिर ( "dsb" );
        __asm अस्थिर ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        अगर( eTaskConfirmSleepModeStatus() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm अस्थिर ( "cpsie i" ::: "memory" );
        }
        अन्यथा
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_बायाँ = port_NVIC_SYSTICK_CURRENT_मूल्य_REG;

            अगर( ul_Sys_Tick_Decrements_बायाँ == 0 )
            {
                ul_Sys_Tick_Decrements_बायाँ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_मूल्य = ul_Sys_Tick_Decrements_बायाँ + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );

            अगर( ( portNVIC_INT_CTRL_REG & portNVIC_PEND_SYSTICK_SET_BIT ) != 0 )
            {
                portNVIC_INT_CTRL_REG = portNVIC_PEND_SYSTICK_CLEAR_BIT;
                ul_Reload_मूल्य -= ulTimerCountsForOneTick;
            }

            अगर( ul_Reload_मूल्य > ulStoppedTimerCompensation )
            {
                ul_Reload_मूल्य -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            portNVIC_SYSTICK_LOAD_REG = ul_Reload_मूल्य;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            port_NVIC_SYSTICK_CURRENT_मूल्य_REG = 0UL;

            /* Restart SysTick. */
            portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            xModifiableIdleTime = xExpectedIdleTime;
            configPRE_SLEEP_PROCESSING( xModifiableIdleTime );

            अगर( xModifiableIdleTime > 0 )
            {
                __asm अस्थिर ( "dsb" ::: "memory" );
                __asm अस्थिर ( "wfi" );
                __asm अस्थिर ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm अस्थिर ( "cpsie i" ::: "memory" );
            __asm अस्थिर ( "dsb" );
            __asm अस्थिर ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm अस्थिर ( "cpsid i" ::: "memory" );
            __asm अस्थिर ( "dsb" );
            __asm अस्थिर ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT );

            /* Determine whether the SysTick has already counted to zero. */
            अगर( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_गिनती_FLAG_BIT ) != 0 )
            {
                uint32_t ul_Calculated_Load_मूल्य;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_Load_मूल्य = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_मूल्य - port_NVIC_SYSTICK_CURRENT_मूल्य_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                अगर( ( ul_Calculated_Load_मूल्य <= ulStoppedTimerCompensation ) || ( ul_Calculated_Load_मूल्य > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_Load_मूल्य = ( ulTimerCountsForOneTick - 1UL );
                }

                portNVIC_SYSTICK_LOAD_REG = ul_Calculated_Load_मूल्य;

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
                ul_Sys_Tick_Decrements_बायाँ = port_NVIC_SYSTICK_CURRENT_मूल्य_REG;
                #अगर ( portNVIC_SYSTICK_CLK_BIT_CONFIG != portNVIC_SYSTICK_CLK_BIT )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    अगर( ul_Sys_Tick_Decrements_बायाँ == 0 )
                    {
                        ul_Sys_Tick_Decrements_बायाँ = ul_Reload_मूल्य;
                    }
                }
                #पूर्ण_अगर /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_बायाँ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                portNVIC_SYSTICK_LOAD_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            port_NVIC_SYSTICK_CURRENT_मूल्य_REG = 0UL;
            portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            #अगर ( portNVIC_SYSTICK_CLK_BIT_CONFIG == portNVIC_SYSTICK_CLK_BIT )
            {
                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
            }
            #अन्यथा
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT;

                अगर( ( portNVIC_SYSTICK_CTRL_REG & port_NVIC_SYSTICK_गिनती_FLAG_BIT ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    port_NVIC_SYSTICK_CURRENT_मूल्य_REG = 0;
                }

                portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;
                portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
            }
            #पूर्ण_अगर /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            vTaskStepTick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm अस्थिर ( "cpsie i" ::: "memory" );
        }
    }

#पूर्ण_अगर /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) व्योम vPortSetupTimerInterrupt( व्योम ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #अगर ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ );
        xMaximumPossibleSuppressedTicks = port_MAX_24_BIT_संख्या / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = portMISSED_COUNTS_FACTOR / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #पूर्ण_अगर /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT_CONFIG;
    port_NVIC_SYSTICK_CURRENT_मूल्य_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
    portNVIC_SYSTICK_CTRL_REG = portNVIC_SYSTICK_CLK_BIT_CONFIG | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT;
}

/*-----------------------------------------------------------*/

अटल व्योम prvTaskExitError( व्योम )
{
    अस्थिर uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    जबतक( ulDummy == 0 )
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

#अगर ( configENABLE_MPU == 1 )

    अटल uint32_t prv_Get_MPURegion_आकार_Setting( uint32_t ul_Actual_आकार_In_Bytes )
    {
        uint32_t ul_Region_आकार, ul_Return_मूल्य = 7UL;

        /* 256 is the smallest region size, 31 is the largest valid value for
         * ulReturnValue. */
        क्रम( ul_Region_आकार = 256UL; ul_Return_मूल्य < 31UL; ( ul_Region_आकार <<= 1UL ) )
        {
            अगर( ul_Actual_आकार_In_Bytes <= ul_Region_आकार )
            {
                अवरोध;
            }
            अन्यथा
            {
                ul_Return_मूल्य++;
            }
        }

        /* Shift the code by one before returning so it can be written directly
         * into the correct bit position of the attribute register. */
        वापस( ul_Return_मूल्य << 1UL );
    }

#पूर्ण_अगर /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#अगर ( configENABLE_MPU == 1 )

    अटल व्योम prvSetupMPU( व्योम ) /* PRIVILEGED_FUNCTION */
    {
        #अगर defined( __ARMCC_VERSION )

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

        #पूर्ण_अगर /* defined( __ARMCC_VERSION ) */

        /* Ensure that the MPU is present. */
        configASSERT( portMPU_TYPE_REG == port_EXPECTED_MPU_TYPE_मूल्य );

        /* Check that the MPU is present. */
        अगर( portMPU_TYPE_REG == port_EXPECTED_MPU_TYPE_मूल्य )
        {
            /* Setup privileged flash as Read Only so that privileged tasks can
             * read it but not modify. */
            portMPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                 ( port_MPU_RBAR_REGION_संख्या_VALID_BITMASK ) |
                                 ( portPRIVILEGED_FLASH_REGION ) );

            portMPU_RASR_REG = ( ( portMPU_REGION_PRIV_RO_UNPRIV_NA ) |
                                 ( ( configS_C_B_FLASH & portMPU_RASR_S_C_B_BITMASK ) << portMPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                 ( portMPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup unprivileged flash as Read Only by both privileged and
             * unprivileged tasks. All tasks can read it but no-one can modify. */
            portMPU_RBAR_REG = ( ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                 ( port_MPU_RBAR_REGION_संख्या_VALID_BITMASK ) |
                                 ( portUNPRIVILEGED_FLASH_REGION ) );

            portMPU_RASR_REG = ( ( portMPU_REGION_PRIV_RO_UNPRIV_RO ) |
                                 ( ( configS_C_B_FLASH & portMPU_RASR_S_C_B_BITMASK ) << portMPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                 ( portMPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup RAM containing kernel data for privileged access only. */
            portMPU_RBAR_REG = ( ( uint32_t ) __privileged_sram_start__ ) | /* Base address. */
                                 ( port_MPU_RBAR_REGION_संख्या_VALID_BITMASK ) |
                                 ( portPRIVILEGED_RAM_REGION );

            portMPU_RASR_REG = ( ( portMPU_REGION_PRIV_RW_UNPRIV_NA ) |
                                 ( portMPU_REGION_EXECUTE_NEVER ) |
                                 ( ( configS_C_B_SRAM & portMPU_RASR_S_C_B_BITMASK ) << portMPU_RASR_S_C_B_LOCATION ) |
                                 prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __privileged_sram_end__ - ( uint32_t ) __privileged_sram_start__ ) |
                                 ( portMPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Enable MPU with privileged background access i.e. unmapped
             * regions have privileged access. */
            portMPU_CTRL_REG |= ( portMPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK |
                                  portMPU_CTRL_ENABLE_BITMASK );
        }
    }

#पूर्ण_अगर /* configENABLE_MPU */

/*-----------------------------------------------------------*/

व्योम vPortYield( व्योम ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm अस्थिर ( "dsb" ::: "memory" );
    __asm अस्थिर ( "isb" );
}

/*-----------------------------------------------------------*/

व्योम vPortEnterCritical( व्योम ) /* PRIVILEGED_FUNCTION */
{
    portDISABLE_INTERRUPTS();
    ulCriticalNesting++;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm अस्थिर ( "dsb" ::: "memory" );
    __asm अस्थिर ( "isb" );
}

/*-----------------------------------------------------------*/

व्योम vPortExitCritical( व्योम ) /* PRIVILEGED_FUNCTION */
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    अगर( ulCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
    }
}

/*-----------------------------------------------------------*/

व्योम SysTick_Handler( व्योम ) /* PRIVILEGED_FUNCTION */
{
    uint32_t ulPreviousMask;

    ulPreviousMask = portSET_INTERRUPT_MASK_FROM_ISR();

    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        अगर( xTaskIncrementTick() != pdFALSE )
        {
            traceISR_EXIT_TO_SCHEDULER();
            /* Pend a context switch. */
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
        }
        अन्यथा
        {
            traceISR_EXIT();
        }
    }

    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulPreviousMask );
}

/*-----------------------------------------------------------*/

व्योम vPortSVCHandler_C( uint32_t * pul_Caller_ढेर_Address ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        #अगर defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __syscalls_flash_start__;
            बाह्य uint32_t * __syscalls_flash_end__;

        #अन्यथा

            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __syscalls_flash_start__[];
            बाह्य uint32_t __syscalls_flash_end__[];

        #पूर्ण_अगर /* defined( __ARMCC_VERSION ) */

    #पूर्ण_अगर /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    uint32_t ulPC;
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_ढेर_Address[ portOFFSET_TO_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    चयन( ucSVCNumber )
    {
        हाल portSVC_START_SCHEDULER:
            /* Setup the context of the first task so that the first task starts
             * executing. */
            vRestoreContextOfFirstTask();
            अवरोध;

    #अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        हाल portSVC_RAISE_PRIVILEGE:
            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            अगर( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            अवरोध;

    #पूर्ण_अगर /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #अगर ( configENABLE_MPU == 1 )

        हाल portSVC_YIELD:
            vPortYield();
            अवरोध;

    #पूर्ण_अगर /* configENABLE_MPU == 1 */

        शेष:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}

/*-----------------------------------------------------------*/

#अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    व्योम vSystemCallEnter( uint32_t * pul_Task_ढेर,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_संख्या ) /* PRIVILEGED_FUNCTION */
    {
        बाह्य TaskHandle_t pxCurrentTCB;
        बाह्य UBaseType_t uxSystemCallImplementations[ अंक_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ढेर;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        स्थिर uint32_t ul_Hardware_Saved_Exception_Frame_आकार = 8;

        #अगर defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __syscalls_flash_start__;
            बाह्य uint32_t * __syscalls_flash_end__;

        #अन्यथा

            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __syscalls_flash_start__[];
            बाह्य uint32_t __syscalls_flash_end__[];

        #पूर्ण_अगर /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ढेर[ portOFFSET_TO_PC ];
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
        अगर( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ढेर_Info.pul_Task_ढेर == शून्य ) &&
            ( uxSystemCallImplementations[ uc_System_Call_संख्या ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ढेर = pxMpuSettings->x_System_Call_ढेर_Info.pul_System_Call_ढेर;

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ढेर = pul_System_Call_ढेर - ul_Hardware_Saved_Exception_Frame_आकार;

            /* Copy the stack frame. */
            क्रम( i = 0; i < ul_Hardware_Saved_Exception_Frame_आकार; i++ )
            {
                pul_System_Call_ढेर[ i ] = pul_Task_ढेर[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ढेर_Info.ulLinkRegisterAtSystemCallEntry = pul_Task_ढेर[ portOFFSET_TO_LR ];

            /* Use the pulSystemCallStack in thread mode. */
            __asm अस्थिर ( "msr psp, %0" : : "r" ( pul_System_Call_ढेर ) );

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ढेर[ portOFFSET_TO_PC ] = uxSystemCallImplementations[ uc_System_Call_संख्या ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ढेर[ portOFFSET_TO_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ढेर_Info.pul_Task_ढेर = pul_Task_ढेर + ul_Hardware_Saved_Exception_Frame_आकार;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            अगर( ( pul_Task_ढेर[ portOFFSET_TO_PSR ] & port_PSR_ढेर_PADDING_MASK ) == port_PSR_ढेर_PADDING_MASK )
            {
                pxMpuSettings->ulTaskFlags |= port_ढेर_FRAME_HAS_PADDING_FLAG;
            }
            अन्यथा
            {
                pxMpuSettings->ulTaskFlags &= ( ~port_ढेर_FRAME_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ढेर[ portOFFSET_TO_PSR ] &= ( ~port_PSR_ढेर_PADDING_MASK );

            /* Raise the privilege for the duration of the system call. */
            __asm अस्थिर
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

#पूर्ण_अगर /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    व्योम vRequestSystemCallExit( व्योम ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm अस्थिर ( "svc %0 \n" ::"i" ( portSVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#पूर्ण_अगर /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    व्योम vSystemCallExit( uint32_t * pul_System_Call_ढेर,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        बाह्य TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ढेर;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        स्थिर uint32_t ul_Hardware_Saved_Exception_Frame_आकार = 8;

        #अगर defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            बाह्य uint32_t * __privileged_functions_start__;
            बाह्य uint32_t * __privileged_functions_end__;

        #अन्यथा

            /* Declaration when these variable are exported from linker scripts. */
            बाह्य uint32_t __privileged_functions_start__[];
            बाह्य uint32_t __privileged_functions_end__[];

        #पूर्ण_अगर /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ढेर[ portOFFSET_TO_PC ];
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
        अगर( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ढेर_Info.pul_Task_ढेर != शून्य ) )
        {
            pul_Task_ढेर = pxMpuSettings->x_System_Call_ढेर_Info.pul_Task_ढेर;

            /* Make space on the task stack for the stack frame. */
            pul_Task_ढेर = pul_Task_ढेर - ul_Hardware_Saved_Exception_Frame_आकार;

            /* Copy the stack frame. */
            क्रम( i = 0; i < ul_Hardware_Saved_Exception_Frame_आकार; i++ )
            {
                pul_Task_ढेर[ i ] = pul_System_Call_ढेर[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm अस्थिर ( "msr psp, %0" : : "r" ( pul_Task_ढेर ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ढेर[ portOFFSET_TO_PC ] = pxMpuSettings->x_System_Call_ढेर_Info.ulLinkRegisterAtSystemCallEntry;

            /* Ensure that LR has a valid value.*/
            pul_Task_ढेर[ portOFFSET_TO_LR ] = pxMpuSettings->x_System_Call_ढेर_Info.ulLinkRegisterAtSystemCallEntry;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            अगर( ( pxMpuSettings->ulTaskFlags & port_ढेर_FRAME_HAS_PADDING_FLAG ) == port_ढेर_FRAME_HAS_PADDING_FLAG )
            {
                pul_Task_ढेर[ portOFFSET_TO_PSR ] |= port_PSR_ढेर_PADDING_MASK;
            }
            अन्यथा
            {
                pul_Task_ढेर[ portOFFSET_TO_PSR ] &= ( ~port_PSR_ढेर_PADDING_MASK );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ढेर_Info.pul_Task_ढेर = शून्य;

            /* Drop the privilege before returning to the thread mode. */
            __asm अस्थिर
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

#पूर्ण_अगर /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#अगर ( configENABLE_MPU == 1 )

    BaseType_t xPortIsTaskPrivileged( व्योम ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xTaskIsPrivileged = pdFALSE;
        स्थिर xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( शून्य ); /* Calling task's MPU settings. */

        अगर( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        वापस xTaskIsPrivileged;
    }

#पूर्ण_अगर /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#अगर ( configENABLE_MPU == 1 )

    ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                         TaskFunction_t pxCode,
                                         व्योम * pvParameters,
                                         BaseType_t xRunPrivileged,
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
        xMPUSettings->ulContext[ 13 ] = ( uint32_t ) portTASK_RETURN_ADDRESS; /* LR. */
        xMPUSettings->ulContext[ 14 ] = ( uint32_t ) pxCode;                  /* PC. */
        xMPUSettings->ulContext[ 15 ] = portINITIAL_XPSR;                     /* xPSR. */

        xMPUSettings->ulContext[ 16 ] = ( uint32_t ) ( px_शीर्ष_Of_ढेर - 8 ); /* PSP with the hardware saved stack. */
        अगर( xRunPrivileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= portTASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) portINITIAL_CONTROL_PRIVILEGED; /* CONTROL. */
        }
        अन्यथा
        {
            xMPUSettings->ulTaskFlags &= ( ~portTASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) portINITIAL_CONTROL_UNPRIVILEGED; /* CONTROL. */
        }
        xMPUSettings->ulContext[ 18 ] = portINITIAL_EXC_RETURN; /* LR (EXC_RETURN). */

        #अगर ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_ढेर_Info.pul_System_Call_ढेर = &( xMPUSettings->x_System_Call_ढेर_Info.ul_System_Call_ढेर_बफर[ config_SYSTEM_CALL_ढेर_आकार - 1 ] );
            xMPUSettings->x_System_Call_ढेर_Info.pul_System_Call_ढेर = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ढेर_Info.pul_System_Call_ढेर ) &
                                                                                     ( uint32_t ) ( ~( portBYTE_ALIGNMENT_MASK ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_ढेर_Info.pul_Task_ढेर = शून्य;
        }
        #पूर्ण_अगर /* configUSE_MPU_WRAPPERS_V1 == 0 */

        वापस &( xMPUSettings->ulContext[ 19 ] );
    }

#अन्यथा /* configENABLE_MPU */

    ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                         TaskFunction_t pxCode,
                                         व्योम * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #अगर ( portPRELOAD_REGISTERS == 0 )
        {
            px_शीर्ष_Of_ढेर--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_शीर्ष_Of_ढेर = portINITIAL_XPSR;                        /* xPSR. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pxCode;                  /* PC. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) portTASK_RETURN_ADDRESS; /* LR. */
            px_शीर्ष_Of_ढेर -= 5;                                       /* R12, R3, R2 and R1. */
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters;            /* R0. */
            px_शीर्ष_Of_ढेर -= 9;                                       /* R11..R4, EXC_RETURN. */
            *px_शीर्ष_Of_ढेर = portINITIAL_EXC_RETURN;
        }
        #अन्यथा /* portPRELOAD_REGISTERS */
        {
            px_शीर्ष_Of_ढेर--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_शीर्ष_Of_ढेर = portINITIAL_XPSR;                        /* xPSR. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pxCode;                  /* PC. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) portTASK_RETURN_ADDRESS; /* LR. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x12121212UL;            /* R12. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x03030303UL;            /* R3. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x02020202UL;            /* R2. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x01010101UL;            /* R1. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters;            /* R0. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x11111111UL;            /* R11. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x10101010UL;            /* R10. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x09090909UL;            /* R09. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x08080808UL;            /* R08. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x07070707UL;            /* R07. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x06060606UL;            /* R06. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x05050505UL;            /* R05. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x04040404UL;            /* R04. */
            px_शीर्ष_Of_ढेर--;
            *px_शीर्ष_Of_ढेर = portINITIAL_EXC_RETURN;                  /* EXC_RETURN. */
        }
        #पूर्ण_अगर /* portPRELOAD_REGISTERS */

        वापस px_शीर्ष_Of_ढेर;
    }

#पूर्ण_अगर /* configENABLE_MPU */

/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम ) /* PRIVILEGED_FUNCTION */
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
    #अगर ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        स्थिर portISR_t * स्थिर pxVectorTable = portSCB_VTOR_REG;

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
        configASSERT( pxVectorTable[ port_VECTOR_सूचकांक_SVC ] == SVC_Handler );
        configASSERT( pxVectorTable[ port_VECTOR_सूचकांक_PENDSV ] == PendSV_Handler );
    }
    #पूर्ण_अगर /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
     * the highest priority. */
    portNVIC_SHPR3_REG |= portNVIC_PENDSV_PRI;
    portNVIC_SHPR3_REG |= portNVIC_SYSTICK_PRI;
    portNVIC_SHPR2_REG = 0;

    #अगर ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prvSetupMPU();
    }
    #पूर्ण_अगर /* configENABLE_MPU */

    /* Start the timer that generates the tick ISR. Interrupts are disabled
     * here already. */
    vPortSetupTimerInterrupt();

    /* Initialize the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    #अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #पूर्ण_अगर

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
    वापस 0;
}

/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}

/*-----------------------------------------------------------*/

#अगर ( configENABLE_MPU == 1 )

    व्योम vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    स्थिर काष्ठा xMEMORY_REGION * स्थिर xRegions,
                                    ढेर_Type_t * px_Bottom_Of_ढेर,
                                    config_ढेर_DEPTH_TYPE ux_ढेर_Depth )
    {
        #अगर defined( __ARMCC_VERSION )

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

        #पूर्ण_अगर /* defined( __ARMCC_VERSION ) */

        int32_t l_सूचकांक;
        uint32_t ul;

        अगर( xRegions == शून्य )
        {
            /* No MPU regions are specified so allow access to all RAM. */
            xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                ( ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
                  ( port_MPU_RBAR_REGION_संख्या_VALID_BITMASK ) |
                  ( port_ढेर_REGION ) );                   /* Region number. */

            xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                ( ( portMPU_REGION_PRIV_RW_UNPRIV_RW ) |
                  ( portMPU_REGION_EXECUTE_NEVER ) |
                  ( ( configS_C_B_SRAM & portMPU_RASR_S_C_B_BITMASK ) << portMPU_RASR_S_C_B_LOCATION ) |
                  ( prv_Get_MPURegion_आकार_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
                  ( portMPU_RASR_REGION_ENABLE_BITMASK ) );


            /* Invalidate user configurable regions. */
            क्रम( ul = 1UL; ul <= port_अंक_CONFIGURABLE_REGIONS; ul++ )
            {
                xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | port_MPU_RBAR_REGION_संख्या_VALID_BITMASK );
                xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
            }
        }
        अन्यथा
        {
            /* This function is called automatically when the task is created - in
             * which case the stack region parameters will be valid.  At all other
             * times the stack parameters will not be valid and it is assumed that the
             * stack region has already been configured. */
            अगर( ux_ढेर_Depth > 0 )
            {
                /* Define the region that allows access to the stack. */
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                    ( ( ( uint32_t ) px_Bottom_Of_ढेर ) |
                      ( port_MPU_RBAR_REGION_संख्या_VALID_BITMASK ) |
                      ( port_ढेर_REGION ) ); /* Region number. */

                xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                    ( ( portMPU_REGION_PRIV_RW_UNPRIV_RW ) |
                      ( portMPU_REGION_EXECUTE_NEVER ) |
                      ( prv_Get_MPURegion_आकार_Setting( ux_ढेर_Depth * ( uint32_t ) माप( ढेर_Type_t ) ) ) |
                      ( ( configS_C_B_SRAM & portMPU_RASR_S_C_B_BITMASK ) << portMPU_RASR_S_C_B_LOCATION ) |
                      ( portMPU_RASR_REGION_ENABLE_BITMASK ) );
            }

            l_सूचकांक = 0;

            क्रम( ul = 1UL; ul <= port_अंक_CONFIGURABLE_REGIONS; ul++ )
            {
                अगर( ( xRegions[ l_सूचकांक ] ).ul_लंबाई_In_Bytes > 0UL )
                {
                    /* Translate the generic region definition contained in
                     * xRegions into the CM0+ specific MPU settings that are then
                     * stored in xMPUSettings. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR =
                        ( ( uint32_t ) xRegions[ l_सूचकांक ].pvBaseAddress ) |
                        ( port_MPU_RBAR_REGION_संख्या_VALID_BITMASK ) |
                        ( ul - 1UL ); /* Region number. */

                    xMPUSettings->xRegionsSettings[ ul ].ulRASR =
                        ( prv_Get_MPURegion_आकार_Setting( xRegions[ l_सूचकांक ].ul_लंबाई_In_Bytes ) ) |
                        ( xRegions[ l_सूचकांक ].ulParameters ) |
                        ( portMPU_RASR_REGION_ENABLE_BITMASK );
                }
                अन्यथा
                {
                    /* Invalidate the region. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | port_MPU_RBAR_REGION_संख्या_VALID_BITMASK );
                    xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
                }

            l_सूचकांक++;
        }
    }
}

#पूर्ण_अगर /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    BaseType_t x_Port_Is_Authorized_To_Access_बफर( स्थिर व्योम * pv_बफर,
                                                माप_प्रकार x_बफर_लंबाई,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_बफर_Start_Address, ul_बफर_End_Address;
        uint32_t ulRegionStart, ul_Region_आकार, ulRegionEnd;
        uint32_t ulMPURegionAccessPermissions;
        BaseType_t xAccessGranted = pdFALSE;
        स्थिर xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( शून्य ); /* Calling task's MPU settings. */

        अगर( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        अन्यथा अगर( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        अन्यथा
        {
            अगर( portADD_UINT32_WILL_OVERFLOW( ( ( uint32_t ) pv_बफर ), ( ( uint32_t ) x_बफर_लंबाई - 1UL ) ) == pdFALSE )
            {
                ul_बफर_Start_Address = ( uint32_t ) pv_बफर;
                ul_बफर_End_Address = ( ( ( uint32_t ) pv_बफर ) + ( uint32_t ) x_बफर_लंबाई - 1UL );

                क्रम( i = 0; i < port_योग_अंक_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    अगर( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                          portMPU_RASR_REGION_ENABLE_BITMASK ) == portMPU_RASR_REGION_ENABLE_BITMASK )
                    {
                        ulRegionStart = portEXTRACT_FIRST_ADDRESS_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR );
                        ul_Region_आकार = port_EXTRACT_REGION_आकार_FROM_RASR( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR );
                        ulRegionEnd = ulRegionStart + ul_Region_आकार;

                        अगर( portIS_ADDRESS_WITHIN_RANGE( ul_बफर_Start_Address,
                                                         ulRegionStart,
                                                         ulRegionEnd ) &&
                            portIS_ADDRESS_WITHIN_RANGE( ul_बफर_End_Address,
                                                         ulRegionStart,
                                                         ulRegionEnd ) )
                        {
                            ulMPURegionAccessPermissions = xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                                                           portMPU_RASR_AP_BITMASK;

                            अगर( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
                            {
                                अगर( ( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RW_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RO_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RW_UNPRIV_RW ) )
                                {
                                    xAccessGranted = pdTRUE;
                                    अवरोध;
                                }
                            }
                            अन्यथा अगर( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
                            {
                                अगर( ulMPURegionAccessPermissions == portMPU_REGION_PRIV_RW_UNPRIV_RW )
                                {
                                    xAccessGranted = pdTRUE;
                                    अवरोध;
                                }
                            }
                        }
                    }
                }
            }
        }

        वापस xAccessGranted;
    }

#पूर्ण_अगर /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/

BaseType_t xPortIsInsideInterrupt( व्योम )
{
    uint32_t ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm अस्थिर ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

    अगर( ulCurrentInterrupt == 0 )
    {
        xReturn = pdFALSE;
    }
    अन्यथा
    {
        xReturn = pdTRUE;
    }

    वापस xReturn;
}

/*-----------------------------------------------------------*/

#अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    व्योम vPortGrantAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                         int32_t l_Internal_सूचकांक_Of_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_Entry_सूचकांक, ulAccessControlListEntryBit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_Entry_सूचकांक = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object / port_ACL_ENTRY_आकार_BITS );
        ulAccessControlListEntryBit = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object % port_ACL_ENTRY_आकार_BITS );

        xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_Entry_सूचकांक ] |= ( 1U << ulAccessControlListEntryBit );
    }

#पूर्ण_अगर /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    व्योम vPortRevokeAccessToKernelObject( TaskHandle_t xInternalTaskHandle,
                                          int32_t l_Internal_सूचकांक_Of_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_Entry_सूचकांक, ulAccessControlListEntryBit;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_Entry_सूचकांक = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object / port_ACL_ENTRY_आकार_BITS );
        ulAccessControlListEntryBit = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object % port_ACL_ENTRY_आकार_BITS );

        xTaskMpuSettings = xTaskGetMPUSettings( xInternalTaskHandle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_Entry_सूचकांक ] &= ~( 1U << ulAccessControlListEntryBit );
    }

#पूर्ण_अगर /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#अगर ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t l_Internal_सूचकांक_Of_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_Entry_सूचकांक, ulAccessControlListEntryBit;
            BaseType_t xAccessGranted = pdFALSE;
            स्थिर xMPU_SETTINGS * xTaskMpuSettings;

            अगर( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            अन्यथा
            {
                xTaskMpuSettings = xTaskGetMPUSettings( शून्य ); /* Calling task's MPU settings. */

                ul_Access_Control_List_Entry_सूचकांक = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object / port_ACL_ENTRY_आकार_BITS );
                ulAccessControlListEntryBit = ( ( uint32_t ) l_Internal_सूचकांक_Of_Kernel_Object % port_ACL_ENTRY_आकार_BITS );

                अगर( ( xTaskMpuSettings->ulTaskFlags & portTASK_IS_PRIVILEGED_FLAG ) == portTASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                अन्यथा
                {
                    अगर( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_Entry_सूचकांक ] & ( 1U << ulAccessControlListEntryBit ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            वापस xAccessGranted;
        }

    #अन्यथा /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        BaseType_t xPortIsAuthorizedToAccessKernelObject( int32_t l_Internal_सूचकांक_Of_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( व्योम ) l_Internal_सूचकांक_Of_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            वापस pdTRUE;
        }

    #पूर्ण_अगर /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#पूर्ण_अगर /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/
