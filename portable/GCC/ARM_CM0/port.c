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
#ವ್ಯಾಖ್ಯಾನಿಸು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

/* MPU includes. */
#ಅನ್ತರ್ಭಾವ "mpu_wrappers.h"
#ಅನ್ತರ್ಭಾವ "mpu_syscall_numbers.h"

/* Portasm includes. */
#ಅನ್ತರ್ಭಾವ "portasm.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*-----------------------------------------------------------*/

/**
 * @brief Prototype of all Interrupt Service Routines (ISRs).
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ ( * ಪೋರ್ಟ್_ISR_t )( ಶೂನ್ಯ );

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the NVIC.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG             ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e010 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG             ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e014 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000e018 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SHPR3_REG                    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed20 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SHPR2_REG                    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed1c ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್           ( 1UL << 0UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್              ( 1UL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್              ( 1UL << 2UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್       ( 1UL << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_CLEAR_ಬಿಟ್       ( 1UL << 25UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_ಗಣ_ಬಿಟ್         ( 1UL << 26UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ            ( 255UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSV_PRI                   ( ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ << 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_PRI                  ( ಪೋರ್ಟ್_MIN_ಅಡಚಣೆ_ಆದ್ಯತೆ << 24UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the SCB.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SCB_VTOR_REG                      ( *( ( ಪೋರ್ಟ್_ISR_t ** ) 0xe000ed08 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SCB_SYS_HANDLER_CTRL_STATE_REG    ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed24 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SCB_MEM_FAULT_ENABLE_ಬಿಟ್          ( 1UL << 16UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used to check the installation of the FreeRTOS interrupt handlers.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_SVC       ( 11 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_PENDSV    ( 14 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants used during system call enter and exit.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ              ( 1UL << 9UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXC_RETURN_ರಾಶಿ_ಚೌಕಟ್ಟು_TYPE_ಮುಖವಾಡ    ( 1UL << 4UL )

/*-----------------------------------------------------------*/

/**
 * @brief Offsets in the stack to the parameters when inside the SVC handler.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR     ( 5 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC     ( 6 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR    ( 7 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to manipulate the MPU.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_TYPE_REG                            ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed90 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_CTRL_REG                            ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed94 ) )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RBAR_REG                            ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed9c ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RASR_REG                            ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000eda0 ) )

/* MPU Region Attribute and Size Register (RASR) bitmasks. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RASR_AP_BITMASK                     ( 0x7UL << 24UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RASR_S_C_B_BITMASK                  ( 0x7UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RASR_S_C_B_LOCATION                 ( 16UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RASR_ಗಾತ್ರ_BITMASK                   ( 0x1FUL << 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RASR_REGION_ENABLE_BITMASK          ( 0x1UL )

/* MPU Region Base Address Register (RBAR) bitmasks. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RBAR_ವಿಳಾಸ_BITMASK                ( 0xFFFFFF00UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RBAR_REGION_ಸಂಖ್ಯೆ_VALID_BITMASK    ( 0x1UL << 4UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_RBAR_REGION_ಸಂಖ್ಯೆ_BITMASK          ( 0x0000000FUL )

/* MPU Control Register (MPU_CTRL) bitmasks. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_CTRL_ENABLE_BITMASK                 ( 0x1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK ( 0x1UL << 2UL ) /* PRIVDEFENA bit. */

/* Expected value of the portMPU_TYPE register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXPECTED_MPU_TYPE_ಮೌಲ್ಯ                 ( 0x8UL << 8UL ) /* 8 DREGION unified. */

/* Extract first address of the MPU region as encoded in the
 * RBAR (Region Base Address Register) value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಮೊದಲ_ವಿಳಾಸ_FROM_RBAR( rbar ) \
    ( ( rbar ) & ಪೋರ್ಟ್_MPU_RBAR_ವಿಳಾಸ_BITMASK )

/* Extract size of the MPU region as encoded in the
 * RASR (Region Attribute and Size Register) value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಹೊರತೆಗೆ_REGION_ಗಾತ್ರ_FROM_RASR( rasr ) \
    ( 1 << ( ( ( ( rasr ) & ಪೋರ್ಟ್_MPU_RASR_ಗಾತ್ರ_BITMASK ) >> 1 )+ 1 ) )

/* Does addr lies within [start, end] address range? */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( addr, ಆರಂಭ, ಕೊನೆ ) \
    ( ( ( addr ) >= ( ಆರಂಭ ) ) && ( ( addr ) <= ( ಕೊನೆ ) ) )

/* Is the access request satisfied by the available permissions? */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_AUTHORIZED( accessRequest, permissions ) \
    ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

/* Max value that fits in a uint32_t type. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UINT32_MAX    ( ~( ( uint32_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೂಡಿಸು_UINT32_WILL_ಅತಿಪ್ರವಾಹ( a, b )    ( ( a ) > ( ಪೋರ್ಟ್_UINT32_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/**
 * @brief The maximum 24-bit number.
 *
 * It is needed because the systick is a 24-bit counter.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_24_ಬಿಟ್_ಸಂಖ್ಯೆ       ( 0xffffffUL )

/**
 * @brief A fiddle factor to estimate the number of SysTick counts that would
 * have occurred while the SysTick counter is stopped during tickless idle
 * calculations.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MISSED_COUNTS_ಗುಣಕ    ( 94UL )

/*-----------------------------------------------------------*/

/**
 * @brief Constants required to set up the initial stack.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_XPSR    ( 0x01000000 )

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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_EXC_RETURN    ( 0xfffffffdUL )

/**
 * @brief CONTROL register privileged bit mask.
 *
 * Bit[0] in CONTROL register tells the privilege:
 *  Bit[0] = 0 ==> The task is privileged.
 *  Bit[0] = 1 ==> The task is not privileged.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONTROL_PRIVILEGED_ಮುಖವಾಡ         ( 1UL << 0UL )

/**
 * @brief Initial CONTROL register values.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_CONTROL_UNPRIVILEGED    ( 0x3 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_CONTROL_PRIVILEGED      ( 0x2 )

/**
 * @brief Let the user override the default SysTick clock rate.  If defined by the
 * user, this symbol must equal the SysTick clock rate when the CLK bit is 0 in the
 * configuration register.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configSYSTICK_CLOCK_HZ
    #ವ್ಯಾಖ್ಯಾನಿಸು configSYSTICK_CLOCK_HZ             ( configCPU_CLOCK_HZ )
    /* Ensure the SysTick is clocked at the same frequency as the core. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG    ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
#ಇಲ್ಲದಿದ್ದರೆ
    /* Select the option to clock SysTick not at the same frequency as the core. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG    ( 0 )
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief Let the user override the pre-loading of the initial LR with the
 * address of prvTaskExitError() in case it messes up unwinding of the stack
 * in the debugger.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_TASK_RETURN_ವಿಳಾಸ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    config_TASK_RETURN_ವಿಳಾಸ
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    prvTaskExitError
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief If portPRELOAD_REGISTERS then registers will be given an initial value
 * when a task is created. This helps in debugging at the cost of code size.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRELOAD_REGISTERS    1

/*-----------------------------------------------------------*/

