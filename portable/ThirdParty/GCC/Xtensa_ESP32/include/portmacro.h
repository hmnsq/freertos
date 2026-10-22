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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PORTMACRO_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMACRO_H

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ASSEMBLER__

    #ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

    #ਅਨ੍ਤਰ੍ਭਾਵ <xtensa/hal.h>
    #ਅਨ੍ਤਰ੍ਭਾਵ <xtensa/config/core.h>
    #ਅਨ੍ਤਰ੍ਭਾਵ <xtensa/config/system.h> /* required for XSHAL_CLIB */
    #ਅਨ੍ਤਰ੍ਭਾਵ <xtensa/xtruntime.h>
    #ਅਨ੍ਤਰ੍ਭਾਵ "soc/spinlock.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_timer.h" /* required for FreeRTOS run time stats */
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_system.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_idf_version.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_heap_caps.h"

/* TODO: Resolve build warnings generated due to this header inclusion */
    #ਅਨ੍ਤਰ੍ਭਾਵ "hal/cpu_hal.h"

/* TODO: These includes are not directly used in this file. They are kept into to prevent a breaking change. Remove these. */
    #ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
    #ਅਨ੍ਤਰ੍ਭਾਵ <xtensa/xtensa_api.h>

    #ਅਨ੍ਤਰ੍ਭਾਵ "soc/cpu.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "soc/soc_memory_layout.h"
    #ਜੇ ( ESP_IDF_ਸੰਸਕਰਣ >= ESP_IDF_ਸੰਸਕਰਣ_VAL( 4, 2, 0 ) )
        #ਅਨ੍ਤਰ੍ਭਾਵ "soc/compare_set.h"
    #ਜੇ_ਅੰਤ /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

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

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CHAR          int8_t
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FLOAT         ਦਸ਼ਮਲਵ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DOUBLE        ਦੁੱਗਣਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_LONG          int32_t
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SHORT         int16_t
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_TYPE    uint8_t
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਅਧਾਰ_TYPE     ਪੂਰਨ

    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਢੇਰ_TYPE           ਢੇਰ_Type_t;
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੋਰਟ_ਅਧਾਰ_TYPE            ਅਧਾਰ_Type_t;
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੋਰਟ_ਅਧਾਰ_TYPE   UBaseType_t;

    #ਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_16_ਬਿੱਟ )
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t             TickType_t;
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) 0xffff
    #ਜਾਂਜੇ ( config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ == TICK_TYPE_ਚੌੜਾਈ_32_ਬਿੱਟ )
        ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t             TickType_t;
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_DELAY    ( TickType_t ) 0xffffffffUL
    #ਨਹੀਂਤਾਂ
        #ਗਲਤੀ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ ਸੈੱਟ ਮੰਜ਼ਿਲ unsupported tick type ਚੌੜਾਈ.
    #ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/* portbenchmark */
    #ਅਨ੍ਤਰ੍ਭਾਵ "portbenchmark.h"

    #ਅਨ੍ਤਰ੍ਭਾਵ "sdkconfig.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "esp_attr.h"

