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

    #اگر_تعریف_شده __cplusplus
        خارجي "C"
        {
    #پایان_اگر

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions - These are a bit legacy and not really used now, other
 * than portSTACK_TYPE and portBASE_TYPE. */
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

/* Defines the maximum time when using a wait command in a task */
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

/* Architecture specifics */

    #تعریف_کن پورت_STSR( reg )              __stsr( ( reg ) )
    #تعریف_کن پورت_LDSR( reg, val )         __ldsr( ( reg ), ( val ) )
    #تعریف_کن پورت_STSR_CCRH( reg, sel )    __stsr_rh( ( reg ), ( sel ) )
    #تعریف_کن پورت_SYNCM()                  __syncm()

/* Determine the descending of the stack from high address to address */
    #تعریف_کن پورت_پشته_GROWTH      ( -1 )

/* Determine the time (in milliseconds) corresponding to each tick */
    #تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )

/* It is a multiple of 4 (the two lower-order bits of the address = 0),
 * otherwise it will cause MAE (Misaligned Exception) according to the manual */
    #تعریف_کن پورت_BYTE_ALIGNMENT    ( 4 )

/* Interrupt control macros. */

    #تعریف_کن پورت_ENABLE_INTERRUPTS()     __EI() /* Macro to enable all maskable interrupts. */
    #تعریف_کن پورت_DISABLE_INTERRUPTS()    __DI() /* Macro to disable all maskable interrupts. */
    #تعریف_کن taskENABLE_INTERRUPTS()     پورت_ENABLE_INTERRUPTS()
    #تعریف_کن taskDISABLE_INTERRUPTS()    پورت_DISABLE_INTERRUPTS()

/* SMP build which means configNUM_CORES is relevant */
    #تعریف_کن پورت_SUPPORT_SMP              1

    #تعریف_کن پورت_MAX_CORE_شمار           2
    #اگر_تعریف_نشده config_عدد_از_CORES
        #تعریف_کن config_عدد_از_CORES    1
    #پایان_اگر

/*-----------------------------------------------------------*/
/* Scheduler utilities */

/* Called at the end of an ISR that can cause a context switch */
    خارجي فراغ v_پورت_مجموعه_Switch( پایه_Type_t xSwitchRequired );

    #تعریف_کن پورت_انتها_SWITCHING_ISR( x )    v_پورت_مجموعه_Switch( x )

    #تعریف_کن پورت_YIELD_FROM_ISR( x )       پورت_انتها_SWITCHING_ISR( x )

/* Use to transfer control from one task to perform other tasks of
 * higher priority */
    خارجي فراغ v_پورت_Yield( فراغ );

    #تعریف_کن پورت_YIELD()    v_پورت_Yield()
    #إذا ( config_عدد_از_CORES > 1 )

/* Return the core ID on which the code is running. */
        خارجي پایه_Type_t x_پورت_GET_CORE_ID();

        #تعریف_کن پورت_GET_CORE_ID()    x_پورت_GET_CORE_ID()
        #تعریف_کن coreid    x_پورت_GET_CORE_ID()

/* Request the core ID x to yield. */
        خارجي فراغ v_پورت_Yield_Core( uint32_t coreID );

        #تعریف_کن پورت_YIELD_CORE( x )                v_پورت_Yield_Core( x )

        #تعریف_کن پورت_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
        #تعریف_کن پورت_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )

    #پایان_اگر /* if ( configNUMBER_OF_CORES > 1 ) */

    #إذا ( config_عدد_از_CORES == 1 )
        #تعریف_کن پورت_GET_ISR_قفل( xCoreID )
        #تعریف_کن پورت_RELEASE_ISR_قفل( xCoreID )
        #تعریف_کن پورت_GET_TASK_قفل( xCoreID )
        #تعریف_کن پورت_RELEASE_TASK_قفل( xCoreID )
    #وإلا
        خارجي فراغ v_پورت_Recursive_قفل_Acquire( پایه_Type_t xCoreID, پایه_Type_t xFromIsr );
        خارجي فراغ v_پورت_Recursive_قفل_Release( پایه_Type_t xCoreID, پایه_Type_t xFromIsr );

        #تعریف_کن پورت_GET_ISR_قفل( xCoreID )         v_پورت_Recursive_قفل_Acquire( ( xCoreID ), pdTRUE )
        #تعریف_کن پورت_RELEASE_ISR_قفل( xCoreID )     v_پورت_Recursive_قفل_Release( ( xCoreID ), pdTRUE )
        #تعریف_کن پورت_GET_TASK_قفل( xCoreID )        v_پورت_Recursive_قفل_Acquire( ( xCoreID ), pdFALSE )
        #تعریف_کن پورت_RELEASE_TASK_قفل( xCoreID )    v_پورت_Recursive_قفل_Release( ( xCoreID ), pdFALSE )
    #پایان_اگر /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/
/* Critical section management. */

/* The critical nesting functions defined within tasks.c */

    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );

/* Macro to mark the start of a critical code region */
    #تعریف_کن پورت_ENTER_CRITICAL()    vTaskEnterCritical()

/* Macro to mark the end of a critical code region */
    #تعریف_کن پورت_EXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/
/* Macros to set and clear the interrupt mask. */
    پورت_LONG x_پورت_مجموعه_وقفه_ماسک();
    فراغ v_پورت_Clear_وقفه_ماسک( پورت_LONG );

    #تعریف_کن پورت_مجموعه_وقفه_ماسک()                  x_پورت_مجموعه_وقفه_ماسک()
    #تعریف_کن پورت_CLEAR_وقفه_ماسک( x )             v_پورت_Clear_وقفه_ماسک( ( x ) )
    #تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()         x_پورت_مجموعه_وقفه_ماسک()
    #تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( x )    v_پورت_Clear_وقفه_ماسک( ( x ) )

/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */

    #تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/*-----------------------------------------------------------*/

    #اگر_تعریف_شده __cplusplus
}
    #پایان_اگر
#پایان_اگر /* PORTMACRO_H */
