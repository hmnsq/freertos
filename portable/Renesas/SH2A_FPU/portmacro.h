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


#ifndef PORTMACRO_H
#define PORTMACRO_H

#অন্তর্ভাব <machine.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
    বাহ্য "C" {
#endif
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
#define portCHAR          বর্ণ
#define portFLOAT         ভিন্ন
#define portDOUBLE        দ্বিগুণ
#define portLONG          long
#define portSHORT         short
#define port_স্তূপ_TYPE    uint32_t
#define portBASE_TYPE     long

প্রকারনির্দেশ port_স্তূপ_TYPE   স্তূপ_Type_t;
প্রকারনির্দেশ long             BaseType_t;
প্রকারনির্দেশ unsigned long    UBaseType_t;

#যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    প্রকারনির্দেশ uint16_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#নোচেদ্যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    প্রকারনির্দেশ uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#endif
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT               8
#define port_স্তূপ_GROWTH                 -1
#define portTICK_PERIOD_MS               ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portNOP()    nop()
#define portSTART_SCHEDULER_TRAP_NO      ( 32 )
#define portYIELD_TRAP_NO                ( 33 )
#define portKERNEL_INTERRUPT_PRIORITY    ( 1 )

শূন্য vPortYield( শূন্য );
#define portYIELD()                vPortYield()

বাহ্য শূন্য vTaskSwitchContext( শূন্য );
#define portYIELD_FROM_ISR( x )    কুরু { যদি( x != pdFALSE ) vTaskSwitchContext( ); } যাবত্( 0 )

/*
 * This function tells the kernel that the task referenced by xTask is going to
 * use the floating point registers and therefore requires the floating point
 * registers saved as part of its context.
 */
BaseType_t xPortUsesFloatingPoint( শূন্য * xTask );

/*
 * The flop save and restore functions are defined in portasm.src and called by
 * the trace "task switched in" and "trace task switched out" macros.
 */
শূন্য vPortSaveFlopRegisters( শূন্য * pulBuffer );
শূন্য vPortRestoreFlopRegisters( শূন্য * pulBuffer );

/*
 * pxTaskTag is used to point to the buffer into which the floating point
 * context should be saved.  If pxTaskTag is NULL then the task does not use
 * a floating point context.
 */
#define traceTASK_SWITCHED_OUT()    কুরু { যদি( pxCurrentTCB->pxTaskTag != রিক্ত ) vPortSaveFlopRegisters( pxCurrentTCB->pxTaskTag ); } যাবত্( 0 )
#define traceTASK_SWITCHED_IN()     কুরু { যদি( pxCurrentTCB->pxTaskTag != রিক্ত ) vPortRestoreFlopRegisters( pxCurrentTCB->pxTaskTag ); } যাবত্( 0 )

/*
 * These macros should be called directly, but through the taskENTER_CRITICAL()
 * and taskEXIT_CRITICAL() macros.
 */
#define portENABLE_INTERRUPTS()     set_imask( 0x00 )
#define portDISABLE_INTERRUPTS()    set_imask( portKERNEL_INTERRUPT_PRIORITY )

/* Critical nesting counts are stored in the TCB. */
#define portCRITICAL_NESTING_IN_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
বাহ্য শূন্য vTaskEnterCritical( শূন্য );
বাহ্য শূন্য vTaskExitCritical( শূন্য );
#define portENTER_CRITICAL()    vTaskEnterCritical();
#define portEXIT_CRITICAL()     vTaskExitCritical();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    শূন্য vFunction( শূন্য * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          শূন্য vFunction( শূন্য * pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
