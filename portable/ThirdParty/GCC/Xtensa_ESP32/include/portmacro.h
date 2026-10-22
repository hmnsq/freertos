/*
 * SPDX-FileCopyrightText: 2017 Amazon.com, Inc. or its affiliates
 * SPDX-FileCopyrightText: 2015-2019 Cadence Design Systems, Inc.
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

/*
 * Copyright (c) 2015-2019 Cadence Design Systems, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#यदि_अपरिभाषितम् PORTMACRO_H
#परिभाषय PORTMACRO_H

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    बाह्य "C" {
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अपरिभाषितम् __ASSEMBLER__

    #अन्तर्भाव <stdint.h>

    #अन्तर्भाव <xtensa/hal.h>
    #अन्तर्भाव <xtensa/config/core.h>
    #अन्तर्भाव <xtensa/config/system.h> /* required for XSHAL_CLIB */
    #अन्तर्भाव <xtensa/xtruntime.h>
    #अन्तर्भाव "soc/spinlock.h"
    #अन्तर्भाव "esp_timer.h" /* required for FreeRTOS run time stats */
    #अन्तर्भाव "esp_system.h"
    #अन्तर्भाव "esp_idf_version.h"
    #अन्तर्भाव "esp_heap_caps.h"

/* TODO: Resolve build warnings generated due to this header inclusion */
    #अन्तर्भाव "hal/cpu_hal.h"

/* TODO: These includes are not directly used in this file. They are kept into to prevent a breaking change. Remove these. */
    #अन्तर्भाव <limits.h>
    #अन्तर्भाव <xtensa/xtensa_api.h>

    #अन्तर्भाव "soc/cpu.h"
    #अन्तर्भाव "soc/soc_memory_layout.h"
    #यदि ( ESP_IDF_संस्करणम् >= ESP_IDF_संस्करणम्_VAL( 4, 2, 0 ) )
        #अन्तर्भाव "soc/compare_set.h"
    #यदि_अन्तः /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

/*#include "xtensa_context.h" */

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */

    #परिभाषय पत्तनम्_CHAR          int8_t
    #परिभाषय पत्तनम्_FLOAT         भिन्न
    #परिभाषय पत्तनम्_DOUBLE        द्विगुण
    #परिभाषय पत्तनम्_LONG          int32_t
    #परिभाषय पत्तनम्_SHORT         int16_t
    #परिभाषय पत्तनम्_राशिः_TYPE    uint8_t
    #परिभाषय पत्तनम्_आधारः_TYPE     पूर्णाङ्क

    प्रकारनिर्देश पत्तनम्_राशिः_TYPE           राशिः_Type_t;
    प्रकारनिर्देश पत्तनम्_आधारः_TYPE            आधारः_Type_t;
    प्रकारनिर्देश अचिह्नित पत्तनम्_आधारः_TYPE   UBaseType_t;

    #यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_16_द्वयङ्काः )
        प्रकारनिर्देश uint16_t             TickType_t;
        #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffff
    #नोचेद्यदि ( config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः == TICK_TYPE_विस्तारः_32_द्वयङ्काः )
        प्रकारनिर्देश uint32_t             TickType_t;
        #परिभाषय पत्तनम्_MAX_DELAY    ( TickType_t ) 0xffffffffUL
    #अन्यथा
        #दोषः config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः समुच्चयः गन्तव्यम् unsupported tick type विस्तारः.
    #यदि_अन्तः
/*-----------------------------------------------------------*/

/* portbenchmark */
    #अन्तर्भाव "portbenchmark.h"

    #अन्तर्भाव "sdkconfig.h"
    #अन्तर्भाव "esp_attr.h"