/**
 * @brief Used to catch tasks that attempt to return from their implementing
 * function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

#ಆದರೆ ( configENABLE_MPU == 1 )

    /**
     * @brief Setup the Memory Protection Unit (MPU).
     */
    ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_MPU( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

/**
 * @brief Setup the timer to generate the tick interrupts.
 *
 * The implementation in this file is weak to allow application writers to
 * change the timer used to generate the tick interrupt.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief Checks whether the current execution context is interrupt.
 *
 * @return pdTRUE if the current execution context is interrupt, pdFALSE
 * otherwise.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Inside_ಅಡಚಣೆ( ಶೂನ್ಯ );

/**
 * @brief Yield the processor.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief Enter critical section.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief Exit from critical section.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief SysTick handler.
 */
ಶೂನ್ಯ SysTick_Handler( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief C part of SVC handler.
 */
ಪೋರ್ಟ್_DONT_DISCARD ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler_C( uint32_t * pul_Caller_ರಾಶಿ_ವಿಳಾಸ ) PRIVILEGED_FUNCTION;

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the system call stack so that upon returning from
     * SVC, the system call stack is used.
     *
     * @param pulTaskStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     * @param ucSystemCallNumber The system call number of the system call.
     */
    ಶೂನ್ಯ vSystemCallEnter( uint32_t * pul_Task_ರಾಶಿ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ಸಂಖ್ಯೆ ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Raise SVC for exiting from a system call.
     */
    ಶೂನ್ಯ vRequestSystemCallExit( ಶೂನ್ಯ ) __attribute__( ( naked ) ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief Sets up the task stack so that upon returning from
     * SVC, the task stack is used again.
     *
     * @param pulSystemCallStack The current SP when the SVC was raised.
     * @param ulLR The value of Link Register (EXC_RETURN) in the SVC handler.
     */
    ಶೂನ್ಯ vSystemCallExit( uint32_t * pul_System_Call_ರಾಶಿ,
                          uint32_t ulLR ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

#ಆದರೆ ( configENABLE_MPU == 1 )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    /**
     * @brief This variable is set to pdTRUE when the scheduler is started.
     */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ತಳ_Type_t xSchedulerRunning = pdFALSE;

#ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief Each task maintains its own interrupt status in the critical nesting
 * variable.
 */
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ಅಸ್ಥಿರ uint32_t ulCriticalNesting = 0xaaaaaaaaUL;

#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )

    /**
     * @brief The number of SysTick increments that make up one tick period.
     */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ uint32_t ulTimerCountsForOneTick = 0;

    /**
     * @brief The maximum number of tick periods that can be suppressed is
     * limited by the 24 bit resolution of the SysTick timer.
     */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ uint32_t x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks = 0;

    /**
     * @brief Compensate for the CPU cycles that pass while the SysTick is
     * stopped (low power functionality only).
     */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ uint32_t ulStoppedTimerCompensation = 0;

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )

    __attribute__( ( weak ) ) ಶೂನ್ಯ v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ಸಮಯ )
    {
        uint32_t ul_Reload_ಮೌಲ್ಯ, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ul_Sys_Tick_Decrements_ಎಡ;
        TickType_t x_Modifiable_Idle_ಸಮಯ;

        /* Make sure the SysTick reload value does not overflow the counter. */
        ಆದರೆ( x_Expected_Idle_ಸಮಯ > x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks )
        {
            x_Expected_Idle_ಸಮಯ = x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks;
        }

        /* Enter a critical section but don't use the taskENTER_CRITICAL()
         * method as that will mask interrupts that should exit sleep mode. */
        __asm ಅಸ್ಥಿರ ( "cpsid i" ::: "memory" );
        __asm ಅಸ್ಥಿರ ( "dsb" );
        __asm ಅಸ್ಥಿರ ( "isb" );

        /* If a context switch is pending or a task is waiting for the scheduler
         * to be unsuspended then abandon the low power entry. */
        ಆದರೆ( e_Task_Confirm_Sleep_ಬಹುಲಕ_ಸ್ಥಿತಿ() == eAbortSleep )
        {
            /* Re-enable interrupts - see comments above the cpsid instruction
             * above. */
            __asm ಅಸ್ಥಿರ ( "cpsie i" ::: "memory" );
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* Stop the SysTick momentarily.  The time the SysTick is stopped for
             * is accounted for as best it can be, but using the tickless mode will
             * inevitably result in some tiny drift of the time maintained by the
             * kernel with respect to calendar time. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ );

            /* Use the SysTick current-value register to determine the number of
             * SysTick decrements remaining until the next tick interrupt.  If the
             * current-value register is zero, then there are actually
             * ulTimerCountsForOneTick decrements remaining, not zero, because the
             * SysTick requests the interrupt when decrementing from 1 to 0. */
            ul_Sys_Tick_Decrements_ಎಡ = ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG;

            ಆದರೆ( ul_Sys_Tick_Decrements_ಎಡ == 0 )
            {
                ul_Sys_Tick_Decrements_ಎಡ = ulTimerCountsForOneTick;
            }

            /* Calculate the reload value required to wait xExpectedIdleTime
             * tick periods.  -1 is used because this code normally executes part
             * way through the first tick period.  But if the SysTick IRQ is now
             * pending, then clear the IRQ, suppressing the first tick, and correct
             * the reload value to reflect that the second tick period is already
             * underway.  The expected idle time is always at least two ticks. */
            ul_Reload_ಮೌಲ್ಯ = ul_Sys_Tick_Decrements_ಎಡ + ( ulTimerCountsForOneTick * ( x_Expected_Idle_ಸಮಯ - 1UL ) );

            ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_INT_CTRL_REG & ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_ಗಣ_ಬಿಟ್ ) != 0 )
            {
                ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PEND_SYSTICK_CLEAR_ಬಿಟ್;
                ul_Reload_ಮೌಲ್ಯ -= ulTimerCountsForOneTick;
            }

            ಆದರೆ( ul_Reload_ಮೌಲ್ಯ > ulStoppedTimerCompensation )
            {
                ul_Reload_ಮೌಲ್ಯ -= ulStoppedTimerCompensation;
            }

            /* Set the new reload value. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ul_Reload_ಮೌಲ್ಯ;

            /* Clear the SysTick count flag and set the count value back to
             * zero. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;

            /* Restart SysTick. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;

            /* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
             * set its parameter to 0 to indicate that its implementation contains
             * its own wait for interrupt or wait for event instruction, and so wfi
             * should not be executed again.  However, the original expected idle
             * time variable must remain unmodified, so a copy is taken. */
            x_Modifiable_Idle_ಸಮಯ = x_Expected_Idle_ಸಮಯ;
            configPRE_SLEEP_PROCESSING( x_Modifiable_Idle_ಸಮಯ );

            ಆದರೆ( x_Modifiable_Idle_ಸಮಯ > 0 )
            {
                __asm ಅಸ್ಥಿರ ( "dsb" ::: "memory" );
                __asm ಅಸ್ಥಿರ ( "wfi" );
                __asm ಅಸ್ಥಿರ ( "isb" );
            }

            configPOST_SLEEP_PROCESSING( x_Expected_Idle_ಸಮಯ );

            /* Re-enable interrupts to allow the interrupt that brought the MCU
             * out of sleep mode to execute immediately.  See comments above
             * the cpsid instruction above. */
            __asm ಅಸ್ಥಿರ ( "cpsie i" ::: "memory" );
            __asm ಅಸ್ಥಿರ ( "dsb" );
            __asm ಅಸ್ಥಿರ ( "isb" );

            /* Disable interrupts again because the clock is about to be stopped
             * and interrupts that execute while the clock is stopped will increase
             * any slippage between the time maintained by the RTOS and calendar
             * time. */
            __asm ಅಸ್ಥಿರ ( "cpsid i" ::: "memory" );
            __asm ಅಸ್ಥಿರ ( "dsb" );
            __asm ಅಸ್ಥಿರ ( "isb" );

            /* Disable the SysTick clock without reading the
             * portNVIC_SYSTICK_CTRL_REG register to ensure the
             * portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
             * the time the SysTick is stopped for is accounted for as best it can
             * be, but using the tickless mode will inevitably result in some tiny
             * drift of the time maintained by the kernel with respect to calendar
             * time*/
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ );

            /* Determine whether the SysTick has already counted to zero. */
            ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG & ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್ ) != 0 )
            {
                uint32_t ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ;

                /* The tick interrupt ended the sleep (or is now pending), and
                 * a new tick period has started.  Reset portNVIC_SYSTICK_LOAD_REG
                 * with whatever remains of the new tick period. */
                ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ = ( ulTimerCountsForOneTick - 1UL ) - ( ul_Reload_ಮೌಲ್ಯ - ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG );

                /* Don't allow a tiny value, or values that have somehow
                 * underflowed because the post sleep hook did something
                 * that took too long or because the SysTick current-value register
                 * is zero. */
                ಆದರೆ( ( ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ <= ulStoppedTimerCompensation ) || ( ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ > ulTimerCountsForOneTick ) )
                {
                    ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ = ( ulTimerCountsForOneTick - 1UL );
                }

                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ul_Calculated_ತುಂಬು_ಮೌಲ್ಯ;

                /* As the pending tick will be processed as soon as this
                 * function exits, the tick value maintained by the tick is stepped
                 * forward by one less than the time spent waiting. */
                ulCompleteTickPeriods = x_Expected_Idle_ಸಮಯ - 1UL;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* Something other than the tick interrupt ended the sleep. */

                /* Use the SysTick current-value register to determine the
                 * number of SysTick decrements remaining until the expected idle
                 * time would have ended. */
                ul_Sys_Tick_Decrements_ಎಡ = ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG;
                #ಆದರೆ ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG != ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
                {
                    /* If the SysTick is not using the core clock, the current-
                     * value register might still be zero here.  In that case, the
                     * SysTick didn't load from the reload register, and there are
                     * ulReloadValue decrements remaining in the expected idle
                     * time, not zero. */
                    ಆದರೆ( ul_Sys_Tick_Decrements_ಎಡ == 0 )
                    {
                        ul_Sys_Tick_Decrements_ಎಡ = ul_Reload_ಮೌಲ್ಯ;
                    }
                }
                #ಆದರೆ_ಅಂತ್ಯ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

                /* Work out how long the sleep lasted rounded to complete tick
                 * periods (not the ulReload value which accounted for part
                 * ticks). */
                ulCompletedSysTickDecrements = ( x_Expected_Idle_ಸಮಯ * ulTimerCountsForOneTick ) - ul_Sys_Tick_Decrements_ಎಡ;

                /* How many complete tick periods passed while the processor
                 * was waiting? */
                ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

                /* The reload value is set to whatever fraction of a single tick
                 * period remains. */
                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
            }

            /* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG again,
             * then set portNVIC_SYSTICK_LOAD_REG back to its standard value.  If
             * the SysTick is not using the core clock, temporarily configure it to
             * use the core clock.  This configuration forces the SysTick to load
             * from portNVIC_SYSTICK_LOAD_REG immediately instead of at the next
             * cycle of the other clock.  Then portNVIC_SYSTICK_LOAD_REG is ready
             * to receive the standard value immediately. */
            ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;
            ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
            #ಆದರೆ ( ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG == ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ )
            {
                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ulTimerCountsForOneTick - 1UL;
            }
            #ಇಲ್ಲದಿದ್ದರೆ
            {
                /* The temporary usage of the core clock has served its purpose,
                 * as described above.  Resume usage of the other clock. */
                ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್;

                ಆದರೆ( ( ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG & ಪೋರ್ಟ್_NVIC_SYSTICK_ಎಣಿಕೆ_FLAG_ಬಿಟ್ ) != 0 )
                {
                    /* The partial tick period already ended.  Be sure the SysTick
                     * counts it only once. */
                    ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0;
                }

                ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ulTimerCountsForOneTick - 1UL;
                ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
            }
            #ಆದರೆ_ಅಂತ್ಯ /* portNVIC_SYSTICK_CLK_BIT_CONFIG */

            /* Step the tick to account for any tick periods that elapsed. */
            v_Task_ಹೆಜ್ಜೆ_Tick( ulCompleteTickPeriods );

            /* Exit with interrupts enabled. */
            __asm ಅಸ್ಥಿರ ( "cpsie i" ::: "memory" );
        }
    }

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

