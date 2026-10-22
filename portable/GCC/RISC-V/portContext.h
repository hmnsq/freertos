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

#که_نه_تعریف_شوی configENABLE_FPU
    #تعریف_کړه configENABLE_FPU 0
#د_که_پای

#که_نه_تعریف_شوی configENABLE_VPU
    #تعریف_کړه configENABLE_VPU 0
#د_که_پای

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
    #تعریف_کړه پورټ_CRITICAL_NESTING_دننه_واټن    14
#وإلا
    #تعریف_کړه پورټ_CONTEXT_اندازه               ( 31 * پورټ_کلمه_اندازه )
    #تعریف_کړه پورټ_CRITICAL_NESTING_دننه_واټن    30
#د_که_پای

#إذا ( configENABLE_FPU == 1 )
    /* Bit [14:13] in the mstatus encode the status of FPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #تعریف_کړه MSTATUS_FS_ماسک                 0x6000
    #تعریف_کړه MSTATUS_FS_INITIAL              0x2000
    #تعریف_کړه MSTATUS_FS_CLEAN                0x4000
    #تعریف_کړه MSTATUS_FS_DIRTY                0x6000
    #تعریف_کړه MSTATUS_FS_دننه_واټن               13

    #که_تعریف_شوی __riscv_fdiv
        #إذا __riscv_flen == 32
            #تعریف_کړه بارول_f                  flw
            #تعریف_کړه store_f                 fsw
        #وإلاإذا __riscv_flen == 64
            #تعریف_کړه بارول_f                  fld
            #تعریف_کړه store_f                 fsd
        #وإلا
            #تېروتنه Assembler did not define __riscv_flen
        #د_که_پای

        #تعریف_کړه پورټ_FPU_REG_اندازه                ( __riscv_flen / 8 )
        #تعریف_کړه پورټ_FPU_REG_شمېر               33 /* 32 Floating point registers plus one CSR. */
        #تعریف_کړه پورټ_FPU_REG_دننه_واټن( reg_شاخص )  ( ( 2 * پورټ_کلمه_اندازه ) + ( reg_شاخص * پورټ_FPU_REG_اندازه ) )
        #تعریف_کړه پورټ_FPU_CONTEXT_اندازه            ( پورټ_FPU_REG_اندازه * پورټ_FPU_REG_شمېر )
    #وإلا
        #تېروتنه configENABLE_FPU must not be سېټ منزل 1 إذا the hardware does not have FPU
    #د_که_پای
#د_که_پای

#إذا ( configENABLE_VPU == 1 )
    /* Bit [10:9] in the mstatus encode the status of VPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #تعریف_کړه MSTATUS_VS_ماسک                 0x600
    #تعریف_کړه MSTATUS_VS_INITIAL              0x200
    #تعریف_کړه MSTATUS_VS_CLEAN                0x400
    #تعریف_کړه MSTATUS_VS_DIRTY                0x600
    #تعریف_کړه MSTATUS_VS_دننه_واټن               9

    #که_نه_تعریف_شوی __riscv_vector
        #تېروتنه configENABLE_VPU must not be سېټ منزل 1 إذا the hardware does not have VPU
    #د_که_پای
#د_که_پای
/*-----------------------------------------------------------*/

