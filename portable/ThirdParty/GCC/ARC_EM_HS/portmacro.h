/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Synopsys, Inc. or its affiliates.  All Rights Reserved.
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

/* record stack high address for stack check */
#अगर_अघोषित config_RECORD_ढेर_ऊपरी_ADDRESS
    #घोषणा config_RECORD_ढेर_ऊपरी_ADDRESS    1
#पूर्ण_अगर

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
#घोषणा portCHAR          अक्षर
#घोषणा portFLOAT         भग्न
#घोषणा portDOUBLE        द्विगुन
#घोषणा portLONG          दीर्घ
#घोषणा portSHORT         लघु
#घोषणा port_ढेर_TYPE    अचिन्हित पूर्णांक
#घोषणा portBASE_TYPE     portLONG

#अगर_अघोषित Asm
    #घोषणा Asm           __asm__ अस्थिर
#पूर्ण_अगर

/*
 *  normal constants
 */
#अगर_अघोषित शून्य
    #घोषणा शून्य    0           /* invalid pointer */
#पूर्ण_अगर /* NULL */

#अगर_अघोषित true
    #घोषणा true    1           /* true */
#पूर्ण_अगर /* true */

#अगर_अघोषित false
    #घोषणा false    0          /* false */
#पूर्ण_अगर /* false */

प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार दीर्घ             BaseType_t;
प्रकार अचिन्हित दीर्घ    UBaseType_t;

#अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t     TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t     TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर

#घोषणा portNO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
#घोषणा port_ढेर_GROWTH           ( -1 )
#घोषणा portTICK_PERIOD_MS         ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT         8
#घोषणा portNOP()               Asm( "nop_s" );
#घोषणा IPM_ENABLE_ALL             1

#घोषणा portYIELD_FROM_ISR()    vPortYieldFromIsr()
#घोषणा portYIELD()             vPortYield()

/* Critical section management. */
#घोषणा portDISABLE_INTERRUPTS() \
    {                            \
        Asm( "clri" );           \
        Asm( "" ::: "memory" );  \
    }                            \

#घोषणा portENABLE_INTERRUPTS() \
    {                           \
        Asm( "" ::: "memory" ); \
        Asm( "seti" );          \
    }                           \

बाह्य अस्थिर अचिन्हित पूर्णांक ulCriticalNesting;

#घोषणा portENTER_CRITICAL()     \
    {                            \
        portDISABLE_INTERRUPTS() \
        ulCriticalNesting++;     \
    }


#घोषणा portEXIT_CRITICAL()                                    \
    {                                                          \
        अगर( ulCriticalNesting > portNO_CRITICAL_NESTING )      \
        {                                                      \
            ulCriticalNesting--;                               \
            अगर( ulCriticalNesting == portNO_CRITICAL_NESTING ) \
            {                                                  \
                portENABLE_INTERRUPTS()                        \
            }                                                  \
        }                                                      \
    }


#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

#घोषणा portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()              करो {} जबतक( 0 )     /* we use the timer */
#घोषणा port_ALT_GET_RUN_TIME_गणक_मूल्य( dest )            ( dest = x_Tick_गिनती )

#अगर defined( __MW__ )
    बाह्य व्योम task_end_hook( व्योम * pxTCB );
    #घोषणा portCLEAN_UP_TCB( pxTCB )    task_end_hook( ( व्योम * ) pxTCB )
#पूर्ण_अगर

व्योम vPortYield( व्योम );
व्योम vPortYieldFromIsr( व्योम );

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
