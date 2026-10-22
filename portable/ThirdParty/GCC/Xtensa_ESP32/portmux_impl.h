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
#إذا ( ESP_IDF_نسخه < ESP_IDF_نسخه_VAL( 4, 2, 0 ) )
    #تعریف_کن CORE_ID_XOR_جابجا           ( CORE_ID_PRO ^ CORE_ID_APP )
#وإلا
    #تعریف_کن CORE_ID_REGVAL_XOR_جابجا    ( CORE_ID_REGVAL_PRO ^ CORE_ID_REGVAL_APP )
#پایان_اگر



/*Define the mux routines for use with muxes in internal RAM */
#تعریف_کن PORTMUX_AQUIRE_MUX_FN_NAME     v_پورت_CPUAcquire_Mutex_Ints_Disabled_داخلی
#تعریف_کن PORTMUX_RELEASE_MUX_FN_NAME    v_پورت_CPURelease_Mutex_Ints_Disabled_داخلی
#تعریف_کن PORTMUX_COMPARE_مجموعه_FN_NAME    ux_پورت_Compare_مجموعه
#ضمن "portmux_impl.inc.h"
#لغو_تعریف PORTMUX_AQUIRE_MUX_FN_NAME
#لغو_تعریف PORTMUX_RELEASE_MUX_FN_NAME
#لغو_تعریف PORTMUX_COMPARE_مجموعه_FN_NAME


#إذا defined( CONFIG_SPIRAM_SUPPORT )

    #تعریف_کن PORTMUX_AQUIRE_MUX_FN_NAME     v_پورت_CPUAcquire_Mutex_Ints_Disabled_Extram
    #تعریف_کن PORTMUX_RELEASE_MUX_FN_NAME    v_پورت_CPURelease_Mutex_Ints_Disabled_Extram
    #تعریف_کن PORTMUX_COMPARE_مجموعه_FN_NAME    ux_پورت_Compare_مجموعه_Extram
    #ضمن "portmux_impl.inc.h"
    #لغو_تعریف PORTMUX_AQUIRE_MUX_FN_NAME
    #لغو_تعریف PORTMUX_RELEASE_MUX_FN_NAME
    #لغو_تعریف PORTMUX_COMPARE_مجموعه_FN_NAME

#پایان_اگر


#اگر_تعریف_شده CONFIG_FREERTOS_PORTMUX_DEBUG
    #تعریف_کن PORTMUX_AQUIRE_MUX_FN_آرگومانها     پورت_MUX_TYPE * mux, صحيح timeout_چرخهها, ثابت حرف * fnName, صحيح سطر
    #تعریف_کن PORTMUX_RELEASE_MUX_FN_آرگومانها    پورت_MUX_TYPE * mux, ثابت حرف * fnName, صحيح سطر
    #تعریف_کن PORTMUX_AQUIRE_MUX_FN_CALL_آرگومانها( x )     x, timeout_چرخهها, fnName, سطر
    #تعریف_کن PORTMUX_RELEASE_MUX_FN_CALL_آرگومانها( x )    x, fnName, سطر
#وإلا
    #تعریف_کن PORTMUX_AQUIRE_MUX_FN_آرگومانها     پورت_MUX_TYPE * mux, صحيح timeout_چرخهها
    #تعریف_کن PORTMUX_RELEASE_MUX_FN_آرگومانها    پورت_MUX_TYPE * mux
    #تعریف_کن PORTMUX_AQUIRE_MUX_FN_CALL_آرگومانها( x )     x, timeout_چرخهها
    #تعریف_کن PORTMUX_RELEASE_MUX_FN_CALL_آرگومانها( x )    x
#پایان_اگر


ساكن مضمن bool __attribute__( ( always_inline ) ) v_پورت_CPUAcquire_Mutex_Ints_Disabled( PORTMUX_AQUIRE_MUX_FN_آرگومانها )
{
    #إذا defined( CONFIG_SPIRAM_SUPPORT )
        إذا( esp_ptr_external_ram( mux ) )
        {
            أرجع v_پورت_CPUAcquire_Mutex_Ints_Disabled_Extram( PORTMUX_AQUIRE_MUX_FN_CALL_آرگومانها( mux ) );
        }
    #پایان_اگر
    أرجع v_پورت_CPUAcquire_Mutex_Ints_Disabled_داخلی( PORTMUX_AQUIRE_MUX_FN_CALL_آرگومانها( mux ) );
}


ساكن مضمن فراغ v_پورت_CPURelease_Mutex_Ints_Disabled( PORTMUX_RELEASE_MUX_FN_آرگومانها )
{
    #إذا defined( CONFIG_SPIRAM_SUPPORT )
        إذا( esp_ptr_external_ram( mux ) )
        {
            v_پورت_CPURelease_Mutex_Ints_Disabled_Extram( PORTMUX_RELEASE_MUX_FN_CALL_آرگومانها( mux ) );
            أرجع;
        }
    #پایان_اگر
    v_پورت_CPURelease_Mutex_Ints_Disabled_داخلی( PORTMUX_RELEASE_MUX_FN_CALL_آرگومانها( mux ) );
}
