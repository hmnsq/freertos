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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"

/* Machine includes */
#ಅನ್ತರ್ಭಾವ <tc1782.h>
#ಅನ್ತರ್ಭಾವ <machine/intrinsics.h>
#ಅನ್ತರ್ಭಾವ <machine/cint.h>
/*---------------------------------------------------------------------------*/

/*
 * This reference is required by the Save/Restore Context Macros.
 */
ಬಾಹ್ಯ ಅಸ್ಥಿರ uint32_t * pxCurrentTCB;
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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MMU_TRAP                                                      0
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IPT_TRAP                                                      1
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_IE_TRAP                                                       2
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CM_TRAP                                                       3
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SBP_TRAP                                                      4
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASSERT_TRAP                                                   5
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NMI_TRAP                                                      7

/* MMU Trap Identifications. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_MMU_VIRTUAL_ವಿಳಾಸ_FILL                                  0
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_MMU_VIRTUAL_ವಿಳಾಸ_PROTECTION                            1

/* Internal Protection Trap Identifications. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IPT_PRIVILEGED_INSTRUCTION                                1
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_READ                                2
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_WRITE                               3
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_EXECUTION                           4
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_PERIPHERAL_ACCESS                   5
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_NULL_ವಿಳಾಸ                        6
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_GLOBAL_ರಿಜಿಸ್ಟರ್_WRITE_PROTECTION    7

/* Instruction Error Trap Identifications. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IE_ILLEGAL_OPCODE                                         1
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IE_UNIMPLEMENTED_OPCODE                                   2
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IE_INVALID_ಕಾರ್ಯಾಂಶ                                        3
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IE_ದತ್ತಾಂಶ_ವಿಳಾಸ_ALIGNMENT                                 4
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_IE_INVALID_LOCAL_ಸ್ಮರಣೆ_ವಿಳಾಸ                           5

/* Context Management Trap Identifications. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_CM_FREE_CONTEXT_LIST_DEPLETION                            1
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_CM_CALL_ಆಳ_ಅತಿಪ್ರವಾಹ                                    2
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_CM_CALL_ಆಳ_UNDEFLOW                                    3
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW                            4
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_CM_CALL_ರಾಶಿ_UNDERFLOW                                   5
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_CM_CONTEXT_TYPE                                           6
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_CM_NESTING_ERROR                                          7

/* System Bus and Peripherals Trap Identifications. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_SBP_ಕಾರ್ಯಕ್ರಮ_FETCH_SYNCHRONOUS_ERROR                       1
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_SBP_ದತ್ತಾಂಶ_ACCESS_SYNCHRONOUS_ERROR                         2
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_SBP_ದತ್ತಾಂಶ_ACCESS_ASYNCHRONOUS_ERROR                        3
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR                   4
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_SBP_ಕಾರ್ಯಕ್ರಮ_ಸ್ಮರಣೆ_INTEGRITY_ERROR                        5
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_SBP_ದತ್ತಾಂಶ_ಸ್ಮರಣೆ_INTEGRITY_ERROR                           6

/* Assertion Trap Identifications. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_ASSERT_ARITHMETIC_ಅತಿಪ್ರವಾಹ                                1
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_ASSERT_STICKY_ARITHMETIC_ಅತಿಪ್ರವಾಹ                         2

/* Non-maskable Interrupt Trap Identifications. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TIN_NMI_NON_MASKABLE_ಅಡಚಣೆ                                0
/*---------------------------------------------------------------------------*/