.خارجي pxCurrentTCB
.خارجي x_ISRStack_سر
.خارجي xCriticalNesting
.خارجي pxCriticalNesting
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_FPU_CONTEXT
addi sp, sp, -( پورټ_FPU_CONTEXT_اندازه )
/* Store the FPU registers. */
store_f f0,  پورټ_FPU_REG_دننه_واټن( 0  )( sp )
store_f f1,  پورټ_FPU_REG_دننه_واټن( 1  )( sp )
store_f f2,  پورټ_FPU_REG_دننه_واټن( 2  )( sp )
store_f f3,  پورټ_FPU_REG_دننه_واټن( 3  )( sp )
store_f f4,  پورټ_FPU_REG_دننه_واټن( 4  )( sp )
store_f f5,  پورټ_FPU_REG_دننه_واټن( 5  )( sp )
store_f f6,  پورټ_FPU_REG_دننه_واټن( 6  )( sp )
store_f f7,  پورټ_FPU_REG_دننه_واټن( 7  )( sp )
store_f f8,  پورټ_FPU_REG_دننه_واټن( 8  )( sp )
store_f f9,  پورټ_FPU_REG_دننه_واټن( 9  )( sp )
store_f f10, پورټ_FPU_REG_دننه_واټن( 10 )( sp )
store_f f11, پورټ_FPU_REG_دننه_واټن( 11 )( sp )
store_f f12, پورټ_FPU_REG_دننه_واټن( 12 )( sp )
store_f f13, پورټ_FPU_REG_دننه_واټن( 13 )( sp )
store_f f14, پورټ_FPU_REG_دننه_واټن( 14 )( sp )
store_f f15, پورټ_FPU_REG_دننه_واټن( 15 )( sp )
store_f f16, پورټ_FPU_REG_دننه_واټن( 16 )( sp )
store_f f17, پورټ_FPU_REG_دننه_واټن( 17 )( sp )
store_f f18, پورټ_FPU_REG_دننه_واټن( 18 )( sp )
store_f f19, پورټ_FPU_REG_دننه_واټن( 19 )( sp )
store_f f20, پورټ_FPU_REG_دننه_واټن( 20 )( sp )
store_f f21, پورټ_FPU_REG_دننه_واټن( 21 )( sp )
store_f f22, پورټ_FPU_REG_دننه_واټن( 22 )( sp )
store_f f23, پورټ_FPU_REG_دننه_واټن( 23 )( sp )
store_f f24, پورټ_FPU_REG_دننه_واټن( 24 )( sp )
store_f f25, پورټ_FPU_REG_دننه_واټن( 25 )( sp )
store_f f26, پورټ_FPU_REG_دننه_واټن( 26 )( sp )
store_f f27, پورټ_FPU_REG_دننه_واټن( 27 )( sp )
store_f f28, پورټ_FPU_REG_دننه_واټن( 28 )( sp )
store_f f29, پورټ_FPU_REG_دننه_واټن( 29 )( sp )
store_f f30, پورټ_FPU_REG_دننه_واټن( 30 )( sp )
store_f f31, پورټ_FPU_REG_دننه_واټن( 31 )( sp )
csrr t0, fcsr
store_x t0,  پورټ_FPU_REG_دننه_واټن( 32 )( sp )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_FPU_CONTEXT
/* Restore the FPU registers. */
بارول_f f0,  پورټ_FPU_REG_دننه_واټن( 0  )( sp )
بارول_f f1,  پورټ_FPU_REG_دننه_واټن( 1  )( sp )
بارول_f f2,  پورټ_FPU_REG_دننه_واټن( 2  )( sp )
بارول_f f3,  پورټ_FPU_REG_دننه_واټن( 3  )( sp )
بارول_f f4,  پورټ_FPU_REG_دننه_واټن( 4  )( sp )
بارول_f f5,  پورټ_FPU_REG_دننه_واټن( 5  )( sp )
بارول_f f6,  پورټ_FPU_REG_دننه_واټن( 6  )( sp )
بارول_f f7,  پورټ_FPU_REG_دننه_واټن( 7  )( sp )
بارول_f f8,  پورټ_FPU_REG_دننه_واټن( 8  )( sp )
بارول_f f9,  پورټ_FPU_REG_دننه_واټن( 9  )( sp )
بارول_f f10, پورټ_FPU_REG_دننه_واټن( 10 )( sp )
بارول_f f11, پورټ_FPU_REG_دننه_واټن( 11 )( sp )
بارول_f f12, پورټ_FPU_REG_دننه_واټن( 12 )( sp )
بارول_f f13, پورټ_FPU_REG_دننه_واټن( 13 )( sp )
بارول_f f14, پورټ_FPU_REG_دننه_واټن( 14 )( sp )
بارول_f f15, پورټ_FPU_REG_دننه_واټن( 15 )( sp )
بارول_f f16, پورټ_FPU_REG_دننه_واټن( 16 )( sp )
بارول_f f17, پورټ_FPU_REG_دننه_واټن( 17 )( sp )
بارول_f f18, پورټ_FPU_REG_دننه_واټن( 18 )( sp )
بارول_f f19, پورټ_FPU_REG_دننه_واټن( 19 )( sp )
بارول_f f20, پورټ_FPU_REG_دننه_واټن( 20 )( sp )
بارول_f f21, پورټ_FPU_REG_دننه_واټن( 21 )( sp )
بارول_f f22, پورټ_FPU_REG_دننه_واټن( 22 )( sp )
بارول_f f23, پورټ_FPU_REG_دننه_واټن( 23 )( sp )
بارول_f f24, پورټ_FPU_REG_دننه_واټن( 24 )( sp )
بارول_f f25, پورټ_FPU_REG_دننه_واټن( 25 )( sp )
بارول_f f26, پورټ_FPU_REG_دننه_واټن( 26 )( sp )
بارول_f f27, پورټ_FPU_REG_دننه_واټن( 27 )( sp )
بارول_f f28, پورټ_FPU_REG_دننه_واټن( 28 )( sp )
بارول_f f29, پورټ_FPU_REG_دننه_واټن( 29 )( sp )
بارول_f f30, پورټ_FPU_REG_دننه_واټن( 30 )( sp )
بارول_f f31, پورټ_FPU_REG_دننه_واټن( 31 )( sp )
بارول_x t0,  پورټ_FPU_REG_دننه_واټن( 32 )( sp )
csrw fcsr, t0
addi sp, sp, ( پورټ_FPU_CONTEXT_اندازه )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
جمع_کړه sp, sp, ( 2 * پورټ_کلمه_اندازه )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */
neg  t0, t0

