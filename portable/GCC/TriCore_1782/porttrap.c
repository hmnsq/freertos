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
#അന്തര്ഭാവ "FreeRTOS.h"

/* Machine includes */
#അന്തര്ഭാവ <tc1782.h>
#അന്തര്ഭാവ <machine/intrinsics.h>
#അന്തര്ഭാവ <machine/cint.h>
/*---------------------------------------------------------------------------*/

/*
 * This reference is required by the Save/Restore Context Macros.
 */
ബാഹ്യ അസ്ഥിര uint32_t * pxCurrentTCB;
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
#define portTIN_IE_DATA_ADDRESS_ALIGNMENT                                 4
#define portTIN_IE_INVALID_LOCAL_MEMORY_ADDRESS                           5

/* Context Management Trap Identifications. */
#define portTIN_CM_FREE_CONTEXT_LIST_DEPLETION                            1
#define portTIN_CM_CALL_DEPTH_OVERFLOW                                    2
#define portTIN_CM_CALL_DEPTH_UNDEFLOW                                    3
#define portTIN_CM_FREE_CONTEXT_LIST_UNDERFLOW                            4
#define port_TIN_CM_CALL_അട്ടി_UNDERFLOW                                   5
#define portTIN_CM_CONTEXT_TYPE                                           6
#define portTIN_CM_NESTING_ERROR                                          7

/* System Bus and Peripherals Trap Identifications. */
#define portTIN_SBP_PROGRAM_FETCH_SYNCHRONOUS_ERROR                       1
#define portTIN_SBP_DATA_ACCESS_SYNCHRONOUS_ERROR                         2
#define portTIN_SBP_DATA_ACCESS_ASYNCHRONOUS_ERROR                        3
#define portTIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR                   4
#define portTIN_SBP_PROGRAM_MEMORY_INTEGRITY_ERROR                        5
#define portTIN_SBP_DATA_MEMORY_INTEGRITY_ERROR                           6

/* Assertion Trap Identifications. */
#define portTIN_ASSERT_ARITHMETIC_OVERFLOW                                1
#define portTIN_ASSERT_STICKY_ARITHMETIC_OVERFLOW                         2

/* Non-maskable Interrupt Trap Identifications. */
#define portTIN_NMI_NON_MASKABLE_INTERRUPT                                0
/*---------------------------------------------------------------------------*/

