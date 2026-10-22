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

#నిర్వచితం_కాకపోతే RP2040_CONFIG_H
#నిర్వచించు RP2040_CONFIG_H

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
/* *INDENT-ON* */

/* configUSE_DYNAMIC_EXCEPTION_HANDLERS == 1 means set the exception handlers dynamically on cores
 * that need them in case the user has set up distinct vector table offsets per core
 */
#నిర్వచితం_కాకపోతే configUSE_DYNAMIC_EXCEPTION_HANDLERS
    #ఒకవేళ defined( PICO_NO_RAM_సదిశ_పట్టిక ) && ( PICO_NO_RAM_సదిశ_పట్టిక == 1 )
        #నిర్వచించు configUSE_DYNAMIC_EXCEPTION_HANDLERS    0
    #లేకపోతే
        #నిర్వచించు configUSE_DYNAMIC_EXCEPTION_HANDLERS    1
    #అయితే_ముగింపు
#అయితే_ముగింపు

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_sync
 * sem/mutex/queue etc. will work correctly when called from FreeRTOS tasks
 */
#నిర్వచితం_కాకపోతే configSUPPORT_PICO_SYNC_INTEROP
    #ఒకవేళ LIB_PICO_SYNC
        #నిర్వచించు configSUPPORT_PICO_SYNC_INTEROP    1
    #అయితే_ముగింపు
#అయితే_ముగింపు

/* configSUPPORT_PICO_SYNC_INTEROP == 1 means that SDK pico_time
 * sleep_ms/sleep_us/sleep_until will work correctly when called from FreeRTOS
 * tasks, and will actually block at the FreeRTOS level
 */
#నిర్వచితం_కాకపోతే config_SUPPORT_PICO_సమయం_INTEROP
    #ఒకవేళ LIB_PICO_సమయం
        #నిర్వచించు config_SUPPORT_PICO_సమయం_INTEROP    1
    #అయితే_ముగింపు
#అయితే_ముగింపు

#ఒకవేళ ( config_సంఖ్య_యొక్క_CORES > 1 )

/* configTICK_CORE indicates which core should handle the SysTick
 * interrupts */
    #నిర్వచితం_కాకపోతే configTICK_CORE
        #నిర్వచించు configTICK_CORE    0
    #అయితే_ముగింపు
#అయితే_ముగింపు

/* This SMP port requires two spin locks, which are claimed from the SDK.
 * the spin lock numbers to be used are defined statically and defaulted here
 * to the values nominally set aside for RTOS by the SDK */
#నిర్వచితం_కాకపోతే configSMP_SPINLOCK_0
    #నిర్వచించు configSMP_SPINLOCK_0    PICO_SPINLOCK_ID_OS1
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే configSMP_SPINLOCK_1
    #నిర్వచించు configSMP_SPINLOCK_1    PICO_SPINLOCK_ID_OS2
#అయితే_ముగింపు

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* ifndef RP2040_CONFIG_H */
