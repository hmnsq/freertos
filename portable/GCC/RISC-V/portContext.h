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

#अगर_अघोषित configENABLE_FPU
    #घोषणा configENABLE_FPU 0
#पूर्ण_अगर

#अगर_अघोषित configENABLE_VPU
    #घोषणा configENABLE_VPU 0
#पूर्ण_अगर

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
    #घोषणा portCRITICAL_NESTING_OFFSET    14
#अन्यथा
    #घोषणा port_CONTEXT_आकार               ( 31 * port_WORD_आकार )
    #घोषणा portCRITICAL_NESTING_OFFSET    30
#पूर्ण_अगर

#अगर ( configENABLE_FPU == 1 )
    /* Bit [14:13] in the mstatus encode the status of FPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #घोषणा MSTATUS_FS_MASK                 0x6000
    #घोषणा MSTATUS_FS_INITIAL              0x2000
    #घोषणा MSTATUS_FS_CLEAN                0x4000
    #घोषणा MSTATUS_FS_DIRTY                0x6000
    #घोषणा MSTATUS_FS_OFFSET               13

    #अगर_घोषित __riscv_fdiv
        #अगर __riscv_flen == 32
            #घोषणा load_f                  flw
            #घोषणा store_f                 fsw
        #या_अगर __riscv_flen == 64
            #घोषणा load_f                  fld
            #घोषणा store_f                 fsd
        #अन्यथा
            #त्रुटि Assembler did not define __riscv_flen
        #पूर्ण_अगर

        #घोषणा port_FPU_REG_आकार                ( __riscv_flen / 8 )
        #घोषणा port_FPU_REG_गिनती               33 /* 32 Floating point registers plus one CSR. */
        #घोषणा portFPU_REG_OFFSET( reg_सूचकांक )  ( ( 2 * port_WORD_आकार ) + ( reg_सूचकांक * port_FPU_REG_आकार ) )
        #घोषणा port_FPU_CONTEXT_आकार            ( port_FPU_REG_आकार * port_FPU_REG_गिनती )
    #अन्यथा
        #त्रुटि configENABLE_FPU must not be set to 1 अगर the hardware does not have FPU
    #पूर्ण_अगर
#पूर्ण_अगर

#अगर ( configENABLE_VPU == 1 )
    /* Bit [10:9] in the mstatus encode the status of VPU state which is one of
     * the following values:
     * 1. Value: 0, Meaning: Off.
     * 2. Value: 1, Meaning: Initial.
     * 3. Value: 2, Meaning: Clean.
     * 4. Value: 3, Meaning: Dirty.
     */
    #घोषणा MSTATUS_VS_MASK                 0x600
    #घोषणा MSTATUS_VS_INITIAL              0x200
    #घोषणा MSTATUS_VS_CLEAN                0x400
    #घोषणा MSTATUS_VS_DIRTY                0x600
    #घोषणा MSTATUS_VS_OFFSET               9

    #अगर_अघोषित __riscv_vector
        #त्रुटि configENABLE_VPU must not be set to 1 अगर the hardware does not have VPU
    #पूर्ण_अगर
#पूर्ण_अगर
/*-----------------------------------------------------------*/