/*-----------------------------------------------------------*/

__attribute__( ( weak ) ) ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    /* Calculate the constants required to configure the tick interrupt. */
    #ಆದರೆ ( configUSE_TICKLESS_IDLE == 1 )
    {
        ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / config_TICK_ದರ_HZ );
        x_ಗರಿಷ್ಠ_Possible_Suppressed_Ticks = ಪೋರ್ಟ್_MAX_24_ಬಿಟ್_ಸಂಖ್ಯೆ / ulTimerCountsForOneTick;
        ulStoppedTimerCompensation = ಪೋರ್ಟ್_MISSED_COUNTS_ಗುಣಕ / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configUSE_TICKLESS_IDLE */

    /* Stop and reset SysTick.
     *
     * QEMU versions older than 7.0.0 contain a bug which causes an error if we
     * enable SysTick without first selecting a valid clock source. We trigger
     * the bug if we change clock sources from a clock with a zero clock period
     * to one with a nonzero clock period and enable Systick at the same time.
     * So we configure the CLKSOURCE bit here, prior to setting the ENABLE bit.
     * This workaround avoids the bug in QEMU versions older than 7.0.0. */
    ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG;
    ಪೋರ್ಟ್_NVIC_SYSTICK_CURRENT_ಮೌಲ್ಯ_REG = 0UL;

    /* Configure SysTick to interrupt at the requested rate. */
    ಪೋರ್ಟ್_NVIC_SYSTICK_ತುಂಬು_REG = ( configSYSTICK_CLOCK_HZ / config_TICK_ದರ_HZ ) - 1UL;
    ಪೋರ್ಟ್_NVIC_SYSTICK_CTRL_REG = ಪೋರ್ಟ್_NVIC_SYSTICK_CLK_ಬಿಟ್_CONFIG | ಪೋರ್ಟ್_NVIC_SYSTICK_INT_ಬಿಟ್ | ಪೋರ್ಟ್_NVIC_SYSTICK_ENABLE_ಬಿಟ್;
}

/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    ಅಸ್ಥಿರ uint32_t ulDummy = 0UL;

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, then stop here so
     * application writers can catch the error. */
    configASSERT( ulCriticalNesting == ~0UL );
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    ಆಗ( ulDummy == 0 )
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

