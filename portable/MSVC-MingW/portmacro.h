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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

/******************************************************************************
*   Defines
******************************************************************************/
/* Type definitions. */
#تعریف_کرو پورٹ_CHAR                 حرف
#تعریف_کرو پورٹ_FLOAT                اعشاری
#تعریف_کرو پورٹ_DOUBLE               دوہرا
#تعریف_کرو پورٹ_LONG                 طویل
#تعریف_کرو پورٹ_SHORT                مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE           size_t
#تعریف_کرو پورٹ_اشارہ_گر_سائز_TYPE    size_t

قسمتعریف پورٹ_ڈھیر_TYPE           ڈھیر_Type_t;

#اگر defined( __x86_64__ ) || defined( _M_X64 )
    #تعریف_کرو پورٹ_بنیاد_TYPE    طویل طویل
    قسمتعریف طویل طویل            بنیاد_Type_t;
    قسمتعریف غیرعلامتی طویل طویل   UBaseType_t;
#ورنہ
    #تعریف_کرو پورٹ_بنیاد_TYPE    طویل
    قسمتعریف طویل                 بنیاد_Type_t;
    قسمتعریف غیرعلامتی طویل        UBaseType_t;
#اگر_ختم


#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t             TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t             TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32/64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_64_بٹ )
    قسمتعریف uint64_t             TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL

#اگر defined( __x86_64__ ) || defined( _M_X64 )
/* 64-bit tick type on a 64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#اگر_ختم
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم

/* Hardware specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH          ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_INLINE                __inline

#اگر defined( __x86_64__ ) || defined( _M_X64 )
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    8
#ورنہ
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    4
#اگر_ختم

#تعریف_کرو پورٹ_YIELD()    v_پورٹ_Generate_Simulated_مداخلت( پورٹ_مداخلت_YIELD )


خارجی متلون بنیاد_Type_t x_Inside_مداخلت;
#تعریف_کرو پورٹ_SOFTWARE_BARRIER()    جب( x_Inside_مداخلت != pdFALSE )


/* Simulated interrupts return pdFALSE if no context switch should be performed,
 * or a non-zero number if a context switch should be performed. */
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )       واپس x
#تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( x )    پورٹ_YIELD_FROM_ISR( ( x ) )

خالی v_پورٹ_Close_Running_Thread( خالی * pv_Task_مقصد_Delete,
                              متلون بنیاد_Type_t * pxPendYield );
خالی v_پورٹ_Delete_Thread( خالی * pv_Thread_مقصد_Delete );
#تعریف_کرو پورٹ_CLEAN_اوپر_TCB( pxTCB )                                  v_پورٹ_Delete_Thread( pxTCB )
#تعریف_کرو پورٹ_PRE_TASK_DELETE_HOOK( pv_Task_مقصد_Delete, pxPendYield )    v_پورٹ_Close_Running_Thread( ( pv_Task_مقصد_Delete ), ( pxPendYield ) )
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                                   v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                                    v_پورٹ_Exit_Critical()

/* Critical section handling. */
خالی v_پورٹ_Enter_Critical( خالی );
خالی v_پورٹ_Exit_Critical( خالی );

#تعریف_کرو پورٹ_ENTER_CRITICAL()    v_پورٹ_Enter_Critical()
#تعریف_کرو پورٹ_EXIT_CRITICAL()     v_پورٹ_Exit_Critical()

#اگر_غیر_تعریف_شدہ config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
#اگر_ختم

/*-----------------------------------------------------------*/

#اگر config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #اگر ( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires مزید than 10 مقصد 15 difference priorities as tasks that share a ترجیح will time قاش.
    #اگر_ختم

    /* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( ( ( UBaseType_t ) 1 ) << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( ( ( UBaseType_t ) 1 ) << ( ux_ترجیح ) )

    #اگر_تعریف_شدہ __GNUC__

        #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    \
        __asm متلون ( "bsr %1, %0\n\t"                                       \
                         : "=r" ( ux_چوٹی_ترجیح )                               \
                         : "rm" ( uxReadyPriorities )                           \
                         : "cc" )

    #ورنہ /* __GNUC__ */
        #شامل <intrin.h>

        /* BitScanReverse returns the bit position of the most significant '1'
         * in the word. */
        #اگر defined( __x86_64__ ) || defined( _M_X64 )
            #ہدایت intrinsic(ثنائی_ہندسہ_جائزہ_Reverse64)

            #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    \
            کرو                                                                      \
            {                                                                       \
                غیرعلامتی طویل ul_چوٹی_ترجیح;                                        \
                ثنائی_ہندسہ_جائزہ_Reverse64( &ul_چوٹی_ترجیح, ( uxReadyPriorities ) );         \
                ux_چوٹی_ترجیح = ul_چوٹی_ترجیح;                                      \
            } جب( 0 )

        #ورنہ /* #if defined( __x86_64__ ) || defined( _M_X64 ) */
            #ہدایت intrinsic(ثنائی_ہندسہ_جائزہ_الٹ)

            #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ثنائی_ہندسہ_جائزہ_الٹ( ( غیرعلامتی طویل * ) &( ux_چوٹی_ترجیح ), ( uxReadyPriorities ) )

        #اگر_ختم /* #if defined( __x86_64__ ) || defined( _M_X64 ) */

    #اگر_ختم /* __GNUC__ */

#اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#اگر_غیر_تعریف_شدہ __GNUC__
    __pragma( warning( disable:4211 ) ) /* Nonstandard extension used, as extern is only nonstandard to MSVC. */
#اگر_ختم


/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

#تعریف_کرو پورٹ_مداخلت_YIELD                        ( 0UL )
#تعریف_کرو پورٹ_مداخلت_TICK                         ( 1UL )
#تعریف_کرو پورٹ_مداخلت_APPLICATION_DEFINED_آغاز    ( 2UL )

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively.
 */
خالی v_پورٹ_Generate_Simulated_مداخلت( uint32_t ul_مداخلت_نمبر );

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively. This function
 * can be called in a windows thread.
 */
خالی v_پورٹ_Generate_Simulated_مداخلت_From_Windows_Thread( uint32_t ul_مداخلت_نمبر );

/*
 * Install an interrupt handler to be called by the simulated interrupt handler
 * thread.  The interrupt number must be above any used by the kernel itself
 * (at the time of writing the kernel was using interrupt numbers 0, 1, and 2
 * as defined above).  The number must also be lower than 32.
 *
 * Interrupt handler functions must return a non-zero value if executing the
 * handler resulted in a task switch being required.
 */
خالی v_پورٹ_سیٹ_مداخلت_Handler( uint32_t ul_مداخلت_نمبر,
                               uint32_t ( * pvHandler )( خالی ) );

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم /* ifndef PORTMACRO_H */
