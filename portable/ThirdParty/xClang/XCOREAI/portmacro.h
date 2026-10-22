/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#اگر_غیر_تعریف_شدہ PORTMACRO_H
    #تعریف_کرو PORTMACRO_H

    #اگر_غیر_تعریف_شدہ __ASSEMBLER__

/* Inclusion of xc1.h will result in clock being defined as a type.
 * By default, FreeRTOS will require standard time.h, where clock is a function.
 */
        #اگر_غیر_تعریف_شدہ USE_XCORE_CLOCK_TYPE
            #تعریف_کرو _clock_defined
        #اگر_ختم

        #شامل <xs1.h>
        #شامل "rtos_support.h"

        #اگر_تعریف_شدہ __cplusplus
        خارجی "C" {
        #اگر_ختم

/* Type definitions. */
        #تعریف_کرو پورٹ_ڈھیر_TYPE    uint32_t
        قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
        قسمتعریف دوہرا           پورٹ_DOUBLE;
        قسمتعریف int32_t          بنیاد_Type_t;
        قسمتعریف uint32_t         UBaseType_t;

        #تعریف_کرو پورٹ_بنیاد_TYPE    بنیاد_Type_t

        #اگر ( config_USE_16_ثنائی_ہندسہ_TICKS == 1 )
            قسمتعریف uint16_t     TickType_t;
            #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffff
        #ورنہ
            قسمتعریف uint32_t     TickType_t;
            #تعریف_کرو پورٹ_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
            #تعریف_کرو پورٹ_TICK_TYPE_IS_ATOMIC    1
        #اگر_ختم
/*-----------------------------------------------------------*/

    #اگر_ختم /* __ASSEMBLER__ */

/* Architecture specifics. These can be used by assembly files as well. */
    #تعریف_کرو پورٹ_ڈھیر_GROWTH               ( -1 )
    #تعریف_کرو پورٹ_TICK_PERIOD_MS             ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT             8
    #تعریف_کرو پورٹ_CRITICAL_NESTING_اندر_TCB    1
    #تعریف_کرو پورٹ_MAX_CORE_گنتی             8
    #اگر_غیر_تعریف_شدہ config_نمبر_کا_CORES
        #تعریف_کرو config_نمبر_کا_CORES      1
    #اگر_ختم

/* This may be set to zero in the config file if the rtos_time
 *  functions are not needed or if it is incremented elsewhere. */
    #اگر_غیر_تعریف_شدہ config_UPDATE_RTOS_وقت_FROM_TICK_ISR
        #تعریف_کرو config_UPDATE_RTOS_وقت_FROM_TICK_ISR    1
    #اگر_ختم

/*
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
    #تعریف_کرو پورٹ_THREAD_CONTEXT_ڈھیر_GROWTH    RTOS_SUPPORT_مداخلت_ڈھیر_GROWTH

    #اگر_غیر_تعریف_شدہ __ASSEMBLER__

/* Check validity of number of cores specified in config */
        #اگر ( config_نمبر_کا_CORES < 1 || پورٹ_MAX_CORE_گنتی < config_نمبر_کا_CORES )
            #غلطی "Invalid number of cores specified in config!"
        #اگر_ختم

        #تعریف_کرو پورٹ_حافظہ_BARRIER()                  RTOS_حافظہ_BARRIER()
        #تعریف_کرو پورٹ_TASK_ڈھیر_گہرائی( px_Task_رمز )    RTOS_THREAD_ڈھیر_سائز( px_Task_رمز )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
        #تعریف_کرو پورٹ_YIELD()    asm متلون ( "KCALLI_lu6 0" ::: "memory" )

        #تعریف_کرو پورٹ_انتہا_SWITCHING_ISR( xSwitchRequired )               \
    کرو                                                                 \
    {                                                                  \
        اگر( xSwitchRequired != pdFALSE )                               \
        {                                                              \
            خارجی uint32_t ul_پورٹ_Yield_Required[ پورٹ_MAX_CORE_گنتی ]; \
            ul_پورٹ_Yield_Required[ پورٹ_GET_CORE_ID() ] = pdTRUE;         \
        }                                                              \
    } جب( 0 )

        #تعریف_کرو پورٹ_YIELD_FROM_ISR( x )    پورٹ_انتہا_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* SMP utilities. */
        #تعریف_کرو پورٹ_GET_CORE_ID()      rtos_core_id_get()

        خالی v_پورٹ_Yield_Other_Core( صحیح xOtherCoreID );
        #تعریف_کرو پورٹ_YIELD_CORE( x )    v_پورٹ_Yield_Other_Core( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
        #اگر_غیر_تعریف_شدہ config_USE_پورٹ_OPTIMISED_TASK_SELECTION
            #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    0
        #اگر_ختم

        #اگر config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
            #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
            #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

            #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31UL - ( uint32_t ) __builtin_clz( uxReadyPriorities ) )

        #اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */

        #تعریف_کرو پورٹ_GET_مداخلت_STATE()                 rtos_مداخلت_نقاب_get()

/*
 * This differs from the standard portDISABLE_INTERRUPTS()
 * in that it also returns what the interrupt state was
 * before it disabling interrupts.
 */
        #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()                  rtos_مداخلت_نقاب_all()

        #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()                   rtos_مداخلت_unmask_all()

/*
 * Port set interrupt mask and clear interrupt mask.
 */
        #تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب()                  rtos_مداخلت_نقاب_all()
        #تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب( ulState )       rtos_مداخلت_نقاب_سیٹ( ulState )

/*
 * Will enable interrupts if ulState is non-zero.
 */
        #تعریف_کرو پورٹ_RESTORE_INTERRUPTS( ulState )         rtos_مداخلت_نقاب_سیٹ( ulState )

/*
 * Returns non-zero if currently running in an
 * ISR or otherwise in kernel mode.
 */
        #تعریف_کرو پورٹ_CHECK_IF_اندر_ISR()                     rtos_isr_running()

        #تعریف_کرو پورٹ_ASSERT_IF_اندر_ISR()                    configASSERT( پورٹ_CHECK_IF_اندر_ISR() == 0 )

        #تعریف_کرو پورٹ_GET_ISR_تالا( xCoreID )               کرو{ ( خالی )( xCoreID ); rtos_تالا_acquire( 0 ); } جب( 0 )
        #تعریف_کرو پورٹ_RELEASE_ISR_تالا( xCoreID )           کرو{ ( خالی )( xCoreID ); rtos_تالا_release( 0 ); } جب( 0 )
        #تعریف_کرو پورٹ_GET_TASK_تالا( xCoreID )              کرو{ ( خالی )( xCoreID ); rtos_تالا_acquire( 1 ); } جب( 0 )
        #تعریف_کرو پورٹ_RELEASE_TASK_تالا( xCoreID )          کرو{ ( خالی )( xCoreID ); rtos_تالا_release( 1 ); } جب( 0 )


        خالی vTaskEnterCritical( خالی );
        خالی vTaskExitCritical( خالی );
        #تعریف_کرو پورٹ_ENTER_CRITICAL()    vTaskEnterCritical()
        #تعریف_کرو پورٹ_EXIT_CRITICAL()     vTaskExitCritical()

        خارجی UBaseType_t vTaskEnterCriticalFromISR( خالی );
        خارجی خالی vTaskExitCriticalFromISR( UBaseType_t ux_Saved_مداخلت_حالت );
        #تعریف_کرو پورٹ_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
        #تعریف_کرو پورٹ_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

/*-----------------------------------------------------------*/

/* Runtime stats support */
        #اگر ( config_GENERATE_تسلسل_وقت_STATS == 1 )
            صحیح xscope_gettime( خالی );
            #تعریف_کرو پورٹ_CONFIGURE_TIMER_FOR_تسلسل_وقت_STATS()    /* nothing needed here */
            #تعریف_کرو پورٹ_GET_تسلسل_وقت_شمار_قدر()            xscope_gettime()
        #اگر_ختم
/*-----------------------------------------------------------*/

/* Maps sprintf and snprintf to the lite version in lib_rtos_support */
        #اگر ( configUSE_DEBUG_SPRINTF == 1 )
            #تعریف_کرو sprintf( ... )     rtos_sprintf( __VA_ARGS__ )
            #تعریف_کرو snprintf( ... )    rtos_snprintf( __VA_ARGS__ )
        #اگر_ختم

/* Attribute for the pxCallbackFunction member of the Timer_t struct.
 * Required by xcc to calculate stack usage. */
        #تعریف_کرو پورٹ_TIMER_CALLBACK_ATTRIBUTE    __attribute__( ( fptrgroup( "timerCallbackGroup" ) ) )

/* Timer callback function macros. For xcc this ensures they get added to the timer callback
 * group so that stack usage for certain functions in timers.c can be calculated. */
        #تعریف_کرو پورٹ_TIMER_CALLBACK_FUNCTION_PROTO( vFunction, xTimer )    خالی vFunction( TimerHandle_t xTimer )
        #تعریف_کرو پورٹ_TIMER_CALLBACK_FUNCTION( vFunction, xTimer )          پورٹ_TIMER_CALLBACK_ATTRIBUTE خالی vFunction( TimerHandle_t xTimer )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
        #تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
        #تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )
/*-----------------------------------------------------------*/


        #اگر_تعریف_شدہ __cplusplus
}
        #اگر_ختم

    #اگر_ختم /* __ASSEMBLER__ */

#اگر_ختم /* PORTMACRO_H */
