/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS അഥവാ
 * IMPLIED, INCLUDING BUT അല്ല LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE ഒപ്പം NONINFRINGEMENT. ഇൽ NO EVENT SHALL THE AUTHORS അഥവാ
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES അഥവാ OTHER LIABILITY, WHETHER
 * ഇൽ AN ACTION OF CONTRACT, TORT അഥവാ OTHERWISE, ARISING FROM, OUT OF അഥവാ ഇൽ
 * CONNECTION WITH THE SOFTWARE അഥവാ THE USE അഥവാ OTHER DEALINGS ഇൽ THE SOFTWARE.
 *
 */

//#include <csi_config.h>

/********************************************************************
 * Functions: vPortStartTask
 *
 ********************************************************************/
.വൈശ്വിക vPortStartTask
.type   vPortStartTask, %function
vPortStartTask:
    psrclr   ie
    lrw      r4, pxCurrentTCB
    ld.w     r4, (r4)                // the current task stack pointer is the first member
    ld.w     sp, (r4)

    ldw      r0, (sp, 64)
    mtcr     r0, epc
    ldw      r0, (sp, 60)
    mtcr     r0, epsr
    ldw      r15, (sp, 56)
    ldm      r0-r13, (sp)
    addi     sp, 68
    rte

/********************************************************************
 * Functions: vPortYield
 *
 ********************************************************************/
.വൈശ്വിക vPortYield
.type   vPortYield, %function
vPortYield:
    psrclr  ee
    subi    sp, 68
    stm     r0-r13, (sp)
    stw     r15, (sp, 56)
    mfcr    r0, psr
    bseti   r0, 8
    stw     r0, (sp, 60)
    stw     r15, (sp, 64)

    lrw     r2, pxCurrentTCB
    ld.w    r3, (r2)
    st.w    sp, (r3)

    jbsr    vTaskSwitchContext
    lrw     r4, pxCurrentTCB
    ld.w    r4, (r4)
    ld.w    sp, (r4)

    ldw     r0, (sp, 64)
    mtcr    r0, epc
    ldw     r0, (sp, 60)
    mtcr    r0, epsr
    ldw     r15, (sp, 56)
    ldm     r0-r13, (sp)
    addi    sp, 68

    rte

/********************************************************************
 * Functions: NOVIC_IRQ_Default_Handler
 *
 ********************************************************************/
.വൈശ്വിക NOVIC_IRQ_Default_Handler
.type   NOVIC_IRQ_Default_Handler, %function
NOVIC_IRQ_Default_Handler:
    psrset  ee
    subi    sp, 68
    stm     r0-r13, (sp)
    stw     r15, (sp, 56)
    mfcr    r0, epsr
    stw     r0, (sp, 60)
    mfcr    r0, epc
    stw     r0, (sp, 64)

    lrw     r7, pxCurrentTCB
    ldw     r7, (r7)
    stw     sp, (r7)

    lrw     sp, g_top_irqstack

    lrw     r1, g_irqvector
    mfcr    r0, psr
    lsri    r0, 16
    sextb   r0
    subi    r0, 32
    lsli    r0, 2
    add     r1, r0
    ldw     r1, (r1)
    lsri    r0, 2
    jsr     r1

    lrw     r7, pxCurrentTCB
    ldw     r7, (r7)
    ldw     sp, (r7)

    ldw     r0, (sp, 64)
    mtcr    r0, epc
    ldw     r0, (sp, 60)
    mtcr    r0, epsr
    ldm     r0-r13, (sp)
    ldw     r15, (sp, 56)
    addi    sp, 68
    rte
