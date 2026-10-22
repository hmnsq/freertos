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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

#جيڪڏهن_وصف_ٿيل __IAR_SYSTEMS_ICC__

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
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
        #warning This پورٽ has not been tested with your selected يادگيري model combination. If a far معلومات_2 model is required it is recommended منزل also use a far ڪوڊ model.
    #جيڪڏهن_پورو

    #إذا __DATA_MODEL__ == __DATA_MODEL_NEAR__ && __CODE_MODEL__ == __CODE_MODEL_FAR__
        #warning This پورٽ has not been tested with your selected يادگيري model combination. If a far ڪوڊ model is required it is recommended منزل also use a far معلومات_2 model.
    #جيڪڏهن_پورو

/* Type definitions. */

    #وصف_ڪريو پورٽ_CHAR          حرف
    #وصف_ڪريو پورٽ_FLOAT         عائم
    #وصف_ڪريو پورٽ_DOUBLE        مزدوج
    #وصف_ڪريو پورٽ_LONG          ڊگهو
    #وصف_ڪريو پورٽ_SHORT         ننڍو
    #وصف_ڪريو پورٽ_ڍير_TYPE    uint16_t
    #وصف_ڪريو پورٽ_بنياد_TYPE     ننڍو

    تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
    تعريفنوع ننڍو            بنياد_Type_t;
    تعريفنوع بنانشان ننڍو   UBaseType_t;


    #إذا __DATA_MODEL__ == __DATA_MODEL_FAR__
        #وصف_ڪريو پورٽ_اشارو_سائيز_TYPE    uint32_t
    #وإلا
        #وصف_ڪريو پورٽ_اشارو_سائيز_TYPE    uint16_t
    #جيڪڏهن_پورو


    #إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
        تعريفنوع بنانشان صحيح   TickType_t;
        #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
        تعريفنوع uint32_t       TickType_t;
        #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
    #وإلا
        #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
    #جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Interrupt control macros. */
    #وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    __asm( "DI" )
    #وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     __asm( "EI" )
/*-----------------------------------------------------------*/

