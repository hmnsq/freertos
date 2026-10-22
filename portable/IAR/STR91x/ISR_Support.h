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

ਪੋਰਟ_SAVE_CONTEXT MACRO

;
ਧੱਕੋ_3 R0 as we are going ਮੰਜ਼ਿਲ use the ਰਜਿਸਟਰ.
   STMDB SP !, {
    R0
}

ਸੈੱਟ_2 R0 ਮੰਜ਼ਿਲ ਬਿੰਦੂ_2 ਮੰਜ਼ਿਲ the task ਢੇਰ ਸੂਚਕ_2.
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
ਧੱਕੋ_3 the ਵਾਪਸ ਪਤਾ_2 onto the ਢੇਰ.
          STMDB R0 !, {
           LR
       }

       Now we have saved LR we can use it instead ਦਾ R0.
          MOV LR, R0

;

ਕੱਢੋ_3 R0 so we can save it onto the system ਬਹੁਲਕ_2 ਢੇਰ.
   LDMIA SP !, {
    R0
}

ਧੱਕੋ_3 all the system ਬਹੁਲਕ_2 registers onto the task ਢੇਰ.
   STMDB LR, {
    R0 - LR
}
^
NOP
SUB LR, LR, # 60

;
ਧੱਕੋ_3 the SPSR onto the task ਢੇਰ.
   MRS R0, SPSR
STMDB LR !, {
    R0
}

LDR R0, = ulCriticalNesting
          LDR R0, [ R0 ]
STMDB LR !, {
    R0
}

Store the new ਸਿਖਰ_2 ਦਾ ਢੇਰ

ਲਈ the task.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
STR LR, [ R0 ]

ENDM


ਪੋਰਟ_RESTORE_CONTEXT MACRO

;
ਸੈੱਟ_2 the LR ਮੰਜ਼ਿਲ the task ਢੇਰ.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
LDR LR, [ R0 ]

;
The critical nesting ਡੂੰਘਾਈ is the ਪਹਿਲਾ_2 ਵਸਤੂ_2 on the ਢੇਰ.
   ;
ਲੱਦੋ it into the ulCriticalNesting variable.
   LDR R0, = ulCriticalNesting
             LDMFD LR !, {
    R1
}

STR R1, [ R0 ]

;
Get the SPSR from the ਢੇਰ.
   LDMFD LR !, {
    R0
}
MSR SPSR_cxsf, R0

;
Restore all system ਬਹੁਲਕ_2 registers

ਲਈ the task.
   LDMFD LR, {
    R0 - R14
}

^
NOP

;
Restore the ਵਾਪਸ ਪਤਾ_2.
          LDR LR, [ LR, # + 60 ]

;

And ਵਾਪਸ -correcting the offset ਵਿੱਚ_2 the LR ਮੰਜ਼ਿਲ obtain the
;

correct ਪਤਾ_2.
   SUBS PC, LR, # 4

ENDM
