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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
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

#అన్తర్భావ <avr/wdt.h>

/* Type definitions. */
#నిర్వచించు పోర్టు_CHAR                 అక్షరం
#నిర్వచించు పోర్టు_FLOAT                దశాంశం
#నిర్వచించు పోర్టు_DOUBLE               ద్విగుణ
#నిర్వచించు పోర్టు_LONG                 దీర్ఘ
#నిర్వచించు పోర్టు_SHORT                పూర్ణాంకం

#నిర్వచించు పోర్టు_సూచిక_కొలత_TYPE    uint16_t

రకనిర్వచనం uint8_t        దొంతర_Type_t;
రకనిర్వచనం int8_t         పునాది_Type_t;
రకనిర్వచనం uint8_t        UBaseType_t;

#ఒకవేళ config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు
    రకనిర్వచనం uint16_t   TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t   TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Critical section management. */

#నిర్వచించు పోర్టు_ENTER_CRITICAL()                        \
    __asm__ __volatile__ (                          \
        "in __tmp_reg__, __SREG__"        "\n\t"    \
        "cli"                             "\n\t"    \
        "push __tmp_reg__"                "\n\t"    \
        ::: "memory"                                \
        )


#నిర్వచించు పోర్టు_EXIT_CRITICAL()                         \
    __asm__ __volatile__ (                          \
        "pop __tmp_reg__"                 "\n\t"    \
        "out __SREG__, __tmp_reg__"       "\n\t"    \
        ::: "memory"                                \
        )


#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    __asm__ __volatile__ ( "cli" ::: "memory" )
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     __asm__ __volatile__ ( "sei" ::: "memory" )
/*-----------------------------------------------------------*/

/* Architecture specifics. */

/* System Tick  - Scheduler timer
 * Prefer to use the enhanced Watchdog Timer, but also Timer0 is ok.
 */

#ఒకవేళ defined( WDIE ) && defined( WDIF ) /* If Enhanced WDT with interrupt capability is available */

    #నిర్వచించు పోర్టు_USE_WDTO    WDTO_15MS  /* use the Watchdog Timer for xTaskIncrementTick */

/* Watchdog period options:         WDTO_15MS
 *                                  WDTO_30MS
 *                                  WDTO_60MS
 *                                  WDTO_120MS
 *                                  WDTO_250MS
 *                                  WDTO_500MS
 *                                  WDTO_1S
 *                                  WDTO_2S
 */

#లేకపోతే

    #నిర్వచించు పోర్టు_USE_TIMER0    /* use the 8-bit Timer0 for xTaskIncrementTick */

#అయితే_ముగింపు

#నిర్వచించు పోర్టు_దొంతర_GROWTH    ( -1 )

/* Timing for the scheduler.
 * Watchdog Timer is 128kHz nominal,
 * but 120 kHz at 5V DC and 25 degrees is actually more accurate,
 * from data sheet.
 */
#ఒకవేళ defined( పోర్టు_USE_WDTO )
    #నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) _BV( పోర్టు_USE_WDTO + 4 ) )
#లేకపోతే
    #నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_BYTE_ALIGNMENT        1
#నిర్వచించు పోర్టు_NOP()    __asm__ __volatile__ ( "nop" );
/*-----------------------------------------------------------*/

/* Kernel utilities. */
బాహ్య శూన్య v_పోర్టు_Yield( శూన్య )      __attribute__( ( naked ) );
#నిర్వచించు పోర్టు_YIELD()             v_పోర్టు_Yield()

బాహ్య శూన్య v_పోర్టు_Yield_From_ISR( శూన్య )   __attribute__( ( naked ) );
#నిర్వచించు పోర్టు_YIELD_FROM_ISR()    v_పోర్టు_Yield_From_ISR()
/*-----------------------------------------------------------*/

#ఒకవేళ defined( __AVR_3_BYTE_PC__ )
/* Task function macros as described on the FreeRTOS.org WEB site. */

/* Add .lowtext tag from the avr linker script avr6.x for ATmega2560 and ATmega2561
 * to make sure functions are loaded in low memory.
 */
    #నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters ) __attribute__( ( section( ".lowtext" ) ) )
#లేకపోతే
    #నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )              శూన్య vFunction( శూన్య * pvParameters )

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
