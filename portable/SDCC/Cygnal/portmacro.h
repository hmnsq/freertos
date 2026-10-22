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

#إذا configUSE_PREEMPTION == 0
    فراغ vTimer2ISR( فراغ ) interrupt 5;
#وإلا
    فراغ vTimer2ISR( فراغ ) interrupt 5 _naked;
#endif

فراغ vSerialISR( فراغ ) interrupt 4;


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
#define portDOUBLE      عائم
#define portLONG        long
#define portSHORT       short
#define port_تيندنن_TYPE  uint8_t
#define portBASE_TYPE   حرف

تعريفنوع port_تيندنن_TYPE تيندنن_Type_t;
تعريفنوع signed حرف BaseType_t;
تعريفنوع unsigned حرف UBaseType_t;

#إذا( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    تعريفنوع uint16_t TickType_t;
    #define portMAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    تعريفنوع uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Critical section management. */
#define portENTER_CRITICAL()        _asm        \
                                    تولق    ACC \
                                    تولق    IE  \
                                    _endasm;    \
                                    EA = 0;

#define portEXIT_CRITICAL()         _asm            \
                                    کلوار     ACC     \
                                    _endasm;        \
                                    ACC &= 0x80;    \
                                    IE |= ACC;      \
                                    _asm            \
                                    کلوار     ACC     \
                                    _endasm;

#define portDISABLE_INTERRUPTS()    EA = 0;
#define portENABLE_INTERRUPTS()     EA = 1;
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT          1
#define port_تيندنن_GROWTH            ( 1 )
#define portTICK_PERIOD_MS          ( ( uint32_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Task utilities. */
فراغ vPortYield( فراغ ) _naked;
#define portYIELD() vPortYield();
/*-----------------------------------------------------------*/

#define portNOP()               _asm    \
                                    nop \
                                _endasm;

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )

#endif /* PORTMACRO_H */
