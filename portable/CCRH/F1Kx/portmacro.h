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

    #جے_تعریف_شدہ __cplusplus
        خارجي "C"
        {
    #جے_انت

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
    #تعریف_کرو پورٹ_CHAR          حرف
    #تعریف_کرو پورٹ_FLOAT         عائم
    #تعریف_کرو پورٹ_DOUBLE        مزدوج
    #تعریف_کرو پورٹ_LONG          لما
    #تعریف_کرو پورٹ_SHORT         چھوٹا
    #تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
    #تعریف_کرو پورٹ_ادھار_TYPE     لما

    تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
    تعريفنوع لما             ادھار_Type_t;
    تعريفنوع بنانشانی لما    UBaseType_t;

/* Defines the maximum time when using a wait command in a task */
    #إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
        تعريفنوع uint16_t     TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
        تعريفنوع uint32_t     TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
    #وإلا
        #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
    #جے_انت

/*-----------------------------------------------------------*/

/* Architecture specifics */

    #تعریف_کرو پورٹ_STSR( reg )              __stsr( ( reg ) )
    #تعریف_کرو پورٹ_LDSR( reg, val )         __ldsr( ( reg ), ( val ) )
    #تعریف_کرو پورٹ_STSR_CCRH( reg, sel )    __stsr_rh( ( reg ), ( sel ) )
    #تعریف_کرو پورٹ_SYNCM()                  __syncm()

/* Determine the descending of the stack from high address to address */
    #تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )

/* Determine the time (in milliseconds) corresponding to each tick */
    #تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )

/* It is a multiple of 4 (the two lower-order bits of the address = 0),
 * otherwise it will cause MAE (Misaligned Exception) according to the manual */
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    ( 4 )

/* Interrupt control macros. */

    #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     __EI() /* Macro to enable all maskable interrupts. */
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    __DI() /* Macro to disable all maskable interrupts. */
    #تعریف_کرو taskENABLE_INTERRUPTS()     پورٹ_ENABLE_INTERRUPTS()
    #تعریف_کرو taskDISABLE_INTERRUPTS()    پورٹ_DISABLE_INTERRUPTS()

/* SMP build which means configNUM_CORES is relevant */
    #تعریف_کرو پورٹ_SUPPORT_SMP              1

    #تعریف_کرو پورٹ_MAX_CORE_گنتی           2
    #جے_بنا_تعریف config_نمبر_دا_CORES
        #تعریف_کرو config_نمبر_دا_CORES    1
    #جے_انت

/*-----------------------------------------------------------*/
/* Scheduler utilities */

/* Called at the end of an ISR that can cause a context switch */
    خارجي فراغ v_پورٹ_سیٹ_Switch( ادھار_Type_t xSwitchRequired );

    #تعریف_کرو پورٹ_سرا_SWITCHING_ISR( x )    v_پورٹ_سیٹ_Switch( x )

    #تعریف_کرو پورٹ_YIELD_FROM_ISR( x )       پورٹ_سرا_SWITCHING_ISR( x )

/* Use to transfer control from one task to perform other tasks of
 * higher priority */
    خارجي فراغ v_پورٹ_Yield( فراغ );

    #تعریف_کرو پورٹ_YIELD()    v_پورٹ_Yield()
    #إذا ( config_نمبر_دا_CORES > 1 )

/* Return the core ID on which the code is running. */
        خارجي ادھار_Type_t x_پورٹ_GET_CORE_ID();

        #تعریف_کرو پورٹ_GET_CORE_ID()    x_پورٹ_GET_CORE_ID()
        #تعریف_کرو coreid    x_پورٹ_GET_CORE_ID()

/* Request the core ID x to yield. */
        خارجي فراغ v_پورٹ_Yield_Core( uint32_t coreID );

        #تعریف_کرو پورٹ_YIELD_CORE( x )                v_پورٹ_Yield_Core( x )

        #تعریف_کرو پورٹ_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
        #تعریف_کرو پورٹ_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )

    #جے_انت /* if ( configNUMBER_OF_CORES > 1 ) */

    #إذا ( config_نمبر_دا_CORES == 1 )
        #تعریف_کرو پورٹ_GET_ISR_جندرا( xCoreID )
        #تعریف_کرو پورٹ_RELEASE_ISR_جندرا( xCoreID )
        #تعریف_کرو پورٹ_GET_TASK_جندرا( xCoreID )
        #تعریف_کرو پورٹ_RELEASE_TASK_جندرا( xCoreID )
    #وإلا
        خارجي فراغ v_پورٹ_Recursive_جندرا_Acquire( ادھار_Type_t xCoreID, ادھار_Type_t xFromIsr );
        خارجي فراغ v_پورٹ_Recursive_جندرا_Release( ادھار_Type_t xCoreID, ادھار_Type_t xFromIsr );

        #تعریف_کرو پورٹ_GET_ISR_جندرا( xCoreID )         v_پورٹ_Recursive_جندرا_Acquire( ( xCoreID ), pdTRUE )
        #تعریف_کرو پورٹ_RELEASE_ISR_جندرا( xCoreID )     v_پورٹ_Recursive_جندرا_Release( ( xCoreID ), pdTRUE )
        #تعریف_کرو پورٹ_GET_TASK_جندرا( xCoreID )        v_پورٹ_Recursive_جندرا_Acquire( ( xCoreID ), pdFALSE )
        #تعریف_کرو پورٹ_RELEASE_TASK_جندرا( xCoreID )    v_پورٹ_Recursive_جندرا_Release( ( xCoreID ), pdFALSE )
    #جے_انت /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/
/* Critical section management. */

/* The critical nesting functions defined within tasks.c */

    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );

/* Macro to mark the start of a critical code region */
    #تعریف_کرو پورٹ_ENTER_CRITICAL()    vTaskEnterCritical()

/* Macro to mark the end of a critical code region */
    #تعریف_کرو پورٹ_EXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/
/* Macros to set and clear the interrupt mask. */
    پورٹ_LONG x_پورٹ_سیٹ_رکاوٹ_نقاب();
    فراغ v_پورٹ_Clear_رکاوٹ_نقاب( پورٹ_LONG );

    #تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب()                  x_پورٹ_سیٹ_رکاوٹ_نقاب()
    #تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب( x )             v_پورٹ_Clear_رکاوٹ_نقاب( ( x ) )
    #تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()         x_پورٹ_سیٹ_رکاوٹ_نقاب()
    #تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( x )    v_پورٹ_Clear_رکاوٹ_نقاب( ( x ) )

/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */

    #تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/*-----------------------------------------------------------*/

    #جے_تعریف_شدہ __cplusplus
}
    #جے_انت
#جے_انت /* PORTMACRO_H */
