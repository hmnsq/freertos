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


#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
/* *INDENT-ON* */

#समावेश <limits.h>
#समावेश <stdint.h>

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
#घोषणा portCHAR                 अक्षर
#घोषणा portFLOAT                भग्न
#घोषणा portDOUBLE               द्विगुन
#घोषणा portLONG                 दीर्घ
#घोषणा portSHORT                लघु
#घोषणा port_ढेर_TYPE           अचिन्हित दीर्घ
#घोषणा portBASE_TYPE            दीर्घ
#घोषणा port_POINTER_आकार_TYPE    intptr_t

प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार दीर्घ             BaseType_t;
प्रकार अचिन्हित दीर्घ    UBaseType_t;

प्रकार अचिन्हित दीर्घ    TickType_t;
#घोषणा portMAX_DELAY              ( ( TickType_t ) अच_दीर्घ_उच्च )

#घोषणा portTICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#घोषणा port_ढेर_GROWTH                   ( -1 )
#घोषणा port_HAS_ढेर_OVERFLOW_CHECKING    ( 1 )
#घोषणा portTICK_PERIOD_MS                 ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portTICK_RATE_MICROSECONDS         ( ( TickType_t ) 1000000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT                 8
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
बाह्य व्योम vPortYield( व्योम );

#घोषणा portYIELD()                vPortYield()

#घोषणा portEND_SWITCHING_ISR( xSwitchRequired ) \
    करो                                           \
    {                                            \
        अगर( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            vPortYield();                        \
        }                                        \
        अन्यथा                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } जबतक( 0 )
#घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
बाह्य व्योम vPortDisableInterrupts( व्योम );
बाह्य व्योम vPortEnableInterrupts( व्योम );
#घोषणा portSET_INTERRUPT_MASK()      ( vPortDisableInterrupts() )
#घोषणा portCLEAR_INTERRUPT_MASK()    ( vPortEnableInterrupts() )

बाह्य UBaseType_t xPortSetInterruptMask( व्योम );
बाह्य व्योम vPortClearInterruptMask( UBaseType_t xMask );

बाह्य व्योम vPortEnterCritical( व्योम );
बाह्य व्योम vPortExitCritical( व्योम );
#घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         xPortSetInterruptMask()
#घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortClearInterruptMask( x )
#घोषणा portDISABLE_INTERRUPTS()                  portSET_INTERRUPT_MASK()
#घोषणा portENABLE_INTERRUPTS()                   portCLEAR_INTERRUPT_MASK()
#घोषणा portENTER_CRITICAL()                      vPortEnterCritical()
#घोषणा portEXIT_CRITICAL()                       vPortExitCritical()

/*-----------------------------------------------------------*/

बाह्य व्योम vPortThreadDying( व्योम * pxTaskToDelete,
                              अस्थिर BaseType_t * pxPendYield );
बाह्य व्योम vPortCancelThread( व्योम * pxTaskToDelete );
#घोषणा portPRE_TASK_DELETE_HOOK( pvTaskToDelete, pxPendYield )    vPortThreadDying( ( pvTaskToDelete ), ( pxPendYield ) )
#घोषणा portCLEAN_UP_TCB( pxTCB )                                  vPortCancelThread( pxTCB )
/*-----------------------------------------------------------*/

#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )         व्योम vFunction( व्योम * pvParameters ) __attribute__( ( noreturn ) )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )               व्योम vFunction( व्योम * pvParameters )
/*-----------------------------------------------------------*/

/*
 * Tasks run in their own pthreads and context switches between them
 * are always a full memory barrier. ISRs are emulated as signals
 * which also imply a full memory barrier.
 *
 * Thus, only a compiler barrier is needed to prevent the compiler
 * reordering.
 */
#घोषणा portMEMORY_BARRIER()                        __asm अस्थिर ( "" ::: "memory" )

बाह्य uint32_t ulPortGetRunTime( व्योम );
#घोषणा portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()    /* no-op */
#घोषणा port_GET_RUN_TIME_गणक_मूल्य()            ulPortGetRunTime()

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
