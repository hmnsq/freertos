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
#परिभाषय पत्तनम्_CHAR        वर्ण
#परिभाषय पत्तनम्_FLOAT       भिन्न
#परिभाषय पत्तनम्_DOUBLE      द्विगुण
#परिभाषय पत्तनम्_LONG        दीर्घ
#परिभाषय पत्तनम्_SHORT       ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE  uint32_t
#परिभाषय पत्तनम्_आधारः_TYPE   दीर्घ

प्रकारनिर्देश पत्तनम्_राशिः_TYPE राशिः_Type_t;
प्रकारनिर्देश दीर्घ आधारः_Type_t;
प्रकारनिर्देश अचिह्नित दीर्घ UBaseType_t;

#यदि( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः  == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t             TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffffffffUL
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#परिभाषय पत्तनम्_BYTE_ALIGNMENT  8
#परिभाषय पत्तनम्_राशिः_GROWTH    -1
#परिभाषय पत्तनम्_TICK_PERIOD_MS  ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#परिभाषय पत्तनम्_IPL_सरणम्       ( 10UL )
/* Don't straddle the CEE bit.  Interrupts calling FreeRTOS functions should
never have higher IPL bits set anyway. */
#परिभाषय पत्तनम्_ALL_IPL_द्वयङ्काः    ( 0x7FUL << पत्तनम्_IPL_सरणम् )
#परिभाषय पत्तनम्_SW0_BIT         ( 0x01 << 8 )

/* Interrupt priority conversion */
#परिभाषय पत्तनम्_IPL_गन्तव्यम्_संहिता( ipl_सङ्ख्या )    ( ( ipl_सङ्ख्या >> 1 ) & 0x03ul )
#परिभाषय पत्तनम्_संहिता_गन्तव्यम्_IPL( ipl_संहिता )      ( ( ipl_संहिता << 1 ) | 0x01ul )

/*-----------------------------------------------------------*/

स्थिर अन्तःस्थ uint32_t ul_पत्तनम्_Get_CP0_स्थितिः( शून्य )
{
uint32_t rv;

    __asm चञ्चल(
            "\n\t"
            "mfc0 %0,$12,0      \n\t"
            : "=r" ( rv ) :: );

    प्रत्यागम rv;
}
/*-----------------------------------------------------------*/

स्थिर अन्तःस्थ शून्य v_पत्तनम्_समुच्चयः_CP0_स्थितिः( uint32_t new_स्थितिः)
{
    ( शून्य ) new_स्थितिः;

    __asm__ __volatile__(
            "\n\t"
            "mtc0 %0,$12,0      \n\t"
            "ehb                \n\t"
            :
            :"r" ( new_स्थितिः ) : );
}
/*-----------------------------------------------------------*/

स्थिर अन्तःस्थ uint32_t ul_पत्तनम्_Get_CP0_Cause( शून्य )
{
uint32_t rv;

    __asm चञ्चल(
            "\n\t"
            "mfc0 %0,$13,0      \n\t"
            : "=r" ( rv ) :: );

    प्रत्यागम rv;
}
/*-----------------------------------------------------------*/

स्थिर अन्तःस्थ शून्य v_पत्तनम्_समुच्चयः_CP0_Cause( uint32_t new_cause )
{
    ( शून्य ) new_cause;

    __asm__ __volatile__(
            "\n\t"
            "mtc0 %0,$13,0      \n\t"
            "ehb                \n\t"
            :
            :"r" ( new_cause ) : );
}
/*-----------------------------------------------------------*/

/* This clears the IPL bits, then sets them to
configMAX_SYSCALL_INTERRUPT_PRIORITY.  An extra check is performed if
configASSERT() is defined to ensure an assertion handler does not inadvertently
attempt to lower the IPL when the call to assert was triggered because the IPL
value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY when an ISR
safe FreeRTOS API function was executed.  ISR safe FreeRTOS API functions are
those that end in FromISR.  FreeRTOS maintains a separate interrupt API to
ensure API function and interrupt entry is as fast and as simple as possible. */
#यदि ( configASSERT_DEFINED == 1 )
    #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                                                                            \
    {                                                                                                           \
    uint32_t ul_स्थितिः;                                                                                          \
        /* Mask interrupts at and below the kernel interrupt priority. */                                       \
        ul_स्थितिः = ul_पत्तनम्_Get_CP0_स्थितिः();                                                                        \
        /* Is the current IPL below configMAX_SYSCALL_INTERRUPT_PRIORITY? */                                    \
        यदि( ( ( ul_स्थितिः & पत्तनम्_ALL_IPL_द्वयङ्काः ) >> पत्तनम्_IPL_सरणम् ) < config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता )       \
        {                                                                                                       \
            ul_स्थितिः &= ~पत्तनम्_ALL_IPL_द्वयङ्काः;                                                                      \
            v_पत्तनम्_समुच्चयः_CP0_स्थितिः( ( ul_स्थितिः | ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता << पत्तनम्_IPL_सरणम् ) ) );      \
        }                                                                                                       \
    }
