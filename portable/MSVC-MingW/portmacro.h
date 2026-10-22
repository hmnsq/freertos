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

#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

/******************************************************************************
*   Defines
******************************************************************************/
/* Type definitions. */
#تعریف_کرو پورٹ_CHAR                 حرف
#تعریف_کرو پورٹ_FLOAT                عائم
#تعریف_کرو پورٹ_DOUBLE               مزدوج
#تعریف_کرو پورٹ_LONG                 لما
#تعریف_کرو پورٹ_SHORT                چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE           size_t
#تعریف_کرو پورٹ_اشارہ_گر_ناپ_TYPE    size_t

تعريفنوع پورٹ_ڈھیر_TYPE           ڈھیر_Type_t;

#إذا defined( __x86_64__ ) || defined( _M_X64 )
    #تعریف_کرو پورٹ_ادھار_TYPE    لما لما
    تعريفنوع لما لما            ادھار_Type_t;
    تعريفنوع بنانشانی لما لما   UBaseType_t;
#وإلا
    #تعریف_کرو پورٹ_ادھار_TYPE    لما
    تعريفنوع لما                 ادھار_Type_t;
    تعريفنوع بنانشانی لما        UBaseType_t;
#جے_انت


#إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t             TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t             TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32/64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_64_بٹ )
    تعريفنوع uint64_t             TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL

#إذا defined( __x86_64__ ) || defined( _M_X64 )
/* 64-bit tick type on a 64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#جے_انت
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت

/* Hardware specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH          ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_INLINE                __inline

#إذا defined( __x86_64__ ) || defined( _M_X64 )
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    8
#وإلا
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    4
#جے_انت

#تعریف_کرو پورٹ_YIELD()    v_پورٹ_Generate_Simulated_رکاوٹ( پورٹ_رکاوٹ_YIELD )


خارجي متطاير ادھار_Type_t x_Inside_رکاوٹ;
#تعریف_کرو پورٹ_SOFTWARE_BARRIER()    طالما( x_Inside_رکاوٹ != pdFALSE )


/* Simulated interrupts return pdFALSE if no context switch should be performed,
 * or a non-zero number if a context switch should be performed. */
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )       أرجع x
#تعریف_کرو پورٹ_سرا_SWITCHING_ISR( x )    پورٹ_YIELD_FROM_ISR( ( x ) )

فراغ v_پورٹ_Close_Running_Thread( فراغ * pv_Task_منزل_Delete,
                              متطاير ادھار_Type_t * pxPendYield );
فراغ v_پورٹ_Delete_Thread( فراغ * pv_Thread_منزل_Delete );
#تعریف_کرو پورٹ_CLEAN_اتے_TCB( pxTCB )                                  v_پورٹ_Delete_Thread( pxTCB )
#تعریف_کرو پورٹ_PRE_TASK_DELETE_HOOK( pv_Task_منزل_Delete, pxPendYield )    v_پورٹ_Close_Running_Thread( ( pv_Task_منزل_Delete ), ( pxPendYield ) )
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                                   v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                                    v_پورٹ_Exit_Critical()

/* Critical section handling. */
فراغ v_پورٹ_Enter_Critical( فراغ );
فراغ v_پورٹ_Exit_Critical( فراغ );

#تعریف_کرو پورٹ_ENTER_CRITICAL()    v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()     v_پورٹ_Exit_Critical()

#جے_بنا_تعریف config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
#جے_انت

/*-----------------------------------------------------------*/

#إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires ہور than 10 منزل 15 difference priorities as tasks that share a ترجیح will time ٹکڑا.
    #جے_انت

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( ( ( UBaseType_t ) 1 ) << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( ( ( UBaseType_t ) 1 ) << ( ux_ترجیح ) )

    #جے_تعریف_شدہ __GNUC__

        #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    \
        __asm متطاير ( "bsr %1, %0\n\t"                                       \
                         : "=r" ( ux_چوٹی_ترجیح )                               \
                         : "rm" ( uxReadyPriorities )                           \
                         : "cc" )

    #وإلا /* __GNUC__ */
        #ضمن <intrin.h>

        /* BitScanReverse returns the bit position of the most significant '1'
         * in the word. */
        #إذا defined( __x86_64__ ) || defined( _M_X64 )
            #ہدایت intrinsic(ثنائی_ہندسہ_جانچ_Reverse64)

            #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    \
            افعل                                                                      \
            {                                                                       \
                بنانشانی لما ul_چوٹی_ترجیح;                                        \
                ثنائی_ہندسہ_جانچ_Reverse64( &ul_چوٹی_ترجیح, ( uxReadyPriorities ) );         \
                ux_چوٹی_ترجیح = ul_چوٹی_ترجیح;                                      \
            } طالما( 0 )

        #وإلا /* #if defined( __x86_64__ ) || defined( _M_X64 ) */
            #ہدایت intrinsic(ثنائی_ہندسہ_جانچ_الٹ)

            #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ثنائی_ہندسہ_جانچ_الٹ( ( بنانشانی لما * ) &( ux_چوٹی_ترجیح ), ( uxReadyPriorities ) )

        #جے_انت /* #if defined( __x86_64__ ) || defined( _M_X64 ) */

    #جے_انت /* __GNUC__ */

#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#جے_بنا_تعریف __GNUC__
    __pragma( warning( disable:4211 ) ) /* Nonstandard extension used, as extern is only nonstandard to MSVC. */
#جے_انت


/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کرو پورٹ_رکاوٹ_YIELD                        ( 0UL )
#تعریف_کرو پورٹ_رکاوٹ_TICK                         ( 1UL )
#تعریف_کرو پورٹ_رکاوٹ_APPLICATION_DEFINED_شروع    ( 2UL )

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively.
 */
فراغ v_پورٹ_Generate_Simulated_رکاوٹ( uint32_t ul_رکاوٹ_نمبر );

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively. This function
 * can be called in a windows thread.
 */
فراغ v_پورٹ_Generate_Simulated_رکاوٹ_From_Windows_Thread( uint32_t ul_رکاوٹ_نمبر );

/*
 * Install an interrupt handler to be called by the simulated interrupt handler
 * thread.  The interrupt number must be above any used by the kernel itself
 * (at the time of writing the kernel was using interrupt numbers 0, 1, and 2
 * as defined above).  The number must also be lower than 32.
 *
 * Interrupt handler functions must return a non-zero value if executing the
 * handler resulted in a task switch being required.
 */
فراغ v_پورٹ_سیٹ_رکاوٹ_Handler( uint32_t ul_رکاوٹ_نمبر,
                               uint32_t ( * pvHandler )( فراغ ) );

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت /* ifndef PORTMACRO_H */
