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
    EXTERN  ul_पत्तनम्_Task_Has_FPUContext
    EXTERN  ul_Asm_APIPriority_आवरणम्

पत्तनम्_SAVE_CONTEXT macro

    ; Save the LR and SPSR onto the system बहुलकम्_2 राशिः before switching गन्तव्यम्
    ; system बहुलकम्_2 गन्तव्यम् save the remaining system बहुलकम्_2 registers
    SRSDB   sp!, #SYS_MODE
    CPS     #SYS_MODE
    प्रक्षिप_2    {R0-R12, R14}

    ; प्रक्षिप_3 the critical nesting गणनम्
    LDR     R2, =ulCriticalNesting
    LDR     R1, [R2]
    प्रक्षिप_2    {R1}

    ; Does the task have a floating point context that needs saving?  If
    ; ul_पत्तनम्_Task_Has_FPUContext is 0 then no.
    LDR     R2, =ul_पत्तनम्_Task_Has_FPUContext
    LDR     R3, [R2]
    CMP     R3, #0

    ; Save the floating point context, यदि any
    FMRXNE  R1,  FPSCR
    VPUSHNE {D0-D15}
    VPUSHNE {D16-D31}
    PUSHNE  {R1}

    ; Save ul_पत्तनम्_Task_Has_FPUContext itself
    प्रक्षिप_2    {R3}

    ; Save the राशिः pointer अन्तर् the TCB
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    STR     SP, [R1]

    endm

; /**********************************************************************/

पत्तनम्_RESTORE_CONTEXT macro

    ; समुच्चयः_2 the SP गन्तव्यम् point गन्तव्यम् the राशिः सम्बन्धि the task being restored.
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    LDR     SP, [R1]

    ; Is there a floating point context गन्तव्यम् restore?  If the restored
    ; ul_पत्तनम्_Task_Has_FPUContext is zero then no.
    LDR     R0, =ul_पत्तनम्_Task_Has_FPUContext
    निष्कासय_2     {R1}
    STR     R1, [R0]
    CMP     R1, #0

    ; Restore the floating point context, यदि any
    POPNE   {R0}
    VPOPNE  {D16-D31}
    VPOPNE  {D0-D15}
    VMSRNE  FPSCR, R0

    ; Restore the critical section nesting गभीरता
    LDR     R0, =ulCriticalNesting
    निष्कासय_2     {R1}
    STR     R1, [R0]

    ; Ensure the प्राथमिकता आवरणम् is correct प्रति the critical nesting गभीरता
    LDR     R2, =पत्तनम्_ICCPMR_प्राथमिकता_आवरणम्_पञ्जिकाकोशः_स्थानाङ्कः
    CMP     R1, #0
    MOVEQ   R4, #255
    LDRNE   R4, =( config_MAX_API_CALL_व्यवधानम्_प्राथमिकता << पत्तनम्_प्राथमिकता_सरणम् )
    STR     R4, [r2]

    ; Restore all system बहुलकम्_2 registers other than the SP (which is already
    ; being प्रयुक्तम्)
    निष्कासय_2     {R0-R12, R14}

    ; Return गन्तव्यम् the task संहिता, loading CPSR on the way.
    RFEIA   sp!

    endm
