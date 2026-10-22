/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT AND BSD-3-Clause
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

/*This file has been prepared for Doxygen automatic documentation generation.*/

/*! \file *********************************************************************
 *
 * \brief FreeRTOS port header for AVR32 UC3.
 *
 * - Compiler:           IAR EWAVR32
 * - Supported devices:  All AVR32 devices can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation (Now Microchip):
 *                                        https://www.microchip.com
 *                       Support and FAQ: https://www.microchip.com/support
 *
 *****************************************************************************/

/*
 * Copyright (c) 2007, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */



#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */
#समावेश <avr32/io.h>
#समावेश "intc.h"
#समावेश "compiler.h"

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
/* *INDENT-ON* */


/* Type definitions. */
#घोषणा portCHAR          अक्षर
#घोषणा portFLOAT         भग्न
#घोषणा portDOUBLE        द्विगुन
#घोषणा portLONG          दीर्घ
#घोषणा portSHORT         लघु
#घोषणा port_ढेर_TYPE    uint32_t
#घोषणा portBASE_TYPE     दीर्घ

प्रकार port_ढेर_TYPE   ढेर_Type_t;
प्रकार दीर्घ             BaseType_t;
प्रकार अचिन्हित दीर्घ    UBaseType_t;


#घोषणा TASK_DELAY_MS( x )     ( ( x ) / portTICK_PERIOD_MS )
#घोषणा TASK_DELAY_S( x )      ( ( x ) * 1000 / portTICK_PERIOD_MS )
#घोषणा TASK_DELAY_MIN( x )    ( ( x ) * 60 * 1000 / portTICK_PERIOD_MS )

#घोषणा configTICK_TC_IRQ    ATPASTE2( AVR32_TC_IRQ, configTICK_TC_CHANNEL )

#अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
    प्रकार uint16_t   TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) 0xffff
#या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
    प्रकार uint32_t   TickType_t;
    #घोषणा portMAX_DELAY    ( TickType_t ) ( 0xFFFFFFFFUL )
#अन्यथा
    #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
#पूर्ण_अगर
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#घोषणा port_ढेर_GROWTH      ( -1 )
#घोषणा portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#घोषणा portBYTE_ALIGNMENT    4
#घोषणा portNOP()    { __asm__ __volatile__ ( "nop" ); }
/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/

/* INTC-specific. */
#घोषणा DISABLE_ALL_EXCEPTIONS()        Disable_global_exception()
#घोषणा ENABLE_ALL_EXCEPTIONS()         Enable_global_exception()

#घोषणा DISABLE_ALL_INTERRUPTS()        Disable_global_interrupt()
#घोषणा ENABLE_ALL_INTERRUPTS()         Enable_global_interrupt()

#घोषणा DISABLE_INT_LEVEL( int_lev )    Disable_interrupt_level( int_lev )
#घोषणा ENABLE_INT_LEVEL( int_lev )     Enable_interrupt_level( int_lev )


/*
 * Debug trace.
 * Activated if and only if configDBG is nonzero.
 * Prints a formatted string to stdout.
 * The current source file name and line number are output with a colon before
 * the formatted string.
 * A carriage return and a linefeed are appended to the output.
 * stdout is redirected to the USART configured by configDBG_USART.
 * The parameters are the same as for the standard printf function.
 * There is no return value.
 * SHALL NOT BE CALLED FROM WITHIN AN INTERRUPT as fputs and printf use malloc,
 * which is interrupt-unsafe with the current __malloc_lock and __malloc_unlock.
 */
#अगर configDBG
    #घोषणा portDBG_TRACE( ... )                                 \
    {                                                            \
        ख_माला_दो( __खाता__ ":" ASTRINGZ( __LINE__ ) ": ", मानक_निकास ); \
        म_लिखो( __VA_ARGS__ );                                   \
        ख_माला_दो( "\r\n", मानक_निकास );                                 \
    }
#अन्यथा
    #घोषणा portDBG_TRACE( ... )
#पूर्ण_अगर


/* Critical section management. */
#घोषणा portDISABLE_INTERRUPTS()    DISABLE_ALL_INTERRUPTS()
#घोषणा portENABLE_INTERRUPTS()     ENABLE_ALL_INTERRUPTS()


बाह्य व्योम vPortEnterCritical( व्योम );
बाह्य व्योम vPortExitCritical( व्योम );

#घोषणा portENTER_CRITICAL()    vPortEnterCritical();
#घोषणा portEXIT_CRITICAL()     vPortExitCritical();


/* Added as there is no such function in FreeRTOS. */
बाह्य व्योम * pvPortRealloc( व्योम * pv,
                             माप_प्रकार x_आकार );
/*-----------------------------------------------------------*/


/*=============================================================================================*/

/*
 * Restore Context for cases other than INTi.
 */
