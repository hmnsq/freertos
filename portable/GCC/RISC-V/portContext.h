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

#جيڪڏهن_وصف_نه_ٿيل PORTCONTEXT_H
#وصف_ڪريو PORTCONTEXT_H

#جيڪڏهن_وصف_نه_ٿيل configENABLE_FPU
    #وصف_ڪريو configENABLE_FPU 0
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل configENABLE_VPU
    #وصف_ڪريو configENABLE_VPU 0
#جيڪڏهن_پورو

#إذا __riscv_xlen == 64
    #وصف_ڪريو پورٽ_لفظ_سائيز    8
    #وصف_ڪريو store_x          sd
    #وصف_ڪريو ڀريو_x           ld
#وإلاإذا __riscv_xlen == 32
    #وصف_ڪريو store_x          sw
    #وصف_ڪريو ڀريو_x           lw
    #وصف_ڪريو پورٽ_لفظ_سائيز    4
#وإلا
    #غلطي Assembler did not define __riscv_xlen
#جيڪڏهن_پورو

#ضمن "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#جيڪڏهن_وصف_ٿيل __riscv_32e
    #وصف_ڪريو پورٽ_CONTEXT_سائيز               ( 15 * پورٽ_لفظ_سائيز )
    #وصف_ڪريو پورٽ_CRITICAL_NESTING_وٿي    14
#وإلا
    #وصف_ڪريو پورٽ_CONTEXT_سائيز               ( 31 * پورٽ_لفظ_سائيز )
    #وصف_ڪريو پورٽ_CRITICAL_NESTING_وٿي    30
#جيڪڏهن_پورو

#إذا ( configENABLE_FPU == 1 )
    /* Bit [14:13] in the mstatus encode the status of FPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #وصف_ڪريو MSTATUS_FS_نقاب                 0x6000
    #وصف_ڪريو MSTATUS_FS_INITIAL              0x2000
    #وصف_ڪريو MSTATUS_FS_CLEAN                0x4000
    #وصف_ڪريو MSTATUS_FS_DIRTY                0x6000
    #وصف_ڪريو MSTATUS_FS_وٿي               13

    #جيڪڏهن_وصف_ٿيل __riscv_fdiv
        #إذا __riscv_flen == 32
            #وصف_ڪريو ڀريو_f                  flw
            #وصف_ڪريو store_f                 fsw
        #وإلاإذا __riscv_flen == 64
            #وصف_ڪريو ڀريو_f                  fld
            #وصف_ڪريو store_f                 fsd
        #وإلا
            #غلطي Assembler did not define __riscv_flen
        #جيڪڏهن_پورو

        #وصف_ڪريو پورٽ_FPU_REG_سائيز                ( __riscv_flen / 8 )
        #وصف_ڪريو پورٽ_FPU_REG_ڳڻپ               33 /* 32 Floating point registers plus one CSR. */
        #وصف_ڪريو پورٽ_FPU_REG_وٿي( reg_اشاريو )  ( ( 2 * پورٽ_لفظ_سائيز ) + ( reg_اشاريو * پورٽ_FPU_REG_سائيز ) )
        #وصف_ڪريو پورٽ_FPU_CONTEXT_سائيز            ( پورٽ_FPU_REG_سائيز * پورٽ_FPU_REG_ڳڻپ )
    #وإلا
        #غلطي configENABLE_FPU must not be سيٽ منزل 1 إذا the hardware does not have FPU
    #جيڪڏهن_پورو
#جيڪڏهن_پورو

#إذا ( configENABLE_VPU == 1 )
    /* Bit [10:9] in the mstatus encode the status of VPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #وصف_ڪريو MSTATUS_VS_نقاب                 0x600
    #وصف_ڪريو MSTATUS_VS_INITIAL              0x200
    #وصف_ڪريو MSTATUS_VS_CLEAN                0x400
    #وصف_ڪريو MSTATUS_VS_DIRTY                0x600
    #وصف_ڪريو MSTATUS_VS_وٿي               9

    #جيڪڏهن_وصف_نه_ٿيل __riscv_vector
        #غلطي configENABLE_VPU must not be سيٽ منزل 1 إذا the hardware does not have VPU
    #جيڪڏهن_پورو
#جيڪڏهن_پورو
/*-----------------------------------------------------------*/

