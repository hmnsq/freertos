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

#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

#समावेश <stdlib.h>
#समावेश <stdint.h>
#समावेश <csi_core.h>

बाह्य व्योम vPortYield( व्योम );

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    class vPortYield;
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
प्रकार व्योम (* portvectorfunc)( व्योम );

#अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t     TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t     TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर


/* Hardware specifics. */
#घोषणा portBYTE_ALIGNMENT    8
#घोषणा port_ढेर_GROWTH      -1
#घोषणा portMS_PERIOD_TICK    10
#घोषणा portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )


अटल अंतरभूत व्योम vPortEnableInterrupt( व्योम )
{
    __enable_irq();
}

अटल अंतरभूत व्योम vPortDisableInterrupt( व्योम )
{
    __disable_irq();
}

अटल अंतरभूत portLONG GetCurrentPSR( व्योम )
{
    वापस __get_PSR();
}

अटल अंतरभूत portLONG SaveLocalPSR( व्योम )
{
    portLONG flags = __get_PSR();

    __disable_irq();
    वापस flags;
}

अटल अंतरभूत व्योम RestoreLocalPSR( portLONG newMask )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( newMask )
        : "memory"
        );
}

बाह्य व्योम vPortEnterCritical( व्योम );
बाह्य व्योम vPortExitCritical( व्योम );
बाह्य __attribute__( ( naked ) ) व्योम cpu_yeild( व्योम );

#घोषणा portDISABLE_INTERRUPTS()                  vPortDisableInterrupt()
#घोषणा portENABLE_INTERRUPTS()                   vPortEnableInterrupt()
#घोषणा portENTER_CRITICAL()                      vPortEnterCritical()
#घोषणा portEXIT_CRITICAL()                       vPortExitCritical()
#घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         SaveLocalPSR()
#घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( a )    RestoreLocalPSR( a )

#घोषणा portNOP()                                 यंत्र ( "nop" )

बाह्य portLONG ulCriticalNesting;
बाह्य portLONG pendsvflag;

#घोषणा portYIELD()              \
    अगर( ulCriticalNesting == 0 ) \
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
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters ) __attribute__( ( noreturn ) )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )
/*-----------------------------------------------------------*/

#घोषणा portEND_SWITCHING_ISR( xSwitchRequired ) \
    करो {                                         \
        अगर( xSwitchRequired != pdFALSE )         \
        {                                        \
            traceISR_EXIT_TO_SCHEDULER();        \
            portYIELD();                         \
        }                                        \
        अन्यथा                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } जबतक( 0 )

#घोषणा portYIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