#घोषणा portRESTORE_CONTEXT()                                                                                                                                                                                                                                                                                                                    \
    {                                                                                                                                                                                                                                                                                                                                            \
        बाह्य अस्थिर uint32_t ulCriticalNesting;                                                                                                                                                                                                                                                                                              \
        बाह्य अस्थिर व्योम * अस्थिर pxCurrentTCB;                                                                                                                                                                                                                                                                                            \
                                                                                                                                                                                                                                                                                                                                                 \
        __asm__ __volatile__ (                                                                                                                                                                                                                                                                                                                   \
            /* Set SP to point to new stack */                                                                                                                                                                                                                                                                                                   \
            "mov     r8, LWRD("ASTRINGZ ( pxCurrentTCB ) ")                                             \n\t"                                                                                                                                                                                                                                    \
                                                         "orh     r8, HWRD("ASTRINGZ ( pxCurrentTCB ) ")                                             \n\t"                                                                                                                                                                                       \
                                                                                                      "ld.w    r0, r8[0]                                                                      \n\t"                                                                                                                                              \
                                                                                                      "ld.w    sp, r0[0]                                                                      \n\t"                                                                                                                                              \
                                                                                                                                                                                                                                                                                                                                                 \
            /* Restore ulCriticalNesting variable */                                                                                                                                                                                                                                                                                             \
                                                                                                      "ld.w    r0, sp++                                                                       \n\t"                                                                                                                                              \
                                                                                                      "mov     r8, LWRD("ASTRINGZ ( ulCriticalNesting ) ")                                        \n\t"                                                                                                                                          \
                                                                                                                                                        "orh     r8, HWRD("ASTRINGZ ( ulCriticalNesting ) ")                                        \n\t"                                                                                        \
                                                                                                                                                                                                          "st.w    r8[0], r0                                                                      \n\t"                                          \
                                                                                                                                                                                                                                                                                                                                                 \
            /* Restore R0..R7 */                                                                                                                                                                                                                                                                                                                 \
                                                                                                                                                                                                          "ldm     sp++, r0-r7                                                                    \n\t"                                          \
            /* R0-R7 should not be used below this line */                                                                                                                                                                                                                                                                                       \
            /* Skip PC and SR (will do it at the end) */                                                                                                                                                                                                                                                                                         \
                                                                                                                                                                                                          "sub     sp, -2*4                                                                       \n\t"                                          \
            /* Restore R8..R12 and LR */                                                                                                                                                                                                                                                                                                         \
                                                                                                                                                                                                          "ldm     sp++, r8-r12, lr                                                               \n\t"                                          \
            /* Restore SR */                                                                                                                                                                                                                                                                                                                     \
                                                                                                                                                                                                          "ld.w    r0, sp[-8*4]                                                                   \n\t" /* R0 is modified, is restored later. */ \
                                                                                                                                                                                                          "mtsr    "ASTRINGZ ( AVR32_SR ) ", r0                                                       \n\t"                                      \
            /* Restore r0 */                                                                                                                                                                                                                                                                                                                     \
                                                                                                                                                                                                                                          "ld.w    r0, sp[-9*4]                                                                   \n\t"          \
            /* Restore PC */                                                                                                                                                                                                                                                                                                                     \
                                                                                                                                                                                                                                          "ld.w    pc, sp[-7*4]" /* Get PC from stack - PC is the 7th register saved */                          \
            );                                                                                                                                                                                                                                                                                                                                   \
                                                                                                                                                                                                                                                                                                                                                 \
        /* Force import of global symbols from assembly */                                                                                                                                                                                                                                                                                       \
        ulCriticalNesting;                                                                                                                                                                                                                                                                                                                       \
        pxCurrentTCB;                                                                                                                                                                                                                                                                                                                            \
    }


/*
 * portSAVE_CONTEXT_INT() and portRESTORE_CONTEXT_INT(): for INT0..3 exceptions.
 * portSAVE_CONTEXT_SCALL() and portRESTORE_CONTEXT_SCALL(): for the scall exception.
 *
 * Had to make different versions because registers saved on the system stack
 * are not the same between INT0..3 exceptions and the scall exception.
 */

/* Task context stack layout: */
/* R8  (*) */
/* R9  (*) */
/* R10 (*) */
/* R11 (*) */
/* R12 (*) */
/* R14/LR (*) */
/* R15/PC (*) */
/* SR (*) */
/* R0 */
/* R1 */
/* R2 */
/* R3 */
/* R4 */
/* R5 */
/* R6 */
/* R7 */
/* ulCriticalNesting */
/* (*) automatically done for INT0..INT3, but not for SCALL */

/*
 * The ISR used for the scheduler tick depends on whether the cooperative or
 * the preemptive scheduler is being used.
 */
#अगर configUSE_PREEMPTION == 0

/*
 * portSAVE_CONTEXT_OS_INT() for OS Tick exception.
 */
    #घोषणा portSAVE_CONTEXT_OS_INT()                                                     \
    {                                                                                     \
        /* Save R0..R7 */                                                                 \
        __asm__ __volatile__ ( "stm     --sp, r0-r7" );                                   \
                                                                                          \
        /* With the cooperative scheduler, as there is no context switch by interrupt, */ \
        /* there is also no context save. */                                              \
    }

