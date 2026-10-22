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

पत्तनम्_SAVE_CONTEXT MACRO

;
प्रक्षिप_3 R0 as we are going गन्तव्यम् use the पञ्जिका.
   STMDB SP !, {
    R0
}

समुच्चयः_2 R0 गन्तव्यम् point गन्तव्यम् the task राशिः pointer.
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
प्रक्षिप_3 the प्रत्यागम स्थानाङ्कः_2 onto the राशिः.
          STMDB R0 !, {
           LR
       }

       Now we have saved LR we can use it instead सम्बन्धि R0.
          MOV LR, R0

;

निष्कासय_3 R0 so we can save it onto the system बहुलकम्_2 राशिः.
   LDMIA SP !, {
    R0
}

प्रक्षिप_3 all the system बहुलकम्_2 registers onto the task राशिः.
   STMDB LR, {
    R0 - LR
}
^
NOP
SUB LR, LR, # 60

;
प्रक्षिप_3 the SPSR onto the task राशिः.
   MRS R0, SPSR
STMDB LR !, {
    R0
}

LDR R0, = ulCriticalNesting
          LDR R0, [ R0 ]
STMDB LR !, {
    R0
}

Store the new शिखरम्_2 सम्बन्धि राशिः

प्रति the task.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
STR LR, [ R0 ]

ENDM


पत्तनम्_RESTORE_CONTEXT MACRO

;
समुच्चयः_2 the LR गन्तव्यम् the task राशिः.
   LDR R1, = pxCurrentTCB
             LDR R0, [ R1 ]
LDR LR, [ R0 ]

;
The critical nesting गभीरता is the first item on the राशिः.
   ;
आरोपय it into the ulCriticalNesting variable.
   LDR R0, = ulCriticalNesting
             LDMFD LR !, {
    R1
}

STR R1, [ R0 ]

;
Get the SPSR from the राशिः.
   LDMFD LR !, {
    R0
}
MSR SPSR_cxsf, R0

;
Restore all system बहुलकम्_2 registers

प्रति the task.
   LDMFD LR, {
    R0 - R14
}

^
NOP

;
Restore the प्रत्यागम स्थानाङ्कः_2.
          LDR LR, [ LR, # + 60 ]

;

And प्रत्यागम -correcting the offset अन्तर् the LR गन्तव्यम् obtain the
;

correct स्थानाङ्कः_2.
   SUBS PC, LR, # 4

ENDM