/* Store the vector registers in group of 8. */
جمع_کړه     sp, sp, t0
vs8r.v  v24, (sp)   /* Store v24-v31. */
جمع_کړه     sp, sp, t0
vs8r.v  v16, (sp)   /* Store v16-v23. */
جمع_کړه     sp, sp, t0
vs8r.v  v8, (sp)    /* Store v8-v15. */
جمع_کړه     sp, sp, t0
vs8r.v  v0, (sp)    /* Store v0-v7. */

/* Store the VPU CSRs. */
addi    sp, sp, -( 4 * پورټ_کلمه_اندازه )
csrr    t0, vstart
store_x t0, 0 * پورټ_کلمه_اندازه( sp )
csrr    t0, vcsr
store_x t0, 1 * پورټ_کلمه_اندازه( sp )
csrr    t0, vl
store_x t0, 2 * پورټ_کلمه_اندازه( sp )
csrr    t0, vtype
store_x t0, 3 * پورټ_کلمه_اندازه( sp )

/* Re-reserve the space for mstatus and epc. */
جمع_کړه sp, sp, -( 2 * پورټ_کلمه_اندازه )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
جمع_کړه sp, sp, ( 2 * پورټ_کلمه_اندازه )

/* Restore the VPU CSRs. */
بارول_x  t0, 0  * پورټ_کلمه_اندازه( sp )
csrw    vstart, t0
بارول_x  t0, 1 * پورټ_کلمه_اندازه( sp )
csrw    vcsr, t0
بارول_x  t0, 2 * پورټ_کلمه_اندازه( sp )
بارول_x  t1, 3 * پورټ_کلمه_اندازه( sp )
vsetvl  x0, t0, t1 /* vlen and vtype can only be updated by using vset*vl* instructions. */
addi    sp, sp, ( 4 * پورټ_کلمه_اندازه )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */

/* Restore the vector registers. */
vl8r.v  v0, (sp)    /* Restore v0-v7. */
جمع_کړه     sp, sp, t0
vl8r.v  v8, (sp)    /* Restore v8-v15. */
جمع_کړه     sp, sp, t0
vl8r.v  v16, (sp)   /* Restore v16-v23. */
جمع_کړه     sp, sp, t0
vl8r.v  v24, (sp)   /* Restore v23-v31. */
جمع_کړه     sp, sp, t0

