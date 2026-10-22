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

#اگر_تعریف_نشده configENABLE_FPU
    #تعریف_کن configENABLE_FPU 0
#پایان_اگر

#اگر_تعریف_نشده configENABLE_VPU
    #تعریف_کن configENABLE_VPU 0
#پایان_اگر

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
    #تعریف_کن پورت_CRITICAL_NESTING_جابه_جایی    14
#وإلا
    #تعریف_کن پورت_CONTEXT_اندازه               ( 31 * پورت_کلمه_اندازه )
    #تعریف_کن پورت_CRITICAL_NESTING_جابه_جایی    30
#پایان_اگر

#إذا ( configENABLE_FPU == 1 )
    /* Bit [14:13] in the mstatus encode the status of FPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #تعریف_کن MSTATUS_FS_ماسک                 0x6000
    #تعریف_کن MSTATUS_FS_INITIAL              0x2000
    #تعریف_کن MSTATUS_FS_CLEAN                0x4000
    #تعریف_کن MSTATUS_FS_DIRTY                0x6000
    #تعریف_کن MSTATUS_FS_جابه_جایی               13

    #اگر_تعریف_شده __riscv_fdiv
        #إذا __riscv_flen == 32
            #تعریف_کن بارگیری_f                  flw
            #تعریف_کن store_f                 fsw
        #وإلاإذا __riscv_flen == 64
            #تعریف_کن بارگیری_f                  fld
            #تعریف_کن store_f                 fsd
        #وإلا
            #خطا Assembler did not define __riscv_flen
        #پایان_اگر

        #تعریف_کن پورت_FPU_REG_اندازه                ( __riscv_flen / 8 )
        #تعریف_کن پورت_FPU_REG_شمار               33 /* 32 Floating point registers plus one CSR. */
        #تعریف_کن پورت_FPU_REG_جابه_جایی( reg_شاخص )  ( ( 2 * پورت_کلمه_اندازه ) + ( reg_شاخص * پورت_FPU_REG_اندازه ) )
        #تعریف_کن پورت_FPU_CONTEXT_اندازه            ( پورت_FPU_REG_اندازه * پورت_FPU_REG_شمار )
    #وإلا
        #خطا configENABLE_FPU must not be مجموعه مقصد 1 إذا the hardware does not have FPU
    #پایان_اگر
#پایان_اگر

#إذا ( configENABLE_VPU == 1 )
    /* Bit [10:9] in the mstatus encode the status of VPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #تعریف_کن MSTATUS_VS_ماسک                 0x600
    #تعریف_کن MSTATUS_VS_INITIAL              0x200
    #تعریف_کن MSTATUS_VS_CLEAN                0x400
    #تعریف_کن MSTATUS_VS_DIRTY                0x600
    #تعریف_کن MSTATUS_VS_جابه_جایی               9

    #اگر_تعریف_نشده __riscv_vector
        #خطا configENABLE_VPU must not be مجموعه مقصد 1 إذا the hardware does not have VPU
    #پایان_اگر
#پایان_اگر
/*-----------------------------------------------------------*/