#ಆದರೆ ( configENABLE_MPU == 1 )

    ಸ್ಥಿರ uint32_t prv_Get_MPURegion_ಗಾತ್ರ_Setting( uint32_t ul_Actual_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು )
    {
        uint32_t ul_Region_ಗಾತ್ರ, ul_Return_ಮೌಲ್ಯ = 7UL;

        /* 256 is the smallest region size, 31 is the largest valid value for
         * ulReturnValue. */
        ಗಾಗಿ( ul_Region_ಗಾತ್ರ = 256UL; ul_Return_ಮೌಲ್ಯ < 31UL; ( ul_Region_ಗಾತ್ರ <<= 1UL ) )
        {
            ಆದರೆ( ul_Actual_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು <= ul_Region_ಗಾತ್ರ )
            {
                ನಿಲ್ಲಿಸು;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                ul_Return_ಮೌಲ್ಯ++;
            }
        }

        /* Shift the code by one before returning so it can be written directly
         * into the correct bit position of the attribute register. */
        ಹಿಂತಿರುಗಿ( ul_Return_ಮೌಲ್ಯ << 1UL );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_MPU( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        #ಆದರೆ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
            * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __privileged_functions_start__;
            ಬಾಹ್ಯ uint32_t * __privileged_functions_end__;
            ಬಾಹ್ಯ uint32_t * __FLASH_segment_start__;
            ಬಾಹ್ಯ uint32_t * __FLASH_segment_end__;
            ಬಾಹ್ಯ uint32_t * __privileged_sram_start__;
            ಬಾಹ್ಯ uint32_t * __privileged_sram_end__;

        #ಇಲ್ಲದಿದ್ದರೆ /* if defined( __ARMCC_VERSION ) */

            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __privileged_functions_start__[];
            ಬಾಹ್ಯ uint32_t __privileged_functions_end__[];
            ಬಾಹ್ಯ uint32_t __FLASH_segment_start__[];
            ಬಾಹ್ಯ uint32_t __FLASH_segment_end__[];
            ಬಾಹ್ಯ uint32_t __privileged_sram_start__[];
            ಬಾಹ್ಯ uint32_t __privileged_sram_end__[];

        #ಆದರೆ_ಅಂತ್ಯ /* defined( __ARMCC_VERSION ) */

        /* Ensure that the MPU is present. */
        configASSERT( ಪೋರ್ಟ್_MPU_TYPE_REG == ಪೋರ್ಟ್_EXPECTED_MPU_TYPE_ಮೌಲ್ಯ );

        /* Check that the MPU is present. */
        ಆದರೆ( ಪೋರ್ಟ್_MPU_TYPE_REG == ಪೋರ್ಟ್_EXPECTED_MPU_TYPE_ಮೌಲ್ಯ )
        {
            /* Setup privileged flash as Read Only so that privileged tasks can
             * read it but not modify. */
            ಪೋರ್ಟ್_MPU_RBAR_REG = ( ( ( uint32_t ) __privileged_functions_start__ ) | /* Base address. */
                                 ( ಪೋರ್ಟ್_MPU_RBAR_REGION_ಸಂಖ್ಯೆ_VALID_BITMASK ) |
                                 ( ಪೋರ್ಟ್_PRIVILEGED_FLASH_REGION ) );

            ಪೋರ್ಟ್_MPU_RASR_REG = ( ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_UNPRIV_NA ) |
                                 ( ( configS_C_B_FLASH & ಪೋರ್ಟ್_MPU_RASR_S_C_B_BITMASK ) << ಪೋರ್ಟ್_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_ಗಾತ್ರ_Setting( ( uint32_t ) __privileged_functions_end__ - ( uint32_t ) __privileged_functions_start__ ) ) |
                                 ( ಪೋರ್ಟ್_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup unprivileged flash as Read Only by both privileged and
             * unprivileged tasks. All tasks can read it but no-one can modify. */
            ಪೋರ್ಟ್_MPU_RBAR_REG = ( ( ( uint32_t ) __FLASH_segment_start__ ) | /* Base address. */
                                 ( ಪೋರ್ಟ್_MPU_RBAR_REGION_ಸಂಖ್ಯೆ_VALID_BITMASK ) |
                                 ( ಪೋರ್ಟ್_UNPRIVILEGED_FLASH_REGION ) );

            ಪೋರ್ಟ್_MPU_RASR_REG = ( ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_UNPRIV_RO ) |
                                 ( ( configS_C_B_FLASH & ಪೋರ್ಟ್_MPU_RASR_S_C_B_BITMASK ) << ಪೋರ್ಟ್_MPU_RASR_S_C_B_LOCATION ) |
                                 ( prv_Get_MPURegion_ಗಾತ್ರ_Setting( ( uint32_t ) __FLASH_segment_end__ - ( uint32_t ) __FLASH_segment_start__ ) ) |
                                 ( ಪೋರ್ಟ್_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Setup RAM containing kernel data for privileged access only. */
            ಪೋರ್ಟ್_MPU_RBAR_REG = ( ( uint32_t ) __privileged_sram_start__ ) | /* Base address. */
                                 ( ಪೋರ್ಟ್_MPU_RBAR_REGION_ಸಂಖ್ಯೆ_VALID_BITMASK ) |
                                 ( ಪೋರ್ಟ್_PRIVILEGED_RAM_REGION );

            ಪೋರ್ಟ್_MPU_RASR_REG = ( ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_UNPRIV_NA ) |
                                 ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER ) |
                                 ( ( configS_C_B_SRAM & ಪೋರ್ಟ್_MPU_RASR_S_C_B_BITMASK ) << ಪೋರ್ಟ್_MPU_RASR_S_C_B_LOCATION ) |
                                 prv_Get_MPURegion_ಗಾತ್ರ_Setting( ( uint32_t ) __privileged_sram_end__ - ( uint32_t ) __privileged_sram_start__ ) |
                                 ( ಪೋರ್ಟ್_MPU_RASR_REGION_ENABLE_BITMASK ) );

            /* Enable MPU with privileged background access i.e. unmapped
             * regions have privileged access. */
            ಪೋರ್ಟ್_MPU_CTRL_REG |= ( ಪೋರ್ಟ್_MPU_CTRL_PRIV_BACKGROUND_ENABLE_BITMASK |
                                  ಪೋರ್ಟ್_MPU_CTRL_ENABLE_BITMASK );
        }
    }

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    /* Set a PendSV to request a context switch. */
    ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm ಅಸ್ಥಿರ ( "dsb" ::: "memory" );
    __asm ಅಸ್ಥಿರ ( "isb" );
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
    ulCriticalNesting++;

    /* Barriers are normally not required but do ensure the code is
     * completely within the specified behaviour for the architecture. */
    __asm ಅಸ್ಥಿರ ( "dsb" ::: "memory" );
    __asm ಅಸ್ಥಿರ ( "isb" );
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    configASSERT( ulCriticalNesting );
    ulCriticalNesting--;

    ಆದರೆ( ulCriticalNesting == 0 )
    {
        ಪೋರ್ಟ್_ENABLE_INTERRUPTS();
    }
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ SysTick_Handler( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    uint32_t ul_ಹಿಂದಿನ_ಮುಖವಾಡ;

    ul_ಹಿಂದಿನ_ಮುಖವಾಡ = ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR();

    traceISR_ENTER();
    {
        /* Increment the RTOS tick. */
        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();
            /* Pend a context switch. */
            ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            traceISR_EXIT();
        }
    }

    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ul_ಹಿಂದಿನ_ಮುಖವಾಡ );
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_SVCHandler_C( uint32_t * pul_Caller_ರಾಶಿ_ವಿಳಾಸ ) /* PRIVILEGED_FUNCTION portDONT_DISCARD */
{
    #ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        #ಆದರೆ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_start__;
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_end__;

        #ಇಲ್ಲದಿದ್ದರೆ

            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __syscalls_flash_start__[];
            ಬಾಹ್ಯ uint32_t __syscalls_flash_end__[];

        #ಆದರೆ_ಅಂತ್ಯ /* defined( __ARMCC_VERSION ) */

    #ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    uint32_t ulPC;
    uint8_t ucSVCNumber;

    /* Register are stored on the stack in the following order - R0, R1, R2, R3,
     * R12, LR, PC, xPSR. */
    ulPC = pul_Caller_ರಾಶಿ_ವಿಳಾಸ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ];
    ucSVCNumber = ( ( uint8_t * ) ulPC )[ -2 ];

    ಆಯ್ಕೆ( ucSVCNumber )
    {
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_ಆರಂಭ_SCHEDULER:
            /* Setup the context of the first task so that the first task starts
             * executing. */
            v_Restore_Context_ದ_ಮೊದಲ_Task();
            ನಿಲ್ಲಿಸು;

    #ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

        ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_RAISE_PRIVILEGE:
            /* Only raise the privilege, if the svc was raised from any of
             * the system calls. */
            ಆದರೆ( ( ulPC >= ( uint32_t ) __syscalls_flash_start__ ) &&
                ( ulPC <= ( uint32_t ) __syscalls_flash_end__ ) )
            {
                vRaisePrivilege();
            }
            ನಿಲ್ಲಿಸು;

    #ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) */

    #ಆದರೆ ( configENABLE_MPU == 1 )

        ಸ್ಥಿತಿ ಪೋರ್ಟ್_SVC_YIELD:
            v_ಪೋರ್ಟ್_Yield();
            ನಿಲ್ಲಿಸು;

    #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU == 1 */

        ಪೂರ್ವನಿಯೋಜಿತ:
            /* Incorrect SVC call. */
            configASSERT( pdFALSE );
    }
}

