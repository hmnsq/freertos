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

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
/* *INDENT-ON* */

#అన్తర్భావ <machine/cpu.h>

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
#నిర్వచించు పోర్టు_CHAR          అక్షరం
#నిర్వచించు పోర్టు_FLOAT         దశాంశం
#నిర్వచించు పోర్టు_DOUBLE        ద్విగుణ
#నిర్వచించు పోర్టు_LONG          దీర్ఘ
#నిర్వచించు పోర్టు_SHORT         పొట్టి
#నిర్వచించు పోర్టు_దొంతర_TYPE    uint32_t
#నిర్వచించు పోర్టు_పునాది_TYPE     దీర్ఘ

రకనిర్వచనం పోర్టు_దొంతర_TYPE   దొంతర_Type_t;
రకనిర్వచనం దీర్ఘ             పునాది_Type_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ    UBaseType_t;

#ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
    రకనిర్వచనం uint16_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffff
#లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
    రకనిర్వచనం uint32_t     TickType_t;
    #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#లేకపోతే
    #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#నిర్వచించు పోర్టు_దొంతర_GROWTH               ( -1 )
#నిర్వచించు పోర్టు_TICK_PERIOD_MS             ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
#నిర్వచించు పోర్టు_BYTE_ALIGNMENT             4
#నిర్వచించు పోర్టు_NOP()    __asm__ అస్థిర ( "mov r0, r0" )
#నిర్వచించు పోర్టు_CRITICAL_NESTING_లోపల_TCB    1
#నిర్వచించు పోర్టు_IRQ_TRAP_YIELD             31
/*-----------------------------------------------------------*/

/* Task utilities. */

బాహ్య శూన్య v_పోర్టు_Yield( శూన్య );

/*---------------------------------------------------------------------------*/

#నిర్వచించు పోర్టు_YIELD()    asm __volatile__ ( " trap #%0 " : : "i" ( పోర్టు_IRQ_TRAP_YIELD ) : "memory" )
/*---------------------------------------------------------------------------*/

బాహ్య శూన్య vTaskEnterCritical( శూన్య );
బాహ్య శూన్య vTaskExitCritical( శూన్య );
#నిర్వచించు పోర్టు_ENTER_CRITICAL()    vTaskEnterCritical()
#నిర్వచించు పోర్టు_EXIT_CRITICAL()     vTaskExitCritical()
/*---------------------------------------------------------------------------*/

/* Critical section management. */
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    cpu_int_disable()
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     cpu_int_enable()

/*---------------------------------------------------------------------------*/

#నిర్వచించు పోర్టు_YIELD_FROM_ISR( x_Higher_ప్రాధాన్యత_Task_Woken )    చేయి { ఒకవేళ( x_Higher_ప్రాధాన్యత_Task_Woken != pdFALSE ) vTaskSwitchContext( ); } అయితే( 0 )

/*---------------------------------------------------------------------------*/

#నిర్వచించు పోర్టు_SAVE_CONTEXT()                                                                                      \
    asm __volatile__                                                                                            \
    (                                                                                                           \
        "sub    r1, #68                 \n" /* Make space on the stack for the context. */                      \
        "std    r2, [r1] +  0           \n"                                                                     \
        "stq    r4, [r1] +  8           \n"                                                                     \
        "stq    r8, [r1] +  24          \n"                                                                     \
        "stq    r12, [r1] + 40          \n"                                                                     \
        "mov    r6, rtt                 \n"                                                                     \
        "mov    r7, psr                 \n"                                                                     \
        "std    r6, [r1] +  56          \n"                                                                     \
        "movhi  r2, #16384              \n"         /* Set the pointer to the IC. */                            \
        "ldub   r3, [r2] + 2            \n"         /* Load the current interrupt mask. */                      \
        "st     r3, [r1]+ 64            \n"         /* Store the interrupt mask on the stack. */                \
        "ld     r2, [r0]+short(pxCurrentTCB)    \n" /* Load the pointer to the TCB. */                          \
        "st     r1, [r2]                \n"         /* Save the stack pointer into the TCB. */                  \
        "mov    r14, r1                 \n"         /* Compiler expects r14 to be set to the function stack. */ \
    );
/*---------------------------------------------------------------------------*/

#నిర్వచించు పోర్టు_RESTORE_CONTEXT()                                                                                 \
    asm __volatile__ (                                                                                        \
        "ld     r2, [r0]+short(pxCurrentTCB)    \n" /* Load the TCB to find the stack pointer and context. */ \
        "ld     r1, [r2]                \n"                                                                   \
        "movhi  r2, #16384              \n"         /* Set the pointer to the IC. */                          \
        "ld     r3, [r1] + 64           \n"         /* Load the previous interrupt mask. */                   \
        "stb    r3, [r2] + 2            \n"         /* Set the current interrupt mask to be the previous. */  \
        "ldd    r6, [r1] + 56           \n"         /* Restore context. */                                    \
        "mov    rtt, r6                 \n"                                                                   \
        "mov    psr, r7                 \n"                                                                   \
        "ldd    r2, [r1] + 0            \n"                                                                   \
        "ldq    r4, [r1] +  8           \n"                                                                   \
        "ldq    r8, [r1] +  24          \n"                                                                   \
        "ldq    r12, [r1] + 40          \n"                                                                   \
        "add    r1, #68                 \n"                                                                   \
        "rti                            \n"                                                                   \
        );

/*---------------------------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
#నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )
/*---------------------------------------------------------------------------*/

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
