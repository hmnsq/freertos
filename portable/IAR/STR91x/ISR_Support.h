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

ಪೋರ್ಟ್_SAVE_CONTEXT MACRO

;
ತಳ್ಳು_3 R0 as we are going ಗಮ್ಯ use the ನೋಂದಣಿ.
   STMDB SP !, {
    R0
}

ಗಣ_2 R0 ಗಮ್ಯ ಬಿಂದು_2 ಗಮ್ಯ the task ರಾಶಿ ಸೂಚಕ_3.
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
ತಳ್ಳು_3 the ಹಿಂತಿರುಗಿ ವಿಳಾಸ_2 onto the ರಾಶಿ.
          STMDB R0 !, {
           LR
       }

       Now we have saved LR we can use it instead ದ R0.
          MOV LR, R0

;

ತೆಗೆ_4 R0 so we can save it onto the system ಬಹುಲಕ_2 ರಾಶಿ.
   LDMIA SP !, {
    R0
}

ತಳ್ಳು_3 all the system ಬಹುಲಕ_2 registers onto the task ರಾಶಿ.
   STMDB LR, {
    R0 - LR
}
^
NOP
SUB LR, LR, # 60

;
ತಳ್ಳು_3 the SPSR onto the task ರಾಶಿ.
   MRS R0, SPSR
STMDB LR !, {
    R0
}

LDR R0, = ulCriticalNesting
          LDR R0, [ R0 ]
STMDB LR !, {
    R0
}

Store the new ತುದಿ_2 ದ ರಾಶಿ

ಗಾಗಿ the task.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
STR LR, [ R0 ]

ENDM


ಪೋರ್ಟ್_RESTORE_CONTEXT MACRO

;
ಗಣ_2 the LR ಗಮ್ಯ the task ರಾಶಿ.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
LDR LR, [ R0 ]

;
The critical nesting ಆಳ is the ಮೊದಲ_2 ಅಂಶ on the ರಾಶಿ.
   ;
ತುಂಬು it into the ulCriticalNesting variable.
   LDR R0, = ulCriticalNesting
             LDMFD LR !, {
    R1
}

STR R1, [ R0 ]

;
Get the SPSR from the ರಾಶಿ.
   LDMFD LR !, {
    R0
}
MSR SPSR_cxsf, R0

;
Restore all system ಬಹುಲಕ_2 registers

ಗಾಗಿ the task.
   LDMFD LR, {
    R0 - R14
}

^
NOP

;
Restore the ಹಿಂತಿರುಗಿ ವಿಳಾಸ_2.
          LDR LR, [ LR, # + 60 ]

;

And ಹಿಂತಿರುಗಿ -correcting the offset ಒಳ the LR ಗಮ್ಯ obtain the
;

correct ವಿಳಾಸ_2.
   SUBS PC, LR, # 4

ENDM
