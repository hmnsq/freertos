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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

#اگر_تعریف_شدہ __IAR_SYSTEMS_ICC__

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
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

    #اگر __DATA_MODEL__ == __DATA_MODEL_FAR__ && __CODE_MODEL__ == __CODE_MODEL_NEAR__
        #warning This پورٹ has not been tested with your selected حافظہ model combination. If a far ڈیٹا_2 model is required it is recommended مقصد also use a far رمز model.
    #اگر_ختم

    #اگر __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This پورٹ has not been tested with your selected حافظہ model combination. If a far رمز model is required it is recommended مقصد also use a far ڈیٹا_2 model.
    #اگر_ختم

/* Type definitions. */

    #تعریف_کرو پورٹ_CHAR          حرف
    #تعریف_کرو پورٹ_FLOAT         اعشاری
    #تعریف_کرو پورٹ_DOUBLE        دوہرا
    #تعریف_کرو پورٹ_LONG          طویل
    #تعریف_کرو پورٹ_SHORT         مختصر
    #تعریف_کرو پورٹ_ڈھیر_TYPE    uint16_t
    #تعریف_کرو پورٹ_بنیاد_TYPE     مختصر

    قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
    قسمتعریف مختصر            بنیاد_Type_t;
    قسمتعریف غیرعلامتی مختصر   UBaseType_t;


    #اگر __DATA_MODEL__ == __DATA_MODEL_FAR__
        #تعریف_کرو پورٹ_اشارہ_گر_سائز_TYPE    uint32_t
    #ورنہ
        #تعریف_کرو پورٹ_اشارہ_گر_سائز_TYPE    uint16_t
    #اگر_ختم


    #اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
        قسمتعریف غیرعلامتی صحیح   TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
    #وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
        قسمتعریف uint32_t       TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #ورنہ
        #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
    #اگر_ختم
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    __asm( "DI" )
    #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
    #تعریف_کرو پورٹ_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

    #تعریف_کرو پورٹ_ENTER_CRITICAL()                                                  \
    {                                                                             \
        خارجی متلون uint16_t usCriticalNesting;                               \
                                                                                  \
        پورٹ_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

    #تعریف_کرو پورٹ_EXIT_CRITICAL()                                                   \
    {                                                                             \
        خارجی متلون uint16_t usCriticalNesting;                               \
                                                                                  \
        اگر( usCriticalNesting > پورٹ_NO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            اگر( usCriticalNesting == پورٹ_NO_CRITICAL_SECTION_NESTING )            \
            {                                                                     \
                پورٹ_ENABLE_INTERRUPTS();                                          \
            }                                                                     \
        }                                                                         \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
    #تعریف_کرو پورٹ_NOP()                                         __asm( "NOP" )
    #تعریف_کرو پورٹ_YIELD()                                       __asm( "BRK" )
    #اگر_غیر_تعریف_شدہ configREQUIRE_ASM_ISR_WRAPPER
        #تعریف_کرو configREQUIRE_ASM_ISR_WRAPPER    1
    #اگر_ختم
    #اگر( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #تعریف_کرو پورٹ_YIELD_FROM_ISR( x_Higher_ترجیح_Task_Woken )    کرو { اگر( x_Higher_ترجیح_Task_Woken != pdFALSE ) vTaskSwitchContext(); } جب( 0 )
    #ورنہ
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #تعریف_کرو پورٹ_YIELD_FROM_ISR( x_Higher_ترجیح_Task_Woken )    کرو { اگر( x_Higher_ترجیح_Task_Woken != pdFALSE ) پورٹ_YIELD(); } جب( 0 )
    #اگر_ختم
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    2
    #تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
    #تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
    #تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* __IAR_SYSTEMS_ICC__ */

; /*----------------------------------------------------------------------------- */
  /* The macros below are processed for asm sources which include portmacro.h. */
  /*----------------------------------------------------------------------------- */
#اگر_تعریف_شدہ __IAR_SYSTEMS_ASM__

    ; /* Functions and variables used by this file. */
      /*----------------------------------------------------------------------------- */
    EXTERN _pxCurrentTCB
    EXTERN _usCriticalNesting

    ; /* Macro used to declutter calls, depends on the selected code model. */
      /*----------------------------------------------------------------------------- */
    #اگر __CODE_MODEL__ == __CODE_MODEL_FAR__
        #تعریف_کرو RCALL( X )    CALL F: X
    #ورنہ
        #تعریف_کرو RCALL( X )    CALL X
    #اگر_ختم


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
پورٹ_SAVE_CONTEXT MACRO
    ڈالو_2 AX; /* Save AX Register to stack. */
    ڈالو_2 HL
    #اگر  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        ڈالو_2 AX
    #ورنہ
        MOV A, CS; /* Save CS register. */
        ڈالو_2 AX
    #اگر_ختم
    ڈالو_2 DE;                     /* Save the remaining general purpose registers. */
    ڈالو_2 BC
    MOVW AX, _usCriticalNesting; /* Save the _usCriticalNesting value. */
    ڈالو_2 AX
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
پورٹ_RESTORE_CONTEXT MACRO
    MOVW AX, _pxCurrentTCB; /* Restore the Task stack pointer. */
    MOVW HL, AX
    MOVW AX, [ HL ]
    MOVW SP, AX
    نکالو_2 AX; /* Restore _usCriticalNesting value. */
    MOVW _usCriticalNesting, AX
    نکالو_2 BC; /* Restore the necessary general purpose registers. */
    نکالو_2 DE
    #اگر __CODE_MODEL__ == __CODE_MODEL_FAR__
        نکالو_2 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #ورنہ
        نکالو_2 AX
        MOV CS, A; /* Restore CS register. */
    #اگر_ختم
    نکالو_2 HL;        /* Restore general purpose register HL. */
    نکالو_2 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#اگر_ختم /* __IAR_SYSTEMS_ASM__ */

#اگر_ختم /* PORTMACRO_H */