/*
 * portRESTORE_CONTEXT_OS_INT() for Tick exception.
 */
    #घोषणा portRESTORE_CONTEXT_OS_INT()                                                                  \
    {                                                                                                     \
        __asm__ __volatile__ (                                                                            \
            /* Restore R0..R7 */                                                                          \
            "ldm     sp++, r0-r7                                                                    \n\t" \
                                                                                                          \
            /* With the cooperative scheduler, as there is no context switch by interrupt, */             \
            /* there is also no context restore. */                                                       \
            "rete"                                                                                        \
            );                                                                                            \
    }

#अन्यथा /* if configUSE_PREEMPTION == 0 */

/*
 * portSAVE_CONTEXT_OS_INT() for OS Tick exception.
 */
    #घोषणा portSAVE_CONTEXT_OS_INT()                                                                                                                                                                                                                                                                                                                                       \
    {                                                                                                                                                                                                                                                                                                                                                                       \
        बाह्य अस्थिर uint32_t ulCriticalNesting;                                                                                                                                                                                                                                                                                                                         \
        बाह्य अस्थिर व्योम * अस्थिर pxCurrentTCB;                                                                                                                                                                                                                                                                                                                       \
                                                                                                                                                                                                                                                                                                                                                                            \
        /* When we come here */                                                                                                                                                                                                                                                                                                                                             \
        /* Registers R8..R12, LR, PC and SR had already been pushed to system stack */                                                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                                                                                                                                            \
        __asm__ __volatile__ (                                                                                                                                                                                                                                                                                                                                              \
            /* Save R0..R7 */                                                                                                                                                                                                                                                                                                                                               \
            "stm     --sp, r0-r7                                                                            \n\t"                                                                                                                                                                                                                                                           \
                                                                                                                                                                                                                                                                                                                                                                            \
            /* Save ulCriticalNesting variable  - R0 is overwritten */                                                                                                                                                                                                                                                                                                      \
            "mov     r8, LWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                                                                                                                                                                                                                                       \
                                                              "orh     r8, HWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                                                                                                                                                                                     \
                                                                                                                "ld.w    r0, r8[0]                                                                              \n\t"                                                                                                                                                       \
                                                                                                                "st.w    --sp, r0                                                                               \n\t"                                                                                                                                                       \
                                                                                                                                                                                                                                                                                                                                                                            \
            /* Check if INT0 or higher were being handled (case where the OS tick interrupted another */                                                                                                                                                                                                                                                                    \
            /* interrupt handler (which was of a higher priority level but decided to lower its priority */                                                                                                                                                                                                                                                                 \
            /* level and allow other lower interrupt level to occur). */                                                                                                                                                                                                                                                                                                    \
            /* In this case we don't want to do a task switch because we don't know what the stack */                                                                                                                                                                                                                                                                       \
            /* currently looks like (we don't know what the interrupted interrupt handler was doing). */                                                                                                                                                                                                                                                                    \
            /* Saving SP in pxCurrentTCB and then later restoring it (thinking restoring the task) */                                                                                                                                                                                                                                                                       \
            /* will just be restoring the interrupt handler, no way!!! */                                                                                                                                                                                                                                                                                                   \
            /* So, since we won't do a vTaskSwitchContext(), it's of no use to save SP. */                                                                                                                                                                                                                                                                                  \
                                                                                                                "ld.w    r0, sp[9*4]                                                                            \n\t" /* Read SR in stack */                                                                                                                                \
                                                                                                                "bfextu  r0, r0, 22, 3                                                                          \n\t" /* Extract the mode bits to R0. */                                                                                                                    \
                                                                                                                "cp.w    r0, 1                                                                                  \n\t" /* Compare the mode bits with supervisor mode(b'001) */                                                                                               \
                                                                                                                "brhi    LABEL_INT_SKIP_SAVE_CONTEXT_"ASTRINGZ ( __LINE__ ) "                                       \n\t"                                                                                                                                                   \
                                                                                                                                                                                                                                                                                                                                                                            \
            /* Store SP in the first member of the structure pointed to by pxCurrentTCB */                                                                                                                                                                                                                                                                                  \
            /* NOTE: we don't enter a critical section here because all interrupt handlers */                                                                                                                                                                                                                                                                               \
            /* MUST perform a SAVE_CONTEXT/RESTORE_CONTEXT in the same way as */                                                                                                                                                                                                                                                                                            \
            /* portSAVE_CONTEXT_OS_INT/port_RESTORE_CONTEXT_OS_INT if they call OS functions. */                                                                                                                                                                                                                                                                            \
            /* => all interrupt handlers must use portENTER_SWITCHING_ISR/portEXIT_SWITCHING_ISR. */                                                                                                                                                                                                                                                                        \
                                                                                                                                                                            "mov     r8, LWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                                                                       \
                                                                                                                                                                                                                         "orh     r8, HWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                          \
                                                                                                                                                                                                                                                                      "ld.w    r0, r8[0]                                                                              \n\t" \
                                                                                                                                                                                                                                                                      "st.w    r0[0], sp                                                                              \n"   \
                                                                                                                                                                                                                                                                                                                                                                            \
                                                                                                                                                                                                                                                                      "LABEL_INT_SKIP_SAVE_CONTEXT_"ASTRINGZ ( __LINE__ ) ":"                                               \
            );                                                                                                                                                                                                                                                                                                                                                              \
    }

