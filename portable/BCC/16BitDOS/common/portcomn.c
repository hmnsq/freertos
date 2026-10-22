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

/*
Changes from V1.00:

    + pxPortInitialiseStack() now initialises the stack of new tasks to the
      same format used by the compiler.  This allows the compiler generated
      interrupt mechanism to be used for context switches.

Changes from V2.6.1

    + Move usPortCheckFreeStackSpace() to tasks.c.
*/


#అన్తర్భావ <dos.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ "FreeRTOS.h"

/*-----------------------------------------------------------*/

/* See header file for description. */
దొంతర_Type_t *px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t *px_శిఖరం_యొక్క_దొంతర, TaskFunction_t px_సంకేతం, శూన్య *pvParameters )
{
దొంతర_Type_t DS_Reg = 0;

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_శిఖరం_యొక్క_దొంతర = 0x1111;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x2222;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x3333;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x4444;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = 0x5555;
    px_శిఖరం_యొక్క_దొంతర--;


    /*lint -e950 -e611 -e923 Lint doesn't like this much - but nothing I can do about it. */

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    function call with parameters preamble. */

    *px_శిఖరం_యొక్క_దొంతర = FP_SEG( pvParameters );
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = FP_OFF( pvParameters );
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = FP_SEG( px_సంకేతం );
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = FP_OFF( px_సంకేతం );
    px_శిఖరం_యొక్క_దొంతర--;

    /* Next the status register and interrupt return address. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_INITIAL_SW;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = FP_SEG( px_సంకేతం );
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = FP_OFF( px_సంకేతం );
    px_శిఖరం_యొక్క_దొంతర--;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xAAAA; /* AX */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xBBBB; /* BX */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xCCCC; /* CX */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xDDDD; /* DX */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xEEEE; /* ES */
    px_శిఖరం_యొక్క_దొంతర--;

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    *px_శిఖరం_యొక్క_దొంతర = DS_Reg;                     /* DS */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x0123; /* SI */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xDDDD; /* DI */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0xBBBB; /* BP */

    /*lint +e950 +e611 +e923 */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/
