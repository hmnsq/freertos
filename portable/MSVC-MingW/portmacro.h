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
বাহ্য "C" {
#endif

/******************************************************************************
*   Defines
******************************************************************************/
/* Type definitions. */
#define portCHAR                 ৱর্ণ
#define portFLOAT                ভিন্ন
#define portDOUBLE               দ্ৱিগুণ
#define portLONG                 long
#define portSHORT                short
#define port_স্তূপ_TYPE           size_t
#define portPOINTER_SIZE_TYPE    size_t

প্রকারনির্দেশ port_স্তূপ_TYPE           স্তূপ_Type_t;

#যদি defined( __x86_64__ ) || defined( _M_X64 )
    #define portBASE_TYPE    long long
    প্রকারনির্দেশ long long            BaseType_t;
    প্রকারনির্দেশ unsigned long long   UBaseType_t;
#অন্যথা
    #define portBASE_TYPE    long
    প্রকারনির্দেশ long                 BaseType_t;
    প্রকারনির্দেশ unsigned long        UBaseType_t;
#endif


#যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    প্রকারনির্দেশ uint16_t             TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#নোচেদ্যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    প্রকারনির্দেশ uint32_t             TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32/64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#নোচেদ্যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_64_BITS )
    প্রকারনির্দেশ uint64_t             TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL

#যদি defined( __x86_64__ ) || defined( _M_X64 )
/* 64-bit tick type on a 64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#endif
#অন্যথা
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif

/* Hardware specifics. */
#define port_স্তূপ_GROWTH          ( -1 )
#define portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portINLINE                __inline

#যদি defined( __x86_64__ ) || defined( _M_X64 )
    #define portBYTE_ALIGNMENT    8
#অন্যথা
    #define portBYTE_ALIGNMENT    4
#endif

#define portYIELD()    vPortGenerateSimulatedInterrupt( portINTERRUPT_YIELD )


বাহ্য চঞ্চল BaseType_t xInsideInterrupt;
#define portSOFTWARE_BARRIER()    যেতিয়ালৈ( xInsideInterrupt != pdFALSE )


/* Simulated interrupts return pdFALSE if no context switch should be performed,
 * or a non-zero number if a context switch should be performed. */
#define portYIELD_FROM_ISR( x )       ঘূৰাই x
#define portEND_SWITCHING_ISR( x )    portYIELD_FROM_ISR( ( x ) )

শূন্য vPortCloseRunningThread( শূন্য * pvTaskToDelete,
                              চঞ্চল BaseType_t * pxPendYield );
শূন্য vPortDeleteThread( শূন্য * pvThreadToDelete );
#define portCLEAN_UP_TCB( pxTCB )                                  vPortDeleteThread( pxTCB )
#define portPRE_TASK_DELETE_HOOK( pvTaskToDelete, pxPendYield )    vPortCloseRunningThread( ( pvTaskToDelete ), ( pxPendYield ) )
#define portDISABLE_INTERRUPTS()                                   vPortEnterCritical()
#define portENABLE_INTERRUPTS()                                    vPortExitCritical()

/* Critical section handling. */
শূন্য vPortEnterCritical( শূন্য );
শূন্য vPortExitCritical( শূন্য );

#define portENTER_CRITICAL()    vPortEnterCritical()
#define portEXIT_CRITICAL()     vPortExitCritical()

#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#endif

/*-----------------------------------------------------------*/

#যদি configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #যদি ( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
    #endif

    /* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( ( ( UBaseType_t ) 1 ) << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( ( ( UBaseType_t ) 1 ) << ( uxPriority ) )

    #ifdef __GNUC__

        #define portGET_HIGHEST_PRIORITY( ux_শীৰ্ষ_Priority, uxReadyPriorities )    \
        __asm চঞ্চল ( "bsr %1, %0\n\t"                                       \
                         : "=r" ( ux_শীৰ্ষ_Priority )                               \
                         : "rm" ( uxReadyPriorities )                           \
                         : "cc" )

    #অন্যথা /* __GNUC__ */
        #অন্তর্ভাৱ <intrin.h>

        /* BitScanReverse returns the bit position of the most significant '1'
         * in the word. */
        #যদি defined( __x86_64__ ) || defined( _M_X64 )
            #pragma intrinsic(_BitScanReverse64)

            #define portGET_HIGHEST_PRIORITY( ux_শীৰ্ষ_Priority, uxReadyPriorities )    \
            কৰা                                                                      \
            {                                                                       \
                unsigned long ul_শীৰ্ষ_Priority;                                        \
                _BitScanReverse64( &ul_শীৰ্ষ_Priority, ( uxReadyPriorities ) );         \
                ux_শীৰ্ষ_Priority = ul_শীৰ্ষ_Priority;                                      \
            } যেতিয়ালৈ( 0 )

        #অন্যথা /* #if defined( __x86_64__ ) || defined( _M_X64 ) */
            #pragma intrinsic(_BitScanReverse)

            #define portGET_HIGHEST_PRIORITY( ux_শীৰ্ষ_Priority, uxReadyPriorities )    _BitScanReverse( ( unsigned long * ) &( ux_শীৰ্ষ_Priority ), ( uxReadyPriorities ) )

        #endif /* #if defined( __x86_64__ ) || defined( _M_X64 ) */

    #endif /* __GNUC__ */

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ifndef __GNUC__
    __pragma( warning( disable:4211 ) ) /* Nonstandard extension used, as extern is only nonstandard to MSVC. */
#endif


/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    শূন্য vFunction( শূন্য * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          শূন্য vFunction( শূন্য * pvParameters )

#define portINTERRUPT_YIELD                        ( 0UL )
#define portINTERRUPT_TICK                         ( 1UL )
#define portINTERRUPT_APPLICATION_DEFINED_START    ( 2UL )

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively.
 */
শূন্য vPortGenerateSimulatedInterrupt( uint32_t ul_Interrupt_সংখ্যা );

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively. This function
 * can be called in a windows thread.
 */
শূন্য vPortGenerateSimulatedInterruptFromWindowsThread( uint32_t ul_Interrupt_সংখ্যা );

/*
 * Install an interrupt handler to be called by the simulated interrupt handler
 * thread.  The interrupt number must be above any used by the kernel itself
 * (at the time of writing the kernel was using interrupt numbers 0, 1, and 2
 * as defined above).  The number must also be lower than 32.
 *
 * Interrupt handler functions must return a non-zero value if executing the
 * handler resulted in a task switch being required.
 */
শূন্য vPortSetInterruptHandler( uint32_t ul_Interrupt_সংখ্যা,
                               uint32_t ( * pvHandler )( শূন্য ) );

#ifdef __cplusplus
}
#endif

#endif /* ifndef PORTMACRO_H */