/*
 * portRESTORE_CONTEXT_OS_INT() for Tick exception.
 */
    #घोषणा portRESTORE_CONTEXT_OS_INT()                                                                                                                                                                                                                                                                                                                               \
    {                                                                                                                                                                                                                                                                                                                                                                  \
        बाह्य अस्थिर uint32_t ulCriticalNesting;                                                                                                                                                                                                                                                                                                                    \
        बाह्य अस्थिर व्योम * अस्थिर pxCurrentTCB;                                                                                                                                                                                                                                                                                                                  \
                                                                                                                                                                                                                                                                                                                                                                       \
        /* Check if INT0 or higher were being handled (case where the OS tick interrupted another */                                                                                                                                                                                                                                                                   \
        /* interrupt handler (which was of a higher priority level but decided to lower its priority */                                                                                                                                                                                                                                                                \
        /* level and allow other lower interrupt level to occur). */                                                                                                                                                                                                                                                                                                   \
        /* In this case we don't want to do a task switch because we don't know what the stack */                                                                                                                                                                                                                                                                      \
        /* currently looks like (we don't know what the interrupted interrupt handler was doing). */                                                                                                                                                                                                                                                                   \
        /* Saving SP in pxCurrentTCB and then later restoring it (thinking restoring the task) */                                                                                                                                                                                                                                                                      \
        /* will just be restoring the interrupt handler, no way!!! */                                                                                                                                                                                                                                                                                                  \
        __asm__ __volatile__ (                                                                                                                                                                                                                                                                                                                                         \
            "ld.w    r0, sp[9*4]                                                                            \n\t" /* Read SR in stack */                                                                                                                                                                                                                               \
            "bfextu  r0, r0, 22, 3                                                                          \n\t" /* Extract the mode bits to R0. */                                                                                                                                                                                                                   \
            "cp.w    r0, 1                                                                                  \n\t" /* Compare the mode bits with supervisor mode(b'001) */                                                                                                                                                                                              \
            "brhi    LABEL_INT_SKIP_RESTORE_CONTEXT_"ASTRINGZ ( __LINE__ )                                                                                                                                                                                                                                                                                             \
            );                                                                                                                                                                                                                                                                                                                                                         \
                                                                                                                                                                                                                                                                                                                                                                       \
        /* Else */                                                                                                                                                                                                                                                                                                                                                     \
        /* because it is here safe, always call vTaskSwitchContext() since an OS tick occurred. */                                                                                                                                                                                                                                                                     \
        /* A critical section has to be used here because vTaskSwitchContext handles FreeRTOS linked lists. */                                                                                                                                                                                                                                                         \
        portENTER_CRITICAL();                                                                                                                                                                                                                                                                                                                                          \
        vTaskSwitchContext();                                                                                                                                                                                                                                                                                                                                          \
        portEXIT_CRITICAL();                                                                                                                                                                                                                                                                                                                                           \
                                                                                                                                                                                                                                                                                                                                                                       \
        /* Restore all registers */                                                                                                                                                                                                                                                                                                                                    \
                                                                                                                                                                                                                                                                                                                                                                       \
        __asm__ __volatile__ (                                                                                                                                                                                                                                                                                                                                         \
            /* Set SP to point to new stack */                                                                                                                                                                                                                                                                                                                         \
            "mov     r8, LWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                                                                                                                                                                                                                                  \
                                                         "orh     r8, HWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                                                                                                                                                                                     \
                                                                                                      "ld.w    r0, r8[0]                                                                              \n\t"                                                                                                                                                            \
                                                                                                      "ld.w    sp, r0[0]                                                                              \n"                                                                                                                                                              \
                                                                                                                                                                                                                                                                                                                                                                       \
                                                                                                      "LABEL_INT_SKIP_RESTORE_CONTEXT_"ASTRINGZ ( __LINE__ ) ":                                           \n\t"                                                                                                                                                        \
                                                                                                                                                                                                                                                                                                                                                                       \
            /* Restore ulCriticalNesting variable */                                                                                                                                                                                                                                                                                                                   \
                                                                                                                                                             "ld.w    r0, sp++                                                                               \n\t"                                                                                                     \
                                                                                                                                                             "mov     r8, LWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                                                                                 \
                                                                                                                                                                                                               "orh     r8, HWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                               \
                                                                                                                                                                                                                                                                 "st.w    r8[0], r0                                                                              \n\t" \
                                                                                                                                                                                                                                                                                                                                                                       \
            /* Restore R0..R7 */                                                                                                                                                                                                                                                                                                                                       \
                                                                                                                                                                                                                                                                 "ldm     sp++, r0-r7                                                                            \n\t" \
                                                                                                                                                                                                                                                                                                                                                                       \
            /* Now, the stack should be R8..R12, LR, PC and SR */                                                                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                                 "rete"                                                                                                \
            );                                                                                                                                                                                                                                                                                                                                                         \
                                                                                                                                                                                                                                                                                                                                                                       \
        /* Force import of global symbols from assembly */                                                                                                                                                                                                                                                                                                             \
        ulCriticalNesting;                                                                                                                                                                                                                                                                                                                                             \
        pxCurrentTCB;                                                                                                                                                                                                                                                                                                                                                  \
    }

