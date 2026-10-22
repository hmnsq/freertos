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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTCONTEXT_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTCONTEXT_H

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configENABLE_FPU
    #ವ್ಯಾಖ್ಯಾನಿಸು configENABLE_FPU 0
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configENABLE_VPU
    #ವ್ಯಾಖ್ಯಾನಿಸು configENABLE_VPU 0
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ __riscv_xlen == 64
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ    8
    #ವ್ಯಾಖ್ಯಾನಿಸು store_x          sd
    #ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_x           ld
#ಅಥವಾಆದರೆ __riscv_xlen == 32
    #ವ್ಯಾಖ್ಯಾನಿಸು store_x          sw
    #ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_x           lw
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ    4
#ಇಲ್ಲದಿದ್ದರೆ
    #ದೋಷ Assembler did not define __riscv_xlen
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "freertos_risc_v_chip_specific_extensions.h"

/* Only the standard core registers are stored by default.  Any additional
 * registers must be saved by the portasmSAVE_ADDITIONAL_REGISTERS and
 * portasmRESTORE_ADDITIONAL_REGISTERS macros - which can be defined in a chip
 * specific version of freertos_risc_v_chip_specific_extensions.h.  See the
 * notes at the top of portASM.S file. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __riscv_32e
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONTEXT_ಗಾತ್ರ               ( 15 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CRITICAL_NESTING_ಸ್ಥಾನಾಂತರ    14
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONTEXT_ಗಾತ್ರ               ( 31 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CRITICAL_NESTING_ಸ್ಥಾನಾಂತರ    30
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ ( configENABLE_FPU == 1 )
    /* Bit [14:13] in the mstatus encode the status of FPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು MSTATUS_FS_ಮುಖವಾಡ                 0x6000
    #ವ್ಯಾಖ್ಯಾನಿಸು MSTATUS_FS_INITIAL              0x2000
    #ವ್ಯಾಖ್ಯಾನಿಸು MSTATUS_FS_CLEAN                0x4000
    #ವ್ಯಾಖ್ಯಾನಿಸು MSTATUS_FS_DIRTY                0x6000
    #ವ್ಯಾಖ್ಯಾನಿಸು MSTATUS_FS_ಸ್ಥಾನಾಂತರ               13

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __riscv_fdiv
        #ಆದರೆ __riscv_flen == 32
            #ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_f                  flw
            #ವ್ಯಾಖ್ಯಾನಿಸು store_f                 fsw
        #ಅಥವಾಆದರೆ __riscv_flen == 64
            #ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_f                  fld
            #ವ್ಯಾಖ್ಯಾನಿಸು store_f                 fsd
        #ಇಲ್ಲದಿದ್ದರೆ
            #ದೋಷ Assembler did not define __riscv_flen
        #ಆದರೆ_ಅಂತ್ಯ

        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPU_REG_ಗಾತ್ರ                ( __riscv_flen / 8 )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPU_REG_ಎಣಿಕೆ               33 /* 32 Floating point registers plus one CSR. */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( reg_ಸೂಚ್ಯಂಕ )  ( ( 2 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ ) + ( reg_ಸೂಚ್ಯಂಕ * ಪೋರ್ಟ್_FPU_REG_ಗಾತ್ರ ) )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPU_CONTEXT_ಗಾತ್ರ            ( ಪೋರ್ಟ್_FPU_REG_ಗಾತ್ರ * ಪೋರ್ಟ್_FPU_REG_ಎಣಿಕೆ )
    #ಇಲ್ಲದಿದ್ದರೆ
        #ದೋಷ configENABLE_FPU must not be ಗಣ ಗಮ್ಯ 1 ಆದರೆ the hardware does not have FPU
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ ( configENABLE_VPU == 1 )
    /* Bit [10:9] in the mstatus encode the status of VPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು MSTATUS_VS_ಮುಖವಾಡ                 0x600
    #ವ್ಯಾಖ್ಯಾನಿಸು MSTATUS_VS_INITIAL              0x200
    #ವ್ಯಾಖ್ಯಾನಿಸು MSTATUS_VS_CLEAN                0x400
    #ವ್ಯಾಖ್ಯಾನಿಸು MSTATUS_VS_DIRTY                0x600
    #ವ್ಯಾಖ್ಯಾನಿಸು MSTATUS_VS_ಸ್ಥಾನಾಂತರ               9

    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __riscv_vector
        #ದೋಷ configENABLE_VPU must not be ಗಣ ಗಮ್ಯ 1 ಆದರೆ the hardware does not have VPU
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

.ಬಾಹ್ಯ pxCurrentTCB
.ಬಾಹ್ಯ x_ISRStack_ತುದಿ
.ಬಾಹ್ಯ xCriticalNesting
.ಬಾಹ್ಯ pxCriticalNesting
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_FPU_CONTEXT
addi sp, sp, -( ಪೋರ್ಟ್_FPU_CONTEXT_ಗಾತ್ರ )
/* Store the FPU registers. */
store_f f0,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 0  )( sp )
store_f f1,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 1  )( sp )
store_f f2,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 2  )( sp )
store_f f3,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 3  )( sp )
store_f f4,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 4  )( sp )
store_f f5,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 5  )( sp )
store_f f6,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 6  )( sp )
store_f f7,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 7  )( sp )
store_f f8,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 8  )( sp )
store_f f9,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 9  )( sp )
store_f f10, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 10 )( sp )
store_f f11, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 11 )( sp )
store_f f12, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 12 )( sp )
store_f f13, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 13 )( sp )
store_f f14, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 14 )( sp )
store_f f15, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 15 )( sp )
store_f f16, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 16 )( sp )
store_f f17, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 17 )( sp )
store_f f18, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 18 )( sp )
store_f f19, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 19 )( sp )
store_f f20, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 20 )( sp )
store_f f21, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 21 )( sp )
store_f f22, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 22 )( sp )
store_f f23, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 23 )( sp )
store_f f24, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 24 )( sp )
store_f f25, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 25 )( sp )
store_f f26, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 26 )( sp )
store_f f27, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 27 )( sp )
store_f f28, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 28 )( sp )
store_f f29, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 29 )( sp )
store_f f30, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 30 )( sp )
store_f f31, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 31 )( sp )
csrr t0, fcsr
store_x t0,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 32 )( sp )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_FPU_CONTEXT
/* Restore the FPU registers. */
ತುಂಬು_f f0,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 0  )( sp )
ತುಂಬು_f f1,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 1  )( sp )
ತುಂಬು_f f2,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 2  )( sp )
ತುಂಬು_f f3,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 3  )( sp )
ತುಂಬು_f f4,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 4  )( sp )
ತುಂಬು_f f5,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 5  )( sp )
ತುಂಬು_f f6,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 6  )( sp )
ತುಂಬು_f f7,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 7  )( sp )
ತುಂಬು_f f8,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 8  )( sp )
ತುಂಬು_f f9,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 9  )( sp )
ತುಂಬು_f f10, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 10 )( sp )
ತುಂಬು_f f11, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 11 )( sp )
ತುಂಬು_f f12, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 12 )( sp )
ತುಂಬು_f f13, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 13 )( sp )
ತುಂಬು_f f14, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 14 )( sp )
ತುಂಬು_f f15, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 15 )( sp )
ತುಂಬು_f f16, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 16 )( sp )
ತುಂಬು_f f17, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 17 )( sp )
ತುಂಬು_f f18, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 18 )( sp )
ತುಂಬು_f f19, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 19 )( sp )
ತುಂಬು_f f20, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 20 )( sp )
ತುಂಬು_f f21, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 21 )( sp )
ತುಂಬು_f f22, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 22 )( sp )
ತುಂಬು_f f23, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 23 )( sp )
ತುಂಬು_f f24, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 24 )( sp )
ತುಂಬು_f f25, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 25 )( sp )
ತುಂಬು_f f26, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 26 )( sp )
ತುಂಬು_f f27, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 27 )( sp )
ತುಂಬು_f f28, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 28 )( sp )
ತುಂಬು_f f29, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 29 )( sp )
ತುಂಬು_f f30, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 30 )( sp )
ತುಂಬು_f f31, ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 31 )( sp )
ತುಂಬು_x t0,  ಪೋರ್ಟ್_FPU_REG_ಸ್ಥಾನಾಂತರ( 32 )( sp )
csrw fcsr, t0
addi sp, sp, ( ಪೋರ್ಟ್_FPU_CONTEXT_ಗಾತ್ರ )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
ಕೂಡಿಸು sp, sp, ( 2 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */
neg  t0, t0

/* Store the vector registers in group of 8. */
ಕೂಡಿಸು     sp, sp, t0
vs8r.v  v24, (sp)   /* Store v24-v31. */
ಕೂಡಿಸು     sp, sp, t0
vs8r.v  v16, (sp)   /* Store v16-v23. */
ಕೂಡಿಸು     sp, sp, t0
vs8r.v  v8, (sp)    /* Store v8-v15. */
ಕೂಡಿಸು     sp, sp, t0
vs8r.v  v0, (sp)    /* Store v0-v7. */

/* Store the VPU CSRs. */
addi    sp, sp, -( 4 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ )
csrr    t0, vstart
store_x t0, 0 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
csrr    t0, vcsr
store_x t0, 1 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
csrr    t0, vl
store_x t0, 2 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
csrr    t0, vtype
store_x t0, 3 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )

