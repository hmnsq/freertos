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

#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <csi_core.h>

ಬಾಹ್ಯ ಶೂನ್ಯ vPortYield( ಶೂನ್ಯ );

/* *INDENT-OFF* */
#ifdef __cplusplus
    class vPortYield;
    ಬಾಹ್ಯ "C" {
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
#define portCHAR          ವರ್ಣ
#define portFLOAT         ಭಿನ್ನ
#define portDOUBLE        ದ್ವಿಗುಣ
#define portLONG          long
#define portSHORT         short
#define port_ರಾಶಿ_TYPE    uint32_t
#define portBASE_TYPE     long

ಪ್ರಕಾರನಿರ್ದೇಶ port_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರನಿರ್ದೇಶ long             BaseType_t;
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned long    UBaseType_t;
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (* portvectorfunc)( ಶೂನ್ಯ );

#ಯದಿ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    ಪ್ರಕಾರನಿರ್ದೇಶ uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffff
#ನೋಚೇದ್ಯದಿ ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    ಪ್ರಕಾರನಿರ್ದೇಶ uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#ಅನ್ಯಥಾ
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif


/* Hardware specifics. */
#define portBYTE_ALIGNMENT    8
#define port_ರಾಶಿ_GROWTH      -1
#define portMS_PERIOD_TICK    10
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )


ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ vPortEnableInterrupt( ಶೂನ್ಯ )
{
    __enable_irq();
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ vPortDisableInterrupt( ಶೂನ್ಯ )
{
    __disable_irq();
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ portLONG GetCurrentPSR( ಶೂನ್ಯ )
{
    ಪ್ರತ್ಯಾಗಮ __get_PSR();
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ portLONG SaveLocalPSR( ಶೂನ್ಯ )
{
    portLONG flags = __get_PSR();

    __disable_irq();
    ಪ್ರತ್ಯಾಗಮ flags;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ RestoreLocalPSR( portLONG newMask )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( newMask )
        : "memory"
        );
}

ಬಾಹ್ಯ ಶೂನ್ಯ vPortEnterCritical( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vPortExitCritical( ಶೂನ್ಯ );
ಬಾಹ್ಯ __attribute__( ( naked ) ) ಶೂನ್ಯ cpu_yeild( ಶೂನ್ಯ );

#define portDISABLE_INTERRUPTS()                  vPortDisableInterrupt()
#define portENABLE_INTERRUPTS()                   vPortEnableInterrupt()
#define portENTER_CRITICAL()                      vPortEnterCritical()
#define portEXIT_CRITICAL()                       vPortExitCritical()
#define portSET_INTERRUPT_MASK_FROM_ISR()         SaveLocalPSR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( a )    RestoreLocalPSR( a )

#define portNOP()                                 asm ( "nop" )

ಬಾಹ್ಯ portLONG ulCriticalNesting;
ಬಾಹ್ಯ portLONG pendsvflag;

#define portYIELD()              \
    ಯದಿ( ulCriticalNesting == 0 ) \
    {                            \
        vPortYield();            \
    }                            \
    ಅನ್ಯಥಾ                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    portNOP(); portNOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters ) __attribute__( ( noreturn ) )
#define portTASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
/*-----------------------------------------------------------*/

#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    ಕುರು {                                         \
        ಯದಿ( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        ಅನ್ಯಥಾ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } ಯಾವತ್( 0 )

#define portYIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
