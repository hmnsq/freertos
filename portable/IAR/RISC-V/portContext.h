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

#جيڪڏهن_وصف_نه_ٿيل PORTCONTEXT_H
#وصف_ڪريو PORTCONTEXT_H

#إذا __riscv_xlen == 64
    #وصف_ڪريو پورٽ_لفظ_سائيز    8
    #وصف_ڪريو store_x          sd
    #وصف_ڪريو ڀريو_x           ld
#وإلاإذا __riscv_xlen == 32
    #وصف_ڪريو store_x          sw
    #وصف_ڪريو ڀريو_x           lw
    #وصف_ڪريو پورٽ_لفظ_سائيز    4
#وإلا
    #غلطي Assembler did not define __riscv_xlen
#جيڪڏهن_پورو

#ضمن "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#جيڪڏهن_وصف_ٿيل __riscv_32e
    #وصف_ڪريو پورٽ_CONTEXT_سائيز               ( 15 * پورٽ_لفظ_سائيز )
    #وصف_ڪريو پورٽ_CRITICAL_NESTING_وٿي    13
    #وصف_ڪريو پورٽ_MSTATUS_وٿي             14
#وإلا
    #وصف_ڪريو پورٽ_CONTEXT_سائيز               ( 31 * پورٽ_لفظ_سائيز )
    #وصف_ڪريو پورٽ_CRITICAL_NESTING_وٿي    29
    #وصف_ڪريو پورٽ_MSTATUS_وٿي             30
#جيڪڏهن_پورو

EXTERN pxCurrentTCB
EXTERN x_ISRStack_چوٽي
EXTERN xCriticalNesting
EXTERN pxCriticalNesting

/*-----------------------------------------------------------*/

portcontext_SAVE_CONTEXT_اندروني MACRO
addi sp, sp, -پورٽ_CONTEXT_سائيز
store_x x1, 1 * پورٽ_لفظ_سائيز( sp )
store_x x5, 2 * پورٽ_لفظ_سائيز( sp )
store_x x6, 3 * پورٽ_لفظ_سائيز( sp )
store_x x7, 4 * پورٽ_لفظ_سائيز( sp )
store_x x8, 5 * پورٽ_لفظ_سائيز( sp )
store_x x9, 6 * پورٽ_لفظ_سائيز( sp )
store_x x10, 7 * پورٽ_لفظ_سائيز( sp )
store_x x11, 8 * پورٽ_لفظ_سائيز( sp )
store_x x12, 9 * پورٽ_لفظ_سائيز( sp )
store_x x13, 10 * پورٽ_لفظ_سائيز( sp )
store_x x14, 11 * پورٽ_لفظ_سائيز( sp )
store_x x15, 12 * پورٽ_لفظ_سائيز( sp )
#جيڪڏهن_وصف_نه_ٿيل __riscv_32e
    store_x x16, 13 * پورٽ_لفظ_سائيز( sp )
    store_x x17, 14 * پورٽ_لفظ_سائيز( sp )
    store_x x18, 15 * پورٽ_لفظ_سائيز( sp )
    store_x x19, 16 * پورٽ_لفظ_سائيز( sp )
    store_x x20, 17 * پورٽ_لفظ_سائيز( sp )
    store_x x21, 18 * پورٽ_لفظ_سائيز( sp )
    store_x x22, 19 * پورٽ_لفظ_سائيز( sp )
    store_x x23, 20 * پورٽ_لفظ_سائيز( sp )
    store_x x24, 21 * پورٽ_لفظ_سائيز( sp )
    store_x x25, 22 * پورٽ_لفظ_سائيز( sp )
    store_x x26, 23 * پورٽ_لفظ_سائيز( sp )
    store_x x27, 24 * پورٽ_لفظ_سائيز( sp )
    store_x x28, 25 * پورٽ_لفظ_سائيز( sp )
    store_x x29, 26 * پورٽ_لفظ_سائيز( sp )
    store_x x30, 27 * پورٽ_لفظ_سائيز( sp )
    store_x x31, 28 * پورٽ_لفظ_سائيز( sp )
#جيڪڏهن_پورو /* ifndef __riscv_32e */

ڀريو_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, پورٽ_CRITICAL_NESTING_وٿي * پورٽ_لفظ_سائيز( sp ) /* Store the critical nesting value to the stack. */

csrr t0, mstatus                                              /* Required for MPIE bit. */
store_x t0, پورٽ_MSTATUS_وٿي * پورٽ_لفظ_سائيز( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

ڀريو_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

ENDM
/*-----------------------------------------------------------*/

portcontextSAVE_EXCEPTION_CONTEXT MACRO
portcontext_SAVE_CONTEXT_اندروني
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
ڀريو_x sp, x_ISRStack_چوٽي /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontext_SAVE_مداخلت_CONTEXT MACRO
portcontext_SAVE_CONTEXT_اندروني
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
ڀريو_x sp, x_ISRStack_چوٽي /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontextRESTORE_CONTEXT MACRO
ڀريو_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
ڀريو_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
ڀريو_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Load mstatus with the interrupt enable bits used by the task. */
ڀريو_x t0, پورٽ_MSTATUS_وٿي * پورٽ_لفظ_سائيز( sp )
csrw mstatus, t0                                             /* Required for MPIE bit. */

ڀريو_x t0, پورٽ_CRITICAL_NESTING_وٿي * پورٽ_لفظ_سائيز( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
ڀريو_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

ڀريو_x x1, 1 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x5, 2 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x6, 3 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x7, 4 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x8, 5 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x9, 6 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x10, 7 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x11, 8 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x12, 9 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x13, 10 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x14, 11 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x15, 12 * پورٽ_لفظ_سائيز( sp )
#جيڪڏهن_وصف_نه_ٿيل __riscv_32e
    ڀريو_x x16, 13 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x17, 14 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x18, 15 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x19, 16 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x20, 17 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x21, 18 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x22, 19 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x23, 20 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x24, 21 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x25, 22 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x26, 23 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x27, 24 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x28, 25 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x29, 26 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x30, 27 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x31, 28 * پورٽ_لفظ_سائيز( sp )
#جيڪڏهن_پورو /* ifndef __riscv_32e */
addi sp, sp, پورٽ_CONTEXT_سائيز

mret
ENDM
/*-----------------------------------------------------------*/

#جيڪڏهن_پورو /* PORTCONTEXT_H */
