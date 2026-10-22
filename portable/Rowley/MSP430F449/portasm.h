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
        ادفع    r4
        ادفع    r5
        ادفع    r6
        ادفع    r7
        ادفع    r8
        ادفع    r9
        ادفع    r10
        ادفع    r11
        ادفع    r12
        ادفع    r13
        ادفع    r14
        ادفع    r15
        mov.w   &_usCriticalNesting, r14
        ادفع    r14
        mov.w   &_pxCurrentTCB, r12
        mov.w   r1, @r12
        endm
/*-----------------------------------------------------------*/

portRESTORE_CONTEXT macro
        mov.w   &_pxCurrentTCB, r12
        mov.w   @r12, r1
        اسحب     r15
        mov.w   r15, &_usCriticalNesting
        اسحب     r15
        اسحب     r14
        اسحب     r13
        اسحب     r12
        اسحب     r11
        اسحب     r10
        اسحب     r9
        اسحب     r8
        اسحب     r7
        اسحب     r6
        اسحب     r5
        اسحب     r4

        /* The last thing on the stack will be the status register.
                Ensure the power down bits are clear ready for the next
                time this power down register is popped from the stack. */
        bic.w   #0xf0,0(SP)

        reti
        endm
/*-----------------------------------------------------------*/

#endif
