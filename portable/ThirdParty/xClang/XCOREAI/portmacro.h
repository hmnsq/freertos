/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#جے_بنا_تعریف PORTMACRO_H
    #تعریف_کرو PORTMACRO_H

    #جے_بنا_تعریف __ASSEMBLER__

/* Inclusion of xc1.h will result in clock being defined as a type.
 * By default, FreeRTOS will require standard time.h, where clock is a function.
 */
        #جے_بنا_تعریف USE_XCORE_CLOCK_TYPE
            #تعریف_کرو _clock_defined
        #جے_انت

        #ضمن <xs1.h>
        #ضمن "rtos_support.h"

        #جے_تعریف_شدہ __cplusplus
        خارجي "C" {
        #جے_انت

/* Type definitions. */
        #تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
        تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
        تعريفنوع مزدوج           پورٹ_DOUBLE;
        تعريفنوع int32_t          ادھار_Type_t;
        تعريفنوع uint32_t         UBaseType_t;

        #تعریف_کرو پورٹ_ادھار_TYPE    ادھار_Type_t

        #إذا ( config_USE_16_ثنائی_ہندسہ_TICKS == 1 )
            تعريفنوع uint16_t     TickType_t;
            #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
        #وإلا
            تعريفنوع uint32_t     TickType_t;
            #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
            #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
        #جے_انت
/*-----------------------------------------------------------*/

    #جے_انت /* __ASSEMBLER__ */

/* Architecture specifics. These can be used by assembly files as well. */
    #تعریف_کرو پورٹ_ڈھیر_GROWTH               ( -1 )
    #تعریف_کرو پورٹ_TICK_PERIOD_MS             ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT             8
    #تعریف_کرو پورٹ_CRITICAL_NESTING_وچ_TCB    1
    #تعریف_کرو پورٹ_MAX_CORE_گنتی             8
    #جے_بنا_تعریف config_نمبر_دا_CORES
        #تعریف_کرو config_نمبر_دا_CORES      1
    #جے_انت

/* This may be set to zero in the config file if the rtos_time
 *  functions are not needed or if it is incremented elsewhere. */
    #جے_بنا_تعریف config_UPDATE_RTOS_ویلا_FROM_TICK_ISR
        #تعریف_کرو config_UPDATE_RTOS_ویلا_FROM_TICK_ISR    1
    #جے_انت

/*
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
    #تعریف_کرو پورٹ_THREAD_CONTEXT_ڈھیر_GROWTH    RTOS_SUPPORT_رکاوٹ_ڈھیر_GROWTH

    #جے_بنا_تعریف __ASSEMBLER__

/* Check validity of number of cores specified in config */
        #إذا ( config_نمبر_دا_CORES < 1 || پورٹ_MAX_CORE_گنتی < config_نمبر_دا_CORES )
            #غلطی "Invalid number of cores specified in config!"
        #جے_انت

        #تعریف_کرو پورٹ_حافظہ_BARRIER()                  RTOS_حافظہ_BARRIER()
        #تعریف_کرو پورٹ_TASK_ڈھیر_ڈونگھائی( px_Task_کوڈ )    RTOS_THREAD_ڈھیر_ناپ( px_Task_کوڈ )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
        #تعریف_کرو پورٹ_YIELD()    asm متطاير ( "KCALLI_lu6 0" ::: "memory" )

        #تعریف_کرو پورٹ_سرا_SWITCHING_ISR( xSwitchRequired )               \
    افعل                                                                 \
    {                                                                  \
        إذا( xSwitchRequired != pdFALSE )                               \
        {                                                              \
            خارجي uint32_t ul_پورٹ_Yield_Required[ پورٹ_MAX_CORE_گنتی ]; \
            ul_پورٹ_Yield_Required[ پورٹ_GET_CORE_ID() ] = pdTRUE;         \
        }                                                              \
    } طالما( 0 )

        #تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_سرا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* SMP utilities. */
        #تعریف_کرو پورٹ_GET_CORE_ID()      rtos_core_id_get()

        فراغ v_پورٹ_Yield_Other_Core( صحيح xOtherCoreID );
        #تعریف_کرو پورٹ_YIELD_CORE( x )    v_پورٹ_Yield_Other_Core( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
        #جے_بنا_تعریف config_USE_پورٹ_OPTIMISED_TASK_SELECTION
            #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    0
        #جے_انت

        #إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
            #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
            #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

            #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31UL - ( uint32_t ) __builtin_clz( uxReadyPriorities ) )

        #جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */

        #تعریف_کرو پورٹ_GET_رکاوٹ_STATE()                 rtos_رکاوٹ_نقاب_get()

/*
 * This differs from the standard portDISABLE_INTERRUPTS()
 * in that it also returns what the interrupt state was
 * before it disabling interrupts.
 */
        #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  rtos_رکاوٹ_نقاب_all()

        #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   rtos_رکاوٹ_unmask_all()

/*
 * Port set interrupt mask and clear interrupt mask.
 */
        #تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب()                  rtos_رکاوٹ_نقاب_all()
        #تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب( ulState )       rtos_رکاوٹ_نقاب_سیٹ( ulState )

/*
 * Will enable interrupts if ulState is non-zero.
 */
        #تعریف_کرو پورٹ_RESTORE_INTERRUPTS( ulState )         rtos_رکاوٹ_نقاب_سیٹ( ulState )

/*
 * Returns non-zero if currently running in an
 * ISR or otherwise in kernel mode.
 */
        #تعریف_کرو پورٹ_CHECK_IF_وچ_ISR()                     rtos_isr_running()

        #تعریف_کرو پورٹ_ASSERT_IF_وچ_ISR()                    configASSERT( پورٹ_CHECK_IF_وچ_ISR() == 0 )

        #تعریف_کرو پورٹ_GET_ISR_جندرا( xCoreID )               افعل{ ( فراغ )( xCoreID ); rtos_جندرا_acquire( 0 ); } طالما( 0 )
        #تعریف_کرو پورٹ_RELEASE_ISR_جندرا( xCoreID )           افعل{ ( فراغ )( xCoreID ); rtos_جندرا_release( 0 ); } طالما( 0 )
        #تعریف_کرو پورٹ_GET_TASK_جندرا( xCoreID )              افعل{ ( فراغ )( xCoreID ); rtos_جندرا_acquire( 1 ); } طالما( 0 )
        #تعریف_کرو پورٹ_RELEASE_TASK_جندرا( xCoreID )          افعل{ ( فراغ )( xCoreID ); rtos_جندرا_release( 1 ); } طالما( 0 )


        فراغ vTaskEnterCritical( فراغ );
        فراغ vTaskExitCritical( فراغ );
        #تعریف_کرو پورٹ_ENTER_CRITICAL()    vTaskEnterCritical()
        #تعریف_کرو پورٹ_EXIT_CRITICAL()     vTaskExitCritical()

        خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
        خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_رکاوٹ_حالت );
        #تعریف_کرو پورٹ_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
        #تعریف_کرو پورٹ_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

