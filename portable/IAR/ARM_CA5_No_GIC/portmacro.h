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
    #परिभाषय पत्तनम्_YIELD()                __asm चञ्चल ( "SWI 0" ); __ISB()


/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

    बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य );
    बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य );
    बाह्य uint32_t ul_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्( शून्य );
    बाह्य शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( uint32_t ul_New_आवरणम्_मानम् );

    #परिभाषय पत्तनम्_ENTER_CRITICAL()                      v_पत्तनम्_Enter_Critical();
    #परिभाषय पत्तनम्_EXIT_CRITICAL()                       v_पत्तनम्_Exit_Critical();
    #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                  __disable_irq(); __DSB(); __ISB()        /* No priority mask register so global disable is used. */
    #परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                   __enable_irq()
    #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         __get_interrupt_state(); __disable_irq() /* No priority mask register so global disable is used. */
    #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )    __set_interrupt_state( x )

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

    #परिभाषय पत्तनम्_NOP()    __asm चञ्चल ( "NOP" )

/* Suppress warnings that are generated by the IAR tools, but cannot be
 * fixed in the source code because to do so would cause other compilers to
 * generate warnings. */
    #निर्देशः diag_suppress=Pe191
    #निर्देशः diag_suppress=Pa082

#यदि_अन्तः /* __ICCARM__ */

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
