/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#که_نه_تعریف_شوی PORTMACRO_H
    #تعریف_کړه PORTMACRO_H

    #که_نه_تعریف_شوی __ASSEMBLER__

/* Inclusion of xc1.h will result in clock being defined as a type.
 * By default, FreeRTOS will require standard time.h, where clock is a function.
 */
        #که_نه_تعریف_شوی USE_XCORE_CLOCK_TYPE
            #تعریف_کړه _clock_defined
        #د_که_پای

        #ضمن <xs1.h>
        #ضمن "rtos_support.h"

        #که_تعریف_شوی __cplusplus
        خارجي "C" {
        #د_که_پای

/* Type definitions. */
        #تعریف_کړه پورټ_ډېری_TYPE    uint32_t
        تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
        تعريفنوع مزدوج           پورټ_DOUBLE;
        تعريفنوع int32_t          بنسټ_Type_t;
        تعريفنوع uint32_t         UBaseType_t;

        #تعریف_کړه پورټ_بنسټ_TYPE    بنسټ_Type_t

        #إذا ( config_USE_16_بټ_TICKS == 1 )
            تعريفنوع uint16_t     TickType_t;
            #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffff
        #وإلا
            تعريفنوع uint32_t     TickType_t;
            #تعریف_کړه پورټ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
            #تعریف_کړه پورټ_TICK_TYPE_IS_ATOMIC    1
        #د_که_پای
/*-----------------------------------------------------------*/

    #د_که_پای /* __ASSEMBLER__ */

/* Architecture specifics. These can be used by assembly files as well. */
    #تعریف_کړه پورټ_ډېری_GROWTH               ( -1 )
    #تعریف_کړه پورټ_TICK_PERIOD_MS             ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
    #تعریف_کړه پورټ_BYTE_ALIGNMENT             8
    #تعریف_کړه پورټ_CRITICAL_NESTING_دننه_TCB    1
    #تعریف_کړه پورټ_MAX_CORE_شمېر             8
    #که_نه_تعریف_شوی config_شمېره_د_CORES
        #تعریف_کړه config_شمېره_د_CORES      1
    #د_که_پای

/* This may be set to zero in the config file if the rtos_time
 *  functions are not needed or if it is incremented elsewhere. */
    #که_نه_تعریف_شوی config_UPDATE_RTOS_وخت_FROM_TICK_ISR
        #تعریف_کړه config_UPDATE_RTOS_وخت_FROM_TICK_ISR    1
    #د_که_پای

/*
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
    #تعریف_کړه پورټ_THREAD_CONTEXT_ډېری_GROWTH    RTOS_SUPPORT_مداخله_ډېری_GROWTH

    #که_نه_تعریف_شوی __ASSEMBLER__

/* Check validity of number of cores specified in config */
        #إذا ( config_شمېره_د_CORES < 1 || پورټ_MAX_CORE_شمېر < config_شمېره_د_CORES )
            #تېروتنه "Invalid number of cores specified in config!"
        #د_که_پای

        #تعریف_کړه پورټ_حافظه_BARRIER()                  RTOS_حافظه_BARRIER()
        #تعریف_کړه پورټ_TASK_ډېری_ژوروالی( px_Task_کوډ )    RTOS_THREAD_ډېری_اندازه( px_Task_کوډ )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
        #تعریف_کړه پورټ_YIELD()    asm متطاير ( "KCALLI_lu6 0" ::: "memory" )

        #تعریف_کړه پورټ_پای_ټکی_SWITCHING_ISR( xSwitchRequired )               \
    افعل                                                                 \
    {                                                                  \
        إذا( xSwitchRequired != pdFALSE )                               \
        {                                                              \
            خارجي uint32_t ul_پورټ_Yield_Required[ پورټ_MAX_CORE_شمېر ]; \
            ul_پورټ_Yield_Required[ پورټ_GET_CORE_ID() ] = pdTRUE;         \
        }                                                              \
    } طالما( 0 )

        #تعریف_کړه پورټ_YIELD_FROM_ISR( x )    پورټ_پای_ټکی_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* SMP utilities. */
        #تعریف_کړه پورټ_GET_CORE_ID()      rtos_core_id_get()

        فراغ v_پورټ_Yield_Other_Core( صحيح xOtherCoreID );
        #تعریف_کړه پورټ_YIELD_CORE( x )    v_پورټ_Yield_Other_Core( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
        #که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION
            #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    0
        #د_که_پای

        #إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
            #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
            #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

/*-----------------------------------------------------------*/

            #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )    ux_سر_لومړیتوب = ( 31UL - ( uint32_t ) __builtin_clz( uxReadyPriorities ) )

        #د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */

        #تعریف_کړه پورټ_GET_مداخله_STATE()                 rtos_مداخله_ماسک_get()

/*
 * This differs from the standard portDISABLE_INTERRUPTS()
 * in that it also returns what the interrupt state was
 * before it disabling interrupts.
 */
        #تعریف_کړه پورټ_DISABLE_INTERRUPTS()                  rtos_مداخله_ماسک_all()

        #تعریف_کړه پورټ_ENABLE_INTERRUPTS()                   rtos_مداخله_unmask_all()

/*
 * Port set interrupt mask and clear interrupt mask.
 */
        #تعریف_کړه پورټ_سېټ_مداخله_ماسک()                  rtos_مداخله_ماسک_all()
        #تعریف_کړه پورټ_CLEAR_مداخله_ماسک( ulState )       rtos_مداخله_ماسک_سېټ( ulState )

/*
 * Will enable interrupts if ulState is non-zero.
 */
        #تعریف_کړه پورټ_RESTORE_INTERRUPTS( ulState )         rtos_مداخله_ماسک_سېټ( ulState )

/*
 * Returns non-zero if currently running in an
 * ISR or otherwise in kernel mode.
 */
        #تعریف_کړه پورټ_CHECK_IF_دننه_ISR()                     rtos_isr_running()

        #تعریف_کړه پورټ_ASSERT_IF_دننه_ISR()                    configASSERT( پورټ_CHECK_IF_دننه_ISR() == 0 )

        #تعریف_کړه پورټ_GET_ISR_قلف( xCoreID )               افعل{ ( فراغ )( xCoreID ); rtos_قلف_acquire( 0 ); } طالما( 0 )
        #تعریف_کړه پورټ_RELEASE_ISR_قلف( xCoreID )           افعل{ ( فراغ )( xCoreID ); rtos_قلف_release( 0 ); } طالما( 0 )
        #تعریف_کړه پورټ_GET_TASK_قلف( xCoreID )              افعل{ ( فراغ )( xCoreID ); rtos_قلف_acquire( 1 ); } طالما( 0 )
        #تعریف_کړه پورټ_RELEASE_TASK_قلف( xCoreID )          افعل{ ( فراغ )( xCoreID ); rtos_قلف_release( 1 ); } طالما( 0 )


        فراغ vTaskEnterCritical( فراغ );
        فراغ vTaskExitCritical( فراغ );
        #تعریف_کړه پورټ_ENTER_CRITICAL()    vTaskEnterCritical()
        #تعریف_کړه پورټ_EXIT_CRITICAL()     vTaskExitCritical()

        خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
        خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_مداخله_حالت );
        #تعریف_کړه پورټ_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
        #تعریف_کړه پورټ_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

