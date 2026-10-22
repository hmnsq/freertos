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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
/* *INDENT-ON* */

#شامل "pico.h"
#شامل "hardware/sync.h"
#شامل "rp2040_config.h"

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
#تعریف_کرو پورٹ_FLOAT         اعشاری
#تعریف_کرو پورٹ_DOUBLE        دوہرا
#تعریف_کرو پورٹ_LONG          طویل
#تعریف_کرو پورٹ_SHORT         مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
#تعریف_کرو پورٹ_بنیاد_TYPE     طویل

قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف int32_t          بنیاد_Type_t;
قسمتعریف uint32_t         UBaseType_t;

#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کرو پورٹ_ڈھیر_GROWTH                ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS              ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT              8
#تعریف_کرو پورٹ_DONT_DISCARD                __attribute__( ( مستعمل ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#تعریف_کرو پورٹ_USE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#اگر پورٹ_USE_DIVIDER_SAVE_RESTORE
    #تعریف_کرو پورٹ_ڈھیر_حد_بندی_PADDING     4
#اگر_ختم

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
خارجی خالی v_پورٹ_Yield( خالی );
#تعریف_کرو پورٹ_NVIC_INT_CTRL_REG     ( *( ( متلون uint32_t * ) 0xe000ed04 ) )
#تعریف_کرو پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ    ( 1UL << 28UL )
#تعریف_کرو پورٹ_YIELD()                v_پورٹ_Yield()
#تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( xSwitchRequired )            \
    کرو                                                      \
    {                                                       \
        اگر( xSwitchRequired )                               \
        {                                                   \
            trace_ISR_EXIT_مقصد_SCHEDULER();                   \
            پورٹ_NVIC_INT_CTRL_REG = پورٹ_NVIC_PENDSVSET_ثنائی_ہندسہ; \
        }                                                   \
        ورنہ                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } جب( 0 )
#تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_انتہا_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#اگر ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #تعریف_کرو v_پورٹ_SVCHandler        isr_svcall
    #تعریف_کرو x_پورٹ_Pend_SVHandler     isr_pendsv
    #تعریف_کرو x_پورٹ_Sys_Tick_Handler    isr_systick
#اگر_ختم

/*-----------------------------------------------------------*/

/* Multi-core */
#تعریف_کرو پورٹ_MAX_CORE_گنتی    2

/* Check validity of number of cores specified in config */
#اگر ( config_نمبر_کا_CORES < 1 || پورٹ_MAX_CORE_گنتی < config_نمبر_کا_CORES )
    #غلطی "Invalid number of cores specified in config!"
#اگر_ختم

#اگر ( configTICK_CORE < 0 || configTICK_CORE > config_نمبر_کا_CORES )
    #غلطی "Invalid tick core specified in config!"
#اگر_ختم
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#اگر config_نمبر_کا_CORES == پورٹ_MAX_CORE_گنتی
    #تعریف_کرو پورٹ_GET_CORE_ID()    get_core_عدد()
#ورنہ
    #تعریف_کرو پورٹ_GET_CORE_ID()    0
#اگر_ختم

#تعریف_کرو پورٹ_CHECK_IF_اندر_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm متلون ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#تعریف_کرو x_پورٹ_Is_Inside_مداخلت() ((بنیاد_Type_t)پورٹ_CHECK_IF_اندر_ISR())

خالی vYieldCore( صحیح xCoreID );
#تعریف_کرو پورٹ_YIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#تعریف_کرو پورٹ_CRITICAL_NESTING_اندر_TCB    0

خارجی UBaseType_t uxCriticalNestings[ config_نمبر_کا_CORES ];
#تعریف_کرو پورٹ_GET_CRITICAL_NESTING_گنتی( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#تعریف_کرو پورٹ_سیٹ_CRITICAL_NESTING_گنتی( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#تعریف_کرو پورٹ_INCREMENT_CRITICAL_NESTING_گنتی( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#تعریف_کرو پورٹ_DECREMENT_CRITICAL_NESTING_گنتی( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm متلون ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm متلون ( " cpsid i " ::: "memory" );              \
        ulState; } )

#تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب( ulState )    __asm متلون ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

خارجی uint32_t ul_سیٹ_مداخلت_نقاب_From_ISR( خالی ) __attribute__( ( naked ) );
خارجی خالی v_Clear_مداخلت_نقاب_From_ISR( uint32_t ul_نقاب )  __attribute__( ( naked ) );
#تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR()         ul_سیٹ_مداخلت_نقاب_From_ISR()
#تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( x )    v_Clear_مداخلت_نقاب_From_ISR( x )

#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  __asm متلون ( " cpsid i " ::: "memory" )
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   __asm متلون ( " cpsie i " ::: "memory" )

#اگر ( config_نمبر_کا_CORES == 1 )
    خارجی خالی v_پورٹ_Enter_Critical( خالی );
    خارجی خالی v_پورٹ_Exit_Critical( خالی );
    #تعریف_کرو پورٹ_ENTER_CRITICAL()    v_پورٹ_Enter_Critical()
    #تعریف_کرو پورٹ_EXIT_CRITICAL()     v_پورٹ_Exit_Critical()
