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

#నిర్వచితం_కాకపోతే configENABLE_FPU
    #నిర్వచించు configENABLE_FPU 0
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే configENABLE_VPU
    #నిర్వచించు configENABLE_VPU 0
#అయితే_ముగింపు

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
    #నిర్వచించు పోర్టు_CRITICAL_NESTING_స్థానభ్రంశం    14
#లేకపోతే
    #నిర్వచించు పోర్టు_CONTEXT_కొలత               ( 31 * పోర్టు_మాట_కొలత )
    #నిర్వచించు పోర్టు_CRITICAL_NESTING_స్థానభ్రంశం    30
#అయితే_ముగింపు

#ఒకవేళ ( configENABLE_FPU == 1 )
    /* Bit [14:13] in the mstatus encode the status of FPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #నిర్వచించు MSTATUS_FS_ముసుగు                 0x6000
    #నిర్వచించు MSTATUS_FS_INITIAL              0x2000
    #నిర్వచించు MSTATUS_FS_CLEAN                0x4000
    #నిర్వచించు MSTATUS_FS_DIRTY                0x6000
    #నిర్వచించు MSTATUS_FS_స్థానభ్రంశం               13

    #నిర్వచితమైతే __riscv_fdiv
        #ఒకవేళ __riscv_flen == 32
            #నిర్వచించు ఎక్కించు_f                  flw
            #నిర్వచించు store_f                 fsw
        #లేదావేళ __riscv_flen == 64
            #నిర్వచించు ఎక్కించు_f                  fld
            #నిర్వచించు store_f                 fsd
        #లేకపోతే
            #దోషం Assembler did not define __riscv_flen
        #అయితే_ముగింపు

        #నిర్వచించు పోర్టు_FPU_REG_కొలత                ( __riscv_flen / 8 )
        #నిర్వచించు పోర్టు_FPU_REG_లెక్క               33 /* 32 Floating point registers plus one CSR. */
        #నిర్వచించు పోర్టు_FPU_REG_స్థానభ్రంశం( reg_సూచీ )  ( ( 2 * పోర్టు_మాట_కొలత ) + ( reg_సూచీ * పోర్టు_FPU_REG_కొలత ) )
        #నిర్వచించు పోర్టు_FPU_CONTEXT_కొలత            ( పోర్టు_FPU_REG_కొలత * పోర్టు_FPU_REG_లెక్క )
    #లేకపోతే
        #దోషం configENABLE_FPU must not be సమితి గమ్యం 1 ఒకవేళ the hardware does not have FPU
    #అయితే_ముగింపు
#అయితే_ముగింపు

#ఒకవేళ ( configENABLE_VPU == 1 )
    /* Bit [10:9] in the mstatus encode the status of VPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #నిర్వచించు MSTATUS_VS_ముసుగు                 0x600
    #నిర్వచించు MSTATUS_VS_INITIAL              0x200
    #నిర్వచించు MSTATUS_VS_CLEAN                0x400
    #నిర్వచించు MSTATUS_VS_DIRTY                0x600
    #నిర్వచించు MSTATUS_VS_స్థానభ్రంశం               9

    #నిర్వచితం_కాకపోతే __riscv_vector
        #దోషం configENABLE_VPU must not be సమితి గమ్యం 1 ఒకవేళ the hardware does not have VPU
    #అయితే_ముగింపు
#అయితే_ముగింపు
/*-----------------------------------------------------------*/