/* "mux" data structure (spinlock) */
    प्रकारनिर्देश spinlock_t पत्तनम्_MUX_TYPE;                                /**< Spinlock type used by FreeRTOS critical sections */
    #परिभाषय पत्तनम्_MUX_INITIALIZER_UNLOCKED    SPINLOCK_INITIALIZER    /**< Spinlock initializer */
    #परिभाषय पत्तनम्_MUX_FREE_VAL                SPINLOCK_FREE           /**< Spinlock is free. [refactor-todo] check if this is still required */
    #परिभाषय पत्तनम्_MUX_NO_TIMEOUT              SPINLOCK_WAIT_FOREVER   /**< When passed for 'timeout_cycles', spin forever if necessary. [refactor-todo] check if this is still required */
    #परिभाषय पत्तनम्_MUX_TRY_तालकम्                SPINLOCK_NO_WAIT        /**< Try to acquire the spinlock a single time only. [refactor-todo] check if this is still required */
    #परिभाषय पत्तनम्_MUX_INITIALIZE( mux )    spinlock_initialize( mux ) /*< Initialize a spinlock to its unlocked state */

    #परिभाषय पत्तनम्_CRITICAL_NESTING_अन्तर्_TCB     1

/*
 * Modifications to portENTER_CRITICAL.
 *
 * For an introduction, see "Critical Sections & Disabling Interrupts" in docs/api-guides/freertos-smp.rst
 *
 * The original portENTER_CRITICAL only disabled the ISRs. This is enough for single-CPU operation: by
 * disabling the interrupts, there is no task switch so no other tasks can meddle in the data, and because
 * interrupts are disabled, ISRs can't corrupt data structures either.
 *
 * For multiprocessing, things get a bit more hairy. First of all, disabling the interrupts doesn't stop
 * the tasks or ISRs on the other processors meddling with our CPU. For tasks, this is solved by adding
 * a spinlock to the portENTER_CRITICAL macro. A task running on the other CPU accessing the same data will
 * spinlock in the portENTER_CRITICAL code until the first CPU is done.
 *
 * For ISRs, we now also need muxes: while portENTER_CRITICAL disabling interrupts will stop ISRs on the same
 * CPU from meddling with the data, it does not stop interrupts on the other cores from interfering with the
 * data. For this, we also use a spinlock in the routines called by the ISR, but these spinlocks
 * do not disable the interrupts (because they already are).
 *
 * This all assumes that interrupts are either entirely disabled or enabled. Interrupt priority levels
 * will break this scheme.
 *
 * Remark: For the ESP32, portENTER_CRITICAL and portENTER_CRITICAL_ISR both alias vPortEnterCritical, meaning
 * that either function can be called both from ISR as well as task context. This is not standard FreeRTOS
 * behaviour; please keep this in mind if you need any compatibility with other FreeRTOS implementations.
 */
    शून्य v_पत्तनम्_CPUInitialize_Mutex( पत्तनम्_MUX_TYPE * mux );
    #यदि_परिभाषितम् CONFIG_FREERTOS_PORTMUX_DEBUG
        #दोषः CONFIG_FREERTOS_PORTMUX_DEBUG not supported अन्तर् Amazon FreeRTOS
    #यदि_अन्तः

    शून्य vTaskExitCritical();
    शून्य vTaskEnterCritical();
    स्थिर अन्तःस्थ शून्य v_पत्तनम्_Consume_Spinlock_Arg( पूर्णाङ्क अप्रयुक्तम्,
                                                ... )
    {
    }

