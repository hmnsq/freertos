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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTCONTEXT_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTCONTEXT_H

#ಆದರೆ __riscv_xlen == 64
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ    8
    #ವ್ಯಾಖ್ಯಾನಿಸು store_x          sd
    #ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_x           ld
#ಅಥವಾಆದರೆ __riscv_xlen == 32
    #ವ್ಯಾಖ್ಯಾನಿಸು store_x          sw
    #ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_x           lw
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ    4
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ Assembler did not define __riscv_xlen
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __riscv_32e
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONTEXT_ಗಾತ್ರ               ( 15 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CRITICAL_NESTING_ಸ್ಥಾನಾಂತರ    13
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MSTATUS_ಸ್ಥಾನಾಂತರ             14
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONTEXT_ಗಾತ್ರ               ( 31 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CRITICAL_NESTING_ಸ್ಥಾನಾಂತರ    29
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MSTATUS_ಸ್ಥಾನಾಂತರ             30
#ಆದರೆ_ಅಂತ್ಯ

EXTERN pxCurrentTCB
EXTERN x_ISRStack_ತುದಿ
EXTERN xCriticalNesting
EXTERN pxCriticalNesting

/*-----------------------------------------------------------*/

portcontext_SAVE_CONTEXT_ಆಂತರಿಕ MACRO
addi sp, sp, -ಪೋರ್ಟ್_CONTEXT_ಗಾತ್ರ
store_x x1, 1 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x5, 2 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x6, 3 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x7, 4 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x8, 5 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x9, 6 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x10, 7 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x11, 8 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x12, 9 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x13, 10 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x14, 11 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x15, 12 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __riscv_32e
    store_x x16, 13 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x17, 14 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x18, 15 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x19, 16 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x20, 17 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x21, 18 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x22, 19 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x23, 20 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x24, 21 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x25, 22 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x26, 23 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x27, 24 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x28, 25 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x29, 26 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x30, 27 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x31, 28 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
#ಆದರೆ_ಅಂತ್ಯ /* ifndef __riscv_32e */

ತುಂಬು_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, ಪೋರ್ಟ್_CRITICAL_NESTING_ಸ್ಥಾನಾಂತರ * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp ) /* Store the critical nesting value to the stack. */

csrr t0, mstatus                                              /* Required for MPIE bit. */
store_x t0, ಪೋರ್ಟ್_MSTATUS_ಸ್ಥಾನಾಂತರ * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

ತುಂಬು_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

ENDM
/*-----------------------------------------------------------*/

portcontextSAVE_EXCEPTION_CONTEXT MACRO
portcontext_SAVE_CONTEXT_ಆಂತರಿಕ
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
ತುಂಬು_x sp, x_ISRStack_ತುದಿ /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontext_SAVE_ಅಡಚಣೆ_CONTEXT MACRO
portcontext_SAVE_CONTEXT_ಆಂತರಿಕ
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
ತುಂಬು_x sp, x_ISRStack_ತುದಿ /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontextRESTORE_CONTEXT MACRO
ತುಂಬು_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
ತುಂಬು_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
ತುಂಬು_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Load mstatus with the interrupt enable bits used by the task. */
ತುಂಬು_x t0, ಪೋರ್ಟ್_MSTATUS_ಸ್ಥಾನಾಂತರ * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
csrw mstatus, t0                                             /* Required for MPIE bit. */

ತುಂಬು_x t0, ಪೋರ್ಟ್_CRITICAL_NESTING_ಸ್ಥಾನಾಂತರ * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
ತುಂಬು_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

ತುಂಬು_x x1, 1 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x5, 2 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x6, 3 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x7, 4 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x8, 5 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x9, 6 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x10, 7 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x11, 8 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x12, 9 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x13, 10 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x14, 11 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x15, 12 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __riscv_32e
    ತುಂಬು_x x16, 13 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x17, 14 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x18, 15 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x19, 16 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x20, 17 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x21, 18 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x22, 19 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x23, 20 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x24, 21 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x25, 22 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x26, 23 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x27, 24 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x28, 25 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x29, 26 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x30, 27 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x31, 28 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
#ಆದರೆ_ಅಂತ್ಯ /* ifndef __riscv_32e */
addi sp, sp, ಪೋರ್ಟ್_CONTEXT_ಗಾತ್ರ

mret
ENDM
/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* PORTCONTEXT_H */
