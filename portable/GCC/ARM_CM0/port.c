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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

/* MPU includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_wrappers.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_syscall_numbers.h"

/* Portasm includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "portasm.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ ( * ਪੋਰਟ_ISR_t )( ਖਾਲੀ );

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG             ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e010 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG             ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e014 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG    ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000e018 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SHPR3_REG                    ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed20 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SHPR2_REG                    ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed1c ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ           ( 1UL << 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ              ( 1UL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ              ( 1UL << 2UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_ਗਿਣਤੀ_FLAG_ਦੋਆਧਾਰੀ_ਅੰਕ       ( 1UL << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PEND_SYSTICK_CLEAR_ਦੋਆਧਾਰੀ_ਅੰਕ       ( 1UL << 25UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PEND_SYSTICK_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ         ( 1UL << 26UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ            ( 255UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSV_PRI                   ( ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ << 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_PRI                  ( ਪੋਰਟ_MIN_ਰੁਕਾਵਟ_ਤਰਜੀਹ << 24UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCB_VTOR_REG                      ( *( ( ਪੋਰਟ_ISR_t ** ) 0xe000ed08 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed24 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SCB_MEM_FAULT_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ          ( 1UL << 16UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_SVC       ( 11 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_PENDSV    ( 14 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ              ( 1UL << 9UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXC_RETURN_ਢੇਰ_ਚੌਖਟਾ_TYPE_ਨਕਾਬ    ( 1UL << 4UL )

/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR     ( 5 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC     ( 6 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR    ( 7 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_TYPE_REG                            ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed90 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_CTRL_REG                            ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed94 ) )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RBAR_REG                            ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed9c ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RASR_REG                            ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000eda0 ) )

/* MPU Region Attribute and Size Register (RASR) bitmasks. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RASR_AP_BITMASK                     ( 0x7UL << 24UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RASR_S_C_B_BITMASK                  ( 0x7UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RASR_S_C_B_LOCATION                 ( 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RASR_ਮਾਪ_BITMASK                   ( 0x1FUL << 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RASR_REGION_ENABLE_BITMASK          ( 0x1UL )

/* MPU Region Base Address Register (RBAR) bitmasks. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RBAR_ਪਤਾ_BITMASK                ( 0xFFFFFF00UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RBAR_REGION_ਸੰਖਿਆ_VALID_BITMASK    ( 0x1UL << 4UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_RBAR_REGION_ਸੰਖਿਆ_BITMASK          ( 0x0000000FUL )

/* MPU Control Register (MPU_CTRL) bitmasks. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_CTRL_ENABLE_BITMASK                 ( 0x1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK ( 0x1UL << 2UL ) /* PRIVDEFENA bit. */

/* Expected value of the portMPU_TYPE register. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXPECTED_MPU_TYPE_ਮੁੱਲ                 ( 0x8UL << 8UL ) /* 8 DREGION unified. */

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਕੱਢੋ_ਪਹਿਲਾ_ਪਤਾ_FROM_RBAR( rbar ) \
    ( ( rbar ) & ਪੋਰਟ_MPU_RBAR_ਪਤਾ_BITMASK )

/* Extract size of the MPU region as encoded in the
 * RASR (Region Attribute and Size Register) value. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਕੱਢੋ_REGION_ਮਾਪ_FROM_RASR( rasr ) \
    ( 1 << ( ( ( ( rasr ) & ਪੋਰਟ_MPU_RASR_ਮਾਪ_BITMASK ) >> 1 )+ 1 ) )

/* Does addr lies within [start, end] address range? */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( addr, ਸ਼ੁਰੂ, ਸਿਰਾ ) \
    ( ( ( addr ) >= ( ਸ਼ੁਰੂ ) ) && ( ( addr ) <= ( ਸਿਰਾ ) ) )

