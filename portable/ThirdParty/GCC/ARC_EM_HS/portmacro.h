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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
/* *INDENT-ON* */

/* record stack high address for stack check */
#که_نه_تعریف_شوی config_ریکارډ_ډېری_لوړ_پته
    #تعریف_کړه config_ریکارډ_ډېری_لوړ_پته    1
#د_که_پای

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
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    بینښه صحيح
#تعریف_کړه پورټ_بنسټ_TYPE     پورټ_LONG

#که_نه_تعریف_شوی Asm
    #تعریف_کړه Asm           __asm__ متطاير
#د_که_پای

/*
 *  normal constants
 */
#که_نه_تعریف_شوی عدم
    #تعریف_کړه عدم    0           /* invalid pointer */
#د_که_پای /* NULL */

#که_نه_تعریف_شوی true
    #تعریف_کړه true    1           /* true */
#د_که_پای /* true */

#که_نه_تعریف_شوی false
    #تعریف_کړه false    0          /* false */
#د_که_پای /* false */

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع اوږد             بنسټ_Type_t;
تعريفنوع بینښه اوږد    UBaseType_t;

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای

#تعریف_کړه پورټ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
#تعریف_کړه پورټ_ډېری_GROWTH           ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS         ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT         8
#تعریف_کړه پورټ_NOP()               Asm( "nop_s" );
#تعریف_کړه IPM_ENABLE_ALL             1

#تعریف_کړه پورټ_YIELD_FROM_ISR()    v_پورټ_Yield_From_Isr()
#تعریف_کړه پورټ_YIELD()             v_پورټ_Yield()

/* Critical section management. */
#تعریف_کړه پورټ_DISABLE_INTERRUPTS() \
    {                            \
        Asm( "clri" );           \
        Asm( "" ::: "memory" );  \
    }                            \

#تعریف_کړه پورټ_ENABLE_INTERRUPTS() \
    {                           \
        Asm( "" ::: "memory" ); \
        Asm( "seti" );          \
    }                           \

خارجي متطاير بینښه صحيح ulCriticalNesting;

#تعریف_کړه پورټ_ENTER_CRITICAL()     \
    {                            \
        پورټ_DISABLE_INTERRUPTS() \
        ulCriticalNesting++;     \
    }


#تعریف_کړه پورټ_EXIT_CRITICAL()                                    \
    {                                                          \
        إذا( ulCriticalNesting > پورټ_NO_CRITICAL_NESTING )      \
        {                                                      \
            ulCriticalNesting--;                               \
            إذا( ulCriticalNesting == پورټ_NO_CRITICAL_NESTING ) \
            {                                                  \
                پورټ_ENABLE_INTERRUPTS()                        \
            }                                                  \
        }                                                      \
    }


#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کړه پورټ_CONFIGURE_TIMER_FOR_پرلپسې_وخت_STATS()              افعل {} طالما( 0 )     /* we use the timer */
#تعریف_کړه پورټ_ALT_GET_پرلپسې_وخت_COUNTER_ارزښت( dest )            ( dest = x_Tick_شمېر )

#إذا defined( __MW__ )
    خارجي فراغ task_پای_ټکی_hook( فراغ * pxTCB );
    #تعریف_کړه پورټ_CLEAN_پورته_TCB( pxTCB )    task_پای_ټکی_hook( ( فراغ * ) pxTCB )
#د_که_پای

فراغ v_پورټ_Yield( فراغ );
فراغ v_پورټ_Yield_From_Isr( فراغ );

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
