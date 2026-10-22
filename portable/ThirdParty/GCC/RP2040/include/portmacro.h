/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: MIT AND BSD-3-Clause
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

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
/* *INDENT-ON* */

#अन्तर्भाव "pico.h"
#अन्तर्भाव "hardware/sync.h"
#अन्तर्भाव "rp2040_config.h"

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#परिभाषय पत्तनम्_CHAR          वर्ण
#परिभाषय पत्तनम्_FLOAT         भिन्न
#परिभाषय पत्तनम्_DOUBLE        द्विगुण
#परिभाषय पत्तनम्_LONG          दीर्घ
#परिभाषय पत्तनम्_SHORT         ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE    uint32_t
#परिभाषय पत्तनम्_आधारः_TYPE     दीर्घ

प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
प्रकारनिर्देश int32_t          आधारः_Type_t;
प्रकारनिर्देश uint32_t         UBaseType_t;

#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#परिभाषय पत्तनम्_राशिः_GROWTH                ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT              8
#परिभाषय पत्तनम्_DONT_DISCARD                __attribute__( ( प्रयुक्तम् ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#परिभाषय पत्तनम्_USE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#यदि पत्तनम्_USE_DIVIDER_SAVE_RESTORE
    #परिभाषय पत्तनम्_राशिः_सीमा_PADDING     4
#यदि_अन्तः

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
बाह्य शून्य v_पत्तनम्_Yield( शून्य );
#परिभाषय पत्तनम्_NVIC_INT_CTRL_REG     ( *( ( चञ्चल uint32_t * ) 0xe000ed04 ) )
#परिभाषय पत्तनम्_NVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#परिभाषय पत्तनम्_YIELD()                v_पत्तनम्_Yield()
#परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired )            \
    कुरु                                                      \
    {                                                       \
        यदि( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_गन्तव्यम्_SCHEDULER();                   \
            पत्तनम्_NVIC_INT_CTRL_REG = पत्तनम्_NVIC_PENDSVSET_BIT; \
        }                                                   \
        अन्यथा                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } यावत्( 0 )
#परिभाषय पत्तनम्_YIELD_FROM_ISR( x )    पत्तनम्_अन्तः_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#यदि ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #परिभाषय v_पत्तनम्_SVCHandler        isr_svcall
    #परिभाषय x_पत्तनम्_Pend_SVHandler     isr_pendsv
    #परिभाषय x_पत्तनम्_Sys_Tick_Handler    isr_systick
#यदि_अन्तः

/*-----------------------------------------------------------*/

/* Multi-core */
#परिभाषय पत्तनम्_MAX_CORE_गणनम्    2

/* Check validity of number of cores specified in config */
#यदि ( config_सङ्ख्या_सम्बन्धि_CORES < 1 || पत्तनम्_MAX_CORE_गणनम् < config_सङ्ख्या_सम्बन्धि_CORES )
    #दोषः "Invalid number of cores specified in config!"
#यदि_अन्तः

#यदि ( configTICK_CORE < 0 || configTICK_CORE > config_सङ्ख्या_सम्बन्धि_CORES )
    #दोषः "Invalid tick core specified in config!"
#यदि_अन्तः
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#यदि config_सङ्ख्या_सम्बन्धि_CORES == पत्तनम्_MAX_CORE_गणनम्
    #परिभाषय पत्तनम्_GET_CORE_ID()    get_core_अङ्कः()
#अन्यथा
    #परिभाषय पत्तनम्_GET_CORE_ID()    0
#यदि_अन्तः

#परिभाषय पत्तनम्_CHECK_IF_अन्तर्_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm चञ्चल ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#परिभाषय x_पत्तनम्_Is_Inside_व्यवधानम्() ((आधारः_Type_t)पत्तनम्_CHECK_IF_अन्तर्_ISR())

शून्य vYieldCore( पूर्णाङ्क xCoreID );
#परिभाषय पत्तनम्_YIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#परिभाषय पत्तनम्_CRITICAL_NESTING_अन्तर्_TCB    0

बाह्य UBaseType_t uxCriticalNestings[ config_सङ्ख्या_सम्बन्धि_CORES ];
#परिभाषय पत्तनम्_GET_CRITICAL_NESTING_गणनम्( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#परिभाषय पत्तनम्_समुच्चयः_CRITICAL_NESTING_गणनम्( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#परिभाषय पत्तनम्_INCREMENT_CRITICAL_NESTING_गणनम्( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#परिभाषय पत्तनम्_DECREMENT_CRITICAL_NESTING_गणनम्( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm चञ्चल ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm चञ्चल ( " cpsid i " ::: "memory" );              \
        ulState; } )

#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्( ulState )    __asm चञ्चल ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

बाह्य uint32_t ul_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR( शून्य ) __attribute__( ( naked ) );
बाह्य शून्य v_Clear_व्यवधानम्_आवरणम्_From_ISR( uint32_t ul_आवरणम् )  __attribute__( ( naked ) );
#परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()         ul_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR()
#परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( x )    v_Clear_व्यवधानम्_आवरणम्_From_ISR( x )

#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                  __asm चञ्चल ( " cpsid i " ::: "memory" )
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                   __asm चञ्चल ( " cpsie i " ::: "memory" )

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    बाह्य शून्य v_पत्तनम्_Enter_Critical( शून्य );
    बाह्य शून्य v_पत्तनम्_Exit_Critical( शून्य );
    #परिभाषय पत्तनम्_ENTER_CRITICAL()    v_पत्तनम्_Enter_Critical()
    #परिभाषय पत्तनम्_EXIT_CRITICAL()     v_पत्तनम्_Exit_Critical()
