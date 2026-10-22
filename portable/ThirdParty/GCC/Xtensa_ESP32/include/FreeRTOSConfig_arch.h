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

#यदि_अपरिभाषितम् FREERTOS_CONFIG_XTENSA_H
#परिभाषय FREERTOS_CONFIG_XTENSA_H

#अन्तर्भाव "sdkconfig.h"

/* enable use of optimized task selection by the scheduler */
#यदि defined( CONFIG_FREERTOS_OPTIMIZED_SCHEDULER ) && !defined( config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION )
    #परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    1
#यदि_अन्तः

#परिभाषय XT_USE_THREAD_SAFE_CLIB                        0
#अपरिभाषय XT_USE_SWPRI

#यदि CONFIG_FREERTOS_CORETIMER_0
    #परिभाषय XT_TIMER_सूचकांक    0
#नोचेद्यदि CONFIG_FREERTOS_CORETIMER_1
    #परिभाषय XT_TIMER_सूचकांक    1
#यदि_अन्तः

#यदि_अपरिभाषितम् __ASSEMBLER__

/**
 * This function is defined to provide a deprecation warning whenever
 * XT_CLOCK_FREQ macro is used.
 * Update the code to use esp_clk_cpu_freq function instead.
 * @return current CPU clock frequency, in Hz
 */
    पूर्णाङ्क xt_clock_freq( शून्य ) __attribute__( ( deprecated ) );

    #परिभाषय XT_CLOCK_FREQ    ( xt_clock_freq() )

#यदि_अन्तः // __ASSEMBLER__

/* Required for configuration-dependent settings */
#अन्तर्भाव <xtensa_config.h>

/* configASSERT behaviour */
#यदि_अपरिभाषितम् __ASSEMBLER__
    #अन्तर्भाव <assert.h>
    #अन्तर्भाव "esp_rom_sys.h"
    #यदि CONFIG_IDF_TARGET_ESP32
        #अन्तर्भाव "esp32/rom/ets_sys.h" /* will be removed in idf v5.0 */
    #नोचेद्यदि CONFIG_IDF_TARGET_ESP32S2
        #अन्तर्भाव "esp32s2/rom/ets_sys.h"
    #नोचेद्यदि CONFIG_IDF_TARGET_ESP32S3
        #अन्तर्भाव "esp32s3/rom/ets_sys.h"
    #यदि_अन्तः
#यदि_अन्तः // __ASSEMBLER__

/* If CONFIG_FREERTOS_ASSERT_DISABLE is set then configASSERT is defined empty later in FreeRTOS.h and the macro */
/* configASSERT_DEFINED remains unset (meaning some warnings are avoided) */
#यदि ( configASSERT_DEFINED == 1 )
    #अपरिभाषय configASSERT
    #यदि defined( CONFIG_FREERTOS_ASSERT_FAIL_PRINT_CONTINUE )
        #परिभाषय configASSERT( a )                                           \
    यदि( unlikely( !( a ) ) ) {                                              \
        esp_rom_printf( "%s:%d (%s)- assert failed!\n", __FILE__, __LINE__, \
                        __FUNCTION__ );                                     \
    }
    #नोचेद्यदि defined( CONFIG_FREERTOS_ASSERT_FAIL_ABORT )
        #परिभाषय configASSERT( a )    प्रतिज्ञा( a )
    #यदि_अन्तः
#यदि_अन्तः /* ifdef configASSERT */

#यदि CONFIG_FREERTOS_ASSERT_ON_UNTESTED_FUNCTION
    #परिभाषय UNTESTED_FUNCTION()                                                                     \
    { esp_rom_printf( "Untested FreeRTOS function %s\r\n", __FUNCTION__ ); configASSERT( false ); } \
    यावत्( 0 )
#अन्यथा
    #परिभाषय UNTESTED_FUNCTION()
#यदि_अन्तः

#परिभाषय configXT_BOARD                          1           /* Board mode */
#परिभाषय configXT_SIMULATOR                      0

/* The maximum interrupt priority from which FreeRTOS.org API functions can
 * be called.  Only API functions that end in ...FromISR() can be used within
 * interrupts. */
#परिभाषय config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता    XCHAL_EXCM_LEVEL

/* Stack alignment, architecture specific. Must be a power of two. */
#परिभाषय config_राशिः_ALIGNMENT                   16


/* The Xtensa port uses a separate interrupt stack. Adjust the stack size
 * to suit the needs of your specific application.
 * Size needs to be aligned to the stack increment, since the location of
 * the stack for the 2nd CPU will be calculated using configISR_STACK_SIZE.
 */
#यदि_अपरिभाषितम् config_ISR_राशिः_आकार
    #परिभाषय config_ISR_राशिः_आकार    ( ( CONFIG_FREERTOS_ISR_STACKSIZE + config_राशिः_ALIGNMENT - 1 ) & ( ~( config_राशिः_ALIGNMENT - 1 ) ) )
#यदि_अन्तः

#यदि_अपरिभाषितम् __ASSEMBLER__
    #यदि CONFIG_APPTRACE_SV_ENABLE
        बाह्य uint32_t पत्तनम्_switch_flag[];
        #परिभाषय os_task_switch_is_pended( _cpu_ )    ( पत्तनम्_switch_flag[ _cpu_ ] )
    #अन्यथा
        #परिभाषय os_task_switch_is_pended( _cpu_ )    ( false )
    #यदि_अन्तः
#यदि_अन्तः

#यदि_अन्तः // FREERTOS_CONFIG_XTENSA_H
