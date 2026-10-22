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


#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
/* *INDENT-ON* */

/* Hardware specifics. */
#ضمن "machine.h"

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions - these are a bit legacy and not really used now, other
than portSTACK_TYPE and portBASE_TYPE. */
#تعریف_کړه پورټ_CHAR        حرف
#تعریف_کړه پورټ_FLOAT       عائم
#تعریف_کړه پورټ_DOUBLE      مزدوج
#تعریف_کړه پورټ_LONG        اوږد
#تعریف_کړه پورټ_SHORT       لنډ
#تعریف_کړه پورټ_ډېری_TYPE  uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE   اوږد

تعريفنوع پورټ_ډېری_TYPE ډېری_Type_t;
تعريفنوع اوږد بنسټ_Type_t;
تعريفنوع بینښه اوږد UBaseType_t;

#إذا( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC 1
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_BYTE_ALIGNMENT              8   /* Could make four, according to manual. */
#تعریف_کړه پورټ_ډېری_GROWTH                -1
#تعریف_کړه پورټ_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_NOP()                       nop()

#لارښوونه inline_asm v_پورټ_Yield
ساكن فراغ v_پورټ_Yield( فراغ )
{
    /* Save clobbered register - may not actually be necessary if inline asm
    functions are considered to use the same rules as function calls by the
    compiler. */
    ټېل_2.L R5
    /* Set ITU SWINTR. */
    MOV.L #872E0H, R5
    MOV.B #1, [R5]
    /* Read back to ensure the value is taken before proceeding. */
    MOV.L [R5], R5
    /* Restore clobbered register to its previous value. */
    راوباسه_2 R5
}
#تعریف_کړه پورټ_YIELD() v_پورټ_Yield()
#تعریف_کړه پورټ_YIELD_FROM_ISR( x ) افعل { إذا( x != pdFALSE ) { پورټ_YIELD(); } } طالما( 0 )

/* These macros should not be called directly, but through the
taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
performed if configASSERT() is defined to ensure an assertion handler does not
inadvertently attempt to lower the IPL when the call to assert was triggered
because the IPL value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY
when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
functions are those that end in FromISR.  FreeRTOS maintains a separate
interrupt API to ensure API function and interrupt entry is as fast and as
simple as possible. */
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     سېټ_ipl( ( اوږد ) 0 )
#إذا ( configASSERT_DEFINED == 1 )
    #تعریف_کړه پورټ_ASSERT_IF_مداخله_لومړیتوب_INVALID() configASSERT( ( get_ipl() <= config_MAX_SYSCALL_مداخله_لومړیتوب ) )
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()    إذا( get_ipl() < config_MAX_SYSCALL_مداخله_لومړیتوب ) سېټ_ipl( ( اوږد ) config_MAX_SYSCALL_مداخله_لومړیتوب )
#وإلا
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()    سېټ_ipl( ( اوږد ) config_MAX_SYSCALL_مداخله_لومړیتوب )
#د_که_پای

/* Critical nesting counts are stored in the TCB. */
#تعریف_کړه پورټ_CRITICAL_NESTING_دننه_TCB ( 1 )

/* The critical nesting functions defined within tasks.c. */
خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کړه پورټ_ENTER_CRITICAL()    vTaskEnterCritical()
#تعریف_کړه پورټ_EXIT_CRITICAL()     vTaskExitCritical()

/* As this port allows interrupt nesting... */
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR() ( UBaseType_t ) get_ipl(); سېټ_ipl( ( نښهدار اوږد ) config_MAX_SYSCALL_مداخله_لومړیتوب )
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( ux_Saved_مداخله_حالت ) سېټ_ipl( ( نښهدار اوږد ) ux_Saved_مداخله_حالت )

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#إذا configUSE_TICKLESS_IDLE == 1
    #که_نه_تعریف_شوی پورټ_SUPPRESS_TICKS_AND_SLEEP
        خارجي فراغ v_پورټ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وخت );
        #تعریف_کړه پورټ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_وخت ) v_پورټ_Suppress_Ticks_And_Sleep( x_Expected_Idle_وخت )
    #د_که_پای
#د_که_پای

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )

#لارښوونه inline_asm v_پورټ_حافظه_Barrier
ساكن فراغ v_پورټ_حافظه_Barrier( فراغ )
{
}

#تعریف_کړه پورټ_حافظه_BARRIER()    v_پورټ_حافظه_Barrier()

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
