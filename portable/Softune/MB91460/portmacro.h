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

/* Hardware specific includes. */
#ضمن "mb91467d.h"

/* Standard includes. */
#ضمن <stddef.h>

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
#define portDOUBLE      مزدوج
#define portLONG        long
#define portSHORT       short
#define port_مكدس_TYPE  uint32_t
#define portBASE_TYPE   long

تعريفنوع port_مكدس_TYPE مكدس_Type_t;
تعريفنوع long BaseType_t;
تعريفنوع unsigned long UBaseType_t;


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
#إذا configKERNEL_INTERRUPT_PRIORITY != 30
    #error configKERNEL_INTERRUPT_PRIORITY (set in FreeRTOSConfig.h) must match the ILM قيمة set in the following سطر - 30 (1Eh) being the افتراضي.
#endif
#define portDISABLE_INTERRUPTS() __asm(" STILM #1Eh ")
#define portENABLE_INTERRUPTS() __asm(" STILM #1Fh ")

#define portENTER_CRITICAL()    \
    __asm(" ST PS,@-R15 ");     \
    __asm(" ANDCCR #0xef ");    \


#define portEXIT_CRITICAL()     \
    __asm(" LD @R15+,PS ");     \

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_مكدس_GROWTH            ( -1 )
#define portTICK_PERIOD_MS          ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT          4
#define portNOP()                   __asm( " nop " );
/*-----------------------------------------------------------*/

/* portYIELD() uses a SW interrupt */
#define portYIELD()                 __asm( " INT #40H " );

/* portYIELD_FROM_ISR() uses delayed interrupt */
#define portYIELD_FROM_ISR()            DICR_DLYI = 1
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )

#define port_MINIMAL_مكدس_SIZE config_MINIMAL_مكدس_SIZE


#endif /* PORTMACRO_H */
