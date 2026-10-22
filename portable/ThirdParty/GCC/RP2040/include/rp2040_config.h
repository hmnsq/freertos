/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: MIT AND BSD-3-Clause
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
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ RP2040_CONFIG_H
#ವ್ಯಾಖ್ಯಾನಿಸು RP2040_CONFIG_H

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

/* configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 means set the exception handlers dynamically on cores
 * that need them in case the user has set up distinct vector table offsets per core
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configUSE_DYNAMIC_EXCEPTION_HANDLERS
    #ಆದರೆ defined( PICO_NO_RAM_ಸದಿಶ_ಕೋಷ್ಟಕ ) && ( PICO_NO_RAM_ಸದಿಶ_ಕೋಷ್ಟಕ == 1 )
        #ವ್ಯಾಖ್ಯಾನಿಸು configUSE_DYNAMIC_EXCEPTION_HANDLERS    0
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು configUSE_DYNAMIC_EXCEPTION_HANDLERS    1
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_sync
 * sem/mutex/queue etc. will work correctly when called from FreeRTOS tasks
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configSUPPORT_PICO_SYNC_INTEROP
    #ಆದರೆ LIB_PICO_SYNC
        #ವ್ಯಾಖ್ಯಾನಿಸು configSUPPORT_PICO_SYNC_INTEROP    1
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_time
 * sleep_ms/sleep_us/sleep_until will work correctly when called from FreeRTOS
 * tasks, and will actually block at the FreeRTOS level
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_SUPPORT_PICO_ಸಮಯ_INTEROP
    #ಆದರೆ LIB_PICO_ಸಮಯ
        #ವ್ಯಾಖ್ಯಾನಿಸು config_SUPPORT_PICO_ಸಮಯ_INTEROP    1
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ ( config_ಸಂಖ್ಯೆ_ದ_CORES > 1 )

/* configTICK_CORE indicates which core should handle the SysTick
 * interrupts */
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configTICK_CORE
        #ವ್ಯಾಖ್ಯಾನಿಸು configTICK_CORE    0
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

/* This SMP port requires two spin locks, which are claimed from the SDK.
 * the spin lock numbers to be used are defined statically and defaulted here
 * to the values nominally set aside for RTOS by the SDK */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configSMP_SPINLOCK_0
    #ವ್ಯಾಖ್ಯಾನಿಸು configSMP_SPINLOCK_0    PICO_SPINLOCK_ID_OS1
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ configSMP_SPINLOCK_1
    #ವ್ಯಾಖ್ಯಾನಿಸು configSMP_SPINLOCK_1    PICO_SPINLOCK_ID_OS2
#ಆದರೆ_ಅಂತ್ಯ

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* ifndef RP2040_CONFIG_H */
