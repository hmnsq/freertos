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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
/* *INDENT-ON* */

/* record stack high address for stack check */
#اگر_تعریف_نشده config_رکورد_پشته_بالا_آدرس
    #تعریف_کن config_رکورد_پشته_بالا_آدرس    1
#پایان_اگر

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
#تعریف_کن پورت_CHAR          حرف
#تعریف_کن پورت_FLOAT         عائم
#تعریف_کن پورت_DOUBLE        مزدوج
#تعریف_کن پورت_LONG          دراز
#تعریف_کن پورت_SHORT         کوتاه
#تعریف_کن پورت_پشته_TYPE    بیعلامت صحيح
#تعریف_کن پورت_پایه_TYPE     پورت_LONG

#اگر_تعریف_نشده Asm
    #تعریف_کن Asm           __asm__ متطاير
#پایان_اگر

/*
 *  normal constants
 */
#اگر_تعریف_نشده عدم
    #تعریف_کن عدم    0           /* invalid pointer */
#پایان_اگر /* NULL */

#اگر_تعریف_نشده true
    #تعریف_کن true    1           /* true */
#پایان_اگر /* true */

#اگر_تعریف_نشده false
    #تعریف_کن false    0          /* false */
#پایان_اگر /* false */

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع دراز             پایه_Type_t;
تعريفنوع بیعلامت دراز    UBaseType_t;

#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر

#تعریف_کن پورت_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
#تعریف_کن پورت_پشته_GROWTH           ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS         ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT         8
#تعریف_کن پورت_NOP()               Asm( "nop_s" );
#تعریف_کن IPM_ENABLE_ALL             1

#تعریف_کن پورت_YIELD_FROM_ISR()    v_پورت_Yield_From_Isr()
#تعریف_کن پورت_YIELD()             v_پورت_Yield()

/* Critical section management. */
#تعریف_کن پورت_DISABLE_INTERRUPTS() \
    {                            \
        Asm( "clri" );           \
        Asm( "" ::: "memory" );  \
    }                            \

#تعریف_کن پورت_ENABLE_INTERRUPTS() \
    {                           \
        Asm( "" ::: "memory" ); \
        Asm( "seti" );          \
    }                           \

خارجي متطاير بیعلامت صحيح ulCriticalNesting;

#تعریف_کن پورت_ENTER_CRITICAL()     \
    {                            \
        پورت_DISABLE_INTERRUPTS() \
        ulCriticalNesting++;     \
    }


#تعریف_کن پورت_EXIT_CRITICAL()                                    \
    {                                                          \
        إذا( ulCriticalNesting > پورت_NO_CRITICAL_NESTING )      \
        {                                                      \
            ulCriticalNesting--;                               \
            إذا( ulCriticalNesting == پورت_NO_CRITICAL_NESTING ) \
            {                                                  \
                پورت_ENABLE_INTERRUPTS()                        \
            }                                                  \
        }                                                      \
    }


#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کن پورت_CONFIGURE_TIMER_FOR_پیاپی_زمان_STATS()              افعل {} طالما( 0 )     /* we use the timer */
#تعریف_کن پورت_ALT_GET_پیاپی_زمان_COUNTER_مقدار( dest )            ( dest = x_Tick_شمار )

#إذا defined( __MW__ )
    خارجي فراغ task_انتها_hook( فراغ * pxTCB );
    #تعریف_کن پورت_CLEAN_به_بالا_TCB( pxTCB )    task_انتها_hook( ( فراغ * ) pxTCB )
#پایان_اگر

فراغ v_پورت_Yield( فراغ );
فراغ v_پورت_Yield_From_Isr( فراغ );

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
