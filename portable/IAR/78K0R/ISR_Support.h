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

#അന്തര്ഭാവ "FreeRTOSConfig.h"

;
Variables used by scheduler
;
------------------------------------------------------------------------------
EXTERN pxCurrentTCB
EXTERN usCriticalNesting

;
------------------------------------------------------------------------------
;
portSAVE_CONTEXT MACRO
;
Saves the context of the general purpose registers, CS and ES( only in far
                                                               ;
                                                               memory mode ) registers the usCriticalNesting മൂല്യം_2 and the അട്ടി_2 Pointer
;
of the active Task onto the task അട്ടി
;
------------------------------------------------------------------------------
portSAVE_CONTEXT MACRO

തള്ളുക_2 AX;
Save AX Register to അട്ടി.
   തള്ളുക_2 HL
MOV A, CS;
Save CS രജിസ്റ്റർ.
   XCH A, X
MOV A, ES;
Save ES രജിസ്റ്റർ.
   തള്ളുക_2 AX
തള്ളുക_2 DE;
Save the remaining general purpose registers.
   തള്ളുക_2 BC
MOVW AX, usCriticalNesting;
Save the usCriticalNesting മൂല്യം.
   തള്ളുക_2 AX
MOVW AX, pxCurrentTCB;
Save the അട്ടി_2 pointer.
   MOVW HL, AX
MOVW AX, SP
        MOVW[ HL ], AX
        ENDM
;
------------------------------------------------------------------------------

;
------------------------------------------------------------------------------
;
portRESTORE_CONTEXT MACRO
;
Restores the task അട്ടി_2 Pointer then use this to restore usCriticalNesting,
;
general purpose registers and the CS and ES( only in far memory mode )
;
of the selected task from the task അട്ടി
;
------------------------------------------------------------------------------
portRESTORE_CONTEXT MACRO
MOVW AX, pxCurrentTCB;
Restore the അട്ടി_2 pointer.
   MOVW HL, AX
MOVW AX, [ HL ]
MOVW SP, AX
എടുക്കുക_2 AX;
Restore usCriticalNesting മൂല്യം.
   MOVW usCriticalNesting, AX
എടുക്കുക_2 BC;
Restore the necessary general purpose registers.
   എടുക്കുക_2 DE
എടുക്കുക_2 AX;
Restore the ES രജിസ്റ്റർ.
   MOV ES, A
XCH A, X;
Restore the CS രജിസ്റ്റർ.
   MOV CS, A
എടുക്കുക_2 HL;
Restore general purpose രജിസ്റ്റർ HL.
   എടുക്കുക_2 AX;
Restore AX.
   ENDM
;
------------------------------------------------------------------------------
