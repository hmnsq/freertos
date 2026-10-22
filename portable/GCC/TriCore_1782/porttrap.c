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
#شامل "FreeRTOS.h"

/* Machine includes */
#شامل <tc1782.h>
#شامل <machine/intrinsics.h>
#شامل <machine/cint.h>
/*---------------------------------------------------------------------------*/

/*
 * This reference is required by the Save/Restore Context Macros.
 */
خارجی متلون uint32_t * pxCurrentTCB;
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
#تعریف_کرو پورٹ_MMU_TRAP                                                      0
#تعریف_کرو پورٹ_IPT_TRAP                                                      1
#تعریف_کرو پورٹ_IE_TRAP                                                       2
#تعریف_کرو پورٹ_CM_TRAP                                                       3
#تعریف_کرو پورٹ_SBP_TRAP                                                      4
#تعریف_کرو پورٹ_ASSERT_TRAP                                                   5
#تعریف_کرو پورٹ_NMI_TRAP                                                      7

/* MMU Trap Identifications. */
#تعریف_کرو پورٹ_TIN_MMU_VIRTUAL_پتہ_FILL                                  0
#تعریف_کرو پورٹ_TIN_MMU_VIRTUAL_پتہ_PROTECTION                            1

/* Internal Protection Trap Identifications. */
#تعریف_کرو پورٹ_TIN_IPT_PRIVILEGED_INSTRUCTION                                1
#تعریف_کرو پورٹ_TIN_IPT_حافظہ_PROTECTION_READ                                2
#تعریف_کرو پورٹ_TIN_IPT_حافظہ_PROTECTION_WRITE                               3
#تعریف_کرو پورٹ_TIN_IPT_حافظہ_PROTECTION_EXECUTION                           4
#تعریف_کرو پورٹ_TIN_IPT_حافظہ_PROTECTION_PERIPHERAL_ACCESS                   5
#تعریف_کرو پورٹ_TIN_IPT_حافظہ_PROTECTION_NULL_پتہ                        6
#تعریف_کرو پورٹ_TIN_IPT_حافظہ_PROTECTION_GLOBAL_رجسٹر_WRITE_PROTECTION    7

/* Instruction Error Trap Identifications. */
#تعریف_کرو پورٹ_TIN_IE_ILLEGAL_OPCODE                                         1
#تعریف_کرو پورٹ_TIN_IE_UNIMPLEMENTED_OPCODE                                   2
#تعریف_کرو پورٹ_TIN_IE_INVALID_عملیہ                                        3
#تعریف_کرو پورٹ_TIN_IE_ڈیٹا_پتہ_ALIGNMENT                                 4
#تعریف_کرو پورٹ_TIN_IE_INVALID_LOCAL_حافظہ_پتہ                           5

/* Context Management Trap Identifications. */
#تعریف_کرو پورٹ_TIN_CM_FREE_CONTEXT_LIST_DEPLETION                            1
#تعریف_کرو پورٹ_TIN_CM_CALL_گہرائی_حد_سے_تجاوز                                    2
#تعریف_کرو پورٹ_TIN_CM_CALL_گہرائی_UNDEFLOW                                    3
#تعریف_کرو پورٹ_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW                            4
#تعریف_کرو پورٹ_TIN_CM_CALL_ڈھیر_UNDERFLOW                                   5
#تعریف_کرو پورٹ_TIN_CM_CONTEXT_TYPE                                           6
#تعریف_کرو پورٹ_TIN_CM_NESTING_ERROR                                          7

/* System Bus and Peripherals Trap Identifications. */
#تعریف_کرو پورٹ_TIN_SBP_پروگرام_FETCH_SYNCHRONOUS_ERROR                       1
#تعریف_کرو پورٹ_TIN_SBP_ڈیٹا_ACCESS_SYNCHRONOUS_ERROR                         2
#تعریف_کرو پورٹ_TIN_SBP_ڈیٹا_ACCESS_ASYNCHRONOUS_ERROR                        3
#تعریف_کرو پورٹ_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR                   4
#تعریف_کرو پورٹ_TIN_SBP_پروگرام_حافظہ_INTEGRITY_ERROR                        5
#تعریف_کرو پورٹ_TIN_SBP_ڈیٹا_حافظہ_INTEGRITY_ERROR                           6

/* Assertion Trap Identifications. */
#تعریف_کرو پورٹ_TIN_ASSERT_ARITHMETIC_حد_سے_تجاوز                                1
#تعریف_کرو پورٹ_TIN_ASSERT_STICKY_ARITHMETIC_حد_سے_تجاوز                         2

/* Non-maskable Interrupt Trap Identifications. */
#تعریف_کرو پورٹ_TIN_NMI_NON_MASKABLE_مداخلت                                0
/*---------------------------------------------------------------------------*/

