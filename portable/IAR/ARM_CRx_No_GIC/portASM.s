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

#include "FreeRTOSConfig.h"

    SECTION .text:CODE:ROOT(2)
    arm

    /* Variables and functions. */
    EXTERN pxCurrentTCB
    EXTERN vTaskSwitchContext
    EXTERN vApplicationIRQHandler
    EXTERN ulPortInterruptNesting
    EXTERN ulPortTaskHasFPUContext
    EXTERN ulPortYieldRequired
    EXTERN ulCriticalNesting

    सार्व FreeRTOS_IRQ_Handler
    सार्व FreeRTOS_SVC_Handler
    सार्व vPortRestoreTaskContext

SYS_MODE            सम     0x1f
SVC_MODE            सम     0x13
IRQ_MODE            सम     0x12

portSAVE_CONTEXT सक्रिया

    /* Save the LR and SPSR onto the system mode stack before switching to
    system mode to save the remaining system mode registers. */
    SRSDB   sp!, #SYS_MODE
    CPS     #SYS_MODE
    दो    {R0-R12, R14}

    /* Push the critical nesting count. */
    LDR     R2, =ulCriticalNesting
    LDR     R1, [R2]
    दो    {R1}

    /* Does the task have a floating point context that needs saving?  If
    ulPortTaskHasFPUContext is 0 then no. */
    LDR     R2, =ulPortTaskHasFPUContext
    LDR     R3, [R2]
    भेद     R3, #0

    /* Save the floating point context, if any. */
    FMRXNE  R1,  FPSCR
    VPUSHNE {D0-D15}
#if configFPU_D32 == 1
    VPUSHNE {D16-D31}
#endif /* configFPU_D32 */
    PUSHNE  {R1}

    /* Save ulPortTaskHasFPUContext itself. */
    दो    {R3}

    /* Save the stack pointer in the TCB. */
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    रक्रिर     ढस, [R1]

    पूर्ण_सक्रिया

; /**********************************************************************/

portRESTORE_CONTEXT सक्रिया

    /* Set the ढस to point to the stack of the task being restored. */
    LDR     R0, =pxCurrentTCB
    LDR     R1, [R0]
    LDR     ढस, [R1]

    /* Is there a floating point context to restore?  If the restored
    ulPortTaskHasFPUContext is zero then no. */
    LDR     R0, =ulPortTaskHasFPUContext
    लो     {R1}
    रक्रिर     R1, [R0]
    भेद     R1, #0

    /* Restore the floating point context, if any. */
    POPNE   {R0}
#if configFPU_D32 == 1
    VPOPNE  {D16-D31}
#endif /* configFPU_D32 */
    VPOPNE  {D0-D15}
    VMSRNE  FPSCR, R0

    /* Restore the critical section nesting depth. */
    LDR     R0, =ulCriticalNesting
    लो     {R1}
    रक्रिर     R1, [R0]

    /* Restore all system mode registers other than the ढस (which is already
    being used). */
    लो     {R0-R12, R14}

    /* Return to the task code, loading CPSR on the way. */
    RFEIA   sp!

    पूर्ण_सक्रिया




/******************************************************************************
 * SVC handler is used to yield.
 *****************************************************************************/
FreeRTOS_SVC_Handler:
    /* Save the context of the current task and select a new task to run. */
    portSAVE_CONTEXT
    LDR R0, =vTaskSwitchContext
    BLX R0
    portRESTORE_CONTEXT


/******************************************************************************
 * vPortRestoreTaskContext is used to start the scheduler.
 *****************************************************************************/
vPortRestoreTaskContext:
    /* Switch to system mode. */
    CPS     #SYS_MODE
    portRESTORE_CONTEXT

FreeRTOS_IRQ_Handler:
    /* Return to the interrupted instruction. */
    घटा     lr, lr, #4

    /* Push the return address and SPSR. */
    दो    {lr}
    MRS     lr, SPSR
    दो    {lr}

    /* Change to supervisor mode to allow reentry. */
    CPS     #SVC_MODE

    /* Push used registers. */
    दो    {r0-r3, r12}

    /* Increment nesting count.  r3 holds the address of ulPortInterruptNesting
    for future use.  r1 holds the original ulPortInterruptNesting value for
    future use. */
    LDR     r3, =ulPortInterruptNesting
    LDR     r1, [r3]
    जमा     r0, r1, #1
    रक्रिर     r0, [r3]

    /* Ensure bit 2 of the stack pointer is clear.  r2 holds the bit 2 value for
    future use. */
    डालो     r0, sp
    और     r2, r0, #4
    घटा     sp, sp, r2

    /* Call the interrupt handler. */
    दो    {r0-r3, lr}
    LDR     r1, =vApplicationIRQHandler
    BLX     r1
    लो     {r0-r3, lr}
    जमा     sp, sp, r2

    CPSID   i
    DSB
    ISB

    /* Write to the EOI register. */
    LDR     r2, =configEOI_ADDRESS
    रक्रिर     r0, [r2]

    /* Restore the old nesting count. */
    रक्रिर     r1, [r3]

    /* A context switch is never performed if the nesting count is not 0. */
    भेद     r1, #0
    BNE     exit_without_switch

    /* Did the interrupt request a context switch?  r1 holds the address of
    ulPortYieldRequired and r0 the value of ulPortYieldRequired for future
    use. */
    LDR     r1, =ulPortYieldRequired
    LDR     r0, [r1]
    भेद     r0, #0
    BNE     switch_before_exit

exit_without_switch:
    /* No context switch.  Restore used registers, LR_irq and SPSR before
    returning. */
    लो     {r0-r3, r12}
    CPS     #IRQ_MODE
    लो     {LR}
    MSR     SPSR_cxsf, LR
    लो     {LR}
    MOVS    PC, LR

switch_before_exit:
    /* A context switch is to be performed.  Clear the context switch pending
    flag. */
    डालो     r0, #0
    रक्रिर     r0, [r1]

    /* Restore used registers, LR-irq and SPSR before saving the context
    to the task stack. */
    लो     {r0-r3, r12}
    CPS     #IRQ_MODE
    लो     {LR}
    MSR     SPSR_cxsf, LR
    लो     {LR}
    portSAVE_CONTEXT

    /* Call the function that selects the new task to execute.
    vTaskSwitchContext() if vTaskSwitchContext() uses LDRD or STRD
    instructions, or 8 byte aligned stack allocated data.  LR does not need
    saving as a new LR will be loaded by portRESTORE_CONTEXT anyway. */
    LDR     R0, =vTaskSwitchContext
    BLX     R0

    /* Restore the context of, and branch to, the task selected to execute
    next. */
    portRESTORE_CONTEXT

    पूर्ण
