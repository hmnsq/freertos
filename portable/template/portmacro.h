/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

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
#परिभाषय पत्तनम्_CHAR                 वर्ण
#परिभाषय पत्तनम्_FLOAT                भिन्न
#परिभाषय पत्तनम्_DOUBLE               द्विगुण
#परिभाषय पत्तनम्_LONG                 दीर्घ
#परिभाषय पत्तनम्_SHORT                पूर्णाङ्क
#परिभाषय पत्तनम्_राशिः_TYPE           uint8_t
#परिभाषय पत्तनम्_आधारः_TYPE            वर्ण

#परिभाषय पत्तनम्_राशिः_GROWTH         ( -1 )
#परिभाषय पत्तनम्_BYTE_ALIGNMENT       4
#परिभाषय पत्तनम्_POINTER_आकार_TYPE    size_t
प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
प्रकारनिर्देश चिह्नित वर्ण      आधारः_Type_t;
प्रकारनिर्देश अचिह्नित वर्ण    UBaseType_t;

#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffffU
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffffffffU
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_64_द्वयङ्काः )
    प्रकारनिर्देश uint64_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffffffffffffffffU
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः

/* Architecture specific optimisations. */
#यदि_अपरिभाषितम् config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION
    #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    1
#यदि_अन्तः

#यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #यदि ( configMAX_PRIORITIES > 32 )
        #दोषः config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION can only be समुच्चयः गन्तव्यम् 1 when configMAX_PRIORITIES is less than or equal गन्तव्यम् 32.  It is very rare that a system requires अधिकम् than 10 गन्तव्यम् 15 difference priorities as tasks that share a प्राथमिकता will time खण्डिका.
    #यदि_अन्तः

/* Store/clear the ready priorities in a bit map. */
    #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
    #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

/*-----------------------------------------------------------*/

    #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities ) \
    कुरु {                                                                 \
        ux_शिखरम्_प्राथमिकता = 0;                                               \
    } यावत्( 0 )

#यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* Disable the interrupts */
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    कुरु {} यावत्( 0 )

/* Enable the interrupts */
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     कुरु {} यावत्( 0 )

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES == 1 )
/* preserve current interrupt state and then disable interrupts */
    #परिभाषय पत्तनम्_ENTER_CRITICAL()    कुरु {} यावत्( 0 )

/* restore previously preserved interrupt state */
    #परिभाषय पत्तनम्_EXIT_CRITICAL()     कुरु {} यावत्( 0 )
#अन्यथा

/* The port can maintain the critical nesting count in TCB or maintain the critical
 * nesting count in the port. */
    #परिभाषय पत्तनम्_CRITICAL_NESTING_अन्तर्_TCB    1

/* vTaskEnterCritical and vTaskExitCritical should be used in the implementation
 * of portENTER/EXIT_CRITICAL if the number of cores is more than 1 in the system. */
    #परिभाषय पत्तनम्_ENTER_CRITICAL             vTaskEnterCritical
    #परिभाषय पत्तनम्_EXIT_CRITICAL              vTaskExitCritical

/* vTaskEnterCriticalFromISR and vTaskExitCriticalFromISR should be used in the
 * implementation of portENTER/EXIT_CRITICAL_FROM_ISR if the number of cores is
 * more than 1 in the system. */
    #परिभाषय पत्तनम्_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
    #परिभाषय पत्तनम्_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

#यदि_अन्तः /* if ( configNUMBER_OF_CORES == 1 ) */

बाह्य शून्य v_पत्तनम्_Yield( शून्य );
#परिभाषय पत्तनम्_YIELD()                                           v_पत्तनम्_Yield()

/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters ) __attribute__( ( noreturn ) )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )
    /* Return the core ID on which the code is running. */
    #परिभाषय पत्तनम्_GET_CORE_ID()                0

/* Set the interrupt mask. */
    #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्()         0

/* Clear the interrupt mask. */
    #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्( x )    ( ( शून्य ) ( x ) )

/* Request the core ID x to yield. */
    #परिभाषय पत्तनम्_YIELD_CORE( x )              कुरु {} यावत्( 0 )

/* Acquire the TASK lock. TASK lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #परिभाषय पत्तनम्_GET_TASK_तालकम्( xCoreID )     कुरु {} यावत्( 0 )

/* Release the TASK lock. If a TASK lock is locked by the same core multiple times,
 * it should be released as many times as it is locked. */
    #परिभाषय पत्तनम्_RELEASE_TASK_तालकम्( xCoreID ) कुरु {} यावत्( 0 )

/* Acquire the ISR lock. ISR lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #परिभाषय पत्तनम्_GET_ISR_तालकम्( xCoreID )      कुरु {} यावत्( 0 )

/* Release the ISR lock. If a ISR lock is locked by the same core multiple times, \
 * it should be released as many times as it is locked. */
    #परिभाषय पत्तनम्_RELEASE_ISR_तालकम्( xCoreID )  कुरु {} यावत्( 0 )

#यदि_अन्तः /* if ( configNUMBER_OF_CORES > 1 ) */

#यदि_अन्तः /* PORTMACRO_H */