.బాహ్య pxCurrentTCB
.బాహ్య x_ISRStack_శిఖరం
.బాహ్య xCriticalNesting
.బాహ్య pxCriticalNesting
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_FPU_CONTEXT
addi sp, sp, -( పోర్టు_FPU_CONTEXT_కొలత )
/* Store the FPU registers. */
store_f f0,  పోర్టు_FPU_REG_స్థానభ్రంశం( 0  )( sp )
store_f f1,  పోర్టు_FPU_REG_స్థానభ్రంశం( 1  )( sp )
store_f f2,  పోర్టు_FPU_REG_స్థానభ్రంశం( 2  )( sp )
store_f f3,  పోర్టు_FPU_REG_స్థానభ్రంశం( 3  )( sp )
store_f f4,  పోర్టు_FPU_REG_స్థానభ్రంశం( 4  )( sp )
store_f f5,  పోర్టు_FPU_REG_స్థానభ్రంశం( 5  )( sp )
store_f f6,  పోర్టు_FPU_REG_స్థానభ్రంశం( 6  )( sp )
store_f f7,  పోర్టు_FPU_REG_స్థానభ్రంశం( 7  )( sp )
store_f f8,  పోర్టు_FPU_REG_స్థానభ్రంశం( 8  )( sp )
store_f f9,  పోర్టు_FPU_REG_స్థానభ్రంశం( 9  )( sp )
store_f f10, పోర్టు_FPU_REG_స్థానభ్రంశం( 10 )( sp )
store_f f11, పోర్టు_FPU_REG_స్థానభ్రంశం( 11 )( sp )
store_f f12, పోర్టు_FPU_REG_స్థానభ్రంశం( 12 )( sp )
store_f f13, పోర్టు_FPU_REG_స్థానభ్రంశం( 13 )( sp )
store_f f14, పోర్టు_FPU_REG_స్థానభ్రంశం( 14 )( sp )
store_f f15, పోర్టు_FPU_REG_స్థానభ్రంశం( 15 )( sp )
store_f f16, పోర్టు_FPU_REG_స్థానభ్రంశం( 16 )( sp )
store_f f17, పోర్టు_FPU_REG_స్థానభ్రంశం( 17 )( sp )
store_f f18, పోర్టు_FPU_REG_స్థానభ్రంశం( 18 )( sp )
store_f f19, పోర్టు_FPU_REG_స్థానభ్రంశం( 19 )( sp )
store_f f20, పోర్టు_FPU_REG_స్థానభ్రంశం( 20 )( sp )
store_f f21, పోర్టు_FPU_REG_స్థానభ్రంశం( 21 )( sp )
store_f f22, పోర్టు_FPU_REG_స్థానభ్రంశం( 22 )( sp )
store_f f23, పోర్టు_FPU_REG_స్థానభ్రంశం( 23 )( sp )
store_f f24, పోర్టు_FPU_REG_స్థానభ్రంశం( 24 )( sp )
store_f f25, పోర్టు_FPU_REG_స్థానభ్రంశం( 25 )( sp )
store_f f26, పోర్టు_FPU_REG_స్థానభ్రంశం( 26 )( sp )
store_f f27, పోర్టు_FPU_REG_స్థానభ్రంశం( 27 )( sp )
store_f f28, పోర్టు_FPU_REG_స్థానభ్రంశం( 28 )( sp )
store_f f29, పోర్టు_FPU_REG_స్థానభ్రంశం( 29 )( sp )
store_f f30, పోర్టు_FPU_REG_స్థానభ్రంశం( 30 )( sp )
store_f f31, పోర్టు_FPU_REG_స్థానభ్రంశం( 31 )( sp )
csrr t0, fcsr
store_x t0,  పోర్టు_FPU_REG_స్థానభ్రంశం( 32 )( sp )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_FPU_CONTEXT
/* Restore the FPU registers. */
ఎక్కించు_f f0,  పోర్టు_FPU_REG_స్థానభ్రంశం( 0  )( sp )
ఎక్కించు_f f1,  పోర్టు_FPU_REG_స్థానభ్రంశం( 1  )( sp )
ఎక్కించు_f f2,  పోర్టు_FPU_REG_స్థానభ్రంశం( 2  )( sp )
ఎక్కించు_f f3,  పోర్టు_FPU_REG_స్థానభ్రంశం( 3  )( sp )
ఎక్కించు_f f4,  పోర్టు_FPU_REG_స్థానభ్రంశం( 4  )( sp )
ఎక్కించు_f f5,  పోర్టు_FPU_REG_స్థానభ్రంశం( 5  )( sp )
ఎక్కించు_f f6,  పోర్టు_FPU_REG_స్థానభ్రంశం( 6  )( sp )
ఎక్కించు_f f7,  పోర్టు_FPU_REG_స్థానభ్రంశం( 7  )( sp )
ఎక్కించు_f f8,  పోర్టు_FPU_REG_స్థానభ్రంశం( 8  )( sp )
ఎక్కించు_f f9,  పోర్టు_FPU_REG_స్థానభ్రంశం( 9  )( sp )
ఎక్కించు_f f10, పోర్టు_FPU_REG_స్థానభ్రంశం( 10 )( sp )
ఎక్కించు_f f11, పోర్టు_FPU_REG_స్థానభ్రంశం( 11 )( sp )
ఎక్కించు_f f12, పోర్టు_FPU_REG_స్థానభ్రంశం( 12 )( sp )
ఎక్కించు_f f13, పోర్టు_FPU_REG_స్థానభ్రంశం( 13 )( sp )
ఎక్కించు_f f14, పోర్టు_FPU_REG_స్థానభ్రంశం( 14 )( sp )
ఎక్కించు_f f15, పోర్టు_FPU_REG_స్థానభ్రంశం( 15 )( sp )
ఎక్కించు_f f16, పోర్టు_FPU_REG_స్థానభ్రంశం( 16 )( sp )
ఎక్కించు_f f17, పోర్టు_FPU_REG_స్థానభ్రంశం( 17 )( sp )
ఎక్కించు_f f18, పోర్టు_FPU_REG_స్థానభ్రంశం( 18 )( sp )
ఎక్కించు_f f19, పోర్టు_FPU_REG_స్థానభ్రంశం( 19 )( sp )
ఎక్కించు_f f20, పోర్టు_FPU_REG_స్థానభ్రంశం( 20 )( sp )
ఎక్కించు_f f21, పోర్టు_FPU_REG_స్థానభ్రంశం( 21 )( sp )
ఎక్కించు_f f22, పోర్టు_FPU_REG_స్థానభ్రంశం( 22 )( sp )
ఎక్కించు_f f23, పోర్టు_FPU_REG_స్థానభ్రంశం( 23 )( sp )
ఎక్కించు_f f24, పోర్టు_FPU_REG_స్థానభ్రంశం( 24 )( sp )
ఎక్కించు_f f25, పోర్టు_FPU_REG_స్థానభ్రంశం( 25 )( sp )
ఎక్కించు_f f26, పోర్టు_FPU_REG_స్థానభ్రంశం( 26 )( sp )
ఎక్కించు_f f27, పోర్టు_FPU_REG_స్థానభ్రంశం( 27 )( sp )
ఎక్కించు_f f28, పోర్టు_FPU_REG_స్థానభ్రంశం( 28 )( sp )
ఎక్కించు_f f29, పోర్టు_FPU_REG_స్థానభ్రంశం( 29 )( sp )
ఎక్కించు_f f30, పోర్టు_FPU_REG_స్థానభ్రంశం( 30 )( sp )
ఎక్కించు_f f31, పోర్టు_FPU_REG_స్థానభ్రంశం( 31 )( sp )
ఎక్కించు_x t0,  పోర్టు_FPU_REG_స్థానభ్రంశం( 32 )( sp )
csrw fcsr, t0
addi sp, sp, ( పోర్టు_FPU_CONTEXT_కొలత )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
కూడు sp, sp, ( 2 * పోర్టు_మాట_కొలత )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */
neg  t0, t0

