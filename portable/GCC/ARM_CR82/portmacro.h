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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    size_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਲੰਮਾ

#ਜੇ !defined(__ASSEMBLER__)
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE   ਢੇਰ_Type_t;
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਅਧਾਰ_TYPE    ਅਧਾਰ_Type_t;
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t         UBaseType_t;

    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t         TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( ( TickType_t ) 0xffffffffffffffff )
#ਜੇ_ਅੰਤ /* if !defined(__ASSEMBLER__) */

/* 64-bit tick type on a 64-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH         ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT       16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

#ਜੇ !defined(__ASSEMBLER__)
    /* Called at the end of an ISR that can cause a context switch. */
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( xSwitchRequired ) \
        {                                                \
            ਬਾਹਰੀ uint64_t ull_ਪੋਰਟ_Yield_Required;        \
                                                        \
            ਜੇ( xSwitchRequired != pdFALSE )             \
            {                                            \
                ull_ਪੋਰਟ_Yield_Required = pdTRUE;           \
            }                                            \
        }
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( xSwitchRequired )                   \
        {                                                                  \
            ਬਾਹਰੀ uint64_t ull_ਪੋਰਟ_Yield_Required[ config_ਸੰਖਿਆ_ਦਾ_CORES ]; \
                                                                        \
            ਜੇ( xSwitchRequired != pdFALSE )                               \
            {                                                              \
                ull_ਪੋਰਟ_Yield_Required[ ਪੋਰਟ_GET_CORE_ID() ] = pdTRUE;        \
            }                                                              \
        }
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES == 1 ) */
#ਜੇ_ਅੰਤ /* if !defined(__ASSEMBLER__) */

/**
 * @brief SVC numbers.
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_SYSTEM_CALL_EXIT                    104
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_YIELD                               105
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_ਸ਼ੁਰੂ_ਪਹਿਲਾ_TASK                    106
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_DISABLE_INTERRUPTS                  107
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_ENABLE_INTERRUPTS                   108
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_GET_CORE_ID                         109
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_ਨਕਾਬ_ALL_INTERRUPTS                 110
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_UNMASK_ALL_INTERRUPTS               111
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_UNMASK_INTERRUPTS                   112
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_CHECK_PRIVILEGE                     113
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_SAVE_TASK_CONTEXT                   114
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_RESTORE_CONTEXT                     115
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_DELETE_CURRENT_TASK                 116
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SVC_ਰੁਕਾਵਟ_CORE                      117

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x )    ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( x )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()                __asm ਅਸਥਿਰ ( "SVC %0" : : "i" ( ਪੋਰਟ_SVC_YIELD ) : "memory" )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

#ਜੇ !defined(__ASSEMBLER__)
    ਬਾਹਰੀ UBaseType_t vTaskEnterCriticalFromISR( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ );
    ਬਾਹਰੀ UBaseType_t ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ( ਖਾਲੀ );
    ਬਾਹਰੀ UBaseType_t ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( UBaseType_t ux_New_ਨਕਾਬ_ਮੁੱਲ );
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( UBaseType_t ux_New_ਨਕਾਬ_ਮੁੱਲ );
    ਬਾਹਰੀ ਖਾਲੀ v_ਰੁਕਾਵਟ_Core( uint32_t ul_ਰੁਕਾਵਟ_ID, uint8_t ucCoreID );
#ਜੇ_ਅੰਤ /* if !defined(__ASSEMBLER__) */

/* Use SVC so this is safe from EL0. EL1 sites in the port use direct MSR. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS() __asm ਅਸਥਿਰ ( "SVC %0" : : "i" ( ਪੋਰਟ_SVC_DISABLE_INTERRUPTS ) : "memory" )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()  __asm ਅਸਥਿਰ ( "SVC %0" : : "i" ( ਪੋਰਟ_SVC_ENABLE_INTERRUPTS ) : "memory" )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UNMASK_ਮੁੱਲ           ( 0xFFUL )

#ਜੇ !defined(__ASSEMBLER__)
    /* These macros do not globally disable/enable interrupts.  They do mask off
     * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #ਜੇ  ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
        ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ );
        ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ );
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                  v_ਪੋਰਟ_Enter_Critical()
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                   v_ਪੋਰਟ_Exit_Critical()
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                  vTaskEnterCritical()
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                   vTaskExitCritical()
    #ਜੇ_ਅੰਤ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR()         ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( x )    v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( x )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL_FROM_ISR()             vTaskEnterCriticalFromISR()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL_FROM_ISR( x )           vTaskExitCriticalFromISR( x )
#ਜੇ_ਅੰਤ /* if !defined(__ASSEMBLER__) */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

