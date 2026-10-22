/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright 2020 Cambridge Consultants Ltd.
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
    ಬಾಹ್ಯ "C" {
#endif
/* *INDENT-ON* */

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

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
#define portCHAR                 ವರ್ಣ
#define portFLOAT                ಭಿನ್ನ
#define portDOUBLE               ದ್ವಿಗುಣ
#define portLONG                 long
#define portSHORT                short
#define port_ರಾಶಿ_TYPE           unsigned long
#define portBASE_TYPE            long
#define portPOINTER_SIZE_TYPE    intptr_t

ಪ್ರಕಾರನಿರ್ದೇಶ port_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರನಿರ್ದೇಶ long             BaseType_t;
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned long    UBaseType_t;

ಪ್ರಕಾರನಿರ್ದೇಶ unsigned long    TickType_t;
#define portMAX_DELAY              ( ( TickType_t ) ULONG_MAX )

#define portTICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_ರಾಶಿ_GROWTH                   ( -1 )
#define port_HAS_ರಾಶಿ_OVERFLOW_CHECKING    ( 1 )
#define portTICK_PERIOD_MS                 ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portTICK_RATE_MICROSECONDS         ( ( TickType_t ) 1000000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT                 8
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
ಬಾಹ್ಯ ಶೂನ್ಯ vPortYield( ಶೂನ್ಯ );

#define portYIELD()                vPortYield()

#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    ಕುರು                                           \
    {                                            \
        ಯದಿ( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            vPortYield();                        \
        }                                        \
        ಅನ್ಯಥಾ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } ಯಾವತ್( 0 )
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
ಬಾಹ್ಯ ಶೂನ್ಯ vPortDisableInterrupts( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vPortEnableInterrupts( ಶೂನ್ಯ );
#define portSET_INTERRUPT_MASK()      ( vPortDisableInterrupts() )
#define portCLEAR_INTERRUPT_MASK()    ( vPortEnableInterrupts() )

ಬಾಹ್ಯ UBaseType_t xPortSetInterruptMask( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vPortClearInterruptMask( UBaseType_t xMask );

ಬಾಹ್ಯ ಶೂನ್ಯ vPortEnterCritical( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vPortExitCritical( ಶೂನ್ಯ );
#define portSET_INTERRUPT_MASK_FROM_ISR()         xPortSetInterruptMask()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortClearInterruptMask( x )
#define portDISABLE_INTERRUPTS()                  portSET_INTERRUPT_MASK()
#define portENABLE_INTERRUPTS()                   portCLEAR_INTERRUPT_MASK()
#define portENTER_CRITICAL()                      vPortEnterCritical()
#define portEXIT_CRITICAL()                       vPortExitCritical()

/*-----------------------------------------------------------*/

ಬಾಹ್ಯ ಶೂನ್ಯ vPortThreadDying( ಶೂನ್ಯ * pxTaskToDelete,
                              ಚಞ್ಚಲ BaseType_t * pxPendYield );
ಬಾಹ್ಯ ಶೂನ್ಯ vPortCancelThread( ಶೂನ್ಯ * pxTaskToDelete );
#define portPRE_TASK_DELETE_HOOK( pvTaskToDelete, pxPendYield )    vPortThreadDying( ( pvTaskToDelete ), ( pxPendYield ) )
#define portCLEAN_UP_TCB( pxTCB )                                  vPortCancelThread( pxTCB )
/*-----------------------------------------------------------*/

#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )         ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters ) __attribute__( ( noreturn ) )
#define portTASK_FUNCTION( vFunction, pvParameters )               ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
/*-----------------------------------------------------------*/

/*
 * Tasks run in their own pthreads and context switches between them
 * are always a full memory barrier. ISRs are emulated as signals
 * which also imply a full memory barrier.
 *
 * Thus, only a compiler barrier is needed to prevent the compiler
 * reordering.
 */
#define portMEMORY_BARRIER()                        __asm ಚಞ್ಚಲ ( "" ::: "memory" )

ಬಾಹ್ಯ uint32_t ulPortGetRunTime( ಶೂನ್ಯ );
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()    /* no-op */
#define port_GET_RUN_TIME_COUNTER_ಮೌಲ್ಯ()            ulPortGetRunTime()

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
