/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#ifndef PORTMACRO_H
#define PORTMACRO_H

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
#define portCHAR                 অক্ষর
#define portFLOAT                দশমিক
#define portDOUBLE               দ্বিগুণ
#define portLONG                 long
#define portSHORT                পূর্ণসংখ্যা
#define port_স্তূপ_TYPE           uint8_t
#define portBASE_TYPE            অক্ষর

#define port_স্তূপ_GROWTH         ( -1 )
#define portBYTE_ALIGNMENT       4
#define port_POINTER_আকার_TYPE    size_t
প্রকারলেখ port_স্তূপ_TYPE   স্তূপ_Type_t;
প্রকারলেখ signed অক্ষর      BaseType_t;
প্রকারলেখ unsigned অক্ষর    UBaseType_t;

#যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    প্রকারলেখ uint16_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffU
#নতুবা_যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    প্রকারলেখ uint32_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffU
#নতুবা_যদি ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_64_BITS )
    প্রকারলেখ uint64_t     TickType_t;
    #define portMAX_DELAY    ( TickType_t ) 0xffffffffffffffffU
#অন্যথা
    #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#endif

/* Architecture specific optimisations. */
#ifndef configUSE_PORT_OPTIMISED_TASK_SELECTION
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#endif

#যদি configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #যদি ( configMAX_PRIORITIES > 32 )
        #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
    #endif

/* Store/clear the ready priorities in a bit map. */
    #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #define portGET_HIGHEST_PRIORITY( ux_শীর্ষ_Priority, uxReadyPriorities ) \
    করো {                                                                 \
        ux_শীর্ষ_Priority = 0;                                               \
    } যখন( 0 )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* Disable the interrupts */
#define portDISABLE_INTERRUPTS()    করো {} যখন( 0 )

/* Enable the interrupts */
#define portENABLE_INTERRUPTS()     করো {} যখন( 0 )

#যদি ( config_সংখ্যা_OF_CORES == 1 )
/* preserve current interrupt state and then disable interrupts */
    #define portENTER_CRITICAL()    করো {} যখন( 0 )

/* restore previously preserved interrupt state */
    #define portEXIT_CRITICAL()     করো {} যখন( 0 )
#অন্যথা

/* The port can maintain the critical nesting count in TCB or maintain the critical
 * nesting count in the port. */
    #define portCRITICAL_NESTING_IN_TCB    1

/* vTaskEnterCritical and vTaskExitCritical should be used in the implementation
 * of portENTER/EXIT_CRITICAL if the number of cores is more than 1 in the system. */
    #define portENTER_CRITICAL             vTaskEnterCritical
    #define portEXIT_CRITICAL              vTaskExitCritical

/* vTaskEnterCriticalFromISR and vTaskExitCriticalFromISR should be used in the
 * implementation of portENTER/EXIT_CRITICAL_FROM_ISR if the number of cores is
 * more than 1 in the system. */
    #define portENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
    #define portEXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

#endif /* if ( configNUMBER_OF_CORES == 1 ) */

বাহ্যিক শূন্য vPortYield( শূন্য );
#define portYIELD()                                           vPortYield()

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    শূন্য vFunction( শূন্য * pvParameters ) __attribute__( ( noreturn ) )
#define portTASK_FUNCTION( vFunction, pvParameters )          শূন্য vFunction( শূন্য * pvParameters )

#যদি ( config_সংখ্যা_OF_CORES > 1 )
    /* Return the core ID on which the code is running. */
    #define portGET_CORE_ID()                0

/* Set the interrupt mask. */
    #define portSET_INTERRUPT_MASK()         0

/* Clear the interrupt mask. */
    #define portCLEAR_INTERRUPT_MASK( x )    ( ( শূন্য ) ( x ) )

/* Request the core ID x to yield. */
    #define portYIELD_CORE( x )              করো {} যখন( 0 )

/* Acquire the TASK lock. TASK lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #define portGET_TASK_LOCK( xCoreID )     করো {} যখন( 0 )

/* Release the TASK lock. If a TASK lock is locked by the same core multiple times,
 * it should be released as many times as it is locked. */
    #define portRELEASE_TASK_LOCK( xCoreID ) করো {} যখন( 0 )

/* Acquire the ISR lock. ISR lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #define portGET_ISR_LOCK( xCoreID )      করো {} যখন( 0 )

/* Release the ISR lock. If a ISR lock is locked by the same core multiple times, \
 * it should be released as many times as it is locked. */
    #define portRELEASE_ISR_LOCK( xCoreID )  করো {} যখন( 0 )

#endif /* if ( configNUMBER_OF_CORES > 1 ) */

#endif /* PORTMACRO_H */
