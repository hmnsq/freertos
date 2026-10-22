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
#define portCHAR        അക്ഷരം
#define portFLOAT       ദശാംശം
#define portDOUBLE      ഇരട്ട
#define portLONG        long
#define portSHORT       പൂർണ്ണസംഖ്യ
#define port_അട്ടി_TYPE  uint16_t
#define portBASE_TYPE   short

തരനിർവചനം port_അട്ടി_TYPE അട്ടി_Type_t;
തരനിർവചനം short BaseType_t;
തരനിർവചനം unsigned short UBaseType_t;


#എങ്കിൽ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    തരനിർവചനം uint16_t TickType_t;
    #define portMAX_DELAY ( TickType_t ) 0xffff
#അല്ലെങ്കിലെങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    തരനിർവചനം uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#അല്ലെങ്കിൽ
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
ബാഹ്യ അസ്ഥിര uint16_t usCriticalNesting;                         \
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
ബാഹ്യ അസ്ഥിര uint16_t usCriticalNesting;                         \
                                                                                \
    എങ്കിൽ( usCriticalNesting > portNO_CRITICAL_SECTION_NESTING )                   \
    {                                                                           \
        /* Decrement the nesting count as we are leaving a critical section. */ \
        usCriticalNesting--;                                                    \
                                                                                \
        /* If the nesting level has reached zero then interrupts should be */   \
        /* re-enabled. */                                                       \
        എങ്കിൽ( usCriticalNesting == portNO_CRITICAL_SECTION_NESTING )              \
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
ബാഹ്യ ശൂന്യം vPortYield( ശൂന്യം );
#define portYIELD() vPortYield()
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT          2
#define port_അട്ടി_GROWTH            ( -1 )
#define portTICK_PERIOD_MS          ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portNOP()
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) ശൂന്യം vFunction( ശൂന്യം *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) ശൂന്യം vFunction( ശൂന്യം *pvParameters ) __toplevel

#എങ്കിൽ configINTERRUPT_EXAMPLE_METHOD == 2

ബാഹ്യ ശൂന്യം vTaskSwitchContext( ശൂന്യം );
#define portYIELD_FROM_ISR( x ) ചെയ്യുക { എങ്കിൽ( x ) vTaskSwitchContext(); } ആകുമ്പോൾ( 0 )

#endif

#endif /* PORTMACRO_H */
