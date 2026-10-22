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

#جے_بنا_تعریف PORTCONTEXT_H
#تعریف_کرو PORTCONTEXT_H

#جے_بنا_تعریف configENABLE_FPU
    #تعریف_کرو configENABLE_FPU 0
#جے_انت

#جے_بنا_تعریف configENABLE_VPU
    #تعریف_کرو configENABLE_VPU 0
#جے_انت

#إذا __riscv_xlen == 64
    #تعریف_کرو پورٹ_لفظ_ناپ    8
    #تعریف_کرو store_x          sd
    #تعریف_کرو لدو_x           ld
#وإلاإذا __riscv_xlen == 32
    #تعریف_کرو store_x          sw
    #تعریف_کرو لدو_x           lw
    #تعریف_کرو پورٹ_لفظ_ناپ    4
#وإلا
    #غلطی Assembler did not define __riscv_xlen
#جے_انت

#ضمن "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#جے_تعریف_شدہ __riscv_32e
    #تعریف_کرو پورٹ_CONTEXT_ناپ               ( 15 * پورٹ_لفظ_ناپ )
    #تعریف_کرو پورٹ_CRITICAL_NESTING_وتھ    14
#وإلا
    #تعریف_کرو پورٹ_CONTEXT_ناپ               ( 31 * پورٹ_لفظ_ناپ )
    #تعریف_کرو پورٹ_CRITICAL_NESTING_وتھ    30
#جے_انت

#إذا ( configENABLE_FPU == 1 )
    /* Bit [14:13] in the mstatus encode the status of FPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #تعریف_کرو MSTATUS_FS_نقاب                 0x6000
    #تعریف_کرو MSTATUS_FS_INITIAL              0x2000
    #تعریف_کرو MSTATUS_FS_CLEAN                0x4000
    #تعریف_کرو MSTATUS_FS_DIRTY                0x6000
    #تعریف_کرو MSTATUS_FS_وتھ               13

    #جے_تعریف_شدہ __riscv_fdiv
        #إذا __riscv_flen == 32
            #تعریف_کرو لدو_f                  flw
            #تعریف_کرو store_f                 fsw
        #وإلاإذا __riscv_flen == 64
            #تعریف_کرو لدو_f                  fld
            #تعریف_کرو store_f                 fsd
        #وإلا
            #غلطی Assembler did not define __riscv_flen
        #جے_انت

        #تعریف_کرو پورٹ_FPU_REG_ناپ                ( __riscv_flen / 8 )
        #تعریف_کرو پورٹ_FPU_REG_گنتی               33 /* 32 Floating point registers plus one CSR. */
        #تعریف_کرو پورٹ_FPU_REG_وتھ( reg_اشاریہ )  ( ( 2 * پورٹ_لفظ_ناپ ) + ( reg_اشاریہ * پورٹ_FPU_REG_ناپ ) )
        #تعریف_کرو پورٹ_FPU_CONTEXT_ناپ            ( پورٹ_FPU_REG_ناپ * پورٹ_FPU_REG_گنتی )
    #وإلا
        #غلطی configENABLE_FPU must not be سیٹ منزل 1 إذا the hardware does not have FPU
    #جے_انت
#جے_انت

#إذا ( configENABLE_VPU == 1 )
    /* Bit [10:9] in the mstatus encode the status of VPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #تعریف_کرو MSTATUS_VS_نقاب                 0x600
    #تعریف_کرو MSTATUS_VS_INITIAL              0x200
    #تعریف_کرو MSTATUS_VS_CLEAN                0x400
    #تعریف_کرو MSTATUS_VS_DIRTY                0x600
    #تعریف_کرو MSTATUS_VS_وتھ               9

    #جے_بنا_تعریف __riscv_vector
        #غلطی configENABLE_VPU must not be سیٹ منزل 1 إذا the hardware does not have VPU
    #جے_انت
#جے_انت
/*-----------------------------------------------------------*/

