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

/* Secure context includes. */
#అన్తర్భావ "secure_context.h"

/* Secure port macros. */
#అన్తర్భావ "secure_port_macros.h"

శూన్య Secure_Context_ఎక్కించు_Context_Asm( SecureContext_t * pxSecureContext ) __attribute__( ( naked ) );
శూన్య SecureContext_SaveContextAsm( SecureContext_t * pxSecureContext ) __attribute__( ( naked ) );

శూన్య Secure_Context_ఎక్కించు_Context_Asm( SecureContext_t * pxSecureContext )
{
    /* pxSecureContext value is in r0. */
    __asm అస్థిర
    (
        " .syntax unified                   \n"
        "                                   \n"
        " mrs r1, ipsr                      \n" /* r1 = IPSR. */
        " cbz r1, load_ctx_therad_mode      \n" /* Do nothing if the processor is running in the Thread Mode. */
        " ldmia r0!, {r1, r2}               \n" /* r1 = pxSecureContext->pucCurrentStackPointer, r2 = pxSecureContext->pucStackLimit. */
        "                                   \n"
        #ఒకవేళ ( configENABLE_MPU == 1 )
            " ldmia r1!, {r3}               \n" /* Read CONTROL register value from task's stack. r3 = CONTROL. */
            " msr control, r3               \n" /* CONTROL = r3. */
        #అయితే_ముగింపు /* configENABLE_MPU */
        "                                   \n"
        " msr psplim, r2                    \n" /* PSPLIM = r2. */
        " msr psp, r1                       \n" /* PSP = r1. */
        "                                   \n"
        " load_ctx_therad_mode:             \n"
        "    bx lr                          \n"
        "                                   \n"
        ::: "r0", "r1", "r2"
    );
}
/*-----------------------------------------------------------*/

శూన్య SecureContext_SaveContextAsm( SecureContext_t * pxSecureContext )
{
    /* pxSecureContext value is in r0. */
    __asm అస్థిర
    (
        " .syntax unified                   \n"
        "                                   \n"
        " mrs r1, ipsr                      \n" /* r1 = IPSR. */
        " cbz r1, save_ctx_therad_mode      \n" /* Do nothing if the processor is running in the Thread Mode. */
        " mrs r1, psp                       \n" /* r1 = PSP. */
        "                                   \n"
        #ఒకవేళ ( ( configENABLE_FPU == 1 ) || ( configENABLE_MVE == 1 ) )
            " vstmdb r1!, {s0}              \n" /* Trigger the deferred stacking of FPU registers. */
            " vldmia r1!, {s0}              \n" /* Nullify the effect of the previous statement. */
        #అయితే_ముగింపు /* configENABLE_FPU || configENABLE_MVE */
        "                                   \n"
        #ఒకవేళ ( configENABLE_MPU == 1 )
            " mrs r2, control               \n" /* r2 = CONTROL. */
            " stmdb r1!, {r2}               \n" /* Store CONTROL value on the stack. */
        #అయితే_ముగింపు /* configENABLE_MPU */
        "                                   \n"
        " str r1, [r0]                      \n" /* Save the top of stack in context. pxSecureContext->pucCurrentStackPointer = r1. */
        " movs r1, %0                       \n" /* r1 = securecontextNO_STACK. */
        " msr psplim, r1                    \n" /* PSPLIM = securecontextNO_STACK. */
        " msr psp, r1                       \n" /* PSP = securecontextNO_STACK i.e. No stack for thread mode until next task's context is loaded. */
        "                                   \n"
        " save_ctx_therad_mode:             \n"
        "    bx lr                          \n"
        "                                   \n"
        ::"i" ( securecontext_NO_దొంతర ) : "r1", "memory"
    );
}
/*-----------------------------------------------------------*/
