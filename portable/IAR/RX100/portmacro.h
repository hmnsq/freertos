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

#شامل <intrinsics.h>

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
/* *INDENT-ON* */

/* Hardware specifics. */
#شامل "machine.h"

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
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    8         /* Could make four, according to manual. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH      -1
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_NOP()    __no_operation()

#تعریف_کرو پورٹ_YIELD()                     \
    __asm متلون                      \
    (                                   \
        "MOV.L #0x872E0, R15        \n" \
        "MOV.B #1, [R15]            \n" \
        "MOV.L [R15], R15           \n" \
        ::: "R15"                       \
    )

#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )                           کرو { اگر( ( x ) != pdFALSE ) { پورٹ_YIELD(); } } جب( 0 )

/* These macros should not be called directly, but through the
 * taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
 * performed if configASSERT() is defined to ensure an assertion handler does not
 * inadvertently attempt to lower the IPL when the call to assert was triggered
 * because the IPL value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY
 * when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
 * functions are those that end in FromISR.  FreeRTOS maintains a separate
 * interrupt API to ensure API function and interrupt entry is as fast and as
 * simple as possible. */
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                           __set_interrupt_level( ( uint8_t ) 0 )
#اگر ( configASSERT_DEFINED == 1 )
    #تعریف_کرو پورٹ_ASSERT_IF_مداخلت_ترجیح_INVALID()    configASSERT( ( __get_interrupt_level() <= config_MAX_SYSCALL_مداخلت_ترجیح ) )
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                      اگر( __get_interrupt_level() < config_MAX_SYSCALL_مداخلت_ترجیح ) __set_interrupt_level( ( uint8_t ) config_MAX_SYSCALL_مداخلت_ترجیح )
#ورنہ
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                      __set_interrupt_level( ( uint8_t ) config_MAX_SYSCALL_مداخلت_ترجیح )
#اگر_ختم

/* Critical nesting counts are stored in the TCB. */
#تعریف_کرو پورٹ_CRITICAL_NESTING_اندر_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
خارجی خالی vTaskEnterCritical( خالی );
خارجی خالی vTaskExitCritical( خالی );
#تعریف_کرو پورٹ_ENTER_CRITICAL()                                           vTaskEnterCritical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()                                            vTaskExitCritical()

/* As this port allows interrupt nesting... */
#تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR()                              __get_interrupt_level(); پورٹ_DISABLE_INTERRUPTS()
#تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( ux_Saved_مداخلت_حالت )    __set_interrupt_level( ( uint8_t ) ( ux_Saved_مداخلت_حالت ) )

/* Tickless idle/low power functionality. */
#اگر configUSE_TICKLESS_IDLE == 1
    #اگر_غیر_تعریف_شدہ پورٹ_SUPPRESS_TICKS_AND_SLEEP
        خارجی خالی v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت );
        #تعریف_کرو پورٹ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_وقت )    v_پورٹ_Suppress_Ticks_And_Sleep( x_Expected_Idle_وقت )
    #اگر_ختم
#اگر_ختم

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

/* Prevent warnings of undefined behaviour: the order of volatile accesses is
 * undefined - all warnings have been manually checked and are not an issue, and
 * the warnings cannot be prevent by code changes without undesirable effects. */
#ہدایت diag_suppress=Pa082

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