#पूर्ण_अगर /* if configUSE_PREEMPTION == 0 */


/*
 * portSAVE_CONTEXT_SCALL() for SupervisorCALL exception.
 *
 * NOTE: taskYIELD()(== SCALL) MUST NOT be called in a mode > supervisor mode.
 *
 */
#घोषणा portSAVE_CONTEXT_SCALL()                                                                                                                                                                                      \
    {                                                                                                                                                                                                                 \
        बाह्य अस्थिर uint32_t ulCriticalNesting;                                                                                                                                                                   \
        बाह्य अस्थिर व्योम * अस्थिर pxCurrentTCB;                                                                                                                                                                 \
                                                                                                                                                                                                                      \
        /* Warning: the stack layout after SCALL doesn't match the one after an interrupt. */                                                                                                                         \
        /* If SR[M2:M0] == 001 */                                                                                                                                                                                     \
        /*    PC and SR are on the stack.  */                                                                                                                                                                         \
        /* Else (other modes) */                                                                                                                                                                                      \
        /*    Nothing on the stack. */                                                                                                                                                                                \
                                                                                                                                                                                                                      \
        /* WARNING NOTE: the else case cannot happen as it is strictly forbidden to call */                                                                                                                           \
        /* vTaskDelay() and vTaskDelayUntil() OS functions (that result in a taskYield()) */                                                                                                                          \
        /* in an interrupt|exception handler. */                                                                                                                                                                      \
                                                                                                                                                                                                                      \
        __asm__ __volatile__ (                                                                                                                                                                                        \
            /* in order to save R0-R7 */                                                                                                                                                                              \
            "sub     sp, 6*4                                                                                \n\t"                                                                                                     \
            /* Save R0..R7 */                                                                                                                                                                                         \
            "stm     --sp, r0-r7                                                                            \n\t"                                                                                                     \
                                                                                                                                                                                                                      \
            /* in order to save R8-R12 and LR */                                                                                                                                                                      \
            /* do not use SP if interrupts occurs, SP must be left at bottom of stack */                                                                                                                              \
            "sub     r7, sp,-16*4                                                                           \n\t"                                                                                                     \
            /* Copy PC and SR in other places in the stack. */                                                                                                                                                        \
            "ld.w    r0, r7[-2*4]                                                                           \n\t" /* Read SR */                                                                                       \
            "st.w    r7[-8*4], r0                                                                           \n\t" /* Copy SR */                                                                                       \
            "ld.w    r0, r7[-1*4]                                                                           \n\t" /* Read PC */                                                                                       \
            "st.w    r7[-7*4], r0                                                                           \n\t" /* Copy PC */                                                                                       \
                                                                                                                                                                                                                      \
            /* Save R8..R12 and LR on the stack. */                                                                                                                                                                   \
            "stm     --r7, r8-r12, lr                                                                       \n\t"                                                                                                     \
                                                                                                                                                                                                                      \
            /* Arriving here we have the following stack organizations: */                                                                                                                                            \
            /* R8..R12, LR, PC, SR, R0..R7. */                                                                                                                                                                        \
                                                                                                                                                                                                                      \
            /* Now we can finalize the save. */                                                                                                                                                                       \
                                                                                                                                                                                                                      \
            /* Save ulCriticalNesting variable  - R0 is overwritten */                                                                                                                                                \
            "mov     r8, LWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                                                                                 \
                                                              "orh     r8, HWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                               \
                                                                                                                "ld.w    r0, r8[0]                                                                              \n\t" \
                                                                                                                "st.w    --sp, r0"                                                                                    \
            );                                                                                                                                                                                                        \
                                                                                                                                                                                                                      \
        /* Disable the its which may cause a context switch (i.e. cause a change of */                                                                                                                                \
        /* pxCurrentTCB). */                                                                                                                                                                                          \
        /* Basically, all accesses to the pxCurrentTCB structure should be put in a */                                                                                                                                \
        /* critical section because it is a global structure. */                                                                                                                                                      \
        portENTER_CRITICAL();                                                                                                                                                                                         \
                                                                                                                                                                                                                      \
        /* Store SP in the first member of the structure pointed to by pxCurrentTCB */                                                                                                                                \
        __asm__ __volatile__ (                                                                                                                                                                                        \
            "mov     r8, LWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                                                                                 \
                                                         "orh     r8, HWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                                    \
                                                                                                      "ld.w    r0, r8[0]                                                                              \n\t"           \
                                                                                                      "st.w    r0[0], sp"                                                                                             \
            );                                                                                                                                                                                                        \
    }

/*
 * portRESTORE_CONTEXT() for SupervisorCALL exception.
 */
