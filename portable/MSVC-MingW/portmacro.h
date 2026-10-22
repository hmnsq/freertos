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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

/******************************************************************************
*   Defines
******************************************************************************/
/* Type definitions. */
#تعریف_کړه پورټ_CHAR                 حرف
#تعریف_کړه پورټ_FLOAT                عائم
#تعریف_کړه پورټ_DOUBLE               مزدوج
#تعریف_کړه پورټ_LONG                 اوږد
#تعریف_کړه پورټ_SHORT                لنډ
#تعریف_کړه پورټ_ډېری_TYPE           size_t
#تعریف_کړه پورټ_اشاره_ګر_اندازه_TYPE    size_t

تعريفنوع پورټ_ډېری_TYPE           ډېری_Type_t;

#إذا defined( __x86_64__ ) || defined( _M_X64 )
    #تعریف_کړه پورټ_بنسټ_TYPE    اوږد اوږد
    تعريفنوع اوږد اوږد            بنسټ_Type_t;
    تعريفنوع بینښه اوږد اوږد   UBaseType_t;
#وإلا
    #تعریف_کړه پورټ_بنسټ_TYPE    اوږد
    تعريفنوع اوږد                 بنسټ_Type_t;
    تعريفنوع بینښه اوږد        UBaseType_t;
#د_که_پای


#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t             TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t             TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32/64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_64_بټونه )
    تعريفنوع uint64_t             TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL

#إذا defined( __x86_64__ ) || defined( _M_X64 )
/* 64-bit tick type on a 64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
#د_که_پای
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای

/* Hardware specifics. */
#تعریف_کړه پورټ_ډېری_GROWTH          ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_INLINE                __inline

#إذا defined( __x86_64__ ) || defined( _M_X64 )
    #تعریف_کړه پورټ_BYTE_ALIGNMENT    8
#وإلا
    #تعریف_کړه پورټ_BYTE_ALIGNMENT    4
#د_که_پای

#تعریف_کړه پورټ_YIELD()    v_پورټ_Generate_Simulated_مداخله( پورټ_مداخله_YIELD )


خارجي متطاير بنسټ_Type_t x_Inside_مداخله;
#تعریف_کړه پورټ_SOFTWARE_BARRIER()    طالما( x_Inside_مداخله != pdFALSE )


/* Simulated interrupts return pdFALSE if no context switch should be performed,
 * or a non-zero number if a context switch should be performed. */
#تعریف_کړه پورټ_YIELD_FROM_ISR( x )       أرجع x
#تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( x )    پورټ_YIELD_FROM_ISR( ( x ) )

فراغ v_پورټ_Close_Running_Thread( فراغ * pv_Task_منزل_Delete,
                              متطاير بنسټ_Type_t * pxPendYield );
فراغ v_پورټ_Delete_Thread( فراغ * pv_Thread_منزل_Delete );
#تعریف_کړه پورټ_CLEAN_پورته_TCB( pxTCB )                                  v_پورټ_Delete_Thread( pxTCB )
#تعریف_کړه پورټ_PRE_TASK_DELETE_HOOK( pv_Task_منزل_Delete, pxPendYield )    v_پورټ_Close_Running_Thread( ( pv_Task_منزل_Delete ), ( pxPendYield ) )
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()                                   v_پورټ_Enter_Critical()
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()                                    v_پورټ_Exit_Critical()

/* Critical section handling. */
فراغ v_پورټ_Enter_Critical( فراغ );
فراغ v_پورټ_Exit_Critical( فراغ );

#تعریف_کړه پورټ_ENTER_CRITICAL()    v_پورټ_Enter_Critical()
#تعریف_کړه پورټ_EXIT_CRITICAL()     v_پورټ_Exit_Critical()

#که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION
    #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    1
#د_که_پای

/*-----------------------------------------------------------*/

#إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #تېروتنه config_USE_پورټ_OPTIMISED_TASK_SELECTION can only be سېټ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires نور than 10 منزل 15 difference priorities as tasks that share a لومړیتوب will time ټوټه.
    #د_که_پای

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )    ( uxReadyPriorities ) |= ( ( ( UBaseType_t ) 1 ) << ( ux_لومړیتوب ) )
    #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( ( ( UBaseType_t ) 1 ) << ( ux_لومړیتوب ) )

    #که_تعریف_شوی __GNUC__

        #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )    \
        __asm متطاير ( "bsr %1, %0\n\t"                                       \
                         : "=r" ( ux_سر_لومړیتوب )                               \
                         : "rm" ( uxReadyPriorities )                           \
                         : "cc" )

    #وإلا /* __GNUC__ */
        #ضمن <intrin.h>

        /* BitScanReverse returns the bit position of the most significant '1'
         * in the word. */
        #إذا defined( __x86_64__ ) || defined( _M_X64 )
            #لارښوونه intrinsic(بټ_لټون_Reverse64)

            #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )    \
            افعل                                                                      \
            {                                                                       \
                بینښه اوږد ul_سر_لومړیتوب;                                        \
                بټ_لټون_Reverse64( &ul_سر_لومړیتوب, ( uxReadyPriorities ) );         \
                ux_سر_لومړیتوب = ul_سر_لومړیتوب;                                      \
            } طالما( 0 )

        #وإلا /* #if defined( __x86_64__ ) || defined( _M_X64 ) */
            #لارښوونه intrinsic(بټ_لټون_سرچپه)

            #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )    بټ_لټون_سرچپه( ( بینښه اوږد * ) &( ux_سر_لومړیتوب ), ( uxReadyPriorities ) )

        #د_که_پای /* #if defined( __x86_64__ ) || defined( _M_X64 ) */

    #د_که_پای /* __GNUC__ */

#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#که_نه_تعریف_شوی __GNUC__
    __pragma( warning( disable:4211 ) ) /* Nonstandard extension used, as extern is only nonstandard to MSVC. */
#د_که_پای


/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کړه پورټ_مداخله_YIELD                        ( 0UL )
#تعریف_کړه پورټ_مداخله_TICK                         ( 1UL )
#تعریف_کړه پورټ_مداخله_APPLICATION_DEFINED_پیل    ( 2UL )

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively.
 */
فراغ v_پورټ_Generate_Simulated_مداخله( uint32_t ul_مداخله_شمېره );

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively. This function
 * can be called in a windows thread.
 */
فراغ v_پورټ_Generate_Simulated_مداخله_From_Windows_Thread( uint32_t ul_مداخله_شمېره );

/*
 * Install an interrupt handler to be called by the simulated interrupt handler
 * thread.  The interrupt number must be above any used by the kernel itself
 * (at the time of writing the kernel was using interrupt numbers 0, 1, and 2
 * as defined above).  The number must also be lower than 32.
 *
 * Interrupt handler functions must return a non-zero value if executing the
 * handler resulted in a task switch being required.
 */
فراغ v_پورټ_سېټ_مداخله_Handler( uint32_t ul_مداخله_شمېره,
                               uint32_t ( * pvHandler )( فراغ ) );

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای /* ifndef PORTMACRO_H */
