/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#اگر_غیر_تعریف_شدہ PORTMACRO_H
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
#تعریف_کرو پورٹ_FLOAT                اعشاری
#تعریف_کرو پورٹ_DOUBLE               دوہرا
#تعریف_کرو پورٹ_LONG                 طویل
#تعریف_کرو پورٹ_SHORT                صحیح
#تعریف_کرو پورٹ_ڈھیر_TYPE           uint8_t
#تعریف_کرو پورٹ_بنیاد_TYPE            حرف

#تعریف_کرو پورٹ_ڈھیر_GROWTH         ( -1 )
#تعریف_کرو پورٹ_BYTE_ALIGNMENT       4
#تعریف_کرو پورٹ_اشارہ_گر_سائز_TYPE    size_t
قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف علامتی حرف      بنیاد_Type_t;
قسمتعریف غیرعلامتی حرف    UBaseType_t;

#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffU
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffU
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_64_بٹ )
    قسمتعریف uint64_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffffffffffU
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم

/* Architecture specific optimisations. */
#اگر_غیر_تعریف_شدہ config_USE_پورٹ_OPTIMISED_TASK_SELECTION
    #تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    1
#اگر_ختم

#اگر config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #اگر ( configMAX_PRIORITIES > 32 )
        #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires مزید than 10 مقصد 15 difference priorities as tasks that share a ترجیح will time قاش.
    #اگر_ختم

/* Store/clear the ready priorities in a bit map. */
    #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
    #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

    #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities ) \
    کرو {                                                                 \
        ux_چوٹی_ترجیح = 0;                                               \
    } جب( 0 )

#اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* Disable the interrupts */
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    کرو {} جب( 0 )

/* Enable the interrupts */
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     کرو {} جب( 0 )

#اگر ( config_نمبر_کا_CORES == 1 )
/* preserve current interrupt state and then disable interrupts */
    #تعریف_کرو پورٹ_ENTER_CRITICAL()    کرو {} جب( 0 )

/* restore previously preserved interrupt state */
    #تعریف_کرو پورٹ_EXIT_CRITICAL()     کرو {} جب( 0 )
#ورنہ

/* The port can maintain the critical nesting count in TCB or maintain the critical
 * nesting count in the port. */
    #تعریف_کرو پورٹ_CRITICAL_NESTING_اندر_TCB    1

/* vTaskEnterCritical and vTaskExitCritical should be used in the implementation
 * of portENTER/EXIT_CRITICAL if the number of cores is more than 1 in the system. */
    #تعریف_کرو پورٹ_ENTER_CRITICAL             vTaskEnterCritical
    #تعریف_کرو پورٹ_EXIT_CRITICAL              vTaskExitCritical

/* vTaskEnterCriticalFromISR and vTaskExitCriticalFromISR should be used in the
 * implementation of portENTER/EXIT_CRITICAL_FROM_ISR if the number of cores is
 * more than 1 in the system. */
    #تعریف_کرو پورٹ_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
    #تعریف_کرو پورٹ_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

#اگر_ختم /* if ( configNUMBER_OF_CORES == 1 ) */

خارجی خالی v_پورٹ_Yield( خالی );
#تعریف_کرو پورٹ_YIELD()                                           v_پورٹ_Yield()

/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters ) __attribute__( ( noreturn ) )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

#اگر ( config_نمبر_کا_CORES > 1 )
    /* Return the core ID on which the code is running. */
    #تعریف_کرو پورٹ_GET_CORE_ID()                0

/* Set the interrupt mask. */
    #تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب()         0

/* Clear the interrupt mask. */
    #تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب( x )    ( ( خالی ) ( x ) )

/* Request the core ID x to yield. */
    #تعریف_کرو پورٹ_YIELD_CORE( x )              کرو {} جب( 0 )

/* Acquire the TASK lock. TASK lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #تعریف_کرو پورٹ_GET_TASK_تالا( xCoreID )     کرو {} جب( 0 )

/* Release the TASK lock. If a TASK lock is locked by the same core multiple times,
 * it should be released as many times as it is locked. */
    #تعریف_کرو پورٹ_RELEASE_TASK_تالا( xCoreID ) کرو {} جب( 0 )

/* Acquire the ISR lock. ISR lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #تعریف_کرو پورٹ_GET_ISR_تالا( xCoreID )      کرو {} جب( 0 )

/* Release the ISR lock. If a ISR lock is locked by the same core multiple times, \
 * it should be released as many times as it is locked. */
    #تعریف_کرو پورٹ_RELEASE_ISR_تالا( xCoreID )  کرو {} جب( 0 )

#اگر_ختم /* if ( configNUMBER_OF_CORES > 1 ) */

#اگر_ختم /* PORTMACRO_H */
