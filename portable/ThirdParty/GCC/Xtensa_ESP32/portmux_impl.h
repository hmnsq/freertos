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
#إذا ( ESP_IDF_نسخہ < ESP_IDF_نسخہ_VAL( 4, 2, 0 ) )
    #تعریف_کرو CORE_ID_XOR_وٹاندرا           ( CORE_ID_PRO ^ CORE_ID_APP )
#وإلا
    #تعریف_کرو CORE_ID_REGVAL_XOR_وٹاندرا    ( CORE_ID_REGVAL_PRO ^ CORE_ID_REGVAL_APP )
#جے_انت



/*Define the mux routines for use with muxes in internal RAM */
#تعریف_کرو PORTMUX_AQUIRE_MUX_FN_NAME     v_پورٹ_CPUAcquire_Mutex_Ints_Disabled_اندرونی
#تعریف_کرو PORTMUX_RELEASE_MUX_FN_NAME    v_پورٹ_CPURelease_Mutex_Ints_Disabled_اندرونی
#تعریف_کرو PORTMUX_COMPARE_سیٹ_FN_NAME    ux_پورٹ_Compare_سیٹ
#ضمن "portmux_impl.inc.h"
#تعریف_رد PORTMUX_AQUIRE_MUX_FN_NAME
#تعریف_رد PORTMUX_RELEASE_MUX_FN_NAME
#تعریف_رد PORTMUX_COMPARE_سیٹ_FN_NAME


#إذا defined( CONFIG_SPIRAM_SUPPORT )

    #تعریف_کرو PORTMUX_AQUIRE_MUX_FN_NAME     v_پورٹ_CPUAcquire_Mutex_Ints_Disabled_Extram
    #تعریف_کرو PORTMUX_RELEASE_MUX_FN_NAME    v_پورٹ_CPURelease_Mutex_Ints_Disabled_Extram
    #تعریف_کرو PORTMUX_COMPARE_سیٹ_FN_NAME    ux_پورٹ_Compare_سیٹ_Extram
    #ضمن "portmux_impl.inc.h"
    #تعریف_رد PORTMUX_AQUIRE_MUX_FN_NAME
    #تعریف_رد PORTMUX_RELEASE_MUX_FN_NAME
    #تعریف_رد PORTMUX_COMPARE_سیٹ_FN_NAME

#جے_انت


#جے_تعریف_شدہ CONFIG_FREERTOS_PORTMUX_DEBUG
    #تعریف_کرو PORTMUX_AQUIRE_MUX_FN_دلیلاں     پورٹ_MUX_TYPE * mux, صحيح timeout_چکراں, ثابت حرف * fnName, صحيح سطر
    #تعریف_کرو PORTMUX_RELEASE_MUX_FN_دلیلاں    پورٹ_MUX_TYPE * mux, ثابت حرف * fnName, صحيح سطر
    #تعریف_کرو PORTMUX_AQUIRE_MUX_FN_CALL_دلیلاں( x )     x, timeout_چکراں, fnName, سطر
    #تعریف_کرو PORTMUX_RELEASE_MUX_FN_CALL_دلیلاں( x )    x, fnName, سطر
#وإلا
    #تعریف_کرو PORTMUX_AQUIRE_MUX_FN_دلیلاں     پورٹ_MUX_TYPE * mux, صحيح timeout_چکراں
    #تعریف_کرو PORTMUX_RELEASE_MUX_FN_دلیلاں    پورٹ_MUX_TYPE * mux
    #تعریف_کرو PORTMUX_AQUIRE_MUX_FN_CALL_دلیلاں( x )     x, timeout_چکراں
    #تعریف_کرو PORTMUX_RELEASE_MUX_FN_CALL_دلیلاں( x )    x
#جے_انت


ساكن مضمن bool __attribute__( ( always_inline ) ) v_پورٹ_CPUAcquire_Mutex_Ints_Disabled( PORTMUX_AQUIRE_MUX_FN_دلیلاں )
{
    #إذا defined( CONFIG_SPIRAM_SUPPORT )
        إذا( esp_ptr_external_ram( mux ) )
        {
            أرجع v_پورٹ_CPUAcquire_Mutex_Ints_Disabled_Extram( PORTMUX_AQUIRE_MUX_FN_CALL_دلیلاں( mux ) );
        }
    #جے_انت
    أرجع v_پورٹ_CPUAcquire_Mutex_Ints_Disabled_اندرونی( PORTMUX_AQUIRE_MUX_FN_CALL_دلیلاں( mux ) );
}


ساكن مضمن فراغ v_پورٹ_CPURelease_Mutex_Ints_Disabled( PORTMUX_RELEASE_MUX_FN_دلیلاں )
{
    #إذا defined( CONFIG_SPIRAM_SUPPORT )
        إذا( esp_ptr_external_ram( mux ) )
        {
            v_پورٹ_CPURelease_Mutex_Ints_Disabled_Extram( PORTMUX_RELEASE_MUX_FN_CALL_دلیلاں( mux ) );
            أرجع;
        }
    #جے_انت
    v_پورٹ_CPURelease_Mutex_Ints_Disabled_اندرونی( PORTMUX_RELEASE_MUX_FN_CALL_دلیلاں( mux ) );
}
