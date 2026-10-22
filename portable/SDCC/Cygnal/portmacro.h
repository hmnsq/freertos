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

#यदि configUSE_PREEMPTION == 0
    शून्य vTimer2ISR( शून्य ) interrupt 5;
#अन्यथा
    शून्य vTimer2ISR( शून्य ) interrupt 5 _naked;
#endif

शून्य vSerialISR( शून्य ) interrupt 4;


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
#define portCHAR        वर्ण
#define portFLOAT       भिन्न
#define portDOUBLE      भिन्न
#define portLONG        दीर्घ
#define portSHORT       लघु
#define port_थाक_TYPE  uint8_t
#define portBASE_TYPE   वर्ण

प्रकारनिर्देश port_थाक_TYPE थाक_Type_t;
प्रकारनिर्देश चिन्हित वर्ण BaseType_t;
प्रकारनिर्देश अचिन्हित वर्ण UBaseType_t;

#यदि( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकारनिर्देश uint16_t TickType_t;
    #define portMAX_DELAY ( TickType_t ) 0xffff
#अथवायदि ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    प्रकारनिर्देश uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Critical section management. */
#define portENTER_CRITICAL()        _asm        \
                                    थप    ACC \
                                    थप    IE  \
                                    _endasm;    \
                                    EA = 0;

#define portEXIT_CRITICAL()         _asm            \
                                    झिक     ACC     \
                                    _endasm;        \
                                    ACC &= 0x80;    \
                                    IE |= ACC;      \
                                    _asm            \
                                    झिक     ACC     \
                                    _endasm;

#define portDISABLE_INTERRUPTS()    EA = 0;
#define portENABLE_INTERRUPTS()     EA = 1;
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT          1
#define port_थाक_GROWTH            ( 1 )
#define portTICK_PERIOD_MS          ( ( uint32_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Task utilities. */
शून्य vPortYield( शून्य ) _naked;
#define portYIELD() vPortYield();
/*-----------------------------------------------------------*/

#define portNOP()               _asm    \
                                    nop \
                                _endasm;

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters )

#endif /* PORTMACRO_H */
