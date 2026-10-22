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

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

/******************************************************************************
*   Defines
******************************************************************************/
/* Type definitions. */
#परिभाषय पत्तनम्_CHAR                 वर्ण
#परिभाषय पत्तनम्_FLOAT                भिन्न
#परिभाषय पत्तनम्_DOUBLE               द्विगुण
#परिभाषय पत्तनम्_LONG                 दीर्घ
#परिभाषय पत्तनम्_SHORT                ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE           size_t
#परिभाषय पत्तनम्_POINTER_आकार_TYPE    size_t

प्रकारनिर्देश पत्तनम्_राशिः_TYPE           राशिः_Type_t;

#यदि defined( __x86_64__ ) || defined( _M_X64 )
    #परिभाषय पत्तनम्_आधारः_TYPE    दीर्घ दीर्घ
    प्रकारनिर्देश दीर्घ दीर्घ            आधारः_Type_t;
    प्रकारनिर्देश अचिह्नित दीर्घ दीर्घ   UBaseType_t;
#अन्यथा
    #परिभाषय पत्तनम्_आधारः_TYPE    दीर्घ
    प्रकारनिर्देश दीर्घ                 आधारः_Type_t;
    प्रकारनिर्देश अचिह्नित दीर्घ        UBaseType_t;
#यदि_अन्तः


#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t             TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t             TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32/64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_64_द्वयङ्काः )
    प्रकारनिर्देश uint64_t             TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffffffffffffffffULL

#यदि defined( __x86_64__ ) || defined( _M_X64 )
/* 64-bit tick type on a 64-bit architecture, so reads of the tick
 * count do not need to be guarded with a critical section. */
    #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1
#यदि_अन्तः
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः

/* Hardware specifics. */
#परिभाषय पत्तनम्_राशिः_GROWTH          ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_INLINE                __inline

#यदि defined( __x86_64__ ) || defined( _M_X64 )
    #परिभाषय पत्तनम्_BYTE_ALIGNMENT    8
#अन्यथा
    #परिभाषय पत्तनम्_BYTE_ALIGNMENT    4
#यदि_अन्तः

#परिभाषय पत्तनम्_YIELD()    v_पत्तनम्_Generate_Simulated_व्यवधानम्( पत्तनम्_व्यवधानम्_YIELD )


बाह्य चञ्चल आधारः_Type_t x_Inside_व्यवधानम्;
#परिभाषय पत्तनम्_SOFTWARE_BARRIER()    यावत्( x_Inside_व्यवधानम् != pdFALSE )


/* Simulated interrupts return pdFALSE if no context switch should be performed,
 * or a non-zero number if a context switch should be performed. */
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )       प्रत्यागम x
#परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( x )    पत्तनम्_YIELD_FROM_ISR( ( x ) )

शून्य v_पत्तनम्_Close_Running_Thread( शून्य * pv_Task_गन्तव्यम्_Delete,
                              चञ्चल आधारः_Type_t * pxPendYield );
शून्य v_पत्तनम्_Delete_Thread( शून्य * pv_Thread_गन्तव्यम्_Delete );
#परिभाषय पत्तनम्_CLEAN_ऊर्ध्वम्_TCB( pxTCB )                                  v_पत्तनम्_Delete_Thread( pxTCB )
#परिभाषय पत्तनम्_PRE_TASK_DELETE_HOOK( pv_Task_गन्तव्यम्_Delete, pxPendYield )    v_पत्तनम्_Close_Running_Thread( ( pv_Task_गन्तव्यम्_Delete ), ( pxPendYield ) )
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                                   v_पत्तनम्_Enter_Critical()
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                                    v_पत्तनम्_Exit_Critical()

/* Critical section handling. */
शून्य v_पत्तनम्_Enter_Critical( शून्य );
शून्य v_पत्तनम्_Exit_Critical( शून्य );

#परिभाषय पत्तनम्_ENTER_CRITICAL()    v_पत्तनम्_Enter_Critical()
#परिभाषय पत्तनम्_EXIT_CRITICAL()     v_पत्तनम्_Exit_Critical()

#यदि_अपरिभाषितम् config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION
    #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    1
#यदि_अन्तः

