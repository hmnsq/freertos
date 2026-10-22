/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ASSEMBLER__

/* Inclusion of xc1.h will result in clock being defined as a type.
 * By default, FreeRTOS will require standard time.h, where clock is a function.
 */
        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_XCORE_CLOCK_TYPE
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _clock_defined
        #ਜੇ_ਅੰਤ

        #ਅਨ੍ਤਰ੍ਭਾਵ <xs1.h>
        #ਅਨ੍ਤਰ੍ਭਾਵ "rtos_support.h"

        #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
        ਬਾਹਰੀ "C" {
        #ਜੇ_ਅੰਤ

/* Type definitions. */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    uint32_t
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE   ਢੇਰ_Type_t;
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਦੁੱਗਣਾ           ਪੋਰਟ_DOUBLE;
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ int32_t          ਅਧਾਰ_Type_t;
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t         UBaseType_t;

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE    ਅਧਾਰ_Type_t

        #ਜੇ ( config_USE_16_ਦੋਆਧਾਰੀ_ਅੰਕ_TICKS == 1 )
            ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t     TickType_t;
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffff
        #ਨਹੀਂਤਾਂ
            ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t     TickType_t;
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_TYPE_IS_ATOMIC    1
        #ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

    #ਜੇ_ਅੰਤ /* __ASSEMBLER__ */

/* Architecture specifics. These can be used by assembly files as well. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH               ( -1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS             ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT             8
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਚ_TCB    1
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ             8
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਸੰਖਿਆ_ਦਾ_CORES
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਸੰਖਿਆ_ਦਾ_CORES      1
    #ਜੇ_ਅੰਤ

/* This may be set to zero in the config file if the rtos_time
 *  functions are not needed or if it is incremented elsewhere. */
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_UPDATE_RTOS_ਸਮਾਂ_FROM_TICK_ISR
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_UPDATE_RTOS_ਸਮਾਂ_FROM_TICK_ISR    1
    #ਜੇ_ਅੰਤ

/*
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_THREAD_CONTEXT_ਢੇਰ_GROWTH    RTOS_SUPPORT_ਰੁਕਾਵਟ_ਢੇਰ_GROWTH

    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ASSEMBLER__

/* Check validity of number of cores specified in config */
        #ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES < 1 || ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ < config_ਸੰਖਿਆ_ਦਾ_CORES )
            #ਗਲਤੀ "Invalid number of cores specified in config!"
        #ਜੇ_ਅੰਤ

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER()                  RTOS_ਸਮ੍ਰਿਤੀ_BARRIER()
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_ਢੇਰ_ਡੂੰਘਾਈ( px_Task_ਕੋਡ )    RTOS_THREAD_ਢੇਰ_ਮਾਪ( px_Task_ਕੋਡ )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()    asm ਅਸਥਿਰ ( "KCALLI_lu6 0" ::: "memory" )

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( xSwitchRequired )               \
    ਕਰੋ                                                                 \
    {                                                                  \
        ਜੇ( xSwitchRequired != pdFALSE )                               \
        {                                                              \
            ਬਾਹਰੀ uint32_t ul_ਪੋਰਟ_Yield_Required[ ਪੋਰਟ_MAX_CORE_ਗਿਣਤੀ ]; \
            ul_ਪੋਰਟ_Yield_Required[ ਪੋਰਟ_GET_CORE_ID() ] = pdTRUE;         \
        }                                                              \
    } ਜਦੋਂ( 0 )

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x )    ਪੋਰਟ_ਸਿਰਾ_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* SMP utilities. */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_CORE_ID()      rtos_core_id_get()

        ਖਾਲੀ v_ਪੋਰਟ_Yield_Other_Core( ਪੂਰਨ xOtherCoreID );
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_CORE( x )    v_ਪੋਰਟ_Yield_Other_Core( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION    0
        #ਜੇ_ਅੰਤ

        #ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰਿਕਾਰਡ_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ਤਰਜੀਹ ) )
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ਤਰਜੀਹ ) )

/*-----------------------------------------------------------*/

            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities )    ux_ਸਿਖਰ_ਤਰਜੀਹ = ( 31UL - ( uint32_t ) __builtin_clz( uxReadyPriorities ) )

        #ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ਰੁਕਾਵਟ_STATE()                 rtos_ਰੁਕਾਵਟ_ਨਕਾਬ_get()

