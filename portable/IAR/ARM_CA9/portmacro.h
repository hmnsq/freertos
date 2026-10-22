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

/* IAR includes. */
#अगर_घोषित __ICCARM__

    #समावेश <intrinsics.h>

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
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #घोषणा portTICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #घोषणा port_ढेर_GROWTH      ( -1 )
    #घोषणा portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
    #घोषणा portBYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
    #घोषणा portEND_SWITCHING_ISR( xSwitchRequired ) \
    {                                                \
        बाह्य uint32_t ulPortYieldRequired;         \
                                                     \
        अगर( xSwitchRequired != pdFALSE )             \
        {                                            \
            ulPortYieldRequired = pdTRUE;            \
        }                                            \
    }

    #घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
    #घोषणा portYIELD()                __asm( "SWI 0" );


/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

    बाह्य व्योम vPortEnterCritical( व्योम );
    बाह्य व्योम vPortExitCritical( व्योम );
    बाह्य uint32_t ulPortSetInterruptMask( व्योम );
    बाह्य व्योम vPortClearInterruptMask( uint32_t ul_New_Mask_मूल्य );

/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
    #घोषणा portENTER_CRITICAL()                      vPortEnterCritical();
    #घोषणा portEXIT_CRITICAL()                       vPortExitCritical();
    #घोषणा portDISABLE_INTERRUPTS()                  ulPortSetInterruptMask()
    #घोषणा portENABLE_INTERRUPTS()                   vPortClearInterruptMask( 0 )
    #घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         ulPortSetInterruptMask()
    #घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortClearInterruptMask( x )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
    #घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
    #घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
    व्योम FreeRTOS_Tick_Handler( व्योम );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
    व्योम vPortTaskUsesFPU( व्योम );
    #घोषणा portTASK_USES_FLOATING_POINT()    vPortTaskUsesFPU()

    #घोषणा portLOWEST_INTERRUPT_PRIORITY           ( ( ( uint32_t ) configUNIQUE_INTERRUPT_PRIORITIES ) - 1UL )
    #घोषणा portLOWEST_USABLE_INTERRUPT_PRIORITY    ( portLOWEST_INTERRUPT_PRIORITY - 1UL )

/* Architecture specific optimisations. */
    #अगर_अघोषित configUSE_PORT_OPTIMISED_TASK_SELECTION
        #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    1
    #पूर्ण_अगर

    #अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
        #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
        #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

        #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    ux_शीर्ष_Priority = ( 31 - __CLZ( uxReadyPriorities ) )

    #पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #अगर ( configASSERT_DEFINED == 1 )
        व्योम vPortValidateInterruptPriority( व्योम );
        #घोषणा portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
    #पूर्ण_अगर /* configASSERT */

    #घोषणा portNOP()                                         __asm अस्थिर ( "NOP" )

/* Suppress warnings that are generated by the IAR tools, but cannot be
 * fixed in the source code because to do so would cause other compilers to
 * generate warnings. */
    #आशय diag_suppress=Pe191
    #आशय diag_suppress=Pa082

#पूर्ण_अगर /* __ICCARM__ */


/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#अगर configUNIQUE_INTERRUPT_PRIORITIES == 16
    #घोषणा portPRIORITY_SHIFT            4
    #घोषणा port_MAX_द्विआधारी_POINT_मूल्य    3
#या_अगर configUNIQUE_INTERRUPT_PRIORITIES == 32
    #घोषणा portPRIORITY_SHIFT            3
    #घोषणा port_MAX_द्विआधारी_POINT_मूल्य    2
#या_अगर configUNIQUE_INTERRUPT_PRIORITIES == 64
    #घोषणा portPRIORITY_SHIFT            2
    #घोषणा port_MAX_द्विआधारी_POINT_मूल्य    1
#या_अगर configUNIQUE_INTERRUPT_PRIORITIES == 128
    #घोषणा portPRIORITY_SHIFT            1
    #घोषणा port_MAX_द्विआधारी_POINT_मूल्य    0
#या_अगर configUNIQUE_INTERRUPT_PRIORITIES == 256
    #घोषणा portPRIORITY_SHIFT            0
    #घोषणा port_MAX_द्विआधारी_POINT_मूल्य    0
#अन्यथा /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #त्रुटि Invalid configUNIQUE_INTERRUPT_PRIORITIES setting.  configUNIQUE_INTERRUPT_PRIORITIES must be set to the संख्या of unique priorities implemented by the target hardware
#पूर्ण_अगर /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* Interrupt controller access addresses. */
#घोषणा portICCPMR_PRIORITY_MASK_OFFSET                      ( 0x04 )
#घोषणा portICCIAR_INTERRUPT_ACKNOWLEDGE_OFFSET              ( 0x0C )
#घोषणा portICCEOIR_END_OF_INTERRUPT_OFFSET                  ( 0x10 )
#घोषणा port_ICCBPR_द्विआधारी_POINT_OFFSET                       ( 0x08 )
#घोषणा portICCRPR_RUNNING_PRIORITY_OFFSET                   ( 0x14 )

#घोषणा portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS       ( configINTERRUPT_CONTROLLER_BASE_ADDRESS + configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET )
#घोषणा portICCPMR_PRIORITY_MASK_REGISTER                    ( *( ( अस्थिर uint32_t * ) ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCPMR_PRIORITY_MASK_OFFSET ) ) )
#घोषणा portICCIAR_INTERRUPT_ACKNOWLEDGE_REGISTER_ADDRESS    ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCIAR_INTERRUPT_ACKNOWLEDGE_OFFSET )
#घोषणा portICCEOIR_END_OF_INTERRUPT_REGISTER_ADDRESS        ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCEOIR_END_OF_INTERRUPT_OFFSET )
#घोषणा portICCPMR_PRIORITY_MASK_REGISTER_ADDRESS            ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCPMR_PRIORITY_MASK_OFFSET )
#घोषणा port_ICCBPR_द्विआधारी_POINT_REGISTER                     ( *( ( स्थिर अस्थिर uint32_t * ) ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + port_ICCBPR_द्विआधारी_POINT_OFFSET ) ) )
#घोषणा portICCRPR_RUNNING_PRIORITY_REGISTER                 ( *( ( स्थिर अस्थिर uint32_t * ) ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCRPR_RUNNING_PRIORITY_OFFSET ) ) )

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
