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

/* System include files */
#అన్తర్భావ <xc.h>

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
#నిర్వచించు పోర్టు_CHAR        అక్షరం
#నిర్వచించు పోర్టు_FLOAT       దశాంశం
#నిర్వచించు పోర్టు_DOUBLE      ద్విగుణ
#నిర్వచించు పోర్టు_LONG        దీర్ఘ
#నిర్వచించు పోర్టు_SHORT       పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE  uint32_t
#నిర్వచించు పోర్టు_పునాది_TYPE   దీర్ఘ

రకనిర్వచనం పోర్టు_దొంతర_TYPE దొంతర_Type_t;
రకనిర్వచనం దీర్ఘ పునాది_Type_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ UBaseType_t;

#ఒకవేళ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC 1
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT          8
#నిర్వచించు పోర్టు_దొంతర_GROWTH            -1
#నిర్వచించు పోర్టు_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#నిర్వచించు పోర్టు_IPL_జరుపు               ( 10UL )
#నిర్వచించు పోర్టు_ALL_IPL_బిట్లు            ( 0x3fUL << పోర్టు_IPL_జరుపు )
#నిర్వచించు పోర్టు_SW0_బిట్టు                 ( 0x01 << 8 )

/* This clears the IPL bits, then sets them to
configMAX_SYSCALL_INTERRUPT_PRIORITY.  An extra check is performed if
configASSERT() is defined to ensure an assertion handler does not inadvertently
attempt to lower the IPL when the call to assert was triggered because the IPL
value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY when an ISR
safe FreeRTOS API function was executed.  ISR safe FreeRTOS API functions are
those that end in FromISR.  FreeRTOS maintains a separate interrupt API to
ensure API function and interrupt entry is as fast and as simple as possible. */
#ఒకవేళ ( configASSERT_DEFINED == 1 )
    #నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                                            \
    {                                                                           \
    uint32_t ul_స్థితి;                                                      \
                                                                                \
        /* Mask interrupts at and below the kernel interrupt priority. */       \
        ul_స్థితి = CP0_GET_స్థితి();                                           \
                                                                                \
        /* Is the current IPL below configMAX_SYSCALL_INTERRUPT_PRIORITY? */    \
        ఒకవేళ( ( ( ul_స్థితి & పోర్టు_ALL_IPL_బిట్లు ) >> పోర్టు_IPL_జరుపు ) < config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత ) \
        {                                                                       \
            ul_స్థితి &= ~పోర్టు_ALL_IPL_బిట్లు;                                      \
            CP0_సమితి_స్థితి( ( ul_స్థితి | ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_IPL_జరుపు ) ) ); \
        }                                                                       \
    }
#లేకపోతే /* configASSERT */
    #నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                                        \
    {                                                                       \
    uint32_t ul_స్థితి;                                                  \
                                                                            \
        /* Mask interrupts at and below the kernel interrupt priority. */   \
        ul_స్థితి = CP0_GET_స్థితి();                                       \
        ul_స్థితి &= ~పోర్టు_ALL_IPL_బిట్లు;                                      \
        CP0_సమితి_స్థితి( ( ul_స్థితి | ( config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_IPL_జరుపు ) ) ); \
    }
#అయితే_ముగింపు /* configASSERT */

#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                                         \
{                                                                       \
uint32_t ul_స్థితి;                                                  \
                                                                        \
    /* Unmask all interrupts. */                                        \
    ul_స్థితి = CP0_GET_స్థితి();                                       \
    ul_స్థితి &= ~పోర్టు_ALL_IPL_బిట్లు;                                      \
    CP0_సమితి_స్థితి( ul_స్థితి );                                        \
}


బాహ్య శూన్య vTaskEnterCritical( శూన్య );
బాహ్య శూన్య vTaskExitCritical( శూన్య );
#నిర్వచించు పోర్టు_CRITICAL_NESTING_లోపల_TCB 1
#నిర్వచించు పోర్టు_ENTER_CRITICAL()        vTaskEnterCritical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()         vTaskExitCritical()

బాహ్య UBaseType_t ux_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR();
బాహ్య శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు_From_ISR( UBaseType_t );
#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR() ux_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR()
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( ux_Saved_స్థితి_రిజిస్టరు ) v_పోర్టు_Clear_అంతరాయం_ముసుగు_From_ISR( ux_Saved_స్థితి_రిజిస్టరు )

#నిర్వచితం_కాకపోతే config_USE_పోర్టు_OPTIMISED_TASK_SELECTION
    #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION 1
#అయితే_ముగింపు

#ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #ఒకవేళ( configMAX_PRIORITIES > 32 )
        #దోషం config_USE_పోర్టు_OPTIMISED_TASK_SELECTION can only be సమితి గమ్యం 1 when configMAX_PRIORITIES is less than or equal గమ్యం 32.  It is very rare that a system requires మరిన్ని than 10 గమ్యం 15 difference priorities as tasks that share a ప్రాధాన్యత will time ముక్క.
    #అయితే_ముగింపు

    /* Store/clear the ready priorities in a bit map. */
    #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_ప్రాధాన్యత ) )
    #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_ప్రాధాన్యత ) )

    /*-----------------------------------------------------------*/

    #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities ) ux_శిఖరం_ప్రాధాన్యత = ( 31UL - _clz( ( uxReadyPriorities ) ) )

#అయితే_ముగింపు /* taskRECORD_READY_PRIORITY */

/*-----------------------------------------------------------*/

/* Task utilities. */

#నిర్వచించు పోర్టు_YIELD()                             \
{                                               \
uint32_t ulCause;                           \
                                                \
    /* Trigger software interrupt. */           \
    ulCause = _CP0_GET_CAUSE();                 \
    ulCause |= పోర్టు_SW0_బిట్టు;                     \
    CP0_సమితి_CAUSE( ulCause );                  \
}

బాహ్య అస్థిర UBaseType_t ux_అంతరాయం_Nesting;
#నిర్వచించు పోర్టు_ASSERT_IF_లోపల_ISR() configASSERT( ux_అంతరాయం_Nesting == 0 )

#నిర్వచించు పోర్టు_NOP()   __asm అస్థిర ( "nop" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters ) శూన్య vFunction( శూన్య *pvParameters ) __attribute__((noreturn))
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters ) శూన్య vFunction( శూన్య *pvParameters )
/*-----------------------------------------------------------*/

#నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired ) \
    చేయి                                           \
    {                                            \
        ఒకవేళ( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_గమ్యం_SCHEDULER();        \
            పోర్టు_YIELD();                         \
        }                                        \
        లేకపోతే                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } అయితే( 0 )

/* Required by the kernel aware debugger. */
#నిర్వచితమైతే __DEBUG
    #నిర్వచించు పోర్టు_REMOVE_STATIC_QUALIFIER
#అయితే_ముగింపు

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