#घोषणा portRESTORE_CONTEXT_SCALL()                                                                                                                                                                                                 \
    {                                                                                                                                                                                                                               \
        बाह्य अस्थिर uint32_t ulCriticalNesting;                                                                                                                                                                                 \
        बाह्य अस्थिर व्योम * अस्थिर pxCurrentTCB;                                                                                                                                                                               \
                                                                                                                                                                                                                                    \
        /* Restore all registers */                                                                                                                                                                                                 \
                                                                                                                                                                                                                                    \
        /* Set SP to point to new stack */                                                                                                                                                                                          \
        __asm__ __volatile__ (                                                                                                                                                                                                      \
            "mov     r8, LWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                                                                                               \
                                                         "orh     r8, HWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                                                  \
                                                                                                      "ld.w    r0, r8[0]                                                                              \n\t"                         \
                                                                                                      "ld.w    sp, r0[0]"                                                                                                           \
            );                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                    \
        /* Leave pxCurrentTCB variable access critical section */                                                                                                                                                                   \
        portEXIT_CRITICAL();                                                                                                                                                                                                        \
                                                                                                                                                                                                                                    \
        __asm__ __volatile__ (                                                                                                                                                                                                      \
            /* Restore ulCriticalNesting variable */                                                                                                                                                                                \
            "ld.w    r0, sp++                                                                               \n\t"                                                                                                                   \
            "mov     r8, LWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                                                                                               \
                                                              "orh     r8, HWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                                             \
                                                                                                                "st.w    r8[0], r0                                                                              \n\t"               \
                                                                                                                                                                                                                                    \
            /* skip PC and SR */                                                                                                                                                                                                    \
            /* do not use SP if interrupts occurs, SP must be left at bottom of stack */                                                                                                                                            \
                                                                                                                "sub     r7, sp, -10*4                                                                          \n\t"               \
            /* Restore r8-r12 and LR */                                                                                                                                                                                             \
                                                                                                                "ldm     r7++, r8-r12, lr                                                                       \n\t"               \
                                                                                                                                                                                                                                    \
            /* RETS will take care of the extra PC and SR restore. */                                                                                                                                                               \
            /* So, we have to prepare the stack for this. */                                                                                                                                                                        \
                                                                                                                "ld.w    r0, r7[-8*4]                                                                           \n\t" /* Read SR */ \
                                                                                                                "st.w    r7[-2*4], r0                                                                           \n\t" /* Copy SR */ \
                                                                                                                "ld.w    r0, r7[-7*4]                                                                           \n\t" /* Read PC */ \
                                                                                                                "st.w    r7[-1*4], r0                                                                           \n\t" /* Copy PC */ \
                                                                                                                                                                                                                                    \
            /* Restore R0..R7 */                                                                                                                                                                                                    \
                                                                                                                "ldm     sp++, r0-r7                                                                            \n\t"               \
                                                                                                                                                                                                                                    \
                                                                                                                "sub     sp, -6*4                                                                               \n\t"               \
                                                                                                                                                                                                                                    \
                                                                                                                "rets"                                                                                                              \
            );                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                    \
        /* Force import of global symbols from assembly */                                                                                                                                                                          \
        ulCriticalNesting;                                                                                                                                                                                                          \
        pxCurrentTCB;                                                                                                                                                                                                               \
    }


/*
 * The ISR used depends on whether the cooperative or
 * the preemptive scheduler is being used.
 */
#अगर configUSE_PREEMPTION == 0

/*
 * ISR entry and exit macros.  These are only required if a task switch
 * is required from the ISR.
 */
    #घोषणा portENTER_SWITCHING_ISR()                                                     \
    {                                                                                     \
        /* Save R0..R7 */                                                                 \
        __asm__ __volatile__ ( "stm     --sp, r0-r7" );                                   \
                                                                                          \
        /* With the cooperative scheduler, as there is no context switch by interrupt, */ \
        /* there is also no context save. */                                              \
    }

/*
 * Input parameter: in R12, boolean. Perform a vTaskSwitchContext() if 1
 */
    #घोषणा portEXIT_SWITCHING_ISR()                                                                              \
    {                                                                                                             \
        __asm__ __volatile__ (                                                                                    \
            /* Restore R0..R7 */                                                                                  \
            "ldm     sp++, r0-r7                                                                            \n\t" \
                                                                                                                  \
            /* With the cooperative scheduler, as there is no context switch by interrupt, */                     \
            /* there is also no context restore. */                                                               \
            "rete"                                                                                                \
            );                                                                                                    \
    }

#अन्यथा /* if configUSE_PREEMPTION == 0 */

