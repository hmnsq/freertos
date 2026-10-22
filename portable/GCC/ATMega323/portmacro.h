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

#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
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
#घोषणा portCHAR                 अक्षर
#घोषणा portFLOAT                भग्न
#घोषणा portDOUBLE               द्विगुन
#घोषणा portLONG                 दीर्घ
#घोषणा portSHORT                पूर्णांक
#घोषणा port_ढेर_TYPE           uint8_t
#घोषणा portBASE_TYPE            अक्षर

#घोषणा port_POINTER_आकार_TYPE    uint16_t

प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार चिन्हित अक्षर      BaseType_t;
प्रकार अचिन्हित अक्षर    UBaseType_t;

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

/* Critical section management. */
#घोषणा portENTER_CRITICAL()                            \
    यंत्र अस्थिर ( "in      __tmp_reg__, __SREG__" ::); \
    यंत्र अस्थिर ( "cli" ::);                           \
    यंत्र अस्थिर ( "push    __tmp_reg__" ::)

#घोषणा portEXIT_CRITICAL()                   \
    यंत्र अस्थिर ( "pop     __tmp_reg__" ::); \
    यंत्र अस्थिर ( "out     __SREG__, __tmp_reg__" ::)

#घोषणा portDISABLE_INTERRUPTS()    यंत्र अस्थिर ( "cli" ::);
#घोषणा portENABLE_INTERRUPTS()     यंत्र अस्थिर ( "sei" ::);
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#घोषणा port_ढेर_GROWTH      ( -1 )
#घोषणा portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT    1
#घोषणा portNOP()    यंत्र अस्थिर ( "nop" );
/*-----------------------------------------------------------*/

/* Kernel utilities. */
बाह्य व्योम vPortYield( व्योम ) __attribute__( ( naked ) );
#घोषणा portYIELD()    vPortYield()
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
