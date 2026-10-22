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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
/* *INDENT-ON* */

#అన్తర్భావ "pico.h"
#అన్తర్భావ "hardware/sync.h"
#అన్తర్భావ "rp2040_config.h"

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
#నిర్వచించు పోర్టు_CHAR          అక్షరం
#నిర్వచించు పోర్టు_FLOAT         దశాంశం
#నిర్వచించు పోర్టు_DOUBLE        ద్విగుణ
#నిర్వచించు పోర్టు_LONG          దీర్ఘ
#నిర్వచించు పోర్టు_SHORT         పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE    uint32_t
#నిర్వచించు పోర్టు_పునాది_TYPE     దీర్ఘ

రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం int32_t          పునాది_Type_t;
రకనిర్వచనం uint32_t         UBaseType_t;

#ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC    1
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#నిర్వచించు పోర్టు_దొంతర_GROWTH                ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT              8
#నిర్వచించు పోర్టు_DONT_DISCARD                __attribute__( ( వాడిన ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#నిర్వచించు పోర్టు_USE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#ఒకవేళ పోర్టు_USE_DIVIDER_SAVE_RESTORE
    #నిర్వచించు పోర్టు_దొంతర_హద్దు_PADDING     4
#అయితే_ముగింపు

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
బాహ్య శూన్య v_పోర్టు_Yield( శూన్య );
#నిర్వచించు పోర్టు_NVIC_INT_CTRL_REG     ( *( ( అస్థిర uint32_t * ) 0xe000ed04 ) )
#నిర్వచించు పోర్టు_NVIC_PENDSVSET_బిట్టు    ( 1UL << 28UL )
#నిర్వచించు పోర్టు_YIELD()                v_పోర్టు_Yield()
#నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired )            \
    చేయి                                                      \
    {                                                       \
        ఒకవేళ( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_గమ్యం_SCHEDULER();                   \
            పోర్టు_NVIC_INT_CTRL_REG = పోర్టు_NVIC_PENDSVSET_బిట్టు; \
        }                                                   \
        లేకపోతే                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } అయితే( 0 )
#నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )    పోర్టు_చివర_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#ఒకవేళ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #నిర్వచించు v_పోర్టు_SVCHandler        isr_svcall
    #నిర్వచించు x_పోర్టు_Pend_SVHandler     isr_pendsv
    #నిర్వచించు x_పోర్టు_Sys_Tick_Handler    isr_systick
#అయితే_ముగింపు

/*-----------------------------------------------------------*/

/* Multi-core */
#నిర్వచించు పోర్టు_MAX_CORE_లెక్క    2

/* Check validity of number of cores specified in config */
#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES < 1 || పోర్టు_MAX_CORE_లెక్క < config_సంఖ్య_యొక్క_CORES )
    #దోషం "Invalid number of cores specified in config!"
#అయితే_ముగింపు

#ఒకవేళ ( configTICK_CORE < 0 || configTICK_CORE > config_సంఖ్య_యొక్క_CORES )
    #దోషం "Invalid tick core specified in config!"
#అయితే_ముగింపు
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#ఒకవేళ config_సంఖ్య_యొక్క_CORES == పోర్టు_MAX_CORE_లెక్క
    #నిర్వచించు పోర్టు_GET_CORE_ID()    get_core_అంకె()
#లేకపోతే
    #నిర్వచించు పోర్టు_GET_CORE_ID()    0
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_CHECK_IF_లోపల_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm అస్థిర ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#నిర్వచించు x_పోర్టు_Is_Inside_అంతరాయం() ((పునాది_Type_t)పోర్టు_CHECK_IF_లోపల_ISR())

శూన్య vYieldCore( పూర్ణాంకం xCoreID );
#నిర్వచించు పోర్టు_YIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#నిర్వచించు పోర్టు_CRITICAL_NESTING_లోపల_TCB    0

బాహ్య UBaseType_t uxCriticalNestings[ config_సంఖ్య_యొక్క_CORES ];
#నిర్వచించు పోర్టు_GET_CRITICAL_NESTING_లెక్క( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#నిర్వచించు పోర్టు_సమితి_CRITICAL_NESTING_లెక్క( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#నిర్వచించు పోర్టు_INCREMENT_CRITICAL_NESTING_లెక్క( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#నిర్వచించు పోర్టు_DECREMENT_CRITICAL_NESTING_లెక్క( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm అస్థిర ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm అస్థిర ( " cpsid i " ::: "memory" );              \
        ulState; } )

#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు( ulState )    __asm అస్థిర ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

బాహ్య uint32_t ul_సమితి_అంతరాయం_ముసుగు_From_ISR( శూన్య ) __attribute__( ( naked ) );
బాహ్య శూన్య v_Clear_అంతరాయం_ముసుగు_From_ISR( uint32_t ul_ముసుగు )  __attribute__( ( naked ) );
#నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()         ul_సమితి_అంతరాయం_ముసుగు_From_ISR()
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( x )    v_Clear_అంతరాయం_ముసుగు_From_ISR( x )

#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                  __asm అస్థిర ( " cpsid i " ::: "memory" )
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                   __asm అస్థిర ( " cpsie i " ::: "memory" )

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
    బాహ్య శూన్య v_పోర్టు_Enter_Critical( శూన్య );
    బాహ్య శూన్య v_పోర్టు_Exit_Critical( శూన్య );
    #నిర్వచించు పోర్టు_ENTER_CRITICAL()    v_పోర్టు_Enter_Critical()
    #నిర్వచించు పోర్టు_EXIT_CRITICAL()     v_పోర్టు_Exit_Critical()
