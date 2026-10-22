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
    بیرونی "C" {
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
#define portCHAR        نویسه
#define portFLOAT       اعشاری
#define portDOUBLE      long
#define portLONG        long
#define portSHORT       صحیح
#define port_پشته_TYPE  uint16_t
#define portBASE_TYPE   short

تعریفنوع port_پشته_TYPE پشته_Type_t;
تعریفنوع short BaseType_t;
تعریفنوع unsigned short UBaseType_t;


#اگر( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        تعریفنوع uint16_t TickType_t;
        #define portMAX_DELAY ( TickType_t ) 0xffff
#وگرنهاگر ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    تعریفنوع uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#وگرنه
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Critical section management. */
تهی portENTER_CRITICAL( تهی );
#pragma aux portENTER_CRITICAL = "pushf" \
                                 "cli";

تهی portEXIT_CRITICAL( تهی );
#pragma aux portEXIT_CRITICAL   = "popf";

تهی portDISABLE_INTERRUPTS( تهی );
#pragma aux portDISABLE_INTERRUPTS = "cli";

تهی portENABLE_INTERRUPTS( تهی );
#pragma aux portENABLE_INTERRUPTS = "sti";
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_پشته_GROWTH        ( -1 )
#define port_SWITCH_INT_عدد   0x80
#define portYIELD()             __asm{ صحیح port_SWITCH_INT_عدد }
#define portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT      2
#define portINITIAL_SW          ( ( port_پشته_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
#define portNOP()               __asm{ nop }
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#define port_درون_داد_BYTE( xAddr )                 inp( xAddr )
#define portOUTPUT_BYTE( xAddr, uc_مقدار )       outp( xAddr, uc_مقدار )
#define port_درون_داد_WORD( xAddr )                 inpw( xAddr )
#define portOUTPUT_WORD( xAddr, us_مقدار )       outpw( xAddr, us_مقدار )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) تهی vFunction( تهی *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) تهی vFunction( تهی *pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
