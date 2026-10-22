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

/* When the FIT configurator or the Smart Configurator is used, platform.h has to be
 * used. */
#اگر_تعریف_نشده config_INCLUDE_PLATFORM_H_INSTEAD_از_IODEFINE_H
    #تعریف_کن config_INCLUDE_PLATFORM_H_INSTEAD_از_IODEFINE_H    0
#پایان_اگر

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
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کن پورت_BYTE_ALIGNMENT    8         /* Could make four, according to manual. */
#تعریف_کن پورت_پشته_GROWTH      -1
#تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_NOP()    __asm متطاير ( "NOP" )

/* Save clobbered register, set ITU SWINR (at address 0x872E0), read the value
 * back to ensure it is set before continuing, then restore the clobbered
 * register. */
#تعریف_کن پورت_YIELD()                       \
    __asm متطاير                        \
    (                                     \
        "MOV.L #0x872E0, r5         \n\t" \
        "MOV.B #1, [r5]             \n\t" \
        "MOV.L [r5], r5             \n\t" \
        ::: "r5"                          \
    )

#تعریف_کن پورت_YIELD_FROM_ISR( x )                           افعل { إذا( x != pdFALSE ) { پورت_YIELD(); } } طالما( 0 )

/* These macros should not be called directly, but through the
 * taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
 * performed if configASSERT() is defined to ensure an assertion handler does not
 * inadvertently attempt to lower the IPL when the call to assert was triggered
 * because the IPL value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY
 * when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
 * functions are those that end in FromISR.  FreeRTOS maintains a separate
 * interrupt API to ensure API function and interrupt entry is as fast and as
 * simple as possible. */
#تعریف_کن پورت_ENABLE_INTERRUPTS()                           __asm متطاير ( "MVTIPL    #0" )
#إذا ( configASSERT_DEFINED == 1 )
    #تعریف_کن پورت_ASSERT_IF_وقفه_اولویت_INVALID()    configASSERT( ( ul_پورت_Get_IPL() <= config_MAX_SYSCALL_وقفه_اولویت ) )
    #تعریف_کن پورت_DISABLE_INTERRUPTS()                      إذا( ul_پورت_Get_IPL() < config_MAX_SYSCALL_وقفه_اولویت ) __asm متطاير( "MVTIPL    %0" ::"i" ( config_MAX_SYSCALL_وقفه_اولویت ) )
#وإلا
    #تعریف_کن پورت_DISABLE_INTERRUPTS()                      __asm متطاير ( "MVTIPL    %0" ::"i" ( config_MAX_SYSCALL_وقفه_اولویت ) )
#پایان_اگر

/* Critical nesting counts are stored in the TCB. */
#تعریف_کن پورت_CRITICAL_NESTING_درون_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کن پورت_ENTER_CRITICAL()    vTaskEnterCritical()
#تعریف_کن پورت_EXIT_CRITICAL()     vTaskExitCritical()

/* As this port allows interrupt nesting... */
uint32_t ul_پورت_Get_IPL( فراغ ) __attribute__( ( naked ) );
فراغ v_پورت_مجموعه_IPL( uint32_t ulNewIPL ) __attribute__( ( naked ) );
#تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()                              ul_پورت_Get_IPL(); پورت_DISABLE_INTERRUPTS()
#تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( ux_Saved_وقفه_وضعیت )    v_پورت_مجموعه_IPL( ux_Saved_وقفه_وضعیت )

/* Tickless idle/low power functionality. */
#إذا configUSE_TICKLESS_IDLE == 1
    #اگر_تعریف_نشده پورت_SUPPRESS_TICKS_AND_SLEEP
        خارجي فراغ v_پورت_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_زمان );
        #تعریف_کن پورت_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_زمان )    v_پورت_Suppress_Ticks_And_Sleep( x_Expected_Idle_زمان )
    #پایان_اگر
#پایان_اگر

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کن پورت_حافظه_BARRIER()                                  __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
