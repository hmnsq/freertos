/* Copyright (c) 2020, XMOS Ltd, All rights reserved */

#अगर_अघोषित PORTMACRO_H
    #घोषणा PORTMACRO_H

    #अगर_अघोषित __ASSEMBLER__

/* Inclusion of xc1.h will result in clock being defined as a type.
 * By default, FreeRTOS will require standard time.h, where clock is a function.
 */
        #अगर_अघोषित USE_XCORE_CLOCK_TYPE
            #घोषणा _clock_defined
        #पूर्ण_अगर

        #समावेश <xs1.h>
        #समावेश "rtos_support.h"

        #अगर_घोषित __cplusplus
        बाह्य "C" {
        #पूर्ण_अगर

/* Type definitions. */
        #घोषणा port_ढेर_TYPE    uint32_t
        प्रकार port_ढेर_TYPE   ढेर_Type_t;
        प्रकार द्विगुन           portDOUBLE;
        प्रकार int32_t          BaseType_t;
        प्रकार uint32_t         UBaseType_t;

        #घोषणा portBASE_TYPE    BaseType_t

        #अगर ( configUSE_16_BIT_TICKS == 1 )
            प्रकार uint16_t     TickType_t;
            #घोषणा portMAX_DELAY              ( TickType_t ) 0xffff
        #अन्यथा
            प्रकार uint32_t     TickType_t;
            #घोषणा portMAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
            #घोषणा portTICK_TYPE_IS_ATOMIC    1
        #पूर्ण_अगर
/*-----------------------------------------------------------*/

    #पूर्ण_अगर /* __ASSEMBLER__ */

/* Architecture specifics. These can be used by assembly files as well. */
    #घोषणा port_ढेर_GROWTH               ( -1 )
    #घोषणा portTICK_PERIOD_MS             ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
    #घोषणा portBYTE_ALIGNMENT             8
    #घोषणा portCRITICAL_NESTING_IN_TCB    1
    #घोषणा port_MAX_CORE_गिनती             8
    #अगर_अघोषित config_संख्या_OF_CORES
        #घोषणा config_संख्या_OF_CORES      1
    #पूर्ण_अगर

/* This may be set to zero in the config file if the rtos_time
 *  functions are not needed or if it is incremented elsewhere. */
    #अगर_अघोषित configUPDATE_RTOS_TIME_FROM_TICK_ISR
        #घोषणा configUPDATE_RTOS_TIME_FROM_TICK_ISR    1
    #पूर्ण_अगर

/*
 * When entering an ISR we need to grow the stack by one more word than
 * we actually need to save the thread context. This is because there are
 * some functions, written in assembly *cough* memcpy() *cough*, that think
 * it is OK to store words at SP[0]. Therefore the ISR must leave SP[0] alone
 * even though it is normally not necessary to do so.
 */
    #घोषणा port_THREAD_CONTEXT_ढेर_GROWTH    RTOS_SUPPORT_INTERRUPT_ढेर_GROWTH

    #अगर_अघोषित __ASSEMBLER__

/* Check validity of number of cores specified in config */
        #अगर ( config_संख्या_OF_CORES < 1 || port_MAX_CORE_गिनती < config_संख्या_OF_CORES )
            #त्रुटि "Invalid number of cores specified in config!"
        #पूर्ण_अगर

        #घोषणा portMEMORY_BARRIER()                  RTOS_MEMORY_BARRIER()
        #घोषणा port_TASK_ढेर_DEPTH( pxTaskCode )    RTOS_THREAD_ढेर_आकार( pxTaskCode )
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
        #घोषणा portYIELD()    यंत्र अस्थिर ( "KCALLI_lu6 0" ::: "memory" )

        #घोषणा portEND_SWITCHING_ISR( xSwitchRequired )               \
    करो                                                                 \
    {                                                                  \
        अगर( xSwitchRequired != pdFALSE )                               \
        {                                                              \
            बाह्य uint32_t ulPortYieldRequired[ port_MAX_CORE_गिनती ]; \
            ulPortYieldRequired[ portGET_CORE_ID() ] = pdTRUE;         \
        }                                                              \
    } जबतक( 0 )

        #घोषणा portYIELD_FROM_ISR( x )    portEND_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* SMP utilities. */
        #घोषणा portGET_CORE_ID()      rtos_core_id_get()

        व्योम vPortYieldOtherCore( पूर्णांक xOtherCoreID );
        #घोषणा portYIELD_CORE( x )    vPortYieldOtherCore( x )
/*-----------------------------------------------------------*/

/* Architecture specific optimisations. */
        #अगर_अघोषित configUSE_PORT_OPTIMISED_TASK_SELECTION
            #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    0
        #पूर्ण_अगर

        #अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
            #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
            #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

            #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    ux_शीर्ष_Priority = ( 31UL - ( uint32_t ) __builtin_clz( uxReadyPriorities ) )

        #पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */
/*-----------------------------------------------------------*/

/* Critical section management. */

        #घोषणा portGET_INTERRUPT_STATE()                 rtos_interrupt_mask_get()

/*
 * This differs from the standard portDISABLE_INTERRUPTS()
 * in that it also returns what the interrupt state was
 * before it disabling interrupts.
 */
        #घोषणा portDISABLE_INTERRUPTS()                  rtos_interrupt_mask_all()

        #घोषणा portENABLE_INTERRUPTS()                   rtos_interrupt_unmask_all()

/*
 * Port set interrupt mask and clear interrupt mask.
 */
        #घोषणा portSET_INTERRUPT_MASK()                  rtos_interrupt_mask_all()
        #घोषणा portCLEAR_INTERRUPT_MASK( ulState )       rtos_interrupt_mask_set( ulState )

/*
 * Will enable interrupts if ulState is non-zero.
 */
        #घोषणा portRESTORE_INTERRUPTS( ulState )         rtos_interrupt_mask_set( ulState )

/*
 * Returns non-zero if currently running in an
 * ISR or otherwise in kernel mode.
 */
        #घोषणा portCHECK_IF_IN_ISR()                     rtos_isr_running()

        #घोषणा portASSERT_IF_IN_ISR()                    configASSERT( portCHECK_IF_IN_ISR() == 0 )

        #घोषणा portGET_ISR_LOCK( xCoreID )               करो{ ( व्योम )( xCoreID ); rtos_lock_acquire( 0 ); } जबतक( 0 )
        #घोषणा portRELEASE_ISR_LOCK( xCoreID )           करो{ ( व्योम )( xCoreID ); rtos_lock_release( 0 ); } जबतक( 0 )
        #घोषणा portGET_TASK_LOCK( xCoreID )              करो{ ( व्योम )( xCoreID ); rtos_lock_acquire( 1 ); } जबतक( 0 )
        #घोषणा portRELEASE_TASK_LOCK( xCoreID )          करो{ ( व्योम )( xCoreID ); rtos_lock_release( 1 ); } जबतक( 0 )


        व्योम vTaskEnterCritical( व्योम );
        व्योम vTaskExitCritical( व्योम );
        #घोषणा portENTER_CRITICAL()    vTaskEnterCritical()
        #घोषणा portEXIT_CRITICAL()     vTaskExitCritical()

        बाह्य UBaseType_t vTaskEnterCriticalFromISR( व्योम );
        बाह्य व्योम vTaskExitCriticalFromISR( UBaseType_t uxSavedInterruptStatus );
        #घोषणा portENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
        #घोषणा portEXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

/*-----------------------------------------------------------*/

/* Runtime stats support */
        #अगर ( configGENERATE_RUN_TIME_STATS == 1 )
            पूर्णांक xscope_gettime( व्योम );
            #घोषणा portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()    /* nothing needed here */
            #घोषणा port_GET_RUN_TIME_गणक_मूल्य()            xscope_gettime()
        #पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Maps sprintf and snprintf to the lite version in lib_rtos_support */
        #अगर ( configUSE_DEBUG_SPRINTF == 1 )
            #घोषणा प्र_लिखो( ... )     rtos_sprintf( __VA_ARGS__ )
            #घोषणा snprintf( ... )    rtos_snprintf( __VA_ARGS__ )
        #पूर्ण_अगर

/* Attribute for the pxCallbackFunction member of the Timer_t struct.
 * Required by xcc to calculate stack usage. */
        #घोषणा portTIMER_CALLBACK_ATTRIBUTE    __attribute__( ( fptrgroup( "timerCallbackGroup" ) ) )

/* Timer callback function macros. For xcc this ensures they get added to the timer callback
 * group so that stack usage for certain functions in timers.c can be calculated. */
        #घोषणा portTIMER_CALLBACK_FUNCTION_PROTO( vFunction, xTimer )    व्योम vFunction( TimerHandle_t xTimer )
        #घोषणा portTIMER_CALLBACK_FUNCTION( vFunction, xTimer )          portTIMER_CALLBACK_ATTRIBUTE व्योम vFunction( TimerHandle_t xTimer )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
        #घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
        #घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )
/*-----------------------------------------------------------*/


        #अगर_घोषित __cplusplus
}
        #पूर्ण_अगर

    #पूर्ण_अगर /* __ASSEMBLER__ */

#पूर्ण_अगर /* PORTMACRO_H */
