/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#ifndef PORTMACRO_H
    #define PORTMACRO_H

    #ifndef __ASSEMBLER__

/* Inclusion of xc1.h will result in clock being defined as a type.
 * By default, FreeRTOS will require standard time.h, where clock is a function.
 */
        #ifndef USE_XCORE_CLOCK_TYPE
            #define _clock_defined
        #endif

        #અન્તર્ભાવ <xs1.h>
        #અન્તર્ભાવ "rtos_support.h"

        #ifdef __cplusplus
        બાહ્ય "C" {
        #endif

/* Type definitions. */
        #define port_ઢગલો_TYPE    uint32_t
        પ્રકારવ્યાખ્યા port_ઢગલો_TYPE   ઢગલો_Type_t;
        પ્રકારવ્યાખ્યા દ્વિગુણ           portDOUBLE;
        પ્રકારવ્યાખ્યા int32_t          BaseType_t;
        પ્રકારવ્યાખ્યા uint32_t         UBaseType_t;

        #define portBASE_TYPE    BaseType_t

        #જો ( configUSE_16_BIT_TICKS == 1 )
            પ્રકારવ્યાખ્યા uint16_t     TickType_t;
            #define portMAX_DELAY              ( TickType_t ) 0xffff
        #નહીંતર
            પ્રકારવ્યાખ્યા uint32_t     TickType_t;
            #define portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
            #define portTICK_TYPE_IS_ATOMIC    1
        #endif
/*-----------------------------------------------------------*/

    #endif /* __ASSEMBLER__ */

/* Architecture specifics. These can be used by assembly files as well. */
    #define port_ઢગલો_GROWTH               ( -1 )
    #define portTICK_PERIOD_MS             ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
    #define portBYTE_ALIGNMENT             8
    #define portCRITICAL_NESTING_IN_TCB    1
    #define port_MAX_CORE_ગણતરી             8
    #ifndef config_સંખ્યા_OF_CORES
        #define config_સંખ્યા_OF_CORES      1
    #endif

/* This may be set to zero in the config file if the rtos_time
 *  functions are not needed or if it is incremented elsewhere. */
    #ifndef configUPDATE_RTOS_TIME_FROM_TICK_ISR
        #define configUPDATE_RTOS_TIME_FROM_TICK_ISR    1
    #endif

/*
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
    #define port_THREAD_CONTEXT_ઢગલો_GROWTH    RTOS_SUPPORT_INTERRUPT_ઢગલો_GROWTH

    #ifndef __ASSEMBLER__

/* Check validity of number of cores specified in config */
        #જો ( config_સંખ્યા_OF_CORES < 1 || port_MAX_CORE_ગણતરી < config_સંખ્યા_OF_CORES )
            #error "Invalid number of cores specified in config!"
        #endif

        #define portMEMORY_BARRIER()                  RTOS_MEMORY_BARRIER()
        #define port_TASK_ઢગલો_DEPTH( pxTaskCode )    RTOS_THREAD_ઢગલો_SIZE( pxTaskCode )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
        #define portYIELD()    asm અસ્થિર ( "KCALLI_lu6 0" ::: "memory" )

        #define portEND_SWITCHING_ISR( xSwitchRequired )               \
    કરો                                                                 \
    {                                                                  \
        જો( xSwitchRequired != pdFALSE )                               \
        {                                                              \
            બાહ્ય uint32_t ulPortYieldRequired[ port_MAX_CORE_ગણતરી ]; \
            ulPortYieldRequired[ portGET_CORE_ID() ] = pdTRUE;         \
        }                                                              \
    } જ્યારે( 0 )

        #define portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* SMP utilities. */
        #define portGET_CORE_ID()      rtos_core_id_get()

        શૂન્ય vPortYieldOtherCore( પૂર્ણાંક xOtherCoreID );
        #define portYIELD_CORE( x )    vPortYieldOtherCore( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
        #ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
            #define configUSE_PORT_OPTIMISED_TASK_SELECTION    0
        #endif

        #જો configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
            #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
            #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

            #define portGET_HIGHEST_PRIORITY( ux_ટોચ_Priority, uxReadyPriorities )    ux_ટોચ_Priority = ( 31UL - ( uint32_t ) __builtin_clz( uxReadyPriorities ) )

        #endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */

        #define portGET_INTERRUPT_STATE()                 rtos_interrupt_mask_get()

/*
 * This differs from the standard portDISABLE_INTERRUPTS()
 * in that it also returns what the interrupt state was
 * before it disabling interrupts.
 */
        #define portDISABLE_INTERRUPTS()                  rtos_interrupt_mask_all()

        #define portENABLE_INTERRUPTS()                   rtos_interrupt_unmask_all()

/*
 * Port set interrupt mask and clear interrupt mask.
 */
        #define portSET_INTERRUPT_MASK()                  rtos_interrupt_mask_all()
        #define portCLEAR_INTERRUPT_MASK( ulState )       rtos_interrupt_mask_set( ulState )

/*
 * Will enable interrupts if ulState is non-zero.
 */
        #define portRESTORE_INTERRUPTS( ulState )         rtos_interrupt_mask_set( ulState )

/*
 * Returns non-zero if currently running in an
 * ISR or otherwise in kernel mode.
 */
        #define portCHECK_IF_IN_ISR()                     rtos_isr_running()

        #define portASSERT_IF_IN_ISR()                    configASSERT( portCHECK_IF_IN_ISR() == 0 )

        #define portGET_ISR_LOCK( xCoreID )               કરો{ ( શૂન્ય )( xCoreID ); rtos_lock_acquire( 0 ); } જ્યારે( 0 )
        #define portRELEASE_ISR_LOCK( xCoreID )           કરો{ ( શૂન્ય )( xCoreID ); rtos_lock_release( 0 ); } જ્યારે( 0 )
        #define portGET_TASK_LOCK( xCoreID )              કરો{ ( શૂન્ય )( xCoreID ); rtos_lock_acquire( 1 ); } જ્યારે( 0 )
        #define portRELEASE_TASK_LOCK( xCoreID )          કરો{ ( શૂન્ય )( xCoreID ); rtos_lock_release( 1 ); } જ્યારે( 0 )


        શૂન્ય vTaskEnterCritical( શૂન્ય );
        શૂન્ય vTaskExitCritical( શૂન્ય );
        #define portENTER_CRITICAL()    vTaskEnterCritical()
        #define portEXIT_CRITICAL()     vTaskExitCritical()

        બાહ્ય UBaseType_t vTaskEnterCriticalFromISR( શૂન્ય );
        બાહ્ય શૂન્ય vTaskExitCriticalFromISR( UBaseType_t uxSavedInterruptStatus );
        #define portENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
        #define portEXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

/*-----------------------------------------------------------*/

/* Runtime stats support */
        #જો ( configGENERATE_RUN_TIME_STATS == 1 )
            પૂર્ણાંક xscope_gettime( શૂન્ય );
            #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()    /* nothing needed here */
            #define port_GET_RUN_TIME_COUNTER_કિંમત()            xscope_gettime()
        #endif
/*-----------------------------------------------------------*/

/* Maps sprintf and snprintf to the lite version in lib_rtos_support */
        #જો ( configUSE_DEBUG_SPRINTF == 1 )
            #define sprintf( ... )     rtos_sprintf( __VA_ARGS__ )
            #define snprintf( ... )    rtos_snprintf( __VA_ARGS__ )
        #endif

/* Attribute for the pxCallbackFunction member of the Timer_t struct.
 * Required by xcc to calculate stack usage. */
        #define portTIMER_CALLBACK_ATTRIBUTE    __attribute__( ( fptrgroup( "timerCallbackGroup" ) ) )

/* Timer callback function macros. For xcc this ensures they get added to the timer callback
 * group so that stack usage for certain functions in timers.c can be calculated. */
        #define portTIMER_CALLBACK_FUNCTION_PROTO( vFunction, xTimer )    શૂન્ય vFunction( TimerHandle_t xTimer )
        #define portTIMER_CALLBACK_FUNCTION( vFunction, xTimer )          portTIMER_CALLBACK_ATTRIBUTE શૂન્ય vFunction( TimerHandle_t xTimer )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
        #define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    શૂન્ય vFunction( શૂન્ય * pvParameters )
        #define portTASK_FUNCTION( vFunction, pvParameters )          શૂન્ય vFunction( શૂન્ય * pvParameters )
/*-----------------------------------------------------------*/


        #ifdef __cplusplus
}
        #endif

    #endif /* __ASSEMBLER__ */

#endif /* PORTMACRO_H */
