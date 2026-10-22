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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
    #وصف_ڪريو PORTMACRO_H

    #جيڪڏهن_وصف_ٿيل __cplusplus
        خارجي "C"
        {
    #جيڪڏهن_پورو

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
    #وصف_ڪريو پورٽ_CHAR          حرف
    #وصف_ڪريو پورٽ_FLOAT         عائم
    #وصف_ڪريو پورٽ_DOUBLE        مزدوج
    #وصف_ڪريو پورٽ_LONG          ڊگهو
    #وصف_ڪريو پورٽ_SHORT         ننڍو
    #وصف_ڪريو پورٽ_ڍير_TYPE    uint32_t
    #وصف_ڪريو پورٽ_بنياد_TYPE     ڊگهو

    تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
    تعريفنوع ڊگهو             بنياد_Type_t;
    تعريفنوع بنانشان ڊگهو    UBaseType_t;

/* Defines the maximum time when using a wait command in a task */
    #إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
        تعريفنوع uint16_t     TickType_t;
        #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
        تعريفنوع uint32_t     TickType_t;
        #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1
    #وإلا
        #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
    #جيڪڏهن_پورو

/*-----------------------------------------------------------*/

/* Architecture specifics */

    #وصف_ڪريو پورٽ_STSR( reg )              __stsr( ( reg ) )
    #وصف_ڪريو پورٽ_LDSR( reg, val )         __ldsr( ( reg ), ( val ) )
    #وصف_ڪريو پورٽ_STSR_CCRH( reg, sel )    __stsr_rh( ( reg ), ( sel ) )
    #وصف_ڪريو پورٽ_SYNCM()                  __syncm()

/* Determine the descending of the stack from high address to address */
    #وصف_ڪريو پورٽ_ڍير_GROWTH      ( -1 )

/* Determine the time (in milliseconds) corresponding to each tick */
    #وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )

/* It is a multiple of 4 (the two lower-order bits of the address = 0),
 * otherwise it will cause MAE (Misaligned Exception) according to the manual */
    #وصف_ڪريو پورٽ_BYTE_ALIGNMENT    ( 4 )

/* Interrupt control macros. */

    #وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     __EI() /* Macro to enable all maskable interrupts. */
    #وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    __DI() /* Macro to disable all maskable interrupts. */
    #وصف_ڪريو taskENABLE_INTERRUPTS()     پورٽ_ENABLE_INTERRUPTS()
    #وصف_ڪريو taskDISABLE_INTERRUPTS()    پورٽ_DISABLE_INTERRUPTS()

/* SMP build which means configNUM_CORES is relevant */
    #وصف_ڪريو پورٽ_SUPPORT_SMP              1

    #وصف_ڪريو پورٽ_MAX_CORE_ڳڻپ           2
    #جيڪڏهن_وصف_نه_ٿيل config_عدد_جو_CORES
        #وصف_ڪريو config_عدد_جو_CORES    1
    #جيڪڏهن_پورو

/*-----------------------------------------------------------*/
/* Scheduler utilities */

/* Called at the end of an ISR that can cause a context switch */
    خارجي فراغ v_پورٽ_سيٽ_Switch( بنياد_Type_t xSwitchRequired );

    #وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( x )    v_پورٽ_سيٽ_Switch( x )

    #وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )       پورٽ_پڇاڙي_SWITCHING_ISR( x )

/* Use to transfer control from one task to perform other tasks of
 * higher priority */
    خارجي فراغ v_پورٽ_Yield( فراغ );

    #وصف_ڪريو پورٽ_YIELD()    v_پورٽ_Yield()
    #إذا ( config_عدد_جو_CORES > 1 )

/* Return the core ID on which the code is running. */
        خارجي بنياد_Type_t x_پورٽ_GET_CORE_ID();

        #وصف_ڪريو پورٽ_GET_CORE_ID()    x_پورٽ_GET_CORE_ID()
        #وصف_ڪريو coreid    x_پورٽ_GET_CORE_ID()

/* Request the core ID x to yield. */
        خارجي فراغ v_پورٽ_Yield_Core( uint32_t coreID );

        #وصف_ڪريو پورٽ_YIELD_CORE( x )                v_پورٽ_Yield_Core( x )

        #وصف_ڪريو پورٽ_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
        #وصف_ڪريو پورٽ_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )

    #جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES > 1 ) */

    #إذا ( config_عدد_جو_CORES == 1 )
        #وصف_ڪريو پورٽ_GET_ISR_تالو( xCoreID )
        #وصف_ڪريو پورٽ_RELEASE_ISR_تالو( xCoreID )
        #وصف_ڪريو پورٽ_GET_TASK_تالو( xCoreID )
        #وصف_ڪريو پورٽ_RELEASE_TASK_تالو( xCoreID )
    #وإلا
        خارجي فراغ v_پورٽ_Recursive_تالو_Acquire( بنياد_Type_t xCoreID, بنياد_Type_t xFromIsr );
        خارجي فراغ v_پورٽ_Recursive_تالو_Release( بنياد_Type_t xCoreID, بنياد_Type_t xFromIsr );

        #وصف_ڪريو پورٽ_GET_ISR_تالو( xCoreID )         v_پورٽ_Recursive_تالو_Acquire( ( xCoreID ), pdTRUE )
        #وصف_ڪريو پورٽ_RELEASE_ISR_تالو( xCoreID )     v_پورٽ_Recursive_تالو_Release( ( xCoreID ), pdTRUE )
        #وصف_ڪريو پورٽ_GET_TASK_تالو( xCoreID )        v_پورٽ_Recursive_تالو_Acquire( ( xCoreID ), pdFALSE )
        #وصف_ڪريو پورٽ_RELEASE_TASK_تالو( xCoreID )    v_پورٽ_Recursive_تالو_Release( ( xCoreID ), pdFALSE )
    #جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/
/* Critical section management. */

/* The critical nesting functions defined within tasks.c */

    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );

/* Macro to mark the start of a critical code region */
    #وصف_ڪريو پورٽ_ENTER_CRITICAL()    vTaskEnterCritical()

/* Macro to mark the end of a critical code region */
    #وصف_ڪريو پورٽ_EXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/
/* Macros to set and clear the interrupt mask. */
    پورٽ_LONG x_پورٽ_سيٽ_مداخلت_نقاب();
    فراغ v_پورٽ_Clear_مداخلت_نقاب( پورٽ_LONG );

    #وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب()                  x_پورٽ_سيٽ_مداخلت_نقاب()
    #وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب( x )             v_پورٽ_Clear_مداخلت_نقاب( ( x ) )
    #وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()         x_پورٽ_سيٽ_مداخلت_نقاب()
    #وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_پورٽ_Clear_مداخلت_نقاب( ( x ) )

/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */

    #وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/*-----------------------------------------------------------*/

    #جيڪڏهن_وصف_ٿيل __cplusplus
}
    #جيڪڏهن_پورو
#جيڪڏهن_پورو /* PORTMACRO_H */
