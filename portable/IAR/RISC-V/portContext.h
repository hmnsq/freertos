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

#که_نه_تعریف_شوی PORTCONTEXT_H
#تعریف_کړه PORTCONTEXT_H

#إذا __riscv_xlen == 64
    #تعریف_کړه پورټ_کلمه_اندازه    8
    #تعریف_کړه store_x          sd
    #تعریف_کړه بارول_x           ld
#وإلاإذا __riscv_xlen == 32
    #تعریف_کړه store_x          sw
    #تعریف_کړه بارول_x           lw
    #تعریف_کړه پورټ_کلمه_اندازه    4
#وإلا
    #تېروتنه Assembler did not define __riscv_xlen
#د_که_پای

#ضمن "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#که_تعریف_شوی __riscv_32e
    #تعریف_کړه پورټ_CONTEXT_اندازه               ( 15 * پورټ_کلمه_اندازه )
    #تعریف_کړه پورټ_CRITICAL_NESTING_دننه_واټن    13
    #تعریف_کړه پورټ_MSTATUS_دننه_واټن             14
#وإلا
    #تعریف_کړه پورټ_CONTEXT_اندازه               ( 31 * پورټ_کلمه_اندازه )
    #تعریف_کړه پورټ_CRITICAL_NESTING_دننه_واټن    29
    #تعریف_کړه پورټ_MSTATUS_دننه_واټن             30
#د_که_پای

EXTERN pxCurrentTCB
EXTERN x_ISRStack_سر
EXTERN xCriticalNesting
EXTERN pxCriticalNesting

/*-----------------------------------------------------------*/

portcontext_SAVE_CONTEXT_دننی MACRO
addi sp, sp, -پورټ_CONTEXT_اندازه
store_x x1, 1 * پورټ_کلمه_اندازه( sp )
store_x x5, 2 * پورټ_کلمه_اندازه( sp )
store_x x6, 3 * پورټ_کلمه_اندازه( sp )
store_x x7, 4 * پورټ_کلمه_اندازه( sp )
store_x x8, 5 * پورټ_کلمه_اندازه( sp )
store_x x9, 6 * پورټ_کلمه_اندازه( sp )
store_x x10, 7 * پورټ_کلمه_اندازه( sp )
store_x x11, 8 * پورټ_کلمه_اندازه( sp )
store_x x12, 9 * پورټ_کلمه_اندازه( sp )
store_x x13, 10 * پورټ_کلمه_اندازه( sp )
store_x x14, 11 * پورټ_کلمه_اندازه( sp )
store_x x15, 12 * پورټ_کلمه_اندازه( sp )
#که_نه_تعریف_شوی __riscv_32e
    store_x x16, 13 * پورټ_کلمه_اندازه( sp )
    store_x x17, 14 * پورټ_کلمه_اندازه( sp )
    store_x x18, 15 * پورټ_کلمه_اندازه( sp )
    store_x x19, 16 * پورټ_کلمه_اندازه( sp )
    store_x x20, 17 * پورټ_کلمه_اندازه( sp )
    store_x x21, 18 * پورټ_کلمه_اندازه( sp )
    store_x x22, 19 * پورټ_کلمه_اندازه( sp )
    store_x x23, 20 * پورټ_کلمه_اندازه( sp )
    store_x x24, 21 * پورټ_کلمه_اندازه( sp )
    store_x x25, 22 * پورټ_کلمه_اندازه( sp )
    store_x x26, 23 * پورټ_کلمه_اندازه( sp )
    store_x x27, 24 * پورټ_کلمه_اندازه( sp )
    store_x x28, 25 * پورټ_کلمه_اندازه( sp )
    store_x x29, 26 * پورټ_کلمه_اندازه( sp )
    store_x x30, 27 * پورټ_کلمه_اندازه( sp )
    store_x x31, 28 * پورټ_کلمه_اندازه( sp )
#د_که_پای /* ifndef __riscv_32e */

بارول_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, پورټ_CRITICAL_NESTING_دننه_واټن * پورټ_کلمه_اندازه( sp ) /* Store the critical nesting value to the stack. */

csrr t0, mstatus                                              /* Required for MPIE bit. */
store_x t0, پورټ_MSTATUS_دننه_واټن * پورټ_کلمه_اندازه( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

بارول_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

ENDM
/*-----------------------------------------------------------*/

portcontextSAVE_EXCEPTION_CONTEXT MACRO
portcontext_SAVE_CONTEXT_دننی
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
بارول_x sp, x_ISRStack_سر /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontext_SAVE_مداخله_CONTEXT MACRO
portcontext_SAVE_CONTEXT_دننی
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
بارول_x sp, x_ISRStack_سر /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontextRESTORE_CONTEXT MACRO
بارول_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
بارول_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
بارول_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Load mstatus with the interrupt enable bits used by the task. */
بارول_x t0, پورټ_MSTATUS_دننه_واټن * پورټ_کلمه_اندازه( sp )
csrw mstatus, t0                                             /* Required for MPIE bit. */

بارول_x t0, پورټ_CRITICAL_NESTING_دننه_واټن * پورټ_کلمه_اندازه( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
بارول_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

بارول_x x1, 1 * پورټ_کلمه_اندازه( sp )
بارول_x x5, 2 * پورټ_کلمه_اندازه( sp )
بارول_x x6, 3 * پورټ_کلمه_اندازه( sp )
بارول_x x7, 4 * پورټ_کلمه_اندازه( sp )
بارول_x x8, 5 * پورټ_کلمه_اندازه( sp )
بارول_x x9, 6 * پورټ_کلمه_اندازه( sp )
بارول_x x10, 7 * پورټ_کلمه_اندازه( sp )
بارول_x x11, 8 * پورټ_کلمه_اندازه( sp )
بارول_x x12, 9 * پورټ_کلمه_اندازه( sp )
بارول_x x13, 10 * پورټ_کلمه_اندازه( sp )
بارول_x x14, 11 * پورټ_کلمه_اندازه( sp )
بارول_x x15, 12 * پورټ_کلمه_اندازه( sp )
#که_نه_تعریف_شوی __riscv_32e
    بارول_x x16, 13 * پورټ_کلمه_اندازه( sp )
    بارول_x x17, 14 * پورټ_کلمه_اندازه( sp )
    بارول_x x18, 15 * پورټ_کلمه_اندازه( sp )
    بارول_x x19, 16 * پورټ_کلمه_اندازه( sp )
    بارول_x x20, 17 * پورټ_کلمه_اندازه( sp )
    بارول_x x21, 18 * پورټ_کلمه_اندازه( sp )
    بارول_x x22, 19 * پورټ_کلمه_اندازه( sp )
    بارول_x x23, 20 * پورټ_کلمه_اندازه( sp )
    بارول_x x24, 21 * پورټ_کلمه_اندازه( sp )
    بارول_x x25, 22 * پورټ_کلمه_اندازه( sp )
    بارول_x x26, 23 * پورټ_کلمه_اندازه( sp )
    بارول_x x27, 24 * پورټ_کلمه_اندازه( sp )
    بارول_x x28, 25 * پورټ_کلمه_اندازه( sp )
    بارول_x x29, 26 * پورټ_کلمه_اندازه( sp )
    بارول_x x30, 27 * پورټ_کلمه_اندازه( sp )
    بارول_x x31, 28 * پورټ_کلمه_اندازه( sp )
#د_که_پای /* ifndef __riscv_32e */
addi sp, sp, پورټ_CONTEXT_اندازه

mret
ENDM
/*-----------------------------------------------------------*/

#د_که_پای /* PORTCONTEXT_H */
