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

#اگر_غیر_تعریف_شدہ PORTCONTEXT_H
#تعریف_کرو PORTCONTEXT_H

#اگر __riscv_xlen == 64
    #تعریف_کرو پورٹ_لفظ_سائز    8
    #تعریف_کرو store_x          sd
    #تعریف_کرو بھرو_x           ld
#وگرنہ_اگر __riscv_xlen == 32
    #تعریف_کرو store_x          sw
    #تعریف_کرو بھرو_x           lw
    #تعریف_کرو پورٹ_لفظ_سائز    4
#ورنہ
    #غلطی Assembler did not define __riscv_xlen
#اگر_ختم

#شامل "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#اگر_تعریف_شدہ __riscv_32e
    #تعریف_کرو پورٹ_CONTEXT_سائز               ( 15 * پورٹ_لفظ_سائز )
    #تعریف_کرو پورٹ_CRITICAL_NESTING_انحراف    13
    #تعریف_کرو پورٹ_MSTATUS_انحراف             14
#ورنہ
    #تعریف_کرو پورٹ_CONTEXT_سائز               ( 31 * پورٹ_لفظ_سائز )
    #تعریف_کرو پورٹ_CRITICAL_NESTING_انحراف    29
    #تعریف_کرو پورٹ_MSTATUS_انحراف             30
#اگر_ختم

EXTERN pxCurrentTCB
EXTERN x_ISRStack_چوٹی
EXTERN xCriticalNesting
EXTERN pxCriticalNesting

/*-----------------------------------------------------------*/

portcontext_SAVE_CONTEXT_اندرونی MACRO
addi sp, sp, -پورٹ_CONTEXT_سائز
store_x x1, 1 * پورٹ_لفظ_سائز( sp )
store_x x5, 2 * پورٹ_لفظ_سائز( sp )
store_x x6, 3 * پورٹ_لفظ_سائز( sp )
store_x x7, 4 * پورٹ_لفظ_سائز( sp )
store_x x8, 5 * پورٹ_لفظ_سائز( sp )
store_x x9, 6 * پورٹ_لفظ_سائز( sp )
store_x x10, 7 * پورٹ_لفظ_سائز( sp )
store_x x11, 8 * پورٹ_لفظ_سائز( sp )
store_x x12, 9 * پورٹ_لفظ_سائز( sp )
store_x x13, 10 * پورٹ_لفظ_سائز( sp )
store_x x14, 11 * پورٹ_لفظ_سائز( sp )
store_x x15, 12 * پورٹ_لفظ_سائز( sp )
#اگر_غیر_تعریف_شدہ __riscv_32e
    store_x x16, 13 * پورٹ_لفظ_سائز( sp )
    store_x x17, 14 * پورٹ_لفظ_سائز( sp )
    store_x x18, 15 * پورٹ_لفظ_سائز( sp )
    store_x x19, 16 * پورٹ_لفظ_سائز( sp )
    store_x x20, 17 * پورٹ_لفظ_سائز( sp )
    store_x x21, 18 * پورٹ_لفظ_سائز( sp )
    store_x x22, 19 * پورٹ_لفظ_سائز( sp )
    store_x x23, 20 * پورٹ_لفظ_سائز( sp )
    store_x x24, 21 * پورٹ_لفظ_سائز( sp )
    store_x x25, 22 * پورٹ_لفظ_سائز( sp )
    store_x x26, 23 * پورٹ_لفظ_سائز( sp )
    store_x x27, 24 * پورٹ_لفظ_سائز( sp )
    store_x x28, 25 * پورٹ_لفظ_سائز( sp )
    store_x x29, 26 * پورٹ_لفظ_سائز( sp )
    store_x x30, 27 * پورٹ_لفظ_سائز( sp )
    store_x x31, 28 * پورٹ_لفظ_سائز( sp )
#اگر_ختم /* ifndef __riscv_32e */