/*-----------------------------------------------------------*/

/* Runtime stats support */
        #إذا ( config_GENERATE_لگاتار_ویلا_STATS == 1 )
            صحيح xscope_gettime( فراغ );
            #تعریف_کرو پورٹ_CONFIGURE_TIMER_FOR_لگاتار_ویلا_STATS()    /* nothing needed here */
            #تعریف_کرو پورٹ_GET_لگاتار_ویلا_COUNTER_قدر()            xscope_gettime()
        #جے_انت
/*-----------------------------------------------------------*/

/* Maps sprintf and snprintf to the lite version in lib_rtos_support */
        #إذا ( configUSE_DEBUG_SPRINTF == 1 )
            #تعریف_کرو sprintf( ... )     rtos_sprintf( __VA_ARGS__ )
            #تعریف_کرو snprintf( ... )    rtos_snprintf( __VA_ARGS__ )
        #جے_انت

/* Attribute for the pxCallbackFunction member of the Timer_t struct.
 * Required by xcc to calculate stack usage. */
        #تعریف_کرو پورٹ_TIMER_CALLBACK_ATTRIBUTE    __attribute__( ( fptrgroup( "timerCallbackGroup" ) ) )

/* Timer callback function macros. For xcc this ensures they get added to the timer callback
 * group so that stack usage for certain functions in timers.c can be calculated. */
        #تعریف_کرو پورٹ_TIMER_CALLBACK_FUNCTION_PROTO( vFunction, xTimer )    فراغ vFunction( TimerHandle_t xTimer )
        #تعریف_کرو پورٹ_TIMER_CALLBACK_FUNCTION( vFunction, xTimer )          پورٹ_TIMER_CALLBACK_ATTRIBUTE فراغ vFunction( TimerHandle_t xTimer )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
        #تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
        #تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/


        #جے_تعریف_شدہ __cplusplus
}
        #جے_انت

    #جے_انت /* __ASSEMBLER__ */

#جے_انت /* PORTMACRO_H */
