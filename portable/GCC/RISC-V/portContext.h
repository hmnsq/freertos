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

#यदि_अपरिभाषितम् configENABLE_FPU
    #परिभाषय configENABLE_FPU 0
#यदि_अन्तः

#यदि_अपरिभाषितम् configENABLE_VPU
    #परिभाषय configENABLE_VPU 0
#यदि_अन्तः

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
    #परिभाषय पत्तनम्_CRITICAL_NESTING_विस्थापनम्    14
#अन्यथा
    #परिभाषय पत्तनम्_CONTEXT_आकार               ( 31 * पत्तनम्_WORD_आकार )
    #परिभाषय पत्तनम्_CRITICAL_NESTING_विस्थापनम्    30
#यदि_अन्तः

#यदि ( configENABLE_FPU == 1 )
    /* Bit [14:13] in the mstatus encode the status of FPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #परिभाषय MSTATUS_FS_आवरणम्                 0x6000
    #परिभाषय MSTATUS_FS_INITIAL              0x2000
    #परिभाषय MSTATUS_FS_CLEAN                0x4000
    #परिभाषय MSTATUS_FS_DIRTY                0x6000
    #परिभाषय MSTATUS_FS_विस्थापनम्               13

    #यदि_परिभाषितम् __riscv_fdiv
        #यदि __riscv_flen == 32
            #परिभाषय आरोपय_f                  flw
            #परिभाषय store_f                 fsw
        #नोचेद्यदि __riscv_flen == 64
            #परिभाषय आरोपय_f                  fld
            #परिभाषय store_f                 fsd
        #अन्यथा
            #दोषः Assembler did not define __riscv_flen
        #यदि_अन्तः

        #परिभाषय पत्तनम्_FPU_REG_आकार                ( __riscv_flen / 8 )
        #परिभाषय पत्तनम्_FPU_REG_गणनम्               33 /* 32 Floating point registers plus one CSR. */
        #परिभाषय पत्तनम्_FPU_REG_विस्थापनम्( reg_सूचकांक )  ( ( 2 * पत्तनम्_WORD_आकार ) + ( reg_सूचकांक * पत्तनम्_FPU_REG_आकार ) )
        #परिभाषय पत्तनम्_FPU_CONTEXT_आकार            ( पत्तनम्_FPU_REG_आकार * पत्तनम्_FPU_REG_गणनम् )
    #अन्यथा
        #दोषः configENABLE_FPU must not be समुच्चयः गन्तव्यम् 1 यदि the hardware does not have FPU
    #यदि_अन्तः
#यदि_अन्तः

#यदि ( configENABLE_VPU == 1 )
    /* Bit [10:9] in the mstatus encode the status of VPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #परिभाषय MSTATUS_VS_आवरणम्                 0x600
    #परिभाषय MSTATUS_VS_INITIAL              0x200
    #परिभाषय MSTATUS_VS_CLEAN                0x400
    #परिभाषय MSTATUS_VS_DIRTY                0x600
    #परिभाषय MSTATUS_VS_विस्थापनम्               9

    #यदि_अपरिभाषितम् __riscv_vector
        #दोषः configENABLE_VPU must not be समुच्चयः गन्तव्यम् 1 यदि the hardware does not have VPU
    #यदि_अन्तः
#यदि_अन्तः
/*-----------------------------------------------------------*/

