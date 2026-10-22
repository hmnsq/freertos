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
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"

/* Machine includes */
#ਅਨ੍ਤਰ੍ਭਾਵ <tc1782.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <machine/intrinsics.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <machine/cint.h>
/*---------------------------------------------------------------------------*/

/*
 * This reference is required by the Save/Restore Context Macros.
 */
ਬਾਹਰੀ ਅਸਥਿਰ uint32_t * pxCurrentTCB;
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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MMU_TRAP                                                      0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IPT_TRAP                                                      1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_IE_TRAP                                                       2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CM_TRAP                                                       3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SBP_TRAP                                                      4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASSERT_TRAP                                                   5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NMI_TRAP                                                      7

/* MMU Trap Identifications. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_MMU_VIRTUAL_ਪਤਾ_FILL                                  0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_MMU_VIRTUAL_ਪਤਾ_PROTECTION                            1

/* Internal Protection Trap Identifications. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IPT_PRIVILEGED_INSTRUCTION                                1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_READ                                2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_WRITE                               3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_EXECUTION                           4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_PERIPHERAL_ACCESS                   5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_NULL_ਪਤਾ                        6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_GLOBAL_ਰਜਿਸਟਰ_WRITE_PROTECTION    7

/* Instruction Error Trap Identifications. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IE_ILLEGAL_OPCODE                                         1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IE_UNIMPLEMENTED_OPCODE                                   2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IE_INVALID_ਸੰਕਾਰਜ                                        3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IE_ਅੰਕੜੇ_ਪਤਾ_ALIGNMENT                                 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_IE_INVALID_LOCAL_ਸਮ੍ਰਿਤੀ_ਪਤਾ                           5

/* Context Management Trap Identifications. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_CM_FREE_CONTEXT_LIST_DEPLETION                            1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_CM_CALL_ਡੂੰਘਾਈ_ਉਛਾਲ                                    2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_CM_CALL_ਡੂੰਘਾਈ_UNDEFLOW                                    3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW                            4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_CM_CALL_ਢੇਰ_UNDERFLOW                                   5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_CM_CONTEXT_TYPE                                           6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_CM_NESTING_ERROR                                          7

/* System Bus and Peripherals Trap Identifications. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_SBP_ਪ੍ਰੋਗਰਾਮ_FETCH_SYNCHRONOUS_ERROR                       1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_SBP_ਅੰਕੜੇ_ACCESS_SYNCHRONOUS_ERROR                         2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_SBP_ਅੰਕੜੇ_ACCESS_ASYNCHRONOUS_ERROR                        3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR                   4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_SBP_ਪ੍ਰੋਗਰਾਮ_ਸਮ੍ਰਿਤੀ_INTEGRITY_ERROR                        5
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_SBP_ਅੰਕੜੇ_ਸਮ੍ਰਿਤੀ_INTEGRITY_ERROR                           6

/* Assertion Trap Identifications. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_ASSERT_ARITHMETIC_ਉਛਾਲ                                1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_ASSERT_STICKY_ARITHMETIC_ਉਛਾਲ                         2

/* Non-maskable Interrupt Trap Identifications. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TIN_NMI_NON_MASKABLE_ਰੁਕਾਵਟ                                0
/*---------------------------------------------------------------------------*/

