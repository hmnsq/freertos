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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PORTMACRO_H
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMACRO_H

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __ASSEMBLER__

    #ಅನ್ತರ್ಭಾವ <stdint.h>

    #ಅನ್ತರ್ಭಾವ <xtensa/hal.h>
    #ಅನ್ತರ್ಭಾವ <xtensa/config/core.h>
    #ಅನ್ತರ್ಭಾವ <xtensa/config/system.h> /* required for XSHAL_CLIB */
    #ಅನ್ತರ್ಭಾವ <xtensa/xtruntime.h>
    #ಅನ್ತರ್ಭಾವ "soc/spinlock.h"
    #ಅನ್ತರ್ಭಾವ "esp_timer.h" /* required for FreeRTOS run time stats */
    #ಅನ್ತರ್ಭಾವ "esp_system.h"
    #ಅನ್ತರ್ಭಾವ "esp_idf_version.h"
    #ಅನ್ತರ್ಭಾವ "esp_heap_caps.h"

/* TODO: Resolve build warnings generated due to this header inclusion */
    #ಅನ್ತರ್ಭಾವ "hal/cpu_hal.h"

/* TODO: These includes are not directly used in this file. They are kept into to prevent a breaking change. Remove these. */
    #ಅನ್ತರ್ಭಾವ <limits.h>
    #ಅನ್ತರ್ಭಾವ <xtensa/xtensa_api.h>

    #ಅನ್ತರ್ಭಾವ "soc/cpu.h"
    #ಅನ್ತರ್ಭಾವ "soc/soc_memory_layout.h"
    #ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ >= ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )
        #ಅನ್ತರ್ಭಾವ "soc/compare_set.h"
    #ಆದರೆ_ಅಂತ್ಯ /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

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

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CHAR          int8_t
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FLOAT         ದಶಮಾಂಶ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DOUBLE        ದ್ವಿಗುಣ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_LONG          int32_t
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SHORT         int16_t
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_TYPE    uint8_t
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ತಳ_TYPE     ಪೂರ್ಣಾಂಕ

    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ರಾಶಿ_TYPE           ರಾಶಿ_Type_t;
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೋರ್ಟ್_ತಳ_TYPE            ತಳ_Type_t;
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಪೋರ್ಟ್_ತಳ_TYPE   UBaseType_t;

    #ಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_16_ಬಿಟ್ಟುಗಳು )
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t             TickType_t;
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY    ( TickType_t ) 0xffff
    #ಅಥವಾಆದರೆ ( config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು == TICK_TYPE_ಅಗಲ_32_ಬಿಟ್ಟುಗಳು )
        ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t             TickType_t;
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_DELAY    ( TickType_t ) 0xffffffffUL
    #ಇಲ್ಲದಿದ್ದರೆ
        #ದೋಷ config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು ಗಣ ಗಮ್ಯ unsupported tick type ಅಗಲ.
    #ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/* portbenchmark */
    #ಅನ್ತರ್ಭಾವ "portbenchmark.h"

    #ಅನ್ತರ್ಭಾವ "sdkconfig.h"
    #ಅನ್ತರ್ಭಾವ "esp_attr.h"