.خارجي pxCurrentTCB
.خارجي x_ISRStack_بالاترین
.خارجي xCriticalNesting
.خارجي pxCriticalNesting
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_FPU_CONTEXT
addi sp, sp, -( پورت_FPU_CONTEXT_اندازه )
/* Store the FPU registers. */
store_f f0,  پورت_FPU_REG_جابه_جایی( 0  )( sp )
store_f f1,  پورت_FPU_REG_جابه_جایی( 1  )( sp )
store_f f2,  پورت_FPU_REG_جابه_جایی( 2  )( sp )
store_f f3,  پورت_FPU_REG_جابه_جایی( 3  )( sp )
store_f f4,  پورت_FPU_REG_جابه_جایی( 4  )( sp )
store_f f5,  پورت_FPU_REG_جابه_جایی( 5  )( sp )
store_f f6,  پورت_FPU_REG_جابه_جایی( 6  )( sp )
store_f f7,  پورت_FPU_REG_جابه_جایی( 7  )( sp )
store_f f8,  پورت_FPU_REG_جابه_جایی( 8  )( sp )
store_f f9,  پورت_FPU_REG_جابه_جایی( 9  )( sp )
store_f f10, پورت_FPU_REG_جابه_جایی( 10 )( sp )
store_f f11, پورت_FPU_REG_جابه_جایی( 11 )( sp )
store_f f12, پورت_FPU_REG_جابه_جایی( 12 )( sp )
store_f f13, پورت_FPU_REG_جابه_جایی( 13 )( sp )
store_f f14, پورت_FPU_REG_جابه_جایی( 14 )( sp )
store_f f15, پورت_FPU_REG_جابه_جایی( 15 )( sp )
store_f f16, پورت_FPU_REG_جابه_جایی( 16 )( sp )
store_f f17, پورت_FPU_REG_جابه_جایی( 17 )( sp )
store_f f18, پورت_FPU_REG_جابه_جایی( 18 )( sp )
store_f f19, پورت_FPU_REG_جابه_جایی( 19 )( sp )
store_f f20, پورت_FPU_REG_جابه_جایی( 20 )( sp )
store_f f21, پورت_FPU_REG_جابه_جایی( 21 )( sp )
store_f f22, پورت_FPU_REG_جابه_جایی( 22 )( sp )
store_f f23, پورت_FPU_REG_جابه_جایی( 23 )( sp )
store_f f24, پورت_FPU_REG_جابه_جایی( 24 )( sp )
store_f f25, پورت_FPU_REG_جابه_جایی( 25 )( sp )
store_f f26, پورت_FPU_REG_جابه_جایی( 26 )( sp )
store_f f27, پورت_FPU_REG_جابه_جایی( 27 )( sp )
store_f f28, پورت_FPU_REG_جابه_جایی( 28 )( sp )
store_f f29, پورت_FPU_REG_جابه_جایی( 29 )( sp )
store_f f30, پورت_FPU_REG_جابه_جایی( 30 )( sp )
store_f f31, پورت_FPU_REG_جابه_جایی( 31 )( sp )
csrr t0, fcsr
store_x t0,  پورت_FPU_REG_جابه_جایی( 32 )( sp )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_FPU_CONTEXT
/* Restore the FPU registers. */
بارگیری_f f0,  پورت_FPU_REG_جابه_جایی( 0  )( sp )
بارگیری_f f1,  پورت_FPU_REG_جابه_جایی( 1  )( sp )
بارگیری_f f2,  پورت_FPU_REG_جابه_جایی( 2  )( sp )
بارگیری_f f3,  پورت_FPU_REG_جابه_جایی( 3  )( sp )
بارگیری_f f4,  پورت_FPU_REG_جابه_جایی( 4  )( sp )
بارگیری_f f5,  پورت_FPU_REG_جابه_جایی( 5  )( sp )
بارگیری_f f6,  پورت_FPU_REG_جابه_جایی( 6  )( sp )
بارگیری_f f7,  پورت_FPU_REG_جابه_جایی( 7  )( sp )
بارگیری_f f8,  پورت_FPU_REG_جابه_جایی( 8  )( sp )
بارگیری_f f9,  پورت_FPU_REG_جابه_جایی( 9  )( sp )
بارگیری_f f10, پورت_FPU_REG_جابه_جایی( 10 )( sp )
بارگیری_f f11, پورت_FPU_REG_جابه_جایی( 11 )( sp )
بارگیری_f f12, پورت_FPU_REG_جابه_جایی( 12 )( sp )
بارگیری_f f13, پورت_FPU_REG_جابه_جایی( 13 )( sp )
بارگیری_f f14, پورت_FPU_REG_جابه_جایی( 14 )( sp )
بارگیری_f f15, پورت_FPU_REG_جابه_جایی( 15 )( sp )
بارگیری_f f16, پورت_FPU_REG_جابه_جایی( 16 )( sp )
بارگیری_f f17, پورت_FPU_REG_جابه_جایی( 17 )( sp )
بارگیری_f f18, پورت_FPU_REG_جابه_جایی( 18 )( sp )
بارگیری_f f19, پورت_FPU_REG_جابه_جایی( 19 )( sp )
بارگیری_f f20, پورت_FPU_REG_جابه_جایی( 20 )( sp )
بارگیری_f f21, پورت_FPU_REG_جابه_جایی( 21 )( sp )
بارگیری_f f22, پورت_FPU_REG_جابه_جایی( 22 )( sp )
بارگیری_f f23, پورت_FPU_REG_جابه_جایی( 23 )( sp )
بارگیری_f f24, پورت_FPU_REG_جابه_جایی( 24 )( sp )
بارگیری_f f25, پورت_FPU_REG_جابه_جایی( 25 )( sp )
بارگیری_f f26, پورت_FPU_REG_جابه_جایی( 26 )( sp )
بارگیری_f f27, پورت_FPU_REG_جابه_جایی( 27 )( sp )
بارگیری_f f28, پورت_FPU_REG_جابه_جایی( 28 )( sp )
بارگیری_f f29, پورت_FPU_REG_جابه_جایی( 29 )( sp )
بارگیری_f f30, پورت_FPU_REG_جابه_جایی( 30 )( sp )
بارگیری_f f31, پورت_FPU_REG_جابه_جایی( 31 )( sp )
بارگیری_x t0,  پورت_FPU_REG_جابه_جایی( 32 )( sp )
csrw fcsr, t0
addi sp, sp, ( پورت_FPU_CONTEXT_اندازه )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
جمع_کن sp, sp, ( 2 * پورت_کلمه_اندازه )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */
neg  t0, t0

