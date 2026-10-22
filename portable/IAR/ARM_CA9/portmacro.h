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

/* IAR includes. */
#यदि_परिभाषितम् __ICCARM__

    #अन्तर्भाव <intrinsics.h>

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
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

    प्रकारनिर्देश uint32_t         TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #परिभाषय पत्तनम्_राशिः_GROWTH      ( -1 )
    #परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
    #परिभाषय पत्तनम्_BYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
    #परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired ) \
    {                                                \
        बाह्य uint32_t ul_पत्तनम्_Yield_Required;         \
                                                     \
        यदि( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_पत्तनम्_Yield_Required = pdTRUE;            \
        }                                            \
    }

    #परिभाषय पत्तनम्_YIELD_FROM_ISR( x )    पत्तनम्_अन्तः_SWITCHING_ISR( x )
    #परिभाषय पत्तनम्_YIELD()                __asm( "SWI 0" );


/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

    बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य );
    बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य );
    बाह्य uint32_t ul_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्( शून्य );
    बाह्य शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( uint32_t ul_New_आवरणम्_मानम् );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #परिभाषय पत्तनम्_ENTER_CRITICAL()                      v_पत्तनम्_Enter_Critical();
    #परिभाषय पत्तनम्_EXIT_CRITICAL()                       v_पत्तनम्_Exit_Critical();
    #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                  ul_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()
    #परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                   v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( 0 )
    #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         ul_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()
    #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )    v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( x )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
    #परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
    #परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
    शून्य FreeRTOS_Tick_Handler( शून्य );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
    शून्य v_पत्तनम्_Task_उपयुङ्क्ते_FPU( शून्य );
    #परिभाषय पत्तनम्_TASK_उपयुङ्क्ते_FLOATING_POINT()    v_पत्तनम्_Task_उपयुङ्क्ते_FPU()

    #परिभाषय पत्तनम्_निम्नतमम्_व्यवधानम्_प्राथमिकता           ( ( ( uint32_t ) config_UNIQUE_व्यवधानम्_PRIORITIES ) - 1UL )
    #परिभाषय पत्तनम्_निम्नतमम्_USABLE_व्यवधानम्_प्राथमिकता    ( पत्तनम्_निम्नतमम्_व्यवधानम्_प्राथमिकता - 1UL )

/* Architecture specific optimisations. */
    #यदि_अपरिभाषितम् config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION
        #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    1
    #यदि_अन्तः

    #यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
        #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
        #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

/*-----------------------------------------------------------*/

        #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities )    ux_शिखरम्_प्राथमिकता = ( 31 - __CLZ( uxReadyPriorities ) )

    #यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #यदि ( configASSERT_DEFINED == 1 )
        शून्य v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता( शून्य );
        #परिभाषय पत्तनम्_ASSERT_IF_व्यवधानम्_प्राथमिकता_INVALID()    v_पत्तनम्_Validate_व्यवधानम्_प्राथमिकता()
    #यदि_अन्तः /* configASSERT */

    #परिभाषय पत्तनम्_NOP()                                         __asm चञ्चल ( "NOP" )

/* Suppress warnings that are generated by the IAR tools, but cannot be
 * fixed in the source code because to do so would cause other compilers to
 * generate warnings. */
    #निर्देशः diag_suppress=Pe191
    #निर्देशः diag_suppress=Pa082

#यदि_अन्तः /* __ICCARM__ */


/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 16
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            4
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    3
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 32
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            3
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    2
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 64
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            2
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    1
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 128
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            1
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    0
#नोचेद्यदि config_UNIQUE_व्यवधानम्_PRIORITIES == 256
    #परिभाषय पत्तनम्_प्राथमिकता_सरणम्            0
    #परिभाषय पत्तनम्_MAX_द्विमान_POINT_मानम्    0
#अन्यथा /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #दोषः Invalid config_UNIQUE_व्यवधानम्_PRIORITIES setting.  config_UNIQUE_व्यवधानम्_PRIORITIES must be समुच्चयः गन्तव्यम् the सङ्ख्या सम्बन्धि unique priorities implemented by the target hardware
#यदि_अन्तः /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* Interrupt controller access addresses. */
#परिभाषय पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_विस्थापनम्                      ( 0x04 )
#परिभाषय पत्तनम्_ICCIAR_व्यवधानम्_ACKNOWLEDGE_विस्थापनम्              ( 0x0C )
#परिभाषय पत्तनम्_ICCEOIR_अन्तः_सम्बन्धि_व्यवधानम्_विस्थापनम्                  ( 0x10 )
#परिभाषय पत्तनम्_ICCBPR_द्विमान_POINT_विस्थापनम्                       ( 0x08 )
#परिभाषय पत्तनम्_ICCRPR_RUNNING_प्राथमिकता_विस्थापनम्                   ( 0x14 )

#परिभाषय पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः       ( config_व्यवधानम्_CONTROLLER_आधारः_स्थानाङ्कः + config_व्यवधानम्_CONTROLLER_CPU_INTERFACE_विस्थापनम् )
#परिभाषय पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_पञ्जिकाकोशः                    ( *( ( चञ्चल uint32_t * ) ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_विस्थापनम् ) ) )
#परिभाषय पत्तनम्_ICCIAR_व्यवधानम्_ACKNOWLEDGE_पञ्जिकाकोशः_स्थानाङ्कः    ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCIAR_व्यवधानम्_ACKNOWLEDGE_विस्थापनम् )
#परिभाषय पत्तनम्_ICCEOIR_अन्तः_सम्बन्धि_व्यवधानम्_पञ्जिकाकोशः_स्थानाङ्कः        ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCEOIR_अन्तः_सम्बन्धि_व्यवधानम्_विस्थापनम् )
#परिभाषय पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_पञ्जिकाकोशः_स्थानाङ्कः            ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_विस्थापनम् )
#परिभाषय पत्तनम्_ICCBPR_द्विमान_POINT_पञ्जिकाकोशः                     ( *( ( ध्रुव चञ्चल uint32_t * ) ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCBPR_द्विमान_POINT_विस्थापनम् ) ) )
#परिभाषय पत्तनम्_ICCRPR_RUNNING_प्राथमिकता_पञ्जिकाकोशः                 ( *( ( ध्रुव चञ्चल uint32_t * ) ( पत्तनम्_व्यवधानम्_CONTROLLER_CPU_INTERFACE_स्थानाङ्कः + पत्तनम्_ICCRPR_RUNNING_प्राथमिकता_विस्थापनम् ) ) )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
