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
#अन्तर्भाव "FreeRTOS.h"

/* Machine includes */
#अन्तर्भाव <tc1782.h>
#अन्तर्भाव <machine/intrinsics.h>
#अन्तर्भाव <machine/cint.h>
/*---------------------------------------------------------------------------*/

/*
 * This reference is required by the Save/Restore Context Macros.
 */
बाह्य चञ्चल uint32_t * pxCurrentTCB;
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
#परिभाषय पत्तनम्_MMU_TRAP                                                      0
#परिभाषय पत्तनम्_IPT_TRAP                                                      1
#परिभाषय पत्तनम्_IE_TRAP                                                       2
#परिभाषय पत्तनम्_CM_TRAP                                                       3
#परिभाषय पत्तनम्_SBP_TRAP                                                      4
#परिभाषय पत्तनम्_ASSERT_TRAP                                                   5
#परिभाषय पत्तनम्_NMI_TRAP                                                      7

/* MMU Trap Identifications. */
#परिभाषय पत्तनम्_TIN_MMU_VIRTUAL_स्थानाङ्कः_FILL                                  0
#परिभाषय पत्तनम्_TIN_MMU_VIRTUAL_स्थानाङ्कः_PROTECTION                            1

/* Internal Protection Trap Identifications. */
#परिभाषय पत्तनम्_TIN_IPT_PRIVILEGED_INSTRUCTION                                1
#परिभाषय पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_READ                                2
#परिभाषय पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_WRITE                               3
#परिभाषय पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_EXECUTION                           4
#परिभाषय पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_PERIPHERAL_ACCESS                   5
#परिभाषय पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_NULL_स्थानाङ्कः                        6
#परिभाषय पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_GLOBAL_पञ्जिकाकोशः_WRITE_PROTECTION    7

/* Instruction Error Trap Identifications. */
#परिभाषय पत्तनम्_TIN_IE_ILLEGAL_OPCODE                                         1
#परिभाषय पत्तनम्_TIN_IE_UNIMPLEMENTED_OPCODE                                   2
#परिभाषय पत्तनम्_TIN_IE_INVALID_सङ्कार्यम्                                        3
#परिभाषय पत्तनम्_TIN_IE_दत्त_स्थानाङ्कः_ALIGNMENT                                 4
#परिभाषय पत्तनम्_TIN_IE_INVALID_LOCAL_स्मृतिः_स्थानाङ्कः                           5

/* Context Management Trap Identifications. */
#परिभाषय पत्तनम्_TIN_CM_FREE_CONTEXT_LIST_DEPLETION                            1
#परिभाषय पत्तनम्_TIN_CM_CALL_गभीरता_अतिप्रवाहः                                    2
#परिभाषय पत्तनम्_TIN_CM_CALL_गभीरता_UNDEFLOW                                    3
#परिभाषय पत्तनम्_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW                            4
#परिभाषय पत्तनम्_TIN_CM_CALL_राशिः_UNDERFLOW                                   5
#परिभाषय पत्तनम्_TIN_CM_CONTEXT_TYPE                                           6
#परिभाषय पत्तनम्_TIN_CM_NESTING_ERROR                                          7

/* System Bus and Peripherals Trap Identifications. */
#परिभाषय पत्तनम्_TIN_SBP_क्रमादेशः_FETCH_SYNCHRONOUS_ERROR                       1
#परिभाषय पत्तनम्_TIN_SBP_दत्त_ACCESS_SYNCHRONOUS_ERROR                         2
#परिभाषय पत्तनम्_TIN_SBP_दत्त_ACCESS_ASYNCHRONOUS_ERROR                        3
#परिभाषय पत्तनम्_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR                   4
#परिभाषय पत्तनम्_TIN_SBP_क्रमादेशः_स्मृतिः_INTEGRITY_ERROR                        5
#परिभाषय पत्तनम्_TIN_SBP_दत्त_स्मृतिः_INTEGRITY_ERROR                           6

/* Assertion Trap Identifications. */
#परिभाषय पत्तनम्_TIN_ASSERT_ARITHMETIC_अतिप्रवाहः                                1
#परिभाषय पत्तनम्_TIN_ASSERT_STICKY_ARITHMETIC_अतिप्रवाहः                         2

/* Non-maskable Interrupt Trap Identifications. */
#परिभाषय पत्तनम्_TIN_NMI_NON_MASKABLE_व्यवधानम्                                0
/*---------------------------------------------------------------------------*/

