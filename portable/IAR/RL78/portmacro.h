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

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

#यदि_परिभाषितम् __IAR_SYSTEMS_ICC__

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
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

    #यदि __DATA_MODEL__ == __DATA_MODEL_FAR__ && __CODE_MODEL__ == __CODE_MODEL_NEAR__
        #warning This पत्तनम् has not been tested with your selected स्मृतिः model combination. If a far दत्त_2 model is required it is recommended गन्तव्यम् also use a far संहिता model.
    #यदि_अन्तः

    #यदि __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This पत्तनम् has not been tested with your selected स्मृतिः model combination. If a far संहिता model is required it is recommended गन्तव्यम् also use a far दत्त_2 model.
    #यदि_अन्तः

/* Type definitions. */

    #परिभाषय पत्तनम्_CHAR          वर्ण
    #परिभाषय पत्तनम्_FLOAT         भिन्न
    #परिभाषय पत्तनम्_DOUBLE        द्विगुण
    #परिभाषय पत्तनम्_LONG          दीर्घ
    #परिभाषय पत्तनम्_SHORT         ह्रस्व
    #परिभाषय पत्तनम्_राशिः_TYPE    uint16_t
    #परिभाषय पत्तनम्_आधारः_TYPE     ह्रस्व

    प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
    प्रकारनिर्देश ह्रस्व            आधारः_Type_t;
    प्रकारनिर्देश अचिह्नित ह्रस्व   UBaseType_t;


    #यदि __DATA_MODEL__ == __DATA_MODEL_FAR__
        #परिभाषय पत्तनम्_POINTER_आकार_TYPE    uint32_t
    #अन्यथा
        #परिभाषय पत्तनम्_POINTER_आकार_TYPE    uint16_t
    #यदि_अन्तः


    #यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
        प्रकारनिर्देश अचिह्नित पूर्णाङ्क   TickType_t;
        #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffff
    #नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
        प्रकारनिर्देश uint32_t       TickType_t;
        #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #अन्यथा
        #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
    #यदि_अन्तः
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
    #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    __asm( "DI" )
    #परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
    #परिभाषय पत्तनम्_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

    #परिभाषय पत्तनम्_ENTER_CRITICAL()                                                  \
    {                                                                             \
        बाह्य चञ्चल uint16_t usCriticalNesting;                               \
                                                                                  \
        पत्तनम्_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

    #परिभाषय पत्तनम्_EXIT_CRITICAL()                                                   \
    {                                                                             \
        बाह्य चञ्चल uint16_t usCriticalNesting;                               \
                                                                                  \
        यदि( usCriticalNesting > पत्तनम्_NO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            यदि( usCriticalNesting == पत्तनम्_NO_CRITICAL_SECTION_NESTING )            \
            {                                                                     \
                पत्तनम्_ENABLE_INTERRUPTS();                                          \
            }                                                                     \
        }                                                                         \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
    #परिभाषय पत्तनम्_NOP()                                         __asm( "NOP" )
    #परिभाषय पत्तनम्_YIELD()                                       __asm( "BRK" )
    #यदि_अपरिभाषितम् configREQUIRE_ASM_ISR_WRAPPER
        #परिभाषय configREQUIRE_ASM_ISR_WRAPPER    1
    #यदि_अन्तः
    #यदि( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #परिभाषय पत्तनम्_YIELD_FROM_ISR( x_Higher_प्राथमिकता_Task_Woken )    कुरु { यदि( x_Higher_प्राथमिकता_Task_Woken != pdFALSE ) vTaskSwitchContext(); } यावत्( 0 )
    #अन्यथा
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #परिभाषय पत्तनम्_YIELD_FROM_ISR( x_Higher_प्राथमिकता_Task_Woken )    कुरु { यदि( x_Higher_प्राथमिकता_Task_Woken != pdFALSE ) पत्तनम्_YIELD(); } यावत्( 0 )
    #यदि_अन्तः
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #परिभाषय पत्तनम्_BYTE_ALIGNMENT    2
    #परिभाषय पत्तनम्_राशिः_GROWTH      ( -1 )
    #परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
    #परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* __IAR_SYSTEMS_ICC__ */

; /*----------------------------------------------------------------------------- */
  /* The macros below are processed for asm sources which include portmacro.h. */
  /*----------------------------------------------------------------------------- */
#यदि_परिभाषितम् __IAR_SYSTEMS_ASM__

    ; /* Functions and variables used by this file. */
      /*----------------------------------------------------------------------------- */
    EXTERN _pxCurrentTCB
    EXTERN _usCriticalNesting

    ; /* Macro used to declutter calls, depends on the selected code model. */
      /*----------------------------------------------------------------------------- */
    #यदि __CODE_MODEL__ == __CODE_MODEL_FAR__
        #परिभाषय RCALL( X )    CALL F: X
    #अन्यथा
        #परिभाषय RCALL( X )    CALL X
    #यदि_अन्तः


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
पत्तनम्_SAVE_CONTEXT MACRO
    प्रक्षिप_2 AX; /* Save AX Register to stack. */
    प्रक्षिप_2 HL
    #यदि  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        प्रक्षिप_2 AX
    #अन्यथा
        MOV A, CS; /* Save CS register. */
        प्रक्षिप_2 AX
    #यदि_अन्तः
    प्रक्षिप_2 DE;                     /* Save the remaining general purpose registers. */
    प्रक्षिप_2 BC
    MOVW AX, _usCriticalNesting; /* Save the _usCriticalNesting value. */
    प्रक्षिप_2 AX
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
पत्तनम्_RESTORE_CONTEXT MACRO
    MOVW AX, _pxCurrentTCB; /* Restore the Task stack pointer. */
    MOVW HL, AX
    MOVW AX, [ HL ]
    MOVW SP, AX
    निष्कासय_2 AX; /* Restore _usCriticalNesting value. */
    MOVW _usCriticalNesting, AX
    निष्कासय_2 BC; /* Restore the necessary general purpose registers. */
    निष्कासय_2 DE
    #यदि __CODE_MODEL__ == __CODE_MODEL_FAR__
        निष्कासय_2 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #अन्यथा
        निष्कासय_2 AX
        MOV CS, A; /* Restore CS register. */
    #यदि_अन्तः
    निष्कासय_2 HL;        /* Restore general purpose register HL. */
    निष्कासय_2 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#यदि_अन्तः /* __IAR_SYSTEMS_ASM__ */

#यदि_अन्तः /* PORTMACRO_H */
