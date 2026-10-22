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

#अगर_अघोषित __PORTMACRO_H__
#घोषणा __PORTMACRO_H__

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
#घोषणा port_ढेर_TYPE  uint32_t
#घोषणा portBASE_TYPE   दीर्घ

प्रकार port_ढेर_TYPE ढेर_Type_t;
प्रकार दीर्घ BaseType_t;
प्रकार अचिन्हित दीर्घ UBaseType_t;

#अगर (configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS)
    प्रकार uint16_t TickType_t;
    #घोषणा portMAX_DELAY (TickType_t) 0xFFFF
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t TickType_t;
    #घोषणा portMAX_DELAY (TickType_t) 0xFFFFFFFFF

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #घोषणा portTICK_TYPE_IS_ATOMIC 1
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर


/* Architecture specifics. */
#घोषणा port_ढेर_GROWTH    (-1)
#घोषणा portTICK_PERIOD_MS    ((TickType_t) 1000 / configTICK_RATE_HZ)
#घोषणा portBYTE_ALIGNMENT  8

/* Critical section handling. */
बाह्य व्योम vPortEnterCritical(व्योम);
बाह्य व्योम vPortExitCritical(व्योम);
#घोषणा portENTER_CRITICAL()        vPortEnterCritical()
#घोषणा portEXIT_CRITICAL()         vPortExitCritical()
#घोषणा portDISABLE_INTERRUPTS()    यंत्र( " CPSID I" )
#घोषणा portENABLE_INTERRUPTS()     यंत्र( " CPSIE I" )

/* Scheduler utilities. */
#आशय SWI_ALIAS( vPortYield, 0 )
बाह्य व्योम vPortYield( व्योम );
#घोषणा portYIELD()                 vPortYield()
#घोषणा portSYS_SSIR1_REG           ( * ( ( अस्थिर uint32_t * ) 0xFFFFFFB0 ) )
#घोषणा portSYS_SSIR1_SSKEY         ( 0x7500UL )
#घोषणा portYIELD_WITHIN_API()      { portSYS_SSIR1_REG = portSYS_SSIR1_SSKEY;  यंत्र( " DSB " ); यंत्र( " ISB " ); }
#घोषणा portYIELD_FROM_ISR( x )     करो { अगर( x != pdFALSE ) { portSYS_SSIR1_REG = portSYS_SSIR1_SSKEY;  ( व्योम ) portSYS_SSIR1_REG; } } जबतक( 0 )

#अगर_अघोषित configUSE_PORT_OPTIMISED_TASK_SELECTION
    #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#पूर्ण_अगर

/* Architecture specific optimisations. */
#अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #अगर( configMAX_PRIORITIES > 32 )
        #त्रुटि configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 difference priorities as tasks that share a priority will समय slice.
    #पूर्ण_अगर

    /* Store/clear the ready priorities in a bit map. */
    #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

    /*-----------------------------------------------------------*/

    #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities ) ux_शीर्ष_Priority = ( 31 - __clz( ( uxReadyPriorities ) ) )

#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/* Task function macros as described on the FreeRTOS.org WEB site. */
#घोषणा portTASK_FUNCTION(vFunction, pvParameters)       व्योम vFunction(व्योम *pvParameters)
#घोषणा portTASK_FUNCTION_PROTO(vFunction, pvParameters) व्योम vFunction(व्योम *pvParameters)

#पूर्ण_अगर /* __PORTMACRO_H__ */
