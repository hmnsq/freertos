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

/* Kernel includes. */
#ضمن "FreeRTOS.h"

/* Machine includes */
#ضمن <tc1782.h>
#ضمن <machine/intrinsics.h>
#ضمن <machine/cint.h>
/*---------------------------------------------------------------------------*/

/*
 * This reference is required by the Save/Restore Context Macros.
 */
خارجي متطاير uint32_t * pxCurrentTCB;
/*-----------------------------------------------------------*/

/*
 * This file contains base definitions for all of the possible traps in the system.
 * It is suggested to provide implementations for all of the traps but for
 * the time being they simply trigger a DEBUG instruction so that it is easy
 * to see what caused a particular trap.
 *
 * Trap Class 6, the SYSCALL, is used exclusively by the operating system.
 */

/* The Trap Classes. */
#وصف_ڪريو پورٽ_MMU_TRAP                                                      0
#وصف_ڪريو پورٽ_IPT_TRAP                                                      1
#وصف_ڪريو پورٽ_IE_TRAP                                                       2
#وصف_ڪريو پورٽ_CM_TRAP                                                       3
#وصف_ڪريو پورٽ_SBP_TRAP                                                      4
#وصف_ڪريو پورٽ_ASSERT_TRAP                                                   5
#وصف_ڪريو پورٽ_NMI_TRAP                                                      7

/* MMU Trap Identifications. */
#وصف_ڪريو پورٽ_TIN_MMU_VIRTUAL_پتو_FILL                                  0
#وصف_ڪريو پورٽ_TIN_MMU_VIRTUAL_پتو_PROTECTION                            1

/* Internal Protection Trap Identifications. */
#وصف_ڪريو پورٽ_TIN_IPT_PRIVILEGED_INSTRUCTION                                1
#وصف_ڪريو پورٽ_TIN_IPT_يادگيري_PROTECTION_READ                                2
#وصف_ڪريو پورٽ_TIN_IPT_يادگيري_PROTECTION_WRITE                               3
#وصف_ڪريو پورٽ_TIN_IPT_يادگيري_PROTECTION_EXECUTION                           4
#وصف_ڪريو پورٽ_TIN_IPT_يادگيري_PROTECTION_PERIPHERAL_ACCESS                   5
#وصف_ڪريو پورٽ_TIN_IPT_يادگيري_PROTECTION_NULL_پتو                        6
#وصف_ڪريو پورٽ_TIN_IPT_يادگيري_PROTECTION_GLOBAL_رجسٽر_WRITE_PROTECTION    7

/* Instruction Error Trap Identifications. */
#وصف_ڪريو پورٽ_TIN_IE_ILLEGAL_OPCODE                                         1
#وصف_ڪريو پورٽ_TIN_IE_UNIMPLEMENTED_OPCODE                                   2
#وصف_ڪريو پورٽ_TIN_IE_INVALID_عمليو                                        3
#وصف_ڪريو پورٽ_TIN_IE_معلومات_پتو_ALIGNMENT                                 4
#وصف_ڪريو پورٽ_TIN_IE_INVALID_LOCAL_يادگيري_پتو                           5

/* Context Management Trap Identifications. */
#وصف_ڪريو پورٽ_TIN_CM_FREE_CONTEXT_LIST_DEPLETION                            1
#وصف_ڪريو پورٽ_TIN_CM_CALL_اونهائي_حد_کان_مٿي                                    2
#وصف_ڪريو پورٽ_TIN_CM_CALL_اونهائي_UNDEFLOW                                    3
#وصف_ڪريو پورٽ_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW                            4
#وصف_ڪريو پورٽ_TIN_CM_CALL_ڍير_UNDERFLOW                                   5
#وصف_ڪريو پورٽ_TIN_CM_CONTEXT_TYPE                                           6
#وصف_ڪريو پورٽ_TIN_CM_NESTING_ERROR                                          7

/* System Bus and Peripherals Trap Identifications. */
#وصف_ڪريو پورٽ_TIN_SBP_پروگرام_FETCH_SYNCHRONOUS_ERROR                       1
#وصف_ڪريو پورٽ_TIN_SBP_معلومات_ACCESS_SYNCHRONOUS_ERROR                         2
#وصف_ڪريو پورٽ_TIN_SBP_معلومات_ACCESS_ASYNCHRONOUS_ERROR                        3
#وصف_ڪريو پورٽ_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR                   4
#وصف_ڪريو پورٽ_TIN_SBP_پروگرام_يادگيري_INTEGRITY_ERROR                        5
#وصف_ڪريو پورٽ_TIN_SBP_معلومات_يادگيري_INTEGRITY_ERROR                           6

