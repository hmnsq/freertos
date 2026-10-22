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

/* The compiler needs to be told functions that are only referenced by pointer
 * are to be included in the build.  NOTE:  Omitting these lines will result in a
 * run-time crash, not a linker error! */
    #निर्देशः funcall vTaskStartScheduler prvIdleTask
    #निर्देशः funcall xTimerCreateTimerTask prvTimerTask

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
    #परिभाषय पत्तनम्_YIELD()                                 \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __asm{ dsb };                                              \
        __asm{ isb };                                              \
    }

#परिभाषय पत्तनम्_NVIC_INT_CTRL_REG     ( *( ( चञ्चल uint32_t * ) 0xe000ed04 ) )
#परिभाषय पत्तनम्_NVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired ) \
    कुरु                                           \
    {                                            \
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
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )    पत्तनम्_अन्तः_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
    बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य );
    बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य );
    #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                  CPU_REG_समुच्चयः( CPU_BASEPRI, config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता ); __asm{ dsb }; __asm{ isb }
    #परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                   CPU_REG_समुच्चयः( CPU_BASEPRI, 0 );
    #परिभाषय पत्तनम्_ENTER_CRITICAL()                      v_पत्तनम्_Enter_Critical()
    #परिभाषय पत्तनम्_EXIT_CRITICAL()                       v_पत्तनम्_Exit_Critical()
    #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         ul_पत्तनम्_Raise_BASEPRI()
    #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )    CPU_REG_समुच्चयः( CPU_BASEPRI, x ); /* Barrier instructions not used as this is only used to lower the basepri. */

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
    #परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
    #परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )
/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
    #यदि_अपरिभाषितम् पत्तनम्_SUPPRESS_TICKS_AND_SLEEP
        बाह्य शून्य v_पत्तनम्_Suppress_Ticks_And_Sleep( TickType_t xExpectedIdleTime );
        #परिभाषय पत्तनम्_SUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    v_पत्तनम्_Suppress_Ticks_And_Sleep( xExpectedIdleTime )
    #यदि_अन्तः
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
    #यदि_अपरिभाषितम् config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION
        #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    1
    #यदि_अन्तः

    #यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1

/* Generic helper function. */
        __attribute__( ( always_inline ) ) स्थिर अन्तःस्थ uint8_t uc_पत्तनम्_गणनम्_Leading_Zeros( uint32_t ulBitmap )
        {
            uint8_t ucReturn;

            __asm चञ्चल ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );

            प्रत्यागम ucReturn;
        }

/* Check the configuration. */
        #यदि ( configMAX_PRIORITIES > 32 )
            #दोषः config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION can only be समुच्चयः गन्तव्यम् 1 when configMAX_PRIORITIES is less than or equal गन्तव्यम् 32.  It is very rare that a system requires अधिकम् than 10 गन्तव्यम् 15 difference priorities as tasks that share a प्राथमिकता will time खण्डिका.
        #यदि_अन्तः

/* Store/clear the ready priorities in a bit map. */
        #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
        #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

/*-----------------------------------------------------------*/

        #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities )    ux_शिखरम्_प्राथमिकता = ( 31UL - ( uint32_t ) uc_पत्तनम्_गणनम्_Leading_Zeros( ( uxReadyPriorities ) ) )

    #यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/*-----------------------------------------------------------*/

    #यदि ( configASSERT_DEFINED == 1 )
        शून्य v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता( शून्य );
        #परिभाषय पत्तनम्_ASSERT_IF_व्यवधानम्_प्राथमिकता_INVALID()    v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता()
    #यदि_अन्तः

/* portNOP() is not required by this port. */
    #परिभाषय पत्तनम्_NOP()

    आधारः_Type_t x_पत्तनम्_Is_Inside_व्यवधानम्( शून्य );

/*-----------------------------------------------------------*/

    स्थिर अन्तःस्थ uint32_t ul_पत्तनम्_Raise_BASEPRI( शून्य )
    {
        uint32_t ulOriginalBASEPRI;

        ulOriginalBASEPRI = CPU_REG_GET( CPU_BASEPRI );
        CPU_REG_समुच्चयः( CPU_BASEPRI, config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता );
        __asm{ dsb };
        __asm{ isb };
        प्रत्यागम ulOriginalBASEPRI;
    }
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
