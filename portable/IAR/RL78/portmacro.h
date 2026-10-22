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

#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __IAR_SYSTEMS_ICC__

/* *INDENT-OFF* */
#ifdef __cplusplus
    ବାହ୍ୟ "C" {
#endif
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

    #ଯଦି __DATA_MODEL__ == __DATA_MODEL_FAR__ && __CODE_MODEL__ == __CODE_MODEL_NEAR__
        #warning This port has not been tested with your selected memory model combination. If a far data model is required it is recommended to also use a far code model.
    #endif

    #ଯଦି __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This port has not been tested with your selected memory model combination. If a far code model is required it is recommended to also use a far data model.
    #endif

/* Type definitions. */

    #define portCHAR          ଅକ୍ଷର
    #define portFLOAT         ଦଶମିକ
    #define portDOUBLE        ଦ୍ୱିଗୁଣ
    #define portLONG          long
    #define portSHORT         short
    #define port_ଗଦା_TYPE    uint16_t
    #define portBASE_TYPE     short

    ପ୍ରକାରବ୍ୟାଖ୍ୟା port_ଗଦା_TYPE   ଗଦା_Type_t;
    ପ୍ରକାରବ୍ୟାଖ୍ୟା short            BaseType_t;
    ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned short   UBaseType_t;


    #ଯଦି __DATA_MODEL__ == __DATA_MODEL_FAR__
        #define portPOINTER_SIZE_TYPE    uint32_t
    #ଅନ୍ୟଥା
        #define portPOINTER_SIZE_TYPE    uint16_t
    #endif


    #ଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା   TickType_t;
        #define portMAX_DELAY    ( TickType_t ) 0xffff
    #ନଚେତଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
        ପ୍ରକାରବ୍ୟାଖ୍ୟା uint32_t       TickType_t;
        #define portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #ଅନ୍ୟଥା
        #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
    #endif
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
    #define portDISABLE_INTERRUPTS()    __asm( "DI" )
    #define portENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
    #define portNO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

    #define portENTER_CRITICAL()                                                  \
    {                                                                             \
        ବାହ୍ୟ ଅସ୍ଥିର uint16_t usCriticalNesting;                               \
                                                                                  \
        portDISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

    #define portEXIT_CRITICAL()                                                   \
    {                                                                             \
        ବାହ୍ୟ ଅସ୍ଥିର uint16_t usCriticalNesting;                               \
                                                                                  \
        ଯଦି( usCriticalNesting > portNO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            ଯଦି( usCriticalNesting == portNO_CRITICAL_SECTION_NESTING )            \
            {                                                                     \
                portENABLE_INTERRUPTS();                                          \
            }                                                                     \
        }                                                                         \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
    #define portNOP()                                         __asm( "NOP" )
    #define portYIELD()                                       __asm( "BRK" )
    #ifndef configREQUIRE_ASM_ISR_WRAPPER
        #define configREQUIRE_ASM_ISR_WRAPPER    1
    #endif
    #ଯଦି( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #define portYIELD_FROM_ISR( xHigherPriorityTaskWoken )    କର { ଯଦି( xHigherPriorityTaskWoken != pdFALSE ) vTaskSwitchContext(); } ଯେତେବେଳେ( 0 )
    #ଅନ୍ୟଥା
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #define portYIELD_FROM_ISR( xHigherPriorityTaskWoken )    କର { ଯଦି( xHigherPriorityTaskWoken != pdFALSE ) portYIELD(); } ଯେତେବେଳେ( 0 )
    #endif
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #define portBYTE_ALIGNMENT    2
    #define port_ଗଦା_GROWTH      ( -1 )
    #define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )
    #define portTASK_FUNCTION( vFunction, pvParameters )          ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* __IAR_SYSTEMS_ICC__ */

; /*----------------------------------------------------------------------------- */
  /* The macros below are processed for asm sources which include portmacro.h. */
  /*----------------------------------------------------------------------------- */
#ifdef __IAR_SYSTEMS_ASM__

    ; /* Functions and variables used by this file. */
      /*----------------------------------------------------------------------------- */
    EXTERN _pxCurrentTCB
    EXTERN _usCriticalNesting

    ; /* Macro used to declutter calls, depends on the selected code model. */
      /*----------------------------------------------------------------------------- */
    #ଯଦି __CODE_MODEL__ == __CODE_MODEL_FAR__
        #define RCALL( X )    CALL F: X
    #ଅନ୍ୟଥା
        #define RCALL( X )    CALL X
    #endif


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
portSAVE_CONTEXT MACRO
    ଠେଲ_2 AX; /* Save AX Register to stack. */
    ଠେଲ_2 HL
    #ଯଦି  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        ଠେଲ_2 AX
    #ଅନ୍ୟଥା
        MOV A, CS; /* Save CS register. */
        ଠେଲ_2 AX
    #endif
    ଠେଲ_2 DE;                     /* Save the remaining general purpose registers. */
    ଠେଲ_2 BC
    MOVW AX, _usCriticalNesting; /* Save the _usCriticalNesting value. */
    ଠେଲ_2 AX
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
    କାଢ଼_2 AX; /* Restore _usCriticalNesting value. */
    MOVW _usCriticalNesting, AX
    କାଢ଼_2 BC; /* Restore the necessary general purpose registers. */
    କାଢ଼_2 DE
    #ଯଦି __CODE_MODEL__ == __CODE_MODEL_FAR__
        କାଢ଼_2 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #ଅନ୍ୟଥା
        କାଢ଼_2 AX
        MOV CS, A; /* Restore CS register. */
    #endif
    କାଢ଼_2 HL;        /* Restore general purpose register HL. */
    କାଢ଼_2 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#endif /* __IAR_SYSTEMS_ASM__ */

#endif /* PORTMACRO_H */
