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

#ifndef PORTMACRO_H
#define PORTMACRO_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    ବାହ୍ୟ "C" {
#endif
/* *INDENT-ON* */

#ifndef __ASSEMBLER__

    #ଅନ୍ତର୍ଭାଵ <stdint.h>

    #ଅନ୍ତର୍ଭାଵ <xtensa/hal.h>
    #ଅନ୍ତର୍ଭାଵ <xtensa/config/core.h>
    #ଅନ୍ତର୍ଭାଵ <xtensa/config/system.h> /* required for XSHAL_CLIB */
    #ଅନ୍ତର୍ଭାଵ <xtensa/xtruntime.h>
    #ଅନ୍ତର୍ଭାଵ "soc/spinlock.h"
    #ଅନ୍ତର୍ଭାଵ "esp_timer.h" /* required for FreeRTOS run time stats */
    #ଅନ୍ତର୍ଭାଵ "esp_system.h"
    #ଅନ୍ତର୍ଭାଵ "esp_idf_version.h"
    #ଅନ୍ତର୍ଭାଵ "esp_heap_caps.h"

/* TODO: Resolve build warnings generated due to this header inclusion */
    #ଅନ୍ତର୍ଭାଵ "hal/cpu_hal.h"

/* TODO: These includes are not directly used in this file. They are kept into to prevent a breaking change. Remove these. */
    #ଅନ୍ତର୍ଭାଵ <limits.h>
    #ଅନ୍ତର୍ଭାଵ <xtensa/xtensa_api.h>

    #ଅନ୍ତର୍ଭାଵ "soc/cpu.h"
    #ଅନ୍ତର୍ଭାଵ "soc/soc_memory_layout.h"
    #ଯଦି ( ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
        #ଅନ୍ତର୍ଭାଵ "soc/compare_set.h"
    #endif /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

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

    #define portCHAR          int8_t
    #define portFLOAT         ଦଶମିକ
    #define portDOUBLE        ଦ୍ୱିଗୁଣ
    #define portLONG          int32_t
    #define portSHORT         int16_t
    #define port_ଗଦା_TYPE    uint8_t
    #define portBASE_TYPE     ପୂର୍ଣ୍ଣସଂଖ୍ୟା

    ପ୍ରକାରବ୍ୟାଖ୍ୟା port_ଗଦା_TYPE           ଗଦା_Type_t;
    ପ୍ରକାରବ୍ୟାଖ୍ୟା portBASE_TYPE            BaseType_t;
    ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned portBASE_TYPE   UBaseType_t;

    #ଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        ପ୍ରକାରବ୍ୟାଖ୍ୟା uint16_t             TickType_t;
        #define portMAX_DELAY    ( TickType_t ) 0xffff
    #ନଚେତଯଦି ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
        ପ୍ରକାରବ୍ୟାଖ୍ୟା uint32_t             TickType_t;
        #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
    #ଅନ୍ୟଥା
        #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
    #endif
/*-----------------------------------------------------------*/

/* portbenchmark */
    #ଅନ୍ତର୍ଭାଵ "portbenchmark.h"

    #ଅନ୍ତର୍ଭାଵ "sdkconfig.h"
    #ଅନ୍ତର୍ଭାଵ "esp_attr.h"

