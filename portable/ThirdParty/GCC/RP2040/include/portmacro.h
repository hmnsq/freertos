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

#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
/* *INDENT-ON* */

#समावेश "pico.h"
#समावेश "hardware/sync.h"
#समावेश "rp2040_config.h"

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
#घोषणा portCHAR          अक्षर
#घोषणा portFLOAT         भग्न
#घोषणा portDOUBLE        द्विगुन
#घोषणा portLONG          दीर्घ
#घोषणा portSHORT         लघु
#घोषणा port_ढेर_TYPE    uint32_t
#घोषणा portBASE_TYPE     दीर्घ

प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार int32_t          BaseType_t;
प्रकार uint32_t         UBaseType_t;

#अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t     TickType_t;
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t     TickType_t;
    #घोषणा portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #घोषणा portTICK_TYPE_IS_ATOMIC    1
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#घोषणा port_ढेर_GROWTH                ( -1 )
#घोषणा portTICK_PERIOD_MS              ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT              8
#घोषणा portDONT_DISCARD                __attribute__( ( used ) )

/* We have to use PICO_DIVIDER_DISABLE_INTERRUPTS as the source of truth rather than our config,
 * as our FreeRTOSConfig.h header cannot be included by ASM code - which is what this affects in the SDK */
#घोषणा portUSE_DIVIDER_SAVE_RESTORE    !PICO_DIVIDER_DISABLE_INTERRUPTS
#अगर portUSE_DIVIDER_SAVE_RESTORE
    #घोषणा port_ढेर_LIMIT_PADDING     4
#पूर्ण_अगर

/*-----------------------------------------------------------*/


/* Scheduler utilities. */
बाह्य व्योम vPortYield( व्योम );
#घोषणा portNVIC_INT_CTRL_REG     ( *( ( अस्थिर uint32_t * ) 0xe000ed04 ) )
#घोषणा portNVIC_PENDSVSET_BIT    ( 1UL << 28UL )
#घोषणा portYIELD()                vPortYield()
#घोषणा portEND_SWITCHING_ISR( xSwitchRequired )            \
    करो                                                      \
    {                                                       \
        अगर( xSwitchRequired )                               \
        {                                                   \
            traceISR_EXIT_TO_SCHEDULER();                   \
            portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
        }                                                   \
        अन्यथा                                                \
        {                                                   \
            traceISR_EXIT();                                \
        }                                                   \
    } जबतक( 0 )
#घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )

/*-----------------------------------------------------------*/

/* Exception handlers */
#अगर ( configUSE_DYNAMIC_EXCEPTION_HANDLERS == 0 )
    /* We only need to override the SDK's weak functions if we want to replace them at compile time */
    #घोषणा vPortSVCHandler        isr_svcall
    #घोषणा xPortPendSVHandler     isr_pendsv
    #घोषणा xPortSysTickHandler    isr_systick
#पूर्ण_अगर

/*-----------------------------------------------------------*/

/* Multi-core */
#घोषणा port_MAX_CORE_गिनती    2

/* Check validity of number of cores specified in config */
#अगर ( config_संख्या_OF_CORES < 1 || port_MAX_CORE_गिनती < config_संख्या_OF_CORES )
    #त्रुटि "Invalid number of cores specified in config!"
#पूर्ण_अगर

#अगर ( configTICK_CORE < 0 || configTICK_CORE > config_संख्या_OF_CORES )
    #त्रुटि "Invalid tick core specified in config!"
#पूर्ण_अगर
/* FreeRTOS core id is always zero based, so always 0 if we're running on only one core */
#अगर config_संख्या_OF_CORES == port_MAX_CORE_गिनती
    #घोषणा portGET_CORE_ID()    get_core_अंक()
#अन्यथा
    #घोषणा portGET_CORE_ID()    0
#पूर्ण_अगर

#घोषणा portCHECK_IF_IN_ISR()                                 \
    ( {                                                       \
        uint32_t ulIPSR;                                      \
        __asm अस्थिर ( "mrs %0, IPSR" : "=r" ( ulIPSR )::); \
        ( ( uint8_t ) ulIPSR ) > 0; } )