.बाह्य pxCurrentTCB
.बाह्य x_ISRStack_शीर्ष
.बाह्य xCriticalNesting
.बाह्य pxCriticalNesting
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_FPU_CONTEXT
addi sp, sp, -( port_FPU_CONTEXT_आकार )
/* Store the FPU registers. */
store_f f0,  portFPU_REG_OFFSET( 0  )( sp )
store_f f1,  portFPU_REG_OFFSET( 1  )( sp )
store_f f2,  portFPU_REG_OFFSET( 2  )( sp )
store_f f3,  portFPU_REG_OFFSET( 3  )( sp )
store_f f4,  portFPU_REG_OFFSET( 4  )( sp )
store_f f5,  portFPU_REG_OFFSET( 5  )( sp )
store_f f6,  portFPU_REG_OFFSET( 6  )( sp )
store_f f7,  portFPU_REG_OFFSET( 7  )( sp )
store_f f8,  portFPU_REG_OFFSET( 8  )( sp )
store_f f9,  portFPU_REG_OFFSET( 9  )( sp )
store_f f10, portFPU_REG_OFFSET( 10 )( sp )
store_f f11, portFPU_REG_OFFSET( 11 )( sp )
store_f f12, portFPU_REG_OFFSET( 12 )( sp )
store_f f13, portFPU_REG_OFFSET( 13 )( sp )
store_f f14, portFPU_REG_OFFSET( 14 )( sp )
store_f f15, portFPU_REG_OFFSET( 15 )( sp )
store_f f16, portFPU_REG_OFFSET( 16 )( sp )
store_f f17, portFPU_REG_OFFSET( 17 )( sp )
store_f f18, portFPU_REG_OFFSET( 18 )( sp )
store_f f19, portFPU_REG_OFFSET( 19 )( sp )
store_f f20, portFPU_REG_OFFSET( 20 )( sp )
store_f f21, portFPU_REG_OFFSET( 21 )( sp )
store_f f22, portFPU_REG_OFFSET( 22 )( sp )
store_f f23, portFPU_REG_OFFSET( 23 )( sp )
store_f f24, portFPU_REG_OFFSET( 24 )( sp )
store_f f25, portFPU_REG_OFFSET( 25 )( sp )
store_f f26, portFPU_REG_OFFSET( 26 )( sp )
store_f f27, portFPU_REG_OFFSET( 27 )( sp )
store_f f28, portFPU_REG_OFFSET( 28 )( sp )
store_f f29, portFPU_REG_OFFSET( 29 )( sp )
store_f f30, portFPU_REG_OFFSET( 30 )( sp )
store_f f31, portFPU_REG_OFFSET( 31 )( sp )
csrr t0, fcsr
store_x t0,  portFPU_REG_OFFSET( 32 )( sp )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_FPU_CONTEXT
/* Restore the FPU registers. */
load_f f0,  portFPU_REG_OFFSET( 0  )( sp )
load_f f1,  portFPU_REG_OFFSET( 1  )( sp )
load_f f2,  portFPU_REG_OFFSET( 2  )( sp )
load_f f3,  portFPU_REG_OFFSET( 3  )( sp )
load_f f4,  portFPU_REG_OFFSET( 4  )( sp )
load_f f5,  portFPU_REG_OFFSET( 5  )( sp )
load_f f6,  portFPU_REG_OFFSET( 6  )( sp )
load_f f7,  portFPU_REG_OFFSET( 7  )( sp )
load_f f8,  portFPU_REG_OFFSET( 8  )( sp )
load_f f9,  portFPU_REG_OFFSET( 9  )( sp )
load_f f10, portFPU_REG_OFFSET( 10 )( sp )
load_f f11, portFPU_REG_OFFSET( 11 )( sp )
load_f f12, portFPU_REG_OFFSET( 12 )( sp )
load_f f13, portFPU_REG_OFFSET( 13 )( sp )
load_f f14, portFPU_REG_OFFSET( 14 )( sp )
load_f f15, portFPU_REG_OFFSET( 15 )( sp )
load_f f16, portFPU_REG_OFFSET( 16 )( sp )
load_f f17, portFPU_REG_OFFSET( 17 )( sp )
load_f f18, portFPU_REG_OFFSET( 18 )( sp )
load_f f19, portFPU_REG_OFFSET( 19 )( sp )
load_f f20, portFPU_REG_OFFSET( 20 )( sp )
load_f f21, portFPU_REG_OFFSET( 21 )( sp )
load_f f22, portFPU_REG_OFFSET( 22 )( sp )
load_f f23, portFPU_REG_OFFSET( 23 )( sp )
load_f f24, portFPU_REG_OFFSET( 24 )( sp )
load_f f25, portFPU_REG_OFFSET( 25 )( sp )
load_f f26, portFPU_REG_OFFSET( 26 )( sp )
load_f f27, portFPU_REG_OFFSET( 27 )( sp )
load_f f28, portFPU_REG_OFFSET( 28 )( sp )
load_f f29, portFPU_REG_OFFSET( 29 )( sp )
load_f f30, portFPU_REG_OFFSET( 30 )( sp )
load_f f31, portFPU_REG_OFFSET( 31 )( sp )
load_x t0,  portFPU_REG_OFFSET( 32 )( sp )
csrw fcsr, t0
addi sp, sp, ( port_FPU_CONTEXT_आकार )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontexSAVE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
add sp, sp, ( 2 * port_WORD_आकार )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */
neg  t0, t0

