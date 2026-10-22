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

/* Hardware specific includes. */
#अन्तर्भाव "mb91467d.h"

/* Standard includes. */
#अन्तर्भाव <stddef.h>

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


#यदि( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः  == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t             TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Critical section management. */
#यदि config_KERNEL_व्यवधानम्_प्राथमिकता != 30
    #दोषः config_KERNEL_व्यवधानम्_प्राथमिकता (समुच्चयः अन्तर् FreeRTOSConfig.h) must मेलनम् the ILM मानम् समुच्चयः अन्तर् the following पङ्क्तिः - 30 (1Eh) being the स्वभाव.
#यदि_अन्तः
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS() __asm(" STILM #1Eh ")
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS() __asm(" STILM #1Fh ")

#परिभाषय पत्तनम्_ENTER_CRITICAL()    \
    __asm(" ST PS,@-R15 ");     \
    __asm(" ANDCCR #0xef ");    \


#परिभाषय पत्तनम्_EXIT_CRITICAL()     \
    __asm(" LD @R15+,PS ");     \

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#परिभाषय पत्तनम्_राशिः_GROWTH            ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT          4
#परिभाषय पत्तनम्_NOP()                   __asm( " nop " );
/*-----------------------------------------------------------*/

/* portYIELD() uses a SW interrupt */
#परिभाषय पत्तनम्_YIELD()                 __asm( " INT #40H " );

/* portYIELD_FROM_ISR() uses delayed interrupt */
#परिभाषय पत्तनम्_YIELD_FROM_ISR()            DICR_DLYI = 1
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters )

#परिभाषय पत्तनम्_अल्पिष्ठम्_राशिः_आकार config_अल्पिष्ठम्_राशिः_आकार


#यदि_अन्तः /* PORTMACRO_H */