ಶೂನ್ಯ vMMUTrap( ಪೂರ್ಣಾಂಕ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ಶೂನ್ಯ v_ಆಂತರಿಕ_Protection_Trap( ಪೂರ್ಣಾಂಕ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ಶೂನ್ಯ vInstructionErrorTrap( ಪೂರ್ಣಾಂಕ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ಶೂನ್ಯ vContextManagementTrap( ಪೂರ್ಣಾಂಕ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ಶೂನ್ಯ vSystemBusAndPeripheralsTrap( ಪೂರ್ಣಾಂಕ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ಶೂನ್ಯ vAssertionTrap( ಪೂರ್ಣಾಂಕ iTrapIdentification ) __attribute__( ( longcall, weak ) );
ಶೂನ್ಯ v_Non_Maskable_ಅಡಚಣೆ_Trap( ಪೂರ್ಣಾಂಕ iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

ಶೂನ್ಯ vTrapInstallHandlers( ಶೂನ್ಯ )
{
    ಆದರೆ( 0 == _install_trap_handler( ಪೋರ್ಟ್_MMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    ಆದರೆ( 0 == _install_trap_handler( ಪೋರ್ಟ್_IPT_TRAP, v_ಆಂತರಿಕ_Protection_Trap ) )
    {
        _debug();
    }

    ಆದರೆ( 0 == _install_trap_handler( ಪೋರ್ಟ್_IE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    ಆದರೆ( 0 == _install_trap_handler( ಪೋರ್ಟ್_CM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    ಆದರೆ( 0 == _install_trap_handler( ಪೋರ್ಟ್_SBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    ಆದರೆ( 0 == _install_trap_handler( ಪೋರ್ಟ್_ASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    ಆದರೆ( 0 == _install_trap_handler( ಪೋರ್ಟ್_NMI_TRAP, v_Non_Maskable_ಅಡಚಣೆ_Trap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vMMUTrap( ಪೂರ್ಣಾಂಕ iTrapIdentification )
{
    ಆಯ್ಕೆ( iTrapIdentification )
    {
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_MMU_VIRTUAL_ವಿಳಾಸ_FILL:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_MMU_VIRTUAL_ವಿಳಾಸ_PROTECTION:
        ಪೂರ್ವನಿಯೋಜಿತ:
            _debug();
            ನಿಲ್ಲಿಸು;
    }
}
/*---------------------------------------------------------------------------*/

ಶೂನ್ಯ v_ಆಂತರಿಕ_Protection_Trap( ಪೂರ್ಣಾಂಕ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ಆಯ್ಕೆ( iTrapIdentification )
    {
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_READ:
        /* Load word using invalid address. */

        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_NULL_ವಿಳಾಸ:
        /* NULL Pointer. */

        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IPT_ಸ್ಮರಣೆ_PROTECTION_GLOBAL_ರಿಜಿಸ್ಟರ್_WRITE_PROTECTION:
        /* Tried to modify a global address pointer register. */

        ಪೂರ್ವನಿಯೋಜಿತ:

            pxCurrentTCB[ 0 ] = __MFCR( $PCXI );
            _debug();
            ನಿಲ್ಲಿಸು;
    }
}
/*---------------------------------------------------------------------------*/

ಶೂನ್ಯ vInstructionErrorTrap( ಪೂರ್ಣಾಂಕ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ಆಯ್ಕೆ( iTrapIdentification )
    {
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IE_ILLEGAL_OPCODE:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IE_UNIMPLEMENTED_OPCODE:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IE_INVALID_ಕಾರ್ಯಾಂಶ:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IE_ದತ್ತಾಂಶ_ವಿಳಾಸ_ALIGNMENT:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_IE_INVALID_LOCAL_ಸ್ಮರಣೆ_ವಿಳಾಸ:
        ಪೂರ್ವನಿಯೋಜಿತ:
            _debug();
            ನಿಲ್ಲಿಸು;
    }
}
/*---------------------------------------------------------------------------*/

ಶೂನ್ಯ vContextManagementTrap( ಪೂರ್ಣಾಂಕ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ಆಯ್ಕೆ( iTrapIdentification )
    {
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_CM_CALL_ಆಳ_ಅತಿಪ್ರವಾಹ:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_CM_CALL_ಆಳ_UNDEFLOW:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_CM_CALL_ರಾಶಿ_UNDERFLOW:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_CM_CONTEXT_TYPE:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_CM_NESTING_ERROR:
        ಪೂರ್ವನಿಯೋಜಿತ:
            _debug();
            ನಿಲ್ಲಿಸು;
    }
}
/*---------------------------------------------------------------------------*/

ಶೂನ್ಯ vSystemBusAndPeripheralsTrap( ಪೂರ್ಣಾಂಕ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ಆಯ್ಕೆ( iTrapIdentification )
    {
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_SBP_ಕಾರ್ಯಕ್ರಮ_FETCH_SYNCHRONOUS_ERROR:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_SBP_ದತ್ತಾಂಶ_ACCESS_SYNCHRONOUS_ERROR:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_SBP_ದತ್ತಾಂಶ_ACCESS_ASYNCHRONOUS_ERROR:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_SBP_ಕಾರ್ಯಕ್ರಮ_ಸ್ಮರಣೆ_INTEGRITY_ERROR:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_SBP_ದತ್ತಾಂಶ_ಸ್ಮರಣೆ_INTEGRITY_ERROR:
        ಪೂರ್ವನಿಯೋಜಿತ:
            _debug();
            ನಿಲ್ಲಿಸು;
    }
}
/*---------------------------------------------------------------------------*/

ಶೂನ್ಯ vAssertionTrap( ಪೂರ್ಣಾಂಕ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ಆಯ್ಕೆ( iTrapIdentification )
    {
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_ASSERT_ARITHMETIC_ಅತಿಪ್ರವಾಹ:
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_ASSERT_STICKY_ARITHMETIC_ಅತಿಪ್ರವಾಹ:
        ಪೂರ್ವನಿಯೋಜಿತ:
            _debug();
            ನಿಲ್ಲಿಸು;
    }
}
/*---------------------------------------------------------------------------*/

ಶೂನ್ಯ v_Non_Maskable_ಅಡಚಣೆ_Trap( ಪೂರ್ಣಾಂಕ iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ಆಯ್ಕೆ( iTrapIdentification )
    {
        ಸ್ಥಿತಿ ಪೋರ್ಟ್_TIN_NMI_NON_MASKABLE_ಅಡಚಣೆ:
        ಪೂರ್ವನಿಯೋಜಿತ:
            _debug();
            ನಿಲ್ಲಿಸು;
    }
}
/*---------------------------------------------------------------------------*/
