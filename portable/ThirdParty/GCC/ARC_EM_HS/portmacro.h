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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

/* record stack high address for stack check */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਰਿਕਾਰਡ_ਢੇਰ_ਉੱਚਾ_ਪਤਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਰਿਕਾਰਡ_ਢੇਰ_ਉੱਚਾ_ਪਤਾ    1
#ਜੇ_ਅੰਤ

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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਪੋਰਟ_LONG

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ Asm
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Asm           __asm__ ਅਸਥਿਰ
#ਜੇ_ਅੰਤ

/*
 *  normal constants
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਨਿਰਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਨਿਰਾ    0           /* invalid pointer */
#ਜੇ_ਅੰਤ /* NULL */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ true
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ true    1           /* true */
#ਜੇ_ਅੰਤ /* true */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ false
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ false    0          /* false */
#ਜੇ_ਅੰਤ /* false */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE   ਢੇਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਲੰਮਾ             ਅਧਾਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ    UBaseType_t;

#ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) 0xffff
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH           ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS         ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT         8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()               Asm( "nop_s" );
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IPM_ENABLE_ALL             1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR()    v_ਪੋਰਟ_Yield_From_Isr()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()             v_ਪੋਰਟ_Yield()

/* Critical section management. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS() \
    {                            \
        Asm( "clri" );           \
        Asm( "" ::: "memory" );  \
    }                            \

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS() \
    {                           \
        Asm( "" ::: "memory" ); \
        Asm( "seti" );          \
    }                           \

ਬਾਹਰੀ ਅਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ulCriticalNesting;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()     \
    {                            \
        ਪੋਰਟ_DISABLE_INTERRUPTS() \
        ulCriticalNesting++;     \
    }


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                                    \
    {                                                          \
        ਜੇ( ulCriticalNesting > ਪੋਰਟ_NO_CRITICAL_NESTING )      \
        {                                                      \
            ulCriticalNesting--;                               \
            ਜੇ( ulCriticalNesting == ਪੋਰਟ_NO_CRITICAL_NESTING ) \
            {                                                  \
                ਪੋਰਟ_ENABLE_INTERRUPTS()                        \
            }                                                  \
        }                                                      \
    }


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONFIGURE_TIMER_FOR_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS()              ਕਰੋ {} ਜਦੋਂ( 0 )     /* we use the timer */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ALT_GET_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_ਮੁੱਲ( dest )            ( dest = x_Tick_ਗਿਣਤੀ )

#ਜੇ defined( __MW__ )
    ਬਾਹਰੀ ਖਾਲੀ task_ਸਿਰਾ_hook( ਖਾਲੀ * pxTCB );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAN_ਉੱਪਰ_TCB( pxTCB )    task_ਸਿਰਾ_hook( ( ਖਾਲੀ * ) pxTCB )
#ਜੇ_ਅੰਤ

ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ );
ਖਾਲੀ v_ਪੋਰਟ_Yield_From_Isr( ਖਾਲੀ );

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