/* Re-reserve the space for mstatus and epc. */
ಕೂಡಿಸು sp, sp, -( 2 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
ಕೂಡಿಸು sp, sp, ( 2 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ )

/* Restore the VPU CSRs. */
ತುಂಬು_x  t0, 0  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
csrw    vstart, t0
ತುಂಬು_x  t0, 1 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
csrw    vcsr, t0
ತುಂಬು_x  t0, 2 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x  t1, 3 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
vsetvl  x0, t0, t1 /* vlen and vtype can only be updated by using vset*vl* instructions. */
addi    sp, sp, ( 4 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */

/* Restore the vector registers. */
vl8r.v  v0, (sp)    /* Restore v0-v7. */
ಕೂಡಿಸು     sp, sp, t0
vl8r.v  v8, (sp)    /* Restore v8-v15. */
ಕೂಡಿಸು     sp, sp, t0
vl8r.v  v16, (sp)   /* Restore v16-v23. */
ಕೂಡಿಸು     sp, sp, t0
vl8r.v  v24, (sp)   /* Restore v23-v31. */
ಕೂಡಿಸು     sp, sp, t0

/* Re-reserve the space for mstatus and epc. */
ಕೂಡಿಸು sp, sp, -( 2 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ )
    .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_CONTEXT_ಆಂತರಿಕ
addi sp, sp, -ಪೋರ್ಟ್_CONTEXT_ಗಾತ್ರ
store_x x1,  2  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x5,  3  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x6,  4  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x7,  5  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x8,  6  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x9,  7  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x10, 8  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x11, 9  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x12, 10 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x13, 11 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x14, 12 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
store_x x15, 13 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __riscv_32e
    store_x x16, 14 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x17, 15 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x18, 16 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x19, 17 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x20, 18 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x21, 19 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x22, 20 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x23, 21 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x24, 22 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x25, 23 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x26, 24 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x27, 25 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x28, 26 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x29, 27 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x30, 28 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    store_x x31, 29 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
#ಆದರೆ_ಅಂತ್ಯ /* ifndef __riscv_32e */

ತುಂಬು_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, ಪೋರ್ಟ್_CRITICAL_NESTING_ಸ್ಥಾನಾಂತರ * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp ) /* Store the critical nesting value to the stack. */

#ಆದರೆ( configENABLE_FPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_FS_ಸ್ಥಾನಾಂತರ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 1f /* If FPU status is not dirty, do not save FPU registers. */

    portcontexSAVE_FPU_CONTEXT
1:
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ( configENABLE_VPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_VS_ಸ್ಥಾನಾಂತರ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 2f /* If VPU status is not dirty, do not save VPU registers. */

    portcontexSAVE_VPU_CONTEXT
2:
#ಆದರೆ_ಅಂತ್ಯ

csrr t0, mstatus
store_x t0, 1 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

#ಆದರೆ( configENABLE_FPU == 1 )
    /* Mark the FPU as clean, if it was dirty and we saved FPU registers. */
    srl t1, t0, MSTATUS_FS_ಸ್ಥಾನಾಂತರ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 3f

    li t1, ~MSTATUS_FS_ಮುಖವಾಡ
    and t0, t0, t1
    li t1, MSTATUS_FS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
3:
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ( configENABLE_VPU == 1 )
    /* Mark the VPU as clean, if it was dirty and we saved VPU registers. */
    srl t1, t0, MSTATUS_VS_ಸ್ಥಾನಾಂತರ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 4f

    li t1, ~MSTATUS_VS_ಮುಖವಾಡ
    and t0, t0, t1
    li t1, MSTATUS_VS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
4:
#ಆದರೆ_ಅಂತ್ಯ

ತುಂಬು_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

   .endm
/*-----------------------------------------------------------*/

   .macro portcontextSAVE_EXCEPTION_CONTEXT
portcontext_SAVE_CONTEXT_ಆಂತರಿಕ
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
ತುಂಬು_x sp, x_ISRStack_ತುದಿ /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontext_SAVE_ಅಡಚಣೆ_CONTEXT
portcontext_SAVE_CONTEXT_ಆಂತರಿಕ
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
ತುಂಬು_x sp, x_ISRStack_ತುದಿ /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontextRESTORE_CONTEXT
ತುಂಬು_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
ತುಂಬು_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
ತುಂಬು_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Restore mstatus register. It is important to use t3 (and not t0) here as t3
 * is not clobbered by portcontextRESTORE_VPU_CONTEXT and
 * portcontextRESTORE_FPU_CONTEXT. */
ತುಂಬು_x t3, 1 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
csrw mstatus, t3

#ಆದರೆ( configENABLE_VPU == 1 )
    srl t1, t3, MSTATUS_VS_ಸ್ಥಾನಾಂತರ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 5f /* If VPU status is not dirty, do not restore VPU registers. */

    portcontextRESTORE_VPU_CONTEXT
5:
#ಆದರೆ_ಅಂತ್ಯ /* ifdef portasmSTORE_VPU_CONTEXT */

#ಆದರೆ( configENABLE_FPU == 1 )
    srl t1, t3, MSTATUS_FS_ಸ್ಥಾನಾಂತರ
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 6f /* If FPU status is not dirty, do not restore FPU registers. */

    portcontextRESTORE_FPU_CONTEXT
6:
#ಆದರೆ_ಅಂತ್ಯ /* ifdef portasmSTORE_FPU_CONTEXT */

ತುಂಬು_x t0, ಪೋರ್ಟ್_CRITICAL_NESTING_ಸ್ಥಾನಾಂತರ * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
ತುಂಬು_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

ತುಂಬು_x x1,  2  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x5,  3  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x6,  4  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x7,  5  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x8,  6  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x9,  7  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x10, 8  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x11, 9  * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x12, 10 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x13, 11 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x14, 12 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
ತುಂಬು_x x15, 13 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __riscv_32e
    ತುಂಬು_x x16, 14 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x17, 15 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x18, 16 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x19, 17 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x20, 18 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x21, 19 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x22, 20 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x23, 21 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x24, 22 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x25, 23 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x26, 24 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x27, 25 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x28, 26 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x29, 27 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x30, 28 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
    ತುಂಬು_x x31, 29 * ಪೋರ್ಟ್_ಶಬ್ದ_ಗಾತ್ರ( sp )
#ಆದರೆ_ಅಂತ್ಯ /* ifndef __riscv_32e */
addi sp, sp, ಪೋರ್ಟ್_CONTEXT_ಗಾತ್ರ

mret
   .endm
/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* PORTCONTEXT_H */
