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

#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <csi_core.h>

ବାହ୍ୟ ଶୂନ୍ୟ vPortYield( ଶୂନ୍ୟ );

/* *INDENT-OFF* */
#ifdef __cplusplus
    class vPortYield;
    ବାହ୍ୟ "C" {
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
#define portCHAR          ଅକ୍ଷର
#define portFLOAT         ଦଶମିକ
#define portDOUBLE        ଦ୍ୱିଗୁଣ
#define portLONG          long
#define portSHORT         short
#define port_ଗଦା_TYPE    uint32_t
#define portBASE_TYPE     long

ପ୍ରକାରବ୍ୟାଖ୍ୟା port_ଗଦା_TYPE   ଗଦା_Type_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା long             BaseType_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned long    UBaseType_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (* portvectorfunc)( ଶୂନ୍ୟ );

#ଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    ପ୍ରକାରବ୍ୟାଖ୍ୟା uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#ନଚେତଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    ପ୍ରକାରବ୍ୟାଖ୍ୟା uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#ଅନ୍ୟଥା
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif


/* Hardware specifics. */
#define portBYTE_ALIGNMENT    8
#define port_ଗଦା_GROWTH      -1
#define portMS_PERIOD_TICK    10
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )


ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ vPortEnableInterrupt( ଶୂନ୍ୟ )
{
    __enable_irq();
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ vPortDisableInterrupt( ଶୂନ୍ୟ )
{
    __disable_irq();
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ portLONG GetCurrentPSR( ଶୂନ୍ୟ )
{
    ଫେରନ୍ତୁ __get_PSR();
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ portLONG SaveLocalPSR( ଶୂନ୍ୟ )
{
    portLONG flags = __get_PSR();

    __disable_irq();
    ଫେରନ୍ତୁ flags;
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ RestoreLocalPSR( portLONG newMask )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( newMask )
        : "memory"
        );
}

ବାହ୍ୟ ଶୂନ୍ୟ vPortEnterCritical( ଶୂନ୍ୟ );
ବାହ୍ୟ ଶୂନ୍ୟ vPortExitCritical( ଶୂନ୍ୟ );
ବାହ୍ୟ __attribute__( ( naked ) ) ଶୂନ୍ୟ cpu_yeild( ଶୂନ୍ୟ );

#define portDISABLE_INTERRUPTS()                  vPortDisableInterrupt()
#define portENABLE_INTERRUPTS()                   vPortEnableInterrupt()
#define portENTER_CRITICAL()                      vPortEnterCritical()
#define portEXIT_CRITICAL()                       vPortExitCritical()
#define portSET_INTERRUPT_MASK_FROM_ISR()         SaveLocalPSR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( a )    RestoreLocalPSR( a )

#define portNOP()                                 asm ( "nop" )

ବାହ୍ୟ portLONG ulCriticalNesting;
ବାହ୍ୟ portLONG pendsvflag;

#define portYIELD()              \
    ଯଦି( ulCriticalNesting == 0 ) \
    {                            \
        vPortYield();            \
    }                            \
    ଅନ୍ୟଥା                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    portNOP(); portNOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters ) __attribute__( ( noreturn ) )
#define portTASK_FUNCTION( vFunction, pvParameters )          ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )
/*-----------------------------------------------------------*/

#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    କର {                                         \
        ଯଦି( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        ଅନ୍ୟଥା                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } ଯେତେବେଳେ( 0 )

#define portYIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
