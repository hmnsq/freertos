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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
/* *INDENT-ON* */

/* record stack high address for stack check */
#నిర్వచితం_కాకపోతే config_రికార్డు_దొంతర_ఎగువ_చిరునామా
    #నిర్వచించు config_రికార్డు_దొంతర_ఎగువ_చిరునామా    1
#అయితే_ముగింపు

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
#నిర్వచించు పోర్టు_CHAR          అక్షరం
#నిర్వచించు పోర్టు_FLOAT         దశాంశం
#నిర్వచించు పోర్టు_DOUBLE        ద్విగుణ
#నిర్వచించు పోర్టు_LONG          దీర్ఘ
#నిర్వచించు పోర్టు_SHORT         పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE    గుర్తులేని పూర్ణాంకం
#నిర్వచించు పోర్టు_పునాది_TYPE     పోర్టు_LONG

#నిర్వచితం_కాకపోతే Asm
    #నిర్వచించు Asm           __asm__ అస్థిర
#అయితే_ముగింపు

/*
 *  normal constants
 */
#నిర్వచితం_కాకపోతే ఖాళీ
    #నిర్వచించు ఖాళీ    0           /* invalid pointer */
#అయితే_ముగింపు /* NULL */

#నిర్వచితం_కాకపోతే true
    #నిర్వచించు true    1           /* true */
#అయితే_ముగింపు /* true */

#నిర్వచితం_కాకపోతే false
    #నిర్వచించు false    0          /* false */
#అయితే_ముగింపు /* false */

రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం దీర్ఘ             పునాది_Type_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ    UBaseType_t;

#ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING    ( ( uint32_t ) 0 )
#నిర్వచించు పోర్టు_దొంతర_GROWTH           ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS         ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT         8
#నిర్వచించు పోర్టు_NOP()               Asm( "nop_s" );
#నిర్వచించు IPM_ENABLE_ALL             1

#నిర్వచించు పోర్టు_YIELD_FROM_ISR()    v_పోర్టు_Yield_From_Isr()
#నిర్వచించు పోర్టు_YIELD()             v_పోర్టు_Yield()

/* Critical section management. */
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS() \
    {                            \
        Asm( "clri" );           \
        Asm( "" ::: "memory" );  \
    }                            \

#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS() \
    {                           \
        Asm( "" ::: "memory" ); \
        Asm( "seti" );          \
    }                           \

బాహ్య అస్థిర గుర్తులేని పూర్ణాంకం ulCriticalNesting;

#నిర్వచించు పోర్టు_ENTER_CRITICAL()     \
    {                            \
        పోర్టు_DISABLE_INTERRUPTS() \
        ulCriticalNesting++;     \
    }


#నిర్వచించు పోర్టు_EXIT_CRITICAL()                                    \
    {                                                          \
        ఒకవేళ( ulCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )      \
        {                                                      \
            ulCriticalNesting--;                               \
            ఒకవేళ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING ) \
            {                                                  \
                పోర్టు_ENABLE_INTERRUPTS()                        \
            }                                                  \
        }                                                      \
    }


#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

#నిర్వచించు పోర్టు_CONFIGURE_TIMER_FOR_నిరంతరం_సమయం_STATS()              చేయి {} అయితే( 0 )     /* we use the timer */
#నిర్వచించు పోర్టు_ALT_GET_నిరంతరం_సమయం_COUNTER_విలువ( dest )            ( dest = x_Tick_లెక్క )

#ఒకవేళ defined( __MW__ )
    బాహ్య శూన్య task_చివర_hook( శూన్య * pxTCB );
    #నిర్వచించు పోర్టు_CLEAN_పైకి_TCB( pxTCB )    task_చివర_hook( ( శూన్య * ) pxTCB )
#అయితే_ముగింపు

శూన్య v_పోర్టు_Yield( శూన్య );
శూన్య v_పోర్టు_Yield_From_Isr( శూన్య );

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
