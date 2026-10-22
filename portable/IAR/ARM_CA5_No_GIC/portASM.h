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
    EXTERN  ul_పోర్టు_Task_Has_FPUContext
    EXTERN  ul_Asm_APIPriority_ముసుగు

పోర్టు_SAVE_CONTEXT macro

    ; Save the LR and SPSR onto the system బహుళకం_2 దొంతర before switching గమ్యం
    ; system బహుళకం_2 గమ్యం save the మిగిలిన system బహుళకం_2 registers
    SRSDB   sp!, #SYS_MODE
    CPS     #SYS_MODE
    నెట్టు_2    {R0-R12, R14}

    ; నెట్టు_3 the critical nesting లెక్క
    LDR     R2, =ulCriticalNesting
    LDR     R1, [R2]
    నెట్టు_2    {R1}

    ; Does the task have a floating బిందువు_2 context that needs saving?  If
    ; ul_పోర్టు_Task_Has_FPUContext is 0 then no.
    LDR     R2, =ul_పోర్టు_Task_Has_FPUContext
    LDR     R3, [R2]
    CMP     R3, #0

    ; Save the floating బిందువు_2 context, ఒకవేళ any
    FMRXNE  R1,  FPSCR
    VPUSHNE {D0-D15}
#ఒకవేళ configFPU_D32 == 1
    VPUSHNE {D16-D31}
#అయితే_ముగింపు ; configFPU_D32
    PUSHNE  {R1}

    ; Save ul_పోర్టు_Task_Has_FPUContext itself
    నెట్టు_2    {R3}

    ; Save the దొంతర సూచిక_3 లోపల the TCB
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    STR     SP, [R1]

    endm

; /**********************************************************************/

పోర్టు_RESTORE_CONTEXT macro

    ; సమితి_2 the SP గమ్యం బిందువు_2 గమ్యం the దొంతర యొక్క the task being restored.
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    LDR     SP, [R1]

    ; Is there a floating బిందువు_2 context గమ్యం restore?  If the restored
    ; ul_పోర్టు_Task_Has_FPUContext is zero then no.
    LDR     R0, =ul_పోర్టు_Task_Has_FPUContext
    తీయి_2     {R1}
    STR     R1, [R0]
    CMP     R1, #0

    ; Restore the floating బిందువు_2 context, ఒకవేళ any
    POPNE   {R0}
#ఒకవేళ configFPU_D32 == 1
    VPOPNE  {D16-D31}
#అయితే_ముగింపు ; configFPU_D32
    VPOPNE  {D0-D15}
    VMSRNE  FPSCR, R0

    ; Restore the critical section nesting లోతు
    LDR     R0, =ulCriticalNesting
    తీయి_2     {R1}
    STR     R1, [R0]

    ; Restore all system బహుళకం_2 registers other than the SP (which is already
    ; being వాడిన)
    తీయి_2     {R0-R12, R14}

    ; Return గమ్యం the task సంకేతం_2, loading CPSR on the way.  CPSR has the అంతరాయం
    ; enable బిట్టు_2 సమితి appropriately కొరకు the task about గమ్యం execute.
    RFEIA   sp!

    endm
