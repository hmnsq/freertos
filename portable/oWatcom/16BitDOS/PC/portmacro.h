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
    बाह्य "C" {
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
#define portCHAR        वर्ण
#define portFLOAT       भिन्न
#define portDOUBLE      द्विगुण
#define portLONG        long
#define portSHORT       पूर्णाङ्क
#define port_चळत_TYPE  uint16_t
#define portBASE_TYPE   short

प्रकारनिर्देश port_चळत_TYPE चळत_Type_t;
प्रकारनिर्देश short BaseType_t;
प्रकारनिर्देश unsigned short UBaseType_t;


#यदि( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकारनिर्देश uint16_t TickType_t;
    #define portMAX_DELAY ( TickType_t ) 0xffff
#नोचेद्यदि ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    प्रकारनिर्देश uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Critical section definitions.  portENTER_CRITICAL() must be defined as a
macro for portable.h to work properly. */
शून्य portLOCAL_ENTER_CRITICAL( शून्य );
#pragma aux portLOCAL_ENTER_CRITICAL =  "pushf" \
                                        "cli";
#define portENTER_CRITICAL() portLOCAL_ENTER_CRITICAL()

शून्य portEXIT_CRITICAL( शून्य );
#pragma aux portEXIT_CRITICAL   =       "popf";

शून्य portDISABLE_INTERRUPTS( शून्य );
#pragma aux portDISABLE_INTERRUPTS =    "cli";

शून्य portENABLE_INTERRUPTS( शून्य );
#pragma aux portENABLE_INTERRUPTS =     "sti";
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_चळत_GROWTH        ( -1 )
#define port_SWITCH_INT_संख्या   0x80
#define portYIELD()             __asm{ पूर्णाङ्क port_SWITCH_INT_संख्या }
#define portDOS_TICK_RATE       ( 18.20648 )
#define portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portTICKS_PER_DOS_TICK  ( ( uint16_t ) ( ( ( portDOUBLE ) configTICK_RATE_HZ / portDOS_TICK_RATE ) + 0.5 ) )
#define portINITIAL_SW          ( ( port_चळत_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
#define portBYTE_ALIGNMENT      ( 2 )
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#define port_आदान_BYTE( xAddr )             inp( xAddr )
#define portOUTPUT_BYTE( xAddr, uc_मूल्य )   outp( xAddr, uc_मूल्य )
#define portNOP() __asm{ nop }
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vTaskFunction, pvParameters ) शून्य vTaskFunction( शून्य *pvParameters )
#define portTASK_FUNCTION( vTaskFunction, pvParameters ) शून्य vTaskFunction( शून्य *pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */


#endif /* PORTMACRO_H */
