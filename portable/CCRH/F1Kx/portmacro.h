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

#ifndef PORTMACRO_H
    #define PORTMACRO_H

    #ifdef __cplusplus
        बाह्य "C"
        {
    #endif

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
    #define portCHAR          अक्षर
    #define portFLOAT         दशांश
    #define portDOUBLE        द्विगुण
    #define portLONG          दीर्घ
    #define portSHORT         लघु
    #define port_चळत_TYPE    uint32_t
    #define portBASE_TYPE     दीर्घ

    प्रकारव्याख्या port_चळत_TYPE   चळत_Type_t;
    प्रकारव्याख्या दीर्घ             BaseType_t;
    प्रकारव्याख्या अचिन्हित दीर्घ    UBaseType_t;

/* Defines the maximum time when using a wait command in a task */
    #जर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        प्रकारव्याख्या uint16_t     TickType_t;
        #define portMAX_DELAY              ( TickType_t ) 0xffff
    #किंवाजर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
        प्रकारव्याख्या uint32_t     TickType_t;
        #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #define portTICK_TYPE_IS_ATOMIC    1
    #अन्यथा
        #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
    #endif

/*-----------------------------------------------------------*/

/* Architecture specifics */

    #define portSTSR( reg )              __stsr( ( reg ) )
    #define portLDSR( reg, val )         __ldsr( ( reg ), ( val ) )
    #define portSTSR_CCRH( reg, sel )    __stsr_rh( ( reg ), ( sel ) )
    #define portSYNCM()                  __syncm()

/* Determine the descending of the stack from high address to address */
    #define port_चळत_GROWTH      ( -1 )

/* Determine the time (in milliseconds) corresponding to each tick */
    #define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )

/* It is a multiple of 4 (the two lower-order bits of the address = 0),
 * otherwise it will cause MAE (Misaligned Exception) according to the manual */
    #define portBYTE_ALIGNMENT    ( 4 )

/* Interrupt control macros. */

    #define portENABLE_INTERRUPTS()     __EI() /* Macro to enable all maskable interrupts. */
    #define portDISABLE_INTERRUPTS()    __DI() /* Macro to disable all maskable interrupts. */
    #define taskENABLE_INTERRUPTS()     portENABLE_INTERRUPTS()
    #define taskDISABLE_INTERRUPTS()    portDISABLE_INTERRUPTS()

/* SMP build which means configNUM_CORES is relevant */
    #define portSUPPORT_SMP              1

    #define port_MAX_CORE_मोजणी           2
    #ifndef config_संख्या_OF_CORES
        #define config_संख्या_OF_CORES    1
    #endif

/*-----------------------------------------------------------*/
/* Scheduler utilities */

/* Called at the end of an ISR that can cause a context switch */
    बाह्य शून्य vPortSetSwitch( BaseType_t xSwitchRequired );

    #define portEND_SWITCHING_ISR( x )    vPortSetSwitch( x )

    #define portYIELD_FROM_ISR( x )       portEND_SWITCHING_ISR( x )

/* Use to transfer control from one task to perform other tasks of
 * higher priority */
    बाह्य शून्य vPortYield( शून्य );

    #define portYIELD()    vPortYield()
    #जर ( config_संख्या_OF_CORES > 1 )

/* Return the core ID on which the code is running. */
        बाह्य BaseType_t xPortGET_CORE_ID();

        #define portGET_CORE_ID()    xPortGET_CORE_ID()
        #define coreid    xPortGET_CORE_ID()

/* Request the core ID x to yield. */
        बाह्य शून्य vPortYieldCore( uint32_t coreID );

        #define portYIELD_CORE( x )                vPortYieldCore( x )

        #define portENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
        #define portEXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )

    #endif /* if ( configNUMBER_OF_CORES > 1 ) */

    #जर ( config_संख्या_OF_CORES == 1 )
        #define portGET_ISR_LOCK( xCoreID )
        #define portRELEASE_ISR_LOCK( xCoreID )
        #define portGET_TASK_LOCK( xCoreID )
        #define portRELEASE_TASK_LOCK( xCoreID )
    #अन्यथा
        बाह्य शून्य vPortRecursiveLockAcquire( BaseType_t xCoreID, BaseType_t xFromIsr );
        बाह्य शून्य vPortRecursiveLockRelease( BaseType_t xCoreID, BaseType_t xFromIsr );

        #define portGET_ISR_LOCK( xCoreID )         vPortRecursiveLockAcquire( ( xCoreID ), pdTRUE )
        #define portRELEASE_ISR_LOCK( xCoreID )     vPortRecursiveLockRelease( ( xCoreID ), pdTRUE )
        #define portGET_TASK_LOCK( xCoreID )        vPortRecursiveLockAcquire( ( xCoreID ), pdFALSE )
        #define portRELEASE_TASK_LOCK( xCoreID )    vPortRecursiveLockRelease( ( xCoreID ), pdFALSE )
    #endif /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/
/* Critical section management. */

/* The critical nesting functions defined within tasks.c */

    बाह्य शून्य vTaskEnterCritical( शून्य );
    बाह्य शून्य vTaskExitCritical( शून्य );

/* Macro to mark the start of a critical code region */
    #define portENTER_CRITICAL()    vTaskEnterCritical()

/* Macro to mark the end of a critical code region */
    #define portEXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/
/* Macros to set and clear the interrupt mask. */
    portLONG xPortSetInterruptMask();
    शून्य vPortClearInterruptMask( portLONG );

    #define portSET_INTERRUPT_MASK()                  xPortSetInterruptMask()
    #define portCLEAR_INTERRUPT_MASK( x )             vPortClearInterruptMask( ( x ) )
    #define portSET_INTERRUPT_MASK_FROM_ISR()         xPortSetInterruptMask()
    #define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortClearInterruptMask( ( x ) )

/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */

    #define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
    #define portTASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

/*-----------------------------------------------------------*/

    #ifdef __cplusplus
}
    #endif
#endif /* PORTMACRO_H */