.خارجي pxCurrentTCB
.خارجي x_ISRStack_چوٽي
.خارجي xCriticalNesting
.خارجي pxCriticalNesting
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_FPU_CONTEXT
addi sp, sp, -( پورٽ_FPU_CONTEXT_سائيز )
/* Store the FPU registers. */
store_f f0,  پورٽ_FPU_REG_وٿي( 0  )( sp )
store_f f1,  پورٽ_FPU_REG_وٿي( 1  )( sp )
store_f f2,  پورٽ_FPU_REG_وٿي( 2  )( sp )
store_f f3,  پورٽ_FPU_REG_وٿي( 3  )( sp )
store_f f4,  پورٽ_FPU_REG_وٿي( 4  )( sp )
store_f f5,  پورٽ_FPU_REG_وٿي( 5  )( sp )
store_f f6,  پورٽ_FPU_REG_وٿي( 6  )( sp )
store_f f7,  پورٽ_FPU_REG_وٿي( 7  )( sp )
store_f f8,  پورٽ_FPU_REG_وٿي( 8  )( sp )
store_f f9,  پورٽ_FPU_REG_وٿي( 9  )( sp )
store_f f10, پورٽ_FPU_REG_وٿي( 10 )( sp )
store_f f11, پورٽ_FPU_REG_وٿي( 11 )( sp )
store_f f12, پورٽ_FPU_REG_وٿي( 12 )( sp )
store_f f13, پورٽ_FPU_REG_وٿي( 13 )( sp )
store_f f14, پورٽ_FPU_REG_وٿي( 14 )( sp )
store_f f15, پورٽ_FPU_REG_وٿي( 15 )( sp )
store_f f16, پورٽ_FPU_REG_وٿي( 16 )( sp )
store_f f17, پورٽ_FPU_REG_وٿي( 17 )( sp )
store_f f18, پورٽ_FPU_REG_وٿي( 18 )( sp )
store_f f19, پورٽ_FPU_REG_وٿي( 19 )( sp )
store_f f20, پورٽ_FPU_REG_وٿي( 20 )( sp )
store_f f21, پورٽ_FPU_REG_وٿي( 21 )( sp )
store_f f22, پورٽ_FPU_REG_وٿي( 22 )( sp )
store_f f23, پورٽ_FPU_REG_وٿي( 23 )( sp )
store_f f24, پورٽ_FPU_REG_وٿي( 24 )( sp )
store_f f25, پورٽ_FPU_REG_وٿي( 25 )( sp )
store_f f26, پورٽ_FPU_REG_وٿي( 26 )( sp )
store_f f27, پورٽ_FPU_REG_وٿي( 27 )( sp )
store_f f28, پورٽ_FPU_REG_وٿي( 28 )( sp )
store_f f29, پورٽ_FPU_REG_وٿي( 29 )( sp )
store_f f30, پورٽ_FPU_REG_وٿي( 30 )( sp )
store_f f31, پورٽ_FPU_REG_وٿي( 31 )( sp )
csrr t0, fcsr
store_x t0,  پورٽ_FPU_REG_وٿي( 32 )( sp )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_FPU_CONTEXT
/* Restore the FPU registers. */
ڀريو_f f0,  پورٽ_FPU_REG_وٿي( 0  )( sp )
ڀريو_f f1,  پورٽ_FPU_REG_وٿي( 1  )( sp )
ڀريو_f f2,  پورٽ_FPU_REG_وٿي( 2  )( sp )
ڀريو_f f3,  پورٽ_FPU_REG_وٿي( 3  )( sp )
ڀريو_f f4,  پورٽ_FPU_REG_وٿي( 4  )( sp )
ڀريو_f f5,  پورٽ_FPU_REG_وٿي( 5  )( sp )
ڀريو_f f6,  پورٽ_FPU_REG_وٿي( 6  )( sp )
ڀريو_f f7,  پورٽ_FPU_REG_وٿي( 7  )( sp )
ڀريو_f f8,  پورٽ_FPU_REG_وٿي( 8  )( sp )
ڀريو_f f9,  پورٽ_FPU_REG_وٿي( 9  )( sp )
ڀريو_f f10, پورٽ_FPU_REG_وٿي( 10 )( sp )
ڀريو_f f11, پورٽ_FPU_REG_وٿي( 11 )( sp )
ڀريو_f f12, پورٽ_FPU_REG_وٿي( 12 )( sp )
ڀريو_f f13, پورٽ_FPU_REG_وٿي( 13 )( sp )
ڀريو_f f14, پورٽ_FPU_REG_وٿي( 14 )( sp )
ڀريو_f f15, پورٽ_FPU_REG_وٿي( 15 )( sp )
ڀريو_f f16, پورٽ_FPU_REG_وٿي( 16 )( sp )
ڀريو_f f17, پورٽ_FPU_REG_وٿي( 17 )( sp )
ڀريو_f f18, پورٽ_FPU_REG_وٿي( 18 )( sp )
ڀريو_f f19, پورٽ_FPU_REG_وٿي( 19 )( sp )
ڀريو_f f20, پورٽ_FPU_REG_وٿي( 20 )( sp )
ڀريو_f f21, پورٽ_FPU_REG_وٿي( 21 )( sp )
ڀريو_f f22, پورٽ_FPU_REG_وٿي( 22 )( sp )
ڀريو_f f23, پورٽ_FPU_REG_وٿي( 23 )( sp )
ڀريو_f f24, پورٽ_FPU_REG_وٿي( 24 )( sp )
ڀريو_f f25, پورٽ_FPU_REG_وٿي( 25 )( sp )
ڀريو_f f26, پورٽ_FPU_REG_وٿي( 26 )( sp )
ڀريو_f f27, پورٽ_FPU_REG_وٿي( 27 )( sp )
ڀريو_f f28, پورٽ_FPU_REG_وٿي( 28 )( sp )
ڀريو_f f29, پورٽ_FPU_REG_وٿي( 29 )( sp )
ڀريو_f f30, پورٽ_FPU_REG_وٿي( 30 )( sp )
ڀريو_f f31, پورٽ_FPU_REG_وٿي( 31 )( sp )
ڀريو_x t0,  پورٽ_FPU_REG_وٿي( 32 )( sp )
csrw fcsr, t0
addi sp, sp, ( پورٽ_FPU_CONTEXT_سائيز )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
جوڙيو sp, sp, ( 2 * پورٽ_لفظ_سائيز )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */
neg  t0, t0