/* "mux" data structure (spinlock) */
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ spinlock_t ਪੋਰਟ_MUX_TYPE;                                /**< Spinlock type used by FreeRTOS critical sections */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MUX_INITIALIZER_UNLOCKED    SPINLOCK_INITIALIZER    /**< Spinlock initializer */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MUX_FREE_VAL                SPINLOCK_FREE           /**< Spinlock is free. [refactor-todo] check if this is still required */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MUX_NO_TIMEOUT              SPINLOCK_WAIT_FOREVER   /**< When passed for 'timeout_cycles', spin forever if necessary. [refactor-todo] check if this is still required */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MUX_TRY_ਤਾਲਾ                SPINLOCK_NO_WAIT        /**< Try to acquire the spinlock a single time only. [refactor-todo] check if this is still required */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MUX_INITIALIZE( mux )    spinlock_initialize( mux ) /*< Initialize a spinlock to its unlocked state */

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਚ_TCB     1

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
    ਖਾਲੀ v_ਪੋਰਟ_CPUInitialize_Mutex( ਪੋਰਟ_MUX_TYPE * mux );
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
        #ਗਲਤੀ CONFIG_FREERTOS_PORTMUX_DEBUG not supported ਵਿੱਚ_2 Amazon FreeRTOS
    #ਜੇ_ਅੰਤ

    ਖਾਲੀ vTaskExitCritical();
    ਖਾਲੀ vTaskEnterCritical();
    ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ v_ਪੋਰਟ_Consume_Spinlock_Arg( ਪੂਰਨ ਅਣਵਰਤਿਆ,
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
    bool v_ਪੋਰਟ_CPUAcquire_Mutex_Timeout( ਪੋਰਟ_MUX_TYPE * mux,
                                      ਪੂਰਨ timeout_ਚੱਕਰਾਂ );
    ਖਾਲੀ v_ਪੋਰਟ_CPURelease_Mutex( ਪੋਰਟ_MUX_TYPE * mux );

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL( ... )        ਕਰੋ { vTaskEnterCritical(); v_ਪੋਰਟ_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } ਜਦੋਂ( 0 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL( ... )         ਕਰੋ { vTaskExitCritical(); v_ਪੋਰਟ_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } ਜਦੋਂ( 0 )


    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL_ISR( mux )    v_ਪੋਰਟ_CPUAcquire_Mutex_Timeout( mux, ਪੋਰਟ_MUX_NO_TIMEOUT )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL_ISR( mux )     v_ਪੋਰਟ_CPURelease_Mutex( mux )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENTER_CRITICAL_ਸੁਰੱਖਿਅਤ( mux ) \
    ਕਰੋ {                                   \
        ਜੇ( x_ਪੋਰਟ_ਵਿੱਚ_Isr_Context() ) {        \
            ਪੋਰਟ_ENTER_CRITICAL_ISR( mux ); \
        }                                  \
        ਨਹੀਂਤਾਂ {                             \
            ਪੋਰਟ_ENTER_CRITICAL( mux );     \
        }                                  \
    } ਜਦੋਂ( 0 )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EXIT_CRITICAL_ਸੁਰੱਖਿਅਤ( mux ) \
    ਕਰੋ {                                  \
        ਜੇ( x_ਪੋਰਟ_ਵਿੱਚ_Isr_Context() ) {       \
            ਪੋਰਟ_EXIT_CRITICAL_ISR( mux ); \
        }                                 \
        ਨਹੀਂਤਾਂ {                            \
            ਪੋਰਟ_EXIT_CRITICAL( mux );     \
        }                                 \
    } ਜਦੋਂ( 0 )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ASSERT_IF_ਵਿੱਚ_ISR()    v_ਪੋਰਟ_Assert_If_ਵਿੱਚ_ISR()
    ਖਾਲੀ v_ਪੋਰਟ_Assert_If_ਵਿੱਚ_ISR( ਖਾਲੀ );

/* Critical section management. NW-TODO: replace XTOS_SET_INTLEVEL with more efficient version, if any? */
/* These cannot be nested. They should be used with a lot of care and cannot be called from interrupt level. */
/* */
/* Only applies to one CPU. See notes above & below for reasons not to use these. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DISABLE_INTERRUPTS()    ਕਰੋ { XTOS_ਸੈੱਟ_INTLEVEL( XCHAL_EXCM_LEVEL ); portbenchmark_ਰੁਕਾਵਟ_DISABLE(); } ਜਦੋਂ( 0 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ENABLE_INTERRUPTS()     ਕਰੋ { portbenchmark_ਰੁਕਾਵਟ_RESTORE( 0 ); XTOS_ਸੈੱਟ_INTLEVEL( 0 ); } ਜਦੋਂ( 0 )

/* Cleaner solution allows nested interrupts disabling and restoring via local registers or stack. */
/* They can be called from interrupts too. */
/* WARNING: Only applies to current CPU. See notes above. */
    ਸਥਿਰ ਸਤਰਅੰਦਰ UBaseType_t __attribute__( ( always_inline ) ) x_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( ਖਾਲੀ )
    {
        UBaseType_t prev_int_level = XTOS_ਸੈੱਟ_INTLEVEL( XCHAL_EXCM_LEVEL );

        portbenchmark_ਰੁਕਾਵਟ_DISABLE();
        ਵਾਪਸ prev_int_level;
    }

    ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ __attribute__( ( always_inline ) ) v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( UBaseType_t prev_level )
    {
        portbenchmark_ਰੁਕਾਵਟ_RESTORE( prev_level );
        XTOS_RESTORE_JUST_INTLEVEL( prev_level );
    }

/* These FreeRTOS versions are similar to the nested versions above */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR()                  x_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR()
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ_FROM_ISR( prev_level )    v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ_From_ISR( prev_level )

/*Because the ROM routines don't necessarily handle a stack in external RAM correctly, we force */
/*the stack memory to always be internal. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_Tcb_ਸਮ੍ਰਿਤੀ_Caps      ( MALLOC_CAP_ਅੰਦਰੂਨੀ | MALLOC_CAP_8_ਦੋਆਧਾਰੀ_ਅੰਕ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_ਸਮ੍ਰਿਤੀ_Caps    ( MALLOC_CAP_ਅੰਦਰੂਨੀ | MALLOC_CAP_8_ਦੋਆਧਾਰੀ_ਅੰਕ )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pv_ਪੋਰਟ_Malloc_Tcb_Mem( ਮਾਪ )        ਢੇਰ_caps_malloc( ਮਾਪ, ਪੋਰਟ_Tcb_ਸਮ੍ਰਿਤੀ_Caps )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pv_ਪੋਰਟ_Malloc_ਢੇਰ_Mem( ਮਾਪ )      ਢੇਰ_caps_malloc( ਮਾਪ, ਪੋਰਟ_ਢੇਰ_ਸਮ੍ਰਿਤੀ_Caps )

/*xTaskCreateStatic uses these functions to check incoming memory. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_VALID_TCB_MEM( ptr )          ( esp_ptr_ਅੰਦਰੂਨੀ( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_SPIRAM_ALLOW_ਢੇਰ_EXTERNAL_ਸਮ੍ਰਿਤੀ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_VALID_ਢੇਰ_MEM( ptr )    esp_ptr_byte_accessible( ptr )
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_VALID_ਢੇਰ_MEM( ptr )    ( esp_ptr_ਅੰਦਰੂਨੀ( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #ਜੇ_ਅੰਤ

/*
 * Wrapper for the Xtensa compare-and-set instruction. This subroutine will atomically compare
 * *addr to 'compare'. If *addr == compare, *addr is set to *set. *set is updated with the previous
 * value of *addr (either 'compare' or some other value.)
 *
 * Warning: From the ISA docs: in some (unspecified) cases, the s32c1i instruction may return the
 * *bitwise inverse* of the old mem if the mem wasn't written. This doesn't seem to happen on the
 * ESP32 (portMUX assertions would fail).
 */
    ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ ux_ਪੋਰਟ_Compare_ਸੈੱਟ( ਅਸਥਿਰ uint32_t * addr,
                                         uint32_t compare,
                                         uint32_t * ਸੈੱਟ )
    {
        #ਜੇ ( ESP_IDF_ਸੰਸਕਰਣ < ESP_IDF_ਸੰਸਕਰਣ_VAL( 4, 2, 0 ) )
            __asm__ __volatile__ (
                "WSR       %2,SCOMPARE1 \n"
                "S32C1I     %0, %1, 0   \n"
                : "=r" ( *ਸੈੱਟ )
                : "r" ( addr ), "r" ( compare ), "0" ( *ਸੈੱਟ )
                );
        #ਨਹੀਂਤਾਂ
            #ਜੇ ( XCHAL_HAVE_S32C1I > 0 )
                __asm__ __volatile__ (
                    "WSR        %2,SCOMPARE1 \n"
                    "S32C1I     %0, %1, 0    \n"
                    : "=r" ( *ਸੈੱਟ )
                    : "r" ( addr ), "r" ( compare ), "0" ( *ਸੈੱਟ )
                    );
            #ਨਹੀਂਤਾਂ
                /* No S32C1I, so do this by disabling and re-enabling interrupts (slower) */
                uint32_t intlevel, old_ਮੁੱਲ;
                __asm__ __volatile__ ( "rsil %0, " XTSTR( XCHAL_EXCM_LEVEL ) "\n"
                                       : "=r" ( intlevel ) );

                old_ਮੁੱਲ = *addr;

                ਜੇ( old_ਮੁੱਲ == compare )
                {
                    *addr = *ਸੈੱਟ;
                }

                __asm__ __volatile__ ( "memw \n"
                                       "wsr %0, ps\n"
                                       : : "r" ( intlevel ) );

                *ਸੈੱਟ = old_ਮੁੱਲ;
            #ਜੇ_ਅੰਤ /* if ( XCHAL_HAVE_S32C1I > 0 ) */
        #ਜੇ_ਅੰਤ /* #if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)) */
    }

    #ਜੇ ( ESP_IDF_ਸੰਸਕਰਣ < ESP_IDF_ਸੰਸਕਰਣ_VAL( 4, 2, 0 ) )
        ਖਾਲੀ ux_ਪੋਰਟ_Compare_ਸੈੱਟ_Extram( ਅਸਥਿਰ uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * ਸੈੱਟ );
    #ਨਹੀਂਤਾਂ
        ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ ux_ਪੋਰਟ_Compare_ਸੈੱਟ_Extram( ਅਸਥਿਰ uint32_t * addr,
                                                   uint32_t compare,
                                                   uint32_t * ਸੈੱਟ )
        {
            #ਜੇ defined( CONFIG_SPIRAM )
                compare_and_ਸੈੱਟ_extram( addr, compare, ਸੈੱਟ );
            #ਜੇ_ਅੰਤ
        }
    #ਜੇ_ਅੰਤ /* if ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) ) */

/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਢੇਰ_GROWTH      ( -1 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ਦਰ_HZ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_BYTE_ALIGNMENT    4
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NOP()    XT_NOP()
/*-----------------------------------------------------------*/

/* Fine resolution time */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_ਮੁੱਲ()    xthal_get_ccount()
/*ccount or esp_timer are initialized elsewhere */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CONFIGURE_TIMER_FOR_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS()

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS_USING_ESP_TIMER
/* Coarse resolution time (us) */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ALT_GET_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_ਮੁੱਲ( x )    ਕਰੋ { x = ( uint32_t ) esp_timer_get_ਸਮਾਂ(); } ਜਦੋਂ( 0 )
    #ਜੇ_ਅੰਤ



/* Kernel utilities. */
    ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ );
    ਖਾਲੀ v_ਪੋਰਟ_Evaluate_Yield_From_ISR( ਪੂਰਨ argc,
                                    ... );
    ਖਾਲੀ frxt_ਤਿਆਰੀ_switch( ਖਾਲੀ );

/* Macro to count number of arguments of a __VA_ARGS__ used to support portYIELD_FROM_ISR with,
 * or without arguments. The macro counts only 0 or 1 arguments.
 *
 * In the future, we want to switch to C++20. We also want to become compatible with clang.
 * Hence, we provide two versions of the following macros which are using variadic arguments.
 * The first one is using the GNU extension ##__VA_ARGS__. The second one is using the C++20 feature __VA_OPT__(,).
 * This allows users to compile their code with standard C++20 enabled instead of the GNU extension.
 * Below C++20, we haven't found any good alternative to using ##__VA_ARGS__.
 */
    #ਜੇ defined( __cplusplus ) && ( __cplusplus > 201703L )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ਦਲੀਲ_ਗਿਣਤੀ( ... )                        ਪੋਰਟ_GET_ਦਲੀਲ_ਗਿਣਤੀ_INNER( 0 __VA_OPT__(, ) __VA_ARGS__, 1, 0 )
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ਦਲੀਲ_ਗਿਣਤੀ( ... )                        ਪੋਰਟ_GET_ਦਲੀਲ_ਗਿਣਤੀ_INNER( 0, ## __VA_ARGS__, 1, 0 )
    #ਜੇ_ਅੰਤ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_ਦਲੀਲ_ਗਿਣਤੀ_INNER( zero, one, ਗਿਣਤੀ_2, ... )    ਗਿਣਤੀ_2

    _Static_assert( ਪੋਰਟ_GET_ਦਲੀਲ_ਗਿਣਤੀ() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments" );
    _Static_assert( ਪੋਰਟ_GET_ਦਲੀਲ_ਗਿਣਤੀ( 1 ) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument" );

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD()    v_ਪੋਰਟ_Yield()

/* The macro below could be used when passing a single argument, or without any argument,
 * it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 * might result in undesired behaviour
 */
    #ਜੇ defined( __cplusplus ) && ( __cplusplus > 201703L )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( ... )    v_ਪੋਰਟ_Evaluate_Yield_From_ISR( ਪੋਰਟ_GET_ਦਲੀਲ_ਗਿਣਤੀ( __VA_ARGS__ ) __VA_OPT__(, ) __VA_ARGS__ )
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_YIELD_FROM_ISR( ... )    v_ਪੋਰਟ_Evaluate_Yield_From_ISR( ਪੋਰਟ_GET_ਦਲੀਲ_ਗਿਣਤੀ( __VA_ARGS__ ), ## __VA_ARGS__ )
    #ਜੇ_ਅੰਤ

    ਸਥਿਰ ਸਤਰਅੰਦਰ ਅਧਾਰ_Type_t x_ਪੋਰਟ_Get_Core_ID();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_FUNCTION( vFunction, pvParameters )          ਖਾਲੀ vFunction( ਖਾਲੀ * pvParameters )

/* When coprocessors are defined, we to maintain a pointer to coprocessors area. */
/* We currently use a hack: redefine field xMPU_SETTINGS in TCB block as a structure that can hold: */
/* MPU wrappers, coprocessor area pointer, trace code structure, and more if needed. */
/* The field is normally used for memory protection. FreeRTOS should create another general purpose field. */
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
    {
        #ਜੇ XCHAL_CP_ਅੰਕ > 0
            ਅਸਥਿਰ ਢੇਰ_Type_t * coproc_area; /* Pointer to coprocessor save area; MUST BE FIRST */
        #ਜੇ_ਅੰਤ

        #ਜੇ ਪੋਰਟ_USING_MPU_WRAPPERS
            /* Define here mpu_settings, which is port dependent */
            ਪੂਰਨ mpu_setting; /* Just a dummy example here; MPU not ported to Xtensa yet */
        #ਜੇ_ਅੰਤ

        #ਜੇ configUSE_TRACE_FACILITY_2
            ਬਣਤਰ
            {
                /* Cf. porttraceStamp() */
                ਪੂਰਨ taskstamp;      /* Stamp from inside task to see where we are */
                ਪੂਰਨ taskstampcount; /* A counter usually incremented when we restart the task's loop */
            } porttrace;
        #ਜੇ_ਅੰਤ
    } xMPU_SETTINGS;

/* Main hack to use MPU_wrappers even when no MPU is defined (warning: mpu_setting should not be accessed; otherwise move this above xMPU_SETTINGS) */
    #ਜੇ ( XCHAL_CP_ਅੰਕ > 0 || configUSE_TRACE_FACILITY_2 ) && !ਪੋਰਟ_USING_MPU_WRAPPERS /* If MPU wrappers not used, we still need to allocate coproc area */
        #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਪੋਰਟ_USING_MPU_WRAPPERS
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_USING_MPU_WRAPPERS    1                                           /* Enable it to allocate coproc area */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_WRAPPERS_H                                                        /* Override mpu_wrapper.h to disable unwanted code */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRIVILEGED_FUNCTION
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRIVILEGED_ਅੰਕੜੇ
    #ਜੇ_ਅੰਤ

    ਖਾਲੀ vApplicationSleep( TickType_t x_Expected_Idle_ਸਮਾਂ );

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SUPPRESS_TICKS_AND_SLEEP( idle_ਸਮਾਂ )    vApplicationSleep( idle_ਸਮਾਂ )

    ਖਾਲੀ _xt_coproc_release( ਅਸਥਿਰ ਖਾਲੀ * coproc_sa_ਅਧਾਰ );

/*-----------------------------------------------------------*/

    #ਜੇ ( ESP_IDF_ਸੰਸਕਰਣ >= ESP_IDF_ਸੰਸਕਰਣ_VAL( 4, 2, 0 ) )
        /* Architecture specific optimisations. */

        #ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
            #ਜੇ ( configMAX_PRIORITIES > 32 )
                #ਗਲਤੀ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION can only be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 when configMAX_PRIORITIES is less than or equal ਮੰਜ਼ਿਲ 32.  It is very rare that a system requires ਹੋਰ than 10 ਮੰਜ਼ਿਲ 15 different priorities as tasks that share a ਤਰਜੀਹ will time ਟੁਕੜਾ.
            #ਜੇ_ਅੰਤ

/* Store/clear the ready priorities in a bit map. */
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰਿਕਾਰਡ_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ਤਰਜੀਹ ) )
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_RESET_READY_ਤਰਜੀਹ( ux_ਤਰਜੀਹ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ਤਰਜੀਹ ) )

/*-----------------------------------------------------------*/

            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_GET_HIGHEST_ਤਰਜੀਹ( ux_ਸਿਖਰ_ਤਰਜੀਹ, uxReadyPriorities )    ux_ਸਿਖਰ_ਤਰਜੀਹ = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )

        #ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #ਜੇ_ਅੰਤ /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

/*-----------------------------------------------------------*/

/*
 * Map to the memory management routines required for the port.
 *
 * Note that libc standard malloc/free are also available for
 * non-FreeRTOS-specific code, and behave the same as
 * pvPortMalloc()/vPortFree().
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ pv_ਪੋਰਟ_Malloc                       ਢੇਰ_caps_malloc_default
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ v_ਪੋਰਟ_Free                          ਢੇਰ_caps_free
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ x_ਪੋਰਟ_Get_Free_ਢੇਰ_ਮਾਪ               esp_get_free_ਢੇਰ_ਮਾਪ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ x_ਪੋਰਟ_Get_Minimum_Ever_Free_ਢੇਰ_ਮਾਪ    esp_get_minimum_free_ਢੇਰ_ਮਾਪ

    #ਜੇ ( ESP_IDF_ਸੰਸਕਰਣ < ESP_IDF_ਸੰਸਕਰਣ_VAL( 4, 2, 0 ) )

/*
 * Send an interrupt to another core in order to make the task running
 * on it yield for a higher-priority task.
 */

        ਖਾਲੀ v_ਪੋਰਟ_Yield_Other_Core( ਅਧਾਰ_Type_t coreid ) PRIVILEGED_FUNCTION;

    #ਜੇ_ਅੰਤ /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

/*
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack
 * watchpoint around.
 */
    ਖਾਲੀ v_ਪੋਰਟ_ਸੈੱਟ_ਢੇਰ_Watchpoint( ਖਾਲੀ * px_ਢੇਰ_ਸ਼ੁਰੂ );

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
    ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਵਿੱਚ_Isr_Context();


/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
    ਅਧਾਰ_Type_t x_ਪੋਰਟ_Interrupted_From_ISRContext();

/*
 * The structures and methods of manipulating the MPU are contained within the
 * port layer.
 *
 * Fills the xMPUSettings structure with the memory region information
 * contained in xRegions.
 */
    #ਜੇ ( ਪੋਰਟ_USING_MPU_WRAPPERS == 1 )
        ਬਣਤਰ x_ਸਮ੍ਰਿਤੀ_REGION;
        ਖਾਲੀ v_ਪੋਰਟ_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                        ਅਚਲ ਬਣਤਰ x_ਸਮ੍ਰਿਤੀ_REGION * ਅਚਲ xRegions,
                                        ਢੇਰ_Type_t * px_Bottom_ਦਾ_ਢੇਰ,
                                        config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ux_ਢੇਰ_ਡੂੰਘਾਈ ) PRIVILEGED_FUNCTION;
        ਖਾਲੀ v_ਪੋਰਟ_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings );
    #ਜੇ_ਅੰਤ

