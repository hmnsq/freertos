/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2025-2026 Arm Limited and/or its affiliates
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR          ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT         ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE        ದ್ವಿಗುಣ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG          ದೀರ್ಘ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT         ಗಿಡ್ಡ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE    size_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE     ದೀರ್ಘ

#ಆದರೆ !defined(__ASSEMBLER__)
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ತಳ_TYPE    ತಳ_Type_t;
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t         UBaseType_t;

    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t         TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY    ( ( TickType_t ) 0xffffffffffffffff )
#ಆದರೆ_ಅಂತ್ಯ /* if !defined(__ASSEMBLER__) */

/* 64-bit tick type on a 64-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH         ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT       16
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

#ಆದರೆ !defined(__ASSEMBLER__)
    /* Called at the end of an ISR that can cause a context switch. */
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( xSwitchRequired ) \
        {                                                \
            ಬಾಹ್ಯ uint64_t ull_ಪೋರ್ಟ್_Yield_Required;        \
                                                        \
            ಆದರೆ( xSwitchRequired != pdFALSE )             \
            {                                            \
                ull_ಪೋರ್ಟ್_Yield_Required = pdTRUE;           \
            }                                            \
        }
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( xSwitchRequired )                   \
        {                                                                  \
            ಬಾಹ್ಯ uint64_t ull_ಪೋರ್ಟ್_Yield_Required[ config_ಸಂಖ್ಯೆ_ದ_CORES ]; \
                                                                        \
            ಆದರೆ( xSwitchRequired != pdFALSE )                               \
            {                                                              \
                ull_ಪೋರ್ಟ್_Yield_Required[ ಪೋರ್ಟ್_GET_CORE_ID() ] = pdTRUE;        \
            }                                                              \
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES == 1 ) */
#ಆದರೆ_ಅಂತ್ಯ /* if !defined(__ASSEMBLER__) */

/**
 * @brief SVC numbers.
 */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_SYSTEM_CALL_EXIT                    104
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_YIELD                               105
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_ಆರಂಭ_ಮೊದಲ_TASK                    106
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_DISABLE_INTERRUPTS                  107
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_ENABLE_INTERRUPTS                   108
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_GET_CORE_ID                         109
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_ಮುಖವಾಡ_ALL_INTERRUPTS                 110
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_UNMASK_ALL_INTERRUPTS               111
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_UNMASK_INTERRUPTS                   112
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_CHECK_PRIVILEGE                     113
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_SAVE_TASK_CONTEXT                   114
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_RESTORE_CONTEXT                     115
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_DELETE_CURRENT_TASK                 116
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SVC_ಅಡಚಣೆ_CORE                      117

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )    ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()                __asm ಅಸ್ಥಿರ ( "SVC %0" : : "i" ( ಪೋರ್ಟ್_SVC_YIELD ) : "memory" )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