/* Store the vector registers in group of 8. */
add     sp, sp, t0
vs8r.v  v24, (sp)   /* Store v24-v31. */
add     sp, sp, t0
vs8r.v  v16, (sp)   /* Store v16-v23. */
add     sp, sp, t0
vs8r.v  v8, (sp)    /* Store v8-v15. */
add     sp, sp, t0
vs8r.v  v0, (sp)    /* Store v0-v7. */

/* Store the VPU CSRs. */
addi    sp, sp, -( 4 * port_WORD_आकार )
csrr    t0, vstart
store_x t0, 0 * port_WORD_आकार( sp )
csrr    t0, vcsr
store_x t0, 1 * port_WORD_आकार( sp )
csrr    t0, vl
store_x t0, 2 * port_WORD_आकार( sp )
csrr    t0, vtype
store_x t0, 3 * port_WORD_आकार( sp )

/* Re-reserve the space for mstatus and epc. */
add sp, sp, -( 2 * port_WORD_आकार )
    .endm
/*-----------------------------------------------------------*/

    .macro portcontextRESTORE_VPU_CONTEXT
/* Un-reserve the space reserved for mstatus and epc. */
add sp, sp, ( 2 * port_WORD_आकार )

/* Restore the VPU CSRs. */
load_x  t0, 0  * port_WORD_आकार( sp )
csrw    vstart, t0
load_x  t0, 1 * port_WORD_आकार( sp )
csrw    vcsr, t0
load_x  t0, 2 * port_WORD_आकार( sp )
load_x  t1, 3 * port_WORD_आकार( sp )
vsetvl  x0, t0, t1 /* vlen and vtype can only be updated by using vset*vl* instructions. */
addi    sp, sp, ( 4 * port_WORD_आकार )

csrr t0, vlenb /* t0 = vlenb. vlenb is the length of each vector register in bytes. */
slli t0, t0, 3 /* t0 = vlenb * 8. t0 now contains the space required to store 8 vector registers. */

/* Restore the vector registers. */
vl8r.v  v0, (sp)    /* Restore v0-v7. */
add     sp, sp, t0
vl8r.v  v8, (sp)    /* Restore v8-v15. */
add     sp, sp, t0
vl8r.v  v16, (sp)   /* Restore v16-v23. */
add     sp, sp, t0
vl8r.v  v24, (sp)   /* Restore v23-v31. */
add     sp, sp, t0

/* Re-reserve the space for mstatus and epc. */
add sp, sp, -( 2 * port_WORD_आकार )
    .endm
/*-----------------------------------------------------------*/

   .macro portcontextSAVE_CONTEXT_INTERNAL
