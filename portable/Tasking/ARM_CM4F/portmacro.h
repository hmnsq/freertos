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

/*
 * Set basepri to portMAX_SYSCALL_INTERRUPT_PRIORITY without effecting other
 * registers.  r0 is clobbered.
 */
    #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()      __set_BASEPRI( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता )

/*
 * Set basepri back to 0 without effective other registers.
 * r0 is clobbered.  FAQ:  Setting BASEPRI to 0 is not a bug.  Please see
 * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html before disagreeing.
 */
    #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्()    __set_BASEPRI( 0 )

    बाह्य uint32_t ul_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्( शून्य );
    बाह्य शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( uint32_t ul_New_आवरणम् );
    #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         ul_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()
    #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )    v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( x )


    बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य );
    बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य );

    #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()
    #परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     पत्तनम्_CLEAR_व्यवधानम्_आवरणम्()
    #परिभाषय पत्तनम्_ENTER_CRITICAL()        v_पत्तनम्_Enter_Critical()
    #परिभाषय पत्तनम्_EXIT_CRITICAL()         v_पत्तनम्_Exit_Critical()

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
    #परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

    #परिभाषय पत्तनम्_NOP()

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
