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
#অন্তর্ভাব "FreeRTOS.h"

/* Machine includes */
#অন্তর্ভাব <tc1782.h>
#অন্তর্ভাব <machine/intrinsics.h>
#অন্তর্ভাব <machine/cint.h>
/*---------------------------------------------------------------------------*/

/*
 * This reference is required by the Save/Restore Context Macros.
 */
বাহ্যিক অস্থির uint32_t * pxCurrentTCB;
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
#define portMMU_TRAP                                                      0
#define portIPT_TRAP                                                      1
#define portIE_TRAP                                                       2
#define portCM_TRAP                                                       3
#define portSBP_TRAP                                                      4
#define portASSERT_TRAP                                                   5
#define portNMI_TRAP                                                      7

/* MMU Trap Identifications. */
#define portTIN_MMU_VIRTUAL_ADDRESS_FILL                                  0
#define portTIN_MMU_VIRTUAL_ADDRESS_PROTECTION                            1

/* Internal Protection Trap Identifications. */
#define portTIN_IPT_PRIVILEGED_INSTRUCTION                                1
#define portTIN_IPT_MEMORY_PROTECTION_READ                                2
#define portTIN_IPT_MEMORY_PROTECTION_WRITE                               3
#define portTIN_IPT_MEMORY_PROTECTION_EXECUTION                           4
#define portTIN_IPT_MEMORY_PROTECTION_PERIPHERAL_ACCESS                   5
#define portTIN_IPT_MEMORY_PROTECTION_NULL_ADDRESS                        6
#define portTIN_IPT_MEMORY_PROTECTION_GLOBAL_REGISTER_WRITE_PROTECTION    7

/* Instruction Error Trap Identifications. */
#define portTIN_IE_ILLEGAL_OPCODE                                         1
#define portTIN_IE_UNIMPLEMENTED_OPCODE                                   2
#define portTIN_IE_INVALID_OPERAND                                        3
#define port_TIN_IE_তথ্য_ADDRESS_ALIGNMENT                                 4
#define portTIN_IE_INVALID_LOCAL_MEMORY_ADDRESS                           5

/* Context Management Trap Identifications. */
#define portTIN_CM_FREE_CONTEXT_LIST_DEPLETION                            1
#define portTIN_CM_CALL_DEPTH_OVERFLOW                                    2
#define portTIN_CM_CALL_DEPTH_UNDEFLOW                                    3
#define portTIN_CM_FREE_CONTEXT_LIST_UNDERFLOW                            4
#define port_TIN_CM_CALL_স্তূপ_UNDERFLOW                                   5
#define portTIN_CM_CONTEXT_TYPE                                           6
#define portTIN_CM_NESTING_ERROR                                          7

/* System Bus and Peripherals Trap Identifications. */
#define portTIN_SBP_PROGRAM_FETCH_SYNCHRONOUS_ERROR                       1
#define port_TIN_SBP_তথ্য_ACCESS_SYNCHRONOUS_ERROR                         2
#define port_TIN_SBP_তথ্য_ACCESS_ASYNCHRONOUS_ERROR                        3
#define portTIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR                   4
#define portTIN_SBP_PROGRAM_MEMORY_INTEGRITY_ERROR                        5
#define port_TIN_SBP_তথ্য_MEMORY_INTEGRITY_ERROR                           6

/* Assertion Trap Identifications. */
#define portTIN_ASSERT_ARITHMETIC_OVERFLOW                                1
#define portTIN_ASSERT_STICKY_ARITHMETIC_OVERFLOW                         2

/* Non-maskable Interrupt Trap Identifications. */
#define portTIN_NMI_NON_MASKABLE_INTERRUPT                                0
/*---------------------------------------------------------------------------*/

