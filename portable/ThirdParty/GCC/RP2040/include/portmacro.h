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

#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
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
#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         عائم
#تعریف_کرو پورٹ_DOUBLE        مزدوج
#تعریف_کرو پورٹ_LONG          لما
#تعریف_کرو پورٹ_SHORT         چھوٹا
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_ادھار_TYPE     لما

تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع int32_t          ادھار_Type_t;
تعريفنوع uint32_t         UBaseType_t;

#إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH                ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT              8
#تعریف_کرو پورٹ_DONT_DISCARD                __attribute__( ( ورتیا ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#تعریف_کرو پورٹ_USE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#إذا پورٹ_USE_DIVIDER_SAVE_RESTORE
    #تعریف_کرو پورٹ_ڈھیر_حد_بندی_PADDING     4
#جے_انت

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
خارجي فراغ v_پورٹ_Yield( فراغ );
#تعریف_کرو پورٹ_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کرو پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ    ( 1UL << 28UL )
#تعریف_کرو پورٹ_YIELD()                v_پورٹ_Yield()
#تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_منزل_SCHEDULER();                   \
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_سرا_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#إذا ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #تعریف_کرو v_پورٹ_SVCHandler        isr_svcall
    #تعریف_کرو x_پورٹ_Pend_SVHandler     isr_pendsv
    #تعریف_کرو x_پورٹ_Sys_Tick_Handler    isr_systick
#جے_انت

/*-----------------------------------------------------------*/

/* Multi-core */
#تعریف_کرو پورٹ_MAX_CORE_گنتی    2

/* Check validity of number of cores specified in config */
#إذا ( config_نمبر_دا_CORES < 1 || پورٹ_MAX_CORE_گنتی < config_نمبر_دا_CORES )
    #غلطی "Invalid number of cores specified in config!"
#جے_انت

#إذا ( configTICK_CORE < 0 || configTICK_CORE > config_نمبر_دا_CORES )
    #غلطی "Invalid tick core specified in config!"
#جے_انت
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#إذا config_نمبر_دا_CORES == پورٹ_MAX_CORE_گنتی
    #تعریف_کرو پورٹ_GET_CORE_ID()    get_core_عدد()
#وإلا
    #تعریف_کرو پورٹ_GET_CORE_ID()    0
#جے_انت

#تعریف_کرو پورٹ_CHECK_IF_وچ_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm متطاير ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#تعریف_کرو x_پورٹ_Is_Inside_رکاوٹ() ((ادھار_Type_t)پورٹ_CHECK_IF_وچ_ISR())

فراغ vYieldCore( صحيح xCoreID );
#تعریف_کرو پورٹ_YIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#تعریف_کرو پورٹ_CRITICAL_NESTING_وچ_TCB    0

خارجي UBaseType_t uxCriticalNestings[ config_نمبر_دا_CORES ];
#تعریف_کرو پورٹ_GET_CRITICAL_NESTING_گنتی( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#تعریف_کرو پورٹ_سیٹ_CRITICAL_NESTING_گنتی( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#تعریف_کرو پورٹ_INCREMENT_CRITICAL_NESTING_گنتی( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#تعریف_کرو پورٹ_DECREMENT_CRITICAL_NESTING_گنتی( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm متطاير ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm متطاير ( " cpsid i " ::: "memory" );              \
        ulState; } )

#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب( ulState )    __asm متطاير ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

خارجي uint32_t ul_سیٹ_رکاوٹ_نقاب_From_ISR( فراغ ) __attribute__( ( naked ) );
خارجي فراغ v_Clear_رکاوٹ_نقاب_From_ISR( uint32_t ul_نقاب )  __attribute__( ( naked ) );
#تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب_FROM_ISR()         ul_سیٹ_رکاوٹ_نقاب_From_ISR()
#تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب_FROM_ISR( x )    v_Clear_رکاوٹ_نقاب_From_ISR( x )

#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  __asm متطاير ( " cpsid i " ::: "memory" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   __asm متطاير ( " cpsie i " ::: "memory" )

#إذا ( config_نمبر_دا_CORES == 1 )
    خارجي فراغ v_پورٹ_Enter_Critical( فراغ );
    خارجي فراغ v_پورٹ_Exit_Critical( فراغ );
    #تعریف_کرو پورٹ_ENTER_CRITICAL()    v_پورٹ_Enter_Critical()
    #تعریف_کرو پورٹ_EXIT_CRITICAL()     v_پورٹ_Exit_Critical()
