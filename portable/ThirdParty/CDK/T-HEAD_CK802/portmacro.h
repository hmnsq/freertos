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

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <csi_core.h>

बाह्य शून्य v_पत्तनम्_Yield( शून्य );

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    class v_पत्तनम्_Yield;
    बाह्य "C" {
#यदि_अन्तः
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
#परिभाषय पत्तनम्_CHAR          वर्ण
#परिभाषय पत्तनम्_FLOAT         भिन्न
#परिभाषय पत्तनम्_DOUBLE        द्विगुण
#परिभाषय पत्तनम्_LONG          दीर्घ
#परिभाषय पत्तनम्_SHORT         ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE    uint32_t
#परिभाषय पत्तनम्_आधारः_TYPE     दीर्घ

प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
प्रकारनिर्देश दीर्घ             आधारः_Type_t;
प्रकारनिर्देश अचिह्नित दीर्घ    UBaseType_t;
प्रकारनिर्देश शून्य (* portvectorfunc)( शून्य );

#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः


/* Hardware specifics. */
#परिभाषय पत्तनम्_BYTE_ALIGNMENT    8
#परिभाषय पत्तनम्_राशिः_GROWTH      -1
#परिभाषय पत्तनम्_MS_PERIOD_TICK    10
#परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )


स्थिर अन्तःस्थ शून्य v_पत्तनम्_Enable_व्यवधानम्( शून्य )
{
    __enable_irq();
}

स्थिर अन्तःस्थ शून्य v_पत्तनम्_Disable_व्यवधानम्( शून्य )
{
    __disable_irq();
}

स्थिर अन्तःस्थ पत्तनम्_LONG GetCurrentPSR( शून्य )
{
    प्रत्यागम __get_PSR();
}

स्थिर अन्तःस्थ पत्तनम्_LONG SaveLocalPSR( शून्य )
{
    पत्तनम्_LONG flags = __get_PSR();

    __disable_irq();
    प्रत्यागम flags;
}

स्थिर अन्तःस्थ शून्य RestoreLocalPSR( पत्तनम्_LONG new_आवरणम् )
{
    __asm__ __volatile__ (
        "mtcr   %0, psr \n"
        :
        : "r" ( new_आवरणम् )
        : "memory"
        );
}

बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य );
बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य );
बाह्य __attribute__( ( naked ) ) शून्य cpu_yeild( शून्य );

#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                  v_पत्तनम्_Disable_व्यवधानम्()
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                   v_पत्तनम्_Enable_व्यवधानम्()
#परिभाषय पत्तनम्_ENTER_CRITICAL()                      v_पत्तनम्_Enter_Critical()
#परिभाषय पत्तनम्_EXIT_CRITICAL()                       v_पत्तनम्_Exit_Critical()
#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         SaveLocalPSR()
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( a )    RestoreLocalPSR( a )

#परिभाषय पत्तनम्_NOP()                                 asm ( "nop" )

बाह्य पत्तनम्_LONG ulCriticalNesting;
बाह्य पत्तनम्_LONG pendsvflag;

#परिभाषय पत्तनम्_YIELD()              \
    यदि( ulCriticalNesting == 0 ) \
    {                            \
        v_पत्तनम्_Yield();            \
    }                            \
    अन्यथा                         \
    {                            \
        pendsvflag = 1;          \
    }                            \
    पत्तनम्_NOP(); पत्तनम्_NOP()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters ) __attribute__( ( noreturn ) )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )
/*-----------------------------------------------------------*/

#परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired ) \
    कुरु {                                         \
        यदि( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();        \
            पत्तनम्_YIELD();                         \
        }                                        \
        अन्यथा                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } यावत्( 0 )

#परिभाषय पत्तनम्_YIELD_FROM_ISR( a )    vTaskSwitchContext()



/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
