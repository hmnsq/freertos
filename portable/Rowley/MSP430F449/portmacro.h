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
#define portCHAR        অক্ষর
#define portFLOAT       দশমিক
#define portDOUBLE      দ্বিগুণ
#define portLONG        long
#define portSHORT       পূর্ণসংখ্যা
#define port_স্তূপ_TYPE  uint16_t
#define portBASE_TYPE   short

প্রকারলেখ port_স্তূপ_TYPE স্তূপ_Type_t;
প্রকারলেখ short BaseType_t;
প্রকারলেখ unsigned short UBaseType_t;


#যদি( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    প্রকারলেখ uint16_t TickType_t;
    #define portMAX_DELAY ( TickType_t ) 0xffff
#নতুবা_যদি ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    প্রকারলেখ uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#অন্যথা
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif

/*-----------------------------------------------------------*/

/* Interrupt control macros. */
#define portDISABLE_INTERRUPTS()    _DINT(); _NOP()
#define portENABLE_INTERRUPTS()     _EINT();
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#define portNO_CRITICAL_SECTION_NESTING     ( ( uint16_t ) 0 )

#define portENTER_CRITICAL()                                                    \
{                                                                               \
বাহ্যিক অস্থির uint16_t usCriticalNesting;                         \
                                                                                \
    portDISABLE_INTERRUPTS();                                                   \
                                                                                \
    /* Now interrupts are disabled usCriticalNesting can be accessed */         \
    /* directly.  Increment ulCriticalNesting to keep a count of how many */    \
    /* times portENTER_CRITICAL() has been called. */                           \
    usCriticalNesting++;                                                        \
}

#define portEXIT_CRITICAL()                                                     \
{                                                                               \
বাহ্যিক অস্থির uint16_t usCriticalNesting;                         \
                                                                                \
    যদি( usCriticalNesting > portNO_CRITICAL_SECTION_NESTING )                   \
    {                                                                           \
        /* Decrement the nesting count as we are leaving a critical section. */ \
        usCriticalNesting--;                                                    \
                                                                                \
        /* If the nesting level has reached zero then interrupts should be */   \
        /* re-enabled. */                                                       \
        যদি( usCriticalNesting == portNO_CRITICAL_SECTION_NESTING )              \
        {                                                                       \
            portENABLE_INTERRUPTS();                                            \
        }                                                                       \
    }                                                                           \
}
/*-----------------------------------------------------------*/

/* Task utilities. */

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
বাহ্যিক শূন্য vPortYield( শূন্য );
#define portYIELD() vPortYield()
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT          2
#define port_স্তূপ_GROWTH            ( -1 )
#define portTICK_PERIOD_MS          ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portNOP()
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) শূন্য vFunction( শূন্য *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) শূন্য vFunction( শূন্য *pvParameters ) __toplevel

#যদি configINTERRUPT_EXAMPLE_METHOD == 2

বাহ্যিক শূন্য vTaskSwitchContext( শূন্য );
#define portYIELD_FROM_ISR( x ) করো { যদি( x ) vTaskSwitchContext(); } যখন( 0 )

#endif

#endif /* PORTMACRO_H */
