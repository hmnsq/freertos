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
#परिभाषय पत्तनम्_DOUBLE      दीर्घ
#परिभाषय पत्तनम्_LONG        दीर्घ
#परिभाषय पत्तनम्_SHORT       पूर्णाङ्क
#परिभाषय पत्तनम्_राशिः_TYPE  uint16_t
#परिभाषय पत्तनम्_आधारः_TYPE   ह्रस्व

प्रकारनिर्देश पत्तनम्_राशिः_TYPE राशिः_Type_t;
प्रकारनिर्देश ह्रस्व आधारः_Type_t;
प्रकारनिर्देश अचिह्नित ह्रस्व UBaseType_t;


प्रकारनिर्देश शून्य ( __interrupt __far *pxISR )();

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

/* Critical section handling. */
#परिभाषय पत्तनम्_ENTER_CRITICAL()            __asm{ pushf }  \
                                        __asm{ cli   }  \

#परिभाषय पत्तनम्_EXIT_CRITICAL()             __asm{ popf }

#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()        __asm{ cli }

#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()         __asm{ sti }
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#परिभाषय पत्तनम्_NOP()                       __asm{ nop }
#परिभाषय पत्तनम्_राशिः_GROWTH                ( -1 )
#परिभाषय पत्तनम्_SWITCH_INT_सङ्ख्या           0x80
#परिभाषय पत्तनम्_YIELD()                     __asm{ पूर्णाङ्क पत्तनम्_SWITCH_INT_सङ्ख्या }
#परिभाषय पत्तनम्_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT              2
#परिभाषय पत्तनम्_INITIAL_SW                  ( ( पत्तनम्_राशिः_TYPE ) 0x0202 )   /* Start the tasks with interrupts enabled. */
/*-----------------------------------------------------------*/

/* Compiler specifics. */
#परिभाषय पत्तनम्_निवेशः_BYTE( xAddr )             inp( xAddr )
#परिभाषय पत्तनम्_OUTPUT_BYTE( xAddr, uc_मानम् )   outp( xAddr, uc_मानम् )
#परिभाषय पत्तनम्_निवेशः_WORD( xAddr )             inpw( xAddr )
#परिभाषय पत्तनम्_OUTPUT_WORD( xAddr, us_मानम् )   outpw( xAddr, us_मानम् )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vTaskFunction, vParameters ) शून्य vTaskFunction( शून्य *pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vTaskFunction, vParameters ) शून्य vTaskFunction( शून्य *pvParameters )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