.बाह्य pxCurrentTCB
.बाह्य x_ISRStack_शिखरम्
.बाह्य xCriticalNesting
.बाह्य pxCriticalNesting
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_FPU_CONTEXT
addi sp, sp, -( पत्तनम्_FPU_CONTEXT_आकार )
/* Store the FPU registers. */
store_f f0,  पत्तनम्_FPU_REG_विस्थापनम्( 0  )( sp )
store_f f1,  पत्तनम्_FPU_REG_विस्थापनम्( 1  )( sp )
store_f f2,  पत्तनम्_FPU_REG_विस्थापनम्( 2  )( sp )
store_f f3,  पत्तनम्_FPU_REG_विस्थापनम्( 3  )( sp )
store_f f4,  पत्तनम्_FPU_REG_विस्थापनम्( 4  )( sp )
store_f f5,  पत्तनम्_FPU_REG_विस्थापनम्( 5  )( sp )
store_f f6,  पत्तनम्_FPU_REG_विस्थापनम्( 6  )( sp )
store_f f7,  पत्तनम्_FPU_REG_विस्थापनम्( 7  )( sp )
store_f f8,  पत्तनम्_FPU_REG_विस्थापनम्( 8  )( sp )
store_f f9,  पत्तनम्_FPU_REG_विस्थापनम्( 9  )( sp )
store_f f10, पत्तनम्_FPU_REG_विस्थापनम्( 10 )( sp )
store_f f11, पत्तनम्_FPU_REG_विस्थापनम्( 11 )( sp )
store_f f12, पत्तनम्_FPU_REG_विस्थापनम्( 12 )( sp )
store_f f13, पत्तनम्_FPU_REG_विस्थापनम्( 13 )( sp )
store_f f14, पत्तनम्_FPU_REG_विस्थापनम्( 14 )( sp )
store_f f15, पत्तनम्_FPU_REG_विस्थापनम्( 15 )( sp )
store_f f16, पत्तनम्_FPU_REG_विस्थापनम्( 16 )( sp )
store_f f17, पत्तनम्_FPU_REG_विस्थापनम्( 17 )( sp )
store_f f18, पत्तनम्_FPU_REG_विस्थापनम्( 18 )( sp )
store_f f19, पत्तनम्_FPU_REG_विस्थापनम्( 19 )( sp )
store_f f20, पत्तनम्_FPU_REG_विस्थापनम्( 20 )( sp )
store_f f21, पत्तनम्_FPU_REG_विस्थापनम्( 21 )( sp )
store_f f22, पत्तनम्_FPU_REG_विस्थापनम्( 22 )( sp )
store_f f23, पत्तनम्_FPU_REG_विस्थापनम्( 23 )( sp )
store_f f24, पत्तनम्_FPU_REG_विस्थापनम्( 24 )( sp )
store_f f25, पत्तनम्_FPU_REG_विस्थापनम्( 25 )( sp )
store_f f26, पत्तनम्_FPU_REG_विस्थापनम्( 26 )( sp )
store_f f27, पत्तनम्_FPU_REG_विस्थापनम्( 27 )( sp )
store_f f28, पत्तनम्_FPU_REG_विस्थापनम्( 28 )( sp )
store_f f29, पत्तनम्_FPU_REG_विस्थापनम्( 29 )( sp )
store_f f30, पत्तनम्_FPU_REG_विस्थापनम्( 30 )( sp )
store_f f31, पत्तनम्_FPU_REG_विस्थापनम्( 31 )( sp )
csrr t0, fcsr
store_x t0,  पत्तनम्_FPU_REG_विस्थापनम्( 32 )( sp )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_FPU_CONTEXT
/* Restore the FPU registers. */
आरोपय_f f0,  पत्तनम्_FPU_REG_विस्थापनम्( 0  )( sp )
आरोपय_f f1,  पत्तनम्_FPU_REG_विस्थापनम्( 1  )( sp )
आरोपय_f f2,  पत्तनम्_FPU_REG_विस्थापनम्( 2  )( sp )
आरोपय_f f3,  पत्तनम्_FPU_REG_विस्थापनम्( 3  )( sp )
आरोपय_f f4,  पत्तनम्_FPU_REG_विस्थापनम्( 4  )( sp )
आरोपय_f f5,  पत्तनम्_FPU_REG_विस्थापनम्( 5  )( sp )
आरोपय_f f6,  पत्तनम्_FPU_REG_विस्थापनम्( 6  )( sp )
आरोपय_f f7,  पत्तनम्_FPU_REG_विस्थापनम्( 7  )( sp )
आरोपय_f f8,  पत्तनम्_FPU_REG_विस्थापनम्( 8  )( sp )
आरोपय_f f9,  पत्तनम्_FPU_REG_विस्थापनम्( 9  )( sp )
आरोपय_f f10, पत्तनम्_FPU_REG_विस्थापनम्( 10 )( sp )
आरोपय_f f11, पत्तनम्_FPU_REG_विस्थापनम्( 11 )( sp )
आरोपय_f f12, पत्तनम्_FPU_REG_विस्थापनम्( 12 )( sp )
आरोपय_f f13, पत्तनम्_FPU_REG_विस्थापनम्( 13 )( sp )
आरोपय_f f14, पत्तनम्_FPU_REG_विस्थापनम्( 14 )( sp )
आरोपय_f f15, पत्तनम्_FPU_REG_विस्थापनम्( 15 )( sp )
आरोपय_f f16, पत्तनम्_FPU_REG_विस्थापनम्( 16 )( sp )
आरोपय_f f17, पत्तनम्_FPU_REG_विस्थापनम्( 17 )( sp )
आरोपय_f f18, पत्तनम्_FPU_REG_विस्थापनम्( 18 )( sp )
आरोपय_f f19, पत्तनम्_FPU_REG_विस्थापनम्( 19 )( sp )
आरोपय_f f20, पत्तनम्_FPU_REG_विस्थापनम्( 20 )( sp )
आरोपय_f f21, पत्तनम्_FPU_REG_विस्थापनम्( 21 )( sp )
आरोपय_f f22, पत्तनम्_FPU_REG_विस्थापनम्( 22 )( sp )
आरोपय_f f23, पत्तनम्_FPU_REG_विस्थापनम्( 23 )( sp )
आरोपय_f f24, पत्तनम्_FPU_REG_विस्थापनम्( 24 )( sp )
आरोपय_f f25, पत्तनम्_FPU_REG_विस्थापनम्( 25 )( sp )
आरोपय_f f26, पत्तनम्_FPU_REG_विस्थापनम्( 26 )( sp )
आरोपय_f f27, पत्तनम्_FPU_REG_विस्थापनम्( 27 )( sp )
आरोपय_f f28, पत्तनम्_FPU_REG_विस्थापनम्( 28 )( sp )
आरोपय_f f29, पत्तनम्_FPU_REG_विस्थापनम्( 29 )( sp )
आरोपय_f f30, पत्तनम्_FPU_REG_विस्थापनम्( 30 )( sp )
आरोपय_f f31, पत्तनम्_FPU_REG_विस्थापनम्( 31 )( sp )
आरोपय_x t0,  पत्तनम्_FPU_REG_विस्थापनम्( 32 )( sp )
csrw fcsr, t0
addi sp, sp, ( पत्तनम्_FPU_CONTEXT_आकार )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
सङ्कलय sp, sp, ( 2 * पत्तनम्_WORD_आकार )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */
neg  t0, t0