/* Store the vector registers in group of 8. */
جوڙيو     sp, sp, t0
vs8r.v  v24, (sp)   /* Store v24-v31. */
جوڙيو     sp, sp, t0
vs8r.v  v16, (sp)   /* Store v16-v23. */
جوڙيو     sp, sp, t0
vs8r.v  v8, (sp)    /* Store v8-v15. */
جوڙيو     sp, sp, t0
vs8r.v  v0, (sp)    /* Store v0-v7. */

/* Store the VPU CSRs. */
addi    sp, sp, -( 4 * پورٽ_لفظ_سائيز )
csrr    t0, vstart
store_x t0, 0 * پورٽ_لفظ_سائيز( sp )
csrr    t0, vcsr
store_x t0, 1 * پورٽ_لفظ_سائيز( sp )
csrr    t0, vl
store_x t0, 2 * پورٽ_لفظ_سائيز( sp )
csrr    t0, vtype
store_x t0, 3 * پورٽ_لفظ_سائيز( sp )

/* Re-reserve the space for mstatus and epc. */
جوڙيو sp, sp, -( 2 * پورٽ_لفظ_سائيز )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
جوڙيو sp, sp, ( 2 * پورٽ_لفظ_سائيز )

/* Restore the VPU CSRs. */
ڀريو_x  t0, 0  * پورٽ_لفظ_سائيز( sp )
csrw    vstart, t0
ڀريو_x  t0, 1 * پورٽ_لفظ_سائيز( sp )
csrw    vcsr, t0
ڀريو_x  t0, 2 * پورٽ_لفظ_سائيز( sp )
ڀريو_x  t1, 3 * پورٽ_لفظ_سائيز( sp )
vsetvl  x0, t0, t1 /* vlen and vtype can only be updated by using vset*vl* instructions. */
addi    sp, sp, ( 4 * پورٽ_لفظ_سائيز )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */

