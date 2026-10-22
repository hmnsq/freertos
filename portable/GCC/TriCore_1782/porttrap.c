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
#समावेश "FreeRTOS.h"

/* Machine includes */
#समावेश <tc1782.h>
#समावेश <machine/intrinsics.h>
#समावेश <machine/cint.h>
/*---------------------------------------------------------------------------*/

/*
 * This reference is required by the Save/Restore Context Macros.
 */
बाह्य अस्थिर uint32_t * pxCurrentTCB;
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
#घोषणा portMMU_TRAP                                                      0
#घोषणा portIPT_TRAP                                                      1
#घोषणा portIE_TRAP                                                       2
#घोषणा portCM_TRAP                                                       3
#घोषणा portSBP_TRAP                                                      4
#घोषणा portASSERT_TRAP                                                   5
#घोषणा portNMI_TRAP                                                      7

/* MMU Trap Identifications. */
#घोषणा portTIN_MMU_VIRTUAL_ADDRESS_FILL                                  0
#घोषणा portTIN_MMU_VIRTUAL_ADDRESS_PROTECTION                            1

/* Internal Protection Trap Identifications. */
#घोषणा portTIN_IPT_PRIVILEGED_INSTRUCTION                                1
#घोषणा portTIN_IPT_MEMORY_PROTECTION_READ                                2
#घोषणा portTIN_IPT_MEMORY_PROTECTION_WRITE                               3
#घोषणा portTIN_IPT_MEMORY_PROTECTION_EXECUTION                           4
#घोषणा portTIN_IPT_MEMORY_PROTECTION_PERIPHERAL_ACCESS                   5
#घोषणा portTIN_IPT_MEMORY_PROTECTION_NULL_ADDRESS                        6
#घोषणा portTIN_IPT_MEMORY_PROTECTION_GLOBAL_REGISTER_WRITE_PROTECTION    7

/* Instruction Error Trap Identifications. */
#घोषणा portTIN_IE_ILLEGAL_OPCODE                                         1
#घोषणा portTIN_IE_UNIMPLEMENTED_OPCODE                                   2
#घोषणा portTIN_IE_INVALID_OPERAND                                        3
#घोषणा port_TIN_IE_तथ्य_ADDRESS_ALIGNMENT                                 4
#घोषणा portTIN_IE_INVALID_LOCAL_MEMORY_ADDRESS                           5

/* Context Management Trap Identifications. */
#घोषणा portTIN_CM_FREE_CONTEXT_LIST_DEPLETION                            1
#घोषणा portTIN_CM_CALL_DEPTH_OVERFLOW                                    2
#घोषणा portTIN_CM_CALL_DEPTH_UNDEFLOW                                    3
#घोषणा portTIN_CM_FREE_CONTEXT_LIST_UNDERFLOW                            4
#घोषणा port_TIN_CM_CALL_ढेर_UNDERFLOW                                   5
#घोषणा portTIN_CM_CONTEXT_TYPE                                           6
#घोषणा portTIN_CM_NESTING_ERROR                                          7

/* System Bus and Peripherals Trap Identifications. */
#घोषणा portTIN_SBP_PROGRAM_FETCH_SYNCHRONOUS_ERROR                       1
#घोषणा port_TIN_SBP_तथ्य_ACCESS_SYNCHRONOUS_ERROR                         2
#घोषणा port_TIN_SBP_तथ्य_ACCESS_ASYNCHRONOUS_ERROR                        3
#घोषणा portTIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR                   4
#घोषणा portTIN_SBP_PROGRAM_MEMORY_INTEGRITY_ERROR                        5
#घोषणा port_TIN_SBP_तथ्य_MEMORY_INTEGRITY_ERROR                           6

/* Assertion Trap Identifications. */
#घोषणा portTIN_ASSERT_ARITHMETIC_OVERFLOW                                1
#घोषणा portTIN_ASSERT_STICKY_ARITHMETIC_OVERFLOW                         2

/* Non-maskable Interrupt Trap Identifications. */
#घोषणा portTIN_NMI_NON_MASKABLE_INTERRUPT                                0
/*---------------------------------------------------------------------------*/