/* Store the vector registers in group of 8. */
جمع_کن     sp, sp, t0
vs8r.v  v24, (sp)   /* Store v24-v31. */
جمع_کن     sp, sp, t0
vs8r.v  v16, (sp)   /* Store v16-v23. */
جمع_کن     sp, sp, t0
vs8r.v  v8, (sp)    /* Store v8-v15. */
جمع_کن     sp, sp, t0
vs8r.v  v0, (sp)    /* Store v0-v7. */

/* Store the VPU CSRs. */
addi    sp, sp, -( 4 * پورت_کلمه_اندازه )
csrr    t0, vstart
store_x t0, 0 * پورت_کلمه_اندازه( sp )
csrr    t0, vcsr
store_x t0, 1 * پورت_کلمه_اندازه( sp )
csrr    t0, vl
store_x t0, 2 * پورت_کلمه_اندازه( sp )
csrr    t0, vtype
store_x t0, 3 * پورت_کلمه_اندازه( sp )

/* Re-reserve the space for mstatus and epc. */
جمع_کن sp, sp, -( 2 * پورت_کلمه_اندازه )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
جمع_کن sp, sp, ( 2 * پورت_کلمه_اندازه )

/* Restore the VPU CSRs. */
بارگیری_x  t0, 0  * پورت_کلمه_اندازه( sp )
csrw    vstart, t0
بارگیری_x  t0, 1 * پورت_کلمه_اندازه( sp )
csrw    vcsr, t0
بارگیری_x  t0, 2 * پورت_کلمه_اندازه( sp )
بارگیری_x  t1, 3 * پورت_کلمه_اندازه( sp )
vsetvl  x0, t0, t1 /* vlen and vtype can only be updated by using vset*vl* instructions. */
addi    sp, sp, ( 4 * پورت_کلمه_اندازه )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */

/* Restore the vector registers. */
vl8r.v  v0, (sp)    /* Restore v0-v7. */
جمع_کن     sp, sp, t0
vl8r.v  v8, (sp)    /* Restore v8-v15. */
جمع_کن     sp, sp, t0
vl8r.v  v16, (sp)   /* Restore v16-v23. */
جمع_کن     sp, sp, t0
vl8r.v  v24, (sp)   /* Restore v23-v31. */
جمع_کن     sp, sp, t0

