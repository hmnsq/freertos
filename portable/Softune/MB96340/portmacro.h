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

/* Standard includes. */
#समावेश <stddef.h>

/* Constants denoting the available memory models.  These are used within
FreeRTOSConfig.h to set the configMEMMODEL value. */
#घोषणा portSMALL     0
#घोषणा portMEDIUM    1
#घोषणा portCOMPACT   2
#घोषणा portLARGE     3


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
#घोषणा portDOUBLE      द्विगुन
#घोषणा portLONG        दीर्घ
#घोषणा portSHORT       लघु
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

/* Critical section handling. */
#अगर configKERNEL_INTERRUPT_PRIORITY != 6
    #त्रुटि configKERNEL_INTERRUPT_PRIORITY (set in FreeRTOSConfig.h) must match the ILM मूल्य set in the following पंक्ति - #06H being the शेष.
#पूर्ण_अगर
#घोषणा portDISABLE_INTERRUPTS()    __asm(" MOV ILM, #06h ")
#घोषणा portENABLE_INTERRUPTS()     __asm(" MOV ILM, #07h ")

#घोषणा portENTER_CRITICAL()                                \
        {   __asm(" PUSHW PS ");                            \
            portDISABLE_INTERRUPTS();                       \
        }

#घोषणा portEXIT_CRITICAL()                                 \
        {   __asm(" POPW PS ");                             \
        }

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#घोषणा port_ढेर_GROWTH            ( -1 )
#घोषणा portTICK_PERIOD_MS          ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT          2
#घोषणा portNOP()                   __asm( " NOP " );
/*-----------------------------------------------------------*/

/* portYIELD() uses SW interrupt */
#घोषणा portYIELD()                 __asm( " INT #122 " );

/* portYIELD_FROM_ISR() uses delayed interrupt */
#घोषणा portYIELD_FROM_ISR()         __asm( " SETB  03A4H:0 " );
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters ) व्योम vFunction( व्योम *pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters ) व्योम vFunction( व्योम *pvParameters )

#घोषणा port_MINIMAL_ढेर_आकार config_MINIMAL_ढेर_आकार


#पूर्ण_अगर /* PORTMACRO_H */