/* Store the vector registers in group of 8. */
కూడు     sp, sp, t0
vs8r.v  v24, (sp)   /* Store v24-v31. */
కూడు     sp, sp, t0
vs8r.v  v16, (sp)   /* Store v16-v23. */
కూడు     sp, sp, t0
vs8r.v  v8, (sp)    /* Store v8-v15. */
కూడు     sp, sp, t0
vs8r.v  v0, (sp)    /* Store v0-v7. */

/* Store the VPU CSRs. */
addi    sp, sp, -( 4 * పోర్టు_మాట_కొలత )
csrr    t0, vstart
store_x t0, 0 * పోర్టు_మాట_కొలత( sp )
csrr    t0, vcsr
store_x t0, 1 * పోర్టు_మాట_కొలత( sp )
csrr    t0, vl
store_x t0, 2 * పోర్టు_మాట_కొలత( sp )
csrr    t0, vtype
store_x t0, 3 * పోర్టు_మాట_కొలత( sp )

/* Re-reserve the space for mstatus and epc. */
కూడు sp, sp, -( 2 * పోర్టు_మాట_కొలత )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
కూడు sp, sp, ( 2 * పోర్టు_మాట_కొలత )

/* Restore the VPU CSRs. */
ఎక్కించు_x  t0, 0  * పోర్టు_మాట_కొలత( sp )
csrw    vstart, t0
ఎక్కించు_x  t0, 1 * పోర్టు_మాట_కొలత( sp )
csrw    vcsr, t0
ఎక్కించు_x  t0, 2 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x  t1, 3 * పోర్టు_మాట_కొలత( sp )
vsetvl  x0, t0, t1 /* vlen and vtype can only be updated by using vset*vl* instructions. */
addi    sp, sp, ( 4 * పోర్టు_మాట_కొలత )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */

