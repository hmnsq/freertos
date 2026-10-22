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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS లేదా
 * IMPLIED, INCLUDING BUT కాదు LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE మరియు NONINFRINGEMENT. లో NO EVENT SHALL THE AUTHORS లేదా
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES లేదా OTHER LIABILITY, WHETHER
 * లో AN ACTION OF CONTRACT, TORT లేదా OTHERWISE, ARISING FROM, OUT OF లేదా లో
 * CONNECTION WITH THE SOFTWARE లేదా THE USE లేదా OTHER DEALINGS లో THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

.file "portASM.S"
#include "FreeRTOSConfig.h"
#include "ISR_Support.h"

    .extern pxCurrentTCB
    .extern vTaskSwitchContext
    .extern vPortCentralInterruptHandler
    .extern xTaskIncrementTick
    .extern vPortAPICErrorHandler
    .extern pucPortTaskFPUContextBuffer
    .extern ulPortYieldPending

    .వైశ్విక v_పోర్టు_ప్రారంభం_మొదటి_Task
    .వైశ్విక v_పోర్టు_Central_అంతరాయం_Wrapper
    .వైశ్విక v_పోర్టు_APICError_Handler_Wrapper
    .వైశ్విక v_పోర్టు_Timer_Handler
    .వైశ్విక v_పోర్టు_Yield_Call
    .వైశ్విక v_పోర్టు_APICSpurious_Handler

    .text

/*-----------------------------------------------------------*/

.align 4
.func v_పోర్టు_Yield_Call
v_పోర్టు_Yield_Call:
    /* Save general purpose registers. */
    pusha

    .if configSUPPORT_FPU == 1

        /* If the task has a buffer allocated to save the FPU context then save
        the FPU context now. */
        movl    pucPortTaskFPUContextBuffer, %eax
        test    %eax, %eax
        je      1f
        fnsave  ( %eax )
        fwait

        1:

        /* Save the address of the FPU context, if any. */
        push    pucPortTaskFPUContextBuffer

    .endif /* configSUPPORT_FPU */

    /* Find the TCB. */
    movl    pxCurrentTCB, %eax

    /* Stack location is first item in the TCB. */
    movl    %esp, (%eax)

    పిలువు vTaskSwitchContext

    /* Find the location of pxCurrentTCB again - a callee saved register could
    be used in place of eax to prevent this second load, but that then relies
    on the compiler and other asm code. */
    movl    pxCurrentTCB, %eax
    movl    (%eax), %esp

    .if configSUPPORT_FPU == 1

        /* Restore address of task's FPU context buffer. */
        pop     pucPortTaskFPUContextBuffer

        /* If the task has a buffer allocated in which its FPU context is saved,
        then restore it now. */
        movl    pucPortTaskFPUContextBuffer, %eax
        test    %eax, %eax
        je      1f
        frstor  ( %eax )
        1:
    .endif

    popa
    iret

.endfunc
/*-----------------------------------------------------------*/

.align 4
.func v_పోర్టు_ప్రారంభం_మొదటి_Task
v_పోర్టు_ప్రారంభం_మొదటి_Task:

    /* Find the TCB. */
    movl    pxCurrentTCB, %eax

    /* Stack location is first item in the TCB. */
    movl    (%eax), %esp

    /* Restore FPU context flag. */
    .if configSUPPORT_FPU == 1

        pop     pucPortTaskFPUContextBuffer

    .endif /* configSUPPORT_FPU */

    /* Restore general purpose registers. */
    popa
    iret
.endfunc
/*-----------------------------------------------------------*/

.align 4
.func v_పోర్టు_APICError_Handler_Wrapper
v_పోర్టు_APICError_Handler_Wrapper:
    pusha
    పిలువు    vPortAPICErrorHandler
    popa
    /* EOI. */
    movl    $0x00, (0xFEE000B0)
    iret
.endfunc
/*-----------------------------------------------------------*/

