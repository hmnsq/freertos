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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

/******************************************************************************
*   Defines
******************************************************************************/
/* Type definitions. */
#నిర్వచించు పోర్టు_CHAR                 అక్షరం
#నిర్వచించు పోర్టు_FLOAT                దశాంశం
#నిర్వచించు పోర్టు_DOUBLE               ద్విగుణ
#నిర్వచించు పోర్టు_LONG                 దీర్ఘ
#నిర్వచించు పోర్టు_SHORT                పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE           size_t
#నిర్వచించు పోర్టు_సూచిక_కొలత_TYPE    size_t

రకనిర్వచనం పోర్టు_దొంతర_TYPE           దొంతర_Type_t;

#ఒకవేళ defined( __x86_64__ ) || defined( _M_X64 )
    #నిర్వచించు పోర్టు_పునాది_TYPE    దీర్ఘ దీర్ఘ
    రకనిర్వచనం దీర్ఘ దీర్ఘ            పునాది_Type_t;
    రకనిర్వచనం గుర్తులేని దీర్ఘ దీర్ఘ   UBaseType_t;
#లేకపోతే
    #నిర్వచించు పోర్టు_పునాది_TYPE    దీర్ఘ
    రకనిర్వచనం దీర్ఘ                 పునాది_Type_t;
    రకనిర్వచనం గుర్తులేని దీర్ఘ        UBaseType_t;
#అయితే_ముగింపు


#ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t             TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t             TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32/64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC    1
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_64_బిట్లు )
    రకనిర్వచనం uint64_t             TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL

#ఒకవేళ defined( __x86_64__ ) || defined( _M_X64 )
/* 64-bit tick type on a 64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC    1
#అయితే_ముగింపు
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు

/* Hardware specifics. */
#నిర్వచించు పోర్టు_దొంతర_GROWTH          ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_INLINE                __inline

#ఒకవేళ defined( __x86_64__ ) || defined( _M_X64 )
    #నిర్వచించు పోర్టు_BYTE_ALIGNMENT    8
#లేకపోతే
    #నిర్వచించు పోర్టు_BYTE_ALIGNMENT    4
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_YIELD()    v_పోర్టు_Generate_Simulated_అంతరాయం( పోర్టు_అంతరాయం_YIELD )


బాహ్య అస్థిర పునాది_Type_t x_Inside_అంతరాయం;
#నిర్వచించు పోర్టు_SOFTWARE_BARRIER()    అయితే( x_Inside_అంతరాయం != pdFALSE )


/* Simulated interrupts return pdFALSE if no context switch should be performed,
 * or a non-zero number if a context switch should be performed. */
#నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )       తిరిగి x
#నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( x )    పోర్టు_YIELD_FROM_ISR( ( x ) )

శూన్య v_పోర్టు_Close_Running_Thread( శూన్య * pv_Task_గమ్యం_Delete,
                              అస్థిర పునాది_Type_t * pxPendYield );
శూన్య v_పోర్టు_Delete_Thread( శూన్య * pv_Thread_గమ్యం_Delete );
#నిర్వచించు పోర్టు_CLEAN_పైకి_TCB( pxTCB )                                  v_పోర్టు_Delete_Thread( pxTCB )
#నిర్వచించు పోర్టు_PRE_TASK_DELETE_HOOK( pv_Task_గమ్యం_Delete, pxPendYield )    v_పోర్టు_Close_Running_Thread( ( pv_Task_గమ్యం_Delete ), ( pxPendYield ) )
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                                   v_పోర్టు_Enter_Critical()
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                                    v_పోర్టు_Exit_Critical()

/* Critical section handling. */
శూన్య v_పోర్టు_Enter_Critical( శూన్య );
శూన్య v_పోర్టు_Exit_Critical( శూన్య );

#నిర్వచించు పోర్టు_ENTER_CRITICAL()    v_పోర్టు_Enter_Critical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()     v_పోర్టు_Exit_Critical()

#నిర్వచితం_కాకపోతే config_USE_పోర్టు_OPTIMISED_TASK_SELECTION
    #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    1
#అయితే_ముగింపు

/*-----------------------------------------------------------*/

#ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #ఒకవేళ ( configMAX_PRIORITIES > 32 )
        #దోషం config_USE_పోర్టు_OPTIMISED_TASK_SELECTION can only be సమితి గమ్యం 1 when configMAX_PRIORITIES is less than or equal గమ్యం 32.  It is very rare that a system requires మరిన్ని than 10 గమ్యం 15 difference priorities as tasks that share a ప్రాధాన్యత will time ముక్క.
    #అయితే_ముగింపు

    /* Store/clear the ready priorities in a bit map. */
    #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )    ( uxReadyPriorities ) |= ( ( ( UBaseType_t ) 1 ) << ( ux_ప్రాధాన్యత ) )
    #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( ( ( UBaseType_t ) 1 ) << ( ux_ప్రాధాన్యత ) )

    #నిర్వచితమైతే __GNUC__

        #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities )    \
        __asm అస్థిర ( "bsr %1, %0\n\t"                                       \
                         : "=r" ( ux_శిఖరం_ప్రాధాన్యత )                               \
                         : "rm" ( uxReadyPriorities )                           \
                         : "cc" )

    #లేకపోతే /* __GNUC__ */
        #అన్తర్భావ <intrin.h>

        /* BitScanReverse returns the bit position of the most significant '1'
         * in the word. */
        #ఒకవేళ defined( __x86_64__ ) || defined( _M_X64 )
            #సూచన intrinsic(బిట్టు_పరిశీలన_Reverse64)

            #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities )    \
            చేయి                                                                      \
            {                                                                       \
                గుర్తులేని దీర్ఘ ul_శిఖరం_ప్రాధాన్యత;                                        \
                బిట్టు_పరిశీలన_Reverse64( &ul_శిఖరం_ప్రాధాన్యత, ( uxReadyPriorities ) );         \
                ux_శిఖరం_ప్రాధాన్యత = ul_శిఖరం_ప్రాధాన్యత;                                      \
            } అయితే( 0 )

        #లేకపోతే /* #if defined( __x86_64__ ) || defined( _M_X64 ) */
            #సూచన intrinsic(బిట్టు_పరిశీలన_తిరగేయి)

            #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities )    బిట్టు_పరిశీలన_తిరగేయి( ( గుర్తులేని దీర్ఘ * ) &( ux_శిఖరం_ప్రాధాన్యత ), ( uxReadyPriorities ) )

        #అయితే_ముగింపు /* #if defined( __x86_64__ ) || defined( _M_X64 ) */

    #అయితే_ముగింపు /* __GNUC__ */

#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#నిర్వచితం_కాకపోతే __GNUC__
    __pragma( warning( disable:4211 ) ) /* Nonstandard extension used, as extern is only nonstandard to MSVC. */
#అయితే_ముగింపు


/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

#నిర్వచించు పోర్టు_అంతరాయం_YIELD                        ( 0UL )
#నిర్వచించు పోర్టు_అంతరాయం_TICK                         ( 1UL )
#నిర్వచించు పోర్టు_అంతరాయం_APPLICATION_DEFINED_ప్రారంభం    ( 2UL )

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively.
 */
శూన్య v_పోర్టు_Generate_Simulated_అంతరాయం( uint32_t ul_అంతరాయం_సంఖ్య );

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively. This function
 * can be called in a windows thread.
 */
శూన్య v_పోర్టు_Generate_Simulated_అంతరాయం_From_Windows_Thread( uint32_t ul_అంతరాయం_సంఖ్య );

/*
 * Install an interrupt handler to be called by the simulated interrupt handler
 * thread.  The interrupt number must be above any used by the kernel itself
 * (at the time of writing the kernel was using interrupt numbers 0, 1, and 2
 * as defined above).  The number must also be lower than 32.
 *
 * Interrupt handler functions must return a non-zero value if executing the
 * handler resulted in a task switch being required.
 */
శూన్య v_పోర్టు_సమితి_అంతరాయం_Handler( uint32_t ul_అంతరాయం_సంఖ్య,
                               uint32_t ( * pvHandler )( శూన్య ) );

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు /* ifndef PORTMACRO_H */