#وإلا
    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_رکاوٹ_حالت );
    #تعریف_کرو پورٹ_ENTER_CRITICAL()               vTaskEnterCritical()
    #تعریف_کرو پورٹ_EXIT_CRITICAL()                vTaskExitCritical()
    #تعریف_کرو پورٹ_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #تعریف_کرو پورٹ_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#جے_انت /* if ( configNUMBER_OF_CORES == 1 ) */

#تعریف_کرو پورٹ_RTOS_SPINLOCK_گنتی    2

#إذا PICO_SDK_نسخہ_MAJOR < 2
__force_inline ساكن bool spin_try_جندرا_unsafe(spin_جندرا_t *جندرا_2) {
   أرجع *جندرا_2;
}
#جے_انت

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
ساكن مضمن فراغ v_پورٹ_Recursive_جندرا( ادھار_Type_t xCoreID,
                                       uint32_t ul_جندرا_عدد,
                                       spin_جندرا_t * px_Spin_جندرا,
                                       ادھار_Type_t uxAcquire )
{
    ساكن متطاير uint8_t ucOwnedByCore[ پورٹ_MAX_CORE_گنتی ][پورٹ_RTOS_SPINLOCK_گنتی];
    ساكن متطاير uint8_t uc_Recursion_گنتی_By_جندرا[ پورٹ_RTOS_SPINLOCK_گنتی ];

    configASSERT( ul_جندرا_عدد < پورٹ_RTOS_SPINLOCK_گنتی );

    إذا( uxAcquire )
    {
        إذا (!spin_try_جندرا_unsafe(px_Spin_جندرا)) {
            إذا( ucOwnedByCore[ xCoreID ][ ul_جندرا_عدد ] )
            {
                configASSERT( uc_Recursion_گنتی_By_جندرا[ ul_جندرا_عدد ] != 255u );
                uc_Recursion_گنتی_By_جندرا[ ul_جندرا_عدد ] = uc_Recursion_گنتی_By_جندرا[ ul_جندرا_عدد ] + 1;
                أرجع;
            }
            spin_جندرا_unsafe_blocking(px_Spin_جندرا);
        }
        configASSERT( uc_Recursion_گنتی_By_جندرا[ ul_جندرا_عدد ] == 0 );
        uc_Recursion_گنتی_By_جندرا[ ul_جندرا_عدد ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_جندرا_عدد ] = 1;
    }
    وإلا
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_جندرا_عدد ] ) != 0 );
        configASSERT( uc_Recursion_گنتی_By_جندرا[ ul_جندرا_عدد ] != 0 );

        uc_Recursion_گنتی_By_جندرا[ ul_جندرا_عدد ] = uc_Recursion_گنتی_By_جندرا[ ul_جندرا_عدد ] - 1;
        إذا ( uc_Recursion_گنتی_By_جندرا[ ul_جندرا_عدد ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_جندرا_عدد ] = 0;
            spin_unlock_unsafe(px_Spin_جندرا);
        }
    }
}

#إذا ( config_نمبر_دا_CORES == 1 )
    #تعریف_کرو پورٹ_GET_ISR_جندرا( xCoreID )
    #تعریف_کرو پورٹ_RELEASE_ISR_جندرا( xCoreID )
    #تعریف_کرو پورٹ_GET_TASK_جندرا( xCoreID )
    #تعریف_کرو پورٹ_RELEASE_TASK_جندرا( xCoreID )
#وإلا
    #تعریف_کرو پورٹ_GET_ISR_جندرا( xCoreID )         v_پورٹ_Recursive_جندرا( ( xCoreID ), 0, spin_جندرا_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #تعریف_کرو پورٹ_RELEASE_ISR_جندرا( xCoreID )     v_پورٹ_Recursive_جندرا( ( xCoreID ), 0, spin_جندرا_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #تعریف_کرو پورٹ_GET_TASK_جندرا( xCoreID )        v_پورٹ_Recursive_جندرا( ( xCoreID ), 1, spin_جندرا_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #تعریف_کرو پورٹ_RELEASE_TASK_جندرا( xCoreID )    v_پورٹ_Recursive_جندرا( ( xCoreID ), 1, spin_جندرا_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#جے_انت

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#جے_بنا_تعریف پورٹ_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ویلا );
    #تعریف_کرو پورٹ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_ویلا )    v_پورٹ_Suppress_Ticks_And_Sleep( x_Expected_Idle_ویلا )
#جے_انت
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کرو پورٹ_NOP()               __asm متطاير ( "nop" )

#تعریف_کرو پورٹ_حافظہ_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* PORTMACRO_H */
