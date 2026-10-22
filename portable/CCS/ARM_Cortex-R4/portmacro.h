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

#ifndef __PORTMACRO_H__
#define __PORTMACRO_H__

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR        حرف
#define portFLOAT       عائم
#define portDOUBLE      مزدوج
#define portLONG        long
#define portSHORT       short
#define port_کەڵەکە_TYPE  uint32_t
#define portBASE_TYPE   long

تعريفنوع port_کەڵەکە_TYPE کەڵەکە_Type_t;
تعريفنوع long BaseType_t;
تعريفنوع unsigned long UBaseType_t;

#إذا (configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS)
    تعريفنوع uint16_t TickType_t;
    #define portMAX_DELAY (TickType_t) 0xFFFF
#وإلاإذا ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    تعريفنوع uint32_t TickType_t;
    #define portMAX_DELAY (TickType_t) 0xFFFFFFFFF

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC 1
#وإلا
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif


/* Architecture specifics. */
#define port_کەڵەکە_GROWTH    (-1)
#define portTICK_PERIOD_MS    ((TickType_t) 1000 / configTICK_RATE_HZ)
#define portBYTE_ALIGNMENT  8

/* Critical section handling. */
خارجي فراغ vPortEnterCritical(فراغ);
خارجي فراغ vPortExitCritical(فراغ);
#define portENTER_CRITICAL()        vPortEnterCritical()
#define portEXIT_CRITICAL()         vPortExitCritical()
#define portDISABLE_INTERRUPTS()    asm( " CPSID I" )
#define portENABLE_INTERRUPTS()     asm( " CPSIE I" )

/* Scheduler utilities. */
#pragma SWI_ALIAS( vPortYield, 0 )
خارجي فراغ vPortYield( فراغ );
#define portYIELD()                 vPortYield()
#define portSYS_SSIR1_REG           ( * ( ( متطاير uint32_t * ) 0xFFFFFFB0 ) )
#define portSYS_SSIR1_SSKEY         ( 0x7500UL )
#define portYIELD_WITHIN_API()      { portSYS_SSIR1_REG = portSYS_SSIR1_SSKEY;  asm( " DSB " ); asm( " ISB " ); }
#define portYIELD_FROM_ISR( x )     افعل { إذا( x != pdFALSE ) { portSYS_SSIR1_REG = portSYS_SSIR1_SSKEY;  ( فراغ ) portSYS_SSIR1_REG; } } طالما( 0 )

#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#endif

/* Architecture specific optimisations. */
#إذا configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #إذا( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
    #endif

    /* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

    /*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( ux_لووتکە_Priority, uxReadyPriorities ) ux_لووتکە_Priority = ( 31 - __clz( ( uxReadyPriorities ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION(vFunction, pvParameters)       فراغ vFunction(فراغ *pvParameters)
#define portTASK_FUNCTION_PROTO(vFunction, pvParameters) فراغ vFunction(فراغ *pvParameters)

#endif /* __PORTMACRO_H__ */
