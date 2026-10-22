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
#అన్తర్భావ "FreeRTOS.h"

/* Machine includes */
#అన్తర్భావ <tc1782.h>
#అన్తర్భావ <machine/intrinsics.h>
#అన్తర్భావ <machine/cint.h>
/*---------------------------------------------------------------------------*/

/*
 * This reference is required by the Save/Restore Context Macros.
 */
బాహ్య అస్థిర uint32_t * pxCurrentTCB;
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
#నిర్వచించు పోర్టు_MMU_TRAP                                                      0
#నిర్వచించు పోర్టు_IPT_TRAP                                                      1
#నిర్వచించు పోర్టు_IE_TRAP                                                       2
#నిర్వచించు పోర్టు_CM_TRAP                                                       3
#నిర్వచించు పోర్టు_SBP_TRAP                                                      4
#నిర్వచించు పోర్టు_ASSERT_TRAP                                                   5
#నిర్వచించు పోర్టు_NMI_TRAP                                                      7

/* MMU Trap Identifications. */
#నిర్వచించు పోర్టు_TIN_MMU_VIRTUAL_చిరునామా_FILL                                  0
#నిర్వచించు పోర్టు_TIN_MMU_VIRTUAL_చిరునామా_PROTECTION                            1

/* Internal Protection Trap Identifications. */
#నిర్వచించు పోర్టు_TIN_IPT_PRIVILEGED_INSTRUCTION                                1
#నిర్వచించు పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_READ                                2
#నిర్వచించు పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_WRITE                               3
#నిర్వచించు పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_EXECUTION                           4
#నిర్వచించు పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_PERIPHERAL_ACCESS                   5
#నిర్వచించు పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_NULL_చిరునామా                        6
#నిర్వచించు పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_GLOBAL_రిజిస్టరు_WRITE_PROTECTION    7

/* Instruction Error Trap Identifications. */
#నిర్వచించు పోర్టు_TIN_IE_ILLEGAL_OPCODE                                         1
#నిర్వచించు పోర్టు_TIN_IE_UNIMPLEMENTED_OPCODE                                   2
#నిర్వచించు పోర్టు_TIN_IE_INVALID_నిర్వాహ్యం                                        3
#నిర్వచించు పోర్టు_TIN_IE_దత్తాంశం_చిరునామా_ALIGNMENT                                 4
#నిర్వచించు పోర్టు_TIN_IE_INVALID_LOCAL_జ్ఞాపకం_చిరునామా                           5

/* Context Management Trap Identifications. */
#నిర్వచించు పోర్టు_TIN_CM_FREE_CONTEXT_LIST_DEPLETION                            1
#నిర్వచించు పోర్టు_TIN_CM_CALL_లోతు_అధికప్రవాహం                                    2
#నిర్వచించు పోర్టు_TIN_CM_CALL_లోతు_UNDEFLOW                                    3
#నిర్వచించు పోర్టు_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW                            4
#నిర్వచించు పోర్టు_TIN_CM_CALL_దొంతర_UNDERFLOW                                   5
#నిర్వచించు పోర్టు_TIN_CM_CONTEXT_TYPE                                           6
#నిర్వచించు పోర్టు_TIN_CM_NESTING_ERROR                                          7

/* System Bus and Peripherals Trap Identifications. */
#నిర్వచించు పోర్టు_TIN_SBP_కార్యక్రమం_FETCH_SYNCHRONOUS_ERROR                       1
#నిర్వచించు పోర్టు_TIN_SBP_దత్తాంశం_ACCESS_SYNCHRONOUS_ERROR                         2
#నిర్వచించు పోర్టు_TIN_SBP_దత్తాంశం_ACCESS_ASYNCHRONOUS_ERROR                        3
#నిర్వచించు పోర్టు_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR                   4
#నిర్వచించు పోర్టు_TIN_SBP_కార్యక్రమం_జ్ఞాపకం_INTEGRITY_ERROR                        5
#నిర్వచించు పోర్టు_TIN_SBP_దత్తాంశం_జ్ఞాపకం_INTEGRITY_ERROR                           6