/* Use #define rather than inline method to make it easier for user code
 * to work with kernel versions both with and without xPortIsInsideInterrupt */
#घोषणा xPortIsInsideInterrupt() ((BaseType_t)portCHECK_IF_IN_ISR())

व्योम vYieldCore( पूर्णांक xCoreID );
#घोषणा portYIELD_CORE( a )                  vYieldCore( a )

/*-----------------------------------------------------------*/

/* Critical nesting count management. */
#घोषणा portCRITICAL_NESTING_IN_TCB    0

बाह्य UBaseType_t uxCriticalNestings[ config_संख्या_OF_CORES ];
#घोषणा port_GET_CRITICAL_NESTING_गिनती( xCoreID )          ( uxCriticalNestings[ ( xCoreID ) ] )
#घोषणा port_SET_CRITICAL_NESTING_गिनती( xCoreID, x )       ( uxCriticalNestings[ ( xCoreID ) ] = ( x ) )
#घोषणा port_INCREMENT_CRITICAL_NESTING_गिनती( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]++ )
#घोषणा port_DECREMENT_CRITICAL_NESTING_गिनती( xCoreID )    ( uxCriticalNestings[ ( xCoreID ) ]-- )

/*-----------------------------------------------------------*/

/* Critical section management. */

#घोषणा portSET_INTERRUPT_MASK()                                  \
    ( {                                                           \
        uint32_t ulState;                                         \
        __asm अस्थिर ( "mrs %0, PRIMASK" : "=r" ( ulState )::); \
        __asm अस्थिर ( " cpsid i " ::: "memory" );              \
        ulState; } )

#घोषणा portCLEAR_INTERRUPT_MASK( ulState )    __asm अस्थिर ( "msr PRIMASK,%0" ::"r" ( ulState ) : )

बाह्य uint32_t ulSetInterruptMaskFromISR( व्योम ) __attribute__( ( naked ) );
बाह्य व्योम vClearInterruptMaskFromISR( uint32_t ulMask )  __attribute__( ( naked ) );
#घोषणा portSET_INTERRUPT_MASK_FROM_ISR()         ulSetInterruptMaskFromISR()
#घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( x )    vClearInterruptMaskFromISR( x )

#घोषणा portDISABLE_INTERRUPTS()                  __asm अस्थिर ( " cpsid i " ::: "memory" )
#घोषणा portENABLE_INTERRUPTS()                   __asm अस्थिर ( " cpsie i " ::: "memory" )

#अगर ( config_संख्या_OF_CORES == 1 )
    बाह्य व्योम vPortEnterCritical( व्योम );
    बाह्य व्योम vPortExitCritical( व्योम );
    #घोषणा portENTER_CRITICAL()    vPortEnterCritical()
    #घोषणा portEXIT_CRITICAL()     vPortExitCritical()
#अन्यथा
    बाह्य व्योम vTaskEnterCritical( व्योम );
    बाह्य व्योम vTaskExitCritical( व्योम );
    बाह्य UBaseType_t vTaskEnterCriticalFromISR( व्योम );
    बाह्य व्योम vTaskExitCriticalFromISR( UBaseType_t uxSavedInterruptStatus );
    #घोषणा portENTER_CRITICAL()               vTaskEnterCritical()
    #घोषणा portEXIT_CRITICAL()                vTaskExitCritical()
    #घोषणा portENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
    #घोषणा portEXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )
#पूर्ण_अगर /* if ( configNUMBER_OF_CORES == 1 ) */

#घोषणा port_RTOS_SPINLOCK_गिनती    2

#अगर PICO_SDK_VERSION_MAJOR < 2
__force_inline अटल bool spin_try_lock_unsafe(spin_lock_t *lock) {
   वापस *lock;
}
#पूर्ण_अगर

/* Note this is a single method with uxAcquire parameter since we have
 * static vars, the method is always called with a compile time constant for
 * uxAcquire, and the compiler should do the right thing! */
