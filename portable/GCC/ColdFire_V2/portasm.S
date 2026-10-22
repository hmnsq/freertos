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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS أو
 * IMPLIED, INCLUDING BUT ليس LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE و NONINFRINGEMENT. في NO EVENT SHALL THE AUTHORS أو
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES أو OTHER LIABILITY, WHETHER
 * في AN ACTION OF CONTRACT, TORT أو OTHERWISE, ARISING FROM, OUT OF أو في
 * CONNECTION WITH THE SOFTWARE أو THE USE أو OTHER DEALINGS في THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*
 * Purpose: Lowest level routines for all ColdFire processors.
 *
 * Notes:
 *
 * ul_پورټ_سېټ_IPL() and mcf5xxx_wr_cacr() copied with permission from FreeScale
 * supplied source files.
 */

    .global ul_پورټ_سېټ_IPL
    .global mcf5xxx_wr_cacr
    .global __cs3_isr_interrupt_80
    .global v_پورټ_پیل_لومړی_Task

    .text

.macro portSAVE_CONTEXT

    lea.l       (-60, %sp), %sp
    movem.l     %d0-%fp, (%sp)
    move.l      pxCurrentTCB, %a0
    move.l      %sp, (%a0)

    .endm

.macro portRESTORE_CONTEXT

    move.l      pxCurrentTCB, %a0
    move.l      (%a0), %sp
    movem.l     (%sp), %d0-%fp
    lea.l       %sp@(60), %sp
    rte

    .endm

/********************************************************************/
/*
 * This routines changes the IPL to the value passed into the routine.
 * It also returns the old IPL value back.
 * Calling convention from C:
 *   old_ipl = asm_set_ipl(new_ipl);
 * For the Diab Data C compiler, it passes return value thru D0.
 * Note that only the least significant three bits of the passed
 * value are used.
 */

ul_پورټ_سېټ_IPL:
    link    A6,#-8
    movem.l D6-D7,(SP)

    move.w  SR,D7       /* current sr    */

    move.l  D7,D0       /* prepare return value  */
    andi.l  #0x0700,D0  /* mask out IPL  */
    lsr.l   #8,D0       /* IPL   */

    move.l  8(A6),D6    /* get argument  */
    andi.l  #0x07,D6    /* least significant three bits  */
    lsl.l   #8,D6       /* move over to make mask    */

    andi.l  #0x0000F8FF,D7  /* zero out current IPL  */
    or.l    D6,D7           /* place new IPL in sr   */
    move.w  D7,SR

    movem.l (SP),D6-D7
    lea     8(SP),SP
    unlk    A6
    rts
/********************************************************************/

mcf5xxx_wr_cacr:
    move.l  4(sp),d0
    .long   0x4e7b0002  /* movec d0,cacr   */
    nop
    rts

/********************************************************************/

/* Yield interrupt. */
__cs3_isr_interrupt_80:
    portSAVE_CONTEXT
    jsr vPortYieldHandler
    portRESTORE_CONTEXT

/********************************************************************/


v_پورټ_پیل_لومړی_Task:
    portRESTORE_CONTEXT

    .end