addi sp, sp, -port_CONTEXT_आकार
store_x x1,  2  * port_WORD_आकार( sp )
store_x x5,  3  * port_WORD_आकार( sp )
store_x x6,  4  * port_WORD_आकार( sp )
store_x x7,  5  * port_WORD_आकार( sp )
store_x x8,  6  * port_WORD_आकार( sp )
store_x x9,  7  * port_WORD_आकार( sp )
store_x x10, 8  * port_WORD_आकार( sp )
store_x x11, 9  * port_WORD_आकार( sp )
store_x x12, 10 * port_WORD_आकार( sp )
store_x x13, 11 * port_WORD_आकार( sp )
store_x x14, 12 * port_WORD_आकार( sp )
store_x x15, 13 * port_WORD_आकार( sp )
#अगर_अघोषित __riscv_32e
    store_x x16, 14 * port_WORD_आकार( sp )
    store_x x17, 15 * port_WORD_आकार( sp )
    store_x x18, 16 * port_WORD_आकार( sp )
    store_x x19, 17 * port_WORD_आकार( sp )
    store_x x20, 18 * port_WORD_आकार( sp )
    store_x x21, 19 * port_WORD_आकार( sp )
    store_x x22, 20 * port_WORD_आकार( sp )
    store_x x23, 21 * port_WORD_आकार( sp )
    store_x x24, 22 * port_WORD_आकार( sp )
    store_x x25, 23 * port_WORD_आकार( sp )
    store_x x26, 24 * port_WORD_आकार( sp )
    store_x x27, 25 * port_WORD_आकार( sp )
    store_x x28, 26 * port_WORD_आकार( sp )
    store_x x29, 27 * port_WORD_आकार( sp )
    store_x x30, 28 * port_WORD_आकार( sp )
    store_x x31, 29 * port_WORD_आकार( sp )
#पूर्ण_अगर /* ifndef __riscv_32e */

load_x t0, xCriticalNesting                                   /* Load the value of xCriticalNesting into t0. */
store_x t0, portCRITICAL_NESTING_OFFSET * port_WORD_आकार( sp ) /* Store the critical nesting value to the stack. */

#अगर( configENABLE_FPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_FS_OFFSET
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 1f /* If FPU status is not dirty, do not save FPU registers. */

    portcontexSAVE_FPU_CONTEXT
1:
#पूर्ण_अगर

#अगर( configENABLE_VPU == 1 )
    csrr t0, mstatus
    srl t1, t0, MSTATUS_VS_OFFSET
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 2f /* If VPU status is not dirty, do not save VPU registers. */

    portcontexSAVE_VPU_CONTEXT
2:
#पूर्ण_अगर

csrr t0, mstatus
store_x t0, 1 * port_WORD_आकार( sp )

portasmSAVE_ADDITIONAL_REGISTERS /* Defined in freertos_risc_v_chip_specific_extensions.h to save any registers unique to the RISC-V implementation. */

#अगर( configENABLE_FPU == 1 )
    /* Mark the FPU as clean, if it was dirty and we saved FPU registers. */
    srl t1, t0, MSTATUS_FS_OFFSET
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 3f

    li t1, ~MSTATUS_FS_MASK
    and t0, t0, t1
    li t1, MSTATUS_FS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
3:
#पूर्ण_अगर

#अगर( configENABLE_VPU == 1 )
    /* Mark the VPU as clean, if it was dirty and we saved VPU registers. */
    srl t1, t0, MSTATUS_VS_OFFSET
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 4f

    li t1, ~MSTATUS_VS_MASK
    and t0, t0, t1
    li t1, MSTATUS_VS_CLEAN
    or t0, t0, t1
    csrw mstatus, t0
4:
#पूर्ण_अगर

load_x t0, pxCurrentTCB          /* Load pxCurrentTCB. */
store_x sp, 0 ( t0 )             /* Write sp to first TCB member. */

   .endm
/*-----------------------------------------------------------*/

   .macro portcontextSAVE_EXCEPTION_CONTEXT
portcontextSAVE_CONTEXT_INTERNAL
csrr a0, mcause
csrr a1, mepc
addi a1, a1, 4          /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
store_x a1, 0 ( sp )    /* Save updated exception return address. */
load_x sp, x_ISRStack_शीर्ष /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontextSAVE_INTERRUPT_CONTEXT
portcontextSAVE_CONTEXT_INTERNAL
csrr a0, mcause
csrr a1, mepc
store_x a1, 0 ( sp )    /* Asynchronous interrupt so save unmodified exception return address. */
load_x sp, x_ISRStack_शीर्ष /* Switch to ISR stack. */
   .endm
