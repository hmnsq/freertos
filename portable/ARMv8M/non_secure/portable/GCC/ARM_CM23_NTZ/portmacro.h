/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2026 Arm Limited and/or its affiliates <open-source-office@arm.com>
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

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
/* *INDENT-ON* */

/*------------------------------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the given hardware
 * and compiler.
 *
 * These settings should not be altered.
 *------------------------------------------------------------------------------
 */

/**
 * Architecture specifics.
 */
#परिभाषय पत्तनम्_ARCH_NAME                    "Cortex-M23"
#परिभाषय पत्तनम्_HAS_ARMV8_M_MAIN_EXTENSION    0
#परिभाषय पत्तनम्_ARMV8_M_MINOR_संस्करणम्         0
#परिभाषय पत्तनम्_DONT_DISCARD                 __attribute__( ( प्रयुक्तम् ) )
#परिभाषय पत्तनम्_VALIDATED_FOR_SMP            0
/*-----------------------------------------------------------*/

/* ARMv8-M common port configurations. */
#अन्तर्भाव "portmacrocommon.h"
/*-----------------------------------------------------------*/

#यदि ( config_योग_MPU_REGIONS == 16 )
    #दोषः 16 MPU regions are not yet supported प्रति this पत्तनम्.
#यदि_अन्तः

#यदि_अपरिभाषितम् configENABLE_MVE
    #परिभाषय configENABLE_MVE    0
#नोचेद्यदि ( configENABLE_MVE != 0 )
    #दोषः configENABLE_MVE must be वामः undefined, or defined गन्तव्यम् 0 प्रति the Cortex-M23.
#यदि_अन्तः
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    __asm चञ्चल ( " cpsid i " ::: "memory" )
#परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     __asm चञ्चल ( " cpsie i " ::: "memory" )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
