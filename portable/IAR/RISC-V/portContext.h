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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTCONTEXT_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTCONTEXT_H

#ਜੇ __riscv_xlen == 64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ    8
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ store_x          sd
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_x           ld
#ਜਾਂਜੇ __riscv_xlen == 32
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ store_x          sw
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_x           lw
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ    4
#ਨਹੀਂਤਾਂ
    #ਗਲਤੀ Assembler did not define __riscv_xlen
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __riscv_32e
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONTEXT_ਮਾਪ               ( 15 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਥ    13
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MSTATUS_ਵਿੱਥ             14
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONTEXT_ਮਾਪ               ( 31 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਥ    29
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MSTATUS_ਵਿੱਥ             30
#ਜੇ_ਅੰਤ

EXTERN pxCurrentTCB
EXTERN x_ISRStack_ਸਿਖਰ
EXTERN xCriticalNesting
EXTERN pxCriticalNesting

/*-----------------------------------------------------------*/

portcontext_SAVE_CONTEXT_ਅੰਦਰੂਨੀ MACRO
addi sp, sp, -ਪੋਰਟ_CONTEXT_ਮਾਪ
store_x x1, 1 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x5, 2 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x6, 3 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x7, 4 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x8, 5 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x9, 6 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x10, 7 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x11, 8 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x12, 9 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x13, 10 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x14, 11 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x15, 12 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __riscv_32e
    store_x x16, 13 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x17, 14 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x18, 15 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x19, 16 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x20, 17 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x21, 18 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x22, 19 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x23, 20 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x24, 21 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x25, 22 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x26, 23 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x27, 24 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x28, 25 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x29, 26 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x30, 27 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x31, 28 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
#ਜੇ_ਅੰਤ /* ifndef __riscv_32e */

ਲੱਦੋ_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਥ * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp ) /* Store the critical nesting value to the stack. */

csrr t0, mstatus                                              /* Required for MPIE bit. */
store_x t0, ਪੋਰਟ_MSTATUS_ਵਿੱਥ * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

ਲੱਦੋ_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

ENDM
/*-----------------------------------------------------------*/

portcontextSAVE_EXCEPTION_CONTEXT MACRO
portcontext_SAVE_CONTEXT_ਅੰਦਰੂਨੀ
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
ਲੱਦੋ_x sp, x_ISRStack_ਸਿਖਰ /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontext_SAVE_ਰੁਕਾਵਟ_CONTEXT MACRO
portcontext_SAVE_CONTEXT_ਅੰਦਰੂਨੀ
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
ਲੱਦੋ_x sp, x_ISRStack_ਸਿਖਰ /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontextRESTORE_CONTEXT MACRO
ਲੱਦੋ_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
ਲੱਦੋ_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
ਲੱਦੋ_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Load mstatus with the interrupt enable bits used by the task. */
ਲੱਦੋ_x t0, ਪੋਰਟ_MSTATUS_ਵਿੱਥ * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
csrw mstatus, t0                                             /* Required for MPIE bit. */

ਲੱਦੋ_x t0, ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਥ * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
ਲੱਦੋ_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

ਲੱਦੋ_x x1, 1 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x5, 2 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x6, 3 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x7, 4 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x8, 5 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x9, 6 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x10, 7 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x11, 8 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x12, 9 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x13, 10 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x14, 11 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x15, 12 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __riscv_32e
    ਲੱਦੋ_x x16, 13 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x17, 14 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x18, 15 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x19, 16 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x20, 17 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x21, 18 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x22, 19 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x23, 20 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x24, 21 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x25, 22 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x26, 23 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x27, 24 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x28, 25 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x29, 26 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x30, 27 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x31, 28 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
#ਜੇ_ਅੰਤ /* ifndef __riscv_32e */
addi sp, sp, ਪੋਰਟ_CONTEXT_ਮਾਪ

mret
ENDM
/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* PORTCONTEXT_H */
