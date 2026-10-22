/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __ASSEMBLER__

/* Inclusion of xc1.h will result in clock being defined as a type.
 * By default, FreeRTOS will require standard time.h, where clock is a function.
 */
        #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_XCORE_CLOCK_TYPE
            #ವ್ಯಾಖ್ಯಾನಿಸು _clock_defined
        #ಆದರೆ_ಅಂತ್ಯ

        #ಅನ್ತರ್ಭಾವ <xs1.h>
        #ಅನ್ತರ್ಭಾವ "rtos_support.h"

        #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
        ಬಾಹ್ಯ "C" {
        #ಆದರೆ_ಅಂತ್ಯ

/* Type definitions. */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE    uint32_t
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ದ್ವಿಗುಣ           ಪೋರ್ಟ್_DOUBLE;
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int32_t          ತಳ_Type_t;
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t         UBaseType_t;

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE    ತಳ_Type_t

        #ಆದರೆ ( config_USE_16_ಬಿಟ್_TICKS == 1 )
            ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t     TickType_t;
            #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY              ( TickType_t ) 0xffff
        #ಇಲ್ಲದಿದ್ದರೆ
            ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t     TickType_t;
            #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
            #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC    1
        #ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

    #ಆದರೆ_ಅಂತ್ಯ /* __ASSEMBLER__ */

/* Architecture specifics. These can be used by assembly files as well. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH               ( -1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS             ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT             8
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CRITICAL_NESTING_ಒಳ_TCB    1
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ             8
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಸಂಖ್ಯೆ_ದ_CORES
        #ವ್ಯಾಖ್ಯಾನಿಸು config_ಸಂಖ್ಯೆ_ದ_CORES      1
    #ಆದರೆ_ಅಂತ್ಯ

/* This may be set to zero in the config file if the rtos_time
 *  functions are not needed or if it is incremented elsewhere. */
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_UPDATE_RTOS_ಸಮಯ_FROM_TICK_ISR
        #ವ್ಯಾಖ್ಯಾನಿಸು config_UPDATE_RTOS_ಸಮಯ_FROM_TICK_ISR    1
    #ಆದರೆ_ಅಂತ್ಯ

/*
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THREAD_CONTEXT_ರಾಶಿ_GROWTH    RTOS_SUPPORT_ಅಡಚಣೆ_ರಾಶಿ_GROWTH

    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __ASSEMBLER__

/* Check validity of number of cores specified in config */
        #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES < 1 || ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ < config_ಸಂಖ್ಯೆ_ದ_CORES )
            #ದೋಷ "Invalid number of cores specified in config!"
        #ಆದರೆ_ಅಂತ್ಯ

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER()                  RTOS_ಸ್ಮರಣೆ_BARRIER()
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_ರಾಶಿ_ಆಳ( px_Task_ಸಂಕೇತ )    RTOS_THREAD_ರಾಶಿ_ಗಾತ್ರ( px_Task_ಸಂಕೇತ )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()    asm ಅಸ್ಥಿರ ( "KCALLI_lu6 0" ::: "memory" )

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( xSwitchRequired )               \
    ಮಾಡು                                                                 \
    {                                                                  \
        ಆದರೆ( xSwitchRequired != pdFALSE )                               \
        {                                                              \
            ಬಾಹ್ಯ uint32_t ul_ಪೋರ್ಟ್_Yield_Required[ ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ ]; \
            ul_ಪೋರ್ಟ್_Yield_Required[ ಪೋರ್ಟ್_GET_CORE_ID() ] = pdTRUE;         \
        }                                                              \
    } ಆಗ( 0 )

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )    ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* SMP utilities. */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_CORE_ID()      rtos_core_id_get()

        ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield_Other_Core( ಪೂರ್ಣಾಂಕ xOtherCoreID );
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_CORE( x )    v_ಪೋರ್ಟ್_Yield_Other_Core( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
        #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION
            #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION    0
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
            #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
            #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

/*-----------------------------------------------------------*/

            #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities )    ux_ತುದಿ_ಆದ್ಯತೆ = ( 31UL - ( uint32_t ) __builtin_clz( uxReadyPriorities ) )

        #ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ಅಡಚಣೆ_STATE()                 rtos_ಅಡಚಣೆ_ಮುಖವಾಡ_get()

/*
 * This differs from the standard portDISABLE_INTERRUPTS()
 * in that it also returns what the interrupt state was
 * before it disabling interrupts.
 */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()                  rtos_ಅಡಚಣೆ_ಮುಖವಾಡ_all()

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()                   rtos_ಅಡಚಣೆ_unmask_all()

/*
 * Port set interrupt mask and clear interrupt mask.
 */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()                  rtos_ಅಡಚಣೆ_ಮುಖವಾಡ_all()
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ( ulState )       rtos_ಅಡಚಣೆ_ಮುಖವಾಡ_ಗಣ( ulState )

/*
 * Will enable interrupts if ulState is non-zero.
 */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESTORE_INTERRUPTS( ulState )         rtos_ಅಡಚಣೆ_ಮುಖವಾಡ_ಗಣ( ulState )

/*
 * Returns non-zero if currently running in an
 * ISR or otherwise in kernel mode.
 */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHECK_IF_ಒಳ_ISR()                     rtos_isr_running()

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASSERT_IF_ಒಳ_ISR()                    configASSERT( ಪೋರ್ಟ್_CHECK_IF_ಒಳ_ISR() == 0 )

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ISR_ಬೀಗ( xCoreID )               ಮಾಡು{ ( ಶೂನ್ಯ )( xCoreID ); rtos_ಬೀಗ_acquire( 0 ); } ಆಗ( 0 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_ISR_ಬೀಗ( xCoreID )           ಮಾಡು{ ( ಶೂನ್ಯ )( xCoreID ); rtos_ಬೀಗ_release( 0 ); } ಆಗ( 0 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_TASK_ಬೀಗ( xCoreID )              ಮಾಡು{ ( ಶೂನ್ಯ )( xCoreID ); rtos_ಬೀಗ_acquire( 1 ); } ಆಗ( 0 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_TASK_ಬೀಗ( xCoreID )          ಮಾಡು{ ( ಶೂನ್ಯ )( xCoreID ); rtos_ಬೀಗ_release( 1 ); } ಆಗ( 0 )


        ಶೂನ್ಯ vTaskEnterCritical( ಶೂನ್ಯ );
        ಶೂನ್ಯ vTaskExitCritical( ಶೂನ್ಯ );
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()    vTaskEnterCritical()
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()     vTaskExitCritical()

        ಬಾಹ್ಯ UBaseType_t vTaskEnterCriticalFromISR( ಶೂನ್ಯ );
        ಬಾಹ್ಯ ಶೂನ್ಯ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_ಅಡಚಣೆ_ಸ್ಥಿತಿ );
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

/*-----------------------------------------------------------*/

/* Runtime stats support */
        #ಆದರೆ ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 )
            ಪೂರ್ಣಾಂಕ xscope_gettime( ಶೂನ್ಯ );
            #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONFIGURE_TIMER_FOR_ಸತತ_ಸಮಯ_STATS()    /* nothing needed here */
            #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ಸತತ_ಸಮಯ_COUNTER_ಮೌಲ್ಯ()            xscope_gettime()
        #ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* Maps sprintf and snprintf to the lite version in lib_rtos_support */
        #ಆದರೆ ( configUSE_DEBUG_SPRINTF == 1 )
            #ವ್ಯಾಖ್ಯಾನಿಸು sprintf( ... )     rtos_sprintf( __VA_ARGS__ )
            #ವ್ಯಾಖ್ಯಾನಿಸು snprintf( ... )    rtos_snprintf( __VA_ARGS__ )
        #ಆದರೆ_ಅಂತ್ಯ

/* Attribute for the pxCallbackFunction member of the Timer_t struct.
 * Required by xcc to calculate stack usage. */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_CALLBACK_ATTRIBUTE    __attribute__( ( fptrgroup( "timerCallbackGroup" ) ) )

/* Timer callback function macros. For xcc this ensures they get added to the timer callback
 * group so that stack usage for certain functions in timers.c can be calculated. */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_CALLBACK_FUNCTION_PROTO( vFunction, xTimer )    ಶೂನ್ಯ vFunction( TimerHandle_t xTimer )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIMER_CALLBACK_FUNCTION( vFunction, xTimer )          ಪೋರ್ಟ್_TIMER_CALLBACK_ATTRIBUTE ಶೂನ್ಯ vFunction( TimerHandle_t xTimer )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
/*-----------------------------------------------------------*/


        #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
        #ಆದರೆ_ಅಂತ್ಯ

    #ಆದರೆ_ಅಂತ್ಯ /* __ASSEMBLER__ */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
