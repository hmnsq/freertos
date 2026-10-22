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

#اگر_تعریف_نشده RP2040_CONFIG_H
#تعریف_کن RP2040_CONFIG_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
/* *INDENT-ON* */

/* configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 means set the exception handlers dynamically on cores
 * that need them in case the user has set up distinct vector table offsets per core
 */
#اگر_تعریف_نشده configUSE_DYNAMIC_EXCEPTION_HANDLERS
    #إذا defined( PICO_NO_RAM_وکتور_جدول ) && ( PICO_NO_RAM_وکتور_جدول == 1 )
        #تعریف_کن configUSE_DYNAMIC_EXCEPTION_HANDLERS    0
    #وإلا
        #تعریف_کن configUSE_DYNAMIC_EXCEPTION_HANDLERS    1
    #پایان_اگر
#پایان_اگر

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_sync
 * sem/mutex/queue etc. will work correctly when called from FreeRTOS tasks
 */
#اگر_تعریف_نشده configSUPPORT_PICO_SYNC_INTEROP
    #إذا LIB_PICO_SYNC
        #تعریف_کن configSUPPORT_PICO_SYNC_INTEROP    1
    #پایان_اگر
#پایان_اگر

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_time
 * sleep_ms/sleep_us/sleep_until will work correctly when called from FreeRTOS
 * tasks, and will actually block at the FreeRTOS level
 */
#اگر_تعریف_نشده config_SUPPORT_PICO_زمان_INTEROP
    #إذا LIB_PICO_زمان
        #تعریف_کن config_SUPPORT_PICO_زمان_INTEROP    1
    #پایان_اگر
#پایان_اگر

#إذا ( config_عدد_از_CORES > 1 )

/* configTICK_CORE indicates which core should handle the SysTick
 * interrupts */
    #اگر_تعریف_نشده configTICK_CORE
        #تعریف_کن configTICK_CORE    0
    #پایان_اگر
#پایان_اگر

/* This SMP port requires two spin locks, which are claimed from the SDK.
 * the spin lock numbers to be used are defined statically and defaulted here
 * to the values nominally set aside for RTOS by the SDK */
#اگر_تعریف_نشده configSMP_SPINLOCK_0
    #تعریف_کن configSMP_SPINLOCK_0    PICO_SPINLOCK_ID_OS1
#پایان_اگر

#اگر_تعریف_نشده configSMP_SPINLOCK_1
    #تعریف_کن configSMP_SPINLOCK_1    PICO_SPINLOCK_ID_OS2
#پایان_اگر

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* ifndef RP2040_CONFIG_H */
