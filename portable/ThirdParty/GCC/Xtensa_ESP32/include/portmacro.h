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

#اگر_غیر_تعریف_شدہ PORTMACRO_H
#تعریف_کرو PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    خارجی "C" {
#اگر_ختم
/* *INDENT-ON* */

#اگر_غیر_تعریف_شدہ __ASSEMBLER__

    #شامل <stdint.h>

    #شامل <xtensa/hal.h>
    #شامل <xtensa/config/core.h>
    #شامل <xtensa/config/system.h> /* required for XSHAL_CLIB */
    #شامل <xtensa/xtruntime.h>
    #شامل "soc/spinlock.h"
    #شامل "esp_timer.h" /* required for FreeRTOS run time stats */
    #شامل "esp_system.h"
    #شامل "esp_idf_version.h"
    #شامل "esp_heap_caps.h"

/* TODO: Resolve build warnings generated due to this header inclusion */
    #شامل "hal/cpu_hal.h"

/* TODO: These includes are not directly used in this file. They are kept into to prevent a breaking change. Remove these. */
    #شامل <limits.h>
    #شامل <xtensa/xtensa_api.h>

    #شامل "soc/cpu.h"
    #شامل "soc/soc_memory_layout.h"
    #اگر ( ESP_IDF_نسخہ >= ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )
        #شامل "soc/compare_set.h"
    #اگر_ختم /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

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

    #تعریف_کرو پورٹ_CHAR          int8_t
    #تعریف_کرو پورٹ_FLOAT         اعشاری
    #تعریف_کرو پورٹ_DOUBLE        دوہرا
    #تعریف_کرو پورٹ_LONG          int32_t
    #تعریف_کرو پورٹ_SHORT         int16_t
    #تعریف_کرو پورٹ_ڈھیر_TYPE    uint8_t
    #تعریف_کرو پورٹ_بنیاد_TYPE     صحیح

    قسمتعریف پورٹ_ڈھیر_TYPE           ڈھیر_Type_t;
    قسمتعریف پورٹ_بنیاد_TYPE            بنیاد_Type_t;
    قسمتعریف غیرعلامتی پورٹ_بنیاد_TYPE   UBaseType_t;

    #اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_16_بٹ )
        قسمتعریف uint16_t             TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffff
    #وگرنہ_اگر ( config_TICK_TYPE_چوڑائی_اندر_بٹ == TICK_TYPE_چوڑائی_32_بٹ )
        قسمتعریف uint32_t             TickType_t;
        #تعریف_کرو پورٹ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
    #ورنہ
        #غلطی config_TICK_TYPE_چوڑائی_اندر_بٹ سیٹ مقصد unsupported tick type چوڑائی.
    #اگر_ختم
/*-----------------------------------------------------------*/

/* portbenchmark */
    #شامل "portbenchmark.h"

    #شامل "sdkconfig.h"
    #شامل "esp_attr.h"