/*
 * ISR entry and exit macros.  These are only required if a task switch
 * is required from the ISR.
 */
    #घोषणा portENTER_SWITCHING_ISR()                                                                                                                                                                                                                                                                                                                                       \
    {                                                                                                                                                                                                                                                                                                                                                                       \
        बाह्य अस्थिर uint32_t ulCriticalNesting;                                                                                                                                                                                                                                                                                                                         \
        बाह्य अस्थिर व्योम * अस्थिर pxCurrentTCB;                                                                                                                                                                                                                                                                                                                       \
                                                                                                                                                                                                                                                                                                                                                                            \
        /* When we come here */                                                                                                                                                                                                                                                                                                                                             \
        /* Registers R8..R12, LR, PC and SR had already been pushed to system stack */                                                                                                                                                                                                                                                                                      \
                                                                                                                                                                                                                                                                                                                                                                            \
        __asm__ __volatile__ (                                                                                                                                                                                                                                                                                                                                              \
            /* Save R0..R7 */                                                                                                                                                                                                                                                                                                                                               \
            "stm     --sp, r0-r7                                                                            \n\t"                                                                                                                                                                                                                                                           \
                                                                                                                                                                                                                                                                                                                                                                            \
            /* Save ulCriticalNesting variable  - R0 is overwritten */                                                                                                                                                                                                                                                                                                      \
            "mov     r8, LWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                                                                                                                                                                                                                                       \
                                                              "orh     r8, HWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                                                                                                                                                                                     \
                                                                                                                "ld.w    r0, r8[0]                                                                              \n\t"                                                                                                                                                       \
                                                                                                                "st.w    --sp, r0                                                                               \n\t"                                                                                                                                                       \
                                                                                                                                                                                                                                                                                                                                                                            \
            /* Check if INT0 or higher were being handled (case where the OS tick interrupted another */                                                                                                                                                                                                                                                                    \
            /* interrupt handler (which was of a higher priority level but decided to lower its priority */                                                                                                                                                                                                                                                                 \
            /* level and allow other lower interrupt level to occur). */                                                                                                                                                                                                                                                                                                    \
            /* In this case we don't want to do a task switch because we don't know what the stack */                                                                                                                                                                                                                                                                       \
            /* currently looks like (we don't know what the interrupted interrupt handler was doing). */                                                                                                                                                                                                                                                                    \
            /* Saving SP in pxCurrentTCB and then later restoring it (thinking restoring the task) */                                                                                                                                                                                                                                                                       \
            /* will just be restoring the interrupt handler, no way!!! */                                                                                                                                                                                                                                                                                                   \
            /* So, since we won't do a vTaskSwitchContext(), it's of no use to save SP. */                                                                                                                                                                                                                                                                                  \
                                                                                                                "ld.w    r0, sp[9*4]                                                                            \n\t" /* Read SR in stack */                                                                                                                                \
                                                                                                                "bfextu  r0, r0, 22, 3                                                                          \n\t" /* Extract the mode bits to R0. */                                                                                                                    \
                                                                                                                "cp.w    r0, 1                                                                                  \n\t" /* Compare the mode bits with supervisor mode(b'001) */                                                                                               \
                                                                                                                "brhi    LABEL_ISR_SKIP_SAVE_CONTEXT_"ASTRINGZ ( __LINE__ ) "                                       \n\t"                                                                                                                                                   \
                                                                                                                                                                                                                                                                                                                                                                            \
            /* Store SP in the first member of the structure pointed to by pxCurrentTCB */                                                                                                                                                                                                                                                                                  \
                                                                                                                                                                            "mov     r8, LWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                                                                       \
                                                                                                                                                                                                                         "orh     r8, HWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                          \
                                                                                                                                                                                                                                                                      "ld.w    r0, r8[0]                                                                              \n\t" \
                                                                                                                                                                                                                                                                      "st.w    r0[0], sp                                                                              \n"   \
                                                                                                                                                                                                                                                                                                                                                                            \
                                                                                                                                                                                                                                                                      "LABEL_ISR_SKIP_SAVE_CONTEXT_"ASTRINGZ ( __LINE__ ) ":"                                               \
            );                                                                                                                                                                                                                                                                                                                                                              \
    }


