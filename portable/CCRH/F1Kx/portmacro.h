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

#यदि_अपरिभाषितम् PORTMACRO_H
    #परिभाषय PORTMACRO_H

    #यदि_परिभाषितम् __cplusplus
        बाह्य "C"
        {
    #यदि_अन्तः

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
    #परिभाषय पत्तनम्_CHAR          वर्ण
    #परिभाषय पत्तनम्_FLOAT         भिन्न
    #परिभाषय पत्तनम्_DOUBLE        द्विगुण
    #परिभाषय पत्तनम्_LONG          दीर्घ
    #परिभाषय पत्तनम्_SHORT         ह्रस्व
    #परिभाषय पत्तनम्_राशिः_TYPE    uint32_t
    #परिभाषय पत्तनम्_आधारः_TYPE     दीर्घ

    प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
    प्रकारनिर्देश दीर्घ             आधारः_Type_t;
    प्रकारनिर्देश अचिह्नित दीर्घ    UBaseType_t;

/* Defines the maximum time when using a wait command in a task */
    #यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
        प्रकारनिर्देश uint16_t     TickType_t;
        #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffff
    #नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
        प्रकारनिर्देश uint32_t     TickType_t;
        #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1
    #अन्यथा
        #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
    #यदि_अन्तः

/*-----------------------------------------------------------*/

/* Architecture specifics */

    #परिभाषय पत्तनम्_STSR( reg )              __stsr( ( reg ) )
    #परिभाषय पत्तनम्_LDSR( reg, val )         __ldsr( ( reg ), ( val ) )
    #परिभाषय पत्तनम्_STSR_CCRH( reg, sel )    __stsr_rh( ( reg ), ( sel ) )
    #परिभाषय पत्तनम्_SYNCM()                  __syncm()

/* Determine the descending of the stack from high address to address */
    #परिभाषय पत्तनम्_राशिः_GROWTH      ( -1 )

/* Determine the time (in milliseconds) corresponding to each tick */
    #परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )

/* It is a multiple of 4 (the two lower-order bits of the address = 0),
 * otherwise it will cause MAE (Misaligned Exception) according to the manual */
    #परिभाषय पत्तनम्_BYTE_ALIGNMENT    ( 4 )

/* Interrupt control macros. */

    #परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     __EI() /* Macro to enable all maskable interrupts. */
    #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    __DI() /* Macro to disable all maskable interrupts. */
    #परिभाषय taskENABLE_INTERRUPTS()     पत्तनम्_ENABLE_INTERRUPTS()
    #परिभाषय taskDISABLE_INTERRUPTS()    पत्तनम्_DISABLE_INTERRUPTS()

/* SMP build which means configNUM_CORES is relevant */
    #परिभाषय पत्तनम्_SUPPORT_SMP              1

    #परिभाषय पत्तनम्_MAX_CORE_गणनम्           2
    #यदि_अपरिभाषितम् config_सङ्ख्या_सम्बन्धि_CORES
        #परिभाषय config_सङ्ख्या_सम्बन्धि_CORES    1
    #यदि_अन्तः

/*-----------------------------------------------------------*/
/* Scheduler utilities */

/* Called at the end of an ISR that can cause a context switch */
    बाह्य शून्य v_पत्तनम्_समुच्चयः_Switch( आधारः_Type_t xSwitchRequired );

    #परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( x )    v_पत्तनम्_समुच्चयः_Switch( x )

    #परिभाषय पत्तनम्_YIELD_FROM_ISR( x )       पत्तनम्_अन्तः_SWITCHING_ISR( x )

/* Use to transfer control from one task to perform other tasks of
 * higher priority */
    बाह्य शून्य v_पत्तनम्_Yield( शून्य );

    #परिभाषय पत्तनम्_YIELD()    v_पत्तनम्_Yield()
    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

/* Return the core ID on which the code is running. */
        बाह्य आधारः_Type_t x_पत्तनम्_GET_CORE_ID();

        #परिभाषय पत्तनम्_GET_CORE_ID()    x_पत्तनम्_GET_CORE_ID()
        #परिभाषय coreid    x_पत्तनम्_GET_CORE_ID()

/* Request the core ID x to yield. */
        बाह्य शून्य v_पत्तनम्_Yield_Core( uint32_t coreID );

        #परिभाषय पत्तनम्_YIELD_CORE( x )                v_पत्तनम्_Yield_Core( x )

        #परिभाषय पत्तनम्_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
        #परिभाषय पत्तनम्_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )

    #यदि_अन्तः /* if ( configNUMBER_OF_CORES > 1 ) */

    #यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
        #परिभाषय पत्तनम्_GET_ISR_तालकम्( xCoreID )
        #परिभाषय पत्तनम्_RELEASE_ISR_तालकम्( xCoreID )
        #परिभाषय पत्तनम्_GET_TASK_तालकम्( xCoreID )
        #परिभाषय पत्तनम्_RELEASE_TASK_तालकम्( xCoreID )
    #अन्यथा
        बाह्य शून्य v_पत्तनम्_Recursive_तालकम्_Acquire( आधारः_Type_t xCoreID, आधारः_Type_t xFromIsr );
        बाह्य शून्य v_पत्तनम्_Recursive_तालकम्_Release( आधारः_Type_t xCoreID, आधारः_Type_t xFromIsr );

        #परिभाषय पत्तनम्_GET_ISR_तालकम्( xCoreID )         v_पत्तनम्_Recursive_तालकम्_Acquire( ( xCoreID ), pdTRUE )
        #परिभाषय पत्तनम्_RELEASE_ISR_तालकम्( xCoreID )     v_पत्तनम्_Recursive_तालकम्_Release( ( xCoreID ), pdTRUE )
        #परिभाषय पत्तनम्_GET_TASK_तालकम्( xCoreID )        v_पत्तनम्_Recursive_तालकम्_Acquire( ( xCoreID ), pdFALSE )
        #परिभाषय पत्तनम्_RELEASE_TASK_तालकम्( xCoreID )    v_पत्तनम्_Recursive_तालकम्_Release( ( xCoreID ), pdFALSE )
    #यदि_अन्तः /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/
/* Critical section management. */

/* The critical nesting functions defined within tasks.c */

    बाह्य शून्य vTaskEnterCritical( शून्य );
    बाह्य शून्य vTaskExitCritical( शून्य );

/* Macro to mark the start of a critical code region */
    #परिभाषय पत्तनम्_ENTER_CRITICAL()    vTaskEnterCritical()

/* Macro to mark the end of a critical code region */
    #परिभाषय पत्तनम्_EXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/
/* Macros to set and clear the interrupt mask. */
    पत्तनम्_LONG x_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्();
    शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( पत्तनम्_LONG );

    #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()                  x_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()
    #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्( x )             v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( ( x ) )
    #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         x_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()
    #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )    v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( ( x ) )

/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */

    #परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
    #परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

/*-----------------------------------------------------------*/

    #यदि_परिभाषितम् __cplusplus
}
    #यदि_अन्तः
#यदि_अन्तः /* PORTMACRO_H */