/** @brief Acquire a portmux spinlock with a timeout
 *
 * @param mux Pointer to portmux to acquire.
 * @param timeout_cycles Timeout to spin, in CPU cycles. Pass portMUX_NO_TIMEOUT to wait forever,
 * portMUX_TRY_LOCK to try a single time to acquire the lock.
 *
 * @return true if mutex is successfully acquired, false on timeout.
 */
    bool v_पत्तनम्_CPUAcquire_Mutex_Timeout( पत्तनम्_MUX_TYPE * mux,
                                      पूर्णाङ्क timeout_आवृत्तयः );
    शून्य v_पत्तनम्_CPURelease_Mutex( पत्तनम्_MUX_TYPE * mux );

    #परिभाषय पत्तनम्_ENTER_CRITICAL( ... )        कुरु { vTaskEnterCritical(); v_पत्तनम्_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } यावत्( 0 )
    #परिभाषय पत्तनम्_EXIT_CRITICAL( ... )         कुरु { vTaskExitCritical(); v_पत्तनम्_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } यावत्( 0 )


    #परिभाषय पत्तनम्_ENTER_CRITICAL_ISR( mux )    v_पत्तनम्_CPUAcquire_Mutex_Timeout( mux, पत्तनम्_MUX_NO_TIMEOUT )
    #परिभाषय पत्तनम्_EXIT_CRITICAL_ISR( mux )     v_पत्तनम्_CPURelease_Mutex( mux )

    #परिभाषय पत्तनम्_ENTER_CRITICAL_SAFE( mux ) \
    कुरु {                                   \
        यदि( x_पत्तनम्_अन्तर्_Isr_Context() ) {        \
            पत्तनम्_ENTER_CRITICAL_ISR( mux ); \
        }                                  \
        अन्यथा {                             \
            पत्तनम्_ENTER_CRITICAL( mux );     \
        }                                  \
    } यावत्( 0 )

    #परिभाषय पत्तनम्_EXIT_CRITICAL_SAFE( mux ) \
    कुरु {                                  \
        यदि( x_पत्तनम्_अन्तर्_Isr_Context() ) {       \
            पत्तनम्_EXIT_CRITICAL_ISR( mux ); \
        }                                 \
        अन्यथा {                            \
            पत्तनम्_EXIT_CRITICAL( mux );     \
        }                                 \
    } यावत्( 0 )

    #परिभाषय पत्तनम्_ASSERT_IF_अन्तर्_ISR()    v_पत्तनम्_Assert_If_अन्तर्_ISR()
    शून्य v_पत्तनम्_Assert_If_अन्तर्_ISR( शून्य );

/* Critical section management. NW-TODO: replace XTOS_SET_INTLEVEL with more efficient version, if any? */
/* These cannot be nested. They should be used with a lot of care and cannot be called from interrupt level. */
/* */
/* Only applies to one CPU. See notes above & below for reasons not to use these. */
    #परिभाषय पत्तनम्_DISABLE_INTERRUPTS()    कुरु { XTOS_समुच्चयः_INTLEVEL( XCHAL_EXCM_LEVEL ); portbenchmark_व्यवधानम्_DISABLE(); } यावत्( 0 )
    #परिभाषय पत्तनम्_ENABLE_INTERRUPTS()     कुरु { portbenchmark_व्यवधानम्_RESTORE( 0 ); XTOS_समुच्चयः_INTLEVEL( 0 ); } यावत्( 0 )

/* Cleaner solution allows nested interrupts disabling and restoring via local registers or stack. */
/* They can be called from interrupts too. */
/* WARNING: Only applies to current CPU. See notes above. */
    स्थिर अन्तःस्थ UBaseType_t __attribute__( ( always_inline ) ) x_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR( शून्य )
    {
        UBaseType_t पूर्व_int_level = XTOS_समुच्चयः_INTLEVEL( XCHAL_EXCM_LEVEL );

        portbenchmark_व्यवधानम्_DISABLE();
        प्रत्यागम पूर्व_int_level;
    }

    स्थिर अन्तःस्थ शून्य __attribute__( ( always_inline ) ) v_पत्तनम्_Clear_व्यवधानम्_आवरणम्_From_ISR( UBaseType_t पूर्व_level )
    {
        portbenchmark_व्यवधानम्_RESTORE( पूर्व_level );
        XTOS_RESTORE_JUST_INTLEVEL( पूर्व_level );
    }

/* These FreeRTOS versions are similar to the nested versions above */
    #परिभाषय पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_FROM_ISR()                  x_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्_From_ISR()
    #परिभाषय पत्तनम्_CLEAR_व्यवधानम्_आवरणम्_FROM_ISR( पूर्व_level )    v_पत्तनम्_Clear_व्यवधानम्_आवरणम्_From_ISR( पूर्व_level )