/* Store the vector registers in group of 8. */
सङ्कलय     sp, sp, t0
vs8r.v  v24, (sp)   /* Store v24-v31. */
सङ्कलय     sp, sp, t0
vs8r.v  v16, (sp)   /* Store v16-v23. */
सङ्कलय     sp, sp, t0
vs8r.v  v8, (sp)    /* Store v8-v15. */
सङ्कलय     sp, sp, t0
vs8r.v  v0, (sp)    /* Store v0-v7. */

/* Store the VPU CSRs. */
addi    sp, sp, -( 4 * पत्तनम्_WORD_आकार )
csrr    t0, vstart
store_x t0, 0 * पत्तनम्_WORD_आकार( sp )
csrr    t0, vcsr
store_x t0, 1 * पत्तनम्_WORD_आकार( sp )
csrr    t0, vl
store_x t0, 2 * पत्तनम्_WORD_आकार( sp )
csrr    t0, vtype
store_x t0, 3 * पत्तनम्_WORD_आकार( sp )

/* Re-reserve the space for mstatus and epc. */
सङ्कलय sp, sp, -( 2 * पत्तनम्_WORD_आकार )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
सङ्कलय sp, sp, ( 2 * पत्तनम्_WORD_आकार )

/* Restore the VPU CSRs. */
आरोपय_x  t0, 0  * पत्तनम्_WORD_आकार( sp )
csrw    vstart, t0
आरोपय_x  t0, 1 * पत्तनम्_WORD_आकार( sp )
csrw    vcsr, t0
आरोपय_x  t0, 2 * पत्तनम्_WORD_आकार( sp )
आरोपय_x  t1, 3 * पत्तनम्_WORD_आकार( sp )
vsetvl  x0, t0, t1 /* vlen and vtype can only be updated by using vset*vl* instructions. */
addi    sp, sp, ( 4 * पत्तनम्_WORD_आकार )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */

