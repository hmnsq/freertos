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

    #నిర్వచితమైతే __cplusplus
        బాహ్య "C"
        {
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

/* Type definitions - These are a bit legacy and not really used now, other
 * than portSTACK_TYPE and portBASE_TYPE. */
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

/* Defines the maximum time when using a wait command in a task */
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

/* Architecture specifics */

    #నిర్వచించు పోర్టు_STSR( reg )              __stsr( ( reg ) )
    #నిర్వచించు పోర్టు_LDSR( reg, val )         __ldsr( ( reg ), ( val ) )
    #నిర్వచించు పోర్టు_STSR_CCRH( reg, sel )    __stsr_rh( ( reg ), ( sel ) )
    #నిర్వచించు పోర్టు_SYNCM()                  __syncm()

/* Determine the descending of the stack from high address to address */
    #నిర్వచించు పోర్టు_దొంతర_GROWTH      ( -1 )

/* Determine the time (in milliseconds) corresponding to each tick */
    #నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )

/* It is a multiple of 4 (the two lower-order bits of the address = 0),
 * otherwise it will cause MAE (Misaligned Exception) according to the manual */
    #నిర్వచించు పోర్టు_BYTE_ALIGNMENT    ( 4 )

/* Interrupt control macros. */

    #నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     __EI() /* Macro to enable all maskable interrupts. */
    #నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    __DI() /* Macro to disable all maskable interrupts. */
    #నిర్వచించు taskENABLE_INTERRUPTS()     పోర్టు_ENABLE_INTERRUPTS()
    #నిర్వచించు taskDISABLE_INTERRUPTS()    పోర్టు_DISABLE_INTERRUPTS()

/* SMP build which means configNUM_CORES is relevant */
    #నిర్వచించు పోర్టు_SUPPORT_SMP              1

    #నిర్వచించు పోర్టు_MAX_CORE_లెక్క           2
    #నిర్వచితం_కాకపోతే config_సంఖ్య_యొక్క_CORES
        #నిర్వచించు config_సంఖ్య_యొక్క_CORES    1
    #అయితే_ముగింపు

/*-----------------------------------------------------------*/
/* Scheduler utilities */

/* Called at the end of an ISR that can cause a context switch */
    బాహ్య శూన్య v_పోర్టు_సమితి_Switch( పునాది_Type_t xSwitchRequired );

    #నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( x )    v_పోర్టు_సమితి_Switch( x )

    #నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )       పోర్టు_చివర_SWITCHING_ISR( x )

/* Use to transfer control from one task to perform other tasks of
 * higher priority */
    బాహ్య శూన్య v_పోర్టు_Yield( శూన్య );

    #నిర్వచించు పోర్టు_YIELD()    v_పోర్టు_Yield()
    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

/* Return the core ID on which the code is running. */
        బాహ్య పునాది_Type_t x_పోర్టు_GET_CORE_ID();

        #నిర్వచించు పోర్టు_GET_CORE_ID()    x_పోర్టు_GET_CORE_ID()
        #నిర్వచించు coreid    x_పోర్టు_GET_CORE_ID()

/* Request the core ID x to yield. */
        బాహ్య శూన్య v_పోర్టు_Yield_Core( uint32_t coreID );

        #నిర్వచించు పోర్టు_YIELD_CORE( x )                v_పోర్టు_Yield_Core( x )

        #నిర్వచించు పోర్టు_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
        #నిర్వచించు పోర్టు_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )

    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES > 1 ) */

    #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
        #నిర్వచించు పోర్టు_GET_ISR_తాళం( xCoreID )
        #నిర్వచించు పోర్టు_RELEASE_ISR_తాళం( xCoreID )
        #నిర్వచించు పోర్టు_GET_TASK_తాళం( xCoreID )
        #నిర్వచించు పోర్టు_RELEASE_TASK_తాళం( xCoreID )
    #లేకపోతే
        బాహ్య శూన్య v_పోర్టు_Recursive_తాళం_Acquire( పునాది_Type_t xCoreID, పునాది_Type_t xFromIsr );
        బాహ్య శూన్య v_పోర్టు_Recursive_తాళం_Release( పునాది_Type_t xCoreID, పునాది_Type_t xFromIsr );

        #నిర్వచించు పోర్టు_GET_ISR_తాళం( xCoreID )         v_పోర్టు_Recursive_తాళం_Acquire( ( xCoreID ), pdTRUE )
        #నిర్వచించు పోర్టు_RELEASE_ISR_తాళం( xCoreID )     v_పోర్టు_Recursive_తాళం_Release( ( xCoreID ), pdTRUE )
        #నిర్వచించు పోర్టు_GET_TASK_తాళం( xCoreID )        v_పోర్టు_Recursive_తాళం_Acquire( ( xCoreID ), pdFALSE )
        #నిర్వచించు పోర్టు_RELEASE_TASK_తాళం( xCoreID )    v_పోర్టు_Recursive_తాళం_Release( ( xCoreID ), pdFALSE )
    #అయితే_ముగింపు /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/
/* Critical section management. */

/* The critical nesting functions defined within tasks.c */

    బాహ్య శూన్య vTaskEnterCritical( శూన్య );
    బాహ్య శూన్య vTaskExitCritical( శూన్య );

/* Macro to mark the start of a critical code region */
    #నిర్వచించు పోర్టు_ENTER_CRITICAL()    vTaskEnterCritical()

/* Macro to mark the end of a critical code region */
    #నిర్వచించు పోర్టు_EXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/
/* Macros to set and clear the interrupt mask. */
    పోర్టు_LONG x_పోర్టు_సమితి_అంతరాయం_ముసుగు();
    శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు( పోర్టు_LONG );

    #నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు()                  x_పోర్టు_సమితి_అంతరాయం_ముసుగు()
    #నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు( x )             v_పోర్టు_Clear_అంతరాయం_ముసుగు( ( x ) )
    #నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()         x_పోర్టు_సమితి_అంతరాయం_ముసుగు()
    #నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x )    v_పోర్టు_Clear_అంతరాయం_ముసుగు( ( x ) )

/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */

    #నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
    #నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

/*-----------------------------------------------------------*/

    #నిర్వచితమైతే __cplusplus
}
    #అయితే_ముగింపు
#అయితే_ముగింపు /* PORTMACRO_H */
