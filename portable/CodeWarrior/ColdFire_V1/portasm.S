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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS ಅಥವಾ
 * IMPLIED, INCLUDING BUT ಅಲ್ಲ LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE ಮತ್ತು NONINFRINGEMENT. ಒಳಗೆ NO EVENT SHALL THE AUTHORS ಅಥವಾ
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES ಅಥವಾ OTHER LIABILITY, WHETHER
 * ಒಳಗೆ AN ACTION OF CONTRACT, TORT ಅಥವಾ OTHERWISE, ARISING FROM, OUT OF ಅಥವಾ ಒಳಗೆ
 * CONNECTION WITH THE SOFTWARE ಅಥವಾ THE USE ಅಥವಾ OTHER DEALINGS ಒಳಗೆ THE SOFTWARE.
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
 * ul_ಪೋರ್ಟ್_ಗಣ_IPL() and mcf5xxx_wr_cacr() copied with permission from FreeScale
 * supplied source files.
 */

    .ವೈಶ್ವಿಕ ul_ಪೋರ್ಟ್_ಗಣ_IPL
    .ವೈಶ್ವಿಕ _ulPortSetIPL
    .ವೈಶ್ವಿಕ mcf5xxx_wr_cacrx
    .ವೈಶ್ವಿಕ _mcf5xxx_wr_cacrx
    .ವೈಶ್ವಿಕ v_ಪೋರ್ಟ್_Yield_ISR
    .ವೈಶ್ವಿಕ _vPortYieldISR
    .ವೈಶ್ವಿಕ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task
    .ವೈಶ್ವಿಕ _vPortStartFirstTask
    .extern _pxCurrentTCB
    .extern _vPortYieldHandler

    .text

.macro portSAVE_CONTEXT

    lea.l       (-60, sp), sp
    movem.l     d0-a6, (sp)
    move.l      _pxCurrentTCB, a0
    move.l      sp, (a0)

    .endm

.macro portRESTORE_CONTEXT

    move.l      _pxCurrentTCB, a0
    move.l      (a0), sp
    movem.l     (sp), d0-a6
    lea.l       (60, sp), sp
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

ul_ಪೋರ್ಟ್_ಗಣ_IPL:
_ulPortSetIPL:
    link    A6,#-8
    movem.l D6-D7,(SP)

    move.w  SR,D7       /* current sr    */

    move.l  D7,D6       /* prepare return value  */
    andi.l  #0x0700,D6  /* mask out IPL  */
    lsr.l   #8,D6       /* IPL   */

    andi.l  #0x07,D0    /* least significant three bits  */
    lsl.l   #8,D0       /* move over to make mask    */

    andi.l  #0x0000F8FF,D7  /* zero out current IPL  */
    or.l    D0,D7           /* place new IPL in sr   */
    move.w  D7,SR

    move.l  D6, D0      /* Return value in D0. */
    movem.l (SP),D6-D7
    lea     8(SP),SP
    unlk    A6
    rts
/********************************************************************/

mcf5xxx_wr_cacrx:
_mcf5xxx_wr_cacrx:
    move.l  4(sp),d0
    .long   0x4e7b0002  /* movec d0,cacr   */
    nop
    rts

/********************************************************************/

/* Yield interrupt. */
_vPortYieldISR:
v_ಪೋರ್ಟ್_Yield_ISR:
    portSAVE_CONTEXT
    jsr _vPortYieldHandler
    portRESTORE_CONTEXT

/********************************************************************/


v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task:
_vPortStartFirstTask:
    portRESTORE_CONTEXT

    .end
