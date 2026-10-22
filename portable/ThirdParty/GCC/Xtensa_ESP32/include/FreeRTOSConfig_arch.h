/*
 * SPDX-FileCopyrightText: 2022 Amazon.com, Inc. or its affiliates
 *
 * SPDX-License-Identifier: MIT
 *
 * SPDX-FileContributor: 2016-2022 Espressif Systems (Shanghai) CO LTD
 */

/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
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
 *
 * 1 tab == 4 spaces!
 */

#جيڪڏهن_وصف_نه_ٿيل FREERTOS_CONFIG_XTENSA_H
#وصف_ڪريو FREERTOS_CONFIG_XTENSA_H

#ضمن "sdkconfig.h"

/* enable use of optimized task selection by the scheduler */
#إذا defined( CONFIG_FREERTOS_OPTIMIZED_SCHEDULER ) && !defined( config_USE_پورٽ_OPTIMISED_TASK_SELECTION )
    #وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    1
#جيڪڏهن_پورو

#وصف_ڪريو XT_USE_THREAD_محفوظ_CLIB                        0
#وصف_رد XT_USE_SWPRI

#إذا CONFIG_FREERTOS_CORETIMER_0
    #وصف_ڪريو XT_TIMER_اشاريو    0
#وإلاإذا CONFIG_FREERTOS_CORETIMER_1
    #وصف_ڪريو XT_TIMER_اشاريو    1
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل __ASSEMBLER__

/**
 * This function is defined to provide a deprecation warning whenever
 * XT_CLOCK_FREQ macro is used.
 * Update the code to use esp_clk_cpu_freq function instead.
 * @return current CPU clock frequency, in Hz
 */
    صحيح xt_clock_freq( فراغ ) __attribute__( ( deprecated ) );

    #وصف_ڪريو XT_CLOCK_FREQ    ( xt_clock_freq() )

#جيڪڏهن_پورو // __ASSEMBLER__

/* Required for configuration-dependent settings */
#ضمن <xtensa_config.h>

/* configASSERT behaviour */
#جيڪڏهن_وصف_نه_ٿيل __ASSEMBLER__
    #ضمن <assert.h>
    #ضمن "esp_rom_sys.h"
    #إذا CONFIG_IDF_هدف_ESP32
        #ضمن "esp32/rom/ets_sys.h" /* will be removed in idf v5.0 */
    #وإلاإذا CONFIG_IDF_هدف_ESP32_S2
        #ضمن "esp32s2/rom/ets_sys.h"
    #وإلاإذا CONFIG_IDF_هدف_ESP32_S3
        #ضمن "esp32s3/rom/ets_sys.h"
    #جيڪڏهن_پورو
#جيڪڏهن_پورو // __ASSEMBLER__

/* If CONFIG_FREERTOS_ASSERT_DISABLE is set then configASSERT is defined empty later in FreeRTOS.h and the macro */
/* configASSERT_DEFINED remains unset (meaning some warnings are avoided) */
#إذا ( configASSERT_DEFINED == 1 )
    #وصف_رد configASSERT
    #إذا defined( CONFIG_FREERTOS_ASSERT_FAIL_PRINT_CONTINUE )
        #وصف_ڪريو configASSERT( a )                                           \
    إذا( unlikely( !( a ) ) ) {                                              \
        esp_rom_printf( "%s:%d (%s)- assert failed!\n", __FILE__, __LINE__, \
                        __FUNCTION__ );                                     \
    }
    #وإلاإذا defined( CONFIG_FREERTOS_ASSERT_FAIL_ABORT )
        #وصف_ڪريو configASSERT( a )    أكد( a )
    #جيڪڏهن_پورو
#جيڪڏهن_پورو /* ifdef configASSERT */

#إذا CONFIG_FREERTOS_ASSERT_ON_UNTESTED_FUNCTION
    #وصف_ڪريو UNTESTED_FUNCTION()                                                                     \
    { esp_rom_printf( "Untested FreeRTOS function %s\r\n", __FUNCTION__ ); configASSERT( false ); } \
    طالما( 0 )
#وإلا
    #وصف_ڪريو UNTESTED_FUNCTION()
#جيڪڏهن_پورو

#وصف_ڪريو configXT_BOARD                          1           /* Board mode */
#وصف_ڪريو configXT_SIMULATOR                      0

/* The maximum interrupt priority from which FreeRTOS.org API functions can
 * be called.  Only API functions that end in ...FromISR() can be used within
 * interrupts. */
#وصف_ڪريو config_MAX_SYSCALL_مداخلت_ترجيح    XCHAL_EXCM_LEVEL

/* Stack alignment, architecture specific. Must be a power of two. */
#وصف_ڪريو config_ڍير_ALIGNMENT                   16


/* The Xtensa port uses a separate interrupt stack. Adjust the stack size
 * to suit the needs of your specific application.
 * Size needs to be aligned to the stack increment, since the location of
 * the stack for the 2nd CPU will be calculated using configISR_STACK_SIZE.
 */
#جيڪڏهن_وصف_نه_ٿيل config_ISR_ڍير_سائيز
    #وصف_ڪريو config_ISR_ڍير_سائيز    ( ( CONFIG_FREERTOS_ISR_STACKSIZE + config_ڍير_ALIGNMENT - 1 ) & ( ~( config_ڍير_ALIGNMENT - 1 ) ) )
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل __ASSEMBLER__
    #إذا CONFIG_APPTRACE_SV_ENABLE
        خارجي uint32_t پورٽ_switch_flag[];
        #وصف_ڪريو os_task_switch_is_pended( _cpu_ )    ( پورٽ_switch_flag[ _cpu_ ] )
    #وإلا
        #وصف_ڪريو os_task_switch_is_pended( _cpu_ )    ( false )
    #جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_پورو // FREERTOS_CONFIG_XTENSA_H