#ਜੇ !defined(__ASSEMBLER__)
    /* Prototype of the FreeRTOS tick handler.  This must be installed as the
     * handler for whichever peripheral is used to generate the RTOS tick. */
    ਖਾਲੀ FreeRTOS_Tick_Handler( ਖਾਲੀ );
#ਜੇ_ਅੰਤ /* if !defined(__ASSEMBLER__) */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_NO_FPU_CONTEXT_BY_DEFAULT     ( 1U )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT   ( 2U )

/* If configUSE_TASK_FPU_SUPPORT is set to portTASK_NO_FPU_CONTEXT_BY_DEFAULT (1U)
 * (or left undefined) then tasks are created without an FPU context and
 * must call vPortTaskUsesFPU() to give themselves an FPU context before
 * using any FPU instructions.  If configUSE_TASK_FPU_SUPPORT is set to
 * portTASK_HAVE_FPU_CONTEXT_BY_DEFAULT (2U) then all tasks will have an FPU context
 * by default. */
#ਜੇ ( configUSE_TASK_FPU_SUPPORT == ਪੋਰਟ_TASK_NO_FPU_CONTEXT_BY_DEFAULT )
    ਖਾਲੀ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU( ਖਾਲੀ );
#ਨਹੀਂਤਾਂ
/* Each task has an FPU context already, so define this function away to
 * nothing to prevent it from being called accidentally. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU()
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_ਵਰਤਦਾ_FLOATING_ਬਿੰਦੂ()          v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU()

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ_ਰੁਕਾਵਟ_ਤਰਜੀਹ           ( ( ( uint32_t ) config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES ) - 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ_USABLE_ਰੁਕਾਵਟ_ਤਰਜੀਹ    ( ਪੋਰਟ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ_ਰੁਕਾਵਟ_ਤਰਜੀਹ - 1UL )

/* Architecture specific optimisations. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION    1
#ਜੇ_ਅੰਤ

#ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1

    /* Store/clear the ready priorities in a bit map. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰਿਕਾਰਡ_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ਤਰਜੀਹ ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ਤਰਜੀਹ ) )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities )    ux_ਸਿਖਰ_ਤਰਜੀਹ = ( 31 - __builtin_clz( uxReadyPriorities ) )

#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ਜੇ ( configASSERT_DEFINED == 1 )
    ਖਾਲੀ v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ( ਖਾਲੀ );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASSERT_IF_ਰੁਕਾਵਟ_ਤਰਜੀਹ_INVALID()    v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ()
#ਜੇ_ਅੰਤ /* configASSERT */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()     __asm ਅਸਥਿਰ ( "NOP" )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#ਜੇ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES == 16
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ            4
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ    3
#ਜਾਂਜੇ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES == 32
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ            3
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ    2
#ਜਾਂਜੇ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES == 64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ            2
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ    1
#ਜਾਂਜੇ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES == 128
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ            1
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ    0
#ਜਾਂਜੇ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES == 256
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ            0
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ    0
#ਨਹੀਂਤਾਂ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #ਗਲਤੀ Invalid config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES setting.  config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES must be ਸੈੱਟ ਮੰਜ਼ਿਲ the ਸੰਖਿਆ ਦਾ unique priorities implemented by the ਨਿਸ਼ਾਨਾ hardware
#ਜੇ_ਅੰਤ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰੁਕਾਵਟ_ਤਰਜੀਹ_ਰਜਿਸਟਰ_ਵਿੱਥ    ( 0x400U )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_CORE_INT_ID                     ( 0x0U )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_API_ਤਰਜੀਹ_ਨਕਾਬ                 ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ )

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

    #ਜੇ !defined(__ASSEMBLER__)
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
        {
            e_Isr_ਤਾਲਾ = 0,
            e_Task_ਤਾਲਾ,
            e_ਤਾਲਾ_ਗਿਣਤੀ
        } e_ਪੋਰਟ_RTOSLock;

        ਬਾਹਰੀ ਅਸਥਿਰ uint64_t ullCriticalNestings[ config_ਸੰਖਿਆ_ਦਾ_CORES ];
        ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Recursive_ਤਾਲਾ( uint8_t ucCoreID,
                                        e_ਪੋਰਟ_RTOSLock e_ਤਾਲਾ_ਅੰਕ,
                                        ਅਧਾਰ_Type_t uxAcquire );
        ਬਾਹਰੀ uint8_t uc_ਪੋਰਟ_Get_Core_ID( ਖਾਲੀ );
        ਬਾਹਰੀ uint8_t uc_ਪੋਰਟ_Get_Core_IDFrom_Isr( ਖਾਲੀ );
    #ਜੇ_ਅੰਤ /* if !defined(__ASSEMBLER__) */

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()         ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ( x )    v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( x )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ               config_ਸੰਖਿਆ_ਦਾ_CORES
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_CORE_ID()                uc_ਪੋਰਟ_Get_Core_ID()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_CORE_ID_FROM_ISR()       uc_ਪੋਰਟ_Get_Core_IDFrom_Isr()

    /* Use SGI 0 as the yield core interrupt. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_CORE( xCoreID )                          v_ਰੁਕਾਵਟ_Core( ਪੋਰਟ_YIELD_CORE_INT_ID, ( uint8_t ) xCoreID )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_ISR_ਤਾਲਾ( xCoreID )                    v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( uint8_t ) xCoreID, e_Isr_ਤਾਲਾ, pdFALSE )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ISR_ਤਾਲਾ( xCoreID )                        v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( uint8_t ) xCoreID, e_Isr_ਤਾਲਾ, pdTRUE )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_TASK_ਤਾਲਾ( xCoreID )                   v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( uint8_t ) xCoreID, e_Task_ਤਾਲਾ, pdFALSE )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_TASK_ਤਾਲਾ( xCoreID )                       v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( uint8_t ) xCoreID, e_Task_ਤਾਲਾ, pdTRUE )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID )          ( ullCriticalNestings[ ( uint8_t ) xCoreID ] )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID, x )       ( ullCriticalNestings[ ( uint8_t ) xCoreID ] = ( x ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INCREMENT_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]++ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DECREMENT_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID )    ( ullCriticalNestings[ ( uint8_t ) xCoreID ]-- )

#ਜੇ_ਅੰਤ /* configNUMBER_OF_CORES > 1 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER()    __asm ਅਸਥਿਰ ( "" ::: "memory" )

/**
 * @brief MPU specific constants.
 */
