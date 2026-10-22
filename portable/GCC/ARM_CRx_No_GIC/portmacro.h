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
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
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
#define port_ڈھیر_TYPE    uint32_t
#define portBASE_TYPE     long

تعريفنوع port_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع long             BaseType_t;
تعريفنوع unsigned long    UBaseType_t;

تعريفنوع uint32_t         TickType_t;
#define portMAX_DELAY    ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#define portTICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define port_ڈھیر_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#define portEND_SWITCHING_ISR( xSwitchRequired )      \
    {                                                 \
        خارجي متطاير uint32_t ulPortYieldRequired; \
                                                      \
        إذا( xSwitchRequired != pdFALSE )              \
        {                                             \
            ulPortYieldRequired = pdTRUE;             \
        }                                             \
    }

#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )

فراغ vPortYield( فراغ );

#define portYIELD()     vPortYield();

/*-----------------------------------------------------------*/

/*
 * Critical section management.
 */

خارجي فراغ vPortEnterCritical( فراغ );
خارجي فراغ vPortExitCritical( فراغ );
خارجي فراغ vPortEnableInterrupts( فراغ );
خارجي فراغ vPortDisableInterrupts( فراغ );
خارجي uint32_t ulPortSetInterruptMaskFromISR( فراغ );

/* In the absence of a priority mask register, these functions and macros
 * globally enable and disable interrupts. */
#define portENTER_CRITICAL()                    vPortEnterCritical();
#define portEXIT_CRITICAL()                     vPortExitCritical();
#define portENABLE_INTERRUPTS()                 vPortEnableInterrupts();
#define portDISABLE_INTERRUPTS()                vPortDisableInterrupts();
#define portSET_INTERRUPT_MASK_FROM_ISR()       ulPortSetInterruptMaskFromISR();
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )  افعل { إذا( x == 0 ) portENABLE_INTERRUPTS(); } طالما( 0 )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#endif

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
فراغ FreeRTOS_Tick_Handler( فراغ );

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_Port_گنتی_Leading_Zeros( UBaseType_t ulBitmap );

/* If configUSE_TASK_FPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without an FPU context and must call vPortTaskUsesFPU() to give
 * themselves an FPU context before using any FPU instructions.  If
 * configUSE_TASK_FPU_SUPPORT is set to 2 then all tasks will have an FPU
 * context by default. */
#إذا ( configUSE_TASK_FPU_SUPPORT != 2 )
    فراغ vPortTaskUsesFPU( فراغ );
#وإلا
    /* Each task has an FPU context already, so define this function as a
     * no-op. */
    #define vPortTaskUsesFPU()
#endif
#define portTASK_USES_FLOATING_POINT()    vPortTaskUsesFPU()

#define portLOWEST_INTERRUPT_PRIORITY           ( ( ( uint32_t ) configUNIQUE_INTERRUPT_PRIORITIES ) - 1UL )
#define portLOWEST_USABLE_INTERRUPT_PRIORITY    ( portLOWEST_INTERRUPT_PRIORITY - 1UL )

/* Architecture specific optimisations. */
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#endif

#إذا configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

    /* Store, clear and get the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )
    #define portGET_HIGHEST_PRIORITY( ux_چوٹی_Priority, uxReadyPriorities )  ux_چوٹی_Priority = ( 31UL - ul_Port_گنتی_Leading_Zeros( ( ux_چوٹی_Ready_Priority ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#define portNOP()               __asm متطاير ( "NOP" )
#define portINLINE              __inline
#define portMEMORY_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
