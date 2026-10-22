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

#define portCHAR                 वर्ण
#define portFLOAT                भिन्न
#define portDOUBLE               द्विगुण
#define portLONG                 दीर्घ
#define portSHORT                लघु
#define port_ढेर_TYPE           uint16_t
#define portBASE_TYPE            लघु
#define portPOINTER_SIZE_TYPE    uint16_t

प्रकारनिर्देश port_ढेर_TYPE   ढेर_Type_t;
प्रकारनिर्देश लघु            BaseType_t;
प्रकारनिर्देश अचिन्हित लघु   UBaseType_t;

#यदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकारनिर्देश uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#नोचेद्यदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकारनिर्देश uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#अन्यथा
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
#define portDISABLE_INTERRUPTS()    __asm चञ्चल ( "DI" )
#define portENABLE_INTERRUPTS()     __asm चञ्चल ( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#define portNO_CRITICAL_SECTION_NESTING    ( ( अचिन्हित लघु ) 0 )

#define portENTER_CRITICAL()                                                      \
    {                                                                             \
        बाह्य चञ्चल uint16_t usCriticalNesting;                               \
                                                                                  \
        portDISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

#define portEXIT_CRITICAL()                                                         \
    {                                                                               \
        बाह्य चञ्चल uint16_t usCriticalNesting;                                 \
                                                                                    \
        यदि( usCriticalNesting > portNO_CRITICAL_SECTION_NESTING )                   \
        {                                                                           \
            /* Decrement the nesting count as we are leaving a critical section. */ \
            usCriticalNesting--;                                                    \
                                                                                    \
            /* If the nesting level has reached zero then interrupts should be */   \
            /* re-enabled. */                                                       \
            यदि( usCriticalNesting == portNO_CRITICAL_SECTION_NESTING )              \
            {                                                                       \
                portENABLE_INTERRUPTS();                                            \
            }                                                                       \
        }                                                                           \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
#define portYIELD()                                       __asm चञ्चल ( "BRK" )
#ifndef configREQUIRE_ASM_ISR_WRAPPER
    #define configREQUIRE_ASM_ISR_WRAPPER    1
#endif
#यदि( configREQUIRE_ASM_ISR_WRAPPER == 1 )
    /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
     * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
    #define portYIELD_FROM_ISR( xHigherPriorityTaskWoken )    कुरु { यदि( xHigherPriorityTaskWoken != pdFALSE ) vTaskSwitchContext(); } यावत्( 0 )
#अन्यथा
    /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
     * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
    #define portYIELD_FROM_ISR( xHigherPriorityTaskWoken )    कुरु { यदि( xHigherPriorityTaskWoken != pdFALSE ) portYIELD(); } यावत्( 0 )
#endif
#define portNOP()                                         __asm चञ्चल ( "NOP" )
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT    2
#define port_ढेर_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

#endif /* PORTMACRO_H */
