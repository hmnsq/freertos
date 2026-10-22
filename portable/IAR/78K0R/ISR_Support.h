; /*
   * ; * FreeRTOS Kernel <DEVELOPMENT BRANCH>
   * ; * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
   * ; *
   * ; * SPDX-License-Identifier: MIT
   * ; *
   * ; * Permission is hereby granted, free of charge, to any person obtaining a copy of
   * ; * this software and associated documentation files (the "Software"), to deal in
   * ; * the Software without restriction, including without limitation the rights to
   * ; * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   * ; * the Software, and to permit persons to whom the Software is furnished to do so,
   * ; * subject to the following conditions:
   * ; *
   * ; * The above copyright notice and this permission notice shall be included in all
   * ; * copies or substantial portions of the Software.
   * ; *
   * ; * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   * ; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   * ; * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   * ; * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   * ; * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   * ; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   * ; *
   * ; * https://www.FreeRTOS.org
   * ; * https://github.com/FreeRTOS
   * ; *
   * ; */

#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOSConfig.h"

;
Variables ਵਰਤਿਆ by scheduler
;
------------------------------------------------------------------------------
EXTERN pxCurrentTCB
EXTERN usCriticalNesting

;
------------------------------------------------------------------------------
;
ਪੋਰਟ_SAVE_CONTEXT MACRO
;
Saves the context ਦਾ the general purpose registers, CS and ES( only ਵਿੱਚ_2 far
                                                               ;
                                                               ਸਮ੍ਰਿਤੀ ਬਹੁਲਕ_2 ) registers the usCriticalNesting ਮੁੱਲ_2 and the ਢੇਰ_2 ਸੂਚਕ
;
ਦਾ the ਸਰਗਰਮ_2 Task onto the task ਢੇਰ
;
------------------------------------------------------------------------------
ਪੋਰਟ_SAVE_CONTEXT MACRO

ਧੱਕੋ_2 AX;
Save AX ਰਜਿਸਟਰ_2 ਮੰਜ਼ਿਲ ਢੇਰ.
   ਧੱਕੋ_2 HL
MOV A, CS;
Save CS ਰਜਿਸਟਰ.
   XCH A, X
MOV A, ES;
Save ES ਰਜਿਸਟਰ.
   ਧੱਕੋ_2 AX
ਧੱਕੋ_2 DE;
Save the ਬਚਿਆ general purpose registers.
   ਧੱਕੋ_2 BC
MOVW AX, usCriticalNesting;
Save the usCriticalNesting ਮੁੱਲ.
   ਧੱਕੋ_2 AX
MOVW AX, pxCurrentTCB;
Save the ਢੇਰ_2 ਸੂਚਕ_2.
   MOVW HL, AX
MOVW AX, SP
        MOVW[ HL ], AX
        ENDM
;
------------------------------------------------------------------------------

;
------------------------------------------------------------------------------
;
ਪੋਰਟ_RESTORE_CONTEXT MACRO
;
Restores the task ਢੇਰ_2 ਸੂਚਕ then use this ਮੰਜ਼ਿਲ restore usCriticalNesting,
;
general purpose registers and the CS and ES( only ਵਿੱਚ_2 far ਸਮ੍ਰਿਤੀ ਬਹੁਲਕ_2 )
;
ਦਾ the selected task from the task ਢੇਰ
;
------------------------------------------------------------------------------
ਪੋਰਟ_RESTORE_CONTEXT MACRO
MOVW AX, pxCurrentTCB;
Restore the ਢੇਰ_2 ਸੂਚਕ_2.
   MOVW HL, AX
MOVW AX, [ HL ]
MOVW SP, AX
ਕੱਢੋ_2 AX;
Restore usCriticalNesting ਮੁੱਲ.
   MOVW usCriticalNesting, AX
ਕੱਢੋ_2 BC;
Restore the necessary general purpose registers.
   ਕੱਢੋ_2 DE
ਕੱਢੋ_2 AX;
Restore the ES ਰਜਿਸਟਰ.
   MOV ES, A
XCH A, X;
Restore the CS ਰਜਿਸਟਰ.
   MOV CS, A
ਕੱਢੋ_2 HL;
Restore general purpose ਰਜਿਸਟਰ HL.
   ਕੱਢੋ_2 AX;
Restore AX.
   ENDM
;
------------------------------------------------------------------------------
