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

#అన్తర్భావ "FreeRTOSConfig.h"

;
Variables వాడిన by scheduler
;
------------------------------------------------------------------------------
EXTERN pxCurrentTCB
EXTERN usCriticalNesting

;
------------------------------------------------------------------------------
;
పోర్టు_SAVE_CONTEXT MACRO
;
Saves the context యొక్క the general purpose registers, CS and ES( only లోపల far
                                                               ;
                                                               జ్ఞాపకం బహుళకం_2 ) registers the usCriticalNesting విలువ_2 and the దొంతర_2 సూచిక_2
;
యొక్క the చురుకైన_2 Task onto the task దొంతర
;
------------------------------------------------------------------------------
పోర్టు_SAVE_CONTEXT MACRO

నెట్టు_2 AX;
Save AX రిజిస్టరు గమ్యం దొంతర.
   నెట్టు_2 HL
MOV A, CS;
Save CS నమోదు.
   XCH A, X
MOV A, ES;
Save ES నమోదు.
   నెట్టు_2 AX
నెట్టు_2 DE;
Save the మిగిలిన general purpose registers.
   నెట్టు_2 BC
MOVW AX, usCriticalNesting;
Save the usCriticalNesting విలువ.
   నెట్టు_2 AX
MOVW AX, pxCurrentTCB;
Save the దొంతర_2 సూచిక_3.
   MOVW HL, AX
MOVW AX, SP
        MOVW[ HL ], AX
        ENDM
;
------------------------------------------------------------------------------

;
------------------------------------------------------------------------------
;
పోర్టు_RESTORE_CONTEXT MACRO
;
Restores the task దొంతర_2 సూచిక_2 then use this గమ్యం restore usCriticalNesting,
;
general purpose registers and the CS and ES( only లోపల far జ్ఞాపకం బహుళకం_2 )
;
యొక్క the selected task from the task దొంతర
;
------------------------------------------------------------------------------
పోర్టు_RESTORE_CONTEXT MACRO
MOVW AX, pxCurrentTCB;
Restore the దొంతర_2 సూచిక_3.
   MOVW HL, AX
MOVW AX, [ HL ]
MOVW SP, AX
తీయి_2 AX;
Restore usCriticalNesting విలువ.
   MOVW usCriticalNesting, AX
తీయి_2 BC;
Restore the necessary general purpose registers.
   తీయి_2 DE
తీయి_2 AX;
Restore the ES నమోదు.
   MOV ES, A
XCH A, X;
Restore the CS నమోదు.
   MOV CS, A
తీయి_2 HL;
Restore general purpose నమోదు HL.
   తీయి_2 AX;
Restore AX.
   ENDM
;
------------------------------------------------------------------------------