ശൂന്യം vMMUTrap( പൂർണ്ണസംഖ്യ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ശൂന്യം vInternalProtectionTrap( പൂർണ്ണസംഖ്യ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ശൂന്യം vInstructionErrorTrap( പൂർണ്ണസംഖ്യ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ശൂന്യം vContextManagementTrap( പൂർണ്ണസംഖ്യ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ശൂന്യം vSystemBusAndPeripheralsTrap( പൂർണ്ണസംഖ്യ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ശൂന്യം vAssertionTrap( പൂർണ്ണസംഖ്യ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ശൂന്യം vNonMaskableInterruptTrap( പൂർണ്ണസംഖ്യ iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

ശൂന്യം vTrapInstallHandlers( ശൂന്യം )
{
    എങ്കിൽ( 0 == _install_trap_handler( portMMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    എങ്കിൽ( 0 == _install_trap_handler( portIPT_TRAP, vInternalProtectionTrap ) )
    {
        _debug();
    }

    എങ്കിൽ( 0 == _install_trap_handler( portIE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    എങ്കിൽ( 0 == _install_trap_handler( portCM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    എങ്കിൽ( 0 == _install_trap_handler( portSBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    എങ്കിൽ( 0 == _install_trap_handler( portASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    എങ്കിൽ( 0 == _install_trap_handler( portNMI_TRAP, vNonMaskableInterruptTrap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

ശൂന്യം vMMUTrap( പൂർണ്ണസംഖ്യ iTrapIdentification )
{
    തിരഞ്ഞെടുപ്പ്( iTrapIdentification )
    {
        അവസ്ഥ portTIN_MMU_VIRTUAL_ADDRESS_FILL:
        അവസ്ഥ portTIN_MMU_VIRTUAL_ADDRESS_PROTECTION:
        സ്ഥിരസ്ഥിതി:
            _debug();
            നിർത്തുക;
    }
}
/*---------------------------------------------------------------------------*/

ശൂന്യം vInternalProtectionTrap( പൂർണ്ണസംഖ്യ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    തിരഞ്ഞെടുപ്പ്( iTrapIdentification )
    {
        അവസ്ഥ portTIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        അവസ്ഥ portTIN_IPT_MEMORY_PROTECTION_READ:
        /* Load word using invalid address. */

        അവസ്ഥ portTIN_IPT_MEMORY_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        അവസ്ഥ portTIN_IPT_MEMORY_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        അവസ്ഥ portTIN_IPT_MEMORY_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        അവസ്ഥ portTIN_IPT_MEMORY_PROTECTION_NULL_ADDRESS:
        /* NULL Pointer. */

        അവസ്ഥ portTIN_IPT_MEMORY_PROTECTION_GLOBAL_REGISTER_WRITE_PROTECTION:
        /* Tried to modify a global address pointer register. */

        സ്ഥിരസ്ഥിതി:

            pxCurrentTCB[ 0 ] = __MFCR( $PCXI );
            _debug();
            നിർത്തുക;
    }
}
/*---------------------------------------------------------------------------*/

ശൂന്യം vInstructionErrorTrap( പൂർണ്ണസംഖ്യ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    തിരഞ്ഞെടുപ്പ്( iTrapIdentification )
    {
        അവസ്ഥ portTIN_IE_ILLEGAL_OPCODE:
        അവസ്ഥ portTIN_IE_UNIMPLEMENTED_OPCODE:
        അവസ്ഥ portTIN_IE_INVALID_OPERAND:
        അവസ്ഥ portTIN_IE_DATA_ADDRESS_ALIGNMENT:
        അവസ്ഥ portTIN_IE_INVALID_LOCAL_MEMORY_ADDRESS:
        സ്ഥിരസ്ഥിതി:
            _debug();
            നിർത്തുക;
    }
}
/*---------------------------------------------------------------------------*/

ശൂന്യം vContextManagementTrap( പൂർണ്ണസംഖ്യ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    തിരഞ്ഞെടുപ്പ്( iTrapIdentification )
    {
        അവസ്ഥ portTIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        അവസ്ഥ portTIN_CM_CALL_DEPTH_OVERFLOW:
        അവസ്ഥ portTIN_CM_CALL_DEPTH_UNDEFLOW:
        അവസ്ഥ portTIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        അവസ്ഥ port_TIN_CM_CALL_അട്ടി_UNDERFLOW:
        അവസ്ഥ portTIN_CM_CONTEXT_TYPE:
        അവസ്ഥ portTIN_CM_NESTING_ERROR:
        സ്ഥിരസ്ഥിതി:
            _debug();
            നിർത്തുക;
    }
}
/*---------------------------------------------------------------------------*/

ശൂന്യം vSystemBusAndPeripheralsTrap( പൂർണ്ണസംഖ്യ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    തിരഞ്ഞെടുപ്പ്( iTrapIdentification )
    {
        അവസ്ഥ portTIN_SBP_PROGRAM_FETCH_SYNCHRONOUS_ERROR:
        അവസ്ഥ portTIN_SBP_DATA_ACCESS_SYNCHRONOUS_ERROR:
        അവസ്ഥ portTIN_SBP_DATA_ACCESS_ASYNCHRONOUS_ERROR:
        അവസ്ഥ portTIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        അവസ്ഥ portTIN_SBP_PROGRAM_MEMORY_INTEGRITY_ERROR:
        അവസ്ഥ portTIN_SBP_DATA_MEMORY_INTEGRITY_ERROR:
        സ്ഥിരസ്ഥിതി:
            _debug();
            നിർത്തുക;
    }
}
/*---------------------------------------------------------------------------*/

ശൂന്യം vAssertionTrap( പൂർണ്ണസംഖ്യ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    തിരഞ്ഞെടുപ്പ്( iTrapIdentification )
    {
        അവസ്ഥ portTIN_ASSERT_ARITHMETIC_OVERFLOW:
        അവസ്ഥ portTIN_ASSERT_STICKY_ARITHMETIC_OVERFLOW:
        സ്ഥിരസ്ഥിതി:
            _debug();
            നിർത്തുക;
    }
}
/*---------------------------------------------------------------------------*/

ശൂന്യം vNonMaskableInterruptTrap( പൂർണ്ണസംഖ്യ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    തിരഞ്ഞെടുപ്പ്( iTrapIdentification )
    {
        അവസ്ഥ portTIN_NMI_NON_MASKABLE_INTERRUPT:
        സ്ഥിരസ്ഥിതി:
            _debug();
            നിർത്തുക;
    }
}
/*---------------------------------------------------------------------------*/
