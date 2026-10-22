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

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

/******************************************************************************
*   Defines
******************************************************************************/
/* Type definitions. */
#घोषणा portCHAR                 अक्षर
#घोषणा portFLOAT                भग्न
#घोषणा portDOUBLE               द्विगुन
#घोषणा portLONG                 दीर्घ
#घोषणा portSHORT                लघु
#घोषणा port_ढेर_TYPE           माप_प्रकार
#घोषणा port_POINTER_आकार_TYPE    माप_प्रकार

प्रकार port_ढेर_TYPE           ढेर_Type_t;

#अगर defined( __x86_64__ ) || defined( _M_X64 )
    #घोषणा portBASE_TYPE    दीर्घ दीर्घ
    प्रकार दीर्घ दीर्घ            BaseType_t;
    प्रकार अचिन्हित दीर्घ दीर्घ   UBaseType_t;
#अन्यथा
    #घोषणा portBASE_TYPE    दीर्घ
    प्रकार दीर्घ                 BaseType_t;
    प्रकार अचिन्हित दीर्घ        UBaseType_t;
#पूर्ण_अगर


#अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t             TickType_t;
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t             TickType_t;
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32/64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #घोषणा portTICK_TYPE_IS_ATOMIC    1
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_64_BITS )
    प्रकार uint64_t             TickType_t;
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL

#अगर defined( __x86_64__ ) || defined( _M_X64 )
/* 64-bit tick type on a 64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #घोषणा portTICK_TYPE_IS_ATOMIC    1
#पूर्ण_अगर
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर

/* Hardware specifics. */
#घोषणा port_ढेर_GROWTH          ( -1 )
#घोषणा portTICK_PERIOD_MS        ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portINLINE                __inline

#अगर defined( __x86_64__ ) || defined( _M_X64 )
    #घोषणा portBYTE_ALIGNMENT    8
#अन्यथा
    #घोषणा portBYTE_ALIGNMENT    4
#पूर्ण_अगर

#घोषणा portYIELD()    vPortGenerateSimulatedInterrupt( portINTERRUPT_YIELD )


बाह्य अस्थिर BaseType_t xInsideInterrupt;
#घोषणा portSOFTWARE_BARRIER()    जबतक( xInsideInterrupt != pdFALSE )


/* Simulated interrupts return pdFALSE if no context switch should be performed,
 * or a non-zero number if a context switch should be performed. */
#घोषणा portYIELD_FROM_ISR( x )       वापस x
#घोषणा portEND_SWITCHING_ISR( x )    portYIELD_FROM_ISR( ( x ) )

व्योम vPortCloseRunningThread( व्योम * pvTaskToDelete,
                              अस्थिर BaseType_t * pxPendYield );
व्योम vPortDeleteThread( व्योम * pvThreadToDelete );
#घोषणा portCLEAN_UP_TCB( pxTCB )                                  vPortDeleteThread( pxTCB )
#घोषणा portPRE_TASK_DELETE_HOOK( pvTaskToDelete, pxPendYield )    vPortCloseRunningThread( ( pvTaskToDelete ), ( pxPendYield ) )
#घोषणा portDISABLE_INTERRUPTS()                                   vPortEnterCritical()
#घोषणा portENABLE_INTERRUPTS()                                    vPortExitCritical()

/* Critical section handling. */
व्योम vPortEnterCritical( व्योम );
व्योम vPortExitCritical( व्योम );

#घोषणा portENTER_CRITICAL()    vPortEnterCritical()
#घोषणा portEXIT_CRITICAL()     vPortExitCritical()

#अगर_अघोषित configUSE_PORT_OPTIMISED_TASK_SELECTION
    #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#पूर्ण_अगर

/*-----------------------------------------------------------*/

#अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #अगर ( configMAX_PRIORITIES > 32 )
        #त्रुटि configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 difference priorities as tasks that share a priority will समय slice.
    #पूर्ण_अगर

    /* Store/clear the ready priorities in a bit map. */
    #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( ( ( UBaseType_t ) 1 ) << ( uxPriority ) )
    #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( ( ( UBaseType_t ) 1 ) << ( uxPriority ) )

    #अगर_घोषित __GNUC__

        #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    \
        __asm अस्थिर ( "bsr %1, %0\n\t"                                       \
                         : "=r" ( ux_शीर्ष_Priority )                               \
                         : "rm" ( uxReadyPriorities )                           \
                         : "cc" )

    #अन्यथा /* __GNUC__ */
        #समावेश <intrin.h>

        /* BitScanReverse returns the bit position of the most significant '1'
         * in the word. */
        #अगर defined( __x86_64__ ) || defined( _M_X64 )
            #आशय intrinsic(_BitScanReverse64)

            #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    \
            करो                                                                      \
            {                                                                       \
                अचिन्हित दीर्घ ul_शीर्ष_Priority;                                        \
                _BitScanReverse64( &ul_शीर्ष_Priority, ( uxReadyPriorities ) );         \
                ux_शीर्ष_Priority = ul_शीर्ष_Priority;                                      \
            } जबतक( 0 )

        #अन्यथा /* #if defined( __x86_64__ ) || defined( _M_X64 ) */
            #आशय intrinsic(_BitScanReverse)

            #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    _BitScanReverse( ( अचिन्हित दीर्घ * ) &( ux_शीर्ष_Priority ), ( uxReadyPriorities ) )

        #पूर्ण_अगर /* #if defined( __x86_64__ ) || defined( _M_X64 ) */

    #पूर्ण_अगर /* __GNUC__ */

#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#अगर_अघोषित __GNUC__
    __pragma( warning( disable:4211 ) ) /* Nonstandard extension used, as extern is only nonstandard to MSVC. */
#पूर्ण_अगर


/* Task function macros as described on the FreeRTOS.org WEB site. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

#घोषणा portINTERRUPT_YIELD                        ( 0UL )
#घोषणा portINTERRUPT_TICK                         ( 1UL )
#घोषणा portINTERRUPT_APPLICATION_DEFINED_START    ( 2UL )

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively.
 */
व्योम vPortGenerateSimulatedInterrupt( uint32_t ul_Interrupt_संख्या );

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively. This function
 * can be called in a windows thread.
 */
व्योम vPortGenerateSimulatedInterruptFromWindowsThread( uint32_t ul_Interrupt_संख्या );

/*
 * Install an interrupt handler to be called by the simulated interrupt handler
 * thread.  The interrupt number must be above any used by the kernel itself
 * (at the time of writing the kernel was using interrupt numbers 0, 1, and 2
 * as defined above).  The number must also be lower than 32.
 *
 * Interrupt handler functions must return a non-zero value if executing the
 * handler resulted in a task switch being required.
 */
व्योम vPortSetInterruptHandler( uint32_t ul_Interrupt_संख्या,
                               uint32_t ( * pvHandler )( व्योम ) );

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर /* ifndef PORTMACRO_H */