শূন্য vMMUTrap( পূর্ণসংখ্যা iTrapIdentification ) __attribute__( ( longcall, weak ) );
শূন্য vInternalProtectionTrap( পূর্ণসংখ্যা iTrapIdentification ) __attribute__( ( longcall, weak ) );
শূন্য vInstructionErrorTrap( পূর্ণসংখ্যা iTrapIdentification ) __attribute__( ( longcall, weak ) );
শূন্য vContextManagementTrap( পূর্ণসংখ্যা iTrapIdentification ) __attribute__( ( longcall, weak ) );
শূন্য vSystemBusAndPeripheralsTrap( পূর্ণসংখ্যা iTrapIdentification ) __attribute__( ( longcall, weak ) );
শূন্য vAssertionTrap( পূর্ণসংখ্যা iTrapIdentification ) __attribute__( ( longcall, weak ) );
শূন্য vNonMaskableInterruptTrap( পূর্ণসংখ্যা iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

শূন্য vTrapInstallHandlers( শূন্য )
{
    যদি( 0 == _install_trap_handler( portMMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    যদি( 0 == _install_trap_handler( portIPT_TRAP, vInternalProtectionTrap ) )
    {
        _debug();
    }

    যদি( 0 == _install_trap_handler( portIE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    যদি( 0 == _install_trap_handler( portCM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    যদি( 0 == _install_trap_handler( portSBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    যদি( 0 == _install_trap_handler( portASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    যদি( 0 == _install_trap_handler( portNMI_TRAP, vNonMaskableInterruptTrap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

শূন্য vMMUTrap( পূর্ণসংখ্যা iTrapIdentification )
{
    নির্বাচন( iTrapIdentification )
    {
        ক্ষেত্র portTIN_MMU_VIRTUAL_ADDRESS_FILL:
        ক্ষেত্র portTIN_MMU_VIRTUAL_ADDRESS_PROTECTION:
        পূর্বনির্ধারিত:
            _debug();
            বিরতি;
    }
}
/*---------------------------------------------------------------------------*/

শূন্য vInternalProtectionTrap( পূর্ণসংখ্যা iTrapIdentification )
{
    /* Deliberate fall through to default. */
    নির্বাচন( iTrapIdentification )
    {
        ক্ষেত্র portTIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        ক্ষেত্র portTIN_IPT_MEMORY_PROTECTION_READ:
        /* Load word using invalid address. */

        ক্ষেত্র portTIN_IPT_MEMORY_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        ক্ষেত্র portTIN_IPT_MEMORY_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        ক্ষেত্র portTIN_IPT_MEMORY_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        ক্ষেত্র portTIN_IPT_MEMORY_PROTECTION_NULL_ADDRESS:
        /* NULL Pointer. */

        ক্ষেত্র portTIN_IPT_MEMORY_PROTECTION_GLOBAL_REGISTER_WRITE_PROTECTION:
        /* Tried to modify a global address pointer register. */

        পূর্বনির্ধারিত:

            pxCurrentTCB[ 0 ] = __MFCR( $PCXI );
            _debug();
            বিরতি;
    }
}
/*---------------------------------------------------------------------------*/

শূন্য vInstructionErrorTrap( পূর্ণসংখ্যা iTrapIdentification )
{
    /* Deliberate fall through to default. */
    নির্বাচন( iTrapIdentification )
    {
        ক্ষেত্র portTIN_IE_ILLEGAL_OPCODE:
        ক্ষেত্র portTIN_IE_UNIMPLEMENTED_OPCODE:
        ক্ষেত্র portTIN_IE_INVALID_OPERAND:
        ক্ষেত্র port_TIN_IE_তথ্য_ADDRESS_ALIGNMENT:
        ক্ষেত্র portTIN_IE_INVALID_LOCAL_MEMORY_ADDRESS:
        পূর্বনির্ধারিত:
            _debug();
            বিরতি;
    }
}
/*---------------------------------------------------------------------------*/

শূন্য vContextManagementTrap( পূর্ণসংখ্যা iTrapIdentification )
{
    /* Deliberate fall through to default. */
    নির্বাচন( iTrapIdentification )
    {
        ক্ষেত্র portTIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        ক্ষেত্র portTIN_CM_CALL_DEPTH_OVERFLOW:
        ক্ষেত্র portTIN_CM_CALL_DEPTH_UNDEFLOW:
        ক্ষেত্র portTIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        ক্ষেত্র port_TIN_CM_CALL_স্তূপ_UNDERFLOW:
        ক্ষেত্র portTIN_CM_CONTEXT_TYPE:
        ক্ষেত্র portTIN_CM_NESTING_ERROR:
        পূর্বনির্ধারিত:
            _debug();
            বিরতি;
    }
}
/*---------------------------------------------------------------------------*/

শূন্য vSystemBusAndPeripheralsTrap( পূর্ণসংখ্যা iTrapIdentification )
{
    /* Deliberate fall through to default. */
    নির্বাচন( iTrapIdentification )
    {
        ক্ষেত্র portTIN_SBP_PROGRAM_FETCH_SYNCHRONOUS_ERROR:
        ক্ষেত্র port_TIN_SBP_তথ্য_ACCESS_SYNCHRONOUS_ERROR:
        ক্ষেত্র port_TIN_SBP_তথ্য_ACCESS_ASYNCHRONOUS_ERROR:
        ক্ষেত্র portTIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        ক্ষেত্র portTIN_SBP_PROGRAM_MEMORY_INTEGRITY_ERROR:
        ক্ষেত্র port_TIN_SBP_তথ্য_MEMORY_INTEGRITY_ERROR:
        পূর্বনির্ধারিত:
            _debug();
            বিরতি;
    }
}
/*---------------------------------------------------------------------------*/

শূন্য vAssertionTrap( পূর্ণসংখ্যা iTrapIdentification )
{
    /* Deliberate fall through to default. */
    নির্বাচন( iTrapIdentification )
    {
        ক্ষেত্র portTIN_ASSERT_ARITHMETIC_OVERFLOW:
        ক্ষেত্র portTIN_ASSERT_STICKY_ARITHMETIC_OVERFLOW:
        পূর্বনির্ধারিত:
            _debug();
            বিরতি;
    }
}
/*---------------------------------------------------------------------------*/

শূন্য vNonMaskableInterruptTrap( পূর্ণসংখ্যা iTrapIdentification )
{
    /* Deliberate fall through to default. */
    নির্বাচন( iTrapIdentification )
    {
        ক্ষেত্র portTIN_NMI_NON_MASKABLE_INTERRUPT:
        পূর্বনির্ধারিত:
            _debug();
            বিরতি;
    }
}
/*---------------------------------------------------------------------------*/
