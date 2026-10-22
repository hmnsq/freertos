/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

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
#تعریف_کن پورت_CHAR                 حرف
#تعریف_کن پورت_FLOAT                عائم
#تعریف_کن پورت_DOUBLE               مزدوج
#تعریف_کن پورت_LONG                 دراز
#تعریف_کن پورت_SHORT                صحيح
#تعریف_کن پورت_پشته_TYPE           uint8_t
#تعریف_کن پورت_پایه_TYPE            حرف

#تعریف_کن پورت_پشته_GROWTH         ( -1 )
#تعریف_کن پورت_BYTE_ALIGNMENT       4
#تعریف_کن پورت_اشاره_گر_اندازه_TYPE    size_t
تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
تعريفنوع علامتدار حرف      پایه_Type_t;
تعريفنوع بیعلامت حرف    UBaseType_t;

#إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffffU
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffffffffU
#وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_64_بیتها )
    تعريفنوع uint64_t     TickType_t;
    #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffffffffffffffffU
#وإلا
    #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
#پایان_اگر

/* Architecture specific optimisations. */
#اگر_تعریف_نشده config_USE_پورت_OPTIMISED_TASK_SELECTION
    #تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION    1
#پایان_اگر

#إذا config_USE_پورت_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #خطا config_USE_پورت_OPTIMISED_TASK_SELECTION can only be مجموعه مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires بیشتر than 10 مقصد 15 difference priorities as tasks that share a اولویت will time برش.
    #پایان_اگر

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_اولویت ) )
    #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_اولویت ) )

/*-----------------------------------------------------------*/

    #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities ) \
    افعل {                                                                 \
        ux_بالاترین_اولویت = 0;                                               \
    } طالما( 0 )

#پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* Disable the interrupts */
#تعریف_کن پورت_DISABLE_INTERRUPTS()    افعل {} طالما( 0 )

/* Enable the interrupts */
#تعریف_کن پورت_ENABLE_INTERRUPTS()     افعل {} طالما( 0 )

#إذا ( config_عدد_از_CORES == 1 )
/* preserve current interrupt state and then disable interrupts */
    #تعریف_کن پورت_ENTER_CRITICAL()    افعل {} طالما( 0 )

/* restore previously preserved interrupt state */
    #تعریف_کن پورت_EXIT_CRITICAL()     افعل {} طالما( 0 )
#وإلا

/* The port can maintain the critical nesting count in TCB or maintain the critical
 * nesting count in the port. */
    #تعریف_کن پورت_CRITICAL_NESTING_درون_TCB    1

/* vTaskEnterCritical and vTaskExitCritical should be used in the implementation
 * of portENTER/EXIT_CRITICAL if the number of cores is more than 1 in the system. */
    #تعریف_کن پورت_ENTER_CRITICAL             vTaskEnterCritical
    #تعریف_کن پورت_EXIT_CRITICAL              vTaskExitCritical

/* vTaskEnterCriticalFromISR and vTaskExitCriticalFromISR should be used in the
 * implementation of portENTER/EXIT_CRITICAL_FROM_ISR if the number of cores is
 * more than 1 in the system. */
    #تعریف_کن پورت_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
    #تعریف_کن پورت_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

#پایان_اگر /* if ( configNUMBER_OF_CORES == 1 ) */

خارجي فراغ v_پورت_Yield( فراغ );
#تعریف_کن پورت_YIELD()                                           v_پورت_Yield()

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters ) __attribute__( ( noreturn ) )
#تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

#إذا ( config_عدد_از_CORES > 1 )
    /* Return the core ID on which the code is running. */
    #تعریف_کن پورت_GET_CORE_ID()                0

/* Set the interrupt mask. */
    #تعریف_کن پورت_مجموعه_وقفه_ماسک()         0

/* Clear the interrupt mask. */
    #تعریف_کن پورت_CLEAR_وقفه_ماسک( x )    ( ( فراغ ) ( x ) )

/* Request the core ID x to yield. */
    #تعریف_کن پورت_YIELD_CORE( x )              افعل {} طالما( 0 )

/* Acquire the TASK lock. TASK lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #تعریف_کن پورت_GET_TASK_قفل( xCoreID )     افعل {} طالما( 0 )

/* Release the TASK lock. If a TASK lock is locked by the same core multiple times,
 * it should be released as many times as it is locked. */
    #تعریف_کن پورت_RELEASE_TASK_قفل( xCoreID ) افعل {} طالما( 0 )

/* Acquire the ISR lock. ISR lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #تعریف_کن پورت_GET_ISR_قفل( xCoreID )      افعل {} طالما( 0 )

/* Release the ISR lock. If a ISR lock is locked by the same core multiple times, \
 * it should be released as many times as it is locked. */
    #تعریف_کن پورت_RELEASE_ISR_قفل( xCoreID )  افعل {} طالما( 0 )

#پایان_اگر /* if ( configNUMBER_OF_CORES > 1 ) */

#پایان_اگر /* PORTMACRO_H */
