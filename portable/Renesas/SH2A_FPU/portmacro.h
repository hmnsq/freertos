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


#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

#ضمن <machine.h>

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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
#تعریف_کن پورت_CHAR          حرف
#تعریف_کن پورت_FLOAT         عائم
#تعریف_کن پورت_DOUBLE        مزدوج
#تعریف_کن پورت_LONG          دراز
#تعریف_کن پورت_SHORT         کوتاه
#تعریف_کن پورت_پشته_TYPE    uint32_t
#تعریف_کن پورت_پایه_TYPE     دراز

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع دراز             پایه_Type_t;
تعريفنوع بیعلامت دراز    UBaseType_t;

#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
#پایان_اگر
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کن پورت_BYTE_ALIGNMENT               8
#تعریف_کن پورت_پشته_GROWTH                 -1
#تعریف_کن پورت_TICK_PERIOD_MS               ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_NOP()    nop()
#تعریف_کن پورت_شروع_SCHEDULER_TRAP_NO      ( 32 )
#تعریف_کن پورت_YIELD_TRAP_NO                ( 33 )
#تعریف_کن پورت_KERNEL_وقفه_اولویت    ( 1 )

فراغ v_پورت_Yield( فراغ );
#تعریف_کن پورت_YIELD()                v_پورت_Yield()

خارجي فراغ vTaskSwitchContext( فراغ );
#تعریف_کن پورت_YIELD_FROM_ISR( x )    افعل { إذا( x != pdFALSE ) vTaskSwitchContext( ); } طالما( 0 )

/*
 * This function tells the kernel that the task referenced by xTask is going to
 * use the floating point registers and therefore requires the floating point
 * registers saved as part of its context.
 */
پایه_Type_t x_پورت_استفاده_میکند_Floating_نقطه( فراغ * xTask );

/*
 * The flop save and restore functions are defined in portasm.src and called by
 * the trace "task switched in" and "trace task switched out" macros.
 */
فراغ v_پورت_Save_Flop_Registers( فراغ * pul_میانگیر );
فراغ v_پورت_Restore_Flop_Registers( فراغ * pul_میانگیر );

/*
 * pxTaskTag is used to point to the buffer into which the floating point
 * context should be saved.  If pxTaskTag is NULL then the task does not use
 * a floating point context.
 */
#تعریف_کن trace_TASK_SWITCHED_بیرون()    افعل { إذا( pxCurrentTCB->px_Task_برچسب != عدم ) v_پورت_Save_Flop_Registers( pxCurrentTCB->px_Task_برچسب ); } طالما( 0 )
#تعریف_کن trace_TASK_SWITCHED_درون()     افعل { إذا( pxCurrentTCB->px_Task_برچسب != عدم ) v_پورت_Restore_Flop_Registers( pxCurrentTCB->px_Task_برچسب ); } طالما( 0 )

/*
 * These macros should be called directly, but through the taskENTER_CRITICAL()
 * and taskEXIT_CRITICAL() macros.
 */
#تعریف_کن پورت_ENABLE_INTERRUPTS()     مجموعه_imask( 0x00 )
#تعریف_کن پورت_DISABLE_INTERRUPTS()    مجموعه_imask( پورت_KERNEL_وقفه_اولویت )

/* Critical nesting counts are stored in the TCB. */
#تعریف_کن پورت_CRITICAL_NESTING_درون_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کن پورت_ENTER_CRITICAL()    vTaskEnterCritical();
#تعریف_کن پورت_EXIT_CRITICAL()     vTaskExitCritical();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
