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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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
#تعریف_کن پورت_CHAR          حرف
#تعریف_کن پورت_FLOAT         عائم
#تعریف_کن پورت_DOUBLE        مزدوج
#تعریف_کن پورت_LONG          دراز
#تعریف_کن پورت_SHORT         کوتاه
#تعریف_کن پورت_پشته_TYPE    uint32_t
#تعریف_کن پورت_پایه_TYPE     دراز

تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع int32_t          پایه_Type_t;
تعريفنوع uint32_t         UBaseType_t;

#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کن پورت_پشته_GROWTH                ( -1 )
#تعریف_کن پورت_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
#تعریف_کن پورت_BYTE_ALIGNMENT              8
#تعریف_کن پورت_DONT_DISCARD                __attribute__( ( استفاده_شده ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#تعریف_کن پورت_USE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#إذا پورت_USE_DIVIDER_SAVE_RESTORE
    #تعریف_کن پورت_پشته_حد_PADDING     4
#پایان_اگر

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
خارجي فراغ v_پورت_Yield( فراغ );
#تعریف_کن پورت_NVIC_INT_CTRL_REG     ( *( ( متطاير uint32_t * ) 0xe000ed04 ) )
#تعریف_کن پورت_NVIC_PENDSVSET_بیت    ( 1UL << 28UL )
#تعریف_کن پورت_YIELD()                v_پورت_Yield()
#تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired )            \
    افعل                                                      \
    {                                                       \
        إذا( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_مقصد_SCHEDULER();                   \
            پورت_NVIC_INT_CTRL_REG = پورت_NVIC_PENDSVSET_بیت; \
        }                                                   \
        وإلا                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } طالما( 0 )
#تعریف_کن پورت_YIELD_FROM_ISR( x )    پورت_انتها_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#إذا ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #تعریف_کن v_پورت_SVCHandler        isr_svcall
    #تعریف_کن x_پورت_Pend_SVHandler     isr_pendsv
    #تعریف_کن x_پورت_Sys_Tick_Handler    isr_systick
#پایان_اگر

/*-----------------------------------------------------------*/

/* Multi-core */
#تعریف_کن پورت_MAX_CORE_شمار    2

/* Check validity of number of cores specified in config */
#إذا ( config_عدد_از_CORES < 1 || پورت_MAX_CORE_شمار < config_عدد_از_CORES )
    #خطا "Invalid number of cores specified in config!"
#پایان_اگر

#إذا ( configTICK_CORE < 0 || configTICK_CORE > config_عدد_از_CORES )
    #خطا "Invalid tick core specified in config!"
#پایان_اگر
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#إذا config_عدد_از_CORES == پورت_MAX_CORE_شمار
    #تعریف_کن پورت_GET_CORE_ID()    get_core_رقم()
#وإلا
    #تعریف_کن پورت_GET_CORE_ID()    0
#پایان_اگر

#تعریف_کن پورت_CHECK_IF_درون_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm متطاير ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#تعریف_کن x_پورت_Is_Inside_وقفه() ((پایه_Type_t)پورت_CHECK_IF_درون_ISR())

فراغ vYieldCore( صحيح xCoreID );
#تعریف_کن پورت_YIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#تعریف_کن پورت_CRITICAL_NESTING_درون_TCB    0

خارجي UBaseType_t uxCriticalNestings[ config_عدد_از_CORES ];
#تعریف_کن پورت_GET_CRITICAL_NESTING_شمار( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#تعریف_کن پورت_مجموعه_CRITICAL_NESTING_شمار( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#تعریف_کن پورت_INCREMENT_CRITICAL_NESTING_شمار( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#تعریف_کن پورت_DECREMENT_CRITICAL_NESTING_شمار( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#تعریف_کن پورت_مجموعه_وقفه_ماسک()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm متطاير ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm متطاير ( " cpsid i " ::: "memory" );              \
        ulState; } )

#تعریف_کن پورت_CLEAR_وقفه_ماسک( ulState )    __asm متطاير ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

خارجي uint32_t ul_مجموعه_وقفه_ماسک_From_ISR( فراغ ) __attribute__( ( naked ) );
خارجي فراغ v_Clear_وقفه_ماسک_From_ISR( uint32_t ul_ماسک )  __attribute__( ( naked ) );
#تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()         ul_مجموعه_وقفه_ماسک_From_ISR()
#تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( x )    v_Clear_وقفه_ماسک_From_ISR( x )

#تعریف_کن پورت_DISABLE_INTERRUPTS()                  __asm متطاير ( " cpsid i " ::: "memory" )
#تعریف_کن پورت_ENABLE_INTERRUPTS()                   __asm متطاير ( " cpsie i " ::: "memory" )