/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ಶೂನ್ಯ vSystemCallEnter( uint32_t * pul_Task_ರಾಶಿ,
                           uint32_t ulLR,
                           uint8_t uc_System_Call_ಸಂಖ್ಯೆ ) /* PRIVILEGED_FUNCTION */
    {
        ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
        ಬಾಹ್ಯ UBaseType_t uxSystemCallImplementations[ ಅಂಕೆ_SYSTEM_CALLS ];
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_System_Call_ರಾಶಿ;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ಸ್ಥಿರಾಂಕ uint32_t ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 8;

        #ಆದರೆ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_start__;
            ಬಾಹ್ಯ uint32_t * __syscalls_flash_end__;

        #ಇಲ್ಲದಿದ್ದರೆ

            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __syscalls_flash_start__[];
            ಬಾಹ್ಯ uint32_t __syscalls_flash_end__[];

        #ಆದರೆ_ಅಂತ್ಯ /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ];
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
        ಆದರೆ( ( ulSystemCallLocation >= ( uint32_t ) __syscalls_flash_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __syscalls_flash_end__ ) &&
            ( pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ == ಖಾಲಿ ) &&
            ( uxSystemCallImplementations[ uc_System_Call_ಸಂಖ್ಯೆ ] != ( UBaseType_t ) 0 ) )
        {
            pul_System_Call_ರಾಶಿ = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ;

            /* Make space on the system call stack for the stack frame. */
            pul_System_Call_ರಾಶಿ = pul_System_Call_ರಾಶಿ - ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ;

            /* Copy the stack frame. */
            ಗಾಗಿ( i = 0; i < ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ; i++ )
            {
                pul_System_Call_ರಾಶಿ[ i ] = pul_Task_ರಾಶಿ[ i ];
            }

            /* Store the value of the Link Register before the SVC was raised.
             * It contains the address of the caller of the System Call entry
             * point (i.e. the caller of the MPU_<API>). We need to restore it
             * when we exit from the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು = pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR ];

            /* Use the pulSystemCallStack in thread mode. */
            __asm ಅಸ್ಥಿರ ( "msr psp, %0" : : "r" ( pul_System_Call_ರಾಶಿ ) );

            /* Start executing the system call upon returning from this handler. */
            pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ] = uxSystemCallImplementations[ uc_System_Call_ಸಂಖ್ಯೆ ];

            /* Raise a request to exit from the system call upon finishing the
             * system call. */
            pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR ] = ( uint32_t ) vRequestSystemCallExit;

            /* Remember the location where we should copy the stack frame when we exit from
             * the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = pul_Task_ರಾಶಿ + ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ;

            /* Record if the hardware used padding to force the stack pointer
             * to be double word aligned. */
            ಆದರೆ( ( pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] & ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ ) == ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ )
            {
                pxMpuSettings->ulTaskFlags |= ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                pxMpuSettings->ulTaskFlags &= ( ~ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG );
            }

            /* We ensure in pxPortInitialiseStack that the system call stack is
             * double word aligned and therefore, there is no need of padding.
             * Clear the bit[9] of stacked xPSR. */
            pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] &= ( ~ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ );

            /* Raise the privilege for the duration of the system call. */
            __asm ಅಸ್ಥಿರ
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

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ಶೂನ್ಯ vRequestSystemCallExit( ಶೂನ್ಯ ) /* __attribute__( ( naked ) ) PRIVILEGED_FUNCTION */
    {
        __asm ಅಸ್ಥಿರ ( "svc %0 \n" ::"i" ( ಪೋರ್ಟ್_SVC_SYSTEM_CALL_EXIT ) : "memory" );
    }

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ಶೂನ್ಯ vSystemCallExit( uint32_t * pul_System_Call_ರಾಶಿ,
                          uint32_t ulLR ) /* PRIVILEGED_FUNCTION */
    {
        ಬಾಹ್ಯ TaskHandle_t pxCurrentTCB;
        xMPU_SETTINGS * pxMpuSettings;
        uint32_t * pul_Task_ರಾಶಿ;
        uint32_t ulSystemCallLocation, i;
        /* Hardware Saved Stack Frame Size upon Exception entry:
         * Basic frame (R0-R3, R12, LR, PC, and xPSR) = 8 words.
         */
        ಸ್ಥಿರಾಂಕ uint32_t ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ = 8;

        #ಆದರೆ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __privileged_functions_start__;
            ಬಾಹ್ಯ uint32_t * __privileged_functions_end__;

        #ಇಲ್ಲದಿದ್ದರೆ

            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __privileged_functions_start__[];
            ಬಾಹ್ಯ uint32_t __privileged_functions_end__[];

        #ಆದರೆ_ಅಂತ್ಯ /* #if defined( __ARMCC_VERSION ) */

        ulSystemCallLocation = pul_System_Call_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ];
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
        ಆದರೆ( ( ulSystemCallLocation >= ( uint32_t ) __privileged_functions_start__ ) &&
            ( ulSystemCallLocation <= ( uint32_t ) __privileged_functions_end__ ) &&
            ( pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ != ಖಾಲಿ ) )
        {
            pul_Task_ರಾಶಿ = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ;

            /* Make space on the task stack for the stack frame. */
            pul_Task_ರಾಶಿ = pul_Task_ರಾಶಿ - ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ;

            /* Copy the stack frame. */
            ಗಾಗಿ( i = 0; i < ul_Hardware_Saved_Exception_ಚೌಕಟ್ಟು_ಗಾತ್ರ; i++ )
            {
                pul_Task_ರಾಶಿ[ i ] = pul_System_Call_ರಾಶಿ[ i ];
            }

            /* Use the pulTaskStack in thread mode. */
            __asm ಅಸ್ಥಿರ ( "msr psp, %0" : : "r" ( pul_Task_ರಾಶಿ ) );

            /* Return to the caller of the System Call entry point (i.e. the
             * caller of the MPU_<API>). */
            pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC ] = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು;

            /* Ensure that LR has a valid value.*/
            pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR ] = pxMpuSettings->x_System_Call_ರಾಶಿ_Info.ul_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು;

            /* If the hardware used padding to force the stack pointer
             * to be double word aligned, set the stacked xPSR bit[9],
             * otherwise clear it. */
            ಆದರೆ( ( pxMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG ) == ಪೋರ್ಟ್_ರಾಶಿ_ಚೌಕಟ್ಟು_HAS_PADDING_FLAG )
            {
                pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] |= ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                pul_Task_ರಾಶಿ[ ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PSR ] &= ( ~ಪೋರ್ಟ್_PSR_ರಾಶಿ_PADDING_ಮುಖವಾಡ );
            }

            /* This is not NULL only for the duration of the system call. */
            pxMpuSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = ಖಾಲಿ;

            /* Drop the privilege before returning to the thread mode. */
            __asm ಅಸ್ಥಿರ
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

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */

