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
#घोषणा portCHAR        अक्षर
#घोषणा portFLOAT       भग्न
#घोषणा portDOUBLE      दीर्घ
#घोषणा portLONG        दीर्घ
#घोषणा portSHORT       पूर्णांक
#घोषणा port_ढेर_TYPE  uint16_t
#घोषणा portBASE_TYPE   लघु

प्रकार port_ढेर_TYPE ढेर_Type_t;
प्रकार लघु BaseType_t;
प्रकार अचिन्हित लघु UBaseType_t;


#अगर( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        प्रकार uint16_t TickType_t;
        #घोषणा portMAX_DELAY ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t             TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Critical section management. */
व्योम portENTER_CRITICAL( व्योम );
#आशय aux portENTER_CRITICAL = "pushf" \
                                 "cli";

व्योम portEXIT_CRITICAL( व्योम );
#आशय aux portEXIT_CRITICAL   = "popf";

व्योम portDISABLE_INTERRUPTS( व्योम );
#आशय aux portDISABLE_INTERRUPTS = "cli";

व्योम portENABLE_INTERRUPTS( व्योम );
#आशय aux portENABLE_INTERRUPTS = "sti";
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#घोषणा port_ढेर_GROWTH        ( -1 )
#घोषणा port_SWITCH_INT_संख्या   0x80
#घोषणा portYIELD()             __asm{ पूर्णांक port_SWITCH_INT_संख्या }
#घोषणा portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT      2
#घोषणा portINITIAL_SW          ( ( port_ढेर_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
#घोषणा portNOP()               __asm{ nop }
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#घोषणा port_निवेश_BYTE( xAddr )                 inp( xAddr )
#घोषणा portOUTPUT_BYTE( xAddr, uc_मूल्य )       outp( xAddr, uc_मूल्य )
#घोषणा port_निवेश_WORD( xAddr )                 inpw( xAddr )
#घोषणा portOUTPUT_WORD( xAddr, us_मूल्य )       outpw( xAddr, us_मूल्य )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters ) व्योम vFunction( व्योम *pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters ) व्योम vFunction( व्योम *pvParameters )

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