/* Critical section control macros. */
    #وصف_ڪريو پورٽ_NO_CRITICAL_SECTION_NESTING    ( ( uint16_t ) 0 )

    #وصف_ڪريو پورٽ_ENTER_CRITICAL()                                                  \
    {                                                                             \
        خارجي متطاير uint16_t usCriticalNesting;                               \
                                                                                  \
        پورٽ_DISABLE_INTERRUPTS();                                                 \
                                                                                  \
        /* Now that interrupts are disabled, ulCriticalNesting can be accessed */ \
        /* directly.  Increment ulCriticalNesting to keep a count of how many */  \
        /* times portENTER_CRITICAL() has been called. */                         \
        usCriticalNesting++;                                                      \
    }

    #وصف_ڪريو پورٽ_EXIT_CRITICAL()                                                   \
    {                                                                             \
        خارجي متطاير uint16_t usCriticalNesting;                               \
                                                                                  \
        إذا( usCriticalNesting > پورٽ_NO_CRITICAL_SECTION_NESTING )                 \
        {                                                                         \
            /* Decrement the nesting count when leaving a critical section. */    \
            usCriticalNesting--;                                                  \
                                                                                  \
            /* If the nesting level has reached zero then interrupts should be */ \
            /* re-enabled. */                                                     \
            إذا( usCriticalNesting == پورٽ_NO_CRITICAL_SECTION_NESTING )            \
            {                                                                     \
                پورٽ_ENABLE_INTERRUPTS();                                          \
            }                                                                     \
        }                                                                         \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */
    #وصف_ڪريو پورٽ_NOP()                                         __asm( "NOP" )
    #وصف_ڪريو پورٽ_YIELD()                                       __asm( "BRK" )
    #جيڪڏهن_وصف_نه_ٿيل configREQUIRE_ASM_ISR_WRAPPER
        #وصف_ڪريو configREQUIRE_ASM_ISR_WRAPPER    1
    #جيڪڏهن_پورو
    #إذا( configREQUIRE_ASM_ISR_WRAPPER == 1 )
        /* You must implement an assembly ISR wrapper (see the below for details) if you need an ISR to cause a context switch.
         * https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/Renesas/RTOS_RL78_IAR_Demos#writing-interrupt-service-routines */
        #وصف_ڪريو پورٽ_YIELD_FROM_ISR( x_Higher_ترجيح_Task_Woken )    افعل { إذا( x_Higher_ترجيح_Task_Woken != pdFALSE ) vTaskSwitchContext(); } طالما( 0 )
    #وإلا
        /* You must not implement an assembly ISR wrapper even if you need an ISR to cause a context switch.
         * The portYIELD, which is similar to role of an assembly ISR wrapper, runs only when a context switch is required. */
        #وصف_ڪريو پورٽ_YIELD_FROM_ISR( x_Higher_ترجيح_Task_Woken )    افعل { إذا( x_Higher_ترجيح_Task_Woken != pdFALSE ) پورٽ_YIELD(); } طالما( 0 )
    #جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Hardware specifics. */
    #وصف_ڪريو پورٽ_BYTE_ALIGNMENT    2
    #وصف_ڪريو پورٽ_ڍير_GROWTH      ( -1 )
    #وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* __IAR_SYSTEMS_ICC__ */

; /*----------------------------------------------------------------------------- */
  /* The macros below are processed for asm sources which include portmacro.h. */
  /*----------------------------------------------------------------------------- */
#جيڪڏهن_وصف_ٿيل __IAR_SYSTEMS_ASM__

    ; /* Functions and variables used by this file. */
      /*----------------------------------------------------------------------------- */
    EXTERN _pxCurrentTCB
    EXTERN _usCriticalNesting

    ; /* Macro used to declutter calls, depends on the selected code model. */
      /*----------------------------------------------------------------------------- */
    #إذا __CODE_MODEL__ == __CODE_MODEL_FAR__
        #وصف_ڪريو RCALL( X )    CALL F: X
    #وإلا
        #وصف_ڪريو RCALL( X )    CALL X
    #جيڪڏهن_پورو


    ;        /*-----------------------------------------------------------------------------
              * ; * portSAVE_CONTEXT MACRO
              * ; * Saves the context of the general purpose registers, CS and ES (only in __far
              * ; * memory mode) registers the _usCriticalNesting value and the Stack Pointer
              * ; * of the active Task onto the task stack.
              * ; *---------------------------------------------------------------------------*/
پورٽ_SAVE_CONTEXT MACRO
    ڌڪو_2 AX; /* Save AX Register to stack. */
    ڌڪو_2 HL
    #إذا  __CODE_MODEL__ == __CODE_MODEL_FAR__
        MOV A, CS; /* Save CS register. */
        XCH A, X
        MOV A, ES; /* Save ES register. */
        ڌڪو_2 AX
    #وإلا
        MOV A, CS; /* Save CS register. */
        ڌڪو_2 AX
    #جيڪڏهن_پورو
    ڌڪو_2 DE;                     /* Save the remaining general purpose registers. */
    ڌڪو_2 BC
    MOVW AX, _usCriticalNesting; /* Save the _usCriticalNesting value. */
    ڌڪو_2 AX
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
پورٽ_RESTORE_CONTEXT MACRO
    MOVW AX, _pxCurrentTCB; /* Restore the Task stack pointer. */
    MOVW HL, AX
    MOVW AX, [ HL ]
    MOVW SP, AX
    ڪڍو_2 AX; /* Restore _usCriticalNesting value. */
    MOVW _usCriticalNesting, AX
    ڪڍو_2 BC; /* Restore the necessary general purpose registers. */
    ڪڍو_2 DE
    #إذا __CODE_MODEL__ == __CODE_MODEL_FAR__
        ڪڍو_2 AX;   /* Restore the ES register. */
        MOV ES, A
        XCH A, X; /* Restore the CS register. */
        MOV CS, A
    #وإلا
        ڪڍو_2 AX
        MOV CS, A; /* Restore CS register. */
    #جيڪڏهن_پورو
    ڪڍو_2 HL;        /* Restore general purpose register HL. */
    ڪڍو_2 AX;        /* Restore AX. */
    ENDM
    ;              /*----------------------------------------------------------------------------- */

#جيڪڏهن_پورو /* __IAR_SYSTEMS_ASM__ */

#جيڪڏهن_پورو /* PORTMACRO_H */
