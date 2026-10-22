/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
        ਬਾਹਰੀ "C"
        {
    #ਜੇ_ਅੰਤ

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions - These are a bit legacy and not really used now, other
 * than portSTACK_TYPE and portBASE_TYPE. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          ਅੱਖਰ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          ਲੰਮਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         ਛੋਟਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    uint32_t
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਲੰਮਾ

    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE   ਢੇਰ_Type_t;
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਲੰਮਾ             ਅਧਾਰ_Type_t;
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ    UBaseType_t;

/* Defines the maximum time when using a wait command in a task */
    #ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t     TickType_t;
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffff
    #ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t     TickType_t;
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_TYPE_IS_ATOMIC    1
    #ਨਹੀਂਤਾਂ
        #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
    #ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/

/* Architecture specifics */

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_STSR( reg )              __stsr( ( reg ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LDSR( reg, val )         __ldsr( ( reg ), ( val ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_STSR_CCRH( reg, sel )    __stsr_rh( ( reg ), ( sel ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SYNCM()                  __syncm()

/* Determine the descending of the stack from high address to address */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH      ( -1 )

/* Determine the time (in milliseconds) corresponding to each tick */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )

/* It is a multiple of 4 (the two lower-order bits of the address = 0),
 * otherwise it will cause MAE (Misaligned Exception) according to the manual */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT    ( 4 )

/* Interrupt control macros. */

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()     __EI() /* Macro to enable all maskable interrupts. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()    __DI() /* Macro to disable all maskable interrupts. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ taskENABLE_INTERRUPTS()     ਪੋਰਟ_ENABLE_INTERRUPTS()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ taskDISABLE_INTERRUPTS()    ਪੋਰਟ_DISABLE_INTERRUPTS()

/* SMP build which means configNUM_CORES is relevant */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SUPPORT_SMP              1

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ           2
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਸੰਖਿਆ_ਦਾ_CORES
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਸੰਖਿਆ_ਦਾ_CORES    1
    #ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/
/* Scheduler utilities */

/* Called at the end of an ISR that can cause a context switch */
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_ਸੈੱਟ_Switch( ਅਧਾਰ_Type_t xSwitchRequired );

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( x )    v_ਪੋਰਟ_ਸੈੱਟ_Switch( x )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x )       ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( x )

/* Use to transfer control from one task to perform other tasks of
 * higher priority */
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ );

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()    v_ਪੋਰਟ_Yield()
    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

/* Return the core ID on which the code is running. */
        ਬਾਹਰੀ ਅਧਾਰ_Type_t x_ਪੋਰਟ_GET_CORE_ID();

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_CORE_ID()    x_ਪੋਰਟ_GET_CORE_ID()
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ coreid    x_ਪੋਰਟ_GET_CORE_ID()

/* Request the core ID x to yield. */
        ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Yield_Core( uint32_t coreID );

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_CORE( x )                v_ਪੋਰਟ_Yield_Core( x )

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )

    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES > 1 ) */

    #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ISR_ਤਾਲਾ( xCoreID )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_ISR_ਤਾਲਾ( xCoreID )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_TASK_ਤਾਲਾ( xCoreID )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_TASK_ਤਾਲਾ( xCoreID )
    #ਨਹੀਂਤਾਂ
        ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Recursive_ਤਾਲਾ_Acquire( ਅਧਾਰ_Type_t xCoreID, ਅਧਾਰ_Type_t xFromIsr );
        ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Recursive_ਤਾਲਾ_Release( ਅਧਾਰ_Type_t xCoreID, ਅਧਾਰ_Type_t xFromIsr );

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ISR_ਤਾਲਾ( xCoreID )         v_ਪੋਰਟ_Recursive_ਤਾਲਾ_Acquire( ( xCoreID ), pdTRUE )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_ISR_ਤਾਲਾ( xCoreID )     v_ਪੋਰਟ_Recursive_ਤਾਲਾ_Release( ( xCoreID ), pdTRUE )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_TASK_ਤਾਲਾ( xCoreID )        v_ਪੋਰਟ_Recursive_ਤਾਲਾ_Acquire( ( xCoreID ), pdFALSE )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_TASK_ਤਾਲਾ( xCoreID )    v_ਪੋਰਟ_Recursive_ਤਾਲਾ_Release( ( xCoreID ), pdFALSE )
    #ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/
/* Critical section management. */

/* The critical nesting functions defined within tasks.c */

    ਬਾਹਰੀ ਖਾਲੀ vTaskEnterCritical( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ vTaskExitCritical( ਖਾਲੀ );

/* Macro to mark the start of a critical code region */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()    vTaskEnterCritical()

/* Macro to mark the end of a critical code region */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/
/* Macros to set and clear the interrupt mask. */
    ਪੋਰਟ_LONG x_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ();
    ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( ਪੋਰਟ_LONG );

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()                  x_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ( x )             v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( ( x ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR()         x_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( x )    v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( ( x ) )

/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

/*-----------------------------------------------------------*/

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* PORTMACRO_H */
