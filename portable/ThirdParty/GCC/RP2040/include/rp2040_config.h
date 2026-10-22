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

#अगर_अघोषित RP2040_CONFIG_H
#घोषणा RP2040_CONFIG_H

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
/* *INDENT-ON* */

/* configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 means set the exception handlers dynamically on cores
 * that need them in case the user has set up distinct vector table offsets per core
 */
#अगर_अघोषित configUSE_DYNAMIC_EXCEPTION_HANDLERS
    #अगर defined( PICO_NO_RAM_VECTOR_TABLE ) && ( PICO_NO_RAM_VECTOR_TABLE == 1 )
        #घोषणा configUSE_DYNAMIC_EXCEPTION_HANDLERS    0
    #अन्यथा
        #घोषणा configUSE_DYNAMIC_EXCEPTION_HANDLERS    1
    #पूर्ण_अगर
#पूर्ण_अगर

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_sync
 * sem/mutex/queue etc. will work correctly when called from FreeRTOS tasks
 */
#अगर_अघोषित configSUPPORT_PICO_SYNC_INTEROP
    #अगर LIB_PICO_SYNC
        #घोषणा configSUPPORT_PICO_SYNC_INTEROP    1
    #पूर्ण_अगर
#पूर्ण_अगर

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_time
 * sleep_ms/sleep_us/sleep_until will work correctly when called from FreeRTOS
 * tasks, and will actually block at the FreeRTOS level
 */
#अगर_अघोषित configSUPPORT_PICO_TIME_INTEROP
    #अगर LIB_PICO_TIME
        #घोषणा configSUPPORT_PICO_TIME_INTEROP    1
    #पूर्ण_अगर
#पूर्ण_अगर

#अगर ( config_संख्या_OF_CORES > 1 )

/* configTICK_CORE indicates which core should handle the SysTick
 * interrupts */
    #अगर_अघोषित configTICK_CORE
        #घोषणा configTICK_CORE    0
    #पूर्ण_अगर
#पूर्ण_अगर

/* This SMP port requires two spin locks, which are claimed from the SDK.
 * the spin lock numbers to be used are defined statically and defaulted here
 * to the values nominally set aside for RTOS by the SDK */
#अगर_अघोषित configSMP_SPINLOCK_0
    #घोषणा configSMP_SPINLOCK_0    PICO_SPINLOCK_ID_OS1
#पूर्ण_अगर

#अगर_अघोषित configSMP_SPINLOCK_1
    #घोषणा configSMP_SPINLOCK_1    PICO_SPINLOCK_ID_OS2
#पूर्ण_अगर

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* ifndef RP2040_CONFIG_H */
