/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright (c) 2026 Arm Technology (China) Co., Ltd.All Rights Reserved.
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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
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

#నిర్వచితం_కాకపోతే configENABLE_MVE
    #దోషం configENABLE_MVE must be defined లోపల FreeRTOSConfig.h. సమితి_2 configENABLE_MVE గమ్యం 1 గమ్యం enable the MVE or 0 గమ్యం disable the MVE.
#అయితే_ముగింపు /* configENABLE_MVE */
/*-----------------------------------------------------------*/

/**
 * Architecture specifics.
 */
#నిర్వచించు పోర్టు_ARCH_NAME                    "STAR-MC3"
#నిర్వచించు పోర్టు_HAS_ARMV8_M_MAIN_EXTENSION    1
#నిర్వచించు పోర్టు_ARMV8_M_MINOR_సంస్కరణ         1
#నిర్వచించు పోర్టు_DONT_DISCARD                 __attribute__( ( వాడిన ) )
#నిర్వచించు పోర్టు_VALIDATED_FOR_SMP            0
/*-----------------------------------------------------------*/

/* ARMv8-M common port configurations. */
#అన్తర్భావ "portmacrocommon.h"
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    ul_సమితి_అంతరాయం_ముసుగు()
#నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     v_Clear_అంతరాయం_ముసుగు( 0 )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
