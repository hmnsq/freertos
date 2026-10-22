/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
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
 */

#ifndef PORTMACRO_H
#define PORTMACRO_H

#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <csi_core.h>

ബാഹ്യ ശൂന്യം vPortYield( ശൂന്യം );

/* *INDENT-OFF* */
#ifdef __cplusplus
    class vPortYield;
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
തരനിർവചനം ശൂന്യം (* portvectorfunc)( ശൂന്യം );

#എങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    തരനിർവചനം uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#അല്ലെങ്കിലെങ്കിൽ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    തരനിർവചനം uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#അല്ലെങ്കിൽ
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif


/* Hardware specifics. */
#define portBYTE_ALIGNMENT    8
#define port_അട്ടി_GROWTH      -1
#define portMS_PERIOD_TICK    10
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )


സ്ഥിതം വരിയിൽ ശൂന്യം vPortEnableInterrupt( ശൂന്യം )
{
    __enable_irq();
}

സ്ഥിതം വരിയിൽ ശൂന്യം vPortDisableInterrupt( ശൂന്യം )
{
    __disable_irq();
}

സ്ഥിതം വരിയിൽ portLONG GetCurrentPSR( ശൂന്യം )
{
    തിരികെ __get_PSR();
}

സ്ഥിതം വരിയിൽ portLONG SaveLocalPSR( ശൂന്യം )
{
    portLONG flags = __get_PSR();

    __disable_irq();
    തിരികെ flags;
}

സ്ഥിതം വരിയിൽ ശൂന്യം RestoreLocalPSR( portLONG newMask )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( newMask )
        : "memory"
        );
}

ബാഹ്യ ശൂന്യം vPortEnterCritical( ശൂന്യം );
ബാഹ്യ ശൂന്യം vPortExitCritical( ശൂന്യം );
ബാഹ്യ __attribute__( ( naked ) ) ശൂന്യം cpu_yeild( ശൂന്യം );

#define portDISABLE_INTERRUPTS()                  vPortDisableInterrupt()
#define portENABLE_INTERRUPTS()                   vPortEnableInterrupt()
#define portENTER_CRITICAL()                      vPortEnterCritical()
#define portEXIT_CRITICAL()                       vPortExitCritical()
#define portSET_INTERRUPT_MASK_FROM_ISR()         SaveLocalPSR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( a )    RestoreLocalPSR( a )

#define portNOP()                                 asm ( "nop" )

ബാഹ്യ portLONG ulCriticalNesting;
ബാഹ്യ portLONG pendsvflag;

#define portYIELD()              \
    എങ്കിൽ( ulCriticalNesting == 0 ) \
    {                            \
        vPortYield();            \
    }                            \
    അല്ലെങ്കിൽ                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    portNOP(); portNOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ശൂന്യം vFunction( ശൂന്യം * pvParameters ) __attribute__( ( noreturn ) )
#define portTASK_FUNCTION( vFunction, pvParameters )          ശൂന്യം vFunction( ശൂന്യം * pvParameters )
/*-----------------------------------------------------------*/

#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    ചെയ്യുക {                                         \
        എങ്കിൽ( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        അല്ലെങ്കിൽ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } ആകുമ്പോൾ( 0 )

#define portYIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
