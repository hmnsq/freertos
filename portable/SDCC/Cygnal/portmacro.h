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

#ifndef PORTMACRO_H
#define PORTMACRO_H

#ಯದಿ configUSE_PREEMPTION == 0
    ಶೂನ್ಯ vTimer2ISR( ಶೂನ್ಯ ) interrupt 5;
#ಅನ್ಯಥಾ
    ಶೂನ್ಯ vTimer2ISR( ಶೂನ್ಯ ) interrupt 5 _naked;
#endif

ಶೂನ್ಯ vSerialISR( ಶೂನ್ಯ ) interrupt 4;


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
#define portCHAR        ವರ್ಣ
#define portFLOAT       ಭಿನ್ನ
#define portDOUBLE      ಭಿನ್ನ
#define portLONG        long
#define portSHORT       short
#define port_ರಾಶಿ_TYPE  uint8_t
#define portBASE_TYPE   ವರ್ಣ

ಪ್ರಕಾರನಿರ್ದೇಶ port_ರಾಶಿ_TYPE ರಾಶಿ_Type_t;
ಪ್ರಕಾರನಿರ್ದೇಶ signed ವರ್ಣ BaseType_t;
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned ವರ್ಣ UBaseType_t;

#ಯದಿ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    ಪ್ರಕಾರನಿರ್ದೇಶ uint16_t TickType_t;
    #define portMAX_DELAY ( TickType_t ) 0xffff
#ನೋಚೇದ್ಯದಿ ( configTICK_TYPE_WIDTH_IN_BITS  == TICK_TYPE_WIDTH_32_BITS )
    ಪ್ರಕಾರನಿರ್ದೇಶ uint32_t             TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#ಅನ್ಯಥಾ
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Critical section management. */
#define portENTER_CRITICAL()        _asm        \
                                    ತಳ್ಳು    ACC \
                                    ತಳ್ಳು    IE  \
                                    _endasm;    \
                                    EA = 0;

#define portEXIT_CRITICAL()         _asm            \
                                    ತೆಗೆ     ACC     \
                                    _endasm;        \
                                    ACC &= 0x80;    \
                                    IE |= ACC;      \
                                    _asm            \
                                    ತೆಗೆ     ACC     \
                                    _endasm;

#define portDISABLE_INTERRUPTS()    EA = 0;
#define portENABLE_INTERRUPTS()     EA = 1;
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT          1
#define port_ರಾಶಿ_GROWTH            ( 1 )
#define portTICK_PERIOD_MS          ( ( uint32_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Task utilities. */
ಶೂನ್ಯ vPortYield( ಶೂನ್ಯ ) _naked;
#define portYIELD() vPortYield();
/*-----------------------------------------------------------*/

#define portNOP()               _asm    \
                                    nop \
                                _endasm;

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) ಶೂನ್ಯ vFunction( ಶೂನ್ಯ *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) ಶೂನ್ಯ vFunction( ಶೂನ್ಯ *pvParameters )

#endif /* PORTMACRO_H */
