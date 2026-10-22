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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

#که_تعریف_شوی __IAR_SYSTEMS_ICC__

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
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

    #إذا __DATA_MODEL__ == __DATA_MODEL_FAR__ && __CODE_MODEL__ == __CODE_MODEL_NEAR__
        #warning This پورټ has not been tested with your selected حافظه model combination. If a far معلومات_2 model is required it is recommended منزل also use a far کوډ model.
    #د_که_پای

    #إذا __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This پورټ has not been tested with your selected حافظه model combination. If a far کوډ model is required it is recommended منزل also use a far معلومات_2 model.
    #د_که_پای

/* Type definitions. */

    #تعریف_کړه پورټ_CHAR          حرف
    #تعریف_کړه پورټ_FLOAT         عائم
    #تعریف_کړه پورټ_DOUBLE        مزدوج
    #تعریف_کړه پورټ_LONG          اوږد
    #تعریف_کړه پورټ_SHORT         لنډ
    #تعریف_کړه پورټ_ډېری_TYPE    uint16_t
    #تعریف_کړه پورټ_بنسټ_TYPE     لنډ

    تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
    تعريفنوع لنډ            بنسټ_Type_t;
    تعريفنوع بینښه لنډ   UBaseType_t;


    #إذا __DATA_MODEL__ == __DATA_MODEL_FAR__
        #تعریف_کړه پورټ_اشاره_ګر_اندازه_TYPE    uint32_t
    #وإلا
        #تعریف_کړه پورټ_اشاره_ګر_اندازه_TYPE    uint16_t
    #د_که_پای


    #إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
        تعريفنوع بینښه صحيح   TickType_t;
        #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
        تعريفنوع uint32_t       TickType_t;
        #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #وإلا
        #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
    #د_که_پای
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()    __asm( "DI" )
    #تعریف_کړه پورټ_ENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
    #تعریف_کړه پورټ_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

    #تعریف_کړه پورټ_ENTER_CRITICAL()                                                  \
    {                                                                             \
        خارجي متطاير uint16_t usCriticalNesting;                               \
                                                                                  \
        پورټ_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

    #تعریف_کړه پورټ_EXIT_CRITICAL()                                                   \
    {                                                                             \
        خارجي متطاير uint16_t usCriticalNesting;                               \
                                                                                  \
        إذا( usCriticalNesting > پورټ_NO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            إذا( usCriticalNesting == پورټ_NO_CRITICAL_SECTION_NESTING )            \
            {                                                                     \
                پورټ_ENABLE_INTERRUPTS();                                          \
            }                                                                     \
        }                                                                         \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
    #تعریف_کړه پورټ_NOP()                                         __asm( "NOP" )
    #تعریف_کړه پورټ_YIELD()                                       __asm( "BRK" )
    #که_نه_تعریف_شوی configREQUIRE_ASM_ISR_WRAPPER
        #تعریف_کړه configREQUIRE_ASM_ISR_WRAPPER    1
    #د_که_پای
    #إذا( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #تعریف_کړه پورټ_YIELD_FROM_ISR( x_Higher_لومړیتوب_Task_Woken )    افعل { إذا( x_Higher_لومړیتوب_Task_Woken != pdFALSE ) vTaskSwitchContext(); } طالما( 0 )
    #وإلا
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #تعریف_کړه پورټ_YIELD_FROM_ISR( x_Higher_لومړیتوب_Task_Woken )    افعل { إذا( x_Higher_لومړیتوب_Task_Woken != pdFALSE ) پورټ_YIELD(); } طالما( 0 )
    #د_که_پای
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #تعریف_کړه پورټ_BYTE_ALIGNMENT    2
    #تعریف_کړه پورټ_ډېری_GROWTH      ( -1 )
    #تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* __IAR_SYSTEMS_ICC__ */

; /*----------------------------------------------------------------------------- */
  /* The macros below are processed for asm sources which include portmacro.h. */
  /*----------------------------------------------------------------------------- */
#که_تعریف_شوی __IAR_SYSTEMS_ASM__

    ; /* Functions and variables used by this file. */
      /*----------------------------------------------------------------------------- */
    EXTERN _pxCurrentTCB
    EXTERN _usCriticalNesting

    ; /* Macro used to declutter calls, depends on the selected code model. */
      /*----------------------------------------------------------------------------- */
    #إذا __CODE_MODEL__ == __CODE_MODEL_FAR__
        #تعریف_کړه RCALL( X )    CALL F: X
    #وإلا
        #تعریف_کړه RCALL( X )    CALL X
    #د_که_پای


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
پورټ_SAVE_CONTEXT MACRO
    ټېل_2 AX; /* Save AX Register to stack. */
    ټېل_2 HL
    #إذا  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        ټېل_2 AX
    #وإلا
        MOV A, CS; /* Save CS register. */
        ټېل_2 AX
    #د_که_پای
    ټېل_2 DE;                     /* Save the remaining general purpose registers. */
    ټېل_2 BC
    MOVW AX, _usCriticalNesting; /* Save the _usCriticalNesting value. */
    ټېل_2 AX
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
پورټ_RESTORE_CONTEXT MACRO
    MOVW AX, _pxCurrentTCB; /* Restore the Task stack pointer. */
    MOVW HL, AX
    MOVW AX, [ HL ]
    MOVW SP, AX
    راوباسه_2 AX; /* Restore _usCriticalNesting value. */
    MOVW _usCriticalNesting, AX
    راوباسه_2 BC; /* Restore the necessary general purpose registers. */
    راوباسه_2 DE
    #إذا __CODE_MODEL__ == __CODE_MODEL_FAR__
        راوباسه_2 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #وإلا
        راوباسه_2 AX
        MOV CS, A; /* Restore CS register. */
    #د_که_پای
    راوباسه_2 HL;        /* Restore general purpose register HL. */
    راوباسه_2 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#د_که_پای /* __IAR_SYSTEMS_ASM__ */

#د_که_پای /* PORTMACRO_H */
