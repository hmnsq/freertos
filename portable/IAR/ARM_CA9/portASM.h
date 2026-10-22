;/*
; * FreeRTOS Kernel <DEVELOPMENT BRANCH>
; * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
; *
; * SPDX-License-Identifier: MIT
; *
; * Permission is hereby granted, free of charge, to any person obtaining a copy of
; * this software and associated documentation files (the "Software"), to deal in
; * the Software without restriction, including without limitation the rights to
; * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
; * the Software, and to permit persons to whom the Software is furnished to do so,
; * subject to the following conditions:
; *
; * The above copyright notice and this permission notice shall be included in all
; * copies or substantial portions of the Software.
; *
; * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
; * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
; * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
; * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
; *
; * https://www.FreeRTOS.org
; * https://github.com/FreeRTOS
; *
; */

    EXTERN  vTaskSwitchContext
    EXTERN  ulCriticalNesting
    EXTERN  pxCurrentTCB
    EXTERN  ul_ಪೋರ್ಟ್_Task_Has_FPUContext
    EXTERN  ul_Asm_APIPriority_ಮುಖವಾಡ

ಪೋರ್ಟ್_SAVE_CONTEXT macro

    ; Save the LR and SPSR onto the system ಬಹುಲಕ_2 ರಾಶಿ before switching ಗಮ್ಯ
    ; system ಬಹುಲಕ_2 ಗಮ್ಯ save the ಉಳಿದ system ಬಹುಲಕ_2 registers
    SRSDB   sp!, #SYS_MODE
    CPS     #SYS_MODE
    ತಳ್ಳು_2    {R0-R12, R14}

    ; ತಳ್ಳು_3 the critical nesting ಎಣಿಕೆ_2
    LDR     R2, =ulCriticalNesting
    LDR     R1, [R2]
    ತಳ್ಳು_2    {R1}

    ; Does the task have a floating ಬಿಂದು_2 context that needs saving?  If
    ; ul_ಪೋರ್ಟ್_Task_Has_FPUContext is 0 then no.
    LDR     R2, =ul_ಪೋರ್ಟ್_Task_Has_FPUContext
    LDR     R3, [R2]
    CMP     R3, #0

    ; Save the floating ಬಿಂದು_2 context, ಆದರೆ any
    FMRXNE  R1,  FPSCR
    VPUSHNE {D0-D15}
    VPUSHNE {D16-D31}
    PUSHNE  {R1}

    ; Save ul_ಪೋರ್ಟ್_Task_Has_FPUContext itself
    ತಳ್ಳು_2    {R3}

    ; Save the ರಾಶಿ ಸೂಚಕ_3 ಒಳ the TCB
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    STR     SP, [R1]

    endm

; /**********************************************************************/

ಪೋರ್ಟ್_RESTORE_CONTEXT macro

    ; ಗಣ_2 the SP ಗಮ್ಯ ಬಿಂದು_2 ಗಮ್ಯ the ರಾಶಿ ದ the task being restored.
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    LDR     SP, [R1]

    ; Is there a floating ಬಿಂದು_2 context ಗಮ್ಯ restore?  If the restored
    ; ul_ಪೋರ್ಟ್_Task_Has_FPUContext is zero then no.
    LDR     R0, =ul_ಪೋರ್ಟ್_Task_Has_FPUContext
    ತೆಗೆ_3     {R1}
    STR     R1, [R0]
    CMP     R1, #0

    ; Restore the floating ಬಿಂದು_2 context, ಆದರೆ any
    POPNE   {R0}
    VPOPNE  {D16-D31}
    VPOPNE  {D0-D15}
    VMSRNE  FPSCR, R0

    ; Restore the critical section nesting ಆಳ
    LDR     R0, =ulCriticalNesting
    ತೆಗೆ_3     {R1}
    STR     R1, [R0]

    ; Ensure the ಆದ್ಯತೆ ಮುಖವಾಡ is correct ಗಾಗಿ the critical nesting ಆಳ
    LDR     R2, =ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್_ವಿಳಾಸ
    CMP     R1, #0
    MOVEQ   R4, #255
    LDRNE   R4, =( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು )
    STR     R4, [r2]

    ; Restore all system ಬಹುಲಕ_2 registers other than the SP (which is already
    ; being ಬಳಸಿದ)
    ತೆಗೆ_3     {R0-R12, R14}

    ; Return ಗಮ್ಯ the task ಸಂಕೇತ_2, loading CPSR on the way.
    RFEIA   sp!

    endm