/*
 * This differs from the standard portDISABLE_INTERRUPTS()
 * in that it also returns what the interrupt state was
 * before it disabling interrupts.
 */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()                  rtos_ਰੁਕਾਵਟ_ਨਕਾਬ_all()

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()                   rtos_ਰੁਕਾਵਟ_unmask_all()

/*
 * Port set interrupt mask and clear interrupt mask.
 */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ()                  rtos_ਰੁਕਾਵਟ_ਨਕਾਬ_all()
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ( ulState )       rtos_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸੈੱਟ( ulState )

/*
 * Will enable interrupts if ulState is non-zero.
 */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESTORE_INTERRUPTS( ulState )         rtos_ਰੁਕਾਵਟ_ਨਕਾਬ_ਸੈੱਟ( ulState )

/*
 * Returns non-zero if currently running in an
 * ISR or otherwise in kernel mode.
 */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHECK_IF_ਵਿੱਚ_ISR()                     rtos_isr_running()

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASSERT_IF_ਵਿੱਚ_ISR()                    configASSERT( ਪੋਰਟ_CHECK_IF_ਵਿੱਚ_ISR() == 0 )

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ISR_ਤਾਲਾ( xCoreID )               ਕਰੋ{ ( ਖਾਲੀ )( xCoreID ); rtos_ਤਾਲਾ_acquire( 0 ); } ਜਦੋਂ( 0 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_ISR_ਤਾਲਾ( xCoreID )           ਕਰੋ{ ( ਖਾਲੀ )( xCoreID ); rtos_ਤਾਲਾ_release( 0 ); } ਜਦੋਂ( 0 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_TASK_ਤਾਲਾ( xCoreID )              ਕਰੋ{ ( ਖਾਲੀ )( xCoreID ); rtos_ਤਾਲਾ_acquire( 1 ); } ਜਦੋਂ( 0 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RELEASE_TASK_ਤਾਲਾ( xCoreID )          ਕਰੋ{ ( ਖਾਲੀ )( xCoreID ); rtos_ਤਾਲਾ_release( 1 ); } ਜਦੋਂ( 0 )


        ਖਾਲੀ vTaskEnterCritical( ਖਾਲੀ );
        ਖਾਲੀ vTaskExitCritical( ਖਾਲੀ );
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()    vTaskEnterCritical()
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()     vTaskExitCritical()

        ਬਾਹਰੀ UBaseType_t vTaskEnterCriticalFromISR( ਖਾਲੀ );
        ਬਾਹਰੀ ਖਾਲੀ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_ਰੁਕਾਵਟ_ਸਥਿਤੀ );
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

/*-----------------------------------------------------------*/

/* Runtime stats support */
        #ਜੇ ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )
            ਪੂਰਨ xscope_gettime( ਖਾਲੀ );
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONFIGURE_TIMER_FOR_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS()    /* nothing needed here */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_ਮੁੱਲ()            xscope_gettime()
        #ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* Maps sprintf and snprintf to the lite version in lib_rtos_support */
        #ਜੇ ( configUSE_DEBUG_SPRINTF == 1 )
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sprintf( ... )     rtos_sprintf( __VA_ARGS__ )
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ snprintf( ... )    rtos_snprintf( __VA_ARGS__ )
        #ਜੇ_ਅੰਤ

/* Attribute for the pxCallbackFunction member of the Timer_t struct.
 * Required by xcc to calculate stack usage. */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_CALLBACK_ATTRIBUTE    __attribute__( ( fptrgroup( "timerCallbackGroup" ) ) )

/* Timer callback function macros. For xcc this ensures they get added to the timer callback
 * group so that stack usage for certain functions in timers.c can be calculated. */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_CALLBACK_FUNCTION_PROTO( vFunction, xTimer )    ਖਾਲੀ vFunction( TimerHandle_t xTimer )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIMER_CALLBACK_FUNCTION( vFunction, xTimer )          ਪੋਰਟ_TIMER_CALLBACK_ATTRIBUTE ਖਾਲੀ vFunction( TimerHandle_t xTimer )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
/*-----------------------------------------------------------*/


        #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
        #ਜੇ_ਅੰਤ

    #ਜੇ_ਅੰਤ /* __ASSEMBLER__ */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
