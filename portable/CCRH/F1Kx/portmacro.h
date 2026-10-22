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

#अगर_अघोषित PORTMACRO_H
    #घोषणा PORTMACRO_H

    #अगर_घोषित __cplusplus
        बाह्य "C"
        {
    #पूर्ण_अगर

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
    #घोषणा portCHAR          अक्षर
    #घोषणा portFLOAT         भग्न
    #घोषणा portDOUBLE        द्विगुन
    #घोषणा portLONG          दीर्घ
    #घोषणा portSHORT         लघु
    #घोषणा port_ढेर_TYPE    uint32_t
    #घोषणा portBASE_TYPE     दीर्घ

    प्रकार port_ढेर_TYPE   ढेर_Type_t;
    प्रकार दीर्घ             BaseType_t;
    प्रकार अचिन्हित दीर्घ    UBaseType_t;

/* Defines the maximum time when using a wait command in a task */
    #अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        प्रकार uint16_t     TickType_t;
        #घोषणा portMAX_DELAY              ( TickType_t ) 0xffff
    #या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
        प्रकार uint32_t     TickType_t;
        #घोषणा portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #घोषणा portTICK_TYPE_IS_ATOMIC    1
    #अन्यथा
        #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
    #पूर्ण_अगर

/*-----------------------------------------------------------*/

/* Architecture specifics */

    #घोषणा portSTSR( reg )              __stsr( ( reg ) )
    #घोषणा portLDSR( reg, val )         __ldsr( ( reg ), ( val ) )
    #घोषणा portSTSR_CCRH( reg, sel )    __stsr_rh( ( reg ), ( sel ) )
    #घोषणा portSYNCM()                  __syncm()

/* Determine the descending of the stack from high address to address */
    #घोषणा port_ढेर_GROWTH      ( -1 )

/* Determine the time (in milliseconds) corresponding to each tick */
    #घोषणा portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )

/* It is a multiple of 4 (the two lower-order bits of the address = 0),
 * otherwise it will cause MAE (Misaligned Exception) according to the manual */
    #घोषणा portBYTE_ALIGNMENT    ( 4 )

/* Interrupt control macros. */

    #घोषणा portENABLE_INTERRUPTS()     __EI() /* Macro to enable all maskable interrupts. */
    #घोषणा portDISABLE_INTERRUPTS()    __DI() /* Macro to disable all maskable interrupts. */
    #घोषणा taskENABLE_INTERRUPTS()     portENABLE_INTERRUPTS()
    #घोषणा taskDISABLE_INTERRUPTS()    portDISABLE_INTERRUPTS()

/* SMP build which means configNUM_CORES is relevant */
    #घोषणा portSUPPORT_SMP              1

    #घोषणा port_MAX_CORE_गिनती           2
    #अगर_अघोषित config_संख्या_OF_CORES
        #घोषणा config_संख्या_OF_CORES    1
    #पूर्ण_अगर

/*-----------------------------------------------------------*/
/* Scheduler utilities */

/* Called at the end of an ISR that can cause a context switch */
    बाह्य व्योम vPortSetSwitch( BaseType_t xSwitchRequired );

    #घोषणा portEND_SWITCHING_ISR( x )    vPortSetSwitch( x )

    #घोषणा portYIELD_FROM_ISR( x )       portEND_SWITCHING_ISR( x )

/* Use to transfer control from one task to perform other tasks of
 * higher priority */
    बाह्य व्योम vPortYield( व्योम );

    #घोषणा portYIELD()    vPortYield()
    #अगर ( config_संख्या_OF_CORES > 1 )

/* Return the core ID on which the code is running. */
        बाह्य BaseType_t xPortGET_CORE_ID();

        #घोषणा portGET_CORE_ID()    xPortGET_CORE_ID()
        #घोषणा coreid    xPortGET_CORE_ID()

/* Request the core ID x to yield. */
        बाह्य व्योम vPortYieldCore( uint32_t coreID );

        #घोषणा portYIELD_CORE( x )                vPortYieldCore( x )

        #घोषणा portENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
        #घोषणा portEXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )

    #पूर्ण_अगर /* if ( configNUMBER_OF_CORES > 1 ) */

    #अगर ( config_संख्या_OF_CORES == 1 )
        #घोषणा portGET_ISR_LOCK( xCoreID )
        #घोषणा portRELEASE_ISR_LOCK( xCoreID )
        #घोषणा portGET_TASK_LOCK( xCoreID )
        #घोषणा portRELEASE_TASK_LOCK( xCoreID )
    #अन्यथा
        बाह्य व्योम vPortRecursiveLockAcquire( BaseType_t xCoreID, BaseType_t xFromIsr );
        बाह्य व्योम vPortRecursiveLockRelease( BaseType_t xCoreID, BaseType_t xFromIsr );

        #घोषणा portGET_ISR_LOCK( xCoreID )         vPortRecursiveLockAcquire( ( xCoreID ), pdTRUE )
        #घोषणा portRELEASE_ISR_LOCK( xCoreID )     vPortRecursiveLockRelease( ( xCoreID ), pdTRUE )
        #घोषणा portGET_TASK_LOCK( xCoreID )        vPortRecursiveLockAcquire( ( xCoreID ), pdFALSE )
        #घोषणा portRELEASE_TASK_LOCK( xCoreID )    vPortRecursiveLockRelease( ( xCoreID ), pdFALSE )
    #पूर्ण_अगर /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/
/* Critical section management. */

/* The critical nesting functions defined within tasks.c */

    बाह्य व्योम vTaskEnterCritical( व्योम );
    बाह्य व्योम vTaskExitCritical( व्योम );

/* Macro to mark the start of a critical code region */
    #घोषणा portENTER_CRITICAL()    vTaskEnterCritical()

/* Macro to mark the end of a critical code region */
    #घोषणा portEXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/
/* Macros to set and clear the interrupt mask. */
    portLONG xPortSetInterruptMask();
    व्योम vPortClearInterruptMask( portLONG );

    #घोषणा portSET_INTERRUPT_MASK()                  xPortSetInterruptMask()
    #घोषणा portCLEAR_INTERRUPT_MASK( x )             vPortClearInterruptMask( ( x ) )
    #घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         xPortSetInterruptMask()
    #घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortClearInterruptMask( ( x ) )

/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */

    #घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
    #घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

/*-----------------------------------------------------------*/

    #अगर_घोषित __cplusplus
}
    #पूर्ण_अगर
#पूर्ण_अगर /* PORTMACRO_H */