/* Restore the vector registers. */
vl8r.v  v0, (sp)    /* Restore v0-v7. */
सङ्कलय     sp, sp, t0
vl8r.v  v8, (sp)    /* Restore v8-v15. */
सङ्कलय     sp, sp, t0
vl8r.v  v16, (sp)   /* Restore v16-v23. */
सङ्कलय     sp, sp, t0
vl8r.v  v24, (sp)   /* Restore v23-v31. */
सङ्कलय     sp, sp, t0

/* Re-reserve the space for mstatus and epc. */
सङ्कलय sp, sp, -( 2 * पत्तनम्_WORD_आकार )
    .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_CONTEXT_आन्तरिकम्
addi sp, sp, -पत्तनम्_CONTEXT_आकार
store_x x1,  2  * पत्तनम्_WORD_आकार( sp )
store_x x5,  3  * पत्तनम्_WORD_आकार( sp )
store_x x6,  4  * पत्तनम्_WORD_आकार( sp )
store_x x7,  5  * पत्तनम्_WORD_आकार( sp )
store_x x8,  6  * पत्तनम्_WORD_आकार( sp )
store_x x9,  7  * पत्तनम्_WORD_आकार( sp )
store_x x10, 8  * पत्तनम्_WORD_आकार( sp )
store_x x11, 9  * पत्तनम्_WORD_आकार( sp )
store_x x12, 10 * पत्तनम्_WORD_आकार( sp )
store_x x13, 11 * पत्तनम्_WORD_आकार( sp )
store_x x14, 12 * पत्तनम्_WORD_आकार( sp )
store_x x15, 13 * पत्तनम्_WORD_आकार( sp )
#यदि_अपरिभाषितम् __riscv_32e
    store_x x16, 14 * पत्तनम्_WORD_आकार( sp )
    store_x x17, 15 * पत्तनम्_WORD_आकार( sp )
    store_x x18, 16 * पत्तनम्_WORD_आकार( sp )
    store_x x19, 17 * पत्तनम्_WORD_आकार( sp )
    store_x x20, 18 * पत्तनम्_WORD_आकार( sp )
    store_x x21, 19 * पत्तनम्_WORD_आकार( sp )
    store_x x22, 20 * पत्तनम्_WORD_आकार( sp )
    store_x x23, 21 * पत्तनम्_WORD_आकार( sp )
    store_x x24, 22 * पत्तनम्_WORD_आकार( sp )
    store_x x25, 23 * पत्तनम्_WORD_आकार( sp )
    store_x x26, 24 * पत्तनम्_WORD_आकार( sp )
    store_x x27, 25 * पत्तनम्_WORD_आकार( sp )
    store_x x28, 26 * पत्तनम्_WORD_आकार( sp )
    store_x x29, 27 * पत्तनम्_WORD_आकार( sp )
    store_x x30, 28 * पत्तनम्_WORD_आकार( sp )
    store_x x31, 29 * पत्तनम्_WORD_आकार( sp )
#यदि_अन्तः /* ifndef __riscv_32e */

आरोपय_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, पत्तनम्_CRITICAL_NESTING_विस्थापनम् * पत्तनम्_WORD_आकार( sp ) /* Store the critical nesting value to the stack. */

#यदि( configENABLE_FPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_FS_विस्थापनम्
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 1f /* If FPU status is not dirty, do not save FPU registers. */

    portcontexSAVE_FPU_CONTEXT
1:
#यदि_अन्तः

#यदि( configENABLE_VPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_VS_विस्थापनम्
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 2f /* If VPU status is not dirty, do not save VPU registers. */

    portcontexSAVE_VPU_CONTEXT
2:
#यदि_अन्तः

