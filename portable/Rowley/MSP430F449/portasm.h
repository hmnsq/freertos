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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ಪೋರ್ಟ್_ASM_H
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASM_H

ಪೋರ್ಟ್_SAVE_CONTEXT macro
                /* Save the remaining registers. */
        ತಳ್ಳು    r4
        ತಳ್ಳು    r5
        ತಳ್ಳು    r6
        ತಳ್ಳು    r7
        ತಳ್ಳು    r8
        ತಳ್ಳು    r9
        ತಳ್ಳು    r10
        ತಳ್ಳು    r11
        ತಳ್ಳು    r12
        ತಳ್ಳು    r13
        ತಳ್ಳು    r14
        ತಳ್ಳು    r15
        mov.w   &_usCriticalNesting, r14
        ತಳ್ಳು    r14
        mov.w   &_pxCurrentTCB, r12
        mov.w   r1, @r12
        endm
/*-----------------------------------------------------------*/

ಪೋರ್ಟ್_RESTORE_CONTEXT macro
        mov.w   &_pxCurrentTCB, r12
        mov.w   @r12, r1
        ತೆಗೆ_2     r15
        mov.w   r15, &_usCriticalNesting
        ತೆಗೆ_2     r15
        ತೆಗೆ_2     r14
        ತೆಗೆ_2     r13
        ತೆಗೆ_2     r12
        ತೆಗೆ_2     r11
        ತೆಗೆ_2     r10
        ತೆಗೆ_2     r9
        ತೆಗೆ_2     r8
        ತೆಗೆ_2     r7
        ತೆಗೆ_2     r6
        ತೆಗೆ_2     r5
        ತೆಗೆ_2     r4

        /* The last thing on the stack will be the status register.
                Ensure the power down bits are clear ready for the next
                time this power down register is popped from the stack. */
        bic.w   #0xf0,0(SP)

        reti
        endm
/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ
