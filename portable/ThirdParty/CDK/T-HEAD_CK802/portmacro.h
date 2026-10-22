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

#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <csi_core.h>

বাহ্য শূন্য vPortYield( শূন্য );

/* *INDENT-OFF* */
#ifdef __cplusplus
    class vPortYield;
    বাহ্য "C" {
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
#define portCHAR          বর্ণ
#define portFLOAT         ভিন্ন
#define portDOUBLE        দ্বিগুণ
#define portLONG          long
#define portSHORT         short
#define port_স্তূপ_TYPE    uint32_t
#define portBASE_TYPE     long

প্রকারনির্দেশ port_স্তূপ_TYPE   স্তূপ_Type_t;
প্রকারনির্দেশ long             BaseType_t;
প্রকারনির্দেশ unsigned long    UBaseType_t;
প্রকারনির্দেশ শূন্য (* portvectorfunc)( শূন্য );

#যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    প্রকারনির্দেশ uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#নোচেদ্যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    প্রকারনির্দেশ uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#অন্যথা
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif


/* Hardware specifics. */
#define portBYTE_ALIGNMENT    8
#define port_স্তূপ_GROWTH      -1
#define portMS_PERIOD_TICK    10
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )


স্থির অন্তঃস্থ শূন্য vPortEnableInterrupt( শূন্য )
{
    __enable_irq();
}

স্থির অন্তঃস্থ শূন্য vPortDisableInterrupt( শূন্য )
{
    __disable_irq();
}

স্থির অন্তঃস্থ portLONG GetCurrentPSR( শূন্য )
{
    প্রত্যাগম __get_PSR();
}

স্থির অন্তঃস্থ portLONG SaveLocalPSR( শূন্য )
{
    portLONG flags = __get_PSR();

    __disable_irq();
    প্রত্যাগম flags;
}

স্থির অন্তঃস্থ শূন্য RestoreLocalPSR( portLONG newMask )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( newMask )
        : "memory"
        );
}

বাহ্য শূন্য vPortEnterCritical( শূন্য );
বাহ্য শূন্য vPortExitCritical( শূন্য );
বাহ্য __attribute__( ( naked ) ) শূন্য cpu_yeild( শূন্য );

#define portDISABLE_INTERRUPTS()                  vPortDisableInterrupt()
#define portENABLE_INTERRUPTS()                   vPortEnableInterrupt()
#define portENTER_CRITICAL()                      vPortEnterCritical()
#define portEXIT_CRITICAL()                       vPortExitCritical()
#define portSET_INTERRUPT_MASK_FROM_ISR()         SaveLocalPSR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( a )    RestoreLocalPSR( a )

#define portNOP()                                 asm ( "nop" )

বাহ্য portLONG ulCriticalNesting;
বাহ্য portLONG pendsvflag;

#define portYIELD()              \
    যদি( ulCriticalNesting == 0 ) \
    {                            \
        vPortYield();            \
    }                            \
    অন্যথা                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    portNOP(); portNOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    শূন্য vFunction( শূন্য * pvParameters ) __attribute__( ( noreturn ) )
#define portTASK_FUNCTION( vFunction, pvParameters )          শূন্য vFunction( শূন্য * pvParameters )
/*-----------------------------------------------------------*/

#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    কুরু {                                         \
        যদি( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        অন্যথা                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } যাবত্( 0 )

#define portYIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
