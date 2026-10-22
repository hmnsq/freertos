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
                                                               memory mode ) registers the usCriticalNesting मान_2 and the थाक_2 Pointer
;
of the active Task onto the task थाक
;
------------------------------------------------------------------------------
portSAVE_CONTEXT MACRO

थप_2 AX;
Save AX Register to थाक.
   थप_2 HL
MOV A, CS;
Save CS पञ्जिका.
   XCH A, X
MOV A, ES;
Save ES पञ्जिका.
   थप_2 AX
थप_2 DE;
Save the remaining general purpose registers.
   थप_2 BC
MOVW AX, usCriticalNesting;
Save the usCriticalNesting मान.
   थप_2 AX
MOVW AX, pxCurrentTCB;
Save the थाक_2 pointer.
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
Restores the task थाक_2 Pointer then use this to restore usCriticalNesting,
;
general purpose registers and the CS and ES( only in far memory mode )
;
of the selected task from the task थाक
;
------------------------------------------------------------------------------
portRESTORE_CONTEXT MACRO
MOVW AX, pxCurrentTCB;
Restore the थाक_2 pointer.
   MOVW HL, AX
MOVW AX, [ HL ]
MOVW SP, AX
झिक_2 AX;
Restore usCriticalNesting मान.
   MOVW usCriticalNesting, AX
झिक_2 BC;
Restore the necessary general purpose registers.
   झिक_2 DE
झिक_2 AX;
Restore the ES पञ्जिका.
   MOV ES, A
XCH A, X;
Restore the CS पञ्जिका.
   MOV CS, A
झिक_2 HL;
Restore general purpose पञ्जिका HL.
   झिक_2 AX;
Restore AX.
   ENDM
;
------------------------------------------------------------------------------