/* "mux" data structure (spinlock) */
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ spinlock_t ಪೋರ್ಟ್_MUX_TYPE;                                /**< Spinlock type used by FreeRTOS critical sections */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MUX_INITIALIZER_UNLOCKED    SPINLOCK_INITIALIZER    /**< Spinlock initializer */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MUX_FREE_VAL                SPINLOCK_FREE           /**< Spinlock is free. [refactor-todo] check if this is still required */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MUX_NO_TIMEOUT              SPINLOCK_WAIT_FOREVER   /**< When passed for 'timeout_cycles', spin forever if necessary. [refactor-todo] check if this is still required */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MUX_TRY_ಬೀಗ                SPINLOCK_NO_WAIT        /**< Try to acquire the spinlock a single time only. [refactor-todo] check if this is still required */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MUX_INITIALIZE( mux )    spinlock_initialize( mux ) /*< Initialize a spinlock to its unlocked state */

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CRITICAL_NESTING_ಒಳ_TCB     1

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
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_CPUInitialize_Mutex( ಪೋರ್ಟ್_MUX_TYPE * mux );
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
        #ದೋಷ CONFIG_FREERTOS_PORTMUX_DEBUG not supported ಒಳ Amazon FreeRTOS
    #ಆದರೆ_ಅಂತ್ಯ

    ಶೂನ್ಯ vTaskExitCritical();
    ಶೂನ್ಯ vTaskEnterCritical();
    ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Consume_Spinlock_Arg( ಪೂರ್ಣಾಂಕ ಬಳಸದ,
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
    bool v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Timeout( ಪೋರ್ಟ್_MUX_TYPE * mux,
                                      ಪೂರ್ಣಾಂಕ timeout_ಚಕ್ರಗಳು );
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_CPURelease_Mutex( ಪೋರ್ಟ್_MUX_TYPE * mux );

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL( ... )        ಮಾಡು { vTaskEnterCritical(); v_ಪೋರ್ಟ್_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } ಆಗ( 0 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL( ... )         ಮಾಡು { vTaskExitCritical(); v_ಪೋರ್ಟ್_Consume_Spinlock_Arg( 0, ## __VA_ARGS__ ); } ಆಗ( 0 )


    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL_ISR( mux )    v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Timeout( mux, ಪೋರ್ಟ್_MUX_NO_TIMEOUT )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL_ISR( mux )     v_ಪೋರ್ಟ್_CPURelease_Mutex( mux )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENTER_CRITICAL_ಸುರಕ್ಷಿತ( mux ) \
    ಮಾಡು {                                   \
        ಆದರೆ( x_ಪೋರ್ಟ್_ಒಳ_Isr_Context() ) {        \
            ಪೋರ್ಟ್_ENTER_CRITICAL_ISR( mux ); \
        }                                  \
        ಇಲ್ಲದಿದ್ದರೆ {                             \
            ಪೋರ್ಟ್_ENTER_CRITICAL( mux );     \
        }                                  \
    } ಆಗ( 0 )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EXIT_CRITICAL_ಸುರಕ್ಷಿತ( mux ) \
    ಮಾಡು {                                  \
        ಆದರೆ( x_ಪೋರ್ಟ್_ಒಳ_Isr_Context() ) {       \
            ಪೋರ್ಟ್_EXIT_CRITICAL_ISR( mux ); \
        }                                 \
        ಇಲ್ಲದಿದ್ದರೆ {                            \
            ಪೋರ್ಟ್_EXIT_CRITICAL( mux );     \
        }                                 \
    } ಆಗ( 0 )

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ASSERT_IF_ಒಳ_ISR()    v_ಪೋರ್ಟ್_Assert_If_ಒಳ_ISR()
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Assert_If_ಒಳ_ISR( ಶೂನ್ಯ );

/* Critical section management. NW-TODO: replace XTOS_SET_INTLEVEL with more efficient version, if any? */
/* These cannot be nested. They should be used with a lot of care and cannot be called from interrupt level. */
/* */
/* Only applies to one CPU. See notes above & below for reasons not to use these. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DISABLE_INTERRUPTS()    ಮಾಡು { XTOS_ಗಣ_INTLEVEL( XCHAL_EXCM_LEVEL ); portbenchmark_ಅಡಚಣೆ_DISABLE(); } ಆಗ( 0 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ENABLE_INTERRUPTS()     ಮಾಡು { portbenchmark_ಅಡಚಣೆ_RESTORE( 0 ); XTOS_ಗಣ_INTLEVEL( 0 ); } ಆಗ( 0 )

/* Cleaner solution allows nested interrupts disabling and restoring via local registers or stack. */
/* They can be called from interrupts too. */
/* WARNING: Only applies to current CPU. See notes above. */
    ಸ್ಥಿರ ಸಾಲೊಳಗೆ UBaseType_t __attribute__( ( always_inline ) ) x_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( ಶೂನ್ಯ )
    {
        UBaseType_t prev_int_level = XTOS_ಗಣ_INTLEVEL( XCHAL_EXCM_LEVEL );

        portbenchmark_ಅಡಚಣೆ_DISABLE();
        ಹಿಂತಿರುಗಿ prev_int_level;
    }

    ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ __attribute__( ( always_inline ) ) v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( UBaseType_t prev_level )
    {
        portbenchmark_ಅಡಚಣೆ_RESTORE( prev_level );
        XTOS_RESTORE_JUST_INTLEVEL( prev_level );
    }

/* These FreeRTOS versions are similar to the nested versions above */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR()                  x_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR()
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ_FROM_ISR( prev_level )    v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ_From_ISR( prev_level )

/*Because the ROM routines don't necessarily handle a stack in external RAM correctly, we force */
/*the stack memory to always be internal. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_Tcb_ಸ್ಮರಣೆ_Caps      ( MALLOC_CAP_ಆಂತರಿಕ | MALLOC_CAP_8_ಬಿಟ್ )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_ಸ್ಮರಣೆ_Caps    ( MALLOC_CAP_ಆಂತರಿಕ | MALLOC_CAP_8_ಬಿಟ್ )

    #ವ್ಯಾಖ್ಯಾನಿಸು pv_ಪೋರ್ಟ್_Malloc_Tcb_Mem( ಗಾತ್ರ_2 )        ರಾಶಿ_caps_malloc( ಗಾತ್ರ_2, ಪೋರ್ಟ್_Tcb_ಸ್ಮರಣೆ_Caps )
    #ವ್ಯಾಖ್ಯಾನಿಸು pv_ಪೋರ್ಟ್_Malloc_ರಾಶಿ_Mem( ಗಾತ್ರ_2 )      ರಾಶಿ_caps_malloc( ಗಾತ್ರ_2, ಪೋರ್ಟ್_ರಾಶಿ_ಸ್ಮರಣೆ_Caps )

/*xTaskCreateStatic uses these functions to check incoming memory. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_VALID_TCB_MEM( ptr )          ( esp_ptr_ಆಂತರಿಕ( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_SPIRAM_ALLOW_ರಾಶಿ_EXTERNAL_ಸ್ಮರಣೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_VALID_ರಾಶಿ_MEM( ptr )    esp_ptr_byte_accessible( ptr )
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_VALID_ರಾಶಿ_MEM( ptr )    ( esp_ptr_ಆಂತರಿಕ( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #ಆದರೆ_ಅಂತ್ಯ

/*
 * Wrapper for the Xtensa compare-and-set instruction. This subroutine will atomically compare
 * *addr to 'compare'. If *addr == compare, *addr is set to *set. *set is updated with the previous
 * value of *addr (either 'compare' or some other value.)
 *
 * Warning: From the ISA docs: in some (unspecified) cases, the s32c1i instruction may return the
 * *bitwise inverse* of the old mem if the mem wasn't written. This doesn't seem to happen on the
 * ESP32 (portMUX assertions would fail).
 */
    ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ ux_ಪೋರ್ಟ್_Compare_ಗಣ( ಅಸ್ಥಿರ uint32_t * addr,
                                         uint32_t compare,
                                         uint32_t * ಗಣ )
    {
        #ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ < ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )
            __asm__ __volatile__ (
                "WSR       %2,SCOMPARE1 \n"
                "S32C1I     %0, %1, 0   \n"
                : "=r" ( *ಗಣ )
                : "r" ( addr ), "r" ( compare ), "0" ( *ಗಣ )
                );
        #ಇಲ್ಲದಿದ್ದರೆ
            #ಆದರೆ ( XCHAL_HAVE_S32C1I > 0 )
                __asm__ __volatile__ (
                    "WSR        %2,SCOMPARE1 \n"
                    "S32C1I     %0, %1, 0    \n"
                    : "=r" ( *ಗಣ )
                    : "r" ( addr ), "r" ( compare ), "0" ( *ಗಣ )
                    );
            #ಇಲ್ಲದಿದ್ದರೆ
                /* No S32C1I, so do this by disabling and re-enabling interrupts (slower) */
                uint32_t intlevel, old_ಮೌಲ್ಯ;
                __asm__ __volatile__ ( "rsil %0, " XTSTR( XCHAL_EXCM_LEVEL ) "\n"
                                       : "=r" ( intlevel ) );

                old_ಮೌಲ್ಯ = *addr;

                ಆದರೆ( old_ಮೌಲ್ಯ == compare )
                {
                    *addr = *ಗಣ;
                }

                __asm__ __volatile__ ( "memw \n"
                                       "wsr %0, ps\n"
                                       : : "r" ( intlevel ) );

                *ಗಣ = old_ಮೌಲ್ಯ;
            #ಆದರೆ_ಅಂತ್ಯ /* if ( XCHAL_HAVE_S32C1I > 0 ) */
        #ಆದರೆ_ಅಂತ್ಯ /* #if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)) */
    }

    #ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ < ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )
        ಶೂನ್ಯ ux_ಪೋರ್ಟ್_Compare_ಗಣ_Extram( ಅಸ್ಥಿರ uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * ಗಣ );
    #ಇಲ್ಲದಿದ್ದರೆ
        ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ ux_ಪೋರ್ಟ್_Compare_ಗಣ_Extram( ಅಸ್ಥಿರ uint32_t * addr,
                                                   uint32_t compare,
                                                   uint32_t * ಗಣ )
        {
            #ಆದರೆ defined( CONFIG_SPIRAM )
                compare_and_ಗಣ_extram( addr, compare, ಗಣ );
            #ಆದರೆ_ಅಂತ್ಯ
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) ) */

/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ರಾಶಿ_GROWTH      ( -1 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TICK_PERIOD_MS    ( ( TickType_t ) 1000 / config_TICK_ದರ_HZ )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_BYTE_ALIGNMENT    4
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NOP()    XT_NOP()
/*-----------------------------------------------------------*/

/* Fine resolution time */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ಸತತ_ಸಮಯ_COUNTER_ಮೌಲ್ಯ()    xthal_get_ccount()
/*ccount or esp_timer are initialized elsewhere */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CONFIGURE_TIMER_FOR_ಸತತ_ಸಮಯ_STATS()

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_ಸತತ_ಸಮಯ_STATS_USING_ESP_TIMER
/* Coarse resolution time (us) */
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ALT_GET_ಸತತ_ಸಮಯ_COUNTER_ಮೌಲ್ಯ( x )    ಮಾಡು { x = ( uint32_t ) esp_timer_get_ಸಮಯ(); } ಆಗ( 0 )
    #ಆದರೆ_ಅಂತ್ಯ



/* Kernel utilities. */
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ );
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Evaluate_Yield_From_ISR( ಪೂರ್ಣಾಂಕ argc,
                                    ... );
    ಶೂನ್ಯ frxt_ಸಿದ್ಧತೆ_switch( ಶೂನ್ಯ );

/* Macro to count number of arguments of a __VA_ARGS__ used to support portYIELD_FROM_ISR with,
 * or without arguments. The macro counts only 0 or 1 arguments.
 *
 * In the future, we want to switch to C++20. We also want to become compatible with clang.
 * Hence, we provide two versions of the following macros which are using variadic arguments.
 * The first one is using the GNU extension ##__VA_ARGS__. The second one is using the C++20 feature __VA_OPT__(,).
 * This allows users to compile their code with standard C++20 enabled instead of the GNU extension.
 * Below C++20, we haven't found any good alternative to using ##__VA_ARGS__.
 */
    #ಆದರೆ defined( __cplusplus ) && ( __cplusplus > 201703L )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ವಾದ_ಎಣಿಕೆ( ... )                        ಪೋರ್ಟ್_GET_ವಾದ_ಎಣಿಕೆ_INNER( 0 __VA_OPT__(, ) __VA_ARGS__, 1, 0 )
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ವಾದ_ಎಣಿಕೆ( ... )                        ಪೋರ್ಟ್_GET_ವಾದ_ಎಣಿಕೆ_INNER( 0, ## __VA_ARGS__, 1, 0 )
    #ಆದರೆ_ಅಂತ್ಯ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_ವಾದ_ಎಣಿಕೆ_INNER( zero, one, ಎಣಿಕೆ_2, ... )    ಎಣಿಕೆ_2

    _Static_assert( ಪೋರ್ಟ್_GET_ವಾದ_ಎಣಿಕೆ() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments" );
    _Static_assert( ಪೋರ್ಟ್_GET_ವಾದ_ಎಣಿಕೆ( 1 ) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument" );

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD()    v_ಪೋರ್ಟ್_Yield()

/* The macro below could be used when passing a single argument, or without any argument,
 * it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 * might result in undesired behaviour
 */
    #ಆದರೆ defined( __cplusplus ) && ( __cplusplus > 201703L )
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( ... )    v_ಪೋರ್ಟ್_Evaluate_Yield_From_ISR( ಪೋರ್ಟ್_GET_ವಾದ_ಎಣಿಕೆ( __VA_ARGS__ ) __VA_OPT__(, ) __VA_ARGS__ )
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_YIELD_FROM_ISR( ... )    v_ಪೋರ್ಟ್_Evaluate_Yield_From_ISR( ಪೋರ್ಟ್_GET_ವಾದ_ಎಣಿಕೆ( __VA_ARGS__ ), ## __VA_ARGS__ )
    #ಆದರೆ_ಅಂತ್ಯ

    ಸ್ಥಿರ ಸಾಲೊಳಗೆ ತಳ_Type_t x_ಪೋರ್ಟ್_Get_Core_ID();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION_PROTO( vFunction, pvParameters )    ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_FUNCTION( vFunction, pvParameters )          ಶೂನ್ಯ vFunction( ಶೂನ್ಯ * pvParameters )

/* When coprocessors are defined, we to maintain a pointer to coprocessors area. */
/* We currently use a hack: redefine field xMPU_SETTINGS in TCB block as a structure that can hold: */
/* MPU wrappers, coprocessor area pointer, trace code structure, and more if needed. */
/* The field is normally used for memory protection. FreeRTOS should create another general purpose field. */
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
    {
        #ಆದರೆ XCHAL_CP_ಅಂಕೆ > 0
            ಅಸ್ಥಿರ ರಾಶಿ_Type_t * coproc_area; /* Pointer to coprocessor save area; MUST BE FIRST */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ಪೋರ್ಟ್_USING_MPU_WRAPPERS
            /* Define here mpu_settings, which is port dependent */
            ಪೂರ್ಣಾಂಕ mpu_setting; /* Just a dummy example here; MPU not ported to Xtensa yet */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ configUSE_TRACE_FACILITY_2
            ರಚನೆ
            {
                /* Cf. porttraceStamp() */
                ಪೂರ್ಣಾಂಕ taskstamp;      /* Stamp from inside task to see where we are */
                ಪೂರ್ಣಾಂಕ taskstampcount; /* A counter usually incremented when we restart the task's loop */
            } porttrace;
        #ಆದರೆ_ಅಂತ್ಯ
    } xMPU_SETTINGS;

/* Main hack to use MPU_wrappers even when no MPU is defined (warning: mpu_setting should not be accessed; otherwise move this above xMPU_SETTINGS) */
    #ಆದರೆ ( XCHAL_CP_ಅಂಕೆ > 0 || configUSE_TRACE_FACILITY_2 ) && !ಪೋರ್ಟ್_USING_MPU_WRAPPERS /* If MPU wrappers not used, we still need to allocate coproc area */
        #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಪೋರ್ಟ್_USING_MPU_WRAPPERS
        #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_USING_MPU_WRAPPERS    1                                           /* Enable it to allocate coproc area */
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_WRAPPERS_H                                                        /* Override mpu_wrapper.h to disable unwanted code */
        #ವ್ಯಾಖ್ಯಾನಿಸು PRIVILEGED_FUNCTION
        #ವ್ಯಾಖ್ಯಾನಿಸು PRIVILEGED_ದತ್ತಾಂಶ
    #ಆದರೆ_ಅಂತ್ಯ

    ಶೂನ್ಯ vApplicationSleep( TickType_t x_Expected_Idle_ಸಮಯ );

    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SUPPRESS_TICKS_AND_SLEEP( idle_ಸಮಯ )    vApplicationSleep( idle_ಸಮಯ )

    ಶೂನ್ಯ _xt_coproc_release( ಅಸ್ಥಿರ ಶೂನ್ಯ * coproc_sa_ತಳ );

/*-----------------------------------------------------------*/

    #ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ >= ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )
        /* Architecture specific optimisations. */

        #ಆದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
            #ಆದರೆ ( configMAX_PRIORITIES > 32 )
                #ದೋಷ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION can only be ಗಣ ಗಮ್ಯ 1 when configMAX_PRIORITIES is less than or equal ಗಮ್ಯ 32.  It is very rare that a system requires ಇನ್ನಷ್ಟು than 10 ಗಮ್ಯ 15 different priorities as tasks that share a ಆದ್ಯತೆ will time ತುಂಡು.
            #ಆದರೆ_ಅಂತ್ಯ

/* Store/clear the ready priorities in a bit map. */
            #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದಾಖಲೆ_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( ux_ಆದ್ಯತೆ ) )
            #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_RESET_READY_ಆದ್ಯತೆ( ux_ಆದ್ಯತೆ, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( ux_ಆದ್ಯತೆ ) )

/*-----------------------------------------------------------*/

            #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_GET_HIGHEST_ಆದ್ಯತೆ( ux_ತುದಿ_ಆದ್ಯತೆ, uxReadyPriorities )    ux_ತುದಿ_ಆದ್ಯತೆ = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )

        #ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #ಆದರೆ_ಅಂತ್ಯ /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

/*-----------------------------------------------------------*/

/*
 * Map to the memory management routines required for the port.
 *
 * Note that libc standard malloc/free are also available for
 * non-FreeRTOS-specific code, and behave the same as
 * pvPortMalloc()/vPortFree().
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು pv_ಪೋರ್ಟ್_Malloc                       ರಾಶಿ_caps_malloc_default
    #ವ್ಯಾಖ್ಯಾನಿಸು v_ಪೋರ್ಟ್_Free                          ರಾಶಿ_caps_free
    #ವ್ಯಾಖ್ಯಾನಿಸು x_ಪೋರ್ಟ್_Get_Free_ರಾಶಿ_ಗಾತ್ರ               esp_get_free_ರಾಶಿ_ಗಾತ್ರ
    #ವ್ಯಾಖ್ಯಾನಿಸು x_ಪೋರ್ಟ್_Get_Minimum_Ever_Free_ರಾಶಿ_ಗಾತ್ರ    esp_get_minimum_free_ರಾಶಿ_ಗಾತ್ರ

    #ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ < ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )

/*
 * Send an interrupt to another core in order to make the task running
 * on it yield for a higher-priority task.
 */

        ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield_Other_Core( ತಳ_Type_t coreid ) PRIVILEGED_FUNCTION;

    #ಆದರೆ_ಅಂತ್ಯ /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

/*
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack
 * watchpoint around.
 */
    ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಗಣ_ರಾಶಿ_Watchpoint( ಶೂನ್ಯ * px_ರಾಶಿ_ಆರಂಭ );

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
    ತಳ_Type_t x_ಪೋರ್ಟ್_ಒಳ_Isr_Context();


/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
    ತಳ_Type_t x_ಪೋರ್ಟ್_Interrupted_From_ISRContext();

/*
 * The structures and methods of manipulating the MPU are contained within the
 * port layer.
 *
 * Fills the xMPUSettings structure with the memory region information
 * contained in xRegions.
 */
    #ಆದರೆ ( ಪೋರ್ಟ್_USING_MPU_WRAPPERS == 1 )
        ರಚನೆ x_ಸ್ಮರಣೆ_REGION;
        ಶೂನ್ಯ v_ಪೋರ್ಟ್_Store_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings,
                                        ಸ್ಥಿರಾಂಕ ರಚನೆ x_ಸ್ಮರಣೆ_REGION * ಸ್ಥಿರಾಂಕ xRegions,
                                        ರಾಶಿ_Type_t * px_Bottom_ದ_ರಾಶಿ,
                                        config_ರಾಶಿ_ಆಳ_TYPE ux_ರಾಶಿ_ಆಳ ) PRIVILEGED_FUNCTION;
        ಶೂನ್ಯ v_ಪೋರ್ಟ್_Release_Task_MPUSettings( xMPU_SETTINGS * xMPUSettings );
    #ಆದರೆ_ಅಂತ್ಯ

/* Multi-core: get current core ID */
    ಸ್ಥಿರ ಸಾಲೊಳಗೆ ತಳ_Type_t IRAM_ATTR x_ಪೋರ್ಟ್_Get_Core_ID()
    {
        ಹಿಂತಿರುಗಿ ( uint32_t ) cpu_hal_get_core_id();
    }

/* Get tick rate per second */
    uint32_t x_ಪೋರ್ಟ್_Get_Tick_ದರ_Hz( ಶೂನ್ಯ );

    ಸ್ಥಿರ ಸಾಲೊಳಗೆ bool IRAM_ATTR x_ಪೋರ್ಟ್_Can_Yield( ಶೂನ್ಯ )
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

        ಹಿಂತಿರುಗಿ( ( ps_reg & PS_INTLEVEL_ಮುಖವಾಡ ) == 0 );
    }

/* porttrace */
    #ಆದರೆ configUSE_TRACE_FACILITY_2
        #ಅನ್ತರ್ಭಾವ "porttrace.h"
    #ಆದರೆ_ಅಂತ್ಯ

/* configASSERT_2 if requested */
    #ಆದರೆ configASSERT_2
        #ಅನ್ತರ್ಭಾವ <stdio.h>
        ಶೂನ್ಯ ನಿರ್ಗಮಿಸು( ಪೂರ್ಣಾಂಕ );
        #ವ್ಯಾಖ್ಯಾನಿಸು configASSERT( x )    ಆದರೆ( !( x ) ) { porttracePrint( -1 ); ಬರೆ( "\nAssertion failed in %s:%d\n", __FILE__, __LINE__ ); ನಿರ್ಗಮಿಸು( -1 ); }
    #ಆದರೆ_ಅಂತ್ಯ

/* Barriers */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER()    __asm ಅಸ್ಥಿರ ( "" ::: "memory" )


#ಆದರೆ_ಅಂತ್ಯ // __ASSEMBLER__

/* *INDENT-OFF* */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
    }
#ಆದರೆ_ಅಂತ್ಯ
/* *INDENT-ON* */

#ಆದರೆ_ಅಂತ್ಯ /* PORTMACRO_H */
