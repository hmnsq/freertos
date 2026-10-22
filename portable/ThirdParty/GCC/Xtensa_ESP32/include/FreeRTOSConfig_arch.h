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

#ifndef FREERTOS_CONFIG_XTENSA_H
#define FREERTOS_CONFIG_XTENSA_H

#ಅನ್ತರ್ಭಾವ "sdkconfig.h"

/* enable use of optimized task selection by the scheduler */
#ಯದಿ defined( CONFIG_FREERTOS_OPTIMIZED_SCHEDULER ) && !defined( configUSE_PORT_OPTIMISED_TASK_SELECTION )
    #define configUSE_PORT_OPTIMISED_TASK_SELECTION    1
#endif

#define XT_USE_THREAD_SAFE_CLIB                        0
#undef XT_USE_SWPRI

#ಯದಿ CONFIG_FREERTOS_CORETIMER_0
    #define XT_TIMER_INDEX    0
#ನೋಚೇದ್ಯದಿ CONFIG_FREERTOS_CORETIMER_1
    #define XT_TIMER_INDEX    1
#endif

#ifndef __ASSEMBLER__

/**
 * This function is defined to provide a deprecation warning whenever
 * XT_CLOCK_FREQ macro is used.
 * Update the code to use esp_clk_cpu_freq function instead.
 * @return current CPU clock frequency, in Hz
 */
    ಪೂರ್ಣಾಙ್ಕ xt_clock_freq( ಶೂನ್ಯ ) __attribute__( ( deprecated ) );

    #define XT_CLOCK_FREQ    ( xt_clock_freq() )

#endif // __ASSEMBLER__

/* Required for configuration-dependent settings */
#ಅನ್ತರ್ಭಾವ <xtensa_config.h>

/* configASSERT behaviour */
#ifndef __ASSEMBLER__
    #ಅನ್ತರ್ಭಾವ <assert.h>
    #ಅನ್ತರ್ಭಾವ "esp_rom_sys.h"
    #ಯದಿ CONFIG_IDF_TARGET_ESP32
        #ಅನ್ತರ್ಭಾವ "esp32/rom/ets_sys.h" /* will be removed in idf v5.0 */
    #ನೋಚೇದ್ಯದಿ CONFIG_IDF_TARGET_ESP32S2
        #ಅನ್ತರ್ಭಾವ "esp32s2/rom/ets_sys.h"
    #ನೋಚೇದ್ಯದಿ CONFIG_IDF_TARGET_ESP32S3
        #ಅನ್ತರ್ಭಾವ "esp32s3/rom/ets_sys.h"
    #endif
#endif // __ASSEMBLER__

/* If CONFIG_FREERTOS_ASSERT_DISABLE is set then configASSERT is defined empty later in FreeRTOS.h and the macro */
/* configASSERT_DEFINED remains unset (meaning some warnings are avoided) */
#ಯದಿ ( configASSERT_DEFINED == 1 )
    #undef configASSERT
    #ಯದಿ defined( CONFIG_FREERTOS_ASSERT_FAIL_PRINT_CONTINUE )
        #define configASSERT( a )                                           \
    ಯದಿ( unlikely( !( a ) ) ) {                                              \
        esp_rom_printf( "%s:%d (%s)- assert failed!\n", __FILE__, __LINE__, \
                        __FUNCTION__ );                                     \
    }
    #ನೋಚೇದ್ಯದಿ defined( CONFIG_FREERTOS_ASSERT_FAIL_ABORT )
        #define configASSERT( a )    ಪ್ರತಿಜ್ಞಾ( a )
    #endif
#endif /* ifdef configASSERT */

#ಯದಿ CONFIG_FREERTOS_ASSERT_ON_UNTESTED_FUNCTION
    #define UNTESTED_FUNCTION()                                                                     \
    { esp_rom_printf( "Untested FreeRTOS function %s\r\n", __FUNCTION__ ); configASSERT( false ); } \
    ಯಾವತ್( 0 )
#ಅನ್ಯಥಾ
    #define UNTESTED_FUNCTION()
#endif

#define configXT_BOARD                          1           /* Board mode */
#define configXT_SIMULATOR                      0

/* The maximum interrupt priority from which FreeRTOS.org API functions can
 * be called.  Only API functions that end in ...FromISR() can be used within
 * interrupts. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    XCHAL_EXCM_LEVEL

/* Stack alignment, architecture specific. Must be a power of two. */
#define config_ರಾಶಿ_ALIGNMENT                   16


/* The Xtensa port uses a separate interrupt stack. Adjust the stack size
 * to suit the needs of your specific application.
 * Size needs to be aligned to the stack increment, since the location of
 * the stack for the 2nd CPU will be calculated using configISR_STACK_SIZE.
 */
#ifndef config_ISR_ರಾಶಿ_SIZE
    #define config_ISR_ರಾಶಿ_SIZE    ( ( CONFIG_FREERTOS_ISR_STACKSIZE + config_ರಾಶಿ_ALIGNMENT - 1 ) & ( ~( config_ರಾಶಿ_ALIGNMENT - 1 ) ) )
#endif

#ifndef __ASSEMBLER__
    #ಯದಿ CONFIG_APPTRACE_SV_ENABLE
        ಬಾಹ್ಯ uint32_t port_switch_flag[];
        #define os_task_switch_is_pended( _cpu_ )    ( port_switch_flag[ _cpu_ ] )
    #ಅನ್ಯಥಾ
        #define os_task_switch_is_pended( _cpu_ )    ( false )
    #endif
#endif

#endif // FREERTOS_CONFIG_XTENSA_H