/* Assertion Trap Identifications. */
#وصف_ڪريو پورٽ_TIN_ASSERT_ARITHMETIC_حد_کان_مٿي                                1
#وصف_ڪريو پورٽ_TIN_ASSERT_STICKY_ARITHMETIC_حد_کان_مٿي                         2

/* Non-maskable Interrupt Trap Identifications. */
#وصف_ڪريو پورٽ_TIN_NMI_NON_MASKABLE_مداخلت                                0
/*---------------------------------------------------------------------------*/

فراغ vMMUTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ v_اندروني_Protection_Trap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vInstructionErrorTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vContextManagementTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vSystemBusAndPeripheralsTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vAssertionTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ v_Non_Maskable_مداخلت_Trap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

فراغ vTrapInstallHandlers( فراغ )
{
    إذا( 0 == _install_trap_handler( پورٽ_MMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورٽ_IPT_TRAP, v_اندروني_Protection_Trap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورٽ_IE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورٽ_CM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورٽ_SBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورٽ_ASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورٽ_NMI_TRAP, v_Non_Maskable_مداخلت_Trap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

فراغ vMMUTrap( صحيح iTrapIdentification )
{
    بدل( iTrapIdentification )
    {
        حالة پورٽ_TIN_MMU_VIRTUAL_پتو_FILL:
        حالة پورٽ_TIN_MMU_VIRTUAL_پتو_PROTECTION:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/

فراغ v_اندروني_Protection_Trap( صحيح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    بدل( iTrapIdentification )
    {
        حالة پورٽ_TIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        حالة پورٽ_TIN_IPT_يادگيري_PROTECTION_READ:
        /* Load word using invalid address. */

        حالة پورٽ_TIN_IPT_يادگيري_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        حالة پورٽ_TIN_IPT_يادگيري_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        حالة پورٽ_TIN_IPT_يادگيري_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        حالة پورٽ_TIN_IPT_يادگيري_PROTECTION_NULL_پتو:
        /* NULL Pointer. */

        حالة پورٽ_TIN_IPT_يادگيري_PROTECTION_GLOBAL_رجسٽر_WRITE_PROTECTION:
        /* Tried to modify a global address pointer register. */

        افتراضي:

            pxCurrentTCB[ 0 ] = __MFCR( $PCXI );
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/

فراغ vInstructionErrorTrap( صحيح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    بدل( iTrapIdentification )
    {
        حالة پورٽ_TIN_IE_ILLEGAL_OPCODE:
        حالة پورٽ_TIN_IE_UNIMPLEMENTED_OPCODE:
        حالة پورٽ_TIN_IE_INVALID_عمليو:
        حالة پورٽ_TIN_IE_معلومات_پتو_ALIGNMENT:
        حالة پورٽ_TIN_IE_INVALID_LOCAL_يادگيري_پتو:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/

فراغ vContextManagementTrap( صحيح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    بدل( iTrapIdentification )
    {
        حالة پورٽ_TIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        حالة پورٽ_TIN_CM_CALL_اونهائي_حد_کان_مٿي:
        حالة پورٽ_TIN_CM_CALL_اونهائي_UNDEFLOW:
        حالة پورٽ_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        حالة پورٽ_TIN_CM_CALL_ڍير_UNDERFLOW:
        حالة پورٽ_TIN_CM_CONTEXT_TYPE:
        حالة پورٽ_TIN_CM_NESTING_ERROR:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/

فراغ vSystemBusAndPeripheralsTrap( صحيح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    بدل( iTrapIdentification )
    {
        حالة پورٽ_TIN_SBP_پروگرام_FETCH_SYNCHRONOUS_ERROR:
        حالة پورٽ_TIN_SBP_معلومات_ACCESS_SYNCHRONOUS_ERROR:
        حالة پورٽ_TIN_SBP_معلومات_ACCESS_ASYNCHRONOUS_ERROR:
        حالة پورٽ_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        حالة پورٽ_TIN_SBP_پروگرام_يادگيري_INTEGRITY_ERROR:
        حالة پورٽ_TIN_SBP_معلومات_يادگيري_INTEGRITY_ERROR:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/

فراغ vAssertionTrap( صحيح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    بدل( iTrapIdentification )
    {
        حالة پورٽ_TIN_ASSERT_ARITHMETIC_حد_کان_مٿي:
        حالة پورٽ_TIN_ASSERT_STICKY_ARITHMETIC_حد_کان_مٿي:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/

فراغ v_Non_Maskable_مداخلت_Trap( صحيح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    بدل( iTrapIdentification )
    {
        حالة پورٽ_TIN_NMI_NON_MASKABLE_مداخلت:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/
