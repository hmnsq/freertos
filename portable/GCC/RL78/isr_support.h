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

/* Variables used by scheduler */
.ബാഹ്യ _pxCurrentTCB
   .ബാഹ്യ _usCriticalNesting

/*
 * portSAVE_CONTEXT MACRO
 * Saves the context of the general purpose registers, CS and ES (only in far
 * memory mode) registers the usCriticalNesting Value and the Stack Pointer
 * of the active Task onto the task stack
 */
   .macro portSAVE_CONTEXT

SEL RB0

/* Save AX Register to stack. */
തള്ളുക_2 AX
തള്ളുക_2 HL
/* Save CS register. */
MOV A, CS
XCH A, X
/* Save ES register. */
MOV A, ES
തള്ളുക_2 AX
/* Save the remaining general purpose registers from bank 0. */
തള്ളുക_2 DE
തള്ളുക_2 BC
/* Save the other register banks - only necessary in the GCC port. */
SEL RB1
തള്ളുക_2 AX
തള്ളുക_2 BC
തള്ളുക_2 DE
തള്ളുക_2 HL
SEL RB2
തള്ളുക_2 AX
തള്ളുക_2 BC
തള്ളുക_2 DE
തള്ളുക_2 HL
/* Registers in bank 3 are for ISR use only so don't need saving. */
SEL RB0
/* Save the usCriticalNesting value. */
MOVW AX, !_usCriticalNesting
തള്ളുക_2 AX
/* Save the Stack pointer. */
MOVW AX, !_pxCurrentTCB
MOVW HL, AX
MOVW AX, SP
MOVW[ HL ], AX
/* Switch stack pointers. */
movw sp, # അട്ടി_3 /* Set stack pointer */

   .endm


/*
 * portRESTORE_CONTEXT MACRO
 * Restores the task Stack Pointer then use this to restore usCriticalNesting,
 * general purpose registers and the CS and ES (only in far memory mode)
 * of the selected task from the task stack
 */
   .macro portRESTORE_CONTEXT MACRO
SEL RB0
/* Restore the Stack pointer. */
MOVW AX, !_pxCurrentTCB
MOVW HL, AX
MOVW AX, [ HL ]
MOVW SP, AX
/* Restore usCriticalNesting value. */
എടുക്കുക_2 AX
MOVW    !_usCriticalNesting, AX

/* Restore the alternative register banks - only necessary in the GCC
 * port.  Register bank 3 is dedicated for interrupts use so is not saved or
 * restored. */
SEL RB2
എടുക്കുക_2 HL
എടുക്കുക_2 DE
എടുക്കുക_2 BC
എടുക്കുക_2 AX
SEL RB1
എടുക്കുക_2 HL
എടുക്കുക_2 DE
എടുക്കുക_2 BC
എടുക്കുക_2 AX
SEL RB0
/* Restore the necessary general purpose registers. */
എടുക്കുക_2 BC
എടുക്കുക_2 DE
/* Restore the ES register. */
എടുക്കുക_2 AX
MOV ES, A
/* Restore the CS register. */
XCH A, X
MOV CS, A
/* Restore general purpose register HL. */
എടുക്കുക_2 HL
/* Restore AX. */
എടുക്കുക_2 AX

   .endm
