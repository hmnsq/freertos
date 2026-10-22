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

/* Type definitions. */
#وصف_ڪريو پورٽ_CHAR          حرف
#وصف_ڪريو پورٽ_FLOAT         عائم
#وصف_ڪريو پورٽ_DOUBLE        مزدوج
#وصف_ڪريو پورٽ_LONG          ڊگهو
#وصف_ڪريو پورٽ_SHORT         ننڍو
#وصف_ڪريو پورٽ_ڍير_TYPE    uint8_t
#وصف_ڪريو پورٽ_بنياد_TYPE     حرف

تعريفنوع پورٽ_ڍير_TYPE   ڍير_Type_t;
تعريفنوع نشانوارو حرف      بنياد_Type_t;
تعريفنوع بنانشان حرف    UBaseType_t;


#إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
    تعريفنوع uint16_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
    تعريفنوع uint32_t     TickType_t;
    #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#وإلا
    #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#وصف_ڪريو پورٽ_BYTE_ALIGNMENT    1
#وصف_ڪريو پورٽ_ڍير_GROWTH      ( -1 )
#وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#وصف_ڪريو پورٽ_YIELD()    __asm( "swi" );
/*-----------------------------------------------------------*/

/* Critical section handling. */
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     __asm( "cli" )
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    __asm( "sei" )

/*
 * Disable interrupts before incrementing the count of critical section nesting.
 * The nesting count is maintained so we know when interrupts should be
 * re-enabled.  Once interrupts are disabled the nesting count can be accessed
 * directly.  Each task maintains its own nesting count.
 */
#وصف_ڪريو پورٽ_ENTER_CRITICAL()                           \
    {                                                  \
        خارجي متطاير UBaseType_t uxCriticalNesting; \
                                                       \
        پورٽ_DISABLE_INTERRUPTS();                      \
        uxCriticalNesting++;                           \
    }

/*
 * Interrupts are disabled so we can access the nesting count directly.  If the
 * nesting is found to be 0 (no nesting) then we are leaving the critical
 * section and interrupts can be re-enabled.
 */
#وصف_ڪريو  پورٽ_EXIT_CRITICAL()                           \
    {                                                  \
        خارجي متطاير UBaseType_t uxCriticalNesting; \
                                                       \
        uxCriticalNesting--;                           \
        إذا( uxCriticalNesting == 0 )                   \
        {                                              \
            پورٽ_ENABLE_INTERRUPTS();                   \
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

#جيڪڏهن_وصف_ٿيل BANKED_MODEL

/*
 * Load the stack pointer for the task, then pull the critical nesting
 * count and PPAGE register from the stack.  The remains of the
 * context are restored by the RTI instruction.
 */
    #وصف_ڪريو پورٽ_RESTORE_CONTEXT() \
    {                             \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; فراغ *            \n\
        .globl uxCriticalNesting        ; حرف              \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        lds  0,x                ; ڍير_2             \n\
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
    #وصف_ڪريو پورٽ_SAVE_CONTEXT() \
    {                          \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; فراغ *            \n\
        .globl uxCriticalNesting        ; حرف              \n\
                                            \n\
        movb 0x30, 1,-sp            ; PPAGE             \n\
        movb uxCriticalNesting, 1,-sp                       \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        sts  0,x                ; ڍير_2             \n\
        " );                   \
    }
#وإلا /* ifdef BANKED_MODEL */

/*
 * These macros are as per the BANKED versions above, but without saving
 * and restoring the PPAGE register.
 */

    #وصف_ڪريو پورٽ_RESTORE_CONTEXT() \
    {                             \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; فراغ *            \n\
        .globl uxCriticalNesting        ; حرف              \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        lds  0,x                ; ڍير_2             \n\
                                            \n\
        movb 1,sp+,uxCriticalNesting                        \n\
        " );                      \
    }

    #وصف_ڪريو پورٽ_SAVE_CONTEXT() \
    {                          \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; فراغ *            \n\
        .globl uxCriticalNesting        ; حرف              \n\
                                            \n\
        movb uxCriticalNesting, 1,-sp                       \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        sts  0,x                ; ڍير_2             \n\
        " );                   \
    }
#جيڪڏهن_پورو /* ifdef BANKED_MODEL */

/*
 * Utility macros to save/restore correct software registers for GCC. This is
 * useful when GCC does not generate appropriate ISR head/tail code.
 */
#وصف_ڪريو پورٽ_ISR_سر() \
    {                  \
        __asm( "                                 \n\
        movw _.چوکٺو_2, 2,-sp                         \n\
        movw _.tmp, 2,-sp                           \n\
        movw _.z, 2,-sp                             \n\
        movw _.xy, 2,-sp                            \n\
        ;movw _.d2, 2,-sp                           \n\
        ;movw _.d1, 2,-sp                           \n\
        " );           \
    }

#وصف_ڪريو پورٽ_ISR_پڇ() \
    {                  \
        __asm( "                                 \n\
        movw 2,sp+, _.xy                            \n\
        movw 2,sp+, _.z                             \n\
        movw 2,sp+, _.tmp                           \n\
        movw 2,sp+, _.چوکٺو_2                         \n\
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

#وصف_ڪريو پورٽ_TASK_SWITCH_FROM_ISR() \
    پورٽ_SAVE_CONTEXT();            \
    vTaskSwitchContext();          \
    پورٽ_RESTORE_CONTEXT();


/* Task function macros as described on the FreeRTOS.org WEB site. */
#وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
