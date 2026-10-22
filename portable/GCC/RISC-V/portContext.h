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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configENABLE_FPU
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configENABLE_FPU 0
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configENABLE_VPU
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configENABLE_VPU 0
#ਜੇ_ਅੰਤ

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
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਥ    14
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONTEXT_ਮਾਪ               ( 31 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਥ    30
#ਜੇ_ਅੰਤ

#ਜੇ ( configENABLE_FPU == 1 )
    /* Bit [14:13] in the mstatus encode the status of FPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_FS_ਨਕਾਬ                 0x6000
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_FS_INITIAL              0x2000
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_FS_CLEAN                0x4000
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_FS_DIRTY                0x6000
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_FS_ਵਿੱਥ               13

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __riscv_fdiv
        #ਜੇ __riscv_flen == 32
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_f                  flw
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ store_f                 fsw
        #ਜਾਂਜੇ __riscv_flen == 64
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_f                  fld
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ store_f                 fsd
        #ਨਹੀਂਤਾਂ
            #ਗਲਤੀ Assembler did not define __riscv_flen
        #ਜੇ_ਅੰਤ

        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPU_REG_ਮਾਪ                ( __riscv_flen / 8 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPU_REG_ਗਿਣਤੀ               33 /* 32 Floating point registers plus one CSR. */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPU_REG_ਵਿੱਥ( reg_ਸੂਚਕਾਂਕ )  ( ( 2 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ ) + ( reg_ਸੂਚਕਾਂਕ * ਪੋਰਟ_FPU_REG_ਮਾਪ ) )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPU_CONTEXT_ਮਾਪ            ( ਪੋਰਟ_FPU_REG_ਮਾਪ * ਪੋਰਟ_FPU_REG_ਗਿਣਤੀ )
    #ਨਹੀਂਤਾਂ
        #ਗਲਤੀ configENABLE_FPU must not be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 ਜੇ the hardware does not have FPU
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ ( configENABLE_VPU == 1 )
    /* Bit [10:9] in the mstatus encode the status of VPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_VS_ਨਕਾਬ                 0x600
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_VS_INITIAL              0x200
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_VS_CLEAN                0x400
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_VS_DIRTY                0x600
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_VS_ਵਿੱਥ               9

    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __riscv_vector
        #ਗਲਤੀ configENABLE_VPU must not be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 ਜੇ the hardware does not have VPU
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

.ਬਾਹਰੀ pxCurrentTCB
.ਬਾਹਰੀ x_ISRStack_ਸਿਖਰ
.ਬਾਹਰੀ xCriticalNesting
.ਬਾਹਰੀ pxCriticalNesting
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_FPU_CONTEXT
addi sp, sp, -( ਪੋਰਟ_FPU_CONTEXT_ਮਾਪ )
/* Store the FPU registers. */
store_f f0,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 0  )( sp )
store_f f1,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 1  )( sp )
store_f f2,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 2  )( sp )
store_f f3,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 3  )( sp )
store_f f4,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 4  )( sp )
store_f f5,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 5  )( sp )
store_f f6,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 6  )( sp )
store_f f7,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 7  )( sp )
store_f f8,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 8  )( sp )
store_f f9,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 9  )( sp )
store_f f10, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 10 )( sp )
store_f f11, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 11 )( sp )
store_f f12, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 12 )( sp )
store_f f13, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 13 )( sp )
store_f f14, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 14 )( sp )
store_f f15, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 15 )( sp )
store_f f16, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 16 )( sp )
store_f f17, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 17 )( sp )
store_f f18, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 18 )( sp )
store_f f19, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 19 )( sp )
store_f f20, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 20 )( sp )
store_f f21, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 21 )( sp )
store_f f22, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 22 )( sp )
store_f f23, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 23 )( sp )
store_f f24, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 24 )( sp )
store_f f25, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 25 )( sp )
store_f f26, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 26 )( sp )
store_f f27, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 27 )( sp )
store_f f28, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 28 )( sp )
store_f f29, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 29 )( sp )
store_f f30, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 30 )( sp )
store_f f31, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 31 )( sp )
csrr t0, fcsr
store_x t0,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 32 )( sp )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_FPU_CONTEXT
/* Restore the FPU registers. */
ਲੱਦੋ_f f0,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 0  )( sp )
ਲੱਦੋ_f f1,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 1  )( sp )
ਲੱਦੋ_f f2,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 2  )( sp )
ਲੱਦੋ_f f3,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 3  )( sp )
ਲੱਦੋ_f f4,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 4  )( sp )
ਲੱਦੋ_f f5,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 5  )( sp )
ਲੱਦੋ_f f6,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 6  )( sp )
ਲੱਦੋ_f f7,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 7  )( sp )
ਲੱਦੋ_f f8,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 8  )( sp )
ਲੱਦੋ_f f9,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 9  )( sp )
ਲੱਦੋ_f f10, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 10 )( sp )
ਲੱਦੋ_f f11, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 11 )( sp )
ਲੱਦੋ_f f12, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 12 )( sp )
ਲੱਦੋ_f f13, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 13 )( sp )
ਲੱਦੋ_f f14, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 14 )( sp )
ਲੱਦੋ_f f15, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 15 )( sp )
ਲੱਦੋ_f f16, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 16 )( sp )
ਲੱਦੋ_f f17, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 17 )( sp )
ਲੱਦੋ_f f18, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 18 )( sp )
ਲੱਦੋ_f f19, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 19 )( sp )
ਲੱਦੋ_f f20, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 20 )( sp )
ਲੱਦੋ_f f21, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 21 )( sp )
ਲੱਦੋ_f f22, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 22 )( sp )
ਲੱਦੋ_f f23, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 23 )( sp )
ਲੱਦੋ_f f24, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 24 )( sp )
ਲੱਦੋ_f f25, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 25 )( sp )
ਲੱਦੋ_f f26, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 26 )( sp )
ਲੱਦੋ_f f27, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 27 )( sp )
ਲੱਦੋ_f f28, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 28 )( sp )
ਲੱਦੋ_f f29, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 29 )( sp )
ਲੱਦੋ_f f30, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 30 )( sp )
ਲੱਦੋ_f f31, ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 31 )( sp )
ਲੱਦੋ_x t0,  ਪੋਰਟ_FPU_REG_ਵਿੱਥ( 32 )( sp )
csrw fcsr, t0
addi sp, sp, ( ਪੋਰਟ_FPU_CONTEXT_ਮਾਪ )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
ਜੋੜੋ sp, sp, ( 2 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */
neg  t0, t0

/* Store the vector registers in group of 8. */
ਜੋੜੋ     sp, sp, t0
vs8r.v  v24, (sp)   /* Store v24-v31. */
ਜੋੜੋ     sp, sp, t0
vs8r.v  v16, (sp)   /* Store v16-v23. */
ਜੋੜੋ     sp, sp, t0
vs8r.v  v8, (sp)    /* Store v8-v15. */
ਜੋੜੋ     sp, sp, t0
vs8r.v  v0, (sp)    /* Store v0-v7. */

/* Store the VPU CSRs. */
addi    sp, sp, -( 4 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ )
csrr    t0, vstart
store_x t0, 0 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
csrr    t0, vcsr
store_x t0, 1 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
csrr    t0, vl
store_x t0, 2 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
csrr    t0, vtype
store_x t0, 3 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )

/* Re-reserve the space for mstatus and epc. */
ਜੋੜੋ sp, sp, -( 2 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
ਜੋੜੋ sp, sp, ( 2 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ )

/* Restore the VPU CSRs. */
ਲੱਦੋ_x  t0, 0  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
csrw    vstart, t0
ਲੱਦੋ_x  t0, 1 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
csrw    vcsr, t0
ਲੱਦੋ_x  t0, 2 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x  t1, 3 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
vsetvl  x0, t0, t1 /* vlen and vtype can only be updated by using vset*vl* instructions. */
addi    sp, sp, ( 4 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */

/* Restore the vector registers. */
vl8r.v  v0, (sp)    /* Restore v0-v7. */
ਜੋੜੋ     sp, sp, t0
vl8r.v  v8, (sp)    /* Restore v8-v15. */
ਜੋੜੋ     sp, sp, t0
vl8r.v  v16, (sp)   /* Restore v16-v23. */
ਜੋੜੋ     sp, sp, t0
vl8r.v  v24, (sp)   /* Restore v23-v31. */
ਜੋੜੋ     sp, sp, t0

/* Re-reserve the space for mstatus and epc. */
ਜੋੜੋ sp, sp, -( 2 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ )
    .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_CONTEXT_ਅੰਦਰੂਨੀ
addi sp, sp, -ਪੋਰਟ_CONTEXT_ਮਾਪ
store_x x1,  2  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x5,  3  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x6,  4  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x7,  5  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x8,  6  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x9,  7  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x10, 8  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x11, 9  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x12, 10 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x13, 11 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x14, 12 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
store_x x15, 13 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __riscv_32e
    store_x x16, 14 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x17, 15 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x18, 16 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x19, 17 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x20, 18 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x21, 19 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x22, 20 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x23, 21 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x24, 22 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x25, 23 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x26, 24 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x27, 25 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x28, 26 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x29, 27 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x30, 28 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    store_x x31, 29 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
#ਜੇ_ਅੰਤ /* ifndef __riscv_32e */

ਲੱਦੋ_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਥ * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp ) /* Store the critical nesting value to the stack. */

#ਜੇ( configENABLE_FPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_FS_ਵਿੱਥ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 1f /* If FPU status is not dirty, do not save FPU registers. */

    portcontexSAVE_FPU_CONTEXT
1:
#ਜੇ_ਅੰਤ

#ਜੇ( configENABLE_VPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_VS_ਵਿੱਥ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 2f /* If VPU status is not dirty, do not save VPU registers. */

    portcontexSAVE_VPU_CONTEXT
2:
#ਜੇ_ਅੰਤ

csrr t0, mstatus
store_x t0, 1 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

#ਜੇ( configENABLE_FPU == 1 )
    /* Mark the FPU as clean, if it was dirty and we saved FPU registers. */
    srl t1, t0, MSTATUS_FS_ਵਿੱਥ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 3f

    li t1, ~MSTATUS_FS_ਨਕਾਬ
    and t0, t0, t1
    li t1, MSTATUS_FS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
3:
#ਜੇ_ਅੰਤ

#ਜੇ( configENABLE_VPU == 1 )
    /* Mark the VPU as clean, if it was dirty and we saved VPU registers. */
    srl t1, t0, MSTATUS_VS_ਵਿੱਥ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 4f

    li t1, ~MSTATUS_VS_ਨਕਾਬ
    and t0, t0, t1
    li t1, MSTATUS_VS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
4:
#ਜੇ_ਅੰਤ

ਲੱਦੋ_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

   .endm
/*-----------------------------------------------------------*/

   .macro portcontextSAVE_EXCEPTION_CONTEXT
portcontext_SAVE_CONTEXT_ਅੰਦਰੂਨੀ
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
ਲੱਦੋ_x sp, x_ISRStack_ਸਿਖਰ /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_ਰੁਕਾਵਟ_CONTEXT
portcontext_SAVE_CONTEXT_ਅੰਦਰੂਨੀ
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
ਲੱਦੋ_x sp, x_ISRStack_ਸਿਖਰ /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontextRESTORE_CONTEXT
ਲੱਦੋ_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
ਲੱਦੋ_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
ਲੱਦੋ_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Restore mstatus register. It is important to use t3 (and not t0) here as t3
 * is not clobbered by portcontextRESTORE_VPU_CONTEXT and
 * portcontextRESTORE_FPU_CONTEXT. */
ਲੱਦੋ_x t3, 1 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
csrw mstatus, t3

#ਜੇ( configENABLE_VPU == 1 )
    srl t1, t3, MSTATUS_VS_ਵਿੱਥ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 5f /* If VPU status is not dirty, do not restore VPU registers. */

    portcontextRESTORE_VPU_CONTEXT
5:
#ਜੇ_ਅੰਤ /* ifdef portasmSTORE_VPU_CONTEXT */

#ਜੇ( configENABLE_FPU == 1 )
    srl t1, t3, MSTATUS_FS_ਵਿੱਥ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 6f /* If FPU status is not dirty, do not restore FPU registers. */

    portcontextRESTORE_FPU_CONTEXT
6:
#ਜੇ_ਅੰਤ /* ifdef portasmSTORE_FPU_CONTEXT */

ਲੱਦੋ_x t0, ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਥ * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
ਲੱਦੋ_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

ਲੱਦੋ_x x1,  2  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x5,  3  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x6,  4  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x7,  5  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x8,  6  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x9,  7  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x10, 8  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x11, 9  * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x12, 10 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x13, 11 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x14, 12 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
ਲੱਦੋ_x x15, 13 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __riscv_32e
    ਲੱਦੋ_x x16, 14 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x17, 15 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x18, 16 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x19, 17 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x20, 18 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x21, 19 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x22, 20 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x23, 21 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x24, 22 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x25, 23 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x26, 24 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x27, 25 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x28, 26 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x29, 27 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x30, 28 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
    ਲੱਦੋ_x x31, 29 * ਪੋਰਟ_ਸ਼ਬਦ_ਮਾਪ( sp )
#ਜੇ_ਅੰਤ /* ifndef __riscv_32e */
addi sp, sp, ਪੋਰਟ_CONTEXT_ਮਾਪ

mret
   .endm
/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* PORTCONTEXT_H */
