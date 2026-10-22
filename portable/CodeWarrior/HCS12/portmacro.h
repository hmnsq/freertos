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
#నిర్వచించు పోర్టు_CHAR        అక్షరం
#నిర్వచించు పోర్టు_FLOAT       దశాంశం
#నిర్వచించు పోర్టు_DOUBLE      ద్విగుణ
#నిర్వచించు పోర్టు_LONG        దీర్ఘ
#నిర్వచించు పోర్టు_SHORT       పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE  uint8_t
#నిర్వచించు పోర్టు_పునాది_TYPE   అక్షరం

రకనిర్వచనం పోర్టు_దొంతర_TYPE దొంతర_Type_t;
రకనిర్వచనం గుర్తుగల అక్షరం పునాది_Type_t;
రకనిర్వచనం గుర్తులేని అక్షరం UBaseType_t;

#ఒకవేళ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY ( TickType_t )    ( 0xFFFFFFFFUL )
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Hardware specifics. */
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT          1
#నిర్వచించు పోర్టు_దొంతర_GROWTH            ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS          ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_YIELD()                 __asm( "swi" );
#నిర్వచించు పోర్టు_NOP()                   __asm( "nop" );
/*-----------------------------------------------------------*/

/* Critical section handling. */
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()             __asm( "cli" )
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()            __asm( "sei" )

/*
 * Disable interrupts before incrementing the count of critical section nesting.
 * The nesting count is maintained so we know when interrupts should be
 * re-enabled.  Once interrupts are disabled the nesting count can be accessed
 * directly.  Each task maintains its own nesting count.
 */
#నిర్వచించు పోర్టు_ENTER_CRITICAL()                                    \
{                                                               \
    బాహ్య అస్థిర UBaseType_t uxCriticalNesting;  \
                                                                \
    పోర్టు_DISABLE_INTERRUPTS();                                   \
    uxCriticalNesting++;                                        \
}

/*
 * Interrupts are disabled so we can access the nesting count directly.  If the
 * nesting is found to be 0 (no nesting) then we are leaving the critical
 * section and interrupts can be re-enabled.
 */
#నిర్వచించు  పోర్టు_EXIT_CRITICAL()                                    \
{                                                               \
    బాహ్య అస్థిర UBaseType_t uxCriticalNesting;  \
                                                                \
    uxCriticalNesting--;                                        \
    ఒకవేళ( uxCriticalNesting == 0 )                                \
    {                                                           \
        పోర్టు_ENABLE_INTERRUPTS();                                \
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

#నిర్వచితమైతే BANKED_MODEL
    /*
     * Load the stack pointer for the task, then pull the critical nesting
     * count and PPAGE register from the stack.  The remains of the
     * context are restored by the RTI instruction.
     */
    #నిర్వచించు పోర్టు_RESTORE_CONTEXT()                                   \
    {                                                               \
        బాహ్య అస్థిర శూన్య * pxCurrentTCB;                        \
        బాహ్య అస్థిర UBaseType_t uxCriticalNesting;  \
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
    #నిర్వచించు పోర్టు_SAVE_CONTEXT()                                      \
    {                                                               \
        బాహ్య అస్థిర శూన్య * pxCurrentTCB;                        \
        బాహ్య అస్థిర UBaseType_t uxCriticalNesting;  \
                                                                    \
        __asm( "ldaa 0x30" );  /* 0x30 = PPAGE */                   \
        __asm( "psha" );                                            \
        __asm( "ldaa uxCriticalNesting" );                          \
        __asm( "psha" );                                            \
        __asm( "ldx pxCurrentTCB" );                                \
        __asm( "sts 0, x" );                                        \
    }
#లేకపోతే

    /*
     * These macros are as per the BANKED versions above, but without saving
     * and restoring the PPAGE register.
     */

    #నిర్వచించు పోర్టు_RESTORE_CONTEXT()                                   \
    {                                                               \
        బాహ్య అస్థిర శూన్య * pxCurrentTCB;                        \
        బాహ్య అస్థిర UBaseType_t uxCriticalNesting;  \
                                                                    \
        __asm( "ldx pxCurrentTCB" );                                \
        __asm( "lds 0, x" );                                        \
        __asm( "pula" );                                            \
        __asm( "staa uxCriticalNesting" );                          \
    }

    #నిర్వచించు పోర్టు_SAVE_CONTEXT()                                      \
    {                                                               \
        బాహ్య అస్థిర శూన్య * pxCurrentTCB;                        \
        బాహ్య అస్థిర UBaseType_t uxCriticalNesting;  \
                                                                    \
        __asm( "ldaa uxCriticalNesting" );                          \
        __asm( "psha" );                                            \
        __asm( "ldx pxCurrentTCB" );                                \
        __asm( "sts 0, x" );                                        \
    }
#అయితే_ముగింపు

/*
 * Utility macro to call macros above in correct order in order to perform a
 * task switch from within a standard ISR.  This macro can only be used if
 * the ISR does not use any local (stack) variables.  If the ISR uses stack
 * variables portYIELD() should be used in it's place.
 */
#నిర్వచించు పోర్టు_TASK_SWITCH_FROM_ISR()                              \
    పోర్టు_SAVE_CONTEXT();                                         \
    vTaskSwitchContext();                                       \
    పోర్టు_RESTORE_CONTEXT();


/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters ) శూన్య vFunction( శూన్య *pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters ) శూన్య vFunction( శూన్య *pvParameters )

#అయితే_ముగింపు /* PORTMACRO_H */
