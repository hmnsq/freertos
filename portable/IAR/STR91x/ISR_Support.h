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

پورت_SAVE_CONTEXT MACRO

;
افزودن_3 R0 as we are going مقصد use the سجل.
   STMDB SP !, {
    R0
}

مجموعه_2 R0 مقصد نقطه_2 مقصد the task پشته اشاره_گر_2.
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
افزودن_3 the أرجع آدرس_2 onto the پشته.
          STMDB R0 !, {
           LR
       }

       Now we have saved LR we can use it instead از R0.
          MOV LR, R0

;

برداشت_3 R0 so we can save it onto the system نما_2 پشته.
   LDMIA SP !, {
    R0
}

افزودن_3 all the system نما_2 registers onto the task پشته.
   STMDB LR, {
    R0 - LR
}
^
NOP
SUB LR, LR, # 60

;
افزودن_3 the SPSR onto the task پشته.
   MRS R0, SPSR
STMDB LR !, {
    R0
}

LDR R0, = ulCriticalNesting
          LDR R0, [ R0 ]
STMDB LR !, {
    R0
}

Store the new بالاترین_2 از پشته

لكل the task.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
STR LR, [ R0 ]

ENDM


پورت_RESTORE_CONTEXT MACRO

;
مجموعه_2 the LR مقصد the task پشته.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
LDR LR, [ R0 ]

;
The critical nesting عمق is the اولی_2 قلم on the پشته.
   ;
بارگیری it into the ulCriticalNesting variable.
   LDR R0, = ulCriticalNesting
             LDMFD LR !, {
    R1
}

STR R1, [ R0 ]

;
Get the SPSR from the پشته.
   LDMFD LR !, {
    R0
}
MSR SPSR_cxsf, R0

;
Restore all system نما_2 registers

لكل the task.
   LDMFD LR, {
    R0 - R14
}

^
NOP

;
Restore the أرجع آدرس_2.
          LDR LR, [ LR, # + 60 ]

;

And أرجع -correcting the offset درون the LR مقصد obtain the
;

correct آدرس_2.
   SUBS PC, LR, # 4

ENDM