/* Restore the vector registers. */
vl8r.v  v0, (sp)    /* Restore v0-v7. */
جوڙيو     sp, sp, t0
vl8r.v  v8, (sp)    /* Restore v8-v15. */
جوڙيو     sp, sp, t0
vl8r.v  v16, (sp)   /* Restore v16-v23. */
جوڙيو     sp, sp, t0
vl8r.v  v24, (sp)   /* Restore v23-v31. */
جوڙيو     sp, sp, t0

/* Re-reserve the space for mstatus and epc. */
جوڙيو sp, sp, -( 2 * پورٽ_لفظ_سائيز )
    .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_CONTEXT_اندروني
addi sp, sp, -پورٽ_CONTEXT_سائيز
store_x x1,  2  * پورٽ_لفظ_سائيز( sp )
store_x x5,  3  * پورٽ_لفظ_سائيز( sp )
store_x x6,  4  * پورٽ_لفظ_سائيز( sp )
store_x x7,  5  * پورٽ_لفظ_سائيز( sp )
store_x x8,  6  * پورٽ_لفظ_سائيز( sp )
store_x x9,  7  * پورٽ_لفظ_سائيز( sp )
store_x x10, 8  * پورٽ_لفظ_سائيز( sp )
store_x x11, 9  * پورٽ_لفظ_سائيز( sp )
store_x x12, 10 * پورٽ_لفظ_سائيز( sp )
store_x x13, 11 * پورٽ_لفظ_سائيز( sp )
store_x x14, 12 * پورٽ_لفظ_سائيز( sp )
store_x x15, 13 * پورٽ_لفظ_سائيز( sp )
#جيڪڏهن_وصف_نه_ٿيل __riscv_32e
    store_x x16, 14 * پورٽ_لفظ_سائيز( sp )
    store_x x17, 15 * پورٽ_لفظ_سائيز( sp )
    store_x x18, 16 * پورٽ_لفظ_سائيز( sp )
    store_x x19, 17 * پورٽ_لفظ_سائيز( sp )
    store_x x20, 18 * پورٽ_لفظ_سائيز( sp )
    store_x x21, 19 * پورٽ_لفظ_سائيز( sp )
    store_x x22, 20 * پورٽ_لفظ_سائيز( sp )
    store_x x23, 21 * پورٽ_لفظ_سائيز( sp )
    store_x x24, 22 * پورٽ_لفظ_سائيز( sp )
    store_x x25, 23 * پورٽ_لفظ_سائيز( sp )
    store_x x26, 24 * پورٽ_لفظ_سائيز( sp )
    store_x x27, 25 * پورٽ_لفظ_سائيز( sp )
    store_x x28, 26 * پورٽ_لفظ_سائيز( sp )
    store_x x29, 27 * پورٽ_لفظ_سائيز( sp )
    store_x x30, 28 * پورٽ_لفظ_سائيز( sp )
    store_x x31, 29 * پورٽ_لفظ_سائيز( sp )
#جيڪڏهن_پورو /* ifndef __riscv_32e */

ڀريو_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, پورٽ_CRITICAL_NESTING_وٿي * پورٽ_لفظ_سائيز( sp ) /* Store the critical nesting value to the stack. */

#إذا( configENABLE_FPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_FS_وٿي
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 1f /* If FPU status is not dirty, do not save FPU registers. */

    portcontexSAVE_FPU_CONTEXT
1:
#جيڪڏهن_پورو

#إذا( configENABLE_VPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_VS_وٿي
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 2f /* If VPU status is not dirty, do not save VPU registers. */

    portcontexSAVE_VPU_CONTEXT
2:
#جيڪڏهن_پورو

