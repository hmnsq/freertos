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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE    uint32_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE     ದೀರ್ಘ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ದೀರ್ಘ             ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ    UBaseType_t;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t         TickType_t;
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY    ( TickType_t ) 0xffffffffUL

/* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
 * not need to be guarded with a critical section. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC    1

/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH      ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT    8

/*-----------------------------------------------------------*/

/* Task utilities. */

/* Called at the end of an ISR that can cause a context switch. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( xSwitchRequired )      \
    {                                                 \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ uint32_t ul_ಪೋರ್ಟ್_Yield_Required; \
                                                      \
        ಆದರೆ( xSwitchRequired != pdFALSE )              \
        {                                             \
            ul_ಪೋರ್ಟ್_Yield_Required = pdTRUE;             \
        }                                             \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )    ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()     v_ಪೋರ್ಟ್_Yield();

/*-----------------------------------------------------------*/

/*
 * Critical section management.
 */

ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_Interrupts( ಶೂನ್ಯ );
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Disable_Interrupts( ಶೂನ್ಯ );
ಬಾಹ್ಯ uint32_t ul_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( ಶೂನ್ಯ );

/* In the absence of a priority mask register, these functions and macros
 * globally enable and disable interrupts. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                    v_ಪೋರ್ಟ್_Enter_Critical();
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                     v_ಪೋರ್ಟ್_Exit_Critical();
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()                 v_ಪೋರ್ಟ್_Enable_Interrupts();
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()                v_ಪೋರ್ಟ್_Disable_Interrupts();
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR()       ul_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR();
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x )  ಮಾಡು { ಆದರೆ( x == 0 ) ಪೋರ್ಟ್_ENABLE_INTERRUPTS(); } ಆಗ( 0 )

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site.  These are
 * not required for this port but included in case common demo code that uses these
 * macros is used. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

/* Tickless idle/low power functionality. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_SUPPRESS_TICKS_AND_SLEEP
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( TickType_t x_Expected_Idle_ಸಮಯ );
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SUPPRESS_TICKS_AND_SLEEP( x_Expected_Idle_ಸಮಯ )    v_ಪೋರ್ಟ್_Suppress_Ticks_And_Sleep( x_Expected_Idle_ಸಮಯ )
#ಆದರೆ_ಅಂತ್ಯ

/* Prototype of the FreeRTOS tick handler.  This must be installed as the
 * handler for whichever peripheral is used to generate the RTOS tick. */
ಶೂನ್ಯ FreeRTOS_Tick_Handler( ಶೂನ್ಯ );

/**
 * @brief Returns the number of leading zeros in a 32 bit variable.
 *
 * @param[in] ulBitmap 32-Bit number to count leading zeros in.
 *
 * @return The number of leading zeros in ulBitmap.
 */
UBaseType_t ul_ಪೋರ್ಟ್_ಎಣಿಕೆ_Leading_Zeros( UBaseType_t ulBitmap );

/* If configUSE_TASK_FPU_SUPPORT is set to 1 (or left undefined) then tasks are
 * created without an FPU context and must call vPortTaskUsesFPU() to give
 * themselves an FPU context before using any FPU instructions.  If
 * configUSE_TASK_FPU_SUPPORT is set to 2 then all tasks will have an FPU
 * context by default. */
#ಆದರೆ ( configUSE_TASK_FPU_SUPPORT != 2 )
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ );
#ಇಲ್ಲದಿದ್ದರೆ
    /* Each task has an FPU context already, so define this function as a
     * no-op. */
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

    /* Store, clear and get the ready priorities in a bit map. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities )  ux_ತುದಿ_ಆದ್ಯತೆ = ( 31UL - ul_ಪೋರ್ಟ್_ಎಣಿಕೆ_Leading_Zeros( ( ux_ತುದಿ_Ready_ಆದ್ಯತೆ ) ) )

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()               __asm ಅಸ್ಥಿರ ( "NOP" )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INLINE              __inline
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER()    __asm ಅಸ್ಥಿರ ( "" ::: "memory" )

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
