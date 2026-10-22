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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

#اگر_تعریف_شده __IAR_SYSTEMS_ICC__

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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
        #warning This پورت has not been tested with your selected حافظه model combination. If a far داده_2 model is required it is recommended مقصد also use a far کد model.
    #پایان_اگر

    #إذا __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This پورت has not been tested with your selected حافظه model combination. If a far کد model is required it is recommended مقصد also use a far داده_2 model.
    #پایان_اگر

/* Type definitions. */

    #تعریف_کن پورت_CHAR          حرف
    #تعریف_کن پورت_FLOAT         عائم
    #تعریف_کن پورت_DOUBLE        مزدوج
    #تعریف_کن پورت_LONG          دراز
    #تعریف_کن پورت_SHORT         کوتاه
    #تعریف_کن پورت_پشته_TYPE    uint16_t
    #تعریف_کن پورت_پایه_TYPE     کوتاه

    تعريفنوع پورت_پشته_TYPE   پشته_Type_t;
    تعريفنوع کوتاه            پایه_Type_t;
    تعريفنوع بیعلامت کوتاه   UBaseType_t;


    #إذا __DATA_MODEL__ == __DATA_MODEL_FAR__
        #تعریف_کن پورت_اشاره_گر_اندازه_TYPE    uint32_t
    #وإلا
        #تعریف_کن پورت_اشاره_گر_اندازه_TYPE    uint16_t
    #پایان_اگر


    #إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
        تعريفنوع بیعلامت صحيح   TickType_t;
        #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
        تعريفنوع uint32_t       TickType_t;
        #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #وإلا
        #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
    #پایان_اگر
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
    #تعریف_کن پورت_DISABLE_INTERRUPTS()    __asm( "DI" )
    #تعریف_کن پورت_ENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
    #تعریف_کن پورت_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

    #تعریف_کن پورت_ENTER_CRITICAL()                                                  \
    {                                                                             \
        خارجي متطاير uint16_t usCriticalNesting;                               \
                                                                                  \
        پورت_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

    #تعریف_کن پورت_EXIT_CRITICAL()                                                   \
    {                                                                             \
        خارجي متطاير uint16_t usCriticalNesting;                               \
                                                                                  \
        إذا( usCriticalNesting > پورت_NO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            إذا( usCriticalNesting == پورت_NO_CRITICAL_SECTION_NESTING )            \
            {                                                                     \
                پورت_ENABLE_INTERRUPTS();                                          \
            }                                                                     \
        }                                                                         \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
    #تعریف_کن پورت_NOP()                                         __asm( "NOP" )
    #تعریف_کن پورت_YIELD()                                       __asm( "BRK" )
    #اگر_تعریف_نشده configREQUIRE_ASM_ISR_WRAPPER
        #تعریف_کن configREQUIRE_ASM_ISR_WRAPPER    1
    #پایان_اگر
    #إذا( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #تعریف_کن پورت_YIELD_FROM_ISR( x_Higher_اولویت_Task_Woken )    افعل { إذا( x_Higher_اولویت_Task_Woken != pdFALSE ) vTaskSwitchContext(); } طالما( 0 )
    #وإلا
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #تعریف_کن پورت_YIELD_FROM_ISR( x_Higher_اولویت_Task_Woken )    افعل { إذا( x_Higher_اولویت_Task_Woken != pdFALSE ) پورت_YIELD(); } طالما( 0 )
    #پایان_اگر
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #تعریف_کن پورت_BYTE_ALIGNMENT    2
    #تعریف_کن پورت_پشته_GROWTH      ( -1 )
    #تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* __IAR_SYSTEMS_ICC__ */

; /*----------------------------------------------------------------------------- */
  /* The macros below are processed for asm sources which include portmacro.h. */
  /*----------------------------------------------------------------------------- */
#اگر_تعریف_شده __IAR_SYSTEMS_ASM__

    ; /* Functions and variables used by this file. */
      /*----------------------------------------------------------------------------- */
    EXTERN _pxCurrentTCB
    EXTERN _usCriticalNesting

    ; /* Macro used to declutter calls, depends on the selected code model. */
      /*----------------------------------------------------------------------------- */
    #إذا __CODE_MODEL__ == __CODE_MODEL_FAR__
        #تعریف_کن RCALL( X )    CALL F: X
    #وإلا
        #تعریف_کن RCALL( X )    CALL X
    #پایان_اگر


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
پورت_SAVE_CONTEXT MACRO
    افزودن_2 AX; /* Save AX Register to stack. */
    افزودن_2 HL
    #إذا  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        افزودن_2 AX
    #وإلا
        MOV A, CS; /* Save CS register. */
        افزودن_2 AX
    #پایان_اگر
    افزودن_2 DE;                     /* Save the remaining general purpose registers. */
    افزودن_2 BC
    MOVW AX, _usCriticalNesting; /* Save the _usCriticalNesting value. */
    افزودن_2 AX
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
پورت_RESTORE_CONTEXT MACRO
    MOVW AX, _pxCurrentTCB; /* Restore the Task stack pointer. */
    MOVW HL, AX
    MOVW AX, [ HL ]
    MOVW SP, AX
    برداشت_2 AX; /* Restore _usCriticalNesting value. */
    MOVW _usCriticalNesting, AX
    برداشت_2 BC; /* Restore the necessary general purpose registers. */
    برداشت_2 DE
    #إذا __CODE_MODEL__ == __CODE_MODEL_FAR__
        برداشت_2 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #وإلا
        برداشت_2 AX
        MOV CS, A; /* Restore CS register. */
    #پایان_اگر
    برداشت_2 HL;        /* Restore general purpose register HL. */
    برداشت_2 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#پایان_اگر /* __IAR_SYSTEMS_ASM__ */

#پایان_اگر /* PORTMACRO_H */
