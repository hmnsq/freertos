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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
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
#تعریف_کړه پورټ_ARCH_NAME                    "Cortex-M33"
#تعریف_کړه پورټ_HAS_ARMV8_M_MAIN_EXTENSION    1
#تعریف_کړه پورټ_ARMV8_M_MINOR_نسخه         0
#تعریف_کړه پورټ_DONT_DISCARD                 __attribute__( ( کارول_شوی ) )
#تعریف_کړه پورټ_VALIDATED_FOR_SMP            0
/*-----------------------------------------------------------*/

/* ARMv8-M common port configurations. */
#ضمن "portmacrocommon.h"
/*-----------------------------------------------------------*/

#که_نه_تعریف_شوی configENABLE_MVE
    #تعریف_کړه configENABLE_MVE    0
#وإلاإذا ( configENABLE_MVE != 0 )
    #تېروتنه configENABLE_MVE must be کیڼ undefined, or defined منزل 0 لكل the Cortex-M33.
#د_که_پای
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#تعریف_کړه پورټ_DISABLE_INTERRUPTS()    ul_سېټ_مداخله_ماسک()
#تعریف_کړه پورټ_ENABLE_INTERRUPTS()     v_Clear_مداخله_ماسک( 0 )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
