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

#ifndef PORTASM_H
#define PORTASM_H

portSAVE_CONTEXT macro

    IMPORT pxCurrentTCB
    IMPORT usCriticalNesting

    /* Save the remaining registers. */
    ঠেলো   r4
    ঠেলো   r5
    ঠেলো   r6
    ঠেলো   r7
    ঠেলো   r8
    ঠেলো   r9
    ঠেলো   r10
    ঠেলো   r11
    ঠেলো   r12
    ঠেলো   r13
    ঠেলো   r14
    ঠেলো   r15
    mov.w  &usCriticalNesting, r14
    ঠেলো   r14
    mov.w  &pxCurrentTCB, r12
    mov.w  r1, 0(r12)
    endm
/*-----------------------------------------------------------*/

portRESTORE_CONTEXT macro
    mov.w  &pxCurrentTCB, r12
    mov.w  @r12, r1
    বেৰ_কৰো    r15
    mov.w  r15, &usCriticalNesting
    বেৰ_কৰো    r15
    বেৰ_কৰো    r14
    বেৰ_কৰো    r13
    বেৰ_কৰো    r12
    বেৰ_কৰো    r11
    বেৰ_কৰো    r10
    বেৰ_কৰো    r9
    বেৰ_কৰো    r8
    বেৰ_কৰো    r7
    বেৰ_কৰো    r6
    বেৰ_কৰো    r5
    বেৰ_কৰো    r4

    /* The last thing on the stack will be the status register.
     * Ensure the power down bits are clear ready for the next
     * time this power down register is popped from the stack. */
    bic.w  #0xf0, 0(SP)

    reti
    endm
/*-----------------------------------------------------------*/

#endif /* ifndef PORTASM_H */
