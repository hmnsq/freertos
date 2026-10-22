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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਅਨ੍ਤਰ੍ਭਾਵ "pico.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hardware/sync.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "rp2040_config.h"

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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    uint32_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਲੰਮਾ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE   ਢੇਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int32_t          ਅਧਾਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t         UBaseType_t;

#ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffff
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_TYPE_IS_ATOMIC    1
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH                ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT              8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DONT_DISCARD                __attribute__( ( ਵਰਤਿਆ ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_USE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#ਜੇ ਪੋਰਟ_USE_DIVIDER_SAVE_RESTORE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_ਹੱਦਬੰਦੀ_PADDING     4
#ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ );
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_INT_CTRL_REG     ( *( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed04 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ    ( 1UL << 28UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()                v_ਪੋਰਟ_Yield()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( xSwitchRequired )            \
    ਕਰੋ                                                      \
    {                                                       \
        ਜੇ( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_ਮੰਜ਼ਿਲ_SCHEDULER();                   \
            ਪੋਰਟ_NVIC_INT_CTRL_REG = ਪੋਰਟ_NVIC_PENDSVSET_ਦੋਆਧਾਰੀ_ਅੰਕ; \
        }                                                   \
        ਨਹੀਂਤਾਂ                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } ਜਦੋਂ( 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x )    ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#ਜੇ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ v_ਪੋਰਟ_SVCHandler        isr_svcall
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ x_ਪੋਰਟ_Pend_SVHandler     isr_pendsv
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ x_ਪੋਰਟ_Sys_Tick_Handler    isr_systick
#ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/

/* Multi-core */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ    2

/* Check validity of number of cores specified in config */
#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES < 1 || ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ < config_ਸੰਖਿਆ_ਦਾ_CORES )
    #ਗਲਤੀ "Invalid number of cores specified in config!"
#ਜੇ_ਅੰਤ

#ਜੇ ( configTICK_CORE < 0 || configTICK_CORE > config_ਸੰਖਿਆ_ਦਾ_CORES )
    #ਗਲਤੀ "Invalid tick core specified in config!"
#ਜੇ_ਅੰਤ
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#ਜੇ config_ਸੰਖਿਆ_ਦਾ_CORES == ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_CORE_ID()    get_core_ਅੰਕ()
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_CORE_ID()    0
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHECK_IF_ਵਿੱਚ_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm ਅਸਥਿਰ ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ x_ਪੋਰਟ_Is_Inside_ਰੁਕਾਵਟ() ((ਅਧਾਰ_Type_t)ਪੋਰਟ_CHECK_IF_ਵਿੱਚ_ISR())

ਖਾਲੀ vYieldCore( ਪੂਰਨ xCoreID );
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਚ_TCB    0

ਬਾਹਰੀ UBaseType_t uxCriticalNestings[ config_ਸੰਖਿਆ_ਦਾ_CORES ];
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INCREMENT_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DECREMENT_CRITICAL_NESTING_ਗਿਣਤੀ( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm ਅਸਥਿਰ ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm ਅਸਥਿਰ ( " cpsid i " ::: "memory" );              \
        ulState; } )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ( ulState )    __asm ਅਸਥਿਰ ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

ਬਾਹਰੀ uint32_t ul_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( ਖਾਲੀ ) __attribute__( ( naked ) );
ਬਾਹਰੀ ਖਾਲੀ v_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( uint32_t ul_ਨਕਾਬ )  __attribute__( ( naked ) );
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR()         ul_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR()
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( x )    v_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( x )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()                  __asm ਅਸਥਿਰ ( " cpsid i " ::: "memory" )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()                   __asm ਅਸਥਿਰ ( " cpsie i " ::: "memory" )

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()    v_ਪੋਰਟ_Enter_Critical()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()     v_ਪੋਰਟ_Exit_Critical()
#ਨਹੀਂਤਾਂ
    ਬਾਹਰੀ ਖਾਲੀ vTaskEnterCritical( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ vTaskExitCritical( ਖਾਲੀ );
    ਬਾਹਰੀ UBaseType_t vTaskEnterCriticalFromISR( ਖਾਲੀ );
    ਬਾਹਰੀ ਖਾਲੀ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()               vTaskEnterCritical()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                vTaskExitCritical()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#ਜੇ_ਅੰਤ /* if ( configNUMBER_OF_CORES == 1 ) */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RTOS_SPINLOCK_ਗਿਣਤੀ    2

#ਜੇ PICO_SDK_ਸੰਸਕਰਣ_MAJOR < 2
__force_inline ਸਥਿਰ bool spin_try_ਤਾਲਾ_unsafe(spin_ਤਾਲਾ_t *ਤਾਲਾ_2) {
   ਵਾਪਸ *ਤਾਲਾ_2;
}
#ਜੇ_ਅੰਤ

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ਅਧਾਰ_Type_t xCoreID,
                                       uint32_t ul_ਤਾਲਾ_ਅੰਕ,
                                       spin_ਤਾਲਾ_t * px_Spin_ਤਾਲਾ,
                                       ਅਧਾਰ_Type_t uxAcquire )
{
    ਸਥਿਰ ਅਸਥਿਰ uint8_t ucOwnedByCore[ ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ ][ਪੋਰਟ_RTOS_SPINLOCK_ਗਿਣਤੀ];
    ਸਥਿਰ ਅਸਥਿਰ uint8_t uc_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ ਪੋਰਟ_RTOS_SPINLOCK_ਗਿਣਤੀ ];

    configASSERT( ul_ਤਾਲਾ_ਅੰਕ < ਪੋਰਟ_RTOS_SPINLOCK_ਗਿਣਤੀ );

    ਜੇ( uxAcquire )
    {
        ਜੇ (!spin_try_ਤਾਲਾ_unsafe(px_Spin_ਤਾਲਾ)) {
            ਜੇ( ucOwnedByCore[ xCoreID ][ ul_ਤਾਲਾ_ਅੰਕ ] )
            {
                configASSERT( uc_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ ul_ਤਾਲਾ_ਅੰਕ ] != 255u );
                uc_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ ul_ਤਾਲਾ_ਅੰਕ ] = uc_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ ul_ਤਾਲਾ_ਅੰਕ ] + 1;
                ਵਾਪਸ;
            }
            spin_ਤਾਲਾ_unsafe_blocking(px_Spin_ਤਾਲਾ);
        }
        configASSERT( uc_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ ul_ਤਾਲਾ_ਅੰਕ ] == 0 );
        uc_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ ul_ਤਾਲਾ_ਅੰਕ ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_ਤਾਲਾ_ਅੰਕ ] = 1;
    }
    ਨਹੀਂਤਾਂ
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_ਤਾਲਾ_ਅੰਕ ] ) != 0 );
        configASSERT( uc_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ ul_ਤਾਲਾ_ਅੰਕ ] != 0 );

        uc_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ ul_ਤਾਲਾ_ਅੰਕ ] = uc_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ ul_ਤਾਲਾ_ਅੰਕ ] - 1;
        ਜੇ ( uc_Recursion_ਗਿਣਤੀ_By_ਤਾਲਾ[ ul_ਤਾਲਾ_ਅੰਕ ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_ਤਾਲਾ_ਅੰਕ ] = 0;
            spin_unlock_unsafe(px_Spin_ਤਾਲਾ);
        }
    }
}

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES == 1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ISR_ਤਾਲਾ( xCoreID )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_ISR_ਤਾਲਾ( xCoreID )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_TASK_ਤਾਲਾ( xCoreID )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_TASK_ਤਾਲਾ( xCoreID )
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ISR_ਤਾਲਾ( xCoreID )         v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( xCoreID ), 0, spin_ਤਾਲਾ_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_ISR_ਤਾਲਾ( xCoreID )     v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( xCoreID ), 0, spin_ਤਾਲਾ_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_TASK_ਤਾਲਾ( xCoreID )        v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( xCoreID ), 1, spin_ਤਾਲਾ_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_TASK_ਤਾਲਾ( xCoreID )    v_ਪੋਰਟ_Recursive_ਤਾਲਾ( ( xCoreID ), 1, spin_ਤਾਲਾ_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#ਜੇ_ਅੰਤ

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਪੋਰਟ_SUPPRESS_TICKS_AND_SLEEP
    ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ਸਮਾਂ );
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_ਸਮਾਂ )    v_ਪੋਰਟ_Suppress_Ticks_And_Sleep( x_Expected_Idle_ਸਮਾਂ )
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()               __asm ਅਸਥਿਰ ( "nop" )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER()    __asm ਅਸਥਿਰ ( "" ::: "memory" )

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