#లేకపోతే
    బాహ్య శూన్య vTaskEnterCritical( శూన్య );
    బాహ్య శూన్య vTaskExitCritical( శూన్య );
    బాహ్య UBaseType_t vTaskEnterCriticalFromISR( శూన్య );
    బాహ్య శూన్య vTaskExitCriticalFromISR( UBaseType_t ux_Saved_అంతరాయం_స్థితి );
    #నిర్వచించు పోర్టు_ENTER_CRITICAL()               vTaskEnterCritical()
    #నిర్వచించు పోర్టు_EXIT_CRITICAL()                vTaskExitCritical()
    #నిర్వచించు పోర్టు_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #నిర్వచించు పోర్టు_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#అయితే_ముగింపు /* if ( configNUMBER_OF_CORES == 1 ) */

#నిర్వచించు పోర్టు_RTOS_SPINLOCK_లెక్క    2

#ఒకవేళ PICO_SDK_సంస్కరణ_MAJOR < 2
__force_inline స్థిర bool spin_try_తాళం_unsafe(spin_తాళం_t *తాళం_3) {
   తిరిగి *తాళం_3;
}
#అయితే_ముగింపు

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
స్థిర అంతఃవరుస శూన్య v_పోర్టు_Recursive_తాళం( పునాది_Type_t xCoreID,
                                       uint32_t ul_తాళం_అంకె,
                                       spin_తాళం_t * px_Spin_తాళం,
                                       పునాది_Type_t uxAcquire )
{
    స్థిర అస్థిర uint8_t ucOwnedByCore[ పోర్టు_MAX_CORE_లెక్క ][పోర్టు_RTOS_SPINLOCK_లెక్క];
    స్థిర అస్థిర uint8_t uc_Recursion_లెక్క_By_తాళం[ పోర్టు_RTOS_SPINLOCK_లెక్క ];

    configASSERT( ul_తాళం_అంకె < పోర్టు_RTOS_SPINLOCK_లెక్క );

    ఒకవేళ( uxAcquire )
    {
        ఒకవేళ (!spin_try_తాళం_unsafe(px_Spin_తాళం)) {
            ఒకవేళ( ucOwnedByCore[ xCoreID ][ ul_తాళం_అంకె ] )
            {
                configASSERT( uc_Recursion_లెక్క_By_తాళం[ ul_తాళం_అంకె ] != 255u );
                uc_Recursion_లెక్క_By_తాళం[ ul_తాళం_అంకె ] = uc_Recursion_లెక్క_By_తాళం[ ul_తాళం_అంకె ] + 1;
                తిరిగి;
            }
            spin_తాళం_unsafe_blocking(px_Spin_తాళం);
        }
        configASSERT( uc_Recursion_లెక్క_By_తాళం[ ul_తాళం_అంకె ] == 0 );
        uc_Recursion_లెక్క_By_తాళం[ ul_తాళం_అంకె ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_తాళం_అంకె ] = 1;
    }
    లేకపోతే
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_తాళం_అంకె ] ) != 0 );
        configASSERT( uc_Recursion_లెక్క_By_తాళం[ ul_తాళం_అంకె ] != 0 );

        uc_Recursion_లెక్క_By_తాళం[ ul_తాళం_అంకె ] = uc_Recursion_లెక్క_By_తాళం[ ul_తాళం_అంకె ] - 1;
        ఒకవేళ ( uc_Recursion_లెక్క_By_తాళం[ ul_తాళం_అంకె ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_తాళం_అంకె ] = 0;
            spin_unlock_unsafe(px_Spin_తాళం);
        }
    }
}

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
    #నిర్వచించు పోర్టు_GET_ISR_తాళం( xCoreID )
    #నిర్వచించు పోర్టు_RELEASE_ISR_తాళం( xCoreID )
    #నిర్వచించు పోర్టు_GET_TASK_తాళం( xCoreID )
    #నిర్వచించు పోర్టు_RELEASE_TASK_తాళం( xCoreID )
#లేకపోతే
    #నిర్వచించు పోర్టు_GET_ISR_తాళం( xCoreID )         v_పోర్టు_Recursive_తాళం( ( xCoreID ), 0, spin_తాళం_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #నిర్వచించు పోర్టు_RELEASE_ISR_తాళం( xCoreID )     v_పోర్టు_Recursive_తాళం( ( xCoreID ), 0, spin_తాళం_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #నిర్వచించు పోర్టు_GET_TASK_తాళం( xCoreID )        v_పోర్టు_Recursive_తాళం( ( xCoreID ), 1, spin_తాళం_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #నిర్వచించు పోర్టు_RELEASE_TASK_తాళం( xCoreID )    v_పోర్టు_Recursive_తాళం( ( xCoreID ), 1, spin_తాళం_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#అయితే_ముగింపు

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#నిర్వచితం_కాకపోతే పోర్టు_SUPPRESS_TICKS_AND_SLEEP
    బాహ్య శూన్య v_పోర్టు_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_సమయం );
    #నిర్వచించు పోర్టు_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_సమయం )    v_పోర్టు_Suppress_Ticks_And_Sleep( x_Expected_Idle_సమయం )
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

#నిర్వచించు పోర్టు_NOP()               __asm అస్థిర ( "nop" )

#నిర్వచించు పోర్టు_జ్ఞాపకం_BARRIER()    __asm అస్థిర ( "" ::: "memory" )

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
