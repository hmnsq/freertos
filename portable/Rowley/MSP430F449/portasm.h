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

#ifndef PORT_ASM_H
#define PORT_ASM_H

portSAVE_CONTEXT macro
                /* Save the remaining registers. */
        تور    r4
        تور    r5
        تور    r6
        تور    r7
        تور    r8
        تور    r9
        تور    r10
        تور    r11
        تور    r12
        تور    r13
        تور    r14
        تور    r15
        mov.w   &_usCriticalNesting, r14
        تور    r14
        mov.w   &_pxCurrentTCB, r12
        mov.w   r1, @r12
        endm
/*-----------------------------------------------------------*/

portRESTORE_CONTEXT macro
        mov.w   &_pxCurrentTCB, r12
        mov.w   @r12, r1
        چرو     r15
        mov.w   r15, &_usCriticalNesting
        چرو     r15
        چرو     r14
        چرو     r13
        چرو     r12
        چرو     r11
        چرو     r10
        چرو     r9
        چرو     r8
        چرو     r7
        چرو     r6
        چرو     r5
        چرو     r4

        /* The last thing on the stack will be the status register.
                Ensure the power down bits are clear ready for the next
                time this power down register is popped from the stack. */
        bic.w   #0xf0,0(SP)

        reti
        endm
/*-----------------------------------------------------------*/

#endif
