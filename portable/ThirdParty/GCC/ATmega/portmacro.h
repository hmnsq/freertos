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

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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
#تعریف_کن پورت_CHAR                 حرف
#تعریف_کن پورت_FLOAT                عائم
#تعریف_کن پورت_DOUBLE               مزدوج
#تعریف_کن پورت_LONG                 دراز
#تعریف_کن پورت_SHORT                صحيح

#تعریف_کن پورت_اشاره_گر_اندازه_TYPE    uint16_t

تعريفنوع uint8_t        پشته_Type_t;
تعريفنوع int8_t         پایه_Type_t;
تعريفنوع uint8_t        UBaseType_t;

#إذا config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها
    تعريفنوع uint16_t   TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t   TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر
/*-----------------------------------------------------------*/

/* Critical section management. */

#تعریف_کن پورت_ENTER_CRITICAL()                        \
    __asm__ __volatile__ (                          \
        "in __tmp_reg__, __SREG__"        "\n\t"    \
        "cli"                             "\n\t"    \
        "push __tmp_reg__"                "\n\t"    \
        ::: "memory"                                \
        )


#تعریف_کن پورت_EXIT_CRITICAL()                         \
    __asm__ __volatile__ (                          \
        "pop __tmp_reg__"                 "\n\t"    \
        "out __SREG__, __tmp_reg__"       "\n\t"    \
        ::: "memory"                                \
        )


#تعریف_کن پورت_DISABLE_INTERRUPTS()    __asm__ __volatile__ ( "cli" ::: "memory" )
#تعریف_کن پورت_ENABLE_INTERRUPTS()     __asm__ __volatile__ ( "sei" ::: "memory" )
/*-----------------------------------------------------------*/

/* Architecture specifics. */

/* System Tick  - Scheduler timer
 * Prefer to use the enhanced Watchdog Timer, but also Timer0 is ok.
 */

#إذا defined( WDIE ) && defined( WDIF ) /* If Enhanced WDT with interrupt capability is available */

    #تعریف_کن پورت_USE_WDTO    WDTO_15MS  /* use the Watchdog Timer for xTaskIncrementTick */

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

    #تعریف_کن پورت_USE_TIMER0    /* use the 8-bit Timer0 for xTaskIncrementTick */

#پایان_اگر

#تعریف_کن پورت_پشته_GROWTH    ( -1 )

/* Timing for the scheduler.
 * Watchdog Timer is 128kHz nominal,
 * but 120 kHz at 5V DC and 25 degrees is actually more accurate,
 * from data sheet.
 */
#إذا defined( پورت_USE_WDTO )
    #تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) _BV( پورت_USE_WDTO + 4 ) )
#وإلا
    #تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#پایان_اگر

#تعریف_کن پورت_BYTE_ALIGNMENT        1
#تعریف_کن پورت_NOP()    __asm__ __volatile__ ( "nop" );
/*-----------------------------------------------------------*/

/* Kernel utilities. */
خارجي فراغ v_پورت_Yield( فراغ )      __attribute__( ( naked ) );
#تعریف_کن پورت_YIELD()             v_پورت_Yield()

خارجي فراغ v_پورت_Yield_From_ISR( فراغ )   __attribute__( ( naked ) );
#تعریف_کن پورت_YIELD_FROM_ISR()    v_پورت_Yield_From_ISR()
/*-----------------------------------------------------------*/

#إذا defined( __AVR_3_BYTE_PC__ )
/* Task function macros as described on the FreeRTOS.org WEB site. */

/* Add .lowtext tag from the avr linker script avr6.x for ATmega2560 and ATmega2561
 * to make sure functions are loaded in low memory.
 */
    #تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( section( ".lowtext" ) ) )
#وإلا
    #تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#پایان_اگر

#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )              فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
