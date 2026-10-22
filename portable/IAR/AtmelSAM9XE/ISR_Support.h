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
EXTERN pxCurrentTCB
EXTERN ulCriticalNesting

;
Context save and restore macro definitions
;

portSAVE_CONTEXT MACRO

;
தள்ளு_3 R0 as we are going to use the பதிவு.
   STMDB SP !, {
    R0
}

Set R0 to point to the task அடுக்கு pointer.
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
தள்ளு_3 the திரும்பு address onto the அடுக்கு.
          STMDB R0 !, {
           LR
       }

       Now we have saved LR we can use it instead of R0.
          MOV LR, R0

;

எடு_3 R0 so we can save it onto the system mode அடுக்கு.
   LDMIA SP !, {
    R0
}

தள்ளு_3 all the system mode registers onto the task அடுக்கு.
   STMDB LR, {
    R0 - LR
}
^
NOP
SUB LR, LR, # 60

;
தள்ளு_3 the SPSR onto the task அடுக்கு.
   MRS R0, SPSR
STMDB LR !, {
    R0
}

LDR R0, = ulCriticalNesting
          LDR R0, [ R0 ]
STMDB LR !, {
    R0
}

Store the new உச்சி_2 of அடுக்கு

க்கு the task.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
STR LR, [ R0 ]

ENDM


portRESTORE_CONTEXT MACRO

;
Set the LR to the task அடுக்கு.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
LDR LR, [ R0 ]

;
The critical nesting depth is the first item on the அடுக்கு.
   ;
Load it into the ulCriticalNesting variable.
   LDR R0, = ulCriticalNesting
             LDMFD LR !, {
    R1
}

STR R1, [ R0 ]

;
Get the SPSR from the அடுக்கு.
   LDMFD LR !, {
    R0
}
MSR SPSR_cxsf, R0

;
Restore all system mode registers

க்கு the task.
   LDMFD LR, {
    R0 - R14
}

^
NOP

;
Restore the திரும்பு address.
          LDR LR, [ LR, # + 60 ]

;

And திரும்பு -correcting the offset in the LR to obtain the
;

correct address.
   SUBS PC, LR, # 4

ENDM
