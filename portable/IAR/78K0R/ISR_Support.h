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
Variables ورتیا by scheduler
;
------------------------------------------------------------------------------
EXTERN pxCurrentTCB
EXTERN usCriticalNesting

;
------------------------------------------------------------------------------
;
پورٹ_SAVE_CONTEXT MACRO
;
Saves the context دا the general purpose registers, CS and ES( only وچ far
                                                               ;
                                                               حافظہ منوال_2 ) registers the usCriticalNesting قدر_2 and the ڈھیر_2 اشارہ_گر
;
دا the سرگرم_2 Task onto the task ڈھیر
;
------------------------------------------------------------------------------
پورٹ_SAVE_CONTEXT MACRO

ڈالو_2 AX;
Save AX رجسٹر منزل ڈھیر.
   ڈالو_2 HL
MOV A, CS;
Save CS سجل.
   XCH A, X
MOV A, ES;
Save ES سجل.
   ڈالو_2 AX
ڈالو_2 DE;
Save the بچیا general purpose registers.
   ڈالو_2 BC
MOVW AX, usCriticalNesting;
Save the usCriticalNesting قدر.
   ڈالو_2 AX
MOVW AX, pxCurrentTCB;
Save the ڈھیر_2 اشارہ_گر_2.
   MOVW HL, AX
MOVW AX, SP
        MOVW[ HL ], AX
        ENDM
;
------------------------------------------------------------------------------

;
------------------------------------------------------------------------------
;
پورٹ_RESTORE_CONTEXT MACRO
;
Restores the task ڈھیر_2 اشارہ_گر then use this منزل restore usCriticalNesting,
;
general purpose registers and the CS and ES( only وچ far حافظہ منوال_2 )
;
دا the selected task from the task ڈھیر
;
------------------------------------------------------------------------------
پورٹ_RESTORE_CONTEXT MACRO
MOVW AX, pxCurrentTCB;
Restore the ڈھیر_2 اشارہ_گر_2.
   MOVW HL, AX
MOVW AX, [ HL ]
MOVW SP, AX
نکالو_2 AX;
Restore usCriticalNesting قدر.
   MOVW usCriticalNesting, AX
نکالو_2 BC;
Restore the necessary general purpose registers.
   نکالو_2 DE
نکالو_2 AX;
Restore the ES سجل.
   MOV ES, A
XCH A, X;
Restore the CS سجل.
   MOV CS, A
نکالو_2 HL;
Restore general purpose سجل HL.
   نکالو_2 AX;
Restore AX.
   ENDM
;
------------------------------------------------------------------------------
