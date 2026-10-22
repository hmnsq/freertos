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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
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
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE     اوږد

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع int32_t          بنسټ_Type_t;
تعريفنوع uint32_t         UBaseType_t;

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کړه پورټ_ډېری_GROWTH                ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT              8
#تعریف_کړه پورټ_DONT_DISCARD                __attribute__( ( کارول_شوی ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#تعریف_کړه پورټ_USE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#إذا پورټ_USE_DIVIDER_SAVE_RESTORE
    #تعریف_کړه پورټ_ډېری_حد_PADDING     4
#د_که_پای

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
خارجي فراغ v_پورټ_Yield( فراغ );
#تعریف_کړه پورټ_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کړه پورټ_NVIC_PENDSVSET_بټ    ( 1UL << 28UL )
#تعریف_کړه پورټ_YIELD()                v_پورټ_Yield()
#تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_منزل_SCHEDULER();                   \
            پورټ_NVIC_INT_CTRL_REG = پورټ_NVIC_PENDSVSET_بټ; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#تعریف_کړه پورټ_YIELD_FROM_ISR( x )    پورټ_پای_ټکی_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#إذا ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #تعریف_کړه v_پورټ_SVCHandler        isr_svcall
    #تعریف_کړه x_پورټ_Pend_SVHandler     isr_pendsv
    #تعریف_کړه x_پورټ_Sys_Tick_Handler    isr_systick
#د_که_پای

/*-----------------------------------------------------------*/

/* Multi-core */
#تعریف_کړه پورټ_MAX_CORE_شمېر    2

/* Check validity of number of cores specified in config */
#إذا ( config_شمېره_د_CORES < 1 || پورټ_MAX_CORE_شمېر < config_شمېره_د_CORES )
    #تېروتنه "Invalid number of cores specified in config!"
#د_که_پای

#إذا ( configTICK_CORE < 0 || configTICK_CORE > config_شمېره_د_CORES )
    #تېروتنه "Invalid tick core specified in config!"
#د_که_پای
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#إذا config_شمېره_د_CORES == پورټ_MAX_CORE_شمېر
    #تعریف_کړه پورټ_GET_CORE_ID()    get_core_عدد()
#وإلا
    #تعریف_کړه پورټ_GET_CORE_ID()    0
#د_که_پای

#تعریف_کړه پورټ_CHECK_IF_دننه_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm متطاير ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#تعریف_کړه x_پورټ_Is_Inside_مداخله() ((بنسټ_Type_t)پورټ_CHECK_IF_دننه_ISR())

فراغ vYieldCore( صحيح xCoreID );
#تعریف_کړه پورټ_YIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#تعریف_کړه پورټ_CRITICAL_NESTING_دننه_TCB    0

خارجي UBaseType_t uxCriticalNestings[ config_شمېره_د_CORES ];
#تعریف_کړه پورټ_GET_CRITICAL_NESTING_شمېر( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#تعریف_کړه پورټ_سېټ_CRITICAL_NESTING_شمېر( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#تعریف_کړه پورټ_INCREMENT_CRITICAL_NESTING_شمېر( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#تعریف_کړه پورټ_DECREMENT_CRITICAL_NESTING_شمېر( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#تعریف_کړه پورټ_سېټ_مداخله_ماسک()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm متطاير ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm متطاير ( " cpsid i " ::: "memory" );              \
        ulState; } )

#تعریف_کړه پورټ_CLEAR_مداخله_ماسک( ulState )    __asm متطاير ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

خارجي uint32_t ul_سېټ_مداخله_ماسک_From_ISR( فراغ ) __attribute__( ( naked ) );
خارجي فراغ v_Clear_مداخله_ماسک_From_ISR( uint32_t ul_ماسک )  __attribute__( ( naked ) );
#تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()         ul_سېټ_مداخله_ماسک_From_ISR()
#تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( x )    v_Clear_مداخله_ماسک_From_ISR( x )

#تعریف_کړه پورټ_DISABLE_INTERRUPTS()                  __asm متطاير ( " cpsid i " ::: "memory" )
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()                   __asm متطاير ( " cpsie i " ::: "memory" )

#إذا ( config_شمېره_د_CORES == 1 )
    خارجي فراغ v_پورټ_Enter_Critical( فراغ );
    خارجي فراغ v_پورټ_Exit_Critical( فراغ );
    #تعریف_کړه پورټ_ENTER_CRITICAL()    v_پورټ_Enter_Critical()
    #تعریف_کړه پورټ_EXIT_CRITICAL()     v_پورټ_Exit_Critical()
