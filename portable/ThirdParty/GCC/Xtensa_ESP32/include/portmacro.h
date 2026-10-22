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

#اگر_تعریف_نشده PORTMACRO_H
#تعریف_کن PORTMACRO_H

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    خارجي "C" {
#پایان_اگر
/* *INDENT-ON* */

#اگر_تعریف_نشده __ASSEMBLER__

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
    #إذا ( ESP_IDF_نسخه >= ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
        #ضمن "soc/compare_set.h"
    #پایان_اگر /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

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

    #تعریف_کن پورت_CHAR          int8_t
    #تعریف_کن پورت_FLOAT         عائم
    #تعریف_کن پورت_DOUBLE        مزدوج
    #تعریف_کن پورت_LONG          int32_t
    #تعریف_کن پورت_SHORT         int16_t
    #تعریف_کن پورت_پشته_TYPE    uint8_t
    #تعریف_کن پورت_پایه_TYPE     صحيح

    تعريفنوع پورت_پشته_TYPE           پشته_Type_t;
    تعريفنوع پورت_پایه_TYPE            پایه_Type_t;
    تعريفنوع بیعلامت پورت_پایه_TYPE   UBaseType_t;

    #إذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_16_بیتها )
        تعريفنوع uint16_t             TickType_t;
        #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_عرض_درون_بیتها == TICK_TYPE_عرض_32_بیتها )
        تعريفنوع uint32_t             TickType_t;
        #تعریف_کن پورت_MAX_DELAY    ( TickType_t ) 0xffffffffUL
    #وإلا
        #خطا config_TICK_TYPE_عرض_درون_بیتها مجموعه مقصد unsupported tick type عرض.
    #پایان_اگر
/*-----------------------------------------------------------*/

/* portbenchmark */
    #ضمن "portbenchmark.h"

    #ضمن "sdkconfig.h"
    #ضمن "esp_attr.h"

/* "mux" data structure (spinlock) */
    تعريفنوع spinlock_t پورت_MUX_TYPE;                                /**< Spinlock type used by FreeRTOS critical sections */
    #تعریف_کن پورت_MUX_INITIALIZER_UNLOCKED    SPINLOCK_INITIALIZER    /**< Spinlock initializer */
    #تعریف_کن پورت_MUX_FREE_VAL                SPINLOCK_FREE           /**< Spinlock is free. [refactor-todo] check if this is still required */
    #تعریف_کن پورت_MUX_NO_TIMEOUT              SPINLOCK_WAIT_FOREVER   /**< When passed for 'timeout_cycles', spin forever if necessary. [refactor-todo] check if this is still required */
    #تعریف_کن پورت_MUX_TRY_قفل                SPINLOCK_NO_WAIT        /**< Try to acquire the spinlock a single time only. [refactor-todo] check if this is still required */
    #تعریف_کن پورت_MUX_INITIALIZE( mux )    spinlock_initialize( mux ) /*< Initialize a spinlock to its unlocked state */

    #تعریف_کن پورت_CRITICAL_NESTING_درون_TCB     1

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
    فراغ v_پورت_CPUInitialize_Mutex( پورت_MUX_TYPE * mux );
    #اگر_تعریف_شده CONFIG_FREERTOS_PORTMUX_DEBUG
        #خطا CONFIG_FREERTOS_PORTMUX_DEBUG not supported درون Amazon FreeRTOS
    #پایان_اگر

    فراغ vTaskExitCritical();
    فراغ vTaskEnterCritical();
    ساكن مضمن فراغ v_پورت_Consume_Spinlock_Arg( صحيح استفادهنشده,
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
    bool v_پورت_CPUAcquire_Mutex_Timeout( پورت_MUX_TYPE * mux,
                                      صحيح timeout_چرخهها );
    فراغ v_پورت_CPURelease_Mutex( پورت_MUX_TYPE * mux );

    #تعریف_کن پورت_ENTER_CRITICAL( ... )        افعل { vTaskEnterCritical(); v_پورت_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } طالما( 0 )
    #تعریف_کن پورت_EXIT_CRITICAL( ... )         افعل { vTaskExitCritical(); v_پورت_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } طالما( 0 )


    #تعریف_کن پورت_ENTER_CRITICAL_ISR( mux )    v_پورت_CPUAcquire_Mutex_Timeout( mux, پورت_MUX_NO_TIMEOUT )
    #تعریف_کن پورت_EXIT_CRITICAL_ISR( mux )     v_پورت_CPURelease_Mutex( mux )

    #تعریف_کن پورت_ENTER_CRITICAL_امن( mux ) \
    افعل {                                   \
        إذا( x_پورت_درون_Isr_Context() ) {        \
            پورت_ENTER_CRITICAL_ISR( mux ); \
        }                                  \
        وإلا {                             \
            پورت_ENTER_CRITICAL( mux );     \
        }                                  \
    } طالما( 0 )

    #تعریف_کن پورت_EXIT_CRITICAL_امن( mux ) \
    افعل {                                  \
        إذا( x_پورت_درون_Isr_Context() ) {       \
            پورت_EXIT_CRITICAL_ISR( mux ); \
        }                                 \
        وإلا {                            \
            پورت_EXIT_CRITICAL( mux );     \
        }                                 \
    } طالما( 0 )

    #تعریف_کن پورت_ASSERT_IF_درون_ISR()    v_پورت_Assert_If_درون_ISR()
    فراغ v_پورت_Assert_If_درون_ISR( فراغ );

/* Critical section management. NW-TODO: replace XTOS_SET_INTLEVEL with more efficient version, if any? */
/* These cannot be nested. They should be used with a lot of care and cannot be called from interrupt level. */
/* */
/* Only applies to one CPU. See notes above & below for reasons not to use these. */
    #تعریف_کن پورت_DISABLE_INTERRUPTS()    افعل { XTOS_مجموعه_INTLEVEL( XCHAL_EXCM_LEVEL ); portbenchmark_وقفه_DISABLE(); } طالما( 0 )
    #تعریف_کن پورت_ENABLE_INTERRUPTS()     افعل { portbenchmark_وقفه_RESTORE( 0 ); XTOS_مجموعه_INTLEVEL( 0 ); } طالما( 0 )

/* Cleaner solution allows nested interrupts disabling and restoring via local registers or stack. */
/* They can be called from interrupts too. */
/* WARNING: Only applies to current CPU. See notes above. */
    ساكن مضمن UBaseType_t __attribute__( ( always_inline ) ) x_پورت_مجموعه_وقفه_ماسک_From_ISR( فراغ )
    {
        UBaseType_t prev_int_level = XTOS_مجموعه_INTLEVEL( XCHAL_EXCM_LEVEL );

        portbenchmark_وقفه_DISABLE();
        أرجع prev_int_level;
    }

    ساكن مضمن فراغ __attribute__( ( always_inline ) ) v_پورت_Clear_وقفه_ماسک_From_ISR( UBaseType_t prev_level )
    {
        portbenchmark_وقفه_RESTORE( prev_level );
        XTOS_RESTORE_JUST_INTLEVEL( prev_level );
    }

/* These FreeRTOS versions are similar to the nested versions above */
    #تعریف_کن پورت_مجموعه_وقفه_ماسک_FROM_ISR()                  x_پورت_مجموعه_وقفه_ماسک_From_ISR()
    #تعریف_کن پورت_CLEAR_وقفه_ماسک_FROM_ISR( prev_level )    v_پورت_Clear_وقفه_ماسک_From_ISR( prev_level )

/*Because the ROM routines don't necessarily handle a stack in external RAM correctly, we force */
/*the stack memory to always be internal. */
    #تعریف_کن پورت_Tcb_حافظه_Caps      ( MALLOC_CAP_داخلی | MALLOC_CAP_8_بیت )
    #تعریف_کن پورت_پشته_حافظه_Caps    ( MALLOC_CAP_داخلی | MALLOC_CAP_8_بیت )

    #تعریف_کن pv_پورت_Malloc_Tcb_Mem( اندازه )        انباشته_caps_malloc( اندازه, پورت_Tcb_حافظه_Caps )
    #تعریف_کن pv_پورت_Malloc_پشته_Mem( اندازه )      انباشته_caps_malloc( اندازه, پورت_پشته_حافظه_Caps )

/*xTaskCreateStatic uses these functions to check incoming memory. */
    #تعریف_کن پورت_VALID_TCB_MEM( ptr )          ( esp_ptr_داخلی( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #اگر_تعریف_شده CONFIG_SPIRAM_ALLOW_پشته_EXTERNAL_حافظه
        #تعریف_کن پورت_VALID_پشته_MEM( ptr )    esp_ptr_byte_accessible( ptr )
    #وإلا
        #تعریف_کن پورت_VALID_پشته_MEM( ptr )    ( esp_ptr_داخلی( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #پایان_اگر

/*
 * Wrapper for the Xtensa compare-and-set instruction. This subroutine will atomically compare
 * *addr to 'compare'. If *addr == compare, *addr is set to *set. *set is updated with the previous
 * value of *addr (either 'compare' or some other value.)
 *
 * Warning: From the ISA docs: in some (unspecified) cases, the s32c1i instruction may return the
 * *bitwise inverse* of the old mem if the mem wasn't written. This doesn't seem to happen on the
 * ESP32 (portMUX assertions would fail).
 */
    ساكن مضمن فراغ ux_پورت_Compare_مجموعه( متطاير uint32_t * addr,
                                         uint32_t compare,
                                         uint32_t * مجموعه )
    {
        #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
            __asm__ __volatile__ (
                "WSR       %2,SCOMPARE1 \n"
                "S32C1I     %0, %1, 0   \n"
                : "=r" ( *مجموعه )
                : "r" ( addr ), "r" ( compare ), "0" ( *مجموعه )
                );
        #وإلا
            #إذا ( XCHAL_HAVE_S32C1I > 0 )
                __asm__ __volatile__ (
                    "WSR        %2,SCOMPARE1 \n"
                    "S32C1I     %0, %1, 0    \n"
                    : "=r" ( *مجموعه )
                    : "r" ( addr ), "r" ( compare ), "0" ( *مجموعه )
                    );
            #وإلا
                /* No S32C1I, so do this by disabling and re-enabling interrupts (slower) */
                uint32_t intlevel, old_مقدار;
                __asm__ __volatile__ ( "rsil %0, " XTSTR( XCHAL_EXCM_LEVEL ) "\n"
                                       : "=r" ( intlevel ) );

                old_مقدار = *addr;

                إذا( old_مقدار == compare )
                {
                    *addr = *مجموعه;
                }

                __asm__ __volatile__ ( "memw \n"
                                       "wsr %0, ps\n"
                                       : : "r" ( intlevel ) );

                *مجموعه = old_مقدار;
            #پایان_اگر /* if ( XCHAL_HAVE_S32C1I > 0 ) */
        #پایان_اگر /* #if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)) */
    }

    #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
        فراغ ux_پورت_Compare_مجموعه_Extram( متطاير uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * مجموعه );
    #وإلا
        ساكن مضمن فراغ ux_پورت_Compare_مجموعه_Extram( متطاير uint32_t * addr,
                                                   uint32_t compare,
                                                   uint32_t * مجموعه )
        {
            #إذا defined( CONFIG_SPIRAM )
                compare_and_مجموعه_extram( addr, compare, مجموعه );
            #پایان_اگر
        }
    #پایان_اگر /* if ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) ) */

/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #تعریف_کن پورت_پشته_GROWTH      ( -1 )
    #تعریف_کن پورت_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_نرخ_HZ )
    #تعریف_کن پورت_BYTE_ALIGNMENT    4
    #تعریف_کن پورت_NOP()    XT_NOP()
/*-----------------------------------------------------------*/

/* Fine resolution time */
    #تعریف_کن پورت_GET_پیاپی_زمان_COUNTER_مقدار()    xthal_get_ccount()
/*ccount or esp_timer are initialized elsewhere */
    #تعریف_کن پورت_CONFIGURE_TIMER_FOR_پیاپی_زمان_STATS()

    #اگر_تعریف_شده CONFIG_FREERTOS_پیاپی_زمان_STATS_USING_ESP_TIMER
/* Coarse resolution time (us) */
        #تعریف_کن پورت_ALT_GET_پیاپی_زمان_COUNTER_مقدار( x )    افعل { x = ( uint32_t ) esp_timer_get_زمان(); } طالما( 0 )
    #پایان_اگر



/* Kernel utilities. */
    فراغ v_پورت_Yield( فراغ );
    فراغ v_پورت_Evaluate_Yield_From_ISR( صحيح argc,
                                    ... );
    فراغ frxt_راهاندازی_switch( فراغ );

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
        #تعریف_کن پورت_GET_آرگومان_شمار( ... )                        پورت_GET_آرگومان_شمار_INNER( 0 __VA_OPT__(, ) __VA_ARGS__, 1, 0 )
    #وإلا
        #تعریف_کن پورت_GET_آرگومان_شمار( ... )                        پورت_GET_آرگومان_شمار_INNER( 0, ## __VA_ARGS__, 1, 0 )
    #پایان_اگر
    #تعریف_کن پورت_GET_آرگومان_شمار_INNER( zero, one, شمار, ... )    شمار

    _Static_assert( پورت_GET_آرگومان_شمار() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments" );
    _Static_assert( پورت_GET_آرگومان_شمار( 1 ) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument" );

    #تعریف_کن پورت_YIELD()    v_پورت_Yield()

/* The macro below could be used when passing a single argument, or without any argument,
 * it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 * might result in undesired behaviour
 */
    #إذا defined( __cplusplus ) && ( __cplusplus > 201703L )
        #تعریف_کن پورت_YIELD_FROM_ISR( ... )    v_پورت_Evaluate_Yield_From_ISR( پورت_GET_آرگومان_شمار( __VA_ARGS__ ) __VA_OPT__(, ) __VA_ARGS__ )
    #وإلا
        #تعریف_کن پورت_YIELD_FROM_ISR( ... )    v_پورت_Evaluate_Yield_From_ISR( پورت_GET_آرگومان_شمار( __VA_ARGS__ ), ## __VA_ARGS__ )
    #پایان_اگر

    ساكن مضمن پایه_Type_t x_پورت_Get_Core_ID();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #تعریف_کن پورت_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کن پورت_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* When coprocessors are defined, we to maintain a pointer to coprocessors area. */
/* We currently use a hack: redefine field xMPU_SETTINGS in TCB block as a structure that can hold: */
/* MPU wrappers, coprocessor area pointer, trace code structure, and more if needed. */
/* The field is normally used for memory protection. FreeRTOS should create another general purpose field. */
    تعريفنوع بنية
    {
        #إذا XCHAL_CP_رقم > 0
            متطاير پشته_Type_t * coproc_area; /* Pointer to coprocessor save area; MUST BE FIRST */
        #پایان_اگر

        #إذا پورت_USING_MPU_WRAPPERS
            /* Define here mpu_settings, which is port dependent */
            صحيح mpu_setting; /* Just a dummy example here; MPU not ported to Xtensa yet */
        #پایان_اگر

        #إذا configUSE_TRACE_FACILITY_2
            بنية
            {
                /* Cf. porttraceStamp() */
                صحيح taskstamp;      /* Stamp from inside task to see where we are */
                صحيح taskstampcount; /* A counter usually incremented when we restart the task's loop */
            } porttrace;
        #پایان_اگر
    } xMPU_SETTINGS;

/* Main hack to use MPU_wrappers even when no MPU is defined (warning: mpu_setting should not be accessed; otherwise move this above xMPU_SETTINGS) */
    #إذا ( XCHAL_CP_رقم > 0 || configUSE_TRACE_FACILITY_2 ) && !پورت_USING_MPU_WRAPPERS /* If MPU wrappers not used, we still need to allocate coproc area */
        #لغو_تعریف پورت_USING_MPU_WRAPPERS
        #تعریف_کن پورت_USING_MPU_WRAPPERS    1                                           /* Enable it to allocate coproc area */
        #تعریف_کن MPU_WRAPPERS_H                                                        /* Override mpu_wrapper.h to disable unwanted code */
        #تعریف_کن PRIVILEGED_FUNCTION
        #تعریف_کن PRIVILEGED_داده
    #پایان_اگر

    فراغ vApplicationSleep( TickType_t x_Expected_Idle_زمان );

    #تعریف_کن پورت_SUPPRESS_TICKS_AND_SLEEP( idle_زمان )    vApplicationSleep( idle_زمان )

    فراغ _xt_coproc_release( متطاير فراغ * coproc_sa_پایه );

/*-----------------------------------------------------------*/

    #إذا ( ESP_IDF_نسخه >= ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
        /* Architecture specific optimisations. */

        #إذا config_USE_پورت_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
            #إذا ( configMAX_PRIORITIES > 32 )
                #خطا config_USE_پورت_OPTIMISED_TASK_SELECTION can only be مجموعه مقصد 1 when configMAX_PRIORITIES is less than or equal مقصد 32.  It is very rare that a system requires بیشتر than 10 مقصد 15 different priorities as tasks that share a اولویت will time برش.
            #پایان_اگر

/* Store/clear the ready priorities in a bit map. */
            #تعریف_کن پورت_رکورد_READY_اولویت( ux_اولویت, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_اولویت ) )
            #تعریف_کن پورت_RESET_READY_اولویت( ux_اولویت, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_اولویت ) )

/*-----------------------------------------------------------*/

            #تعریف_کن پورت_GET_HIGHEST_اولویت( ux_بالاترین_اولویت, uxReadyPriorities )    ux_بالاترین_اولویت = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )

        #پایان_اگر /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #پایان_اگر /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

/*-----------------------------------------------------------*/

/*
 * Map to the memory management routines required for the port.
 *
 * Note that libc standard malloc/free are also available for
 * non-FreeRTOS-specific code, and behave the same as
 * pvPortMalloc()/vPortFree().
 */
    #تعریف_کن pv_پورت_Malloc                       انباشته_caps_malloc_default
    #تعریف_کن v_پورت_Free                          انباشته_caps_free
    #تعریف_کن x_پورت_Get_Free_انباشته_اندازه               esp_get_free_انباشته_اندازه
    #تعریف_کن x_پورت_Get_Minimum_Ever_Free_انباشته_اندازه    esp_get_minimum_free_انباشته_اندازه

    #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )

/*
 * Send an interrupt to another core in order to make the task running
 * on it yield for a higher-priority task.
 */

        فراغ v_پورت_Yield_Other_Core( پایه_Type_t coreid ) PRIVILEGED_FUNCTION;

    #پایان_اگر /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

/*
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack
 * watchpoint around.
 */
    فراغ v_پورت_مجموعه_پشته_Watchpoint( فراغ * px_پشته_شروع );

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
    پایه_Type_t x_پورت_درون_Isr_Context();


/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
    پایه_Type_t x_پورت_Interrupted_From_ISRContext();

/*
 * The structures and methods of manipulating the MPU are contained within the
 * port layer.
 *
 * Fills the xMPUSettings structure with the memory region information
 * contained in xRegions.
 */
    #إذا ( پورت_USING_MPU_WRAPPERS == 1 )
        بنية x_حافظه_REGION;
        فراغ v_پورت_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                        ثابت بنية x_حافظه_REGION * ثابت xRegions,
                                        پشته_Type_t * px_Bottom_از_پشته,
                                        config_پشته_عمق_TYPE ux_پشته_عمق ) PRIVILEGED_FUNCTION;
        فراغ v_پورت_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings );
    #پایان_اگر

/* Multi-core: get current core ID */
    ساكن مضمن پایه_Type_t IRAM_ATTR x_پورت_Get_Core_ID()
    {
        أرجع ( uint32_t ) cpu_hal_get_core_id();
    }

/* Get tick rate per second */
    uint32_t x_پورت_Get_Tick_نرخ_Hz( فراغ );

    ساكن مضمن bool IRAM_ATTR x_پورت_Can_Yield( فراغ )
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

        أرجع( ( ps_reg & PS_INTLEVEL_ماسک ) == 0 );
    }

/* porttrace */
    #إذا configUSE_TRACE_FACILITY_2
        #ضمن "porttrace.h"
    #پایان_اگر

/* configASSERT_2 if requested */
    #إذا configASSERT_2
        #ضمن <stdio.h>
        فراغ خروج( صحيح );
        #تعریف_کن configASSERT( x )    إذا( !( x ) ) { porttracePrint( -1 ); چاپ_کن( "\nAssertion failed in %s:%d\n", __FILE__, __LINE__ ); خروج( -1 ); }
    #پایان_اگر

/* Barriers */
    #تعریف_کن پورت_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )


#پایان_اگر // __ASSEMBLER__

/* *INDENT-OFF* */
#اگر_تعریف_شده __cplusplus
    }
#پایان_اگر
/* *INDENT-ON* */

#پایان_اگر /* PORTMACRO_H */
