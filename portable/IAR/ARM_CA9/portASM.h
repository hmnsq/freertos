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
    EXTERN  ulPortTaskHasFPUContext
    EXTERN  ulAsmAPIPriorityMask

portSAVE_CONTEXT macro

    ; Save the LR and SPSR onto the system mode ರಾಶಿ before switching to
    ; system mode to save the remaining system mode registers
    SRSDB   sp!, #SYS_MODE
    CPS     #SYS_MODE
    ತಳ್ಳು_2    {R0-R12, R14}

    ; ತಳ್ಳು_3 the critical nesting ಎಣಿಕೆ
    LDR     R2, =ulCriticalNesting
    LDR     R1, [R2]
    ತಳ್ಳು_2    {R1}

    ; Does the task have a floating point context that needs saving?  If
    ; ulPortTaskHasFPUContext is 0 then no.
    LDR     R2, =ulPortTaskHasFPUContext
    LDR     R3, [R2]
    CMP     R3, #0

    ; Save the floating point context, ಯದಿ any
    FMRXNE  R1,  FPSCR
    VPUSHNE {D0-D15}
    VPUSHNE {D16-D31}
    PUSHNE  {R1}

    ; Save ulPortTaskHasFPUContext itself
    ತಳ್ಳು_2    {R3}

    ; Save the ರಾಶಿ pointer in the TCB
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    STR     SP, [R1]

    endm

; /**********************************************************************/

portRESTORE_CONTEXT macro

    ; Set the SP to point to the ರಾಶಿ of the task being restored.
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    LDR     SP, [R1]

    ; Is there a floating point context to restore?  If the restored
    ; ulPortTaskHasFPUContext is zero then no.
    LDR     R0, =ulPortTaskHasFPUContext
    ತೆಗೆ_2     {R1}
    STR     R1, [R0]
    CMP     R1, #0

    ; Restore the floating point context, ಯದಿ any
    POPNE   {R0}
    VPOPNE  {D16-D31}
    VPOPNE  {D0-D15}
    VMSRNE  FPSCR, R0

    ; Restore the critical section nesting depth
    LDR     R0, =ulCriticalNesting
    ತೆಗೆ_2     {R1}
    STR     R1, [R0]

    ; Ensure the priority mask is correct ಪ್ರತಿ the critical nesting depth
    LDR     R2, =portICCPMR_PRIORITY_MASK_REGISTER_ADDRESS
    CMP     R1, #0
    MOVEQ   R4, #255
    LDRNE   R4, =( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT )
    STR     R4, [r2]

    ; Restore all system mode registers other than the SP (which is already
    ; being used)
    ತೆಗೆ_2     {R0-R12, R14}

    ; Return to the task code, loading CPSR on the way.
    RFEIA   sp!

    endm