/* Re-reserve the space for mstatus and epc. */
جمع_کړه sp, sp, -( 2 * پورټ_کلمه_اندازه )
    .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_CONTEXT_دننی
addi sp, sp, -پورټ_CONTEXT_اندازه
store_x x1,  2  * پورټ_کلمه_اندازه( sp )
store_x x5,  3  * پورټ_کلمه_اندازه( sp )
store_x x6,  4  * پورټ_کلمه_اندازه( sp )
store_x x7,  5  * پورټ_کلمه_اندازه( sp )
store_x x8,  6  * پورټ_کلمه_اندازه( sp )
store_x x9,  7  * پورټ_کلمه_اندازه( sp )
store_x x10, 8  * پورټ_کلمه_اندازه( sp )
store_x x11, 9  * پورټ_کلمه_اندازه( sp )
store_x x12, 10 * پورټ_کلمه_اندازه( sp )
store_x x13, 11 * پورټ_کلمه_اندازه( sp )
store_x x14, 12 * پورټ_کلمه_اندازه( sp )
store_x x15, 13 * پورټ_کلمه_اندازه( sp )
#که_نه_تعریف_شوی __riscv_32e
    store_x x16, 14 * پورټ_کلمه_اندازه( sp )
    store_x x17, 15 * پورټ_کلمه_اندازه( sp )
    store_x x18, 16 * پورټ_کلمه_اندازه( sp )
    store_x x19, 17 * پورټ_کلمه_اندازه( sp )
    store_x x20, 18 * پورټ_کلمه_اندازه( sp )
    store_x x21, 19 * پورټ_کلمه_اندازه( sp )
    store_x x22, 20 * پورټ_کلمه_اندازه( sp )
    store_x x23, 21 * پورټ_کلمه_اندازه( sp )
    store_x x24, 22 * پورټ_کلمه_اندازه( sp )
    store_x x25, 23 * پورټ_کلمه_اندازه( sp )
    store_x x26, 24 * پورټ_کلمه_اندازه( sp )
    store_x x27, 25 * پورټ_کلمه_اندازه( sp )
    store_x x28, 26 * پورټ_کلمه_اندازه( sp )
    store_x x29, 27 * پورټ_کلمه_اندازه( sp )
    store_x x30, 28 * پورټ_کلمه_اندازه( sp )
    store_x x31, 29 * پورټ_کلمه_اندازه( sp )
#د_که_پای /* ifndef __riscv_32e */

بارول_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, پورټ_CRITICAL_NESTING_دننه_واټن * پورټ_کلمه_اندازه( sp ) /* Store the critical nesting value to the stack. */

#إذا( configENABLE_FPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_FS_دننه_واټن
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 1f /* If FPU status is not dirty, do not save FPU registers. */

    portcontexSAVE_FPU_CONTEXT
1:
#د_که_پای

#إذا( configENABLE_VPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_VS_دننه_واټن
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 2f /* If VPU status is not dirty, do not save VPU registers. */

    portcontexSAVE_VPU_CONTEXT
2:
#د_که_پای