/* Restore the vector registers. */
vl8r.v  v0, (sp)    /* Restore v0-v7. */
కూడు     sp, sp, t0
vl8r.v  v8, (sp)    /* Restore v8-v15. */
కూడు     sp, sp, t0
vl8r.v  v16, (sp)   /* Restore v16-v23. */
కూడు     sp, sp, t0
vl8r.v  v24, (sp)   /* Restore v23-v31. */
కూడు     sp, sp, t0

/* Re-reserve the space for mstatus and epc. */
కూడు sp, sp, -( 2 * పోర్టు_మాట_కొలత )
    .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_CONTEXT_అంతర్గత
addi sp, sp, -పోర్టు_CONTEXT_కొలత
store_x x1,  2  * పోర్టు_మాట_కొలత( sp )
store_x x5,  3  * పోర్టు_మాట_కొలత( sp )
store_x x6,  4  * పోర్టు_మాట_కొలత( sp )
store_x x7,  5  * పోర్టు_మాట_కొలత( sp )
store_x x8,  6  * పోర్టు_మాట_కొలత( sp )
store_x x9,  7  * పోర్టు_మాట_కొలత( sp )
store_x x10, 8  * పోర్టు_మాట_కొలత( sp )
store_x x11, 9  * పోర్టు_మాట_కొలత( sp )
store_x x12, 10 * పోర్టు_మాట_కొలత( sp )
store_x x13, 11 * పోర్టు_మాట_కొలత( sp )
store_x x14, 12 * పోర్టు_మాట_కొలత( sp )
store_x x15, 13 * పోర్టు_మాట_కొలత( sp )
#నిర్వచితం_కాకపోతే __riscv_32e
    store_x x16, 14 * పోర్టు_మాట_కొలత( sp )
    store_x x17, 15 * పోర్టు_మాట_కొలత( sp )
    store_x x18, 16 * పోర్టు_మాట_కొలత( sp )
    store_x x19, 17 * పోర్టు_మాట_కొలత( sp )
    store_x x20, 18 * పోర్టు_మాట_కొలత( sp )
    store_x x21, 19 * పోర్టు_మాట_కొలత( sp )
    store_x x22, 20 * పోర్టు_మాట_కొలత( sp )
    store_x x23, 21 * పోర్టు_మాట_కొలత( sp )
    store_x x24, 22 * పోర్టు_మాట_కొలత( sp )
    store_x x25, 23 * పోర్టు_మాట_కొలత( sp )
    store_x x26, 24 * పోర్టు_మాట_కొలత( sp )
    store_x x27, 25 * పోర్టు_మాట_కొలత( sp )
    store_x x28, 26 * పోర్టు_మాట_కొలత( sp )
    store_x x29, 27 * పోర్టు_మాట_కొలత( sp )
    store_x x30, 28 * పోర్టు_మాట_కొలత( sp )
    store_x x31, 29 * పోర్టు_మాట_కొలత( sp )
#అయితే_ముగింపు /* ifndef __riscv_32e */

ఎక్కించు_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, పోర్టు_CRITICAL_NESTING_స్థానభ్రంశం * పోర్టు_మాట_కొలత( sp ) /* Store the critical nesting value to the stack. */

#ఒకవేళ( configENABLE_FPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_FS_స్థానభ్రంశం
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 1f /* If FPU status is not dirty, do not save FPU registers. */

    portcontexSAVE_FPU_CONTEXT
