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
#परिभाषय पत्तनम्_MAX_DELAY    ( ( TickType_t ) 0xffffffffUL )

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#परिभाषय पत्तनम्_राशिः_GROWTH      ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT    32

/*-----------------------------------------------------------*/

/* Task utilities. */

/* The interrupt priority (for vectors 16 to 255) is determined using vector/16.
 * The quotient is rounded to the nearest integer with 1 being the lowest priority
 * and 15 is the highest.  Therefore the following two interrupts are at the lowest
 * priority.  *NOTE 1* If the yield vector is changed then it must also be changed
 * in the portYIELD_INTERRUPT definition immediately below. */
#परिभाषय पत्तनम्_APIC_TIMER_INT_सदिशम्       ( 0x21 )
#परिभाषय पत्तनम्_APIC_YIELD_INT_सदिशम्       ( 0x20 )

/* Build yield interrupt instruction. */
#परिभाषय पत्तनम्_YIELD_व्यवधानम्             "int $0x20"

/* APIC register addresses. */
#परिभाषय पत्तनम्_APIC_EOI                    ( *( ( चञ्चल uint32_t * ) 0xFEE000B0UL ) )

/* APIC bit definitions. */
#परिभाषय पत्तनम्_APIC_ENABLE_BIT             ( 1UL << 8UL )
#परिभाषय पत्तनम्_APIC_TIMER_PERIODIC         ( 1UL << 17UL )
#परिभाषय पत्तनम्_APIC_DISABLE                ( 1UL << 16UL )
#परिभाषय पत्तनम्_APIC_NMI                    ( 4 << 8 )
#परिभाषय पत्तनम्_APIC_DIV_16                 ( 0x03 )

/* Define local API register addresses. */
#परिभाषय पत्तनम्_APIC_ID_पञ्जिकाकोशः            ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0x20UL ) ) )
#परिभाषय पत्तनम्_APIC_SPURIOUS_INT           ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0xF0UL ) ) )
#परिभाषय पत्तनम्_APIC_LVT_TIMER              ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0x320UL ) ) )
#परिभाषय पत्तनम्_APIC_TIMER_INITIAL_गणनम्    ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0x380UL ) ) )
#परिभाषय पत्तनम्_APIC_TIMER_CURRENT_गणनम्    ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0x390UL ) ) )
#परिभाषय पत्तनम्_APIC_TASK_प्राथमिकता          ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0x80UL ) ) )
#परिभाषय पत्तनम्_APIC_LVT_ERROR              ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0x370UL ) ) )
#परिभाषय पत्तनम्_APIC_ERROR_स्थितिः           ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0x280UL ) ) )
#परिभाषय पत्तनम्_APIC_LDR                    ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0xD0UL ) ) )
#परिभाषय पत्तनम्_APIC_TMRDIV                 ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0x3E0UL ) ) )
#परिभाषय पत्तनम्_APIC_LVT_PERF               ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0x340UL ) ) )
#परिभाषय पत्तनम्_APIC_LVT_LINT0              ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0x350UL ) ) )
#परिभाषय पत्तनम्_APIC_LVT_LINT1              ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0x360UL ) ) )

/* Don't yield if inside a critical section - instead hold the yield pending
 * so it is performed when the critical section is exited. */
#परिभाषय पत्तनम्_YIELD()                                  \
    {                                                \
        बाह्य चञ्चल uint32_t ulCriticalNesting;  \
        बाह्य चञ्चल uint32_t ul_पत्तनम्_Yield_Pending; \
        यदि( ulCriticalNesting != 0 )                 \
        {                                            \
            ul_पत्तनम्_Yield_Pending = pdTRUE;             \
        }                                            \
        अन्यथा                                         \
        {                                            \
            __asm चञ्चल ( पत्तनम्_YIELD_व्यवधानम् );  \
        }                                            \
    }

/* Called at the end of an ISR that can cause a context switch - pend a yield if
 * xSwitchRequired is not false. */
#परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired )     \
    {                                                \
        बाह्य चञ्चल uint32_t ul_पत्तनम्_Yield_Pending; \
        यदि( xSwitchRequired != pdFALSE )             \
        {                                            \
            ul_पत्तनम्_Yield_Pending = 1;                  \
        }                                            \
    }

/* Same as portEND_SWITCHING_ISR() - take your pick which name to use. */
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )    पत्तनम्_अन्तः_SWITCHING_ISR( x )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

/* Critical sections for use in interrupts. */
#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         ul_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )    v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( x )

बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य );
बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य );
बाह्य uint32_t ul_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्( शून्य );
बाह्य शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( uint32_t ul_New_आवरणम्_मानम् );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#परिभाषय पत्तनम्_ENTER_CRITICAL()        v_पत्तनम्_Enter_Critical()
#परिभाषय पत्तनम्_EXIT_CRITICAL()         v_पत्तनम्_Exit_Critical()
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    __asm चञ्चल ( "cli" )
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     __asm चञ्चल ( "sti" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

/* Architecture specific optimisations. */
#यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities ) \
    __asm चञ्चल ( "bsr %1, %0\n\t"                                    \
                     : "=r" ( ux_शिखरम्_प्राथमिकता ) : "rm" ( uxReadyPriorities ) : "cc" )

    #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
    #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#परिभाषय पत्तनम्_NOP()    __asm चञ्चल ( "NOP" )

/*-----------------------------------------------------------
* Misc
*----------------------------------------------------------*/

#परिभाषय पत्तनम्_अङ्कः_VECTORS     256
#परिभाषय पत्तनम्_MAX_प्राथमिकता    15
प्रकारनिर्देश शून्य ( * ISR_Handler_t ) ( शून्य );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
#यदि_अपरिभाषितम् configSUPPORT_FPU
    #परिभाषय configSUPPORT_FPU    0
#यदि_अन्तः

#यदि configSUPPORT_FPU == 1
    शून्य v_पत्तनम्_Task_उपयुङ्क्ते_FPU( शून्य );
    #परिभाषय पत्तनम्_TASK_उपयुङ्क्ते_FLOATING_POINT()    v_पत्तनम्_Task_उपयुङ्क्ते_FPU()
#यदि_अन्तः

/* See the comments under the configUSE_COMMON_INTERRUPT_ENTRY_POINT definition
 * below. */
आधारः_Type_t x_पत्तनम्_पञ्जिकाकोशः_CInterrupt_Handler( ISR_Handler_t pxHandler,
                                           uint32_t ul_सदिशम्_सङ्ख्या );
आधारः_Type_t x_पत्तनम्_Install_व्यवधानम्_Handler( ISR_Handler_t pxHandler,
                                         uint32_t ul_सदिशम्_सङ्ख्या );

#यदि_अपरिभाषितम् config_APIC_आधारः

/* configAPIC_BASE_ADDRESS sets the base address of the local APIC.  It can
 * be overridden in FreeRTOSConfig.h should it not be constant. */
    #परिभाषय config_APIC_आधारः    0xFEE00000UL
#यदि_अन्तः

#यदि_अपरिभाषितम् config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION

/* The FreeRTOS scheduling algorithm selects the task that will enter the
 * Running state.  configUSE_PORT_OPTIMISED_TASK_SELECTION is used to set how
 * that is done.
 *
 * If configUSE_PORT_OPTIMISED_TASK_SELECTION is set to 0 then the task to
 * enter the Running state is selected using a portable algorithm written in
 * C.  This is the slowest method, but the algorithm does not restrict the
 * maximum number of unique RTOS task priorities that are available.
 *
 * If configUSE_PORT_OPTIMISED_TASK_SELECTION is set to 1 then the task to
 * enter the Running state is selected using a single assembly instruction.
 * This is the fastest method, but restricts the maximum number of unique RTOS
 * task priorities to 32 (the same task priority can be assigned to any number
 * of RTOS tasks). */
    #warning config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION was not defined अन्तर् FreeRTOSConfig.h and has been defaulted गन्तव्यम् 1
    #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    1
#यदि_अन्तः

#यदि_अपरिभाषितम् config_USE_COMMON_व्यवधानम्_प्रविष्टिः_POINT

/* There are two ways of implementing interrupt handlers:
 *
 *  1) As standard C functions -
 *
 *  This method can only be used if configUSE_COMMON_INTERRUPT_ENTRY_POINT
 *  is set to 1.  The C function is installed using
 *  xPortRegisterCInterruptHandler().
 *
 *  This is the simplest of the two methods but incurs a slightly longer
 *  interrupt entry time.
 *
 *  2) By using an assembly stub that wraps the handler in the FreeRTOS
 *     portFREERTOS_INTERRUPT_ENTRY and portFREERTOS_INTERRUPT_EXIT macros.
 *
 *  This method can always be used.  It is slightly more complex than
 *  method 1 but benefits from a faster interrupt entry time. */
    #warning config_USE_COMMON_व्यवधानम्_प्रविष्टिः_POINT was not defined अन्तर् FreeRTOSConfig.h and has been defaulted गन्तव्यम् 1.
    #परिभाषय config_USE_COMMON_व्यवधानम्_प्रविष्टिः_POINT    1
#यदि_अन्तः

#यदि_अपरिभाषितम् config_ISR_राशिः_आकार

/* Interrupt entry code will switch the stack in use to a dedicated system
 * stack.
 *
 * configISR_STACK_SIZE defines the number of 32-bit values that can be stored
 * on the system stack, and must be large enough to hold a potentially nested
 * interrupt stack frame. */

    #दोषः config_ISR_राशिः_आकार was not defined अन्तर् FreeRTOSConfig.h.
#यदि_अन्तः

#यदि_अपरिभाषितम् config_MAX_API_CALL_व्यवधानम्_प्राथमिकता

/* Interrupt safe FreeRTOS functions (those that end in "FromISR" must not
 * be called from an interrupt that has a priority above that set by
 * configMAX_API_CALL_INTERRUPT_PRIORITY.  */
    #warning config_MAX_API_CALL_व्यवधानम्_प्राथमिकता was not defined अन्तर् FreeRTOSConfig.h and has been defaulted गन्तव्यम् 10
    #परिभाषय config_MAX_API_CALL_व्यवधानम्_प्राथमिकता    10
#यदि_अन्तः

#यदि_अपरिभाषितम् configSUPPORT_FPU
    #warning configSUPPORT_FPU was not defined अन्तर् FreeRTOSConfig.h and has been defaulted गन्तव्यम् 0
    #परिभाषय configSUPPORT_FPU    0
#यदि_अन्तः

/* The value written to the task priority register to raise the interrupt mask
 * to the maximum from which FreeRTOS API calls can be made. */
#परिभाषय पत्तनम्_APIC_प्राथमिकता_सरणम्        ( 4UL )
#परिभाषय पत्तनम्_APIC_MAX_SUB_प्राथमिकता      ( 0x0fUL )
#परिभाषय पत्तनम्_MAX_API_CALL_प्राथमिकता      ( ( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता << पत्तनम्_APIC_प्राथमिकता_सरणम् ) | पत्तनम्_APIC_MAX_SUB_प्राथमिकता )

/* Asserts if interrupt safe FreeRTOS functions are called from a priority
 * above the max system call interrupt priority. */
#परिभाषय पत्तनम्_APIC_PROCESSOR_प्राथमिकता    ( *( ( चञ्चल uint32_t * ) ( config_APIC_आधारः + 0xA0UL ) ) )
#परिभाषय पत्तनम्_ASSERT_IF_व्यवधानम्_प्राथमिकता_INVALID()    configASSERT( ( पत्तनम्_APIC_PROCESSOR_प्राथमिकता ) <= ( पत्तनम्_MAX_API_CALL_प्राथमिकता ) )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