/*
 * Input parameter: in R12, boolean. Perform a vTaskSwitchContext() if 1
 */
    #घोषणा portEXIT_SWITCHING_ISR()                                                                                                                                                                                                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                                                                                                                                                                                                    \
        बाह्य अस्थिर uint32_t ulCriticalNesting;                                                                                                                                                                                                                                                                                                                                                                      \
        बाह्य अस्थिर व्योम * अस्थिर pxCurrentTCB;                                                                                                                                                                                                                                                                                                                                                                    \
                                                                                                                                                                                                                                                                                                                                                                                                                         \
        __asm__ __volatile__ (                                                                                                                                                                                                                                                                                                                                                                                           \
            /* Check if INT0 or higher were being handled (case where the OS tick interrupted another */                                                                                                                                                                                                                                                                                                                 \
            /* interrupt handler (which was of a higher priority level but decided to lower its priority */                                                                                                                                                                                                                                                                                                              \
            /* level and allow other lower interrupt level to occur). */                                                                                                                                                                                                                                                                                                                                                 \
            /* In this case it's of no use to switch context and restore a new SP because we purposely */                                                                                                                                                                                                                                                                                                                \
            /* did not previously save SP in its TCB. */                                                                                                                                                                                                                                                                                                                                                                 \
            "ld.w    r0, sp[9*4]                                                                            \n\t" /* Read SR in stack */                                                                                                                                                                                                                                                                                 \
            "bfextu  r0, r0, 22, 3                                                                          \n\t" /* Extract the mode bits to R0. */                                                                                                                                                                                                                                                                     \
            "cp.w    r0, 1                                                                                  \n\t" /* Compare the mode bits with supervisor mode(b'001) */                                                                                                                                                                                                                                                \
            "brhi    LABEL_ISR_SKIP_RESTORE_CONTEXT_"ASTRINGZ ( __LINE__ ) "                                    \n\t"                                                                                                                                                                                                                                                                                                    \
                                                                                                                                                                                                                                                                                                                                                                                                                         \
            /* If a switch is required then we just need to call */                                                                                                                                                                                                                                                                                                                                                      \
            /* vTaskSwitchContext() as the context has already been */                                                                                                                                                                                                                                                                                                                                                   \
            /* saved. */                                                                                                                                                                                                                                                                                                                                                                                                 \
                                                                           "cp.w    r12, 1                                                                                 \n\t" /* Check if Switch context is required. */                                                                                                                                                                                              \
                                                                           "brne    LABEL_ISR_RESTORE_CONTEXT_"ASTRINGZ ( __LINE__ ) ":C"                                                                                                                                                                                                                                                                                \
            );                                                                                                                                                                                                                                                                                                                                                                                                           \
                                                                                                                                                                                                                                                                                                                                                                                                                         \
        /* A critical section has to be used here because vTaskSwitchContext handles FreeRTOS linked lists. */                                                                                                                                                                                                                                                                                                           \
        portENTER_CRITICAL();                                                                                                                                                                                                                                                                                                                                                                                            \
        vTaskSwitchContext();                                                                                                                                                                                                                                                                                                                                                                                            \
        portEXIT_CRITICAL();                                                                                                                                                                                                                                                                                                                                                                                             \
                                                                                                                                                                                                                                                                                                                                                                                                                         \
        __asm__ __volatile__ (                                                                                                                                                                                                                                                                                                                                                                                           \
            "LABEL_ISR_RESTORE_CONTEXT_"ASTRINGZ ( __LINE__ ) ":                                                \n\t"                                                                                                                                                                                                                                                                                                    \
            /* Restore the context of which ever task is now the highest */                                                                                                                                                                                                                                                                                                                                              \
            /* priority that is ready to run. */                                                                                                                                                                                                                                                                                                                                                                         \
                                                                                                                                                                                                                                                                                                                                                                                                                         \
            /* Restore all registers */                                                                                                                                                                                                                                                                                                                                                                                  \
                                                                                                                                                                                                                                                                                                                                                                                                                         \
            /* Set SP to point to new stack */                                                                                                                                                                                                                                                                                                                                                                           \
                                                              "mov     r8, LWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                                                                                                                                                                                                                                  \
                                                                                                           "orh     r8, HWRD("ASTRINGZ ( pxCurrentTCB ) ")                                                     \n\t"                                                                                                                                                                                                     \
                                                                                                                                                        "ld.w    r0, r8[0]                                                                              \n\t"                                                                                                                                                            \
                                                                                                                                                        "ld.w    sp, r0[0]                                                                              \n"                                                                                                                                                              \
                                                                                                                                                                                                                                                                                                                                                                                                                         \
                                                                                                                                                        "LABEL_ISR_SKIP_RESTORE_CONTEXT_"ASTRINGZ ( __LINE__ ) ":                                           \n\t"                                                                                                                                                        \
                                                                                                                                                                                                                                                                                                                                                                                                                         \
            /* Restore ulCriticalNesting variable */                                                                                                                                                                                                                                                                                                                                                                     \
                                                                                                                                                                                                               "ld.w    r0, sp++                                                                               \n\t"                                                                                                     \
                                                                                                                                                                                                               "mov     r8, LWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                                                                                 \
                                                                                                                                                                                                                                                                 "orh     r8, HWRD("ASTRINGZ ( ulCriticalNesting ) ")                                                \n\t"                                               \
                                                                                                                                                                                                                                                                                                                   "st.w    r8[0], r0                                                                              \n\t" \
                                                                                                                                                                                                                                                                                                                                                                                                                         \
            /* Restore R0..R7 */                                                                                                                                                                                                                                                                                                                                                                                         \
                                                                                                                                                                                                                                                                                                                   "ldm     sp++, r0-r7                                                                            \n\t" \
                                                                                                                                                                                                                                                                                                                                                                                                                         \
            /* Now, the stack should be R8..R12, LR, PC and SR  */                                                                                                                                                                                                                                                                                                                                                       \
                                                                                                                                                                                                                                                                                                                   "rete"                                                                                                \
            );                                                                                                                                                                                                                                                                                                                                                                                                           \
                                                                                                                                                                                                                                                                                                                                                                                                                         \
        /* Force import of global symbols from assembly */                                                                                                                                                                                                                                                                                                                                                               \
        ulCriticalNesting;                                                                                                                                                                                                                                                                                                                                                                                               \
        pxCurrentTCB;                                                                                                                                                                                                                                                                                                                                                                                                    \
    }

#पूर्ण_अगर /* if configUSE_PREEMPTION == 0 */


#घोषणा portYIELD()                                           { __asm__ __volatile__ ( "scall" ); }

/* Task function macros as described on the FreeRTOS.org WEB site. */
#घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
#घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