خالی vMMUTrap( صحیح iTrapIdentification ) __attribute__( ( longcall, weak ) );
خالی v_اندرونی_Protection_Trap( صحیح iTrapIdentification ) __attribute__( ( longcall, weak ) );
خالی vInstructionErrorTrap( صحیح iTrapIdentification ) __attribute__( ( longcall, weak ) );
خالی vContextManagementTrap( صحیح iTrapIdentification ) __attribute__( ( longcall, weak ) );
خالی vSystemBusAndPeripheralsTrap( صحیح iTrapIdentification ) __attribute__( ( longcall, weak ) );
خالی vAssertionTrap( صحیح iTrapIdentification ) __attribute__( ( longcall, weak ) );
خالی v_Non_Maskable_مداخلت_Trap( صحیح iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

خالی vTrapInstallHandlers( خالی )
{
    اگر( 0 == _install_trap_handler( پورٹ_MMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    اگر( 0 == _install_trap_handler( پورٹ_IPT_TRAP, v_اندرونی_Protection_Trap ) )
    {
        _debug();
    }

    اگر( 0 == _install_trap_handler( پورٹ_IE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    اگر( 0 == _install_trap_handler( پورٹ_CM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    اگر( 0 == _install_trap_handler( پورٹ_SBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    اگر( 0 == _install_trap_handler( پورٹ_ASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    اگر( 0 == _install_trap_handler( پورٹ_NMI_TRAP, v_Non_Maskable_مداخلت_Trap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

خالی vMMUTrap( صحیح iTrapIdentification )
{
    انتخاب( iTrapIdentification )
    {
        حالت پورٹ_TIN_MMU_VIRTUAL_پتہ_FILL:
        حالت پورٹ_TIN_MMU_VIRTUAL_پتہ_PROTECTION:
        طےشدہ:
            _debug();
            توڑو;
    }
}
/*---------------------------------------------------------------------------*/

خالی v_اندرونی_Protection_Trap( صحیح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    انتخاب( iTrapIdentification )
    {
        حالت پورٹ_TIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        حالت پورٹ_TIN_IPT_حافظہ_PROTECTION_READ:
        /* Load word using invalid address. */

        حالت پورٹ_TIN_IPT_حافظہ_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        حالت پورٹ_TIN_IPT_حافظہ_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        حالت پورٹ_TIN_IPT_حافظہ_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        حالت پورٹ_TIN_IPT_حافظہ_PROTECTION_NULL_پتہ:
        /* NULL Pointer. */

        حالت پورٹ_TIN_IPT_حافظہ_PROTECTION_GLOBAL_رجسٹر_WRITE_PROTECTION:
        /* Tried to modify a global address pointer register. */

        طےشدہ:

            pxCurrentTCB[ 0 ] = __MFCR( $PCXI );
            _debug();
            توڑو;
    }
}
/*---------------------------------------------------------------------------*/

خالی vInstructionErrorTrap( صحیح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    انتخاب( iTrapIdentification )
    {
        حالت پورٹ_TIN_IE_ILLEGAL_OPCODE:
        حالت پورٹ_TIN_IE_UNIMPLEMENTED_OPCODE:
        حالت پورٹ_TIN_IE_INVALID_عملیہ:
        حالت پورٹ_TIN_IE_ڈیٹا_پتہ_ALIGNMENT:
        حالت پورٹ_TIN_IE_INVALID_LOCAL_حافظہ_پتہ:
        طےشدہ:
            _debug();
            توڑو;
    }
}
/*---------------------------------------------------------------------------*/

خالی vContextManagementTrap( صحیح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    انتخاب( iTrapIdentification )
    {
        حالت پورٹ_TIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        حالت پورٹ_TIN_CM_CALL_گہرائی_حد_سے_تجاوز:
        حالت پورٹ_TIN_CM_CALL_گہرائی_UNDEFLOW:
        حالت پورٹ_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        حالت پورٹ_TIN_CM_CALL_ڈھیر_UNDERFLOW:
        حالت پورٹ_TIN_CM_CONTEXT_TYPE:
        حالت پورٹ_TIN_CM_NESTING_ERROR:
        طےشدہ:
            _debug();
            توڑو;
    }
}
/*---------------------------------------------------------------------------*/

خالی vSystemBusAndPeripheralsTrap( صحیح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    انتخاب( iTrapIdentification )
    {
        حالت پورٹ_TIN_SBP_پروگرام_FETCH_SYNCHRONOUS_ERROR:
        حالت پورٹ_TIN_SBP_ڈیٹا_ACCESS_SYNCHRONOUS_ERROR:
        حالت پورٹ_TIN_SBP_ڈیٹا_ACCESS_ASYNCHRONOUS_ERROR:
        حالت پورٹ_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        حالت پورٹ_TIN_SBP_پروگرام_حافظہ_INTEGRITY_ERROR:
        حالت پورٹ_TIN_SBP_ڈیٹا_حافظہ_INTEGRITY_ERROR:
        طےشدہ:
            _debug();
            توڑو;
    }
}
/*---------------------------------------------------------------------------*/

خالی vAssertionTrap( صحیح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    انتخاب( iTrapIdentification )
    {
        حالت پورٹ_TIN_ASSERT_ARITHMETIC_حد_سے_تجاوز:
        حالت پورٹ_TIN_ASSERT_STICKY_ARITHMETIC_حد_سے_تجاوز:
        طےشدہ:
            _debug();
            توڑو;
    }
}
/*---------------------------------------------------------------------------*/

خالی v_Non_Maskable_مداخلت_Trap( صحیح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    انتخاب( iTrapIdentification )
    {
        حالت پورٹ_TIN_NMI_NON_MASKABLE_مداخلت:
        طےشدہ:
            _debug();
            توڑو;
    }
}
/*---------------------------------------------------------------------------*/
