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

#که_نه_تعریف_شوی RP2040_CONFIG_H
#تعریف_کړه RP2040_CONFIG_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
/* *INDENT-ON* */

/* configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 means set the exception handlers dynamically on cores
 * that need them in case the user has set up distinct vector table offsets per core
 */
#که_نه_تعریف_شوی configUSE_DYNAMIC_EXCEPTION_HANDLERS
    #إذا defined( PICO_NO_RAM_ویکټور_جدول ) && ( PICO_NO_RAM_ویکټور_جدول == 1 )
        #تعریف_کړه configUSE_DYNAMIC_EXCEPTION_HANDLERS    0
    #وإلا
        #تعریف_کړه configUSE_DYNAMIC_EXCEPTION_HANDLERS    1
    #د_که_پای
#د_که_پای

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_sync
 * sem/mutex/queue etc. will work correctly when called from FreeRTOS tasks
 */
#که_نه_تعریف_شوی configSUPPORT_PICO_SYNC_INTEROP
    #إذا LIB_PICO_SYNC
        #تعریف_کړه configSUPPORT_PICO_SYNC_INTEROP    1
    #د_که_پای
#د_که_پای

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_time
 * sleep_ms/sleep_us/sleep_until will work correctly when called from FreeRTOS
 * tasks, and will actually block at the FreeRTOS level
 */
#که_نه_تعریف_شوی config_SUPPORT_PICO_وخت_INTEROP
    #إذا LIB_PICO_وخت
        #تعریف_کړه config_SUPPORT_PICO_وخت_INTEROP    1
    #د_که_پای
#د_که_پای

#إذا ( config_شمېره_د_CORES > 1 )

/* configTICK_CORE indicates which core should handle the SysTick
 * interrupts */
    #که_نه_تعریف_شوی configTICK_CORE
        #تعریف_کړه configTICK_CORE    0
    #د_که_پای
#د_که_پای

/* This SMP port requires two spin locks, which are claimed from the SDK.
 * the spin lock numbers to be used are defined statically and defaulted here
 * to the values nominally set aside for RTOS by the SDK */
#که_نه_تعریف_شوی configSMP_SPINLOCK_0
    #تعریف_کړه configSMP_SPINLOCK_0    PICO_SPINLOCK_ID_OS1
#د_که_پای

#که_نه_تعریف_شوی configSMP_SPINLOCK_1
    #تعریف_کړه configSMP_SPINLOCK_1    PICO_SPINLOCK_ID_OS2
#د_که_پای

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* ifndef RP2040_CONFIG_H */
