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

#यदि_अपरिभाषितम् __PORTMACRO_H__
#परिभाषय __PORTMACRO_H__

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
#परिभाषय पत्तनम्_SHORT       ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE  uint32_t
#परिभाषय पत्तनम्_आधारः_TYPE   दीर्घ

प्रकारनिर्देश पत्तनम्_राशिः_TYPE राशिः_Type_t;
प्रकारनिर्देश दीर्घ आधारः_Type_t;
प्रकारनिर्देश अचिह्नित दीर्घ UBaseType_t;

#यदि (config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः)
    प्रकारनिर्देश uint16_t TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY (TickType_t) 0xFFFF
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY (TickType_t) 0xFFFFFFFFF

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC 1
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः


/* Architecture specifics. */
#परिभाषय पत्तनम्_राशिः_GROWTH    (-1)
#परिभाषय पत्तनम्_TICK_PERIOD_MS    ((TickType_t) 1000 / config_TICK_दरः_HZ)
#परिभाषय पत्तनम्_BYTE_ALIGNMENT  8

/* Critical section handling. */
बाह्य शून्य v_पत्तनम्_Enter_Critical(शून्य);
बाह्य शून्य v_पत्तनम्_Exit_Critical(शून्य);
#परिभाषय पत्तनम्_ENTER_CRITICAL()        v_पत्तनम्_Enter_Critical()
#परिभाषय पत्तनम्_EXIT_CRITICAL()         v_पत्तनम्_Exit_Critical()
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    asm( " CPSID I" )
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     asm( " CPSIE I" )

/* Scheduler utilities. */
#निर्देशः SWI_ALIAS( v_पत्तनम्_Yield, 0 )
बाह्य शून्य v_पत्तनम्_Yield( शून्य );
#परिभाषय पत्तनम्_YIELD()                 v_पत्तनम्_Yield()
#परिभाषय पत्तनम्_SYS_SSIR1_REG           ( * ( ( चञ्चल uint32_t * ) 0xFFFFFFB0 ) )
#परिभाषय पत्तनम्_SYS_SSIR1_SSKEY         ( 0x7500UL )
#परिभाषय पत्तनम्_YIELD_WITHIN_API()      { पत्तनम्_SYS_SSIR1_REG = पत्तनम्_SYS_SSIR1_SSKEY;  asm( " DSB " ); asm( " ISB " ); }
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )     कुरु { यदि( x != pdFALSE ) { पत्तनम्_SYS_SSIR1_REG = पत्तनम्_SYS_SSIR1_SSKEY;  ( शून्य ) पत्तनम्_SYS_SSIR1_REG; } } यावत्( 0 )

#यदि_अपरिभाषितम् config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION
    #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION 1
#यदि_अन्तः

/* Architecture specific optimisations. */
#यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #यदि( configMAX_PRIORITIES > 32 )
        #दोषः config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION can only be समुच्चयः गन्तव्यम् 1 when configMAX_PRIORITIES is less than or equal गन्तव्यम् 32.  It is very rare that a system requires अधिकम् than 10 गन्तव्यम् 15 difference priorities as tasks that share a प्राथमिकता will time खण्डिका.
    #यदि_अन्तः

    /* Store/clear the ready priorities in a bit map. */
    #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
    #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

    /*-----------------------------------------------------------*/

    #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities ) ux_शिखरम्_प्राथमिकता = ( 31 - __clz( ( uxReadyPriorities ) ) )

#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION(vFunction, pvParameters)       शून्य vFunction(शून्य *pvParameters)
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO(vFunction, pvParameters) शून्य vFunction(शून्य *pvParameters)

#यदि_अन्तः /* __PORTMACRO_H__ */
