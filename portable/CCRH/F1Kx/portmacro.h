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

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
        ಬಾಹ್ಯ "C"
        {
    #ಆದರೆ_ಅಂತ್ಯ

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions - These are a bit legacy and not really used now, other
 * than portSTACK_TYPE and portBASE_TYPE. */
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

/* Defines the maximum time when using a wait command in a task */
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

/* Architecture specifics */

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_STSR( reg )              __stsr( ( reg ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LDSR( reg, val )         __ldsr( ( reg ), ( val ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_STSR_CCRH( reg, sel )    __stsr_rh( ( reg ), ( sel ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SYNCM()                  __syncm()

/* Determine the descending of the stack from high address to address */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH      ( -1 )

/* Determine the time (in milliseconds) corresponding to each tick */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )

/* It is a multiple of 4 (the two lower-order bits of the address = 0),
 * otherwise it will cause MAE (Misaligned Exception) according to the manual */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT    ( 4 )

/* Interrupt control macros. */

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()     __EI() /* Macro to enable all maskable interrupts. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()    __DI() /* Macro to disable all maskable interrupts. */
    #ವ್ಯಾಖ್ಯಾನಿಸು taskENABLE_INTERRUPTS()     ಪೋರ್ಟ್_ENABLE_INTERRUPTS()
    #ವ್ಯಾಖ್ಯಾನಿಸು taskDISABLE_INTERRUPTS()    ಪೋರ್ಟ್_DISABLE_INTERRUPTS()

/* SMP build which means configNUM_CORES is relevant */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SUPPORT_SMP              1

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_CORE_ಎಣಿಕೆ           2
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಸಂಖ್ಯೆ_ದ_CORES
        #ವ್ಯಾಖ್ಯಾನಿಸು config_ಸಂಖ್ಯೆ_ದ_CORES    1
    #ಆದರೆ_ಅಂತ್ಯ

/*-----------------------------------------------------------*/
/* Scheduler utilities */

/* Called at the end of an ISR that can cause a context switch */
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಗಣ_Switch( ತಳ_Type_t xSwitchRequired );

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )    v_ಪೋರ್ಟ್_ಗಣ_Switch( x )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )       ಪೋರ್ಟ್_ಕೊನೆ_SWITCHING_ISR( x )

/* Use to transfer control from one task to perform other tasks of
 * higher priority */
    ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ );

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()    v_ಪೋರ್ಟ್_Yield()
    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

/* Return the core ID on which the code is running. */
        ಬಾಹ್ಯ ತಳ_Type_t x_ಪೋರ್ಟ್_GET_CORE_ID();

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_CORE_ID()    x_ಪೋರ್ಟ್_GET_CORE_ID()
        #ವ್ಯಾಖ್ಯಾನಿಸು coreid    x_ಪೋರ್ಟ್_GET_CORE_ID()

/* Request the core ID x to yield. */
        ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield_Core( uint32_t coreID );

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_CORE( x )                v_ಪೋರ್ಟ್_Yield_Core( x )

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL_FROM_ISR()      vTaskEnterCriticalFromISR()
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL_FROM_ISR( x )    vTaskExitCriticalFromISR( x )

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES > 1 ) */

    #ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES == 1 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ISR_ಬೀಗ( xCoreID )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_ISR_ಬೀಗ( xCoreID )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_TASK_ಬೀಗ( xCoreID )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_TASK_ಬೀಗ( xCoreID )
    #ಇಲ್ಲದಿದ್ದರೆ
        ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Recursive_ಬೀಗ_Acquire( ತಳ_Type_t xCoreID, ತಳ_Type_t xFromIsr );
        ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Recursive_ಬೀಗ_Release( ತಳ_Type_t xCoreID, ತಳ_Type_t xFromIsr );

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ISR_ಬೀಗ( xCoreID )         v_ಪೋರ್ಟ್_Recursive_ಬೀಗ_Acquire( ( xCoreID ), pdTRUE )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_ISR_ಬೀಗ( xCoreID )     v_ಪೋರ್ಟ್_Recursive_ಬೀಗ_Release( ( xCoreID ), pdTRUE )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_TASK_ಬೀಗ( xCoreID )        v_ಪೋರ್ಟ್_Recursive_ಬೀಗ_Acquire( ( xCoreID ), pdFALSE )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RELEASE_TASK_ಬೀಗ( xCoreID )    v_ಪೋರ್ಟ್_Recursive_ಬೀಗ_Release( ( xCoreID ), pdFALSE )
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUMBER_OF_CORES == 1 ) */

/*-----------------------------------------------------------*/
/* Critical section management. */

/* The critical nesting functions defined within tasks.c */

    ಬಾಹ್ಯ ಶೂನ್ಯ vTaskEnterCritical( ಶೂನ್ಯ );
    ಬಾಹ್ಯ ಶೂನ್ಯ vTaskExitCritical( ಶೂನ್ಯ );

/* Macro to mark the start of a critical code region */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()    vTaskEnterCritical()

/* Macro to mark the end of a critical code region */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()     vTaskExitCritical()

/*-----------------------------------------------------------*/
/* Macros to set and clear the interrupt mask. */
    ಪೋರ್ಟ್_LONG x_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ();
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( ಪೋರ್ಟ್_LONG );

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()                  x_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ( x )             v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( ( x ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR()         x_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( x )    v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( ( x ) )

/*-----------------------------------------------------------*/
/* Task function macros as described on the FreeRTOS.org WEB site. */

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

/*-----------------------------------------------------------*/

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
