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

#ଅନ୍ତର୍ଭାଵ <intrinsics.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
    ବାହ୍ୟ "C" {
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
#define portCHAR          ଅକ୍ଷର
#define portFLOAT         ଦଶମିକ
#define portDOUBLE        ଦ୍ୱିଗୁଣ
#define portLONG          long
#define portSHORT         short
#define port_ଗଦା_TYPE    uint32_t
#define portBASE_TYPE     long

ପ୍ରକାରବ୍ୟାଖ୍ୟା port_ଗଦା_TYPE   ଗଦା_Type_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା long             BaseType_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned long    UBaseType_t;

ପ୍ରକାରବ୍ୟାଖ୍ୟା uint32_t         TickType_t;
#define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#define portTICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#define port_ଗଦା_GROWTH      ( -1 )
#define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#define portEND_SWITCHING_ISR( xSwitchRequired )      \
    {                                                 \
        ବାହ୍ୟ ଅସ୍ଥିର uint32_t ulPortYieldRequired; \
                                                      \
        ଯଦି( xSwitchRequired != pdFALSE )              \
        {                                             \
            ulPortYieldRequired = pdTRUE;             \
        }                                             \
    }

#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
#define portYIELD()                 \
    __asm ଅସ୍ଥିର ( "SWI 0     \n" \
                     "ISB         " );


/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

ବାହ୍ୟ ଶୂନ୍ୟ vPortEnterCritical( ଶୂନ୍ୟ );
ବାହ୍ୟ ଶୂନ୍ୟ vPortExitCritical( ଶୂନ୍ୟ );
ବାହ୍ୟ uint32_t ulPortSetInterruptMask( ଶୂନ୍ୟ );
ବାହ୍ୟ ଶୂନ୍ୟ vPortClearInterruptMask( uint32_t ul_New_Mask_ମୂଲ୍ୟ );
ବାହ୍ୟ ଶୂନ୍ୟ vPortInstallFreeRTOSVectorTable( ଶୂନ୍ୟ );

/* The I bit within the CPSR. */
#define portINTERRUPT_ENABLE_BIT    ( 1 << 7 )

/* In the absence of a priority mask register, these functions and macros
 * globally enable and disable interrupts. */
#define portENTER_CRITICAL()       vPortEnterCritical();
#define portEXIT_CRITICAL()        vPortExitCritical();
#define portENABLE_INTERRUPTS()    __asm ଅସ୍ଥିର ( "CPSIE i   \n" );
#define portDISABLE_INTERRUPTS()    \
    __asm ଅସ୍ଥିର ( "CPSID i   \n" \
                     "DSB       \n" \
                     "ISB         " );
#pragma ଧାଡ଼ିଭିତରେ
ସ୍ଥିର ଧାଡ଼ିଭିତରେ uint32_t portINLINE_SET_INTERRUPT_MASK_FROM_ISR( ଶୂନ୍ୟ )
{
    ଅସ୍ଥିର uint32_t ulCPSR;

    __asm ଅସ୍ଥିର ( "MRS %0, CPSR" : "=r" ( ulCPSR ) );

    ulCPSR &= portINTERRUPT_ENABLE_BIT;
    portDISABLE_INTERRUPTS();
    ଫେରନ୍ତୁ ulCPSR;
}

#define portSET_INTERRUPT_MASK_FROM_ISR()         portINLINE_SET_INTERRUPT_MASK_FROM_ISR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    କର { ଯଦି( x == 0 ) portENABLE_INTERRUPTS( ); } ଯେତେବେଳେ( 0 )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
ଶୂନ୍ୟ FreeRTOS_Tick_Handler( ଶୂନ୍ୟ );

/* Any task that uses the floating point unit MUST call vPortTaskUsesFPU()
 * before any floating point instructions are executed. */
ଶୂନ୍ୟ vPortTaskUsesFPU( ଶୂନ୍ୟ );
#define portTASK_USES_FLOATING_POINT()    vPortTaskUsesFPU()

#define portLOWEST_INTERRUPT_PRIORITY           ( ( ( uint32_t ) configUNIQUE_INTERRUPT_PRIORITIES ) - 1UL )
#define portLOWEST_USABLE_INTERRUPT_PRIORITY    ( portLOWEST_INTERRUPT_PRIORITY - 1UL )

/* Architecture specific optimisations. */
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#endif

#ଯଦି configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( ux_ଶୀର୍ଷ_Priority, uxReadyPriorities )    ux_ଶୀର୍ଷ_Priority = ( 31UL - ( uint32_t ) __CLZ( uxReadyPriorities ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#define portNOP()    __asm ଅସ୍ଥିର ( "NOP" )
#define portINLINE    ଧାଡ଼ିଭିତରେ

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