csrr t0, mstatus
store_x t0, 1 * पत्तनम्_WORD_आकार( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

#यदि( configENABLE_FPU == 1 )
    /* Mark the FPU as clean, if it was dirty and we saved FPU registers. */
    srl t1, t0, MSTATUS_FS_विस्थापनम्
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 3f

    li t1, ~MSTATUS_FS_आवरणम्
    and t0, t0, t1
    li t1, MSTATUS_FS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
3:
#यदि_अन्तः

#यदि( configENABLE_VPU == 1 )
    /* Mark the VPU as clean, if it was dirty and we saved VPU registers. */
    srl t1, t0, MSTATUS_VS_विस्थापनम्
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 4f

    li t1, ~MSTATUS_VS_आवरणम्
    and t0, t0, t1
    li t1, MSTATUS_VS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
4:
#यदि_अन्तः

आरोपय_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

   .endm
/*-----------------------------------------------------------*/

   .macro portcontextSAVE_EXCEPTION_CONTEXT
portcontext_SAVE_CONTEXT_आन्तरिकम्
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
आरोपय_x sp, x_ISRStack_शिखरम् /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_व्यवधानम्_CONTEXT
portcontext_SAVE_CONTEXT_आन्तरिकम्
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
आरोपय_x sp, x_ISRStack_शिखरम् /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontextRESTORE_CONTEXT
आरोपय_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
आरोपय_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
आरोपय_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Restore mstatus register. It is important to use t3 (and not t0) here as t3
 * is not clobbered by portcontextRESTORE_VPU_CONTEXT and
 * portcontextRESTORE_FPU_CONTEXT. */
आरोपय_x t3, 1 * पत्तनम्_WORD_आकार( sp )
csrw mstatus, t3

#यदि( configENABLE_VPU == 1 )
    srl t1, t3, MSTATUS_VS_विस्थापनम्
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 5f /* If VPU status is not dirty, do not restore VPU registers. */

    portcontextRESTORE_VPU_CONTEXT
5:
#यदि_अन्तः /* ifdef portasmSTORE_VPU_CONTEXT */

#यदि( configENABLE_FPU == 1 )
    srl t1, t3, MSTATUS_FS_विस्थापनम्
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 6f /* If FPU status is not dirty, do not restore FPU registers. */

    portcontextRESTORE_FPU_CONTEXT
6:
#यदि_अन्तः /* ifdef portasmSTORE_FPU_CONTEXT */

आरोपय_x t0, पत्तनम्_CRITICAL_NESTING_विस्थापनम् * पत्तनम्_WORD_आकार( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
आरोपय_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

आरोपय_x x1,  2  * पत्तनम्_WORD_आकार( sp )
आरोपय_x x5,  3  * पत्तनम्_WORD_आकार( sp )
आरोपय_x x6,  4  * पत्तनम्_WORD_आकार( sp )
आरोपय_x x7,  5  * पत्तनम्_WORD_आकार( sp )
आरोपय_x x8,  6  * पत्तनम्_WORD_आकार( sp )
आरोपय_x x9,  7  * पत्तनम्_WORD_आकार( sp )
आरोपय_x x10, 8  * पत्तनम्_WORD_आकार( sp )
आरोपय_x x11, 9  * पत्तनम्_WORD_आकार( sp )
आरोपय_x x12, 10 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x13, 11 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x14, 12 * पत्तनम्_WORD_आकार( sp )
आरोपय_x x15, 13 * पत्तनम्_WORD_आकार( sp )
#यदि_अपरिभाषितम् __riscv_32e
    आरोपय_x x16, 14 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x17, 15 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x18, 16 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x19, 17 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x20, 18 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x21, 19 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x22, 20 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x23, 21 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x24, 22 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x25, 23 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x26, 24 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x27, 25 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x28, 26 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x29, 27 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x30, 28 * पत्तनम्_WORD_आकार( sp )
    आरोपय_x x31, 29 * पत्तनम्_WORD_आकार( sp )
#यदि_अन्तः /* ifndef __riscv_32e */
addi sp, sp, पत्तनम्_CONTEXT_आकार

mret
   .endm
/*-----------------------------------------------------------*/

#यदि_अन्तः /* PORTCONTEXT_H */
