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
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE    size_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE     ದೀರ್ಘ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ತಳ_TYPE    ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t         UBaseType_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t         TickType_t;
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY              ( ( TickType_t ) 0xffffffffffffffff )

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH         ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS       ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT       16
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE    uint64_t

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( xSwitchRequired ) \
    {                                            \
        ಬಾಹ್ಯ uint64_t ull_ಪೋರ್ಟ್_Yield_Required;    \
                                                 \
        ಆದರೆ( xSwitchRequired != pdFALSE )         \
        {                                        \
            ull_ಪೋರ್ಟ್_Yield_Required = pdTRUE;       \
        }                                        \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )    ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )
#ಆದರೆ defined( GUEST )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()            __asm ಅಸ್ಥಿರ ( "SVC 0" ::: "memory" )
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()            __asm ಅಸ್ಥಿರ ( "SMC 0" ::: "memory" )
#ಆದರೆ_ಅಂತ್ಯ

/*-----------------------------------------------------------
* Critical section control
*----------------------------------------------------------*/

ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ );
ಬಾಹ್ಯ UBaseType_t ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( UBaseType_t ux_New_ಮುಖವಾಡ_ಮೌಲ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Install_Free_RTOSVector_ಕೋಷ್ಟಕ( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()                       \
    __asm ಅಸ್ಥಿರ ( "MSR DAIFSET, #2" ::: "memory" ); \
    __asm ಅಸ್ಥಿರ ( "DSB SY" );                       \
    __asm ಅಸ್ಥಿರ ( "ISB SY" );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()                        \
    __asm ಅಸ್ಥಿರ ( "MSR DAIFCLR, #2" ::: "memory" ); \
    __asm ಅಸ್ಥಿರ ( "DSB SY" );                       \
    __asm ಅಸ್ಥಿರ ( "ISB SY" );


/* These macros do not globally disable/enable interrupts.  They do mask off
 * interrupts that have a priority below configMAX_API_CALL_INTERRUPT_PRIORITY. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                      v_ಪೋರ್ಟ್_Enter_Critical();
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                       v_ಪೋರ್ಟ್_Exit_Critical();
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR()         ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x )    v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( x )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
ಶೂನ್ಯ FreeRTOS_Tick_Handler( ಶೂನ್ಯ );

/* If configUSE_TASK_FPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without an FPU context and must call vPortTaskUsesFPU() to give
 * themselves an FPU context before using any FPU instructions.  If
 * configUSE_TASK_FPU_SUPPORT is set to 2 then all tasks will have an FPU context
 * by default. */
#ಆದರೆ ( configUSE_TASK_FPU_SUPPORT != 2 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ );
#ಇಲ್ಲದಿದ್ದರೆ
    /* Each task has an FPU context already, so define this function away to
    * nothing to prevent it from being called accidentally. */
    #ವ್ಯಾಖ್ಯಾನಿಸು v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU()
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_ಬಳಸುತ್ತದೆ_FLOATING_ಬಿಂದು()    v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU()

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅತಿಕಡಿಮೆ_ಅಡಚಣೆ_ಆದ್ಯತೆ           ( ( ( uint32_t ) config_UNIQUE_ಅಡಚಣೆ_PRIORITIES ) - 1UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅತಿಕಡಿಮೆ_USABLE_ಅಡಚಣೆ_ಆದ್ಯತೆ    ( ಪೋರ್ಟ್_ಅತಿಕಡಿಮೆ_ಅಡಚಣೆ_ಆದ್ಯತೆ - 1UL )

/* Architecture specific optimisations. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION
    #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION    1
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1

/* Store/clear the ready priorities in a bit map. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

/*-----------------------------------------------------------*/

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities )    ux_ತುದಿ_ಆದ್ಯತೆ = ( 31 - __builtin_clz( uxReadyPriorities ) )

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ಆದರೆ ( configASSERT_DEFINED == 1 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ( ಶೂನ್ಯ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASSERT_IF_ಅಡಚಣೆ_ಆದ್ಯತೆ_INVALID()    v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ()
#ಆದರೆ_ಅಂತ್ಯ /* configASSERT */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()                                         __asm ಅಸ್ಥಿರ ( "NOP" )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INLINE    __inline

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#ಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 16
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            4
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    3
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 32
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            3
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    2
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 64
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            2
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    1
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 128
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            1
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    0
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 256
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            0
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    0
#ಇಲ್ಲದಿದ್ದರೆ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #ದೋಷ Invalid config_UNIQUE_ಅಡಚಣೆ_PRIORITIES setting.  config_UNIQUE_ಅಡಚಣೆ_PRIORITIES must be ಗಣ ಗಮ್ಯ the ಸಂಖ್ಯೆ ದ unique priorities implemented by the ಗುರಿ hardware
#ಆದರೆ_ಅಂತ್ಯ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER()    __asm ಅಸ್ಥಿರ ( "" ::: "memory" )

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
