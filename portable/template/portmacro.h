/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * license and copyright intentionally withheld to promote copying into user code.
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR                 ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT                ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE               ದ್ವಿಗುಣ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG                 ದೀರ್ಘ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT                ಪೂರ್ಣಾಂಕ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE           uint8_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE            ಅಕ್ಷರ

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH         ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT       4
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE    size_t
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ ಅಕ್ಷರ      ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ    UBaseType_t;

#ಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t     TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY    ( TickType_t ) 0xffffU
#ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t     TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY    ( TickType_t ) 0xffffffffU
#ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_64_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t     TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY    ( TickType_t ) 0xffffffffffffffffU
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು ಗಣ ಗಮ್ಯ unsupported tick type ಅಗಲ.
#ಆದರೆ_ಅಂತ್ಯ

/* Architecture specific optimisations. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION
    #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION    1
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
    #ಆದರೆ ( configMAX_PRIORITIES > 32 )
        #ದೋಷ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION can only be ಗಣ ಗಮ್ಯ 1 when configMAX_PRIORITIES is less than or equal ಗಮ್ಯ 32.  It is very rare that a system requires ಇನ್ನಷ್ಟು than 10 ಗಮ್ಯ 15 difference priorities as tasks that share a ಆದ್ಯತೆ will time ತುಂಡು.
    #ಆದರೆ_ಅಂತ್ಯ

/* Store/clear the ready priorities in a bit map. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

/*-----------------------------------------------------------*/

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities ) \
    ಮಾಡು {                                                                 \
        ux_ತುದಿ_ಆದ್ಯತೆ = 0;                                               \
    } ಆಗ( 0 )

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* Disable the interrupts */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()    ಮಾಡು {} ಆಗ( 0 )

/* Enable the interrupts */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()     ಮಾಡು {} ಆಗ( 0 )

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
/* preserve current interrupt state and then disable interrupts */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()    ಮಾಡು {} ಆಗ( 0 )

/* restore previously preserved interrupt state */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()     ಮಾಡು {} ಆಗ( 0 )
#ಇಲ್ಲದಿದ್ದರೆ

/* The port can maintain the critical nesting count in TCB or maintain the critical
 * nesting count in the port. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CRITICAL_NESTING_ಒಳ_TCB    1

/* vTaskEnterCritical and vTaskExitCritical should be used in the implementation
 * of portENTER/EXIT_CRITICAL if the number of cores is more than 1 in the system. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL             vTaskEnterCritical
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL              vTaskExitCritical

/* vTaskEnterCriticalFromISR and vTaskExitCriticalFromISR should be used in the
 * implementation of portENTER/EXIT_CRITICAL_FROM_ISR if the number of cores is
 * more than 1 in the system. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL_FROM_ISR    vTaskEnterCriticalFromISR
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL_FROM_ISR     vTaskExitCriticalFromISR

#ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES == 1 ) */

ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ );
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()                                           v_ಪೋರ್ಟ್_Yield()

/* Task function macros as described on the FreeRTOS.org WEB site. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters ) __attribute__( ( noreturn ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )
    /* Return the core ID on which the code is running. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_CORE_ID()                0

/* Set the interrupt mask. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()         0

/* Clear the interrupt mask. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ( x )    ( ( ಶೂನ್ಯ ) ( x ) )

/* Request the core ID x to yield. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_CORE( x )              ಮಾಡು {} ಆಗ( 0 )

/* Acquire the TASK lock. TASK lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_TASK_ಬೀಗ( xCoreID )     ಮಾಡು {} ಆಗ( 0 )

/* Release the TASK lock. If a TASK lock is locked by the same core multiple times,
 * it should be released as many times as it is locked. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_TASK_ಬೀಗ( xCoreID ) ಮಾಡು {} ಆಗ( 0 )

/* Acquire the ISR lock. ISR lock is a recursive lock.
 * It should be able to be locked by the same core multiple times. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ISR_ಬೀಗ( xCoreID )      ಮಾಡು {} ಆಗ( 0 )

/* Release the ISR lock. If a ISR lock is locked by the same core multiple times, \
 * it should be released as many times as it is locked. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_ISR_ಬೀಗ( xCoreID )  ಮಾಡು {} ಆಗ( 0 )

#ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES > 1 ) */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
