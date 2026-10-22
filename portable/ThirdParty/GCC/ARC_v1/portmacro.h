/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Synopsys, Inc. or its affiliates.  All Rights Reserved.
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
#ضمن "embARC.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
    خارجي "C" {
#endif
/* *INDENT-ON* */

/* record stack high address for stack check */
#ifndef config_RECORD_کەڵەکە_بەرز_ADDRESS
    #define config_RECORD_کەڵەکە_بەرز_ADDRESS    1
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

/* Type definitions. */
#define portCHAR          حرف
#define portFLOAT         عائم
#define portDOUBLE        مزدوج
#define portLONG          long
#define portSHORT         short
#define port_کەڵەکە_TYPE    unsigned صحيح
#define portBASE_TYPE     portLONG

#ifndef Asm
    #define Asm           __asm__ متطاير
#endif

/*
 *  normal constants
 */
#ifndef عدم
    #define عدم    0           /* invalid pointer */
#endif /* NULL */

#ifndef true
    #define true    1           /* true */
#endif /* true */

#ifndef false
    #define false    0          /* false */
#endif /* false */

تعريفنوع port_کەڵەکە_TYPE   کەڵەکە_Type_t;
تعريفنوع long             BaseType_t;
تعريفنوع unsigned long    UBaseType_t;

#إذا ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    تعريفنوع uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    تعريفنوع uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif

#define portNO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
#define port_کەڵەکە_GROWTH           ( -1 )
#define portTICK_PERIOD_MS         ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT         8
#define portNOP()               Asm( "nop_s" );
#define IPM_ENABLE_ALL             1

#define portYIELD_FROM_ISR()    vPortYieldFromIsr()
#define portYIELD()             vPortYield()

/* Critical section management. */
#define portDISABLE_INTERRUPTS() \
    {                            \
        arc_lock();              \
    }                            \

#define portENABLE_INTERRUPTS() \
    {                           \
        arc_unlock();           \
    }                           \

خارجي متطاير unsigned صحيح ulCriticalNesting;

#define portENTER_CRITICAL()     \
    {                            \
        portDISABLE_INTERRUPTS() \
        ulCriticalNesting++;     \
    }


#define portEXIT_CRITICAL()                                    \
    {                                                          \
        إذا( ulCriticalNesting > portNO_CRITICAL_NESTING )      \
        {                                                      \
            ulCriticalNesting--;                               \
            إذا( ulCriticalNesting == portNO_CRITICAL_NESTING ) \
            {                                                  \
                portENABLE_INTERRUPTS()                        \
            }                                                  \
        }                                                      \
    }


#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()              افعل {} طالما( 0 )     /* we use the timer */
#define port_ALT_GET_RUN_TIME_COUNTER_بەها( dest )            ( dest = x_Tick_ژماردن )

فراغ vPortYield( فراغ );
فراغ vPortYieldFromIsr( فراغ );

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
