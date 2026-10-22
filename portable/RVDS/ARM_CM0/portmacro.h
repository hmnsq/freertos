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

/* Type definitions. */
#నిర్వచించు పోర్టు_CHAR          అక్షరం
#నిర్వచించు పోర్టు_FLOAT         దశాంశం
#నిర్వచించు పోర్టు_DOUBLE        ద్విగుణ
#నిర్వచించు పోర్టు_LONG          దీర్ఘ
#నిర్వచించు పోర్టు_SHORT         పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE    uint32_t
#నిర్వచించు పోర్టు_పునాది_TYPE     దీర్ఘ

రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం దీర్ఘ             పునాది_Type_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ    UBaseType_t;

#ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC    1
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#నిర్వచించు పోర్టు_దొంతర_GROWTH      ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/


/* Scheduler utilities. */
బాహ్య శూన్య v_పోర్టు_Yield( శూన్య );
#నిర్వచించు పోర్టు_NVIC_INT_CTRL_REG     ( *( ( అస్థిర uint32_t * ) 0xe000ed04 ) )
#నిర్వచించు పోర్టు_NVIC_PENDSVSET_బిట్టు    ( 1UL << 28UL )
#నిర్వచించు పోర్టు_YIELD()                v_పోర్టు_Yield()
#నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired )            \
    చేయి                                                      \
    {                                                       \
        ఒకవేళ( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_గమ్యం_SCHEDULER();                   \
            పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు; \
        }                                                   \
        లేకపోతే                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } అయితే( 0 )
#నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )    పోర్టు_చివర_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య );
బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య );
బాహ్య uint32_t ul_సమితి_అంతరాయం_ముసుగు_From_ISR( శూన్య );
బాహ్య శూన్య v_Clear_అంతరాయం_ముసుగు_From_ISR( uint32_t ul_ముసుగు );

#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()         ul_సమితి_అంతరాయం_ముసుగు_From_ISR()
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x )    v_Clear_అంతరాయం_ముసుగు_From_ISR( x )
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                  __disable_irq()
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                   __enable_irq()
#నిర్వచించు పోర్టు_ENTER_CRITICAL()                      v_పోర్టు_Enter_Critical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()                       v_పోర్టు_Exit_Critical()

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#నిర్వచితం_కాకపోతే పోర్టు_SUPPRESS_TICKS_AND_SLEEP
    బాహ్య శూన్య v_పోర్టు_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_సమయం );
    #నిర్వచించు పోర్టు_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_సమయం )    v_పోర్టు_Suppress_Ticks_And_Sleep( x_Expected_Idle_సమయం )
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

#నిర్వచించు పోర్టు_NOP()

#నిర్వచించు పోర్టు_INLINE              __inline

#నిర్వచితం_కాకపోతే పోర్టు_FORCE_INLINE
    #నిర్వచించు పోర్టు_FORCE_INLINE    __forceinline
#అయితే_ముగింపు

/*-----------------------------------------------------------*/

స్థిర పోర్టు_FORCE_INLINE పునాది_Type_t x_పోర్టు_Is_Inside_అంతరాయం( శూన్య )
{
    uint32_t ul_Current_అంతరాయం;
    పునాది_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm
    {
/* *INDENT-OFF* */
            mrs ul_Current_అంతరాయం, ipsr
/* *INDENT-ON* */
    }

    ఒకవేళ( ul_Current_అంతరాయం == 0 )
    {
        xReturn = pdFALSE;
    }
    లేకపోతే
    {
        xReturn = pdTRUE;
    }

    తిరిగి xReturn;
}

/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
