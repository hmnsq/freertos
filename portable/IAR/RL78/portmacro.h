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

#جے_بنا_تعریف PORTMACRO_H
#تعریف_کرو PORTMACRO_H

#جے_تعریف_شدہ __IAR_SYSTEMS_ICC__

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
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
        #warning This پورٹ has not been tested with your selected حافظہ model combination. If a far انکڑے_2 model is required it is recommended منزل also use a far کوڈ model.
    #جے_انت

    #إذا __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This پورٹ has not been tested with your selected حافظہ model combination. If a far کوڈ model is required it is recommended منزل also use a far انکڑے_2 model.
    #جے_انت

/* Type definitions. */

    #تعریف_کرو پورٹ_CHAR          حرف
    #تعریف_کرو پورٹ_FLOAT         عائم
    #تعریف_کرو پورٹ_DOUBLE        مزدوج
    #تعریف_کرو پورٹ_LONG          لما
    #تعریف_کرو پورٹ_SHORT         چھوٹا
    #تعریف_کرو پورٹ_ڈھیر_TYPE    uint16_t
    #تعریف_کرو پورٹ_ادھار_TYPE     چھوٹا

    تعريفنوع پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
    تعريفنوع چھوٹا            ادھار_Type_t;
    تعريفنوع بنانشانی چھوٹا   UBaseType_t;


    #إذا __DATA_MODEL__ == __DATA_MODEL_FAR__
        #تعریف_کرو پورٹ_اشارہ_گر_ناپ_TYPE    uint32_t
    #وإلا
        #تعریف_کرو پورٹ_اشارہ_گر_ناپ_TYPE    uint16_t
    #جے_انت


    #إذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
        تعريفنوع بنانشانی صحيح   TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_چوڑائی_وچ_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
        تعريفنوع uint32_t       TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #وإلا
        #غلطی config_TICK_TYPE_چوڑائی_وچ_بٹ سیٹ منزل unsupported tick type چوڑائی.
    #جے_انت
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    __asm( "DI" )
    #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
    #تعریف_کرو پورٹ_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

    #تعریف_کرو پورٹ_ENTER_CRITICAL()                                                  \
    {                                                                             \
        خارجي متطاير uint16_t usCriticalNesting;                               \
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
        خارجي متطاير uint16_t usCriticalNesting;                               \
                                                                                  \
        إذا( usCriticalNesting > پورٹ_NO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            إذا( usCriticalNesting == پورٹ_NO_CRITICAL_SECTION_NESTING )            \
            {                                                                     \
                پورٹ_ENABLE_INTERRUPTS();                                          \
            }                                                                     \
        }                                                                         \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
    #تعریف_کرو پورٹ_NOP()                                         __asm( "NOP" )
    #تعریف_کرو پورٹ_YIELD()                                       __asm( "BRK" )
    #جے_بنا_تعریف configREQUIRE_ASM_ISR_WRAPPER
        #تعریف_کرو configREQUIRE_ASM_ISR_WRAPPER    1
    #جے_انت
    #إذا( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #تعریف_کرو پورٹ_YIELD_FROM_ISR( x_Higher_ترجیح_Task_Woken )    افعل { إذا( x_Higher_ترجیح_Task_Woken != pdFALSE ) vTaskSwitchContext(); } طالما( 0 )
    #وإلا
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #تعریف_کرو پورٹ_YIELD_FROM_ISR( x_Higher_ترجیح_Task_Woken )    افعل { إذا( x_Higher_ترجیح_Task_Woken != pdFALSE ) پورٹ_YIELD(); } طالما( 0 )
    #جے_انت
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    2
    #تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
    #تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* __IAR_SYSTEMS_ICC__ */

; /*----------------------------------------------------------------------------- */
  /* The macros below are processed for asm sources which include portmacro.h. */
  /*----------------------------------------------------------------------------- */
#جے_تعریف_شدہ __IAR_SYSTEMS_ASM__

    ; /* Functions and variables used by this file. */
      /*----------------------------------------------------------------------------- */
    EXTERN _pxCurrentTCB
    EXTERN _usCriticalNesting

    ; /* Macro used to declutter calls, depends on the selected code model. */
      /*----------------------------------------------------------------------------- */
    #إذا __CODE_MODEL__ == __CODE_MODEL_FAR__
        #تعریف_کرو RCALL( X )    CALL F: X
    #وإلا
        #تعریف_کرو RCALL( X )    CALL X
    #جے_انت


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
پورٹ_SAVE_CONTEXT MACRO
    ڈالو_2 AX; /* Save AX Register to stack. */
    ڈالو_2 HL
    #إذا  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        ڈالو_2 AX
    #وإلا
        MOV A, CS; /* Save CS register. */
        ڈالو_2 AX
    #جے_انت
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
    #إذا __CODE_MODEL__ == __CODE_MODEL_FAR__
        نکالو_2 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #وإلا
        نکالو_2 AX
        MOV CS, A; /* Restore CS register. */
    #جے_انت
    نکالو_2 HL;        /* Restore general purpose register HL. */
    نکالو_2 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#جے_انت /* __IAR_SYSTEMS_ASM__ */

#جے_انت /* PORTMACRO_H */
