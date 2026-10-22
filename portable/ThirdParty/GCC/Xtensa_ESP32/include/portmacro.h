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
    बाह्य "C" {
#endif
/* *INDENT-ON* */

#ifndef __ASSEMBLER__

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
    #यदि ( ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
        #अन्तर्भाव "soc/compare_set.h"
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
    #define portFLOAT         भिन्न
    #define portDOUBLE        द्विगुण
    #define portLONG          int32_t
    #define portSHORT         int16_t
    #define port_थाक_TYPE    uint8_t
    #define portBASE_TYPE     पूर्णाङ्क

    प्रकारनिर्देश port_थाक_TYPE           थाक_Type_t;
    प्रकारनिर्देश portBASE_TYPE            BaseType_t;
    प्रकारनिर्देश अचिन्हित portBASE_TYPE   UBaseType_t;

    #यदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        प्रकारनिर्देश uint16_t             TickType_t;
        #define portMAX_DELAY    ( TickType_t ) 0xffff
    #अथवायदि ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
        प्रकारनिर्देश uint32_t             TickType_t;
        #define portMAX_DELAY    ( TickType_t ) 0xffffffffUL
    #अन्यथा
        #error configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
    #endif
/*-----------------------------------------------------------*/

/* portbenchmark */
    #अन्तर्भाव "portbenchmark.h"

    #अन्तर्भाव "sdkconfig.h"
    #अन्तर्भाव "esp_attr.h"

/* "mux" data structure (spinlock) */
    प्रकारनिर्देश spinlock_t portMUX_TYPE;                                /**< Spinlock type used by FreeRTOS critical sections */
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
    शून्य vPortCPUInitializeMutex( portMUX_TYPE * mux );
    #ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
        #error CONFIG_FREERTOS_PORTMUX_DEBUG not supported in Amazon FreeRTOS
    #endif

    शून्य vTaskExitCritical();
    शून्य vTaskEnterCritical();
    स्थिर अन्तःस्थ शून्य vPortConsumeSpinlockArg( पूर्णाङ्क unused,
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
                                      पूर्णाङ्क timeout_cycles );
    शून्य vPortCPUReleaseMutex( portMUX_TYPE * mux );

    #define portENTER_CRITICAL( ... )        गर { vTaskEnterCritical(); vPortConsumeSpinlockArg( 0, ## __VA_ARGS__ ); } जबसम्म( 0 )
    #define portEXIT_CRITICAL( ... )         गर { vTaskExitCritical(); vPortConsumeSpinlockArg( 0, ## __VA_ARGS__ ); } जबसम्म( 0 )


    #define portENTER_CRITICAL_ISR( mux )    vPortCPUAcquireMutexTimeout( mux, portMUX_NO_TIMEOUT )
    #define portEXIT_CRITICAL_ISR( mux )     vPortCPUReleaseMutex( mux )

    #define portENTER_CRITICAL_SAFE( mux ) \
    गर {                                   \
        यदि( xPortInIsrContext() ) {        \
            portENTER_CRITICAL_ISR( mux ); \
        }                                  \
        अन्यथा {                             \
            portENTER_CRITICAL( mux );     \
        }                                  \
    } जबसम्म( 0 )

    #define portEXIT_CRITICAL_SAFE( mux ) \
    गर {                                  \
        यदि( xPortInIsrContext() ) {       \
            portEXIT_CRITICAL_ISR( mux ); \
        }                                 \
        अन्यथा {                            \
            portEXIT_CRITICAL( mux );     \
        }                                 \
    } जबसम्म( 0 )

    #define portASSERT_IF_IN_ISR()    vPortAssertIfInISR()
    शून्य vPortAssertIfInISR( शून्य );

/* Critical section management. NW-TODO: replace XTOS_SET_INTLEVEL with more efficient version, if any? */
/* These cannot be nested. They should be used with a lot of care and cannot be called from interrupt level. */
/* */
/* Only applies to one CPU. See notes above & below for reasons not to use these. */
    #define portDISABLE_INTERRUPTS()    गर { XTOS_SET_INTLEVEL( XCHAL_EXCM_LEVEL ); portbenchmarkINTERRUPT_DISABLE(); } जबसम्म( 0 )
    #define portENABLE_INTERRUPTS()     गर { portbenchmarkINTERRUPT_RESTORE( 0 ); XTOS_SET_INTLEVEL( 0 ); } जबसम्म( 0 )

/* Cleaner solution allows nested interrupts disabling and restoring via local registers or stack. */
/* They can be called from interrupts too. */
/* WARNING: Only applies to current CPU. See notes above. */
    स्थिर अन्तःस्थ UBaseType_t __attribute__( ( always_inline ) ) xPortSetInterruptMaskFromISR( शून्य )
    {
        UBaseType_t prev_int_level = XTOS_SET_INTLEVEL( XCHAL_EXCM_LEVEL );

        portbenchmarkINTERRUPT_DISABLE();
        फर्काऊ prev_int_level;
    }

    स्थिर अन्तःस्थ शून्य __attribute__( ( always_inline ) ) vPortClearInterruptMaskFromISR( UBaseType_t prev_level )
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
    #define port_थाक_Memory_Caps    ( MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT )

    #define pvPortMallocTcbMem( size )        heap_caps_malloc( size, portTcbMemoryCaps )
    #define pv_Port_Malloc_थाक_Mem( size )      heap_caps_malloc( size, port_थाक_Memory_Caps )

/*xTaskCreateStatic uses these functions to check incoming memory. */
    #define portVALID_TCB_MEM( ptr )          ( esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #ifdef CONFIG_SPIRAM_ALLOW_थाक_EXTERNAL_MEMORY
        #define port_VALID_थाक_MEM( ptr )    esp_ptr_byte_accessible( ptr )
    #अन्यथा
        #define port_VALID_थाक_MEM( ptr )    ( esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr ) )
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
    स्थिर अन्तःस्थ शून्य uxPortCompareSet( चञ्चल uint32_t * addr,
                                         uint32_t compare,
                                         uint32_t * set )
    {
        #यदि ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
            __asm__ __volatile__ (
                "WSR       %2,SCOMPARE1 \n"
                "S32C1I     %0, %1, 0   \n"
                : "=r" ( *set )
                : "r" ( addr ), "r" ( compare ), "0" ( *set )
                );
        #अन्यथा
            #यदि ( XCHAL_HAVE_S32C1I > 0 )
                __asm__ __volatile__ (
                    "WSR        %2,SCOMPARE1 \n"
                    "S32C1I     %0, %1, 0    \n"
                    : "=r" ( *set )
                    : "r" ( addr ), "r" ( compare ), "0" ( *set )
                    );
            #अन्यथा
                /* No S32C1I, so do this by disabling and re-enabling interrupts (slower) */
                uint32_t intlevel, old_मान;
                __asm__ __volatile__ ( "rsil %0, " XTSTR( XCHAL_EXCM_LEVEL ) "\n"
                                       : "=r" ( intlevel ) );

                old_मान = *addr;

                यदि( old_मान == compare )
                {
                    *addr = *set;
                }

                __asm__ __volatile__ ( "memw \n"
                                       "wsr %0, ps\n"
                                       : : "r" ( intlevel ) );

                *set = old_मान;
            #endif /* if ( XCHAL_HAVE_S32C1I > 0 ) */
        #endif /* #if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)) */
    }

    #यदि ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
        शून्य uxPortCompareSetExtram( चञ्चल uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * set );
    #अन्यथा
        स्थिर अन्तःस्थ शून्य uxPortCompareSetExtram( चञ्चल uint32_t * addr,
                                                   uint32_t compare,
                                                   uint32_t * set )
        {
            #यदि defined( CONFIG_SPIRAM )
                compare_and_set_extram( addr, compare, set );
            #endif
        }
    #endif /* if ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) ) */

/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #define port_थाक_GROWTH      ( -1 )
    #define portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
    #define portBYTE_ALIGNMENT    4
    #define portNOP()    XT_NOP()
/*-----------------------------------------------------------*/

/* Fine resolution time */
    #define port_GET_RUN_TIME_COUNTER_मान()    xthal_get_ccount()
/*ccount or esp_timer are initialized elsewhere */
    #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()

    #ifdef CONFIG_FREERTOS_RUN_TIME_STATS_USING_ESP_TIMER
/* Coarse resolution time (us) */
        #define port_ALT_GET_RUN_TIME_COUNTER_मान( x )    गर { x = ( uint32_t ) esp_timer_get_time(); } जबसम्म( 0 )
    #endif



/* Kernel utilities. */
    शून्य vPortYield( शून्य );
    शून्य vPortEvaluateYieldFromISR( पूर्णाङ्क argc,
                                    ... );
    शून्य _frxt_setup_switch( शून्य );

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
        #define port_GET_ARGUMENT_गन्ती( ... )                        port_GET_ARGUMENT_गन्ती_INNER( 0 __VA_OPT__(, ) __VA_ARGS__, 1, 0 )
    #अन्यथा
        #define port_GET_ARGUMENT_गन्ती( ... )                        port_GET_ARGUMENT_गन्ती_INNER( 0, ## __VA_ARGS__, 1, 0 )
    #endif
    #define port_GET_ARGUMENT_गन्ती_INNER( zero, one, गन्ती, ... )    गन्ती

    _Static_assert( port_GET_ARGUMENT_गन्ती() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments" );
    _Static_assert( port_GET_ARGUMENT_गन्ती( 1 ) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument" );

    #define portYIELD()    vPortYield()

/* The macro below could be used when passing a single argument, or without any argument,
 * it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 * might result in undesired behaviour
 */
    #यदि defined( __cplusplus ) && ( __cplusplus > 201703L )
        #define portYIELD_FROM_ISR( ... )    vPortEvaluateYieldFromISR( port_GET_ARGUMENT_गन्ती( __VA_ARGS__ ) __VA_OPT__(, ) __VA_ARGS__ )
    #अन्यथा
        #define portYIELD_FROM_ISR( ... )    vPortEvaluateYieldFromISR( port_GET_ARGUMENT_गन्ती( __VA_ARGS__ ), ## __VA_ARGS__ )
    #endif

    स्थिर अन्तःस्थ BaseType_t xPortGetCoreID();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #define portTASK_FUNCTION_PROTO( vFunction, pvParameters )    शून्य vFunction( शून्य * pvParameters )
    #define portTASK_FUNCTION( vFunction, pvParameters )          शून्य vFunction( शून्य * pvParameters )

/* When coprocessors are defined, we to maintain a pointer to coprocessors area. */
/* We currently use a hack: redefine field xMPU_SETTINGS in TCB block as a structure that can hold: */
/* MPU wrappers, coprocessor area pointer, trace code structure, and more if needed. */
/* The field is normally used for memory protection. FreeRTOS should create another general purpose field. */
    प्रकारनिर्देश संरचना
    {
        #यदि XCHAL_CP_अङ्क > 0
            चञ्चल थाक_Type_t * coproc_area; /* Pointer to coprocessor save area; MUST BE FIRST */
        #endif

        #यदि portUSING_MPU_WRAPPERS
            /* Define here mpu_settings, which is port dependent */
            पूर्णाङ्क mpu_setting; /* Just a dummy example here; MPU not ported to Xtensa yet */
        #endif

        #यदि configUSE_TRACE_FACILITY_2
            संरचना
            {
                /* Cf. porttraceStamp() */
                पूर्णाङ्क taskstamp;      /* Stamp from inside task to see where we are */
                पूर्णाङ्क taskstampcount; /* A counter usually incremented when we restart the task's loop */
            } porttrace;
        #endif
    } xMPU_SETTINGS;

/* Main hack to use MPU_wrappers even when no MPU is defined (warning: mpu_setting should not be accessed; otherwise move this above xMPU_SETTINGS) */
    #यदि ( XCHAL_CP_अङ्क > 0 || configUSE_TRACE_FACILITY_2 ) && !portUSING_MPU_WRAPPERS /* If MPU wrappers not used, we still need to allocate coproc area */
        #undef portUSING_MPU_WRAPPERS
        #define portUSING_MPU_WRAPPERS    1                                           /* Enable it to allocate coproc area */
        #define MPU_WRAPPERS_H                                                        /* Override mpu_wrapper.h to disable unwanted code */
        #define PRIVILEGED_FUNCTION
        #define PRIVILEGED_DATA
    #endif

    शून्य vApplicationSleep( TickType_t xExpectedIdleTime );

    #define portSUPPRESS_TICKS_AND_SLEEP( idleTime )    vApplicationSleep( idleTime )

    शून्य _xt_coproc_release( चञ्चल शून्य * coproc_sa_base );

/*-----------------------------------------------------------*/

    #यदि ( ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
        /* Architecture specific optimisations. */

        #यदि configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
            #यदि ( configMAX_PRIORITIES > 32 )
                #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 different priorities as tasks that share a priority will समय slice.
            #endif

/* Store/clear the ready priorities in a bit map. */
            #define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
            #define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

            #define portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    ux_शीर्ष_Priority = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )

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

    #यदि ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )

/*
 * Send an interrupt to another core in order to make the task running
 * on it yield for a higher-priority task.
 */

        शून्य vPortYieldOtherCore( BaseType_t coreid ) PRIVILEGED_FUNCTION;

    #endif /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

/*
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack
 * watchpoint around.
 */
    शून्य v_Port_Set_थाक_Watchpoint( शून्य * px_थाक_Start );

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
    #यदि ( portUSING_MPU_WRAPPERS == 1 )
        संरचना xMEMORY_REGION;
        शून्य vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                        अचर संरचना xMEMORY_REGION * अचर xRegions,
                                        थाक_Type_t * px_Bottom_Of_थाक,
                                        config_थाक_DEPTH_TYPE ux_थाक_Depth ) PRIVILEGED_FUNCTION;
        शून्य vPortReleaseTaskMPUSettings( xMPU_SETTINGS * xMPUSettings );
    #endif

/* Multi-core: get current core ID */
    स्थिर अन्तःस्थ BaseType_t IRAM_ATTR xPortGetCoreID()
    {
        फर्काऊ ( uint32_t ) cpu_hal_get_core_id();
    }

/* Get tick rate per second */
    uint32_t xPortGetTickRateHz( शून्य );

    स्थिर अन्तःस्थ bool IRAM_ATTR xPortCanYield( शून्य )
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

        फर्काऊ( ( ps_reg & PS_INTLEVEL_MASK ) == 0 );
    }

/* porttrace */
    #यदि configUSE_TRACE_FACILITY_2
        #अन्तर्भाव "porttrace.h"
    #endif

/* configASSERT_2 if requested */
    #यदि configASSERT_2
        #अन्तर्भाव <stdio.h>
        शून्य निकास( पूर्णाङ्क );
        #define configASSERT( x )    यदि( !( x ) ) { porttracePrint( -1 ); म_लिखो( "\nAssertion failed in %s:%d\n", __FILE__, __LINE__ ); निकास( -1 ); }
    #endif

/* Barriers */
    #define portMEMORY_BARRIER()    __asm चञ्चल ( "" ::: "memory" )


#endif // __ASSEMBLER__

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* PORTMACRO_H */