/* Re-reserve the space for mstatus and epc. */
جمع_کن sp, sp, -( 2 * پورت_کلمه_اندازه )
    .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_CONTEXT_داخلی
addi sp, sp, -پورت_CONTEXT_اندازه
store_x x1,  2  * پورت_کلمه_اندازه( sp )
store_x x5,  3  * پورت_کلمه_اندازه( sp )
store_x x6,  4  * پورت_کلمه_اندازه( sp )
store_x x7,  5  * پورت_کلمه_اندازه( sp )
store_x x8,  6  * پورت_کلمه_اندازه( sp )
store_x x9,  7  * پورت_کلمه_اندازه( sp )
store_x x10, 8  * پورت_کلمه_اندازه( sp )
store_x x11, 9  * پورت_کلمه_اندازه( sp )
store_x x12, 10 * پورت_کلمه_اندازه( sp )
store_x x13, 11 * پورت_کلمه_اندازه( sp )
store_x x14, 12 * پورت_کلمه_اندازه( sp )
store_x x15, 13 * پورت_کلمه_اندازه( sp )
#اگر_تعریف_نشده __riscv_32e
    store_x x16, 14 * پورت_کلمه_اندازه( sp )
    store_x x17, 15 * پورت_کلمه_اندازه( sp )
    store_x x18, 16 * پورت_کلمه_اندازه( sp )
    store_x x19, 17 * پورت_کلمه_اندازه( sp )
    store_x x20, 18 * پورت_کلمه_اندازه( sp )
    store_x x21, 19 * پورت_کلمه_اندازه( sp )
    store_x x22, 20 * پورت_کلمه_اندازه( sp )
    store_x x23, 21 * پورت_کلمه_اندازه( sp )
    store_x x24, 22 * پورت_کلمه_اندازه( sp )
    store_x x25, 23 * پورت_کلمه_اندازه( sp )
    store_x x26, 24 * پورت_کلمه_اندازه( sp )
    store_x x27, 25 * پورت_کلمه_اندازه( sp )
    store_x x28, 26 * پورت_کلمه_اندازه( sp )
    store_x x29, 27 * پورت_کلمه_اندازه( sp )
    store_x x30, 28 * پورت_کلمه_اندازه( sp )
    store_x x31, 29 * پورت_کلمه_اندازه( sp )
#پایان_اگر /* ifndef __riscv_32e */

بارگیری_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, پورت_CRITICAL_NESTING_جابه_جایی * پورت_کلمه_اندازه( sp ) /* Store the critical nesting value to the stack. */

#إذا( configENABLE_FPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_FS_جابه_جایی
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 1f /* If FPU status is not dirty, do not save FPU registers. */

    portcontexSAVE_FPU_CONTEXT
1:
#پایان_اگر

#إذا( configENABLE_VPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_VS_جابه_جایی
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 2f /* If VPU status is not dirty, do not save VPU registers. */

    portcontexSAVE_VPU_CONTEXT
2:
#پایان_اگر