.align 4
.func v_పోర్టు_Timer_Handler
v_పోర్టు_Timer_Handler:

    /* Save general purpose registers. */
    pusha

    /* Interrupts are not nested, so save the rest of the task context. */
    .if configSUPPORT_FPU == 1

        /* If the task has a buffer allocated to save the FPU context then save the
        FPU context now. */
        movl    pucPortTaskFPUContextBuffer, %eax
        test    %eax, %eax
        je      1f
        fnsave  ( %eax ) /* Save FLOP context into ucTempFPUBuffer array. */
        fwait

        1:
        /* Save the address of the FPU context, if any. */
        push    pucPortTaskFPUContextBuffer

    .endif /* configSUPPORT_FPU */

    /* Find the TCB. */
    movl    pxCurrentTCB, %eax

    /* Stack location is first item in the TCB. */
    movl    %esp, (%eax)

    /* Switch stacks. */
    movl    ulTopOfSystemStack, %esp
    movl    %esp, %ebp

    /* Increment nesting count. */
    add     $1, ulInterruptNesting

    పిలువు    xTaskIncrementTick

    sti

    /* Is a switch to another task required? */
    test    %eax, %eax
    je      _skip_context_switch
    cli
    పిలువు    vTaskSwitchContext

_skip_context_switch:
    cli

    /* Decrement the variable used to determine if a switch to a system
    stack is necessary. */
    sub     $1, ulInterruptNesting

    /* Stack location is first item in the TCB. */
    movl    pxCurrentTCB, %eax
    movl    (%eax), %esp

    .if configSUPPORT_FPU == 1

        /* Restore address of task's FPU context buffer. */
        pop     pucPortTaskFPUContextBuffer

        /* If the task has a buffer allocated in which its FPU context is saved,
        then restore it now. */
        movl    pucPortTaskFPUContextBuffer, %eax
        test    %eax, %eax
        je      1f
        frstor  ( %eax )
        1:
    .endif

    popa

    /* EOI. */
    movl    $0x00, (0xFEE000B0)
    iret

.endfunc
/*-----------------------------------------------------------*/

.if configUSE_COMMON_INTERRUPT_ENTRY_POINT == 1

    .align 4
    .func v_పోర్టు_Central_అంతరాయం_Wrapper
    v_పోర్టు_Central_అంతరాయం_Wrapper:

        portFREERTOS_INTERRUPT_ENTRY

        movl $0xFEE00170, %eax          /* Highest In Service Register (ISR) long word. */
        movl $8, %ecx                   /* Loop counter. */

    next_isr_long_word:
        test %ecx, %ecx                 /* Loop counter reached 0? */
        je wrapper_epilogue             /* Looked at all ISR registers without finding a bit set. */
        sub $1, %ecx                    /* Sub 1 from loop counter. */
        movl (%eax), %ebx               /* Load next ISR long word. */
        sub $0x10, %eax                 /* Point to next ISR long word in case no bits are set in the current long word. */
        test %ebx, %ebx                 /* Are there any bits set? */
        je next_isr_long_word           /* Look at next ISR long word if no bits were set. */
        sti
        bsr %ebx, %ebx                  /* A bit was set, which one? */
        movl $32, %eax                  /* Destination operand for following multiplication. */
        mul %ecx                        /* Calculate base vector for current register, 32 vectors per register. */
        add %ebx, %eax                  /* Add bit offset into register to get final vector number. */
        push %eax                       /* Vector number is function parameter. */
        పిలువు vPortCentralInterruptHandler
        pop %eax                        /* Remove parameter. */

    wrapper_epilogue:
        portFREERTOS_INTERRUPT_EXIT

    .endfunc

.endif /* configUSE_COMMON_INTERRUPT_ENTRY_POINT */
/*-----------------------------------------------------------*/

.align 4
.func vPortAPISpuriousHandler
v_పోర్టు_APICSpurious_Handler:
    iret

.endfunc

.end
