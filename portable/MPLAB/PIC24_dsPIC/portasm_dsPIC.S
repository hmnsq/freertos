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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS অথবা
 * IMPLIED, INCLUDING BUT নয় LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE এবং NONINFRINGEMENT. মধ্যে NO EVENT SHALL THE AUTHORS অথবা
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES অথবা OTHER LIABILITY, WHETHER
 * মধ্যে AN ACTION OF CONTRACT, TORT অথবা OTHERWISE, ARISING FROM, OUT OF অথবা মধ্যে
 * CONNECTION WITH THE SOFTWARE অথবা THE USE অথবা OTHER DEALINGS মধ্যে THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#if defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )

        .বৈশ্বিক _vPortYield
        .extern _vTaskSwitchContext
        .extern uxCriticalNesting

_vPortYield:

        PUSH    SR                      /* Save the SR used by the task.... */
        PUSH    W0                      /* ....then disable interrupts. */
        MOV     #32, W0
        MOV     W0, SR
        PUSH    W1                      /* Save registers to the stack. */
        PUSH.D  W2
        PUSH.D  W4
        PUSH.D  W6
        PUSH.D  W8
        PUSH.D  W10
        PUSH.D  W12
        PUSH    W14
        PUSH    RCOUNT
        PUSH    TBLPAG
        PUSH    ACCAL
        PUSH    ACCAH
        PUSH    ACCAU
        PUSH    ACCBL
        PUSH    ACCBH
        PUSH    ACCBU
        PUSH    DCOUNT
        PUSH    DOSTARTL
        PUSH    DOSTARTH
        PUSH    DOENDL
        PUSH    DOENDH


        PUSH    CORCON
        PUSH    PSVPAG
        MOV     _uxCriticalNesting, W0      /* Save the critical nesting counter for the task. */
        PUSH    W0
        MOV     _pxCurrentTCB, W0           /* Save the new top of stack into the TCB. */
        MOV     W15, [W0]

        ডাকো    _vTaskSwitchContext

        MOV     _pxCurrentTCB, W0           /* Restore the stack pointer for the task. */
        MOV     [W0], W15
        POP     W0                          /* Restore the critical nesting counter for the task. */
        MOV     W0, _uxCriticalNesting
        POP     PSVPAG
        POP     CORCON
        POP     DOENDH
        POP     DOENDL
        POP     DOSTARTH
        POP     DOSTARTL
        POP     DCOUNT
        POP     ACCBU
        POP     ACCBH
        POP     ACCBL
        POP     ACCAU
        POP     ACCAH
        POP     ACCAL
        POP     TBLPAG
        POP     RCOUNT                      /* Restore the registers from the stack. */
        POP     W14
        POP.D   W12
        POP.D   W10
        POP.D   W8
        POP.D   W6
        POP.D   W4
        POP.D   W2
        POP.D   W0
        POP     SR

        return

        .end

#endif /* defined( __dsPIC30F__ ) || defined( __dsPIC33F__ ) */
