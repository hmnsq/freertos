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

#অন্তর্ভাব "FreeRTOSConfig.h"

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
                                                               memory mode ) registers the usCriticalNesting মান_2 and the স্তূপ_2 Pointer
;
of the active Task onto the task স্তূপ
;
------------------------------------------------------------------------------
portSAVE_CONTEXT MACRO

ঠেলো_2 AX;
Save AX Register to স্তূপ.
   ঠেলো_2 HL
MOV A, CS;
Save CS পঞ্জিকা.
   XCH A, X
MOV A, ES;
Save ES পঞ্জিকা.
   ঠেলো_2 AX
ঠেলো_2 DE;
Save the remaining general purpose registers.
   ঠেলো_2 BC
MOVW AX, usCriticalNesting;
Save the usCriticalNesting মান.
   ঠেলো_2 AX
MOVW AX, pxCurrentTCB;
Save the স্তূপ_2 pointer.
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
Restores the task স্তূপ_2 Pointer then use this to restore usCriticalNesting,
;
general purpose registers and the CS and ES( only in far memory mode )
;
of the selected task from the task স্তূপ
;
------------------------------------------------------------------------------
portRESTORE_CONTEXT MACRO
MOVW AX, pxCurrentTCB;
Restore the স্তূপ_2 pointer.
   MOVW HL, AX
MOVW AX, [ HL ]
MOVW SP, AX
বের_করো_2 AX;
Restore usCriticalNesting মান.
   MOVW usCriticalNesting, AX
বের_করো_2 BC;
Restore the necessary general purpose registers.
   বের_করো_2 DE
বের_করো_2 AX;
Restore the ES পঞ্জিকা.
   MOV ES, A
XCH A, X;
Restore the CS পঞ্জিকা.
   MOV CS, A
বের_করো_2 HL;
Restore general purpose পঞ্জিকা HL.
   বের_করো_2 AX;
Restore AX.
   ENDM
;
------------------------------------------------------------------------------
