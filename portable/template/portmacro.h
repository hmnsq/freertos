/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

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
#घोषणा portCHAR                 अक्षर
#घोषणा portFLOAT                भग्न
#घोषणा portDOUBLE               द्विगुन
#घोषणा portLONG                 दीर्घ
#घोषणा portSHORT                पूर्णांक
#घोषणा port_ढेर_TYPE           uint8_t
#घोषणा portBASE_TYPE            अक्षर

#घोषणा port_ढेर_GROWTH         ( -1 )
#घोषणा portBYTE_ALIGNMENT       4
#घोषणा port_POINTER_आकार_TYPE    माप_प्रकार
प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार चिन्हित अक्षर      BaseType_t;
प्रकार अचिन्हित अक्षर    UBaseType_t;

#अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t     TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) 0xffffU
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t     TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) 0xffffffffU
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_64_BITS )
    प्रकार uint64_t     TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) 0xffffffffffffffffU
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर

/* Architecture specific optimisations. */
#अगर_अघोषित configUSE_PORT_OPTIMISED_TASK_SELECTION
    #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#पूर्ण_अगर

#अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #अगर ( configMAX_PRIORITIES > 32 )
        #त्रुटि configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 difference priorities as tasks that share a priority will समय slice.
    #पूर्ण_अगर

/* Store/clear the ready priorities in a bit map. */
    #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
    #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

    #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities ) \
    करो {                                                                 \
        ux_शीर्ष_Priority = 0;                                               \
    } जबतक( 0 )

#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* Disable the interrupts */
#घोषणा portDISABLE_INTERRUPTS()    करो {} जबतक( 0 )

/* Enable the interrupts */
#घोषणा portENABLE_INTERRUPTS()     करो {} जबतक( 0 )

#अगर ( config_संख्या_OF_CORES == 1 )
/* preserve current interrupt state and then disable interrupts */
    #घोषणा portENTER_CRITICAL()    करो {} जबतक( 0 )

/* restore previously preserved interrupt state */
    #घोषणा portEXIT_CRITICAL()     करो {} जबतक( 0 )
#अन्यथा

/* The port can maintain the critical nesting count in TCB or maintain the critical
 * nesting count in the port. */
    #घोषणा portCRITICAL_NESTING_IN_TCB    1

/* vTaskEnterCritical and vTaskExitCritical should be used in the implementation
 * of portENTER/EXIT_CRITICAL if the number of cores is more than 1 in the system. */
    #घोषणा portENTER_CRITICAL             vTaskEnterCritical
    #घोषणा portEXIT_CRITICAL              vTaskExitCritical

/* vTaskEnterCriticalFromISR and vTaskExitCriticalFromISR should be used in the
 * implementation of portENTER/EXIT_CRITICAL_FROM_ISR if the number of cores is
 * more than 1 in the system. */
    #घोषणा portENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
    #घोषणा portEXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

#पूर्ण_अगर /* if ( configNUMBER_OF_CORES == 1 ) */

बाह्य व्योम vPortYield( व्योम );
#घोषणा portYIELD()                                           vPortYield()

/* Task function macros as described on the FreeRTOS.org WEB site. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters ) __attribute__( ( noreturn ) )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

#अगर ( config_संख्या_OF_CORES > 1 )
    /* Return the core ID on which the code is running. */
    #घोषणा portGET_CORE_ID()                0

/* Set the interrupt mask. */
    #घोषणा portSET_INTERRUPT_MASK()         0

/* Clear the interrupt mask. */
    #घोषणा portCLEAR_INTERRUPT_MASK( x )    ( ( व्योम ) ( x ) )

/* Request the core ID x to yield. */
    #घोषणा portYIELD_CORE( x )              करो {} जबतक( 0 )

/* Acquire the TASK lock. TASK lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #घोषणा portGET_TASK_LOCK( xCoreID )     करो {} जबतक( 0 )

/* Release the TASK lock. If a TASK lock is locked by the same core multiple times,
 * it should be released as many times as it is locked. */
    #घोषणा portRELEASE_TASK_LOCK( xCoreID ) करो {} जबतक( 0 )

/* Acquire the ISR lock. ISR lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #घोषणा portGET_ISR_LOCK( xCoreID )      करो {} जबतक( 0 )

/* Release the ISR lock. If a ISR lock is locked by the same core multiple times, \
 * it should be released as many times as it is locked. */
    #घोषणा portRELEASE_ISR_LOCK( xCoreID )  करो {} जबतक( 0 )

#पूर्ण_अगर /* if ( configNUMBER_OF_CORES > 1 ) */

#पूर्ण_अगर /* PORTMACRO_H */
