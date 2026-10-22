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

    .خارجي ul_بالاترین_از_System_پشته
    .خارجي ul_وقفه_Nesting

/*-----------------------------------------------------------*/

.macro پورت_FREERTOS_وقفه_مدخل

    /* Save general purpose registers. */
    pusha

    /* If ulInterruptNesting is zero the rest of the task context will need
    saving and a stack switch might be required. */
    movl    ul_وقفه_Nesting, %eax
    test    %eax, %eax
    jne     2f

    /* Interrupts are not nested, so save the rest of the task context. */
    .إذا configSUPPORT_FPU == 1

        /* If the task has a buffer allocated to save the FPU context then
        save the FPU context now. */
        movl    puc_پورت_Task_FPUContext_میانگیر, %eax
        test    %eax, %eax
        je      1f
        fnsave  ( %eax ) /* Save FLOP context into ucTempFPUBuffer array. */
        fwait

        1:
        /* Save the address of the FPU context, if any. */
        افزودن    puc_پورت_Task_FPUContext_میانگیر

    .endif /* configSUPPORT_FPU */

    /* Find the TCB. */
    movl    pxCurrentTCB, %eax

    /* Stack location is first item in the TCB. */
    movl    %esp, (%eax)

    /* Switch stacks. */
    movl    ul_بالاترین_از_System_پشته, %esp
    movl    %esp, %ebp

    2:
    /* Increment nesting count. */
    جمع_کن     $1, ul_وقفه_Nesting

.endm
/*-----------------------------------------------------------*/

.macro پورت_وقفه_EPILOGUE

    cli
    sub     $1, ul_وقفه_Nesting

    /* If the nesting has unwound to zero. */
    movl    ul_وقفه_Nesting, %eax
    test    %eax, %eax
    jne     2f

    /* If a yield was requested then select a new TCB now. */
    movl    ul_پورت_Yield_Pending, %eax
    test    %eax, %eax
    je      1f
    movl    $0, ul_پورت_Yield_Pending
    call    vTaskSwitchContext

    1:
    /* Stack location is first item in the TCB. */
    movl    pxCurrentTCB, %eax
    movl    (%eax), %esp

    .إذا configSUPPORT_FPU == 1

        /* Restore address of task's FPU context buffer. */
        برداشت     puc_پورت_Task_FPUContext_میانگیر

        /* If the task has a buffer allocated in which its FPU context is saved,
        then restore it now. */
        movl    puc_پورت_Task_FPUContext_میانگیر, %eax
        test    %eax, %eax
        je      1f
        frstor  ( %eax )
        1:
    .endif

    2:
    popa

.endm
/*-----------------------------------------------------------*/

.macro پورت_FREERTOS_وقفه_EXIT

    پورت_وقفه_EPILOGUE
    /* EOI. */
    movl    $0x00, (0xFEE000B0)
    iret

.endm