.خارجي pxCurrentTCB
.خارجي x_ISRStack_چوٹی
.خارجي xCriticalNesting
.خارجي pxCriticalNesting
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_FPU_CONTEXT
addi sp, sp, -( پورٹ_FPU_CONTEXT_ناپ )
/* Store the FPU registers. */
store_f f0,  پورٹ_FPU_REG_وتھ( 0  )( sp )
store_f f1,  پورٹ_FPU_REG_وتھ( 1  )( sp )
store_f f2,  پورٹ_FPU_REG_وتھ( 2  )( sp )
store_f f3,  پورٹ_FPU_REG_وتھ( 3  )( sp )
store_f f4,  پورٹ_FPU_REG_وتھ( 4  )( sp )
store_f f5,  پورٹ_FPU_REG_وتھ( 5  )( sp )
store_f f6,  پورٹ_FPU_REG_وتھ( 6  )( sp )
store_f f7,  پورٹ_FPU_REG_وتھ( 7  )( sp )
store_f f8,  پورٹ_FPU_REG_وتھ( 8  )( sp )
store_f f9,  پورٹ_FPU_REG_وتھ( 9  )( sp )
store_f f10, پورٹ_FPU_REG_وتھ( 10 )( sp )
store_f f11, پورٹ_FPU_REG_وتھ( 11 )( sp )
store_f f12, پورٹ_FPU_REG_وتھ( 12 )( sp )
store_f f13, پورٹ_FPU_REG_وتھ( 13 )( sp )
store_f f14, پورٹ_FPU_REG_وتھ( 14 )( sp )
store_f f15, پورٹ_FPU_REG_وتھ( 15 )( sp )
store_f f16, پورٹ_FPU_REG_وتھ( 16 )( sp )
store_f f17, پورٹ_FPU_REG_وتھ( 17 )( sp )
store_f f18, پورٹ_FPU_REG_وتھ( 18 )( sp )
store_f f19, پورٹ_FPU_REG_وتھ( 19 )( sp )
store_f f20, پورٹ_FPU_REG_وتھ( 20 )( sp )
store_f f21, پورٹ_FPU_REG_وتھ( 21 )( sp )
store_f f22, پورٹ_FPU_REG_وتھ( 22 )( sp )
store_f f23, پورٹ_FPU_REG_وتھ( 23 )( sp )
store_f f24, پورٹ_FPU_REG_وتھ( 24 )( sp )
store_f f25, پورٹ_FPU_REG_وتھ( 25 )( sp )
store_f f26, پورٹ_FPU_REG_وتھ( 26 )( sp )
store_f f27, پورٹ_FPU_REG_وتھ( 27 )( sp )
store_f f28, پورٹ_FPU_REG_وتھ( 28 )( sp )
store_f f29, پورٹ_FPU_REG_وتھ( 29 )( sp )
store_f f30, پورٹ_FPU_REG_وتھ( 30 )( sp )
store_f f31, پورٹ_FPU_REG_وتھ( 31 )( sp )
csrr t0, fcsr
store_x t0,  پورٹ_FPU_REG_وتھ( 32 )( sp )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_FPU_CONTEXT
/* Restore the FPU registers. */
لدو_f f0,  پورٹ_FPU_REG_وتھ( 0  )( sp )
لدو_f f1,  پورٹ_FPU_REG_وتھ( 1  )( sp )
لدو_f f2,  پورٹ_FPU_REG_وتھ( 2  )( sp )
لدو_f f3,  پورٹ_FPU_REG_وتھ( 3  )( sp )
لدو_f f4,  پورٹ_FPU_REG_وتھ( 4  )( sp )
لدو_f f5,  پورٹ_FPU_REG_وتھ( 5  )( sp )
لدو_f f6,  پورٹ_FPU_REG_وتھ( 6  )( sp )
لدو_f f7,  پورٹ_FPU_REG_وتھ( 7  )( sp )
لدو_f f8,  پورٹ_FPU_REG_وتھ( 8  )( sp )
لدو_f f9,  پورٹ_FPU_REG_وتھ( 9  )( sp )
لدو_f f10, پورٹ_FPU_REG_وتھ( 10 )( sp )
لدو_f f11, پورٹ_FPU_REG_وتھ( 11 )( sp )
لدو_f f12, پورٹ_FPU_REG_وتھ( 12 )( sp )
لدو_f f13, پورٹ_FPU_REG_وتھ( 13 )( sp )
لدو_f f14, پورٹ_FPU_REG_وتھ( 14 )( sp )
لدو_f f15, پورٹ_FPU_REG_وتھ( 15 )( sp )
لدو_f f16, پورٹ_FPU_REG_وتھ( 16 )( sp )
لدو_f f17, پورٹ_FPU_REG_وتھ( 17 )( sp )
لدو_f f18, پورٹ_FPU_REG_وتھ( 18 )( sp )
لدو_f f19, پورٹ_FPU_REG_وتھ( 19 )( sp )
لدو_f f20, پورٹ_FPU_REG_وتھ( 20 )( sp )
لدو_f f21, پورٹ_FPU_REG_وتھ( 21 )( sp )
لدو_f f22, پورٹ_FPU_REG_وتھ( 22 )( sp )
لدو_f f23, پورٹ_FPU_REG_وتھ( 23 )( sp )
لدو_f f24, پورٹ_FPU_REG_وتھ( 24 )( sp )
لدو_f f25, پورٹ_FPU_REG_وتھ( 25 )( sp )
لدو_f f26, پورٹ_FPU_REG_وتھ( 26 )( sp )
لدو_f f27, پورٹ_FPU_REG_وتھ( 27 )( sp )
لدو_f f28, پورٹ_FPU_REG_وتھ( 28 )( sp )
لدو_f f29, پورٹ_FPU_REG_وتھ( 29 )( sp )
لدو_f f30, پورٹ_FPU_REG_وتھ( 30 )( sp )
لدو_f f31, پورٹ_FPU_REG_وتھ( 31 )( sp )
لدو_x t0,  پورٹ_FPU_REG_وتھ( 32 )( sp )
csrw fcsr, t0
addi sp, sp, ( پورٹ_FPU_CONTEXT_ناپ )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
جوڑو sp, sp, ( 2 * پورٹ_لفظ_ناپ )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */
neg  t0, t0

