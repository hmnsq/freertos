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

#यदि_अपरिभाषितम् RP2040_CONFIG_H
#परिभाषय RP2040_CONFIG_H

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
/* *INDENT-ON* */

/* configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 means set the exception handlers dynamically on cores
 * that need them in case the user has set up distinct vector table offsets per core
 */
#यदि_अपरिभाषितम् configUSE_DYNAMIC_EXCEPTION_HANDLERS
    #यदि defined( PICO_NO_RAM_सदिशम्_सारणी ) && ( PICO_NO_RAM_सदिशम्_सारणी == 1 )
        #परिभाषय configUSE_DYNAMIC_EXCEPTION_HANDLERS    0
    #अन्यथा
        #परिभाषय configUSE_DYNAMIC_EXCEPTION_HANDLERS    1
    #यदि_अन्तः
#यदि_अन्तः

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_sync
 * sem/mutex/queue etc. will work correctly when called from FreeRTOS tasks
 */
#यदि_अपरिभाषितम् configSUPPORT_PICO_SYNC_INTEROP
    #यदि LIB_PICO_SYNC
        #परिभाषय configSUPPORT_PICO_SYNC_INTEROP    1
    #यदि_अन्तः
#यदि_अन्तः

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_time
 * sleep_ms/sleep_us/sleep_until will work correctly when called from FreeRTOS
 * tasks, and will actually block at the FreeRTOS level
 */
#यदि_अपरिभाषितम् configSUPPORT_PICO_TIME_INTEROP
    #यदि LIB_PICO_TIME
        #परिभाषय configSUPPORT_PICO_TIME_INTEROP    1
    #यदि_अन्तः
#यदि_अन्तः

#यदि ( config_सङ्ख्या_सम्बन्धि_CORES > 1 )

/* configTICK_CORE indicates which core should handle the SysTick
 * interrupts */
    #यदि_अपरिभाषितम् configTICK_CORE
        #परिभाषय configTICK_CORE    0
    #यदि_अन्तः
#यदि_अन्तः

/* This SMP port requires two spin locks, which are claimed from the SDK.
 * the spin lock numbers to be used are defined statically and defaulted here
 * to the values nominally set aside for RTOS by the SDK */
#यदि_अपरिभाषितम् configSMP_SPINLOCK_0
    #परिभाषय configSMP_SPINLOCK_0    PICO_SPINLOCK_ID_OS1
#यदि_अन्तः

#यदि_अपरिभाषितम् configSMP_SPINLOCK_1
    #परिभाषय configSMP_SPINLOCK_1    PICO_SPINLOCK_ID_OS2
#यदि_अन्तः

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* ifndef RP2040_CONFIG_H */
