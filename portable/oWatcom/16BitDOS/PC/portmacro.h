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
    ಬಾಹ್ಯ "C" {
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
#define portCHAR        ವರ್ಣ
#define portFLOAT       ಭಿನ್ನ
#define portDOUBLE      ದ್ವಿಗುಣ
#define portLONG        long
#define portSHORT       ಪೂರ್ಣಾಙ್ಕ
#define port_ರಾಶಿ_TYPE  uint16_t
#define portBASE_TYPE   short

ಪ್ರಕಾರನಿರ್ದೇಶ port_ರಾಶಿ_TYPE ರಾಶಿ_Type_t;
ಪ್ರಕಾರನಿರ್ದೇಶ short BaseType_t;
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned short UBaseType_t;


#ಯದಿ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    ಪ್ರಕಾರನಿರ್ದೇಶ uint16_t TickType_t;
    #define portMAX_DELAY ( TickType_t ) 0xffff
#ನೋಚೇದ್ಯದಿ ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    ಪ್ರಕಾರನಿರ್ದೇಶ uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#ಅನ್ಯಥಾ
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Critical section definitions.  portENTER_CRITICAL() must be defined as a
macro for portable.h to work properly. */
ಶೂನ್ಯ portLOCAL_ENTER_CRITICAL( ಶೂನ್ಯ );
#pragma aux portLOCAL_ENTER_CRITICAL =  "pushf" \
                                        "cli";
#define portENTER_CRITICAL() portLOCAL_ENTER_CRITICAL()

ಶೂನ್ಯ portEXIT_CRITICAL( ಶೂನ್ಯ );
#pragma aux portEXIT_CRITICAL   =       "popf";

ಶೂನ್ಯ portDISABLE_INTERRUPTS( ಶೂನ್ಯ );
#pragma aux portDISABLE_INTERRUPTS =    "cli";

ಶೂನ್ಯ portENABLE_INTERRUPTS( ಶೂನ್ಯ );
#pragma aux portENABLE_INTERRUPTS =     "sti";
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_ರಾಶಿ_GROWTH        ( -1 )
#define port_SWITCH_INT_ಸಂಖ್ಯೆ   0x80
#define portYIELD()             __asm{ ಪೂರ್ಣಾಙ್ಕ port_SWITCH_INT_ಸಂಖ್ಯೆ }
#define portDOS_TICK_RATE       ( 18.20648 )
#define portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portTICKS_PER_DOS_TICK  ( ( uint16_t ) ( ( ( portDOUBLE ) configTICK_RATE_HZ / portDOS_TICK_RATE ) + 0.5 ) )
#define portINITIAL_SW          ( ( port_ರಾಶಿ_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
#define portBYTE_ALIGNMENT      ( 2 )
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#define port_ಒಳಹರಿವು_BYTE( xAddr )             inp( xAddr )
#define portOUTPUT_BYTE( xAddr, uc_ಮೌಲ್ಯ )   outp( xAddr, uc_ಮೌಲ್ಯ )
#define portNOP() __asm{ nop }
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vTaskFunction, pvParameters ) ಶೂನ್ಯ vTaskFunction( ಶೂನ್ಯ *pvParameters )
#define portTASK_FUNCTION( vTaskFunction, pvParameters ) ಶೂನ್ಯ vTaskFunction( ಶೂನ್ಯ *pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */


#endif /* PORTMACRO_H */