/*Because the ROM routines don't necessarily handle a stack in external RAM correctly, we force */
/*the stack memory to always be internal. */
    #परिभाषय पत्तनम्_Tcb_स्मृतिः_Caps      ( MALLOC_CAP_आन्तरिकम् | MALLOC_CAP_8BIT )
    #परिभाषय पत्तनम्_राशिः_स्मृतिः_Caps    ( MALLOC_CAP_आन्तरिकम् | MALLOC_CAP_8BIT )

    #परिभाषय pv_पत्तनम्_Malloc_Tcb_Mem( आकार )        heap_caps_malloc( आकार, पत्तनम्_Tcb_स्मृतिः_Caps )
    #परिभाषय pv_पत्तनम्_Malloc_राशिः_Mem( आकार )      heap_caps_malloc( आकार, पत्तनम्_राशिः_स्मृतिः_Caps )

/*xTaskCreateStatic uses these functions to check incoming memory. */
    #परिभाषय पत्तनम्_VALID_TCB_MEM( ptr )          ( esp_ptr_आन्तरिकम्( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #यदि_परिभाषितम् CONFIG_SPIRAM_ALLOW_राशिः_EXTERNAL_स्मृतिः
        #परिभाषय पत्तनम्_VALID_राशिः_MEM( ptr )    esp_ptr_byte_accessible( ptr )
    #अन्यथा
        #परिभाषय पत्तनम्_VALID_राशिः_MEM( ptr )    ( esp_ptr_आन्तरिकम्( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #यदि_अन्तः

/*
 * Wrapper for the Xtensa compare-and-set instruction. This subroutine will atomically compare
 * *addr to 'compare'. If *addr == compare, *addr is set to *set. *set is updated with the previous
 * value of *addr (either 'compare' or some other value.)
 *
 * Warning: From the ISA docs: in some (unspecified) cases, the s32c1i instruction may return the
 * *bitwise inverse* of the old mem if the mem wasn't written. This doesn't seem to happen on the
 * ESP32 (portMUX assertions would fail).
 */
    स्थिर अन्तःस्थ शून्य ux_पत्तनम्_Compare_समुच्चयः( चञ्चल uint32_t * addr,
                                         uint32_t compare,
                                         uint32_t * समुच्चयः )
    {
        #यदि ( ESP_IDF_संस्करणम् < ESP_IDF_संस्करणम्_VAL( 4, 2, 0 ) )
            __asm__ __volatile__ (
                "WSR       %2,SCOMPARE1 \n"
                "S32C1I     %0, %1, 0   \n"
                : "=r" ( *समुच्चयः )
                : "r" ( addr ), "r" ( compare ), "0" ( *समुच्चयः )
                );
        #अन्यथा
            #यदि ( XCHAL_HAVE_S32C1I > 0 )
                __asm__ __volatile__ (
                    "WSR        %2,SCOMPARE1 \n"
                    "S32C1I     %0, %1, 0    \n"
                    : "=r" ( *समुच्चयः )
                    : "r" ( addr ), "r" ( compare ), "0" ( *समुच्चयः )
                    );
            #अन्यथा
                /* No S32C1I, so do this by disabling and re-enabling interrupts (slower) */
                uint32_t intlevel, old_मानम्;
                __asm__ __volatile__ ( "rsil %0, " XTSTR( XCHAL_EXCM_LEVEL ) "\n"
                                       : "=r" ( intlevel ) );

                old_मानम् = *addr;

                यदि( old_मानम् == compare )
                {
                    *addr = *समुच्चयः;
                }

                __asm__ __volatile__ ( "memw \n"
                                       "wsr %0, ps\n"
                                       : : "r" ( intlevel ) );

                *समुच्चयः = old_मानम्;
            #यदि_अन्तः /* if ( XCHAL_HAVE_S32C1I > 0 ) */
        #यदि_अन्तः /* #if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)) */
    }

    #यदि ( ESP_IDF_संस्करणम् < ESP_IDF_संस्करणम्_VAL( 4, 2, 0 ) )
        शून्य ux_पत्तनम्_Compare_समुच्चयः_Extram( चञ्चल uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * समुच्चयः );
    #अन्यथा
        स्थिर अन्तःस्थ शून्य ux_पत्तनम्_Compare_समुच्चयः_Extram( चञ्चल uint32_t * addr,
                                                   uint32_t compare,
                                                   uint32_t * समुच्चयः )
        {
            #यदि defined( CONFIG_SPIRAM )
                compare_and_समुच्चयः_extram( addr, compare, समुच्चयः );
            #यदि_अन्तः
        }
    #यदि_अन्तः /* if ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) ) */

