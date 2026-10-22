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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

#నిర్వచితమైతే __IAR_SYSTEMS_ICC__

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
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

    #ఒకవేళ __DATA_MODEL__ == __DATA_MODEL_FAR__ && __CODE_MODEL__ == __CODE_MODEL_NEAR__
        #warning This పోర్టు has not been tested with your selected జ్ఞాపకం model combination. If a far దత్తాంశం_2 model is required it is recommended గమ్యం also use a far సంకేతం_2 model.
    #అయితే_ముగింపు

    #ఒకవేళ __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This పోర్టు has not been tested with your selected జ్ఞాపకం model combination. If a far సంకేతం_2 model is required it is recommended గమ్యం also use a far దత్తాంశం_2 model.
    #అయితే_ముగింపు

/* Type definitions. */

    #నిర్వచించు పోర్టు_CHAR          అక్షరం
    #నిర్వచించు పోర్టు_FLOAT         దశాంశం
    #నిర్వచించు పోర్టు_DOUBLE        ద్విగుణ
    #నిర్వచించు పోర్టు_LONG          దీర్ఘ
    #నిర్వచించు పోర్టు_SHORT         పొట్టి
    #నిర్వచించు పోర్టు_దొంతర_TYPE    uint16_t
    #నిర్వచించు పోర్టు_పునాది_TYPE     పొట్టి

    రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
    రకనిర్వచనం పొట్టి            పునాది_Type_t;
    రకనిర్వచనం గుర్తులేని పొట్టి   UBaseType_t;


    #ఒకవేళ __DATA_MODEL__ == __DATA_MODEL_FAR__
        #నిర్వచించు పోర్టు_సూచిక_కొలత_TYPE    uint32_t
    #లేకపోతే
        #నిర్వచించు పోర్టు_సూచిక_కొలత_TYPE    uint16_t
    #అయితే_ముగింపు


    #ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
        రకనిర్వచనం గుర్తులేని పూర్ణాంకం   TickType_t;
        #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffff
    #లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
        రకనిర్వచనం uint32_t       TickType_t;
        #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #లేకపోతే
        #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
    #అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
    #నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    __asm( "DI" )
    #నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
    #నిర్వచించు పోర్టు_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

    #నిర్వచించు పోర్టు_ENTER_CRITICAL()                                                  \
    {                                                                             \
        బాహ్య అస్థిర uint16_t usCriticalNesting;                               \
                                                                                  \
        పోర్టు_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

    #నిర్వచించు పోర్టు_EXIT_CRITICAL()                                                   \
    {                                                                             \
        బాహ్య అస్థిర uint16_t usCriticalNesting;                               \
                                                                                  \
        ఒకవేళ( usCriticalNesting > పోర్టు_NO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            ఒకవేళ( usCriticalNesting == పోర్టు_NO_CRITICAL_SECTION_NESTING )            \
            {                                                                     \
                పోర్టు_ENABLE_INTERRUPTS();                                          \
            }                                                                     \
        }                                                                         \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
    #నిర్వచించు పోర్టు_NOP()                                         __asm( "NOP" )
    #నిర్వచించు పోర్టు_YIELD()                                       __asm( "BRK" )
    #నిర్వచితం_కాకపోతే configREQUIRE_ASM_ISR_WRAPPER
        #నిర్వచించు configREQUIRE_ASM_ISR_WRAPPER    1
    #అయితే_ముగింపు
    #ఒకవేళ( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #నిర్వచించు పోర్టు_YIELD_FROM_ISR( x_Higher_ప్రాధాన్యత_Task_Woken )    చేయి { ఒకవేళ( x_Higher_ప్రాధాన్యత_Task_Woken != pdFALSE ) vTaskSwitchContext(); } అయితే( 0 )
    #లేకపోతే
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #నిర్వచించు పోర్టు_YIELD_FROM_ISR( x_Higher_ప్రాధాన్యత_Task_Woken )    చేయి { ఒకవేళ( x_Higher_ప్రాధాన్యత_Task_Woken != pdFALSE ) పోర్టు_YIELD(); } అయితే( 0 )
    #అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #నిర్వచించు పోర్టు_BYTE_ALIGNMENT    2
    #నిర్వచించు పోర్టు_దొంతర_GROWTH      ( -1 )
    #నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
    #నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* __IAR_SYSTEMS_ICC__ */

; /*----------------------------------------------------------------------------- */
  /* The macros below are processed for asm sources which include portmacro.h. */
  /*----------------------------------------------------------------------------- */
#నిర్వచితమైతే __IAR_SYSTEMS_ASM__

    ; /* Functions and variables used by this file. */
      /*----------------------------------------------------------------------------- */
    EXTERN _pxCurrentTCB
    EXTERN _usCriticalNesting

    ; /* Macro used to declutter calls, depends on the selected code model. */
      /*----------------------------------------------------------------------------- */
    #ఒకవేళ __CODE_MODEL__ == __CODE_MODEL_FAR__
        #నిర్వచించు RCALL( X )    CALL F: X
    #లేకపోతే
        #నిర్వచించు RCALL( X )    CALL X
    #అయితే_ముగింపు


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
పోర్టు_SAVE_CONTEXT MACRO
    నెట్టు_2 AX; /* Save AX Register to stack. */
    నెట్టు_2 HL
    #ఒకవేళ  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        నెట్టు_2 AX
    #లేకపోతే
        MOV A, CS; /* Save CS register. */
        నెట్టు_2 AX
    #అయితే_ముగింపు
    నెట్టు_2 DE;                     /* Save the remaining general purpose registers. */
    నెట్టు_2 BC
    MOVW AX, _usCriticalNesting; /* Save the _usCriticalNesting value. */
    నెట్టు_2 AX
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
పోర్టు_RESTORE_CONTEXT MACRO
    MOVW AX, _pxCurrentTCB; /* Restore the Task stack pointer. */
    MOVW HL, AX
    MOVW AX, [ HL ]
    MOVW SP, AX
    తీయి_2 AX; /* Restore _usCriticalNesting value. */
    MOVW _usCriticalNesting, AX
    తీయి_2 BC; /* Restore the necessary general purpose registers. */
    తీయి_2 DE
    #ఒకవేళ __CODE_MODEL__ == __CODE_MODEL_FAR__
        తీయి_2 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #లేకపోతే
        తీయి_2 AX
        MOV CS, A; /* Restore CS register. */
    #అయితే_ముగింపు
    తీయి_2 HL;        /* Restore general purpose register HL. */
    తీయి_2 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#అయితే_ముగింపు /* __IAR_SYSTEMS_ASM__ */

#అయితే_ముగింపు /* PORTMACRO_H */
