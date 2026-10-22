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
#define port_थाक_TYPE    uint32_t
#define portBASE_TYPE     दीर्घ

प्रकारनिर्देश port_थाक_TYPE   थाक_Type_t;
प्रकारनिर्देश दीर्घ             BaseType_t;
प्रकारनिर्देश अचिन्हित दीर्घ    UBaseType_t;

#यदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकारनिर्देश uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#अथवायदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकारनिर्देश uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#अन्यथा
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define portBYTE_ALIGNMENT    4
#define port_थाक_GROWTH      -1
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/
uint32_t ulPortSetIPL( uint32_t );
#define portDISABLE_INTERRUPTS()    ulPortSetIPL( configMAX_SYSCALL_INTERRUPT_PRIORITY )
#define portENABLE_INTERRUPTS()     ulPortSetIPL( 0 )


बाह्य शून्य vPortEnterCritical( शून्य );
बाह्य शून्य vPortExitCritical( शून्य );
#define portENTER_CRITICAL()    vPortEnterCritical()
#define portEXIT_CRITICAL()     vPortExitCritical()

बाह्य UBaseType_t uxPortSetInterruptMaskFromISR( शून्य );
बाह्य शून्य vPortClearInterruptMaskFromISR( UBaseType_t );
#define portSET_INTERRUPT_MASK_FROM_ISR()                             ulPortSetIPL( configMAX_SYSCALL_INTERRUPT_PRIORITY )
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedStatusRegister )    ulPortSetIPL( uxSavedStatusRegister )

/*-----------------------------------------------------------*/

/* Task utilities. */

#define portNOP()      यंत्र चञ्चल ( "nop" )

/* Note this will overwrite all other bits in the force register, it is done this way for speed. */
#define portYIELD()    MCF_INTC0_INTFRCL = ( 1UL << configYIELD_INTERRUPT_VECTOR ); portNOP(); portNOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters ) __attribute__( ( noreturn ) )
#define portTASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )
/*-----------------------------------------------------------*/

#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    गर                                           \
    {                                            \
        यदि( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        अन्यथा                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } जबसम्म( 0 )


/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