/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #परिभाषय पत्तनम्_राशिः_GROWTH      ( -1 )
    #परिभाषय पत्तनम्_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_दरः_HZ )
    #परिभाषय पत्तनम्_BYTE_ALIGNMENT    4
    #परिभाषय पत्तनम्_NOP()    XT_NOP()
/*-----------------------------------------------------------*/

/* Fine resolution time */
    #परिभाषय पत्तनम्_GET_सततम्_TIME_गणक_मानम्()    xthal_get_ccount()
/*ccount or esp_timer are initialized elsewhere */
    #परिभाषय पत्तनम्_CONFIGURE_TIMER_FOR_सततम्_TIME_STATS()

    #यदि_परिभाषितम् CONFIG_FREERTOS_सततम्_TIME_STATS_USING_ESP_TIMER
/* Coarse resolution time (us) */
        #परिभाषय पत्तनम्_ALT_GET_सततम्_TIME_गणक_मानम्( x )    कुरु { x = ( uint32_t ) esp_timer_get_time(); } यावत्( 0 )
    #यदि_अन्तः



/* Kernel utilities. */
    शून्य v_पत्तनम्_Yield( शून्य );
    शून्य v_पत्तनम्_Evaluate_Yield_From_ISR( पूर्णाङ्क argc,
                                    ... );
    शून्य frxt_सज्जता_switch( शून्य );

