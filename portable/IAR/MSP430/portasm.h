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

#که_نه_تعریف_شوی PORTASM_H
#تعریف_کړه PORTASM_H

پورټ_SAVE_CONTEXT macro

    IMPORT pxCurrentTCB
    IMPORT usCriticalNesting

    /* Save the remaining registers. */
    ټېل   r4
    ټېل   r5
    ټېل   r6
    ټېل   r7
    ټېل   r8
    ټېل   r9
    ټېل   r10
    ټېل   r11
    ټېل   r12
    ټېل   r13
    ټېل   r14
    ټېل   r15
    mov.w  &usCriticalNesting, r14
    ټېل   r14
    mov.w  &pxCurrentTCB, r12
    mov.w  r1, 0(r12)
    endm
/*-----------------------------------------------------------*/

پورټ_RESTORE_CONTEXT macro
    mov.w  &pxCurrentTCB, r12
    mov.w  @r12, r1
    راوباسه    r15
    mov.w  r15, &usCriticalNesting
    راوباسه    r15
    راوباسه    r14
    راوباسه    r13
    راوباسه    r12
    راوباسه    r11
    راوباسه    r10
    راوباسه    r9
    راوباسه    r8
    راوباسه    r7
    راوباسه    r6
    راوباسه    r5
    راوباسه    r4

    /* The last thing on the stack will be the status register.
     * Ensure the power down bits are clear ready for the next
     * time this power down register is popped from the stack. */
    bic.w  #0xf0, 0(SP)

    reti
    endm
/*-----------------------------------------------------------*/

#د_که_پای /* ifndef PORTASM_H */