#ਜੇ ( configENABLE_MPU == 1 )

    #ਜੇ !defined(__ASSEMBLER__)
        ਬਾਹਰੀ ਅਧਾਰ_Type_t x_ਪੋਰਟ_Is_Task_Privileged( ਖਾਲੀ );
    #ਜੇ_ਅੰਤ /* if !defined(__ASSEMBLER__) */

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
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_n_Gn_Rn_E                 ( 0x00 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_n_Gn_RE                  ( 0x04 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_n_GRE                   ( 0x08 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_DEVICE_ਸਮ੍ਰਿਤੀ_GRE                    ( 0x0C )

    /* MPU settings that can be overridden in FreeRTOSConfig.h. */
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਕੁੱਲ_MPU_REGIONS
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਕੁੱਲ_MPU_REGIONS                  ( 16UL )
    #ਜੇ_ਅੰਤ

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGED_FLASH_REGION                  ( 0ULL )                                /* Privileged flash region number. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UNPRIVILEGED_FLASH_REGION                ( 1ULL )                                /* Unprivileged flash region number. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UNPRIVILEGED_SYSCALLS_REGION             ( 2ULL )                                /* Unprivileged syscalls region number. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGED_RAM_REGION                    ( 3ULL )                                /* Privileged RAM region number. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_REGION                             ( 4ULL )                                /* Stack region number. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_REGION_ਸੂਚਕਾਂਕ                       ( 0ULL )                                /* Stack region index in the xRegionSettings array. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਪਹਿਲਾ_CONFIGURABLE_REGION                ( 5ULL )                                /* First user configurable region number. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਆਖਰੀ_CONFIGURABLE_REGION                 ( config_ਕੁੱਲ_MPU_REGIONS - 1UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS                 ( ( ਪੋਰਟ_ਆਖਰੀ_CONFIGURABLE_REGION - ਪੋਰਟ_ਪਹਿਲਾ_CONFIGURABLE_REGION ) + 1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS                        ( ਪੋਰਟ_ਅੰਕ_CONFIGURABLE_REGIONS + 1 )    /* Plus one to make space for the stack region. */

    #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ ( 32UL )
    #ਜੇ_ਅੰਤ /* configENABLE_ACCESS_CONTROL_LIST == 1 */

    #ਜੇ !defined(__ASSEMBLER__)
        /**
         * @brief Settings to define an MPU region.
         */
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPURegionSettings
        {
            uint64_t ullPrbarEl1; /**< PRBAR_EL1 for the region. */
            uint64_t ullPrlarEl1; /**< PRLAR_EL1 for the region. */
        } MPURegionSettings_t;

        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ 128  /* must be defined to the desired size of the system call stack in words for using MPU wrappers v2. */
        #ਜੇ_ਅੰਤ

        /**
         * @brief System call info.
         */
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SYSTEM_CALL_INFO
        {
            /* Used to save both the user-mode stack pointer (SP_EL0) and link register (X30)
             * at system call entry so they can be restored or referenced safely even if the task
             * switches out while executing the system call.
             */
            uint64_t ull_Link_ਰਜਿਸਟਰ_At_System_Call_ਇੰਦਰਾਜ;
            uint64_t ull_User_SPAt_System_Call_ਇੰਦਰਾਜ;
        } xSYSTEM_CALL_INFO;
    #ਜੇ_ਅੰਤ /* if !defined(__ASSEMBLER__) */

    /**
     * @brief Task context as stored in the TCB.
     */
    #ਜੇ ( configENABLE_FPU == 1 )
        /*
         * +-----------+------------+--------------------------------+-------------+------------------+
         * |  Q0-Q31   | FPSR, FPCR |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +-----------+------------+--------------------------------+-------------+------------------+
         *
         * <-----------><-----------><-------------------------------><------------><----------------->
         *      64            2                      2                      32               2
         */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ    102

    #ਨਹੀਂਤਾਂ /* #if ( configENABLE_FPU == 1 ) */
        /*
         * +--------------------------------+-------------+------------------+
         * |  CRITICAL_NESTING, FPU_CONTEXT | X0-X30, XZR | INIT_PSTATE, PC  |
         * +--------------------------------+-------------+------------------+
         * <-------------------------------><------------><------------------>
         *                 2                      32               2
         */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CONTEXT_ਮਾਪ    36
    #ਜੇ_ਅੰਤ /* #if ( configENABLE_FPU == 1 ) */

    #ਜੇ !defined(__ASSEMBLER__)
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ MPU_SETTINGS
        {
            uint64_t ullTaskUnprivilegedSP;                                              /* Task's unprivileged user stack pointer. */
            uint64_t ullMairEl1;                                                         /* MAIR_EL1 for the task containing attributes. */
            MPURegionSettings_t xRegionsSettings[ ਪੋਰਟ_ਕੁੱਲ_ਅੰਕ_REGIONS ];               /* Settings for tasks' regions. */
            uint64_t ullContext[ MAX_CONTEXT_ਮਾਪ + config_SYSTEM_CALL_ਢੇਰ_ਮਾਪ ];      /* Task's saved context. */
            uint64_t ullTaskFlags;

            xSYSTEM_CALL_INFO xSystemCallInfo;

            #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                uint32_t ulAccessControlList[ ( config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ / ਪੋਰਟ_ACL_ਇੰਦਰਾਜ_ਮਾਪ_ਬਿੱਟ ) + 1 ];
            #ਜੇ_ਅੰਤ /* configENABLE_ACCESS_CONTROL_LIST */
        } xMPU_SETTINGS;
    #ਜੇ_ਅੰਤ /* if !defined(__ASSEMBLER__) */

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_USING_MPU_WRAPPERS                        ( 1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ                             ( 0x80000000UL )

    /* Normal memory attributes used in MAIR_EL1 registers. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_ਸਾਧਾਰਨ_ਸਮ੍ਰਿਤੀ_NON_CACHEABLE           ( 0x44 )       /* Non-cacheable. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_ਸਾਧਾਰਨ_ਸਮ੍ਰਿਤੀ_BUFFERABLE_CACHEABLE    ( 0xFF )       /* Non-Transient, Write-back, Read-Allocate and Write-Allocate. */

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR0_POS                    ( 0UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR0_ਨਕਾਬ                   ( 0x00000000000000ffULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR1_POS                    ( 8UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR1_ਨਕਾਬ                   ( 0x000000000000ff00ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR2_POS                    ( 16UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR2_ਨਕਾਬ                   ( 0x0000000000ff0000ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR3_POS                    ( 24UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR3_ਨਕਾਬ                   ( 0x00000000ff000000ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR4_POS                    ( 32UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR4_ਨਕਾਬ                   ( 0x000000ff00000000ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR5_POS                    ( 40UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR5_ਨਕਾਬ                   ( 0x0000ff0000000000ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR6_POS                    ( 48UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR6_ਨਕਾਬ                   ( 0x00ff000000000000ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR7_POS                    ( 56UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_MAIR_EL1_ATTR7_ਨਕਾਬ                   ( 0xff00000000000000ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ                ( 0x0000FFFFFFFFFFC0ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_ਨਕਾਬ                ( 0x0000FFFFFFFFFFC0ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_IMPLIED_ਬਿੱਟ        ( 0x000000000000003FULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRBAR_EL1_ACCESS_PERMISSIONS_ਨਕਾਬ     ( 3ULL<< 2ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_NON_SHAREABLE                  ( 0ULL << 4ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_OUTER_SHAREABLE                ( 2ULL << 4ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_INNER_SHAREABLE                ( 3ULL << 4ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_WRITE          ( 0ULL << 2ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_READ_WRITE                     ( 1ULL << 2ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_PRIVILEGED_READ_ONLY           ( 2ULL << 2ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_READ_ONLY                      ( 3ULL << 2ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_REGION_EXECUTE_NEVER                  ( 1ULL << 1ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX0                 ( 0ULL << 1ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX1                 ( 1ULL << 1ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX2                 ( 2ULL << 1ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX3                 ( 3ULL << 1ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX4                 ( 4ULL << 1ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX5                 ( 5ULL << 1ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX6                 ( 6ULL << 1ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRLAR_EL1_ATTR_INDEX7                 ( 7ULL << 1ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRLAR_EL1_REGION_ENABLE               ( 1ULL )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ                            ( 1ULL << 0ULL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MPU_PRIV_BACKGROUND_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ            ( 1ULL << 17ULL )

    /* Max value that fits in a uint64_t type. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UINT64_MAX                                ( ~( ( uint64_t ) 0 ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਜੋੜੋ_UINT64_WILL_ਉਛਾਲ( a, b )          ( ( a ) > ( ਪੋਰਟ_UINT64_MAX - ( b ) ) )

    /* Extract first address of the MPU region as encoded in the
     * PRBAR_EL1 register value. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਕੱਢੋ_ਪਹਿਲਾ_ਪਤਾ_FROM_PRBAR_EL1( prbar_el1 ) \
        ( ( prbar_el1 ) & ਪੋਰਟ_MPU_PRBAR_EL1_ਪਤਾ_ਨਕਾਬ )

    /* Extract last address of the MPU region as encoded in the
     * PRLAR_EL1 register value. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਕੱਢੋ_ਆਖਰੀ_ਪਤਾ_FROM_PRLAR_EL1( prlar_el1 ) \
        ( ( ( prlar_el1 ) & ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_ਨਕਾਬ ) | ਪੋਰਟ_MPU_PRLAR_EL1_ਪਤਾ_IMPLIED_ਬਿੱਟ )

    /* Does addr lies within [start, end] address range? */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_ਪਤਾ_WITHIN_RANGE( addr, ਸ਼ੁਰੂ, ਸਿਰਾ ) \
        ( ( ( addr ) >= ( ਸ਼ੁਰੂ ) ) && ( ( addr ) <= ( ਸਿਰਾ ) ) )

    /* Is the access request satisfied by the available permissions? */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_AUTHORIZED( accessRequest, permissions ) \
        ( ( ( permissions ) & ( accessRequest ) ) == accessRequest )

    /**
     * @brief Offsets in the task's stack (context).
     */
    #ਜੇ ( configUSE_TASK_FPU_SUPPORT == ਪੋਰਟ_TASK_HAVE_FPU_CONTEXT_BY_DEFAULT )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC     ( 68 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR     ( 70 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X0     ( 100 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X1     ( 101 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X2     ( 98 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X3     ( 99 )
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_PC     ( 2 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_LR     ( 4 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X0     ( 34 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X1     ( 35 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X2     ( 32 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਵਿੱਥ_ਮੰਜ਼ਿਲ_X3     ( 33 )
    #ਜੇ_ਅੰਤ

    /**
     * @brief Flag used to mark that a Task is privileged.
     *
     * @ingroup Port Privilege
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_IS_PRIVILEGED_FLAG   ( 1UL << 1UL )

    /**
     * @brief Checks whether or not the calling task is privileged.
     *
     * @return pdTRUE if the calling task is privileged, pdFALSE otherwise.
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IS_TASK_PRIVILEGED() x_ਪੋਰਟ_Is_Task_Privileged()

#ਨਹੀਂਤਾਂ

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ        ( 0x0UL )

#ਜੇ_ਅੰਤ /* #if ( configENABLE_MPU == 1 ) */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PSTATE_I_ਦੋਆਧਾਰੀ_ਅੰਕ             ( 0x7 )

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