/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        ತಳ_Type_t xTaskIsPrivileged = pdFALSE;
        ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ ); /* Calling task's MPU settings. */

        ಆದರೆ( ( xTaskMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
        {
            xTaskIsPrivileged = pdTRUE;
        }

        ಹಿಂತಿರುಗಿ xTaskIsPrivileged;
    }

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU == 1 */

/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                         TaskFunction_t px_ಸಂಕೇತ,
                                         ಶೂನ್ಯ * pvParameters,
                                         ತಳ_Type_t x_ಸತತ_Privileged,
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
        xMPUSettings->ulContext[ 13 ] = ( uint32_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ; /* LR. */
        xMPUSettings->ulContext[ 14 ] = ( uint32_t ) px_ಸಂಕೇತ;                  /* PC. */
        xMPUSettings->ulContext[ 15 ] = ಪೋರ್ಟ್_INITIAL_XPSR;                     /* xPSR. */

        xMPUSettings->ulContext[ 16 ] = ( uint32_t ) ( px_ತುದಿ_ದ_ರಾಶಿ - 8 ); /* PSP with the hardware saved stack. */
        ಆದರೆ( x_ಸತತ_Privileged == pdTRUE )
        {
            xMPUSettings->ulTaskFlags |= ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG;
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) ಪೋರ್ಟ್_INITIAL_CONTROL_PRIVILEGED; /* CONTROL. */
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xMPUSettings->ulTaskFlags &= ( ~ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG );
            xMPUSettings->ulContext[ 17 ] = ( uint32_t ) ಪೋರ್ಟ್_INITIAL_CONTROL_UNPRIVILEGED; /* CONTROL. */
        }
        xMPUSettings->ulContext[ 18 ] = ಪೋರ್ಟ್_INITIAL_EXC_RETURN; /* LR (EXC_RETURN). */

        #ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )
        {
            /* Ensure that the system call stack is double word aligned. */
            xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ = &( xMPUSettings->x_System_Call_ರಾಶಿ_Info.ul_System_Call_ರಾಶಿ_ಬಫರ್[ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ - 1 ] );
            xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ = ( uint32_t * ) ( ( uint32_t ) ( xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_System_Call_ರಾಶಿ ) &
                                                                                     ( uint32_t ) ( ~( ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) ) );

            /* This is not NULL only for the duration of a system call. */
            xMPUSettings->x_System_Call_ರಾಶಿ_Info.pul_Task_ರಾಶಿ = ಖಾಲಿ;
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configUSE_MPU_WRAPPERS_V1 == 0 */

        ಹಿಂತಿರುಗಿ &( xMPUSettings->ulContext[ 19 ] );
    }

#ಇಲ್ಲದಿದ್ದರೆ /* configENABLE_MPU */

    ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                         TaskFunction_t px_ಸಂಕೇತ,
                                         ಶೂನ್ಯ * pvParameters ) /* PRIVILEGED_FUNCTION */
    {
        /* Simulate the stack frame as it would be created by a context switch
         * interrupt. */
        #ಆದರೆ ( ಪೋರ್ಟ್_PRELOAD_REGISTERS == 0 )
        {
            px_ತುದಿ_ದ_ರಾಶಿ--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_XPSR;                        /* xPSR. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;                  /* PC. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ; /* LR. */
            px_ತುದಿ_ದ_ರಾಶಿ -= 5;                                       /* R12, R3, R2 and R1. */
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;            /* R0. */
            px_ತುದಿ_ದ_ರಾಶಿ -= 9;                                       /* R11..R4, EXC_RETURN. */
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_EXC_RETURN;
        }
        #ಇಲ್ಲದಿದ್ದರೆ /* portPRELOAD_REGISTERS */
        {
            px_ತುದಿ_ದ_ರಾಶಿ--;                                          /* Offset added to account for the way the MCU uses the stack on entry/exit of interrupts. */
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_XPSR;                        /* xPSR. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;                  /* PC. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ; /* LR. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x12121212UL;            /* R12. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x03030303UL;            /* R3. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x02020202UL;            /* R2. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x01010101UL;            /* R1. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;            /* R0. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11111111UL;            /* R11. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x10101010UL;            /* R10. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x09090909UL;            /* R09. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x08080808UL;            /* R08. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x07070707UL;            /* R07. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x06060606UL;            /* R06. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x05050505UL;            /* R05. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x04040404UL;            /* R04. */
            px_ತುದಿ_ದ_ರಾಶಿ--;
            *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_EXC_RETURN;                  /* EXC_RETURN. */
        }
        #ಆದರೆ_ಅಂತ್ಯ /* portPRELOAD_REGISTERS */

        ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
    }

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
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
    #ಆದರೆ ( configCHECK_HANDLER_INSTALLATION == 1 )
    {
        ಸ್ಥಿರಾಂಕ ಪೋರ್ಟ್_ISR_t * ಸ್ಥಿರಾಂಕ px_ಸದಿಶ_ಕೋಷ್ಟಕ = ಪೋರ್ಟ್_SCB_VTOR_REG;

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
        configASSERT( px_ಸದಿಶ_ಕೋಷ್ಟಕ[ ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_SVC ] == SVC_Handler );
        configASSERT( px_ಸದಿಶ_ಕೋಷ್ಟಕ[ ಪೋರ್ಟ್_ಸದಿಶ_ಸೂಚ್ಯಂಕ_PENDSV ] == PendSV_Handler );
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configCHECK_HANDLER_INSTALLATION */

    /* Make PendSV and SysTick the lowest priority interrupts, and make SVCall
     * the highest priority. */
    ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_PENDSV_PRI;
    ಪೋರ್ಟ್_NVIC_SHPR3_REG |= ಪೋರ್ಟ್_NVIC_SYSTICK_PRI;
    ಪೋರ್ಟ್_NVIC_SHPR2_REG = 0;

    #ಆದರೆ ( configENABLE_MPU == 1 )
    {
        /* Setup the Memory Protection Unit (MPU). */
        prv_ಸಿದ್ಧತೆ_MPU();
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

    /* Start the timer that generates the tick ISR. Interrupts are disabled
     * here already. */
    v_ಪೋರ್ಟ್_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /* Initialize the critical nesting count ready for the first task. */
    ulCriticalNesting = 0;

    #ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )
    {
        xSchedulerRunning = pdTRUE;
    }
    #ಆದರೆ_ಅಂತ್ಯ

    /* Start the first task. */
    v_ಆರಂಭ_ಮೊದಲ_Task();

    /* Should never get here as the tasks will now be executing. Call the task
     * exit error function to prevent compiler warnings about a static function
     * not being called in the case that the application writer overrides this
     * functionality by defining configTASK_RETURN_ADDRESS. Call
     * vTaskSwitchContext() so link time optimization does not remove the
     * symbol. */
    vTaskSwitchContext();
    prvTaskExitError();

    /* Should not get here. */
    ಹಿಂತಿರುಗಿ 0;
}

/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}

