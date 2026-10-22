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


#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
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


#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#परिभाषय पत्तनम्_राशिः_GROWTH      ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT    8
/*-----------------------------------------------------------*/


/* Scheduler utilities. */
बाह्य शून्य v_पत्तनम्_Yield( शून्य );
#परिभाषय पत्तनम्_NVIC_INT_CTRL     ( ( चञ्चल uint32_t * ) 0xe000ed04 )
#परिभाषय पत्तनम्_NVIC_PENDSVSET    0x10000000
#परिभाषय पत्तनम्_YIELD()                v_पत्तनम्_Yield()
#परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired )         \
    कुरु                                                   \
    {                                                    \
        यदि( xSwitchRequired != pdFALSE )                 \
        {                                                \
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();                \
            *( पत्तनम्_NVIC_INT_CTRL ) = पत्तनम्_NVIC_PENDSVSET; \
        }                                                \
        अन्यथा                                             \
        {                                                \
            traceISR_EXIT();                             \
        }                                                \
    } यावत्( 0 )
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )    पत्तनम्_अन्तः_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/


/* Critical section management. */

बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य );
बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य );
बाह्य uint32_t ul_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR( शून्य );
बाह्य शून्य v_Clear_व्यवधानम्_आवरणम्_From_ISR( uint32_t ul_आवरणम् );

#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                  __asm चञ्चल ( "cpsid i" )
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                   __asm चञ्चल ( "cpsie i" )
#परिभाषय पत्तनम्_ENTER_CRITICAL()                      v_पत्तनम्_Enter_Critical()
#परिभाषय पत्तनम्_EXIT_CRITICAL()                       v_पत्तनम्_Exit_Critical()
#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         ul_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR()
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )    v_Clear_व्यवधानम्_आवरणम्_From_ISR( x )

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#यदि_अपरिभाषितम् पत्तनम्_SUPPRESS_TICKS_AND_SLEEP
    बाह्य शून्य v_पत्तनम्_Suppress_Ticks_And_Sleep( TickType_t xExpectedIdleTime );
    #परिभाषय पत्तनम्_SUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    v_पत्तनम्_Suppress_Ticks_And_Sleep( xExpectedIdleTime )
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

#परिभाषय पत्तनम्_NOP()

#परिभाषय पत्तनम्_INLINE              __inline

#यदि_अपरिभाषितम् पत्तनम्_FORCE_INLINE
    #परिभाषय पत्तनम्_FORCE_INLINE    अन्तःस्थ __attribute__( ( always_inline ) )
#यदि_अन्तः

/*-----------------------------------------------------------*/

पत्तनम्_FORCE_INLINE स्थिर आधारः_Type_t x_पत्तनम्_Is_Inside_व्यवधानम्( शून्य )
{
    uint32_t ul_Current_व्यवधानम्;
    आधारः_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm चञ्चल ( "mrs %0, ipsr" : "=r" ( ul_Current_व्यवधानम् )::"memory" );

    यदि( ul_Current_व्यवधानम् == 0 )
    {
        xReturn = pdFALSE;
    }
    अन्यथा
    {
        xReturn = pdTRUE;
    }

    प्रत्यागम xReturn;
}

/*-----------------------------------------------------------*/

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#निर्देशः diag_suppress=Pa082

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
