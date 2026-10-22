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


#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          ਲੰਮਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    uint8_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਅੱਖਰ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE   ਢੇਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਨਿਸ਼ਾਨੀਵਾਲਾ ਅੱਖਰ      ਅਧਾਰ_Type_t;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ    UBaseType_t;


#ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) 0xffff
#ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t     TickType_t;
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT    1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH      ( -1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()    __asm( "swi" );
/*-----------------------------------------------------------*/

/* Critical section handling. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()     __asm( "cli" )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()    __asm( "sei" )

/*
 * Disable interrupts before incrementing the count of critical section nesting.
 * The nesting count is maintained so we know when interrupts should be
 * re-enabled.  Once interrupts are disabled the nesting count can be accessed
 * directly.  Each task maintains its own nesting count.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL()                           \
    {                                                  \
        ਬਾਹਰੀ ਅਸਥਿਰ UBaseType_t uxCriticalNesting; \
                                                       \
        ਪੋਰਟ_DISABLE_INTERRUPTS();                      \
        uxCriticalNesting++;                           \
    }

/*
 * Interrupts are disabled so we can access the nesting count directly.  If the
 * nesting is found to be 0 (no nesting) then we are leaving the critical
 * section and interrupts can be re-enabled.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ  ਪੋਰਟ_EXIT_CRITICAL()                           \
    {                                                  \
        ਬਾਹਰੀ ਅਸਥਿਰ UBaseType_t uxCriticalNesting; \
                                                       \
        uxCriticalNesting--;                           \
        ਜੇ( uxCriticalNesting == 0 )                   \
        {                                              \
            ਪੋਰਟ_ENABLE_INTERRUPTS();                   \
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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ BANKED_MODEL

/*
 * Load the stack pointer for the task, then pull the critical nesting
 * count and PPAGE register from the stack.  The remains of the
 * context are restored by the RTI instruction.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESTORE_CONTEXT() \
    {                             \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; ਖਾਲੀ *            \n\
        .globl uxCriticalNesting        ; ਅੱਖਰ              \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        lds  0,x                ; ਢੇਰ_2             \n\
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
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SAVE_CONTEXT() \
    {                          \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; ਖਾਲੀ *            \n\
        .globl uxCriticalNesting        ; ਅੱਖਰ              \n\
                                            \n\
        movb 0x30, 1,-sp            ; PPAGE             \n\
        movb uxCriticalNesting, 1,-sp                       \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        sts  0,x                ; ਢੇਰ_2             \n\
        " );                   \
    }
#ਨਹੀਂਤਾਂ /* ifdef BANKED_MODEL */

/*
 * These macros are as per the BANKED versions above, but without saving
 * and restoring the PPAGE register.
 */

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESTORE_CONTEXT() \
    {                             \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; ਖਾਲੀ *            \n\
        .globl uxCriticalNesting        ; ਅੱਖਰ              \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        lds  0,x                ; ਢੇਰ_2             \n\
                                            \n\
        movb 1,sp+,uxCriticalNesting                        \n\
        " );                      \
    }

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SAVE_CONTEXT() \
    {                          \
        __asm( "                                \n\
        .globl pxCurrentTCB         ; ਖਾਲੀ *            \n\
        .globl uxCriticalNesting        ; ਅੱਖਰ              \n\
                                            \n\
        movb uxCriticalNesting, 1,-sp                       \n\
                                            \n\
        ldx  pxCurrentTCB                           \n\
        sts  0,x                ; ਢੇਰ_2             \n\
        " );                   \
    }
#ਜੇ_ਅੰਤ /* ifdef BANKED_MODEL */

/*
 * Utility macros to save/restore correct software registers for GCC. This is
 * useful when GCC does not generate appropriate ISR head/tail code.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ISR_ਸਿਰ() \
    {                  \
        __asm( "                                 \n\
        movw _.ਚੌਖਟਾ_2, 2,-sp                         \n\
        movw _.tmp, 2,-sp                           \n\
        movw _.z, 2,-sp                             \n\
        movw _.xy, 2,-sp                            \n\
        ;movw _.d2, 2,-sp                           \n\
        ;movw _.d1, 2,-sp                           \n\
        " );           \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ISR_ਪੂਛ() \
    {                  \
        __asm( "                                 \n\
        movw 2,sp+, _.xy                            \n\
        movw 2,sp+, _.z                             \n\
        movw 2,sp+, _.tmp                           \n\
        movw 2,sp+, _.ਚੌਖਟਾ_2                         \n\
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_SWITCH_FROM_ISR() \
    ਪੋਰਟ_SAVE_CONTEXT();            \
    vTaskSwitchContext();          \
    ਪੋਰਟ_RESTORE_CONTEXT();


/* Task function macros as described on the FreeRTOS.org WEB site. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
