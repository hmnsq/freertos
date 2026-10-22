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

#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    வெளி "C" {
#endif
/* *INDENT-ON* */

#அந்தர்பாவ "pico.h"
#அந்தர்பாவ "hardware/sync.h"
#அந்தர்பாவ "rp2040_config.h"

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
#define portCHAR          எழுத்து
#define portFLOAT         தசம
#define portDOUBLE        இரட்டை
#define portLONG          long
#define portSHORT         short
#define port_அடுக்கு_TYPE    uint32_t
#define portBASE_TYPE     long

வகைவரை port_அடுக்கு_TYPE   அடுக்கு_Type_t;
வகைவரை int32_t          BaseType_t;
வகைவரை uint32_t         UBaseType_t;

#எனில் ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    வகைவரை uint16_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#அல்லதெனில் ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    வகைவரை uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#இல்லையெனில்
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_அடுக்கு_GROWTH                ( -1 )
#define portTICK_PERIOD_MS              ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT              8
#define portDONT_DISCARD                __attribute__( ( used ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#define portUSE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#எனில் portUSE_DIVIDER_SAVE_RESTORE
    #define port_அடுக்கு_LIMIT_PADDING     4
#endif

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
வெளி வெறுமை vPortYield( வெறுமை );
#define portNVIC_INT_CTRL_REG     ( *( ( நிலையற்ற uint32_t * ) 0xe000ed04 ) )
#define portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#define portYIELD()                vPortYield()
#define portEND_SWITCHING_ISR( xSwitchRequired )            \
    செய்                                                      \
    {                                                       \
        எனில்( xSwitchRequired )                               \
        {                                                   \
            traceISR_EXIT_TO_SCHEDULER();                   \
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
        }                                                   \
        இல்லையெனில்                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } போது( 0 )
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#எனில் ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #define vPortSVCHandler        isr_svcall
    #define xPortPendSVHandler     isr_pendsv
    #define xPortSysTickHandler    isr_systick
#endif

/*-----------------------------------------------------------*/

/* Multi-core */
#define port_MAX_CORE_மொத்தம்    2

/* Check validity of number of cores specified in config */
#எனில் ( config_எண்_OF_CORES < 1 || port_MAX_CORE_மொத்தம் < config_எண்_OF_CORES )
    #error "Invalid number of cores specified in config!"
#endif

#எனில் ( configTICK_CORE < 0 || configTICK_CORE > config_எண்_OF_CORES )
    #error "Invalid tick core specified in config!"
#endif
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#எனில் config_எண்_OF_CORES == port_MAX_CORE_மொத்தம்
    #define portGET_CORE_ID()    get_core_இலக்கம்()
#இல்லையெனில்
    #define portGET_CORE_ID()    0
#endif

#define portCHECK_IF_IN_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm நிலையற்ற ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#define xPortIsInsideInterrupt() ((BaseType_t)portCHECK_IF_IN_ISR())

வெறுமை vYieldCore( முழு xCoreID );
#define portYIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#define portCRITICAL_NESTING_IN_TCB    0

வெளி UBaseType_t uxCriticalNestings[ config_எண்_OF_CORES ];
#define port_GET_CRITICAL_NESTING_மொத்தம்( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#define port_SET_CRITICAL_NESTING_மொத்தம்( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#define port_INCREMENT_CRITICAL_NESTING_மொத்தம்( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#define port_DECREMENT_CRITICAL_NESTING_மொத்தம்( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#define portSET_INTERRUPT_MASK()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm நிலையற்ற ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm நிலையற்ற ( " cpsid i " ::: "memory" );              \
        ulState; } )

#define portCLEAR_INTERRUPT_MASK( ulState )    __asm நிலையற்ற ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

வெளி uint32_t ulSetInterruptMaskFromISR( வெறுமை ) __attribute__( ( naked ) );
வெளி வெறுமை vClearInterruptMaskFromISR( uint32_t ulMask )  __attribute__( ( naked ) );
#define portSET_INTERRUPT_MASK_FROM_ISR()         ulSetInterruptMaskFromISR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vClearInterruptMaskFromISR( x )

#define portDISABLE_INTERRUPTS()                  __asm நிலையற்ற ( " cpsid i " ::: "memory" )
#define portENABLE_INTERRUPTS()                   __asm நிலையற்ற ( " cpsie i " ::: "memory" )

#எனில் ( config_எண்_OF_CORES == 1 )
    வெளி வெறுமை vPortEnterCritical( வெறுமை );
    வெளி வெறுமை vPortExitCritical( வெறுமை );
    #define portENTER_CRITICAL()    vPortEnterCritical()
    #define portEXIT_CRITICAL()     vPortExitCritical()
