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

#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
/* *INDENT-ON* */

/* record stack high address for stack check */
#جے_بنا_تعریف config_ریکارڈ_ڈھیر_بلند_پتہ
    #تعریف_کرو config_ریکارڈ_ڈھیر_بلند_پتہ    1
#جے_انت

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
#تعریف_کرو پورٹ_FLOAT         عائم
#تعریف_کرو پورٹ_DOUBLE        مزدوج
#تعریف_کرو پورٹ_LONG          لما
#تعریف_کرو پورٹ_SHORT         چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE    بنانشانی صحيح
#تعریف_کرو پورٹ_ادھار_TYPE     پورٹ_LONG

#جے_بنا_تعریف Asm
    #تعریف_کرو Asm           __asm__ متطاير
#جے_انت

/*
 *  normal constants
 */
#جے_بنا_تعریف عدم
    #تعریف_کرو عدم    0           /* invalid pointer */
#جے_انت /* NULL */

#جے_بنا_تعریف true
    #تعریف_کرو true    1           /* true */
#جے_انت /* true */

#جے_بنا_تعریف false
    #تعریف_کرو false    0          /* false */
#جے_انت /* false */

تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع لما             ادھار_Type_t;
تعريفنوع بنانشانی لما    UBaseType_t;

#إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت

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

خارجي متطاير بنانشانی صحيح ulCriticalNesting;

#تعریف_کرو پورٹ_ENTER_CRITICAL()     \
    {                            \
        پورٹ_DISABLE_INTERRUPTS() \
        ulCriticalNesting++;     \
    }


#تعریف_کرو پورٹ_EXIT_CRITICAL()                                    \
    {                                                          \
        إذا( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )      \
        {                                                      \
            ulCriticalNesting--;                               \
            إذا( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING ) \
            {                                                  \
                پورٹ_ENABLE_INTERRUPTS()                        \
            }                                                  \
        }                                                      \
    }


#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کرو پورٹ_CONFIGURE_TIMER_FOR_لگاتار_ویلا_STATS()              افعل {} طالما( 0 )     /* we use the timer */
#تعریف_کرو پورٹ_ALT_GET_لگاتار_ویلا_COUNTER_قدر( dest )            ( dest = x_Tick_گنتی )

#إذا defined( __MW__ )
    خارجي فراغ task_سرا_hook( فراغ * pxTCB );
    #تعریف_کرو پورٹ_CLEAN_اتے_TCB( pxTCB )    task_سرا_hook( ( فراغ * ) pxTCB )
#جے_انت

فراغ v_پورٹ_Yield( فراغ );
فراغ v_پورٹ_Yield_From_Isr( فراغ );

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