शून्य vMMUTrap( पूर्णाङ्क iTrapIdentification ) __attribute__( ( longcall, weak ) );
शून्य v_आन्तरिकम्_Protection_Trap( पूर्णाङ्क iTrapIdentification ) __attribute__( ( longcall, weak ) );
शून्य vInstructionErrorTrap( पूर्णाङ्क iTrapIdentification ) __attribute__( ( longcall, weak ) );
शून्य vContextManagementTrap( पूर्णाङ्क iTrapIdentification ) __attribute__( ( longcall, weak ) );
शून्य vSystemBusAndPeripheralsTrap( पूर्णाङ्क iTrapIdentification ) __attribute__( ( longcall, weak ) );
शून्य vAssertionTrap( पूर्णाङ्क iTrapIdentification ) __attribute__( ( longcall, weak ) );
शून्य v_Non_Maskable_व्यवधानम्_Trap( पूर्णाङ्क iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

शून्य vTrapInstallHandlers( शून्य )
{
    यदि( 0 == _install_trap_handler( पत्तनम्_MMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    यदि( 0 == _install_trap_handler( पत्तनम्_IPT_TRAP, v_आन्तरिकम्_Protection_Trap ) )
    {
        _debug();
    }

    यदि( 0 == _install_trap_handler( पत्तनम्_IE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    यदि( 0 == _install_trap_handler( पत्तनम्_CM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    यदि( 0 == _install_trap_handler( पत्तनम्_SBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    यदि( 0 == _install_trap_handler( पत्तनम्_ASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    यदि( 0 == _install_trap_handler( पत्तनम्_NMI_TRAP, v_Non_Maskable_व्यवधानम्_Trap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

शून्य vMMUTrap( पूर्णाङ्क iTrapIdentification )
{
    विकल्प( iTrapIdentification )
    {
        पक्ष पत्तनम्_TIN_MMU_VIRTUAL_स्थानाङ्कः_FILL:
        पक्ष पत्तनम्_TIN_MMU_VIRTUAL_स्थानाङ्कः_PROTECTION:
        स्वभाव:
            _debug();
            भङ्ग;
    }
}
/*---------------------------------------------------------------------------*/

शून्य v_आन्तरिकम्_Protection_Trap( पूर्णाङ्क iTrapIdentification )
{
    /* Deliberate fall through to default. */
    विकल्प( iTrapIdentification )
    {
        पक्ष पत्तनम्_TIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        पक्ष पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_READ:
        /* Load word using invalid address. */

        पक्ष पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        पक्ष पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        पक्ष पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        पक्ष पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_NULL_स्थानाङ्कः:
        /* NULL Pointer. */

        पक्ष पत्तनम्_TIN_IPT_स्मृतिः_PROTECTION_GLOBAL_पञ्जिकाकोशः_WRITE_PROTECTION:
        /* Tried to modify a global address pointer register. */

        स्वभाव:

            pxCurrentTCB[ 0 ] = __MFCR( $PCXI );
            _debug();
            भङ्ग;
    }
}
/*---------------------------------------------------------------------------*/

शून्य vInstructionErrorTrap( पूर्णाङ्क iTrapIdentification )
{
    /* Deliberate fall through to default. */
    विकल्प( iTrapIdentification )
    {
        पक्ष पत्तनम्_TIN_IE_ILLEGAL_OPCODE:
        पक्ष पत्तनम्_TIN_IE_UNIMPLEMENTED_OPCODE:
        पक्ष पत्तनम्_TIN_IE_INVALID_सङ्कार्यम्:
        पक्ष पत्तनम्_TIN_IE_दत्त_स्थानाङ्कः_ALIGNMENT:
        पक्ष पत्तनम्_TIN_IE_INVALID_LOCAL_स्मृतिः_स्थानाङ्कः:
        स्वभाव:
            _debug();
            भङ्ग;
    }
}
/*---------------------------------------------------------------------------*/

शून्य vContextManagementTrap( पूर्णाङ्क iTrapIdentification )
{
    /* Deliberate fall through to default. */
    विकल्प( iTrapIdentification )
    {
        पक्ष पत्तनम्_TIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        पक्ष पत्तनम्_TIN_CM_CALL_गभीरता_अतिप्रवाहः:
        पक्ष पत्तनम्_TIN_CM_CALL_गभीरता_UNDEFLOW:
        पक्ष पत्तनम्_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        पक्ष पत्तनम्_TIN_CM_CALL_राशिः_UNDERFLOW:
        पक्ष पत्तनम्_TIN_CM_CONTEXT_TYPE:
        पक्ष पत्तनम्_TIN_CM_NESTING_ERROR:
        स्वभाव:
            _debug();
            भङ्ग;
    }
}
/*---------------------------------------------------------------------------*/

शून्य vSystemBusAndPeripheralsTrap( पूर्णाङ्क iTrapIdentification )
{
    /* Deliberate fall through to default. */
    विकल्प( iTrapIdentification )
    {
        पक्ष पत्तनम्_TIN_SBP_क्रमादेशः_FETCH_SYNCHRONOUS_ERROR:
        पक्ष पत्तनम्_TIN_SBP_दत्त_ACCESS_SYNCHRONOUS_ERROR:
        पक्ष पत्तनम्_TIN_SBP_दत्त_ACCESS_ASYNCHRONOUS_ERROR:
        पक्ष पत्तनम्_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        पक्ष पत्तनम्_TIN_SBP_क्रमादेशः_स्मृतिः_INTEGRITY_ERROR:
        पक्ष पत्तनम्_TIN_SBP_दत्त_स्मृतिः_INTEGRITY_ERROR:
        स्वभाव:
            _debug();
            भङ्ग;
    }
}
/*---------------------------------------------------------------------------*/

शून्य vAssertionTrap( पूर्णाङ्क iTrapIdentification )
{
    /* Deliberate fall through to default. */
    विकल्प( iTrapIdentification )
    {
        पक्ष पत्तनम्_TIN_ASSERT_ARITHMETIC_अतिप्रवाहः:
        पक्ष पत्तनम्_TIN_ASSERT_STICKY_ARITHMETIC_अतिप्रवाहः:
        स्वभाव:
            _debug();
            भङ्ग;
    }
}
/*---------------------------------------------------------------------------*/

शून्य v_Non_Maskable_व्यवधानम्_Trap( पूर्णाङ्क iTrapIdentification )
{
    /* Deliberate fall through to default. */
    विकल्प( iTrapIdentification )
    {
        पक्ष पत्तनम्_TIN_NMI_NON_MASKABLE_व्यवधानम्:
        स्वभाव:
            _debug();
            भङ्ग;
    }
}
/*---------------------------------------------------------------------------*/