अटल अंतरभूत व्योम vPortRecursiveLock( BaseType_t xCoreID,
                                       uint32_t ul_Lock_अंक,
                                       spin_lock_t * pxSpinLock,
                                       BaseType_t uxAcquire )
{
    अटल अस्थिर uint8_t ucOwnedByCore[ port_MAX_CORE_गिनती ][port_RTOS_SPINLOCK_गिनती];
    अटल अस्थिर uint8_t uc_Recursion_गिनती_By_Lock[ port_RTOS_SPINLOCK_गिनती ];

    configASSERT( ul_Lock_अंक < port_RTOS_SPINLOCK_गिनती );

    अगर( uxAcquire )
    {
        अगर (!spin_try_lock_unsafe(pxSpinLock)) {
            अगर( ucOwnedByCore[ xCoreID ][ ul_Lock_अंक ] )
            {
                configASSERT( uc_Recursion_गिनती_By_Lock[ ul_Lock_अंक ] != 255u );
                uc_Recursion_गिनती_By_Lock[ ul_Lock_अंक ] = uc_Recursion_गिनती_By_Lock[ ul_Lock_अंक ] + 1;
                वापस;
            }
            spin_lock_unsafe_blocking(pxSpinLock);
        }
        configASSERT( uc_Recursion_गिनती_By_Lock[ ul_Lock_अंक ] == 0 );
        uc_Recursion_गिनती_By_Lock[ ul_Lock_अंक ] = 1;
        ucOwnedByCore[ xCoreID ][ ul_Lock_अंक ] = 1;
    }
    अन्यथा
    {
        configASSERT( ( ucOwnedByCore[ xCoreID ] [ul_Lock_अंक ] ) != 0 );
        configASSERT( uc_Recursion_गिनती_By_Lock[ ul_Lock_अंक ] != 0 );

        uc_Recursion_गिनती_By_Lock[ ul_Lock_अंक ] = uc_Recursion_गिनती_By_Lock[ ul_Lock_अंक ] - 1;
        अगर ( uc_Recursion_गिनती_By_Lock[ ul_Lock_अंक ] == 0U )
        {
            ucOwnedByCore[ xCoreID ] [ ul_Lock_अंक ] = 0;
            spin_unlock_unsafe(pxSpinLock);
        }
    }
}

#अगर ( config_संख्या_OF_CORES == 1 )
    #घोषणा portGET_ISR_LOCK( xCoreID )
    #घोषणा portRELEASE_ISR_LOCK( xCoreID )
    #घोषणा portGET_TASK_LOCK( xCoreID )
    #घोषणा portRELEASE_TASK_LOCK( xCoreID )
#अन्यथा
    #घोषणा portGET_ISR_LOCK( xCoreID )         vPortRecursiveLock( ( xCoreID ), 0, spin_lock_instance( configSMP_SPINLOCK_0 ), pdTRUE )
    #घोषणा portRELEASE_ISR_LOCK( xCoreID )     vPortRecursiveLock( ( xCoreID ), 0, spin_lock_instance( configSMP_SPINLOCK_0 ), pdFALSE )
    #घोषणा portGET_TASK_LOCK( xCoreID )        vPortRecursiveLock( ( xCoreID ), 1, spin_lock_instance( configSMP_SPINLOCK_1 ), pdTRUE )
    #घोषणा portRELEASE_TASK_LOCK( xCoreID )    vPortRecursiveLock( ( xCoreID ), 1, spin_lock_instance( configSMP_SPINLOCK_1 ), pdFALSE )
#पूर्ण_अगर

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#अगर_अघोषित portSUPPRESS_TICKS_AND_SLEEP
    बाह्य व्योम vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
    #घोषणा portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime )    vPortSuppressTicksAndSleep( xExpectedIdleTime )
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

#घोषणा portNOP()               __asm अस्थिर ( "nop" )

#घोषणा portMEMORY_BARRIER()    __asm अस्थिर ( "" ::: "memory" )

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