/*-----------------------------------------------------------*/

#यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #यदि ( configMAX_PRIORITIES > 32 )
        #दोषः config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION can only be समुच्चयः गन्तव्यम् 1 when configMAX_PRIORITIES is less than or equal गन्तव्यम् 32.  It is very rare that a system requires अधिकम् than 10 गन्तव्यम् 15 difference priorities as tasks that share a प्राथमिकता will time खण्डिका.
    #यदि_अन्तः

    /* Store/clear the ready priorities in a bit map. */
    #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )    ( uxReadyPriorities ) |= ( ( ( UBaseType_t ) 1 ) << ( ux_प्राथमिकता ) )
    #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( ( ( UBaseType_t ) 1 ) << ( ux_प्राथमिकता ) )

    #यदि_परिभाषितम् __GNUC__

        #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities )    \
        __asm चञ्चल ( "bsr %1, %0\n\t"                                       \
                         : "=r" ( ux_शिखरम्_प्राथमिकता )                               \
                         : "rm" ( uxReadyPriorities )                           \
                         : "cc" )

    #अन्यथा /* __GNUC__ */
        #अन्तर्भाव <intrin.h>

        /* BitScanReverse returns the bit position of the most significant '1'
         * in the word. */
        #यदि defined( __x86_64__ ) || defined( _M_X64 )
            #निर्देशः intrinsic(Bit_अवलोकनम्_Reverse64)

            #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities )    \
            कुरु                                                                      \
            {                                                                       \
                अचिह्नित दीर्घ ul_शिखरम्_प्राथमिकता;                                        \
                Bit_अवलोकनम्_Reverse64( &ul_शिखरम्_प्राथमिकता, ( uxReadyPriorities ) );         \
                ux_शिखरम्_प्राथमिकता = ul_शिखरम्_प्राथमिकता;                                      \
            } यावत्( 0 )

        #अन्यथा /* #if defined( __x86_64__ ) || defined( _M_X64 ) */
            #निर्देशः intrinsic(Bit_अवलोकनम्_Reverse)

            #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities )    Bit_अवलोकनम्_Reverse( ( अचिह्नित दीर्घ * ) &( ux_शिखरम्_प्राथमिकता ), ( uxReadyPriorities ) )

        #यदि_अन्तः /* #if defined( __x86_64__ ) || defined( _M_X64 ) */

    #यदि_अन्तः /* __GNUC__ */

#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#यदि_अपरिभाषितम् __GNUC__
    __pragma( warning( disable:4211 ) ) /* Nonstandard extension used, as extern is only nonstandard to MSVC. */
#यदि_अन्तः


/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

#परिभाषय पत्तनम्_व्यवधानम्_YIELD                        ( 0UL )
#परिभाषय पत्तनम्_व्यवधानम्_TICK                         ( 1UL )
#परिभाषय पत्तनम्_व्यवधानम्_APPLICATION_DEFINED_START    ( 2UL )

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively.
 */
शून्य v_पत्तनम्_Generate_Simulated_व्यवधानम्( uint32_t ul_व्यवधानम्_सङ्ख्या );

/*
 * Raise a simulated interrupt represented by the bit mask in ulInterruptMask.
 * Each bit can be used to represent an individual interrupt - with the first
 * two bits being used for the Yield and Tick interrupts respectively. This function
 * can be called in a windows thread.
 */
शून्य v_पत्तनम्_Generate_Simulated_व्यवधानम्_From_Windows_Thread( uint32_t ul_व्यवधानम्_सङ्ख्या );

/*
 * Install an interrupt handler to be called by the simulated interrupt handler
 * thread.  The interrupt number must be above any used by the kernel itself
 * (at the time of writing the kernel was using interrupt numbers 0, 1, and 2
 * as defined above).  The number must also be lower than 32.
 *
 * Interrupt handler functions must return a non-zero value if executing the
 * handler resulted in a task switch being required.
 */
शून्य v_पत्तनम्_समुच्चयः_व्यवधानम्_Handler( uint32_t ul_व्यवधानम्_सङ्ख्या,
                               uint32_t ( * pvHandler )( शून्य ) );

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः /* ifndef PORTMACRO_H */
