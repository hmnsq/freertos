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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
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
#وصف_ڪريو پورٽ_CHAR                 حرف
#وصف_ڪريو پورٽ_FLOAT                عائم
#وصف_ڪريو پورٽ_DOUBLE               مزدوج
#وصف_ڪريو پورٽ_LONG                 ڊگهو
#وصف_ڪريو پورٽ_SHORT                صحيح

#وصف_ڪريو پورٽ_اشارو_سائيز_TYPE    uint16_t

تعريفنوع uint8_t        ڍير_Type_t;
تعريفنوع int8_t         بنياد_Type_t;
تعريفنوع uint8_t        UBaseType_t;

#إذا config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ
    تعريفنوع uint16_t   TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t   TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Critical section management. */

#وصف_ڪريو پورٽ_ENTER_CRITICAL()                        \
    __asm__ __volatile__ (                          \
        "in __tmp_reg__, __SREG__"        "\n\t"    \
        "cli"                             "\n\t"    \
        "push __tmp_reg__"                "\n\t"    \
        ::: "memory"                                \
        )


#وصف_ڪريو پورٽ_EXIT_CRITICAL()                         \
    __asm__ __volatile__ (                          \
        "pop __tmp_reg__"                 "\n\t"    \
        "out __SREG__, __tmp_reg__"       "\n\t"    \
        ::: "memory"                                \
        )


#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    __asm__ __volatile__ ( "cli" ::: "memory" )
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     __asm__ __volatile__ ( "sei" ::: "memory" )
/*-----------------------------------------------------------*/

/* Architecture specifics. */

/* System Tick  - Scheduler timer
 * Prefer to use the enhanced Watchdog Timer, but also Timer0 is ok.
 */

#إذا defined( WDIE ) && defined( WDIF ) /* If Enhanced WDT with interrupt capability is available */

    #وصف_ڪريو پورٽ_USE_WDTO    WDTO_15MS  /* use the Watchdog Timer for xTaskIncrementTick */

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

    #وصف_ڪريو پورٽ_USE_TIMER0    /* use the 8-bit Timer0 for xTaskIncrementTick */

#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_ڍير_GROWTH    ( -1 )

/* Timing for the scheduler.
 * Watchdog Timer is 128kHz nominal,
 * but 120 kHz at 5V DC and 25 degrees is actually more accurate,
 * from data sheet.
 */
#إذا defined( پورٽ_USE_WDTO )
    #وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) _BV( پورٽ_USE_WDTO + 4 ) )
#وإلا
    #وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_BYTE_ALIGNMENT        1
#وصف_ڪريو پورٽ_NOP()    __asm__ __volatile__ ( "nop" );
/*-----------------------------------------------------------*/

/* Kernel utilities. */
خارجي فراغ v_پورٽ_Yield( فراغ )      __attribute__( ( naked ) );
#وصف_ڪريو پورٽ_YIELD()             v_پورٽ_Yield()

خارجي فراغ v_پورٽ_Yield_From_ISR( فراغ )   __attribute__( ( naked ) );
#وصف_ڪريو پورٽ_YIELD_FROM_ISR()    v_پورٽ_Yield_From_ISR()
/*-----------------------------------------------------------*/

#إذا defined( __AVR_3_BYTE_PC__ )
/* Task function macros as described on the FreeRTOS.org WEB site. */

/* Add .lowtext tag from the avr linker script avr6.x for ATmega2560 and ATmega2561
 * to make sure functions are loaded in low memory.
 */
    #وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( section( ".lowtext" ) ) )
#وإلا
    #وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )              فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
