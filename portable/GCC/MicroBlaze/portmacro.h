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

#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    خارجي "C" {
#endif
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

/* Type definitions. */
#define portCHAR          حرف
#define portFLOAT         عائم
#define portDOUBLE        مزدوج
#define portLONG          long
#define portSHORT         short
#define port_تيندنن_TYPE    uint32_t
#define portBASE_TYPE     long

تعريفنوع port_تيندنن_TYPE   تيندنن_Type_t;
تعريفنوع long             BaseType_t;
تعريفنوع unsigned long    UBaseType_t;

#إذا ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    تعريفنوع uint16_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    تعريفنوع uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#وإلا
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
فراغ microblaze_disable_interrupts( فراغ );
فراغ microblaze_enable_interrupts( فراغ );
#define portDISABLE_INTERRUPTS()    microblaze_disable_interrupts()
#define portENABLE_INTERRUPTS()     microblaze_enable_interrupts()
/*-----------------------------------------------------------*/

/* Critical section macros. */
فراغ vPortEnterCritical( فراغ );
فراغ vPortExitCritical( فراغ );
#define portENTER_CRITICAL()                  \
    {                                         \
        خارجي UBaseType_t uxCriticalNesting; \
        microblaze_disable_interrupts();      \
        uxCriticalNesting++;                  \
    }

#define portEXIT_CRITICAL()                      \
    {                                            \
        خارجي UBaseType_t uxCriticalNesting;    \
        /* Interrupts are disabled, so we can */ \
        /* access the variable directly. */      \
        uxCriticalNesting--;                     \
        إذا( uxCriticalNesting == 0 )             \
        {                                        \
            /* The nesting has unwound and we \
             * can enable interrupts again. */ \
            portENABLE_INTERRUPTS();           \
        }                                      \
    }

/*-----------------------------------------------------------*/

/* Task utilities. */
فراغ vPortYield( فراغ );
#define portYIELD()             vPortYield()

فراغ vTaskSwitchContext();
#define portYIELD_FROM_ISR()    vTaskSwitchContext()
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT    4
#define port_تيندنن_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portNOP()               asm متطاير ( "NOP" )
#define portMEMORY_BARRIER()    asm متطاير ( "" ::: "memory" )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