/* Macro to count number of arguments of a __VA_ARGS__ used to support portYIELD_FROM_ISR with,
 * or without arguments. The macro counts only 0 or 1 arguments.
 *
 * In the future, we want to switch to C++20. We also want to become compatible with clang.
 * Hence, we provide two versions of the following macros which are using variadic arguments.
 * The first one is using the GNU extension ##__VA_ARGS__. The second one is using the C++20 feature __VA_OPT__(,).
 * This allows users to compile their code with standard C++20 enabled instead of the GNU extension.
 * Below C++20, we haven't found any good alternative to using ##__VA_ARGS__.
 */
    #यदि defined( __cplusplus ) && ( __cplusplus > 201703L )
        #परिभाषय पत्तनम्_GET_तर्कः_गणनम्( ... )                        पत्तनम्_GET_तर्कः_गणनम्_INNER( 0 __VA_OPT__(, ) __VA_ARGS__, 1, 0 )
    #अन्यथा
        #परिभाषय पत्तनम्_GET_तर्कः_गणनम्( ... )                        पत्तनम्_GET_तर्कः_गणनम्_INNER( 0, ## __VA_ARGS__, 1, 0 )
    #यदि_अन्तः
    #परिभाषय पत्तनम्_GET_तर्कः_गणनम्_INNER( zero, one, गणनम्, ... )    गणनम्

    _Static_assert( पत्तनम्_GET_तर्कः_गणनम्() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments" );
    _Static_assert( पत्तनम्_GET_तर्कः_गणनम्( 1 ) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument" );

    #परिभाषय पत्तनम्_YIELD()    v_पत्तनम्_Yield()

/* The macro below could be used when passing a single argument, or without any argument,
 * it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 * might result in undesired behaviour
 */
    #यदि defined( __cplusplus ) && ( __cplusplus > 201703L )
        #परिभाषय पत्तनम्_YIELD_FROM_ISR( ... )    v_पत्तनम्_Evaluate_Yield_From_ISR( पत्तनम्_GET_तर्कः_गणनम्( __VA_ARGS__ ) __VA_OPT__(, ) __VA_ARGS__ )
    #अन्यथा
        #परिभाषय पत्तनम्_YIELD_FROM_ISR( ... )    v_पत्तनम्_Evaluate_Yield_From_ISR( पत्तनम्_GET_तर्कः_गणनम्( __VA_ARGS__ ), ## __VA_ARGS__ )
    #यदि_अन्तः

    स्थिर अन्तःस्थ आधारः_Type_t x_पत्तनम्_Get_Core_ID();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #परिभाषय पत्तनम्_TASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
    #परिभाषय पत्तनम्_TASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

/* When coprocessors are defined, we to maintain a pointer to coprocessors area. */
/* We currently use a hack: redefine field xMPU_SETTINGS in TCB block as a structure that can hold: */
/* MPU wrappers, coprocessor area pointer, trace code structure, and more if needed. */
/* The field is normally used for memory protection. FreeRTOS should create another general purpose field. */
    प्रकारनिर्देश संरचना
    {
        #यदि XCHAL_CP_अङ्कः > 0
            चञ्चल राशिः_Type_t * coproc_area; /* Pointer to coprocessor save area; MUST BE FIRST */
        #यदि_अन्तः

        #यदि पत्तनम्_USING_MPU_WRAPPERS
            /* Define here mpu_settings, which is port dependent */
            पूर्णाङ्क mpu_setting; /* Just a dummy example here; MPU not ported to Xtensa yet */
        #यदि_अन्तः

        #यदि configUSE_TRACE_FACILITY_2
            संरचना
            {
                /* Cf. porttraceStamp() */
                पूर्णाङ्क taskstamp;      /* Stamp from inside task to see where we are */
                पूर्णाङ्क taskstampcount; /* A counter usually incremented when we restart the task's loop */
            } porttrace;
        #यदि_अन्तः
    } xMPU_SETTINGS;

/* Main hack to use MPU_wrappers even when no MPU is defined (warning: mpu_setting should not be accessed; otherwise move this above xMPU_SETTINGS) */
    #यदि ( XCHAL_CP_अङ्कः > 0 || configUSE_TRACE_FACILITY_2 ) && !पत्तनम्_USING_MPU_WRAPPERS /* If MPU wrappers not used, we still need to allocate coproc area */
        #अपरिभाषय पत्तनम्_USING_MPU_WRAPPERS
        #परिभाषय पत्तनम्_USING_MPU_WRAPPERS    1                                           /* Enable it to allocate coproc area */
        #परिभाषय MPU_WRAPPERS_H                                                        /* Override mpu_wrapper.h to disable unwanted code */
        #परिभाषय PRIVILEGED_FUNCTION
        #परिभाषय PRIVILEGED_दत्त
    #यदि_अन्तः

    शून्य vApplicationSleep( TickType_t xExpectedIdleTime );

    #परिभाषय पत्तनम्_SUPPRESS_TICKS_AND_SLEEP( idleTime )    vApplicationSleep( idleTime )

    शून्य _xt_coproc_release( चञ्चल शून्य * coproc_sa_आधारः );

/*-----------------------------------------------------------*/

    #यदि ( ESP_IDF_संस्करणम् >= ESP_IDF_संस्करणम्_VAL( 4, 2, 0 ) )
        /* Architecture specific optimisations. */

        #यदि config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
            #यदि ( configMAX_PRIORITIES > 32 )
                #दोषः config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION can only be समुच्चयः गन्तव्यम् 1 when configMAX_PRIORITIES is less than or equal गन्तव्यम् 32.  It is very rare that a system requires अधिकम् than 10 गन्तव्यम् 15 different priorities as tasks that share a प्राथमिकता will time खण्डिका.
            #यदि_अन्तः

/* Store/clear the ready priorities in a bit map. */
            #परिभाषय पत्तनम्_लेखः_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_प्राथमिकता ) )
            #परिभाषय पत्तनम्_RESET_READY_प्राथमिकता( ux_प्राथमिकता, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_प्राथमिकता ) )

/*-----------------------------------------------------------*/

            #परिभाषय पत्तनम्_GET_HIGHEST_प्राथमिकता( ux_शिखरम्_प्राथमिकता, uxReadyPriorities )    ux_शिखरम्_प्राथमिकता = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )

        #यदि_अन्तः /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #यदि_अन्तः /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

/*-----------------------------------------------------------*/

/*
 * Map to the memory management routines required for the port.
 *
 * Note that libc standard malloc/free are also available for
 * non-FreeRTOS-specific code, and behave the same as
 * pvPortMalloc()/vPortFree().
 */
    #परिभाषय pv_पत्तनम्_Malloc                       heap_caps_malloc_default
    #परिभाषय v_पत्तनम्_Free                          heap_caps_free
    #परिभाषय x_पत्तनम्_Get_Free_Heap_आकार               esp_get_free_heap_आकार
    #परिभाषय x_पत्तनम्_Get_Minimum_Ever_Free_Heap_आकार    esp_get_minimum_free_heap_आकार

    #यदि ( ESP_IDF_संस्करणम् < ESP_IDF_संस्करणम्_VAL( 4, 2, 0 ) )

/*
 * Send an interrupt to another core in order to make the task running
 * on it yield for a higher-priority task.
 */

        शून्य v_पत्तनम्_Yield_Other_Core( आधारः_Type_t coreid ) PRIVILEGED_FUNCTION;

    #यदि_अन्तः /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

/*
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack
 * watchpoint around.
 */
    शून्य v_पत्तनम्_समुच्चयः_राशिः_Watchpoint( शून्य * px_राशिः_Start );

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
    आधारः_Type_t x_पत्तनम्_अन्तर्_Isr_Context();


/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
    आधारः_Type_t x_पत्तनम्_Interrupted_From_ISRContext();

/*
 * The structures and methods of manipulating the MPU are contained within the
 * port layer.
 *
 * Fills the xMPUSettings structure with the memory region information
 * contained in xRegions.
 */
    #यदि ( पत्तनम्_USING_MPU_WRAPPERS == 1 )
        संरचना x_स्मृतिः_REGION;
        शून्य v_पत्तनम्_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                        ध्रुव संरचना x_स्मृतिः_REGION * ध्रुव xRegions,
                                        राशिः_Type_t * px_Bottom_सम्बन्धि_राशिः,
                                        config_राशिः_गभीरता_TYPE ux_राशिः_गभीरता ) PRIVILEGED_FUNCTION;
        शून्य v_पत्तनम्_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings );
    #यदि_अन्तः

