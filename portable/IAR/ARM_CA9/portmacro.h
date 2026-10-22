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

/* IAR includes. */
#నిర్వచితమైతే __ICCARM__

    #అన్తర్భావ <intrinsics.h>

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
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffffffffUL

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
    #నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired ) \
    {                                                \
        బాహ్య uint32_t ul_పోర్టు_Yield_Required;         \
                                                     \
        ఒకవేళ( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_పోర్టు_Yield_Required = pdTRUE;            \
        }                                            \
    }

    #నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )    పోర్టు_చివర_SWITCHING_ISR( x )
    #నిర్వచించు పోర్టు_YIELD()                __asm( "SWI 0" );


/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

    బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య );
    బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య );
    బాహ్య uint32_t ul_పోర్టు_సమితి_అంతరాయం_ముసుగు( శూన్య );
    బాహ్య శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు( uint32_t ul_New_ముసుగు_విలువ );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #నిర్వచించు పోర్టు_ENTER_CRITICAL()                      v_పోర్టు_Enter_Critical();
    #నిర్వచించు పోర్టు_EXIT_CRITICAL()                       v_పోర్టు_Exit_Critical();
    #నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                  ul_పోర్టు_సమితి_అంతరాయం_ముసుగు()
    #నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                   v_పోర్టు_Clear_అంతరాయం_ముసుగు( 0 )
    #నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()         ul_పోర్టు_సమితి_అంతరాయం_ముసుగు()
    #నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x )    v_పోర్టు_Clear_అంతరాయం_ముసుగు( x )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
    #నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
    #నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
    శూన్య FreeRTOS_Tick_Handler( శూన్య );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU( శూన్య );
    #నిర్వచించు పోర్టు_TASK_ఉపయోగిస్తుంది_FLOATING_బిందువు()    v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU()

    #నిర్వచించు పోర్టు_అత్యల్ప_అంతరాయం_ప్రాధాన్యత           ( ( ( uint32_t ) config_UNIQUE_అంతరాయం_PRIORITIES ) - 1UL )
    #నిర్వచించు పోర్టు_అత్యల్ప_USABLE_అంతరాయం_ప్రాధాన్యత    ( పోర్టు_అత్యల్ప_అంతరాయం_ప్రాధాన్యత - 1UL )

/* Architecture specific optimisations. */
    #నిర్వచితం_కాకపోతే config_USE_పోర్టు_OPTIMISED_TASK_SELECTION
        #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    1
    #అయితే_ముగింపు

    #ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
        #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ప్రాధాన్యత ) )
        #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ప్రాధాన్యత ) )

/*-----------------------------------------------------------*/

        #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities )    ux_శిఖరం_ప్రాధాన్యత = ( 31 - __CLZ( uxReadyPriorities ) )

    #అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #ఒకవేళ ( configASSERT_DEFINED == 1 )
        శూన్య v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత( శూన్య );
        #నిర్వచించు పోర్టు_ASSERT_IF_అంతరాయం_ప్రాధాన్యత_INVALID()    v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత()
    #అయితే_ముగింపు /* configASSERT */

    #నిర్వచించు పోర్టు_NOP()                                         __asm అస్థిర ( "NOP" )

/* Suppress warnings that are generated by the IAR tools, but cannot be
 * fixed in the source code because to do so would cause other compilers to
 * generate warnings. */
    #సూచన diag_suppress=Pe191
    #సూచన diag_suppress=Pa082

#అయితే_ముగింపు /* __ICCARM__ */


/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#ఒకవేళ config_UNIQUE_అంతరాయం_PRIORITIES == 16
    #నిర్వచించు పోర్టు_ప్రాధాన్యత_జరుపు            4
    #నిర్వచించు పోర్టు_MAX_ద్విమాన_బిందువు_విలువ    3
#లేదావేళ config_UNIQUE_అంతరాయం_PRIORITIES == 32
    #నిర్వచించు పోర్టు_ప్రాధాన్యత_జరుపు            3
    #నిర్వచించు పోర్టు_MAX_ద్విమాన_బిందువు_విలువ    2