/* Assertion Trap Identifications. */
#నిర్వచించు పోర్టు_TIN_ASSERT_ARITHMETIC_అధికప్రవాహం                                1
#నిర్వచించు పోర్టు_TIN_ASSERT_STICKY_ARITHMETIC_అధికప్రవాహం                         2

/* Non-maskable Interrupt Trap Identifications. */
#నిర్వచించు పోర్టు_TIN_NMI_NON_MASKABLE_అంతరాయం                                0
/*---------------------------------------------------------------------------*/

శూన్య vMMUTrap( పూర్ణాంకం iTrapIdentification ) __attribute__( ( longcall, weak ) );
శూన్య v_అంతర్గత_Protection_Trap( పూర్ణాంకం iTrapIdentification ) __attribute__( ( longcall, weak ) );
శూన్య vInstructionErrorTrap( పూర్ణాంకం iTrapIdentification ) __attribute__( ( longcall, weak ) );
శూన్య vContextManagementTrap( పూర్ణాంకం iTrapIdentification ) __attribute__( ( longcall, weak ) );
శూన్య vSystemBusAndPeripheralsTrap( పూర్ణాంకం iTrapIdentification ) __attribute__( ( longcall, weak ) );
శూన్య vAssertionTrap( పూర్ణాంకం iTrapIdentification ) __attribute__( ( longcall, weak ) );
శూన్య v_Non_Maskable_అంతరాయం_Trap( పూర్ణాంకం iTrapIdentification ) __attribute__( ( longcall, weak ) );
/*---------------------------------------------------------------------------*/

శూన్య vTrapInstallHandlers( శూన్య )
{
    ఒకవేళ( 0 == _install_trap_handler( పోర్టు_MMU_TRAP, vMMUTrap ) )
    {
        _debug();
    }

    ఒకవేళ( 0 == _install_trap_handler( పోర్టు_IPT_TRAP, v_అంతర్గత_Protection_Trap ) )
    {
        _debug();
    }

    ఒకవేళ( 0 == _install_trap_handler( పోర్టు_IE_TRAP, vInstructionErrorTrap ) )
    {
        _debug();
    }

    ఒకవేళ( 0 == _install_trap_handler( పోర్టు_CM_TRAP, vContextManagementTrap ) )
    {
        _debug();
    }

    ఒకవేళ( 0 == _install_trap_handler( పోర్టు_SBP_TRAP, vSystemBusAndPeripheralsTrap ) )
    {
        _debug();
    }

    ఒకవేళ( 0 == _install_trap_handler( పోర్టు_ASSERT_TRAP, vAssertionTrap ) )
    {
        _debug();
    }

    ఒకవేళ( 0 == _install_trap_handler( పోర్టు_NMI_TRAP, v_Non_Maskable_అంతరాయం_Trap ) )
    {
        _debug();
    }
}
/*-----------------------------------------------------------*/

శూన్య vMMUTrap( పూర్ణాంకం iTrapIdentification )
{
    ఎంపిక( iTrapIdentification )
    {
        స్థితి పోర్టు_TIN_MMU_VIRTUAL_చిరునామా_FILL:
        స్థితి పోర్టు_TIN_MMU_VIRTUAL_చిరునామా_PROTECTION:
        అప్రమేయ:
            _debug();
            ఆపు;
    }
}
/*---------------------------------------------------------------------------*/

శూన్య v_అంతర్గత_Protection_Trap( పూర్ణాంకం iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ఎంపిక( iTrapIdentification )
    {
        స్థితి పోర్టు_TIN_IPT_PRIVILEGED_INSTRUCTION:
        /* Instruction is not allowed at current execution level, eg DISABLE at User-0. */

        స్థితి పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_READ:
        /* Load word using invalid address. */

        స్థితి పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_WRITE:
        /* Store Word using invalid address. */

        స్థితి పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_EXECUTION:
        /* PC jumped to an address outside of the valid range. */

        స్థితి పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_PERIPHERAL_ACCESS:
        /* Access to a peripheral denied at current execution level. */

        స్థితి పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_NULL_చిరునామా:
        /* NULL Pointer. */

        స్థితి పోర్టు_TIN_IPT_జ్ఞాపకం_PROTECTION_GLOBAL_రిజిస్టరు_WRITE_PROTECTION:
        /* Tried to modify a global address pointer register. */

        అప్రమేయ:

            pxCurrentTCB[ 0 ] = __MFCR( $PCXI );
            _debug();
            ఆపు;
    }
}
/*---------------------------------------------------------------------------*/

