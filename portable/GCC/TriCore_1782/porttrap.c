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
#تعریف_کن پورت_MMU_TRAP                                                      0
#تعریف_کن پورت_IPT_TRAP                                                      1
#تعریف_کن پورت_IE_TRAP                                                       2
#تعریف_کن پورت_CM_TRAP                                                       3
#تعریف_کن پورت_SBP_TRAP                                                      4
#تعریف_کن پورت_ASSERT_TRAP                                                   5
#تعریف_کن پورت_NMI_TRAP                                                      7

/* MMU Trap Identifications. */
#تعریف_کن پورت_TIN_MMU_VIRTUAL_آدرس_FILL                                  0
#تعریف_کن پورت_TIN_MMU_VIRTUAL_آدرس_PROTECTION                            1

/* Internal Protection Trap Identifications. */
#تعریف_کن پورت_TIN_IPT_PRIVILEGED_INSTRUCTION                                1
#تعریف_کن پورت_TIN_IPT_حافظه_PROTECTION_READ                                2
#تعریف_کن پورت_TIN_IPT_حافظه_PROTECTION_WRITE                               3
#تعریف_کن پورت_TIN_IPT_حافظه_PROTECTION_EXECUTION                           4
#تعریف_کن پورت_TIN_IPT_حافظه_PROTECTION_PERIPHERAL_ACCESS                   5
#تعریف_کن پورت_TIN_IPT_حافظه_PROTECTION_NULL_آدرس                        6
#تعریف_کن پورت_TIN_IPT_حافظه_PROTECTION_GLOBAL_ثبات_WRITE_PROTECTION    7

/* Instruction Error Trap Identifications. */
#تعریف_کن پورت_TIN_IE_ILLEGAL_OPCODE                                         1
#تعریف_کن پورت_TIN_IE_UNIMPLEMENTED_OPCODE                                   2
#تعریف_کن پورت_TIN_IE_INVALID_عملوند                                        3
#تعریف_کن پورت_TIN_IE_داده_آدرس_ALIGNMENT                                 4
#تعریف_کن پورت_TIN_IE_INVALID_LOCAL_حافظه_آدرس                           5

/* Context Management Trap Identifications. */
#تعریف_کن پورت_TIN_CM_FREE_CONTEXT_LIST_DEPLETION                            1
#تعریف_کن پورت_TIN_CM_CALL_عمق_سرریز                                    2
#تعریف_کن پورت_TIN_CM_CALL_عمق_UNDEFLOW                                    3
#تعریف_کن پورت_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW                            4
#تعریف_کن پورت_TIN_CM_CALL_پشته_UNDERFLOW                                   5
#تعریف_کن پورت_TIN_CM_CONTEXT_TYPE                                           6
#تعریف_کن پورت_TIN_CM_NESTING_ERROR                                          7

/* System Bus and Peripherals Trap Identifications. */
#تعریف_کن پورت_TIN_SBP_برنامه_FETCH_SYNCHRONOUS_ERROR                       1
#تعریف_کن پورت_TIN_SBP_داده_ACCESS_SYNCHRONOUS_ERROR                         2
#تعریف_کن پورت_TIN_SBP_داده_ACCESS_ASYNCHRONOUS_ERROR                        3
#تعریف_کن پورت_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR                   4
#تعریف_کن پورت_TIN_SBP_برنامه_حافظه_INTEGRITY_ERROR                        5
#تعریف_کن پورت_TIN_SBP_داده_حافظه_INTEGRITY_ERROR                           6

/* Assertion Trap Identifications. */
#تعریف_کن پورت_TIN_ASSERT_ARITHMETIC_سرریز                                1
#تعریف_کن پورت_TIN_ASSERT_STICKY_ARITHMETIC_سرریز                         2

/* Non-maskable Interrupt Trap Identifications. */
#تعریف_کن پورت_TIN_NMI_NON_MASKABLE_وقفه                                0
/*---------------------------------------------------------------------------*/

فراغ vMMUTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ v_داخلی_Protection_Trap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vInstructionErrorTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vContextManagementTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vSystemBusAndPeripheralsTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ vAssertionTrap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
فراغ v_Non_Maskable_وقفه_Trap( صحيح iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

فراغ vTrapInstallHandlers( فراغ )
{
    إذا( 0 == _install_trap_handler( پورت_MMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورت_IPT_TRAP, v_داخلی_Protection_Trap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورت_IE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورت_CM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورت_SBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورت_ASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    إذا( 0 == _install_trap_handler( پورت_NMI_TRAP, v_Non_Maskable_وقفه_Trap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

فراغ vMMUTrap( صحيح iTrapIdentification )
{
    بدل( iTrapIdentification )
    {
        حالة پورت_TIN_MMU_VIRTUAL_آدرس_FILL:
        حالة پورت_TIN_MMU_VIRTUAL_آدرس_PROTECTION:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/

فراغ v_داخلی_Protection_Trap( صحيح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    بدل( iTrapIdentification )
    {
        حالة پورت_TIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        حالة پورت_TIN_IPT_حافظه_PROTECTION_READ:
        /* Load word using invalid address. */

        حالة پورت_TIN_IPT_حافظه_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        حالة پورت_TIN_IPT_حافظه_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        حالة پورت_TIN_IPT_حافظه_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        حالة پورت_TIN_IPT_حافظه_PROTECTION_NULL_آدرس:
        /* NULL Pointer. */

        حالة پورت_TIN_IPT_حافظه_PROTECTION_GLOBAL_ثبات_WRITE_PROTECTION:
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
        حالة پورت_TIN_IE_ILLEGAL_OPCODE:
        حالة پورت_TIN_IE_UNIMPLEMENTED_OPCODE:
        حالة پورت_TIN_IE_INVALID_عملوند:
        حالة پورت_TIN_IE_داده_آدرس_ALIGNMENT:
        حالة پورت_TIN_IE_INVALID_LOCAL_حافظه_آدرس:
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
        حالة پورت_TIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        حالة پورت_TIN_CM_CALL_عمق_سرریز:
        حالة پورت_TIN_CM_CALL_عمق_UNDEFLOW:
        حالة پورت_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        حالة پورت_TIN_CM_CALL_پشته_UNDERFLOW:
        حالة پورت_TIN_CM_CONTEXT_TYPE:
        حالة پورت_TIN_CM_NESTING_ERROR:
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
        حالة پورت_TIN_SBP_برنامه_FETCH_SYNCHRONOUS_ERROR:
        حالة پورت_TIN_SBP_داده_ACCESS_SYNCHRONOUS_ERROR:
        حالة پورت_TIN_SBP_داده_ACCESS_ASYNCHRONOUS_ERROR:
        حالة پورت_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        حالة پورت_TIN_SBP_برنامه_حافظه_INTEGRITY_ERROR:
        حالة پورت_TIN_SBP_داده_حافظه_INTEGRITY_ERROR:
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
        حالة پورت_TIN_ASSERT_ARITHMETIC_سرریز:
        حالة پورت_TIN_ASSERT_STICKY_ARITHMETIC_سرریز:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/

فراغ v_Non_Maskable_وقفه_Trap( صحيح iTrapIdentification )
{
    /* Deliberate fall through to default. */
    بدل( iTrapIdentification )
    {
        حالة پورت_TIN_NMI_NON_MASKABLE_وقفه:
        افتراضي:
            _debug();
            اكسر;
    }
}
/*---------------------------------------------------------------------------*/
