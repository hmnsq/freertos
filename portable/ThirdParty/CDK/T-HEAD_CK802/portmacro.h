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

#ضمن <stdlib.h>
#ضمن <stdint.h>
#ضمن <csi_core.h>

خارجي فراغ vPortYield( فراغ );

/* *INDENT-OFF* */
#ifdef __cplusplus
    class vPortYield;
    خارجي "C" {
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
#define portCHAR          حرف
#define portFLOAT         عائم
#define portDOUBLE        مزدوج
#define portLONG          long
#define portSHORT         short
#define port_دۆۋە_TYPE    uint32_t
#define portBASE_TYPE     long

تعريفنوع port_دۆۋە_TYPE   دۆۋە_Type_t;
تعريفنوع long             BaseType_t;
تعريفنوع unsigned long    UBaseType_t;
تعريفنوع فراغ (* portvectorfunc)( فراغ );

#إذا ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    تعريفنوع uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    تعريفنوع uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#وإلا
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif


/* Hardware specifics. */
#define portBYTE_ALIGNMENT    8
#define port_دۆۋە_GROWTH      -1
#define portMS_PERIOD_TICK    10
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )


ساكن مضمن فراغ vPortEnableInterrupt( فراغ )
{
    __enable_irq();
}

ساكن مضمن فراغ vPortDisableInterrupt( فراغ )
{
    __disable_irq();
}

ساكن مضمن portLONG GetCurrentPSR( فراغ )
{
    أرجع __get_PSR();
}

ساكن مضمن portLONG SaveLocalPSR( فراغ )
{
    portLONG flags = __get_PSR();

    __disable_irq();
    أرجع flags;
}

ساكن مضمن فراغ RestoreLocalPSR( portLONG newMask )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( newMask )
        : "memory"
        );
}

خارجي فراغ vPortEnterCritical( فراغ );
خارجي فراغ vPortExitCritical( فراغ );
خارجي __attribute__( ( naked ) ) فراغ cpu_yeild( فراغ );

#define portDISABLE_INTERRUPTS()                  vPortDisableInterrupt()
#define portENABLE_INTERRUPTS()                   vPortEnableInterrupt()
#define portENTER_CRITICAL()                      vPortEnterCritical()
#define portEXIT_CRITICAL()                       vPortExitCritical()
#define portSET_INTERRUPT_MASK_FROM_ISR()         SaveLocalPSR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( a )    RestoreLocalPSR( a )

#define portNOP()                                 asm ( "nop" )

خارجي portLONG ulCriticalNesting;
خارجي portLONG pendsvflag;

#define portYIELD()              \
    إذا( ulCriticalNesting == 0 ) \
    {                            \
        vPortYield();            \
    }                            \
    وإلا                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    portNOP(); portNOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( noreturn ) )
#define portTASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/

#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    افعل {                                         \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        وإلا                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } طالما( 0 )

#define portYIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
