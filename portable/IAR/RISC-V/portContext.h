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

#اگر_تعریف_نشده PORTCONTEXT_H
#تعریف_کن PORTCONTEXT_H

#إذا __riscv_xlen == 64
    #تعریف_کن پورت_کلمه_اندازه    8
    #تعریف_کن store_x          sd
    #تعریف_کن بارگیری_x           ld
#وإلاإذا __riscv_xlen == 32
    #تعریف_کن store_x          sw
    #تعریف_کن بارگیری_x           lw
    #تعریف_کن پورت_کلمه_اندازه    4
#وإلا
    #خطا Assembler did not define __riscv_xlen
#پایان_اگر

#ضمن "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#اگر_تعریف_شده __riscv_32e
    #تعریف_کن پورت_CONTEXT_اندازه               ( 15 * پورت_کلمه_اندازه )
    #تعریف_کن پورت_CRITICAL_NESTING_جابه_جایی    13
    #تعریف_کن پورت_MSTATUS_جابه_جایی             14
#وإلا
    #تعریف_کن پورت_CONTEXT_اندازه               ( 31 * پورت_کلمه_اندازه )
    #تعریف_کن پورت_CRITICAL_NESTING_جابه_جایی    29
    #تعریف_کن پورت_MSTATUS_جابه_جایی             30
#پایان_اگر

EXTERN pxCurrentTCB
EXTERN x_ISRStack_بالاترین
EXTERN xCriticalNesting
EXTERN pxCriticalNesting

/*-----------------------------------------------------------*/

portcontext_SAVE_CONTEXT_داخلی MACRO
addi sp, sp, -پورت_CONTEXT_اندازه
store_x x1, 1 * پورت_کلمه_اندازه( sp )
store_x x5, 2 * پورت_کلمه_اندازه( sp )
store_x x6, 3 * پورت_کلمه_اندازه( sp )
store_x x7, 4 * پورت_کلمه_اندازه( sp )
store_x x8, 5 * پورت_کلمه_اندازه( sp )
store_x x9, 6 * پورت_کلمه_اندازه( sp )
store_x x10, 7 * پورت_کلمه_اندازه( sp )
store_x x11, 8 * پورت_کلمه_اندازه( sp )
store_x x12, 9 * پورت_کلمه_اندازه( sp )
store_x x13, 10 * پورت_کلمه_اندازه( sp )
store_x x14, 11 * پورت_کلمه_اندازه( sp )
store_x x15, 12 * پورت_کلمه_اندازه( sp )
#اگر_تعریف_نشده __riscv_32e
    store_x x16, 13 * پورت_کلمه_اندازه( sp )
    store_x x17, 14 * پورت_کلمه_اندازه( sp )
    store_x x18, 15 * پورت_کلمه_اندازه( sp )
    store_x x19, 16 * پورت_کلمه_اندازه( sp )
    store_x x20, 17 * پورت_کلمه_اندازه( sp )
    store_x x21, 18 * پورت_کلمه_اندازه( sp )
    store_x x22, 19 * پورت_کلمه_اندازه( sp )
    store_x x23, 20 * پورت_کلمه_اندازه( sp )
    store_x x24, 21 * پورت_کلمه_اندازه( sp )
    store_x x25, 22 * پورت_کلمه_اندازه( sp )
    store_x x26, 23 * پورت_کلمه_اندازه( sp )
    store_x x27, 24 * پورت_کلمه_اندازه( sp )
    store_x x28, 25 * پورت_کلمه_اندازه( sp )
    store_x x29, 26 * پورت_کلمه_اندازه( sp )
    store_x x30, 27 * پورت_کلمه_اندازه( sp )
    store_x x31, 28 * پورت_کلمه_اندازه( sp )
#پایان_اگر /* ifndef __riscv_32e */

بارگیری_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, پورت_CRITICAL_NESTING_جابه_جایی * پورت_کلمه_اندازه( sp ) /* Store the critical nesting value to the stack. */

csrr t0, mstatus                                              /* Required for MPIE bit. */
store_x t0, پورت_MSTATUS_جابه_جایی * پورت_کلمه_اندازه( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

بارگیری_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

ENDM
/*-----------------------------------------------------------*/

portcontextSAVE_EXCEPTION_CONTEXT MACRO
portcontext_SAVE_CONTEXT_داخلی
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
بارگیری_x sp, x_ISRStack_بالاترین /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontext_SAVE_وقفه_CONTEXT MACRO
portcontext_SAVE_CONTEXT_داخلی
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
بارگیری_x sp, x_ISRStack_بالاترین /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontextRESTORE_CONTEXT MACRO
بارگیری_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
بارگیری_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
بارگیری_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Load mstatus with the interrupt enable bits used by the task. */
بارگیری_x t0, پورت_MSTATUS_جابه_جایی * پورت_کلمه_اندازه( sp )
csrw mstatus, t0                                             /* Required for MPIE bit. */

بارگیری_x t0, پورت_CRITICAL_NESTING_جابه_جایی * پورت_کلمه_اندازه( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
بارگیری_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

بارگیری_x x1, 1 * پورت_کلمه_اندازه( sp )
بارگیری_x x5, 2 * پورت_کلمه_اندازه( sp )
بارگیری_x x6, 3 * پورت_کلمه_اندازه( sp )
بارگیری_x x7, 4 * پورت_کلمه_اندازه( sp )
بارگیری_x x8, 5 * پورت_کلمه_اندازه( sp )
بارگیری_x x9, 6 * پورت_کلمه_اندازه( sp )
بارگیری_x x10, 7 * پورت_کلمه_اندازه( sp )
بارگیری_x x11, 8 * پورت_کلمه_اندازه( sp )
بارگیری_x x12, 9 * پورت_کلمه_اندازه( sp )
بارگیری_x x13, 10 * پورت_کلمه_اندازه( sp )
بارگیری_x x14, 11 * پورت_کلمه_اندازه( sp )
بارگیری_x x15, 12 * پورت_کلمه_اندازه( sp )
#اگر_تعریف_نشده __riscv_32e
    بارگیری_x x16, 13 * پورت_کلمه_اندازه( sp )
    بارگیری_x x17, 14 * پورت_کلمه_اندازه( sp )
    بارگیری_x x18, 15 * پورت_کلمه_اندازه( sp )
    بارگیری_x x19, 16 * پورت_کلمه_اندازه( sp )
    بارگیری_x x20, 17 * پورت_کلمه_اندازه( sp )
    بارگیری_x x21, 18 * پورت_کلمه_اندازه( sp )
    بارگیری_x x22, 19 * پورت_کلمه_اندازه( sp )
    بارگیری_x x23, 20 * پورت_کلمه_اندازه( sp )
    بارگیری_x x24, 21 * پورت_کلمه_اندازه( sp )
    بارگیری_x x25, 22 * پورت_کلمه_اندازه( sp )
    بارگیری_x x26, 23 * پورت_کلمه_اندازه( sp )
    بارگیری_x x27, 24 * پورت_کلمه_اندازه( sp )
    بارگیری_x x28, 25 * پورت_کلمه_اندازه( sp )
    بارگیری_x x29, 26 * پورت_کلمه_اندازه( sp )
    بارگیری_x x30, 27 * پورت_کلمه_اندازه( sp )
    بارگیری_x x31, 28 * پورت_کلمه_اندازه( sp )
#پایان_اگر /* ifndef __riscv_32e */
addi sp, sp, پورت_CONTEXT_اندازه

mret
ENDM
/*-----------------------------------------------------------*/

#پایان_اگر /* PORTCONTEXT_H */
