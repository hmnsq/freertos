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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTASM_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTASM_H

ਪੋਰਟ_SAVE_CONTEXT macro

    IMPORT pxCurrentTCB
    IMPORT usCriticalNesting

    /* Save the remaining registers. */
    ਧੱਕੋ   r4
    ਧੱਕੋ   r5
    ਧੱਕੋ   r6
    ਧੱਕੋ   r7
    ਧੱਕੋ   r8
    ਧੱਕੋ   r9
    ਧੱਕੋ   r10
    ਧੱਕੋ   r11
    ਧੱਕੋ   r12
    ਧੱਕੋ   r13
    ਧੱਕੋ   r14
    ਧੱਕੋ   r15
    mov.w  &usCriticalNesting, r14
    ਧੱਕੋ   r14
    mov.w  &pxCurrentTCB, r12
    mov.w  r1, 0(r12)
    endm
/*-----------------------------------------------------------*/

ਪੋਰਟ_RESTORE_CONTEXT macro
    mov.w  &pxCurrentTCB, r12
    mov.w  @r12, r1
    ਕੱਢੋ    r15
    mov.w  r15, &usCriticalNesting
    ਕੱਢੋ    r15
    ਕੱਢੋ    r14
    ਕੱਢੋ    r13
    ਕੱਢੋ    r12
    ਕੱਢੋ    r11
    ਕੱਢੋ    r10
    ਕੱਢੋ    r9
    ਕੱਢੋ    r8
    ਕੱਢੋ    r7
    ਕੱਢੋ    r6
    ਕੱਢੋ    r5
    ਕੱਢੋ    r4

    /* The last thing on the stack will be the status register.
     * Ensure the power down bits are clear ready for the next
     * time this power down register is popped from the stack. */
    bic.w  #0xf0, 0(SP)

    reti
    endm
/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* ifndef PORTASM_H */
