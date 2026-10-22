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

#که_نه_تعریف_شوی PORTMACRO_H
#تعریف_کړه PORTMACRO_H

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    خارجي "C" {
#د_که_پای
/* *INDENT-ON* */

#که_نه_تعریف_شوی __ASSEMBLER__

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
    #د_که_پای /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

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

    #تعریف_کړه پورټ_CHAR          int8_t
    #تعریف_کړه پورټ_FLOAT         عائم
    #تعریف_کړه پورټ_DOUBLE        مزدوج
    #تعریف_کړه پورټ_LONG          int32_t
    #تعریف_کړه پورټ_SHORT         int16_t
    #تعریف_کړه پورټ_ډېری_TYPE    uint8_t
    #تعریف_کړه پورټ_بنسټ_TYPE     صحيح

    تعريفنوع پورټ_ډېری_TYPE           ډېری_Type_t;
    تعريفنوع پورټ_بنسټ_TYPE            بنسټ_Type_t;
    تعريفنوع بینښه پورټ_بنسټ_TYPE   UBaseType_t;

    #إذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_16_بټونه )
        تعريفنوع uint16_t             TickType_t;
        #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffff
    #وإلاإذا ( config_TICK_TYPE_پلنوالی_دننه_بټونه == TICK_TYPE_پلنوالی_32_بټونه )
        تعريفنوع uint32_t             TickType_t;
        #تعریف_کړه پورټ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
    #وإلا
        #تېروتنه config_TICK_TYPE_پلنوالی_دننه_بټونه سېټ منزل unsupported tick type پلنوالی.
    #د_که_پای
/*-----------------------------------------------------------*/

/* portbenchmark */
    #ضمن "portbenchmark.h"

    #ضمن "sdkconfig.h"
    #ضمن "esp_attr.h"

/* "mux" data structure (spinlock) */
    تعريفنوع spinlock_t پورټ_MUX_TYPE;                                /**< Spinlock type used by FreeRTOS critical sections */
    #تعریف_کړه پورټ_MUX_INITIALIZER_UNLOCKED    SPINLOCK_INITIALIZER    /**< Spinlock initializer */
    #تعریف_کړه پورټ_MUX_FREE_VAL                SPINLOCK_FREE           /**< Spinlock is free. [refactor-todo] check if this is still required */
    #تعریف_کړه پورټ_MUX_NO_TIMEOUT              SPINLOCK_WAIT_FOREVER   /**< When passed for 'timeout_cycles', spin forever if necessary. [refactor-todo] check if this is still required */
    #تعریف_کړه پورټ_MUX_TRY_قلف                SPINLOCK_NO_WAIT        /**< Try to acquire the spinlock a single time only. [refactor-todo] check if this is still required */
    #تعریف_کړه پورټ_MUX_INITIALIZE( mux )    spinlock_initialize( mux ) /*< Initialize a spinlock to its unlocked state */

    #تعریف_کړه پورټ_CRITICAL_NESTING_دننه_TCB     1

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
    فراغ v_پورټ_CPUInitialize_Mutex( پورټ_MUX_TYPE * mux );
    #که_تعریف_شوی CONFIG_FREERTOS_PORTMUX_DEBUG
        #تېروتنه CONFIG_FREERTOS_PORTMUX_DEBUG not supported دننه Amazon FreeRTOS
    #د_که_پای

    فراغ vTaskExitCritical();
    فراغ vTaskEnterCritical();
    ساكن مضمن فراغ v_پورټ_Consume_Spinlock_Arg( صحيح ناکارول_شوی,
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
    bool v_پورټ_CPUAcquire_Mutex_Timeout( پورټ_MUX_TYPE * mux,
                                      صحيح timeout_دورې );
    فراغ v_پورټ_CPURelease_Mutex( پورټ_MUX_TYPE * mux );

    #تعریف_کړه پورټ_ENTER_CRITICAL( ... )        افعل { vTaskEnterCritical(); v_پورټ_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } طالما( 0 )
    #تعریف_کړه پورټ_EXIT_CRITICAL( ... )         افعل { vTaskExitCritical(); v_پورټ_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } طالما( 0 )


    #تعریف_کړه پورټ_ENTER_CRITICAL_ISR( mux )    v_پورټ_CPUAcquire_Mutex_Timeout( mux, پورټ_MUX_NO_TIMEOUT )
    #تعریف_کړه پورټ_EXIT_CRITICAL_ISR( mux )     v_پورټ_CPURelease_Mutex( mux )

    #تعریف_کړه پورټ_ENTER_CRITICAL_خوندي( mux ) \
    افعل {                                   \
        إذا( x_پورټ_دننه_Isr_Context() ) {        \
            پورټ_ENTER_CRITICAL_ISR( mux ); \
        }                                  \
        وإلا {                             \
            پورټ_ENTER_CRITICAL( mux );     \
        }                                  \
    } طالما( 0 )

    #تعریف_کړه پورټ_EXIT_CRITICAL_خوندي( mux ) \
    افعل {                                  \
        إذا( x_پورټ_دننه_Isr_Context() ) {       \
            پورټ_EXIT_CRITICAL_ISR( mux ); \
        }                                 \
        وإلا {                            \
            پورټ_EXIT_CRITICAL( mux );     \
        }                                 \
    } طالما( 0 )

    #تعریف_کړه پورټ_ASSERT_IF_دننه_ISR()    v_پورټ_Assert_If_دننه_ISR()
    فراغ v_پورټ_Assert_If_دننه_ISR( فراغ );

/* Critical section management. NW-TODO: replace XTOS_SET_INTLEVEL with more efficient version, if any? */
/* These cannot be nested. They should be used with a lot of care and cannot be called from interrupt level. */
/* */
/* Only applies to one CPU. See notes above & below for reasons not to use these. */
    #تعریف_کړه پورټ_DISABLE_INTERRUPTS()    افعل { XTOS_سېټ_INTLEVEL( XCHAL_EXCM_LEVEL ); portbenchmark_مداخله_DISABLE(); } طالما( 0 )
    #تعریف_کړه پورټ_ENABLE_INTERRUPTS()     افعل { portbenchmark_مداخله_RESTORE( 0 ); XTOS_سېټ_INTLEVEL( 0 ); } طالما( 0 )

/* Cleaner solution allows nested interrupts disabling and restoring via local registers or stack. */
/* They can be called from interrupts too. */
/* WARNING: Only applies to current CPU. See notes above. */
    ساكن مضمن UBaseType_t __attribute__( ( always_inline ) ) x_پورټ_سېټ_مداخله_ماسک_From_ISR( فراغ )
    {
        UBaseType_t prev_int_level = XTOS_سېټ_INTLEVEL( XCHAL_EXCM_LEVEL );

        portbenchmark_مداخله_DISABLE();
        أرجع prev_int_level;
    }

    ساكن مضمن فراغ __attribute__( ( always_inline ) ) v_پورټ_Clear_مداخله_ماسک_From_ISR( UBaseType_t prev_level )
    {
        portbenchmark_مداخله_RESTORE( prev_level );
        XTOS_RESTORE_JUST_INTLEVEL( prev_level );
    }

/* These FreeRTOS versions are similar to the nested versions above */
    #تعریف_کړه پورټ_سېټ_مداخله_ماسک_FROM_ISR()                  x_پورټ_سېټ_مداخله_ماسک_From_ISR()
    #تعریف_کړه پورټ_CLEAR_مداخله_ماسک_FROM_ISR( prev_level )    v_پورټ_Clear_مداخله_ماسک_From_ISR( prev_level )

/*Because the ROM routines don't necessarily handle a stack in external RAM correctly, we force */
/*the stack memory to always be internal. */
    #تعریف_کړه پورټ_Tcb_حافظه_Caps      ( MALLOC_CAP_دننی | MALLOC_CAP_8_بټ )
    #تعریف_کړه پورټ_ډېری_حافظه_Caps    ( MALLOC_CAP_دننی | MALLOC_CAP_8_بټ )

    #تعریف_کړه pv_پورټ_Malloc_Tcb_Mem( اندازه )        ډېرۍ_caps_malloc( اندازه, پورټ_Tcb_حافظه_Caps )
    #تعریف_کړه pv_پورټ_Malloc_ډېری_Mem( اندازه )      ډېرۍ_caps_malloc( اندازه, پورټ_ډېری_حافظه_Caps )

/*xTaskCreateStatic uses these functions to check incoming memory. */
    #تعریف_کړه پورټ_VALID_TCB_MEM( ptr )          ( esp_ptr_دننی( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #که_تعریف_شوی CONFIG_SPIRAM_ALLOW_ډېری_EXTERNAL_حافظه
        #تعریف_کړه پورټ_VALID_ډېری_MEM( ptr )    esp_ptr_byte_accessible( ptr )
    #وإلا
        #تعریف_کړه پورټ_VALID_ډېری_MEM( ptr )    ( esp_ptr_دننی( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #د_که_پای

/*
 * Wrapper for the Xtensa compare-and-set instruction. This subroutine will atomically compare
 * *addr to 'compare'. If *addr == compare, *addr is set to *set. *set is updated with the previous
 * value of *addr (either 'compare' or some other value.)
 *
 * Warning: From the ISA docs: in some (unspecified) cases, the s32c1i instruction may return the
 * *bitwise inverse* of the old mem if the mem wasn't written. This doesn't seem to happen on the
 * ESP32 (portMUX assertions would fail).
 */
    ساكن مضمن فراغ ux_پورټ_Compare_سېټ( متطاير uint32_t * addr,
                                         uint32_t compare,
                                         uint32_t * سېټ )
    {
        #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
            __asm__ __volatile__ (
                "WSR       %2,SCOMPARE1 \n"
                "S32C1I     %0, %1, 0   \n"
                : "=r" ( *سېټ )
                : "r" ( addr ), "r" ( compare ), "0" ( *سېټ )
                );
        #وإلا
            #إذا ( XCHAL_HAVE_S32C1I > 0 )
                __asm__ __volatile__ (
                    "WSR        %2,SCOMPARE1 \n"
                    "S32C1I     %0, %1, 0    \n"
                    : "=r" ( *سېټ )
                    : "r" ( addr ), "r" ( compare ), "0" ( *سېټ )
                    );
            #وإلا
                /* No S32C1I, so do this by disabling and re-enabling interrupts (slower) */
                uint32_t intlevel, old_ارزښت;
                __asm__ __volatile__ ( "rsil %0, " XTSTR( XCHAL_EXCM_LEVEL ) "\n"
                                       : "=r" ( intlevel ) );

                old_ارزښت = *addr;

                إذا( old_ارزښت == compare )
                {
                    *addr = *سېټ;
                }

                __asm__ __volatile__ ( "memw \n"
                                       "wsr %0, ps\n"
                                       : : "r" ( intlevel ) );

                *سېټ = old_ارزښت;
            #د_که_پای /* if ( XCHAL_HAVE_S32C1I > 0 ) */
        #د_که_پای /* #if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)) */
    }

    #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
        فراغ ux_پورټ_Compare_سېټ_Extram( متطاير uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * سېټ );
    #وإلا
        ساكن مضمن فراغ ux_پورټ_Compare_سېټ_Extram( متطاير uint32_t * addr,
                                                   uint32_t compare,
                                                   uint32_t * سېټ )
        {
            #إذا defined( CONFIG_SPIRAM )
                compare_and_سېټ_extram( addr, compare, سېټ );
            #د_که_پای
        }
    #د_که_پای /* if ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) ) */

/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #تعریف_کړه پورټ_ډېری_GROWTH      ( -1 )
    #تعریف_کړه پورټ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_شرح_HZ )
    #تعریف_کړه پورټ_BYTE_ALIGNMENT    4
    #تعریف_کړه پورټ_NOP()    XT_NOP()
/*-----------------------------------------------------------*/

/* Fine resolution time */
    #تعریف_کړه پورټ_GET_پرلپسې_وخت_COUNTER_ارزښت()    xthal_get_ccount()
/*ccount or esp_timer are initialized elsewhere */
    #تعریف_کړه پورټ_CONFIGURE_TIMER_FOR_پرلپسې_وخت_STATS()

    #که_تعریف_شوی CONFIG_FREERTOS_پرلپسې_وخت_STATS_USING_ESP_TIMER
/* Coarse resolution time (us) */
        #تعریف_کړه پورټ_ALT_GET_پرلپسې_وخت_COUNTER_ارزښت( x )    افعل { x = ( uint32_t ) esp_timer_get_وخت(); } طالما( 0 )
    #د_که_پای



/* Kernel utilities. */
    فراغ v_پورټ_Yield( فراغ );
    فراغ v_پورټ_Evaluate_Yield_From_ISR( صحيح argc,
                                    ... );
    فراغ frxt_تیاری_switch( فراغ );

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
        #تعریف_کړه پورټ_GET_دلیل_شمېر( ... )                        پورټ_GET_دلیل_شمېر_INNER( 0 __VA_OPT__(, ) __VA_ARGS__, 1, 0 )
    #وإلا
        #تعریف_کړه پورټ_GET_دلیل_شمېر( ... )                        پورټ_GET_دلیل_شمېر_INNER( 0, ## __VA_ARGS__, 1, 0 )
    #د_که_پای
    #تعریف_کړه پورټ_GET_دلیل_شمېر_INNER( zero, one, شمېر, ... )    شمېر

    _Static_assert( پورټ_GET_دلیل_شمېر() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments" );
    _Static_assert( پورټ_GET_دلیل_شمېر( 1 ) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument" );

    #تعریف_کړه پورټ_YIELD()    v_پورټ_Yield()

/* The macro below could be used when passing a single argument, or without any argument,
 * it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 * might result in undesired behaviour
 */
    #إذا defined( __cplusplus ) && ( __cplusplus > 201703L )
        #تعریف_کړه پورټ_YIELD_FROM_ISR( ... )    v_پورټ_Evaluate_Yield_From_ISR( پورټ_GET_دلیل_شمېر( __VA_ARGS__ ) __VA_OPT__(, ) __VA_ARGS__ )
    #وإلا
        #تعریف_کړه پورټ_YIELD_FROM_ISR( ... )    v_پورټ_Evaluate_Yield_From_ISR( پورټ_GET_دلیل_شمېر( __VA_ARGS__ ), ## __VA_ARGS__ )
    #د_که_پای

    ساكن مضمن بنسټ_Type_t x_پورټ_Get_Core_ID();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #تعریف_کړه پورټ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    فراغ vFunction( فراغ * pvParameters )
    #تعریف_کړه پورټ_TASK_FUNCTION( vFunction, pvParameters )          فراغ vFunction( فراغ * pvParameters )

/* When coprocessors are defined, we to maintain a pointer to coprocessors area. */
/* We currently use a hack: redefine field xMPU_SETTINGS in TCB block as a structure that can hold: */
/* MPU wrappers, coprocessor area pointer, trace code structure, and more if needed. */
/* The field is normally used for memory protection. FreeRTOS should create another general purpose field. */
    تعريفنوع بنية
    {
        #إذا XCHAL_CP_عدد > 0
            متطاير ډېری_Type_t * coproc_area; /* Pointer to coprocessor save area; MUST BE FIRST */
        #د_که_پای

        #إذا پورټ_USING_MPU_WRAPPERS
            /* Define here mpu_settings, which is port dependent */
            صحيح mpu_setting; /* Just a dummy example here; MPU not ported to Xtensa yet */
        #د_که_پای

        #إذا configUSE_TRACE_FACILITY_2
            بنية
            {
                /* Cf. porttraceStamp() */
                صحيح taskstamp;      /* Stamp from inside task to see where we are */
                صحيح taskstampcount; /* A counter usually incremented when we restart the task's loop */
            } porttrace;
        #د_که_پای
    } xMPU_SETTINGS;

/* Main hack to use MPU_wrappers even when no MPU is defined (warning: mpu_setting should not be accessed; otherwise move this above xMPU_SETTINGS) */
    #إذا ( XCHAL_CP_عدد > 0 || configUSE_TRACE_FACILITY_2 ) && !پورټ_USING_MPU_WRAPPERS /* If MPU wrappers not used, we still need to allocate coproc area */
        #تعریف_لغوه پورټ_USING_MPU_WRAPPERS
        #تعریف_کړه پورټ_USING_MPU_WRAPPERS    1                                           /* Enable it to allocate coproc area */
        #تعریف_کړه MPU_WRAPPERS_H                                                        /* Override mpu_wrapper.h to disable unwanted code */
        #تعریف_کړه PRIVILEGED_FUNCTION
        #تعریف_کړه PRIVILEGED_معلومات
    #د_که_پای

    فراغ vApplicationSleep( TickType_t x_Expected_Idle_وخت );

    #تعریف_کړه پورټ_SUPPRESS_TICKS_AND_SLEEP( idle_وخت )    vApplicationSleep( idle_وخت )

    فراغ _xt_coproc_release( متطاير فراغ * coproc_sa_بنسټ );

/*-----------------------------------------------------------*/

    #إذا ( ESP_IDF_نسخه >= ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
        /* Architecture specific optimisations. */

        #إذا config_USE_پورټ_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
            #إذا ( configMAX_PRIORITIES > 32 )
                #تېروتنه config_USE_پورټ_OPTIMISED_TASK_SELECTION can only be سېټ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires نور than 10 منزل 15 different priorities as tasks that share a لومړیتوب will time ټوټه.
            #د_که_پای

/* Store/clear the ready priorities in a bit map. */
            #تعریف_کړه پورټ_ریکارډ_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_لومړیتوب ) )
            #تعریف_کړه پورټ_RESET_READY_لومړیتوب( ux_لومړیتوب, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_لومړیتوب ) )

/*-----------------------------------------------------------*/

            #تعریف_کړه پورټ_GET_HIGHEST_لومړیتوب( ux_سر_لومړیتوب, uxReadyPriorities )    ux_سر_لومړیتوب = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )

        #د_که_پای /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #د_که_پای /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

/*-----------------------------------------------------------*/

/*
 * Map to the memory management routines required for the port.
 *
 * Note that libc standard malloc/free are also available for
 * non-FreeRTOS-specific code, and behave the same as
 * pvPortMalloc()/vPortFree().
 */
    #تعریف_کړه pv_پورټ_Malloc                       ډېرۍ_caps_malloc_default
    #تعریف_کړه v_پورټ_Free                          ډېرۍ_caps_free
    #تعریف_کړه x_پورټ_Get_Free_ډېرۍ_اندازه               esp_get_free_ډېرۍ_اندازه
    #تعریف_کړه x_پورټ_Get_Minimum_Ever_Free_ډېرۍ_اندازه    esp_get_minimum_free_ډېرۍ_اندازه

    #إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )

/*
 * Send an interrupt to another core in order to make the task running
 * on it yield for a higher-priority task.
 */

        فراغ v_پورټ_Yield_Other_Core( بنسټ_Type_t coreid ) PRIVILEGED_FUNCTION;

    #د_که_پای /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

/*
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack
 * watchpoint around.
 */
    فراغ v_پورټ_سېټ_ډېری_Watchpoint( فراغ * px_ډېری_پیل );

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
    بنسټ_Type_t x_پورټ_دننه_Isr_Context();


/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
    بنسټ_Type_t x_پورټ_Interrupted_From_ISRContext();

/*
 * The structures and methods of manipulating the MPU are contained within the
 * port layer.
 *
 * Fills the xMPUSettings structure with the memory region information
 * contained in xRegions.
 */
    #إذا ( پورټ_USING_MPU_WRAPPERS == 1 )
        بنية x_حافظه_REGION;
        فراغ v_پورټ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                        ثابت بنية x_حافظه_REGION * ثابت xRegions,
                                        ډېری_Type_t * px_Bottom_د_ډېری,
                                        config_ډېری_ژوروالی_TYPE ux_ډېری_ژوروالی ) PRIVILEGED_FUNCTION;
        فراغ v_پورټ_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings );
    #د_که_پای

/* Multi-core: get current core ID */
    ساكن مضمن بنسټ_Type_t IRAM_ATTR x_پورټ_Get_Core_ID()
    {
        أرجع ( uint32_t ) cpu_hal_get_core_id();
    }

/* Get tick rate per second */
    uint32_t x_پورټ_Get_Tick_شرح_Hz( فراغ );

    ساكن مضمن bool IRAM_ATTR x_پورټ_Can_Yield( فراغ )
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
    #د_که_پای

/* configASSERT_2 if requested */
    #إذا configASSERT_2
        #ضمن <stdio.h>
        فراغ وتل( صحيح );
        #تعریف_کړه configASSERT( x )    إذا( !( x ) ) { porttracePrint( -1 ); چاپ_کړه( "\nAssertion failed in %s:%d\n", __FILE__, __LINE__ ); وتل( -1 ); }
    #د_که_پای

/* Barriers */
    #تعریف_کړه پورټ_حافظه_BARRIER()    __asm متطاير ( "" ::: "memory" )


#د_که_پای // __ASSEMBLER__

/* *INDENT-OFF* */
#که_تعریف_شوی __cplusplus
    }
#د_که_پای
/* *INDENT-ON* */

#د_که_پای /* PORTMACRO_H */