/* "mux" data structure (spinlock) */
    قسمتعریف spinlock_t پورٹ_MUX_TYPE;                                /**< Spinlock type used by FreeRTOS critical sections */
    #تعریف_کرو پورٹ_MUX_INITIALIZER_UNLOCKED    SPINLOCK_INITIALIZER    /**< Spinlock initializer */
    #تعریف_کرو پورٹ_MUX_FREE_VAL                SPINLOCK_FREE           /**< Spinlock is free. [refactor-todo] check if this is still required */
    #تعریف_کرو پورٹ_MUX_NO_TIMEOUT              SPINLOCK_WAIT_FOREVER   /**< When passed for 'timeout_cycles', spin forever if necessary. [refactor-todo] check if this is still required */
    #تعریف_کرو پورٹ_MUX_TRY_تالا                SPINLOCK_NO_WAIT        /**< Try to acquire the spinlock a single time only. [refactor-todo] check if this is still required */
    #تعریف_کرو پورٹ_MUX_INITIALIZE( mux )    spinlock_initialize( mux ) /*< Initialize a spinlock to its unlocked state */

    #تعریف_کرو پورٹ_CRITICAL_NESTING_اندر_TCB     1

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
    خالی v_پورٹ_CPUInitialize_Mutex( پورٹ_MUX_TYPE * mux );
    #اگر_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
        #غلطی CONFIG_FREERTOS_PORTMUX_DEBUG not supported اندر Amazon FreeRTOS
    #اگر_ختم

    خالی vTaskExitCritical();
    خالی vTaskEnterCritical();
    ساکن اندرونی خالی v_پورٹ_Consume_Spinlock_Arg( صحیح غیر_مستعمل,
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
    bool v_پورٹ_CPUAcquire_Mutex_Timeout( پورٹ_MUX_TYPE * mux,
                                      صحیح timeout_ادوار );
    خالی v_پورٹ_CPURelease_Mutex( پورٹ_MUX_TYPE * mux );

    #تعریف_کرو پورٹ_ENTER_CRITICAL( ... )        کرو { vTaskEnterCritical(); v_پورٹ_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } جب( 0 )
    #تعریف_کرو پورٹ_EXIT_CRITICAL( ... )         کرو { vTaskExitCritical(); v_پورٹ_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } جب( 0 )


    #تعریف_کرو پورٹ_ENTER_CRITICAL_ISR( mux )    v_پورٹ_CPUAcquire_Mutex_Timeout( mux, پورٹ_MUX_NO_TIMEOUT )
    #تعریف_کرو پورٹ_EXIT_CRITICAL_ISR( mux )     v_پورٹ_CPURelease_Mutex( mux )

    #تعریف_کرو پورٹ_ENTER_CRITICAL_محفوظ( mux ) \
    کرو {                                   \
        اگر( x_پورٹ_اندر_Isr_Context() ) {        \
            پورٹ_ENTER_CRITICAL_ISR( mux ); \
        }                                  \
        ورنہ {                             \
            پورٹ_ENTER_CRITICAL( mux );     \
        }                                  \
    } جب( 0 )

    #تعریف_کرو پورٹ_EXIT_CRITICAL_محفوظ( mux ) \
    کرو {                                  \
        اگر( x_پورٹ_اندر_Isr_Context() ) {       \
            پورٹ_EXIT_CRITICAL_ISR( mux ); \
        }                                 \
        ورنہ {                            \
            پورٹ_EXIT_CRITICAL( mux );     \
        }                                 \
    } جب( 0 )

    #تعریف_کرو پورٹ_ASSERT_IF_اندر_ISR()    v_پورٹ_Assert_If_اندر_ISR()
    خالی v_پورٹ_Assert_If_اندر_ISR( خالی );

/* Critical section management. NW-TODO: replace XTOS_SET_INTLEVEL with more efficient version, if any? */
/* These cannot be nested. They should be used with a lot of care and cannot be called from interrupt level. */
/* */
/* Only applies to one CPU. See notes above & below for reasons not to use these. */
    #تعریف_کرو پورٹ_DISABLE_INTERRUPTS()    کرو { XTOS_سیٹ_INTLEVEL( XCHAL_EXCM_LEVEL ); portbenchmark_مداخلت_DISABLE(); } جب( 0 )
    #تعریف_کرو پورٹ_ENABLE_INTERRUPTS()     کرو { portbenchmark_مداخلت_RESTORE( 0 ); XTOS_سیٹ_INTLEVEL( 0 ); } جب( 0 )

/* Cleaner solution allows nested interrupts disabling and restoring via local registers or stack. */
/* They can be called from interrupts too. */
/* WARNING: Only applies to current CPU. See notes above. */
    ساکن اندرونی UBaseType_t __attribute__( ( always_inline ) ) x_پورٹ_سیٹ_مداخلت_نقاب_From_ISR( خالی )
    {
        UBaseType_t پچھلا_int_level = XTOS_سیٹ_INTLEVEL( XCHAL_EXCM_LEVEL );

        portbenchmark_مداخلت_DISABLE();
        واپس پچھلا_int_level;
    }

    ساکن اندرونی خالی __attribute__( ( always_inline ) ) v_پورٹ_Clear_مداخلت_نقاب_From_ISR( UBaseType_t پچھلا_level )
    {
        portbenchmark_مداخلت_RESTORE( پچھلا_level );
        XTOS_RESTORE_JUST_INTLEVEL( پچھلا_level );
    }

/* These FreeRTOS versions are similar to the nested versions above */
    #تعریف_کرو پورٹ_سیٹ_مداخلت_نقاب_FROM_ISR()                  x_پورٹ_سیٹ_مداخلت_نقاب_From_ISR()
    #تعریف_کرو پورٹ_CLEAR_مداخلت_نقاب_FROM_ISR( پچھلا_level )    v_پورٹ_Clear_مداخلت_نقاب_From_ISR( پچھلا_level )

/*Because the ROM routines don't necessarily handle a stack in external RAM correctly, we force */
/*the stack memory to always be internal. */
    #تعریف_کرو پورٹ_Tcb_حافظہ_Caps      ( MALLOC_CAP_اندرونی | MALLOC_CAP_8_ثنائی_ہندسہ )
    #تعریف_کرو پورٹ_ڈھیر_حافظہ_Caps    ( MALLOC_CAP_اندرونی | MALLOC_CAP_8_ثنائی_ہندسہ )

    #تعریف_کرو pv_پورٹ_Malloc_Tcb_Mem( سائز )        ڈھیر_caps_malloc( سائز, پورٹ_Tcb_حافظہ_Caps )
    #تعریف_کرو pv_پورٹ_Malloc_ڈھیر_Mem( سائز )      ڈھیر_caps_malloc( سائز, پورٹ_ڈھیر_حافظہ_Caps )

/*xTaskCreateStatic uses these functions to check incoming memory. */
    #تعریف_کرو پورٹ_VALID_TCB_MEM( ptr )          ( esp_ptr_اندرونی( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #اگر_تعریف_شدہ CONFIG_SPIRAM_ALLOW_ڈھیر_EXTERNAL_حافظہ
        #تعریف_کرو پورٹ_VALID_ڈھیر_MEM( ptr )    esp_ptr_byte_accessible( ptr )
    #ورنہ
        #تعریف_کرو پورٹ_VALID_ڈھیر_MEM( ptr )    ( esp_ptr_اندرونی( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #اگر_ختم

/*
 * Wrapper for the Xtensa compare-and-set instruction. This subroutine will atomically compare
 * *addr to 'compare'. If *addr == compare, *addr is set to *set. *set is updated with the previous
 * value of *addr (either 'compare' or some other value.)
 *
 * Warning: From the ISA docs: in some (unspecified) cases, the s32c1i instruction may return the
 * *bitwise inverse* of the old mem if the mem wasn't written. This doesn't seem to happen on the
 * ESP32 (portMUX assertions would fail).
 */
    ساکن اندرونی خالی ux_پورٹ_Compare_سیٹ( متلون uint32_t * addr,
                                         uint32_t compare,
                                         uint32_t * سیٹ )
    {
        #اگر ( ESP_IDF_نسخہ < ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )
            __asm__ __volatile__ (
                "WSR       %2,SCOMPARE1 \n"
                "S32C1I     %0, %1, 0   \n"
                : "=r" ( *سیٹ )
                : "r" ( addr ), "r" ( compare ), "0" ( *سیٹ )
                );
        #ورنہ
            #اگر ( XCHAL_HAVE_S32C1I > 0 )
                __asm__ __volatile__ (
                    "WSR        %2,SCOMPARE1 \n"
                    "S32C1I     %0, %1, 0    \n"
                    : "=r" ( *سیٹ )
                    : "r" ( addr ), "r" ( compare ), "0" ( *سیٹ )
                    );
            #ورنہ
                /* No S32C1I, so do this by disabling and re-enabling interrupts (slower) */
                uint32_t intlevel, old_قدر;
                __asm__ __volatile__ ( "rsil %0, " XTSTR( XCHAL_EXCM_LEVEL ) "\n"
                                       : "=r" ( intlevel ) );

                old_قدر = *addr;

                اگر( old_قدر == compare )
                {
                    *addr = *سیٹ;
                }

                __asm__ __volatile__ ( "memw \n"
                                       "wsr %0, ps\n"
                                       : : "r" ( intlevel ) );

                *سیٹ = old_قدر;
            #اگر_ختم /* if ( XCHAL_HAVE_S32C1I > 0 ) */
        #اگر_ختم /* #if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)) */
    }

    #اگر ( ESP_IDF_نسخہ < ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )
        خالی ux_پورٹ_Compare_سیٹ_Extram( متلون uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * سیٹ );
    #ورنہ
        ساکن اندرونی خالی ux_پورٹ_Compare_سیٹ_Extram( متلون uint32_t * addr,
                                                   uint32_t compare,
                                                   uint32_t * سیٹ )
        {
            #اگر defined( CONFIG_SPIRAM )
                compare_and_سیٹ_extram( addr, compare, سیٹ );
            #اگر_ختم
        }
    #اگر_ختم /* if ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) ) */

/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #تعریف_کرو پورٹ_ڈھیر_GROWTH      ( -1 )
    #تعریف_کرو پورٹ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
    #تعریف_کرو پورٹ_BYTE_ALIGNMENT    4
    #تعریف_کرو پورٹ_NOP()    XT_NOP()
/*-----------------------------------------------------------*/

/* Fine resolution time */
    #تعریف_کرو پورٹ_GET_تسلسل_وقت_شمار_قدر()    xthal_get_ccount()
/*ccount or esp_timer are initialized elsewhere */
    #تعریف_کرو پورٹ_CONFIGURE_TIMER_FOR_تسلسل_وقت_STATS()

    #اگر_تعریف_شدہ CONFIG_FREERTOS_تسلسل_وقت_STATS_USING_ESP_TIMER
/* Coarse resolution time (us) */
        #تعریف_کرو پورٹ_ALT_GET_تسلسل_وقت_شمار_قدر( x )    کرو { x = ( uint32_t ) esp_timer_get_وقت(); } جب( 0 )
    #اگر_ختم



/* Kernel utilities. */
    خالی v_پورٹ_Yield( خالی );
    خالی v_پورٹ_Evaluate_Yield_From_ISR( صحیح argc,
                                    ... );
    خالی frxt_تیاری_switch( خالی );

/* Macro to count number of arguments of a __VA_ARGS__ used to support portYIELD_FROM_ISR with,
 * or without arguments. The macro counts only 0 or 1 arguments.
 *
 * In the future, we want to switch to C++20. We also want to become compatible with clang.
 * Hence, we provide two versions of the following macros which are using variadic arguments.
 * The first one is using the GNU extension ##__VA_ARGS__. The second one is using the C++20 feature __VA_OPT__(,).
 * This allows users to compile their code with standard C++20 enabled instead of the GNU extension.
 * Below C++20, we haven't found any good alternative to using ##__VA_ARGS__.
 */
    #اگر defined( __cplusplus ) && ( __cplusplus > 201703L )
        #تعریف_کرو پورٹ_GET_دلیل_گنتی( ... )                        پورٹ_GET_دلیل_گنتی_INNER( 0 __VA_OPT__(, ) __VA_ARGS__, 1, 0 )
    #ورنہ
        #تعریف_کرو پورٹ_GET_دلیل_گنتی( ... )                        پورٹ_GET_دلیل_گنتی_INNER( 0, ## __VA_ARGS__, 1, 0 )
    #اگر_ختم
    #تعریف_کرو پورٹ_GET_دلیل_گنتی_INNER( zero, one, گنتی, ... )    گنتی

    _Static_assert( پورٹ_GET_دلیل_گنتی() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments" );
    _Static_assert( پورٹ_GET_دلیل_گنتی( 1 ) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument" );

    #تعریف_کرو پورٹ_YIELD()    v_پورٹ_Yield()

/* The macro below could be used when passing a single argument, or without any argument,
 * it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 * might result in undesired behaviour
 */
    #اگر defined( __cplusplus ) && ( __cplusplus > 201703L )
        #تعریف_کرو پورٹ_YIELD_FROM_ISR( ... )    v_پورٹ_Evaluate_Yield_From_ISR( پورٹ_GET_دلیل_گنتی( __VA_ARGS__ ) __VA_OPT__(, ) __VA_ARGS__ )
    #ورنہ
        #تعریف_کرو پورٹ_YIELD_FROM_ISR( ... )    v_پورٹ_Evaluate_Yield_From_ISR( پورٹ_GET_دلیل_گنتی( __VA_ARGS__ ), ## __VA_ARGS__ )
    #اگر_ختم

    ساکن اندرونی بنیاد_Type_t x_پورٹ_Get_Core_ID();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #تعریف_کرو پورٹ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    خالی vFunction( خالی * pvParameters )
    #تعریف_کرو پورٹ_TASK_FUNCTION( vFunction, pvParameters )          خالی vFunction( خالی * pvParameters )

/* When coprocessors are defined, we to maintain a pointer to coprocessors area. */
/* We currently use a hack: redefine field xMPU_SETTINGS in TCB block as a structure that can hold: */
/* MPU wrappers, coprocessor area pointer, trace code structure, and more if needed. */
/* The field is normally used for memory protection. FreeRTOS should create another general purpose field. */
    قسمتعریف ساخت
    {
        #اگر XCHAL_CP_عدد > 0
            متلون ڈھیر_Type_t * coproc_area; /* Pointer to coprocessor save area; MUST BE FIRST */
        #اگر_ختم

        #اگر پورٹ_USING_MPU_WRAPPERS
            /* Define here mpu_settings, which is port dependent */
            صحیح mpu_setting; /* Just a dummy example here; MPU not ported to Xtensa yet */
        #اگر_ختم

        #اگر configUSE_TRACE_FACILITY_2
            ساخت
            {
                /* Cf. porttraceStamp() */
                صحیح taskstamp;      /* Stamp from inside task to see where we are */
                صحیح taskstampcount; /* A counter usually incremented when we restart the task's loop */
            } porttrace;
        #اگر_ختم
    } xMPU_SETTINGS;

/* Main hack to use MPU_wrappers even when no MPU is defined (warning: mpu_setting should not be accessed; otherwise move this above xMPU_SETTINGS) */
    #اگر ( XCHAL_CP_عدد > 0 || configUSE_TRACE_FACILITY_2 ) && !پورٹ_USING_MPU_WRAPPERS /* If MPU wrappers not used, we still need to allocate coproc area */
        #تعریف_منسوخ پورٹ_USING_MPU_WRAPPERS
        #تعریف_کرو پورٹ_USING_MPU_WRAPPERS    1                                           /* Enable it to allocate coproc area */
        #تعریف_کرو MPU_WRAPPERS_H                                                        /* Override mpu_wrapper.h to disable unwanted code */
        #تعریف_کرو PRIVILEGED_FUNCTION
        #تعریف_کرو PRIVILEGED_ڈیٹا
    #اگر_ختم

    خالی vApplicationSleep( TickType_t x_Expected_Idle_وقت );

    #تعریف_کرو پورٹ_SUPPRESS_TICKS_AND_SLEEP( idle_وقت )    vApplicationSleep( idle_وقت )

    خالی _xt_coproc_release( متلون خالی * coproc_sa_بنیاد );

/*-----------------------------------------------------------*/

    #اگر ( ESP_IDF_نسخہ >= ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )
        /* Architecture specific optimisations. */

        #اگر config_USE_پورٹ_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
            #اگر ( configMAX_PRIORITIES > 32 )
                #غلطی config_USE_پورٹ_OPTIMISED_TASK_SELECTION can only be سیٹ مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires مزید than 10 مقصد 15 different priorities as tasks that share a ترجیح will time قاش.
            #اگر_ختم

/* Store/clear the ready priorities in a bit map. */
            #تعریف_کرو پورٹ_ریکارڈ_READY_ترجیح( ux_ترجیح, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ترجیح ) )
            #تعریف_کرو پورٹ_RESET_READY_ترجیح( ux_ترجیح, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ترجیح ) )

/*-----------------------------------------------------------*/

            #تعریف_کرو پورٹ_GET_HIGHEST_ترجیح( ux_چوٹی_ترجیح, uxReadyPriorities )    ux_چوٹی_ترجیح = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )

        #اگر_ختم /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #اگر_ختم /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

/*-----------------------------------------------------------*/

/*
 * Map to the memory management routines required for the port.
 *
 * Note that libc standard malloc/free are also available for
 * non-FreeRTOS-specific code, and behave the same as
 * pvPortMalloc()/vPortFree().
 */
    #تعریف_کرو pv_پورٹ_Malloc                       ڈھیر_caps_malloc_default
    #تعریف_کرو v_پورٹ_Free                          ڈھیر_caps_free
    #تعریف_کرو x_پورٹ_Get_Free_ڈھیر_سائز               esp_get_free_ڈھیر_سائز
    #تعریف_کرو x_پورٹ_Get_Minimum_Ever_Free_ڈھیر_سائز    esp_get_minimum_free_ڈھیر_سائز

    #اگر ( ESP_IDF_نسخہ < ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )

/*
 * Send an interrupt to another core in order to make the task running
 * on it yield for a higher-priority task.
 */

        خالی v_پورٹ_Yield_Other_Core( بنیاد_Type_t coreid ) PRIVILEGED_FUNCTION;

    #اگر_ختم /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

/*
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack
 * watchpoint around.
 */
    خالی v_پورٹ_سیٹ_ڈھیر_Watchpoint( خالی * px_ڈھیر_آغاز );

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
    بنیاد_Type_t x_پورٹ_اندر_Isr_Context();


/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
    بنیاد_Type_t x_پورٹ_Interrupted_From_ISRContext();

/*
 * The structures and methods of manipulating the MPU are contained within the
 * port layer.
 *
 * Fills the xMPUSettings structure with the memory region information
 * contained in xRegions.
 */
    #اگر ( پورٹ_USING_MPU_WRAPPERS == 1 )
        ساخت x_حافظہ_REGION;
        خالی v_پورٹ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                        ثابت ساخت x_حافظہ_REGION * ثابت xRegions,
                                        ڈھیر_Type_t * px_Bottom_کا_ڈھیر,
                                        config_ڈھیر_گہرائی_TYPE ux_ڈھیر_گہرائی ) PRIVILEGED_FUNCTION;
        خالی v_پورٹ_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings );
    #اگر_ختم

/* Multi-core: get current core ID */
    ساکن اندرونی بنیاد_Type_t IRAM_ATTR x_پورٹ_Get_Core_ID()
    {
        واپس ( uint32_t ) cpu_hal_get_core_id();
    }

/* Get tick rate per second */
    uint32_t x_پورٹ_Get_Tick_شرح_Hz( خالی );

    ساکن اندرونی bool IRAM_ATTR x_پورٹ_Can_Yield( خالی )
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

        واپس( ( ps_reg & PS_INTLEVEL_نقاب ) == 0 );
    }

/* porttrace */
    #اگر configUSE_TRACE_FACILITY_2
        #شامل "porttrace.h"
    #اگر_ختم

/* configASSERT_2 if requested */
    #اگر configASSERT_2
        #شامل <stdio.h>
        خالی باہر_نکلو( صحیح );
        #تعریف_کرو configASSERT( x )    اگر( !( x ) ) { porttracePrint( -1 ); لکھو( "\nAssertion failed in %s:%d\n", __FILE__, __LINE__ ); باہر_نکلو( -1 ); }
    #اگر_ختم

/* Barriers */
    #تعریف_کرو پورٹ_حافظہ_BARRIER()    __asm متلون ( "" ::: "memory" )


#اگر_ختم // __ASSEMBLER__

/* *INDENT-OFF* */
#اگر_تعریف_شدہ __cplusplus
    }
#اگر_ختم
/* *INDENT-ON* */

#اگر_ختم /* PORTMACRO_H */
