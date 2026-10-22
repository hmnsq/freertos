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

#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

#अगर_घोषित __IAR_SYSTEMS_ICC__

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
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

    #अगर __DATA_MODEL__ == __DATA_MODEL_FAR__ && __CODE_MODEL__ == __CODE_MODEL_NEAR__
        #warning This port has not been tested with your selected memory model combination. If a far तथ्य_2 model is required it is recommended to also use a far code model.
    #पूर्ण_अगर

    #अगर __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This port has not been tested with your selected memory model combination. If a far code model is required it is recommended to also use a far तथ्य_2 model.
    #पूर्ण_अगर

/* Type definitions. */

    #घोषणा portCHAR          अक्षर
    #घोषणा portFLOAT         भग्न
    #घोषणा portDOUBLE        द्विगुन
    #घोषणा portLONG          दीर्घ
    #घोषणा portSHORT         लघु
    #घोषणा port_ढेर_TYPE    uint16_t
    #घोषणा portBASE_TYPE     लघु

    प्रकार port_ढेर_TYPE   ढेर_Type_t;
    प्रकार लघु            BaseType_t;
    प्रकार अचिन्हित लघु   UBaseType_t;


    #अगर __DATA_MODEL__ == __DATA_MODEL_FAR__
        #घोषणा port_POINTER_आकार_TYPE    uint32_t
    #अन्यथा
        #घोषणा port_POINTER_आकार_TYPE    uint16_t
    #पूर्ण_अगर


    #अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        प्रकार अचिन्हित पूर्णांक   TickType_t;
        #घोषणा portMAX_DELAY    ( TickType_t ) 0xffff
    #या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
        प्रकार uint32_t       TickType_t;
        #घोषणा portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #अन्यथा
        #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
    #पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
    #घोषणा portDISABLE_INTERRUPTS()    __asm( "DI" )
    #घोषणा portENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
    #घोषणा portNO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

    #घोषणा portENTER_CRITICAL()                                                  \
    {                                                                             \
        बाह्य अस्थिर uint16_t usCriticalNesting;                               \
                                                                                  \
        portDISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

    #घोषणा portEXIT_CRITICAL()                                                   \
    {                                                                             \
        बाह्य अस्थिर uint16_t usCriticalNesting;                               \
                                                                                  \
        अगर( usCriticalNesting > portNO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            अगर( usCriticalNesting == portNO_CRITICAL_SECTION_NESTING )            \
            {                                                                     \
                portENABLE_INTERRUPTS();                                          \
            }                                                                     \
        }                                                                         \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
    #घोषणा portNOP()                                         __asm( "NOP" )
    #घोषणा portYIELD()                                       __asm( "BRK" )
    #अगर_अघोषित configREQUIRE_ASM_ISR_WRAPPER
        #घोषणा configREQUIRE_ASM_ISR_WRAPPER    1
    #पूर्ण_अगर
    #अगर( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #घोषणा portYIELD_FROM_ISR( xHigherPriorityTaskWoken )    करो { अगर( xHigherPriorityTaskWoken != pdFALSE ) vTaskSwitchContext(); } जबतक( 0 )
    #अन्यथा
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #घोषणा portYIELD_FROM_ISR( xHigherPriorityTaskWoken )    करो { अगर( xHigherPriorityTaskWoken != pdFALSE ) portYIELD(); } जबतक( 0 )
    #पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #घोषणा portBYTE_ALIGNMENT    2
    #घोषणा port_ढेर_GROWTH      ( -1 )
    #घोषणा portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
    #घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* __IAR_SYSTEMS_ICC__ */

; /*----------------------------------------------------------------------------- */
  /* The macros below are processed for asm sources which include portmacro.h. */
  /*----------------------------------------------------------------------------- */
#अगर_घोषित __IAR_SYSTEMS_ASM__

    ; /* Functions and variables used by this file. */
      /*----------------------------------------------------------------------------- */
    EXTERN _pxCurrentTCB
    EXTERN _usCriticalNesting

    ; /* Macro used to declutter calls, depends on the selected code model. */
      /*----------------------------------------------------------------------------- */
    #अगर __CODE_MODEL__ == __CODE_MODEL_FAR__
        #घोषणा RCALL( X )    CALL F: X
    #अन्यथा
        #घोषणा RCALL( X )    CALL X
    #पूर्ण_अगर


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
portSAVE_CONTEXT MACRO
    धकेलो_2 AX; /* Save AX Register to stack. */
    धकेलो_2 HL
    #अगर  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        धकेलो_2 AX
    #अन्यथा
        MOV A, CS; /* Save CS register. */
        धकेलो_2 AX
    #पूर्ण_अगर
    धकेलो_2 DE;                     /* Save the remaining general purpose registers. */
    धकेलो_2 BC
    MOVW AX, _usCriticalNesting; /* Save the _usCriticalNesting value. */
    धकेलो_2 AX
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
portRESTORE_CONTEXT MACRO
    MOVW AX, _pxCurrentTCB; /* Restore the Task stack pointer. */
    MOVW HL, AX
    MOVW AX, [ HL ]
    MOVW SP, AX
    निकालो_2 AX; /* Restore _usCriticalNesting value. */
    MOVW _usCriticalNesting, AX
    निकालो_2 BC; /* Restore the necessary general purpose registers. */
    निकालो_2 DE
    #अगर __CODE_MODEL__ == __CODE_MODEL_FAR__
        निकालो_2 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #अन्यथा
        निकालो_2 AX
        MOV CS, A; /* Restore CS register. */
    #पूर्ण_अगर
    निकालो_2 HL;        /* Restore general purpose register HL. */
    निकालो_2 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#पूर्ण_अगर /* __IAR_SYSTEMS_ASM__ */

#पूर्ण_अगर /* PORTMACRO_H */
