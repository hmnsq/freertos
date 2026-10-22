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

#اگر_غیر_تعریف_شدہ RP2040_CONFIG_H
#تعریف_کرو RP2040_CONFIG_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
/* *INDENT-ON* */

/* configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 means set the exception handlers dynamically on cores
 * that need them in case the user has set up distinct vector table offsets per core
 */
#اگر_غیر_تعریف_شدہ configUSE_DYNAMIC_EXCEPTION_HANDLERS
    #اگر defined( PICO_NO_RAM_سمتیہ_جدول ) && ( PICO_NO_RAM_سمتیہ_جدول == 1 )
        #تعریف_کرو configUSE_DYNAMIC_EXCEPTION_HANDLERS    0
    #ورنہ
        #تعریف_کرو configUSE_DYNAMIC_EXCEPTION_HANDLERS    1
    #اگر_ختم
#اگر_ختم

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_sync
 * sem/mutex/queue etc. will work correctly when called from FreeRTOS tasks
 */
#اگر_غیر_تعریف_شدہ configSUPPORT_PICO_SYNC_INTEROP
    #اگر LIB_PICO_SYNC
        #تعریف_کرو configSUPPORT_PICO_SYNC_INTEROP    1
    #اگر_ختم
#اگر_ختم

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_time
 * sleep_ms/sleep_us/sleep_until will work correctly when called from FreeRTOS
 * tasks, and will actually block at the FreeRTOS level
 */
#اگر_غیر_تعریف_شدہ config_SUPPORT_PICO_وقت_INTEROP
    #اگر LIB_PICO_وقت
        #تعریف_کرو config_SUPPORT_PICO_وقت_INTEROP    1
    #اگر_ختم
#اگر_ختم

#اگر ( config_نمبر_کا_CORES > 1 )

/* configTICK_CORE indicates which core should handle the SysTick
 * interrupts */
    #اگر_غیر_تعریف_شدہ configTICK_CORE
        #تعریف_کرو configTICK_CORE    0
    #اگر_ختم
#اگر_ختم

/* This SMP port requires two spin locks, which are claimed from the SDK.
 * the spin lock numbers to be used are defined statically and defaulted here
 * to the values nominally set aside for RTOS by the SDK */
#اگر_غیر_تعریف_شدہ configSMP_SPINLOCK_0
    #تعریف_کرو configSMP_SPINLOCK_0    PICO_SPINLOCK_ID_OS1
#اگر_ختم

#اگر_غیر_تعریف_شدہ configSMP_SPINLOCK_1
    #تعریف_کرو configSMP_SPINLOCK_1    PICO_SPINLOCK_ID_OS2
#اگر_ختم

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* ifndef RP2040_CONFIG_H */
