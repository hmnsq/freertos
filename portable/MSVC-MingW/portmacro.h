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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

/******************************************************************************
*   Defines
******************************************************************************/
/* Type definitions. */
#وصف_ڪريو پورٽ_CHAR                 حرف
#وصف_ڪريو پورٽ_FLOAT                عائم
#وصف_ڪريو پورٽ_DOUBLE               مزدوج
#وصف_ڪريو پورٽ_LONG                 ڊگهو
#وصف_ڪريو پورٽ_SHORT                ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE           size_t
#وصف_ڪريو پورٽ_اشارو_سائيز_TYPE    size_t

تعريفنوع پورٽ_ڍير_TYPE           ڍير_Type_t;

#إذا defined( __x86_64__ ) || defined( _M_X64 )
    #وصف_ڪريو پورٽ_بنياد_TYPE    ڊگهو ڊگهو
    تعريفنوع ڊگهو ڊگهو            بنياد_Type_t;
    تعريفنوع بنانشان ڊگهو ڊگهو   UBaseType_t;
#وإلا
    #وصف_ڪريو پورٽ_بنياد_TYPE    ڊگهو
    تعريفنوع ڊگهو                 بنياد_Type_t;
    تعريفنوع بنانشان ڊگهو        UBaseType_t;
#جيڪڏهن_پورو


#إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t             TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t             TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32/64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_64_بٽ )
    تعريفنوع uint64_t             TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL

#إذا defined( __x86_64__ ) || defined( _M_X64 )
/* 64-bit tick type on a 64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1
#جيڪڏهن_پورو
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو

/* Hardware specifics. */
#وصف_ڪريو پورٽ_ڍير_GROWTH          ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_INLINE                __inline

#إذا defined( __x86_64__ ) || defined( _M_X64 )
    #وصف_ڪريو پورٽ_BYTE_ALIGNMENT    8
#وإلا
    #وصف_ڪريو پورٽ_BYTE_ALIGNMENT    4
#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_YIELD()    v_پورٽ_Generate_Simulated_مداخلت( پورٽ_مداخلت_YIELD )


خارجي متطاير بنياد_Type_t x_Inside_مداخلت;
#وصف_ڪريو پورٽ_SOFTWARE_BARRIER()    طالما( x_Inside_مداخلت != pdFALSE )


/* Simulated interrupts return pdFALSE if no context switch should be performed,
 * or a non-zero number if a context switch should be performed. */
#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )       أرجع x
#وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( x )    پورٽ_YIELD_FROM_ISR( ( x ) )

فراغ v_پورٽ_Close_Running_Thread( فراغ * pv_Task_منزل_Delete,
                              متطاير بنياد_Type_t * pxPendYield );
فراغ v_پورٽ_Delete_Thread( فراغ * pv_Thread_منزل_Delete );
#وصف_ڪريو پورٽ_CLEAN_مٿي_TCB( pxTCB )                                  v_پورٽ_Delete_Thread( pxTCB )
#وصف_ڪريو پورٽ_PRE_TASK_DELETE_HOOK( pv_Task_منزل_Delete, pxPendYield )    v_پورٽ_Close_Running_Thread( ( pv_Task_منزل_Delete ), ( pxPendYield ) )
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                                   v_پورٽ_Enter_Critical()
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                                    v_پورٽ_Exit_Critical()

/* Critical section handling. */
فراغ v_پورٽ_Enter_Critical( فراغ );
فراغ v_پورٽ_Exit_Critical( فراغ );

#وصف_ڪريو پورٽ_ENTER_CRITICAL()    v_پورٽ_Enter_Critical()
#وصف_ڪريو پورٽ_EXIT_CRITICAL()     v_پورٽ_Exit_Critical()

#جيڪڏهن_وصف_نه_ٿيل config_USE_پورٽ_OPTIMISED_TASK_SELECTION
    #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    1
#جيڪڏهن_پورو

/*-----------------------------------------------------------*/

#إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطي config_USE_پورٽ_OPTIMISED_TASK_SELECTION can only be سيٽ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires وڌيڪ than 10 منزل 15 difference priorities as tasks that share a ترجيح will time ٽڪرو.
    #جيڪڏهن_پورو

    /* Store/clear the ready priorities in a bit map. */
    #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( ( ( UBaseType_t ) 1 ) << ( ux_ترجيح ) )
    #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( ( ( UBaseType_t ) 1 ) << ( ux_ترجيح ) )

    #جيڪڏهن_وصف_ٿيل __GNUC__

        #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities )    \
        __asm متطاير ( "bsr %1, %0\n\t"                                       \
                         : "=r" ( ux_چوٽي_ترجيح )                               \
                         : "rm" ( uxReadyPriorities )                           \
                         : "cc" )

    #وإلا /* __GNUC__ */
        #ضمن <intrin.h>

        /* BitScanReverse returns the bit position of the most significant '1'
         * in the word. */
        #إذا defined( __x86_64__ ) || defined( _M_X64 )
            #هدايت intrinsic(ٻٽو_انگ_جاچ_Reverse64)

            #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities )    \
            افعل                                                                      \
            {                                                                       \
                بنانشان ڊگهو ul_چوٽي_ترجيح;                                        \
                ٻٽو_انگ_جاچ_Reverse64( &ul_چوٽي_ترجيح, ( uxReadyPriorities ) );         \
                ux_چوٽي_ترجيح = ul_چوٽي_ترجيح;                                      \
            } طالما( 0 )

        #وإلا /* #if defined( __x86_64__ ) || defined( _M_X64 ) */
            #هدايت intrinsic(ٻٽو_انگ_جاچ_ابتو)

            #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities )    ٻٽو_انگ_جاچ_ابتو( ( بنانشان ڊگهو * ) &( ux_چوٽي_ترجيح ), ( uxReadyPriorities ) )

        #جيڪڏهن_پورو /* #if defined( __x86_64__ ) || defined( _M_X64 ) */

    #جيڪڏهن_پورو /* __GNUC__ */

#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#جيڪڏهن_وصف_نه_ٿيل __GNUC__
    __pragma( warning( disable:4211 ) ) /* Nonstandard extension used, as extern is only nonstandard to MSVC. */
#جيڪڏهن_پورو


/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#وصف_ڪريو پورٽ_مداخلت_YIELD                        ( 0UL )
#وصف_ڪريو پورٽ_مداخلت_TICK                         ( 1UL )
#وصف_ڪريو پورٽ_مداخلت_APPLICATION_DEFINED_شروعات    ( 2UL )

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively.
 */
فراغ v_پورٽ_Generate_Simulated_مداخلت( uint32_t ul_مداخلت_عدد );

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively. This function
 * can be called in a windows thread.
 */
فراغ v_پورٽ_Generate_Simulated_مداخلت_From_Windows_Thread( uint32_t ul_مداخلت_عدد );

/*
 * Install an interrupt handler to be called by the simulated interrupt handler
 * thread.  The interrupt number must be above any used by the kernel itself
 * (at the time of writing the kernel was using interrupt numbers 0, 1, and 2
 * as defined above).  The number must also be lower than 32.
 *
 * Interrupt handler functions must return a non-zero value if executing the
 * handler resulted in a task switch being required.
 */
فراغ v_پورٽ_سيٽ_مداخلت_Handler( uint32_t ul_مداخلت_عدد,
                               uint32_t ( * pvHandler )( فراغ ) );

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو /* ifndef PORTMACRO_H */
