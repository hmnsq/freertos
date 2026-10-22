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
    ବାହ୍ୟ "C" {
#endif
/* *INDENT-ON* */

#ଅନ୍ତର୍ଭାଵ "pico.h"
#ଅନ୍ତର୍ଭାଵ "hardware/sync.h"
#ଅନ୍ତର୍ଭାଵ "rp2040_config.h"

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
#define portCHAR          ଅକ୍ଷର
#define portFLOAT         ଦଶମିକ
#define portDOUBLE        ଦ୍ୱିଗୁଣ
#define portLONG          long
#define portSHORT         short
#define port_ଗଦା_TYPE    uint32_t
#define portBASE_TYPE     long

ପ୍ରକାରବ୍ୟାଖ୍ୟା port_ଗଦା_TYPE   ଗଦା_Type_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା int32_t          BaseType_t;
ପ୍ରକାରବ୍ୟାଖ୍ୟା uint32_t         UBaseType_t;

#ଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    ପ୍ରକାରବ୍ୟାଖ୍ୟା uint16_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#ନଚେତଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    ପ୍ରକାରବ୍ୟାଖ୍ୟା uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#ଅନ୍ୟଥା
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_ଗଦା_GROWTH                ( -1 )
#define portTICK_PERIOD_MS              ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT              8
#define portDONT_DISCARD                __attribute__( ( used ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#define portUSE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#ଯଦି portUSE_DIVIDER_SAVE_RESTORE
    #define port_ଗଦା_LIMIT_PADDING     4
#endif

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
ବାହ୍ୟ ଶୂନ୍ୟ vPortYield( ଶୂନ୍ୟ );
#define portNVIC_INT_CTRL_REG     ( *( ( ଅସ୍ଥିର uint32_t * ) 0xe000ed04 ) )
#define portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#define portYIELD()                vPortYield()
#define portEND_SWITCHING_ISR( xSwitchRequired )            \
    କର                                                      \
    {                                                       \
        ଯଦି( xSwitchRequired )                               \
        {                                                   \
            traceISR_EXIT_TO_SCHEDULER();                   \
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
        }                                                   \
        ଅନ୍ୟଥା                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } ଯେତେବେଳେ( 0 )
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#ଯଦି ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #define vPortSVCHandler        isr_svcall
    #define xPortPendSVHandler     isr_pendsv
    #define xPortSysTickHandler    isr_systick
#endif

/*-----------------------------------------------------------*/

/* Multi-core */
#define port_MAX_CORE_ଗଣନା    2

/* Check validity of number of cores specified in config */
#ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES < 1 || port_MAX_CORE_ଗଣନା < config_ସଂଖ୍ୟା_OF_CORES )
    #error "Invalid number of cores specified in config!"
#endif

#ଯଦି ( configTICK_CORE < 0 || configTICK_CORE > config_ସଂଖ୍ୟା_OF_CORES )
    #error "Invalid tick core specified in config!"
#endif
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#ଯଦି config_ସଂଖ୍ୟା_OF_CORES == port_MAX_CORE_ଗଣନା
    #define portGET_CORE_ID()    get_core_ଅଙ୍କ()
#ଅନ୍ୟଥା
    #define portGET_CORE_ID()    0
#endif

#define portCHECK_IF_IN_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm ଅସ୍ଥିର ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#define xPortIsInsideInterrupt() ((BaseType_t)portCHECK_IF_IN_ISR())

ଶୂନ୍ୟ vYieldCore( ପୂର୍ଣ୍ଣସଂଖ୍ୟା xCoreID );
#define portYIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#define portCRITICAL_NESTING_IN_TCB    0

ବାହ୍ୟ UBaseType_t uxCriticalNestings[ config_ସଂଖ୍ୟା_OF_CORES ];
#define port_GET_CRITICAL_NESTING_ଗଣନା( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#define port_SET_CRITICAL_NESTING_ଗଣନା( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#define port_INCREMENT_CRITICAL_NESTING_ଗଣନା( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#define port_DECREMENT_CRITICAL_NESTING_ଗଣନା( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#define portSET_INTERRUPT_MASK()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm ଅସ୍ଥିର ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm ଅସ୍ଥିର ( " cpsid i " ::: "memory" );              \
        ulState; } )

#define portCLEAR_INTERRUPT_MASK( ulState )    __asm ଅସ୍ଥିର ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

ବାହ୍ୟ uint32_t ulSetInterruptMaskFromISR( ଶୂନ୍ୟ ) __attribute__( ( naked ) );
ବାହ୍ୟ ଶୂନ୍ୟ vClearInterruptMaskFromISR( uint32_t ulMask )  __attribute__( ( naked ) );
#define portSET_INTERRUPT_MASK_FROM_ISR()         ulSetInterruptMaskFromISR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vClearInterruptMaskFromISR( x )

#define portDISABLE_INTERRUPTS()                  __asm ଅସ୍ଥିର ( " cpsid i " ::: "memory" )
#define portENABLE_INTERRUPTS()                   __asm ଅସ୍ଥିର ( " cpsie i " ::: "memory" )

#ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES == 1 )
    ବାହ୍ୟ ଶୂନ୍ୟ vPortEnterCritical( ଶୂନ୍ୟ );
    ବାହ୍ୟ ଶୂନ୍ୟ vPortExitCritical( ଶୂନ୍ୟ );
    #define portENTER_CRITICAL()    vPortEnterCritical()
    #define portEXIT_CRITICAL()     vPortExitCritical()
#ଅନ୍ୟଥା
    ବାହ୍ୟ ଶୂନ୍ୟ vTaskEnterCritical( ଶୂନ୍ୟ );
    ବାହ୍ୟ ଶୂନ୍ୟ vTaskExitCritical( ଶୂନ୍ୟ );
    ବାହ୍ୟ UBaseType_t vTaskEnterCriticalFromISR( ଶୂନ୍ୟ );
    ବାହ୍ୟ ଶୂନ୍ୟ vTaskExitCriticalFromISR( UBaseType_t uxSavedInterruptStatus );
    #define portENTER_CRITICAL()               vTaskEnterCritical()
    #define portEXIT_CRITICAL()                vTaskExitCritical()
    #define portENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #define portEXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#endif /* if ( configNUMBER_OF_CORES == 1 ) */

#define port_RTOS_SPINLOCK_ଗଣନା    2

#ଯଦି PICO_SDK_VERSION_MAJOR < 2
__force_inline ସ୍ଥିର bool spin_try_lock_unsafe(spin_lock_t *lock) {
   ଫେରନ୍ତୁ *lock;
}
#endif

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ vPortRecursiveLock( BaseType_t xCoreID,
                                       uint32_t ul_Lock_ଅଙ୍କ,
                                       spin_lock_t * pxSpinLock,
                                       BaseType_t uxAcquire )
{
    ସ୍ଥିର ଅସ୍ଥିର uint8_t ucOwnedByCore[ port_MAX_CORE_ଗଣନା ][port_RTOS_SPINLOCK_ଗଣନା];
    ସ୍ଥିର ଅସ୍ଥିର uint8_t uc_Recursion_ଗଣନା_By_Lock[ port_RTOS_SPINLOCK_ଗଣନା ];

    configASSERT( ul_Lock_ଅଙ୍କ < port_RTOS_SPINLOCK_ଗଣନା );

    ଯଦି( uxAcquire )
    {
        ଯଦି (!spin_try_lock_unsafe(pxSpinLock)) {
            ଯଦି( ucOwnedByCore[ xCoreID ][ ul_Lock_ଅଙ୍କ ] )
            {
                configASSERT( uc_Recursion_ଗଣନା_By_Lock[ ul_Lock_ଅଙ୍କ ] != 255u );
                uc_Recursion_ଗଣନା_By_Lock[ ul_Lock_ଅଙ୍କ ] = uc_Recursion_ଗଣନା_By_Lock[ ul_Lock_ଅଙ୍କ ] + 1;
                ଫେରନ୍ତୁ;
            }
            spin_lock_unsafe_blocking(pxSpinLock);
        }
        configASSERT( uc_Recursion_ଗଣନା_By_Lock[ ul_Lock_ଅଙ୍କ ] == 0 );
        uc_Recursion_ଗଣନା_By_Lock[ ul_Lock_ଅଙ୍କ ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_Lock_ଅଙ୍କ ] = 1;
    }
    ଅନ୍ୟଥା
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_Lock_ଅଙ୍କ ] ) != 0 );
        configASSERT( uc_Recursion_ଗଣନା_By_Lock[ ul_Lock_ଅଙ୍କ ] != 0 );

        uc_Recursion_ଗଣନା_By_Lock[ ul_Lock_ଅଙ୍କ ] = uc_Recursion_ଗଣନା_By_Lock[ ul_Lock_ଅଙ୍କ ] - 1;
        ଯଦି ( uc_Recursion_ଗଣନା_By_Lock[ ul_Lock_ଅଙ୍କ ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_Lock_ଅଙ୍କ ] = 0;
            spin_unlock_unsafe(pxSpinLock);
        }
    }
}

#ଯଦି ( config_ସଂଖ୍ୟା_OF_CORES == 1 )
    #define portGET_ISR_LOCK( xCoreID )
    #define portRELEASE_ISR_LOCK( xCoreID )
    #define portGET_TASK_LOCK( xCoreID )
    #define portRELEASE_TASK_LOCK( xCoreID )
#ଅନ୍ୟଥା
    #define portGET_ISR_LOCK( xCoreID )         vPortRecursiveLock( ( xCoreID ), 0, spin_lock_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #define portRELEASE_ISR_LOCK( xCoreID )     vPortRecursiveLock( ( xCoreID ), 0, spin_lock_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #define portGET_TASK_LOCK( xCoreID )        vPortRecursiveLock( ( xCoreID ), 1, spin_lock_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #define portRELEASE_TASK_LOCK( xCoreID )    vPortRecursiveLock( ( xCoreID ), 1, spin_lock_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#endif

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
    ବାହ୍ୟ ଶୂନ୍ୟ vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#endif
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )

#define portNOP()               __asm ଅସ୍ଥିର ( "nop" )

#define portMEMORY_BARRIER()    __asm ଅସ୍ଥିର ( "" ::: "memory" )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
