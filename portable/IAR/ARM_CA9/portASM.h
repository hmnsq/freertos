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
    EXTERN  ul_ਪੋਰਟ_Task_Has_FPUContext
    EXTERN  ul_Asm_APIPriority_ਨਕਾਬ

ਪੋਰਟ_SAVE_CONTEXT macro

    ; Save the LR and SPSR onto the system ਬਹੁਲਕ_2 ਢੇਰ before switching ਮੰਜ਼ਿਲ
    ; system ਬਹੁਲਕ_2 ਮੰਜ਼ਿਲ save the ਬਚਿਆ system ਬਹੁਲਕ_2 registers
    SRSDB   sp!, #SYS_MODE
    CPS     #SYS_MODE
    ਧੱਕੋ_2    {R0-R12, R14}

    ; ਧੱਕੋ_3 the critical nesting ਗਿਣਤੀ_2
    LDR     R2, =ulCriticalNesting
    LDR     R1, [R2]
    ਧੱਕੋ_2    {R1}

    ; Does the task have a floating ਬਿੰਦੂ_2 context that needs saving?  If
    ; ul_ਪੋਰਟ_Task_Has_FPUContext is 0 then no.
    LDR     R2, =ul_ਪੋਰਟ_Task_Has_FPUContext
    LDR     R3, [R2]
    CMP     R3, #0

    ; Save the floating ਬਿੰਦੂ_2 context, ਜੇ any
    FMRXNE  R1,  FPSCR
    VPUSHNE {D0-D15}
    VPUSHNE {D16-D31}
    PUSHNE  {R1}

    ; Save ul_ਪੋਰਟ_Task_Has_FPUContext itself
    ਧੱਕੋ_2    {R3}

    ; Save the ਢੇਰ ਸੂਚਕ_2 ਵਿੱਚ_2 the TCB
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    STR     SP, [R1]

    endm

; /**********************************************************************/

ਪੋਰਟ_RESTORE_CONTEXT macro

    ; ਸੈੱਟ_2 the SP ਮੰਜ਼ਿਲ ਬਿੰਦੂ_2 ਮੰਜ਼ਿਲ the ਢੇਰ ਦਾ the task being restored.
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    LDR     SP, [R1]

    ; Is there a floating ਬਿੰਦੂ_2 context ਮੰਜ਼ਿਲ restore?  If the restored
    ; ul_ਪੋਰਟ_Task_Has_FPUContext is zero then no.
    LDR     R0, =ul_ਪੋਰਟ_Task_Has_FPUContext
    ਕੱਢੋ_2     {R1}
    STR     R1, [R0]
    CMP     R1, #0

    ; Restore the floating ਬਿੰਦੂ_2 context, ਜੇ any
    POPNE   {R0}
    VPOPNE  {D16-D31}
    VPOPNE  {D0-D15}
    VMSRNE  FPSCR, R0

    ; Restore the critical section nesting ਡੂੰਘਾਈ
    LDR     R0, =ulCriticalNesting
    ਕੱਢੋ_2     {R1}
    STR     R1, [R0]

    ; Ensure the ਤਰਜੀਹ ਨਕਾਬ is correct ਲਈ the critical nesting ਡੂੰਘਾਈ
    LDR     R2, =ਪੋਰਟ_ICCPMR_ਤਰਜੀਹ_ਨਕਾਬ_ਰਜਿਸਟਰ_ਪਤਾ
    CMP     R1, #0
    MOVEQ   R4, #255
    LDRNE   R4, =( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ )
    STR     R4, [r2]

    ; Restore all system ਬਹੁਲਕ_2 registers other than the SP (which is already
    ; being ਵਰਤਿਆ)
    ਕੱਢੋ_2     {R0-R12, R14}

    ; Return ਮੰਜ਼ਿਲ the task ਕੋਡ, loading CPSR on the way.
    RFEIA   sp!

    endm
