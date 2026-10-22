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
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

/* Secure init includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "secure_init.h"

/* Secure port macros. */
#ਅਨ੍ਤਰ੍ਭਾਵ "secure_port_macros.h"

/**
 * @brief Constants required to manipulate the SCB.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinitSCB_AIRCR                 ( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed0c )  /* Application Interrupt and Reset Control Register. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinitSCB_AIRCR_VECTKEY_POS     ( 16UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinit_SCB_AIRCR_VECTKEY_ਨਕਾਬ    ( 0xFFFFUL << secureinitSCB_AIRCR_VECTKEY_POS )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinitSCB_AIRCR_PRIS_POS        ( 14UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinit_SCB_AIRCR_PRIS_ਨਕਾਬ       ( 1UL << secureinitSCB_AIRCR_PRIS_POS )

/**
 * @brief Constants required to manipulate the FPU.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinitFPCCR                     ( ( ਅਸਥਿਰ uint32_t * ) 0xe000ef34 )  /* Floating Point Context Control Register. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinitFPCCR_LSPENS_POS          ( 29UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinit_FPCCR_LSPENS_ਨਕਾਬ         ( 1UL << secureinitFPCCR_LSPENS_POS )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinitFPCCR_TS_POS              ( 26UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinit_FPCCR_TS_ਨਕਾਬ             ( 1UL << secureinitFPCCR_TS_POS )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinitNSACR                     ( ( ਅਸਥਿਰ uint32_t * ) 0xe000ed8c )  /* Non-secure Access Control Register. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinitNSACR_CP10_POS            ( 10UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinit_NSACR_CP10_ਨਕਾਬ           ( 1UL << secureinitNSACR_CP10_POS )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinitNSACR_CP11_POS            ( 11UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureinit_NSACR_CP11_ਨਕਾਬ           ( 1UL << secureinitNSACR_CP11_POS )
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE ਖਾਲੀ SecureInit_DePrioritizeNSExceptions( ਖਾਲੀ )
{
    uint32_t ulIPSR;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    ਜੇ( ulIPSR != 0 )
    {
        *( secureinitSCB_AIRCR ) = ( *( secureinitSCB_AIRCR ) & ~( secureinit_SCB_AIRCR_VECTKEY_ਨਕਾਬ | secureinit_SCB_AIRCR_PRIS_ਨਕਾਬ ) ) |
                                   ( ( 0x05FAUL << secureinitSCB_AIRCR_VECTKEY_POS ) & secureinit_SCB_AIRCR_VECTKEY_ਨਕਾਬ ) |
                                   ( ( 0x1UL << secureinitSCB_AIRCR_PRIS_POS ) & secureinit_SCB_AIRCR_PRIS_ਨਕਾਬ );
    }
}
/*-----------------------------------------------------------*/

secureportNON_SECURE_CALLABLE ਖਾਲੀ SecureInit_EnableNSFPUAccess( ਖਾਲੀ )
{
    uint32_t ulIPSR;

    /* Read the Interrupt Program Status Register (IPSR) value. */
    secureportREAD_IPSR( ulIPSR );

    /* Do nothing if the processor is running in the Thread Mode. IPSR is zero
     * when the processor is running in the Thread Mode. */
    ਜੇ( ulIPSR != 0 )
    {
        /* CP10 = 1 ==> Non-secure access to the Floating Point Unit is
         * permitted. CP11 should be programmed to the same value as CP10. */
        *( secureinitNSACR ) |= ( secureinit_NSACR_CP10_ਨਕਾਬ | secureinit_NSACR_CP11_ਨਕਾਬ );

        /* LSPENS = 0 ==> LSPEN is writable from non-secure state. This ensures
         * that we can enable/disable lazy stacking in port.c file. */
        *( secureinitFPCCR ) &= ~( secureinit_FPCCR_LSPENS_ਨਕਾਬ );

        /* TS = 1 ==> Treat FP registers as secure i.e. callee saved FP
         * registers (S16-S31) are also pushed to stack on exception entry and
         * restored on exception return. */
        *( secureinitFPCCR ) |= ( secureinit_FPCCR_TS_ਨਕਾਬ );
    }
}
/*-----------------------------------------------------------*/
