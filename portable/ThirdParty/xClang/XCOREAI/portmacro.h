/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
    #وصف_ڪريو PORTMACRO_H

    #جيڪڏهن_وصف_نه_ٿيل __ASSEMBLER__

/* Inclusion of xc1.h will result in clock being defined as a type.
 * By default, FreeRTOS will require standard time.h, where clock is a function.
 */
        #جيڪڏهن_وصف_نه_ٿيل USE_XCORE_CLOCK_TYPE
            #وصف_ڪريو _clock_defined
        #جيڪڏهن_پورو

        #ضمن <xs1.h>
        #ضمن "rtos_support.h"

        #جيڪڏهن_وصف_ٿيل __cplusplus
        خارجي "C" {
        #جيڪڏهن_پورو

/* Type definitions. */
        #وصف_ڪريو پورٽ_ڍير_TYPE    uint32_t
        تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
        تعريفنوع مزدوج           پورٽ_DOUBLE;
        تعريفنوع int32_t          بنياد_Type_t;
        تعريفنوع uint32_t         UBaseType_t;

        #وصف_ڪريو پورٽ_بنياد_TYPE    بنياد_Type_t

        #إذا ( config_USE_16_ٻٽو_انگ_TICKS == 1 )
            تعريفنوع uint16_t     TickType_t;
            #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffff
        #وإلا
            تعريفنوع uint32_t     TickType_t;
            #وصف_ڪريو پورٽ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
            #وصف_ڪريو پورٽ_TICK_TYPE_IS_ATOMIC    1
        #جيڪڏهن_پورو
/*-----------------------------------------------------------*/

    #جيڪڏهن_پورو /* __ASSEMBLER__ */

/* Architecture specifics. These can be used by assembly files as well. */
    #وصف_ڪريو پورٽ_ڍير_GROWTH               ( -1 )
    #وصف_ڪريو پورٽ_TICK_PERIOD_MS             ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
    #وصف_ڪريو پورٽ_BYTE_ALIGNMENT             8
    #وصف_ڪريو پورٽ_CRITICAL_NESTING_اندريون_TCB    1
    #وصف_ڪريو پورٽ_MAX_CORE_ڳڻپ             8
    #جيڪڏهن_وصف_نه_ٿيل config_عدد_جو_CORES
        #وصف_ڪريو config_عدد_جو_CORES      1
    #جيڪڏهن_پورو

/* This may be set to zero in the config file if the rtos_time
 *  functions are not needed or if it is incremented elsewhere. */
    #جيڪڏهن_وصف_نه_ٿيل config_UPDATE_RTOS_وقت_FROM_TICK_ISR
        #وصف_ڪريو config_UPDATE_RTOS_وقت_FROM_TICK_ISR    1
    #جيڪڏهن_پورو

/*
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
    #وصف_ڪريو پورٽ_THREAD_CONTEXT_ڍير_GROWTH    RTOS_SUPPORT_مداخلت_ڍير_GROWTH

    #جيڪڏهن_وصف_نه_ٿيل __ASSEMBLER__

/* Check validity of number of cores specified in config */
        #إذا ( config_عدد_جو_CORES < 1 || پورٽ_MAX_CORE_ڳڻپ < config_عدد_جو_CORES )
            #غلطي "Invalid number of cores specified in config!"
        #جيڪڏهن_پورو

        #وصف_ڪريو پورٽ_يادگيري_BARRIER()                  RTOS_يادگيري_BARRIER()
        #وصف_ڪريو پورٽ_TASK_ڍير_اونهائي( px_Task_ڪوڊ )    RTOS_THREAD_ڍير_سائيز( px_Task_ڪوڊ )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
        #وصف_ڪريو پورٽ_YIELD()    asm متطاير ( "KCALLI_lu6 0" ::: "memory" )

        #وصف_ڪريو پورٽ_پڇاڙي_SWITCHING_ISR( xSwitchRequired )               \
    افعل                                                                 \
    {                                                                  \
        إذا( xSwitchRequired != pdFALSE )                               \
        {                                                              \
            خارجي uint32_t ul_پورٽ_Yield_Required[ پورٽ_MAX_CORE_ڳڻپ ]; \
            ul_پورٽ_Yield_Required[ پورٽ_GET_CORE_ID() ] = pdTRUE;         \
        }                                                              \
    } طالما( 0 )

        #وصف_ڪريو پورٽ_YIELD_FROM_ISR( x )    پورٽ_پڇاڙي_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* SMP utilities. */
        #وصف_ڪريو پورٽ_GET_CORE_ID()      rtos_core_id_get()

        فراغ v_پورٽ_Yield_Other_Core( صحيح xOtherCoreID );
        #وصف_ڪريو پورٽ_YIELD_CORE( x )    v_پورٽ_Yield_Other_Core( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
        #جيڪڏهن_وصف_نه_ٿيل config_USE_پورٽ_OPTIMISED_TASK_SELECTION
            #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    0
        #جيڪڏهن_پورو

        #إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
            #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجيح ) )
            #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجيح ) )

/*-----------------------------------------------------------*/

            #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities )    ux_چوٽي_ترجيح = ( 31UL - ( uint32_t ) __builtin_clz( uxReadyPriorities ) )

        #جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */

        #وصف_ڪريو پورٽ_GET_مداخلت_STATE()                 rtos_مداخلت_نقاب_get()

/*
 * This differs from the standard portDISABLE_INTERRUPTS()
 * in that it also returns what the interrupt state was
 * before it disabling interrupts.
 */
        #وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()                  rtos_مداخلت_نقاب_all()

        #وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()                   rtos_مداخلت_unmask_all()

/*
 * Port set interrupt mask and clear interrupt mask.
 */
        #وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب()                  rtos_مداخلت_نقاب_all()
        #وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب( ulState )       rtos_مداخلت_نقاب_سيٽ( ulState )

/*
 * Will enable interrupts if ulState is non-zero.
 */
        #وصف_ڪريو پورٽ_RESTORE_INTERRUPTS( ulState )         rtos_مداخلت_نقاب_سيٽ( ulState )

/*
 * Returns non-zero if currently running in an
 * ISR or otherwise in kernel mode.
 */
        #وصف_ڪريو پورٽ_CHECK_IF_اندريون_ISR()                     rtos_isr_running()

        #وصف_ڪريو پورٽ_ASSERT_IF_اندريون_ISR()                    configASSERT( پورٽ_CHECK_IF_اندريون_ISR() == 0 )

        #وصف_ڪريو پورٽ_GET_ISR_تالو( xCoreID )               افعل{ ( فراغ )( xCoreID ); rtos_تالو_acquire( 0 ); } طالما( 0 )
        #وصف_ڪريو پورٽ_RELEASE_ISR_تالو( xCoreID )           افعل{ ( فراغ )( xCoreID ); rtos_تالو_release( 0 ); } طالما( 0 )
        #وصف_ڪريو پورٽ_GET_TASK_تالو( xCoreID )              افعل{ ( فراغ )( xCoreID ); rtos_تالو_acquire( 1 ); } طالما( 0 )
        #وصف_ڪريو پورٽ_RELEASE_TASK_تالو( xCoreID )          افعل{ ( فراغ )( xCoreID ); rtos_تالو_release( 1 ); } طالما( 0 )


        فراغ vTaskEnterCritical( فراغ );
        فراغ vTaskExitCritical( فراغ );
        #وصف_ڪريو پورٽ_ENTER_CRITICAL()    vTaskEnterCritical()
        #وصف_ڪريو پورٽ_EXIT_CRITICAL()     vTaskExitCritical()

        خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
        خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_مداخلت_حالت );
        #وصف_ڪريو پورٽ_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
        #وصف_ڪريو پورٽ_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

