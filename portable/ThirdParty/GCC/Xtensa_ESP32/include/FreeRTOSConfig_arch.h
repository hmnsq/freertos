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

#अगर_अघोषित FREERTOS_CONFIG_XTENSA_H
#घोषणा FREERTOS_CONFIG_XTENSA_H

#समावेश "sdkconfig.h"

/* enable use of optimized task selection by the scheduler */
#अगर defined( CONFIG_FREERTOS_OPTIMIZED_SCHEDULER ) && !defined( configUSE_PORT_OPTIMISED_TASK_SELECTION )
    #घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#पूर्ण_अगर

#घोषणा XT_USE_THREAD_SAFE_CLIB                        0
#अघोषित XT_USE_SWPRI

#अगर CONFIG_FREERTOS_CORETIMER_0
    #घोषणा XT_TIMER_सूचकांक    0
#या_अगर CONFIG_FREERTOS_CORETIMER_1
    #घोषणा XT_TIMER_सूचकांक    1
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLER__

/**
 * This function is defined to provide a deprecation warning whenever
 * XT_CLOCK_FREQ macro is used.
 * Update the code to use esp_clk_cpu_freq function instead.
 * @return current CPU clock frequency, in Hz
 */
    पूर्णांक xt_clock_freq( व्योम ) __attribute__( ( deprecated ) );

    #घोषणा XT_CLOCK_FREQ    ( xt_clock_freq() )

#पूर्ण_अगर // __ASSEMBLER__

/* Required for configuration-dependent settings */
#समावेश <xtensa_config.h>

/* configASSERT behaviour */
#अगर_अघोषित __ASSEMBLER__
    #समावेश <assert.h>
    #समावेश "esp_rom_sys.h"
    #अगर CONFIG_IDF_TARGET_ESP32
        #समावेश "esp32/rom/ets_sys.h" /* will be removed in idf v5.0 */
    #या_अगर CONFIG_IDF_TARGET_ESP32S2
        #समावेश "esp32s2/rom/ets_sys.h"
    #या_अगर CONFIG_IDF_TARGET_ESP32S3
        #समावेश "esp32s3/rom/ets_sys.h"
    #पूर्ण_अगर
#पूर्ण_अगर // __ASSEMBLER__

/* If CONFIG_FREERTOS_ASSERT_DISABLE is set then configASSERT is defined empty later in FreeRTOS.h and the macro */
/* configASSERT_DEFINED remains unset (meaning some warnings are avoided) */
#अगर ( configASSERT_DEFINED == 1 )
    #अघोषित configASSERT
    #अगर defined( CONFIG_FREERTOS_ASSERT_FAIL_PRINT_CONTINUE )
        #घोषणा configASSERT( a )                                           \
    अगर( unlikely( !( a ) ) ) {                                              \
        esp_rom_printf( "%s:%d (%s)- assert failed!\n", __खाता__, __LINE__, \
                        __FUNCTION__ );                                     \
    }
    #या_अगर defined( CONFIG_FREERTOS_ASSERT_FAIL_ABORT )
        #घोषणा configASSERT( a )    निश्चित( a )
    #पूर्ण_अगर
#पूर्ण_अगर /* ifdef configASSERT */

#अगर CONFIG_FREERTOS_ASSERT_ON_UNTESTED_FUNCTION
    #घोषणा UNTESTED_FUNCTION()                                                                     \
    { esp_rom_printf( "Untested FreeRTOS function %s\r\n", __FUNCTION__ ); configASSERT( false ); } \
    जबतक( 0 )
#अन्यथा
    #घोषणा UNTESTED_FUNCTION()
#पूर्ण_अगर

#घोषणा configXT_BOARD                          1           /* Board mode */
#घोषणा configXT_SIMULATOR                      0

/* The maximum interrupt priority from which FreeRTOS.org API functions can
 * be called.  Only API functions that end in ...FromISR() can be used within
 * interrupts. */
#घोषणा configMAX_SYSCALL_INTERRUPT_PRIORITY    XCHAL_EXCM_LEVEL

/* Stack alignment, architecture specific. Must be a power of two. */
#घोषणा config_ढेर_ALIGNMENT                   16


/* The Xtensa port uses a separate interrupt stack. Adjust the stack size
 * to suit the needs of your specific application.
 * Size needs to be aligned to the stack increment, since the location of
 * the stack for the 2nd CPU will be calculated using configISR_STACK_SIZE.
 */
#अगर_अघोषित config_ISR_ढेर_आकार
    #घोषणा config_ISR_ढेर_आकार    ( ( CONFIG_FREERTOS_ISR_STACKSIZE + config_ढेर_ALIGNMENT - 1 ) & ( ~( config_ढेर_ALIGNMENT - 1 ) ) )
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLER__
    #अगर CONFIG_APPTRACE_SV_ENABLE
        बाह्य uint32_t port_switch_flag[];
        #घोषणा os_task_switch_is_pended( _cpu_ )    ( port_switch_flag[ _cpu_ ] )
    #अन्यथा
        #घोषणा os_task_switch_is_pended( _cpu_ )    ( false )
    #पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर // FREERTOS_CONFIG_XTENSA_H