#లేదావేళ config_UNIQUE_అంతరాయం_PRIORITIES == 64
    #నిర్వచించు పోర్టు_ప్రాధాన్యత_జరుపు            2
    #నిర్వచించు పోర్టు_MAX_ద్విమాన_బిందువు_విలువ    1
#లేదావేళ config_UNIQUE_అంతరాయం_PRIORITIES == 128
    #నిర్వచించు పోర్టు_ప్రాధాన్యత_జరుపు            1
    #నిర్వచించు పోర్టు_MAX_ద్విమాన_బిందువు_విలువ    0
#లేదావేళ config_UNIQUE_అంతరాయం_PRIORITIES == 256
    #నిర్వచించు పోర్టు_ప్రాధాన్యత_జరుపు            0
    #నిర్వచించు పోర్టు_MAX_ద్విమాన_బిందువు_విలువ    0
#లేకపోతే /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #దోషం Invalid config_UNIQUE_అంతరాయం_PRIORITIES setting.  config_UNIQUE_అంతరాయం_PRIORITIES must be సమితి గమ్యం the సంఖ్య యొక్క unique priorities implemented by the లక్ష్యం hardware
#అయితే_ముగింపు /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* Interrupt controller access addresses. */
#నిర్వచించు పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_స్థానభ్రంశం                      ( 0x04 )
#నిర్వచించు పోర్టు_ICCIAR_అంతరాయం_ACKNOWLEDGE_స్థానభ్రంశం              ( 0x0C )
#నిర్వచించు పోర్టు_ICCEOIR_చివర_యొక్క_అంతరాయం_స్థానభ్రంశం                  ( 0x10 )
#నిర్వచించు పోర్టు_ICCBPR_ద్విమాన_బిందువు_స్థానభ్రంశం                       ( 0x08 )
#నిర్వచించు పోర్టు_ICCRPR_RUNNING_ప్రాధాన్యత_స్థానభ్రంశం                   ( 0x14 )

#నిర్వచించు పోర్టు_అంతరాయం_CONTROLLER_CPU_INTERFACE_చిరునామా       ( config_అంతరాయం_CONTROLLER_పునాది_చిరునామా + config_అంతరాయం_CONTROLLER_CPU_INTERFACE_స్థానభ్రంశం )
#నిర్వచించు పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు                    ( *( ( అస్థిర uint32_t * ) ( పోర్టు_అంతరాయం_CONTROLLER_CPU_INTERFACE_చిరునామా + పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_స్థానభ్రంశం ) ) )
#నిర్వచించు పోర్టు_ICCIAR_అంతరాయం_ACKNOWLEDGE_రిజిస్టరు_చిరునామా    ( పోర్టు_అంతరాయం_CONTROLLER_CPU_INTERFACE_చిరునామా + పోర్టు_ICCIAR_అంతరాయం_ACKNOWLEDGE_స్థానభ్రంశం )
#నిర్వచించు పోర్టు_ICCEOIR_చివర_యొక్క_అంతరాయం_రిజిస్టరు_చిరునామా        ( పోర్టు_అంతరాయం_CONTROLLER_CPU_INTERFACE_చిరునామా + పోర్టు_ICCEOIR_చివర_యొక్క_అంతరాయం_స్థానభ్రంశం )
#నిర్వచించు పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు_చిరునామా            ( పోర్టు_అంతరాయం_CONTROLLER_CPU_INTERFACE_చిరునామా + పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_స్థానభ్రంశం )
#నిర్వచించు పోర్టు_ICCBPR_ద్విమాన_బిందువు_రిజిస్టరు                     ( *( ( స్థిరరాశి అస్థిర uint32_t * ) ( పోర్టు_అంతరాయం_CONTROLLER_CPU_INTERFACE_చిరునామా + పోర్టు_ICCBPR_ద్విమాన_బిందువు_స్థానభ్రంశం ) ) )
#నిర్వచించు పోర్టు_ICCRPR_RUNNING_ప్రాధాన్యత_రిజిస్టరు                 ( *( ( స్థిరరాశి అస్థిర uint32_t * ) ( పోర్టు_అంతరాయం_CONTROLLER_CPU_INTERFACE_చిరునామా + పోర్టు_ICCRPR_RUNNING_ప్రాధాన్యత_స్థానభ్రంశం ) ) )

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
