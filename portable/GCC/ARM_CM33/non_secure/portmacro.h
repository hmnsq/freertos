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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
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
#تعریف_کن پورت_ARCH_NAME                    "Cortex-M33"
#تعریف_کن پورت_HAS_ARMV8_M_MAIN_EXTENSION    1
#تعریف_کن پورت_ARMV8_M_MINOR_نسخه         0
#تعریف_کن پورت_DONT_DISCARD                 __attribute__( ( استفاده_شده ) )
#تعریف_کن پورت_VALIDATED_FOR_SMP            0
/*-----------------------------------------------------------*/

/* ARMv8-M common port configurations. */
#ضمن "portmacrocommon.h"
/*-----------------------------------------------------------*/

#اگر_تعریف_نشده configENABLE_MVE
    #تعریف_کن configENABLE_MVE    0
#وإلاإذا ( configENABLE_MVE != 0 )
    #خطا configENABLE_MVE must be چپ undefined, or defined مقصد 0 لكل the Cortex-M33.
#پایان_اگر
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#تعریف_کن پورت_DISABLE_INTERRUPTS()    ul_مجموعه_وقفه_ماسک()
#تعریف_کن پورت_ENABLE_INTERRUPTS()     v_Clear_وقفه_ماسک( 0 )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
