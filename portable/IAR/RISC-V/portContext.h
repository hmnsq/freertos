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

#अगर_अघोषित PORTCONTEXT_H
#घोषणा PORTCONTEXT_H

#अगर __riscv_xlen == 64
    #घोषणा port_WORD_आकार    8
    #घोषणा store_x          sd
    #घोषणा load_x           ld
#या_अगर __riscv_xlen == 32
    #घोषणा store_x          sw
    #घोषणा load_x           lw
    #घोषणा port_WORD_आकार    4
#अन्यथा
    #त्रुटि Assembler did not define __riscv_xlen
#पूर्ण_अगर

#समावेश "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#अगर_घोषित __riscv_32e
    #घोषणा port_CONTEXT_आकार               ( 15 * port_WORD_आकार )
    #घोषणा portCRITICAL_NESTING_OFFSET    13
    #घोषणा portMSTATUS_OFFSET             14
#अन्यथा
    #घोषणा port_CONTEXT_आकार               ( 31 * port_WORD_आकार )
    #घोषणा portCRITICAL_NESTING_OFFSET    29
    #घोषणा portMSTATUS_OFFSET             30
#पूर्ण_अगर

EXTERN pxCurrentTCB
EXTERN x_ISRStack_शीर्ष
EXTERN xCriticalNesting
EXTERN pxCriticalNesting

/*-----------------------------------------------------------*/

portcontextSAVE_CONTEXT_INTERNAL MACRO
addi sp, sp, -port_CONTEXT_आकार
store_x x1, 1 * port_WORD_आकार( sp )
store_x x5, 2 * port_WORD_आकार( sp )
store_x x6, 3 * port_WORD_आकार( sp )
store_x x7, 4 * port_WORD_आकार( sp )
store_x x8, 5 * port_WORD_आकार( sp )
store_x x9, 6 * port_WORD_आकार( sp )
store_x x10, 7 * port_WORD_आकार( sp )
store_x x11, 8 * port_WORD_आकार( sp )
store_x x12, 9 * port_WORD_आकार( sp )
store_x x13, 10 * port_WORD_आकार( sp )
store_x x14, 11 * port_WORD_आकार( sp )
store_x x15, 12 * port_WORD_आकार( sp )
#अगर_अघोषित __riscv_32e
    store_x x16, 13 * port_WORD_आकार( sp )
    store_x x17, 14 * port_WORD_आकार( sp )
    store_x x18, 15 * port_WORD_आकार( sp )
    store_x x19, 16 * port_WORD_आकार( sp )
    store_x x20, 17 * port_WORD_आकार( sp )
    store_x x21, 18 * port_WORD_आकार( sp )
    store_x x22, 19 * port_WORD_आकार( sp )
    store_x x23, 20 * port_WORD_आकार( sp )
    store_x x24, 21 * port_WORD_आकार( sp )
    store_x x25, 22 * port_WORD_आकार( sp )
    store_x x26, 23 * port_WORD_आकार( sp )
    store_x x27, 24 * port_WORD_आकार( sp )
    store_x x28, 25 * port_WORD_आकार( sp )
    store_x x29, 26 * port_WORD_आकार( sp )
    store_x x30, 27 * port_WORD_आकार( sp )
    store_x x31, 28 * port_WORD_आकार( sp )
#पूर्ण_अगर /* ifndef __riscv_32e */

load_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, portCRITICAL_NESTING_OFFSET * port_WORD_आकार( sp ) /* Store the critical nesting value to the stack. */

csrr t0, mstatus                                              /* Required for MPIE bit. */
store_x t0, portMSTATUS_OFFSET * port_WORD_आकार( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

load_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

ENDM
/*-----------------------------------------------------------*/

portcontextSAVE_EXCEPTION_CONTEXT MACRO
portcontextSAVE_CONTEXT_INTERNAL
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
load_x sp, x_ISRStack_शीर्ष /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontextSAVE_INTERRUPT_CONTEXT MACRO
portcontextSAVE_CONTEXT_INTERNAL
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
load_x sp, x_ISRStack_शीर्ष /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontextRESTORE_CONTEXT MACRO
load_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
load_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
load_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Load mstatus with the interrupt enable bits used by the task. */
load_x t0, portMSTATUS_OFFSET * port_WORD_आकार( sp )
csrw mstatus, t0                                             /* Required for MPIE bit. */

load_x t0, portCRITICAL_NESTING_OFFSET * port_WORD_आकार( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
load_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

load_x x1, 1 * port_WORD_आकार( sp )
load_x x5, 2 * port_WORD_आकार( sp )
load_x x6, 3 * port_WORD_आकार( sp )
load_x x7, 4 * port_WORD_आकार( sp )
load_x x8, 5 * port_WORD_आकार( sp )
load_x x9, 6 * port_WORD_आकार( sp )
load_x x10, 7 * port_WORD_आकार( sp )
load_x x11, 8 * port_WORD_आकार( sp )
load_x x12, 9 * port_WORD_आकार( sp )
load_x x13, 10 * port_WORD_आकार( sp )
load_x x14, 11 * port_WORD_आकार( sp )
load_x x15, 12 * port_WORD_आकार( sp )
#अगर_अघोषित __riscv_32e
    load_x x16, 13 * port_WORD_आकार( sp )
    load_x x17, 14 * port_WORD_आकार( sp )
    load_x x18, 15 * port_WORD_आकार( sp )
    load_x x19, 16 * port_WORD_आकार( sp )
    load_x x20, 17 * port_WORD_आकार( sp )
    load_x x21, 18 * port_WORD_आकार( sp )
    load_x x22, 19 * port_WORD_आकार( sp )
    load_x x23, 20 * port_WORD_आकार( sp )
    load_x x24, 21 * port_WORD_आकार( sp )
    load_x x25, 22 * port_WORD_आकार( sp )
    load_x x26, 23 * port_WORD_आकार( sp )
    load_x x27, 24 * port_WORD_आकार( sp )
    load_x x28, 25 * port_WORD_आकार( sp )
    load_x x29, 26 * port_WORD_आकार( sp )
    load_x x30, 27 * port_WORD_आकार( sp )
    load_x x31, 28 * port_WORD_आकार( sp )
#पूर्ण_अगर /* ifndef __riscv_32e */
addi sp, sp, port_CONTEXT_आकार

mret
ENDM
/*-----------------------------------------------------------*/

#पूर्ण_अगर /* PORTCONTEXT_H */
