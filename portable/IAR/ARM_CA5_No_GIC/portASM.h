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
    EXTERN  ul_پورٹ_Task_Has_FPUContext
    EXTERN  ul_Asm_APIPriority_نقاب

پورٹ_SAVE_CONTEXT macro

    ; Save the LR and SPSR onto the system منوال_2 ڈھیر before switching مقصد
    ; system منوال_2 مقصد save the بقایا system منوال_2 registers
    SRSDB   sp!, #SYS_MODE
    CPS     #SYS_MODE
    ڈالو_2    {R0-R12, R14}

    ; ڈالو_3 the critical nesting گنتی
    LDR     R2, =ulCriticalNesting
    LDR     R1, [R2]
    ڈالو_2    {R1}

    ; Does the task have a floating نقطہ_2 context that needs saving?  If
    ; ul_پورٹ_Task_Has_FPUContext is 0 then no.
    LDR     R2, =ul_پورٹ_Task_Has_FPUContext
    LDR     R3, [R2]
    CMP     R3, #0

    ; Save the floating نقطہ_2 context, اگر any
    FMRXNE  R1,  FPSCR
    VPUSHNE {D0-D15}
#اگر configFPU_D32 == 1
    VPUSHNE {D16-D31}
#اگر_ختم ; configFPU_D32
    PUSHNE  {R1}

    ; Save ul_پورٹ_Task_Has_FPUContext itself
    ڈالو_2    {R3}

    ; Save the ڈھیر اشارہ_گر_2 اندر the TCB
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    STR     SP, [R1]

    endm

; /**********************************************************************/

پورٹ_RESTORE_CONTEXT macro

    ; سیٹ_2 the SP مقصد نقطہ_2 مقصد the ڈھیر کا the task being restored.
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    LDR     SP, [R1]

    ; Is there a floating نقطہ_2 context مقصد restore?  If the restored
    ; ul_پورٹ_Task_Has_FPUContext is zero then no.
    LDR     R0, =ul_پورٹ_Task_Has_FPUContext
    نکالو_2     {R1}
    STR     R1, [R0]
    CMP     R1, #0

    ; Restore the floating نقطہ_2 context, اگر any
    POPNE   {R0}
#اگر configFPU_D32 == 1
    VPOPNE  {D16-D31}
#اگر_ختم ; configFPU_D32
    VPOPNE  {D0-D15}
    VMSRNE  FPSCR, R0

    ; Restore the critical section nesting گہرائی
    LDR     R0, =ulCriticalNesting
    نکالو_2     {R1}
    STR     R1, [R0]

    ; Restore all system منوال_2 registers other than the SP (which is already
    ; being مستعمل)
    نکالو_2     {R0-R12, R14}

    ; Return مقصد the task رمز, loading CPSR on the way.  CPSR has the مداخلت
    ; enable ثنائی_ہندسہ_2 سیٹ appropriately برائے the task about مقصد execute.
    RFEIA   sp!

    endm
