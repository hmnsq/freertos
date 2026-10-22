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

#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
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

प्रकार uint32_t         TickType_t;
#घोषणा portMAX_DELAY    ( ( TickType_t ) 0xffffffffUL )

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#घोषणा port_ढेर_GROWTH      ( -1 )
#घोषणा portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT    32

/*-----------------------------------------------------------*/

/* Task utilities. */

/* The interrupt priority (for vectors 16 to 255) is determined using vector/16.
 * The quotient is rounded to the nearest integer with 1 being the lowest priority
 * and 15 is the highest.  Therefore the following two interrupts are at the lowest
 * priority.  *NOTE 1* If the yield vector is changed then it must also be changed
 * in the portYIELD_INTERRUPT definition immediately below. */
#घोषणा portAPIC_TIMER_INT_VECTOR       ( 0x21 )
#घोषणा portAPIC_YIELD_INT_VECTOR       ( 0x20 )

/* Build yield interrupt instruction. */
#घोषणा portYIELD_INTERRUPT             "int $0x20"

/* APIC register addresses. */
#घोषणा portAPIC_EOI                    ( *( ( अस्थिर uint32_t * ) 0xFEE000B0UL ) )

/* APIC bit definitions. */
#घोषणा portAPIC_ENABLE_BIT             ( 1UL << 8UL )
#घोषणा portAPIC_TIMER_PERIODIC         ( 1UL << 17UL )
#घोषणा portAPIC_DISABLE                ( 1UL << 16UL )
#घोषणा portAPIC_NMI                    ( 4 << 8 )
#घोषणा portAPIC_DIV_16                 ( 0x03 )

/* Define local API register addresses. */
#घोषणा portAPIC_ID_REGISTER            ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0x20UL ) ) )
#घोषणा portAPIC_SPURIOUS_INT           ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0xF0UL ) ) )
#घोषणा portAPIC_LVT_TIMER              ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0x320UL ) ) )
#घोषणा port_APIC_TIMER_INITIAL_गिनती    ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0x380UL ) ) )
#घोषणा port_APIC_TIMER_CURRENT_गिनती    ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0x390UL ) ) )
#घोषणा portAPIC_TASK_PRIORITY          ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0x80UL ) ) )
#घोषणा portAPIC_LVT_ERROR              ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0x370UL ) ) )
#घोषणा portAPIC_ERROR_STATUS           ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0x280UL ) ) )
#घोषणा portAPIC_LDR                    ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0xD0UL ) ) )
#घोषणा portAPIC_TMRDIV                 ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0x3E0UL ) ) )
#घोषणा portAPIC_LVT_PERF               ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0x340UL ) ) )
#घोषणा portAPIC_LVT_LINT0              ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0x350UL ) ) )
#घोषणा portAPIC_LVT_LINT1              ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0x360UL ) ) )

/* Don't yield if inside a critical section - instead hold the yield pending
 * so it is performed when the critical section is exited. */
#घोषणा portYIELD()                                  \
    {                                                \
        बाह्य अस्थिर uint32_t ulCriticalNesting;  \
        बाह्य अस्थिर uint32_t ulPortYieldPending; \
        अगर( ulCriticalNesting != 0 )                 \
        {                                            \
            ulPortYieldPending = pdTRUE;             \
        }                                            \
        अन्यथा                                         \
        {                                            \
            __asm अस्थिर ( portYIELD_INTERRUPT );  \
        }                                            \
    }

/* Called at the end of an ISR that can cause a context switch - pend a yield if
 * xSwitchRequired is not false. */
#घोषणा portEND_SWITCHING_ISR( xSwitchRequired )     \
    {                                                \
        बाह्य अस्थिर uint32_t ulPortYieldPending; \
        अगर( xSwitchRequired != pdFALSE )             \
        {                                            \
            ulPortYieldPending = 1;                  \
        }                                            \
    }

/* Same as portEND_SWITCHING_ISR() - take your pick which name to use. */
#घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

/* Critical sections for use in interrupts. */
#घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         ulPortSetInterruptMask()
#घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortClearInterruptMask( x )

बाह्य व्योम vPortEnterCritical( व्योम );
बाह्य व्योम vPortExitCritical( व्योम );
बाह्य uint32_t ulPortSetInterruptMask( व्योम );
बाह्य व्योम vPortClearInterruptMask( uint32_t ul_New_Mask_मूल्य );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#घोषणा portENTER_CRITICAL()        vPortEnterCritical()
#घोषणा portEXIT_CRITICAL()         vPortExitCritical()
#घोषणा portDISABLE_INTERRUPTS()    __asm अस्थिर ( "cli" )
#घोषणा portENABLE_INTERRUPTS()     __asm अस्थिर ( "sti" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