csrr t0, mstatus
store_x t0, 1 * پورټ_کلمه_اندازه( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

#إذا( configENABLE_FPU == 1 )
    /* Mark the FPU as clean, if it was dirty and we saved FPU registers. */
    srl t1, t0, MSTATUS_FS_دننه_واټن
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 3f

    li t1, ~MSTATUS_FS_ماسک
    and t0, t0, t1
    li t1, MSTATUS_FS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
3:
#د_که_پای

#إذا( configENABLE_VPU == 1 )
    /* Mark the VPU as clean, if it was dirty and we saved VPU registers. */
    srl t1, t0, MSTATUS_VS_دننه_واټن
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 4f

    li t1, ~MSTATUS_VS_ماسک
    and t0, t0, t1
    li t1, MSTATUS_VS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
4:
#د_که_پای

بارول_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

   .endm
/*-----------------------------------------------------------*/

   .macro portcontextSAVE_EXCEPTION_CONTEXT
portcontext_SAVE_CONTEXT_دننی
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
بارول_x sp, x_ISRStack_سر /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_مداخله_CONTEXT
portcontext_SAVE_CONTEXT_دننی
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
بارول_x sp, x_ISRStack_سر /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontextRESTORE_CONTEXT
بارول_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
بارول_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
بارول_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Restore mstatus register. It is important to use t3 (and not t0) here as t3
 * is not clobbered by portcontextRESTORE_VPU_CONTEXT and
 * portcontextRESTORE_FPU_CONTEXT. */
بارول_x t3, 1 * پورټ_کلمه_اندازه( sp )
csrw mstatus, t3

#إذا( configENABLE_VPU == 1 )
    srl t1, t3, MSTATUS_VS_دننه_واټن
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 5f /* If VPU status is not dirty, do not restore VPU registers. */

    portcontextRESTORE_VPU_CONTEXT
5:
#د_که_پای /* ifdef portasmSTORE_VPU_CONTEXT */

#إذا( configENABLE_FPU == 1 )
    srl t1, t3, MSTATUS_FS_دننه_واټن
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 6f /* If FPU status is not dirty, do not restore FPU registers. */

    portcontextRESTORE_FPU_CONTEXT
6:
#د_که_پای /* ifdef portasmSTORE_FPU_CONTEXT */

بارول_x t0, پورټ_CRITICAL_NESTING_دننه_واټن * پورټ_کلمه_اندازه( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
بارول_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

بارول_x x1,  2  * پورټ_کلمه_اندازه( sp )
بارول_x x5,  3  * پورټ_کلمه_اندازه( sp )
بارول_x x6,  4  * پورټ_کلمه_اندازه( sp )
بارول_x x7,  5  * پورټ_کلمه_اندازه( sp )
بارول_x x8,  6  * پورټ_کلمه_اندازه( sp )
بارول_x x9,  7  * پورټ_کلمه_اندازه( sp )
بارول_x x10, 8  * پورټ_کلمه_اندازه( sp )
بارول_x x11, 9  * پورټ_کلمه_اندازه( sp )
بارول_x x12, 10 * پورټ_کلمه_اندازه( sp )
بارول_x x13, 11 * پورټ_کلمه_اندازه( sp )
بارول_x x14, 12 * پورټ_کلمه_اندازه( sp )
بارول_x x15, 13 * پورټ_کلمه_اندازه( sp )
#که_نه_تعریف_شوی __riscv_32e
    بارول_x x16, 14 * پورټ_کلمه_اندازه( sp )
    بارول_x x17, 15 * پورټ_کلمه_اندازه( sp )
    بارول_x x18, 16 * پورټ_کلمه_اندازه( sp )
    بارول_x x19, 17 * پورټ_کلمه_اندازه( sp )
    بارول_x x20, 18 * پورټ_کلمه_اندازه( sp )
    بارول_x x21, 19 * پورټ_کلمه_اندازه( sp )
    بارول_x x22, 20 * پورټ_کلمه_اندازه( sp )
    بارول_x x23, 21 * پورټ_کلمه_اندازه( sp )
    بارول_x x24, 22 * پورټ_کلمه_اندازه( sp )
    بارول_x x25, 23 * پورټ_کلمه_اندازه( sp )
    بارول_x x26, 24 * پورټ_کلمه_اندازه( sp )
    بارول_x x27, 25 * پورټ_کلمه_اندازه( sp )
    بارول_x x28, 26 * پورټ_کلمه_اندازه( sp )
    بارول_x x29, 27 * پورټ_کلمه_اندازه( sp )
    بارول_x x30, 28 * پورټ_کلمه_اندازه( sp )
    بارول_x x31, 29 * پورټ_کلمه_اندازه( sp )
#د_که_پای /* ifndef __riscv_32e */
addi sp, sp, پورټ_CONTEXT_اندازه

mret
   .endm
/*-----------------------------------------------------------*/

#د_که_پای /* PORTCONTEXT_H */
