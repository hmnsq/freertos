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

/* *INDENT-OFF* */
#ifdef __cplusplus
    ബാഹ്യ "C" {
#endif
/* *INDENT-ON* */

/* record stack high address for stack check */
#ifndef config_RECORD_അട്ടി_മുകളിലെ_ADDRESS
    #define config_RECORD_അട്ടി_മുകളിലെ_ADDRESS    1
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
#define portCHAR          അക്ഷരം
#define portFLOAT         ദശാംശം
#define portDOUBLE        ഇരട്ട
#define portLONG          long
#define portSHORT         short
#define port_അട്ടി_TYPE    unsigned പൂർണ്ണസംഖ്യ
#define portBASE_TYPE     portLONG

#ifndef Asm
    #define Asm           __asm__ അസ്ഥിര
#endif

/*
 *  normal constants
 */
#ifndef ശൂന്യ
    #define ശൂന്യ    0           /* invalid pointer */
#endif /* NULL */

#ifndef true
    #define true    1           /* true */
#endif /* true */

#ifndef false
    #define false    0          /* false */
#endif /* false */

തരനിർവചനം port_അട്ടി_TYPE   അട്ടി_Type_t;
തരനിർവചനം long             BaseType_t;
തരനിർവചനം unsigned long    UBaseType_t;

#എങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    തരനിർവചനം uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#അല്ലെങ്കിലെങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    തരനിർവചനം uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#അല്ലെങ്കിൽ
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif

#define portNO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
#define port_അട്ടി_GROWTH           ( -1 )
#define portTICK_PERIOD_MS         ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT         8
#define portNOP()               Asm( "nop_s" );
#define IPM_ENABLE_ALL             1

#define portYIELD_FROM_ISR()    vPortYieldFromIsr()
#define portYIELD()             vPortYield()

/* Critical section management. */
#define portDISABLE_INTERRUPTS() \
    {                            \
        Asm( "clri" );           \
        Asm( "" ::: "memory" );  \
    }                            \

#define portENABLE_INTERRUPTS() \
    {                           \
        Asm( "" ::: "memory" ); \
        Asm( "seti" );          \
    }                           \

ബാഹ്യ അസ്ഥിര unsigned പൂർണ്ണസംഖ്യ ulCriticalNesting;

#define portENTER_CRITICAL()     \
    {                            \
        portDISABLE_INTERRUPTS() \
        ulCriticalNesting++;     \
    }


#define portEXIT_CRITICAL()                                    \
    {                                                          \
        എങ്കിൽ( ulCriticalNesting > portNO_CRITICAL_NESTING )      \
        {                                                      \
            ulCriticalNesting--;                               \
            എങ്കിൽ( ulCriticalNesting == portNO_CRITICAL_NESTING ) \
            {                                                  \
                portENABLE_INTERRUPTS()                        \
            }                                                  \
        }                                                      \
    }


#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ശൂന്യം vFunction( ശൂന്യം * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ശൂന്യം vFunction( ശൂന്യം * pvParameters )

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()              ചെയ്യുക {} ആകുമ്പോൾ( 0 )     /* we use the timer */
#define port_ALT_GET_RUN_TIME_COUNTER_മൂല്യം( dest )            ( dest = x_Tick_എണ്ണം )

#എങ്കിൽ defined( __MW__ )
    ബാഹ്യ ശൂന്യം task_end_hook( ശൂന്യം * pxTCB );
    #define portCLEAN_UP_TCB( pxTCB )    task_end_hook( ( ശൂന്യം * ) pxTCB )
#endif

ശൂന്യം vPortYield( ശൂന്യം );
ശൂന്യം vPortYieldFromIsr( ശൂന്യം );

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
