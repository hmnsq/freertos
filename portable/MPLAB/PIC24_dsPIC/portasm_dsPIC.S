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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS या
 * IMPLIED, INCLUDING BUT नहीं LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE और NONINFRINGEMENT. अंदर NO EVENT SHALL THE AUTHORS या
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES या OTHER LIABILITY, WHETHER
 * अंदर AN ACTION OF CONTRACT, TORT या OTHERWISE, ARISING FROM, बाहर OF या अंदर
 * CONNECTION WITH THE SOFTWARE या THE USE या OTHER DEALINGS अंदर THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#if defined( __dsPIC30F__ ) || defined( __dsPIC33F__ )

        .global _vPortYield
        .extern _vTaskSwitchContext
        .extern uxCriticalNesting

_vPortYield:

        दो    SR                      /* Save the SR used by the task.... */
        दो    W0                      /* ....then disable interrupts. */
        डालो     #32, W0
        डालो     W0, SR
        दो    W1                      /* Save registers to the stack. */
        दो.D  W2
        दो.D  W4
        दो.D  W6
        दो.D  W8
        दो.D  W10
        दो.D  W12
        दो    W14
        दो    RCOUNT
        दो    TBLPAG
        दो    ACCAL
        दो    ACCAH
        दो    ACCAU
        दो    ACCBL
        दो    ACCBH
        दो    ACCBU
        दो    DCOUNT
        दो    DOSTARTL
        दो    DOSTARTH
        दो    DOENDL
        दो    DOENDH


        दो    CORCON
        दो    PSVPAG
        डालो     _uxCriticalNesting, W0      /* Save the critical nesting counter for the task. */
        दो    W0
        डालो     _pxCurrentTCB, W0           /* Save the new top of stack into the TCB. */
        डालो     W15, [W0]

        call    _vTaskSwitchContext

        डालो     _pxCurrentTCB, W0           /* Restore the stack pointer for the task. */
        डालो     [W0], W15
        लो     W0                          /* Restore the critical nesting counter for the task. */
        डालो     W0, _uxCriticalNesting
        लो     PSVPAG
        लो     CORCON
        लो     DOENDH
        लो     DOENDL
        लो     DOSTARTH
        लो     DOSTARTL
        लो     DCOUNT
        लो     ACCBU
        लो     ACCBH
        लो     ACCBL
        लो     ACCAU
        लो     ACCAH
        लो     ACCAL
        लो     TBLPAG
        लो     RCOUNT                      /* Restore the registers from the stack. */
        लो     W14
        लो.D   W12
        लो.D   W10
        लो.D   W8
        लो.D   W6
        लो.D   W4
        लो.D   W2
        लो.D   W0
        लो     SR

        return

        .end

#endif /* defined( __dsPIC30F__ ) || defined( __dsPIC33F__ ) */
