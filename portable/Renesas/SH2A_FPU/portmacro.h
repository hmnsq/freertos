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


#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

#شامل <machine.h>

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
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
#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         اعشاری
#تعریف_کرو پورٹ_DOUBLE        دوہرا
#تعریف_کرو پورٹ_LONG          طویل
#تعریف_کرو پورٹ_SHORT         مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_بنیاد_TYPE     طویل

قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف طویل             بنیاد_Type_t;
قسمتعریف غیرعلامتی طویل    UBaseType_t;

#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#اگر_ختم
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT               8
#تعریف_کرو پورٹ_ڈھیر_GROWTH                 -1
#تعریف_کرو پورٹ_TICK_PERIOD_MS               ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_NOP()    nop()
#تعریف_کرو پورٹ_آغاز_SCHEDULER_TRAP_NO      ( 32 )
#تعریف_کرو پورٹ_YIELD_TRAP_NO                ( 33 )
#تعریف_کرو پورٹ_KERNEL_مداخلت_ترجیح    ( 1 )

خالی v_پورٹ_Yield( خالی );
#تعریف_کرو پورٹ_YIELD()                v_پورٹ_Yield()

خارجی خالی vTaskSwitchContext( خالی );
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    کرو { اگر( x != pdFALSE ) vTaskSwitchContext( ); } جب( 0 )

/*
 * This function tells the kernel that the task referenced by xTask is going to
 * use the floating point registers and therefore requires the floating point
 * registers saved as part of its context.
 */
بنیاد_Type_t x_پورٹ_استعمال_کرتا_Floating_نقطہ( خالی * xTask );

/*
 * The flop save and restore functions are defined in portasm.src and called by
 * the trace "task switched in" and "trace task switched out" macros.
 */
خالی v_پورٹ_Save_Flop_Registers( خالی * pul_بفر );
خالی v_پورٹ_Restore_Flop_Registers( خالی * pul_بفر );

/*
 * pxTaskTag is used to point to the buffer into which the floating point
 * context should be saved.  If pxTaskTag is NULL then the task does not use
 * a floating point context.
 */
#تعریف_کرو trace_TASK_SWITCHED_برآمد()    کرو { اگر( pxCurrentTCB->px_Task_لیبل != تہی ) v_پورٹ_Save_Flop_Registers( pxCurrentTCB->px_Task_لیبل ); } جب( 0 )
#تعریف_کرو trace_TASK_SWITCHED_اندر()     کرو { اگر( pxCurrentTCB->px_Task_لیبل != تہی ) v_پورٹ_Restore_Flop_Registers( pxCurrentTCB->px_Task_لیبل ); } جب( 0 )

/*
 * These macros should be called directly, but through the taskENTER_CRITICAL()
 * and taskEXIT_CRITICAL() macros.
 */
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     سیٹ_imask( 0x00 )
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    سیٹ_imask( پورٹ_KERNEL_مداخلت_ترجیح )

/* Critical nesting counts are stored in the TCB. */
#تعریف_کرو پورٹ_CRITICAL_NESTING_اندر_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
خارجی خالی vTaskEnterCritical( خالی );
خارجی خالی vTaskExitCritical( خالی );
#تعریف_کرو پورٹ_ENTER_CRITICAL()    vTaskEnterCritical();
#تعریف_کرو پورٹ_EXIT_CRITICAL()     vTaskExitCritical();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
