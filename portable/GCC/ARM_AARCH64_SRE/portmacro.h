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
#घोषणा port_ढेर_TYPE    माप_प्रकार
#घोषणा portBASE_TYPE     दीर्घ

प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार portBASE_TYPE    BaseType_t;
प्रकार uint64_t         UBaseType_t;

प्रकार uint64_t         TickType_t;
#घोषणा portMAX_DELAY              ( ( TickType_t ) 0xffffffffffffffff )

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#घोषणा portTICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#घोषणा port_ढेर_GROWTH         ( -1 )
#घोषणा portTICK_PERIOD_MS       ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT       16
#घोषणा port_POINTER_आकार_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#घोषणा portEND_SWITCHING_ISR( xSwitchRequired ) \
    {                                            \
        बाह्य uint64_t ullPortYieldRequired;    \
                                                 \
        अगर( xSwitchRequired != pdFALSE )         \
        {                                        \
            ullPortYieldRequired = pdTRUE;       \
        }                                        \
    }

#घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
#अगर defined( GUEST )
    #घोषणा portYIELD()            __asm अस्थिर ( "SVC 0" ::: "memory" )
#अन्यथा
    #घोषणा portYIELD()            __asm अस्थिर ( "SMC 0" ::: "memory" )
#पूर्ण_अगर

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

बाह्य व्योम vPortEnterCritical( व्योम );
बाह्य व्योम vPortExitCritical( व्योम );
बाह्य UBaseType_t uxPortSetInterruptMask( व्योम );
बाह्य व्योम vPortClearInterruptMask( UBaseType_t ux_New_Mask_मूल्य );
बाह्य व्योम vPortInstallFreeRTOSVectorTable( व्योम );

#घोषणा portDISABLE_INTERRUPTS()                       \
    __asm अस्थिर ( "MSR DAIFSET, #2" ::: "memory" ); \
    __asm अस्थिर ( "DSB SY" );                       \
    __asm अस्थिर ( "ISB SY" );

#घोषणा portENABLE_INTERRUPTS()                        \
    __asm अस्थिर ( "MSR DAIFCLR, #2" ::: "memory" ); \
    __asm अस्थिर ( "DSB SY" );                       \
    __asm अस्थिर ( "ISB SY" );


/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#घोषणा portENTER_CRITICAL()                      vPortEnterCritical();
#घोषणा portEXIT_CRITICAL()                       vPortExitCritical();
#घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         uxPortSetInterruptMask()
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

/* If configUSE_TASK_FPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without an FPU context and must call vPortTaskUsesFPU() to give
 * themselves an FPU context before using any FPU instructions.  If
 * configUSE_TASK_FPU_SUPPORT is set to 2 then all tasks will have an FPU context
 * by default. */
#अगर ( configUSE_TASK_FPU_SUPPORT != 2 )
    व्योम vPortTaskUsesFPU( व्योम );
#अन्यथा
    /* Each task has an FPU context already, so define this function away to
    * nothing to prevent it from being called accidentally. */
    #घोषणा vPortTaskUsesFPU()
#पूर्ण_अगर
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

    #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    ux_शीर्ष_Priority = ( 31 - __builtin_clz( uxReadyPriorities ) )

#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#अगर ( configASSERT_DEFINED == 1 )
    व्योम vPortValidateInterruptPriority( व्योम );
    #घोषणा portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
#पूर्ण_अगर /* configASSERT */

#घोषणा portNOP()                                         __asm अस्थिर ( "NOP" )
#घोषणा portINLINE    __inline

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

#घोषणा portMEMORY_BARRIER()    __asm अस्थिर ( "" ::: "memory" )

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
