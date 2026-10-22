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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __PORTMACRO_H__
#ವ್ಯಾಖ್ಯಾನಿಸು __PORTMACRO_H__

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

#ಆದರೆ (config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು)
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY (TickType_t) 0xFFFF
#ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY (TickType_t) 0xFFFFFFFFF

    /* 32-bit tick type on a 32-bit architecture, so reads of the tick count do
    not need to be guarded with a critical section. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_TYPE_IS_ATOMIC 1
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು ಗಣ ಗಮ್ಯ unsupported tick type ಅಗಲ.
#ಆದರೆ_ಅಂತ್ಯ


/* Architecture specifics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH    (-1)
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS    ((TickType_t) 1000 / config_TICK_ದರ_HZ)
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT  8

/* Critical section handling. */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical(ಶೂನ್ಯ);
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()        v_ಪೋರ್ಟ್_Enter_Critical()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()         v_ಪೋರ್ಟ್_Exit_Critical()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()    asm( " CPSID I" )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()     asm( " CPSIE I" )

/* Scheduler utilities. */
#ಸೂಚನೆ SWI_ALIAS( v_ಪೋರ್ಟ್_Yield, 0 )
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ );
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()                 v_ಪೋರ್ಟ್_Yield()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SYS_SSIR1_REG           ( * ( ( ಅಸ್ಥಿರ uint32_t * ) 0xFFFFFFB0 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SYS_SSIR1_SSKEY         ( 0x7500UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_WITHIN_API()      { ಪೋರ್ಟ್_SYS_SSIR1_REG = ಪೋರ್ಟ್_SYS_SSIR1_SSKEY;  asm( " DSB " ); asm( " ISB " ); }
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x )     ಮಾಡು { ಆದರೆ( x != pdFALSE ) { ಪೋರ್ಟ್_SYS_SSIR1_REG = ಪೋರ್ಟ್_SYS_SSIR1_SSKEY;  ( ಶೂನ್ಯ ) ಪೋರ್ಟ್_SYS_SSIR1_REG; } } ಆಗ( 0 )

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION
    #ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION 1
#ಆದರೆ_ಅಂತ್ಯ

/* Architecture specific optimisations. */
#ಆದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1

    /* Check the configuration. */
    #ಆದರೆ( configMAX_PRIORITIES > 32 )
        #ದೋಷ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION can only be ಗಣ ಗಮ್ಯ 1 when configMAX_PRIORITIES is less than or equal ಗಮ್ಯ 32.  It is very rare that a system requires ಇನ್ನಷ್ಟು than 10 ಗಮ್ಯ 15 difference priorities as tasks that share a ಆದ್ಯತೆ will time ತುಂಡು.
    #ಆದರೆ_ಅಂತ್ಯ

    /* Store/clear the ready priorities in a bit map. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

    /*-----------------------------------------------------------*/

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities ) ux_ತುದಿ_ಆದ್ಯತೆ = ( 31 - __clz( ( uxReadyPriorities ) ) )

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/* Task function macros as described on the FreeRTOS.org WEB site. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION(vFunction, pvParameters)       ಶೂನ್ಯ vFunction(ಶೂನ್ಯ *pvParameters)
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO(vFunction, pvParameters) ಶೂನ್ಯ vFunction(ಶೂನ್ಯ *pvParameters)

#ಆದರೆ_ಅಂತ್ಯ /* __PORTMACRO_H__ */
