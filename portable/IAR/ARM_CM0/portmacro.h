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
    ബാഹ്യ "C" {
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
#define portCHAR          അക്ഷരം
#define portFLOAT         ദശാംശം
#define portDOUBLE        ഇരട്ട
#define portLONG          long
#define portSHORT         short
#define port_അട്ടി_TYPE    uint32_t
#define portBASE_TYPE     long

തരനിർവചനം port_അട്ടി_TYPE   അട്ടി_Type_t;
തരനിർവചനം long             BaseType_t;
തരനിർവചനം unsigned long    UBaseType_t;


#എങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    തരനിർവചനം uint16_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#അല്ലെങ്കിലെങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    തരനിർവചനം uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#അല്ലെങ്കിൽ
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_അട്ടി_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/


/* Scheduler utilities. */
ബാഹ്യ ശൂന്യം vPortYield( ശൂന്യം );
#define portNVIC_INT_CTRL     ( ( അസ്ഥിര uint32_t * ) 0xe000ed04 )
#define portNVIC_PENDSVSET    0x10000000
#define portYIELD()                vPortYield()
#define portEND_SWITCHING_ISR( xSwitchRequired )         \
    ചെയ്യുക                                                   \
    {                                                    \
        എങ്കിൽ( xSwitchRequired != pdFALSE )                 \
        {                                                \
            traceISR_EXIT_TO_SCHEDULER();                \
            *( portNVIC_INT_CTRL ) = portNVIC_PENDSVSET; \
        }                                                \
        അല്ലെങ്കിൽ                                             \
        {                                                \
            traceISR_EXIT();                             \
        }                                                \
    } ആകുമ്പോൾ( 0 )
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/


/* Critical section management. */

ബാഹ്യ ശൂന്യം vPortEnterCritical( ശൂന്യം );
ബാഹ്യ ശൂന്യം vPortExitCritical( ശൂന്യം );
ബാഹ്യ uint32_t ulSetInterruptMaskFromISR( ശൂന്യം );
ബാഹ്യ ശൂന്യം vClearInterruptMaskFromISR( uint32_t ulMask );

#define portDISABLE_INTERRUPTS()                  __asm അസ്ഥിര ( "cpsid i" )
#define portENABLE_INTERRUPTS()                   __asm അസ്ഥിര ( "cpsie i" )
#define portENTER_CRITICAL()                      vPortEnterCritical()
#define portEXIT_CRITICAL()                       vPortExitCritical()
#define portSET_INTERRUPT_MASK_FROM_ISR()         ulSetInterruptMaskFromISR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vClearInterruptMaskFromISR( x )

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
    ബാഹ്യ ശൂന്യം vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#endif
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ശൂന്യം vFunction( ശൂന്യം * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ശൂന്യം vFunction( ശൂന്യം * pvParameters )

#define portNOP()

#define portINLINE              __inline

#ifndef portFORCE_INLINE
    #define portFORCE_INLINE    വരിയിൽ __attribute__( ( always_inline ) )
#endif

/*-----------------------------------------------------------*/

portFORCE_INLINE സ്ഥിതം BaseType_t xPortIsInsideInterrupt( ശൂന്യം )
{
    uint32_t ulCurrentInterrupt;
    BaseType_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm അസ്ഥിര ( "mrs %0, ipsr" : "=r" ( ulCurrentInterrupt )::"memory" );

    എങ്കിൽ( ulCurrentInterrupt == 0 )
    {
        xReturn = pdFALSE;
    }
    അല്ലെങ്കിൽ
    {
        xReturn = pdTRUE;
    }

    തിരികെ xReturn;
}

/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#pragma diag_suppress=Pa082

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
