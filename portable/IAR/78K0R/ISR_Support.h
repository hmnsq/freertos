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

#ಅನ್ತರ್ಭಾವ "FreeRTOSConfig.h"

;
Variables ಬಳಸಿದ by scheduler
;
------------------------------------------------------------------------------
EXTERN pxCurrentTCB
EXTERN usCriticalNesting

;
------------------------------------------------------------------------------
;
ಪೋರ್ಟ್_SAVE_CONTEXT MACRO
;
Saves the context ದ the general purpose registers, CS and ES( only ಒಳ far
                                                               ;
                                                               ಸ್ಮರಣೆ ಬಹುಲಕ_2 ) registers the usCriticalNesting ಮೌಲ್ಯ_2 and the ರಾಶಿ_2 ಸೂಚಕ_2
;
ದ the ಸಕ್ರಿಯ_2 Task onto the task ರಾಶಿ
;
------------------------------------------------------------------------------
ಪೋರ್ಟ್_SAVE_CONTEXT MACRO

ತಳ್ಳು_2 AX;
Save AX ರಿಜಿಸ್ಟರ್ ಗಮ್ಯ ರಾಶಿ.
   ತಳ್ಳು_2 HL
MOV A, CS;
Save CS ನೋಂದಣಿ.
   XCH A, X
MOV A, ES;
Save ES ನೋಂದಣಿ.
   ತಳ್ಳು_2 AX
ತಳ್ಳು_2 DE;
Save the ಉಳಿದ general purpose registers.
   ತಳ್ಳು_2 BC
MOVW AX, usCriticalNesting;
Save the usCriticalNesting ಮೌಲ್ಯ.
   ತಳ್ಳು_2 AX
MOVW AX, pxCurrentTCB;
Save the ರಾಶಿ_2 ಸೂಚಕ_3.
   MOVW HL, AX
MOVW AX, SP
        MOVW[ HL ], AX
        ENDM
;
------------------------------------------------------------------------------

;
------------------------------------------------------------------------------
;
ಪೋರ್ಟ್_RESTORE_CONTEXT MACRO
;
Restores the task ರಾಶಿ_2 ಸೂಚಕ_2 then use this ಗಮ್ಯ restore usCriticalNesting,
;
general purpose registers and the CS and ES( only ಒಳ far ಸ್ಮರಣೆ ಬಹುಲಕ_2 )
;
ದ the selected task from the task ರಾಶಿ
;
------------------------------------------------------------------------------
ಪೋರ್ಟ್_RESTORE_CONTEXT MACRO
MOVW AX, pxCurrentTCB;
Restore the ರಾಶಿ_2 ಸೂಚಕ_3.
   MOVW HL, AX
MOVW AX, [ HL ]
MOVW SP, AX
ತೆಗೆ_3 AX;
Restore usCriticalNesting ಮೌಲ್ಯ.
   MOVW usCriticalNesting, AX
ತೆಗೆ_3 BC;
Restore the necessary general purpose registers.
   ತೆಗೆ_3 DE
ತೆಗೆ_3 AX;
Restore the ES ನೋಂದಣಿ.
   MOV ES, A
XCH A, X;
Restore the CS ನೋಂದಣಿ.
   MOV CS, A
ತೆಗೆ_3 HL;
Restore general purpose ನೋಂದಣಿ HL.
   ತೆಗೆ_3 AX;
Restore AX.
   ENDM
;
------------------------------------------------------------------------------
