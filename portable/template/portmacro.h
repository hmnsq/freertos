/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#నిర్వచించు పోర్టు_CHAR                 అక్షరం
#నిర్వచించు పోర్టు_FLOAT                దశాంశం
#నిర్వచించు పోర్టు_DOUBLE               ద్విగుణ
#నిర్వచించు పోర్టు_LONG                 దీర్ఘ
#నిర్వచించు పోర్టు_SHORT                పూర్ణాంకం
#నిర్వచించు పోర్టు_దొంతర_TYPE           uint8_t
#నిర్వచించు పోర్టు_పునాది_TYPE            అక్షరం

#నిర్వచించు పోర్టు_దొంతర_GROWTH         ( -1 )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT       4
#నిర్వచించు పోర్టు_సూచిక_కొలత_TYPE    size_t
రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం గుర్తుగల అక్షరం      పునాది_Type_t;
రకనిర్వచనం గుర్తులేని అక్షరం    UBaseType_t;

#ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffffU
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffffffffU
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_64_బిట్లు )
    రకనిర్వచనం uint64_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffffffffffffffffU
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు

/* Architecture specific optimisations. */
#నిర్వచితం_కాకపోతే config_USE_పోర్టు_OPTIMISED_TASK_SELECTION
    #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    1
#అయితే_ముగింపు

#ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #ఒకవేళ ( configMAX_PRIORITIES > 32 )
        #దోషం config_USE_పోర్టు_OPTIMISED_TASK_SELECTION can only be సమితి గమ్యం 1 when configMAX_PRIORITIES is less than or equal గమ్యం 32.  It is very rare that a system requires మరిన్ని than 10 గమ్యం 15 difference priorities as tasks that share a ప్రాధాన్యత will time ముక్క.
    #అయితే_ముగింపు

/* Store/clear the ready priorities in a bit map. */
    #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ప్రాధాన్యత ) )
    #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ప్రాధాన్యత ) )

/*-----------------------------------------------------------*/

    #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities ) \
    చేయి {                                                                 \
        ux_శిఖరం_ప్రాధాన్యత = 0;                                               \
    } అయితే( 0 )

#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* Disable the interrupts */
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    చేయి {} అయితే( 0 )

/* Enable the interrupts */
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     చేయి {} అయితే( 0 )

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES == 1 )
/* preserve current interrupt state and then disable interrupts */
    #నిర్వచించు పోర్టు_ENTER_CRITICAL()    చేయి {} అయితే( 0 )

/* restore previously preserved interrupt state */
    #నిర్వచించు పోర్టు_EXIT_CRITICAL()     చేయి {} అయితే( 0 )
#లేకపోతే

/* The port can maintain the critical nesting count in TCB or maintain the critical
 * nesting count in the port. */
    #నిర్వచించు పోర్టు_CRITICAL_NESTING_లోపల_TCB    1

/* vTaskEnterCritical and vTaskExitCritical should be used in the implementation
 * of portENTER/EXIT_CRITICAL if the number of cores is more than 1 in the system. */
    #నిర్వచించు పోర్టు_ENTER_CRITICAL             vTaskEnterCritical
    #నిర్వచించు పోర్టు_EXIT_CRITICAL              vTaskExitCritical

/* vTaskEnterCriticalFromISR and vTaskExitCriticalFromISR should be used in the
 * implementation of portENTER/EXIT_CRITICAL_FROM_ISR if the number of cores is
 * more than 1 in the system. */
    #నిర్వచించు పోర్టు_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
    #నిర్వచించు పోర్టు_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

#అయితే_ముగింపు /* if ( configNUMBER_OF_CORES == 1 ) */

బాహ్య శూన్య v_పోర్టు_Yield( శూన్య );
#నిర్వచించు పోర్టు_YIELD()                                           v_పోర్టు_Yield()

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters ) __attribute__( ( noreturn ) )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )
    /* Return the core ID on which the code is running. */
    #నిర్వచించు పోర్టు_GET_CORE_ID()                0

/* Set the interrupt mask. */
    #నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు()         0

/* Clear the interrupt mask. */
    #నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు( x )    ( ( శూన్య ) ( x ) )

/* Request the core ID x to yield. */
    #నిర్వచించు పోర్టు_YIELD_CORE( x )              చేయి {} అయితే( 0 )

/* Acquire the TASK lock. TASK lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #నిర్వచించు పోర్టు_GET_TASK_తాళం( xCoreID )     చేయి {} అయితే( 0 )

/* Release the TASK lock. If a TASK lock is locked by the same core multiple times,
 * it should be released as many times as it is locked. */
    #నిర్వచించు పోర్టు_RELEASE_TASK_తాళం( xCoreID ) చేయి {} అయితే( 0 )

/* Acquire the ISR lock. ISR lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #నిర్వచించు పోర్టు_GET_ISR_తాళం( xCoreID )      చేయి {} అయితే( 0 )

/* Release the ISR lock. If a ISR lock is locked by the same core multiple times, \
 * it should be released as many times as it is locked. */
    #నిర్వచించు పోర్టు_RELEASE_ISR_తాళం( xCoreID )  చేయి {} అయితే( 0 )

#అయితే_ముగింపు /* if ( configNUMBER_OF_CORES > 1 ) */

#అయితే_ముగింపు /* PORTMACRO_H */
