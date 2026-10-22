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

/* When the FIT configurator or the Smart Configurator is used, platform.h has to be
 * used. */
#यदि_अपरिभाषितम् config_INCLUDE_PLATFORM_H_INSTEAD_सम्बन्धि_IODEFINE_H
    #परिभाषय config_INCLUDE_PLATFORM_H_INSTEAD_सम्बन्धि_IODEFINE_H    0
#यदि_अन्तः

/* Type definitions - these are a bit legacy and not really used now, other than
 * portSTACK_TYPE and portBASE_TYPE. */
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

/* Hardware specifics. */
#परिभाषय पत्तनम्_BYTE_ALIGNMENT    8         /* Could make four, according to manual. */
#परिभाषय पत्तनम्_राशिः_GROWTH      -1
#परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_NOP()    __asm चञ्चल ( "NOP" )

/* Yield equivalent to "*portITU_SWINTR = 0x01; ( void ) *portITU_SWINTR;"
 * where portITU_SWINTR is the location of the software interrupt register
 * (0x000872E0).  Don't rely on the assembler to select a register, so instead
 * save and restore clobbered registers manually. */
#परिभाषय पत्तनम्_YIELD()                     \
    __asm चञ्चल                      \
    (                                   \
        "PUSH.L R10                 \n" \
        "MOV.L  #0x872E0, R10       \n" \
        "MOV.B  #0x1, [R10]         \n" \
        "MOV.L  [R10], R10          \n" \
        "POP    R10                 \n" \
    )

#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )                           यदि( x != pdFALSE ) पत्तनम्_YIELD( )

/* These macros should not be called directly, but through the
 * taskENTER_CRITICAL() and taskEXIT_CRITICAL() macros.  An extra check is
 * performed if configASSERT() is defined to ensure an assertion handler does not
 * inadvertently attempt to lower the IPL when the call to assert was triggered
 * because the IPL value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY
 * when an ISR safe FreeRTOS API function was executed.  ISR safe FreeRTOS API
 * functions are those that end in FromISR.  FreeRTOS maintains a separate
 * interrupt API to ensure API function and interrupt entry is as fast and as
 * simple as possible. */
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                           __asm चञ्चल ( "MVTIPL    #0" )
#यदि ( configASSERT_DEFINED == 1 )
    #परिभाषय पत्तनम्_ASSERT_IF_व्यवधानम्_प्राथमिकता_INVALID()    configASSERT( ( ul_पत्तनम्_Get_IPL() <= config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता ) )
    #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                      यदि( ul_पत्तनम्_Get_IPL() < config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता ) __asm चञ्चल( "MVTIPL    %0" ::"i" ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता ) )
#अन्यथा
    #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                      __asm चञ्चल ( "MVTIPL    %0" ::"i" ( config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता ) )
#यदि_अन्तः

/* Critical nesting counts are stored in the TCB. */
#परिभाषय पत्तनम्_CRITICAL_NESTING_अन्तर्_TCB    ( 1 )

/* The critical nesting functions defined within tasks.c. */
बाह्य शून्य vTaskEnterCritical( शून्य );
बाह्य शून्य vTaskExitCritical( शून्य );
#परिभाषय पत्तनम्_ENTER_CRITICAL()    vTaskEnterCritical()
#परिभाषय पत्तनम्_EXIT_CRITICAL()     vTaskExitCritical()

/* As this port allows interrupt nesting... */
uint32_t ul_पत्तनम्_Get_IPL( शून्य ) __attribute__( ( naked ) );
शून्य v_पत्तनम्_समुच्चयः_IPL( uint32_t ulNewIPL ) __attribute__( ( naked ) );
#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()                              ul_पत्तनम्_Get_IPL(); पत्तनम्_DISABLE_INTERRUPTS()
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( ux_Saved_व्यवधानम्_स्थितिः )    v_पत्तनम्_समुच्चयः_IPL( ux_Saved_व्यवधानम्_स्थितिः )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

#परिभाषय पत्तनम्_स्मृतिः_BARRIER()                                  __asm चञ्चल ( "" ::: "memory" )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
