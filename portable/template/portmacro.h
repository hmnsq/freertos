/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

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
#وصف_ڪريو پورٽ_CHAR                 حرف
#وصف_ڪريو پورٽ_FLOAT                عائم
#وصف_ڪريو پورٽ_DOUBLE               مزدوج
#وصف_ڪريو پورٽ_LONG                 ڊگهو
#وصف_ڪريو پورٽ_SHORT                صحيح
#وصف_ڪريو پورٽ_ڍير_TYPE           uint8_t
#وصف_ڪريو پورٽ_بنياد_TYPE            حرف

#وصف_ڪريو پورٽ_ڍير_GROWTH         ( -1 )
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT       4
#وصف_ڪريو پورٽ_اشارو_سائيز_TYPE    size_t
تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع نشانوارو حرف      بنياد_Type_t;
تعريفنوع بنانشان حرف    UBaseType_t;

#إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffffU
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffffffffU
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_64_بٽ )
    تعريفنوع uint64_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffffffffffffffffU
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو

/* Architecture specific optimisations. */
#جيڪڏهن_وصف_نه_ٿيل config_USE_پورٽ_OPTIMISED_TASK_SELECTION
    #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    1
#جيڪڏهن_پورو

#إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطي config_USE_پورٽ_OPTIMISED_TASK_SELECTION can only be سيٽ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires وڌيڪ than 10 منزل 15 difference priorities as tasks that share a ترجيح will time ٽڪرو.
    #جيڪڏهن_پورو

/* Store/clear the ready priorities in a bit map. */
    #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجيح ) )
    #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجيح ) )

/*-----------------------------------------------------------*/

    #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities ) \
    افعل {                                                                 \
        ux_چوٽي_ترجيح = 0;                                               \
    } طالما( 0 )

#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* Disable the interrupts */
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    افعل {} طالما( 0 )

/* Enable the interrupts */
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     افعل {} طالما( 0 )

#إذا ( config_عدد_جو_CORES == 1 )
/* preserve current interrupt state and then disable interrupts */
    #وصف_ڪريو پورٽ_ENTER_CRITICAL()    افعل {} طالما( 0 )

/* restore previously preserved interrupt state */
    #وصف_ڪريو پورٽ_EXIT_CRITICAL()     افعل {} طالما( 0 )
#وإلا

/* The port can maintain the critical nesting count in TCB or maintain the critical
 * nesting count in the port. */
    #وصف_ڪريو پورٽ_CRITICAL_NESTING_اندريون_TCB    1

/* vTaskEnterCritical and vTaskExitCritical should be used in the implementation
 * of portENTER/EXIT_CRITICAL if the number of cores is more than 1 in the system. */
    #وصف_ڪريو پورٽ_ENTER_CRITICAL             vTaskEnterCritical
    #وصف_ڪريو پورٽ_EXIT_CRITICAL              vTaskExitCritical

/* vTaskEnterCriticalFromISR and vTaskExitCriticalFromISR should be used in the
 * implementation of portENTER/EXIT_CRITICAL_FROM_ISR if the number of cores is
 * more than 1 in the system. */
    #وصف_ڪريو پورٽ_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
    #وصف_ڪريو پورٽ_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

#جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES == 1 ) */

خارجي فراغ v_پورٽ_Yield( فراغ );
#وصف_ڪريو پورٽ_YIELD()                                           v_پورٽ_Yield()

/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( noreturn ) )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#إذا ( config_عدد_جو_CORES > 1 )
    /* Return the core ID on which the code is running. */
    #وصف_ڪريو پورٽ_GET_CORE_ID()                0

/* Set the interrupt mask. */
    #وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب()         0

/* Clear the interrupt mask. */
    #وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب( x )    ( ( فراغ ) ( x ) )

/* Request the core ID x to yield. */
    #وصف_ڪريو پورٽ_YIELD_CORE( x )              افعل {} طالما( 0 )

/* Acquire the TASK lock. TASK lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #وصف_ڪريو پورٽ_GET_TASK_تالو( xCoreID )     افعل {} طالما( 0 )

/* Release the TASK lock. If a TASK lock is locked by the same core multiple times,
 * it should be released as many times as it is locked. */
    #وصف_ڪريو پورٽ_RELEASE_TASK_تالو( xCoreID ) افعل {} طالما( 0 )

/* Acquire the ISR lock. ISR lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #وصف_ڪريو پورٽ_GET_ISR_تالو( xCoreID )      افعل {} طالما( 0 )

/* Release the ISR lock. If a ISR lock is locked by the same core multiple times, \
 * it should be released as many times as it is locked. */
    #وصف_ڪريو پورٽ_RELEASE_ISR_تالو( xCoreID )  افعل {} طالما( 0 )

#جيڪڏهن_پورو /* if ( configNUMBER_OF_CORES > 1 ) */

#جيڪڏهن_پورو /* PORTMACRO_H */
