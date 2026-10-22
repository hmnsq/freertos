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

#నిర్వచితం_కాకపోతే PORTMACRO_H
#నిర్వచించు PORTMACRO_H

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    బాహ్య "C" {
#అయితే_ముగింపు
/* *INDENT-ON* */

#నిర్వచితం_కాకపోతే __ASSEMBLER__

    #అన్తర్భావ <stdint.h>

    #అన్తర్భావ <xtensa/hal.h>
    #అన్తర్భావ <xtensa/config/core.h>
    #అన్తర్భావ <xtensa/config/system.h> /* required for XSHAL_CLIB */
    #అన్తర్భావ <xtensa/xtruntime.h>
    #అన్తర్భావ "soc/spinlock.h"
    #అన్తర్భావ "esp_timer.h" /* required for FreeRTOS run time stats */
    #అన్తర్భావ "esp_system.h"
    #అన్తర్భావ "esp_idf_version.h"
    #అన్తర్భావ "esp_heap_caps.h"

/* TODO: Resolve build warnings generated due to this header inclusion */
    #అన్తర్భావ "hal/cpu_hal.h"

/* TODO: These includes are not directly used in this file. They are kept into to prevent a breaking change. Remove these. */
    #అన్తర్భావ <limits.h>
    #అన్తర్భావ <xtensa/xtensa_api.h>

    #అన్తర్భావ "soc/cpu.h"
    #అన్తర్భావ "soc/soc_memory_layout.h"
    #ఒకవేళ ( ESP_IDF_సంస్కరణ >= ESP_IDF_సంస్కరణ_VAL( 4, 2, 0 ) )
        #అన్తర్భావ "soc/compare_set.h"
    #అయితే_ముగింపు /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

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

    #నిర్వచించు పోర్టు_CHAR          int8_t
    #నిర్వచించు పోర్టు_FLOAT         దశాంశం
    #నిర్వచించు పోర్టు_DOUBLE        ద్విగుణ
    #నిర్వచించు పోర్టు_LONG          int32_t
    #నిర్వచించు పోర్టు_SHORT         int16_t
    #నిర్వచించు పోర్టు_దొంతర_TYPE    uint8_t
    #నిర్వచించు పోర్టు_పునాది_TYPE     పూర్ణాంకం

    రకనిర్వచనం పోర్టు_దొంతర_TYPE           దొంతర_Type_t;
    రకనిర్వచనం పోర్టు_పునాది_TYPE            పునాది_Type_t;
    రకనిర్వచనం గుర్తులేని పోర్టు_పునాది_TYPE   UBaseType_t;

    #ఒకవేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_16_బిట్లు )
        రకనిర్వచనం uint16_t             TickType_t;
        #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffff
    #లేదావేళ ( config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు == TICK_TYPE_వెడల్పు_32_బిట్లు )
        రకనిర్వచనం uint32_t             TickType_t;
        #నిర్వచించు పోర్టు_MAX_DELAY    ( TickType_t ) 0xffffffffUL
    #లేకపోతే
        #దోషం config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు సమితి గమ్యం unsupported tick type వెడల్పు.
    #అయితే_ముగింపు
/*-----------------------------------------------------------*/

/* portbenchmark */
    #అన్తర్భావ "portbenchmark.h"

    #అన్తర్భావ "sdkconfig.h"
    #అన్తర్భావ "esp_attr.h"

/* "mux" data structure (spinlock) */
    రకనిర్వచనం spinlock_t పోర్టు_MUX_TYPE;                                /**< Spinlock type used by FreeRTOS critical sections */
    #నిర్వచించు పోర్టు_MUX_INITIALIZER_UNLOCKED    SPINLOCK_INITIALIZER    /**< Spinlock initializer */
    #నిర్వచించు పోర్టు_MUX_FREE_VAL                SPINLOCK_FREE           /**< Spinlock is free. [refactor-todo] check if this is still required */
    #నిర్వచించు పోర్టు_MUX_NO_TIMEOUT              SPINLOCK_WAIT_FOREVER   /**< When passed for 'timeout_cycles', spin forever if necessary. [refactor-todo] check if this is still required */
    #నిర్వచించు పోర్టు_MUX_TRY_తాళం                SPINLOCK_NO_WAIT        /**< Try to acquire the spinlock a single time only. [refactor-todo] check if this is still required */
    #నిర్వచించు పోర్టు_MUX_INITIALIZE( mux )    spinlock_initialize( mux ) /*< Initialize a spinlock to its unlocked state */

    #నిర్వచించు పోర్టు_CRITICAL_NESTING_లోపల_TCB     1

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
    శూన్య v_పోర్టు_CPUInitialize_Mutex( పోర్టు_MUX_TYPE * mux );
    #నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
        #దోషం CONFIG_FREERTOS_PORTMUX_DEBUG not supported లోపల Amazon FreeRTOS
    #అయితే_ముగింపు

    శూన్య vTaskExitCritical();
    శూన్య vTaskEnterCritical();
    స్థిర అంతఃవరుస శూన్య v_పోర్టు_Consume_Spinlock_Arg( పూర్ణాంకం వాడని,
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
    bool v_పోర్టు_CPUAcquire_Mutex_Timeout( పోర్టు_MUX_TYPE * mux,
                                      పూర్ణాంకం timeout_చక్రాలు );
    శూన్య v_పోర్టు_CPURelease_Mutex( పోర్టు_MUX_TYPE * mux );

    #నిర్వచించు పోర్టు_ENTER_CRITICAL( ... )        చేయి { vTaskEnterCritical(); v_పోర్టు_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } అయితే( 0 )
    #నిర్వచించు పోర్టు_EXIT_CRITICAL( ... )         చేయి { vTaskExitCritical(); v_పోర్టు_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } అయితే( 0 )


    #నిర్వచించు పోర్టు_ENTER_CRITICAL_ISR( mux )    v_పోర్టు_CPUAcquire_Mutex_Timeout( mux, పోర్టు_MUX_NO_TIMEOUT )
    #నిర్వచించు పోర్టు_EXIT_CRITICAL_ISR( mux )     v_పోర్టు_CPURelease_Mutex( mux )

    #నిర్వచించు పోర్టు_ENTER_CRITICAL_సురక్షిత( mux ) \
    చేయి {                                   \
        ఒకవేళ( x_పోర్టు_లోపల_Isr_Context() ) {        \
            పోర్టు_ENTER_CRITICAL_ISR( mux ); \
        }                                  \
        లేకపోతే {                             \
            పోర్టు_ENTER_CRITICAL( mux );     \
        }                                  \
    } అయితే( 0 )

    #నిర్వచించు పోర్టు_EXIT_CRITICAL_సురక్షిత( mux ) \
    చేయి {                                  \
        ఒకవేళ( x_పోర్టు_లోపల_Isr_Context() ) {       \
            పోర్టు_EXIT_CRITICAL_ISR( mux ); \
        }                                 \
        లేకపోతే {                            \
            పోర్టు_EXIT_CRITICAL( mux );     \
        }                                 \
    } అయితే( 0 )

    #నిర్వచించు పోర్టు_ASSERT_IF_లోపల_ISR()    v_పోర్టు_Assert_If_లోపల_ISR()
    శూన్య v_పోర్టు_Assert_If_లోపల_ISR( శూన్య );

/* Critical section management. NW-TODO: replace XTOS_SET_INTLEVEL with more efficient version, if any? */
/* These cannot be nested. They should be used with a lot of care and cannot be called from interrupt level. */
/* */
/* Only applies to one CPU. See notes above & below for reasons not to use these. */
    #నిర్వచించు పోర్టు_DISABLE_INTERRUPTS()    చేయి { XTOS_సమితి_INTLEVEL( XCHAL_EXCM_LEVEL ); portbenchmark_అంతరాయం_DISABLE(); } అయితే( 0 )
    #నిర్వచించు పోర్టు_ENABLE_INTERRUPTS()     చేయి { portbenchmark_అంతరాయం_RESTORE( 0 ); XTOS_సమితి_INTLEVEL( 0 ); } అయితే( 0 )

/* Cleaner solution allows nested interrupts disabling and restoring via local registers or stack. */
/* They can be called from interrupts too. */
/* WARNING: Only applies to current CPU. See notes above. */
    స్థిర అంతఃవరుస UBaseType_t __attribute__( ( always_inline ) ) x_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR( శూన్య )
    {
        UBaseType_t prev_int_level = XTOS_సమితి_INTLEVEL( XCHAL_EXCM_LEVEL );

        portbenchmark_అంతరాయం_DISABLE();
        తిరిగి prev_int_level;
    }

    స్థిర అంతఃవరుస శూన్య __attribute__( ( always_inline ) ) v_పోర్టు_Clear_అంతరాయం_ముసుగు_From_ISR( UBaseType_t prev_level )
    {
        portbenchmark_అంతరాయం_RESTORE( prev_level );
        XTOS_RESTORE_JUST_INTLEVEL( prev_level );
    }

/* These FreeRTOS versions are similar to the nested versions above */
    #నిర్వచించు పోర్టు_సమితి_అంతరాయం_ముసుగు_FROM_ISR()                  x_పోర్టు_సమితి_అంతరాయం_ముసుగు_From_ISR()
    #నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు_FROM_ISR( prev_level )    v_పోర్టు_Clear_అంతరాయం_ముసుగు_From_ISR( prev_level )

/*Because the ROM routines don't necessarily handle a stack in external RAM correctly, we force */
/*the stack memory to always be internal. */
    #నిర్వచించు పోర్టు_Tcb_జ్ఞాపకం_Caps      ( MALLOC_CAP_అంతర్గత | MALLOC_CAP_8_బిట్టు )
    #నిర్వచించు పోర్టు_దొంతర_జ్ఞాపకం_Caps    ( MALLOC_CAP_అంతర్గత | MALLOC_CAP_8_బిట్టు )

    #నిర్వచించు pv_పోర్టు_Malloc_Tcb_Mem( కొలత )        కుప్ప_caps_malloc( కొలత, పోర్టు_Tcb_జ్ఞాపకం_Caps )
    #నిర్వచించు pv_పోర్టు_Malloc_దొంతర_Mem( కొలత )      కుప్ప_caps_malloc( కొలత, పోర్టు_దొంతర_జ్ఞాపకం_Caps )

/*xTaskCreateStatic uses these functions to check incoming memory. */
    #నిర్వచించు పోర్టు_VALID_TCB_MEM( ptr )          ( esp_ptr_అంతర్గత( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #నిర్వచితమైతే CONFIG_SPIRAM_ALLOW_దొంతర_EXTERNAL_జ్ఞాపకం
        #నిర్వచించు పోర్టు_VALID_దొంతర_MEM( ptr )    esp_ptr_byte_accessible( ptr )
    #లేకపోతే
        #నిర్వచించు పోర్టు_VALID_దొంతర_MEM( ptr )    ( esp_ptr_అంతర్గత( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #అయితే_ముగింపు

/*
 * Wrapper for the Xtensa compare-and-set instruction. This subroutine will atomically compare
 * *addr to 'compare'. If *addr == compare, *addr is set to *set. *set is updated with the previous
 * value of *addr (either 'compare' or some other value.)
 *
 * Warning: From the ISA docs: in some (unspecified) cases, the s32c1i instruction may return the
 * *bitwise inverse* of the old mem if the mem wasn't written. This doesn't seem to happen on the
 * ESP32 (portMUX assertions would fail).
 */
    స్థిర అంతఃవరుస శూన్య ux_పోర్టు_Compare_సమితి( అస్థిర uint32_t * addr,
                                         uint32_t compare,
                                         uint32_t * సమితి )
    {
        #ఒకవేళ ( ESP_IDF_సంస్కరణ < ESP_IDF_సంస్కరణ_VAL( 4, 2, 0 ) )
            __asm__ __volatile__ (
                "WSR       %2,SCOMPARE1 \n"
                "S32C1I     %0, %1, 0   \n"
                : "=r" ( *సమితి )
                : "r" ( addr ), "r" ( compare ), "0" ( *సమితి )
                );
        #లేకపోతే
            #ఒకవేళ ( XCHAL_HAVE_S32C1I > 0 )
                __asm__ __volatile__ (
                    "WSR        %2,SCOMPARE1 \n"
                    "S32C1I     %0, %1, 0    \n"
                    : "=r" ( *సమితి )
                    : "r" ( addr ), "r" ( compare ), "0" ( *సమితి )
                    );
            #లేకపోతే
                /* No S32C1I, so do this by disabling and re-enabling interrupts (slower) */
                uint32_t intlevel, old_విలువ;
                __asm__ __volatile__ ( "rsil %0, " XTSTR( XCHAL_EXCM_LEVEL ) "\n"
                                       : "=r" ( intlevel ) );

                old_విలువ = *addr;

                ఒకవేళ( old_విలువ == compare )
                {
                    *addr = *సమితి;
                }

                __asm__ __volatile__ ( "memw \n"
                                       "wsr %0, ps\n"
                                       : : "r" ( intlevel ) );

                *సమితి = old_విలువ;
            #అయితే_ముగింపు /* if ( XCHAL_HAVE_S32C1I > 0 ) */
        #అయితే_ముగింపు /* #if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)) */
    }

    #ఒకవేళ ( ESP_IDF_సంస్కరణ < ESP_IDF_సంస్కరణ_VAL( 4, 2, 0 ) )
        శూన్య ux_పోర్టు_Compare_సమితి_Extram( అస్థిర uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * సమితి );
    #లేకపోతే
        స్థిర అంతఃవరుస శూన్య ux_పోర్టు_Compare_సమితి_Extram( అస్థిర uint32_t * addr,
                                                   uint32_t compare,
                                                   uint32_t * సమితి )
        {
            #ఒకవేళ defined( CONFIG_SPIRAM )
                compare_and_సమితి_extram( addr, compare, సమితి );
            #అయితే_ముగింపు
        }
    #అయితే_ముగింపు /* if ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) ) */

/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #నిర్వచించు పోర్టు_దొంతర_GROWTH      ( -1 )
    #నిర్వచించు పోర్టు_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_రేటు_HZ )
    #నిర్వచించు పోర్టు_BYTE_ALIGNMENT    4
    #నిర్వచించు పోర్టు_NOP()    XT_NOP()
/*-----------------------------------------------------------*/

/* Fine resolution time */
    #నిర్వచించు పోర్టు_GET_నిరంతరం_సమయం_COUNTER_విలువ()    xthal_get_ccount()
/*ccount or esp_timer are initialized elsewhere */
    #నిర్వచించు పోర్టు_CONFIGURE_TIMER_FOR_నిరంతరం_సమయం_STATS()

    #నిర్వచితమైతే CONFIG_FREERTOS_నిరంతరం_సమయం_STATS_USING_ESP_TIMER
/* Coarse resolution time (us) */
        #నిర్వచించు పోర్టు_ALT_GET_నిరంతరం_సమయం_COUNTER_విలువ( x )    చేయి { x = ( uint32_t ) esp_timer_get_సమయం(); } అయితే( 0 )
    #అయితే_ముగింపు



/* Kernel utilities. */
    శూన్య v_పోర్టు_Yield( శూన్య );
    శూన్య v_పోర్టు_Evaluate_Yield_From_ISR( పూర్ణాంకం argc,
                                    ... );
    శూన్య frxt_అమరిక_switch( శూన్య );

/* Macro to count number of arguments of a __VA_ARGS__ used to support portYIELD_FROM_ISR with,
 * or without arguments. The macro counts only 0 or 1 arguments.
 *
 * In the future, we want to switch to C++20. We also want to become compatible with clang.
 * Hence, we provide two versions of the following macros which are using variadic arguments.
 * The first one is using the GNU extension ##__VA_ARGS__. The second one is using the C++20 feature __VA_OPT__(,).
 * This allows users to compile their code with standard C++20 enabled instead of the GNU extension.
 * Below C++20, we haven't found any good alternative to using ##__VA_ARGS__.
 */
    #ఒకవేళ defined( __cplusplus ) && ( __cplusplus > 201703L )
        #నిర్వచించు పోర్టు_GET_వాదం_లెక్క( ... )                        పోర్టు_GET_వాదం_లెక్క_INNER( 0 __VA_OPT__(, ) __VA_ARGS__, 1, 0 )
    #లేకపోతే
        #నిర్వచించు పోర్టు_GET_వాదం_లెక్క( ... )                        పోర్టు_GET_వాదం_లెక్క_INNER( 0, ## __VA_ARGS__, 1, 0 )
    #అయితే_ముగింపు
    #నిర్వచించు పోర్టు_GET_వాదం_లెక్క_INNER( zero, one, లెక్క, ... )    లెక్క

    _Static_assert( పోర్టు_GET_వాదం_లెక్క() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments" );
    _Static_assert( పోర్టు_GET_వాదం_లెక్క( 1 ) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument" );

    #నిర్వచించు పోర్టు_YIELD()    v_పోర్టు_Yield()

/* The macro below could be used when passing a single argument, or without any argument,
 * it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 * might result in undesired behaviour
 */
    #ఒకవేళ defined( __cplusplus ) && ( __cplusplus > 201703L )
        #నిర్వచించు పోర్టు_YIELD_FROM_ISR( ... )    v_పోర్టు_Evaluate_Yield_From_ISR( పోర్టు_GET_వాదం_లెక్క( __VA_ARGS__ ) __VA_OPT__(, ) __VA_ARGS__ )
    #లేకపోతే
        #నిర్వచించు పోర్టు_YIELD_FROM_ISR( ... )    v_పోర్టు_Evaluate_Yield_From_ISR( పోర్టు_GET_వాదం_లెక్క( __VA_ARGS__ ), ## __VA_ARGS__ )
    #అయితే_ముగింపు

    స్థిర అంతఃవరుస పునాది_Type_t x_పోర్టు_Get_Core_ID();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #నిర్వచించు పోర్టు_TASK_FUNCTION_PROTO( vFunction, pvParameters )    శూన్య vFunction( శూన్య * pvParameters )
    #నిర్వచించు పోర్టు_TASK_FUNCTION( vFunction, pvParameters )          శూన్య vFunction( శూన్య * pvParameters )

/* When coprocessors are defined, we to maintain a pointer to coprocessors area. */
/* We currently use a hack: redefine field xMPU_SETTINGS in TCB block as a structure that can hold: */
/* MPU wrappers, coprocessor area pointer, trace code structure, and more if needed. */
/* The field is normally used for memory protection. FreeRTOS should create another general purpose field. */
    రకనిర్వచనం నిర్మాణం
    {
        #ఒకవేళ XCHAL_CP_అంకె > 0
            అస్థిర దొంతర_Type_t * coproc_area; /* Pointer to coprocessor save area; MUST BE FIRST */
        #అయితే_ముగింపు

        #ఒకవేళ పోర్టు_USING_MPU_WRAPPERS
            /* Define here mpu_settings, which is port dependent */
            పూర్ణాంకం mpu_setting; /* Just a dummy example here; MPU not ported to Xtensa yet */
        #అయితే_ముగింపు

        #ఒకవేళ configUSE_TRACE_FACILITY_2
            నిర్మాణం
            {
                /* Cf. porttraceStamp() */
                పూర్ణాంకం taskstamp;      /* Stamp from inside task to see where we are */
                పూర్ణాంకం taskstampcount; /* A counter usually incremented when we restart the task's loop */
            } porttrace;
        #అయితే_ముగింపు
    } xMPU_SETTINGS;

/* Main hack to use MPU_wrappers even when no MPU is defined (warning: mpu_setting should not be accessed; otherwise move this above xMPU_SETTINGS) */
    #ఒకవేళ ( XCHAL_CP_అంకె > 0 || configUSE_TRACE_FACILITY_2 ) && !పోర్టు_USING_MPU_WRAPPERS /* If MPU wrappers not used, we still need to allocate coproc area */
        #నిర్వచనం_రద్దు పోర్టు_USING_MPU_WRAPPERS
        #నిర్వచించు పోర్టు_USING_MPU_WRAPPERS    1                                           /* Enable it to allocate coproc area */
        #నిర్వచించు MPU_WRAPPERS_H                                                        /* Override mpu_wrapper.h to disable unwanted code */
        #నిర్వచించు PRIVILEGED_FUNCTION
        #నిర్వచించు PRIVILEGED_దత్తాంశం
    #అయితే_ముగింపు

    శూన్య vApplicationSleep( TickType_t x_Expected_Idle_సమయం );

    #నిర్వచించు పోర్టు_SUPPRESS_TICKS_AND_SLEEP( idle_సమయం )    vApplicationSleep( idle_సమయం )

    శూన్య _xt_coproc_release( అస్థిర శూన్య * coproc_sa_పునాది );

/*-----------------------------------------------------------*/

    #ఒకవేళ ( ESP_IDF_సంస్కరణ >= ESP_IDF_సంస్కరణ_VAL( 4, 2, 0 ) )
        /* Architecture specific optimisations. */

        #ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
            #ఒకవేళ ( configMAX_PRIORITIES > 32 )
                #దోషం config_USE_పోర్టు_OPTIMISED_TASK_SELECTION can only be సమితి గమ్యం 1 when configMAX_PRIORITIES is less than or equal గమ్యం 32.  It is very rare that a system requires మరిన్ని than 10 గమ్యం 15 different priorities as tasks that share a ప్రాధాన్యత will time ముక్క.
            #అయితే_ముగింపు

/* Store/clear the ready priorities in a bit map. */
            #నిర్వచించు పోర్టు_రికార్డు_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ప్రాధాన్యత ) )
            #నిర్వచించు పోర్టు_RESET_READY_ప్రాధాన్యత( ux_ప్రాధాన్యత, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ప్రాధాన్యత ) )

/*-----------------------------------------------------------*/

            #నిర్వచించు పోర్టు_GET_HIGHEST_ప్రాధాన్యత( ux_శిఖరం_ప్రాధాన్యత, uxReadyPriorities )    ux_శిఖరం_ప్రాధాన్యత = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )

        #అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #అయితే_ముగింపు /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

/*-----------------------------------------------------------*/

/*
 * Map to the memory management routines required for the port.
 *
 * Note that libc standard malloc/free are also available for
 * non-FreeRTOS-specific code, and behave the same as
 * pvPortMalloc()/vPortFree().
 */
    #నిర్వచించు pv_పోర్టు_Malloc                       కుప్ప_caps_malloc_default
    #నిర్వచించు v_పోర్టు_Free                          కుప్ప_caps_free
    #నిర్వచించు x_పోర్టు_Get_Free_కుప్ప_కొలత               esp_get_free_కుప్ప_కొలత
    #నిర్వచించు x_పోర్టు_Get_Minimum_Ever_Free_కుప్ప_కొలత    esp_get_minimum_free_కుప్ప_కొలత

    #ఒకవేళ ( ESP_IDF_సంస్కరణ < ESP_IDF_సంస్కరణ_VAL( 4, 2, 0 ) )

/*
 * Send an interrupt to another core in order to make the task running
 * on it yield for a higher-priority task.
 */

        శూన్య v_పోర్టు_Yield_Other_Core( పునాది_Type_t coreid ) PRIVILEGED_FUNCTION;

    #అయితే_ముగింపు /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

/*
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack
 * watchpoint around.
 */
    శూన్య v_పోర్టు_సమితి_దొంతర_Watchpoint( శూన్య * px_దొంతర_ప్రారంభం );

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
    పునాది_Type_t x_పోర్టు_లోపల_Isr_Context();


/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
    పునాది_Type_t x_పోర్టు_Interrupted_From_ISRContext();

/*
 * The structures and methods of manipulating the MPU are contained within the
 * port layer.
 *
 * Fills the xMPUSettings structure with the memory region information
 * contained in xRegions.
 */
    #ఒకవేళ ( పోర్టు_USING_MPU_WRAPPERS == 1 )
        నిర్మాణం x_జ్ఞాపకం_REGION;
        శూన్య v_పోర్టు_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                        స్థిరరాశి నిర్మాణం x_జ్ఞాపకం_REGION * స్థిరరాశి xRegions,
                                        దొంతర_Type_t * px_Bottom_యొక్క_దొంతర,
                                        config_దొంతర_లోతు_TYPE ux_దొంతర_లోతు ) PRIVILEGED_FUNCTION;
        శూన్య v_పోర్టు_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings );
    #అయితే_ముగింపు

/* Multi-core: get current core ID */
    స్థిర అంతఃవరుస పునాది_Type_t IRAM_ATTR x_పోర్టు_Get_Core_ID()
    {
        తిరిగి ( uint32_t ) cpu_hal_get_core_id();
    }

/* Get tick rate per second */
    uint32_t x_పోర్టు_Get_Tick_రేటు_Hz( శూన్య );

    స్థిర అంతఃవరుస bool IRAM_ATTR x_పోర్టు_Can_Yield( శూన్య )
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

        తిరిగి( ( ps_reg & PS_INTLEVEL_ముసుగు ) == 0 );
    }

/* porttrace */
    #ఒకవేళ configUSE_TRACE_FACILITY_2
        #అన్తర్భావ "porttrace.h"
    #అయితే_ముగింపు

/* configASSERT_2 if requested */
    #ఒకవేళ configASSERT_2
        #అన్తర్భావ <stdio.h>
        శూన్య నిష్క్రమించు( పూర్ణాంకం );
        #నిర్వచించు configASSERT( x )    ఒకవేళ( !( x ) ) { porttracePrint( -1 ); రాయి( "\nAssertion failed in %s:%d\n", __FILE__, __LINE__ ); నిష్క్రమించు( -1 ); }
    #అయితే_ముగింపు

/* Barriers */
    #నిర్వచించు పోర్టు_జ్ఞాపకం_BARRIER()    __asm అస్థిర ( "" ::: "memory" )


#అయితే_ముగింపు // __ASSEMBLER__

/* *INDENT-OFF* */
#నిర్వచితమైతే __cplusplus
    }
#అయితే_ముగింపు
/* *INDENT-ON* */

#అయితే_ముగింపు /* PORTMACRO_H */
