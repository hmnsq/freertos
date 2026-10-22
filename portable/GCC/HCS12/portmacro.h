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

/* Type definitions. */
#परिभाषय पत्तनम्_CHAR          वर्ण
#परिभाषय पत्तनम्_FLOAT         भिन्न
#परिभाषय पत्तनम्_DOUBLE        द्विगुण
#परिभाषय पत्तनम्_LONG          दीर्घ
#परिभाषय पत्तनम्_SHORT         ह्रस्व
#परिभाषय पत्तनम्_राशिः_TYPE    uint8_t
#परिभाषय पत्तनम्_आधारः_TYPE     वर्ण

प्रकारनिर्देश पत्तनम्_राशिः_TYPE   राशिः_Type_t;
प्रकारनिर्देश चिह्नित वर्ण      आधारः_Type_t;
प्रकारनिर्देश अचिह्नित वर्ण    UBaseType_t;


#यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
    प्रकारनिर्देश uint16_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffff
#नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
    प्रकारनिर्देश uint32_t     TickType_t;
    #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#अन्यथा
    #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
#यदि_अन्तः
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#परिभाषय पत्तनम्_BYTE_ALIGNMENT    1
#परिभाषय पत्तनम्_राशिः_GROWTH      ( -1 )
#परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
#परिभाषय पत्तनम्_YIELD()    __asm( "swi" );
/*-----------------------------------------------------------*/

/* Critical section handling. */
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     __asm( "cli" )
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    __asm( "sei" )

/*
 * Disable interrupts before incrementing the count of critical section nesting.
 * The nesting count is maintained so we know when interrupts should be
 * re-enabled.  Once interrupts are disabled the nesting count can be accessed
 * directly.  Each task maintains its own nesting count.
 */
#परिभाषय पत्तनम्_ENTER_CRITICAL()                           \
    {                                                  \
        बाह्य चञ्चल UBaseType_t uxCriticalNesting; \
                                                       \
        पत्तनम्_DISABLE_INTERRUPTS();                      \
        uxCriticalNesting++;                           \
    }

/*
 * Interrupts are disabled so we can access the nesting count directly.  If the
 * nesting is found to be 0 (no nesting) then we are leaving the critical
 * section and interrupts can be re-enabled.
 */
#परिभाषय  पत्तनम्_EXIT_CRITICAL()                           \
    {                                                  \
        बाह्य चञ्चल UBaseType_t uxCriticalNesting; \
                                                       \
        uxCriticalNesting--;                           \
        यदि( uxCriticalNesting == 0 )                   \
        {                                              \
            पत्तनम्_ENABLE_INTERRUPTS();                   \
        }                                              \
    }
/*-----------------------------------------------------------*/

/* Task utilities. */

/*
 * These macros are very simple as the processor automatically saves and
 * restores its registers as interrupts are entered and exited.  In
 * addition to the (automatically stacked) registers we also stack the
 * critical nesting count.  Each task maintains its own critical nesting
 * count as it is legitimate for a task to yield from within a critical
 * section.  If the banked memory model is being used then the PPAGE
 * register is also stored as part of the tasks context.
 */

#यदि_परिभाषितम् BANKED_MODEL

/*
 * Load the stack pointer for the task, then pull the critical nesting
 * count and PPAGE register from the stack.  The remains of the
 * context are restored by the RTI instruction.
 */
    #परिभाषय पत्तनम्_RESTORE_CONTEXT() \
    {                             \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; शून्य *            \n\
        .globl uxCriticalNesting        ; वर्ण              \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        lds  0,x                ; राशिः_2             \n\
                                            \n\
        movb 1,sp+,uxCriticalNesting                        \n\
        movb 1,sp+,0x30             ; PPAGE             \n\
        " );                      \
    }

/*
 * By the time this macro is called the processor has already stacked the
 * registers.  Simply stack the nesting count and PPAGE value, then save
 * the task stack pointer.
 */
    #परिभाषय पत्तनम्_SAVE_CONTEXT() \
    {                          \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; शून्य *            \n\
        .globl uxCriticalNesting        ; वर्ण              \n\
                                            \n\
        movb 0x30, 1,-sp            ; PPAGE             \n\
        movb uxCriticalNesting, 1,-sp                       \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        sts  0,x                ; राशिः_2             \n\
        " );                   \
    }
#अन्यथा /* ifdef BANKED_MODEL */

/*
 * These macros are as per the BANKED versions above, but without saving
 * and restoring the PPAGE register.
 */

    #परिभाषय पत्तनम्_RESTORE_CONTEXT() \
    {                             \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; शून्य *            \n\
        .globl uxCriticalNesting        ; वर्ण              \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        lds  0,x                ; राशिः_2             \n\
                                            \n\
        movb 1,sp+,uxCriticalNesting                        \n\
        " );                      \
    }

    #परिभाषय पत्तनम्_SAVE_CONTEXT() \
    {                          \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; शून्य *            \n\
        .globl uxCriticalNesting        ; वर्ण              \n\
                                            \n\
        movb uxCriticalNesting, 1,-sp                       \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        sts  0,x                ; राशिः_2             \n\
        " );                   \
    }
#यदि_अन्तः /* ifdef BANKED_MODEL */

/*
 * Utility macros to save/restore correct software registers for GCC. This is
 * useful when GCC does not generate appropriate ISR head/tail code.
 */
#परिभाषय पत्तनम्_ISR_शीर्ष() \
    {                  \
        __asm( "                                 \n\
        movw _.frame, 2,-sp                         \n\
        movw _.tmp, 2,-sp                           \n\
        movw _.z, 2,-sp                             \n\
        movw _.xy, 2,-sp                            \n\
        ;movw _.d2, 2,-sp                           \n\
        ;movw _.d1, 2,-sp                           \n\
        " );           \
    }

#परिभाषय पत्तनम्_ISR_पुच्छ() \
    {                  \
        __asm( "                                 \n\
        movw 2,sp+, _.xy                            \n\
        movw 2,sp+, _.z                             \n\
        movw 2,sp+, _.tmp                           \n\
        movw 2,sp+, _.frame                         \n\
        ;movw 2,sp+, _.d1                           \n\
        ;movw 2,sp+, _.d2                           \n\
        rti                                 \n\
        " );           \
    }

/*
 * Utility macro to call macros above in correct order in order to perform a
 * task switch from within a standard ISR.  This macro can only be used if
 * the ISR does not use any local (stack) variables.  If the ISR uses stack
 * variables portYIELD() should be used in it's place.
 */

#परिभाषय पत्तनम्_TASK_SWITCH_FROM_ISR() \
    पत्तनम्_SAVE_CONTEXT();            \
    vTaskSwitchContext();          \
    पत्तनम्_RESTORE_CONTEXT();


/* Task function macros as described on the FreeRTOS.org WEB site. */
#परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
#परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