/* Multi-core: get current core ID */
    स्थिर अन्तःस्थ आधारः_Type_t IRAM_ATTR x_पत्तनम्_Get_Core_ID()
    {
        प्रत्यागम ( uint32_t ) cpu_hal_get_core_id();
    }

/* Get tick rate per second */
    uint32_t x_पत्तनम्_Get_Tick_दरः_Hz( शून्य );

    स्थिर अन्तःस्थ bool IRAM_ATTR x_पत्तनम्_Can_Yield( शून्य )
    {
        uint32_t ps_reg = 0;

        /*Get the current value of PS (processor status) register */
        RSR( PS, ps_reg );

        /*
         * intlevel = (ps_reg & 0xf);
         * excm  = (ps_reg >> 4) & 0x1;
         * CINTLEVEL is max(excm * EXCMLEVEL, INTLEVEL), where EXCMLEVEL is 3.
         * However, just return true, only intlevel is zero.
         */

        प्रत्यागम( ( ps_reg & PS_INTLEVEL_आवरणम् ) == 0 );
    }

/* porttrace */
    #यदि configUSE_TRACE_FACILITY_2
        #अन्तर्भाव "porttrace.h"
    #यदि_अन्तः

/* configASSERT_2 if requested */
    #यदि configASSERT_2
        #अन्तर्भाव <stdio.h>
        शून्य निर्गच्छ( पूर्णाङ्क );
        #परिभाषय configASSERT( x )    यदि( !( x ) ) { porttracePrint( -1 ); प्रारूप_लिख( "\nAssertion failed in %s:%d\n", __FILE__, __LINE__ ); निर्गच्छ( -1 ); }
    #यदि_अन्तः

/* Barriers */
    #परिभाषय पत्तनम्_स्मृतिः_BARRIER()    __asm चञ्चल ( "" ::: "memory" )


#यदि_अन्तः // __ASSEMBLER__

/* *INDENT-OFF* */
#यदि_परिभाषितम् __cplusplus
    }
#यदि_अन्तः
/* *INDENT-ON* */

#यदि_अन्तः /* PORTMACRO_H */