/*-----------------------------------------------------------*/

#ಆದರೆ ( configENABLE_MPU == 1 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                    ಸ್ಥಿರಾಂಕ ರಚನೆ x_ಸ್ಮರಣೆ_REGION * ಸ್ಥಿರಾಂಕ xRegions,
                                    ರಾಶಿ_Type_t * px_Bottom_ದ_ರಾಶಿ,
                                    config_ರಾಶಿ_ಆಳ_TYPE ux_ರಾಶಿ_ಆಳ )
    {
        #ಆದರೆ defined( __ARMCC_VERSION )

            /* Declaration when these variable are defined in code instead of being
             * exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t * __SRAM_segment_start__;
            ಬಾಹ್ಯ uint32_t * __SRAM_segment_end__;
            ಬಾಹ್ಯ uint32_t * __privileged_sram_start__;
            ಬಾಹ್ಯ uint32_t * __privileged_sram_end__;

        #ಇಲ್ಲದಿದ್ದರೆ
            /* Declaration when these variable are exported from linker scripts. */
            ಬಾಹ್ಯ uint32_t __SRAM_segment_start__[];
            ಬಾಹ್ಯ uint32_t __SRAM_segment_end__[];
            ಬಾಹ್ಯ uint32_t __privileged_sram_start__[];
            ಬಾಹ್ಯ uint32_t __privileged_sram_end__[];

        #ಆದರೆ_ಅಂತ್ಯ /* defined( __ARMCC_VERSION ) */

        int32_t l_ಸೂಚ್ಯಂಕ;
        uint32_t ul;

        ಆದರೆ( xRegions == ಖಾಲಿ )
        {
            /* No MPU regions are specified so allow access to all RAM. */
            xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                ( ( ( uint32_t ) __SRAM_segment_start__ ) | /* Base address. */
                  ( ಪೋರ್ಟ್_MPU_RBAR_REGION_ಸಂಖ್ಯೆ_VALID_BITMASK ) |
                  ( ಪೋರ್ಟ್_ರಾಶಿ_REGION ) );                   /* Region number. */

            xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                ( ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                  ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER ) |
                  ( ( configS_C_B_SRAM & ಪೋರ್ಟ್_MPU_RASR_S_C_B_BITMASK ) << ಪೋರ್ಟ್_MPU_RASR_S_C_B_LOCATION ) |
                  ( prv_Get_MPURegion_ಗಾತ್ರ_Setting( ( uint32_t ) __SRAM_segment_end__ - ( uint32_t ) __SRAM_segment_start__ ) ) |
                  ( ಪೋರ್ಟ್_MPU_RASR_REGION_ENABLE_BITMASK ) );


            /* Invalidate user configurable regions. */
            ಗಾಗಿ( ul = 1UL; ul <= ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS; ul++ )
            {
                xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | ಪೋರ್ಟ್_MPU_RBAR_REGION_ಸಂಖ್ಯೆ_VALID_BITMASK );
                xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
            }
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* This function is called automatically when the task is created - in
             * which case the stack region parameters will be valid.  At all other
             * times the stack parameters will not be valid and it is assumed that the
             * stack region has already been configured. */
            ಆದರೆ( ux_ರಾಶಿ_ಆಳ > 0 )
            {
                /* Define the region that allows access to the stack. */
                xMPUSettings->xRegionsSettings[ 0 ].ulRBAR =
                    ( ( ( uint32_t ) px_Bottom_ದ_ರಾಶಿ ) |
                      ( ಪೋರ್ಟ್_MPU_RBAR_REGION_ಸಂಖ್ಯೆ_VALID_BITMASK ) |
                      ( ಪೋರ್ಟ್_ರಾಶಿ_REGION ) ); /* Region number. */

                xMPUSettings->xRegionsSettings[ 0 ].ulRASR =
                    ( ( ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_UNPRIV_RW ) |
                      ( ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER ) |
                      ( prv_Get_MPURegion_ಗಾತ್ರ_Setting( ux_ರಾಶಿ_ಆಳ * ( uint32_t ) ಗಾತ್ರ( ರಾಶಿ_Type_t ) ) ) |
                      ( ( configS_C_B_SRAM & ಪೋರ್ಟ್_MPU_RASR_S_C_B_BITMASK ) << ಪೋರ್ಟ್_MPU_RASR_S_C_B_LOCATION ) |
                      ( ಪೋರ್ಟ್_MPU_RASR_REGION_ENABLE_BITMASK ) );
            }

            l_ಸೂಚ್ಯಂಕ = 0;

            ಗಾಗಿ( ul = 1UL; ul <= ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS; ul++ )
            {
                ಆದರೆ( ( xRegions[ l_ಸೂಚ್ಯಂಕ ] ).ul_ಉದ್ದಳತೆ_ಒಳ_ಬೈಟುಗಳು > 0UL )
                {
                    /* Translate the generic region definition contained in
                     * xRegions into the CM0+ specific MPU settings that are then
                     * stored in xMPUSettings. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR =
                        ( ( uint32_t ) xRegions[ l_ಸೂಚ್ಯಂಕ ].pv_ತಳ_ವಿಳಾಸ ) |
                        ( ಪೋರ್ಟ್_MPU_RBAR_REGION_ಸಂಖ್ಯೆ_VALID_BITMASK ) |
                        ( ul - 1UL ); /* Region number. */

                    xMPUSettings->xRegionsSettings[ ul ].ulRASR =
                        ( prv_Get_MPURegion_ಗಾತ್ರ_Setting( xRegions[ l_ಸೂಚ್ಯಂಕ ].ul_ಉದ್ದಳತೆ_ಒಳ_ಬೈಟುಗಳು ) ) |
                        ( xRegions[ l_ಸೂಚ್ಯಂಕ ].ulParameters ) |
                        ( ಪೋರ್ಟ್_MPU_RASR_REGION_ENABLE_BITMASK );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    /* Invalidate the region. */
                    xMPUSettings->xRegionsSettings[ ul ].ulRBAR = ( ( ul - 1UL ) | ಪೋರ್ಟ್_MPU_RBAR_REGION_ಸಂಖ್ಯೆ_VALID_BITMASK );
                    xMPUSettings->xRegionsSettings[ ul ].ulRASR = 0UL;
                }

            l_ಸೂಚ್ಯಂಕ++;
        }
    }
}

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_MPU */

