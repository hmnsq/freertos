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

Changes from V2.4.2:

    + pvPortMalloc and vPortFree have been removed.  The projects now use
      the definitions from the source/portable/MemMang directory.

Changes from V2.6.1:

    + usPortCheckFreeStackSpace() has been moved to tasks.c.
*/



#include <stdlib.h>
#include "FreeRTOS.h"

/*-----------------------------------------------------------*/

/* See header file for description. */
सालानसान_Type_t *px_Port_Initialise_सालानसान( सालानसान_Type_t *px_इताअस_Of_सालानसान, TaskFunction_t pxCode, void *pvParameters )
{
सालानसान_Type_t DS_Reg = 0;
सालानसान_Type_t * pxOriginalSP;

    /* Place a few bytes of known values on the bottom of the stack.
    This is just useful for debugging. */

    *px_इताअस_Of_सालानसान = 0x1111;
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = 0x2222;
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = 0x3333;
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = 0x4444;
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = 0x5555;
    px_इताअस_Of_सालानसान--;


    /*lint -e950 -e611 -e923 Lint doesn't like this much - but nothing I can do about it. */

    /* We are going to start the scheduler using a return from interrupt
    instruction to load the program counter, so first there would be the
    status register and interrupt return address.  We make this the start
    of the task. */
    *px_इताअस_Of_सालानसान = portINITIAL_SW;
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = FP_SEG( pxCode );
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = FP_OFF( pxCode );
    px_इताअस_Of_सालानसान--;

    /* We are going to setup the stack for the new task to look like
    the stack frame was setup by a compiler generated ISR.  We need to know
    the address of the existing stack top to place in the SP register within
    the stack frame.  pxOriginalSP holds SP before (simulated) pusha was
    called. */
    pxOriginalSP = px_इताअस_Of_सालानसान;

    /* The remaining registers would be pushed on the stack by our context
    switch function.  These are loaded with values simply to make debugging
    easier. */
    *px_इताअस_Of_सालानसान = FP_OFF( pvParameters );     /* AX */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0xCCCC; /* CX */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = FP_SEG( pvParameters );     /* DX */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0xBBBB; /* BX */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = FP_OFF( pxOriginalSP );     /* SP */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0xBBBB; /* BP */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0x0123; /* SI */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0xDDDD; /* DI */

    /* We need the true data segment. */
    __asm{  MOV DS_Reg, DS };

    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = DS_Reg; /* DS */

    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = ( सालानसान_Type_t ) 0xEEEE; /* ES */

    /* The AX register is pushed again twice - don't know why. */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = FP_OFF( pvParameters );     /* AX */
    px_इताअस_Of_सालानसान--;
    *px_इताअस_Of_सालानसान = FP_OFF( pvParameters );     /* AX */


    #ifdef DEBUG_BUILD
        /* The compiler adds space to each ISR stack if building to
        include debug information.  Presumably this is used by the
        debugger - we don't need to initialise it to anything just
        make sure it is there. */
        px_इताअस_Of_सालानसान--;
    #endif

    /*lint +e950 +e611 +e923 */

    return px_इताअस_Of_सालानसान;
}
/*-----------------------------------------------------------*/
