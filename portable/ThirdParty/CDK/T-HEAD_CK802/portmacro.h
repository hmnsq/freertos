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

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <csi_core.h>

बाह्य शून्य vPortYield( शून्य );

/* *INDENT-OFF* */
#ifdef __cplusplus
    class vPortYield;
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
#define portLONG          long
#define portSHORT         short
#define port_ढेर_TYPE    uint32_t
#define portBASE_TYPE     long

प्रकारनिर्देश port_ढेर_TYPE   ढेर_Type_t;
प्रकारनिर्देश long             BaseType_t;
प्रकारनिर्देश unsigned long    UBaseType_t;
प्रकारनिर्देश शून्य (* portvectorfunc)( शून्य );

#यदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकारनिर्देश uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#नोचेद्यदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकारनिर्देश uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif


/* Hardware specifics. */
#define portBYTE_ALIGNMENT    8
#define port_ढेर_GROWTH      -1
#define portMS_PERIOD_TICK    10
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )


स्थिर अन्तःस्थ शून्य vPortEnableInterrupt( शून्य )
{
    __enable_irq();
}

स्थिर अन्तःस्थ शून्य vPortDisableInterrupt( शून्य )
{
    __disable_irq();
}

स्थिर अन्तःस्थ portLONG GetCurrentPSR( शून्य )
{
    प्रत्यागम __get_PSR();
}

स्थिर अन्तःस्थ portLONG SaveLocalPSR( शून्य )
{
    portLONG flags = __get_PSR();

    __disable_irq();
    प्रत्यागम flags;
}

स्थिर अन्तःस्थ शून्य RestoreLocalPSR( portLONG newMask )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( newMask )
        : "memory"
        );
}

बाह्य शून्य vPortEnterCritical( शून्य );
बाह्य शून्य vPortExitCritical( शून्य );
बाह्य __attribute__( ( naked ) ) शून्य cpu_yeild( शून्य );

#define portDISABLE_INTERRUPTS()                  vPortDisableInterrupt()
#define portENABLE_INTERRUPTS()                   vPortEnableInterrupt()
#define portENTER_CRITICAL()                      vPortEnterCritical()
#define portEXIT_CRITICAL()                       vPortExitCritical()
#define portSET_INTERRUPT_MASK_FROM_ISR()         SaveLocalPSR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( a )    RestoreLocalPSR( a )

#define portNOP()                                 asm ( "nop" )

बाह्य portLONG ulCriticalNesting;
बाह्य portLONG pendsvflag;

#define portYIELD()              \
    यदि( ulCriticalNesting == 0 ) \
    {                            \
        vPortYield();            \
    }                            \
    अन्यथा                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    portNOP(); portNOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters ) __attribute__( ( noreturn ) )
#define portTASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )
/*-----------------------------------------------------------*/

#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    कुरु {                                         \
        यदि( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        अन्यथा                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } यावत्( 0 )

#define portYIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
