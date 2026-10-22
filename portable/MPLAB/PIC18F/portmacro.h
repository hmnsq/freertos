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

#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

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
#تعریف_کرو پورٹ_CHAR        حرف
#تعریف_کرو پورٹ_FLOAT       عائم
#تعریف_کرو پورٹ_DOUBLE      مزدوج
#تعریف_کرو پورٹ_LONG        لما
#تعریف_کرو پورٹ_SHORT       صحيح
#تعریف_کرو پورٹ_ڈھیر_TYPE  uint8_t
#تعریف_کرو پورٹ_ادھار_TYPE   حرف

تعريفنوع پورٹ_ڈھیر_TYPE ڈھیر_Type_t;
تعريفنوع نشانیوالا حرف ادھار_Type_t;
تعريفنوع بنانشانی حرف UBaseType_t;

#إذا( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ  == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t             TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT          1
#تعریف_کرو پورٹ_GLOBAL_INT_ENABLE_ثنائی_ہندسہ   0x80
#تعریف_کرو پورٹ_ڈھیر_GROWTH            1
#تعریف_کرو پورٹ_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    INTCONbits.GIEH = 0;
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     INTCONbits.GIEH = 1;

/* Push the INTCON register onto the stack, then disable interrupts. */
#تعریف_کرو پورٹ_ENTER_CRITICAL()        POSTINC1 = INTCON;              \
                                    INTCONbits.GIEH = 0;

/* Retrieve the INTCON register from the stack, and enable interrupts
if they were saved as being enabled.  Don't modify any other bits
within the INTCON register as these may have legitimately have been
modified within the critical region. */
#تعریف_کرو پورٹ_EXIT_CRITICAL()         _asm                                    \
                                        MOVF    POSTDEC1, 1, 0              \
                                    _endasm                                 \
                                    إذا( INDF1 & پورٹ_GLOBAL_INT_ENABLE_ثنائی_ہندسہ ) \
                                    {                                       \
                                        پورٹ_ENABLE_INTERRUPTS();            \
                                    }
/*-----------------------------------------------------------*/

/* Task utilities. */
خارجي فراغ v_پورٹ_Yield( فراغ );
#تعریف_کرو پورٹ_YIELD()             v_پورٹ_Yield()
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
/*-----------------------------------------------------------*/

/* Required by the kernel aware debugger. */
#جے_تعریف_شدہ __DEBUG
    #تعریف_کرو پورٹ_REMOVE_STATIC_QUALIFIER
#جے_انت


#تعریف_کرو پورٹ_NOP()               _asm    \
                                    NOP \
                                _endasm

#جے_انت /* PORTMACRO_H */
