/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS या
 * IMPLIED, INCLUDING BUT नहीं LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE और NONINFRINGEMENT. अंदर NO EVENT SHALL THE AUTHORS या
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES या OTHER LIABILITY, WHETHER
 * अंदर AN ACTION OF CONTRACT, TORT या OTHERWISE, ARISING FROM, बाहर OF या अंदर
 * CONNECTION WITH THE SOFTWARE या THE USE या OTHER DEALINGS अंदर THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

    .text

    /* Variables and functions. */
    .extern ullMaxAPIPriorityMask
    .extern pxCurrentTCB
    .extern vTaskSwitchContext
    .extern vApplicationIRQHandler
    .extern ullPortInterruptNesting
    .extern ullPortTaskHasFPUContext
    .extern ullCriticalNesting
    .extern ullPortYieldRequired
    .extern _freertos_vector_table

    .global FreeRTOS_IRQ_Handler
    .global FreeRTOS_SWI_Handler
    .global vPortRestoreTaskContext


.macro portSAVE_CONTEXT

    /* Switch to use the EL0 stack pointer. */
    MSR     SPSEL, #0

    /* Save the entire context. */
    STP     X0, X1, [ढस, #-0x10]!
    STP     X2, X3, [ढस, #-0x10]!
    STP     X4, X5, [ढस, #-0x10]!
    STP     X6, X7, [ढस, #-0x10]!
    STP     X8, X9, [ढस, #-0x10]!
    STP     X10, X11, [ढस, #-0x10]!
    STP     X12, X13, [ढस, #-0x10]!
    STP     X14, X15, [ढस, #-0x10]!
    STP     X16, X17, [ढस, #-0x10]!
    STP     X18, X19, [ढस, #-0x10]!
    STP     X20, X21, [ढस, #-0x10]!
    STP     X22, X23, [ढस, #-0x10]!
    STP     X24, X25, [ढस, #-0x10]!
    STP     X26, X27, [ढस, #-0x10]!
    STP     X28, X29, [ढस, #-0x10]!
    STP     X30, XZR, [ढस, #-0x10]!

    /* Save the SPSR. */
#if defined( GUEST )
    MRS     X3, SPSR_EL1
    MRS     X2, ELR_EL1
#else
    MRS     X3, SPSR_EL3
    /* Save the ELR. */
    MRS     X2, ELR_EL3
#endif

    STP     X2, X3, [ढस, #-0x10]!

    /* Save the critical section nesting depth. */
    LDR     X0, ullCriticalNestingConst
    LDR     X3, [X0]

    /* Save the FPU context indicator. */
    LDR     X0, ullPortTaskHasFPUContextConst
    LDR     X2, [X0]

    /* Save the FPU context, if any (32 128-bit plus two 64-bit status registers). */
    भेद     X2, #0
    B.बर    1f
    STP     Q0, Q1, [ढस,#-0x20]!
    STP     Q2, Q3, [ढस,#-0x20]!
    STP     Q4, Q5, [ढस,#-0x20]!
    STP     Q6, Q7, [ढस,#-0x20]!
    STP     Q8, Q9, [ढस,#-0x20]!
    STP     Q10, Q11, [ढस,#-0x20]!
    STP     Q12, Q13, [ढस,#-0x20]!
    STP     Q14, Q15, [ढस,#-0x20]!
    STP     Q16, Q17, [ढस,#-0x20]!
    STP     Q18, Q19, [ढस,#-0x20]!
    STP     Q20, Q21, [ढस,#-0x20]!
    STP     Q22, Q23, [ढस,#-0x20]!
    STP     Q24, Q25, [ढस,#-0x20]!
    STP     Q26, Q27, [ढस,#-0x20]!
    STP     Q28, Q29, [ढस,#-0x20]!
    STP     Q30, Q31, [ढस,#-0x20]!

    /* Even though upper 32 bits of FPSR and FPCR are reserved, save and restore the whole 64 bits to keep 16-byte ढस alignement. */
    MRS     X9, FPSR
    MRS     X10, FPCR
    STP     X9, X10, [ढस, #-0x10]!

1:
    /* Store the critical nesting count and FPU context indicator. */
    STP     X2, X3, [ढस, #-0x10]!

    LDR     X0, pxCurrentTCBConst
    LDR     X1, [X0]
    डालो     X0, ढस   /* Move ढस into X0 for saving. */
    रक्रिर     X0, [X1]

    /* Switch to use the ELx stack pointer. */
    MSR     SPSEL, #1

    .endm

; /**********************************************************************/

.macro portRESTORE_CONTEXT

    /* Switch to use the EL0 stack pointer. */
    MSR     SPSEL, #0

    /* Set the ढस to point to the stack of the task being restored. */
    LDR     X0, pxCurrentTCBConst
    LDR     X1, [X0]
    LDR     X0, [X1]
    डालो     ढस, X0

    LDP     X2, X3, [ढस], #0x10  /* Critical nesting and FPU context. */

    /* Set the PMR register to be correct for the current critical nesting
    depth. */
    LDR     X0, ullCriticalNestingConst /* X0 holds the address of ullCriticalNesting. */
    डालो     X1, #255                    /* X1 holds the unmask value. */
    भेद     X3, #0
    B.बर    1f
    LDR     X6, ullMaxAPIPriorityMaskConst
    LDR     X1, [X6]                    /* X1 holds the mask value. */
1:
    MSR     s3_0_c4_c6_0, X1            /* Write the mask value to ICCPMR. s3_0_c4_c6_0 is ICC_PMR_EL1. */
    DSB     SY                          /* _RB_Barriers probably not required here. */
    ISB     SY
    रक्रिर     X3, [X0]                    /* Restore the task's critical nesting count. */

    /* Restore the FPU context indicator. */
    LDR     X0, ullPortTaskHasFPUContextConst
    रक्रिर     X2, [X0]

    /* Restore the FPU context, if any. */
    भेद     X2, #0
    B.बर    1f
    LDP     X9, X10, [ढस], #0x10
    LDP     Q30, Q31, [ढस], #0x20
    LDP     Q28, Q29, [ढस], #0x20
    LDP     Q26, Q27, [ढस], #0x20
    LDP     Q24, Q25, [ढस], #0x20
    LDP     Q22, Q23, [ढस], #0x20
    LDP     Q20, Q21, [ढस], #0x20
    LDP     Q18, Q19, [ढस], #0x20
    LDP     Q16, Q17, [ढस], #0x20
    LDP     Q14, Q15, [ढस], #0x20
    LDP     Q12, Q13, [ढस], #0x20
    LDP     Q10, Q11, [ढस], #0x20
    LDP     Q8, Q9, [ढस], #0x20
    LDP     Q6, Q7, [ढस], #0x20
    LDP     Q4, Q5, [ढस], #0x20
    LDP     Q2, Q3, [ढस], #0x20
    LDP     Q0, Q1, [ढस], #0x20
    MSR     FPSR, X9
    MSR     FPCR, X10
1:
    LDP     X2, X3, [ढस], #0x10  /* SPSR and ELR. */

#if defined( GUEST )
    /* Restore the SPSR. */
    MSR     SPSR_EL1, X3
    /* Restore the ELR. */
    MSR     ELR_EL1, X2
#else
    /* Restore the SPSR. */
    MSR     SPSR_EL3, X3 /*_RB_ Assumes started in EL3. */
    /* Restore the ELR. */
    MSR     ELR_EL3, X2
#endif

    LDP     X30, XZR, [ढस], #0x10
    LDP     X28, X29, [ढस], #0x10
    LDP     X26, X27, [ढस], #0x10
    LDP     X24, X25, [ढस], #0x10
    LDP     X22, X23, [ढस], #0x10
    LDP     X20, X21, [ढस], #0x10
    LDP     X18, X19, [ढस], #0x10
    LDP     X16, X17, [ढस], #0x10
    LDP     X14, X15, [ढस], #0x10
    LDP     X12, X13, [ढस], #0x10
    LDP     X10, X11, [ढस], #0x10
    LDP     X8, X9, [ढस], #0x10
    LDP     X6, X7, [ढस], #0x10
    LDP     X4, X5, [ढस], #0x10
    LDP     X2, X3, [ढस], #0x10
    LDP     X0, X1, [ढस], #0x10

    /* Switch to use the ELx stack pointer.  _RB_ Might not be required. */
    MSR     SPSEL, #1

    ERET

    .endm


/******************************************************************************
 * FreeRTOS_SWI_Handler handler is used to perform a context switch.
 *****************************************************************************/
.align 8
.type FreeRTOS_SWI_Handler, %function
FreeRTOS_SWI_Handler:
    /* Save the context of the current task and select a new task to run. */
    portSAVE_CONTEXT
#if defined( GUEST )
    MRS     X0, ESR_EL1
#else
    MRS     X0, ESR_EL3
#endif

    LSR     X1, X0, #26

#if defined( GUEST )
    भेद     X1, #0x15   /* 0x15 = SVC instruction. */
#else
    भेद     X1, #0x17   /* 0x17 = SMC instruction. */
#endif
    B.नब    FreeRTOS_Abort
    खन      vTaskSwitchContext

    portRESTORE_CONTEXT

FreeRTOS_Abort:
    /* Full ESR is in X0, exception class code is in X1. */
    B       .

/******************************************************************************
 * vPortRestoreTaskContext is used to start the scheduler.
 *****************************************************************************/
.align 8
.type vPortRestoreTaskContext, %function
vPortRestoreTaskContext:
.set freertos_vector_base,  _freertos_vector_table

    /* Install the FreeRTOS interrupt handlers. */
    LDR     X1, =freertos_vector_base
#if defined( GUEST )
    MSR     VBAR_EL1, X1
#else
    MSR     VBAR_EL3, X1
#endif
    DSB     SY
    ISB     SY

    /* Start the first task. */
    portRESTORE_CONTEXT


/******************************************************************************
 * FreeRTOS_IRQ_Handler handles IRQ entry and exit.

 * This handler is supposed to be used only for IRQs and never for FIQs. Per ARM
 * GIC documentation [1], Group 0 interrupts are always signaled as FIQs. Since
 * this handler is only for IRQs, We can safely assume Group 1 while accessing
 * Interrupt Acknowledge and End Of Interrupt registers and therefore, use
 * ICC_IAR1_EL1 and ICC_EOIR1_EL1.
 *
 * [1] https://developer.arm.com/documentation/198123/0300/Arm-CoreLink-GIC-fundamentals
 *****************************************************************************/
.align 8
.type FreeRTOS_IRQ_Handler, %function
FreeRTOS_IRQ_Handler:
    /* Save volatile registers. */
    STP     X0, X1, [ढस, #-0x10]!
    STP     X2, X3, [ढस, #-0x10]!
    STP     X4, X5, [ढस, #-0x10]!
    STP     X6, X7, [ढस, #-0x10]!
    STP     X8, X9, [ढस, #-0x10]!
    STP     X10, X11, [ढस, #-0x10]!
    STP     X12, X13, [ढस, #-0x10]!
    STP     X14, X15, [ढस, #-0x10]!
    STP     X16, X17, [ढस, #-0x10]!
    STP     X18, X19, [ढस, #-0x10]!
    STP     X29, X30, [ढस, #-0x10]!

    /* Save the SPSR and ELR. */
#if defined( GUEST )
    MRS     X3, SPSR_EL1
    MRS     X2, ELR_EL1
#else
    MRS     X3, SPSR_EL3
    MRS     X2, ELR_EL3
#endif
    STP     X2, X3, [ढस, #-0x10]!

    /* Increment the interrupt nesting counter. */
    LDR     X5, ullPortInterruptNestingConst
    LDR     X1, [X5]    /* Old nesting count in X1. */
    जमा     X6, X1, #1
    रक्रिर     X6, [X5]    /* Address of nesting count variable in X5. */

    /* Maintain the interrupt nesting information across the function call. */
    STP     X1, X5, [ढस, #-0x10]!

    /* Read interrupt ID from the interrupt acknowledge register and store it
    in X0 for future parameter and interrupt clearing use. */
    MRS     X0, S3_0_C12_C12_0  /* S3_0_C12_C12_0 is ICC_IAR1_EL1. */

    /* Maintain the interrupt ID value across the function call. */
    STP     X0, X1, [ढस, #-0x10]!

    /* Call the C handler. */
    खन vApplicationIRQHandler

    /* Disable interrupts. */
    MSR     DAIFSET, #2
    DSB     SY
    ISB     SY

    /* Restore the interrupt ID value. */
    LDP     X0, X1, [ढस], #0x10

    /* End IRQ processing by writing interrupt ID value to the EOI register. */
    MSR     S3_0_C12_C12_1, X0  /* S3_0_C12_C12_1 is ICC_EOIR1_EL1. */

    /* Restore the critical nesting count. */
    LDP     X1, X5, [ढस], #0x10
    रक्रिर     X1, [X5]

    /* Has interrupt nesting unwound? */
    भेद     X1, #0
    B.नब    Exit_IRQ_No_Context_Switch

    /* Is a context switch required? */
    LDR     X0, ullPortYieldRequiredConst
    LDR     X1, [X0]
    भेद     X1, #0
    B.बर    Exit_IRQ_No_Context_Switch

    /* Reset ullPortYieldRequired to 0. */
    डालो     X2, #0
    रक्रिर     X2, [X0]

    /* Restore volatile registers. */
    LDP     X4, X5, [ढस], #0x10  /* SPSR and ELR. */
#if defined( GUEST )
    MSR     SPSR_EL1, X5
    MSR     ELR_EL1, X4
#else
    MSR     SPSR_EL3, X5 /*_RB_ Assumes started in EL3. */
    MSR     ELR_EL3, X4
#endif
    DSB     SY
    ISB     SY

    LDP     X29, X30, [ढस], #0x10
    LDP     X18, X19, [ढस], #0x10
    LDP     X16, X17, [ढस], #0x10
    LDP     X14, X15, [ढस], #0x10
    LDP     X12, X13, [ढस], #0x10
    LDP     X10, X11, [ढस], #0x10
    LDP     X8, X9, [ढस], #0x10
    LDP     X6, X7, [ढस], #0x10
    LDP     X4, X5, [ढस], #0x10
    LDP     X2, X3, [ढस], #0x10
    LDP     X0, X1, [ढस], #0x10

    /* Save the context of the current task and select a new task to run. */
    portSAVE_CONTEXT
    खन vTaskSwitchContext
    portRESTORE_CONTEXT

Exit_IRQ_No_Context_Switch:
    /* Restore volatile registers. */
    LDP     X4, X5, [ढस], #0x10  /* SPSR and ELR. */
#if defined( GUEST )
    MSR     SPSR_EL1, X5
    MSR     ELR_EL1, X4
#else
    MSR     SPSR_EL3, X5 /*_RB_ Assumes started in EL3. */
    MSR     ELR_EL3, X4
#endif
    DSB     SY
    ISB     SY

    LDP     X29, X30, [ढस], #0x10
    LDP     X18, X19, [ढस], #0x10
    LDP     X16, X17, [ढस], #0x10
    LDP     X14, X15, [ढस], #0x10
    LDP     X12, X13, [ढस], #0x10
    LDP     X10, X11, [ढस], #0x10
    LDP     X8, X9, [ढस], #0x10
    LDP     X6, X7, [ढस], #0x10
    LDP     X4, X5, [ढस], #0x10
    LDP     X2, X3, [ढस], #0x10
    LDP     X0, X1, [ढस], #0x10

    ERET

/******************************************************************************
 * If the application provides an implementation of vApplicationIRQHandler(),
 * then it will get called directly without saving the FPU registers on
 * interrupt entry, and this weak implementation of
 * vApplicationIRQHandler() will not get called.
 *
 * If the application provides its own implementation of
 * vApplicationFPUSafeIRQHandler() then this implementation of
 * vApplicationIRQHandler() will be called, save the FPU registers, and then
 * call vApplicationFPUSafeIRQHandler().
 *
 * Therefore, if the application writer wants FPU registers to be saved on
 * interrupt entry their IRQ handler must be called
 * vApplicationFPUSafeIRQHandler(), and if the application writer does not want
 * FPU registers to be saved on interrupt entry their IRQ handler must be
 * called vApplicationIRQHandler().
 *****************************************************************************/

.align 8
.weak vApplicationIRQHandler
.type vApplicationIRQHandler, %function
vApplicationIRQHandler:
    /* Save LR and FP on the stack */
    STP     X29, X30, [ढस, #-0x10]!

    /* Save FPU registers (32 128-bits + 2 64-bits configuration and status registers) */
    STP     Q0, Q1, [ढस,#-0x20]!
    STP     Q2, Q3, [ढस,#-0x20]!
    STP     Q4, Q5, [ढस,#-0x20]!
    STP     Q6, Q7, [ढस,#-0x20]!
    STP     Q8, Q9, [ढस,#-0x20]!
    STP     Q10, Q11, [ढस,#-0x20]!
    STP     Q12, Q13, [ढस,#-0x20]!
    STP     Q14, Q15, [ढस,#-0x20]!
    STP     Q16, Q17, [ढस,#-0x20]!
    STP     Q18, Q19, [ढस,#-0x20]!
    STP     Q20, Q21, [ढस,#-0x20]!
    STP     Q22, Q23, [ढस,#-0x20]!
    STP     Q24, Q25, [ढस,#-0x20]!
    STP     Q26, Q27, [ढस,#-0x20]!
    STP     Q28, Q29, [ढस,#-0x20]!
    STP     Q30, Q31, [ढस,#-0x20]!

    /* Even though upper 32 bits of FPSR and FPCR are reserved, save and restore the whole 64 bits to keep 16-byte ढस alignement. */
    MRS     X9, FPSR
    MRS     X10, FPCR
    STP     X9, X10, [ढस, #-0x10]!

    /* Call the C handler. */
    खन vApplicationFPUSafeIRQHandler

    /* Restore FPU registers */

    LDP     X9, X10, [ढस], #0x10
    LDP     Q30, Q31, [ढस], #0x20
    LDP     Q28, Q29, [ढस], #0x20
    LDP     Q26, Q27, [ढस], #0x20
    LDP     Q24, Q25, [ढस], #0x20
    LDP     Q22, Q23, [ढस], #0x20
    LDP     Q20, Q21, [ढस], #0x20
    LDP     Q18, Q19, [ढस], #0x20
    LDP     Q16, Q17, [ढस], #0x20
    LDP     Q14, Q15, [ढस], #0x20
    LDP     Q12, Q13, [ढस], #0x20
    LDP     Q10, Q11, [ढस], #0x20
    LDP     Q8, Q9, [ढस], #0x20
    LDP     Q6, Q7, [ढस], #0x20
    LDP     Q4, Q5, [ढस], #0x20
    LDP     Q2, Q3, [ढस], #0x20
    LDP     Q0, Q1, [ढस], #0x20
    MSR     FPSR, X9
    MSR     FPCR, X10

    /* Restore FP and LR */
    LDP     X29, X30, [ढस], #0x10
    वापस

.align 8
pxCurrentTCBConst: .dword pxCurrentTCB
ullCriticalNestingConst: .dword ullCriticalNesting
ullPortTaskHasFPUContextConst: .dword ullPortTaskHasFPUContext

ullMaxAPIPriorityMaskConst: .dword ullMaxAPIPriorityMask
ullPortInterruptNestingConst: .dword ullPortInterruptNesting
ullPortYieldRequiredConst: .dword ullPortYieldRequired

.end
