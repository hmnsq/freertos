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

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
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
#تعریف_کرو پورٹ_CHAR                 حرف
#تعریف_کرو پورٹ_FLOAT                عائم
#تعریف_کرو پورٹ_DOUBLE               مزدوج
#تعریف_کرو پورٹ_LONG                 لما
#تعریف_کرو پورٹ_SHORT                صحيح

#تعریف_کرو پورٹ_اشارہ_گر_ناپ_TYPE    uint16_t

تعريفنوع uint8_t        ڈھیر_Type_t;
تعريفنوع int8_t         ادھار_Type_t;
تعريفنوع uint8_t        UBaseType_t;

#إذا config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ
    تعريفنوع uint16_t   TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t   TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/* Critical section management. */

#تعریف_کرو پورٹ_ENTER_CRITICAL()                        \
    __asm__ __volatile__ (                          \
        "in __tmp_reg__, __SREG__"        "\n\t"    \
        "cli"                             "\n\t"    \
        "push __tmp_reg__"                "\n\t"    \
        ::: "memory"                                \
        )


#تعریف_کرو پورٹ_EXIT_CRITICAL()                         \
    __asm__ __volatile__ (                          \
        "pop __tmp_reg__"                 "\n\t"    \
        "out __SREG__, __tmp_reg__"       "\n\t"    \
        ::: "memory"                                \
        )


#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    __asm__ __volatile__ ( "cli" ::: "memory" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     __asm__ __volatile__ ( "sei" ::: "memory" )
/*-----------------------------------------------------------*/

/* Architecture specifics. */

/* System Tick  - Scheduler timer
 * Prefer to use the enhanced Watchdog Timer, but also Timer0 is ok.
 */

#إذا defined( WDIE ) && defined( WDIF ) /* If Enhanced WDT with interrupt capability is available */

    #تعریف_کرو پورٹ_USE_WDTO    WDTO_15MS  /* use the Watchdog Timer for xTaskIncrementTick */

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

    #تعریف_کرو پورٹ_USE_TIMER0    /* use the 8-bit Timer0 for xTaskIncrementTick */

#جے_انت

#تعریف_کرو پورٹ_ڈھیر_GROWTH    ( -1 )

/* Timing for the scheduler.
 * Watchdog Timer is 128kHz nominal,
 * but 120 kHz at 5V DC and 25 degrees is actually more accurate,
 * from data sheet.
 */
#إذا defined( پورٹ_USE_WDTO )
    #تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) _BV( پورٹ_USE_WDTO + 4 ) )
#وإلا
    #تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#جے_انت

#تعریف_کرو پورٹ_BYTE_ALIGNMENT        1
#تعریف_کرو پورٹ_NOP()    __asm__ __volatile__ ( "nop" );
/*-----------------------------------------------------------*/

/* Kernel utilities. */
خارجي فراغ v_پورٹ_Yield( فراغ )      __attribute__( ( naked ) );
#تعریف_کرو پورٹ_YIELD()             v_پورٹ_Yield()

خارجي فراغ v_پورٹ_Yield_From_ISR( فراغ )   __attribute__( ( naked ) );
#تعریف_کرو پورٹ_YIELD_FROM_ISR()    v_پورٹ_Yield_From_ISR()
/*-----------------------------------------------------------*/

#إذا defined( __AVR_3_BYTE_PC__ )
/* Task function macros as described on the FreeRTOS.org WEB site. */

/* Add .lowtext tag from the avr linker script avr6.x for ATmega2560 and ATmega2561
 * to make sure functions are loaded in low memory.
 */
    #تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( section( ".lowtext" ) ) )
#وإلا
    #تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#جے_انت

#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )              فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
