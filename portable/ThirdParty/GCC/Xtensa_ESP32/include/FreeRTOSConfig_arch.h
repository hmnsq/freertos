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

#నిర్వచితం_కాకపోతే FREERTOS_CONFIG_XTENSA_H
#నిర్వచించు FREERTOS_CONFIG_XTENSA_H

#అన్తర్భావ "sdkconfig.h"

/* enable use of optimized task selection by the scheduler */
#ఒకవేళ defined( CONFIG_FREERTOS_OPTIMIZED_SCHEDULER ) && !defined( config_USE_పోర్టు_OPTIMISED_TASK_SELECTION )
    #నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    1
#అయితే_ముగింపు

#నిర్వచించు XT_USE_THREAD_సురక్షిత_CLIB                        0
#నిర్వచనం_రద్దు XT_USE_SWPRI

#ఒకవేళ CONFIG_FREERTOS_CORETIMER_0
    #నిర్వచించు XT_TIMER_సూచీ    0
#లేదావేళ CONFIG_FREERTOS_CORETIMER_1
    #నిర్వచించు XT_TIMER_సూచీ    1
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే __ASSEMBLER__

/**
 * This function is defined to provide a deprecation warning whenever
 * XT_CLOCK_FREQ macro is used.
 * Update the code to use esp_clk_cpu_freq function instead.
 * @return current CPU clock frequency, in Hz
 */
    పూర్ణాంకం xt_clock_freq( శూన్య ) __attribute__( ( deprecated ) );

    #నిర్వచించు XT_CLOCK_FREQ    ( xt_clock_freq() )

#అయితే_ముగింపు // __ASSEMBLER__

/* Required for configuration-dependent settings */
#అన్తర్భావ <xtensa_config.h>

/* configASSERT behaviour */
#నిర్వచితం_కాకపోతే __ASSEMBLER__
    #అన్తర్భావ <assert.h>
    #అన్తర్భావ "esp_rom_sys.h"
    #ఒకవేళ CONFIG_IDF_లక్ష్యం_ESP32
        #అన్తర్భావ "esp32/rom/ets_sys.h" /* will be removed in idf v5.0 */
    #లేదావేళ CONFIG_IDF_లక్ష్యం_ESP32_S2
        #అన్తర్భావ "esp32s2/rom/ets_sys.h"
    #లేదావేళ CONFIG_IDF_లక్ష్యం_ESP32_S3
        #అన్తర్భావ "esp32s3/rom/ets_sys.h"
    #అయితే_ముగింపు
#అయితే_ముగింపు // __ASSEMBLER__

/* If CONFIG_FREERTOS_ASSERT_DISABLE is set then configASSERT is defined empty later in FreeRTOS.h and the macro */
/* configASSERT_DEFINED remains unset (meaning some warnings are avoided) */
#ఒకవేళ ( configASSERT_DEFINED == 1 )
    #నిర్వచనం_రద్దు configASSERT
    #ఒకవేళ defined( CONFIG_FREERTOS_ASSERT_FAIL_PRINT_CONTINUE )
        #నిర్వచించు configASSERT( a )                                           \
    ఒకవేళ( unlikely( !( a ) ) ) {                                              \
        esp_rom_printf( "%s:%d (%s)- assert failed!\n", __FILE__, __LINE__, \
                        __FUNCTION__ );                                     \
    }
    #లేదావేళ defined( CONFIG_FREERTOS_ASSERT_FAIL_ABORT )
        #నిర్వచించు configASSERT( a )    ప్రతిజ్ఞా( a )
    #అయితే_ముగింపు
#అయితే_ముగింపు /* ifdef configASSERT */

#ఒకవేళ CONFIG_FREERTOS_ASSERT_ON_UNTESTED_FUNCTION
    #నిర్వచించు UNTESTED_FUNCTION()                                                                     \
    { esp_rom_printf( "Untested FreeRTOS function %s\r\n", __FUNCTION__ ); configASSERT( false ); } \
    అయితే( 0 )
#లేకపోతే
    #నిర్వచించు UNTESTED_FUNCTION()
#అయితే_ముగింపు

#నిర్వచించు configXT_BOARD                          1           /* Board mode */
#నిర్వచించు configXT_SIMULATOR                      0

/* The maximum interrupt priority from which FreeRTOS.org API functions can
 * be called.  Only API functions that end in ...FromISR() can be used within
 * interrupts. */
#నిర్వచించు config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత    XCHAL_EXCM_LEVEL

/* Stack alignment, architecture specific. Must be a power of two. */
#నిర్వచించు config_దొంతర_ALIGNMENT                   16


/* The Xtensa port uses a separate interrupt stack. Adjust the stack size
 * to suit the needs of your specific application.
 * Size needs to be aligned to the stack increment, since the location of
 * the stack for the 2nd CPU will be calculated using configISR_STACK_SIZE.
 */
#నిర్వచితం_కాకపోతే config_ISR_దొంతర_కొలత
    #నిర్వచించు config_ISR_దొంతర_కొలత    ( ( CONFIG_FREERTOS_ISR_STACKSIZE + config_దొంతర_ALIGNMENT - 1 ) & ( ~( config_దొంతర_ALIGNMENT - 1 ) ) )
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే __ASSEMBLER__
    #ఒకవేళ CONFIG_APPTRACE_SV_ENABLE
        బాహ్య uint32_t పోర్టు_switch_flag[];
        #నిర్వచించు os_task_switch_is_pended( _cpu_ )    ( పోర్టు_switch_flag[ _cpu_ ] )
    #లేకపోతే
        #నిర్వచించు os_task_switch_is_pended( _cpu_ )    ( false )
    #అయితే_ముగింపు
#అయితే_ముగింపు

#అయితే_ముగింపు // FREERTOS_CONFIG_XTENSA_H