/* Is the access request satisfied by the available permissions? */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਜੋੜੋ_UINT32_WILL_ਉਛਾਲ( a, b )    ( ( a ) > ( ਪੋਰਟ_UINT32_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_24_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੰਖਿਆ       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MISSED_COUNTS_ਗੁਣਕ    ( 94UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_XPSR    ( 0x01000000 )

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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_EXC_RETURN    ( 0xfffffffdUL )

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONTROL_PRIVILEGED_ਨਕਾਬ         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configSYSTICK_CLOCK_HZ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG    ( ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ )
#ਨਹੀਂਤਾਂ
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG    ( 0 )
#ਜੇ_ਅੰਤ

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_TASK_RETURN_ਪਤਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    config_TASK_RETURN_ਪਤਾ
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    prvTaskExitError
#ਜੇ_ਅੰਤ

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRELOAD_REGISTERS    1

/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

#ਜੇ ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_MPU( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* configENABLE_MPU */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Inside_ਰੁਕਾਵਟ( ਖਾਲੀ );

/**
 * @brief Yield the processor.
 */
ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
ਖਾਲੀ SysTick_Handler( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
ਪੋਰਟ_DONT_DISCARD ਖਾਲੀ v_ਪੋਰਟ_SVCHandler_C( uint32_t * pul_Caller_ਢੇਰ_ਪਤਾ ) PRIVILEGED_FUNCTION;

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    ਖਾਲੀ vSystemCallEnter( uint32_t * pul_Task_ਢੇਰ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ਸੰਖਿਆ ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    ਖਾਲੀ vRequestSystemCallExit( ਖਾਲੀ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    ਖਾਲੀ vSystemCallExit( uint32_t * pul_System_Call_ਢੇਰ,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ਜੇ ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

#ਜੇ_ਅੰਤ /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਅਧਾਰ_Type_t xSchedulerRunning = pdFALSE;

#ਜੇ_ਅੰਤ

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਅਸਥਿਰ uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ uint32_t x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ uint32_t ulStoppedTimerCompensation = 0;

#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) ਖਾਲੀ v_ਪੋਰਟ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ਸਮਾਂ )
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
        __asm ਅਸਥਿਰ ( "cpsid i" ::: "memory" );
        __asm ਅਸਥਿਰ ( "dsb" );
        __asm ਅਸਥਿਰ ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ਜੇ( e_Task_Confirm_Sleep_ਬਹੁਲਕ_ਸਥਿਤੀ() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm ਅਸਥਿਰ ( "cpsie i" ::: "memory" );
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
                __asm ਅਸਥਿਰ ( "dsb" ::: "memory" );
                __asm ਅਸਥਿਰ ( "wfi" );
                __asm ਅਸਥਿਰ ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_ਸਮਾਂ );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm ਅਸਥਿਰ ( "cpsie i" ::: "memory" );
            __asm ਅਸਥਿਰ ( "dsb" );
            __asm ਅਸਥਿਰ ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm ਅਸਥਿਰ ( "cpsid i" ::: "memory" );
            __asm ਅਸਥਿਰ ( "dsb" );
            __asm ਅਸਥਿਰ ( "isb" );

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
            __asm ਅਸਥਿਰ ( "cpsie i" ::: "memory" );
        }
    }

#ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) ਖਾਲੀ v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #ਜੇ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_ਦਰ_HZ );
        x_ਵੱਧ_ਤੋਂ_ਵੱਧ_Possible_Suppressed_Ticks = ਪੋਰਟ_MAX_24_ਦੋਆਧਾਰੀ_ਅੰਕ_ਸੰਖਿਆ / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = ਪੋਰਟ_MISSED_COUNTS_ਗੁਣਕ / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #ਜੇ_ਅੰਤ /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG;
    ਪੋਰਟ_NVIC_SYSTICK_CURRENT_ਮੁੱਲ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    ਪੋਰਟ_NVIC_SYSTICK_ਲੱਦੋ_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_ਦਰ_HZ ) - 1UL;
    ਪੋਰਟ_NVIC_SYSTICK_CTRL_REG = ਪੋਰਟ_NVIC_SYSTICK_CLK_ਦੋਆਧਾਰੀ_ਅੰਕ_CONFIG | ਪੋਰਟ_NVIC_SYSTICK_INT_ਦੋਆਧਾਰੀ_ਅੰਕ | ਪੋਰਟ_NVIC_SYSTICK_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ;
}

/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ )
{
    ਅਸਥਿਰ uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    ਜਦੋਂ( ulDummy == 0 )
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

#ਜੇ ( configENABLE_MPU == 1 )

    ਸਥਿਰ uint32_t prv_Get_MPURegion_ਮਾਪ_Setting( uint32_t ul_Actual_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ )
    {
        uint32_t ul_Region_ਮਾਪ, ul_Return_ਮੁੱਲ = 7UL;

        /* 256 is the smallest region size, 31 is the largest valid value for
         * ulReturnValue. */
        ਲਈ( ul_Region_ਮਾਪ = 256UL; ul_Return_ਮੁੱਲ < 31UL; ( ul_Region_ਮਾਪ <<= 1UL ) )
        {
            ਜੇ( ul_Actual_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ <= ul_Region_ਮਾਪ )
            {
                ਰੋਕੋ;
            }
            ਨਹੀਂਤਾਂ
            {
                ul_Return_ਮੁੱਲ++;
            }
        }

        /* Shift the code by one before returning so it can be written directly
         * into the correct bit position of the attribute register. */
        ਵਾਪਸ( ul_Return_ਮੁੱਲ << 1UL );
    }

#ਜੇ_ਅੰਤ /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_MPU( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        #ਜੇ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
            * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __privileged_functions_start__;
            ਬਾਹਰੀ uint32_t * __privileged_functions_end__;
            ਬਾਹਰੀ uint32_t * __FLASH_segment_start__;
            ਬਾਹਰੀ uint32_t * __FLASH_segment_end__;
            ਬਾਹਰੀ uint32_t * __privileged_sram_start__;
            ਬਾਹਰੀ uint32_t * __privileged_sram_end__;

        #ਨਹੀਂਤਾਂ /* if defined( __ARMCC_VERSION ) */

            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __privileged_functions_start__[];
            ਬਾਹਰੀ uint32_t __privileged_functions_end__[];
            ਬਾਹਰੀ uint32_t __FLASH_segment_start__[];
            ਬਾਹਰੀ uint32_t __FLASH_segment_end__[];
            ਬਾਹਰੀ uint32_t __privileged_sram_start__[];
            ਬਾਹਰੀ uint32_t __privileged_sram_end__[];

        #ਜੇ_ਅੰਤ /* defined( __ARMCC_VERSION ) */

        /* Ensure that the MPU is present. */
        configASSERT( ਪੋਰਟ_MPU_TYPE_REG == ਪੋਰਟ_EXPECTED_MPU_TYPE_ਮੁੱਲ );

        /* Check that the MPU is present. */
        ਜੇ( ਪੋਰਟ_MPU_TYPE_REG == ਪੋਰਟ_EXPECTED_MPU_TYPE_ਮੁੱਲ )
        {
            /* Setup privileged flash as Read Only so that privileged tasks can
             * read it but not modify. */
            ਪੋਰਟ_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                 ( ਪੋਰਟ_MPU_RBAR_REGION_ਸੰਖਿਆ_VALID_BITMASK ) |
                                 ( ਪੋਰਟ_PRIVILEGED_FLASH_REGION ) );

            ਪੋਰਟ_MPU_RASR_REG = ( ( ਪੋਰਟ_MPU_REGION_PRIV_RO_UNPRIV_NA ) |
                                 ( ( configS_C_B_FLASH & ਪੋਰਟ_MPU_RASR_S_C_B_BITMASK ) << ਪੋਰਟ_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_ਮਾਪ_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                 ( ਪੋਰਟ_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup unprivileged flash as Read Only by both privileged and
             * unprivileged tasks. All tasks can read it but no-one can modify. */
            ਪੋਰਟ_MPU_RBAR_REG = ( ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                 ( ਪੋਰਟ_MPU_RBAR_REGION_ਸੰਖਿਆ_VALID_BITMASK ) |
                                 ( ਪੋਰਟ_UNPRIVILEGED_FLASH_REGION ) );

            ਪੋਰਟ_MPU_RASR_REG = ( ( ਪੋਰਟ_MPU_REGION_PRIV_RO_UNPRIV_RO ) |
                                 ( ( configS_C_B_FLASH & ਪੋਰਟ_MPU_RASR_S_C_B_BITMASK ) << ਪੋਰਟ_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_ਮਾਪ_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                 ( ਪੋਰਟ_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup RAM containing kernel data for privileged access only. */
            ਪੋਰਟ_MPU_RBAR_REG = ( ( uint32_t ) __privileged_sram_start__ ) | /* Base address. */
                                 ( ਪੋਰਟ_MPU_RBAR_REGION_ਸੰਖਿਆ_VALID_BITMASK ) |
                                 ( ਪੋਰਟ_PRIVILEGED_RAM_REGION );

            ਪੋਰਟ_MPU_RASR_REG = ( ( ਪੋਰਟ_MPU_REGION_PRIV_RW_UNPRIV_NA ) |
                                 ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER ) |
                                 ( ( configS_C_B_SRAM & ਪੋਰਟ_MPU_RASR_S_C_B_BITMASK ) << ਪੋਰਟ_MPU_RASR_S_C_B_LOCATION ) |
                                 prv_Get_MPURegion_ਮਾਪ_Setting( ( uint32_t ) __privileged_sram_end__ - ( uint32_t ) __privileged_sram_start__ ) |
                                 ( ਪੋਰਟ_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Enable MPU with privileged background access i.e. unmapped
             * regions have privileged access. */
            ਪੋਰਟ_MPU_CTRL_REG |= ( ਪੋਰਟ_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK |
                                  ਪੋਰਟ_MPU_CTRL_ENABLE_BITMASK );
        }
    }

#ਜੇ_ਅੰਤ /* configENABLE_MPU */

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm ਅਸਥਿਰ ( "dsb" ::: "memory" );
    __asm ਅਸਥਿਰ ( "isb" );
}

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    ਪੋਰਟ_DISABLE_INTERRUPTS();
    ulCriticalNesting++;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm ਅਸਥਿਰ ( "dsb" ::: "memory" );
    __asm ਅਸਥਿਰ ( "isb" );
}

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    ਜੇ( ulCriticalNesting == 0 )
    {
        ਪੋਰਟ_ENABLE_INTERRUPTS();
    }
}

/*-----------------------------------------------------------*/

ਖਾਲੀ SysTick_Handler( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
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
            ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ;
        }
        ਨਹੀਂਤਾਂ
        {
            traceISR_EXIT();
        }
    }

    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( ul_ਪਿਛਲਾ_ਨਕਾਬ );
}

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_SVCHandler_C( uint32_t * pul_Caller_ਢੇਰ_ਪਤਾ ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        #ਜੇ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __syscalls_flash_start__;
            ਬਾਹਰੀ uint32_t * __syscalls_flash_end__;

        #ਨਹੀਂਤਾਂ

            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __syscalls_flash_start__[];
            ਬਾਹਰੀ uint32_t __syscalls_flash_end__[];

        #ਜੇ_ਅੰਤ /* defined( __ARMCC_VERSION ) */

    #ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    uint32_t ulPC;
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_ਢੇਰ_ਪਤਾ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    ਚੋਣ( ucSVCNumber )
    {
        ਹਾਲਤ ਪੋਰਟ_SVC_ਸ਼ੁਰੂ_SCHEDULER:
            /* Setup the context of the first task so that the first task starts
             * executing. */
            v_Restore_Context_ਦਾ_ਪਹਿਲਾ_Task();
            ਰੋਕੋ;

    #ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        ਹਾਲਤ ਪੋਰਟ_SVC_RAISE_PRIVILEGE:
            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            ਜੇ( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            ਰੋਕੋ;

    #ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #ਜੇ ( configENABLE_MPU == 1 )

        ਹਾਲਤ ਪੋਰਟ_SVC_YIELD:
            v_ਪੋਰਟ_Yield();
            ਰੋਕੋ;

    #ਜੇ_ਅੰਤ /* configENABLE_MPU == 1 */

        ਮੂਲ:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}

/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ਖਾਲੀ vSystemCallEnter( uint32_t * pul_Task_ਢੇਰ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ਸੰਖਿਆ ) /* PRIVILEGED_FUNCTION */
    {
        ਬਾਹਰੀ TaskHandle_t pxCurrentTCB;
        ਬਾਹਰੀ UBaseType_t uxSystemCallImplementations[ ਅੰਕ_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ਢੇਰ;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ਅਚਲ uint32_t ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 8;

        #ਜੇ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __syscalls_flash_start__;
            ਬਾਹਰੀ uint32_t * __syscalls_flash_end__;

        #ਨਹੀਂਤਾਂ

            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __syscalls_flash_start__[];
            ਬਾਹਰੀ uint32_t __syscalls_flash_end__[];

        #ਜੇ_ਅੰਤ /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ];
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
        ਜੇ( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ == ਨਿਰਾ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_ਸੰਖਿਆ ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ਢੇਰ = pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ;

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ਢੇਰ = pul_System_Call_ਢੇਰ - ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ;

            /* Copy the stack frame. */
            ਲਈ( i = 0; i < ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ; i++ )
            {
                pul_System_Call_ਢੇਰ[ i ] = pul_Task_ਢੇਰ[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ਢੇਰ_Info.ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ = pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR ];

            /* Use the pulSystemCallStack in thread mode. */
            __asm ਅਸਥਿਰ ( "msr psp, %0" : : "r" ( pul_System_Call_ਢੇਰ ) );

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ] = uxSystemCallImplementations[ uc_System_Call_ਸੰਖਿਆ ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ = pul_Task_ਢੇਰ + ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            ਜੇ( ( pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] & ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ ) == ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ )
            {
                pxMpuSettings->ulTaskFlags |= ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG;
            }
            ਨਹੀਂਤਾਂ
            {
                pxMpuSettings->ulTaskFlags &= ( ~ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] &= ( ~ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ );

            /* Raise the privilege for the duration of the system call. */
            __asm ਅਸਥਿਰ
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

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ਖਾਲੀ vRequestSystemCallExit( ਖਾਲੀ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm ਅਸਥਿਰ ( "svc %0 \n" ::"i" ( ਪੋਰਟ_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ਖਾਲੀ vSystemCallExit( uint32_t * pul_System_Call_ਢੇਰ,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        ਬਾਹਰੀ TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ਢੇਰ;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ਅਚਲ uint32_t ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ = 8;

        #ਜੇ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __privileged_functions_start__;
            ਬਾਹਰੀ uint32_t * __privileged_functions_end__;

        #ਨਹੀਂਤਾਂ

            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __privileged_functions_start__[];
            ਬਾਹਰੀ uint32_t __privileged_functions_end__[];

        #ਜੇ_ਅੰਤ /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ];
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
        ਜੇ( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ != ਨਿਰਾ ) )
        {
            pul_Task_ਢੇਰ = pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ;

            /* Make space on the task stack for the stack frame. */
            pul_Task_ਢੇਰ = pul_Task_ਢੇਰ - ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ;

            /* Copy the stack frame. */
            ਲਈ( i = 0; i < ul_Hardware_Saved_Exception_ਚੌਖਟਾ_ਮਾਪ; i++ )
            {
                pul_Task_ਢੇਰ[ i ] = pul_System_Call_ਢੇਰ[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm ਅਸਥਿਰ ( "msr psp, %0" : : "r" ( pul_Task_ਢੇਰ ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC ] = pxMpuSettings->x_System_Call_ਢੇਰ_Info.ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;

            /* Ensure that LR has a valid value.*/
            pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR ] = pxMpuSettings->x_System_Call_ਢੇਰ_Info.ul_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            ਜੇ( ( pxMpuSettings->ulTaskFlags & ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG ) == ਪੋਰਟ_ਢੇਰ_ਚੌਖਟਾ_HAS_PADDING_FLAG )
            {
                pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] |= ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ;
            }
            ਨਹੀਂਤਾਂ
            {
                pul_Task_ਢੇਰ[ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PSR ] &= ( ~ਪੋਰਟ_PSR_ਢੇਰ_PADDING_ਨਕਾਬ );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ = ਨਿਰਾ;

            /* Drop the privilege before returning to the thread mode. */
            __asm ਅਸਥਿਰ
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

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        ਅਧਾਰ_Type_t xTaskIsPrivileged = pdFALSE;
        ਅਚਲ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ ); /* Calling task's MPU settings. */

        ਜੇ( ( xTaskMpuSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        ਵਾਪਸ xTaskIsPrivileged;
    }

#ਜੇ_ਅੰਤ /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                         TaskFunction_t px_ਕੋਡ,
                                         ਖਾਲੀ * pvParameters,
                                         ਅਧਾਰ_Type_t x_ਲੜੀਵਾਰ_Privileged,
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
        xMPUSettings->ulContext[ 13 ] = ( uint32_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ; /* LR. */
        xMPUSettings->ulContext[ 14 ] = ( uint32_t ) px_ਕੋਡ;                  /* PC. */
        xMPUSettings->ulContext[ 15 ] = ਪੋਰਟ_INITIAL_XPSR;                     /* xPSR. */

        xMPUSettings->ulContext[ 16 ] = ( uint32_t ) ( px_ਸਿਖਰ_ਦਾ_ਢੇਰ - 8 ); /* PSP with the hardware saved stack. */
        ਜੇ( x_ਲੜੀਵਾਰ_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) ਪੋਰਟ_INITIAL_CONTROL_PRIVILEGED; /* CONTROL. */
        }
        ਨਹੀਂਤਾਂ
        {
            xMPUSettings->ulTaskFlags &= ( ~ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) ਪੋਰਟ_INITIAL_CONTROL_UNPRIVILEGED; /* CONTROL. */
        }
        xMPUSettings->ulContext[ 18 ] = ਪੋਰਟ_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */

        #ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ = &( xMPUSettings->x_System_Call_ਢੇਰ_Info.ul_System_Call_ਢੇਰ_ਬਫਰ[ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ - 1 ] );
            xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_System_Call_ਢੇਰ ) &
                                                                                     ( uint32_t ) ( ~( ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_ਢੇਰ_Info.pul_Task_ਢੇਰ = ਨਿਰਾ;
        }
        #ਜੇ_ਅੰਤ /* configUSE_MPU_WRAPPERS_V1 == 0 */

        ਵਾਪਸ &( xMPUSettings->ulContext[ 19 ] );
    }

#ਨਹੀਂਤਾਂ /* configENABLE_MPU */

    ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                         TaskFunction_t px_ਕੋਡ,
                                         ਖਾਲੀ * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #ਜੇ ( ਪੋਰਟ_PRELOAD_REGISTERS == 0 )
        {
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_XPSR;                        /* xPSR. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;                  /* PC. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ; /* LR. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 5;                                       /* R12, R3, R2 and R1. */
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;            /* R0. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= 9;                                       /* R11..R4, EXC_RETURN. */
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_EXC_RETURN;
        }
        #ਨਹੀਂਤਾਂ /* portPRELOAD_REGISTERS */
        {
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_XPSR;                        /* xPSR. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;                  /* PC. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ; /* LR. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x12121212UL;            /* R12. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x03030303UL;            /* R3. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x02020202UL;            /* R2. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x01010101UL;            /* R1. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;            /* R0. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x11111111UL;            /* R11. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x10101010UL;            /* R10. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x09090909UL;            /* R09. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x08080808UL;            /* R08. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x07070707UL;            /* R07. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x06060606UL;            /* R06. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x05050505UL;            /* R05. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x04040404UL;            /* R04. */
            px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
            *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_EXC_RETURN;                  /* EXC_RETURN. */
        }
        #ਜੇ_ਅੰਤ /* portPRELOAD_REGISTERS */

        ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
    }

#ਜੇ_ਅੰਤ /* configENABLE_MPU */

/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
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
    #ਜੇ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ਅਚਲ ਪੋਰਟ_ISR_t * ਅਚਲ px_ਸਦਿਸ਼_ਸਾਰਣੀ = ਪੋਰਟ_SCB_VTOR_REG;

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
        configASSERT( px_ਸਦਿਸ਼_ਸਾਰਣੀ[ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_SVC ] == SVC_Handler );
        configASSERT( px_ਸਦਿਸ਼_ਸਾਰਣੀ[ ਪੋਰਟ_ਸਦਿਸ਼_ਸੂਚਕਾਂਕ_PENDSV ] == PendSV_Handler );
    }
    #ਜੇ_ਅੰਤ /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
     * the highest priority. */
    ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_PENDSV_PRI;
    ਪੋਰਟ_NVIC_SHPR3_REG |= ਪੋਰਟ_NVIC_SYSTICK_PRI;
    ਪੋਰਟ_NVIC_SHPR2_REG = 0;

    #ਜੇ ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_ਤਿਆਰੀ_MPU();
    }
    #ਜੇ_ਅੰਤ /* configENABLE_MPU */

    /* Start the timer that generates the tick ISR. Interrupts are disabled
     * here already. */
    v_ਪੋਰਟ_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /* Initialize the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    #ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #ਜੇ_ਅੰਤ

    /* Start the first task. */
    v_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    vTaskSwitchContext();
    prvTaskExitError();

    /* Should not get here. */
    ਵਾਪਸ 0;
}

/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}

/*-----------------------------------------------------------*/

#ਜੇ ( configENABLE_MPU == 1 )

    ਖਾਲੀ v_ਪੋਰਟ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ਅਚਲ ਬਣਤਰ x_ਸਮ੍ਰਿਤੀ_REGION * ਅਚਲ xRegions,
                                    ਢੇਰ_Type_t * px_Bottom_ਦਾ_ਢੇਰ,
                                    config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ux_ਢੇਰ_ਡੂੰਘਾਈ )
    {
        #ਜੇ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ਬਾਹਰੀ uint32_t * __SRAM_segment_start__;
            ਬਾਹਰੀ uint32_t * __SRAM_segment_end__;
            ਬਾਹਰੀ uint32_t * __privileged_sram_start__;
            ਬਾਹਰੀ uint32_t * __privileged_sram_end__;

        #ਨਹੀਂਤਾਂ
            /* Declaration when these variable are exported from linker scripts. */
            ਬਾਹਰੀ uint32_t __SRAM_segment_start__[];
            ਬਾਹਰੀ uint32_t __SRAM_segment_end__[];
            ਬਾਹਰੀ uint32_t __privileged_sram_start__[];
            ਬਾਹਰੀ uint32_t __privileged_sram_end__[];

        #ਜੇ_ਅੰਤ /* defined( __ARMCC_VERSION ) */

        int32_t l_ਸੂਚਕਾਂਕ;
        uint32_t ul;

        ਜੇ( xRegions == ਨਿਰਾ )
        {
            /* No MPU regions are specified so allow access to all RAM. */
            xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                ( ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
                  ( ਪੋਰਟ_MPU_RBAR_REGION_ਸੰਖਿਆ_VALID_BITMASK ) |
                  ( ਪੋਰਟ_ਢੇਰ_REGION ) );                   /* Region number. */

            xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                ( ( ਪੋਰਟ_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                  ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER ) |
                  ( ( configS_C_B_SRAM & ਪੋਰਟ_MPU_RASR_S_C_B_BITMASK ) << ਪੋਰਟ_MPU_RASR_S_C_B_LOCATION ) |
                  ( prv_Get_MPURegion_ਮਾਪ_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
                  ( ਪੋਰਟ_MPU_RASR_REGION_ENABLE_BITMASK ) );


            /* Invalidate user configurable regions. */
            ਲਈ( ul = 1UL; ul <= ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS; ul++ )
            {
                xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | ਪੋਰਟ_MPU_RBAR_REGION_ਸੰਖਿਆ_VALID_BITMASK );
                xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
            }
        }
        ਨਹੀਂਤਾਂ
        {
            /* This function is called automatically when the task is created - in
             * which case the stack region parameters will be valid.  At all other
             * times the stack parameters will not be valid and it is assumed that the
             * stack region has already been configured. */
            ਜੇ( ux_ਢੇਰ_ਡੂੰਘਾਈ > 0 )
            {
                /* Define the region that allows access to the stack. */
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                    ( ( ( uint32_t ) px_Bottom_ਦਾ_ਢੇਰ ) |
                      ( ਪੋਰਟ_MPU_RBAR_REGION_ਸੰਖਿਆ_VALID_BITMASK ) |
                      ( ਪੋਰਟ_ਢੇਰ_REGION ) ); /* Region number. */

                xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                    ( ( ਪੋਰਟ_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                      ( ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER ) |
                      ( prv_Get_MPURegion_ਮਾਪ_Setting( ux_ਢੇਰ_ਡੂੰਘਾਈ * ( uint32_t ) ਆਕਾਰ( ਢੇਰ_Type_t ) ) ) |
                      ( ( configS_C_B_SRAM & ਪੋਰਟ_MPU_RASR_S_C_B_BITMASK ) << ਪੋਰਟ_MPU_RASR_S_C_B_LOCATION ) |
                      ( ਪੋਰਟ_MPU_RASR_REGION_ENABLE_BITMASK ) );
            }

            l_ਸੂਚਕਾਂਕ = 0;

            ਲਈ( ul = 1UL; ul <= ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS; ul++ )
            {
                ਜੇ( ( xRegions[ l_ਸੂਚਕਾਂਕ ] ).ul_ਲੰਮਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ > 0UL )
                {
                    /* Translate the generic region definition contained in
                     * xRegions into the CM0+ specific MPU settings that are then
                     * stored in xMPUSettings. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR =
                        ( ( uint32_t ) xRegions[ l_ਸੂਚਕਾਂਕ ].pv_ਅਧਾਰ_ਪਤਾ ) |
                        ( ਪੋਰਟ_MPU_RBAR_REGION_ਸੰਖਿਆ_VALID_BITMASK ) |
                        ( ul - 1UL ); /* Region number. */

                    xMPUSettings->xRegionsSettings[ ul ].ulRASR =
                        ( prv_Get_MPURegion_ਮਾਪ_Setting( xRegions[ l_ਸੂਚਕਾਂਕ ].ul_ਲੰਮਾਈ_ਵਿੱਚ_ਬਾਈਟਾਂ ) ) |
                        ( xRegions[ l_ਸੂਚਕਾਂਕ ].ulParameters ) |
                        ( ਪੋਰਟ_MPU_RASR_REGION_ENABLE_BITMASK );
                }
                ਨਹੀਂਤਾਂ
                {
                    /* Invalidate the region. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | ਪੋਰਟ_MPU_RBAR_REGION_ਸੰਖਿਆ_VALID_BITMASK );
                    xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
                }

            l_ਸੂਚਕਾਂਕ++;
        }
    }
}

#ਜੇ_ਅੰਤ /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( ਅਚਲ ਖਾਲੀ * pv_ਬਫਰ,
                                                size_t x_ਬਫਰ_ਲੰਮਾਈ,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ, ul_ਬਫਰ_ਸਿਰਾ_ਪਤਾ;
        uint32_t ul_Region_ਸ਼ੁਰੂ, ul_Region_ਮਾਪ, ul_Region_ਸਿਰਾ;
        uint32_t ulMPURegionAccessPermissions;
        ਅਧਾਰ_Type_t xAccessGranted = pdFALSE;
        ਅਚਲ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ ); /* Calling task's MPU settings. */

        ਜੇ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        ਨਹੀਂਤਾਂ ਜੇ( ( xTaskMpuSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ਨਹੀਂਤਾਂ
        {
            ਜੇ( ਪੋਰਟ_ਜੋੜੋ_UINT32_WILL_ਉਛਾਲ( ( ( uint32_t ) pv_ਬਫਰ ), ( ( uint32_t ) x_ਬਫਰ_ਲੰਮਾਈ - 1UL ) ) == pdFALSE )
            {
                ul_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ = ( uint32_t ) pv_ਬਫਰ;
                ul_ਬਫਰ_ਸਿਰਾ_ਪਤਾ = ( ( ( uint32_t ) pv_ਬਫਰ ) + ( uint32_t ) x_ਬਫਰ_ਲੰਮਾਈ - 1UL );

                ਲਈ( i = 0; i < ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    ਜੇ( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                          ਪੋਰਟ_MPU_RASR_REGION_ENABLE_BITMASK ) == ਪੋਰਟ_MPU_RASR_REGION_ENABLE_BITMASK )
                    {
                        ul_Region_ਸ਼ੁਰੂ = ਪੋਰਟ_ਕੱਢੋ_ਪਹਿਲਾ_ਪਤਾ_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR );
                        ul_Region_ਮਾਪ = ਪੋਰਟ_ਕੱਢੋ_REGION_ਮਾਪ_FROM_RASR( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR );
                        ul_Region_ਸਿਰਾ = ul_Region_ਸ਼ੁਰੂ + ul_Region_ਮਾਪ;

                        ਜੇ( ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ul_ਬਫਰ_ਸ਼ੁਰੂ_ਪਤਾ,
                                                         ul_Region_ਸ਼ੁਰੂ,
                                                         ul_Region_ਸਿਰਾ ) &&
                            ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( ul_ਬਫਰ_ਸਿਰਾ_ਪਤਾ,
                                                         ul_Region_ਸ਼ੁਰੂ,
                                                         ul_Region_ਸਿਰਾ ) )
                        {
                            ulMPURegionAccessPermissions = xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                                                           ਪੋਰਟ_MPU_RASR_AP_BITMASK;

                            ਜੇ( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
                            {
                                ਜੇ( ( ulMPURegionAccessPermissions == ਪੋਰਟ_MPU_REGION_PRIV_RW_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == ਪੋਰਟ_MPU_REGION_PRIV_RO_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == ਪੋਰਟ_MPU_REGION_PRIV_RW_UNPRIV_RW ) )
                                {
                                    xAccessGranted = pdTRUE;
                                    ਰੋਕੋ;
                                }
                            }
                            ਨਹੀਂਤਾਂ ਜੇ( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
                            {
                                ਜੇ( ulMPURegionAccessPermissions == ਪੋਰਟ_MPU_REGION_PRIV_RW_UNPRIV_RW )
                                {
                                    xAccessGranted = pdTRUE;
                                    ਰੋਕੋ;
                                }
                            }
                        }
                    }
                }
            }
        }

        ਵਾਪਸ xAccessGranted;
    }

#ਜੇ_ਅੰਤ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Inside_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    uint32_t ul_Current_ਰੁਕਾਵਟ;
    ਅਧਾਰ_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm ਅਸਥਿਰ ( "mrs %0, ipsr" : "=r" ( ul_Current_ਰੁਕਾਵਟ )::"memory" );

    ਜੇ( ul_Current_ਰੁਕਾਵਟ == 0 )
    {
        xReturn = pdFALSE;
    }
    ਨਹੀਂਤਾਂ
    {
        xReturn = pdTRUE;
    }

    ਵਾਪਸ xReturn;
}

/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ਖਾਲੀ v_ਪੋਰਟ_Grant_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle,
                                         int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
        ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ਅੰਦਰੂਨੀ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] |= ( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ );
    }

#ਜੇ_ਅੰਤ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ਖਾਲੀ v_ਪੋਰਟ_Revoke_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle,
                                          int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
        ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ਅੰਦਰੂਨੀ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] &= ~( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ );
    }

#ਜੇ_ਅੰਤ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ, ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ;
            ਅਧਾਰ_Type_t xAccessGranted = pdFALSE;
            ਅਚਲ xMPU_SETTINGS * xTaskMpuSettings;

            ਜੇ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            ਨਹੀਂਤਾਂ
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ਨਿਰਾ ); /* Calling task's MPU settings. */

                ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );
                ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ = ( ( uint32_t ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object % ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ );

                ਜੇ( ( xTaskMpuSettings->ulTaskFlags & ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG ) == ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                ਨਹੀਂਤਾਂ
                {
                    ਜੇ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ਇੰਦਰਾਜ_ਸੂਚਕਾਂਕ ] & ( 1U << ul_Access_Control_List_ਇੰਦਰਾਜ_ਦੋਆਧਾਰੀ_ਅੰਕ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            ਵਾਪਸ xAccessGranted;
        }

    #ਨਹੀਂਤਾਂ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( int32_t l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( ਖਾਲੀ ) l_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_ਦਾ_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            ਵਾਪਸ pdTRUE;
        }

    #ਜੇ_ਅੰਤ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#ਜੇ_ਅੰਤ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/
