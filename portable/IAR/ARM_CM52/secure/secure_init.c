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
#अन्तर्भाव <stdint.h>

/* Secure init includes. */
#अन्तर्भाव "secure_init.h"

/* Secure port macros. */
#अन्तर्भाव "secure_port_macros.h"

/**
 * @brief Constants required to manipulate the SCB.
 */
#परिभाषय secureinitSCB_AIRCR                 ( ( चञ्चल uint32_t * ) 0xe000ed0c )  /* Application Interrupt and Reset Control Register. */
#परिभाषय secureinitSCB_AIRCR_VECTKEY_POS     ( 16UL )
#परिभाषय secureinit_SCB_AIRCR_VECTKEY_आवरणम्    ( 0xFFFFUL << secureinitSCB_AIRCR_VECTKEY_POS )
#परिभाषय secureinitSCB_AIRCR_PRIS_POS        ( 14UL )
#परिभाषय secureinit_SCB_AIRCR_PRIS_आवरणम्       ( 1UL << secureinitSCB_AIRCR_PRIS_POS )

/**
 * @brief Constants required to manipulate the FPU.
 */
#परिभाषय secureinitFPCCR                     ( ( चञ्चल uint32_t * ) 0xe000ef34 )  /* Floating Point Context Control Register. */
#परिभाषय secureinitFPCCR_LSPENS_POS          ( 29UL )
#परिभाषय secureinit_FPCCR_LSPENS_आवरणम्         ( 1UL << secureinitFPCCR_LSPENS_POS )
#परिभाषय secureinitFPCCR_TS_POS              ( 26UL )
#परिभाषय secureinit_FPCCR_TS_आवरणम्             ( 1UL << secureinitFPCCR_TS_POS )

#परिभाषय secureinitNSACR                     ( ( चञ्चल uint32_t * ) 0xe000ed8c )  /* Non-secure Access Control Register. */
#परिभाषय secureinitNSACR_CP10_POS            ( 10UL )
#परिभाषय secureinit_NSACR_CP10_आवरणम्           ( 1UL << secureinitNSACR_CP10_POS )
#परिभाषय secureinitNSACR_CP11_POS            ( 11UL )
#परिभाषय secureinit_NSACR_CP11_आवरणम्           ( 1UL << secureinitNSACR_CP11_POS )
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE शून्य SecureInit_DePrioritizeNSExceptions( शून्य )
{
    uint32_t ulIPSR;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    यदि( ulIPSR != 0 )
    {
        *( secureinitSCB_AIRCR ) = ( *( secureinitSCB_AIRCR ) & ~( secureinit_SCB_AIRCR_VECTKEY_आवरणम् | secureinit_SCB_AIRCR_PRIS_आवरणम् ) ) |
                                   ( ( 0x05FAUL << secureinitSCB_AIRCR_VECTKEY_POS ) & secureinit_SCB_AIRCR_VECTKEY_आवरणम् ) |
                                   ( ( 0x1UL << secureinitSCB_AIRCR_PRIS_POS ) & secureinit_SCB_AIRCR_PRIS_आवरणम् );
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE शून्य SecureInit_EnableNSFPUAccess( शून्य )
{
    uint32_t ulIPSR;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    यदि( ulIPSR != 0 )
    {
        /* CP10 = 1 ==> Non-secure access to the Floating Point Unit is
         * permitted. CP11 should be programmed to the same value as CP10. */
        *( secureinitNSACR ) |= ( secureinit_NSACR_CP10_आवरणम् | secureinit_NSACR_CP11_आवरणम् );

        /* LSPENS = 0 ==> LSPEN is writable from non-secure state. This ensures
         * that we can enable/disable lazy stacking in port.c file. */
        *( secureinitFPCCR ) &= ~( secureinit_FPCCR_LSPENS_आवरणम् );

        /* TS = 1 ==> Treat FP registers as secure i.e. callee saved FP
         * registers (S16-S31) are also pushed to stack on exception entry and
         * restored on exception return. */
        *( secureinitFPCCR ) |= ( secureinit_FPCCR_TS_आवरणम् );
    }
}
/*-----------------------------------------------------------*/
