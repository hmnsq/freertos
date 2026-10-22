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

#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    خارجي "C" {
#endif
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
#define portCHAR          حرف
#define portFLOAT         عائم
#define portDOUBLE        مزدوج
#define portLONG          long
#define portSHORT         short
#define port_تيندنن_TYPE    uint32_t
#define portBASE_TYPE     long

تعريفنوع port_تيندنن_TYPE   تيندنن_Type_t;
تعريفنوع long             BaseType_t;
تعريفنوع unsigned long    UBaseType_t;

تعريفنوع uint32_t         TickType_t;
#define portMAX_DELAY    ( TickType_t ) 0xffffffffUL

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define port_تيندنن_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#define portEND_SWITCHING_ISR( xSwitchRequired ) \
    {                                            \
        خارجي uint32_t ulPortYieldRequired;     \
                                                 \
        إذا( xSwitchRequired != pdFALSE )         \
        {                                        \
            ulPortYieldRequired = pdTRUE;        \
        }                                        \
    }

#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
#define portYIELD()                __asm متطاير ( "SWI 0" ::: "memory" );


/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

خارجي فراغ vPortEnterCritical( فراغ );
خارجي فراغ vPortExitCritical( فراغ );
خارجي uint32_t ulPortSetInterruptMask( فراغ );
خارجي فراغ vPortClearInterruptMask( uint32_t ul_New_Mask_نيلاي );
خارجي فراغ vPortInstallFreeRTOSVectorTable( فراغ );

/*
 * These macros do not globally disable/enable interrupts. They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY.
 */
#define portENTER_CRITICAL()                      vPortEnterCritical();
#define portEXIT_CRITICAL()                       vPortExitCritical();
#define portDISABLE_INTERRUPTS()                  ulPortSetInterruptMask()
#define portENABLE_INTERRUPTS()                   vPortClearInterruptMask( 0 )
#define portSET_INTERRUPT_MASK_FROM_ISR()         ulPortSetInterruptMask()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vPortClearInterruptMask( x )

/*-----------------------------------------------------------*/

/*
 * Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used.
 */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/*
 * Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick.
 */
فراغ FreeRTOS_Tick_Handler( فراغ );

/*
 * If configUSE_TASK_FPU_SUPPORT is set to 1, then tasks are created without an
 * FPU context and must call vPortTaskUsesFPU() to allocate an FPU context
 * prior to any FPU instructions. If configUSE_TASK_FPU_SUPPORT is set to 2,
 * then all tasks have an FPU context allocated by default.
 */
#إذا ( configUSE_TASK_FPU_SUPPORT == 1 )
    فراغ vPortTaskUsesFPU( فراغ );
    #define portTASK_USES_FLOATING_POINT()    vPortTaskUsesFPU()
#وإلاإذا ( configUSE_TASK_FPU_SUPPORT == 2 )

/*
 * Each task has an FPU context already, so define this function away to
 * prevent it being called accidentally.
 */
    #define vPortTaskUsesFPU()
    #define portTASK_USES_FLOATING_POINT()
#endif /* configUSE_TASK_FPU_SUPPORT */

#define portLOWEST_INTERRUPT_PRIORITY           ( ( ( uint32_t ) configUNIQUE_INTERRUPT_PRIORITIES ) - 1UL )
#define portLOWEST_USABLE_INTERRUPT_PRIORITY    ( portLOWEST_INTERRUPT_PRIORITY - 1UL )

/* Architecture specific optimisations. */
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#endif

#إذا configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( ux_اتس_Priority, uxReadyPriorities )    ux_اتس_Priority = ( 31 - __builtin_clz( uxReadyPriorities ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#إذا ( configASSERT_DEFINED == 1 )
    فراغ vPortValidateInterruptPriority( فراغ );
    #define portASSERT_IF_INTERRUPT_PRIORITY_INVALID()    vPortValidateInterruptPriority()
#endif /* configASSERT */

#define portNOP()                                         __asm متطاير ( "NOP" )


/*
 * The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller.
 */
#إذا configUNIQUE_INTERRUPT_PRIORITIES == 16
    #define portPRIORITY_SHIFT            4
    #define port_MAX_بيناري_POINT_نيلاي    3
#وإلاإذا configUNIQUE_INTERRUPT_PRIORITIES == 32
    #define portPRIORITY_SHIFT            3
    #define port_MAX_بيناري_POINT_نيلاي    2
#وإلاإذا configUNIQUE_INTERRUPT_PRIORITIES == 64
    #define portPRIORITY_SHIFT            2
    #define port_MAX_بيناري_POINT_نيلاي    1
#وإلاإذا configUNIQUE_INTERRUPT_PRIORITIES == 128
    #define portPRIORITY_SHIFT            1
    #define port_MAX_بيناري_POINT_نيلاي    0
#وإلاإذا configUNIQUE_INTERRUPT_PRIORITIES == 256
    #define portPRIORITY_SHIFT            0
    #define port_MAX_بيناري_POINT_نيلاي    0
#وإلا /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #error Invalid configUNIQUE_INTERRUPT_PRIORITIES setting.  configUNIQUE_INTERRUPT_PRIORITIES must be set to the نومبور of unique priorities implemented by the target hardware
#endif /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* Interrupt controller access addresses. */
#define portICCPMR_PRIORITY_MASK_OFFSET                      ( 0x04 )
#define portICCIAR_INTERRUPT_ACKNOWLEDGE_OFFSET              ( 0x0C )
#define portICCEOIR_END_OF_INTERRUPT_OFFSET                  ( 0x10 )
#define port_ICCBPR_بيناري_POINT_OFFSET                       ( 0x08 )
#define portICCRPR_RUNNING_PRIORITY_OFFSET                   ( 0x14 )

#define portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS       ( configINTERRUPT_CONTROLLER_BASE_ADDRESS + configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET )
#define portICCPMR_PRIORITY_MASK_REGISTER                    ( *( ( متطاير uint32_t * ) ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCPMR_PRIORITY_MASK_OFFSET ) ) )
#define portICCIAR_INTERRUPT_ACKNOWLEDGE_REGISTER_ADDRESS    ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCIAR_INTERRUPT_ACKNOWLEDGE_OFFSET )
#define portICCEOIR_END_OF_INTERRUPT_REGISTER_ADDRESS        ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCEOIR_END_OF_INTERRUPT_OFFSET )
#define portICCPMR_PRIORITY_MASK_REGISTER_ADDRESS            ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCPMR_PRIORITY_MASK_OFFSET )
#define port_ICCBPR_بيناري_POINT_REGISTER                     ( *( ( ثابت متطاير uint32_t * ) ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + port_ICCBPR_بيناري_POINT_OFFSET ) ) )
#define portICCRPR_RUNNING_PRIORITY_REGISTER                 ( *( ( ثابت متطاير uint32_t * ) ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCRPR_RUNNING_PRIORITY_OFFSET ) ) )

#define portMEMORY_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#ifdef __cplusplus
    } /* extern C */
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