/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_ಬಫರ್,
                                                size_t x_ಬಫರ್_ಉದ್ದಳತೆ,
                                                uint32_t ulAccessRequested ) /* PRIVILEGED_FUNCTION */

    {
        uint32_t i, ul_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ, ul_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ;
        uint32_t ul_Region_ಆರಂಭ, ul_Region_ಗಾತ್ರ, ul_Region_ಕೊನೆ;
        uint32_t ulMPURegionAccessPermissions;
        ತಳ_Type_t xAccessGranted = pdFALSE;
        ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ ); /* Calling task's MPU settings. */

        ಆದರೆ( xSchedulerRunning == pdFALSE )
        {
            /* Grant access to all the kernel objects before the scheduler
             * is started. It is necessary because there is no task running
             * yet and therefore, we cannot use the permissions of any
             * task. */
            xAccessGranted = pdTRUE;
        }
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ( xTaskMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
        {
            xAccessGranted = pdTRUE;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ಆದರೆ( ಪೋರ್ಟ್_ಕೂಡಿಸು_UINT32_WILL_ಅತಿಪ್ರವಾಹ( ( ( uint32_t ) pv_ಬಫರ್ ), ( ( uint32_t ) x_ಬಫರ್_ಉದ್ದಳತೆ - 1UL ) ) == pdFALSE )
            {
                ul_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ = ( uint32_t ) pv_ಬಫರ್;
                ul_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ = ( ( ( uint32_t ) pv_ಬಫರ್ ) + ( uint32_t ) x_ಬಫರ್_ಉದ್ದಳತೆ - 1UL );

                ಗಾಗಿ( i = 0; i < ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS; i++ )
                {
                    /* Is the MPU region enabled? */
                    ಆದರೆ( ( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                          ಪೋರ್ಟ್_MPU_RASR_REGION_ENABLE_BITMASK ) == ಪೋರ್ಟ್_MPU_RASR_REGION_ENABLE_BITMASK )
                    {
                        ul_Region_ಆರಂಭ = ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಮೊದಲ_ವಿಳಾಸ_FROM_RBAR( xTaskMpuSettings->xRegionsSettings[ i ].ulRBAR );
                        ul_Region_ಗಾತ್ರ = ಪೋರ್ಟ್_ಹೊರತೆಗೆ_REGION_ಗಾತ್ರ_FROM_RASR( xTaskMpuSettings->xRegionsSettings[ i ].ulRASR );
                        ul_Region_ಕೊನೆ = ul_Region_ಆರಂಭ + ul_Region_ಗಾತ್ರ;

                        ಆದರೆ( ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ul_ಬಫರ್_ಆರಂಭ_ವಿಳಾಸ,
                                                         ul_Region_ಆರಂಭ,
                                                         ul_Region_ಕೊನೆ ) &&
                            ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( ul_ಬಫರ್_ಕೊನೆ_ವಿಳಾಸ,
                                                         ul_Region_ಆರಂಭ,
                                                         ul_Region_ಕೊನೆ ) )
                        {
                            ulMPURegionAccessPermissions = xTaskMpuSettings->xRegionsSettings[ i ].ulRASR &
                                                           ಪೋರ್ಟ್_MPU_RASR_AP_BITMASK;

                            ಆದರೆ( ulAccessRequested == tskMPU_READ_PERMISSION ) /* RO. */
                            {
                                ಆದರೆ( ( ulMPURegionAccessPermissions == ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == ಪೋರ್ಟ್_MPU_REGION_PRIV_RO_UNPRIV_RO ) ||
                                    ( ulMPURegionAccessPermissions == ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_UNPRIV_RW ) )
                                {
                                    xAccessGranted = pdTRUE;
                                    ನಿಲ್ಲಿಸು;
                                }
                            }
                            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( ( ulAccessRequested & tskMPU_WRITE_PERMISSION ) != 0UL ) /* W or RW. */
                            {
                                ಆದರೆ( ulMPURegionAccessPermissions == ಪೋರ್ಟ್_MPU_REGION_PRIV_RW_UNPRIV_RW )
                                {
                                    xAccessGranted = pdTRUE;
                                    ನಿಲ್ಲಿಸು;
                                }
                            }
                        }
                    }
                }
            }
        }

        ಹಿಂತಿರುಗಿ xAccessGranted;
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Inside_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    uint32_t ul_Current_ಅಡಚಣೆ;
    ತಳ_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. Interrupt Program
     * Status Register (IPSR) holds the exception number of the currently-executing
     * exception or zero for Thread mode.*/
    __asm ಅಸ್ಥಿರ ( "mrs %0, ipsr" : "=r" ( ul_Current_ಅಡಚಣೆ )::"memory" );

    ಆದರೆ( ul_Current_ಅಡಚಣೆ == 0 )
    {
        xReturn = pdFALSE;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        xReturn = pdTRUE;
    }

    ಹಿಂತಿರುಗಿ xReturn;
}

/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Grant_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t x_ಆಂತರಿಕ_Task_Handle,
                                         int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
        ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ಆಂತರಿಕ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] |= ( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Revoke_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t x_ಆಂತರಿಕ_Task_Handle,
                                          int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
    {
        uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
        xMPU_SETTINGS * xTaskMpuSettings;

        ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
        ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

        xTaskMpuSettings = xTaskGetMPUSettings( x_ಆಂತರಿಕ_Task_Handle );

        xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] &= ~( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) && ( configENABLE_ACCESS_CONTROL_LIST == 1 ) ) */

/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ, ul_Access_Control_List_ನಮೂದು_ಬಿಟ್;
            ತಳ_Type_t xAccessGranted = pdFALSE;
            ಸ್ಥಿರಾಂಕ xMPU_SETTINGS * xTaskMpuSettings;

            ಆದರೆ( xSchedulerRunning == pdFALSE )
            {
                /* Grant access to all the kernel objects before the scheduler
                 * is started. It is necessary because there is no task running
                 * yet and therefore, we cannot use the permissions of any
                 * task. */
                xAccessGranted = pdTRUE;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xTaskMpuSettings = xTaskGetMPUSettings( ಖಾಲಿ ); /* Calling task's MPU settings. */

                ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );
                ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ = ( ( uint32_t ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object % ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು );

                ಆದರೆ( ( xTaskMpuSettings->ulTaskFlags & ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG ) == ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG )
                {
                    xAccessGranted = pdTRUE;
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    ಆದರೆ( ( xTaskMpuSettings->ulAccessControlList[ ul_Access_Control_List_ನಮೂದು_ಸೂಚ್ಯಂಕ ] & ( 1U << ul_Access_Control_List_ನಮೂದು_ಬಿಟ್ ) ) != 0 )
                    {
                        xAccessGranted = pdTRUE;
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xAccessGranted;
        }

    #ಇಲ್ಲದಿದ್ದರೆ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

        ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( int32_t l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object ) /* PRIVILEGED_FUNCTION */
        {
            ( ಶೂನ್ಯ ) l_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_ದ_Kernel_Object;

            /* If Access Control List feature is not used, all the tasks have
             * access to all the kernel objects. */
            ಹಿಂತಿರುಗಿ pdTRUE;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */

/*-----------------------------------------------------------*/