శూన్య vInstructionErrorTrap( పూర్ణాంకం iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ఎంపిక( iTrapIdentification )
    {
        స్థితి పోర్టు_TIN_IE_ILLEGAL_OPCODE:
        స్థితి పోర్టు_TIN_IE_UNIMPLEMENTED_OPCODE:
        స్థితి పోర్టు_TIN_IE_INVALID_నిర్వాహ్యం:
        స్థితి పోర్టు_TIN_IE_దత్తాంశం_చిరునామా_ALIGNMENT:
        స్థితి పోర్టు_TIN_IE_INVALID_LOCAL_జ్ఞాపకం_చిరునామా:
        అప్రమేయ:
            _debug();
            ఆపు;
    }
}
/*---------------------------------------------------------------------------*/

శూన్య vContextManagementTrap( పూర్ణాంకం iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ఎంపిక( iTrapIdentification )
    {
        స్థితి పోర్టు_TIN_CM_FREE_CONTEXT_LIST_DEPLETION:
        స్థితి పోర్టు_TIN_CM_CALL_లోతు_అధికప్రవాహం:
        స్థితి పోర్టు_TIN_CM_CALL_లోతు_UNDEFLOW:
        స్థితి పోర్టు_TIN_CM_FREE_CONTEXT_LIST_UNDERFLOW:
        స్థితి పోర్టు_TIN_CM_CALL_దొంతర_UNDERFLOW:
        స్థితి పోర్టు_TIN_CM_CONTEXT_TYPE:
        స్థితి పోర్టు_TIN_CM_NESTING_ERROR:
        అప్రమేయ:
            _debug();
            ఆపు;
    }
}
/*---------------------------------------------------------------------------*/

శూన్య vSystemBusAndPeripheralsTrap( పూర్ణాంకం iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ఎంపిక( iTrapIdentification )
    {
        స్థితి పోర్టు_TIN_SBP_కార్యక్రమం_FETCH_SYNCHRONOUS_ERROR:
        స్థితి పోర్టు_TIN_SBP_దత్తాంశం_ACCESS_SYNCHRONOUS_ERROR:
        స్థితి పోర్టు_TIN_SBP_దత్తాంశం_ACCESS_ASYNCHRONOUS_ERROR:
        స్థితి పోర్టు_TIN_SBP_COPROCESSOR_TRAP_ASYNCHRONOUS_ERROR:
        స్థితి పోర్టు_TIN_SBP_కార్యక్రమం_జ్ఞాపకం_INTEGRITY_ERROR:
        స్థితి పోర్టు_TIN_SBP_దత్తాంశం_జ్ఞాపకం_INTEGRITY_ERROR:
        అప్రమేయ:
            _debug();
            ఆపు;
    }
}
/*---------------------------------------------------------------------------*/

శూన్య vAssertionTrap( పూర్ణాంకం iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ఎంపిక( iTrapIdentification )
    {
        స్థితి పోర్టు_TIN_ASSERT_ARITHMETIC_అధికప్రవాహం:
        స్థితి పోర్టు_TIN_ASSERT_STICKY_ARITHMETIC_అధికప్రవాహం:
        అప్రమేయ:
            _debug();
            ఆపు;
    }
}
/*---------------------------------------------------------------------------*/

శూన్య v_Non_Maskable_అంతరాయం_Trap( పూర్ణాంకం iTrapIdentification )
{
    /* Deliberate fall through to default. */
    ఎంపిక( iTrapIdentification )
    {
        స్థితి పోర్టు_TIN_NMI_NON_MASKABLE_అంతరాయం:
        అప్రమేయ:
            _debug();
            ఆపు;
    }
}
/*---------------------------------------------------------------------------*/
