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

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
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

#अन्तर्भाव <avr/wdt.h>

/* Type definitions. */
#परिभाषय पत्तनम्_CHAR                 वर्ण
#परिभाषय पत्तनम्_FLOAT                भिन्न
#परिभाषय पत्तनम्_DOUBLE               द्विगुण
#परिभाषय पत्तनम्_LONG                 दीर्घ
#परिभाषय पत्तनम्_SHORT                पूर्णाङ्क

#परिभाषय पत्तनम्_POINTER_आकार_TYPE    uint16_t

प्रकारनिर्देश uint8_t        राशिः_Type_t;
प्रकारनिर्देश int8_t         आधारः_Type_t;
प्रकारनिर्देश uint8_t        UBaseType_t;

#यदि config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः
    प्रकारनिर्देश uint16_t   TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t   TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Critical section management. */

#परिभाषय पत्तनम्_ENTER_CRITICAL()                        \
    __asm__ __volatile__ (                          \
        "in __tmp_reg__, __SREG__"        "\n\t"    \
        "cli"                             "\n\t"    \
        "push __tmp_reg__"                "\n\t"    \
        ::: "memory"                                \
        )


#परिभाषय पत्तनम्_EXIT_CRITICAL()                         \
    __asm__ __volatile__ (                          \
        "pop __tmp_reg__"                 "\n\t"    \
        "out __SREG__, __tmp_reg__"       "\n\t"    \
        ::: "memory"                                \
        )


#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    __asm__ __volatile__ ( "cli" ::: "memory" )
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     __asm__ __volatile__ ( "sei" ::: "memory" )
/*-----------------------------------------------------------*/

/* Architecture specifics. */

/* System Tick  - Scheduler timer
 * Prefer to use the enhanced Watchdog Timer, but also Timer0 is ok.
 */

#यदि defined( WDIE ) && defined( WDIF ) /* If Enhanced WDT with interrupt capability is available */

    #परिभाषय पत्तनम्_USE_WDTO    WDTO_15MS  /* use the Watchdog Timer for xTaskIncrementTick */

/* Watchdog period options:         WDTO_15MS
 *                                  WDTO_30MS
 *                                  WDTO_60MS
 *                                  WDTO_120MS
 *                                  WDTO_250MS
 *                                  WDTO_500MS
 *                                  WDTO_1S
 *                                  WDTO_2S
 */

#अन्यथा

    #परिभाषय पत्तनम्_USE_TIMER0    /* use the 8-bit Timer0 for xTaskIncrementTick */

#यदि_अन्तः

#परिभाषय पत्तनम्_राशिः_GROWTH    ( -1 )

/* Timing for the scheduler.
 * Watchdog Timer is 128kHz nominal,
 * but 120 kHz at 5V DC and 25 degrees is actually more accurate,
 * from data sheet.
 */
#यदि defined( पत्तनम्_USE_WDTO )
    #परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) _BV( पत्तनम्_USE_WDTO + 4 ) )
#अन्यथा
    #परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#यदि_अन्तः

#परिभाषय पत्तनम्_BYTE_ALIGNMENT        1
#परिभाषय पत्तनम्_NOP()    __asm__ __volatile__ ( "nop" );
/*-----------------------------------------------------------*/

/* Kernel utilities. */
बाह्य शून्य v_पत्तनम्_Yield( शून्य )      __attribute__( ( naked ) );
#परिभाषय पत्तनम्_YIELD()             v_पत्तनम्_Yield()

बाह्य शून्य v_पत्तनम्_Yield_From_ISR( शून्य )   __attribute__( ( naked ) );
#परिभाषय पत्तनम्_YIELD_FROM_ISR()    v_पत्तनम्_Yield_From_ISR()
/*-----------------------------------------------------------*/

#यदि defined( __AVR_3_BYTE_PC__ )
/* Task function macros as described on the FreeRTOS.org WEB site. */

/* Add .lowtext tag from the avr linker script avr6.x for ATmega2560 and ATmega2561
 * to make sure functions are loaded in low memory.
 */
    #परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters ) __attribute__( ( section( ".lowtext" ) ) )
#अन्यथा
    #परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#यदि_अन्तः

#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )              शून्य vFunction( शून्य * pvParameters )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
