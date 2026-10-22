/*
 * SPDX-FileCopyrightText: 2015-2019 Cadence Design Systems, Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * SPDX-FileContributor: 2016-2022 Espressif Systems (Shanghai) CO LTD
 */

/*
 * Copyright (c) 2015-2019 Cadence Design Systems, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*******************************************************************************
*
*       XTENSA INITIALIZATION ROUTINES CODED IN C
*
*  This file contains miscellaneous Xtensa RTOS-generic initialization functions
*  that are implemented in C.
*
*******************************************************************************/


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XT_BOARD
    #ಅನ್ತರ್ಭಾವ "xtensa/xtbsp.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "xtensa_rtos.h"
#ಅನ್ತರ್ಭಾವ "sdkconfig.h"
#ಅನ್ತರ್ಭಾವ "esp_idf_version.h"
#ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ < ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )
    #ಅನ್ತರ್ಭಾವ    "esp_clk.h"
#ಇಲ್ಲದಿದ್ದರೆ
    #ಆದರೆ CONFIG_IDF_ಗುರಿ_ESP32
        #ಅನ್ತರ್ಭಾವ "esp32/clk.h"
    #ಅಥವಾಆದರೆ CONFIG_IDF_ಗುರಿ_ESP32_S2
        #ಅನ್ತರ್ಭಾವ "esp32s2/clk.h"
    #ಅಥವಾಆದರೆ CONFIG_IDF_ಗುರಿ_ESP32_S3
        #ಅನ್ತರ್ಭಾವ "esp32s3/clk.h"
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ XT_RTOS_TIMER_INT

    ಚಿಹ್ನೆರಹಿತ xt_tick_ಭಾಜಕ = 0; /* cached number of cycles per tick */

    ಶೂನ್ಯ xt_tick_ಭಾಜಕ_init( ಶೂನ್ಯ )
    {
        xt_tick_ಭಾಜಕ = esp_clk_cpu_freq() / XT_TICK_ಪ್ರತಿ_SEC;
    }

/* Deprecated, to be removed */
    ಪೂರ್ಣಾಂಕ xt_clock_freq( ಶೂನ್ಯ )
    {
        ಹಿಂತಿರುಗಿ esp_clk_cpu_freq();
    }

#ಆದರೆ_ಅಂತ್ಯ /* XT_RTOS_TIMER_INT */