ਖਾਲੀ vMMUTrap( ਪੂਰਨ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ਖਾਲੀ v_ਅੰਦਰੂਨੀ_Protection_Trap( ਪੂਰਨ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ਖਾਲੀ vInstructionErrorTrap( ਪੂਰਨ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ਖਾਲੀ vContextManagementTrap( ਪੂਰਨ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ਖਾਲੀ vSystemBusAndPeripheralsTrap( ਪੂਰਨ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ਖਾਲੀ vAssertionTrap( ਪੂਰਨ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ਖਾਲੀ v_Non_Maskable_ਰੁਕਾਵਟ_Trap( ਪੂਰਨ iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

ਖਾਲੀ vTrapInstallHandlers( ਖਾਲੀ )
{
    ਜੇ( 0 == _install_trap_handler( ਪੋਰਟ_MMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    ਜੇ( 0 == _install_trap_handler( ਪੋਰਟ_IPT_TRAP, v_ਅੰਦਰੂਨੀ_Protection_Trap ) )
    {
        _debug();
    }

    ਜੇ( 0 == _install_trap_handler( ਪੋਰਟ_IE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    ਜੇ( 0 == _install_trap_handler( ਪੋਰਟ_CM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    ਜੇ( 0 == _install_trap_handler( ਪੋਰਟ_SBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    ਜੇ( 0 == _install_trap_handler( ਪੋਰਟ_ASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    ਜੇ( 0 == _install_trap_handler( ਪੋਰਟ_NMI_TRAP, v_Non_Maskable_ਰੁਕਾਵਟ_Trap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ vMMUTrap( ਪੂਰਨ iTrapIdentification )
{
    ਚੋਣ( iTrapIdentification )
    {
        ਹਾਲਤ ਪੋਰਟ_TIN_MMU_VIRTUAL_ਪਤਾ_FILL:
        ਹਾਲਤ ਪੋਰਟ_TIN_MMU_VIRTUAL_ਪਤਾ_PROTECTION:
        ਮੂਲ:
            _debug();
            ਰੋਕੋ;
    }
}
/*---------------------------------------------------------------------------*/

ਖਾਲੀ v_ਅੰਦਰੂਨੀ_Protection_Trap( ਪੂਰਨ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ਚੋਣ( iTrapIdentification )
    {
        ਹਾਲਤ ਪੋਰਟ_TIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        ਹਾਲਤ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_READ:
        /* Load word using invalid address. */

        ਹਾਲਤ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        ਹਾਲਤ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        ਹਾਲਤ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        ਹਾਲਤ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_NULL_ਪਤਾ:
        /* NULL Pointer. */

        ਹਾਲਤ ਪੋਰਟ_TIN_IPT_ਸਮ੍ਰਿਤੀ_PROTECTION_GLOBAL_ਰਜਿਸਟਰ_WRITE_PROTECTION:
        /* Tried to modify a global address pointer register. */

        ਮੂਲ:

            pxCurrentTCB[ 0 ] = __MFCR( $PCXI );
            _debug();
            ਰੋਕੋ;
    }
}
/*---------------------------------------------------------------------------*/

ਖਾਲੀ vInstructionErrorTrap( ਪੂਰਨ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ਚੋਣ( iTrapIdentification )
    {
        ਹਾਲਤ ਪੋਰਟ_TIN_IE_ILLEGAL_OPCODE:
        ਹਾਲਤ ਪੋਰਟ_TIN_IE_UNIMPLEMENTED_OPCODE:
        ਹਾਲਤ ਪੋਰਟ_TIN_IE_INVALID_ਸੰਕਾਰਜ:
        ਹਾਲਤ ਪੋਰਟ_TIN_IE_ਅੰਕੜੇ_ਪਤਾ_ALIGNMENT:
        ਹਾਲਤ ਪੋਰਟ_TIN_IE_INVALID_LOCAL_ਸਮ੍ਰਿਤੀ_ਪਤਾ:
        ਮੂਲ:
            _debug();
            ਰੋਕੋ;
    }
}
/*---------------------------------------------------------------------------*/

ਖਾਲੀ vContextManagementTrap( ਪੂਰਨ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ਚੋਣ( iTrapIdentification )
    {
        ਹਾਲਤ ਪੋਰਟ_TIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        ਹਾਲਤ ਪੋਰਟ_TIN_CM_CALL_ਡੂੰਘਾਈ_ਉਛਾਲ:
        ਹਾਲਤ ਪੋਰਟ_TIN_CM_CALL_ਡੂੰਘਾਈ_UNDEFLOW:
        ਹਾਲਤ ਪੋਰਟ_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        ਹਾਲਤ ਪੋਰਟ_TIN_CM_CALL_ਢੇਰ_UNDERFLOW:
        ਹਾਲਤ ਪੋਰਟ_TIN_CM_CONTEXT_TYPE:
        ਹਾਲਤ ਪੋਰਟ_TIN_CM_NESTING_ERROR:
        ਮੂਲ:
            _debug();
            ਰੋਕੋ;
    }
}
/*---------------------------------------------------------------------------*/

ਖਾਲੀ vSystemBusAndPeripheralsTrap( ਪੂਰਨ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ਚੋਣ( iTrapIdentification )
    {
        ਹਾਲਤ ਪੋਰਟ_TIN_SBP_ਪ੍ਰੋਗਰਾਮ_FETCH_SYNCHRONOUS_ERROR:
        ਹਾਲਤ ਪੋਰਟ_TIN_SBP_ਅੰਕੜੇ_ACCESS_SYNCHRONOUS_ERROR:
        ਹਾਲਤ ਪੋਰਟ_TIN_SBP_ਅੰਕੜੇ_ACCESS_ASYNCHRONOUS_ERROR:
        ਹਾਲਤ ਪੋਰਟ_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        ਹਾਲਤ ਪੋਰਟ_TIN_SBP_ਪ੍ਰੋਗਰਾਮ_ਸਮ੍ਰਿਤੀ_INTEGRITY_ERROR:
        ਹਾਲਤ ਪੋਰਟ_TIN_SBP_ਅੰਕੜੇ_ਸਮ੍ਰਿਤੀ_INTEGRITY_ERROR:
        ਮੂਲ:
            _debug();
            ਰੋਕੋ;
    }
}
/*---------------------------------------------------------------------------*/

ਖਾਲੀ vAssertionTrap( ਪੂਰਨ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ਚੋਣ( iTrapIdentification )
    {
        ਹਾਲਤ ਪੋਰਟ_TIN_ASSERT_ARITHMETIC_ਉਛਾਲ:
        ਹਾਲਤ ਪੋਰਟ_TIN_ASSERT_STICKY_ARITHMETIC_ਉਛਾਲ:
        ਮੂਲ:
            _debug();
            ਰੋਕੋ;
    }
}
/*---------------------------------------------------------------------------*/

ਖਾਲੀ v_Non_Maskable_ਰੁਕਾਵਟ_Trap( ਪੂਰਨ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ਚੋਣ( iTrapIdentification )
    {
        ਹਾਲਤ ਪੋਰਟ_TIN_NMI_NON_MASKABLE_ਰੁਕਾਵਟ:
        ਮੂਲ:
            _debug();
            ਰੋਕੋ;
    }
}
/*---------------------------------------------------------------------------*/
