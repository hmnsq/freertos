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

/* *INDENT-OFF* */
#ifdef __cplusplus
    ബാഹ്യ "C" {
#endif
/* *INDENT-ON* */

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
#define portCHAR        അക്ഷരം
#define portFLOAT       ദശാംശം
#define portDOUBLE      long
#define portLONG        long
#define portSHORT       പൂർണ്ണസംഖ്യ
#define port_അട്ടി_TYPE  uint16_t
#define portBASE_TYPE   short

തരനിർവചനം port_അട്ടി_TYPE അട്ടി_Type_t;
തരനിർവചനം short BaseType_t;
തരനിർവചനം unsigned short UBaseType_t;


#എങ്കിൽ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        തരനിർവചനം uint16_t TickType_t;
        #define portMAX_DELAY ( TickType_t ) 0xffff
#അല്ലെങ്കിലെങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    തരനിർവചനം uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#അല്ലെങ്കിൽ
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Critical section management. */
ശൂന്യം portENTER_CRITICAL( ശൂന്യം );
#pragma aux portENTER_CRITICAL = "pushf" \
                                 "cli";

ശൂന്യം portEXIT_CRITICAL( ശൂന്യം );
#pragma aux portEXIT_CRITICAL   = "popf";

ശൂന്യം portDISABLE_INTERRUPTS( ശൂന്യം );
#pragma aux portDISABLE_INTERRUPTS = "cli";

ശൂന്യം portENABLE_INTERRUPTS( ശൂന്യം );
#pragma aux portENABLE_INTERRUPTS = "sti";
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_അട്ടി_GROWTH        ( -1 )
#define port_SWITCH_INT_സംഖ്യ   0x80
#define portYIELD()             __asm{ പൂർണ്ണസംഖ്യ port_SWITCH_INT_സംഖ്യ }
#define portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT      2
#define portINITIAL_SW          ( ( port_അട്ടി_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
#define portNOP()               __asm{ nop }
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#define port_നിവേശം_BYTE( xAddr )                 inp( xAddr )
#define portOUTPUT_BYTE( xAddr, uc_മൂല്യം )       outp( xAddr, uc_മൂല്യം )
#define port_നിവേശം_WORD( xAddr )                 inpw( xAddr )
#define portOUTPUT_WORD( xAddr, us_മൂല്യം )       outpw( xAddr, us_മൂല്യം )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) ശൂന്യം vFunction( ശൂന്യം *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) ശൂന്യം vFunction( ശൂന്യം *pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
