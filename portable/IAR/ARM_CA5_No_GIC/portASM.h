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

    ; Save the LR and SPSR onto the system mode স্তূপ before switching to
    ; system mode to save the remaining system mode registers
    SRSDB   sp!, #SYS_MODE
    CPS     #SYS_MODE
    ঠেলো_2    {R0-R12, R14}

    ; ঠেলো_3 the critical nesting গুনতি
    LDR     R2, =ulCriticalNesting
    LDR     R1, [R2]
    ঠেলো_2    {R1}

    ; Does the task have a floating point context that needs saving?  If
    ; ulPortTaskHasFPUContext is 0 then no.
    LDR     R2, =ulPortTaskHasFPUContext
    LDR     R3, [R2]
    CMP     R3, #0

    ; Save the floating point context, যদি any
    FMRXNE  R1,  FPSCR
    VPUSHNE {D0-D15}
#যদি configFPU_D32 == 1
    VPUSHNE {D16-D31}
#endif ; configFPU_D32
    PUSHNE  {R1}

    ; Save ulPortTaskHasFPUContext itself
    ঠেলো_2    {R3}

    ; Save the স্তূপ pointer in the TCB
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    STR     SP, [R1]

    endm

; /**********************************************************************/

portRESTORE_CONTEXT macro

    ; Set the SP to point to the স্তূপ of the task being restored.
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    LDR     SP, [R1]

    ; Is there a floating point context to restore?  If the restored
    ; ulPortTaskHasFPUContext is zero then no.
    LDR     R0, =ulPortTaskHasFPUContext
    বের_করো_2     {R1}
    STR     R1, [R0]
    CMP     R1, #0

    ; Restore the floating point context, যদি any
    POPNE   {R0}
#যদি configFPU_D32 == 1
    VPOPNE  {D16-D31}
#endif ; configFPU_D32
    VPOPNE  {D0-D15}
    VMSRNE  FPSCR, R0

    ; Restore the critical section nesting depth
    LDR     R0, =ulCriticalNesting
    বের_করো_2     {R1}
    STR     R1, [R0]

    ; Restore all system mode registers other than the SP (which is already
    ; being used)
    বের_করো_2     {R0-R12, R14}

    ; Return to the task code, loading CPSR on the way.  CPSR has the interrupt
    ; enable bit set appropriately জন্য the task about to execute.
    RFEIA   sp!

    endm
