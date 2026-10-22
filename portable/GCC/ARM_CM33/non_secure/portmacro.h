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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ARCH_NAME                    "Cortex-M33"
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_HAS_ARMV8_M_MAIN_EXTENSION    1
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ARMV8_M_MINOR_ಆವೃತ್ತಿ         0
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DONT_DISCARD                 __attribute__( ( ಬಳಸಿದ ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_VALIDATED_FOR_SMP            0
/*-----------------------------------------------------------*/

/* ARMv8-M common port configurations. */
#ಅನ್ತರ್ಭಾವ "portmacrocommon.h"
/*-----------------------------------------------------------*/

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configENABLE_MVE
    #ವ್ಯಾಖ್ಯಾನಿಸು configENABLE_MVE    0
#ಅಥವಾಆದರೆ ( configENABLE_MVE != 0 )
    #ದೋಷ configENABLE_MVE must be ಎಡ undefined, or defined ಗಮ್ಯ 0 ಗಾಗಿ the Cortex-M33.
#ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/**
 * @brief Critical section management.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()    ul_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ()
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()     v_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( 0 )
/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
