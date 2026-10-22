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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ RP2040_CONFIG_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RP2040_CONFIG_H

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

/* configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 means set the exception handlers dynamically on cores
 * that need them in case the user has set up distinct vector table offsets per core
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configUSE_DYNAMIC_EXCEPTION_HANDLERS
    #ਜੇ defined( PICO_NO_RAM_ਸਦਿਸ਼_ਸਾਰਣੀ ) && ( PICO_NO_RAM_ਸਦਿਸ਼_ਸਾਰਣੀ == 1 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_DYNAMIC_EXCEPTION_HANDLERS    0
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_DYNAMIC_EXCEPTION_HANDLERS    1
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_sync
 * sem/mutex/queue etc. will work correctly when called from FreeRTOS tasks
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configSUPPORT_PICO_SYNC_INTEROP
    #ਜੇ LIB_PICO_SYNC
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configSUPPORT_PICO_SYNC_INTEROP    1
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_time
 * sleep_ms/sleep_us/sleep_until will work correctly when called from FreeRTOS
 * tasks, and will actually block at the FreeRTOS level
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_SUPPORT_PICO_ਸਮਾਂ_INTEROP
    #ਜੇ LIB_PICO_ਸਮਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_SUPPORT_PICO_ਸਮਾਂ_INTEROP    1
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ ( config_ਸੰਖਿਆ_ਦਾ_CORES > 1 )

/* configTICK_CORE indicates which core should handle the SysTick
 * interrupts */
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configTICK_CORE
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configTICK_CORE    0
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

/* This SMP port requires two spin locks, which are claimed from the SDK.
 * the spin lock numbers to be used are defined statically and defaulted here
 * to the values nominally set aside for RTOS by the SDK */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configSMP_SPINLOCK_0
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configSMP_SPINLOCK_0    PICO_SPINLOCK_ID_OS1
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ configSMP_SPINLOCK_1
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configSMP_SPINLOCK_1    PICO_SPINLOCK_ID_OS2
#ਜੇ_ਅੰਤ

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* ifndef RP2040_CONFIG_H */
