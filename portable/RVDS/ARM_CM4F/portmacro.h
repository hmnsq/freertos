/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR          ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT         ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE        ದ್ವಿಗುಣ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG          ದೀರ್ಘ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT         ಗಿಡ್ಡ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE    uint32_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE     ದೀರ್ಘ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ದೀರ್ಘ             ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ    UBaseType_t;

#ಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t     TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY              ( TickType_t ) 0xffff
#ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t     TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY              ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC    1
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು ಗಣ ಗಮ್ಯ unsupported tick type ಅಗಲ.
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH          ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS        ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT        8

/* Constants used with memory barrier intrinsics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE    ( 15 )

/*-----------------------------------------------------------*/

/* Scheduler utilities. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()                                     \
    {                                                   \
        /* Set a PendSV to request a context switch. */ \
        ಪೋರ್ಟ್_NVIC_INT_CTRL_REG = ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್; \
                                                        \
        /* Barriers are normally not required but do ensure the code is completely \
         * within the specified behaviour for the architecture. */ \
        __dsb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );                           \
        __isb( ಪೋರ್ಟ್_SY_ತುಂಬಿದ_READ_WRITE );                           \
    }
/*-----------------------------------------------------------*/

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_INT_CTRL_REG     ( *( ( ಅಸ್ಥಿರ uint32_t * ) 0xe000ed04 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NVIC_PENDSVSET_ಬಿಟ್    ( 1UL << 28UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( xSwitchRequired ) \
    ಮಾಡು                                           \
    {                                            \
        ಆದರೆ( xSwitchRequired != pdFALSE )         \
        {                                        \
            trace_ISR_EXIT_ಗಮ್ಯ_SCHEDULER();        \
            ಪೋರ್ಟ್_YIELD();                         \
        }                                        \
        ಇಲ್ಲದಿದ್ದರೆ                                     \
        {                                        \
            traceISR_EXIT();                     \
        }                                        \
    } ಆಗ( 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )    ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()                  v_ಪೋರ್ಟ್_Raise_BASEPRI()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()                   v_ಪೋರ್ಟ್_ಗಣ_BASEPRI( 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                      v_ಪೋರ್ಟ್_Enter_Critical()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                       v_ಪೋರ್ಟ್_Exit_Critical()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR()         ul_ಪೋರ್ಟ್_Raise_BASEPRI()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x )    v_ಪೋರ್ಟ್_ಗಣ_BASEPRI( x )

/*-----------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_SUPPRESS_TICKS_AND_SLEEP
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ಸಮಯ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_ಸಮಯ )    v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( x_Expected_Idle_ಸಮಯ )
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* Port specific optimisations. */
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

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities )    ux_ತುದಿ_ಆದ್ಯತೆ = ( 31UL - ( uint32_t ) __clz( ( uxReadyPriorities ) ) )

#ಆದರೆ_ಅಂತ್ಯ /* taskRECORD_READY_PRIORITY */
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not necessary for to use this port.  They are defined so the common demo files
 * (which build with all the ports) will build. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
/*-----------------------------------------------------------*/

#ಆದರೆ ( configASSERT_DEFINED == 1 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ( ಶೂನ್ಯ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASSERT_IF_ಅಡಚಣೆ_ಆದ್ಯತೆ_INVALID()    v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ()
#ಆದರೆ_ಅಂತ್ಯ

/* portNOP() is not required by this port. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INLINE              __inline

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_FORCE_INLINE
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FORCE_INLINE    __forceinline
#ಆದರೆ_ಅಂತ್ಯ

/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಪೋರ್ಟ್_FORCE_INLINE ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಗಣ_BASEPRI( uint32_t ulBASEPRI )
{
    __asm
    {
        /* Barrier instructions are not used as this function is only used to
         * lower the BASEPRI value. */
/* *INDENT-OFF* */
            msr basepri, ulBASEPRI
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಪೋರ್ಟ್_FORCE_INLINE ಶೂನ್ಯ v_ಪೋರ್ಟ್_Raise_BASEPRI( ಶೂನ್ಯ )
{
    uint32_t ulNewBASEPRI = config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ;

    __asm
    {
        /* Set BASEPRI to the max syscall priority to effect a critical
         * section. */
/* *INDENT-OFF* */
            msr basepri, ulNewBASEPRI
            dsb
            isb
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಪೋರ್ಟ್_FORCE_INLINE ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_BASEPRIFrom_ISR( ಶೂನ್ಯ )
{
    __asm
    {
        /* Set BASEPRI to 0 so no interrupts are masked.  This function is only
         * used to lower the mask in an interrupt, so memory barriers are not
         * used. */
/* *INDENT-OFF* */
            msr basepri, # 0
/* *INDENT-ON* */
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಪೋರ್ಟ್_FORCE_INLINE uint32_t ul_ಪೋರ್ಟ್_Raise_BASEPRI( ಶೂನ್ಯ )
{
    uint32_t ulReturn, ulNewBASEPRI = config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ;

    __asm
    {
        /* Set BASEPRI to the max syscall priority to effect a critical
         * section. */
/* *INDENT-OFF* */
            mrs ulReturn, basepri
            msr basepri, ulNewBASEPRI
            dsb
            isb
/* *INDENT-ON* */
    }

    ಹಿಂತಿರುಗಿ ulReturn;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಪೋರ್ಟ್_FORCE_INLINE ತಳ_Type_t x_ಪೋರ್ಟ್_Is_Inside_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    uint32_t ul_Current_ಅಡಚಣೆ;
    ತಳ_Type_t xReturn;

    /* Obtain the number of the currently executing interrupt. */
    __asm
    {
/* *INDENT-OFF* */
            mrs ul_Current_ಅಡಚಣೆ, ipsr
/* *INDENT-ON* */
    }

    ಆದರೆ( ul_Current_ಅಡಚಣೆ == 0 )
    {
        xReturn = pdFALSE;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        xReturn = pdTRUE;
    }

    ಹಿಂತಿರುಗಿ xReturn;
}

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