#ಆದರೆ !defined(__ASSEMBLER__)
    ಬಾಹ್ಯ UBaseType_t vTaskEnterCriticalFromISR( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ );
    ಬಾಹ್ಯ UBaseType_t ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ( ಶೂನ್ಯ );
    ಬಾಹ್ಯ UBaseType_t ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( UBaseType_t ux_New_ಮುಖವಾಡ_ಮೌಲ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( UBaseType_t ux_New_ಮುಖವಾಡ_ಮೌಲ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಅಡಚಣೆ_Core( uint32_t ul_ಅಡಚಣೆ_ID, uint8_t ucCoreID );
#ಆದರೆ_ಅಂತ್ಯ /* if !defined(__ASSEMBLER__) */

/* Use SVC so this is safe from EL0. EL1 sites in the port use direct MSR. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS() __asm ಅಸ್ಥಿರ ( "SVC %0" : : "i" ( ಪೋರ್ಟ್_SVC_DISABLE_INTERRUPTS ) : "memory" )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()  __asm ಅಸ್ಥಿರ ( "SVC %0" : : "i" ( ಪೋರ್ಟ್_SVC_ENABLE_INTERRUPTS ) : "memory" )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UNMASK_ಮೌಲ್ಯ           ( 0xFFUL )

#ಆದರೆ !defined(__ASSEMBLER__)
    /* These macros do not globally disable/enable interrupts.  They do mask off
     * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #ಆದರೆ  ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
        ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ );
        ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ );
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                  v_ಪೋರ್ಟ್_Enter_Critical()
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                   v_ಪೋರ್ಟ್_Exit_Critical()
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                  vTaskEnterCritical()
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                   vTaskExitCritical()
    #ಆದರೆ_ಅಂತ್ಯ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR()         ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x )    v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( x )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#ಆದರೆ_ಅಂತ್ಯ /* if !defined(__ASSEMBLER__) */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

#ಆದರೆ !defined(__ASSEMBLER__)
    /* Prototype of the FreeRTOS tick handler.  This must be installed as the
     * handler for whichever peripheral is used to generate the RTOS tick. */
    ಶೂನ್ಯ FreeRTOS_Tick_Handler( ಶೂನ್ಯ );
#ಆದರೆ_ಅಂತ್ಯ /* if !defined(__ASSEMBLER__) */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_NO_FPU_CONTEXT_BY_DEFAULT     ( 1U )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT   ( 2U )

/* If configUSE_TASK_FPU_SUPPORT is set to portTASK_NO_FPU_CONTEXT_BY_DEFAULT (1U)
 * (or left undefined) then tasks are created without an FPU context and
 * must call vPortTaskUsesFPU() to give themselves an FPU context before
 * using any FPU instructions.  If configUSE_TASK_FPU_SUPPORT is set to
 * portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT (2U) then all tasks will have an FPU context
 * by default. */
#ಆದರೆ ( configUSE_TASK_FPU_SUPPORT == ಪೋರ್ಟ್_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ );
#ಇಲ್ಲದಿದ್ದರೆ
/* Each task has an FPU context already, so define this function away to
 * nothing to prevent it from being called accidentally. */
    #ವ್ಯಾಖ್ಯಾನಿಸು v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU()
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_ಬಳಸುತ್ತದೆ_FLOATING_ಬಿಂದು()          v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU()

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅತಿಕಡಿಮೆ_ಅಡಚಣೆ_ಆದ್ಯತೆ           ( ( ( uint32_t ) config_UNIQUE_ಅಡಚಣೆ_PRIORITIES ) - 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅತಿಕಡಿಮೆ_USABLE_ಅಡಚಣೆ_ಆದ್ಯತೆ    ( ಪೋರ್ಟ್_ಅತಿಕಡಿಮೆ_ಅಡಚಣೆ_ಆದ್ಯತೆ - 1UL )

/* Architecture specific optimisations. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION
    #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION    1
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1

    /* Store/clear the ready priorities in a bit map. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities )    ux_ತುದಿ_ಆದ್ಯತೆ = ( 31 - __builtin_clz( uxReadyPriorities ) )

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ಆದರೆ ( configASSERT_DEFINED == 1 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ( ಶೂನ್ಯ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASSERT_IF_ಅಡಚಣೆ_ಆದ್ಯತೆ_INVALID()    v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ()
#ಆದರೆ_ಅಂತ್ಯ /* configASSERT */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()     __asm ಅಸ್ಥಿರ ( "NOP" )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#ಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 16
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            4
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    3
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 32
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            3
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    2
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 64
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            2
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    1
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 128
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            1
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    0
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 256
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            0
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    0
#ಇಲ್ಲದಿದ್ದರೆ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #ದೋಷ Invalid config_UNIQUE_ಅಡಚಣೆ_PRIORITIES setting.  config_UNIQUE_ಅಡಚಣೆ_PRIORITIES must be ಗಣ ಗಮ್ಯ the ಸಂಖ್ಯೆ ದ unique priorities implemented by the ಗುರಿ hardware
#ಆದರೆ_ಅಂತ್ಯ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅಡಚಣೆ_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್_ಸ್ಥಾನಾಂತರ    ( 0x400U )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_CORE_INT_ID                     ( 0x0U )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_API_ಆದ್ಯತೆ_ಮುಖವಾಡ                 ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು )

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

    #ಆದರೆ !defined(__ASSEMBLER__)
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
        {
            e_Isr_ಬೀಗ = 0,
            e_Task_ಬೀಗ,
            e_ಬೀಗ_ಎಣಿಕೆ
        } e_ಪೋರ್ಟ್_RTOSLock;

        ಬಾಹ್ಯ ಅಸ್ಥಿರ uint64_t ullCriticalNestings[ config_ಸಂಖ್ಯೆ_ದ_CORES ];
        ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( uint8_t ucCoreID,
                                        e_ಪೋರ್ಟ್_RTOSLock e_ಬೀಗ_ಅಂಕೆ,
                                        ತಳ_Type_t uxAcquire );
        ಬಾಹ್ಯ uint8_t uc_ಪೋರ್ಟ್_Get_Core_ID( ಶೂನ್ಯ );
        ಬಾಹ್ಯ uint8_t uc_ಪೋರ್ಟ್_Get_Core_IDFrom_Isr( ಶೂನ್ಯ );
    #ಆದರೆ_ಅಂತ್ಯ /* if !defined(__ASSEMBLER__) */

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()         ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ( x )    v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( x )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ               config_ಸಂಖ್ಯೆ_ದ_CORES
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_CORE_ID()                uc_ಪೋರ್ಟ್_Get_Core_ID()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_CORE_ID_FROM_ISR()       uc_ಪೋರ್ಟ್_Get_Core_IDFrom_Isr()

    /* Use SGI 0 as the yield core interrupt. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_CORE( xCoreID )                          v_ಅಡಚಣೆ_Core( ಪೋರ್ಟ್_YIELD_CORE_INT_ID, ( uint8_t ) xCoreID )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_ISR_ಬೀಗ( xCoreID )                    v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( uint8_t ) xCoreID, e_Isr_ಬೀಗ, pdFALSE )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ISR_ಬೀಗ( xCoreID )                        v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( uint8_t ) xCoreID, e_Isr_ಬೀಗ, pdTRUE )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_TASK_ಬೀಗ( xCoreID )                   v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( uint8_t ) xCoreID, e_Task_ಬೀಗ, pdFALSE )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_TASK_ಬೀಗ( xCoreID )                       v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( uint8_t ) xCoreID, e_Task_ಬೀಗ, pdTRUE )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID )          ( ullCriticalNestings[ ( uint8_t ) xCoreID ] )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID, x )       ( ullCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INCREMENT_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DECREMENT_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]-- )

#ಆದರೆ_ಅಂತ್ಯ /* configNUMBER_OF_CORES > 1 */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER()    __asm ಅಸ್ಥಿರ ( "" ::: "memory" )

/**
 * @brief MPU specific constants.
 */
#ಆದರೆ ( configENABLE_MPU == 1 )

    #ಆದರೆ !defined(__ASSEMBLER__)
        ಬಾಹ್ಯ ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Task_Privileged( ಶೂನ್ಯ );
    #ಆದರೆ_ಅಂತ್ಯ /* if !defined(__ASSEMBLER__) */

    /* Device memory attributes used in MAIR_EL1 registers.
     *
     * 8-bit values encoded as follows:
     *  Bit[7:4] - 0000 - Device Memory
     *  Bit[3:2] - 00 --> Device-nGnRnE
     *             01 --> Device-nGnRE
     *             10 --> Device-nGRE
     *             11 --> Device-GRE
     *  Bit[1:0] - 00.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_n_Gn_Rn_E                 ( 0x00 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_n_Gn_RE                  ( 0x04 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_n_GRE                   ( 0x08 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_DEVICE_ಸ್ಮರಣೆ_GRE                    ( 0x0C )

    /* MPU settings that can be overridden in FreeRTOSConfig.h. */
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಒಟ್ಟು_MPU_REGIONS
        #ವ್ಯಾಖ್ಯಾನಿಸು config_ಒಟ್ಟು_MPU_REGIONS                  ( 16UL )
    #ಆದರೆ_ಅಂತ್ಯ

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGED_FLASH_REGION                  ( 0ULL )                                /* Privileged flash region number. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UNPRIVILEGED_FLASH_REGION                ( 1ULL )                                /* Unprivileged flash region number. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UNPRIVILEGED_SYSCALLS_REGION             ( 2ULL )                                /* Unprivileged syscalls region number. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGED_RAM_REGION                    ( 3ULL )                                /* Privileged RAM region number. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_REGION                             ( 4ULL )                                /* Stack region number. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_REGION_ಸೂಚ್ಯಂಕ                       ( 0ULL )                                /* Stack region index in the xRegionSettings array. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಮೊದಲ_CONFIGURABLE_REGION                ( 5ULL )                                /* First user configurable region number. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆಯ_CONFIGURABLE_REGION                 ( config_ಒಟ್ಟು_MPU_REGIONS - 1UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS                 ( ( ಪೋರ್ಟ್_ಕೊನೆಯ_CONFIGURABLE_REGION - ಪೋರ್ಟ್_ಮೊದಲ_CONFIGURABLE_REGION ) + 1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS                        ( ಪೋರ್ಟ್_ಅಂಕೆ_CONFIGURABLE_REGIONS + 1 )    /* Plus one to make space for the stack region. */

    #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು ( 32UL )
    #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_ACCESS_CONTROL_LIST == 1 */

    #ಆದರೆ !defined(__ASSEMBLER__)
        /**
         * @brief Settings to define an MPU region.
         */
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MPURegionSettings
        {
            uint64_t ullPrbarEl1; /**< PRBAR_EL1 for the region. */
            uint64_t ullPrlarEl1; /**< PRLAR_EL1 for the region. */
        } MPURegionSettings_t;

        #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ
            #ವ್ಯಾಖ್ಯಾನಿಸು config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ 128  /* must be defined to the desired size of the system call stack in words for using MPU wrappers v2. */
        #ಆದರೆ_ಅಂತ್ಯ

        /**
         * @brief System call info.
         */
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SYSTEM_CALL_INFO
        {
            /* Used to save both the user-mode stack pointer (SP_EL0) and link register (X30)
             * at system call entry so they can be restored or referenced safely even if the task
             * switches out while executing the system call.
             */
            uint64_t ull_Link_ರಿಜಿಸ್ಟರ್_At_System_Call_ನಮೂದು;
            uint64_t ull_User_SPAt_System_Call_ನಮೂದು;
        } xSYSTEM_CALL_INFO;
    #ಆದರೆ_ಅಂತ್ಯ /* if !defined(__ASSEMBLER__) */

    /**
     * @brief Task context as stored in the TCB.
     */
    #ಆದರೆ ( configENABLE_FPU == 1 )
        /*
         * +-----------+------------+--------------------------------+-------------+------------------+
         * |  Q0-Q31   | FPSR, FPCR |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +-----------+------------+--------------------------------+-------------+------------------+
         *
         * <-----------><-----------><-------------------------------><------------><----------------->
         *      64            2                      2                      32               2
         */
        #ವ್ಯಾಖ್ಯಾನಿಸು MAX_CONTEXT_ಗಾತ್ರ    102

    #ಇಲ್ಲದಿದ್ದರೆ /* #if ( configENABLE_FPU == 1 ) */
        /*
         * +--------------------------------+-------------+------------------+
         * |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +--------------------------------+-------------+------------------+
         * <-------------------------------><------------><------------------>
         *                 2                      32               2
         */
        #ವ್ಯಾಖ್ಯಾನಿಸು MAX_CONTEXT_ಗಾತ್ರ    36
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_FPU == 1 ) */

    #ಆದರೆ !defined(__ASSEMBLER__)
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ MPU_SETTINGS
        {
            uint64_t ullTaskUnprivilegedSP;                                              /* Task's unprivileged user stack pointer. */
            uint64_t ullMairEl1;                                                         /* MAIR_EL1 for the task containing attributes. */
            MPURegionSettings_t xRegionsSettings[ ಪೋರ್ಟ್_ಒಟ್ಟು_ಅಂಕೆ_REGIONS ];               /* Settings for tasks' regions. */
            uint64_t ullContext[ MAX_CONTEXT_ಗಾತ್ರ + config_SYSTEM_CALL_ರಾಶಿ_ಗಾತ್ರ ];      /* Task's saved context. */
            uint64_t ullTaskFlags;

            xSYSTEM_CALL_INFO xSystemCallInfo;

            #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ / ಪೋರ್ಟ್_ACL_ನಮೂದು_ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು ) + 1 ];
            #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_ACCESS_CONTROL_LIST */
        } xMPU_SETTINGS;
    #ಆದರೆ_ಅಂತ್ಯ /* if !defined(__ASSEMBLER__) */

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_USING_MPU_WRAPPERS                        ( 1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್                             ( 0x80000000UL )

    /* Normal memory attributes used in MAIR_EL1 registers. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_ಸಾಮಾನ್ಯ_ಸ್ಮರಣೆ_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_ಸಾಮಾನ್ಯ_ಸ್ಮರಣೆ_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR0_POS                    ( 0UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR0_ಮುಖವಾಡ                   ( 0x00000000000000ffULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR1_POS                    ( 8UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR1_ಮುಖವಾಡ                   ( 0x000000000000ff00ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR2_POS                    ( 16UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR2_ಮುಖವಾಡ                   ( 0x0000000000ff0000ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR3_POS                    ( 24UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR3_ಮುಖವಾಡ                   ( 0x00000000ff000000ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR4_POS                    ( 32UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR4_ಮುಖವಾಡ                   ( 0x000000ff00000000ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR5_POS                    ( 40UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR5_ಮುಖವಾಡ                   ( 0x0000ff0000000000ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR6_POS                    ( 48UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR6_ಮುಖವಾಡ                   ( 0x00ff000000000000ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR7_POS                    ( 56UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_MAIR_EL1_ATTR7_ಮುಖವಾಡ                   ( 0xff00000000000000ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ                ( 0x0000FFFFFFFFFFC0ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ                ( 0x0000FFFFFFFFFFC0ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_IMPLIED_ಬಿಟ್ಟುಗಳು        ( 0x000000000000003FULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ಮುಖವಾಡ     ( 3ULL<< 2ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_NON_SHAREABLE                  ( 0ULL << 4ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_OUTER_SHAREABLE                ( 2ULL << 4ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_INNER_SHAREABLE                ( 3ULL << 4ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0ULL << 2ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_READ_WRITE                     ( 1ULL << 2ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2ULL << 2ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_READ_ONLY                      ( 3ULL << 2ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_REGION_EXECUTE_NEVER                  ( 1ULL << 1ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX0                 ( 0ULL << 1ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX1                 ( 1ULL << 1ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX2                 ( 2ULL << 1ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX3                 ( 3ULL << 1ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX4                 ( 4ULL << 1ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX5                 ( 5ULL << 1ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX6                 ( 6ULL << 1ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRLAR_EL1_ATTR_INDEX7                 ( 7ULL << 1ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRLAR_EL1_REGION_ENABLE               ( 1ULL )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_ENABLE_ಬಿಟ್                            ( 1ULL << 0ULL )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MPU_PRIV_BACKGROUND_ENABLE_ಬಿಟ್            ( 1ULL << 17ULL )

    /* Max value that fits in a uint64_t type. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UINT64_MAX                                ( ~( ( uint64_t ) 0 ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೂಡಿಸು_UINT64_WILL_ಅತಿಪ್ರವಾಹ( a, b )          ( ( a ) > ( ಪೋರ್ಟ್_UINT64_MAX - ( b ) ) )

    /* Extract first address of the MPU region as encoded in the
     * PRBAR_EL1 register value. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಮೊದಲ_ವಿಳಾಸ_FROM_PRBAR_EL1( prbar_el1 ) \
        ( ( prbar_el1 ) & ಪೋರ್ಟ್_MPU_PRBAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ )

    /* Extract last address of the MPU region as encoded in the
     * PRLAR_EL1 register value. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಹೊರತೆಗೆ_ಕೊನೆಯ_ವಿಳಾಸ_FROM_PRLAR_EL1( prlar_el1 ) \
        ( ( ( prlar_el1 ) & ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_ಮುಖವಾಡ ) | ಪೋರ್ಟ್_MPU_PRLAR_EL1_ವಿಳಾಸ_IMPLIED_ಬಿಟ್ಟುಗಳು )

    /* Does addr lies within [start, end] address range? */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_ವಿಳಾಸ_WITHIN_RANGE( addr, ಆರಂಭ, ಕೊನೆ ) \
        ( ( ( addr ) >= ( ಆರಂಭ ) ) && ( ( addr ) <= ( ಕೊನೆ ) ) )

    /* Is the access request satisfied by the available permissions? */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_AUTHORIZED( accessRequest, permissions ) \
        ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

    /**
     * @brief Offsets in the task's stack (context).
     */
    #ಆದರೆ ( configUSE_TASK_FPU_SUPPORT == ಪೋರ್ಟ್_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC     ( 68 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR     ( 70 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X0     ( 100 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X1     ( 101 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X2     ( 98 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X3     ( 99 )
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_PC     ( 2 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_LR     ( 4 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X0     ( 34 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X1     ( 35 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X2     ( 32 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಥಾನಾಂತರ_ಗಮ್ಯ_X3     ( 33 )
    #ಆದರೆ_ಅಂತ್ಯ

    /**
     * @brief Flag used to mark that a Task is privileged.
     *
     * @ingroup Port Privilege
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IS_TASK_PRIVILEGED() x_ಪೋರ್ಟ್_Is_Task_Privileged()

#ಇಲ್ಲದಿದ್ದರೆ

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್        ( 0x0UL )

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_MPU == 1 ) */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_PSTATE_I_ಬಿಟ್             ( 0x7 )

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
