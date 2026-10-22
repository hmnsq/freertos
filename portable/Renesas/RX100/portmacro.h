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


#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
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
#تعریف_کرو پورٹ_CHAR        حرف
#تعریف_کرو پورٹ_FLOAT       عائم
#تعریف_کرو پورٹ_DOUBLE      مزدوج
#تعریف_کرو پورٹ_LONG        لما
#تعریف_کرو پورٹ_SHORT       چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE  uint32_t
#تعریف_کرو پورٹ_ادھار_TYPE   لما

تعريفنوع پورٹ_ڈھیر_TYPE ڈھیر_Type_t;
تعريفنوع لما ادھار_Type_t;
تعريفنوع بنانشانی لما UBaseType_t;

#إذا( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC 1
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT              8   /* Could make four, according to manual. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH                -1
#تعریف_کرو پورٹ_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_NOP()                       nop()

#ہدایت inline_asm v_پورٹ_Yield
ساكن فراغ v_پورٹ_Yield( فراغ )
{
    /* Save clobbered register - may not actually be necessary if inline asm
    functions are considered to use the same rules as function calls by the
    compiler. */
    ڈالو_2.L R5
    /* Set ITU SWINTR. */
    MOV.L #872E0H, R5
    MOV.B #1, [R5]
    /* Read back to ensure the value is taken before proceeding. */
    MOV.L [R5], R5
    /* Restore clobbered register to its previous value. */
    نکالو_2 R5
}
#تعریف_کرو پورٹ_YIELD() v_پورٹ_Yield()
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x ) افعل { إذا( x != pdFALSE ) { پورٹ_YIELD(); } } طالما( 0 )

/* These macros should not be called directly, but through the
taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
performed if configASSERT() is defined to ensure an assertion handler does not
inadvertently attempt to lower the IPL when the call to assert was triggered
because the IPL value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY
when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
functions are those that end in FromISR.  FreeRTOS maintains a separate
interrupt API to ensure API function and interrupt entry is as fast and as
simple as possible. */
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     سیٹ_ipl( ( لما ) 0 )
#إذا ( configASSERT_DEFINED == 1 )
    #تعریف_کرو پورٹ_ASSERT_IF_رکاوٹ_ترجیح_INVALID() configASSERT( ( get_ipl() <= config_MAX_SYSCALL_رکاوٹ_ترجیح ) )
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    إذا( get_ipl() < config_MAX_SYSCALL_رکاوٹ_ترجیح ) سیٹ_ipl( ( لما ) config_MAX_SYSCALL_رکاوٹ_ترجیح )
#وإلا
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    سیٹ_ipl( ( لما ) config_MAX_SYSCALL_رکاوٹ_ترجیح )
#جے_انت

/* Critical nesting counts are stored in the TCB. */
#تعریف_کرو پورٹ_CRITICAL_NESTING_وچ_TCB ( 1 )

/* The critical nesting functions defined within tasks.c. */
خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کرو پورٹ_ENTER_CRITICAL()    vTaskEnterCritical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()     vTaskExitCritical()

/* As this port allows interrupt nesting... */
#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR() ( UBaseType_t ) get_ipl(); سیٹ_ipl( ( نشانیوالا لما ) config_MAX_SYSCALL_رکاوٹ_ترجیح )
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( ux_Saved_رکاوٹ_حالت ) سیٹ_ipl( ( نشانیوالا لما ) ux_Saved_رکاوٹ_حالت )

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#إذا configUSE_TICKLESS_IDLE == 1
    #جے_بنا_تعریف پورٹ_SUPPRESS_TICKS_AND_SLEEP
        خارجي فراغ v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ویلا );
        #تعریف_کرو پورٹ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_ویلا ) v_پورٹ_Suppress_Ticks_And_Sleep( x_Expected_Idle_ویلا )
    #جے_انت
#جے_انت

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )

#ہدایت inline_asm v_پورٹ_حافظہ_Barrier
ساكن فراغ v_پورٹ_حافظہ_Barrier( فراغ )
{
}

#تعریف_کرو پورٹ_حافظہ_BARRIER()    v_پورٹ_حافظہ_Barrier()

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
