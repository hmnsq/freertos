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


#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
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
#تعریف_کرو پورٹ_CHAR          حرف
#تعریف_کرو پورٹ_FLOAT         اعشاری
#تعریف_کرو پورٹ_DOUBLE        دوہرا
#تعریف_کرو پورٹ_LONG          طویل
#تعریف_کرو پورٹ_SHORT         مختصر
#تعریف_کرو پورٹ_ڈھیر_TYPE    uint8_t
#تعریف_کرو پورٹ_بنیاد_TYPE     حرف

قسمتعریف پورٹ_ڈھیر_TYPE   ڈھیر_Type_t;
قسمتعریف علامتی حرف      بنیاد_Type_t;
قسمتعریف غیرعلامتی حرف    UBaseType_t;


#اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
    قسمتعریف uint16_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
#وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
    قسمتعریف uint32_t     TickType_t;
    #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#ورنہ
    #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
#اگر_ختم
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کرو پورٹ_BYTE_ALIGNMENT    1
#تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
#تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کرو پورٹ_YIELD()    __asm( "swi" );
/*-----------------------------------------------------------*/

/* Critical section handling. */
#تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     __asm( "cli" )
#تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    __asm( "sei" )

/*
 * Disable interrupts before incrementing the count of critical section nesting.
 * The nesting count is maintained so we know when interrupts should be
 * re-enabled.  Once interrupts are disabled the nesting count can be accessed
 * directly.  Each task maintains its own nesting count.
 */
#تعریف_کرو پورٹ_ENTER_CRITICAL()                           \
    {                                                  \
        خارجی متلون UBaseType_t uxCriticalNesting; \
                                                       \
        پورٹ_DISABLE_INTERRUPTS();                      \
        uxCriticalNesting++;                           \
    }

/*
 * Interrupts are disabled so we can access the nesting count directly.  If the
 * nesting is found to be 0 (no nesting) then we are leaving the critical
 * section and interrupts can be re-enabled.
 */
#تعریف_کرو  پورٹ_EXIT_CRITICAL()                           \
    {                                                  \
        خارجی متلون UBaseType_t uxCriticalNesting; \
                                                       \
        uxCriticalNesting--;                           \
        اگر( uxCriticalNesting == 0 )                   \
        {                                              \
            پورٹ_ENABLE_INTERRUPTS();                   \
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

#اگر_تعریف_شدہ BANKED_MODEL

/*
 * Load the stack pointer for the task, then pull the critical nesting
 * count and PPAGE register from the stack.  The remains of the
 * context are restored by the RTI instruction.
 */
    #تعریف_کرو پورٹ_RESTORE_CONTEXT() \
    {                             \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; خالی *            \n\
        .globl uxCriticalNesting        ; حرف              \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        lds  0,x                ; ڈھیر_2             \n\
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
    #تعریف_کرو پورٹ_SAVE_CONTEXT() \
    {                          \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; خالی *            \n\
        .globl uxCriticalNesting        ; حرف              \n\
                                            \n\
        movb 0x30, 1,-sp            ; PPAGE             \n\
        movb uxCriticalNesting, 1,-sp                       \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        sts  0,x                ; ڈھیر_2             \n\
        " );                   \
    }
#ورنہ /* ifdef BANKED_MODEL */

/*
 * These macros are as per the BANKED versions above, but without saving
 * and restoring the PPAGE register.
 */

    #تعریف_کرو پورٹ_RESTORE_CONTEXT() \
    {                             \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; خالی *            \n\
        .globl uxCriticalNesting        ; حرف              \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        lds  0,x                ; ڈھیر_2             \n\
                                            \n\
        movb 1,sp+,uxCriticalNesting                        \n\
        " );                      \
    }

    #تعریف_کرو پورٹ_SAVE_CONTEXT() \
    {                          \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; خالی *            \n\
        .globl uxCriticalNesting        ; حرف              \n\
                                            \n\
        movb uxCriticalNesting, 1,-sp                       \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        sts  0,x                ; ڈھیر_2             \n\
        " );                   \
    }
#اگر_ختم /* ifdef BANKED_MODEL */

/*
 * Utility macros to save/restore correct software registers for GCC. This is
 * useful when GCC does not generate appropriate ISR head/tail code.
 */
#تعریف_کرو پورٹ_ISR_سر() \
    {                  \
        __asm( "                                 \n\
        movw _.چوکھٹا_2, 2,-sp                         \n\
        movw _.tmp, 2,-sp                           \n\
        movw _.z, 2,-sp                             \n\
        movw _.xy, 2,-sp                            \n\
        ;movw _.d2, 2,-sp                           \n\
        ;movw _.d1, 2,-sp                           \n\
        " );           \
    }

#تعریف_کرو پورٹ_ISR_دم() \
    {                  \
        __asm( "                                 \n\
        movw 2,sp+, _.xy                            \n\
        movw 2,sp+, _.z                             \n\
        movw 2,sp+, _.tmp                           \n\
        movw 2,sp+, _.چوکھٹا_2                         \n\
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

#تعریف_کرو پورٹ_TASK_SWITCH_FROM_ISR() \
    پورٹ_SAVE_CONTEXT();            \
    vTaskSwitchContext();          \
    پورٹ_RESTORE_CONTEXT();


/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
#تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