/*-----------------------------------------------------------*/

   .macro portcontextRESTORE_CONTEXT
load_x t1, pxCurrentTCB /* Load pxCurrentTCB. */
load_x sp, 0 ( t1 )     /* Read sp from first TCB member. */

/* Load mepc with the address of the instruction in the task to run next. */
load_x t0, 0 ( sp )
csrw mepc, t0

/* Defined in freertos_risc_v_chip_specific_extensions.h to restore any registers unique to the RISC-V implementation. */
portasmRESTORE_ADDITIONAL_REGISTERS

/* Restore mstatus register. It is important to use t3 (and not t0) here as t3
 * is not clobbered by portcontextRESTORE_VPU_CONTEXT and
 * portcontextRESTORE_FPU_CONTEXT. */
load_x t3, 1 * port_WORD_आकार( sp )
csrw mstatus, t3

#अगर( configENABLE_VPU == 1 )
    srl t1, t3, MSTATUS_VS_OFFSET
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 5f /* If VPU status is not dirty, do not restore VPU registers. */

    portcontextRESTORE_VPU_CONTEXT
5:
#पूर्ण_अगर /* ifdef portasmSTORE_VPU_CONTEXT */

#अगर( configENABLE_FPU == 1 )
    srl t1, t3, MSTATUS_FS_OFFSET
    andi t1, t1, 3
    addi t2, x0, 3
    bne t1, t2, 6f /* If FPU status is not dirty, do not restore FPU registers. */

    portcontextRESTORE_FPU_CONTEXT
6:
#पूर्ण_अगर /* ifdef portasmSTORE_FPU_CONTEXT */

load_x t0, portCRITICAL_NESTING_OFFSET * port_WORD_आकार( sp ) /* Obtain xCriticalNesting value for this task from task's stack. */
load_x t1, pxCriticalNesting                                 /* Load the address of xCriticalNesting into t1. */
store_x t0, 0 ( t1 )                                         /* Restore the critical nesting value for this task. */

load_x x1,  2  * port_WORD_आकार( sp )
load_x x5,  3  * port_WORD_आकार( sp )
load_x x6,  4  * port_WORD_आकार( sp )
load_x x7,  5  * port_WORD_आकार( sp )
load_x x8,  6  * port_WORD_आकार( sp )
load_x x9,  7  * port_WORD_आकार( sp )
load_x x10, 8  * port_WORD_आकार( sp )
load_x x11, 9  * port_WORD_आकार( sp )
load_x x12, 10 * port_WORD_आकार( sp )
load_x x13, 11 * port_WORD_आकार( sp )
load_x x14, 12 * port_WORD_आकार( sp )
load_x x15, 13 * port_WORD_आकार( sp )
#अगर_अघोषित __riscv_32e
    load_x x16, 14 * port_WORD_आकार( sp )
    load_x x17, 15 * port_WORD_आकार( sp )
    load_x x18, 16 * port_WORD_आकार( sp )
    load_x x19, 17 * port_WORD_आकार( sp )
    load_x x20, 18 * port_WORD_आकार( sp )
    load_x x21, 19 * port_WORD_आकार( sp )
    load_x x22, 20 * port_WORD_आकार( sp )
    load_x x23, 21 * port_WORD_आकार( sp )
    load_x x24, 22 * port_WORD_आकार( sp )
    load_x x25, 23 * port_WORD_आकार( sp )
    load_x x26, 24 * port_WORD_आकार( sp )
    load_x x27, 25 * port_WORD_आकार( sp )
    load_x x28, 26 * port_WORD_आकार( sp )
    load_x x29, 27 * port_WORD_आकार( sp )
    load_x x30, 28 * port_WORD_आकार( sp )
    load_x x31, 29 * port_WORD_आकार( sp )
#पूर्ण_अगर /* ifndef __riscv_32e */
addi sp, sp, port_CONTEXT_आकार

mret
   .endm
/*-----------------------------------------------------------*/

#पूर्ण_अगर /* PORTCONTEXT_H */
