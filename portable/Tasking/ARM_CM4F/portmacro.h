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


#अगर_अघोषित PORTMACRO_H
    #घोषणा PORTMACRO_H

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
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
    #घोषणा portCHAR          अक्षर
    #घोषणा portFLOAT         भग्न
    #घोषणा portDOUBLE        द्विगुन
    #घोषणा portLONG          दीर्घ
    #घोषणा portSHORT         लघु
    #घोषणा port_ढेर_TYPE    uint32_t
    #घोषणा portBASE_TYPE     दीर्घ

    प्रकार port_ढेर_TYPE   ढेर_Type_t;
    प्रकार दीर्घ             BaseType_t;
    प्रकार अचिन्हित दीर्घ    UBaseType_t;


    #अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        प्रकार uint16_t     TickType_t;
        #घोषणा portMAX_DELAY              ( TickType_t ) 0xffff
    #या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
        प्रकार uint32_t     TickType_t;
        #घोषणा portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
        #घोषणा portTICK_TYPE_IS_ATOMIC    1
    #अन्यथा
        #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
    #पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #घोषणा port_ढेर_GROWTH      ( -1 )
    #घोषणा portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
    #घोषणा portBYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/


/* Scheduler utilities. */
बाह्य व्योम vPortYield( व्योम );
#घोषणा portNVIC_INT_CTRL     ( ( अस्थिर uint32_t * ) 0xe000ed04 )
#घोषणा portNVIC_PENDSVSET    0x10000000
#घोषणा portYIELD()                vPortYield()

#घोषणा portEND_SWITCHING_ISR( xSwitchRequired )         \
    करो                                                   \
    {                                                    \
        अगर( xSwitchRequired != pdFALSE )                 \
        {                                                \
            traceISR_EXIT_TO_SCHEDULER();                \
            *( portNVIC_INT_CTRL ) = portNVIC_PENDSVSET; \
        }                                                \
        अन्यथा                                             \
        {                                                \
            traceISR_EXIT();                             \
        }                                                \
    } जबतक( 0 )
#घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/


/* Critical section management. */

/*
 * Set basepri to portMAX_SYSCALL_INTERRUPT_PRIORITY without effecting other
 * registers.  r0 is clobbered.
 */
    #घोषणा portSET_INTERRUPT_MASK()      __set_BASEPRI( configMAX_SYSCALL_INTERRUPT_PRIORITY )

/*
 * Set basepri back to 0 without effective other registers.
 * r0 is clobbered.  FAQ:  Setting BASEPRI to 0 is not a bug.  Please see
 * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html before disagreeing.
 */
    #घोषणा portCLEAR_INTERRUPT_MASK()    __set_BASEPRI( 0 )

    बाह्य uint32_t ulPortSetInterruptMask( व्योम );
    बाह्य व्योम vPortClearInterruptMask( uint32_t ulNewMask );
    #घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         ulPortSetInterruptMask()
    #घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortClearInterruptMask( x )


    बाह्य व्योम vPortEnterCritical( व्योम );
    बाह्य व्योम vPortExitCritical( व्योम );

    #घोषणा portDISABLE_INTERRUPTS()    portSET_INTERRUPT_MASK()
    #घोषणा portENABLE_INTERRUPTS()     portCLEAR_INTERRUPT_MASK()
    #घोषणा portENTER_CRITICAL()        vPortEnterCritical()
    #घोषणा portEXIT_CRITICAL()         vPortExitCritical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
    #घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

    #घोषणा portNOP()

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
