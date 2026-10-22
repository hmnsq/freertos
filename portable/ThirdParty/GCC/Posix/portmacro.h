/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright 2020 Cambridge Consultants Ltd.
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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdint.h>

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
#నిర్వచించు పోర్టు_CHAR                 అక్షరం
#నిర్వచించు పోర్టు_FLOAT                దశాంశం
#నిర్వచించు పోర్టు_DOUBLE               ద్విగుణ
#నిర్వచించు పోర్టు_LONG                 దీర్ఘ
#నిర్వచించు పోర్టు_SHORT                పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE           గుర్తులేని దీర్ఘ
#నిర్వచించు పోర్టు_పునాది_TYPE            దీర్ఘ
#నిర్వచించు పోర్టు_సూచిక_కొలత_TYPE    intptr_t

రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం దీర్ఘ             పునాది_Type_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ    UBaseType_t;

రకనిర్వచనం గుర్తులేని దీర్ఘ    TickType_t;
#నిర్వచించు పోర్టు_MAX_DELAY              ( ( TickType_t ) ULONG_MAX )

#నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#నిర్వచించు పోర్టు_దొంతర_GROWTH                   ( -1 )
#నిర్వచించు పోర్టు_HAS_దొంతర_అధికప్రవాహం_CHECKING    ( 1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS                 ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_TICK_రేటు_MICROSECONDS         ( ( TickType_t ) 1000000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT                 8
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
బాహ్య శూన్య v_పోర్టు_Yield( శూన్య );

#నిర్వచించు పోర్టు_YIELD()                v_పోర్టు_Yield()

#నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired ) \
    చేయి                                           \
    {                                            \
        ఒకవేళ( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_గమ్యం_SCHEDULER();        \
            v_పోర్టు_Yield();                        \
        }                                        \
        లేకపోతే                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } అయితే( 0 )
#నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )    పోర్టు_చివర_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
బాహ్య శూన్య v_పోర్టు_Disable_Interrupts( శూన్య );
బాహ్య శూన్య v_పోర్టు_Enable_Interrupts( శూన్య );
#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు()      ( v_పోర్టు_Disable_Interrupts() )
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు()    ( v_పోర్టు_Enable_Interrupts() )

బాహ్య UBaseType_t x_పోర్టు_సమితి_అంతరాయం_ముసుగు( శూన్య );
బాహ్య శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు( UBaseType_t x_ముసుగు );

బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య );
బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య );
#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()         x_పోర్టు_సమితి_అంతరాయం_ముసుగు()
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x )    v_పోర్టు_Clear_అంతరాయం_ముసుగు( x )
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                  పోర్టు_సమితి_అంతరాయం_ముసుగు()
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                   పోర్టు_CLEAR_అంతరాయం_ముసుగు()
#నిర్వచించు పోర్టు_ENTER_CRITICAL()                      v_పోర్టు_Enter_Critical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()                       v_పోర్టు_Exit_Critical()

/*-----------------------------------------------------------*/

బాహ్య శూన్య v_పోర్టు_Thread_Dying( శూన్య * px_Task_గమ్యం_Delete,
                              అస్థిర పునాది_Type_t * pxPendYield );
బాహ్య శూన్య v_పోర్టు_Cancel_Thread( శూన్య * px_Task_గమ్యం_Delete );
#నిర్వచించు పోర్టు_PRE_TASK_DELETE_HOOK( pv_Task_గమ్యం_Delete, pxPendYield )    v_పోర్టు_Thread_Dying( ( pv_Task_గమ్యం_Delete ), ( pxPendYield ) )
#నిర్వచించు పోర్టు_CLEAN_పైకి_TCB( pxTCB )                                  v_పోర్టు_Cancel_Thread( pxTCB )
/*-----------------------------------------------------------*/

#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )         శూన్య vFunction( శూన్య * pvParameters ) __attribute__( ( noreturn ) )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )               శూన్య vFunction( శూన్య * pvParameters )
/*-----------------------------------------------------------*/

/*
 * Tasks run in their own pthreads and context switches between them
 * are always a full memory barrier. ISRs are emulated as signals
 * which also imply a full memory barrier.
 *
 * Thus, only a compiler barrier is needed to prevent the compiler
 * reordering.
 */
#నిర్వచించు పోర్టు_జ్ఞాపకం_BARRIER()                        __asm అస్థిర ( "" ::: "memory" )

బాహ్య uint32_t ul_పోర్టు_Get_నిరంతరం_సమయం( శూన్య );
#నిర్వచించు పోర్టు_CONFIGURE_TIMER_FOR_నిరంతరం_సమయం_STATS()    /* no-op */
#నిర్వచించు పోర్టు_GET_నిరంతరం_సమయం_COUNTER_విలువ()            ul_పోర్టు_Get_నిరంతరం_సమయం()

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
