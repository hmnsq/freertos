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
    EXTERN  ul_پورټ_Task_Has_FPUContext
    EXTERN  ul_Asm_APIPriority_ماسک

پورټ_SAVE_CONTEXT macro

    ; Save the LR and SPSR onto the system ډېرپېښ_2 ډېری before switching منزل
    ; system ډېرپېښ_2 منزل save the پاتې_شوی system ډېرپېښ_2 registers
    SRSDB   sp!, #SYS_MODE
    CPS     #SYS_MODE
    ټېل_2    {R0-R12, R14}

    ; ټېل_3 the critical nesting شمېر
    LDR     R2, =ulCriticalNesting
    LDR     R1, [R2]
    ټېل_2    {R1}

    ; Does the task have a floating ټکی_2 context that needs saving?  If
    ; ul_پورټ_Task_Has_FPUContext is 0 then no.
    LDR     R2, =ul_پورټ_Task_Has_FPUContext
    LDR     R3, [R2]
    CMP     R3, #0

    ; Save the floating ټکی_2 context, إذا any
    FMRXNE  R1,  FPSCR
    VPUSHNE {D0-D15}
    VPUSHNE {D16-D31}
    PUSHNE  {R1}

    ; Save ul_پورټ_Task_Has_FPUContext itself
    ټېل_2    {R3}

    ; Save the ډېری اشاره_ګر_2 دننه the TCB
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    STR     SP, [R1]

    endm

; /**********************************************************************/

پورټ_RESTORE_CONTEXT macro

    ; سېټ_2 the SP منزل ټکی_2 منزل the ډېری د the task being restored.
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    LDR     SP, [R1]

    ; Is there a floating ټکی_2 context منزل restore?  If the restored
    ; ul_پورټ_Task_Has_FPUContext is zero then no.
    LDR     R0, =ul_پورټ_Task_Has_FPUContext
    راوباسه_2     {R1}
    STR     R1, [R0]
    CMP     R1, #0

    ; Restore the floating ټکی_2 context, إذا any
    POPNE   {R0}
    VPOPNE  {D16-D31}
    VPOPNE  {D0-D15}
    VMSRNE  FPSCR, R0

    ; Restore the critical section nesting ژوروالی
    LDR     R0, =ulCriticalNesting
    راوباسه_2     {R1}
    STR     R1, [R0]

    ; Ensure the لومړیتوب ماسک is correct لكل the critical nesting ژوروالی
    LDR     R2, =پورټ_ICCPMR_لومړیتوب_ماسک_ثبتوونکی_پته
    CMP     R1, #0
    MOVEQ   R4, #255
    LDRNE   R4, =( config_MAX_API_CALL_مداخله_لومړیتوب << پورټ_لومړیتوب_ښويدنه )
    STR     R4, [r2]

    ; Restore all system ډېرپېښ_2 registers other than the SP (which is already
    ; being کارول_شوی)
    راوباسه_2     {R0-R12, R14}

    ; Return منزل the task کوډ, loading CPSR on the way.
    RFEIA   sp!

    endm
