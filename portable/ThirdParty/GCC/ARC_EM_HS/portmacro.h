/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Synopsys, Inc. or its affiliates.  All Rights Reserved.
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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
/* *INDENT-ON* */

/* record stack high address for stack check */
#اگر_غیر_تعریف_شدہ config_ریکارڈ_ڈھیر_بلند_پتہ
    #تعریف_کرو config_ریکارڈ_ڈھیر_بلند_پتہ    1
#اگر_ختم

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
#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         اعشاری
#تعریف_کرو پورٹ_DOUBLE        دوہرا
#تعریف_کرو پورٹ_LONG          طویل
#تعریف_کرو پورٹ_SHORT         مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE    غیرعلامتی صحیح
#تعریف_کرو پورٹ_بنیاد_TYPE     پورٹ_LONG

#اگر_غیر_تعریف_شدہ Asm
    #تعریف_کرو Asm           __asm__ متلون
#اگر_ختم

/*
 *  normal constants
 */
#اگر_غیر_تعریف_شدہ تہی
    #تعریف_کرو تہی    0           /* invalid pointer */
#اگر_ختم /* NULL */

#اگر_غیر_تعریف_شدہ true
    #تعریف_کرو true    1           /* true */
#اگر_ختم /* true */

#اگر_غیر_تعریف_شدہ false
    #تعریف_کرو false    0          /* false */
#اگر_ختم /* false */

قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف طویل             بنیاد_Type_t;
قسمتعریف غیرعلامتی طویل    UBaseType_t;

#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم

#تعریف_کرو پورٹ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
#تعریف_کرو پورٹ_ڈھیر_GROWTH           ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS         ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT         8
#تعریف_کرو پورٹ_NOP()               Asm( "nop_s" );
#تعریف_کرو IPM_ENABLE_ALL             1

#تعریف_کرو پورٹ_YIELD_FROM_ISR()    v_پورٹ_Yield_From_Isr()
#تعریف_کرو پورٹ_YIELD()             v_پورٹ_Yield()

/* Critical section management. */
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS() \
    {                            \
        Asm( "clri" );           \
        Asm( "" ::: "memory" );  \
    }                            \

#تعریف_کرو پورٹ_ENABLE_INTERRUPTS() \
    {                           \
        Asm( "" ::: "memory" ); \
        Asm( "seti" );          \
    }                           \

خارجی متلون غیرعلامتی صحیح ulCriticalNesting;

#تعریف_کرو پورٹ_ENTER_CRITICAL()     \
    {                            \
        پورٹ_DISABLE_INTERRUPTS() \
        ulCriticalNesting++;     \
    }


#تعریف_کرو پورٹ_EXIT_CRITICAL()                                    \
    {                                                          \
        اگر( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )      \
        {                                                      \
            ulCriticalNesting--;                               \
            اگر( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING ) \
            {                                                  \
                پورٹ_ENABLE_INTERRUPTS()                        \
            }                                                  \
        }                                                      \
    }


#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

#تعریف_کرو پورٹ_CONFIGURE_TIMER_FOR_تسلسل_وقت_STATS()              کرو {} جب( 0 )     /* we use the timer */
#تعریف_کرو پورٹ_ALT_GET_تسلسل_وقت_شمار_قدر( dest )            ( dest = x_Tick_گنتی )

#اگر defined( __MW__ )
    خارجی خالی task_انتہا_hook( خالی * pxTCB );
    #تعریف_کرو پورٹ_CLEAN_اوپر_TCB( pxTCB )    task_انتہا_hook( ( خالی * ) pxTCB )
#اگر_ختم

خالی v_پورٹ_Yield( خالی );
خالی v_پورٹ_Yield_From_Isr( خالی );

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
