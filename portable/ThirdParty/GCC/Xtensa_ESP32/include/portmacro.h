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

#अगर_अघोषित PORTMACRO_H
#घोषणा PORTMACRO_H

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    बाह्य "C" {
#पूर्ण_अगर
/* *INDENT-ON* */

#अगर_अघोषित __ASSEMBLER__

    #समावेश <stdint.h>

    #समावेश <xtensa/hal.h>
    #समावेश <xtensa/config/core.h>
    #समावेश <xtensa/config/system.h> /* required for XSHAL_CLIB */
    #समावेश <xtensa/xtruntime.h>
    #समावेश "soc/spinlock.h"
    #समावेश "esp_timer.h" /* required for FreeRTOS run time stats */
    #समावेश "esp_system.h"
    #समावेश "esp_idf_version.h"
    #समावेश "esp_heap_caps.h"

/* TODO: Resolve build warnings generated due to this header inclusion */
    #समावेश "hal/cpu_hal.h"

/* TODO: These includes are not directly used in this file. They are kept into to prevent a breaking change. Remove these. */
    #समावेश <limits.h>
    #समावेश <xtensa/xtensa_api.h>

    #समावेश "soc/cpu.h"
    #समावेश "soc/soc_memory_layout.h"
    #अगर ( ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
        #समावेश "soc/compare_set.h"
    #पूर्ण_अगर /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

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

    #घोषणा portCHAR          int8_t
    #घोषणा portFLOAT         भग्न
    #घोषणा portDOUBLE        द्विगुन
    #घोषणा portLONG          int32_t
    #घोषणा portSHORT         int16_t
    #घोषणा port_ढेर_TYPE    uint8_t
    #घोषणा portBASE_TYPE     पूर्णांक

    प्रकार port_ढेर_TYPE           ढेर_Type_t;
    प्रकार portBASE_TYPE            BaseType_t;
    प्रकार अचिन्हित portBASE_TYPE   UBaseType_t;

    #अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_16_BITS )
        प्रकार uint16_t             TickType_t;
        #घोषणा portMAX_DELAY    ( TickType_t ) 0xffff
    #या_अगर ( configTICK_TYPE_WIDTH_IN_BITS == TICK_TYPE_WIDTH_32_BITS )
        प्रकार uint32_t             TickType_t;
        #घोषणा portMAX_DELAY    ( TickType_t ) 0xffffffffUL
    #अन्यथा
        #त्रुटि configTICK_TYPE_WIDTH_IN_BITS set to unsupported tick type width.
    #पूर्ण_अगर
/*-----------------------------------------------------------*/

/* portbenchmark */
    #समावेश "portbenchmark.h"

    #समावेश "sdkconfig.h"
    #समावेश "esp_attr.h"

/* "mux" data structure (spinlock) */
    प्रकार spinlock_t portMUX_TYPE;                                /**< Spinlock type used by FreeRTOS critical sections */
    #घोषणा portMUX_INITIALIZER_UNLOCKED    SPINLOCK_INITIALIZER    /**< Spinlock initializer */
    #घोषणा portMUX_FREE_VAL                SPINLOCK_FREE           /**< Spinlock is free. [refactor-todo] check if this is still required */
    #घोषणा portMUX_NO_TIMEOUT              SPINLOCK_WAIT_FOREVER   /**< When passed for 'timeout_cycles', spin forever if necessary. [refactor-todo] check if this is still required */
    #घोषणा portMUX_TRY_LOCK                SPINLOCK_NO_WAIT        /**< Try to acquire the spinlock a single time only. [refactor-todo] check if this is still required */
    #घोषणा portMUX_INITIALIZE( mux )    spinlock_initialize( mux ) /*< Initialize a spinlock to its unlocked state */

    #घोषणा portCRITICAL_NESTING_IN_TCB     1

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
    व्योम vPortCPUInitializeMutex( portMUX_TYPE * mux );
    #अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
        #त्रुटि CONFIG_FREERTOS_PORTMUX_DEBUG not supported in Amazon FreeRTOS
    #पूर्ण_अगर

    व्योम vTaskExitCritical();
    व्योम vTaskEnterCritical();
    अटल अंतरभूत व्योम vPortConsumeSpinlockArg( पूर्णांक unused,
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
                                      पूर्णांक timeout_cycles );
    व्योम vPortCPUReleaseMutex( portMUX_TYPE * mux );

    #घोषणा portENTER_CRITICAL( ... )        करो { vTaskEnterCritical(); vPortConsumeSpinlockArg( 0, ## __VA_ARGS__ ); } जबतक( 0 )
    #घोषणा portEXIT_CRITICAL( ... )         करो { vTaskExitCritical(); vPortConsumeSpinlockArg( 0, ## __VA_ARGS__ ); } जबतक( 0 )


    #घोषणा portENTER_CRITICAL_ISR( mux )    vPortCPUAcquireMutexTimeout( mux, portMUX_NO_TIMEOUT )
    #घोषणा portEXIT_CRITICAL_ISR( mux )     vPortCPUReleaseMutex( mux )

    #घोषणा portENTER_CRITICAL_SAFE( mux ) \
    करो {                                   \
        अगर( xPortInIsrContext() ) {        \
            portENTER_CRITICAL_ISR( mux ); \
        }                                  \
        अन्यथा {                             \
            portENTER_CRITICAL( mux );     \
        }                                  \
    } जबतक( 0 )

    #घोषणा portEXIT_CRITICAL_SAFE( mux ) \
    करो {                                  \
        अगर( xPortInIsrContext() ) {       \
            portEXIT_CRITICAL_ISR( mux ); \
        }                                 \
        अन्यथा {                            \
            portEXIT_CRITICAL( mux );     \
        }                                 \
    } जबतक( 0 )

    #घोषणा portASSERT_IF_IN_ISR()    vPortAssertIfInISR()
    व्योम vPortAssertIfInISR( व्योम );

/* Critical section management. NW-TODO: replace XTOS_SET_INTLEVEL with more efficient version, if any? */
/* These cannot be nested. They should be used with a lot of care and cannot be called from interrupt level. */
/* */
/* Only applies to one CPU. See notes above & below for reasons not to use these. */
    #घोषणा portDISABLE_INTERRUPTS()    करो { XTOS_SET_INTLEVEL( XCHAL_EXCM_LEVEL ); portbenchmarkINTERRUPT_DISABLE(); } जबतक( 0 )
    #घोषणा portENABLE_INTERRUPTS()     करो { portbenchmarkINTERRUPT_RESTORE( 0 ); XTOS_SET_INTLEVEL( 0 ); } जबतक( 0 )

/* Cleaner solution allows nested interrupts disabling and restoring via local registers or stack. */
/* They can be called from interrupts too. */
/* WARNING: Only applies to current CPU. See notes above. */
    अटल अंतरभूत UBaseType_t __attribute__( ( always_inline ) ) xPortSetInterruptMaskFromISR( व्योम )
    {
        UBaseType_t पूर्व_int_level = XTOS_SET_INTLEVEL( XCHAL_EXCM_LEVEL );

        portbenchmarkINTERRUPT_DISABLE();
        वापस पूर्व_int_level;
    }

    अटल अंतरभूत व्योम __attribute__( ( always_inline ) ) vPortClearInterruptMaskFromISR( UBaseType_t पूर्व_level )
    {
        portbenchmarkINTERRUPT_RESTORE( पूर्व_level );
        XTOS_RESTORE_JUST_INTLEVEL( पूर्व_level );
    }

/* These FreeRTOS versions are similar to the nested versions above */
    #घोषणा portSET_INTERRUPT_MASK_FROM_ISR()                  xPortSetInterruptMaskFromISR()
    #घोषणा portCLEAR_INTERRUPT_MASK_FROM_ISR( पूर्व_level )    vPortClearInterruptMaskFromISR( पूर्व_level )

/*Because the ROM routines don't necessarily handle a stack in external RAM correctly, we force */
/*the stack memory to always be internal. */
    #घोषणा portTcbMemoryCaps      ( MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT )
    #घोषणा port_ढेर_Memory_Caps    ( MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT )

    #घोषणा pvPortMallocTcbMem( आकार )        heap_caps_malloc( आकार, portTcbMemoryCaps )
    #घोषणा pv_Port_Malloc_ढेर_Mem( आकार )      heap_caps_malloc( आकार, port_ढेर_Memory_Caps )

/*xTaskCreateStatic uses these functions to check incoming memory. */
    #घोषणा portVALID_TCB_MEM( ptr )          ( esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #अगर_घोषित CONFIG_SPIRAM_ALLOW_ढेर_EXTERNAL_MEMORY
        #घोषणा port_VALID_ढेर_MEM( ptr )    esp_ptr_byte_accessible( ptr )
    #अन्यथा
        #घोषणा port_VALID_ढेर_MEM( ptr )    ( esp_ptr_internal( ptr ) && esp_ptr_byte_accessible( ptr ) )
    #पूर्ण_अगर

/*
 * Wrapper for the Xtensa compare-and-set instruction. This subroutine will atomically compare
 * *addr to 'compare'. If *addr == compare, *addr is set to *set. *set is updated with the previous
 * value of *addr (either 'compare' or some other value.)
 *
 * Warning: From the ISA docs: in some (unspecified) cases, the s32c1i instruction may return the
 * *bitwise inverse* of the old mem if the mem wasn't written. This doesn't seem to happen on the
 * ESP32 (portMUX assertions would fail).
 */
    अटल अंतरभूत व्योम uxPortCompareSet( अस्थिर uint32_t * addr,
                                         uint32_t compare,
                                         uint32_t * set )
    {
        #अगर ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
            __asm__ __volatile__ (
                "WSR       %2,SCOMPARE1 \n"
                "S32C1I     %0, %1, 0   \n"
                : "=r" ( *set )
                : "r" ( addr ), "r" ( compare ), "0" ( *set )
                );
        #अन्यथा
            #अगर ( XCHAL_HAVE_S32C1I > 0 )
                __asm__ __volatile__ (
                    "WSR        %2,SCOMPARE1 \n"
                    "S32C1I     %0, %1, 0    \n"
                    : "=r" ( *set )
                    : "r" ( addr ), "r" ( compare ), "0" ( *set )
                    );
            #अन्यथा
                /* No S32C1I, so do this by disabling and re-enabling interrupts (slower) */
                uint32_t intlevel, old_मूल्य;
                __asm__ __volatile__ ( "rsil %0, " XTSTR( XCHAL_EXCM_LEVEL ) "\n"
                                       : "=r" ( intlevel ) );

                old_मूल्य = *addr;

                अगर( old_मूल्य == compare )
                {
                    *addr = *set;
                }

                __asm__ __volatile__ ( "memw \n"
                                       "wsr %0, ps\n"
                                       : : "r" ( intlevel ) );

                *set = old_मूल्य;
            #पूर्ण_अगर /* if ( XCHAL_HAVE_S32C1I > 0 ) */
        #पूर्ण_अगर /* #if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0)) */
    }

    #अगर ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
        व्योम uxPortCompareSetExtram( अस्थिर uint32_t * addr,
                                     uint32_t compare,
                                     uint32_t * set );
    #अन्यथा
        अटल अंतरभूत व्योम uxPortCompareSetExtram( अस्थिर uint32_t * addr,
                                                   uint32_t compare,
                                                   uint32_t * set )
        {
            #अगर defined( CONFIG_SPIRAM )
                compare_and_set_extram( addr, compare, set );
            #पूर्ण_अगर
        }
    #पूर्ण_अगर /* if ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) ) */

/*-----------------------------------------------------------*/

/* Architecture specifics. */
    #घोषणा port_ढेर_GROWTH      ( -1 )
    #घोषणा portTICK_PERIOD_MS    ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
    #घोषणा portBYTE_ALIGNMENT    4
    #घोषणा portNOP()    XT_NOP()
/*-----------------------------------------------------------*/

/* Fine resolution time */
    #घोषणा port_GET_RUN_TIME_गणक_मूल्य()    xthal_get_ccount()
/*ccount or esp_timer are initialized elsewhere */
    #घोषणा portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()

    #अगर_घोषित CONFIG_FREERTOS_RUN_TIME_STATS_USING_ESP_TIMER
/* Coarse resolution time (us) */
        #घोषणा port_ALT_GET_RUN_TIME_गणक_मूल्य( x )    करो { x = ( uint32_t ) esp_timer_get_time(); } जबतक( 0 )
    #पूर्ण_अगर



/* Kernel utilities. */
    व्योम vPortYield( व्योम );
    व्योम vPortEvaluateYieldFromISR( पूर्णांक argc,
                                    ... );
    व्योम _frxt_setup_switch( व्योम );

/* Macro to count number of arguments of a __VA_ARGS__ used to support portYIELD_FROM_ISR with,
 * or without arguments. The macro counts only 0 or 1 arguments.
 *
 * In the future, we want to switch to C++20. We also want to become compatible with clang.
 * Hence, we provide two versions of the following macros which are using variadic arguments.
 * The first one is using the GNU extension ##__VA_ARGS__. The second one is using the C++20 feature __VA_OPT__(,).
 * This allows users to compile their code with standard C++20 enabled instead of the GNU extension.
 * Below C++20, we haven't found any good alternative to using ##__VA_ARGS__.
 */
    #अगर defined( __cplusplus ) && ( __cplusplus > 201703L )
        #घोषणा port_GET_ARGUMENT_गिनती( ... )                        port_GET_ARGUMENT_गिनती_INNER( 0 __VA_OPT__(, ) __VA_ARGS__, 1, 0 )
    #अन्यथा
        #घोषणा port_GET_ARGUMENT_गिनती( ... )                        port_GET_ARGUMENT_गिनती_INNER( 0, ## __VA_ARGS__, 1, 0 )
    #पूर्ण_अगर
    #घोषणा port_GET_ARGUMENT_गिनती_INNER( zero, one, गिनती, ... )    गिनती

    _Static_assert( port_GET_ARGUMENT_गिनती() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments" );
    _Static_assert( port_GET_ARGUMENT_गिनती( 1 ) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument" );

    #घोषणा portYIELD()    vPortYield()

/* The macro below could be used when passing a single argument, or without any argument,
 * it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 * might result in undesired behaviour
 */
    #अगर defined( __cplusplus ) && ( __cplusplus > 201703L )
        #घोषणा portYIELD_FROM_ISR( ... )    vPortEvaluateYieldFromISR( port_GET_ARGUMENT_गिनती( __VA_ARGS__ ) __VA_OPT__(, ) __VA_ARGS__ )
    #अन्यथा
        #घोषणा portYIELD_FROM_ISR( ... )    vPortEvaluateYieldFromISR( port_GET_ARGUMENT_गिनती( __VA_ARGS__ ), ## __VA_ARGS__ )
    #पूर्ण_अगर

    अटल अंतरभूत BaseType_t xPortGetCoreID();

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
    #घोषणा portTASK_FUNCTION_PROTO( vFunction, pvParameters )    व्योम vFunction( व्योम * pvParameters )
    #घोषणा portTASK_FUNCTION( vFunction, pvParameters )          व्योम vFunction( व्योम * pvParameters )

/* When coprocessors are defined, we to maintain a pointer to coprocessors area. */
/* We currently use a hack: redefine field xMPU_SETTINGS in TCB block as a structure that can hold: */
/* MPU wrappers, coprocessor area pointer, trace code structure, and more if needed. */
/* The field is normally used for memory protection. FreeRTOS should create another general purpose field. */
    प्रकार काष्ठा
    {
        #अगर XCHAL_CP_अंक > 0
            अस्थिर ढेर_Type_t * coproc_area; /* Pointer to coprocessor save area; MUST BE FIRST */
        #पूर्ण_अगर

        #अगर portUSING_MPU_WRAPPERS
            /* Define here mpu_settings, which is port dependent */
            पूर्णांक mpu_setting; /* Just a dummy example here; MPU not ported to Xtensa yet */
        #पूर्ण_अगर

        #अगर configUSE_TRACE_FACILITY_2
            काष्ठा
            {
                /* Cf. porttraceStamp() */
                पूर्णांक taskstamp;      /* Stamp from inside task to see where we are */
                पूर्णांक taskstampcount; /* A counter usually incremented when we restart the task's loop */
            } porttrace;
        #पूर्ण_अगर
    } xMPU_SETTINGS;

/* Main hack to use MPU_wrappers even when no MPU is defined (warning: mpu_setting should not be accessed; otherwise move this above xMPU_SETTINGS) */
    #अगर ( XCHAL_CP_अंक > 0 || configUSE_TRACE_FACILITY_2 ) && !portUSING_MPU_WRAPPERS /* If MPU wrappers not used, we still need to allocate coproc area */
        #अघोषित portUSING_MPU_WRAPPERS
        #घोषणा portUSING_MPU_WRAPPERS    1                                           /* Enable it to allocate coproc area */
        #घोषणा MPU_WRAPPERS_H                                                        /* Override mpu_wrapper.h to disable unwanted code */
        #घोषणा PRIVILEGED_FUNCTION
        #घोषणा PRIVILEGED_तथ्य
    #पूर्ण_अगर

    व्योम vApplicationSleep( TickType_t xExpectedIdleTime );

    #घोषणा portSUPPRESS_TICKS_AND_SLEEP( idleTime )    vApplicationSleep( idleTime )

    व्योम _xt_coproc_release( अस्थिर व्योम * coproc_sa_base );

/*-----------------------------------------------------------*/

    #अगर ( ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
        /* Architecture specific optimisations. */

        #अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

/* Check the configuration. */
            #अगर ( configMAX_PRIORITIES > 32 )
                #त्रुटि configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 different priorities as tasks that share a priority will समय slice.
            #पूर्ण_अगर

/* Store/clear the ready priorities in a bit map. */
            #घोषणा portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities )    ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
            #घोषणा portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities )     ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

/*-----------------------------------------------------------*/

            #घोषणा portGET_HIGHEST_PRIORITY( ux_शीर्ष_Priority, uxReadyPriorities )    ux_शीर्ष_Priority = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )

        #पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

    #पूर्ण_अगर /* ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 2, 0) */

/*-----------------------------------------------------------*/

/*
 * Map to the memory management routines required for the port.
 *
 * Note that libc standard malloc/free are also available for
 * non-FreeRTOS-specific code, and behave the same as
 * pvPortMalloc()/vPortFree().
 */
    #घोषणा pvPortMalloc                       heap_caps_malloc_default
    #घोषणा vPortFree                          heap_caps_free
    #घोषणा x_Port_Get_Free_Heap_आकार               esp_get_free_heap_आकार
    #घोषणा x_Port_Get_Minimum_Ever_Free_Heap_आकार    esp_get_minimum_free_heap_आकार

    #अगर ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )

/*
 * Send an interrupt to another core in order to make the task running
 * on it yield for a higher-priority task.
 */

        व्योम vPortYieldOtherCore( BaseType_t coreid ) PRIVILEGED_FUNCTION;

    #पूर्ण_अगर /* ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 2, 0) */

/*
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack
 * watchpoint around.
 */
    व्योम v_Port_Set_ढेर_Watchpoint( व्योम * px_ढेर_Start );

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
    #अगर ( portUSING_MPU_WRAPPERS == 1 )
        काष्ठा xMEMORY_REGION;
        व्योम vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
                                        स्थिर काष्ठा xMEMORY_REGION * स्थिर xRegions,
                                        ढेर_Type_t * px_Bottom_Of_ढेर,
                                        config_ढेर_DEPTH_TYPE ux_ढेर_Depth ) PRIVILEGED_FUNCTION;
        व्योम vPortReleaseTaskMPUSettings( xMPU_SETTINGS * xMPUSettings );
    #पूर्ण_अगर

/* Multi-core: get current core ID */
    अटल अंतरभूत BaseType_t IRAM_ATTR xPortGetCoreID()
    {
        वापस ( uint32_t ) cpu_hal_get_core_id();
    }

/* Get tick rate per second */
    uint32_t xPortGetTickRateHz( व्योम );

    अटल अंतरभूत bool IRAM_ATTR xPortCanYield( व्योम )
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

        वापस( ( ps_reg & PS_INTLEVEL_MASK ) == 0 );
    }

/* porttrace */
    #अगर configUSE_TRACE_FACILITY_2
        #समावेश "porttrace.h"
    #पूर्ण_अगर

/* configASSERT_2 if requested */
    #अगर configASSERT_2
        #समावेश <stdio.h>
        व्योम निकास( पूर्णांक );
        #घोषणा configASSERT( x )    अगर( !( x ) ) { porttracePrint( -1 ); म_लिखो( "\nAssertion failed in %s:%d\n", __खाता__, __LINE__ ); निकास( -1 ); }
    #पूर्ण_अगर

/* Barriers */
    #घोषणा portMEMORY_BARRIER()    __asm अस्थिर ( "" ::: "memory" )


#पूर्ण_अगर // __ASSEMBLER__

/* *INDENT-OFF* */
#अगर_घोषित __cplusplus
    }
#पूर्ण_अगर
/* *INDENT-ON* */

#पूर्ण_अगर /* PORTMACRO_H */