#ورنہ
    خارجی خالی vTaskEnterCritical( خالی );
    خارجی خالی vTaskExitCritical( خالی );
    خارجی UBaseType_t vTaskEnterCriticalFromISR( خالی );
    خارجی خالی vTaskExitCriticalFromISR( UBaseType_t ux_Saved_مداخلت_حالت );
    #تعریف_کرو پورٹ_ENTER_CRITICAL()               vTaskEnterCritical()
    #تعریف_کرو پورٹ_EXIT_CRITICAL()                vTaskExitCritical()
    #تعریف_کرو پورٹ_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #تعریف_کرو پورٹ_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#اگر_ختم /* if ( configNUMBER_OF_CORES == 1 ) */

#تعریف_کرو پورٹ_RTOS_SPINLOCK_گنتی    2

#اگر PICO_SDK_نسخہ_MAJOR < 2
__force_inline ساکن bool spin_try_تالا_unsafe(spin_تالا_t *تالا_3) {
   واپس *تالا_3;
}
#اگر_ختم

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
ساکن اندرونی خالی v_پورٹ_Recursive_تالا( بنیاد_Type_t xCoreID,
                                       uint32_t ul_تالا_عدد,
                                       spin_تالا_t * px_Spin_تالا,
                                       بنیاد_Type_t uxAcquire )
{
    ساکن متلون uint8_t ucOwnedByCore[ پورٹ_MAX_CORE_گنتی ][پورٹ_RTOS_SPINLOCK_گنتی];
    ساکن متلون uint8_t uc_Recursion_گنتی_By_تالا[ پورٹ_RTOS_SPINLOCK_گنتی ];

    configASSERT( ul_تالا_عدد < پورٹ_RTOS_SPINLOCK_گنتی );

    اگر( uxAcquire )
    {
        اگر (!spin_try_تالا_unsafe(px_Spin_تالا)) {
            اگر( ucOwnedByCore[ xCoreID ][ ul_تالا_عدد ] )
            {
                configASSERT( uc_Recursion_گنتی_By_تالا[ ul_تالا_عدد ] != 255u );
                uc_Recursion_گنتی_By_تالا[ ul_تالا_عدد ] = uc_Recursion_گنتی_By_تالا[ ul_تالا_عدد ] + 1;
                واپس;
            }
            spin_تالا_unsafe_blocking(px_Spin_تالا);
        }
        configASSERT( uc_Recursion_گنتی_By_تالا[ ul_تالا_عدد ] == 0 );
        uc_Recursion_گنتی_By_تالا[ ul_تالا_عدد ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_تالا_عدد ] = 1;
    }
    ورنہ
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_تالا_عدد ] ) != 0 );
        configASSERT( uc_Recursion_گنتی_By_تالا[ ul_تالا_عدد ] != 0 );

        uc_Recursion_گنتی_By_تالا[ ul_تالا_عدد ] = uc_Recursion_گنتی_By_تالا[ ul_تالا_عدد ] - 1;
        اگر ( uc_Recursion_گنتی_By_تالا[ ul_تالا_عدد ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_تالا_عدد ] = 0;
            spin_unlock_unsafe(px_Spin_تالا);
        }
    }
}

#اگر ( config_نمبر_کا_CORES == 1 )
    #تعریف_کرو پورٹ_GET_ISR_تالا( xCoreID )
    #تعریف_کرو پورٹ_RELEASE_ISR_تالا( xCoreID )
    #تعریف_کرو پورٹ_GET_TASK_تالا( xCoreID )
    #تعریف_کرو پورٹ_RELEASE_TASK_تالا( xCoreID )
#ورنہ
    #تعریف_کرو پورٹ_GET_ISR_تالا( xCoreID )         v_پورٹ_Recursive_تالا( ( xCoreID ), 0, spin_تالا_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #تعریف_کرو پورٹ_RELEASE_ISR_تالا( xCoreID )     v_پورٹ_Recursive_تالا( ( xCoreID ), 0, spin_تالا_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #تعریف_کرو پورٹ_GET_TASK_تالا( xCoreID )        v_پورٹ_Recursive_تالا( ( xCoreID ), 1, spin_تالا_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #تعریف_کرو پورٹ_RELEASE_TASK_تالا( xCoreID )    v_پورٹ_Recursive_تالا( ( xCoreID ), 1, spin_تالا_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#اگر_ختم

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#اگر_غیر_تعریف_شدہ پورٹ_SUPPRESS_TICKS_AND_SLEEP
    خارجی خالی v_پورٹ_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_وقت );
    #تعریف_کرو پورٹ_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_وقت )    v_پورٹ_Suppress_Ticks_And_Sleep( x_Expected_Idle_وقت )
#اگر_ختم
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

#تعریف_کرو پورٹ_NOP()               __asm متلون ( "nop" )

#تعریف_کرو پورٹ_حافظہ_BARRIER()    __asm متلون ( "" ::: "memory" )

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
