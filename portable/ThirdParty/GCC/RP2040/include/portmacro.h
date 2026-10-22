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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
/* *INDENT-ON* */

#ضمن "pico.h"
#ضمن "hardware/sync.h"
#ضمن "rp2040_config.h"

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
#وصف_ڪريو پورٽ_CHAR          حرف
#وصف_ڪريو پورٽ_FLOAT         عائم
#وصف_ڪريو پورٽ_DOUBLE        مزدوج
#وصف_ڪريو پورٽ_LONG          ڊگهو
#وصف_ڪريو پورٽ_SHORT         ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE    uint32_t
#وصف_ڪريو پورٽ_بنياد_TYPE     ڊگهو

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع int32_t          بنياد_Type_t;
تعريفنوع uint32_t         UBaseType_t;

#إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#وصف_ڪريو پورٽ_ڍير_GROWTH                ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT              8
#وصف_ڪريو پورٽ_DONT_DISCARD                __attribute__( ( استعمال_ٿيل ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#وصف_ڪريو پورٽ_USE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#إذا پورٽ_USE_DIVIDER_SAVE_RESTORE
    #وصف_ڪريو پورٽ_ڍير_حد_بندي_PADDING     4
#جيڪڏهن_پورو

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
خارجي فراغ v_پورٽ_Yield( فراغ );
#وصف_ڪريو پورٽ_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#وصف_ڪريو پورٽ_NVIC_PENDSVSET_ٻٽو_انگ    ( 1UL << 28UL )
#وصف_ڪريو پورٽ_YIELD()                v_پورٽ_Yield()
#وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_منزل_SCHEDULER();                   \
            پورٽ_NVIC_INT_CTRL_REG = پورٽ_NVIC_PENDSVSET_ٻٽو_انگ; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )    پورٽ_پڇاڙي_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#إذا ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #وصف_ڪريو v_پورٽ_SVCHandler        isr_svcall
    #وصف_ڪريو x_پورٽ_Pend_SVHandler     isr_pendsv
    #وصف_ڪريو x_پورٽ_Sys_Tick_Handler    isr_systick
#جيڪڏهن_پورو

/*-----------------------------------------------------------*/

/* Multi-core */
#وصف_ڪريو پورٽ_MAX_CORE_ڳڻپ    2

/* Check validity of number of cores specified in config */
#إذا ( config_عدد_جو_CORES < 1 || پورٽ_MAX_CORE_ڳڻپ < config_عدد_جو_CORES )
    #غلطي "Invalid number of cores specified in config!"
#جيڪڏهن_پورو

#إذا ( configTICK_CORE < 0 || configTICK_CORE > config_عدد_جو_CORES )
    #غلطي "Invalid tick core specified in config!"
#جيڪڏهن_پورو
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#إذا config_عدد_جو_CORES == پورٽ_MAX_CORE_ڳڻپ
    #وصف_ڪريو پورٽ_GET_CORE_ID()    get_core_انگ()
#وإلا
    #وصف_ڪريو پورٽ_GET_CORE_ID()    0
#جيڪڏهن_پورو

#وصف_ڪريو پورٽ_CHECK_IF_اندريون_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm متطاير ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#وصف_ڪريو x_پورٽ_Is_Inside_مداخلت() ((بنياد_Type_t)پورٽ_CHECK_IF_اندريون_ISR())

فراغ vYieldCore( صحيح xCoreID );
#وصف_ڪريو پورٽ_YIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#وصف_ڪريو پورٽ_CRITICAL_NESTING_اندريون_TCB    0

خارجي UBaseType_t uxCriticalNestings[ config_عدد_جو_CORES ];
#وصف_ڪريو پورٽ_GET_CRITICAL_NESTING_ڳڻپ( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#وصف_ڪريو پورٽ_سيٽ_CRITICAL_NESTING_ڳڻپ( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#وصف_ڪريو پورٽ_INCREMENT_CRITICAL_NESTING_ڳڻپ( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#وصف_ڪريو پورٽ_DECREMENT_CRITICAL_NESTING_ڳڻپ( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm متطاير ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm متطاير ( " cpsid i " ::: "memory" );              \
        ulState; } )

#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب( ulState )    __asm متطاير ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

خارجي uint32_t ul_سيٽ_مداخلت_نقاب_From_ISR( فراغ ) __attribute__( ( naked ) );
خارجي فراغ v_Clear_مداخلت_نقاب_From_ISR( uint32_t ul_نقاب )  __attribute__( ( naked ) );
#وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()         ul_سيٽ_مداخلت_نقاب_From_ISR()
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_Clear_مداخلت_نقاب_From_ISR( x )

#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                  __asm متطاير ( " cpsid i " ::: "memory" )
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                   __asm متطاير ( " cpsie i " ::: "memory" )

