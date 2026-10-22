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
#define portDOUBLE      ഇരട്ട
#define portLONG        long
#define portSHORT       പൂർണ്ണസംഖ്യ
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

/* Hardware specifics. */
#define portBYTE_ALIGNMENT          1
#define portGLOBAL_INT_ENABLE_BIT   0x80
#define port_അട്ടി_GROWTH            1
#define portTICK_PERIOD_MS          ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#define portDISABLE_INTERRUPTS()    INTCONbits.GIEH = 0;
#define portENABLE_INTERRUPTS()     INTCONbits.GIEH = 1;

/* Push the INTCON register onto the stack, then disable interrupts. */
#define portENTER_CRITICAL()        POSTINC1 = INTCON;              \
                                    INTCONbits.GIEH = 0;

/* Retrieve the INTCON register from the stack, and enable interrupts
if they were saved as being enabled.  Don't modify any other bits
within the INTCON register as these may have legitimately have been
modified within the critical region. */
#define portEXIT_CRITICAL()         _asm                                    \
                                        MOVF    POSTDEC1, 1, 0              \
                                    _endasm                                 \
                                    എങ്കിൽ( INDF1 & portGLOBAL_INT_ENABLE_BIT ) \
                                    {                                       \
                                        portENABLE_INTERRUPTS();            \
                                    }
/*-----------------------------------------------------------*/

/* Task utilities. */
ബാഹ്യ ശൂന്യം vPortYield( ശൂന്യം );
#define portYIELD()             vPortYield()
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) ശൂന്യം vFunction( ശൂന്യം *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) ശൂന്യം vFunction( ശൂന്യം *pvParameters )
/*-----------------------------------------------------------*/

/* Required by the kernel aware debugger. */
#ifdef __DEBUG
    #define portREMOVE_STATIC_QUALIFIER
#endif


#define portNOP()               _asm    \
                                    NOP \
                                _endasm

#endif /* PORTMACRO_H */
