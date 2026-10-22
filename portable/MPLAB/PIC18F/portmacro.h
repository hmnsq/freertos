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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

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
#تعریف_کن پورت_CHAR        حرف
#تعریف_کن پورت_FLOAT       عائم
#تعریف_کن پورت_DOUBLE      مزدوج
#تعریف_کن پورت_LONG        دراز
#تعریف_کن پورت_SHORT       صحيح
#تعریف_کن پورت_پشته_TYPE  uint8_t
#تعریف_کن پورت_پایه_TYPE   حرف

تعريفنوع پورت_پشته_TYPE پشته_Type_t;
تعريفنوع علامتدار حرف پایه_Type_t;
تعريفنوع بیعلامت حرف UBaseType_t;

#إذا( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کن پورت_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها  == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t             TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کن پورت_BYTE_ALIGNMENT          1
#تعریف_کن پورت_GLOBAL_INT_ENABLE_بیت   0x80
#تعریف_کن پورت_پشته_GROWTH            1
#تعریف_کن پورت_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#تعریف_کن پورت_DISABLE_INTERRUPTS()    INTCONbits.GIEH = 0;
#تعریف_کن پورت_ENABLE_INTERRUPTS()     INTCONbits.GIEH = 1;

/* Push the INTCON register onto the stack, then disable interrupts. */
#تعریف_کن پورت_ENTER_CRITICAL()        POSTINC1 = INTCON;              \
                                    INTCONbits.GIEH = 0;

/* Retrieve the INTCON register from the stack, and enable interrupts
if they were saved as being enabled.  Don't modify any other bits
within the INTCON register as these may have legitimately have been
modified within the critical region. */
#تعریف_کن پورت_EXIT_CRITICAL()         _asm                                    \
                                        MOVF    POSTDEC1, 1, 0              \
                                    _endasm                                 \
                                    إذا( INDF1 & پورت_GLOBAL_INT_ENABLE_بیت ) \
                                    {                                       \
                                        پورت_ENABLE_INTERRUPTS();            \
                                    }
/*-----------------------------------------------------------*/

/* Task utilities. */
خارجي فراغ v_پورت_Yield( فراغ );
#تعریف_کن پورت_YIELD()             v_پورت_Yield()
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
/*-----------------------------------------------------------*/

/* Required by the kernel aware debugger. */
#اگر_تعریف_شده __DEBUG
    #تعریف_کن پورت_REMOVE_STATIC_QUALIFIER
#پایان_اگر


#تعریف_کن پورت_NOP()               _asm    \
                                    NOP \
                                _endasm

#پایان_اگر /* PORTMACRO_H */
