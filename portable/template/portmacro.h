/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

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
#تعریف_کړه پورټ_CHAR                 حرف
#تعریف_کړه پورټ_FLOAT                عائم
#تعریف_کړه پورټ_DOUBLE               مزدوج
#تعریف_کړه پورټ_LONG                 اوږد
#تعریف_کړه پورټ_SHORT                صحيح
#تعریف_کړه پورټ_ډېری_TYPE           uint8_t
#تعریف_کړه پورټ_بنسټ_TYPE            حرف

#تعریف_کړه پورټ_ډېری_GROWTH         ( -1 )
#تعریف_کړه پورټ_BYTE_ALIGNMENT       4
#تعریف_کړه پورټ_اشاره_ګر_اندازه_TYPE    size_t
تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع نښهدار حرف      بنسټ_Type_t;
تعريفنوع بینښه حرف    UBaseType_t;

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffffU
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffffffffU
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_64_بټونه )
    تعريفنوع uint64_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffffffffffffffffU
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای

/* Architecture specific optimisations. */
#که_نه_تعریف_شوی config_USE_پورټ_OPTIMISED_TASK_SELECTION
    #تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    1
#د_که_پای

#إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #تېروتنه config_USE_پورټ_OPTIMISED_TASK_SELECTION can only be سېټ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires نور than 10 منزل 15 difference priorities as tasks that share a لومړیتوب will time ټوټه.
    #د_که_پای

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
    #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

/*-----------------------------------------------------------*/

    #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities ) \
    افعل {                                                                 \
        ux_سر_لومړیتوب = 0;                                               \
    } طالما( 0 )

#د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* Disable the interrupts */
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    افعل {} طالما( 0 )

/* Enable the interrupts */
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     افعل {} طالما( 0 )

#إذا ( config_شمېره_د_CORES == 1 )
/* preserve current interrupt state and then disable interrupts */
    #تعریف_کړه پورټ_ENTER_CRITICAL()    افعل {} طالما( 0 )

/* restore previously preserved interrupt state */
    #تعریف_کړه پورټ_EXIT_CRITICAL()     افعل {} طالما( 0 )
#وإلا

/* The port can maintain the critical nesting count in TCB or maintain the critical
 * nesting count in the port. */
    #تعریف_کړه پورټ_CRITICAL_NESTING_دننه_TCB    1

/* vTaskEnterCritical and vTaskExitCritical should be used in the implementation
 * of portENTER/EXIT_CRITICAL if the number of cores is more than 1 in the system. */
    #تعریف_کړه پورټ_ENTER_CRITICAL             vTaskEnterCritical
    #تعریف_کړه پورټ_EXIT_CRITICAL              vTaskExitCritical

/* vTaskEnterCriticalFromISR and vTaskExitCriticalFromISR should be used in the
 * implementation of portENTER/EXIT_CRITICAL_FROM_ISR if the number of cores is
 * more than 1 in the system. */
    #تعریف_کړه پورټ_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
    #تعریف_کړه پورټ_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

#د_که_پای /* if ( configNUMBER_OF_CORES == 1 ) */

خارجي فراغ v_پورټ_Yield( فراغ );
#تعریف_کړه پورټ_YIELD()                                           v_پورټ_Yield()

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( noreturn ) )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#إذا ( config_شمېره_د_CORES > 1 )
    /* Return the core ID on which the code is running. */
    #تعریف_کړه پورټ_GET_CORE_ID()                0

/* Set the interrupt mask. */
    #تعریف_کړه پورټ_سېټ_مداخله_ماسک()         0

/* Clear the interrupt mask. */
    #تعریف_کړه پورټ_CLEAR_مداخله_ماسک( x )    ( ( فراغ ) ( x ) )

/* Request the core ID x to yield. */
    #تعریف_کړه پورټ_YIELD_CORE( x )              افعل {} طالما( 0 )

/* Acquire the TASK lock. TASK lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #تعریف_کړه پورټ_GET_TASK_قلف( xCoreID )     افعل {} طالما( 0 )

/* Release the TASK lock. If a TASK lock is locked by the same core multiple times,
 * it should be released as many times as it is locked. */
    #تعریف_کړه پورټ_RELEASE_TASK_قلف( xCoreID ) افعل {} طالما( 0 )

/* Acquire the ISR lock. ISR lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #تعریف_کړه پورټ_GET_ISR_قلف( xCoreID )      افعل {} طالما( 0 )

/* Release the ISR lock. If a ISR lock is locked by the same core multiple times, \
 * it should be released as many times as it is locked. */
    #تعریف_کړه پورټ_RELEASE_ISR_قلف( xCoreID )  افعل {} طالما( 0 )

#د_که_پای /* if ( configNUMBER_OF_CORES > 1 ) */

#د_که_پای /* PORTMACRO_H */
