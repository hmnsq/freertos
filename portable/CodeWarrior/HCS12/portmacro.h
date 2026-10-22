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
#تعریف_کړه پورټ_CHAR        حرف
#تعریف_کړه پورټ_FLOAT       عائم
#تعریف_کړه پورټ_DOUBLE      مزدوج
#تعریف_کړه پورټ_LONG        اوږد
#تعریف_کړه پورټ_SHORT       لنډ
#تعریف_کړه پورټ_ډېری_TYPE  uint8_t
#تعریف_کړه پورټ_بنسټ_TYPE   حرف

تعريفنوع پورټ_ډېری_TYPE ډېری_Type_t;
تعريفنوع نښهدار حرف بنسټ_Type_t;
تعريفنوع بینښه حرف UBaseType_t;

#إذا( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#تعریف_کړه پورټ_BYTE_ALIGNMENT          1
#تعریف_کړه پورټ_ډېری_GROWTH            ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_YIELD()                 __asm( "swi" );
#تعریف_کړه پورټ_NOP()                   __asm( "nop" );
/*-----------------------------------------------------------*/

/* Critical section handling. */
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()             __asm( "cli" )
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()            __asm( "sei" )

/*
 * Disable interrupts before incrementing the count of critical section nesting.
 * The nesting count is maintained so we know when interrupts should be
 * re-enabled.  Once interrupts are disabled the nesting count can be accessed
 * directly.  Each task maintains its own nesting count.
 */
#تعریف_کړه پورټ_ENTER_CRITICAL()                                    \
{                                                               \
    خارجي متطاير UBaseType_t uxCriticalNesting;  \
                                                                \
    پورټ_DISABLE_INTERRUPTS();                                   \
    uxCriticalNesting++;                                        \
}

/*
 * Interrupts are disabled so we can access the nesting count directly.  If the
 * nesting is found to be 0 (no nesting) then we are leaving the critical
 * section and interrupts can be re-enabled.
 */
#تعریف_کړه  پورټ_EXIT_CRITICAL()                                    \
{                                                               \
    خارجي متطاير UBaseType_t uxCriticalNesting;  \
                                                                \
    uxCriticalNesting--;                                        \
    إذا( uxCriticalNesting == 0 )                                \
    {                                                           \
        پورټ_ENABLE_INTERRUPTS();                                \
    }                                                           \
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

#که_تعریف_شوی BANKED_MODEL
    /*
     * Load the stack pointer for the task, then pull the critical nesting
     * count and PPAGE register from the stack.  The remains of the
     * context are restored by the RTI instruction.
     */
    #تعریف_کړه پورټ_RESTORE_CONTEXT()                                   \
    {                                                               \
        خارجي متطاير فراغ * pxCurrentTCB;                        \
        خارجي متطاير UBaseType_t uxCriticalNesting;  \
                                                                    \
        __asm( "ldx pxCurrentTCB" );                                \
        __asm( "lds 0, x" );                                        \
        __asm( "pula" );                                            \
        __asm( "staa uxCriticalNesting" );                          \
        __asm( "pula" );                                            \
        __asm( "staa 0x30" ); /* 0x30 = PPAGE */                    \
    }

    /*
     * By the time this macro is called the processor has already stacked the
     * registers.  Simply stack the nesting count and PPAGE value, then save
     * the task stack pointer.
     */
    #تعریف_کړه پورټ_SAVE_CONTEXT()                                      \
    {                                                               \
        خارجي متطاير فراغ * pxCurrentTCB;                        \
        خارجي متطاير UBaseType_t uxCriticalNesting;  \
                                                                    \
        __asm( "ldaa 0x30" );  /* 0x30 = PPAGE */                   \
        __asm( "psha" );                                            \
        __asm( "ldaa uxCriticalNesting" );                          \
        __asm( "psha" );                                            \
        __asm( "ldx pxCurrentTCB" );                                \
        __asm( "sts 0, x" );                                        \
    }
#وإلا

    /*
     * These macros are as per the BANKED versions above, but without saving
     * and restoring the PPAGE register.
     */

    #تعریف_کړه پورټ_RESTORE_CONTEXT()                                   \
    {                                                               \
        خارجي متطاير فراغ * pxCurrentTCB;                        \
        خارجي متطاير UBaseType_t uxCriticalNesting;  \
                                                                    \
        __asm( "ldx pxCurrentTCB" );                                \
        __asm( "lds 0, x" );                                        \
        __asm( "pula" );                                            \
        __asm( "staa uxCriticalNesting" );                          \
    }

    #تعریف_کړه پورټ_SAVE_CONTEXT()                                      \
    {                                                               \
        خارجي متطاير فراغ * pxCurrentTCB;                        \
        خارجي متطاير UBaseType_t uxCriticalNesting;  \
                                                                    \
        __asm( "ldaa uxCriticalNesting" );                          \
        __asm( "psha" );                                            \
        __asm( "ldx pxCurrentTCB" );                                \
        __asm( "sts 0, x" );                                        \
    }
#د_که_پای

/*
 * Utility macro to call macros above in correct order in order to perform a
 * task switch from within a standard ISR.  This macro can only be used if
 * the ISR does not use any local (stack) variables.  If the ISR uses stack
 * variables portYIELD() should be used in it's place.
 */
#تعریف_کړه پورټ_TASK_SWITCH_FROM_ISR()                              \
    پورټ_SAVE_CONTEXT();                                         \
    vTaskSwitchContext();                                       \
    پورټ_RESTORE_CONTEXT();


/* Task function macros as described on the FreeRTOS.org WEB site. */
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters ) فراغ vFunction( فراغ *pvParameters )

#د_که_پای /* PORTMACRO_H */
