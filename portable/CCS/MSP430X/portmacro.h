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

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

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
#परिभाषय पत्तनम्_CHAR        वर्ण
#परिभाषय पत्तनम्_FLOAT       भिन्न
#परिभाषय पत्तनम्_DOUBLE      द्विगुण
#परिभाषय पत्तनम्_LONG        दीर्घ
#परिभाषय पत्तनम्_SHORT       पूर्णाङ्क
#परिभाषय पत्तनम्_आधारः_TYPE   पत्तनम्_SHORT

/* The stack type changes depending on the data model. */
#यदि_परिभाषितम् __LARGE_DATA_MODEL__
    #परिभाषय पत्तनम्_राशिः_TYPE uint32_t
#अन्यथा
    #परिभाषय पत्तनम्_राशिः_TYPE uint16_t
    #परिभाषय पत्तनम्_POINTER_आकार_TYPE uint16_t
#यदि_अन्तः

प्रकारनिर्देश पत्तनम्_राशिः_TYPE राशिः_Type_t;
प्रकारनिर्देश ह्रस्व आधारः_Type_t;
प्रकारनिर्देश अचिह्नित ह्रस्व UBaseType_t;

#यदि( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः

/*-----------------------------------------------------------*/

/* Interrupt control macros. */
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    __asm चञ्चल ( " DINT\n" " NOP" )
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     __asm चञ्चल ( " NOP\n" " EINT\n" " NOP" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
#परिभाषय पत्तनम्_NO_CRITICAL_SECTION_NESTING     ( ( uint16_t ) 0 )

#परिभाषय पत्तनम्_ENTER_CRITICAL()                                                    \
{                                                                               \
बाह्य चञ्चल uint16_t usCriticalNesting;                                     \
                                                                                \
    पत्तनम्_DISABLE_INTERRUPTS();                                                   \
                                                                                \
    /* Now interrupts are disabled usCriticalNesting can be accessed */         \
    /* directly.  Increment ulCriticalNesting to keep a count of how many */    \
    /* times portENTER_CRITICAL() has been called. */                           \
    usCriticalNesting++;                                                        \
}

#परिभाषय पत्तनम्_EXIT_CRITICAL()                                                     \
{                                                                               \
बाह्य चञ्चल uint16_t usCriticalNesting;                                     \
                                                                                \
    यदि( usCriticalNesting > पत्तनम्_NO_CRITICAL_SECTION_NESTING )                   \
    {                                                                           \
        /* Decrement the nesting count as we are leaving a critical section. */ \
        usCriticalNesting--;                                                    \
                                                                                \
        /* If the nesting level has reached zero then interrupts should be */   \
        /* re-enabled. */                                                       \
        यदि( usCriticalNesting == पत्तनम्_NO_CRITICAL_SECTION_NESTING )              \
        {                                                                       \
            पत्तनम्_ENABLE_INTERRUPTS();                                            \
        }                                                                       \
    }                                                                           \
}
/*-----------------------------------------------------------*/

/* Task utilities. */

/*
 * Manual context switch called by portYIELD or taskYIELD.
 */
बाह्य शून्य v_पत्तनम्_Yield( शून्य );
#परिभाषय पत्तनम्_YIELD() v_पत्तनम्_Yield()
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#परिभाषय पत्तनम्_BYTE_ALIGNMENT          2
#परिभाषय पत्तनम्_राशिः_GROWTH            ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_NOP()                   __asm चञ्चल ( " NOP" )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters )

बाह्य शून्य vTaskSwitchContext( शून्य );
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x ) कुरु { यदि( x ) v_पत्तनम्_Yield(); } यावत्( 0 )

शून्य v_Application_सज्जता_Timer_व्यवधानम्( शून्य );

/* sizeof( int ) != sizeof( long ) so a full printf() library is required if
run time stats information is to be displayed. */
#परिभाषय पत्तनम्_LU_PRINTF_SPECIFIER_REQUIRED

#यदि_अन्तः /* PORTMACRO_H */
