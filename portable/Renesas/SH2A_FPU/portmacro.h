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


#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

#अन्तर्भाव <machine.h>

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
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
#परिभाषय पत्तनम्_CHAR          वर्ण
#परिभाषय पत्तनम्_FLOAT         भिन्न
#परिभाषय पत्तनम्_DOUBLE        द्विगुण
#परिभाषय पत्तनम्_LONG          दीर्घ
#परिभाषय पत्तनम्_SHORT         ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE    uint32_t
#परिभाषय पत्तनम्_आधारः_TYPE     दीर्घ

प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
प्रकारनिर्देश दीर्घ             आधारः_Type_t;
प्रकारनिर्देश अचिह्नित दीर्घ    UBaseType_t;

#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#परिभाषय पत्तनम्_BYTE_ALIGNMENT               8
#परिभाषय पत्तनम्_राशिः_GROWTH                 -1
#परिभाषय पत्तनम्_TICK_PERIOD_MS               ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_NOP()    nop()
#परिभाषय पत्तनम्_START_SCHEDULER_TRAP_NO      ( 32 )
#परिभाषय पत्तनम्_YIELD_TRAP_NO                ( 33 )
#परिभाषय पत्तनम्_KERNEL_व्यवधानम्_प्राथमिकता    ( 1 )

शून्य v_पत्तनम्_Yield( शून्य );
#परिभाषय पत्तनम्_YIELD()                v_पत्तनम्_Yield()

बाह्य शून्य vTaskSwitchContext( शून्य );
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )    कुरु { यदि( x != pdFALSE ) vTaskSwitchContext( ); } यावत्( 0 )

/*
 * This function tells the kernel that the task referenced by xTask is going to
 * use the floating point registers and therefore requires the floating point
 * registers saved as part of its context.
 */
आधारः_Type_t x_पत्तनम्_उपयुङ्क्ते_Floating_Point( शून्य * xTask );

/*
 * The flop save and restore functions are defined in portasm.src and called by
 * the trace "task switched in" and "trace task switched out" macros.
 */
शून्य v_पत्तनम्_Save_Flop_Registers( शून्य * pul_बफर );
शून्य v_पत्तनम्_Restore_Flop_Registers( शून्य * pul_बफर );

/*
 * pxTaskTag is used to point to the buffer into which the floating point
 * context should be saved.  If pxTaskTag is NULL then the task does not use
 * a floating point context.
 */
#परिभाषय trace_TASK_SWITCHED_बहिर्गमनम्()    कुरु { यदि( pxCurrentTCB->px_Task_चिह्नकम् != रिक्त ) v_पत्तनम्_Save_Flop_Registers( pxCurrentTCB->px_Task_चिह्नकम् ); } यावत्( 0 )
#परिभाषय trace_TASK_SWITCHED_अन्तर्()     कुरु { यदि( pxCurrentTCB->px_Task_चिह्नकम् != रिक्त ) v_पत्तनम्_Restore_Flop_Registers( pxCurrentTCB->px_Task_चिह्नकम् ); } यावत्( 0 )

/*
 * These macros should be called directly, but through the taskENTER_CRITICAL()
 * and taskEXIT_CRITICAL() macros.
 */
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     समुच्चयः_imask( 0x00 )
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    समुच्चयः_imask( पत्तनम्_KERNEL_व्यवधानम्_प्राथमिकता )

/* Critical nesting counts are stored in the TCB. */
#परिभाषय पत्तनम्_CRITICAL_NESTING_अन्तर्_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
बाह्य शून्य vTaskEnterCritical( शून्य );
बाह्य शून्य vTaskExitCritical( शून्य );
#परिभाषय पत्तनम्_ENTER_CRITICAL()    vTaskEnterCritical();
#परिभाषय पत्तनम्_EXIT_CRITICAL()     vTaskExitCritical();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
