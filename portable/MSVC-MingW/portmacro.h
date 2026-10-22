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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

/******************************************************************************
*   Defines
******************************************************************************/
/* Type definitions. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR                 ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT                ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE               ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG                 ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT                ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE           size_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE    size_t

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE           ਢੇਰ_Type_t;

#ਜੇ defined( __x86_64__ ) || defined( _M_X64 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE    ਲੰਮਾ ਲੰਮਾ
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਲੰਮਾ ਲੰਮਾ            ਅਧਾਰ_Type_t;
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ   UBaseType_t;
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE    ਲੰਮਾ
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਲੰਮਾ                 ਅਧਾਰ_Type_t;
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ        UBaseType_t;
#ਜੇ_ਅੰਤ


#ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t             TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffff
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t             TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32/64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_TYPE_IS_ATOMIC    1
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_64_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t             TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL

#ਜੇ defined( __x86_64__ ) || defined( _M_X64 )
/* 64-bit tick type on a 64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_TYPE_IS_ATOMIC    1
#ਜੇ_ਅੰਤ
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
#ਜੇ_ਅੰਤ

/* Hardware specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH          ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INLINE                __inline

#ਜੇ defined( __x86_64__ ) || defined( _M_X64 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT    8
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT    4
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()    v_ਪੋਰਟ_Generate_Simulated_ਰੁਕਾਵਟ( ਪੋਰਟ_ਰੁਕਾਵਟ_YIELD )


ਬਾਹਰੀ ਅਸਥਿਰ ਅਧਾਰ_Type_t x_Inside_ਰੁਕਾਵਟ;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SOFTWARE_BARRIER()    ਜਦੋਂ( x_Inside_ਰੁਕਾਵਟ != pdFALSE )


/* Simulated interrupts return pdFALSE if no context switch should be performed,
 * or a non-zero number if a context switch should be performed. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x )       ਵਾਪਸ x
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( x )    ਪੋਰਟ_YIELD_FROM_ISR( ( x ) )

ਖਾਲੀ v_ਪੋਰਟ_Close_Running_Thread( ਖਾਲੀ * pv_Task_ਮੰਜ਼ਿਲ_Delete,
                              ਅਸਥਿਰ ਅਧਾਰ_Type_t * pxPendYield );
ਖਾਲੀ v_ਪੋਰਟ_Delete_Thread( ਖਾਲੀ * pv_Thread_ਮੰਜ਼ਿਲ_Delete );
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAN_ਉੱਪਰ_TCB( pxTCB )                                  v_ਪੋਰਟ_Delete_Thread( pxTCB )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_PRE_TASK_DELETE_HOOK( pv_Task_ਮੰਜ਼ਿਲ_Delete, pxPendYield )    v_ਪੋਰਟ_Close_Running_Thread( ( pv_Task_ਮੰਜ਼ਿਲ_Delete ), ( pxPendYield ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()                                   v_ਪੋਰਟ_Enter_Critical()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()                                    v_ਪੋਰਟ_Exit_Critical()

/* Critical section handling. */
ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ );
ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ );

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()    v_ਪੋਰਟ_Enter_Critical()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()     v_ਪੋਰਟ_Exit_Critical()

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION    1
#ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/

#ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #ਜੇ ( configMAX_PRIORITIES > 32 )
        #ਗਲਤੀ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION can only be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 when configMAX_PRIORITIES is less than or equal ਮੰਜ਼ਿਲ 32.  It is very rare that a system requires ਹੋਰ than 10 ਮੰਜ਼ਿਲ 15 difference priorities as tasks that share a ਤਰਜੀਹ will time ਟੁਕੜਾ.
    #ਜੇ_ਅੰਤ

    /* Store/clear the ready priorities in a bit map. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰਿਕਾਰਡ_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( ( ( UBaseType_t ) 1 ) << ( ux_ਤਰਜੀਹ ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( ( ( UBaseType_t ) 1 ) << ( ux_ਤਰਜੀਹ ) )

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __GNUC__

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities )    \
        __asm ਅਸਥਿਰ ( "bsr %1, %0\n\t"                                       \
                         : "=r" ( ux_ਸਿਖਰ_ਤਰਜੀਹ )                               \
                         : "rm" ( uxReadyPriorities )                           \
                         : "cc" )

    #ਨਹੀਂਤਾਂ /* __GNUC__ */
        #ਅਨ੍ਤਰ੍ਭਾਵ <intrin.h>

        /* BitScanReverse returns the bit position of the most significant '1'
         * in the word. */
        #ਜੇ defined( __x86_64__ ) || defined( _M_X64 )
            #ਹਦਾਇਤ intrinsic(ਦੋਆਧਾਰੀ_ਅੰਕ_ਜਾਂਚ_Reverse64)

            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities )    \
            ਕਰੋ                                                                      \
            {                                                                       \
                ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ul_ਸਿਖਰ_ਤਰਜੀਹ;                                        \
                ਦੋਆਧਾਰੀ_ਅੰਕ_ਜਾਂਚ_Reverse64( &ul_ਸਿਖਰ_ਤਰਜੀਹ, ( uxReadyPriorities ) );         \
                ux_ਸਿਖਰ_ਤਰਜੀਹ = ul_ਸਿਖਰ_ਤਰਜੀਹ;                                      \
            } ਜਦੋਂ( 0 )

        #ਨਹੀਂਤਾਂ /* #if defined( __x86_64__ ) || defined( _M_X64 ) */
            #ਹਦਾਇਤ intrinsic(ਦੋਆਧਾਰੀ_ਅੰਕ_ਜਾਂਚ_ਉਲਟ)

            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities )    ਦੋਆਧਾਰੀ_ਅੰਕ_ਜਾਂਚ_ਉਲਟ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ * ) &( ux_ਸਿਖਰ_ਤਰਜੀਹ ), ( uxReadyPriorities ) )

        #ਜੇ_ਅੰਤ /* #if defined( __x86_64__ ) || defined( _M_X64 ) */

    #ਜੇ_ਅੰਤ /* __GNUC__ */

#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __GNUC__
    __pragma( warning( disable:4211 ) ) /* Nonstandard extension used, as extern is only nonstandard to MSVC. */
#ਜੇ_ਅੰਤ


/* Task function macros as described on the FreeRTOS.org WEB site. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰੁਕਾਵਟ_YIELD                        ( 0UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰੁਕਾਵਟ_TICK                         ( 1UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰੁਕਾਵਟ_APPLICATION_DEFINED_ਸ਼ੁਰੂ    ( 2UL )

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively.
 */
ਖਾਲੀ v_ਪੋਰਟ_Generate_Simulated_ਰੁਕਾਵਟ( uint32_t ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ );

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively. This function
 * can be called in a windows thread.
 */
ਖਾਲੀ v_ਪੋਰਟ_Generate_Simulated_ਰੁਕਾਵਟ_From_Windows_Thread( uint32_t ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ );

/*
 * Install an interrupt handler to be called by the simulated interrupt handler
 * thread.  The interrupt number must be above any used by the kernel itself
 * (at the time of writing the kernel was using interrupt numbers 0, 1, and 2
 * as defined above).  The number must also be lower than 32.
 *
 * Interrupt handler functions must return a non-zero value if executing the
 * handler resulted in a task switch being required.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_Handler( uint32_t ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ,
                               uint32_t ( * pvHandler )( ਖਾਲੀ ) );

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* ifndef PORTMACRO_H */
