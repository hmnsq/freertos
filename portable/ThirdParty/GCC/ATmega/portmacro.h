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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
/* *INDENT-ON* */

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

#ضمن <avr/wdt.h>

/* Type definitions. */
#تعریف_کړه پورټ_CHAR                 حرف
#تعریف_کړه پورټ_FLOAT                عائم
#تعریف_کړه پورټ_DOUBLE               مزدوج
#تعریف_کړه پورټ_LONG                 اوږد
#تعریف_کړه پورټ_SHORT                صحيح

#تعریف_کړه پورټ_اشاره_ګر_اندازه_TYPE    uint16_t

تعريفنوع uint8_t        ډېری_Type_t;
تعريفنوع int8_t         بنسټ_Type_t;
تعريفنوع uint8_t        UBaseType_t;

#إذا config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه
    تعريفنوع uint16_t   TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t   TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/* Critical section management. */

#تعریف_کړه پورټ_ENTER_CRITICAL()                        \
    __asm__ __volatile__ (                          \
        "in __tmp_reg__, __SREG__"        "\n\t"    \
        "cli"                             "\n\t"    \
        "push __tmp_reg__"                "\n\t"    \
        ::: "memory"                                \
        )


#تعریف_کړه پورټ_EXIT_CRITICAL()                         \
    __asm__ __volatile__ (                          \
        "pop __tmp_reg__"                 "\n\t"    \
        "out __SREG__, __tmp_reg__"       "\n\t"    \
        ::: "memory"                                \
        )


#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    __asm__ __volatile__ ( "cli" ::: "memory" )
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     __asm__ __volatile__ ( "sei" ::: "memory" )
/*-----------------------------------------------------------*/

/* Architecture specifics. */

/* System Tick  - Scheduler timer
 * Prefer to use the enhanced Watchdog Timer, but also Timer0 is ok.
 */

#إذا defined( WDIE ) && defined( WDIF ) /* If Enhanced WDT with interrupt capability is available */

    #تعریف_کړه پورټ_USE_WDTO    WDTO_15MS  /* use the Watchdog Timer for xTaskIncrementTick */

/* Watchdog period options:         WDTO_15MS
 *                                  WDTO_30MS
 *                                  WDTO_60MS
 *                                  WDTO_120MS
 *                                  WDTO_250MS
 *                                  WDTO_500MS
 *                                  WDTO_1S
 *                                  WDTO_2S
 */

#وإلا

    #تعریف_کړه پورټ_USE_TIMER0    /* use the 8-bit Timer0 for xTaskIncrementTick */

#د_که_پای

#تعریف_کړه پورټ_ډېری_GROWTH    ( -1 )

/* Timing for the scheduler.
 * Watchdog Timer is 128kHz nominal,
 * but 120 kHz at 5V DC and 25 degrees is actually more accurate,
 * from data sheet.
 */
#إذا defined( پورټ_USE_WDTO )
    #تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) _BV( پورټ_USE_WDTO + 4 ) )
#وإلا
    #تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#د_که_پای

#تعریف_کړه پورټ_BYTE_ALIGNMENT        1
#تعریف_کړه پورټ_NOP()    __asm__ __volatile__ ( "nop" );
/*-----------------------------------------------------------*/

/* Kernel utilities. */
خارجي فراغ v_پورټ_Yield( فراغ )      __attribute__( ( naked ) );
#تعریف_کړه پورټ_YIELD()             v_پورټ_Yield()

خارجي فراغ v_پورټ_Yield_From_ISR( فراغ )   __attribute__( ( naked ) );
#تعریف_کړه پورټ_YIELD_FROM_ISR()    v_پورټ_Yield_From_ISR()
/*-----------------------------------------------------------*/

#إذا defined( __AVR_3_BYTE_PC__ )
/* Task function macros as described on the FreeRTOS.org WEB site. */

/* Add .lowtext tag from the avr linker script avr6.x for ATmega2560 and ATmega2561
 * to make sure functions are loaded in low memory.
 */
    #تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( section( ".lowtext" ) ) )
#وإلا
    #تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#د_که_پای

#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )              فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
