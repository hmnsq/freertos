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
    बाह्य "C" {
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
#define portCHAR          वर्ण
#define portFLOAT         भिन्न
#define portDOUBLE        द्विगुण
#define portLONG          दीर्घ
#define portSHORT         लघु
#define port_ढेर_TYPE    uint32_t
#define portBASE_TYPE     दीर्घ

प्रकारनिर्देश port_ढेर_TYPE   ढेर_Type_t;
प्रकारनिर्देश दीर्घ             BaseType_t;
प्रकारनिर्देश अचिन्हित दीर्घ    UBaseType_t;

#यदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकारनिर्देश uint16_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#नोचेद्यदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकारनिर्देश uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_ढेर_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/


/* Scheduler utilities. */
बाह्य शून्य vPortYield( शून्य );
#define portNVIC_INT_CTRL_REG     ( *( ( चञ्चल uint32_t * ) 0xe000ed04 ) )
#define portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#define portYIELD()                vPortYield()
#define portEND_SWITCHING_ISR( xSwitchRequired )            \
    कुरु                                                      \
    {                                                       \
        यदि( xSwitchRequired )                               \
        {                                                   \
            traceISR_EXIT_TO_SCHEDULER();                   \
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
        }                                                   \
        अन्यथा                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } यावत्( 0 )
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
बाह्य शून्य vPortEnterCritical( शून्य );
बाह्य शून्य vPortExitCritical( शून्य );
बाह्य uint32_t ulSetInterruptMaskFromISR( शून्य );
बाह्य शून्य vClearInterruptMaskFromISR( uint32_t ulMask );

#define portSET_INTERRUPT_MASK_FROM_ISR()         ulSetInterruptMaskFromISR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vClearInterruptMaskFromISR( x )
#define portDISABLE_INTERRUPTS()                  __disable_irq()
#define portENABLE_INTERRUPTS()                   __enable_irq()
#define portENTER_CRITICAL()                      vPortEnterCritical()
#define portEXIT_CRITICAL()                       vPortExitCritical()

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
    बाह्य शून्य vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#endif
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

#define portNOP()

#define portINLINE              __inline

#ifndef portFORCE_INLINE
    #define portFORCE_INLINE    __forceinline
#endif

/*-----------------------------------------------------------*/

स्थिर portFORCE_INLINE BaseType_t xPortIsInsideInterrupt( शून्य )
{
    uint32_t ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm
    {
/* *INDENT-OFF* */
            mrs ulCurrentInterrupt, ipsr
/* *INDENT-ON* */
    }

    यदि( ulCurrentInterrupt == 0 )
    {
        xReturn = pdFALSE;
    }
    अन्यथा
    {
        xReturn = pdTRUE;
    }

    प्रत्यागम xReturn;
}

/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
