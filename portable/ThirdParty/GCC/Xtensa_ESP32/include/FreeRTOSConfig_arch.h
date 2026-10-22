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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ FREERTOS_CONFIG_XTENSA_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FREERTOS_CONFIG_XTENSA_H

#ਅਨ੍ਤਰ੍ਭਾਵ "sdkconfig.h"

/* enable use of optimized task selection by the scheduler */
#ਜੇ defined( CONFIG_FREERTOS_OPTIMIZED_SCHEDULER ) && !defined( config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION    1
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_USE_THREAD_ਸੁਰੱਖਿਅਤ_CLIB                        0
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ XT_USE_SWPRI

#ਜੇ CONFIG_FREERTOS_CORETIMER_0
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_TIMER_ਸੂਚਕਾਂਕ    0
#ਜਾਂਜੇ CONFIG_FREERTOS_CORETIMER_1
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_TIMER_ਸੂਚਕਾਂਕ    1
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ASSEMBLER__

/**
 * This function is defined to provide a deprecation warning whenever
 * XT_CLOCK_FREQ macro is used.
 * Update the code to use esp_clk_cpu_freq function instead.
 * @return current CPU clock frequency, in Hz
 */
    ਪੂਰਨ xt_clock_freq( ਖਾਲੀ ) __attribute__( ( deprecated ) );

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XT_CLOCK_FREQ    ( xt_clock_freq() )

#ਜੇ_ਅੰਤ // __ASSEMBLER__

/* Required for configuration-dependent settings */
#ਅਨ੍ਤਰ੍ਭਾਵ <xtensa_config.h>

/* configASSERT behaviour */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ASSEMBLER__
    #ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_rom_sys.h"
    #ਜੇ CONFIG_IDF_ਨਿਸ਼ਾਨਾ_ESP32
        #ਅਨ੍ਤਰ੍ਭਾਵ "esp32/rom/ets_sys.h" /* will be removed in idf v5.0 */
    #ਜਾਂਜੇ CONFIG_IDF_ਨਿਸ਼ਾਨਾ_ESP32_S2
        #ਅਨ੍ਤਰ੍ਭਾਵ "esp32s2/rom/ets_sys.h"
    #ਜਾਂਜੇ CONFIG_IDF_ਨਿਸ਼ਾਨਾ_ESP32_S3
        #ਅਨ੍ਤਰ੍ਭਾਵ "esp32s3/rom/ets_sys.h"
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ // __ASSEMBLER__

/* If CONFIG_FREERTOS_ASSERT_DISABLE is set then configASSERT is defined empty later in FreeRTOS.h and the macro */
/* configASSERT_DEFINED remains unset (meaning some warnings are avoided) */
#ਜੇ ( configASSERT_DEFINED == 1 )
    #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ configASSERT
    #ਜੇ defined( CONFIG_FREERTOS_ASSERT_FAIL_PRINT_CONTINUE )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configASSERT( a )                                           \
    ਜੇ( unlikely( !( a ) ) ) {                                              \
        esp_rom_printf( "%s:%d (%s)- assert failed!\n", __FILE__, __LINE__, \
                        __FUNCTION__ );                                     \
    }
    #ਜਾਂਜੇ defined( CONFIG_FREERTOS_ASSERT_FAIL_ABORT )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configASSERT( a )    ਪ੍ਰਤਿਜ੍ਞਾ( a )
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* ifdef configASSERT */

#ਜੇ CONFIG_FREERTOS_ASSERT_ON_UNTESTED_FUNCTION
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UNTESTED_FUNCTION()                                                                     \
    { esp_rom_printf( "Untested FreeRTOS function %s\r\n", __FUNCTION__ ); configASSERT( false ); } \
    ਜਦੋਂ( 0 )
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UNTESTED_FUNCTION()
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configXT_BOARD                          1           /* Board mode */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configXT_SIMULATOR                      0

/* The maximum interrupt priority from which FreeRTOS.org API functions can
 * be called.  Only API functions that end in ...FromISR() can be used within
 * interrupts. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ    XCHAL_EXCM_LEVEL

/* Stack alignment, architecture specific. Must be a power of two. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਢੇਰ_ALIGNMENT                   16


/* The Xtensa port uses a separate interrupt stack. Adjust the stack size
 * to suit the needs of your specific application.
 * Size needs to be aligned to the stack increment, since the location of
 * the stack for the 2nd CPU will be calculated using configISR_STACK_SIZE.
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ISR_ਢੇਰ_ਮਾਪ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ISR_ਢੇਰ_ਮਾਪ    ( ( CONFIG_FREERTOS_ISR_STACKSIZE + config_ਢੇਰ_ALIGNMENT - 1 ) & ( ~( config_ਢੇਰ_ALIGNMENT - 1 ) ) )
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ASSEMBLER__
    #ਜੇ CONFIG_APPTRACE_SV_ENABLE
        ਬਾਹਰੀ uint32_t ਪੋਰਟ_switch_flag[];
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ os_task_switch_is_pended( _cpu_ )    ( ਪੋਰਟ_switch_flag[ _cpu_ ] )
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ os_task_switch_is_pended( _cpu_ )    ( false )
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // FREERTOS_CONFIG_XTENSA_H