csrr t0, mstatus
store_x t0, 1 * پورٽ_لفظ_سائيز( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

#إذا( configENABLE_FPU == 1 )
    /* Mark the FPU as clean, if it was dirty and we saved FPU registers. */
    srl t1, t0, MSTATUS_FS_وٿي
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 3f

    li t1, ~MSTATUS_FS_نقاب
    and t0, t0, t1
    li t1, MSTATUS_FS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
3:
#جيڪڏهن_پورو

#إذا( configENABLE_VPU == 1 )
    /* Mark the VPU as clean, if it was dirty and we saved VPU registers. */
    srl t1, t0, MSTATUS_VS_وٿي
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 4f

    li t1, ~MSTATUS_VS_نقاب
    and t0, t0, t1
    li t1, MSTATUS_VS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
4:
#جيڪڏهن_پورو

ڀريو_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

   .endm
/*-----------------------------------------------------------*/

   .macro portcontextSAVE_EXCEPTION_CONTEXT
portcontext_SAVE_CONTEXT_اندروني
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
ڀريو_x sp, x_ISRStack_چوٽي /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_مداخلت_CONTEXT
portcontext_SAVE_CONTEXT_اندروني
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
ڀريو_x sp, x_ISRStack_چوٽي /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontextRESTORE_CONTEXT
ڀريو_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
ڀريو_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
ڀريو_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Restore mstatus register. It is important to use t3 (and not t0) here as t3
 * is not clobbered by portcontextRESTORE_VPU_CONTEXT and
 * portcontextRESTORE_FPU_CONTEXT. */
ڀريو_x t3, 1 * پورٽ_لفظ_سائيز( sp )
csrw mstatus, t3

#إذا( configENABLE_VPU == 1 )
    srl t1, t3, MSTATUS_VS_وٿي
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 5f /* If VPU status is not dirty, do not restore VPU registers. */

    portcontextRESTORE_VPU_CONTEXT
5:
#جيڪڏهن_پورو /* ifdef portasmSTORE_VPU_CONTEXT */

#إذا( configENABLE_FPU == 1 )
    srl t1, t3, MSTATUS_FS_وٿي
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 6f /* If FPU status is not dirty, do not restore FPU registers. */

    portcontextRESTORE_FPU_CONTEXT
6:
#جيڪڏهن_پورو /* ifdef portasmSTORE_FPU_CONTEXT */

ڀريو_x t0, پورٽ_CRITICAL_NESTING_وٿي * پورٽ_لفظ_سائيز( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
ڀريو_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

ڀريو_x x1,  2  * پورٽ_لفظ_سائيز( sp )
ڀريو_x x5,  3  * پورٽ_لفظ_سائيز( sp )
ڀريو_x x6,  4  * پورٽ_لفظ_سائيز( sp )
ڀريو_x x7,  5  * پورٽ_لفظ_سائيز( sp )
ڀريو_x x8,  6  * پورٽ_لفظ_سائيز( sp )
ڀريو_x x9,  7  * پورٽ_لفظ_سائيز( sp )
ڀريو_x x10, 8  * پورٽ_لفظ_سائيز( sp )
ڀريو_x x11, 9  * پورٽ_لفظ_سائيز( sp )
ڀريو_x x12, 10 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x13, 11 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x14, 12 * پورٽ_لفظ_سائيز( sp )
ڀريو_x x15, 13 * پورٽ_لفظ_سائيز( sp )
#جيڪڏهن_وصف_نه_ٿيل __riscv_32e
    ڀريو_x x16, 14 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x17, 15 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x18, 16 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x19, 17 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x20, 18 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x21, 19 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x22, 20 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x23, 21 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x24, 22 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x25, 23 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x26, 24 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x27, 25 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x28, 26 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x29, 27 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x30, 28 * پورٽ_لفظ_سائيز( sp )
    ڀريو_x x31, 29 * پورٽ_لفظ_سائيز( sp )
#جيڪڏهن_پورو /* ifndef __riscv_32e */
addi sp, sp, پورٽ_CONTEXT_سائيز

mret
   .endm
/*-----------------------------------------------------------*/

#جيڪڏهن_پورو /* PORTCONTEXT_H */
