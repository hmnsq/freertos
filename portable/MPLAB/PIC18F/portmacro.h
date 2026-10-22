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
#परिभाषय पत्तनम्_राशिः_TYPE  uint8_t
#परिभाषय पत्तनम्_आधारः_TYPE   वर्ण

प्रकारनिर्देश पत्तनम्_राशिः_TYPE राशिः_Type_t;
प्रकारनिर्देश चिह्नित वर्ण आधारः_Type_t;
प्रकारनिर्देश अचिह्नित वर्ण UBaseType_t;

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

/* Hardware specifics. */
#परिभाषय पत्तनम्_BYTE_ALIGNMENT          1
#परिभाषय पत्तनम्_GLOBAL_INT_ENABLE_BIT   0x80
#परिभाषय पत्तनम्_राशिः_GROWTH            1
#परिभाषय पत्तनम्_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    INTCONbits.GIEH = 0;
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     INTCONbits.GIEH = 1;

/* Push the INTCON register onto the stack, then disable interrupts. */
#परिभाषय पत्तनम्_ENTER_CRITICAL()        POSTINC1 = INTCON;              \
                                    INTCONbits.GIEH = 0;

/* Retrieve the INTCON register from the stack, and enable interrupts
if they were saved as being enabled.  Don't modify any other bits
within the INTCON register as these may have legitimately have been
modified within the critical region. */
#परिभाषय पत्तनम्_EXIT_CRITICAL()         _asm                                    \
                                        MOVF    POSTDEC1, 1, 0              \
                                    _endasm                                 \
                                    यदि( INDF1 & पत्तनम्_GLOBAL_INT_ENABLE_BIT ) \
                                    {                                       \
                                        पत्तनम्_ENABLE_INTERRUPTS();            \
                                    }
/*-----------------------------------------------------------*/

/* Task utilities. */
बाह्य शून्य v_पत्तनम्_Yield( शून्य );
#परिभाषय पत्तनम्_YIELD()             v_पत्तनम्_Yield()
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters )
/*-----------------------------------------------------------*/

/* Required by the kernel aware debugger. */
#यदि_परिभाषितम् __DEBUG
    #परिभाषय पत्तनम्_REMOVE_STATIC_QUALIFIER
#यदि_अन्तः


#परिभाषय पत्तनम्_NOP()               _asm    \
                                    NOP \
                                _endasm

#यदि_अन्तः /* PORTMACRO_H */