#وإلا
    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_مداخله_حالت );
    #تعریف_کړه پورټ_ENTER_CRITICAL()               vTaskEnterCritical()
    #تعریف_کړه پورټ_EXIT_CRITICAL()                vTaskExitCritical()
    #تعریف_کړه پورټ_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #تعریف_کړه پورټ_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#د_که_پای /* if ( configNUMBER_OF_CORES == 1 ) */

#تعریف_کړه پورټ_RTOS_SPINLOCK_شمېر    2

#إذا PICO_SDK_نسخه_MAJOR < 2
__force_inline ساكن bool spin_try_قلف_unsafe(spin_قلف_t *قلف_2) {
   أرجع *قلف_2;
}
#د_که_پای

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
ساكن مضمن فراغ v_پورټ_Recursive_قلف( بنسټ_Type_t xCoreID,
                                       uint32_t ul_قلف_عدد,
                                       spin_قلف_t * px_Spin_قلف,
                                       بنسټ_Type_t uxAcquire )
{
    ساكن متطاير uint8_t ucOwnedByCore[ پورټ_MAX_CORE_شمېر ][پورټ_RTOS_SPINLOCK_شمېر];
    ساكن متطاير uint8_t uc_Recursion_شمېر_By_قلف[ پورټ_RTOS_SPINLOCK_شمېر ];

    configASSERT( ul_قلف_عدد < پورټ_RTOS_SPINLOCK_شمېر );

    إذا( uxAcquire )
    {
        إذا (!spin_try_قلف_unsafe(px_Spin_قلف)) {
            إذا( ucOwnedByCore[ xCoreID ][ ul_قلف_عدد ] )
            {
                configASSERT( uc_Recursion_شمېر_By_قلف[ ul_قلف_عدد ] != 255u );
                uc_Recursion_شمېر_By_قلف[ ul_قلف_عدد ] = uc_Recursion_شمېر_By_قلف[ ul_قلف_عدد ] + 1;
                أرجع;
            }
            spin_قلف_unsafe_blocking(px_Spin_قلف);
        }
        configASSERT( uc_Recursion_شمېر_By_قلف[ ul_قلف_عدد ] == 0 );
        uc_Recursion_شمېر_By_قلف[ ul_قلف_عدد ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_قلف_عدد ] = 1;
    }
    وإلا
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_قلف_عدد ] ) != 0 );
        configASSERT( uc_Recursion_شمېر_By_قلف[ ul_قلف_عدد ] != 0 );

        uc_Recursion_شمېر_By_قلف[ ul_قلف_عدد ] = uc_Recursion_شمېر_By_قلف[ ul_قلف_عدد ] - 1;
        إذا ( uc_Recursion_شمېر_By_قلف[ ul_قلف_عدد ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_قلف_عدد ] = 0;
            spin_unlock_unsafe(px_Spin_قلف);
        }
    }
}

#إذا ( config_شمېره_د_CORES == 1 )
    #تعریف_کړه پورټ_GET_ISR_قلف( xCoreID )
    #تعریف_کړه پورټ_RELEASE_ISR_قلف( xCoreID )
    #تعریف_کړه پورټ_GET_TASK_قلف( xCoreID )
    #تعریف_کړه پورټ_RELEASE_TASK_قلف( xCoreID )
#وإلا
    #تعریف_کړه پورټ_GET_ISR_قلف( xCoreID )         v_پورټ_Recursive_قلف( ( xCoreID ), 0, spin_قلف_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #تعریف_کړه پورټ_RELEASE_ISR_قلف( xCoreID )     v_پورټ_Recursive_قلف( ( xCoreID ), 0, spin_قلف_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #تعریف_کړه پورټ_GET_TASK_قلف( xCoreID )        v_پورټ_Recursive_قلف( ( xCoreID ), 1, spin_قلف_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #تعریف_کړه پورټ_RELEASE_TASK_قلف( xCoreID )    v_پورټ_Recursive_قلف( ( xCoreID ), 1, spin_قلف_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#د_که_پای

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#که_نه_تعریف_شوی پورټ_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورټ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وخت );
    #تعریف_کړه پورټ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_وخت )    v_پورټ_Suppress_Ticks_And_Sleep( x_Expected_Idle_وخت )
#د_که_پای
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کړه پورټ_NOP()               __asm متطاير ( "nop" )

#تعریف_کړه پورټ_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