#إذا ( config_عدد_جو_CORES == 1 )
    خارجي فراغ v_پورٽ_Enter_Critical( فراغ );
    خارجي فراغ v_پورٽ_Exit_Critical( فراغ );
    #وصف_ڪريو پورٽ_ENTER_CRITICAL()    v_پورٽ_Enter_Critical()
    #وصف_ڪريو پورٽ_EXIT_CRITICAL()     v_پورٽ_Exit_Critical()
#وإلا
    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_مداخلت_حالت );
    #وصف_ڪريو پورٽ_ENTER_CRITICAL()               vTaskEnterCritical()
    #وصف_ڪريو پورٽ_EXIT_CRITICAL()                vTaskExitCritical()
    #وصف_ڪريو پورٽ_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #وصف_ڪريو پورٽ_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES == 1 ) */

#وصف_ڪريو پورٽ_RTOS_SPINLOCK_ڳڻپ    2

#إذا PICO_SDK_نسخو_MAJOR < 2
__force_inline ساكن bool spin_try_تالو_unsafe(spin_تالو_t *تالو_2) {
   أرجع *تالو_2;
}
#جيڪڏهن_پورو

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
ساكن مضمن فراغ v_پورٽ_Recursive_تالو( بنياد_Type_t xCoreID,
                                       uint32_t ul_تالو_انگ,
                                       spin_تالو_t * px_Spin_تالو,
                                       بنياد_Type_t uxAcquire )
{
    ساكن متطاير uint8_t ucOwnedByCore[ پورٽ_MAX_CORE_ڳڻپ ][پورٽ_RTOS_SPINLOCK_ڳڻپ];
    ساكن متطاير uint8_t uc_Recursion_ڳڻپ_By_تالو[ پورٽ_RTOS_SPINLOCK_ڳڻپ ];

    configASSERT( ul_تالو_انگ < پورٽ_RTOS_SPINLOCK_ڳڻپ );

    إذا( uxAcquire )
    {
        إذا (!spin_try_تالو_unsafe(px_Spin_تالو)) {
            إذا( ucOwnedByCore[ xCoreID ][ ul_تالو_انگ ] )
            {
                configASSERT( uc_Recursion_ڳڻپ_By_تالو[ ul_تالو_انگ ] != 255u );
                uc_Recursion_ڳڻپ_By_تالو[ ul_تالو_انگ ] = uc_Recursion_ڳڻپ_By_تالو[ ul_تالو_انگ ] + 1;
                أرجع;
            }
            spin_تالو_unsafe_blocking(px_Spin_تالو);
        }
        configASSERT( uc_Recursion_ڳڻپ_By_تالو[ ul_تالو_انگ ] == 0 );
        uc_Recursion_ڳڻپ_By_تالو[ ul_تالو_انگ ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_تالو_انگ ] = 1;
    }
    وإلا
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_تالو_انگ ] ) != 0 );
        configASSERT( uc_Recursion_ڳڻپ_By_تالو[ ul_تالو_انگ ] != 0 );

        uc_Recursion_ڳڻپ_By_تالو[ ul_تالو_انگ ] = uc_Recursion_ڳڻپ_By_تالو[ ul_تالو_انگ ] - 1;
        إذا ( uc_Recursion_ڳڻپ_By_تالو[ ul_تالو_انگ ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_تالو_انگ ] = 0;
            spin_unlock_unsafe(px_Spin_تالو);
        }
    }
}

#إذا ( config_عدد_جو_CORES == 1 )
    #وصف_ڪريو پورٽ_GET_ISR_تالو( xCoreID )
    #وصف_ڪريو پورٽ_RELEASE_ISR_تالو( xCoreID )
    #وصف_ڪريو پورٽ_GET_TASK_تالو( xCoreID )
    #وصف_ڪريو پورٽ_RELEASE_TASK_تالو( xCoreID )
#وإلا
    #وصف_ڪريو پورٽ_GET_ISR_تالو( xCoreID )         v_پورٽ_Recursive_تالو( ( xCoreID ), 0, spin_تالو_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #وصف_ڪريو پورٽ_RELEASE_ISR_تالو( xCoreID )     v_پورٽ_Recursive_تالو( ( xCoreID ), 0, spin_تالو_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #وصف_ڪريو پورٽ_GET_TASK_تالو( xCoreID )        v_پورٽ_Recursive_تالو( ( xCoreID ), 1, spin_تالو_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #وصف_ڪريو پورٽ_RELEASE_TASK_تالو( xCoreID )    v_پورٽ_Recursive_تالو( ( xCoreID ), 1, spin_تالو_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#جيڪڏهن_پورو

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#جيڪڏهن_وصف_نه_ٿيل پورٽ_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورٽ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت );
    #وصف_ڪريو پورٽ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_وقت )    v_پورٽ_Suppress_Ticks_And_Sleep( x_Expected_Idle_وقت )
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#وصف_ڪريو پورٽ_NOP()               __asm متطاير ( "nop" )

#وصف_ڪريو پورٽ_يادگيري_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