#إذا ( config_عدد_از_CORES == 1 )
    خارجي فراغ v_پورت_Enter_Critical( فراغ );
    خارجي فراغ v_پورت_Exit_Critical( فراغ );
    #تعریف_کن پورت_ENTER_CRITICAL()    v_پورت_Enter_Critical()
    #تعریف_کن پورت_EXIT_CRITICAL()     v_پورت_Exit_Critical()
#وإلا
    خارجي فراغ vTaskEnterCritical( فراغ );
    خارجي فراغ vTaskExitCritical( فراغ );
    خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
    خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_وقفه_وضعیت );
    #تعریف_کن پورت_ENTER_CRITICAL()               vTaskEnterCritical()
    #تعریف_کن پورت_EXIT_CRITICAL()                vTaskExitCritical()
    #تعریف_کن پورت_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #تعریف_کن پورت_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#پایان_اگر /* if ( configNUMBER_OF_CORES == 1 ) */

#تعریف_کن پورت_RTOS_SPINLOCK_شمار    2

#إذا PICO_SDK_نسخه_MAJOR < 2
__force_inline ساكن bool spin_try_قفل_unsafe(spin_قفل_t *قفل_3) {
   أرجع *قفل_3;
}
#پایان_اگر

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
ساكن مضمن فراغ v_پورت_Recursive_قفل( پایه_Type_t xCoreID,
                                       uint32_t ul_قفل_رقم,
                                       spin_قفل_t * px_Spin_قفل,
                                       پایه_Type_t uxAcquire )
{
    ساكن متطاير uint8_t ucOwnedByCore[ پورت_MAX_CORE_شمار ][پورت_RTOS_SPINLOCK_شمار];
    ساكن متطاير uint8_t uc_Recursion_شمار_By_قفل[ پورت_RTOS_SPINLOCK_شمار ];

    configASSERT( ul_قفل_رقم < پورت_RTOS_SPINLOCK_شمار );

    إذا( uxAcquire )
    {
        إذا (!spin_try_قفل_unsafe(px_Spin_قفل)) {
            إذا( ucOwnedByCore[ xCoreID ][ ul_قفل_رقم ] )
            {
                configASSERT( uc_Recursion_شمار_By_قفل[ ul_قفل_رقم ] != 255u );
                uc_Recursion_شمار_By_قفل[ ul_قفل_رقم ] = uc_Recursion_شمار_By_قفل[ ul_قفل_رقم ] + 1;
                أرجع;
            }
            spin_قفل_unsafe_blocking(px_Spin_قفل);
        }
        configASSERT( uc_Recursion_شمار_By_قفل[ ul_قفل_رقم ] == 0 );
        uc_Recursion_شمار_By_قفل[ ul_قفل_رقم ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_قفل_رقم ] = 1;
    }
    وإلا
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_قفل_رقم ] ) != 0 );
        configASSERT( uc_Recursion_شمار_By_قفل[ ul_قفل_رقم ] != 0 );

        uc_Recursion_شمار_By_قفل[ ul_قفل_رقم ] = uc_Recursion_شمار_By_قفل[ ul_قفل_رقم ] - 1;
        إذا ( uc_Recursion_شمار_By_قفل[ ul_قفل_رقم ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_قفل_رقم ] = 0;
            spin_unlock_unsafe(px_Spin_قفل);
        }
    }
}

#إذا ( config_عدد_از_CORES == 1 )
    #تعریف_کن پورت_GET_ISR_قفل( xCoreID )
    #تعریف_کن پورت_RELEASE_ISR_قفل( xCoreID )
    #تعریف_کن پورت_GET_TASK_قفل( xCoreID )
    #تعریف_کن پورت_RELEASE_TASK_قفل( xCoreID )
#وإلا
    #تعریف_کن پورت_GET_ISR_قفل( xCoreID )         v_پورت_Recursive_قفل( ( xCoreID ), 0, spin_قفل_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #تعریف_کن پورت_RELEASE_ISR_قفل( xCoreID )     v_پورت_Recursive_قفل( ( xCoreID ), 0, spin_قفل_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #تعریف_کن پورت_GET_TASK_قفل( xCoreID )        v_پورت_Recursive_قفل( ( xCoreID ), 1, spin_قفل_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #تعریف_کن پورت_RELEASE_TASK_قفل( xCoreID )    v_پورت_Recursive_قفل( ( xCoreID ), 1, spin_قفل_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#پایان_اگر

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#اگر_تعریف_نشده پورت_SUPPRESS_TICKS_AND_SLEEP
    خارجي فراغ v_پورت_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_زمان );
    #تعریف_کن پورت_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_زمان )    v_پورت_Suppress_Ticks_And_Sleep( x_Expected_Idle_زمان )
#پایان_اگر
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#تعریف_کن پورت_NOP()               __asm متطاير ( "nop" )

#تعریف_کن پورت_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
