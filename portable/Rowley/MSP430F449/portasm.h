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
        इतुलाक    r4
        इतुलाक    r5
        इतुलाक    r6
        इतुलाक    r7
        इतुलाक    r8
        इतुलाक    r9
        इतुलाक    r10
        इतुलाक    r11
        इतुलाक    r12
        इतुलाक    r13
        इतुलाक    r14
        इतुलाक    r15
        mov.w   &_usCriticalNesting, r14
        इतुलाक    r14
        mov.w   &_pxCurrentTCB, r12
        mov.w   r1, @r12
        endm
/*-----------------------------------------------------------*/

portRESTORE_CONTEXT macro
        mov.w   &_pxCurrentTCB, r12
        mov.w   @r12, r1
        आलिसिन     r15
        mov.w   r15, &_usCriticalNesting
        आलिसिन     r15
        आलिसिन     r14
        आलिसिन     r13
        आलिसिन     r12
        आलिसिन     r11
        आलिसिन     r10
        आलिसिन     r9
        आलिसिन     r8
        आलिसिन     r7
        आलिसिन     r6
        आलिसिन     r5
        आलिसिन     r4

        /* The last thing on the stack will be the status register.
                Ensure the power down bits are clear ready for the next
                time this power down register is popped from the stack. */
        bic.w   #0xf0,0(SP)

        reti
        endm
/*-----------------------------------------------------------*/

#endif
