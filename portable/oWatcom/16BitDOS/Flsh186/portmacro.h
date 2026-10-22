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
    বাহ্য "C" {
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
#define portCHAR        বর্ণ
#define portFLOAT       ভিন্ন
#define portDOUBLE      long
#define portLONG        long
#define portSHORT       পূর্ণাঙ্ক
#define port_স্তূপ_TYPE  uint16_t
#define portBASE_TYPE   short

প্রকারনির্দেশ port_স্তূপ_TYPE স্তূপ_Type_t;
প্রকারনির্দেশ short BaseType_t;
প্রকারনির্দেশ unsigned short UBaseType_t;


#যদি( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        প্রকারনির্দেশ uint16_t TickType_t;
        #define portMAX_DELAY ( TickType_t ) 0xffff
#নোচেদ্যদি ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    প্রকারনির্দেশ uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#অন্যথা
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Critical section management. */
শূন্য portENTER_CRITICAL( শূন্য );
#pragma aux portENTER_CRITICAL = "pushf" \
                                 "cli";

শূন্য portEXIT_CRITICAL( শূন্য );
#pragma aux portEXIT_CRITICAL   = "popf";

শূন্য portDISABLE_INTERRUPTS( শূন্য );
#pragma aux portDISABLE_INTERRUPTS = "cli";

শূন্য portENABLE_INTERRUPTS( শূন্য );
#pragma aux portENABLE_INTERRUPTS = "sti";
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_স্তূপ_GROWTH        ( -1 )
#define port_SWITCH_INT_সংখ্যা   0x80
#define portYIELD()             __asm{ পূর্ণাঙ্ক port_SWITCH_INT_সংখ্যা }
#define portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT      2
#define portINITIAL_SW          ( ( port_স্তূপ_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
#define portNOP()               __asm{ nop }
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#define port_প্রবেশ_BYTE( xAddr )                 inp( xAddr )
#define portOUTPUT_BYTE( xAddr, uc_মান )       outp( xAddr, uc_মান )
#define port_প্রবেশ_WORD( xAddr )                 inpw( xAddr )
#define portOUTPUT_WORD( xAddr, us_মান )       outpw( xAddr, us_মান )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) শূন্য vFunction( শূন্য *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) শূন্য vFunction( শূন্য *pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
