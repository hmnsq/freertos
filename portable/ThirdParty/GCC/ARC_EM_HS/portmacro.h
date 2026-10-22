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

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
/* *INDENT-ON* */

/* record stack high address for stack check */
#यदि_अपरिभाषितम् config_लेखः_राशिः_उच्चः_स्थानाङ्कः
    #परिभाषय config_लेखः_राशिः_उच्चः_स्थानाङ्कः    1
#यदि_अन्तः

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
#परिभाषय पत्तनम्_CHAR          वर्ण
#परिभाषय पत्तनम्_FLOAT         भिन्न
#परिभाषय पत्तनम्_DOUBLE        द्विगुण
#परिभाषय पत्तनम्_LONG          दीर्घ
#परिभाषय पत्तनम्_SHORT         ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE    अचिह्नित पूर्णाङ्क
#परिभाषय पत्तनम्_आधारः_TYPE     पत्तनम्_LONG

#यदि_अपरिभाषितम् Asm
    #परिभाषय Asm           __asm__ चञ्चल
#यदि_अन्तः

/*
 *  normal constants
 */
#यदि_अपरिभाषितम् रिक्त
    #परिभाषय रिक्त    0           /* invalid pointer */
#यदि_अन्तः /* NULL */

#यदि_अपरिभाषितम् true
    #परिभाषय true    1           /* true */
#यदि_अन्तः /* true */

#यदि_अपरिभाषितम् false
    #परिभाषय false    0          /* false */
#यदि_अन्तः /* false */

प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
प्रकारनिर्देश दीर्घ             आधारः_Type_t;
प्रकारनिर्देश अचिह्नित दीर्घ    UBaseType_t;

#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः

#परिभाषय पत्तनम्_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
#परिभाषय पत्तनम्_राशिः_GROWTH           ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS         ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT         8
#परिभाषय पत्तनम्_NOP()               Asm( "nop_s" );
#परिभाषय IPM_ENABLE_ALL             1

#परिभाषय पत्तनम्_YIELD_FROM_ISR()    v_पत्तनम्_Yield_From_Isr()
#परिभाषय पत्तनम्_YIELD()             v_पत्तनम्_Yield()

/* Critical section management. */
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS() \
    {                            \
        Asm( "clri" );           \
        Asm( "" ::: "memory" );  \
    }                            \

#परिभाषय पत्तनम्_ENABLE_INTERRUPTS() \
    {                           \
        Asm( "" ::: "memory" ); \
        Asm( "seti" );          \
    }                           \

बाह्य चञ्चल अचिह्नित पूर्णाङ्क ulCriticalNesting;

#परिभाषय पत्तनम्_ENTER_CRITICAL()     \
    {                            \
        पत्तनम्_DISABLE_INTERRUPTS() \
        ulCriticalNesting++;     \
    }


#परिभाषय पत्तनम्_EXIT_CRITICAL()                                    \
    {                                                          \
        यदि( ulCriticalNesting > पत्तनम्_NO_CRITICAL_NESTING )      \
        {                                                      \
            ulCriticalNesting--;                               \
            यदि( ulCriticalNesting == पत्तनम्_NO_CRITICAL_NESTING ) \
            {                                                  \
                पत्तनम्_ENABLE_INTERRUPTS()                        \
            }                                                  \
        }                                                      \
    }


#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

#परिभाषय पत्तनम्_CONFIGURE_TIMER_FOR_सततम्_TIME_STATS()              कुरु {} यावत्( 0 )     /* we use the timer */
#परिभाषय पत्तनम्_ALT_GET_सततम्_TIME_गणक_मानम्( dest )            ( dest = x_Tick_गणनम् )

#यदि defined( __MW__ )
    बाह्य शून्य task_अन्तः_hook( शून्य * pxTCB );
    #परिभाषय पत्तनम्_CLEAN_ऊर्ध्वम्_TCB( pxTCB )    task_अन्तः_hook( ( शून्य * ) pxTCB )
#यदि_अन्तः

शून्य v_पत्तनम्_Yield( शून्य );
शून्य v_पत्तनम्_Yield_From_Isr( शून्य );

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
