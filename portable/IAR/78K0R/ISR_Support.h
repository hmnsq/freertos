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

#ضمن "FreeRTOSConfig.h"

;
Variables استعمال_ٿيل by scheduler
;
------------------------------------------------------------------------------
EXTERN pxCurrentTCB
EXTERN usCriticalNesting

;
------------------------------------------------------------------------------
;
پورٽ_SAVE_CONTEXT MACRO
;
Saves the context جو the general purpose registers, CS and ES( only اندريون far
                                                               ;
                                                               يادگيري گهڻائي_2 ) registers the usCriticalNesting قدر_2 and the ڍير_2 اشارو
;
جو the سرگرم_2 Task onto the task ڍير
;
------------------------------------------------------------------------------
پورٽ_SAVE_CONTEXT MACRO

ڌڪو_2 AX;
Save AX رجسٽر منزل ڍير.
   ڌڪو_2 HL
MOV A, CS;
Save CS سجل.
   XCH A, X
MOV A, ES;
Save ES سجل.
   ڌڪو_2 AX
ڌڪو_2 DE;
Save the بچيل general purpose registers.
   ڌڪو_2 BC
MOVW AX, usCriticalNesting;
Save the usCriticalNesting قدر.
   ڌڪو_2 AX
MOVW AX, pxCurrentTCB;
Save the ڍير_2 اشارو_2.
   MOVW HL, AX
MOVW AX, SP
        MOVW[ HL ], AX
        ENDM
;
------------------------------------------------------------------------------

;
------------------------------------------------------------------------------
;
پورٽ_RESTORE_CONTEXT MACRO
;
Restores the task ڍير_2 اشارو then use this منزل restore usCriticalNesting,
;
general purpose registers and the CS and ES( only اندريون far يادگيري گهڻائي_2 )
;
جو the selected task from the task ڍير
;
------------------------------------------------------------------------------
پورٽ_RESTORE_CONTEXT MACRO
MOVW AX, pxCurrentTCB;
Restore the ڍير_2 اشارو_2.
   MOVW HL, AX
MOVW AX, [ HL ]
MOVW SP, AX
ڪڍو_2 AX;
Restore usCriticalNesting قدر.
   MOVW usCriticalNesting, AX
ڪڍو_2 BC;
Restore the necessary general purpose registers.
   ڪڍو_2 DE
ڪڍو_2 AX;
Restore the ES سجل.
   MOV ES, A
XCH A, X;
Restore the CS سجل.
   MOV CS, A
ڪڍو_2 HL;
Restore general purpose سجل HL.
   ڪڍو_2 AX;
Restore AX.
   ENDM
;
------------------------------------------------------------------------------
