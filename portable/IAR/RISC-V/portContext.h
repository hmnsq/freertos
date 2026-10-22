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

#నిర్వచితం_కాకపోతే PORTCONTEXT_H
#నిర్వచించు PORTCONTEXT_H

#ఒకవేళ __riscv_xlen == 64
    #నిర్వచించు పోర్టు_మాట_కొలత    8
    #నిర్వచించు store_x          sd
    #నిర్వచించు ఎక్కించు_x           ld
#లేదావేళ __riscv_xlen == 32
    #నిర్వచించు store_x          sw
    #నిర్వచించు ఎక్కించు_x           lw
    #నిర్వచించు పోర్టు_మాట_కొలత    4
#లేకపోతే
    #దోషం Assembler did not define __riscv_xlen
#అయితే_ముగింపు

#అన్తర్భావ "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#నిర్వచితమైతే __riscv_32e
    #నిర్వచించు పోర్టు_CONTEXT_కొలత               ( 15 * పోర్టు_మాట_కొలత )
    #నిర్వచించు పోర్టు_CRITICAL_NESTING_స్థానభ్రంశం    13
    #నిర్వచించు పోర్టు_MSTATUS_స్థానభ్రంశం             14
#లేకపోతే
    #నిర్వచించు పోర్టు_CONTEXT_కొలత               ( 31 * పోర్టు_మాట_కొలత )
    #నిర్వచించు పోర్టు_CRITICAL_NESTING_స్థానభ్రంశం    29
    #నిర్వచించు పోర్టు_MSTATUS_స్థానభ్రంశం             30
#అయితే_ముగింపు

EXTERN pxCurrentTCB
EXTERN x_ISRStack_శిఖరం
EXTERN xCriticalNesting
EXTERN pxCriticalNesting

/*-----------------------------------------------------------*/

portcontext_SAVE_CONTEXT_అంతర్గత MACRO
addi sp, sp, -పోర్టు_CONTEXT_కొలత
store_x x1, 1 * పోర్టు_మాట_కొలత( sp )
store_x x5, 2 * పోర్టు_మాట_కొలత( sp )
store_x x6, 3 * పోర్టు_మాట_కొలత( sp )
store_x x7, 4 * పోర్టు_మాట_కొలత( sp )
store_x x8, 5 * పోర్టు_మాట_కొలత( sp )
store_x x9, 6 * పోర్టు_మాట_కొలత( sp )
store_x x10, 7 * పోర్టు_మాట_కొలత( sp )
store_x x11, 8 * పోర్టు_మాట_కొలత( sp )
store_x x12, 9 * పోర్టు_మాట_కొలత( sp )
store_x x13, 10 * పోర్టు_మాట_కొలత( sp )
store_x x14, 11 * పోర్టు_మాట_కొలత( sp )
store_x x15, 12 * పోర్టు_మాట_కొలత( sp )
#నిర్వచితం_కాకపోతే __riscv_32e
    store_x x16, 13 * పోర్టు_మాట_కొలత( sp )
    store_x x17, 14 * పోర్టు_మాట_కొలత( sp )
    store_x x18, 15 * పోర్టు_మాట_కొలత( sp )
    store_x x19, 16 * పోర్టు_మాట_కొలత( sp )
    store_x x20, 17 * పోర్టు_మాట_కొలత( sp )
    store_x x21, 18 * పోర్టు_మాట_కొలత( sp )
    store_x x22, 19 * పోర్టు_మాట_కొలత( sp )
    store_x x23, 20 * పోర్టు_మాట_కొలత( sp )
    store_x x24, 21 * పోర్టు_మాట_కొలత( sp )
    store_x x25, 22 * పోర్టు_మాట_కొలత( sp )
    store_x x26, 23 * పోర్టు_మాట_కొలత( sp )
    store_x x27, 24 * పోర్టు_మాట_కొలత( sp )
    store_x x28, 25 * పోర్టు_మాట_కొలత( sp )
    store_x x29, 26 * పోర్టు_మాట_కొలత( sp )
    store_x x30, 27 * పోర్టు_మాట_కొలత( sp )
    store_x x31, 28 * పోర్టు_మాట_కొలత( sp )
#అయితే_ముగింపు /* ifndef __riscv_32e */

ఎక్కించు_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, పోర్టు_CRITICAL_NESTING_స్థానభ్రంశం * పోర్టు_మాట_కొలత( sp ) /* Store the critical nesting value to the stack. */

csrr t0, mstatus                                              /* Required for MPIE bit. */
store_x t0, పోర్టు_MSTATUS_స్థానభ్రంశం * పోర్టు_మాట_కొలత( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

ఎక్కించు_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

ENDM
/*-----------------------------------------------------------*/

portcontextSAVE_EXCEPTION_CONTEXT MACRO
portcontext_SAVE_CONTEXT_అంతర్గత
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
ఎక్కించు_x sp, x_ISRStack_శిఖరం /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontext_SAVE_అంతరాయం_CONTEXT MACRO
portcontext_SAVE_CONTEXT_అంతర్గత
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
ఎక్కించు_x sp, x_ISRStack_శిఖరం /* Switch to ISR stack. */
ENDM
/*-----------------------------------------------------------*/

portcontextRESTORE_CONTEXT MACRO
ఎక్కించు_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
ఎక్కించు_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
ఎక్కించు_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Load mstatus with the interrupt enable bits used by the task. */
ఎక్కించు_x t0, పోర్టు_MSTATUS_స్థానభ్రంశం * పోర్టు_మాట_కొలత( sp )
csrw mstatus, t0                                             /* Required for MPIE bit. */

ఎక్కించు_x t0, పోర్టు_CRITICAL_NESTING_స్థానభ్రంశం * పోర్టు_మాట_కొలత( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
ఎక్కించు_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

ఎక్కించు_x x1, 1 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x5, 2 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x6, 3 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x7, 4 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x8, 5 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x9, 6 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x10, 7 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x11, 8 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x12, 9 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x13, 10 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x14, 11 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x15, 12 * పోర్టు_మాట_కొలత( sp )
#నిర్వచితం_కాకపోతే __riscv_32e
    ఎక్కించు_x x16, 13 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x17, 14 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x18, 15 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x19, 16 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x20, 17 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x21, 18 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x22, 19 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x23, 20 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x24, 21 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x25, 22 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x26, 23 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x27, 24 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x28, 25 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x29, 26 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x30, 27 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x31, 28 * పోర్టు_మాట_కొలత( sp )
#అయితే_ముగింపు /* ifndef __riscv_32e */
addi sp, sp, పోర్టు_CONTEXT_కొలత

mret
ENDM
/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* PORTCONTEXT_H */