#இல்லையெனில்
    வெளி வெறுமை vTaskEnterCritical( வெறுமை );
    வெளி வெறுமை vTaskExitCritical( வெறுமை );
    வெளி UBaseType_t vTaskEnterCriticalFromISR( வெறுமை );
    வெளி வெறுமை vTaskExitCriticalFromISR( UBaseType_t uxSavedInterruptStatus );
    #define portENTER_CRITICAL()               vTaskEnterCritical()
    #define portEXIT_CRITICAL()                vTaskExitCritical()
    #define portENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #define portEXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#endif /* if ( configNUMBER_OF_CORES == 1 ) */

#define port_RTOS_SPINLOCK_மொத்தம்    2

#எனில் PICO_SDK_VERSION_MAJOR < 2
__force_inline நிலையான bool spin_try_lock_unsafe(spin_lock_t *lock) {
   திரும்பு *lock;
}
#endif

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
நிலையான உள்வரி வெறுமை vPortRecursiveLock( BaseType_t xCoreID,
                                       uint32_t ul_Lock_இலக்கம்,
                                       spin_lock_t * pxSpinLock,
                                       BaseType_t uxAcquire )
{
    நிலையான நிலையற்ற uint8_t ucOwnedByCore[ port_MAX_CORE_மொத்தம் ][port_RTOS_SPINLOCK_மொத்தம்];
    நிலையான நிலையற்ற uint8_t uc_Recursion_மொத்தம்_By_Lock[ port_RTOS_SPINLOCK_மொத்தம் ];

    configASSERT( ul_Lock_இலக்கம் < port_RTOS_SPINLOCK_மொத்தம் );

    எனில்( uxAcquire )
    {
        எனில் (!spin_try_lock_unsafe(pxSpinLock)) {
            எனில்( ucOwnedByCore[ xCoreID ][ ul_Lock_இலக்கம் ] )
            {
                configASSERT( uc_Recursion_மொத்தம்_By_Lock[ ul_Lock_இலக்கம் ] != 255u );
                uc_Recursion_மொத்தம்_By_Lock[ ul_Lock_இலக்கம் ] = uc_Recursion_மொத்தம்_By_Lock[ ul_Lock_இலக்கம் ] + 1;
                திரும்பு;
            }
            spin_lock_unsafe_blocking(pxSpinLock);
        }
        configASSERT( uc_Recursion_மொத்தம்_By_Lock[ ul_Lock_இலக்கம் ] == 0 );
        uc_Recursion_மொத்தம்_By_Lock[ ul_Lock_இலக்கம் ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_Lock_இலக்கம் ] = 1;
    }
    இல்லையெனில்
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_Lock_இலக்கம் ] ) != 0 );
        configASSERT( uc_Recursion_மொத்தம்_By_Lock[ ul_Lock_இலக்கம் ] != 0 );

        uc_Recursion_மொத்தம்_By_Lock[ ul_Lock_இலக்கம் ] = uc_Recursion_மொத்தம்_By_Lock[ ul_Lock_இலக்கம் ] - 1;
        எனில் ( uc_Recursion_மொத்தம்_By_Lock[ ul_Lock_இலக்கம் ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_Lock_இலக்கம் ] = 0;
            spin_unlock_unsafe(pxSpinLock);
        }
    }
}

#எனில் ( config_எண்_OF_CORES == 1 )
    #define portGET_ISR_LOCK( xCoreID )
    #define portRELEASE_ISR_LOCK( xCoreID )
    #define portGET_TASK_LOCK( xCoreID )
    #define portRELEASE_TASK_LOCK( xCoreID )
#இல்லையெனில்
    #define portGET_ISR_LOCK( xCoreID )         vPortRecursiveLock( ( xCoreID ), 0, spin_lock_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #define portRELEASE_ISR_LOCK( xCoreID )     vPortRecursiveLock( ( xCoreID ), 0, spin_lock_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #define portGET_TASK_LOCK( xCoreID )        vPortRecursiveLock( ( xCoreID ), 1, spin_lock_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #define portRELEASE_TASK_LOCK( xCoreID )    vPortRecursiveLock( ( xCoreID ), 1, spin_lock_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#endif

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
    வெளி வெறுமை vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#endif
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    வெறுமை vFunction( வெறுமை * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          வெறுமை vFunction( வெறுமை * pvParameters )

#define portNOP()               __asm நிலையற்ற ( "nop" )

#define portMEMORY_BARRIER()    __asm நிலையற்ற ( "" ::: "memory" )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
