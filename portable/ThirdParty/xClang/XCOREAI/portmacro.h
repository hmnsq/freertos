/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#यदि_अपरिभाषितम् PORTMACRO_H
    #परिभाषय PORTMACRO_H

    #यदि_अपरिभाषितम् __ASSEMBLER__

/* Inclusion of xc1.h will result in clock being defined as a type.
 * By default, FreeRTOS will require standard time.h, where clock is a function.
 */
        #यदि_अपरिभाषितम् USE_XCORE_CLOCK_TYPE
            #परिभाषय _clock_defined
        #यदि_अन्तः

        #अन्तर्भाव <xs1.h>
        #अन्तर्भाव "rtos_support.h"

        #यदि_परिभाषितम् __cplusplus
        बाह्य "C" {
        #यदि_अन्तः

/* Type definitions. */
        #परिभाषय पत्तनम्_राशिः_TYPE    uint32_t
        प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
        प्रकारनिर्देश द्विगुण           पत्तनम्_DOUBLE;
        प्रकारनिर्देश int32_t          आधारः_Type_t;
        प्रकारनिर्देश uint32_t         UBaseType_t;

        #परिभाषय पत्तनम्_आधारः_TYPE    आधारः_Type_t

        #यदि ( configUSE_16_BIT_TICKS == 1 )
            प्रकारनिर्देश uint16_t     TickType_t;
            #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffff
        #अन्यथा
            प्रकारनिर्देश uint32_t     TickType_t;
            #परिभाषय पत्तनम्_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
            #परिभाषय पत्तनम्_TICK_TYPE_IS_ATOMIC    1
        #यदि_अन्तः
/*-----------------------------------------------------------*/

    #यदि_अन्तः /* __ASSEMBLER__ */

/* Architecture specifics. These can be used by assembly files as well. */
    #परिभाषय पत्तनम्_राशिः_GROWTH               ( -1 )
    #परिभाषय पत्तनम्_TICK_PERIOD_MS             ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
    #परिभाषय पत्तनम्_BYTE_ALIGNMENT             8
    #परिभाषय पत्तनम्_CRITICAL_NESTING_अन्तर्_TCB    1
    #परिभाषय पत्तनम्_MAX_CORE_गणनम्             8
    #यदि_अपरिभाषितम् config_सङ्ख्या_सम्बन्धि_CORES
        #परिभाषय config_सङ्ख्या_सम्बन्धि_CORES      1
    #यदि_अन्तः

/* This may be set to zero in the config file if the rtos_time
 *  functions are not needed or if it is incremented elsewhere. */
    #यदि_अपरिभाषितम् configUPDATE_RTOS_TIME_FROM_TICK_ISR
        #परिभाषय configUPDATE_RTOS_TIME_FROM_TICK_ISR    1
    #यदि_अन्तः

/*
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
    #परिभाषय पत्तनम्_THREAD_CONTEXT_राशिः_GROWTH    RTOS_SUPPORT_व्यवधानम्_राशिः_GROWTH

    #यदि_अपरिभाषितम् __ASSEMBLER__

/* Check validity of number of cores specified in config */
        #यदि ( config_सङ्ख्या_सम्बन्धि_CORES < 1 || पत्तनम्_MAX_CORE_गणनम् < config_सङ्ख्या_सम्बन्धि_CORES )
            #दोषः "Invalid number of cores specified in config!"
        #यदि_अन्तः

        #परिभाषय पत्तनम्_स्मृतिः_BARRIER()                  RTOS_स्मृतिः_BARRIER()
        #परिभाषय पत्तनम्_TASK_राशिः_गभीरता( px_Task_संहिता )    RTOS_THREAD_राशिः_आकार( px_Task_संहिता )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
        #परिभाषय पत्तनम्_YIELD()    asm चञ्चल ( "KCALLI_lu6 0" ::: "memory" )

        #परिभाषय पत्तनम्_अन्तः_SWITCHING_ISR( xSwitchRequired )               \
    कुरु                                                                 \
    {                                                                  \
        यदि( xSwitchRequired != pdFALSE )                               \
        {                                                              \
            बाह्य uint32_t ul_पत्तनम्_Yield_Required[ पत्तनम्_MAX_CORE_गणनम् ]; \
            ul_पत्तनम्_Yield_Required[ पत्तनम्_GET_CORE_ID() ] = pdTRUE;         \
        }                                                              \
    } यावत्( 0 )

        #परिभाषय पत्तनम्_YIELD_FROM_ISR( x )    पत्तनम्_अन्तः_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* SMP utilities. */
        #परिभाषय पत्तनम्_GET_CORE_ID()      rtos_core_id_get()

        शून्य v_पत्तनम्_Yield_Other_Core( पूर्णाङ्क xOtherCoreID );
        #परिभाषय पत्तनम्_YIELD_CORE( x )    v_पत्तनम्_Yield_Other_Core( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
        #यदि_अपरिभाषितम् config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION
            #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    0
        #यदि_अन्तः

        #यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
            #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
            #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

/*-----------------------------------------------------------*/

            #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities )    ux_शिखरम्_प्राथमिकता = ( 31UL - ( uint32_t ) __builtin_clz( uxReadyPriorities ) )

        #यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */

        #परिभाषय पत्तनम्_GET_व्यवधानम्_STATE()                 rtos_व्यवधानम्_आवरणम्_get()

/*
 * This differs from the standard portDISABLE_INTERRUPTS()
 * in that it also returns what the interrupt state was
 * before it disabling interrupts.
 */
        #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()                  rtos_व्यवधानम्_आवरणम्_all()

        #परिभाषय पत्तनम्_ENABLE_INTERRUPTS()                   rtos_व्यवधानम्_unmask_all()

/*
 * Port set interrupt mask and clear interrupt mask.
 */
        #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()                  rtos_व्यवधानम्_आवरणम्_all()
        #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्( ulState )       rtos_व्यवधानम्_आवरणम्_समुच्चयः( ulState )

/*
 * Will enable interrupts if ulState is non-zero.
 */
        #परिभाषय पत्तनम्_RESTORE_INTERRUPTS( ulState )         rtos_व्यवधानम्_आवरणम्_समुच्चयः( ulState )

/*
 * Returns non-zero if currently running in an
 * ISR or otherwise in kernel mode.
 */
        #परिभाषय पत्तनम्_CHECK_IF_अन्तर्_ISR()                     rtos_isr_running()

        #परिभाषय पत्तनम्_ASSERT_IF_अन्तर्_ISR()                    configASSERT( पत्तनम्_CHECK_IF_अन्तर्_ISR() == 0 )

        #परिभाषय पत्तनम्_GET_ISR_तालकम्( xCoreID )               कुरु{ ( शून्य )( xCoreID ); rtos_तालकम्_acquire( 0 ); } यावत्( 0 )
        #परिभाषय पत्तनम्_RELEASE_ISR_तालकम्( xCoreID )           कुरु{ ( शून्य )( xCoreID ); rtos_तालकम्_release( 0 ); } यावत्( 0 )
        #परिभाषय पत्तनम्_GET_TASK_तालकम्( xCoreID )              कुरु{ ( शून्य )( xCoreID ); rtos_तालकम्_acquire( 1 ); } यावत्( 0 )
        #परिभाषय पत्तनम्_RELEASE_TASK_तालकम्( xCoreID )          कुरु{ ( शून्य )( xCoreID ); rtos_तालकम्_release( 1 ); } यावत्( 0 )


        शून्य vTaskEnterCritical( शून्य );
        शून्य vTaskExitCritical( शून्य );
        #परिभाषय पत्तनम्_ENTER_CRITICAL()    vTaskEnterCritical()
        #परिभाषय पत्तनम्_EXIT_CRITICAL()     vTaskExitCritical()

        बाह्य UBaseType_t vTaskEnterCriticalFromISR( शून्य );
        बाह्य शून्य vTaskExitCriticalFromISR( UBaseType_t ux_Saved_व्यवधानम्_स्थितिः );
        #परिभाषय पत्तनम्_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
        #परिभाषय पत्तनम्_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

/*-----------------------------------------------------------*/

/* Runtime stats support */
        #यदि ( config_GENERATE_सततम्_TIME_STATS == 1 )
            पूर्णाङ्क xscope_gettime( शून्य );
            #परिभाषय पत्तनम्_CONFIGURE_TIMER_FOR_सततम्_TIME_STATS()    /* nothing needed here */
            #परिभाषय पत्तनम्_GET_सततम्_TIME_गणक_मानम्()            xscope_gettime()
        #यदि_अन्तः
/*-----------------------------------------------------------*/

/* Maps sprintf and snprintf to the lite version in lib_rtos_support */
        #यदि ( configUSE_DEBUG_SPRINTF == 1 )
            #परिभाषय sprintf( ... )     rtos_sprintf( __VA_ARGS__ )
            #परिभाषय snprintf( ... )    rtos_snprintf( __VA_ARGS__ )
        #यदि_अन्तः

/* Attribute for the pxCallbackFunction member of the Timer_t struct.
 * Required by xcc to calculate stack usage. */
        #परिभाषय पत्तनम्_TIMER_CALLBACK_ATTRIBUTE    __attribute__( ( fptrgroup( "timerCallbackGroup" ) ) )

/* Timer callback function macros. For xcc this ensures they get added to the timer callback
 * group so that stack usage for certain functions in timers.c can be calculated. */
        #परिभाषय पत्तनम्_TIMER_CALLBACK_FUNCTION_PROTO( vFunction, xTimer )    शून्य vFunction( TimerHandle_t xTimer )
        #परिभाषय पत्तनम्_TIMER_CALLBACK_FUNCTION( vFunction, xTimer )          पत्तनम्_TIMER_CALLBACK_ATTRIBUTE शून्य vFunction( TimerHandle_t xTimer )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
        #परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
        #परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )
/*-----------------------------------------------------------*/


        #यदि_परिभाषितम् __cplusplus
}
        #यदि_अन्तः

    #यदि_अन्तः /* __ASSEMBLER__ */

#यदि_अन्तः /* PORTMACRO_H */