व्योम vMMUTrap( पूर्णांक iTrapIdentification ) __attribute__( ( longcall, weak ) );
व्योम vInternalProtectionTrap( पूर्णांक iTrapIdentification ) __attribute__( ( longcall, weak ) );
व्योम vInstructionErrorTrap( पूर्णांक iTrapIdentification ) __attribute__( ( longcall, weak ) );
व्योम vContextManagementTrap( पूर्णांक iTrapIdentification ) __attribute__( ( longcall, weak ) );
व्योम vSystemBusAndPeripheralsTrap( पूर्णांक iTrapIdentification ) __attribute__( ( longcall, weak ) );
व्योम vAssertionTrap( पूर्णांक iTrapIdentification ) __attribute__( ( longcall, weak ) );
व्योम vNonMaskableInterruptTrap( पूर्णांक iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

व्योम vTrapInstallHandlers( व्योम )
{
    अगर( 0 == _install_trap_handler( portMMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    अगर( 0 == _install_trap_handler( portIPT_TRAP, vInternalProtectionTrap ) )
    {
        _debug();
    }

    अगर( 0 == _install_trap_handler( portIE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    अगर( 0 == _install_trap_handler( portCM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    अगर( 0 == _install_trap_handler( portSBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    अगर( 0 == _install_trap_handler( portASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    अगर( 0 == _install_trap_handler( portNMI_TRAP, vNonMaskableInterruptTrap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

व्योम vMMUTrap( पूर्णांक iTrapIdentification )
{
    चयन( iTrapIdentification )
    {
        हाल portTIN_MMU_VIRTUAL_ADDRESS_FILL:
        हाल portTIN_MMU_VIRTUAL_ADDRESS_PROTECTION:
        शेष:
            _debug();
            अवरोध;
    }
}
/*---------------------------------------------------------------------------*/

व्योम vInternalProtectionTrap( पूर्णांक iTrapIdentification )
{
    /* Deliberate fall through to default. */
    चयन( iTrapIdentification )
    {
        हाल portTIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        हाल portTIN_IPT_MEMORY_PROTECTION_READ:
        /* Load word using invalid address. */

        हाल portTIN_IPT_MEMORY_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        हाल portTIN_IPT_MEMORY_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        हाल portTIN_IPT_MEMORY_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        हाल portTIN_IPT_MEMORY_PROTECTION_NULL_ADDRESS:
        /* NULL Pointer. */

        हाल portTIN_IPT_MEMORY_PROTECTION_GLOBAL_REGISTER_WRITE_PROTECTION:
        /* Tried to modify a global address pointer register. */

        शेष:

            pxCurrentTCB[ 0 ] = __MFCR( $PCXI );
            _debug();
            अवरोध;
    }
}
/*---------------------------------------------------------------------------*/

व्योम vInstructionErrorTrap( पूर्णांक iTrapIdentification )
{
    /* Deliberate fall through to default. */
    चयन( iTrapIdentification )
    {
        हाल portTIN_IE_ILLEGAL_OPCODE:
        हाल portTIN_IE_UNIMPLEMENTED_OPCODE:
        हाल portTIN_IE_INVALID_OPERAND:
        हाल port_TIN_IE_तथ्य_ADDRESS_ALIGNMENT:
        हाल portTIN_IE_INVALID_LOCAL_MEMORY_ADDRESS:
        शेष:
            _debug();
            अवरोध;
    }
}
/*---------------------------------------------------------------------------*/

व्योम vContextManagementTrap( पूर्णांक iTrapIdentification )
{
    /* Deliberate fall through to default. */
    चयन( iTrapIdentification )
    {
        हाल portTIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        हाल portTIN_CM_CALL_DEPTH_OVERFLOW:
        हाल portTIN_CM_CALL_DEPTH_UNDEFLOW:
        हाल portTIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        हाल port_TIN_CM_CALL_ढेर_UNDERFLOW:
        हाल portTIN_CM_CONTEXT_TYPE:
        हाल portTIN_CM_NESTING_ERROR:
        शेष:
            _debug();
            अवरोध;
    }
}
/*---------------------------------------------------------------------------*/

व्योम vSystemBusAndPeripheralsTrap( पूर्णांक iTrapIdentification )
{
    /* Deliberate fall through to default. */
    चयन( iTrapIdentification )
    {
        हाल portTIN_SBP_PROGRAM_FETCH_SYNCHRONOUS_ERROR:
        हाल port_TIN_SBP_तथ्य_ACCESS_SYNCHRONOUS_ERROR:
        हाल port_TIN_SBP_तथ्य_ACCESS_ASYNCHRONOUS_ERROR:
        हाल portTIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        हाल portTIN_SBP_PROGRAM_MEMORY_INTEGRITY_ERROR:
        हाल port_TIN_SBP_तथ्य_MEMORY_INTEGRITY_ERROR:
        शेष:
            _debug();
            अवरोध;
    }
}
/*---------------------------------------------------------------------------*/

व्योम vAssertionTrap( पूर्णांक iTrapIdentification )
{
    /* Deliberate fall through to default. */
    चयन( iTrapIdentification )
    {
        हाल portTIN_ASSERT_ARITHMETIC_OVERFLOW:
        हाल portTIN_ASSERT_STICKY_ARITHMETIC_OVERFLOW:
        शेष:
            _debug();
            अवरोध;
    }
}
/*---------------------------------------------------------------------------*/

व्योम vNonMaskableInterruptTrap( पूर्णांक iTrapIdentification )
{
    /* Deliberate fall through to default. */
    चयन( iTrapIdentification )
    {
        हाल portTIN_NMI_NON_MASKABLE_INTERRUPT:
        शेष:
            _debug();
            अवरोध;
    }
}
/*---------------------------------------------------------------------------*/
