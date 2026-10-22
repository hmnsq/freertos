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
    बाह्य "C" {
#endif
/* *INDENT-ON* */

#अन्तर्भाव "pico.h"
#अन्तर्भाव "hardware/sync.h"
#अन्तर्भाव "rp2040_config.h"

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
#define portCHAR          अक्षर
#define portFLOAT         दशांश
#define portDOUBLE        द्विगुण
#define portLONG          दीर्घ
#define portSHORT         लघु
#define port_चळत_TYPE    uint32_t
#define portBASE_TYPE     दीर्घ

प्रकारव्याख्या port_चळत_TYPE   चळत_Type_t;
प्रकारव्याख्या int32_t          BaseType_t;
प्रकारव्याख्या uint32_t         UBaseType_t;

#जर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकारव्याख्या uint16_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffff
#किंवाजर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकारव्याख्या uint32_t     TickType_t;
    #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #define portTICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define port_चळत_GROWTH                ( -1 )
#define portTICK_PERIOD_MS              ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT              8
#define portDONT_DISCARD                __attribute__( ( used ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#define portUSE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#जर portUSE_DIVIDER_SAVE_RESTORE
    #define port_चळत_LIMIT_PADDING     4
#endif

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
बाह्य शून्य vPortYield( शून्य );
#define portNVIC_INT_CTRL_REG     ( *( ( अस्थिर uint32_t * ) 0xe000ed04 ) )
#define portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#define portYIELD()                vPortYield()
#define portEND_SWITCHING_ISR( xSwitchRequired )            \
    करा                                                      \
    {                                                       \
        जर( xSwitchRequired )                               \
        {                                                   \
            traceISR_EXIT_TO_SCHEDULER();                   \
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
        }                                                   \
        अन्यथा                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } पर्यंत( 0 )
#define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#जर ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #define vPortSVCHandler        isr_svcall
    #define xPortPendSVHandler     isr_pendsv
    #define xPortSysTickHandler    isr_systick
#endif

/*-----------------------------------------------------------*/

/* Multi-core */
#define port_MAX_CORE_मोजणी    2

/* Check validity of number of cores specified in config */
#जर ( config_संख्या_OF_CORES < 1 || port_MAX_CORE_मोजणी < config_संख्या_OF_CORES )
    #error "Invalid number of cores specified in config!"
#endif

#जर ( configTICK_CORE < 0 || configTICK_CORE > config_संख्या_OF_CORES )
    #error "Invalid tick core specified in config!"
#endif
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#जर config_संख्या_OF_CORES == port_MAX_CORE_मोजणी
    #define portGET_CORE_ID()    get_core_अंक()
#अन्यथा
    #define portGET_CORE_ID()    0
#endif

#define portCHECK_IF_IN_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm अस्थिर ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#define xPortIsInsideInterrupt() ((BaseType_t)portCHECK_IF_IN_ISR())

शून्य vYieldCore( पूर्णांक xCoreID );
#define portYIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#define portCRITICAL_NESTING_IN_TCB    0

बाह्य UBaseType_t uxCriticalNestings[ config_संख्या_OF_CORES ];
#define port_GET_CRITICAL_NESTING_मोजणी( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#define port_SET_CRITICAL_NESTING_मोजणी( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#define port_INCREMENT_CRITICAL_NESTING_मोजणी( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#define port_DECREMENT_CRITICAL_NESTING_मोजणी( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#define portSET_INTERRUPT_MASK()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm अस्थिर ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm अस्थिर ( " cpsid i " ::: "memory" );              \
        ulState; } )

#define portCLEAR_INTERRUPT_MASK( ulState )    __asm अस्थिर ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

बाह्य uint32_t ulSetInterruptMaskFromISR( शून्य ) __attribute__( ( naked ) );
बाह्य शून्य vClearInterruptMaskFromISR( uint32_t ulMask )  __attribute__( ( naked ) );
#define portSET_INTERRUPT_MASK_FROM_ISR()         ulSetInterruptMaskFromISR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vClearInterruptMaskFromISR( x )

#define portDISABLE_INTERRUPTS()                  __asm अस्थिर ( " cpsid i " ::: "memory" )
#define portENABLE_INTERRUPTS()                   __asm अस्थिर ( " cpsie i " ::: "memory" )

