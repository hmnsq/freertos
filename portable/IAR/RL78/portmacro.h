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
    बाह्य "C" {
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

    #यदि __DATA_MODEL__ == __DATA_MODEL_FAR__ && __CODE_MODEL__ == __CODE_MODEL_NEAR__
        #warning This port has not been tested with your selected memory model combination. If a far data model is required it is recommended to also use a far code model.
    #endif

    #यदि __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This port has not been tested with your selected memory model combination. If a far code model is required it is recommended to also use a far data model.
    #endif

/* Type definitions. */

    #define portCHAR          वर्ण
    #define portFLOAT         भिन्न
    #define portDOUBLE        द्विगुण
    #define portLONG          दीर्घ
    #define portSHORT         लघु
    #define port_ढेर_TYPE    uint16_t
    #define portBASE_TYPE     लघु

    प्रकारनिर्देश port_ढेर_TYPE   ढेर_Type_t;
    प्रकारनिर्देश लघु            BaseType_t;
    प्रकारनिर्देश अचिन्हित लघु   UBaseType_t;


    #यदि __DATA_MODEL__ == __DATA_MODEL_FAR__
        #define portPOINTER_SIZE_TYPE    uint32_t
    #अन्यथा
        #define portPOINTER_SIZE_TYPE    uint16_t
    #endif


    #यदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        प्रकारनिर्देश अचिन्हित पूर्णाङ्क   TickType_t;
        #define portMAX_DELAY    ( TickType_t ) 0xffff
    #नोचेद्यदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
        प्रकारनिर्देश uint32_t       TickType_t;
        #define portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #अन्यथा
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
        बाह्य चञ्चल uint16_t usCriticalNesting;                               \
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
        बाह्य चञ्चल uint16_t usCriticalNesting;                               \
                                                                                  \
        यदि( usCriticalNesting > portNO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            यदि( usCriticalNesting == portNO_CRITICAL_SECTION_NESTING )            \
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
    #यदि( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #define portYIELD_FROM_ISR( xHigherPriorityTaskWoken )    कुरु { यदि( xHigherPriorityTaskWoken != pdFALSE ) vTaskSwitchContext(); } यावत्( 0 )
    #अन्यथा
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #define portYIELD_FROM_ISR( xHigherPriorityTaskWoken )    कुरु { यदि( xHigherPriorityTaskWoken != pdFALSE ) portYIELD(); } यावत्( 0 )
    #endif
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #define portBYTE_ALIGNMENT    2
    #define port_ढेर_GROWTH      ( -1 )
    #define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
    #define portTASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

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
    #यदि __CODE_MODEL__ == __CODE_MODEL_FAR__
        #define RCALL( X )    CALL F: X
    #अन्यथा
        #define RCALL( X )    CALL X
    #endif


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
portSAVE_CONTEXT MACRO
    धकेलो_2 AX; /* Save AX Register to stack. */
    धकेलो_2 HL
    #यदि  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        धकेलो_2 AX
    #अन्यथा
        MOV A, CS; /* Save CS register. */
        धकेलो_2 AX
    #endif
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
    #यदि __CODE_MODEL__ == __CODE_MODEL_FAR__
        निकालो_2 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #अन्यथा
        निकालो_2 AX
        MOV CS, A; /* Restore CS register. */
    #endif
    निकालो_2 HL;        /* Restore general purpose register HL. */
    निकालो_2 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#endif /* __IAR_SYSTEMS_ASM__ */

#endif /* PORTMACRO_H */
