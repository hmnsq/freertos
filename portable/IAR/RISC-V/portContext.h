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

#यदि_अपरिभाषितम् PORTCONTEXT_H
#परिभाषय PORTCONTEXT_H

#यदि __riscv_xlen == 64
    #परिभाषय पत्तनम्_WORD_आकार    8
    #परिभाषय store_x          sd
    #परिभाषय आरोपय_x           ld
#नोचेद्यदि __riscv_xlen == 32
    #परिभाषय store_x          sw
    #परिभाषय आरोपय_x           lw
    #परिभाषय पत्तनम्_WORD_आकार    4
#अन्यथा
    #दोषः Assembler did not define __riscv_xlen
#यदि_अन्तः

#अन्तर्भाव "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#यदि_परिभाषितम् __riscv_32e
    #परिभाषय पत्तनम्_CONTEXT_आकार               ( 15 * पत्तनम्_WORD_आकार )
    #परिभाषय पत्तनम्_CRITICAL_NESTING_विस्थापनम्    13
    #परिभाषय पत्तनम्_MSTATUS_विस्थापनम्             14
#अन्यथा
    #परिभाषय पत्तनम्_CONTEXT_आकार               ( 31 * पत्तनम्_WORD_आकार )
    #परिभाषय पत्तनम्_CRITICAL_NESTING_विस्थापनम्    29
    #परिभाषय पत्तनम्_MSTATUS_विस्थापनम्             30
#यदि_अन्तः

EXTERN pxCurrentTCB
EXTERN x_ISRStack_शिखरम्
EXTERN xCriticalNesting
EXTERN pxCriticalNesting

/*-----------------------------------------------------------*/

portcontext_SAVE_CONTEXT_आन्तरिकम् MACRO
addi sp, sp, -पत्तनम्_CONTEXT_आकार
store_x x1, 1 * पत्तनम्_WORD_आकार( sp )
store_x x5, 2 * पत्तनम्_WORD_आकार( sp )
store_x x6, 3 * पत्तनम्_WORD_आकार( sp )
store_x x7, 4 * पत्तनम्_WORD_आकार( sp )
store_x x8, 5 * पत्तनम्_WORD_आकार( sp )
store_x x9, 6 * पत्तनम्_WORD_आकार( sp )
store_x x10, 7 * पत्तनम्_WORD_आकार( sp )
store_x x11, 8 * पत्तनम्_WORD_आकार( sp )
store_x x12, 9 * पत्तनम्_WORD_आकार( sp )
store_x x13, 10 * पत्तनम्_WORD_आकार( sp )
store_x x14, 11 * पत्तनम्_WORD_आकार( sp )
store_x x15, 12 * पत्तनम्_WORD_आकार( sp )
#यदि_अपरिभाषितम् __riscv_32e
    store_x x16, 13 * पत्तनम्_WORD_आकार( sp )
    store_x x17, 14 * पत्तनम्_WORD_आकार( sp )
    store_x x18, 15 * पत्तनम्_WORD_आकार( sp )
    store_x x19, 16 * पत्तनम्_WORD_आकार( sp )
    store_x x20, 17 * पत्तनम्_WORD_आकार( sp )
    store_x x21, 18 * पत्तनम्_WORD_आकार( sp )
    store_x x22, 19 * पत्तनम्_WORD_आकार( sp )
    store_x x23, 20 * पत्तनम्_WORD_आकार( sp )
    store_x x24, 21 * पत्तनम्_WORD_आकार( sp )
    store_x x25, 22 * पत्तनम्_WORD_आकार( sp )
    store_x x26, 23 * पत्तनम्_WORD_आकार( sp )
    store_x x27, 24 * पत्तनम्_WORD_आकार( sp )
    store_x x28, 25 * पत्तनम्_WORD_आकार( sp )
    store_x x29, 26 * पत्तनम्_WORD_आकार( sp )
    store_x x30, 27 * पत्तनम्_WORD_आकार( sp )
    store_x x31, 28 * पत्तनम्_WORD_आकार( sp )
#यदि_अन्तः /* ifndef __riscv_32e */

आरोपय_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, पत्तनम्_CRITICAL_NESTING_विस्थापनम् * पत्तनम्_WORD_आकार( sp ) /* Store the critical nesting value to the stack. */

csrr t0, mstatus                                              /* Required for MPIE bit. */
store_x t0, पत्तनम्_MSTATUS_विस्थापनम् * पत्तनम्_WORD_आकार( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

आरोपय_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

ENDM
/*-----------------------------------------------------------*/

portcontextSAVE_EXCEPTION_CONTEXT MACRO
portcontext_SAVE_CONTEXT_आन्तरिकम्
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
आरोपय_x sp, x_ISRStack_शिखरम् /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontext_SAVE_व्यवधानम्_CONTEXT MACRO
portcontext_SAVE_CONTEXT_आन्तरिकम्
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
आरोपय_x sp, x_ISRStack_शिखरम् /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontextRESTORE_CONTEXT MACRO
आरोपय_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
आरोपय_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
आरोपय_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Load mstatus with the interrupt enable bits used by the task. */
आरोपय_x t0, पत्तनम्_MSTATUS_विस्थापनम् * पत्तनम्_WORD_आकार( sp )
csrw mstatus, t0                                             /* Required for MPIE bit. */

आरोपय_x t0, पत्तनम्_CRITICAL_NESTING_विस्थापनम् * पत्तनम्_WORD_आकार( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
आरोपय_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

आरोपय_x x1, 1 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x5, 2 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x6, 3 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x7, 4 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x8, 5 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x9, 6 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x10, 7 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x11, 8 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x12, 9 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x13, 10 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x14, 11 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x15, 12 * पत्तनम्_WORD_आकार( sp )
#यदि_अपरिभाषितम् __riscv_32e
    आरोपय_x x16, 13 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x17, 14 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x18, 15 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x19, 16 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x20, 17 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x21, 18 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x22, 19 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x23, 20 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x24, 21 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x25, 22 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x26, 23 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x27, 24 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x28, 25 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x29, 26 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x30, 27 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x31, 28 * पत्तनम्_WORD_आकार( sp )
#यदि_अन्तः /* ifndef __riscv_32e */
addi sp, sp, पत्तनम्_CONTEXT_आकार

mret
ENDM
/*-----------------------------------------------------------*/

#यदि_अन्तः /* PORTCONTEXT_H */