/*-----------------------------------------------------------*/

/* Runtime stats support */
        #إذا ( config_GENERATE_پرلپسې_وخت_STATS == 1 )
            صحيح xscope_gettime( فراغ );
            #تعریف_کړه پورټ_CONFIGURE_TIMER_FOR_پرلپسې_وخت_STATS()    /* nothing needed here */
            #تعریف_کړه پورټ_GET_پرلپسې_وخت_COUNTER_ارزښت()            xscope_gettime()
        #د_که_پای
/*-----------------------------------------------------------*/

/* Maps sprintf and snprintf to the lite version in lib_rtos_support */
        #إذا ( configUSE_DEBUG_SPRINTF == 1 )
            #تعریف_کړه sprintf( ... )     rtos_sprintf( __VA_ARGS__ )
            #تعریف_کړه snprintf( ... )    rtos_snprintf( __VA_ARGS__ )
        #د_که_پای

/* Attribute for the pxCallbackFunction member of the Timer_t struct.
 * Required by xcc to calculate stack usage. */
        #تعریف_کړه پورټ_TIMER_CALLBACK_ATTRIBUTE    __attribute__( ( fptrgroup( "timerCallbackGroup" ) ) )

/* Timer callback function macros. For xcc this ensures they get added to the timer callback
 * group so that stack usage for certain functions in timers.c can be calculated. */
        #تعریف_کړه پورټ_TIMER_CALLBACK_FUNCTION_PROTO( vFunction, xTimer )    فراغ vFunction( TimerHandle_t xTimer )
        #تعریف_کړه پورټ_TIMER_CALLBACK_FUNCTION( vFunction, xTimer )          پورټ_TIMER_CALLBACK_ATTRIBUTE فراغ vFunction( TimerHandle_t xTimer )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
        #تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
        #تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/


        #که_تعریف_شوی __cplusplus
}
        #د_که_پای

    #د_که_پای /* __ASSEMBLER__ */

#د_که_پای /* PORTMACRO_H */
