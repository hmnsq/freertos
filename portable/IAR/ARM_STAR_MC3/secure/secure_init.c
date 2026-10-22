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

/* Standard includes. */
#समावेश <stdint.h>

/* Secure init includes. */
#समावेश "secure_init.h"

/* Secure port macros. */
#समावेश "secure_port_macros.h"

/**
 * @brief Constants required to manipulate the SCB.
 */
#घोषणा secureinitSCB_AIRCR                 ( ( अस्थिर uint32_t * ) 0xe000ed0c )  /* Application Interrupt and Reset Control Register. */
#घोषणा secureinitSCB_AIRCR_VECTKEY_POS     ( 16UL )
#घोषणा secureinitSCB_AIRCR_VECTKEY_MASK    ( 0xFFFFUL << secureinitSCB_AIRCR_VECTKEY_POS )
#घोषणा secureinitSCB_AIRCR_PRIS_POS        ( 14UL )
#घोषणा secureinitSCB_AIRCR_PRIS_MASK       ( 1UL << secureinitSCB_AIRCR_PRIS_POS )

/**
 * @brief Constants required to manipulate the FPU.
 */
#घोषणा secureinitFPCCR                     ( ( अस्थिर uint32_t * ) 0xe000ef34 )  /* Floating Point Context Control Register. */
#घोषणा secureinitFPCCR_LSPENS_POS          ( 29UL )
#घोषणा secureinitFPCCR_LSPENS_MASK         ( 1UL << secureinitFPCCR_LSPENS_POS )
#घोषणा secureinitFPCCR_TS_POS              ( 26UL )
#घोषणा secureinitFPCCR_TS_MASK             ( 1UL << secureinitFPCCR_TS_POS )

#घोषणा secureinitNSACR                     ( ( अस्थिर uint32_t * ) 0xe000ed8c )  /* Non-secure Access Control Register. */
#घोषणा secureinitNSACR_CP10_POS            ( 10UL )
#घोषणा secureinitNSACR_CP10_MASK           ( 1UL << secureinitNSACR_CP10_POS )
#घोषणा secureinitNSACR_CP11_POS            ( 11UL )
#घोषणा secureinitNSACR_CP11_MASK           ( 1UL << secureinitNSACR_CP11_POS )
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE व्योम SecureInit_DePrioritizeNSExceptions( व्योम )
{
    uint32_t ulIPSR;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    अगर( ulIPSR != 0 )
    {
        *( secureinitSCB_AIRCR ) = ( *( secureinitSCB_AIRCR ) & ~( secureinitSCB_AIRCR_VECTKEY_MASK | secureinitSCB_AIRCR_PRIS_MASK ) ) |
                                   ( ( 0x05FAUL << secureinitSCB_AIRCR_VECTKEY_POS ) & secureinitSCB_AIRCR_VECTKEY_MASK ) |
                                   ( ( 0x1UL << secureinitSCB_AIRCR_PRIS_POS ) & secureinitSCB_AIRCR_PRIS_MASK );
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE व्योम SecureInit_EnableNSFPUAccess( व्योम )
{
    uint32_t ulIPSR;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    अगर( ulIPSR != 0 )
    {
        /* CP10 = 1 ==> Non-secure access to the Floating Point Unit is
         * permitted. CP11 should be programmed to the same value as CP10. */
        *( secureinitNSACR ) |= ( secureinitNSACR_CP10_MASK | secureinitNSACR_CP11_MASK );

        /* LSPENS = 0 ==> LSPEN is writable from non-secure state. This ensures
         * that we can enable/disable lazy stacking in port.c file. */
        *( secureinitFPCCR ) &= ~( secureinitFPCCR_LSPENS_MASK );

        /* TS = 1 ==> Treat FP registers as secure i.e. callee saved FP
         * registers (S16-S31) are also pushed to stack on exception entry and
         * restored on exception return. */
        *( secureinitFPCCR ) |= ( secureinitFPCCR_TS_MASK );
    }
}
/*-----------------------------------------------------------*/