/* Store the vector registers in group of 8. */
جوڑو     sp, sp, t0
vs8r.v  v24, (sp)   /* Store v24-v31. */
جوڑو     sp, sp, t0
vs8r.v  v16, (sp)   /* Store v16-v23. */
جوڑو     sp, sp, t0
vs8r.v  v8, (sp)    /* Store v8-v15. */
جوڑو     sp, sp, t0
vs8r.v  v0, (sp)    /* Store v0-v7. */

/* Store the VPU CSRs. */
addi    sp, sp, -( 4 * پورٹ_لفظ_ناپ )
csrr    t0, vstart
store_x t0, 0 * پورٹ_لفظ_ناپ( sp )
csrr    t0, vcsr
store_x t0, 1 * پورٹ_لفظ_ناپ( sp )
csrr    t0, vl
store_x t0, 2 * پورٹ_لفظ_ناپ( sp )
csrr    t0, vtype
store_x t0, 3 * پورٹ_لفظ_ناپ( sp )

/* Re-reserve the space for mstatus and epc. */
جوڑو sp, sp, -( 2 * پورٹ_لفظ_ناپ )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
جوڑو sp, sp, ( 2 * پورٹ_لفظ_ناپ )

/* Restore the VPU CSRs. */
لدو_x  t0, 0  * پورٹ_لفظ_ناپ( sp )
csrw    vstart, t0
لدو_x  t0, 1 * پورٹ_لفظ_ناپ( sp )
csrw    vcsr, t0
لدو_x  t0, 2 * پورٹ_لفظ_ناپ( sp )
لدو_x  t1, 3 * پورٹ_لفظ_ناپ( sp )
vsetvl  x0, t0, t1 /* vlen and vtype can only be updated by using vset*vl* instructions. */
addi    sp, sp, ( 4 * پورٹ_لفظ_ناپ )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */

/* Restore the vector registers. */
vl8r.v  v0, (sp)    /* Restore v0-v7. */
جوڑو     sp, sp, t0
vl8r.v  v8, (sp)    /* Restore v8-v15. */
جوڑو     sp, sp, t0
vl8r.v  v16, (sp)   /* Restore v16-v23. */
جوڑو     sp, sp, t0
vl8r.v  v24, (sp)   /* Restore v23-v31. */
جوڑو     sp, sp, t0