#अन्यथा /* configASSERT */
    #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                                                                            \
    {                                                                                                           \
    uint32_t ul_स्थितिः;                                                                                          \
        /* Mask interrupts at and below the kernel interrupt priority. */                                       \
        ul_स्थितिः = ul_पत्तनम्_Get_CP0_स्थितिः();                                                                        \
        ul_स्थितिः &= ~पत्तनम्_ALL_IPL_द्वयङ्काः;                                                                          \
        v_पत्तनम्_समुच्चयः_CP0_स्थितिः( ( ul_स्थितिः | ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता << पत्तनम्_IPL_सरणम् ) ) );          \
    }
#यदि_अन्तः /* configASSERT */

#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()             \
{                                           \
uint32_t ul_स्थितिः;                          \
    /* Unmask all interrupts. */            \
    ul_स्थितिः = ul_पत्तनम्_Get_CP0_स्थितिः();        \
    ul_स्थितिः &= ~पत्तनम्_ALL_IPL_द्वयङ्काः;          \
    v_पत्तनम्_समुच्चयः_CP0_स्थितिः( ul_स्थितिः );          \
}


बाह्य शून्य vTaskEnterCritical( शून्य );
बाह्य शून्य vTaskExitCritical( शून्य );
#परिभाषय पत्तनम्_CRITICAL_NESTING_अन्तर्_TCB 1
#परिभाषय पत्तनम्_ENTER_CRITICAL()        vTaskEnterCritical()
#परिभाषय पत्तनम्_EXIT_CRITICAL()         vTaskExitCritical()

बाह्य UBaseType_t ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR();
बाह्य शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्_From_ISR( UBaseType_t );
#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR() ux_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR()
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ux_Saved_स्थितिः_पञ्जिकाकोशः ) v_पत्तनम्_Clear_व्यवधानम्_आवरणम्_From_ISR( ux_Saved_स्थितिः_पञ्जिकाकोशः )

#यदि_अपरिभाषितम् config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION
    #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION 1
#यदि_अन्तः

#यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #यदि( configMAX_PRIORITIES > 32 )
        #दोषः config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION can only be समुच्चयः गन्तव्यम् 1 when configMAX_PRIORITIES is less than or equal गन्तव्यम् 32.  It is very rare that a system requires अधिकम् than 10 गन्तव्यम् 15 difference priorities as tasks that share a प्राथमिकता will time खण्डिका.
    #यदि_अन्तः

    /* Store/clear the ready priorities in a bit map. */
    #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
    #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

    /*-----------------------------------------------------------*/

    #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities ) ux_शिखरम्_प्राथमिकता = ( 31 - _clz( ( uxReadyPriorities ) ) )

#यदि_अन्तः /* taskRECORD_READY_PRIORITY */

/*-----------------------------------------------------------*/

/* Task utilities. */

#परिभाषय पत्तनम्_YIELD()                         \
{                                           \
uint32_t ulCause;                           \
    /* Trigger software interrupt. */       \
    ulCause = ul_पत्तनम्_Get_CP0_Cause();          \
    ulCause |= पत्तनम्_SW0_BIT;                 \
    v_पत्तनम्_समुच्चयः_CP0_Cause( ulCause );            \
}

बाह्य चञ्चल UBaseType_t ux_व्यवधानम्_Nesting;
#परिभाषय पत्तनम्_ASSERT_IF_अन्तर्_ISR() configASSERT( ux_व्यवधानम्_Nesting == 0 )

#परिभाषय पत्तनम्_NOP() __asm चञ्चल ( "nop" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters ) __attribute__((noreturn))
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters ) शून्य vFunction( शून्य *pvParameters )
/*-----------------------------------------------------------*/

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

/* Required by the kernel aware debugger. */
#यदि_परिभाषितम् __DEBUG
    #परिभाषय पत्तनम्_REMOVE_STATIC_QUALIFIER
#यदि_अन्तः

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
