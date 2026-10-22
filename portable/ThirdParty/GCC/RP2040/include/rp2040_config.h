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

#جے_بنا_تعریف RP2040_CONFIG_H
#تعریف_کرو RP2040_CONFIG_H

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    خارجي "C" {
#جے_انت
/* *INDENT-ON* */

/* configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 means set the exception handlers dynamically on cores
 * that need them in case the user has set up distinct vector table offsets per core
 */
#جے_بنا_تعریف configUSE_DYNAMIC_EXCEPTION_HANDLERS
    #إذا defined( PICO_NO_RAM_سمتیہ_جدول ) && ( PICO_NO_RAM_سمتیہ_جدول == 1 )
        #تعریف_کرو configUSE_DYNAMIC_EXCEPTION_HANDLERS    0
    #وإلا
        #تعریف_کرو configUSE_DYNAMIC_EXCEPTION_HANDLERS    1
    #جے_انت
#جے_انت

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_sync
 * sem/mutex/queue etc. will work correctly when called from FreeRTOS tasks
 */
#جے_بنا_تعریف configSUPPORT_PICO_SYNC_INTEROP
    #إذا LIB_PICO_SYNC
        #تعریف_کرو configSUPPORT_PICO_SYNC_INTEROP    1
    #جے_انت
#جے_انت

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_time
 * sleep_ms/sleep_us/sleep_until will work correctly when called from FreeRTOS
 * tasks, and will actually block at the FreeRTOS level
 */
#جے_بنا_تعریف config_SUPPORT_PICO_ویلا_INTEROP
    #إذا LIB_PICO_ویلا
        #تعریف_کرو config_SUPPORT_PICO_ویلا_INTEROP    1
    #جے_انت
#جے_انت

#إذا ( config_نمبر_دا_CORES > 1 )

/* configTICK_CORE indicates which core should handle the SysTick
 * interrupts */
    #جے_بنا_تعریف configTICK_CORE
        #تعریف_کرو configTICK_CORE    0
    #جے_انت
#جے_انت

/* This SMP port requires two spin locks, which are claimed from the SDK.
 * the spin lock numbers to be used are defined statically and defaulted here
 * to the values nominally set aside for RTOS by the SDK */
#جے_بنا_تعریف configSMP_SPINLOCK_0
    #تعریف_کرو configSMP_SPINLOCK_0    PICO_SPINLOCK_ID_OS1
#جے_انت

#جے_بنا_تعریف configSMP_SPINLOCK_1
    #تعریف_کرو configSMP_SPINLOCK_1    PICO_SPINLOCK_ID_OS2
#جے_انت

/* *INDENT-OFF* */
#جے_تعریف_شدہ __cplusplus
    }
#جے_انت
/* *INDENT-ON* */

#جے_انت /* ifndef RP2040_CONFIG_H */
