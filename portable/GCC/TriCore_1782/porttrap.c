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
#تعریف_کړه پورټ_MMU_TRAP                                                      0
#تعریف_کړه پورټ_IPT_TRAP                                                      1
#تعریف_کړه پورټ_IE_TRAP                                                       2
#تعریف_کړه پورټ_CM_TRAP                                                       3
#تعریف_کړه پورټ_SBP_TRAP                                                      4
#تعریف_کړه پورټ_ASSERT_TRAP                                                   5
#تعریف_کړه پورټ_NMI_TRAP                                                      7

/* MMU Trap Identifications. */
#تعریف_کړه پورټ_TIN_MMU_VIRTUAL_پته_FILL                                  0
#تعریف_کړه پورټ_TIN_MMU_VIRTUAL_پته_PROTECTION                            1

/* Internal Protection Trap Identifications. */
#تعریف_کړه پورټ_TIN_IPT_PRIVILEGED_INSTRUCTION                                1
#تعریف_کړه پورټ_TIN_IPT_حافظه_PROTECTION_READ                                2
#تعریف_کړه پورټ_TIN_IPT_حافظه_PROTECTION_WRITE                               3
#تعریف_کړه پورټ_TIN_IPT_حافظه_PROTECTION_EXECUTION                           4
#تعریف_کړه پورټ_TIN_IPT_حافظه_PROTECTION_PERIPHERAL_ACCESS                   5
#تعریف_کړه پورټ_TIN_IPT_حافظه_PROTECTION_NULL_پته                        6
#تعریف_کړه پورټ_TIN_IPT_حافظه_PROTECTION_GLOBAL_ثبتوونکی_WRITE_PROTECTION    7

/* Instruction Error Trap Identifications. */
#تعریف_کړه پورټ_TIN_IE_ILLEGAL_OPCODE                                         1
#تعریف_کړه پورټ_TIN_IE_UNIMPLEMENTED_OPCODE                                   2
#تعریف_کړه پورټ_TIN_IE_INVALID_عملوند                                        3
#تعریف_کړه پورټ_TIN_IE_معلومات_پته_ALIGNMENT                                 4
#تعریف_کړه پورټ_TIN_IE_INVALID_LOCAL_حافظه_پته                           5

/* Context Management Trap Identifications. */
#تعریف_کړه پورټ_TIN_CM_FREE_CONTEXT_LIST_DEPLETION                            1
#تعریف_کړه پورټ_TIN_CM_CALL_ژوروالی_ډکېدنه                                    2
#تعریف_کړه پورټ_TIN_CM_CALL_ژوروالی_UNDEFLOW                                    3
#تعریف_کړه پورټ_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW                            4
#تعریف_کړه پورټ_TIN_CM_CALL_ډېری_UNDERFLOW                                   5
#تعریف_کړه پورټ_TIN_CM_CONTEXT_TYPE                                           6
#تعریف_کړه پورټ_TIN_CM_NESTING_ERROR                                          7

/* System Bus and Peripherals Trap Identifications. */
#تعریف_کړه پورټ_TIN_SBP_پروګرام_FETCH_SYNCHRONOUS_ERROR                       1
#تعریف_کړه پورټ_TIN_SBP_معلومات_ACCESS_SYNCHRONOUS_ERROR                         2
#تعریف_کړه پورټ_TIN_SBP_معلومات_ACCESS_ASYNCHRONOUS_ERROR                        3
#تعریف_کړه پورټ_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR                   4
#تعریف_کړه پورټ_TIN_SBP_پروګرام_حافظه_INTEGRITY_ERROR                        5
#تعریف_کړه پورټ_TIN_SBP_معلومات_حافظه_INTEGRITY_ERROR                           6

/* Assertion Trap Identifications. */
#تعریف_کړه پورټ_TIN_ASSERT_ARITHMETIC_ډکېدنه                                1
#تعریف_کړه پورټ_TIN_ASSERT_STICKY_ARITHMETIC_ډکېدنه                         2

/* Non-maskable Interrupt Trap Identifications. */
#تعریف_کړه پورټ_TIN_NMI_NON_MASKABLE_مداخله                                0
/*---------------------------------------------------------------------------*/

فراغ vMMUTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ v_دننی_Protection_Trap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vInstructionErrorTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vContextManagementTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vSystemBusAndPeripheralsTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vAssertionTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ v_Non_Maskable_مداخله_Trap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

فراغ vTrapInstallHandlers( فراغ )
{
    إذا( 0 == _install_trap_handler( پورټ_MMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورټ_IPT_TRAP, v_دننی_Protection_Trap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورټ_IE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورټ_CM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورټ_SBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورټ_ASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورټ_NMI_TRAP, v_Non_Maskable_مداخله_Trap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

فراغ vMMUTrap( صحيح iTrapIdentification )
{
    بدل( iTrapIdentification )
    {
        حالة پورټ_TIN_MMU_VIRTUAL_پته_FILL:
        حالة پورټ_TIN_MMU_VIRTUAL_پته_PROTECTION:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/

فراغ v_دننی_Protection_Trap( صحيح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    بدل( iTrapIdentification )
    {
        حالة پورټ_TIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        حالة پورټ_TIN_IPT_حافظه_PROTECTION_READ:
        /* Load word using invalid address. */

        حالة پورټ_TIN_IPT_حافظه_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        حالة پورټ_TIN_IPT_حافظه_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        حالة پورټ_TIN_IPT_حافظه_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        حالة پورټ_TIN_IPT_حافظه_PROTECTION_NULL_پته:
        /* NULL Pointer. */

        حالة پورټ_TIN_IPT_حافظه_PROTECTION_GLOBAL_ثبتوونکی_WRITE_PROTECTION:
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
        حالة پورټ_TIN_IE_ILLEGAL_OPCODE:
        حالة پورټ_TIN_IE_UNIMPLEMENTED_OPCODE:
        حالة پورټ_TIN_IE_INVALID_عملوند:
        حالة پورټ_TIN_IE_معلومات_پته_ALIGNMENT:
        حالة پورټ_TIN_IE_INVALID_LOCAL_حافظه_پته:
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
        حالة پورټ_TIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        حالة پورټ_TIN_CM_CALL_ژوروالی_ډکېدنه:
        حالة پورټ_TIN_CM_CALL_ژوروالی_UNDEFLOW:
        حالة پورټ_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        حالة پورټ_TIN_CM_CALL_ډېری_UNDERFLOW:
        حالة پورټ_TIN_CM_CONTEXT_TYPE:
        حالة پورټ_TIN_CM_NESTING_ERROR:
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
        حالة پورټ_TIN_SBP_پروګرام_FETCH_SYNCHRONOUS_ERROR:
        حالة پورټ_TIN_SBP_معلومات_ACCESS_SYNCHRONOUS_ERROR:
        حالة پورټ_TIN_SBP_معلومات_ACCESS_ASYNCHRONOUS_ERROR:
        حالة پورټ_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        حالة پورټ_TIN_SBP_پروګرام_حافظه_INTEGRITY_ERROR:
        حالة پورټ_TIN_SBP_معلومات_حافظه_INTEGRITY_ERROR:
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
        حالة پورټ_TIN_ASSERT_ARITHMETIC_ډکېدنه:
        حالة پورټ_TIN_ASSERT_STICKY_ARITHMETIC_ډکېدنه:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/

فراغ v_Non_Maskable_مداخله_Trap( صحيح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    بدل( iTrapIdentification )
    {
        حالة پورټ_TIN_NMI_NON_MASKABLE_مداخله:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/
