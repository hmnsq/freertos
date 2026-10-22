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

#എങ്കിൽ configUSE_PREEMPTION == 0
    ശൂന്യം vTimer2ISR( ശൂന്യം ) interrupt 5;
#അല്ലെങ്കിൽ
    ശൂന്യം vTimer2ISR( ശൂന്യം ) interrupt 5 _naked;
#endif

ശൂന്യം vSerialISR( ശൂന്യം ) interrupt 4;


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
#define portDOUBLE      ദശാംശം
#define portLONG        long
#define portSHORT       short
#define port_അട്ടി_TYPE  uint8_t
#define portBASE_TYPE   അക്ഷരം

തരനിർവചനം port_അട്ടി_TYPE അട്ടി_Type_t;
തരനിർവചനം signed അക്ഷരം BaseType_t;
തരനിർവചനം unsigned അക്ഷരം UBaseType_t;

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
#define portENTER_CRITICAL()        _asm        \
                                    തള്ളുക    ACC \
                                    തള്ളുക    IE  \
                                    _endasm;    \
                                    EA = 0;

#define portEXIT_CRITICAL()         _asm            \
                                    എടുക്കുക     ACC     \
                                    _endasm;        \
                                    ACC &= 0x80;    \
                                    IE |= ACC;      \
                                    _asm            \
                                    എടുക്കുക     ACC     \
                                    _endasm;

#define portDISABLE_INTERRUPTS()    EA = 0;
#define portENABLE_INTERRUPTS()     EA = 1;
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT          1
#define port_അട്ടി_GROWTH            ( 1 )
#define portTICK_PERIOD_MS          ( ( uint32_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Task utilities. */
ശൂന്യം vPortYield( ശൂന്യം ) _naked;
#define portYIELD() vPortYield();
/*-----------------------------------------------------------*/

#define portNOP()               _asm    \
                                    nop \
                                _endasm;

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) ശൂന്യം vFunction( ശൂന്യം *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) ശൂന്യം vFunction( ശൂന്യം *pvParameters )

#endif /* PORTMACRO_H */
