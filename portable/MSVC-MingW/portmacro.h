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

#ifdef __cplusplus
ବାହ୍ୟ "C" {
#endif

/******************************************************************************
*   Defines
******************************************************************************/
/* Type definitions. */
#define portCHAR                 ଅକ୍ଷର
#define portFLOAT                ଦଶମିକ
#define portDOUBLE               ଦ୍ୱିଗୁଣ
#define portLONG                 long
#define portSHORT                short
#define port_ଗଦା_TYPE           size_t
#define portPOINTER_SIZE_TYPE    size_t

ପ୍ରକାରବ୍ୟାଖ୍ୟା port_ଗଦା_TYPE           ଗଦା_Type_t;

#ଯଦି defined( __x86_64__ ) || defined( _M_X64 )
    #define portBASE_TYPE    long long
    ପ୍ରକାରବ୍ୟାଖ୍ୟା long long            BaseType_t;
    ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned long long   UBaseType_t;
#ଅନ୍ୟଥା
    #define portBASE_TYPE    long
    ପ୍ରକାରବ୍ୟାଖ୍ୟା long                 BaseType_t;
    ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned long        UBaseType_t;
#endif


#ଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    ପ୍ରକାରବ୍ୟାଖ୍ୟା uint16_t             TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#ନଚେତଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    ପ୍ରକାରବ୍ୟାଖ୍ୟା uint32_t             TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32/64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#ନଚେତଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_64_BITS )
    ପ୍ରକାରବ୍ୟାଖ୍ୟା uint64_t             TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL

#ଯଦି defined( __x86_64__ ) || defined( _M_X64 )
/* 64-bit tick type on a 64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#endif
#ଅନ୍ୟଥା
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif

/* Hardware specifics. */
#define port_ଗଦା_GROWTH          ( -1 )
#define portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portINLINE                __inline

#ଯଦି defined( __x86_64__ ) || defined( _M_X64 )
    #define portBYTE_ALIGNMENT    8
#ଅନ୍ୟଥା
    #define portBYTE_ALIGNMENT    4
#endif

#define portYIELD()    vPortGenerateSimulatedInterrupt( portINTERRUPT_YIELD )


ବାହ୍ୟ ଅସ୍ଥିର BaseType_t xInsideInterrupt;
#define portSOFTWARE_BARRIER()    ଯେତେବେଳେ( xInsideInterrupt != pdFALSE )


/* Simulated interrupts return pdFALSE if no context switch should be performed,
 * or a non-zero number if a context switch should be performed. */
#define portYIELD_FROM_ISR( x )       ଫେରନ୍ତୁ x
#define portEND_SWITCHING_ISR( x )    portYIELD_FROM_ISR( ( x ) )

ଶୂନ୍ୟ vPortCloseRunningThread( ଶୂନ୍ୟ * pvTaskToDelete,
                              ଅସ୍ଥିର BaseType_t * pxPendYield );
ଶୂନ୍ୟ vPortDeleteThread( ଶୂନ୍ୟ * pvThreadToDelete );
#define portCLEAN_UP_TCB( pxTCB )                                  vPortDeleteThread( pxTCB )
#define portPRE_TASK_DELETE_HOOK( pvTaskToDelete, pxPendYield )    vPortCloseRunningThread( ( pvTaskToDelete ), ( pxPendYield ) )
#define portDISABLE_INTERRUPTS()                                   vPortEnterCritical()
#define portENABLE_INTERRUPTS()                                    vPortExitCritical()

/* Critical section handling. */
ଶୂନ୍ୟ vPortEnterCritical( ଶୂନ୍ୟ );
ଶୂନ୍ୟ vPortExitCritical( ଶୂନ୍ୟ );

#define portENTER_CRITICAL()    vPortEnterCritical()
#define portEXIT_CRITICAL()     vPortExitCritical()

#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#endif

/*-----------------------------------------------------------*/

#ଯଦି configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #ଯଦି ( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
    #endif

    /* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( ( ( UBaseType_t ) 1 ) << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( ( ( UBaseType_t ) 1 ) << ( uxPriority ) )

    #ifdef __GNUC__

        #define portGET_HIGHEST_PRIORITY( ux_ଶୀର୍ଷ_Priority, uxReadyPriorities )    \
        __asm ଅସ୍ଥିର ( "bsr %1, %0\n\t"                                       \
                         : "=r" ( ux_ଶୀର୍ଷ_Priority )                               \
                         : "rm" ( uxReadyPriorities )                           \
                         : "cc" )

    #ଅନ୍ୟଥା /* __GNUC__ */
        #ଅନ୍ତର୍ଭାଵ <intrin.h>

        /* BitScanReverse returns the bit position of the most significant '1'
         * in the word. */
        #ଯଦି defined( __x86_64__ ) || defined( _M_X64 )
            #pragma intrinsic(_BitScanReverse64)

            #define portGET_HIGHEST_PRIORITY( ux_ଶୀର୍ଷ_Priority, uxReadyPriorities )    \
            କର                                                                      \
            {                                                                       \
                unsigned long ul_ଶୀର୍ଷ_Priority;                                        \
                _BitScanReverse64( &ul_ଶୀର୍ଷ_Priority, ( uxReadyPriorities ) );         \
                ux_ଶୀର୍ଷ_Priority = ul_ଶୀର୍ଷ_Priority;                                      \
            } ଯେତେବେଳେ( 0 )

        #ଅନ୍ୟଥା /* #if defined( __x86_64__ ) || defined( _M_X64 ) */
            #pragma intrinsic(_BitScanReverse)

            #define portGET_HIGHEST_PRIORITY( ux_ଶୀର୍ଷ_Priority, uxReadyPriorities )    _BitScanReverse( ( unsigned long * ) &( ux_ଶୀର୍ଷ_Priority ), ( uxReadyPriorities ) )

        #endif /* #if defined( __x86_64__ ) || defined( _M_X64 ) */

    #endif /* __GNUC__ */

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ifndef __GNUC__
    __pragma( warning( disable:4211 ) ) /* Nonstandard extension used, as extern is only nonstandard to MSVC. */
#endif


/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )

#define portINTERRUPT_YIELD                        ( 0UL )
#define portINTERRUPT_TICK                         ( 1UL )
#define portINTERRUPT_APPLICATION_DEFINED_START    ( 2UL )

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively.
 */
ଶୂନ୍ୟ vPortGenerateSimulatedInterrupt( uint32_t ul_Interrupt_ସଂଖ୍ୟା );

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively. This function
 * can be called in a windows thread.
 */
ଶୂନ୍ୟ vPortGenerateSimulatedInterruptFromWindowsThread( uint32_t ul_Interrupt_ସଂଖ୍ୟା );

/*
 * Install an interrupt handler to be called by the simulated interrupt handler
 * thread.  The interrupt number must be above any used by the kernel itself
 * (at the time of writing the kernel was using interrupt numbers 0, 1, and 2
 * as defined above).  The number must also be lower than 32.
 *
 * Interrupt handler functions must return a non-zero value if executing the
 * handler resulted in a task switch being required.
 */
ଶୂନ୍ୟ vPortSetInterruptHandler( uint32_t ul_Interrupt_ସଂଖ୍ୟା,
                               uint32_t ( * pvHandler )( ଶୂନ୍ୟ ) );

#ifdef __cplusplus
}
#endif

#endif /* ifndef PORTMACRO_H */
