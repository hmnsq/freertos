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

#అన్తర్భావ <machine.h>

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

/* Type definitions - these are a bit legacy and not really used now, other than
 * portSTACK_TYPE and portBASE_TYPE. */
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
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT               8
#నిర్వచించు పోర్టు_దొంతర_GROWTH                 -1
#నిర్వచించు పోర్టు_TICK_PERIOD_MS               ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_NOP()    nop()
#నిర్వచించు పోర్టు_ప్రారంభం_SCHEDULER_TRAP_NO      ( 32 )
#నిర్వచించు పోర్టు_YIELD_TRAP_NO                ( 33 )
#నిర్వచించు పోర్టు_KERNEL_అంతరాయం_ప్రాధాన్యత    ( 1 )

శూన్య v_పోర్టు_Yield( శూన్య );
#నిర్వచించు పోర్టు_YIELD()                v_పోర్టు_Yield()

బాహ్య శూన్య vTaskSwitchContext( శూన్య );
#నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )    చేయి { ఒకవేళ( x != pdFALSE ) vTaskSwitchContext( ); } అయితే( 0 )

/*
 * This function tells the kernel that the task referenced by xTask is going to
 * use the floating point registers and therefore requires the floating point
 * registers saved as part of its context.
 */
పునాది_Type_t x_పోర్టు_ఉపయోగిస్తుంది_Floating_బిందువు( శూన్య * xTask );

/*
 * The flop save and restore functions are defined in portasm.src and called by
 * the trace "task switched in" and "trace task switched out" macros.
 */
శూన్య v_పోర్టు_Save_Flop_Registers( శూన్య * pul_బఫరు );
శూన్య v_పోర్టు_Restore_Flop_Registers( శూన్య * pul_బఫరు );

/*
 * pxTaskTag is used to point to the buffer into which the floating point
 * context should be saved.  If pxTaskTag is NULL then the task does not use
 * a floating point context.
 */
#నిర్వచించు trace_TASK_SWITCHED_బహిర్గతం()    చేయి { ఒకవేళ( pxCurrentTCB->px_Task_ట్యాగ్ != ఖాళీ ) v_పోర్టు_Save_Flop_Registers( pxCurrentTCB->px_Task_ట్యాగ్ ); } అయితే( 0 )
#నిర్వచించు trace_TASK_SWITCHED_లోపల()     చేయి { ఒకవేళ( pxCurrentTCB->px_Task_ట్యాగ్ != ఖాళీ ) v_పోర్టు_Restore_Flop_Registers( pxCurrentTCB->px_Task_ట్యాగ్ ); } అయితే( 0 )

/*
 * These macros should be called directly, but through the taskENTER_CRITICAL()
 * and taskEXIT_CRITICAL() macros.
 */
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     సమితి_imask( 0x00 )
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    సమితి_imask( పోర్టు_KERNEL_అంతరాయం_ప్రాధాన్యత )

/* Critical nesting counts are stored in the TCB. */
#నిర్వచించు పోర్టు_CRITICAL_NESTING_లోపల_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
బాహ్య శూన్య vTaskEnterCritical( శూన్య );
బాహ్య శూన్య vTaskExitCritical( శూన్య );
#నిర్వచించు పోర్టు_ENTER_CRITICAL()    vTaskEnterCritical();
#నిర్వచించు పోర్టు_EXIT_CRITICAL()     vTaskExitCritical();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
