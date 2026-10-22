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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __IAR_SYSTEMS_ICC__

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
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

    #ਜੇ __DATA_MODEL__ == __DATA_MODEL_FAR__ && __CODE_MODEL__ == __CODE_MODEL_NEAR__
        #warning This ਪੋਰਟ has not been tested with your selected ਸਮ੍ਰਿਤੀ model combination. If a far ਅੰਕੜੇ_2 model is required it is recommended ਮੰਜ਼ਿਲ also use a far ਕੋਡ model.
    #ਜੇ_ਅੰਤ

    #ਜੇ __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This ਪੋਰਟ has not been tested with your selected ਸਮ੍ਰਿਤੀ model combination. If a far ਕੋਡ model is required it is recommended ਮੰਜ਼ਿਲ also use a far ਅੰਕੜੇ_2 model.
    #ਜੇ_ਅੰਤ

/* Type definitions. */

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          ਅੱਖਰ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          ਲੰਮਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         ਛੋਟਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    uint16_t
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਛੋਟਾ

    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE   ਢੇਰ_Type_t;
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਛੋਟਾ            ਅਧਾਰ_Type_t;
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ   UBaseType_t;


    #ਜੇ __DATA_MODEL__ == __DATA_MODEL_FAR__
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE    uint32_t
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE    uint16_t
    #ਜੇ_ਅੰਤ


    #ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ   TickType_t;
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) 0xffff
    #ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t       TickType_t;
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #ਨਹੀਂਤਾਂ
        #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
    #ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()    __asm( "DI" )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                                                  \
    {                                                                             \
        ਬਾਹਰੀ ਅਸਥਿਰ uint16_t usCriticalNesting;                               \
                                                                                  \
        ਪੋਰਟ_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL()                                                   \
    {                                                                             \
        ਬਾਹਰੀ ਅਸਥਿਰ uint16_t usCriticalNesting;                               \
                                                                                  \
        ਜੇ( usCriticalNesting > ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            ਜੇ( usCriticalNesting == ਪੋਰਟ_NO_CRITICAL_SECTION_NESTING )            \
            {                                                                     \
                ਪੋਰਟ_ENABLE_INTERRUPTS();                                          \
            }                                                                     \
        }                                                                         \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()                                         __asm( "NOP" )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()                                       __asm( "BRK" )
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configREQUIRE_ASM_ISR_WRAPPER
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configREQUIRE_ASM_ISR_WRAPPER    1
    #ਜੇ_ਅੰਤ
    #ਜੇ( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x_Higher_ਤਰਜੀਹ_Task_Woken )    ਕਰੋ { ਜੇ( x_Higher_ਤਰਜੀਹ_Task_Woken != pdFALSE ) vTaskSwitchContext(); } ਜਦੋਂ( 0 )
    #ਨਹੀਂਤਾਂ
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( x_Higher_ਤਰਜੀਹ_Task_Woken )    ਕਰੋ { ਜੇ( x_Higher_ਤਰਜੀਹ_Task_Woken != pdFALSE ) ਪੋਰਟ_YIELD(); } ਜਦੋਂ( 0 )
    #ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT    2
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH      ( -1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* __IAR_SYSTEMS_ICC__ */

; /*----------------------------------------------------------------------------- */
  /* The macros below are processed for asm sources which include portmacro.h. */
  /*----------------------------------------------------------------------------- */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __IAR_SYSTEMS_ASM__

    ; /* Functions and variables used by this file. */
      /*----------------------------------------------------------------------------- */
    EXTERN _pxCurrentTCB
    EXTERN _usCriticalNesting

    ; /* Macro used to declutter calls, depends on the selected code model. */
      /*----------------------------------------------------------------------------- */
    #ਜੇ __CODE_MODEL__ == __CODE_MODEL_FAR__
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RCALL( X )    CALL F: X
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RCALL( X )    CALL X
    #ਜੇ_ਅੰਤ


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
ਪੋਰਟ_SAVE_CONTEXT MACRO
    ਧੱਕੋ_2 AX; /* Save AX Register to stack. */
    ਧੱਕੋ_2 HL
    #ਜੇ  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        ਧੱਕੋ_2 AX
    #ਨਹੀਂਤਾਂ
        MOV A, CS; /* Save CS register. */
        ਧੱਕੋ_2 AX
    #ਜੇ_ਅੰਤ
    ਧੱਕੋ_2 DE;                     /* Save the remaining general purpose registers. */
    ਧੱਕੋ_2 BC
    MOVW AX, _usCriticalNesting; /* Save the _usCriticalNesting value. */
    ਧੱਕੋ_2 AX
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
ਪੋਰਟ_RESTORE_CONTEXT MACRO
    MOVW AX, _pxCurrentTCB; /* Restore the Task stack pointer. */
    MOVW HL, AX
    MOVW AX, [ HL ]
    MOVW SP, AX
    ਕੱਢੋ_2 AX; /* Restore _usCriticalNesting value. */
    MOVW _usCriticalNesting, AX
    ਕੱਢੋ_2 BC; /* Restore the necessary general purpose registers. */
    ਕੱਢੋ_2 DE
    #ਜੇ __CODE_MODEL__ == __CODE_MODEL_FAR__
        ਕੱਢੋ_2 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #ਨਹੀਂਤਾਂ
        ਕੱਢੋ_2 AX
        MOV CS, A; /* Restore CS register. */
    #ਜੇ_ਅੰਤ
    ਕੱਢੋ_2 HL;        /* Restore general purpose register HL. */
    ਕੱਢੋ_2 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#ਜੇ_ਅੰਤ /* __IAR_SYSTEMS_ASM__ */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
