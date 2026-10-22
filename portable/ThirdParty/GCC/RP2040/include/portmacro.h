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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಅನ್ತರ್ಭಾವ "pico.h"
#ಅನ್ತರ್ಭಾವ "hardware/sync.h"
#ಅನ್ತರ್ಭಾವ "rp2040_config.h"

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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR          ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT         ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE        ದ್ವಿಗುಣ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG          ದೀರ್ಘ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT         ಗಿಡ್ಡ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE    uint32_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE     ದೀರ್ಘ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int32_t          ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t         UBaseType_t;

#ಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t     TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY              ( TickType_t ) 0xffff
#ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t     TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC    1
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು ಗಣ ಗಮ್ಯ unsupported tick type ಅಗಲ.
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH                ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT              8
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DONT_DISCARD                __attribute__( ( ಬಳಸಿದ ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_USE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#ಆದರೆ ಪೋರ್ಟ್_USE_DIVIDER_SAVE_RESTORE
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_ಎಲ್ಲೆ_PADDING     4
#ಆದರೆ_ಅಂತ್ಯ

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ );
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_INT_CTRL_REG     ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed04 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್    ( 1UL << 28UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()                v_ಪೋರ್ಟ್_Yield()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( xSwitchRequired )            \
    ಮಾಡು                                                      \
    {                                                       \
        ಆದರೆ( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();                   \
            ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್; \
        }                                                   \
        ಇಲ್ಲದಿದ್ದರೆ                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } ಆಗ( 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )    ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#ಆದರೆ ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #ವ್ಯಾಖ್ಯಾನಿಸು v_ಪೋರ್ಟ್_SVCHandler        isr_svcall
    #ವ್ಯಾಖ್ಯಾನಿಸು x_ಪೋರ್ಟ್_Pend_SVHandler     isr_pendsv
    #ವ್ಯಾಖ್ಯಾನಿಸು x_ಪೋರ್ಟ್_Sys_Tick_Handler    isr_systick
#ಆದರೆ_ಅಂತ್ಯ

/*-----------------------------------------------------------*/

/* Multi-core */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ    2

/* Check validity of number of cores specified in config */
#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES < 1 || ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ < config_ಸಂಖ್ಯೆ_ದ_CORES )
    #ದೋಷ "Invalid number of cores specified in config!"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ ( configTICK_CORE < 0 || configTICK_CORE > config_ಸಂಖ್ಯೆ_ದ_CORES )
    #ದೋಷ "Invalid tick core specified in config!"
#ಆದರೆ_ಅಂತ್ಯ
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#ಆದರೆ config_ಸಂಖ್ಯೆ_ದ_CORES == ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_CORE_ID()    get_core_ಅಂಕೆ()
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_CORE_ID()    0
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHECK_IF_ಒಳ_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm ಅಸ್ಥಿರ ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#ವ್ಯಾಖ್ಯಾನಿಸು x_ಪೋರ್ಟ್_Is_Inside_ಅಡಚಣೆ() ((ತಳ_Type_t)ಪೋರ್ಟ್_CHECK_IF_ಒಳ_ISR())

ಶೂನ್ಯ vYieldCore( ಪೂರ್ಣಾಂಕ xCoreID );
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CRITICAL_NESTING_ಒಳ_TCB    0

ಬಾಹ್ಯ UBaseType_t uxCriticalNestings[ config_ಸಂಖ್ಯೆ_ದ_CORES ];
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INCREMENT_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DECREMENT_CRITICAL_NESTING_ಎಣಿಕೆ( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm ಅಸ್ಥಿರ ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm ಅಸ್ಥಿರ ( " cpsid i " ::: "memory" );              \
        ulState; } )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ( ulState )    __asm ಅಸ್ಥಿರ ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

ಬಾಹ್ಯ uint32_t ul_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( ಶೂನ್ಯ ) __attribute__( ( naked ) );
ಬಾಹ್ಯ ಶೂನ್ಯ v_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( uint32_t ul_ಮುಖವಾಡ )  __attribute__( ( naked ) );
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR()         ul_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x )    v_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( x )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()                  __asm ಅಸ್ಥಿರ ( " cpsid i " ::: "memory" )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()                   __asm ಅಸ್ಥಿರ ( " cpsie i " ::: "memory" )

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()    v_ಪೋರ್ಟ್_Enter_Critical()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()     v_ಪೋರ್ಟ್_Exit_Critical()
#ಇಲ್ಲದಿದ್ದರೆ
    ಬಾಹ್ಯ ಶೂನ್ಯ vTaskEnterCritical( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ vTaskExitCritical( ಶೂನ್ಯ );
    ಬಾಹ್ಯ UBaseType_t vTaskEnterCriticalFromISR( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()               vTaskEnterCritical()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                vTaskExitCritical()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES == 1 ) */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RTOS_SPINLOCK_ಎಣಿಕೆ    2

#ಆದರೆ PICO_SDK_ಆವೃತ್ತಿ_MAJOR < 2
__force_inline ಸ್ಥಿರ bool spin_try_ಬೀಗ_unsafe(spin_ಬೀಗ_t *ಬೀಗ_3) {
   ಹಿಂತಿರುಗಿ *ಬೀಗ_3;
}
#ಆದರೆ_ಅಂತ್ಯ

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ತಳ_Type_t xCoreID,
                                       uint32_t ul_ಬೀಗ_ಅಂಕೆ,
                                       spin_ಬೀಗ_t * px_Spin_ಬೀಗ,
                                       ತಳ_Type_t uxAcquire )
{
    ಸ್ಥಿರ ಅಸ್ಥಿರ uint8_t ucOwnedByCore[ ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ ][ಪೋರ್ಟ್_RTOS_SPINLOCK_ಎಣಿಕೆ];
    ಸ್ಥಿರ ಅಸ್ಥಿರ uint8_t uc_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ ಪೋರ್ಟ್_RTOS_SPINLOCK_ಎಣಿಕೆ ];

    configASSERT( ul_ಬೀಗ_ಅಂಕೆ < ಪೋರ್ಟ್_RTOS_SPINLOCK_ಎಣಿಕೆ );

    ಆದರೆ( uxAcquire )
    {
        ಆದರೆ (!spin_try_ಬೀಗ_unsafe(px_Spin_ಬೀಗ)) {
            ಆದರೆ( ucOwnedByCore[ xCoreID ][ ul_ಬೀಗ_ಅಂಕೆ ] )
            {
                configASSERT( uc_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ ul_ಬೀಗ_ಅಂಕೆ ] != 255u );
                uc_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ ul_ಬೀಗ_ಅಂಕೆ ] = uc_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ ul_ಬೀಗ_ಅಂಕೆ ] + 1;
                ಹಿಂತಿರುಗಿ;
            }
            spin_ಬೀಗ_unsafe_blocking(px_Spin_ಬೀಗ);
        }
        configASSERT( uc_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ ul_ಬೀಗ_ಅಂಕೆ ] == 0 );
        uc_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ ul_ಬೀಗ_ಅಂಕೆ ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_ಬೀಗ_ಅಂಕೆ ] = 1;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_ಬೀಗ_ಅಂಕೆ ] ) != 0 );
        configASSERT( uc_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ ul_ಬೀಗ_ಅಂಕೆ ] != 0 );

        uc_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ ul_ಬೀಗ_ಅಂಕೆ ] = uc_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ ul_ಬೀಗ_ಅಂಕೆ ] - 1;
        ಆದರೆ ( uc_Recursion_ಎಣಿಕೆ_By_ಬೀಗ[ ul_ಬೀಗ_ಅಂಕೆ ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_ಬೀಗ_ಅಂಕೆ ] = 0;
            spin_unlock_unsafe(px_Spin_ಬೀಗ);
        }
    }
}

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ISR_ಬೀಗ( xCoreID )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_ISR_ಬೀಗ( xCoreID )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_TASK_ಬೀಗ( xCoreID )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_TASK_ಬೀಗ( xCoreID )
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ISR_ಬೀಗ( xCoreID )         v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( xCoreID ), 0, spin_ಬೀಗ_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_ISR_ಬೀಗ( xCoreID )     v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( xCoreID ), 0, spin_ಬೀಗ_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_TASK_ಬೀಗ( xCoreID )        v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( xCoreID ), 1, spin_ಬೀಗ_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_TASK_ಬೀಗ( xCoreID )    v_ಪೋರ್ಟ್_Recursive_ಬೀಗ( ( xCoreID ), 1, spin_ಬೀಗ_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#ಆದರೆ_ಅಂತ್ಯ

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_SUPPRESS_TICKS_AND_SLEEP
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ಸಮಯ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_ಸಮಯ )    v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( x_Expected_Idle_ಸಮಯ )
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()               __asm ಅಸ್ಥಿರ ( "nop" )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER()    __asm ಅಸ್ಥಿರ ( "" ::: "memory" )

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