#जर ( config_संख्या_OF_CORES == 1 )
    बाह्य शून्य vPortEnterCritical( शून्य );
    बाह्य शून्य vPortExitCritical( शून्य );
    #define portENTER_CRITICAL()    vPortEnterCritical()
    #define portEXIT_CRITICAL()     vPortExitCritical()
#अन्यथा
    बाह्य शून्य vTaskEnterCritical( शून्य );
    बाह्य शून्य vTaskExitCritical( शून्य );
    बाह्य UBaseType_t vTaskEnterCriticalFromISR( शून्य );
    बाह्य शून्य vTaskExitCriticalFromISR( UBaseType_t uxSavedInterruptStatus );
    #define portENTER_CRITICAL()               vTaskEnterCritical()
    #define portEXIT_CRITICAL()                vTaskExitCritical()
    #define portENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #define portEXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#endif /* if ( configNUMBER_OF_CORES == 1 ) */

#define port_RTOS_SPINLOCK_मोजणी    2

#जर PICO_SDK_VERSION_MAJOR < 2
__force_inline स्थिर bool spin_try_lock_unsafe(spin_lock_t *lock) {
   परत *lock;
}
#endif

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
स्थिर ओळीत शून्य vPortRecursiveLock( BaseType_t xCoreID,
                                       uint32_t ul_Lock_अंक,
                                       spin_lock_t * pxSpinLock,
                                       BaseType_t uxAcquire )
{
    स्थिर अस्थिर uint8_t ucOwnedByCore[ port_MAX_CORE_मोजणी ][port_RTOS_SPINLOCK_मोजणी];
    स्थिर अस्थिर uint8_t uc_Recursion_मोजणी_By_Lock[ port_RTOS_SPINLOCK_मोजणी ];

    configASSERT( ul_Lock_अंक < port_RTOS_SPINLOCK_मोजणी );

    जर( uxAcquire )
    {
        जर (!spin_try_lock_unsafe(pxSpinLock)) {
            जर( ucOwnedByCore[ xCoreID ][ ul_Lock_अंक ] )
            {
                configASSERT( uc_Recursion_मोजणी_By_Lock[ ul_Lock_अंक ] != 255u );
                uc_Recursion_मोजणी_By_Lock[ ul_Lock_अंक ] = uc_Recursion_मोजणी_By_Lock[ ul_Lock_अंक ] + 1;
                परत;
            }
            spin_lock_unsafe_blocking(pxSpinLock);
        }
        configASSERT( uc_Recursion_मोजणी_By_Lock[ ul_Lock_अंक ] == 0 );
        uc_Recursion_मोजणी_By_Lock[ ul_Lock_अंक ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_Lock_अंक ] = 1;
    }
    अन्यथा
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_Lock_अंक ] ) != 0 );
        configASSERT( uc_Recursion_मोजणी_By_Lock[ ul_Lock_अंक ] != 0 );

        uc_Recursion_मोजणी_By_Lock[ ul_Lock_अंक ] = uc_Recursion_मोजणी_By_Lock[ ul_Lock_अंक ] - 1;
        जर ( uc_Recursion_मोजणी_By_Lock[ ul_Lock_अंक ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_Lock_अंक ] = 0;
            spin_unlock_unsafe(pxSpinLock);
        }
    }
}

#जर ( config_संख्या_OF_CORES == 1 )
    #define portGET_ISR_LOCK( xCoreID )
    #define portRELEASE_ISR_LOCK( xCoreID )
    #define portGET_TASK_LOCK( xCoreID )
    #define portRELEASE_TASK_LOCK( xCoreID )
#अन्यथा
    #define portGET_ISR_LOCK( xCoreID )         vPortRecursiveLock( ( xCoreID ), 0, spin_lock_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #define portRELEASE_ISR_LOCK( xCoreID )     vPortRecursiveLock( ( xCoreID ), 0, spin_lock_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #define portGET_TASK_LOCK( xCoreID )        vPortRecursiveLock( ( xCoreID ), 1, spin_lock_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #define portRELEASE_TASK_LOCK( xCoreID )    vPortRecursiveLock( ( xCoreID ), 1, spin_lock_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#endif

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
    बाह्य शून्य vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#endif
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

#define portNOP()               __asm अस्थिर ( "nop" )

#define portMEMORY_BARRIER()    __asm अस्थिर ( "" ::: "memory" )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
