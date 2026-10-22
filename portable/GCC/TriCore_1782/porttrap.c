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
#அந்தர்பாவ "FreeRTOS.h"

/* Machine includes */
#அந்தர்பாவ <tc1782.h>
#அந்தர்பாவ <machine/intrinsics.h>
#அந்தர்பாவ <machine/cint.h>
/*---------------------------------------------------------------------------*/

/*
 * This reference is required by the Save/Restore Context Macros.
 */
வெளி நிலையற்ற uint32_t * pxCurrentTCB;
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
#define port_TIN_CM_CALL_அடுக்கு_UNDERFLOW                                   5
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

வெறுமை vMMUTrap( முழு iTrapIdentification ) __attribute__( ( longcall, weak ) );
வெறுமை vInternalProtectionTrap( முழு iTrapIdentification ) __attribute__( ( longcall, weak ) );
வெறுமை vInstructionErrorTrap( முழு iTrapIdentification ) __attribute__( ( longcall, weak ) );
வெறுமை vContextManagementTrap( முழு iTrapIdentification ) __attribute__( ( longcall, weak ) );
வெறுமை vSystemBusAndPeripheralsTrap( முழு iTrapIdentification ) __attribute__( ( longcall, weak ) );
வெறுமை vAssertionTrap( முழு iTrapIdentification ) __attribute__( ( longcall, weak ) );
வெறுமை vNonMaskableInterruptTrap( முழு iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

வெறுமை vTrapInstallHandlers( வெறுமை )
{
    எனில்( 0 == _install_trap_handler( portMMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    எனில்( 0 == _install_trap_handler( portIPT_TRAP, vInternalProtectionTrap ) )
    {
        _debug();
    }

    எனில்( 0 == _install_trap_handler( portIE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    எனில்( 0 == _install_trap_handler( portCM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    எனில்( 0 == _install_trap_handler( portSBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    எனில்( 0 == _install_trap_handler( portASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    எனில்( 0 == _install_trap_handler( portNMI_TRAP, vNonMaskableInterruptTrap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

வெறுமை vMMUTrap( முழு iTrapIdentification )
{
    தேர்வு( iTrapIdentification )
    {
        நிலை portTIN_MMU_VIRTUAL_ADDRESS_FILL:
        நிலை portTIN_MMU_VIRTUAL_ADDRESS_PROTECTION:
        இயல்பு:
            _debug();
            நிறுத்து;
    }
}
/*---------------------------------------------------------------------------*/

வெறுமை vInternalProtectionTrap( முழு iTrapIdentification )
{
    /* Deliberate fall through to default. */
    தேர்வு( iTrapIdentification )
    {
        நிலை portTIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        நிலை portTIN_IPT_MEMORY_PROTECTION_READ:
        /* Load word using invalid address. */

        நிலை portTIN_IPT_MEMORY_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        நிலை portTIN_IPT_MEMORY_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        நிலை portTIN_IPT_MEMORY_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        நிலை portTIN_IPT_MEMORY_PROTECTION_NULL_ADDRESS:
        /* NULL Pointer. */

        நிலை portTIN_IPT_MEMORY_PROTECTION_GLOBAL_REGISTER_WRITE_PROTECTION:
        /* Tried to modify a global address pointer register. */

        இயல்பு:

            pxCurrentTCB[ 0 ] = __MFCR( $PCXI );
            _debug();
            நிறுத்து;
    }
}
/*---------------------------------------------------------------------------*/

வெறுமை vInstructionErrorTrap( முழு iTrapIdentification )
{
    /* Deliberate fall through to default. */
    தேர்வு( iTrapIdentification )
    {
        நிலை portTIN_IE_ILLEGAL_OPCODE:
        நிலை portTIN_IE_UNIMPLEMENTED_OPCODE:
        நிலை portTIN_IE_INVALID_OPERAND:
        நிலை portTIN_IE_DATA_ADDRESS_ALIGNMENT:
        நிலை portTIN_IE_INVALID_LOCAL_MEMORY_ADDRESS:
        இயல்பு:
            _debug();
            நிறுத்து;
    }
}
/*---------------------------------------------------------------------------*/

வெறுமை vContextManagementTrap( முழு iTrapIdentification )
{
    /* Deliberate fall through to default. */
    தேர்வு( iTrapIdentification )
    {
        நிலை portTIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        நிலை portTIN_CM_CALL_DEPTH_OVERFLOW:
        நிலை portTIN_CM_CALL_DEPTH_UNDEFLOW:
        நிலை portTIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        நிலை port_TIN_CM_CALL_அடுக்கு_UNDERFLOW:
        நிலை portTIN_CM_CONTEXT_TYPE:
        நிலை portTIN_CM_NESTING_ERROR:
        இயல்பு:
            _debug();
            நிறுத்து;
    }
}
/*---------------------------------------------------------------------------*/

வெறுமை vSystemBusAndPeripheralsTrap( முழு iTrapIdentification )
{
    /* Deliberate fall through to default. */
    தேர்வு( iTrapIdentification )
    {
        நிலை portTIN_SBP_PROGRAM_FETCH_SYNCHRONOUS_ERROR:
        நிலை portTIN_SBP_DATA_ACCESS_SYNCHRONOUS_ERROR:
        நிலை portTIN_SBP_DATA_ACCESS_ASYNCHRONOUS_ERROR:
        நிலை portTIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        நிலை portTIN_SBP_PROGRAM_MEMORY_INTEGRITY_ERROR:
        நிலை portTIN_SBP_DATA_MEMORY_INTEGRITY_ERROR:
        இயல்பு:
            _debug();
            நிறுத்து;
    }
}
/*---------------------------------------------------------------------------*/

வெறுமை vAssertionTrap( முழு iTrapIdentification )
{
    /* Deliberate fall through to default. */
    தேர்வு( iTrapIdentification )
    {
        நிலை portTIN_ASSERT_ARITHMETIC_OVERFLOW:
        நிலை portTIN_ASSERT_STICKY_ARITHMETIC_OVERFLOW:
        இயல்பு:
            _debug();
            நிறுத்து;
    }
}
/*---------------------------------------------------------------------------*/

வெறுமை vNonMaskableInterruptTrap( முழு iTrapIdentification )
{
    /* Deliberate fall through to default. */
    தேர்வு( iTrapIdentification )
    {
        நிலை portTIN_NMI_NON_MASKABLE_INTERRUPT:
        இயல்பு:
            _debug();
            நிறுத்து;
    }
}
/*---------------------------------------------------------------------------*/