/* Multi-core: get current core ID */
    ਸਥਿਰ ਸਤਰਅੰਦਰ ਅਧਾਰ_Type_t IRAM_ATTR x_ਪੋਰਟ_Get_Core_ID()
    {
        ਵਾਪਸ ( uint32_t ) cpu_hal_get_core_id();
    }

/* Get tick rate per second */
    uint32_t x_ਪੋਰਟ_Get_Tick_ਦਰ_Hz( ਖਾਲੀ );

    ਸਥਿਰ ਸਤਰਅੰਦਰ bool IRAM_ATTR x_ਪੋਰਟ_Can_Yield( ਖਾਲੀ )
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

        ਵਾਪਸ( ( ps_reg & PS_INTLEVEL_ਨਕਾਬ ) == 0 );
    }

/* porttrace */
    #ਜੇ configUSE_TRACE_FACILITY_2
        #ਅਨ੍ਤਰ੍ਭਾਵ "porttrace.h"
    #ਜੇ_ਅੰਤ

/* configASSERT_2 if requested */
    #ਜੇ configASSERT_2
        #ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
        ਖਾਲੀ ਬਾਹਰ_ਨਿਕਲੋ( ਪੂਰਨ );
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configASSERT( x )    ਜੇ( !( x ) ) { porttracePrint( -1 ); ਲਿਖੋ( "\nAssertion failed in %s:%d\n", __FILE__, __LINE__ ); ਬਾਹਰ_ਨਿਕਲੋ( -1 ); }
    #ਜੇ_ਅੰਤ

/* Barriers */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER()    __asm ਅਸਥਿਰ ( "" ::: "memory" )


#ਜੇ_ਅੰਤ // __ASSEMBLER__

/* *INDENT-OFF* */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
    }
#ਜੇ_ਅੰਤ
/* *INDENT-ON* */

#ਜੇ_ਅੰਤ /* PORTMACRO_H */
