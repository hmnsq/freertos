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

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
/* *INDENT-ON* */

#ضمن <machine/cpu.h>

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
#تعریف_کړه پورټ_CHAR          حرف
#تعریف_کړه پورټ_FLOAT         عائم
#تعریف_کړه پورټ_DOUBLE        مزدوج
#تعریف_کړه پورټ_LONG          اوږد
#تعریف_کړه پورټ_SHORT         لنډ
#تعریف_کړه پورټ_ډېری_TYPE    uint32_t
#تعریف_کړه پورټ_بنسټ_TYPE     اوږد

تعريفنوع پورټ_ډېری_TYPE   ډېری_Type_t;
تعريفنوع اوږد             بنسټ_Type_t;
تعريفنوع بینښه اوږد    UBaseType_t;

#إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
    تعريفنوع uint16_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffff
#وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
    تعريفنوع uint32_t     TickType_t;
    #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#وإلا
    #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
#د_که_پای
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#تعریف_کړه پورټ_ډېری_GROWTH               ( -1 )
#تعریف_کړه پورټ_TICK_PERIOD_MS             ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
#تعریف_کړه پورټ_BYTE_ALIGNMENT             4
#تعریف_کړه پورټ_NOP()    __asm__ متطاير ( "mov r0, r0" )
#تعریف_کړه پورټ_CRITICAL_NESTING_دننه_TCB    1
#تعریف_کړه پورټ_IRQ_TRAP_YIELD             31
/*-----------------------------------------------------------*/

/* Task utilities. */

خارجي فراغ v_پورټ_Yield( فراغ );

/*---------------------------------------------------------------------------*/

#تعریف_کړه پورټ_YIELD()    asm __volatile__ ( " trap #%0 " : : "i" ( پورټ_IRQ_TRAP_YIELD ) : "memory" )
/*---------------------------------------------------------------------------*/

خارجي فراغ vTaskEnterCritical( فراغ );
خارجي فراغ vTaskExitCritical( فراغ );
#تعریف_کړه پورټ_ENTER_CRITICAL()    vTaskEnterCritical()
#تعریف_کړه پورټ_EXIT_CRITICAL()     vTaskExitCritical()
/*---------------------------------------------------------------------------*/

/* Critical section management. */
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    cpu_int_disable()
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     cpu_int_enable()

/*---------------------------------------------------------------------------*/

#تعریف_کړه پورټ_YIELD_FROM_ISR( x_Higher_لومړیتوب_Task_Woken )    افعل { إذا( x_Higher_لومړیتوب_Task_Woken != pdFALSE ) vTaskSwitchContext( ); } طالما( 0 )

/*---------------------------------------------------------------------------*/

#تعریف_کړه پورټ_SAVE_CONTEXT()                                                                                      \
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

#تعریف_کړه پورټ_RESTORE_CONTEXT()                                                                                 \
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
#تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
#تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )
/*---------------------------------------------------------------------------*/

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
