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

#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

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

#घोषणा portCHAR                 अक्षर
#घोषणा portFLOAT                भग्न
#घोषणा portDOUBLE               द्विगुन
#घोषणा portLONG                 दीर्घ
#घोषणा portSHORT                लघु
#घोषणा port_ढेर_TYPE           uint16_t
#घोषणा portBASE_TYPE            लघु
#घोषणा port_POINTER_आकार_TYPE    uint16_t

प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार लघु            BaseType_t;
प्रकार अचिन्हित लघु   UBaseType_t;

#अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t     TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t     TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
#घोषणा portDISABLE_INTERRUPTS()    __asm अस्थिर ( "DI" )
#घोषणा portENABLE_INTERRUPTS()     __asm अस्थिर ( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#घोषणा portNO_CRITICAL_SECTION_NESTING    ( ( अचिन्हित लघु ) 0 )

#घोषणा portENTER_CRITICAL()                                                      \
    {                                                                             \
        बाह्य अस्थिर uint16_t usCriticalNesting;                               \
                                                                                  \
        portDISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

#घोषणा portEXIT_CRITICAL()                                                         \
    {                                                                               \
        बाह्य अस्थिर uint16_t usCriticalNesting;                                 \
                                                                                    \
        अगर( usCriticalNesting > portNO_CRITICAL_SECTION_NESTING )                   \
        {                                                                           \
            /* Decrement the nesting count as we are leaving a critical section. */ \
            usCriticalNesting--;                                                    \
                                                                                    \
            /* If the nesting level has reached zero then interrupts should be */   \
            /* re-enabled. */                                                       \
            अगर( usCriticalNesting == portNO_CRITICAL_SECTION_NESTING )              \
            {                                                                       \
                portENABLE_INTERRUPTS();                                            \
            }                                                                       \
        }                                                                           \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
#घोषणा portYIELD()                                       __asm अस्थिर ( "BRK" )
#अगर_अघोषित configREQUIRE_ASM_ISR_WRAPPER
    #घोषणा configREQUIRE_ASM_ISR_WRAPPER    1
#पूर्ण_अगर
#अगर( configREQUIRE_ASM_ISR_WRAPPER == 1 )
    /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
     * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
    #घोषणा portYIELD_FROM_ISR( xHigherPriorityTaskWoken )    करो { अगर( xHigherPriorityTaskWoken != pdFALSE ) vTaskSwitchContext(); } जबतक( 0 )
#अन्यथा
    /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
     * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
    #घोषणा portYIELD_FROM_ISR( xHigherPriorityTaskWoken )    करो { अगर( xHigherPriorityTaskWoken != pdFALSE ) portYIELD(); } जबतक( 0 )
#पूर्ण_अगर
#घोषणा portNOP()                                         __asm अस्थिर ( "NOP" )
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#घोषणा portBYTE_ALIGNMENT    2
#घोषणा port_ढेर_GROWTH      ( -1 )
#घोषणा portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

#पूर्ण_अगर /* PORTMACRO_H */
