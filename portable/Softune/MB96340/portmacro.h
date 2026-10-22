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

/* Standard includes. */
#অন্তর্ভাব <stddef.h>

/* Constants denoting the available memory models.  These are used within
FreeRTOSConfig.h to set the configMEMMODEL value. */
#define portSMALL     0
#define portMEDIUM    1
#define portCOMPACT   2
#define portLARGE     3


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
#define portDOUBLE      দ্বিগুণ
#define portLONG        long
#define portSHORT       short
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

/* Critical section handling. */
#যদি configKERNEL_INTERRUPT_PRIORITY != 6
    #error configKERNEL_INTERRUPT_PRIORITY (set in FreeRTOSConfig.h) must match the ILM মান set in the following সারি - #06H being the স্বভাব.
#endif
#define portDISABLE_INTERRUPTS()    __asm(" MOV ILM, #06h ")
#define portENABLE_INTERRUPTS()     __asm(" MOV ILM, #07h ")

#define portENTER_CRITICAL()                                \
        {   __asm(" PUSHW PS ");                            \
            portDISABLE_INTERRUPTS();                       \
        }

#define portEXIT_CRITICAL()                                 \
        {   __asm(" POPW PS ");                             \
        }

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_স্তূপ_GROWTH            ( -1 )
#define portTICK_PERIOD_MS          ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT          2
#define portNOP()                   __asm( " NOP " );
/*-----------------------------------------------------------*/

/* portYIELD() uses SW interrupt */
#define portYIELD()                 __asm( " INT #122 " );

/* portYIELD_FROM_ISR() uses delayed interrupt */
#define portYIELD_FROM_ISR()         __asm( " SETB  03A4H:0 " );
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) শূন্য vFunction( শূন্য *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) শূন্য vFunction( শূন্য *pvParameters )

#define port_MINIMAL_স্তূপ_SIZE config_MINIMAL_স্তূপ_SIZE


#endif /* PORTMACRO_H */