/*-----------------------------------------------------------*/

/* Runtime stats support */
        #إذا ( config_GENERATE_لاڳيتو_وقت_STATS == 1 )
            صحيح xscope_gettime( فراغ );
            #وصف_ڪريو پورٽ_CONFIGURE_TIMER_FOR_لاڳيتو_وقت_STATS()    /* nothing needed here */
            #وصف_ڪريو پورٽ_GET_لاڳيتو_وقت_COUNTER_قدر()            xscope_gettime()
        #جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Maps sprintf and snprintf to the lite version in lib_rtos_support */
        #إذا ( configUSE_DEBUG_SPRINTF == 1 )
            #وصف_ڪريو sprintf( ... )     rtos_sprintf( __VA_ARGS__ )
            #وصف_ڪريو snprintf( ... )    rtos_snprintf( __VA_ARGS__ )
        #جيڪڏهن_پورو

/* Attribute for the pxCallbackFunction member of the Timer_t struct.
 * Required by xcc to calculate stack usage. */
        #وصف_ڪريو پورٽ_TIMER_CALLBACK_ATTRIBUTE    __attribute__( ( fptrgroup( "timerCallbackGroup" ) ) )

/* Timer callback function macros. For xcc this ensures they get added to the timer callback
 * group so that stack usage for certain functions in timers.c can be calculated. */
        #وصف_ڪريو پورٽ_TIMER_CALLBACK_FUNCTION_PROTO( vFunction, xTimer )    فراغ vFunction( TimerHandle_t xTimer )
        #وصف_ڪريو پورٽ_TIMER_CALLBACK_FUNCTION( vFunction, xTimer )          پورٽ_TIMER_CALLBACK_ATTRIBUTE فراغ vFunction( TimerHandle_t xTimer )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
        #وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
        #وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/


        #جيڪڏهن_وصف_ٿيل __cplusplus
}
        #جيڪڏهن_پورو

    #جيڪڏهن_پورو /* __ASSEMBLER__ */

#جيڪڏهن_پورو /* PORTMACRO_H */
