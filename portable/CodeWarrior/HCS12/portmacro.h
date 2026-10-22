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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE  uint8_t
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE   ಅಕ್ಷರ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE ರಾಶಿ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ ಅಕ್ಷರ ತಳ_Type_t;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ UBaseType_t;

#ಆದರೆ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY ( TickType_t ) 0xffff
#ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t TickType_t;
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು ಗಣ ಗಮ್ಯ unsupported tick type ಅಗಲ.
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT          1
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH            ( -1 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()                 __asm( "swi" );
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()                   __asm( "nop" );
/*-----------------------------------------------------------*/

/* Critical section handling. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()             __asm( "cli" )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()            __asm( "sei" )

/*
 * Disable interrupts before incrementing the count of critical section nesting.
 * The nesting count is maintained so we know when interrupts should be
 * re-enabled.  Once interrupts are disabled the nesting count can be accessed
 * directly.  Each task maintains its own nesting count.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                                    \
{                                                               \
    ಬಾಹ್ಯ ಅಸ್ಥಿರ UBaseType_t uxCriticalNesting;  \
                                                                \
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();                                   \
    uxCriticalNesting++;                                        \
}

/*
 * Interrupts are disabled so we can access the nesting count directly.  If the
 * nesting is found to be 0 (no nesting) then we are leaving the critical
 * section and interrupts can be re-enabled.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು  ಪೋರ್ಟ್_EXIT_CRITICAL()                                    \
{                                                               \
    ಬಾಹ್ಯ ಅಸ್ಥಿರ UBaseType_t uxCriticalNesting;  \
                                                                \
    uxCriticalNesting--;                                        \
    ಆದರೆ( uxCriticalNesting == 0 )                                \
    {                                                           \
        ಪೋರ್ಟ್_ENABLE_INTERRUPTS();                                \
    }                                                           \
}
/*-----------------------------------------------------------*/

/* Task utilities. */

/*
 * These macros are very simple as the processor automatically saves and
 * restores its registers as interrupts are entered and exited.  In
 * addition to the (automatically stacked) registers we also stack the
 * critical nesting count.  Each task maintains its own critical nesting
 * count as it is legitimate for a task to yield from within a critical
 * section.  If the banked memory model is being used then the PPAGE
 * register is also stored as part of the tasks context.
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ BANKED_MODEL
    /*
     * Load the stack pointer for the task, then pull the critical nesting
     * count and PPAGE register from the stack.  The remains of the
     * context are restored by the RTI instruction.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESTORE_CONTEXT()                                   \
    {                                                               \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ ಶೂನ್ಯ * pxCurrentTCB;                        \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ UBaseType_t uxCriticalNesting;  \
                                                                    \
        __asm( "ldx pxCurrentTCB" );                                \
        __asm( "lds 0, x" );                                        \
        __asm( "pula" );                                            \
        __asm( "staa uxCriticalNesting" );                          \
        __asm( "pula" );                                            \
        __asm( "staa 0x30" ); /* 0x30 = PPAGE */                    \
    }

    /*
     * By the time this macro is called the processor has already stacked the
     * registers.  Simply stack the nesting count and PPAGE value, then save
     * the task stack pointer.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SAVE_CONTEXT()                                      \
    {                                                               \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ ಶೂನ್ಯ * pxCurrentTCB;                        \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ UBaseType_t uxCriticalNesting;  \
                                                                    \
        __asm( "ldaa 0x30" );  /* 0x30 = PPAGE */                   \
        __asm( "psha" );                                            \
        __asm( "ldaa uxCriticalNesting" );                          \
        __asm( "psha" );                                            \
        __asm( "ldx pxCurrentTCB" );                                \
        __asm( "sts 0, x" );                                        \
    }
#ಇಲ್ಲದಿದ್ದರೆ

    /*
     * These macros are as per the BANKED versions above, but without saving
     * and restoring the PPAGE register.
     */

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESTORE_CONTEXT()                                   \
    {                                                               \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ ಶೂನ್ಯ * pxCurrentTCB;                        \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ UBaseType_t uxCriticalNesting;  \
                                                                    \
        __asm( "ldx pxCurrentTCB" );                                \
        __asm( "lds 0, x" );                                        \
        __asm( "pula" );                                            \
        __asm( "staa uxCriticalNesting" );                          \
    }

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SAVE_CONTEXT()                                      \
    {                                                               \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ ಶೂನ್ಯ * pxCurrentTCB;                        \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ UBaseType_t uxCriticalNesting;  \
                                                                    \
        __asm( "ldaa uxCriticalNesting" );                          \
        __asm( "psha" );                                            \
        __asm( "ldx pxCurrentTCB" );                                \
        __asm( "sts 0, x" );                                        \
    }
#ಆದರೆ_ಅಂತ್ಯ

/*
 * Utility macro to call macros above in correct order in order to perform a
 * task switch from within a standard ISR.  This macro can only be used if
 * the ISR does not use any local (stack) variables.  If the ISR uses stack
 * variables portYIELD() should be used in it's place.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_SWITCH_FROM_ISR()                              \
    ಪೋರ್ಟ್_SAVE_CONTEXT();                                         \
    vTaskSwitchContext();                                       \
    ಪೋರ್ಟ್_RESTORE_CONTEXT();


/* Task function macros as described on the FreeRTOS.org WEB site. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters ) ಶೂನ್ಯ vFunction( ಶೂನ್ಯ *pvParameters )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters ) ಶೂನ್ಯ vFunction( ಶೂನ್ಯ *pvParameters )

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
