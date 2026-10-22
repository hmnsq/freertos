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

#ಅನ್ತರ್ಭಾವ <intrinsics.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
    ಬಾಹ್ಯ "C" {
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
#define portCHAR          ವರ್ಣ
#define portFLOAT         ಭಿನ್ನ
#define portDOUBLE        ದ್ವಿಗುಣ
#define portLONG          long
#define portSHORT         short
#define port_ರಾಶಿ_TYPE    uint32_t
#define portBASE_TYPE     long

ಪ್ರಕಾರನಿರ್ದೇಶ port_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರನಿರ್ದೇಶ long             BaseType_t;
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned long    UBaseType_t;

ಪ್ರಕಾರನಿರ್ದೇಶ uint32_t         TickType_t;
#define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#define portTICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define port_ರಾಶಿ_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#define portEND_SWITCHING_ISR( xSwitchRequired )      \
    {                                                 \
        ಬಾಹ್ಯ ಚಞ್ಚಲ uint32_t ulPortYieldRequired; \
                                                      \
        ಯದಿ( xSwitchRequired != pdFALSE )              \
        {                                             \
            ulPortYieldRequired = pdTRUE;             \
        }                                             \
    }

#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
#define portYIELD()                 \
    __asm ಚಞ್ಚಲ ( "SWI 0     \n" \
                     "ISB         " );


/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

ಬಾಹ್ಯ ಶೂನ್ಯ vPortEnterCritical( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vPortExitCritical( ಶೂನ್ಯ );
ಬಾಹ್ಯ uint32_t ulPortSetInterruptMask( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vPortClearInterruptMask( uint32_t ul_New_Mask_ಮೌಲ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vPortInstallFreeRTOSVectorTable( ಶೂನ್ಯ );

/* The I bit within the CPSR. */
#define portINTERRUPT_ENABLE_BIT    ( 1 << 7 )

/* In the absence of a priority mask register, these functions and macros
 * globally enable and disable interrupts. */
#define portENTER_CRITICAL()       vPortEnterCritical();
#define portEXIT_CRITICAL()        vPortExitCritical();
#define portENABLE_INTERRUPTS()    __asm ಚಞ್ಚಲ ( "CPSIE i   \n" );
#define portDISABLE_INTERRUPTS()    \
    __asm ಚಞ್ಚಲ ( "CPSID i   \n" \
                     "DSB       \n" \
                     "ISB         " );
#pragma ಅನ್ತಃಸ್ಥ
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ uint32_t portINLINE_SET_INTERRUPT_MASK_FROM_ISR( ಶೂನ್ಯ )
{
    ಚಞ್ಚಲ uint32_t ulCPSR;

    __asm ಚಞ್ಚಲ ( "MRS %0, CPSR" : "=r" ( ulCPSR ) );

    ulCPSR &= portINTERRUPT_ENABLE_BIT;
    portDISABLE_INTERRUPTS();
    ಪ್ರತ್ಯಾಗಮ ulCPSR;
}

#define portSET_INTERRUPT_MASK_FROM_ISR()         portINLINE_SET_INTERRUPT_MASK_FROM_ISR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    ಕುರು { ಯದಿ( x == 0 ) portENABLE_INTERRUPTS( ); } ಯಾವತ್( 0 )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
ಶೂನ್ಯ FreeRTOS_Tick_Handler( ಶೂನ್ಯ );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
ಶೂನ್ಯ vPortTaskUsesFPU( ಶೂನ್ಯ );
#define portTASK_USES_FLOATING_POINT()    vPortTaskUsesFPU()

#define portLOWEST_INTERRUPT_PRIORITY           ( ( ( uint32_t ) configUNIQUE_INTERRUPT_PRIORITIES ) - 1UL )
#define portLOWEST_USABLE_INTERRUPT_PRIORITY    ( portLOWEST_INTERRUPT_PRIORITY - 1UL )

/* Architecture specific optimisations. */
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#endif

#ಯದಿ configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( ux_ತುದಿ_Priority, uxReadyPriorities )    ux_ತುದಿ_Priority = ( 31UL - ( uint32_t ) __CLZ( uxReadyPriorities ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#define portNOP()    __asm ಚಞ್ಚಲ ( "NOP" )
#define portINLINE    ಅನ್ತಃಸ್ಥ

/* Suppress warnings that are generated by the IAR tools, but cannot be fixed in
 * the source code because to do so would cause other compilers to generate
 * warnings. */
#pragma diag_suppress=Pe191
#pragma diag_suppress=Pa082

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
