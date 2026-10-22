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

    #که_تعریف_شوی __cplusplus
        خارجي "C"
        {
    #د_که_پای

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
    #تعریف_کړه پورټ_CHAR          حرف
    #تعریف_کړه پورټ_FLOAT         عائم
    #تعریف_کړه پورټ_DOUBLE        مزدوج
    #تعریف_کړه پورټ_LONG          اوږد
    #تعریف_کړه پورټ_SHORT         لنډ
    #تعریف_کړه پورټ_ډېری_TYPE    uint32_t
    #تعریف_کړه پورټ_بنسټ_TYPE     اوږد

    تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
    تعريفنوع اوږد             بنسټ_Type_t;
    تعريفنوع بینښه اوږد    UBaseType_t;

/* Defines the maximum time when using a wait command in a task */
    #إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
        تعريفنوع uint16_t     TickType_t;
        #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
        تعريفنوع uint32_t     TickType_t;
        #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
    #وإلا
        #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
    #د_که_پای

/*-----------------------------------------------------------*/

/* Architecture specifics */

    #تعریف_کړه پورټ_STSR( reg )              __stsr( ( reg ) )
    #تعریف_کړه پورټ_LDSR( reg, val )         __ldsr( ( reg ), ( val ) )
    #تعریف_کړه پورټ_STSR_CCRH( reg, sel )    __stsr_rh( ( reg ), ( sel ) )
    #تعریف_کړه پورټ_SYNCM()                  __syncm()

/* Determine the descending of the stack from high address to address */
    #تعریف_کړه پورټ_ډېری_GROWTH      ( -1 )

/* Determine the time (in milliseconds) corresponding to each tick */
    #تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )

/* It is a multiple of 4 (the two lower-order bits of the address = 0),
 * otherwise it will cause MAE (Misaligned Exception) according to the manual */
    #تعریف_کړه پورټ_BYTE_ALIGNMENT    ( 4 )

/* Interrupt control macros. */

    #تعریف_کړه پورټ_ENABLE_INTERRUPTS()     __EI() /* Macro to enable all maskable interrupts. */
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()    __DI() /* Macro to disable all maskable interrupts. */
    #تعریف_کړه taskENABLE_INTERRUPTS()     پورټ_ENABLE_INTERRUPTS()
    #تعریف_کړه taskDISABLE_INTERRUPTS()    پورټ_DISABLE_INTERRUPTS()

/* SMP build which means configNUM_CORES is relevant */
    #تعریف_کړه پورټ_SUPPORT_SMP              1

    #تعریف_کړه پورټ_MAX_CORE_شمېر           2
    #که_نه_تعریف_شوی config_شمېره_د_CORES
        #تعریف_کړه config_شمېره_د_CORES    1
    #د_که_پای

/*-----------------------------------------------------------*/
/* Scheduler utilities */

/* Called at the end of an ISR that can cause a context switch */
    خارجي فراغ v_پورټ_سېټ_Switch( بنسټ_Type_t xSwitchRequired );

    #تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( x )    v_پورټ_سېټ_Switch( x )

    #تعریف_کړه پورټ_YIELD_FROM_ISR( x )       پورټ_پای_ټکی_SWITCHING_ISR( x )

/* Use to transfer control from one task to perform other tasks of
 * higher priority */
    خارجي فراغ v_پورټ_Yield( فراغ );

    #تعریف_کړه پورټ_YIELD()    v_پورټ_Yield()
    #إذا ( config_شمېره_د_CORES > 1 )

/* Return the core ID on which the code is running. */
        خارجي بنسټ_Type_t x_پورټ_GET_CORE_ID();

        #تعریف_کړه پورټ_GET_CORE_ID()    x_پورټ_GET_CORE_ID()
        #تعریف_کړه coreid    x_پورټ_GET_CORE_ID()

/* Request the core ID x to yield. */
        خارجي فراغ v_پورټ_Yield_Core( uint32_t coreID );

        #تعریف_کړه پورټ_YIELD_CORE( x )                v_پورټ_Yield_Core( x )

        #تعریف_کړه پورټ_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
        #تعریف_کړه پورټ_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )

    #د_که_پای /* if ( configNUMBER_OF_CORES > 1 ) */

    #إذا ( config_شمېره_د_CORES == 1 )
        #تعریف_کړه پورټ_GET_ISR_قلف( xCoreID )
        #تعریف_کړه پورټ_RELEASE_ISR_قلف( xCoreID )
        #تعریف_کړه پورټ_GET_TASK_قلف( xCoreID )
        #تعریف_کړه پورټ_RELEASE_TASK_قلف( xCoreID )
    #وإلا
        خارجي فراغ v_پورټ_Recursive_قلف_Acquire( بنسټ_Type_t xCoreID, بنسټ_Type_t xFromIsr );
        خارجي فراغ v_پورټ_Recursive_قلف_Release( بنسټ_Type_t xCoreID, بنسټ_Type_t xFromIsr );

        #تعریف_کړه پورټ_GET_ISR_قلف( xCoreID )         v_پورټ_Recursive_قلف_Acquire( ( xCoreID ), pdTRUE )
        #تعریف_کړه پورټ_RELEASE_ISR_قلف( xCoreID )     v_پورټ_Recursive_قلف_Release( ( xCoreID ), pdTRUE )
        #تعریف_کړه پورټ_GET_TASK_قلف( xCoreID )        v_پورټ_Recursive_قلف_Acquire( ( xCoreID ), pdFALSE )
        #تعریف_کړه پورټ_RELEASE_TASK_قلف( xCoreID )    v_پورټ_Recursive_قلف_Release( ( xCoreID ), pdFALSE )
    #د_که_پای /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/
/* Critical section management. */

/* The critical nesting functions defined within tasks.c */

    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );

/* Macro to mark the start of a critical code region */
    #تعریف_کړه پورټ_ENTER_CRITICAL()    vTaskEnterCritical()

/* Macro to mark the end of a critical code region */
    #تعریف_کړه پورټ_EXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/
/* Macros to set and clear the interrupt mask. */
    پورټ_LONG x_پورټ_سېټ_مداخله_ماسک();
    فراغ v_پورټ_Clear_مداخله_ماسک( پورټ_LONG );

    #تعریف_کړه پورټ_سېټ_مداخله_ماسک()                  x_پورټ_سېټ_مداخله_ماسک()
    #تعریف_کړه پورټ_CLEAR_مداخله_ماسک( x )             v_پورټ_Clear_مداخله_ماسک( ( x ) )
    #تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()         x_پورټ_سېټ_مداخله_ماسک()
    #تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x )    v_پورټ_Clear_مداخله_ماسک( ( x ) )

/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */

    #تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/*-----------------------------------------------------------*/

    #که_تعریف_شوی __cplusplus
}
    #د_که_پای
#د_که_پای /* PORTMACRO_H */
