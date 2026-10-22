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
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
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

రకనిర్వచనం uint32_t         TickType_t;
#నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#నిర్వచించు పోర్టు_దొంతర_GROWTH      ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired )      \
    {                                                 \
        బాహ్య అస్థిర uint32_t ul_పోర్టు_Yield_Required; \
                                                      \
        ఒకవేళ( xSwitchRequired != pdFALSE )              \
        {                                             \
            ul_పోర్టు_Yield_Required = pdTRUE;             \
        }                                             \
    }

#నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )    పోర్టు_చివర_SWITCHING_ISR( x )

శూన్య v_పోర్టు_Yield( శూన్య );

#నిర్వచించు పోర్టు_YIELD()     v_పోర్టు_Yield();

/*-----------------------------------------------------------*/

/*
 * Critical section management.
 */

బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య );
బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య );
బాహ్య శూన్య v_పోర్టు_Enable_Interrupts( శూన్య );
బాహ్య శూన్య v_పోర్టు_Disable_Interrupts( శూన్య );
బాహ్య uint32_t ul_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR( శూన్య );

/* In the absence of a priority mask register, these functions and macros
 * globally enable and disable interrupts. */
#నిర్వచించు పోర్టు_ENTER_CRITICAL()                    v_పోర్టు_Enter_Critical();
#నిర్వచించు పోర్టు_EXIT_CRITICAL()                     v_పోర్టు_Exit_Critical();
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                 v_పోర్టు_Enable_Interrupts();
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                v_పోర్టు_Disable_Interrupts();
#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()       ul_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR();
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x )  చేయి { ఒకవేళ( x == 0 ) పోర్టు_ENABLE_INTERRUPTS(); } అయితే( 0 )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

/* Tickless idle/low power functionality. */
#నిర్వచితం_కాకపోతే పోర్టు_SUPPRESS_TICKS_AND_SLEEP
    బాహ్య శూన్య v_పోర్టు_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_సమయం );
    #నిర్వచించు పోర్టు_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_సమయం )    v_పోర్టు_Suppress_Ticks_And_Sleep( x_Expected_Idle_సమయం )
#అయితే_ముగింపు

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
శూన్య FreeRTOS_Tick_Handler( శూన్య );

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_పోర్టు_లెక్క_Leading_Zeros( UBaseType_t ulBitmap );

/* If configUSE_TASK_FPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without an FPU context and must call vPortTaskUsesFPU() to give
 * themselves an FPU context before using any FPU instructions.  If
 * configUSE_TASK_FPU_SUPPORT is set to 2 then all tasks will have an FPU
 * context by default. */
#ఒకవేళ ( configUSE_TASK_FPU_SUPPORT != 2 )
    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU( శూన్య );
#లేకపోతే
    /* Each task has an FPU context already, so define this function as a
     * no-op. */
    #నిర్వచించు v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU()
#అయితే_ముగింపు
#నిర్వచించు పోర్టు_TASK_ఉపయోగిస్తుంది_FLOATING_బిందువు()    v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU()

#నిర్వచించు పోర్టు_అత్యల్ప_అంతరాయం_ప్రాధాన్యత           ( ( ( uint32_t ) config_UNIQUE_అంతరాయం_PRIORITIES ) - 1UL )
#నిర్వచించు పోర్టు_అత్యల్ప_USABLE_అంతరాయం_ప్రాధాన్యత    ( పోర్టు_అత్యల్ప_అంతరాయం_ప్రాధాన్యత - 1UL )

/* Architecture specific optimisations. */
#నిర్వచితం_కాకపోతే config_USE_పోర్టు_OPTIMISED_TASK_SELECTION
    #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    1
#అయితే_ముగింపు

#ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1

    /* Store, clear and get the ready priorities in a bit map. */
    #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ప్రాధాన్యత ) )
    #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ప్రాధాన్యత ) )
    #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities )  ux_శిఖరం_ప్రాధాన్యత = ( 31UL - ul_పోర్టు_లెక్క_Leading_Zeros( ( ux_శిఖరం_Ready_ప్రాధాన్యత ) ) )

#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#నిర్వచించు పోర్టు_NOP()               __asm అస్థిర ( "NOP" )
#నిర్వచించు పోర్టు_INLINE              __inline
#నిర్వచించు పోర్టు_జ్ఞాపకం_BARRIER()    __asm అస్థిర ( "" ::: "memory" )

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
