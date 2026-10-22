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

#अन्तर्भाव "FreeRTOSConfig.h"

;
Variables प्रयुक्तम् by scheduler
;
------------------------------------------------------------------------------
EXTERN pxCurrentTCB
EXTERN usCriticalNesting

;
------------------------------------------------------------------------------
;
पत्तनम्_SAVE_CONTEXT MACRO
;
Saves the context सम्बन्धि the general purpose registers, CS and ES( only अन्तर् far
                                                               ;
                                                               स्मृतिः बहुलकम्_2 ) registers the usCriticalNesting मानम्_2 and the राशिः_2 Pointer
;
सम्बन्धि the सक्रिय_2 Task onto the task राशिः
;
------------------------------------------------------------------------------
पत्तनम्_SAVE_CONTEXT MACRO

प्रक्षिप_2 AX;
Save AX पञ्जिकाकोशः गन्तव्यम् राशिः.
   प्रक्षिप_2 HL
MOV A, CS;
Save CS पञ्जिका.
   XCH A, X
MOV A, ES;
Save ES पञ्जिका.
   प्रक्षिप_2 AX
प्रक्षिप_2 DE;
Save the remaining general purpose registers.
   प्रक्षिप_2 BC
MOVW AX, usCriticalNesting;
Save the usCriticalNesting मानम्.
   प्रक्षिप_2 AX
MOVW AX, pxCurrentTCB;
Save the राशिः_2 pointer.
   MOVW HL, AX
MOVW AX, SP
        MOVW[ HL ], AX
        ENDM
;
------------------------------------------------------------------------------

;
------------------------------------------------------------------------------
;
पत्तनम्_RESTORE_CONTEXT MACRO
;
Restores the task राशिः_2 Pointer then use this गन्तव्यम् restore usCriticalNesting,
;
general purpose registers and the CS and ES( only अन्तर् far स्मृतिः बहुलकम्_2 )
;
सम्बन्धि the selected task from the task राशिः
;
------------------------------------------------------------------------------
पत्तनम्_RESTORE_CONTEXT MACRO
MOVW AX, pxCurrentTCB;
Restore the राशिः_2 pointer.
   MOVW HL, AX
MOVW AX, [ HL ]
MOVW SP, AX
निष्कासय_2 AX;
Restore usCriticalNesting मानम्.
   MOVW usCriticalNesting, AX
निष्कासय_2 BC;
Restore the necessary general purpose registers.
   निष्कासय_2 DE
निष्कासय_2 AX;
Restore the ES पञ्जिका.
   MOV ES, A
XCH A, X;
Restore the CS पञ्जिका.
   MOV CS, A
निष्कासय_2 HL;
Restore general purpose पञ्जिका HL.
   निष्कासय_2 AX;
Restore AX.
   ENDM
;
------------------------------------------------------------------------------