/* Re-reserve the space for mstatus and epc. */
جوڑو sp, sp, -( 2 * پورٹ_لفظ_ناپ )
    .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_CONTEXT_اندرونی
addi sp, sp, -پورٹ_CONTEXT_ناپ
store_x x1,  2  * پورٹ_لفظ_ناپ( sp )
store_x x5,  3  * پورٹ_لفظ_ناپ( sp )
store_x x6,  4  * پورٹ_لفظ_ناپ( sp )
store_x x7,  5  * پورٹ_لفظ_ناپ( sp )
store_x x8,  6  * پورٹ_لفظ_ناپ( sp )
store_x x9,  7  * پورٹ_لفظ_ناپ( sp )
store_x x10, 8  * پورٹ_لفظ_ناپ( sp )
store_x x11, 9  * پورٹ_لفظ_ناپ( sp )
store_x x12, 10 * پورٹ_لفظ_ناپ( sp )
store_x x13, 11 * پورٹ_لفظ_ناپ( sp )
store_x x14, 12 * پورٹ_لفظ_ناپ( sp )
store_x x15, 13 * پورٹ_لفظ_ناپ( sp )
#جے_بنا_تعریف __riscv_32e
    store_x x16, 14 * پورٹ_لفظ_ناپ( sp )
    store_x x17, 15 * پورٹ_لفظ_ناپ( sp )
    store_x x18, 16 * پورٹ_لفظ_ناپ( sp )
    store_x x19, 17 * پورٹ_لفظ_ناپ( sp )
    store_x x20, 18 * پورٹ_لفظ_ناپ( sp )
    store_x x21, 19 * پورٹ_لفظ_ناپ( sp )
    store_x x22, 20 * پورٹ_لفظ_ناپ( sp )
    store_x x23, 21 * پورٹ_لفظ_ناپ( sp )
    store_x x24, 22 * پورٹ_لفظ_ناپ( sp )
    store_x x25, 23 * پورٹ_لفظ_ناپ( sp )
    store_x x26, 24 * پورٹ_لفظ_ناپ( sp )
    store_x x27, 25 * پورٹ_لفظ_ناپ( sp )
    store_x x28, 26 * پورٹ_لفظ_ناپ( sp )
    store_x x29, 27 * پورٹ_لفظ_ناپ( sp )
    store_x x30, 28 * پورٹ_لفظ_ناپ( sp )
    store_x x31, 29 * پورٹ_لفظ_ناپ( sp )
#جے_انت /* ifndef __riscv_32e */

لدو_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, پورٹ_CRITICAL_NESTING_وتھ * پورٹ_لفظ_ناپ( sp ) /* Store the critical nesting value to the stack. */

#إذا( configENABLE_FPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_FS_وتھ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 1f /* If FPU status is not dirty, do not save FPU registers. */

    portcontexSAVE_FPU_CONTEXT
1:
#جے_انت

#إذا( configENABLE_VPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_VS_وتھ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 2f /* If VPU status is not dirty, do not save VPU registers. */

    portcontexSAVE_VPU_CONTEXT
2:
#جے_انت

