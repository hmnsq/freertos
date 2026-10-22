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
    બાહ્ય "C" {
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
#define portCHAR        અક્ષર
#define portFLOAT       દશાંશ
#define portDOUBLE      દ્વિગુણ
#define portLONG        long
#define portSHORT       પૂર્ણાંક
#define port_ઢગલો_TYPE  uint16_t
#define portBASE_TYPE   short

પ્રકારવ્યાખ્યા port_ઢગલો_TYPE ઢગલો_Type_t;
પ્રકારવ્યાખ્યા short BaseType_t;
પ્રકારવ્યાખ્યા unsigned short UBaseType_t;


#જો( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    પ્રકારવ્યાખ્યા uint16_t TickType_t;
    #define portMAX_DELAY ( TickType_t ) 0xffff
#અથવાજો ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    પ્રકારવ્યાખ્યા uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#નહીંતર
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Critical section definitions.  portENTER_CRITICAL() must be defined as a
macro for portable.h to work properly. */
શૂન્ય portLOCAL_ENTER_CRITICAL( શૂન્ય );
#pragma aux portLOCAL_ENTER_CRITICAL =  "pushf" \
                                        "cli";
#define portENTER_CRITICAL() portLOCAL_ENTER_CRITICAL()

શૂન્ય portEXIT_CRITICAL( શૂન્ય );
#pragma aux portEXIT_CRITICAL   =       "popf";

શૂન્ય portDISABLE_INTERRUPTS( શૂન્ય );
#pragma aux portDISABLE_INTERRUPTS =    "cli";

શૂન્ય portENABLE_INTERRUPTS( શૂન્ય );
#pragma aux portENABLE_INTERRUPTS =     "sti";
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_ઢગલો_GROWTH        ( -1 )
#define port_SWITCH_INT_સંખ્યા   0x80
#define portYIELD()             __asm{ પૂર્ણાંક port_SWITCH_INT_સંખ્યા }
#define portDOS_TICK_RATE       ( 18.20648 )
#define portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portTICKS_PER_DOS_TICK  ( ( uint16_t ) ( ( ( portDOUBLE ) configTICK_RATE_HZ / portDOS_TICK_RATE ) + 0.5 ) )
#define portINITIAL_SW          ( ( port_ઢગલો_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
#define portBYTE_ALIGNMENT      ( 2 )
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#define port_આગત_BYTE( xAddr )             inp( xAddr )
#define portOUTPUT_BYTE( xAddr, uc_કિંમત )   outp( xAddr, uc_કિંમત )
#define portNOP() __asm{ nop }
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vTaskFunction, pvParameters ) શૂન્ય vTaskFunction( શૂન્ય *pvParameters )
#define portTASK_FUNCTION( vTaskFunction, pvParameters ) શૂન્ય vTaskFunction( શૂન્ય *pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */


#endif /* PORTMACRO_H */
