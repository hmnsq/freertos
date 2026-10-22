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

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
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
#परिभाषय पत्तनम्_CHAR        वर्ण
#परिभाषय पत्तनम्_FLOAT       भिन्न
#परिभाषय पत्तनम्_DOUBLE      द्विगुण
#परिभाषय पत्तनम्_LONG        दीर्घ
#परिभाषय पत्तनम्_SHORT       ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE  uint16_t
#परिभाषय पत्तनम्_आधारः_TYPE   ह्रस्व
#परिभाषय पत्तनम्_POINTER_आकार_TYPE size_t
#परिभाषय SIZE_MAX    ( ( size_t ) -1 )

प्रकारनिर्देश पत्तनम्_राशिः_TYPE राशिः_Type_t;
प्रकारनिर्देश ह्रस्व आधारः_Type_t;
प्रकारनिर्देश अचिह्नित ह्रस्व UBaseType_t;

#यदि( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY ( TickType_t ) 0xffff
/* 16-bit tick type on a 16-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC 1
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः  == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t             TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#परिभाषय पत्तनम्_BYTE_ALIGNMENT          2
#परिभाषय पत्तनम्_राशिः_GROWTH            1
#परिभाषय पत्तनम्_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    समुच्चयः_CPU_IPL( config_KERNEL_व्यवधानम्_प्राथमिकता ); __asm चञ्चल ( "NOP" )
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     समुच्चयः_CPU_IPL( 0 )

/* Note that exiting a critical sectino will set the IPL bits to 0, no matter
what their value was prior to entering the critical section. */
बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य );
बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य );
#परिभाषय पत्तनम्_ENTER_CRITICAL()        v_पत्तनम्_Enter_Critical()
#परिभाषय पत्तनम्_EXIT_CRITICAL()         v_पत्तनम्_Exit_Critical()
/*-----------------------------------------------------------*/

/* Task utilities. */
बाह्य शून्य v_पत्तनम्_Yield( शून्य );
#परिभाषय पत्तनम्_YIELD()             asm चञ्चल ( "CALL _vPortYield            \n"     \
                                                "NOP                      " );
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters )
/*-----------------------------------------------------------*/

/* Required by the kernel aware debugger. */
#यदि_परिभाषितम् __DEBUG
    #परिभाषय पत्तनम्_REMOVE_STATIC_QUALIFIER
#यदि_अन्तः

#परिभाषय पत्तनम्_NOP()               asm चञ्चल ( "NOP" )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
