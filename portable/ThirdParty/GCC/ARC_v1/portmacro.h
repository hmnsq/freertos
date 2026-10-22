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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H
#ضمن "embARC.h"

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
/* *INDENT-ON* */

/* record stack high address for stack check */
#جيڪڏهن_وصف_نه_ٿيل config_رڪارڊ_ڍير_مٿاهون_پتو
    #وصف_ڪريو config_رڪارڊ_ڍير_مٿاهون_پتو    1
#جيڪڏهن_پورو

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
#وصف_ڪريو پورٽ_CHAR          حرف
#وصف_ڪريو پورٽ_FLOAT         عائم
#وصف_ڪريو پورٽ_DOUBLE        مزدوج
#وصف_ڪريو پورٽ_LONG          ڊگهو
#وصف_ڪريو پورٽ_SHORT         ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE    بنانشان صحيح
#وصف_ڪريو پورٽ_بنياد_TYPE     پورٽ_LONG

#جيڪڏهن_وصف_نه_ٿيل Asm
    #وصف_ڪريو Asm           __asm__ متطاير
#جيڪڏهن_پورو

/*
 *  normal constants
 */
#جيڪڏهن_وصف_نه_ٿيل عدم
    #وصف_ڪريو عدم    0           /* invalid pointer */
#جيڪڏهن_پورو /* NULL */

#جيڪڏهن_وصف_نه_ٿيل true
    #وصف_ڪريو true    1           /* true */
#جيڪڏهن_پورو /* true */

#جيڪڏهن_وصف_نه_ٿيل false
    #وصف_ڪريو false    0          /* false */
#جيڪڏهن_پورو /* false */

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع ڊگهو             بنياد_Type_t;
تعريفنوع بنانشان ڊگهو    UBaseType_t;

#إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
#وصف_ڪريو پورٽ_ڍير_GROWTH           ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS         ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT         8
#وصف_ڪريو پورٽ_NOP()               Asm( "nop_s" );
#وصف_ڪريو IPM_ENABLE_ALL             1

#وصف_ڪريو پورٽ_YIELD_FROM_ISR()    v_پورٽ_Yield_From_Isr()
#وصف_ڪريو پورٽ_YIELD()             v_پورٽ_Yield()

/* Critical section management. */
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS() \
    {                            \
        arc_تالو();              \
    }                            \

#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS() \
    {                           \
        arc_unlock();           \
    }                           \

خارجي متطاير بنانشان صحيح ulCriticalNesting;

#وصف_ڪريو پورٽ_ENTER_CRITICAL()     \
    {                            \
        پورٽ_DISABLE_INTERRUPTS() \
        ulCriticalNesting++;     \
    }


#وصف_ڪريو پورٽ_EXIT_CRITICAL()                                    \
    {                                                          \
        إذا( ulCriticalNesting > پورٽ_NO_CRITICAL_NESTING )      \
        {                                                      \
            ulCriticalNesting--;                               \
            إذا( ulCriticalNesting == پورٽ_NO_CRITICAL_NESTING ) \
            {                                                  \
                پورٽ_ENABLE_INTERRUPTS()                        \
            }                                                  \
        }                                                      \
    }


#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#وصف_ڪريو پورٽ_CONFIGURE_TIMER_FOR_لاڳيتو_وقت_STATS()              افعل {} طالما( 0 )     /* we use the timer */
#وصف_ڪريو پورٽ_ALT_GET_لاڳيتو_وقت_COUNTER_قدر( dest )            ( dest = x_Tick_ڳڻپ )

فراغ v_پورٽ_Yield( فراغ );
فراغ v_پورٽ_Yield_From_Isr( فراغ );

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