/* Architecture specific optimisations. */
#अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities ) \
    __asm अस्थिर ( "bsr %1, %0\n\t"                                    \
                     : "=r" ( ux_शीर्ष_Priority ) : "rm" ( uxReadyPriorities ) : "cc" )

    #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#घोषणा portNOP()    __asm अस्थिर ( "NOP" )

/*-----------------------------------------------------------
* Misc
*----------------------------------------------------------*/

#घोषणा port_अंक_VECTORS     256
#घोषणा portMAX_PRIORITY    15
प्रकार व्योम ( * ISR_Handler_t ) ( व्योम );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
#अगर_अघोषित configSUPPORT_FPU
    #घोषणा configSUPPORT_FPU    0
#पूर्ण_अगर

#अगर configSUPPORT_FPU == 1
    व्योम vPortTaskUsesFPU( व्योम );
    #घोषणा portTASK_USES_FLOATING_POINT()    vPortTaskUsesFPU()
#पूर्ण_अगर

/* See the comments under the configUSE_COMMON_INTERRUPT_ENTRY_POINT definition
 * below. */
BaseType_t xPortRegisterCInterruptHandler( ISR_Handler_t pxHandler,
                                           uint32_t ul_Vector_संख्या );
BaseType_t xPortInstallInterruptHandler( ISR_Handler_t pxHandler,
                                         uint32_t ul_Vector_संख्या );

#अगर_अघोषित configAPIC_BASE

/* configAPIC_BASE_ADDRESS sets the base address of the local APIC.  It can
 * be overridden in FreeRTOSConfig.h should it not be constant. */
    #घोषणा configAPIC_BASE    0xFEE00000UL
#पूर्ण_अगर

#अगर_अघोषित configUSE_PORT_OPTIMISED_TASK_SELECTION

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
    #warning configUSE_PORT_OPTIMISED_TASK_SELECTION was not defined in FreeRTOSConfig.h and has been defaulted to 1
    #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#पूर्ण_अगर

#अगर_अघोषित configUSE_COMMON_INTERRUPT_ENTRY_POINT

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
    #warning configUSE_COMMON_INTERRUPT_ENTRY_POINT was not defined in FreeRTOSConfig.h and has been defaulted to 1.
    #घोषणा configUSE_COMMON_INTERRUPT_ENTRY_POINT    1
#पूर्ण_अगर

#अगर_अघोषित config_ISR_ढेर_आकार

/* Interrupt entry code will switch the stack in use to a dedicated system
 * stack.
 *
 * configISR_STACK_SIZE defines the number of 32-bit values that can be stored
 * on the system stack, and must be large enough to hold a potentially nested
 * interrupt stack frame. */

    #त्रुटि config_ISR_ढेर_आकार was not defined in FreeRTOSConfig.h.
#पूर्ण_अगर

#अगर_अघोषित configMAX_API_CALL_INTERRUPT_PRIORITY

/* Interrupt safe FreeRTOS functions (those that end in "FromISR" must not
 * be called from an interrupt that has a priority above that set by
 * configMAX_API_CALL_INTERRUPT_PRIORITY.  */
    #warning configMAX_API_CALL_INTERRUPT_PRIORITY was not defined in FreeRTOSConfig.h and has been defaulted to 10
    #घोषणा configMAX_API_CALL_INTERRUPT_PRIORITY    10
#पूर्ण_अगर

#अगर_अघोषित configSUPPORT_FPU
    #warning configSUPPORT_FPU was not defined in FreeRTOSConfig.h and has been defaulted to 0
    #घोषणा configSUPPORT_FPU    0
#पूर्ण_अगर

/* The value written to the task priority register to raise the interrupt mask
 * to the maximum from which FreeRTOS API calls can be made. */
#घोषणा portAPIC_PRIORITY_SHIFT        ( 4UL )
#घोषणा portAPIC_MAX_SUB_PRIORITY      ( 0x0fUL )
#घोषणा portMAX_API_CALL_PRIORITY      ( ( configMAX_API_CALL_INTERRUPT_PRIORITY << portAPIC_PRIORITY_SHIFT ) | portAPIC_MAX_SUB_PRIORITY )

/* Asserts if interrupt safe FreeRTOS functions are called from a priority
 * above the max system call interrupt priority. */
#घोषणा portAPIC_PROCESSOR_PRIORITY    ( *( ( अस्थिर uint32_t * ) ( configAPIC_BASE + 0xA0UL ) ) )
#घोषणा portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    configASSERT( ( portAPIC_PROCESSOR_PRIORITY ) <= ( portMAX_API_CALL_PRIORITY ) )

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
