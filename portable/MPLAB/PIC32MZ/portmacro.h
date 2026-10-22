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

/* System include files */
#ಅನ್ತರ್ಭಾವ <xc.h>

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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR        ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT       ದಶಮಾಂಶ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE      ದ್ವಿಗುಣ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG        ದೀರ್ಘ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT       ಗಿಡ್ಡ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE  uint32_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE   ದೀರ್ಘ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ದೀರ್ಘ ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ UBaseType_t;

#ಆದರೆ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY ( TickType_t ) 0xffff
#ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY ( TickType_t ) 0xffffffffUL

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC 1
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು ಗಣ ಗಮ್ಯ unsupported tick type ಅಗಲ.
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT          8
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH            -1
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
/*-----------------------------------------------------------*/

/* Critical section management. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IPL_ಸರಿಸು               ( 10UL )
/* Don't straddle the CEE bit.  Interrupts calling FreeRTOS functions should
never have higher IPL bits set anyway. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ALL_IPL_ಬಿಟ್ಟುಗಳು            ( 0x7FUL << ಪೋರ್ಟ್_IPL_ಸರಿಸು )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SW0_ಬಿಟ್                 ( 0x01 << 8 )

/* This clears the IPL bits, then sets them to
configMAX_SYSCALL_INTERRUPT_PRIORITY.  An extra check is performed if
configASSERT() is defined to ensure an assertion handler does not inadvertently
attempt to lower the IPL when the call to assert was triggered because the IPL
value was found to be above configMAX_SYSCALL_INTERRUPT_PRIORITY when an ISR
safe FreeRTOS API function was executed.  ISR safe FreeRTOS API functions are
those that end in FromISR.  FreeRTOS maintains a separate interrupt API to
ensure API function and interrupt entry is as fast and as simple as possible. */
#ಆದರೆ ( configASSERT_DEFINED == 1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()                                            \
    {                                                                           \
    uint32_t ul_ಸ್ಥಿತಿ;                                                          \
                                                                                \
        /* Mask interrupts at and below the kernel interrupt priority. */       \
        ul_ಸ್ಥಿತಿ = CP0_GET_ಸ್ಥಿತಿ();                                           \
                                                                                \
        /* Is the current IPL below configMAX_SYSCALL_INTERRUPT_PRIORITY? */    \
        ಆದರೆ( ( ( ul_ಸ್ಥಿತಿ & ಪೋರ್ಟ್_ALL_IPL_ಬಿಟ್ಟುಗಳು ) >> ಪೋರ್ಟ್_IPL_ಸರಿಸು ) < config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ ) \
        {                                                                       \
            ul_ಸ್ಥಿತಿ &= ~ಪೋರ್ಟ್_ALL_IPL_ಬಿಟ್ಟುಗಳು;                                      \
            CP0_ಗಣ_ಸ್ಥಿತಿ( ( ul_ಸ್ಥಿತಿ | ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_IPL_ಸರಿಸು ) ) ); \
        }                                                                       \
    }
#ಇಲ್ಲದಿದ್ದರೆ /* configASSERT */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()                                        \
    {                                                                       \
    uint32_t ul_ಸ್ಥಿತಿ;                                                      \
                                                                            \
        /* Mask interrupts at and below the kernel interrupt priority. */   \
        ul_ಸ್ಥಿತಿ = CP0_GET_ಸ್ಥಿತಿ();                                       \
        ul_ಸ್ಥಿತಿ &= ~ಪೋರ್ಟ್_ALL_IPL_ಬಿಟ್ಟುಗಳು;                                      \
        CP0_ಗಣ_ಸ್ಥಿತಿ( ( ul_ಸ್ಥಿತಿ | ( config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_IPL_ಸರಿಸು ) ) ); \
    }
#ಆದರೆ_ಅಂತ್ಯ /* configASSERT */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()                                         \
{                                                                       \
uint32_t ul_ಸ್ಥಿತಿ;                                                      \
                                                                        \
    /* Unmask all interrupts. */                                        \
    ul_ಸ್ಥಿತಿ = CP0_GET_ಸ್ಥಿತಿ();                                       \
    ul_ಸ್ಥಿತಿ &= ~ಪೋರ್ಟ್_ALL_IPL_ಬಿಟ್ಟುಗಳು;                                      \
    CP0_ಗಣ_ಸ್ಥಿತಿ( ul_ಸ್ಥಿತಿ );                                        \
}


ಬಾಹ್ಯ ಶೂನ್ಯ vTaskEnterCritical( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ vTaskExitCritical( ಶೂನ್ಯ );
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CRITICAL_NESTING_ಒಳ_TCB 1
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()        vTaskEnterCritical()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()         vTaskExitCritical()

ಬಾಹ್ಯ UBaseType_t ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR();
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( UBaseType_t );
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR() ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( ux_Saved_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್ ) v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( ux_Saved_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್ )

#ಆದರೆ ( __mips_hard_float == 0 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    #ದೋಷ configUSE_TASK_FPU_SUPPORT can only be ಗಣ ಗಮ್ಯ 1 when the part supports a hardware FPU module.
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ ( __mips_hard_float == 1 ) && ( configUSE_TASK_FPU_SUPPORT == 1 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_ಬಳಸುತ್ತದೆ_FLOATING_ಬಿಂದು() v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU()
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION
    #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION 1
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #ಆದರೆ( configMAX_PRIORITIES > 32 )
        #ದೋಷ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION can only be ಗಣ ಗಮ್ಯ 1 when configMAX_PRIORITIES is less than or equal ಗಮ್ಯ 32.  It is very rare that a system requires ಇನ್ನಷ್ಟು than 10 ಗಮ್ಯ 15 difference priorities as tasks that share a ಆದ್ಯತೆ will time ತುಂಡು.
    #ಆದರೆ_ಅಂತ್ಯ

    /* Store/clear the ready priorities in a bit map. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

    /*-----------------------------------------------------------*/

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities ) ux_ತುದಿ_ಆದ್ಯತೆ = ( 31UL - _clz( ( uxReadyPriorities ) ) )

#ಆದರೆ_ಅಂತ್ಯ /* taskRECORD_READY_PRIORITY */

/*-----------------------------------------------------------*/

/* Task utilities. */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()                             \
{                                               \
uint32_t ulCause;                               \
                                                \
    /* Trigger software interrupt. */           \
    ulCause = _CP0_GET_CAUSE();                 \
    ulCause |= ಪೋರ್ಟ್_SW0_ಬಿಟ್;                     \
    CP0_ಗಣ_CAUSE( ulCause );                  \
}

ಬಾಹ್ಯ ಅಸ್ಥಿರ UBaseType_t ux_ಅಡಚಣೆ_Nesting;
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASSERT_IF_ಒಳ_ISR() configASSERT( ux_ಅಡಚಣೆ_Nesting == 0 )

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()   __asm ಅಸ್ಥಿರ ( "nop" )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters ) ಶೂನ್ಯ vFunction( ಶೂನ್ಯ *pvParameters ) __attribute__((noreturn))
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters ) ಶೂನ್ಯ vFunction( ಶೂನ್ಯ *pvParameters )
/*-----------------------------------------------------------*/

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

/* Required by the kernel aware debugger. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __DEBUG
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_REMOVE_STATIC_QUALIFIER
#ಆದರೆ_ಅಂತ್ಯ

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
