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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

#إذا configUSE_PREEMPTION == 0
    فراغ vTimer2ISR( فراغ ) مداخلت 5;
#وإلا
    فراغ vTimer2ISR( فراغ ) مداخلت 5 _naked;
#جيڪڏهن_پورو

فراغ vSerialISR( فراغ ) مداخلت 4;


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
#وصف_ڪريو پورٽ_CHAR        حرف
#وصف_ڪريو پورٽ_FLOAT       عائم
#وصف_ڪريو پورٽ_DOUBLE      عائم
#وصف_ڪريو پورٽ_LONG        ڊگهو
#وصف_ڪريو پورٽ_SHORT       ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE  uint8_t
#وصف_ڪريو پورٽ_بنياد_TYPE   حرف

تعريفنوع پورٽ_ڍير_TYPE ڍير_Type_t;
تعريفنوع نشانوارو حرف بنياد_Type_t;
تعريفنوع بنانشان حرف UBaseType_t;

#إذا( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ  == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t             TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Critical section management. */
#وصف_ڪريو پورٽ_ENTER_CRITICAL()        _asm        \
                                    ڌڪو    ACC \
                                    ڌڪو    IE  \
                                    _endasm;    \
                                    EA = 0;

#وصف_ڪريو پورٽ_EXIT_CRITICAL()         _asm            \
                                    ڪڍو     ACC     \
                                    _endasm;        \
                                    ACC &= 0x80;    \
                                    IE |= ACC;      \
                                    _asm            \
                                    ڪڍو     ACC     \
                                    _endasm;

#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    EA = 0;
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     EA = 1;
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT          1
#وصف_ڪريو پورٽ_ڍير_GROWTH            ( 1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS          ( ( uint32_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Task utilities. */
فراغ v_پورٽ_Yield( فراغ ) _naked;
#وصف_ڪريو پورٽ_YIELD() v_پورٽ_Yield();
/*-----------------------------------------------------------*/

#وصف_ڪريو پورٽ_NOP()               _asm    \
                                    nop \
                                _endasm;

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )

#جيڪڏهن_پورو /* PORTMACRO_H */
