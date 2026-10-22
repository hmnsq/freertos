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
#ਅਨ੍ਤਰ੍ਭਾਵ "soc/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "portable.h"

/* XOR one core ID with this value to get the other core ID */
#ਜੇ ( ESP_IDF_ਸੰਸਕਰਣ < ESP_IDF_ਸੰਸਕਰਣ_VAL( 4, 2, 0 ) )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CORE_ID_XOR_ਅਦਲਾ_ਬਦਲੀ           ( CORE_ID_PRO ^ CORE_ID_APP )
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CORE_ID_REGVAL_XOR_ਅਦਲਾ_ਬਦਲੀ    ( CORE_ID_REGVAL_PRO ^ CORE_ID_REGVAL_APP )
#ਜੇ_ਅੰਤ



/*Define the mux routines for use with muxes in internal RAM */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_AQUIRE_MUX_FN_NAME     v_ਪੋਰਟ_CPUAcquire_Mutex_Ints_Disabled_ਅੰਦਰੂਨੀ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_RELEASE_MUX_FN_NAME    v_ਪੋਰਟ_CPURelease_Mutex_Ints_Disabled_ਅੰਦਰੂਨੀ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_COMPARE_ਸੈੱਟ_FN_NAME    ux_ਪੋਰਟ_Compare_ਸੈੱਟ
#ਅਨ੍ਤਰ੍ਭਾਵ "portmux_impl.inc.h"
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ PORTMUX_AQUIRE_MUX_FN_NAME
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ PORTMUX_RELEASE_MUX_FN_NAME
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ PORTMUX_COMPARE_ਸੈੱਟ_FN_NAME


#ਜੇ defined( CONFIG_SPIRAM_SUPPORT )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_AQUIRE_MUX_FN_NAME     v_ਪੋਰਟ_CPUAcquire_Mutex_Ints_Disabled_Extram
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_RELEASE_MUX_FN_NAME    v_ਪੋਰਟ_CPURelease_Mutex_Ints_Disabled_Extram
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_COMPARE_ਸੈੱਟ_FN_NAME    ux_ਪੋਰਟ_Compare_ਸੈੱਟ_Extram
    #ਅਨ੍ਤਰ੍ਭਾਵ "portmux_impl.inc.h"
    #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ PORTMUX_AQUIRE_MUX_FN_NAME
    #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ PORTMUX_RELEASE_MUX_FN_NAME
    #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ PORTMUX_COMPARE_ਸੈੱਟ_FN_NAME

#ਜੇ_ਅੰਤ


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CONFIG_FREERTOS_PORTMUX_DEBUG
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_AQUIRE_MUX_FN_ਦਲੀਲਾਂ     ਪੋਰਟ_MUX_TYPE * mux, ਪੂਰਨ timeout_ਚੱਕਰਾਂ, ਅਚਲ ਅੱਖਰ * fnName, ਪੂਰਨ ਸਤਰ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_RELEASE_MUX_FN_ਦਲੀਲਾਂ    ਪੋਰਟ_MUX_TYPE * mux, ਅਚਲ ਅੱਖਰ * fnName, ਪੂਰਨ ਸਤਰ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_AQUIRE_MUX_FN_CALL_ਦਲੀਲਾਂ( x )     x, timeout_ਚੱਕਰਾਂ, fnName, ਸਤਰ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_RELEASE_MUX_FN_CALL_ਦਲੀਲਾਂ( x )    x, fnName, ਸਤਰ
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_AQUIRE_MUX_FN_ਦਲੀਲਾਂ     ਪੋਰਟ_MUX_TYPE * mux, ਪੂਰਨ timeout_ਚੱਕਰਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_RELEASE_MUX_FN_ਦਲੀਲਾਂ    ਪੋਰਟ_MUX_TYPE * mux
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_AQUIRE_MUX_FN_CALL_ਦਲੀਲਾਂ( x )     x, timeout_ਚੱਕਰਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PORTMUX_RELEASE_MUX_FN_CALL_ਦਲੀਲਾਂ( x )    x
#ਜੇ_ਅੰਤ


ਸਥਿਰ ਸਤਰਅੰਦਰ bool __attribute__( ( always_inline ) ) v_ਪੋਰਟ_CPUAcquire_Mutex_Ints_Disabled( PORTMUX_AQUIRE_MUX_FN_ਦਲੀਲਾਂ )
{
    #ਜੇ defined( CONFIG_SPIRAM_SUPPORT )
        ਜੇ( esp_ptr_external_ram( mux ) )
        {
            ਵਾਪਸ v_ਪੋਰਟ_CPUAcquire_Mutex_Ints_Disabled_Extram( PORTMUX_AQUIRE_MUX_FN_CALL_ਦਲੀਲਾਂ( mux ) );
        }
    #ਜੇ_ਅੰਤ
    ਵਾਪਸ v_ਪੋਰਟ_CPUAcquire_Mutex_Ints_Disabled_ਅੰਦਰੂਨੀ( PORTMUX_AQUIRE_MUX_FN_CALL_ਦਲੀਲਾਂ( mux ) );
}


ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ v_ਪੋਰਟ_CPURelease_Mutex_Ints_Disabled( PORTMUX_RELEASE_MUX_FN_ਦਲੀਲਾਂ )
{
    #ਜੇ defined( CONFIG_SPIRAM_SUPPORT )
        ਜੇ( esp_ptr_external_ram( mux ) )
        {
            v_ਪੋਰਟ_CPURelease_Mutex_Ints_Disabled_Extram( PORTMUX_RELEASE_MUX_FN_CALL_ਦਲੀਲਾਂ( mux ) );
            ਵਾਪਸ;
        }
    #ਜੇ_ਅੰਤ
    v_ਪੋਰਟ_CPURelease_Mutex_Ints_Disabled_ਅੰਦਰੂਨੀ( PORTMUX_RELEASE_MUX_FN_CALL_ਦਲੀਲਾਂ( mux ) );
}
