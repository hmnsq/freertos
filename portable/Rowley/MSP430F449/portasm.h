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

#నిర్వచితం_కాకపోతే పోర్టు_ASM_H
#నిర్వచించు పోర్టు_ASM_H

పోర్టు_SAVE_CONTEXT macro
                /* Save the remaining registers. */
        నెట్టు    r4
        నెట్టు    r5
        నెట్టు    r6
        నెట్టు    r7
        నెట్టు    r8
        నెట్టు    r9
        నెట్టు    r10
        నెట్టు    r11
        నెట్టు    r12
        నెట్టు    r13
        నెట్టు    r14
        నెట్టు    r15
        mov.w   &_usCriticalNesting, r14
        నెట్టు    r14
        mov.w   &_pxCurrentTCB, r12
        mov.w   r1, @r12
        endm
/*-----------------------------------------------------------*/

పోర్టు_RESTORE_CONTEXT macro
        mov.w   &_pxCurrentTCB, r12
        mov.w   @r12, r1
        తీయి     r15
        mov.w   r15, &_usCriticalNesting
        తీయి     r15
        తీయి     r14
        తీయి     r13
        తీయి     r12
        తీయి     r11
        తీయి     r10
        తీయి     r9
        తీయి     r8
        తీయి     r7
        తీయి     r6
        తీయి     r5
        తీయి     r4

        /* The last thing on the stack will be the status register.
                Ensure the power down bits are clear ready for the next
                time this power down register is popped from the stack. */
        bic.w   #0xf0,0(SP)

        reti
        endm
/*-----------------------------------------------------------*/

#అయితే_ముగింపు