#अन्यथा
    बाह्य शून्य vTaskEnterCritical( शून्य );
    बाह्य शून्य vTaskExitCritical( शून्य );
    बाह्य UBaseType_t vTaskEnterCriticalFromISR( शून्य );
    बाह्य शून्य vTaskExitCriticalFromISR( UBaseType_t ux_Saved_व्यवधानम्_स्थितिः );
    #परिभाषय पत्तनम्_ENTER_CRITICAL()               vTaskEnterCritical()
    #परिभाषय पत्तनम्_EXIT_CRITICAL()                vTaskExitCritical()
    #परिभाषय पत्तनम्_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #परिभाषय पत्तनम्_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#यदि_अन्तः /* if ( configNUMBER_OF_CORES == 1 ) */

#परिभाषय पत्तनम्_RTOS_SPINLOCK_गणनम्    2

#यदि PICO_SDK_संस्करणम्_MAJOR < 2
__force_inline स्थिर bool spin_try_तालकम्_unsafe(spin_तालकम्_t *तालकम्_2) {
   प्रत्यागम *तालकम्_2;
}
#यदि_अन्तः

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
स्थिर अन्तःस्थ शून्य v_पत्तनम्_Recursive_तालकम्( आधारः_Type_t xCoreID,
                                       uint32_t ul_तालकम्_अङ्कः,
                                       spin_तालकम्_t * px_Spin_तालकम्,
                                       आधारः_Type_t uxAcquire )
{
    स्थिर चञ्चल uint8_t ucOwnedByCore[ पत्तनम्_MAX_CORE_गणनम् ][पत्तनम्_RTOS_SPINLOCK_गणनम्];
    स्थिर चञ्चल uint8_t uc_Recursion_गणनम्_By_तालकम्[ पत्तनम्_RTOS_SPINLOCK_गणनम् ];

    configASSERT( ul_तालकम्_अङ्कः < पत्तनम्_RTOS_SPINLOCK_गणनम् );

    यदि( uxAcquire )
    {
        यदि (!spin_try_तालकम्_unsafe(px_Spin_तालकम्)) {
            यदि( ucOwnedByCore[ xCoreID ][ ul_तालकम्_अङ्कः ] )
            {
                configASSERT( uc_Recursion_गणनम्_By_तालकम्[ ul_तालकम्_अङ्कः ] != 255u );
                uc_Recursion_गणनम्_By_तालकम्[ ul_तालकम्_अङ्कः ] = uc_Recursion_गणनम्_By_तालकम्[ ul_तालकम्_अङ्कः ] + 1;
                प्रत्यागम;
            }
            spin_तालकम्_unsafe_blocking(px_Spin_तालकम्);
        }
        configASSERT( uc_Recursion_गणनम्_By_तालकम्[ ul_तालकम्_अङ्कः ] == 0 );
        uc_Recursion_गणनम्_By_तालकम्[ ul_तालकम्_अङ्कः ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_तालकम्_अङ्कः ] = 1;
    }
    अन्यथा
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_तालकम्_अङ्कः ] ) != 0 );
        configASSERT( uc_Recursion_गणनम्_By_तालकम्[ ul_तालकम्_अङ्कः ] != 0 );

        uc_Recursion_गणनम्_By_तालकम्[ ul_तालकम्_अङ्कः ] = uc_Recursion_गणनम्_By_तालकम्[ ul_तालकम्_अङ्कः ] - 1;
        यदि ( uc_Recursion_गणनम्_By_तालकम्[ ul_तालकम्_अङ्कः ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_तालकम्_अङ्कः ] = 0;
            spin_unlock_unsafe(px_Spin_तालकम्);
        }
    }
}

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
    #परिभाषय पत्तनम्_GET_ISR_तालकम्( xCoreID )
    #परिभाषय पत्तनम्_RELEASE_ISR_तालकम्( xCoreID )
    #परिभाषय पत्तनम्_GET_TASK_तालकम्( xCoreID )
    #परिभाषय पत्तनम्_RELEASE_TASK_तालकम्( xCoreID )
#अन्यथा
    #परिभाषय पत्तनम्_GET_ISR_तालकम्( xCoreID )         v_पत्तनम्_Recursive_तालकम्( ( xCoreID ), 0, spin_तालकम्_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #परिभाषय पत्तनम्_RELEASE_ISR_तालकम्( xCoreID )     v_पत्तनम्_Recursive_तालकम्( ( xCoreID ), 0, spin_तालकम्_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #परिभाषय पत्तनम्_GET_TASK_तालकम्( xCoreID )        v_पत्तनम्_Recursive_तालकम्( ( xCoreID ), 1, spin_तालकम्_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #परिभाषय पत्तनम्_RELEASE_TASK_तालकम्( xCoreID )    v_पत्तनम्_Recursive_तालकम्( ( xCoreID ), 1, spin_तालकम्_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#यदि_अन्तः

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#यदि_अपरिभाषितम् पत्तनम्_SUPPRESS_TICKS_AND_SLEEP
    बाह्य शून्य v_पत्तनम्_Suppress_Ticks_And_Sleep( TickType_t xExpectedIdleTime );
    #परिभाषय पत्तनम्_SUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    v_पत्तनम्_Suppress_Ticks_And_Sleep( xExpectedIdleTime )
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

#परिभाषय पत्तनम्_NOP()               __asm चञ्चल ( "nop" )

#परिभाषय पत्तनम्_स्मृतिः_BARRIER()    __asm चञ्चल ( "" ::: "memory" )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
