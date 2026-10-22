/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

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
#تعریف_کرو پورٹ_CHAR                 حرف
#تعریف_کرو پورٹ_FLOAT                عائم
#تعریف_کرو پورٹ_DOUBLE               مزدوج
#تعریف_کرو پورٹ_LONG                 لما
#تعریف_کرو پورٹ_SHORT                صحيح
#تعریف_کرو پورٹ_ڈھیر_TYPE           uint8_t
#تعریف_کرو پورٹ_ادھار_TYPE            حرف

#تعریف_کرو پورٹ_ڈھیر_GROWTH         ( -1 )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT       4
#تعریف_کرو پورٹ_اشارہ_گر_ناپ_TYPE    size_t
تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
تعريفنوع نشانیوالا حرف      ادھار_Type_t;
تعريفنوع بنانشانی حرف    UBaseType_t;

#إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffU
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffU
#وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_64_بٹ )
    تعريفنوع uint64_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffffffffffU
#وإلا
    #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
#جے_انت

/* Architecture specific optimisations. */
#جے_بنا_تعریف config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
#جے_انت

#إذا config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires ہور than 10 منزل 15 difference priorities as tasks that share a ترجیح will time ٹکڑا.
    #جے_انت

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities ) \
    افعل {                                                                 \
        ux_چوٹی_ترجیح = 0;                                               \
    } طالما( 0 )

#جے_انت /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* Disable the interrupts */
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    افعل {} طالما( 0 )

/* Enable the interrupts */
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     افعل {} طالما( 0 )

#إذا ( config_نمبر_دا_CORES == 1 )
/* preserve current interrupt state and then disable interrupts */
    #تعریف_کرو پورٹ_ENTER_CRITICAL()    افعل {} طالما( 0 )

/* restore previously preserved interrupt state */
    #تعریف_کرو پورٹ_EXIT_CRITICAL()     افعل {} طالما( 0 )
#وإلا

/* The port can maintain the critical nesting count in TCB or maintain the critical
 * nesting count in the port. */
    #تعریف_کرو پورٹ_CRITICAL_NESTING_وچ_TCB    1

/* vTaskEnterCritical and vTaskExitCritical should be used in the implementation
 * of portENTER/EXIT_CRITICAL if the number of cores is more than 1 in the system. */
    #تعریف_کرو پورٹ_ENTER_CRITICAL             vTaskEnterCritical
    #تعریف_کرو پورٹ_EXIT_CRITICAL              vTaskExitCritical

/* vTaskEnterCriticalFromISR and vTaskExitCriticalFromISR should be used in the
 * implementation of portENTER/EXIT_CRITICAL_FROM_ISR if the number of cores is
 * more than 1 in the system. */
    #تعریف_کرو پورٹ_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
    #تعریف_کرو پورٹ_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

#جے_انت /* if ( configNUMBER_OF_CORES == 1 ) */

خارجي فراغ v_پورٹ_Yield( فراغ );
#تعریف_کرو پورٹ_YIELD()                                           v_پورٹ_Yield()

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( noreturn ) )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#إذا ( config_نمبر_دا_CORES > 1 )
    /* Return the core ID on which the code is running. */
    #تعریف_کرو پورٹ_GET_CORE_ID()                0

/* Set the interrupt mask. */
    #تعریف_کرو پورٹ_سیٹ_رکاوٹ_نقاب()         0

/* Clear the interrupt mask. */
    #تعریف_کرو پورٹ_CLEAR_رکاوٹ_نقاب( x )    ( ( فراغ ) ( x ) )

/* Request the core ID x to yield. */
    #تعریف_کرو پورٹ_YIELD_CORE( x )              افعل {} طالما( 0 )

/* Acquire the TASK lock. TASK lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #تعریف_کرو پورٹ_GET_TASK_جندرا( xCoreID )     افعل {} طالما( 0 )

/* Release the TASK lock. If a TASK lock is locked by the same core multiple times,
 * it should be released as many times as it is locked. */
    #تعریف_کرو پورٹ_RELEASE_TASK_جندرا( xCoreID ) افعل {} طالما( 0 )

/* Acquire the ISR lock. ISR lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #تعریف_کرو پورٹ_GET_ISR_جندرا( xCoreID )      افعل {} طالما( 0 )

/* Release the ISR lock. If a ISR lock is locked by the same core multiple times, \
 * it should be released as many times as it is locked. */
    #تعریف_کرو پورٹ_RELEASE_ISR_جندرا( xCoreID )  افعل {} طالما( 0 )

#جے_انت /* if ( configNUMBER_OF_CORES > 1 ) */

#جے_انت /* PORTMACRO_H */
