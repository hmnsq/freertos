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

/*
 * Changes from V1.2.3
 *
 + portCPU_CLOCK_HZ definition changed to 8MHz base 10, previously it
 +    base 16.
 */

#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    বাহ্যিক "C" {
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
#define portCHAR                 অক্ষর
#define portFLOAT                দশমিক
#define portDOUBLE               দ্বিগুণ
#define portLONG                 long
#define portSHORT                পূর্ণসংখ্যা
#define port_স্তূপ_TYPE           uint8_t
#define portBASE_TYPE            অক্ষর

#define port_POINTER_আকার_TYPE    uint16_t

প্রকারলেখ port_স্তূপ_TYPE   স্তূপ_Type_t;
প্রকারলেখ signed অক্ষর      BaseType_t;
প্রকারলেখ unsigned অক্ষর    UBaseType_t;

#যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    প্রকারলেখ uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#নতুবা_যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    প্রকারলেখ uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#অন্যথা
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Critical section management. */
#define portENTER_CRITICAL()                            \
    asm অস্থির ( "in      __tmp_reg__, __SREG__" ::); \
    asm অস্থির ( "cli" ::);                           \
    asm অস্থির ( "push    __tmp_reg__" ::)

#define portEXIT_CRITICAL()                   \
    asm অস্থির ( "pop     __tmp_reg__" ::); \
    asm অস্থির ( "out     __SREG__, __tmp_reg__" ::)

#define portDISABLE_INTERRUPTS()    asm অস্থির ( "cli" ::);
#define portENABLE_INTERRUPTS()     asm অস্থির ( "sei" ::);
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_স্তূপ_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT    1
#define portNOP()    asm অস্থির ( "nop" );
/*-----------------------------------------------------------*/

/* Kernel utilities. */
বাহ্যিক শূন্য vPortYield( শূন্য ) __attribute__( ( naked ) );
#define portYIELD()    vPortYield()
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    শূন্য vFunction( শূন্য * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          শূন্য vFunction( শূন্য * pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