/* "mux" data structure (spinlock) */
    ପ୍ରକାରବ୍ୟାଖ୍ୟା spinlock_t portMUX_TYPE;                                /**< Spinlock type used by FreeRTOS critical sections */
    #define portMUX_INITIALIZER_UNLOCKED    SPINLOCK_INITIALIZER    /**< Spinlock initializer */
    #define portMUX_FREE_VAL                SPINLOCK_FREE           /**< Spinlock is free. [refactor-todo] check if this is still required */
    #define portMUX_NO_TIMEOUT              SPINLOCK_WAIT_FOREVER   /**< When passed for 'timeout_cycles', spin forever if necessary. [refactor-todo] check if this is still required */
    #define portMUX_TRY_LOCK                SPINLOCK_NO_WAIT        /**< Try to acquire the spinlock a single time only. [refactor-todo] check if this is still required */
    #define portMUX_INITIALIZE( mux )    spinlock_initialize( mux ) /*< Initialize a spinlock to its unlocked state */

    #define portCRITICAL_NESTING_IN_TCB     1

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
    ଶୂନ୍ୟ vPortCPUInitializeMutex( portMUX_TYPE * mux );
    #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
        #error CONFIG_FREERTOS_PORTMUX_DEBUG not supported in Amazon FreeRTOS
    #endif

    ଶୂନ୍ୟ vTaskExitCritical();
    ଶୂନ୍ୟ vTaskEnterCritical();
    ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ vPortConsumeSpinlockArg( ପୂର୍ଣ୍ଣସଂଖ୍ୟା unused,
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
    bool vPortCPUAcquireMutexTimeout( portMUX_TYPE * mux,
                                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା timeout_cycles );
    ଶୂନ୍ୟ vPortCPUReleaseMutex( portMUX_TYPE * mux );

    #define portENTER_CRITICAL( ... )        କର { vTaskEnterCritical(); vPortConsumeSpinlockArg( 0, ## __VA_ARGS__ ); } ଯେତେବେଳେ( 0 )
    #define portEXIT_CRITICAL( ... )         କର { vTaskExitCritical(); vPortConsumeSpinlockArg( 0, ## __VA_ARGS__ ); } ଯେତେବେଳେ( 0 )


    #define portENTER_CRITICAL_ISR( mux )    vPortCPUAcquireMutexTimeout( mux, portMUX_NO_TIMEOUT )
    #define portEXIT_CRITICAL_ISR( mux )     vPortCPUReleaseMutex( mux )

    #define portENTER_CRITICAL_SAFE( mux ) \
    କର {                                   \
        ଯଦି( xPortInIsrContext() ) {        \
            portENTER_CRITICAL_ISR( mux ); \
        }                                  \
        ଅନ୍ୟଥା {                             \
            portENTER_CRITICAL( mux );     \
        }                                  \
    } ଯେତେବେଳେ( 0 )

    #define portEXIT_CRITICAL_SAFE( mux ) \
    କର {                                  \
        ଯଦି( xPortInIsrContext() ) {       \
            portEXIT_CRITICAL_ISR( mux ); \
        }                                 \
        ଅନ୍ୟଥା {                            \
            portEXIT_CRITICAL( mux );     \
        }                                 \
    } ଯେତେବେଳେ( 0 )

    #define portASSERT_IF_IN_ISR()    vPortAssertIfInISR()
    ଶୂନ୍ୟ vPortAssertIfInISR( ଶୂନ୍ୟ );

/* Critical section management. NW-TODO: replace XTOS_SET_INTLEVEL with more efficient version, if any? */
/* These cannot be nested. They should be used with a lot of care and cannot be called from interrupt level. */
/* */
/* Only applies to one CPU. See notes above & below for reasons not to use these. */
    #define portDISABLE_INTERRUPTS()    କର { XTOS_SET_INTLEVEL( XCHAL_EXCM_LEVEL ); portbenchmarkINTERRUPT_DISABLE(); } ଯେତେବେଳେ( 0 )
    #define portENABLE_INTERRUPTS()     କର { portbenchmarkINTERRUPT_RESTORE( 0 ); XTOS_SET_INTLEVEL( 0 ); } ଯେତେବେଳେ( 0 )

/* Cleaner solution allows nested interrupts disabling and restoring via local registers or stack. */
/* They can be called from interrupts too. */
/* WARNING: Only applies to current CPU. See notes above. */
    ସ୍ଥିର ଧାଡ଼ିଭିତରେ UBaseType_t __attribute__( ( always_inline ) ) xPortSetInterruptMaskFromISR( ଶୂନ୍ୟ )
    {
        UBaseType_t prev_int_level = XTOS_SET_INTLEVEL( XCHAL_EXCM_LEVEL );

        portbenchmarkINTERRUPT_DISABLE();
        ଫେରନ୍ତୁ prev_int_level;
    }

    ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ __attribute__( ( always_inline ) ) vPortClearInterruptMaskFromISR( UBaseType_t prev_level )
    {
        portbenchmarkINTERRUPT_RESTORE( prev_level );
        XTOS_RESTORE_JUST_INTLEVEL( prev_level );
    }

/* These FreeRTOS versions are similar to the nested versions above */
    #define portSET_INTERRUPT_MASK_FROM_ISR()                  xPortSetInterruptMaskFromISR()
    #define portCLEAR_INTERRUPT_MASK_FROM_ISR( prev_level )    vPortClearInterruptMaskFromISR( prev_level )

/*Because the ROM routines don't necessarily handle a stack in external RAM correctly, we force */
/*the stack memory to always be internal. */
    #define portTcbMemoryCaps      ( MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT )
    #define port_ଗଦା_Memory_Caps    ( MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT )

    #define pvPortMallocTcbMem( size )        heap_caps_malloc( size, portTcbMemoryCaps )
    #define pv_Port_Malloc_ଗଦା_Mem( size )      heap_caps_malloc( size, port_ଗଦା_Memory_Caps )

/*xTaskCreateStatic uses these functions to check incoming memory. */
    #define portVALID_TCB_MEM( ptr )          ( esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #ifdef CONFIG_SPIRAM_ALLOW_ଗଦା_EXTERNAL_MEMORY
        #define port_VALID_ଗଦା_MEM( ptr )    esp_ptr_byte_accessible( ptr )
    #ଅନ୍ୟଥା
        #define port_VALID_ଗଦା_MEM( ptr )    ( esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #endif

/*
 * Wrapper for the Xtensa compare-and-set instruction. This subroutine will atomically compare
 * *addr to 'compare'. If *addr == compare, *addr is set to *set. *set is updated with the previous
 * value of *addr (either 'compare' or some other value.)
 *
 * Warning: From the ISA docs: in some (unspecified) cases, the s32c1i instruction may return the
 * *bitwise inverse* of the old mem if the mem wasn't written. This doesn't seem to happen on the
 * ESP32 (portMUX assertions would fail).
 */
    ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ uxPortCompareSet( ଅସ୍ଥିର uint32_t * addr,
                                         uint32_t compare,
                                         uint32_t * set )
    {
        #ଯଦି ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
            __asm__ __volatile__ (
                "WSR       %2,SCOMPARE1 \n"
                "S32C1I     %0, %1, 0   \n"
                : "=r" ( *set )
                : "r" ( addr ), "r" ( compare ), "0" ( *set )
                );
        #ଅନ୍ୟଥା
            #ଯଦି ( XCHAL_HAVE_S32C1I > 0 )
                __asm__ __volatile__ (
                    "WSR        %2,SCOMPARE1 \n"
                    "S32C1I     %0, %1, 0    \n"
                    : "=r" ( *set )
                    : "r" ( addr ), "r" ( compare ), "0" ( *set )
                    );
            #ଅନ୍ୟଥା
                /* No S32C1I, so do this by disabling and re-enabling interrupts (slower) */
                uint32_t intlevel, old_ମୂଲ୍ୟ;
                __asm__ __volatile__ ( "rsil %0, " XTSTR( XCHAL_EXCM_LEVEL ) "\n"
                                       : "=r" ( intlevel ) );

                old_ମୂଲ୍ୟ = *addr;

                ଯଦି( old_ମୂଲ୍ୟ == compare )
                {
                    *addr = *set;
                }

                __asm__ __volatile__ ( "memw \n"
                                       "wsr %0, ps\n"
                                       : : "r" ( intlevel ) );

                *set = old_ମୂଲ୍ୟ;
            #endif /* if ( XCHAL_HAVE_S32C1I > 0 ) */
        #endif /* #if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)) */
    }

    #ଯଦି ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
        ଶୂନ୍ୟ uxPortCompareSetExtram( ଅସ୍ଥିର uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * set );
    #ଅନ୍ୟଥା
        ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ uxPortCompareSetExtram( ଅସ୍ଥିର uint32_t * addr,
                                                   uint32_t compare,
                                                   uint32_t * set )
        {
            #ଯଦି defined( CONFIG_SPIRAM )
                compare_and_set_extram( addr, compare, set );
            #endif
        }
    #endif /* if ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) ) */

/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #define port_ଗଦା_GROWTH      ( -1 )
    #define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
    #define portBYTE_ALIGNMENT    4
    #define portNOP()    XT_NOP()
/*-----------------------------------------------------------*/

/* Fine resolution time */
    #define port_GET_RUN_TIME_COUNTER_ମୂଲ୍ୟ()    xthal_get_ccount()
/*ccount or esp_timer are initialized elsewhere */
    #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()

    #ifdef CONFIG_FREERTOS_RUN_TIME_STATS_USING_ESP_TIMER
/* Coarse resolution time (us) */
        #define port_ALT_GET_RUN_TIME_COUNTER_ମୂଲ୍ୟ( x )    କର { x = ( uint32_t ) esp_timer_get_time(); } ଯେତେବେଳେ( 0 )
    #endif



/* Kernel utilities. */
    ଶୂନ୍ୟ vPortYield( ଶୂନ୍ୟ );
    ଶୂନ୍ୟ vPortEvaluateYieldFromISR( ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc,
                                    ... );
    ଶୂନ୍ୟ _frxt_setup_switch( ଶୂନ୍ୟ );

/* Macro to count number of arguments of a __VA_ARGS__ used to support portYIELD_FROM_ISR with,
 * or without arguments. The macro counts only 0 or 1 arguments.
 *
 * In the future, we want to switch to C++20. We also want to become compatible with clang.
 * Hence, we provide two versions of the following macros which are using variadic arguments.
 * The first one is using the GNU extension ##__VA_ARGS__. The second one is using the C++20 feature __VA_OPT__(,).
 * This allows users to compile their code with standard C++20 enabled instead of the GNU extension.
 * Below C++20, we haven't found any good alternative to using ##__VA_ARGS__.
 */
    #ଯଦି defined( __cplusplus ) && ( __cplusplus > 201703L )
        #define port_GET_ARGUMENT_ଗଣନା( ... )                        port_GET_ARGUMENT_ଗଣନା_INNER( 0 __VA_OPT__(, ) __VA_ARGS__, 1, 0 )
    #ଅନ୍ୟଥା
        #define port_GET_ARGUMENT_ଗଣନା( ... )                        port_GET_ARGUMENT_ଗଣନା_INNER( 0, ## __VA_ARGS__, 1, 0 )
    #endif
    #define port_GET_ARGUMENT_ଗଣନା_INNER( zero, one, ଗଣନା_2, ... )    ଗଣନା_2

    _Static_assert( port_GET_ARGUMENT_ଗଣନା() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments" );
    _Static_assert( port_GET_ARGUMENT_ଗଣନା( 1 ) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument" );

    #define portYIELD()    vPortYield()

/* The macro below could be used when passing a single argument, or without any argument,
 * it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 * might result in undesired behaviour
 */
    #ଯଦି defined( __cplusplus ) && ( __cplusplus > 201703L )
        #define portYIELD_FROM_ISR( ... )    vPortEvaluateYieldFromISR( port_GET_ARGUMENT_ଗଣନା( __VA_ARGS__ ) __VA_OPT__(, ) __VA_ARGS__ )
    #ଅନ୍ୟଥା
        #define portYIELD_FROM_ISR( ... )    vPortEvaluateYieldFromISR( port_GET_ARGUMENT_ଗଣନା( __VA_ARGS__ ), ## __VA_ARGS__ )
    #endif

    ସ୍ଥିର ଧାଡ଼ିଭିତରେ BaseType_t xPortGetCoreID();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )
    #define portTASK_FUNCTION( vFunction, pvParameters )          ଶୂନ୍ୟ vFunction( ଶୂନ୍ୟ * pvParameters )

/* When coprocessors are defined, we to maintain a pointer to coprocessors area. */
/* We currently use a hack: redefine field xMPU_SETTINGS in TCB block as a structure that can hold: */
/* MPU wrappers, coprocessor area pointer, trace code structure, and more if needed. */
/* The field is normally used for memory protection. FreeRTOS should create another general purpose field. */
    ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
    {
        #ଯଦି XCHAL_CP_ଅଙ୍କ > 0
            ଅସ୍ଥିର ଗଦା_Type_t * coproc_area; /* Pointer to coprocessor save area; MUST BE FIRST */
        #endif

        #ଯଦି portUSING_MPU_WRAPPERS
            /* Define here mpu_settings, which is port dependent */
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା mpu_setting; /* Just a dummy example here; MPU not ported to Xtensa yet */
        #endif

        #ଯଦି configUSE_TRACE_FACILITY_2
            ସଂରଚନା
            {
                /* Cf. porttraceStamp() */
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା taskstamp;      /* Stamp from inside task to see where we are */
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା taskstampcount; /* A counter usually incremented when we restart the task's loop */
            } porttrace;
        #endif
    } xMPU_SETTINGS;

/* Main hack to use MPU_wrappers even when no MPU is defined (warning: mpu_setting should not be accessed; otherwise move this above xMPU_SETTINGS) */
    #ଯଦି ( XCHAL_CP_ଅଙ୍କ > 0 || configUSE_TRACE_FACILITY_2 ) && !portUSING_MPU_WRAPPERS /* If MPU wrappers not used, we still need to allocate coproc area */
        #undef portUSING_MPU_WRAPPERS
        #define portUSING_MPU_WRAPPERS    1                                           /* Enable it to allocate coproc area */
        #define MPU_WRAPPERS_H                                                        /* Override mpu_wrapper.h to disable unwanted code */
        #define PRIVILEGED_FUNCTION
        #define PRIVILEGED_DATA
    #endif

    ଶୂନ୍ୟ vApplicationSleep( TickType_t xExpectedIdleTime );

    #define portSUPPRESS_TICKS_AND_SLEEP( idleTime )    vApplicationSleep( idleTime )

    ଶୂନ୍ୟ _xt_coproc_release( ଅସ୍ଥିର ଶୂନ୍ୟ * coproc_sa_base );

/*-----------------------------------------------------------*/

    #ଯଦି ( ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
        /* Architecture specific optimisations. */

        #ଯଦି configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
            #ଯଦି ( configMAX_PRIORITIES > 32 )
                #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 different priorities as tasks that share a priority will time slice.
            #endif

/* Store/clear the ready priorities in a bit map. */
            #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
            #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

            #define portGET_HIGHEST_PRIORITY( ux_ଶୀର୍ଷ_Priority, uxReadyPriorities )    ux_ଶୀର୍ଷ_Priority = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )

        #endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #endif /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

/*-----------------------------------------------------------*/

/*
 * Map to the memory management routines required for the port.
 *
 * Note that libc standard malloc/free are also available for
 * non-FreeRTOS-specific code, and behave the same as
 * pvPortMalloc()/vPortFree().
 */
    #define pvPortMalloc                       heap_caps_malloc_default
    #define vPortFree                          heap_caps_free
    #define xPortGetFreeHeapSize               esp_get_free_heap_size
    #define xPortGetMinimumEverFreeHeapSize    esp_get_minimum_free_heap_size

    #ଯଦି ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )

/*
 * Send an interrupt to another core in order to make the task running
 * on it yield for a higher-priority task.
 */

        ଶୂନ୍ୟ vPortYieldOtherCore( BaseType_t coreid ) PRIVILEGED_FUNCTION;

    #endif /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

/*
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack
 * watchpoint around.
 */
    ଶୂନ୍ୟ v_Port_Set_ଗଦା_Watchpoint( ଶୂନ୍ୟ * px_ଗଦା_Start );

/*
 * Returns true if the current core is in ISR context; low prio ISR, med prio ISR or timer tick ISR. High prio ISRs
 * aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 */
    BaseType_t xPortInIsrContext();


/*
 * This function will be called in High prio ISRs. Returns true if the current core was in ISR context
 * before calling into high prio ISR context.
 */
    BaseType_t xPortInterruptedFromISRContext();

/*
 * The structures and methods of manipulating the MPU are contained within the
 * port layer.
 *
 * Fills the xMPUSettings structure with the memory region information
 * contained in xRegions.
 */
    #ଯଦି ( portUSING_MPU_WRAPPERS == 1 )
        ସଂରଚନା xMEMORY_REGION;
        ଶୂନ୍ୟ vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                        ଅଚଳ ସଂରଚନା xMEMORY_REGION * ଅଚଳ xRegions,
                                        ଗଦା_Type_t * px_Bottom_Of_ଗଦା,
                                        config_ଗଦା_DEPTH_TYPE ux_ଗଦା_Depth ) PRIVILEGED_FUNCTION;
        ଶୂନ୍ୟ vPortReleaseTaskMPUSettings( xMPU_SETTINGS * xMPUSettings );
    #endif

/* Multi-core: get current core ID */
    ସ୍ଥିର ଧାଡ଼ିଭିତରେ BaseType_t IRAM_ATTR xPortGetCoreID()
    {
        ଫେରନ୍ତୁ ( uint32_t ) cpu_hal_get_core_id();
    }

/* Get tick rate per second */
    uint32_t xPortGetTickRateHz( ଶୂନ୍ୟ );

    ସ୍ଥିର ଧାଡ଼ିଭିତରେ bool IRAM_ATTR xPortCanYield( ଶୂନ୍ୟ )
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

        ଫେରନ୍ତୁ( ( ps_reg & PS_INTLEVEL_MASK ) == 0 );
    }

/* porttrace */
    #ଯଦି configUSE_TRACE_FACILITY_2
        #ଅନ୍ତର୍ଭାଵ "porttrace.h"
    #endif

/* configASSERT_2 if requested */
    #ଯଦି configASSERT_2
        #ଅନ୍ତର୍ଭାଵ <stdio.h>
        ଶୂନ୍ୟ exit( ପୂର୍ଣ୍ଣସଂଖ୍ୟା );
        #define configASSERT( x )    ଯଦି( !( x ) ) { porttracePrint( -1 ); printf( "\nAssertion failed in %s:%d\n", __FILE__, __LINE__ ); exit( -1 ); }
    #endif

/* Barriers */
    #define portMEMORY_BARRIER()    __asm ଅସ୍ଥିର ( "" ::: "memory" )


#endif // __ASSEMBLER__

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
