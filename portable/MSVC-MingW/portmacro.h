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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

/******************************************************************************
*   Defines
******************************************************************************/
/* Type definitions. */
#تعریف_کن پورت_CHAR                 حرف
#تعریف_کن پورت_FLOAT                عائم
#تعریف_کن پورت_DOUBLE               مزدوج
#تعریف_کن پورت_LONG                 دراز
#تعریف_کن پورت_SHORT                کوتاه
#تعریف_کن پورت_پشته_TYPE           size_t
#تعریف_کن پورت_اشاره_گر_اندازه_TYPE    size_t

تعريفنوع پورت_پشته_TYPE           پشته_Type_t;

#إذا defined( __x86_64__ ) || defined( _M_X64 )
    #تعریف_کن پورت_پایه_TYPE    دراز دراز
    تعريفنوع دراز دراز            پایه_Type_t;
    تعريفنوع بیعلامت دراز دراز   UBaseType_t;
#وإلا
    #تعریف_کن پورت_پایه_TYPE    دراز
    تعريفنوع دراز                 پایه_Type_t;
    تعريفنوع بیعلامت دراز        UBaseType_t;
#پایان_اگر


#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t             TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t             TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32/64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_64_بیتها )
    تعريفنوع uint64_t             TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL

#إذا defined( __x86_64__ ) || defined( _M_X64 )
/* 64-bit tick type on a 64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
#پایان_اگر
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر

/* Hardware specifics. */
#تعریف_کن پورت_پشته_GROWTH          ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_INLINE                __inline

#إذا defined( __x86_64__ ) || defined( _M_X64 )
    #تعریف_کن پورت_BYTE_ALIGNMENT    8
#وإلا
    #تعریف_کن پورت_BYTE_ALIGNMENT    4
#پایان_اگر

#تعریف_کن پورت_YIELD()    v_پورت_Generate_Simulated_وقفه( پورت_وقفه_YIELD )


خارجي متطاير پایه_Type_t x_Inside_وقفه;
#تعریف_کن پورت_SOFTWARE_BARRIER()    طالما( x_Inside_وقفه != pdFALSE )


/* Simulated interrupts return pdFALSE if no context switch should be performed,
 * or a non-zero number if a context switch should be performed. */
#تعریف_کن پورت_YIELD_FROM_ISR( x )       أرجع x
#تعریف_کن پورت_انتها_SWITCHING_ISR( x )    پورت_YIELD_FROM_ISR( ( x ) )

فراغ v_پورت_Close_Running_Thread( فراغ * pv_Task_مقصد_Delete,
                              متطاير پایه_Type_t * pxPendYield );
فراغ v_پورت_Delete_Thread( فراغ * pv_Thread_مقصد_Delete );
#تعریف_کن پورت_CLEAN_به_بالا_TCB( pxTCB )                                  v_پورت_Delete_Thread( pxTCB )
#تعریف_کن پورت_PRE_TASK_DELETE_HOOK( pv_Task_مقصد_Delete, pxPendYield )    v_پورت_Close_Running_Thread( ( pv_Task_مقصد_Delete ), ( pxPendYield ) )
#تعریف_کن پورت_DISABLE_INTERRUPTS()                                   v_پورت_Enter_Critical()
#تعریف_کن پورت_ENABLE_INTERRUPTS()                                    v_پورت_Exit_Critical()

/* Critical section handling. */
فراغ v_پورت_Enter_Critical( فراغ );
فراغ v_پورت_Exit_Critical( فراغ );

#تعریف_کن پورت_ENTER_CRITICAL()    v_پورت_Enter_Critical()
#تعریف_کن پورت_EXIT_CRITICAL()     v_پورت_Exit_Critical()

#اگر_تعریف_نشده config_USE_پورت_OPTIMISED_TASK_SELECTION
    #تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION    1
#پایان_اگر

/*-----------------------------------------------------------*/

#إذا config_USE_پورت_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #خطا config_USE_پورت_OPTIMISED_TASK_SELECTION can only be مجموعه مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires بیشتر than 10 مقصد 15 difference priorities as tasks that share a اولویت will time برش.
    #پایان_اگر

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities )    ( uxReadyPriorities ) |= ( ( ( UBaseType_t ) 1 ) << ( ux_اولویت ) )
    #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( ( ( UBaseType_t ) 1 ) << ( ux_اولویت ) )

    #اگر_تعریف_شده __GNUC__

        #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    \
        __asm متطاير ( "bsr %1, %0\n\t"                                       \
                         : "=r" ( ux_بالاترین_اولویت )                               \
                         : "rm" ( uxReadyPriorities )                           \
                         : "cc" )

    #وإلا /* __GNUC__ */
        #ضمن <intrin.h>

        /* BitScanReverse returns the bit position of the most significant '1'
         * in the word. */
        #إذا defined( __x86_64__ ) || defined( _M_X64 )
            #رهنمود intrinsic(بیت_پیمایش_Reverse64)

            #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    \
            افعل                                                                      \
            {                                                                       \
                بیعلامت دراز ul_بالاترین_اولویت;                                        \
                بیت_پیمایش_Reverse64( &ul_بالاترین_اولویت, ( uxReadyPriorities ) );         \
                ux_بالاترین_اولویت = ul_بالاترین_اولویت;                                      \
            } طالما( 0 )

        #وإلا /* #if defined( __x86_64__ ) || defined( _M_X64 ) */
            #رهنمود intrinsic(بیت_پیمایش_معکوس)

            #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    بیت_پیمایش_معکوس( ( بیعلامت دراز * ) &( ux_بالاترین_اولویت ), ( uxReadyPriorities ) )

        #پایان_اگر /* #if defined( __x86_64__ ) || defined( _M_X64 ) */

    #پایان_اگر /* __GNUC__ */

#پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#اگر_تعریف_نشده __GNUC__
    __pragma( warning( disable:4211 ) ) /* Nonstandard extension used, as extern is only nonstandard to MSVC. */
#پایان_اگر


/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کن پورت_وقفه_YIELD                        ( 0UL )
#تعریف_کن پورت_وقفه_TICK                         ( 1UL )
#تعریف_کن پورت_وقفه_APPLICATION_DEFINED_شروع    ( 2UL )

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively.
 */
فراغ v_پورت_Generate_Simulated_وقفه( uint32_t ul_وقفه_عدد );

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively. This function
 * can be called in a windows thread.
 */
فراغ v_پورت_Generate_Simulated_وقفه_From_Windows_Thread( uint32_t ul_وقفه_عدد );

/*
 * Install an interrupt handler to be called by the simulated interrupt handler
 * thread.  The interrupt number must be above any used by the kernel itself
 * (at the time of writing the kernel was using interrupt numbers 0, 1, and 2
 * as defined above).  The number must also be lower than 32.
 *
 * Interrupt handler functions must return a non-zero value if executing the
 * handler resulted in a task switch being required.
 */
فراغ v_پورت_مجموعه_وقفه_Handler( uint32_t ul_وقفه_عدد,
                               uint32_t ( * pvHandler )( فراغ ) );

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر /* ifndef PORTMACRO_H */
