/*
 * SPDX-FileCopyrightText: 2017-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* This header exists for performance reasons, in order to inline the
 * implementation of vPortCPUAcquireMutexIntsDisabled and
 * vPortCPUReleaseMutexIntsDisabled into the
 * vTaskEnterCritical/vTaskExitCritical functions in task.c as well as the
 * vPortCPUAcquireMutex/vPortCPUReleaseMutex implementations.
 *
 * Normally this kind of performance hack is over the top, but
 * vTaskEnterCritical/vTaskExitCritical is called a great
 * deal by FreeRTOS internals.
 *
 * It should be #included by freertos port.c or tasks.c, in esp-idf.
 *
 * The way it works is that it essentially uses portmux_impl.inc.h as a
 * generator template of sorts. When no external memory is used, this
 * template is only used to generate the vPortCPUAcquireMutexIntsDisabledInternal
 * and vPortCPUReleaseMutexIntsDisabledInternal functions, which use S32C1 to
 * do an atomic compare & swap. When external memory is used the functions
 * vPortCPUAcquireMutexIntsDisabledExtram and vPortCPUReleaseMutexIntsDisabledExtram
 * are also generated, which use uxPortCompareSetExtram to fake the S32C1 instruction.
 * The wrapper functions vPortCPUAcquireMutexIntsDisabled and
 * vPortCPUReleaseMutexIntsDisabled will then use the appropriate function to do the
 * actual lock/unlock.
 */
#ضمن "soc/cpu.h"
#ضمن "portable.h"

/* XOR one core ID with this value to get the other core ID */
#إذا ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
    #define CORE_ID_XOR_SWAP           ( CORE_ID_PRO ^ CORE_ID_APP )
#وإلا
    #define CORE_ID_REGVAL_XOR_SWAP    ( CORE_ID_REGVAL_PRO ^ CORE_ID_REGVAL_APP )
#endif



/*Define the mux routines for use with muxes in internal RAM */
#define PORTMUX_AQUIRE_MUX_FN_NAME     vPortCPUAcquireMutexIntsDisabledInternal
#define PORTMUX_RELEASE_MUX_FN_NAME    vPortCPUReleaseMutexIntsDisabledInternal
#define PORTMUX_COMPARE_SET_FN_NAME    uxPortCompareSet
#ضمن "portmux_impl.inc.h"
#undef PORTMUX_AQUIRE_MUX_FN_NAME
#undef PORTMUX_RELEASE_MUX_FN_NAME
#undef PORTMUX_COMPARE_SET_FN_NAME


#إذا defined( CONFIG_SPIRAM_SUPPORT )

    #define PORTMUX_AQUIRE_MUX_FN_NAME     vPortCPUAcquireMutexIntsDisabledExtram
    #define PORTMUX_RELEASE_MUX_FN_NAME    vPortCPUReleaseMutexIntsDisabledExtram
    #define PORTMUX_COMPARE_SET_FN_NAME    uxPortCompareSetExtram
    #ضمن "portmux_impl.inc.h"
    #undef PORTMUX_AQUIRE_MUX_FN_NAME
    #undef PORTMUX_RELEASE_MUX_FN_NAME
    #undef PORTMUX_COMPARE_SET_FN_NAME

#endif


#ifdef CONFIG_FREERTOS_PORTMUX_DEBUG
    #define PORTMUX_AQUIRE_MUX_FN_ARGS     portMUX_TYPE * mux, صحيح timeout_cycles, ثابت حرف * fnName, صحيح سطر
    #define PORTMUX_RELEASE_MUX_FN_ARGS    portMUX_TYPE * mux, ثابت حرف * fnName, صحيح سطر
    #define PORTMUX_AQUIRE_MUX_FN_CALL_ARGS( x )     x, timeout_cycles, fnName, سطر
    #define PORTMUX_RELEASE_MUX_FN_CALL_ARGS( x )    x, fnName, سطر
#وإلا
    #define PORTMUX_AQUIRE_MUX_FN_ARGS     portMUX_TYPE * mux, صحيح timeout_cycles
    #define PORTMUX_RELEASE_MUX_FN_ARGS    portMUX_TYPE * mux
    #define PORTMUX_AQUIRE_MUX_FN_CALL_ARGS( x )     x, timeout_cycles
    #define PORTMUX_RELEASE_MUX_FN_CALL_ARGS( x )    x
#endif


ساكن مضمن bool __attribute__( ( always_inline ) ) vPortCPUAcquireMutexIntsDisabled( PORTMUX_AQUIRE_MUX_FN_ARGS )
{
    #إذا defined( CONFIG_SPIRAM_SUPPORT )
        إذا( esp_ptr_external_ram( mux ) )
        {
            أرجع vPortCPUAcquireMutexIntsDisabledExtram( PORTMUX_AQUIRE_MUX_FN_CALL_ARGS( mux ) );
        }
    #endif
    أرجع vPortCPUAcquireMutexIntsDisabledInternal( PORTMUX_AQUIRE_MUX_FN_CALL_ARGS( mux ) );
}


ساكن مضمن فراغ vPortCPUReleaseMutexIntsDisabled( PORTMUX_RELEASE_MUX_FN_ARGS )
{
    #إذا defined( CONFIG_SPIRAM_SUPPORT )
        إذا( esp_ptr_external_ram( mux ) )
        {
            vPortCPUReleaseMutexIntsDisabledExtram( PORTMUX_RELEASE_MUX_FN_CALL_ARGS( mux ) );
            أرجع;
        }
    #endif
    vPortCPUReleaseMutexIntsDisabledInternal( PORTMUX_RELEASE_MUX_FN_CALL_ARGS( mux ) );
}
