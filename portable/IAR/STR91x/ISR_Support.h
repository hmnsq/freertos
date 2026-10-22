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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

EXTERN pxCurrentTCB
EXTERN ulCriticalNesting

;
Context save and restore macro definitions
;

పోర్టు_SAVE_CONTEXT MACRO

;
నెట్టు_3 R0 as we are going గమ్యం use the నమోదు.
   STMDB SP !, {
    R0
}

సమితి_2 R0 గమ్యం బిందువు_2 గమ్యం the task దొంతర సూచిక_3.
   STMDB SP, {
    SP
}
^
NOP
SUB SP, SP, # 4
LDMIA SP !, {
    R0
}

;
నెట్టు_3 the తిరిగి చిరునామా_2 onto the దొంతర.
          STMDB R0 !, {
           LR
       }

       Now we have saved LR we can use it instead యొక్క R0.
          MOV LR, R0

;

తీయి_3 R0 so we can save it onto the system బహుళకం_2 దొంతర.
   LDMIA SP !, {
    R0
}

నెట్టు_3 all the system బహుళకం_2 registers onto the task దొంతర.
   STMDB LR, {
    R0 - LR
}
^
NOP
SUB LR, LR, # 60

;
నెట్టు_3 the SPSR onto the task దొంతర.
   MRS R0, SPSR
STMDB LR !, {
    R0
}

LDR R0, = ulCriticalNesting
          LDR R0, [ R0 ]
STMDB LR !, {
    R0
}

Store the new శిఖరం_2 యొక్క దొంతర

కొరకు the task.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
STR LR, [ R0 ]

ENDM


పోర్టు_RESTORE_CONTEXT MACRO

;
సమితి_2 the LR గమ్యం the task దొంతర.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
LDR LR, [ R0 ]

;
The critical nesting లోతు is the మొదటి_2 అంశం on the దొంతర.
   ;
ఎక్కించు it into the ulCriticalNesting variable.
   LDR R0, = ulCriticalNesting
             LDMFD LR !, {
    R1
}

STR R1, [ R0 ]

;
Get the SPSR from the దొంతర.
   LDMFD LR !, {
    R0
}
MSR SPSR_cxsf, R0

;
Restore all system బహుళకం_2 registers

కొరకు the task.
   LDMFD LR, {
    R0 - R14
}

^
NOP

;
Restore the తిరిగి చిరునామా_2.
          LDR LR, [ LR, # + 60 ]

;

And తిరిగి -correcting the offset లోపల the LR గమ్యం obtain the
;

correct చిరునామా_2.
   SUBS PC, LR, # 4

ENDM
