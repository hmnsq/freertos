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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __IAR_SYSTEMS_ICC__

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

    #ಆದರೆ __DATA_MODEL__ == __DATA_MODEL_FAR__ && __CODE_MODEL__ == __CODE_MODEL_NEAR__
        #warning This ಪೋರ್ಟ್ has not been tested with your selected ಸ್ಮರಣೆ model combination. If a far ದತ್ತಾಂಶ_2 model is required it is recommended ಗಮ್ಯ also use a far ಸಂಕೇತ_2 model.
    #ಆದರೆ_ಅಂತ್ಯ

    #ಆದರೆ __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This ಪೋರ್ಟ್ has not been tested with your selected ಸ್ಮರಣೆ model combination. If a far ಸಂಕೇತ_2 model is required it is recommended ಗಮ್ಯ also use a far ದತ್ತಾಂಶ_2 model.
    #ಆದರೆ_ಅಂತ್ಯ

/* Type definitions. */

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR          ಅಕ್ಷರ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT         ದಶಮಾಂಶ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE        ದ್ವಿಗುಣ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG          ದೀರ್ಘ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT         ಗಿಡ್ಡ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE    uint16_t
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE     ಗಿಡ್ಡ

    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE   ರಾಶಿ_Type_t;
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಗಿಡ್ಡ            ತಳ_Type_t;
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ   UBaseType_t;


    #ಆದರೆ __DATA_MODEL__ == __DATA_MODEL_FAR__
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE    uint32_t
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE    uint16_t
    #ಆದರೆ_ಅಂತ್ಯ


    #ಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ   TickType_t;
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY    ( TickType_t ) 0xffff
    #ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t       TickType_t;
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #ಇಲ್ಲದಿದ್ದರೆ
        #ದೋಷ config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು ಗಣ ಗಮ್ಯ unsupported tick type ಅಗಲ.
    #ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()    __asm( "DI" )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL()                                                  \
    {                                                                             \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ uint16_t usCriticalNesting;                               \
                                                                                  \
        ಪೋರ್ಟ್_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL()                                                   \
    {                                                                             \
        ಬಾಹ್ಯ ಅಸ್ಥಿರ uint16_t usCriticalNesting;                               \
                                                                                  \
        ಆದರೆ( usCriticalNesting > ಪೋರ್ಟ್_NO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            ಆದರೆ( usCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_SECTION_NESTING )            \
            {                                                                     \
                ಪೋರ್ಟ್_ENABLE_INTERRUPTS();                                          \
            }                                                                     \
        }                                                                         \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()                                         __asm( "NOP" )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()                                       __asm( "BRK" )
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configREQUIRE_ASM_ISR_WRAPPER
        #ವ್ಯಾಖ್ಯಾನಿಸು configREQUIRE_ASM_ISR_WRAPPER    1
    #ಆದರೆ_ಅಂತ್ಯ
    #ಆದರೆ( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x_Higher_ಆದ್ಯತೆ_Task_Woken )    ಮಾಡು { ಆದರೆ( x_Higher_ಆದ್ಯತೆ_Task_Woken != pdFALSE ) vTaskSwitchContext(); } ಆಗ( 0 )
    #ಇಲ್ಲದಿದ್ದರೆ
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( x_Higher_ಆದ್ಯತೆ_Task_Woken )    ಮಾಡು { ಆದರೆ( x_Higher_ಆದ್ಯತೆ_Task_Woken != pdFALSE ) ಪೋರ್ಟ್_YIELD(); } ಆಗ( 0 )
    #ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT    2
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH      ( -1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* __IAR_SYSTEMS_ICC__ */

; /*----------------------------------------------------------------------------- */
  /* The macros below are processed for asm sources which include portmacro.h. */
  /*----------------------------------------------------------------------------- */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __IAR_SYSTEMS_ASM__

    ; /* Functions and variables used by this file. */
      /*----------------------------------------------------------------------------- */
    EXTERN _pxCurrentTCB
    EXTERN _usCriticalNesting

    ; /* Macro used to declutter calls, depends on the selected code model. */
      /*----------------------------------------------------------------------------- */
    #ಆದರೆ __CODE_MODEL__ == __CODE_MODEL_FAR__
        #ವ್ಯಾಖ್ಯಾನಿಸು RCALL( X )    CALL F: X
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು RCALL( X )    CALL X
    #ಆದರೆ_ಅಂತ್ಯ


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
ಪೋರ್ಟ್_SAVE_CONTEXT MACRO
    ತಳ್ಳು_2 AX; /* Save AX Register to stack. */
    ತಳ್ಳು_2 HL
    #ಆದರೆ  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        ತಳ್ಳು_2 AX
    #ಇಲ್ಲದಿದ್ದರೆ
        MOV A, CS; /* Save CS register. */
        ತಳ್ಳು_2 AX
    #ಆದರೆ_ಅಂತ್ಯ
    ತಳ್ಳು_2 DE;                     /* Save the remaining general purpose registers. */
    ತಳ್ಳು_2 BC
    MOVW AX, _usCriticalNesting; /* Save the _usCriticalNesting value. */
    ತಳ್ಳು_2 AX
    MOVW AX, _pxCurrentTCB;      /* Save the Task stack pointer. */
    MOVW HL, AX
    MOVW AX, SP
         MOVW[ HL ], AX
         ENDM
    ; /*----------------------------------------------------------------------------- */


/*-----------------------------------------------------------------------------
 * ; * portRESTORE_CONTEXT MACRO
 * ; * Restores the task Stack Pointer then use this to restore _usCriticalNesting,
 * ; * general purpose registers and the CS and ES (only in __far memory mode)
 * ; * of the selected task from the task stack.
 * ; *---------------------------------------------------------------------------*/
ಪೋರ್ಟ್_RESTORE_CONTEXT MACRO
    MOVW AX, _pxCurrentTCB; /* Restore the Task stack pointer. */
    MOVW HL, AX
    MOVW AX, [ HL ]
    MOVW SP, AX
    ತೆಗೆ_3 AX; /* Restore _usCriticalNesting value. */
    MOVW _usCriticalNesting, AX
    ತೆಗೆ_3 BC; /* Restore the necessary general purpose registers. */
    ತೆಗೆ_3 DE
    #ಆದರೆ __CODE_MODEL__ == __CODE_MODEL_FAR__
        ತೆಗೆ_3 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #ಇಲ್ಲದಿದ್ದರೆ
        ತೆಗೆ_3 AX
        MOV CS, A; /* Restore CS register. */
    #ಆದರೆ_ಅಂತ್ಯ
    ತೆಗೆ_3 HL;        /* Restore general purpose register HL. */
    ತೆಗೆ_3 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#ಆದರೆ_ಅಂತ್ಯ /* __IAR_SYSTEMS_ASM__ */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
