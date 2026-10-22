/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#اگر_تعریف_نشده PORTMACRO_H
    #تعریف_کن PORTMACRO_H

    #اگر_تعریف_نشده __ASSEMBLER__

/* Inclusion of xc1.h will result in clock being defined as a type.
 * By default, FreeRTOS will require standard time.h, where clock is a function.
 */
        #اگر_تعریف_نشده USE_XCORE_CLOCK_TYPE
            #تعریف_کن _clock_defined
        #پایان_اگر

        #ضمن <xs1.h>
        #ضمن "rtos_support.h"

        #اگر_تعریف_شده __cplusplus
        خارجي "C" {
        #پایان_اگر

/* Type definitions. */
        #تعریف_کن پورت_پشته_TYPE    uint32_t
        تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
        تعريفنوع مزدوج           پورت_DOUBLE;
        تعريفنوع int32_t          پایه_Type_t;
        تعريفنوع uint32_t         UBaseType_t;

        #تعریف_کن پورت_پایه_TYPE    پایه_Type_t

        #إذا ( config_USE_16_بیت_TICKS == 1 )
            تعريفنوع uint16_t     TickType_t;
            #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffff
        #وإلا
            تعريفنوع uint32_t     TickType_t;
            #تعریف_کن پورت_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
            #تعریف_کن پورت_TICK_TYPE_IS_ATOMIC    1
        #پایان_اگر
/*-----------------------------------------------------------*/

    #پایان_اگر /* __ASSEMBLER__ */

/* Architecture specifics. These can be used by assembly files as well. */
    #تعریف_کن پورت_پشته_GROWTH               ( -1 )
    #تعریف_کن پورت_TICK_PERIOD_MS             ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
    #تعریف_کن پورت_BYTE_ALIGNMENT             8
    #تعریف_کن پورت_CRITICAL_NESTING_درون_TCB    1
    #تعریف_کن پورت_MAX_CORE_شمار             8
    #اگر_تعریف_نشده config_عدد_از_CORES
        #تعریف_کن config_عدد_از_CORES      1
    #پایان_اگر

/* This may be set to zero in the config file if the rtos_time
 *  functions are not needed or if it is incremented elsewhere. */
    #اگر_تعریف_نشده config_UPDATE_RTOS_زمان_FROM_TICK_ISR
        #تعریف_کن config_UPDATE_RTOS_زمان_FROM_TICK_ISR    1
    #پایان_اگر

/*
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
    #تعریف_کن پورت_THREAD_CONTEXT_پشته_GROWTH    RTOS_SUPPORT_وقفه_پشته_GROWTH

    #اگر_تعریف_نشده __ASSEMBLER__

/* Check validity of number of cores specified in config */
        #إذا ( config_عدد_از_CORES < 1 || پورت_MAX_CORE_شمار < config_عدد_از_CORES )
            #خطا "Invalid number of cores specified in config!"
        #پایان_اگر

        #تعریف_کن پورت_حافظه_BARRIER()                  RTOS_حافظه_BARRIER()
        #تعریف_کن پورت_TASK_پشته_عمق( px_Task_کد )    RTOS_THREAD_پشته_اندازه( px_Task_کد )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
        #تعریف_کن پورت_YIELD()    asm متطاير ( "KCALLI_lu6 0" ::: "memory" )

        #تعریف_کن پورت_انتها_SWITCHING_ISR( xSwitchRequired )               \
    افعل                                                                 \
    {                                                                  \
        إذا( xSwitchRequired != pdFALSE )                               \
        {                                                              \
            خارجي uint32_t ul_پورت_Yield_Required[ پورت_MAX_CORE_شمار ]; \
            ul_پورت_Yield_Required[ پورت_GET_CORE_ID() ] = pdTRUE;         \
        }                                                              \
    } طالما( 0 )

        #تعریف_کن پورت_YIELD_FROM_ISR( x )    پورت_انتها_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* SMP utilities. */
        #تعریف_کن پورت_GET_CORE_ID()      rtos_core_id_get()

        فراغ v_پورت_Yield_Other_Core( صحيح xOtherCoreID );
        #تعریف_کن پورت_YIELD_CORE( x )    v_پورت_Yield_Other_Core( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
        #اگر_تعریف_نشده config_USE_پورت_OPTIMISED_TASK_SELECTION
            #تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION    0
        #پایان_اگر

        #إذا config_USE_پورت_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
            #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_اولویت ) )
            #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_اولویت ) )

/*-----------------------------------------------------------*/

            #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    ux_بالاترین_اولویت = ( 31UL - ( uint32_t ) __builtin_clz( uxReadyPriorities ) )

        #پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */

        #تعریف_کن پورت_GET_وقفه_STATE()                 rtos_وقفه_ماسک_get()

/*
 * This differs from the standard portDISABLE_INTERRUPTS()
 * in that it also returns what the interrupt state was
 * before it disabling interrupts.
 */
        #تعریف_کن پورت_DISABLE_INTERRUPTS()                  rtos_وقفه_ماسک_all()

        #تعریف_کن پورت_ENABLE_INTERRUPTS()                   rtos_وقفه_unmask_all()

/*
 * Port set interrupt mask and clear interrupt mask.
 */
        #تعریف_کن پورت_مجموعه_وقفه_ماسک()                  rtos_وقفه_ماسک_all()
        #تعریف_کن پورت_CLEAR_وقفه_ماسک( ulState )       rtos_وقفه_ماسک_مجموعه( ulState )

/*
 * Will enable interrupts if ulState is non-zero.
 */
        #تعریف_کن پورت_RESTORE_INTERRUPTS( ulState )         rtos_وقفه_ماسک_مجموعه( ulState )

/*
 * Returns non-zero if currently running in an
 * ISR or otherwise in kernel mode.
 */
        #تعریف_کن پورت_CHECK_IF_درون_ISR()                     rtos_isr_running()

        #تعریف_کن پورت_ASSERT_IF_درون_ISR()                    configASSERT( پورت_CHECK_IF_درون_ISR() == 0 )

        #تعریف_کن پورت_GET_ISR_قفل( xCoreID )               افعل{ ( فراغ )( xCoreID ); rtos_قفل_acquire( 0 ); } طالما( 0 )
        #تعریف_کن پورت_RELEASE_ISR_قفل( xCoreID )           افعل{ ( فراغ )( xCoreID ); rtos_قفل_release( 0 ); } طالما( 0 )
        #تعریف_کن پورت_GET_TASK_قفل( xCoreID )              افعل{ ( فراغ )( xCoreID ); rtos_قفل_acquire( 1 ); } طالما( 0 )
        #تعریف_کن پورت_RELEASE_TASK_قفل( xCoreID )          افعل{ ( فراغ )( xCoreID ); rtos_قفل_release( 1 ); } طالما( 0 )


        فراغ vTaskEnterCritical( فراغ );
        فراغ vTaskExitCritical( فراغ );
        #تعریف_کن پورت_ENTER_CRITICAL()    vTaskEnterCritical()
        #تعریف_کن پورت_EXIT_CRITICAL()     vTaskExitCritical()

        خارجي UBaseType_t vTaskEnterCriticalFromISR( فراغ );
        خارجي فراغ vTaskExitCriticalFromISR( UBaseType_t ux_Saved_وقفه_وضعیت );
        #تعریف_کن پورت_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
        #تعریف_کن پورت_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

/*-----------------------------------------------------------*/

/* Runtime stats support */
        #إذا ( config_GENERATE_پیاپی_زمان_STATS == 1 )
            صحيح xscope_gettime( فراغ );
            #تعریف_کن پورت_CONFIGURE_TIMER_FOR_پیاپی_زمان_STATS()    /* nothing needed here */
            #تعریف_کن پورت_GET_پیاپی_زمان_COUNTER_مقدار()            xscope_gettime()
        #پایان_اگر
/*-----------------------------------------------------------*/

/* Maps sprintf and snprintf to the lite version in lib_rtos_support */
        #إذا ( configUSE_DEBUG_SPRINTF == 1 )
            #تعریف_کن sprintf( ... )     rtos_sprintf( __VA_ARGS__ )
            #تعریف_کن snprintf( ... )    rtos_snprintf( __VA_ARGS__ )
        #پایان_اگر

/* Attribute for the pxCallbackFunction member of the Timer_t struct.
 * Required by xcc to calculate stack usage. */
        #تعریف_کن پورت_TIMER_CALLBACK_ATTRIBUTE    __attribute__( ( fptrgroup( "timerCallbackGroup" ) ) )

/* Timer callback function macros. For xcc this ensures they get added to the timer callback
 * group so that stack usage for certain functions in timers.c can be calculated. */
        #تعریف_کن پورت_TIMER_CALLBACK_FUNCTION_PROTO( vFunction, xTimer )    فراغ vFunction( TimerHandle_t xTimer )
        #تعریف_کن پورت_TIMER_CALLBACK_FUNCTION( vFunction, xTimer )          پورت_TIMER_CALLBACK_ATTRIBUTE فراغ vFunction( TimerHandle_t xTimer )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
        #تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
        #تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*-----------------------------------------------------------*/


        #اگر_تعریف_شده __cplusplus
}
        #پایان_اگر

    #پایان_اگر /* __ASSEMBLER__ */

#پایان_اگر /* PORTMACRO_H */