csrr t0, mstatus
store_x t0, 1 * پورت_کلمه_اندازه( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

#إذا( configENABLE_FPU == 1 )
    /* Mark the FPU as clean, if it was dirty and we saved FPU registers. */
    srl t1, t0, MSTATUS_FS_جابه_جایی
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 3f

    li t1, ~MSTATUS_FS_ماسک
    and t0, t0, t1
    li t1, MSTATUS_FS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
3:
#پایان_اگر

#إذا( configENABLE_VPU == 1 )
    /* Mark the VPU as clean, if it was dirty and we saved VPU registers. */
    srl t1, t0, MSTATUS_VS_جابه_جایی
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 4f

    li t1, ~MSTATUS_VS_ماسک
    and t0, t0, t1
    li t1, MSTATUS_VS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
4:
#پایان_اگر

بارگیری_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

   .endm
/*-----------------------------------------------------------*/

   .macro portcontextSAVE_EXCEPTION_CONTEXT
portcontext_SAVE_CONTEXT_داخلی
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
بارگیری_x sp, x_ISRStack_بالاترین /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_وقفه_CONTEXT
portcontext_SAVE_CONTEXT_داخلی
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
بارگیری_x sp, x_ISRStack_بالاترین /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontextRESTORE_CONTEXT
بارگیری_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
بارگیری_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
بارگیری_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Restore mstatus register. It is important to use t3 (and not t0) here as t3
 * is not clobbered by portcontextRESTORE_VPU_CONTEXT and
 * portcontextRESTORE_FPU_CONTEXT. */
بارگیری_x t3, 1 * پورت_کلمه_اندازه( sp )
csrw mstatus, t3

#إذا( configENABLE_VPU == 1 )
    srl t1, t3, MSTATUS_VS_جابه_جایی
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 5f /* If VPU status is not dirty, do not restore VPU registers. */

    portcontextRESTORE_VPU_CONTEXT
5:
#پایان_اگر /* ifdef portasmSTORE_VPU_CONTEXT */

#إذا( configENABLE_FPU == 1 )
    srl t1, t3, MSTATUS_FS_جابه_جایی
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 6f /* If FPU status is not dirty, do not restore FPU registers. */

    portcontextRESTORE_FPU_CONTEXT
6:
#پایان_اگر /* ifdef portasmSTORE_FPU_CONTEXT */

بارگیری_x t0, پورت_CRITICAL_NESTING_جابه_جایی * پورت_کلمه_اندازه( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
بارگیری_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

بارگیری_x x1,  2  * پورت_کلمه_اندازه( sp )
بارگیری_x x5,  3  * پورت_کلمه_اندازه( sp )
بارگیری_x x6,  4  * پورت_کلمه_اندازه( sp )
بارگیری_x x7,  5  * پورت_کلمه_اندازه( sp )
بارگیری_x x8,  6  * پورت_کلمه_اندازه( sp )
بارگیری_x x9,  7  * پورت_کلمه_اندازه( sp )
بارگیری_x x10, 8  * پورت_کلمه_اندازه( sp )
بارگیری_x x11, 9  * پورت_کلمه_اندازه( sp )
بارگیری_x x12, 10 * پورت_کلمه_اندازه( sp )
بارگیری_x x13, 11 * پورت_کلمه_اندازه( sp )
بارگیری_x x14, 12 * پورت_کلمه_اندازه( sp )
بارگیری_x x15, 13 * پورت_کلمه_اندازه( sp )
#اگر_تعریف_نشده __riscv_32e
    بارگیری_x x16, 14 * پورت_کلمه_اندازه( sp )
    بارگیری_x x17, 15 * پورت_کلمه_اندازه( sp )
    بارگیری_x x18, 16 * پورت_کلمه_اندازه( sp )
    بارگیری_x x19, 17 * پورت_کلمه_اندازه( sp )
    بارگیری_x x20, 18 * پورت_کلمه_اندازه( sp )
    بارگیری_x x21, 19 * پورت_کلمه_اندازه( sp )
    بارگیری_x x22, 20 * پورت_کلمه_اندازه( sp )
    بارگیری_x x23, 21 * پورت_کلمه_اندازه( sp )
    بارگیری_x x24, 22 * پورت_کلمه_اندازه( sp )
    بارگیری_x x25, 23 * پورت_کلمه_اندازه( sp )
    بارگیری_x x26, 24 * پورت_کلمه_اندازه( sp )
    بارگیری_x x27, 25 * پورت_کلمه_اندازه( sp )
    بارگیری_x x28, 26 * پورت_کلمه_اندازه( sp )
    بارگیری_x x29, 27 * پورت_کلمه_اندازه( sp )
    بارگیری_x x30, 28 * پورت_کلمه_اندازه( sp )
    بارگیری_x x31, 29 * پورت_کلمه_اندازه( sp )
#پایان_اگر /* ifndef __riscv_32e */
addi sp, sp, پورت_CONTEXT_اندازه

mret
   .endm
/*-----------------------------------------------------------*/

#پایان_اگر /* PORTCONTEXT_H */
