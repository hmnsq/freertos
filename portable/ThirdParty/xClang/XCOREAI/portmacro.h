/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#నిర్వచితం_కాకపోతే PORTMACRO_H
    #నిర్వచించు PORTMACRO_H

    #నిర్వచితం_కాకపోతే __ASSEMBLER__

/* Inclusion of xc1.h will result in clock being defined as a type.
 * By default, FreeRTOS will require standard time.h, where clock is a function.
 */
        #నిర్వచితం_కాకపోతే USE_XCORE_CLOCK_TYPE
            #నిర్వచించు _clock_defined
        #అయితే_ముగింపు

        #అన్తర్భావ <xs1.h>
        #అన్తర్భావ "rtos_support.h"

        #నిర్వచితమైతే __cplusplus
        బాహ్య "C" {
        #అయితే_ముగింపు

/* Type definitions. */
        #నిర్వచించు పోర్టు_దొంతర_TYPE    uint32_t
        రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
        రకనిర్వచనం ద్విగుణ           పోర్టు_DOUBLE;
        రకనిర్వచనం int32_t          పునాది_Type_t;
        రకనిర్వచనం uint32_t         UBaseType_t;

        #నిర్వచించు పోర్టు_పునాది_TYPE    పునాది_Type_t

        #ఒకవేళ ( config_USE_16_బిట్టు_TICKS == 1 )
            రకనిర్వచనం uint16_t     TickType_t;
            #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffff
        #లేకపోతే
            రకనిర్వచనం uint32_t     TickType_t;
            #నిర్వచించు పోర్టు_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
            #నిర్వచించు పోర్టు_TICK_TYPE_IS_ATOMIC    1
        #అయితే_ముగింపు
/*-----------------------------------------------------------*/

    #అయితే_ముగింపు /* __ASSEMBLER__ */

/* Architecture specifics. These can be used by assembly files as well. */
    #నిర్వచించు పోర్టు_దొంతర_GROWTH               ( -1 )
    #నిర్వచించు పోర్టు_TICK_PERIOD_MS             ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
    #నిర్వచించు పోర్టు_BYTE_ALIGNMENT             8
    #నిర్వచించు పోర్టు_CRITICAL_NESTING_లోపల_TCB    1
    #నిర్వచించు పోర్టు_MAX_CORE_లెక్క             8
    #నిర్వచితం_కాకపోతే config_సంఖ్య_యొక్క_CORES
        #నిర్వచించు config_సంఖ్య_యొక్క_CORES      1
    #అయితే_ముగింపు

/* This may be set to zero in the config file if the rtos_time
 *  functions are not needed or if it is incremented elsewhere. */
    #నిర్వచితం_కాకపోతే config_UPDATE_RTOS_సమయం_FROM_TICK_ISR
        #నిర్వచించు config_UPDATE_RTOS_సమయం_FROM_TICK_ISR    1
    #అయితే_ముగింపు

/*
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
    #నిర్వచించు పోర్టు_THREAD_CONTEXT_దొంతర_GROWTH    RTOS_SUPPORT_అంతరాయం_దొంతర_GROWTH

    #నిర్వచితం_కాకపోతే __ASSEMBLER__

/* Check validity of number of cores specified in config */
        #ఒకవేళ ( config_సంఖ్య_యొక్క_CORES < 1 || పోర్టు_MAX_CORE_లెక్క < config_సంఖ్య_యొక్క_CORES )
            #దోషం "Invalid number of cores specified in config!"
        #అయితే_ముగింపు

        #నిర్వచించు పోర్టు_జ్ఞాపకం_BARRIER()                  RTOS_జ్ఞాపకం_BARRIER()
        #నిర్వచించు పోర్టు_TASK_దొంతర_లోతు( px_Task_సంకేతం )    RTOS_THREAD_దొంతర_కొలత( px_Task_సంకేతం )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
        #నిర్వచించు పోర్టు_YIELD()    asm అస్థిర ( "KCALLI_lu6 0" ::: "memory" )

        #నిర్వచించు పోర్టు_చివర_SWITCHING_ISR( xSwitchRequired )               \
    చేయి                                                                 \
    {                                                                  \
        ఒకవేళ( xSwitchRequired != pdFALSE )                               \
        {                                                              \
            బాహ్య uint32_t ul_పోర్టు_Yield_Required[ పోర్టు_MAX_CORE_లెక్క ]; \
            ul_పోర్టు_Yield_Required[ పోర్టు_GET_CORE_ID() ] = pdTRUE;         \
        }                                                              \
    } అయితే( 0 )

        #నిర్వచించు పోర్టు_YIELD_FROM_ISR( x )    పోర్టు_చివర_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* SMP utilities. */
        #నిర్వచించు పోర్టు_GET_CORE_ID()      rtos_core_id_get()

        శూన్య v_పోర్టు_Yield_Other_Core( పూర్ణాంకం xOtherCoreID );
        #నిర్వచించు పోర్టు_YIELD_CORE( x )    v_పోర్టు_Yield_Other_Core( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
        #నిర్వచితం_కాకపోతే config_USE_పోర్టు_OPTIMISED_TASK_SELECTION
            #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    0
        #అయితే_ముగింపు

        #ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
            #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ప్రాధాన్యత ) )
            #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ప్రాధాన్యత ) )

/*-----------------------------------------------------------*/

            #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities )    ux_శిఖరం_ప్రాధాన్యత = ( 31UL - ( uint32_t ) __builtin_clz( uxReadyPriorities ) )

        #అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */

        #నిర్వచించు పోర్టు_GET_అంతరాయం_STATE()                 rtos_అంతరాయం_ముసుగు_get()

/*
 * This differs from the standard portDISABLE_INTERRUPTS()
 * in that it also returns what the interrupt state was
 * before it disabling interrupts.
 */
        #నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()                  rtos_అంతరాయం_ముసుగు_all()

        #నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()                   rtos_అంతరాయం_unmask_all()

/*
 * Port set interrupt mask and clear interrupt mask.
 */
        #నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు()                  rtos_అంతరాయం_ముసుగు_all()
        #నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు( ulState )       rtos_అంతరాయం_ముసుగు_సమితి( ulState )

/*
 * Will enable interrupts if ulState is non-zero.
 */
        #నిర్వచించు పోర్టు_RESTORE_INTERRUPTS( ulState )         rtos_అంతరాయం_ముసుగు_సమితి( ulState )

/*
 * Returns non-zero if currently running in an
 * ISR or otherwise in kernel mode.
 */
        #నిర్వచించు పోర్టు_CHECK_IF_లోపల_ISR()                     rtos_isr_running()

        #నిర్వచించు పోర్టు_ASSERT_IF_లోపల_ISR()                    configASSERT( పోర్టు_CHECK_IF_లోపల_ISR() == 0 )

        #నిర్వచించు పోర్టు_GET_ISR_తాళం( xCoreID )               చేయి{ ( శూన్య )( xCoreID ); rtos_తాళం_acquire( 0 ); } అయితే( 0 )
        #నిర్వచించు పోర్టు_RELEASE_ISR_తాళం( xCoreID )           చేయి{ ( శూన్య )( xCoreID ); rtos_తాళం_release( 0 ); } అయితే( 0 )
        #నిర్వచించు పోర్టు_GET_TASK_తాళం( xCoreID )              చేయి{ ( శూన్య )( xCoreID ); rtos_తాళం_acquire( 1 ); } అయితే( 0 )
        #నిర్వచించు పోర్టు_RELEASE_TASK_తాళం( xCoreID )          చేయి{ ( శూన్య )( xCoreID ); rtos_తాళం_release( 1 ); } అయితే( 0 )


        శూన్య vTaskEnterCritical( శూన్య );
        శూన్య vTaskExitCritical( శూన్య );
        #నిర్వచించు పోర్టు_ENTER_CRITICAL()    vTaskEnterCritical()
        #నిర్వచించు పోర్టు_EXIT_CRITICAL()     vTaskExitCritical()

        బాహ్య UBaseType_t vTaskEnterCriticalFromISR( శూన్య );
        బాహ్య శూన్య vTaskExitCriticalFromISR( UBaseType_t ux_Saved_అంతరాయం_స్థితి );
        #నిర్వచించు పోర్టు_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
        #నిర్వచించు పోర్టు_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

/*-----------------------------------------------------------*/

/* Runtime stats support */
        #ఒకవేళ ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 )
            పూర్ణాంకం xscope_gettime( శూన్య );
            #నిర్వచించు పోర్టు_CONFIGURE_TIMER_FOR_నిరంతరం_సమయం_STATS()    /* nothing needed here */
            #నిర్వచించు పోర్టు_GET_నిరంతరం_సమయం_COUNTER_విలువ()            xscope_gettime()
        #అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Maps sprintf and snprintf to the lite version in lib_rtos_support */
        #ఒకవేళ ( configUSE_DEBUG_SPRINTF == 1 )
            #నిర్వచించు sprintf( ... )     rtos_sprintf( __VA_ARGS__ )
            #నిర్వచించు snprintf( ... )    rtos_snprintf( __VA_ARGS__ )
        #అయితే_ముగింపు

/* Attribute for the pxCallbackFunction member of the Timer_t struct.
 * Required by xcc to calculate stack usage. */
        #నిర్వచించు పోర్టు_TIMER_CALLBACK_ATTRIBUTE    __attribute__( ( fptrgroup( "timerCallbackGroup" ) ) )

/* Timer callback function macros. For xcc this ensures they get added to the timer callback
 * group so that stack usage for certain functions in timers.c can be calculated. */
        #నిర్వచించు పోర్టు_TIMER_CALLBACK_FUNCTION_PROTO( vFunction, xTimer )    శూన్య vFunction( TimerHandle_t xTimer )
        #నిర్వచించు పోర్టు_TIMER_CALLBACK_FUNCTION( vFunction, xTimer )          పోర్టు_TIMER_CALLBACK_ATTRIBUTE శూన్య vFunction( TimerHandle_t xTimer )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
        #నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
        #నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )
/*-----------------------------------------------------------*/


        #నిర్వచితమైతే __cplusplus
}
        #అయితే_ముగింపు

    #అయితే_ముగింపు /* __ASSEMBLER__ */

#అయితే_ముగింపు /* PORTMACRO_H */
