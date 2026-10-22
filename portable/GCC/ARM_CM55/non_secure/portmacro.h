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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
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

#جيڪڏهن_وصف_نه_ٿيل configENABLE_MVE
    #غلطي configENABLE_MVE must be defined اندريون FreeRTOSConfig.h. سيٽ_2 configENABLE_MVE منزل 1 منزل enable the MVE or 0 منزل disable the MVE.
#جيڪڏهن_پورو /* configENABLE_MVE */
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#وصف_ڪريو پورٽ_ARCH_NAME                    "Cortex-M55"
#وصف_ڪريو پورٽ_HAS_ARMV8_M_MAIN_EXTENSION    1
#وصف_ڪريو پورٽ_ARMV8_M_MINOR_نسخو         1
#وصف_ڪريو پورٽ_DONT_DISCARD                 __attribute__( ( استعمال_ٿيل ) )
#وصف_ڪريو پورٽ_VALIDATED_FOR_SMP            0
/*-----------------------------------------------------------*/

/* ARMv8-M common port configurations. */
#ضمن "portmacrocommon.h"
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    ul_سيٽ_مداخلت_نقاب()
#وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     v_Clear_مداخلت_نقاب( 0 )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
