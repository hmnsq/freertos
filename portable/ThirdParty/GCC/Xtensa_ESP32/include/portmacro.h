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

#جيڪڏهن_وصف_نه_ٿيل PORTMACRO_H
#وصف_ڪريو PORTMACRO_H

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    خارجي "C" {
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_وصف_نه_ٿيل __ASSEMBLER__

    #ضمن <stdint.h>

    #ضمن <xtensa/hal.h>
    #ضمن <xtensa/config/core.h>
    #ضمن <xtensa/config/system.h> /* required for XSHAL_CLIB */
    #ضمن <xtensa/xtruntime.h>
    #ضمن "soc/spinlock.h"
    #ضمن "esp_timer.h" /* required for FreeRTOS run time stats */
    #ضمن "esp_system.h"
    #ضمن "esp_idf_version.h"
    #ضمن "esp_heap_caps.h"

/* TODO: Resolve build warnings generated due to this header inclusion */
    #ضمن "hal/cpu_hal.h"

/* TODO: These includes are not directly used in this file. They are kept into to prevent a breaking change. Remove these. */
    #ضمن <limits.h>
    #ضمن <xtensa/xtensa_api.h>

    #ضمن "soc/cpu.h"
    #ضمن "soc/soc_memory_layout.h"
    #إذا ( ESP_IDF_نسخو >= ESP_IDF_نسخو_VAL( 4, 2, 0 ) )
        #ضمن "soc/compare_set.h"
    #جيڪڏهن_پورو /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

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

    #وصف_ڪريو پورٽ_CHAR          int8_t
    #وصف_ڪريو پورٽ_FLOAT         عائم
    #وصف_ڪريو پورٽ_DOUBLE        مزدوج
    #وصف_ڪريو پورٽ_LONG          int32_t
    #وصف_ڪريو پورٽ_SHORT         int16_t
    #وصف_ڪريو پورٽ_ڍير_TYPE    uint8_t
    #وصف_ڪريو پورٽ_بنياد_TYPE     صحيح

    تعريفنوع پورٽ_ڍير_TYPE           ڍير_Type_t;
    تعريفنوع پورٽ_بنياد_TYPE            بنياد_Type_t;
    تعريفنوع بنانشان پورٽ_بنياد_TYPE   UBaseType_t;

    #إذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_16_بٽ )
        تعريفنوع uint16_t             TickType_t;
        #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_ويڪر_اندريون_بٽ == TICK_TYPE_ويڪر_32_بٽ )
        تعريفنوع uint32_t             TickType_t;
        #وصف_ڪريو پورٽ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
    #وإلا
        #غلطي config_TICK_TYPE_ويڪر_اندريون_بٽ سيٽ منزل unsupported tick type ويڪر.
    #جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/* portbenchmark */
    #ضمن "portbenchmark.h"

    #ضمن "sdkconfig.h"
    #ضمن "esp_attr.h"

/* "mux" data structure (spinlock) */
    تعريفنوع spinlock_t پورٽ_MUX_TYPE;                                /**< Spinlock type used by FreeRTOS critical sections */
    #وصف_ڪريو پورٽ_MUX_INITIALIZER_UNLOCKED    SPINLOCK_INITIALIZER    /**< Spinlock initializer */
    #وصف_ڪريو پورٽ_MUX_FREE_VAL                SPINLOCK_FREE           /**< Spinlock is free. [refactor-todo] check if this is still required */
    #وصف_ڪريو پورٽ_MUX_NO_TIMEOUT              SPINLOCK_WAIT_FOREVER   /**< When passed for 'timeout_cycles', spin forever if necessary. [refactor-todo] check if this is still required */
    #وصف_ڪريو پورٽ_MUX_TRY_تالو                SPINLOCK_NO_WAIT        /**< Try to acquire the spinlock a single time only. [refactor-todo] check if this is still required */
    #وصف_ڪريو پورٽ_MUX_INITIALIZE( mux )    spinlock_initialize( mux ) /*< Initialize a spinlock to its unlocked state */

    #وصف_ڪريو پورٽ_CRITICAL_NESTING_اندريون_TCB     1

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
    فراغ v_پورٽ_CPUInitialize_Mutex( پورٽ_MUX_TYPE * mux );
    #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
        #غلطي CONFIG_FREERTOS_PORTMUX_DEBUG not supported اندريون Amazon FreeRTOS
    #جيڪڏهن_پورو

    فراغ vTaskExitCritical();
    فراغ vTaskEnterCritical();
    ساكن مضمن فراغ v_پورٽ_Consume_Spinlock_Arg( صحيح اڻ_استعمال_ٿيل,
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
    bool v_پورٽ_CPUAcquire_Mutex_Timeout( پورٽ_MUX_TYPE * mux,
                                      صحيح timeout_چڪرن );
    فراغ v_پورٽ_CPURelease_Mutex( پورٽ_MUX_TYPE * mux );

    #وصف_ڪريو پورٽ_ENTER_CRITICAL( ... )        افعل { vTaskEnterCritical(); v_پورٽ_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } طالما( 0 )
    #وصف_ڪريو پورٽ_EXIT_CRITICAL( ... )         افعل { vTaskExitCritical(); v_پورٽ_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } طالما( 0 )


    #وصف_ڪريو پورٽ_ENTER_CRITICAL_ISR( mux )    v_پورٽ_CPUAcquire_Mutex_Timeout( mux, پورٽ_MUX_NO_TIMEOUT )
    #وصف_ڪريو پورٽ_EXIT_CRITICAL_ISR( mux )     v_پورٽ_CPURelease_Mutex( mux )

    #وصف_ڪريو پورٽ_ENTER_CRITICAL_محفوظ( mux ) \
    افعل {                                   \
        إذا( x_پورٽ_اندريون_Isr_Context() ) {        \
            پورٽ_ENTER_CRITICAL_ISR( mux ); \
        }                                  \
        وإلا {                             \
            پورٽ_ENTER_CRITICAL( mux );     \
        }                                  \
    } طالما( 0 )

    #وصف_ڪريو پورٽ_EXIT_CRITICAL_محفوظ( mux ) \
    افعل {                                  \
        إذا( x_پورٽ_اندريون_Isr_Context() ) {       \
            پورٽ_EXIT_CRITICAL_ISR( mux ); \
        }                                 \
        وإلا {                            \
            پورٽ_EXIT_CRITICAL( mux );     \
        }                                 \
    } طالما( 0 )

    #وصف_ڪريو پورٽ_ASSERT_IF_اندريون_ISR()    v_پورٽ_Assert_If_اندريون_ISR()
    فراغ v_پورٽ_Assert_If_اندريون_ISR( فراغ );

/* Critical section management. NW-TODO: replace XTOS_SET_INTLEVEL with more efficient version, if any? */
/* These cannot be nested. They should be used with a lot of care and cannot be called from interrupt level. */
/* */
/* Only applies to one CPU. See notes above & below for reasons not to use these. */
    #وصف_ڪريو پورٽ_DISABLE_INTERRUPTS()    افعل { XTOS_سيٽ_INTLEVEL( XCHAL_EXCM_LEVEL ); portbenchmark_مداخلت_DISABLE(); } طالما( 0 )
    #وصف_ڪريو پورٽ_ENABLE_INTERRUPTS()     افعل { portbenchmark_مداخلت_RESTORE( 0 ); XTOS_سيٽ_INTLEVEL( 0 ); } طالما( 0 )

/* Cleaner solution allows nested interrupts disabling and restoring via local registers or stack. */
/* They can be called from interrupts too. */
/* WARNING: Only applies to current CPU. See notes above. */
    ساكن مضمن UBaseType_t __attribute__( ( always_inline ) ) x_پورٽ_سيٽ_مداخلت_نقاب_From_ISR( فراغ )
    {
        UBaseType_t prev_int_level = XTOS_سيٽ_INTLEVEL( XCHAL_EXCM_LEVEL );

        portbenchmark_مداخلت_DISABLE();
        أرجع prev_int_level;
    }

    ساكن مضمن فراغ __attribute__( ( always_inline ) ) v_پورٽ_Clear_مداخلت_نقاب_From_ISR( UBaseType_t prev_level )
    {
        portbenchmark_مداخلت_RESTORE( prev_level );
        XTOS_RESTORE_JUST_INTLEVEL( prev_level );
    }

/* These FreeRTOS versions are similar to the nested versions above */
    #وصف_ڪريو پورٽ_سيٽ_مداخلت_نقاب_FROM_ISR()                  x_پورٽ_سيٽ_مداخلت_نقاب_From_ISR()
    #وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب_FROM_ISR( prev_level )    v_پورٽ_Clear_مداخلت_نقاب_From_ISR( prev_level )

/*Because the ROM routines don't necessarily handle a stack in external RAM correctly, we force */
/*the stack memory to always be internal. */
    #وصف_ڪريو پورٽ_Tcb_يادگيري_Caps      ( MALLOC_CAP_اندروني | MALLOC_CAP_8_ٻٽو_انگ )
    #وصف_ڪريو پورٽ_ڍير_يادگيري_Caps    ( MALLOC_CAP_اندروني | MALLOC_CAP_8_ٻٽو_انگ )

    #وصف_ڪريو pv_پورٽ_Malloc_Tcb_Mem( سائيز )        ڍير_caps_malloc( سائيز, پورٽ_Tcb_يادگيري_Caps )
    #وصف_ڪريو pv_پورٽ_Malloc_ڍير_Mem( سائيز )      ڍير_caps_malloc( سائيز, پورٽ_ڍير_يادگيري_Caps )

/*xTaskCreateStatic uses these functions to check incoming memory. */
    #وصف_ڪريو پورٽ_VALID_TCB_MEM( ptr )          ( esp_ptr_اندروني( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #جيڪڏهن_وصف_ٿيل CONFIG_SPIRAM_ALLOW_ڍير_EXTERNAL_يادگيري
        #وصف_ڪريو پورٽ_VALID_ڍير_MEM( ptr )    esp_ptr_byte_accessible( ptr )
    #وإلا
        #وصف_ڪريو پورٽ_VALID_ڍير_MEM( ptr )    ( esp_ptr_اندروني( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #جيڪڏهن_پورو

/*
 * Wrapper for the Xtensa compare-and-set instruction. This subroutine will atomically compare
 * *addr to 'compare'. If *addr == compare, *addr is set to *set. *set is updated with the previous
 * value of *addr (either 'compare' or some other value.)
 *
 * Warning: From the ISA docs: in some (unspecified) cases, the s32c1i instruction may return the
 * *bitwise inverse* of the old mem if the mem wasn't written. This doesn't seem to happen on the
 * ESP32 (portMUX assertions would fail).
 */
    ساكن مضمن فراغ ux_پورٽ_Compare_سيٽ( متطاير uint32_t * addr,
                                         uint32_t compare,
                                         uint32_t * سيٽ )
    {
        #إذا ( ESP_IDF_نسخو < ESP_IDF_نسخو_VAL( 4, 2, 0 ) )
            __asm__ __volatile__ (
                "WSR       %2,SCOMPARE1 \n"
                "S32C1I     %0, %1, 0   \n"
                : "=r" ( *سيٽ )
                : "r" ( addr ), "r" ( compare ), "0" ( *سيٽ )
                );
        #وإلا
            #إذا ( XCHAL_HAVE_S32C1I > 0 )
                __asm__ __volatile__ (
                    "WSR        %2,SCOMPARE1 \n"
                    "S32C1I     %0, %1, 0    \n"
                    : "=r" ( *سيٽ )
                    : "r" ( addr ), "r" ( compare ), "0" ( *سيٽ )
                    );
            #وإلا
                /* No S32C1I, so do this by disabling and re-enabling interrupts (slower) */
                uint32_t intlevel, old_قدر;
                __asm__ __volatile__ ( "rsil %0, " XTSTR( XCHAL_EXCM_LEVEL ) "\n"
                                       : "=r" ( intlevel ) );

                old_قدر = *addr;

                إذا( old_قدر == compare )
                {
                    *addr = *سيٽ;
                }

                __asm__ __volatile__ ( "memw \n"
                                       "wsr %0, ps\n"
                                       : : "r" ( intlevel ) );

                *سيٽ = old_قدر;
            #جيڪڏهن_پورو /* if ( XCHAL_HAVE_S32C1I > 0 ) */
        #جيڪڏهن_پورو /* #if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)) */
    }

    #إذا ( ESP_IDF_نسخو < ESP_IDF_نسخو_VAL( 4, 2, 0 ) )
        فراغ ux_پورٽ_Compare_سيٽ_Extram( متطاير uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * سيٽ );
    #وإلا
        ساكن مضمن فراغ ux_پورٽ_Compare_سيٽ_Extram( متطاير uint32_t * addr,
                                                   uint32_t compare,
                                                   uint32_t * سيٽ )
        {
            #إذا defined( CONFIG_SPIRAM )
                compare_and_سيٽ_extram( addr, compare, سيٽ );
            #جيڪڏهن_پورو
        }
    #جيڪڏهن_پورو /* if ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) ) */

/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #وصف_ڪريو پورٽ_ڍير_GROWTH      ( -1 )
    #وصف_ڪريو پورٽ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
    #وصف_ڪريو پورٽ_BYTE_ALIGNMENT    4
    #وصف_ڪريو پورٽ_NOP()    XT_NOP()
/*-----------------------------------------------------------*/

/* Fine resolution time */
    #وصف_ڪريو پورٽ_GET_لاڳيتو_وقت_COUNTER_قدر()    xthal_get_ccount()
/*ccount or esp_timer are initialized elsewhere */
    #وصف_ڪريو پورٽ_CONFIGURE_TIMER_FOR_لاڳيتو_وقت_STATS()

    #جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_لاڳيتو_وقت_STATS_USING_ESP_TIMER
/* Coarse resolution time (us) */
        #وصف_ڪريو پورٽ_ALT_GET_لاڳيتو_وقت_COUNTER_قدر( x )    افعل { x = ( uint32_t ) esp_timer_get_وقت(); } طالما( 0 )
    #جيڪڏهن_پورو



/* Kernel utilities. */
    فراغ v_پورٽ_Yield( فراغ );
    فراغ v_پورٽ_Evaluate_Yield_From_ISR( صحيح argc,
                                    ... );
    فراغ frxt_تياري_switch( فراغ );

/* Macro to count number of arguments of a __VA_ARGS__ used to support portYIELD_FROM_ISR with,
 * or without arguments. The macro counts only 0 or 1 arguments.
 *
 * In the future, we want to switch to C++20. We also want to become compatible with clang.
 * Hence, we provide two versions of the following macros which are using variadic arguments.
 * The first one is using the GNU extension ##__VA_ARGS__. The second one is using the C++20 feature __VA_OPT__(,).
 * This allows users to compile their code with standard C++20 enabled instead of the GNU extension.
 * Below C++20, we haven't found any good alternative to using ##__VA_ARGS__.
 */
    #إذا defined( __cplusplus ) && ( __cplusplus > 201703L )
        #وصف_ڪريو پورٽ_GET_دليل_ڳڻپ( ... )                        پورٽ_GET_دليل_ڳڻپ_INNER( 0 __VA_OPT__(, ) __VA_ARGS__, 1, 0 )
    #وإلا
        #وصف_ڪريو پورٽ_GET_دليل_ڳڻپ( ... )                        پورٽ_GET_دليل_ڳڻپ_INNER( 0, ## __VA_ARGS__, 1, 0 )
    #جيڪڏهن_پورو
    #وصف_ڪريو پورٽ_GET_دليل_ڳڻپ_INNER( zero, one, ڳڻپ, ... )    ڳڻپ

    _Static_assert( پورٽ_GET_دليل_ڳڻپ() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments" );
    _Static_assert( پورٽ_GET_دليل_ڳڻپ( 1 ) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument" );

    #وصف_ڪريو پورٽ_YIELD()    v_پورٽ_Yield()

/* The macro below could be used when passing a single argument, or without any argument,
 * it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 * might result in undesired behaviour
 */
    #إذا defined( __cplusplus ) && ( __cplusplus > 201703L )
        #وصف_ڪريو پورٽ_YIELD_FROM_ISR( ... )    v_پورٽ_Evaluate_Yield_From_ISR( پورٽ_GET_دليل_ڳڻپ( __VA_ARGS__ ) __VA_OPT__(, ) __VA_ARGS__ )
    #وإلا
        #وصف_ڪريو پورٽ_YIELD_FROM_ISR( ... )    v_پورٽ_Evaluate_Yield_From_ISR( پورٽ_GET_دليل_ڳڻپ( __VA_ARGS__ ), ## __VA_ARGS__ )
    #جيڪڏهن_پورو

    ساكن مضمن بنياد_Type_t x_پورٽ_Get_Core_ID();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #وصف_ڪريو پورٽ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #وصف_ڪريو پورٽ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* When coprocessors are defined, we to maintain a pointer to coprocessors area. */
/* We currently use a hack: redefine field xMPU_SETTINGS in TCB block as a structure that can hold: */
/* MPU wrappers, coprocessor area pointer, trace code structure, and more if needed. */
/* The field is normally used for memory protection. FreeRTOS should create another general purpose field. */
    تعريفنوع بنية
    {
        #إذا XCHAL_CP_انگ > 0
            متطاير ڍير_Type_t * coproc_area; /* Pointer to coprocessor save area; MUST BE FIRST */
        #جيڪڏهن_پورو

        #إذا پورٽ_USING_MPU_WRAPPERS
            /* Define here mpu_settings, which is port dependent */
            صحيح mpu_setting; /* Just a dummy example here; MPU not ported to Xtensa yet */
        #جيڪڏهن_پورو

        #إذا configUSE_TRACE_FACILITY_2
            بنية
            {
                /* Cf. porttraceStamp() */
                صحيح taskstamp;      /* Stamp from inside task to see where we are */
                صحيح taskstampcount; /* A counter usually incremented when we restart the task's loop */
            } porttrace;
        #جيڪڏهن_پورو
    } xMPU_SETTINGS;

/* Main hack to use MPU_wrappers even when no MPU is defined (warning: mpu_setting should not be accessed; otherwise move this above xMPU_SETTINGS) */
    #إذا ( XCHAL_CP_انگ > 0 || configUSE_TRACE_FACILITY_2 ) && !پورٽ_USING_MPU_WRAPPERS /* If MPU wrappers not used, we still need to allocate coproc area */
        #وصف_رد پورٽ_USING_MPU_WRAPPERS
        #وصف_ڪريو پورٽ_USING_MPU_WRAPPERS    1                                           /* Enable it to allocate coproc area */
        #وصف_ڪريو MPU_WRAPPERS_H                                                        /* Override mpu_wrapper.h to disable unwanted code */
        #وصف_ڪريو PRIVILEGED_FUNCTION
        #وصف_ڪريو PRIVILEGED_معلومات
    #جيڪڏهن_پورو

    فراغ vApplicationSleep( TickType_t x_Expected_Idle_وقت );

    #وصف_ڪريو پورٽ_SUPPRESS_TICKS_AND_SLEEP( idle_وقت )    vApplicationSleep( idle_وقت )

    فراغ _xt_coproc_release( متطاير فراغ * coproc_sa_بنياد );

/*-----------------------------------------------------------*/

    #إذا ( ESP_IDF_نسخو >= ESP_IDF_نسخو_VAL( 4, 2, 0 ) )
        /* Architecture specific optimisations. */

        #إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
            #إذا ( configMAX_PRIORITIES > 32 )
                #غلطي config_USE_پورٽ_OPTIMISED_TASK_SELECTION can only be سيٽ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires وڌيڪ than 10 منزل 15 different priorities as tasks that share a ترجيح will time ٽڪرو.
            #جيڪڏهن_پورو

/* Store/clear the ready priorities in a bit map. */
            #وصف_ڪريو پورٽ_رڪارڊ_READY_ترجيح( ux_ترجيح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجيح ) )
            #وصف_ڪريو پورٽ_RESET_READY_ترجيح( ux_ترجيح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجيح ) )

/*-----------------------------------------------------------*/

            #وصف_ڪريو پورٽ_GET_HIGHEST_ترجيح( ux_چوٽي_ترجيح, uxReadyPriorities )    ux_چوٽي_ترجيح = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )

        #جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #جيڪڏهن_پورو /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

/*-----------------------------------------------------------*/

/*
 * Map to the memory management routines required for the port.
 *
 * Note that libc standard malloc/free are also available for
 * non-FreeRTOS-specific code, and behave the same as
 * pvPortMalloc()/vPortFree().
 */
    #وصف_ڪريو pv_پورٽ_Malloc                       ڍير_caps_malloc_default
    #وصف_ڪريو v_پورٽ_Free                          ڍير_caps_free
    #وصف_ڪريو x_پورٽ_Get_Free_ڍير_سائيز               esp_get_free_ڍير_سائيز
    #وصف_ڪريو x_پورٽ_Get_Minimum_Ever_Free_ڍير_سائيز    esp_get_minimum_free_ڍير_سائيز

    #إذا ( ESP_IDF_نسخو < ESP_IDF_نسخو_VAL( 4, 2, 0 ) )

/*
 * Send an interrupt to another core in order to make the task running
 * on it yield for a higher-priority task.
 */

        فراغ v_پورٽ_Yield_Other_Core( بنياد_Type_t coreid ) PRIVILEGED_FUNCTION;

    #جيڪڏهن_پورو /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

/*
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack
 * watchpoint around.
 */
    فراغ v_پورٽ_سيٽ_ڍير_Watchpoint( فراغ * px_ڍير_شروعات );

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
    بنياد_Type_t x_پورٽ_اندريون_Isr_Context();


/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
    بنياد_Type_t x_پورٽ_Interrupted_From_ISRContext();

/*
 * The structures and methods of manipulating the MPU are contained within the
 * port layer.
 *
 * Fills the xMPUSettings structure with the memory region information
 * contained in xRegions.
 */
    #إذا ( پورٽ_USING_MPU_WRAPPERS == 1 )
        بنية x_يادگيري_REGION;
        فراغ v_پورٽ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                        ثابت بنية x_يادگيري_REGION * ثابت xRegions,
                                        ڍير_Type_t * px_Bottom_جو_ڍير,
                                        config_ڍير_اونهائي_TYPE ux_ڍير_اونهائي ) PRIVILEGED_FUNCTION;
        فراغ v_پورٽ_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings );
    #جيڪڏهن_پورو

/* Multi-core: get current core ID */
    ساكن مضمن بنياد_Type_t IRAM_ATTR x_پورٽ_Get_Core_ID()
    {
        أرجع ( uint32_t ) cpu_hal_get_core_id();
    }

/* Get tick rate per second */
    uint32_t x_پورٽ_Get_Tick_شرح_Hz( فراغ );

    ساكن مضمن bool IRAM_ATTR x_پورٽ_Can_Yield( فراغ )
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

        أرجع( ( ps_reg & PS_INTLEVEL_نقاب ) == 0 );
    }

/* porttrace */
    #إذا configUSE_TRACE_FACILITY_2
        #ضمن "porttrace.h"
    #جيڪڏهن_پورو

/* configASSERT_2 if requested */
    #إذا configASSERT_2
        #ضمن <stdio.h>
        فراغ ٻاهر_نڪرو( صحيح );
        #وصف_ڪريو configASSERT( x )    إذا( !( x ) ) { porttracePrint( -1 ); لکو( "\nAssertion failed in %s:%d\n", __FILE__, __LINE__ ); ٻاهر_نڪرو( -1 ); }
    #جيڪڏهن_پورو

/* Barriers */
    #وصف_ڪريو پورٽ_يادگيري_BARRIER()    __asm متطاير ( "" ::: "memory" )


#جيڪڏهن_پورو // __ASSEMBLER__

/* *INDENT-OFF* */
#جيڪڏهن_وصف_ٿيل __cplusplus
    }
#جيڪڏهن_پورو
/* *INDENT-ON* */

#جيڪڏهن_پورو /* PORTMACRO_H */