1:
#అయితే_ముగింపు

#ఒకవేళ( configENABLE_VPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_VS_స్థానభ్రంశం
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 2f /* If VPU status is not dirty, do not save VPU registers. */

    portcontexSAVE_VPU_CONTEXT
2:
#అయితే_ముగింపు

csrr t0, mstatus
store_x t0, 1 * పోర్టు_మాట_కొలత( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

#ఒకవేళ( configENABLE_FPU == 1 )
    /* Mark the FPU as clean, if it was dirty and we saved FPU registers. */
    srl t1, t0, MSTATUS_FS_స్థానభ్రంశం
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 3f

    li t1, ~MSTATUS_FS_ముసుగు
    and t0, t0, t1
    li t1, MSTATUS_FS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
3:
#అయితే_ముగింపు

#ఒకవేళ( configENABLE_VPU == 1 )
    /* Mark the VPU as clean, if it was dirty and we saved VPU registers. */
    srl t1, t0, MSTATUS_VS_స్థానభ్రంశం
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 4f

    li t1, ~MSTATUS_VS_ముసుగు
    and t0, t0, t1
    li t1, MSTATUS_VS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
4:
#అయితే_ముగింపు

ఎక్కించు_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

   .endm
/*-----------------------------------------------------------*/

   .macro portcontextSAVE_EXCEPTION_CONTEXT
portcontext_SAVE_CONTEXT_అంతర్గత
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
ఎక్కించు_x sp, x_ISRStack_శిఖరం /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_అంతరాయం_CONTEXT
portcontext_SAVE_CONTEXT_అంతర్గత
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
ఎక్కించు_x sp, x_ISRStack_శిఖరం /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontextRESTORE_CONTEXT
ఎక్కించు_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
ఎక్కించు_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
ఎక్కించు_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Restore mstatus register. It is important to use t3 (and not t0) here as t3
 * is not clobbered by portcontextRESTORE_VPU_CONTEXT and
 * portcontextRESTORE_FPU_CONTEXT. */
ఎక్కించు_x t3, 1 * పోర్టు_మాట_కొలత( sp )
csrw mstatus, t3

#ఒకవేళ( configENABLE_VPU == 1 )
    srl t1, t3, MSTATUS_VS_స్థానభ్రంశం
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 5f /* If VPU status is not dirty, do not restore VPU registers. */

    portcontextRESTORE_VPU_CONTEXT
5:
#అయితే_ముగింపు /* ifdef portasmSTORE_VPU_CONTEXT */

#ఒకవేళ( configENABLE_FPU == 1 )
    srl t1, t3, MSTATUS_FS_స్థానభ్రంశం
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 6f /* If FPU status is not dirty, do not restore FPU registers. */

    portcontextRESTORE_FPU_CONTEXT
6:
#అయితే_ముగింపు /* ifdef portasmSTORE_FPU_CONTEXT */

ఎక్కించు_x t0, పోర్టు_CRITICAL_NESTING_స్థానభ్రంశం * పోర్టు_మాట_కొలత( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
ఎక్కించు_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

ఎక్కించు_x x1,  2  * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x5,  3  * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x6,  4  * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x7,  5  * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x8,  6  * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x9,  7  * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x10, 8  * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x11, 9  * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x12, 10 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x13, 11 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x14, 12 * పోర్టు_మాట_కొలత( sp )
ఎక్కించు_x x15, 13 * పోర్టు_మాట_కొలత( sp )
#నిర్వచితం_కాకపోతే __riscv_32e
    ఎక్కించు_x x16, 14 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x17, 15 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x18, 16 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x19, 17 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x20, 18 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x21, 19 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x22, 20 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x23, 21 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x24, 22 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x25, 23 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x26, 24 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x27, 25 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x28, 26 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x29, 27 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x30, 28 * పోర్టు_మాట_కొలత( sp )
    ఎక్కించు_x x31, 29 * పోర్టు_మాట_కొలత( sp )
#అయితే_ముగింపు /* ifndef __riscv_32e */
addi sp, sp, పోర్టు_CONTEXT_కొలత

mret
   .endm
/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* PORTCONTEXT_H */