csrr t0, mstatus
store_x t0, 1 * پورٹ_لفظ_ناپ( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

#إذا( configENABLE_FPU == 1 )
    /* Mark the FPU as clean, if it was dirty and we saved FPU registers. */
    srl t1, t0, MSTATUS_FS_وتھ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 3f

    li t1, ~MSTATUS_FS_نقاب
    and t0, t0, t1
    li t1, MSTATUS_FS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
3:
#جے_انت

#إذا( configENABLE_VPU == 1 )
    /* Mark the VPU as clean, if it was dirty and we saved VPU registers. */
    srl t1, t0, MSTATUS_VS_وتھ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 4f

    li t1, ~MSTATUS_VS_نقاب
    and t0, t0, t1
    li t1, MSTATUS_VS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
4:
#جے_انت

لدو_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

   .endm
/*-----------------------------------------------------------*/

   .macro portcontextSAVE_EXCEPTION_CONTEXT
portcontext_SAVE_CONTEXT_اندرونی
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
لدو_x sp, x_ISRStack_چوٹی /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_رکاوٹ_CONTEXT
portcontext_SAVE_CONTEXT_اندرونی
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
لدو_x sp, x_ISRStack_چوٹی /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontextRESTORE_CONTEXT
لدو_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
لدو_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
لدو_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Restore mstatus register. It is important to use t3 (and not t0) here as t3
 * is not clobbered by portcontextRESTORE_VPU_CONTEXT and
 * portcontextRESTORE_FPU_CONTEXT. */
لدو_x t3, 1 * پورٹ_لفظ_ناپ( sp )
csrw mstatus, t3

#إذا( configENABLE_VPU == 1 )
    srl t1, t3, MSTATUS_VS_وتھ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 5f /* If VPU status is not dirty, do not restore VPU registers. */

    portcontextRESTORE_VPU_CONTEXT
5:
#جے_انت /* ifdef portasmSTORE_VPU_CONTEXT */

#إذا( configENABLE_FPU == 1 )
    srl t1, t3, MSTATUS_FS_وتھ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 6f /* If FPU status is not dirty, do not restore FPU registers. */

    portcontextRESTORE_FPU_CONTEXT
6:
#جے_انت /* ifdef portasmSTORE_FPU_CONTEXT */

لدو_x t0, پورٹ_CRITICAL_NESTING_وتھ * پورٹ_لفظ_ناپ( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
لدو_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

لدو_x x1,  2  * پورٹ_لفظ_ناپ( sp )
لدو_x x5,  3  * پورٹ_لفظ_ناپ( sp )
لدو_x x6,  4  * پورٹ_لفظ_ناپ( sp )
لدو_x x7,  5  * پورٹ_لفظ_ناپ( sp )
لدو_x x8,  6  * پورٹ_لفظ_ناپ( sp )
لدو_x x9,  7  * پورٹ_لفظ_ناپ( sp )
لدو_x x10, 8  * پورٹ_لفظ_ناپ( sp )
لدو_x x11, 9  * پورٹ_لفظ_ناپ( sp )
لدو_x x12, 10 * پورٹ_لفظ_ناپ( sp )
لدو_x x13, 11 * پورٹ_لفظ_ناپ( sp )
لدو_x x14, 12 * پورٹ_لفظ_ناپ( sp )
لدو_x x15, 13 * پورٹ_لفظ_ناپ( sp )
#جے_بنا_تعریف __riscv_32e
    لدو_x x16, 14 * پورٹ_لفظ_ناپ( sp )
    لدو_x x17, 15 * پورٹ_لفظ_ناپ( sp )
    لدو_x x18, 16 * پورٹ_لفظ_ناپ( sp )
    لدو_x x19, 17 * پورٹ_لفظ_ناپ( sp )
    لدو_x x20, 18 * پورٹ_لفظ_ناپ( sp )
    لدو_x x21, 19 * پورٹ_لفظ_ناپ( sp )
    لدو_x x22, 20 * پورٹ_لفظ_ناپ( sp )
    لدو_x x23, 21 * پورٹ_لفظ_ناپ( sp )
    لدو_x x24, 22 * پورٹ_لفظ_ناپ( sp )
    لدو_x x25, 23 * پورٹ_لفظ_ناپ( sp )
    لدو_x x26, 24 * پورٹ_لفظ_ناپ( sp )
    لدو_x x27, 25 * پورٹ_لفظ_ناپ( sp )
    لدو_x x28, 26 * پورٹ_لفظ_ناپ( sp )
    لدو_x x29, 27 * پورٹ_لفظ_ناپ( sp )
    لدو_x x30, 28 * پورٹ_لفظ_ناپ( sp )
    لدو_x x31, 29 * پورٹ_لفظ_ناپ( sp )
#جے_انت /* ifndef __riscv_32e */
addi sp, sp, پورٹ_CONTEXT_ناپ

mret
   .endm
/*-----------------------------------------------------------*/

#جے_انت /* PORTCONTEXT_H */