بھرو_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, پورٹ_CRITICAL_NESTING_انحراف * پورٹ_لفظ_سائز( sp ) /* Store the critical nesting value to the stack. */

csrr t0, mstatus                                              /* Required for MPIE bit. */
store_x t0, پورٹ_MSTATUS_انحراف * پورٹ_لفظ_سائز( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

بھرو_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

ENDM
/*-----------------------------------------------------------*/

portcontextSAVE_EXCEPTION_CONTEXT MACRO
portcontext_SAVE_CONTEXT_اندرونی
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
بھرو_x sp, x_ISRStack_چوٹی /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontext_SAVE_مداخلت_CONTEXT MACRO
portcontext_SAVE_CONTEXT_اندرونی
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
بھرو_x sp, x_ISRStack_چوٹی /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontextRESTORE_CONTEXT MACRO
بھرو_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
بھرو_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
بھرو_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Load mstatus with the interrupt enable bits used by the task. */
بھرو_x t0, پورٹ_MSTATUS_انحراف * پورٹ_لفظ_سائز( sp )
csrw mstatus, t0                                             /* Required for MPIE bit. */

بھرو_x t0, پورٹ_CRITICAL_NESTING_انحراف * پورٹ_لفظ_سائز( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
بھرو_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

بھرو_x x1, 1 * پورٹ_لفظ_سائز( sp )
بھرو_x x5, 2 * پورٹ_لفظ_سائز( sp )
بھرو_x x6, 3 * پورٹ_لفظ_سائز( sp )
بھرو_x x7, 4 * پورٹ_لفظ_سائز( sp )
بھرو_x x8, 5 * پورٹ_لفظ_سائز( sp )
بھرو_x x9, 6 * پورٹ_لفظ_سائز( sp )
بھرو_x x10, 7 * پورٹ_لفظ_سائز( sp )
بھرو_x x11, 8 * پورٹ_لفظ_سائز( sp )
بھرو_x x12, 9 * پورٹ_لفظ_سائز( sp )
بھرو_x x13, 10 * پورٹ_لفظ_سائز( sp )
بھرو_x x14, 11 * پورٹ_لفظ_سائز( sp )
بھرو_x x15, 12 * پورٹ_لفظ_سائز( sp )
#اگر_غیر_تعریف_شدہ __riscv_32e
    بھرو_x x16, 13 * پورٹ_لفظ_سائز( sp )
    بھرو_x x17, 14 * پورٹ_لفظ_سائز( sp )
    بھرو_x x18, 15 * پورٹ_لفظ_سائز( sp )
    بھرو_x x19, 16 * پورٹ_لفظ_سائز( sp )
    بھرو_x x20, 17 * پورٹ_لفظ_سائز( sp )
    بھرو_x x21, 18 * پورٹ_لفظ_سائز( sp )
    بھرو_x x22, 19 * پورٹ_لفظ_سائز( sp )
    بھرو_x x23, 20 * پورٹ_لفظ_سائز( sp )
    بھرو_x x24, 21 * پورٹ_لفظ_سائز( sp )
    بھرو_x x25, 22 * پورٹ_لفظ_سائز( sp )
    بھرو_x x26, 23 * پورٹ_لفظ_سائز( sp )
    بھرو_x x27, 24 * پورٹ_لفظ_سائز( sp )
    بھرو_x x28, 25 * پورٹ_لفظ_سائز( sp )
    بھرو_x x29, 26 * پورٹ_لفظ_سائز( sp )
    بھرو_x x30, 27 * پورٹ_لفظ_سائز( sp )
    بھرو_x x31, 28 * پورٹ_لفظ_سائز( sp )
#اگر_ختم /* ifndef __riscv_32e */
addi sp, sp, پورٹ_CONTEXT_سائز

mret
ENDM
/*-----------------------------------------------------------*/

#اگر_ختم /* PORTCONTEXT_H */
