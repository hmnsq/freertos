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
    #تعریف_کړه CORE_ID_XOR_بدلون           ( CORE_ID_PRO ^ CORE_ID_APP )
#وإلا
    #تعریف_کړه CORE_ID_REGVAL_XOR_بدلون    ( CORE_ID_REGVAL_PRO ^ CORE_ID_REGVAL_APP )
#د_که_پای



/*Define the mux routines for use with muxes in internal RAM */
#تعریف_کړه PORTMUX_AQUIRE_MUX_FN_NAME     v_پورټ_CPUAcquire_Mutex_Ints_Disabled_دننی
#تعریف_کړه PORTMUX_RELEASE_MUX_FN_NAME    v_پورټ_CPURelease_Mutex_Ints_Disabled_دننی
#تعریف_کړه PORTMUX_COMPARE_سېټ_FN_NAME    ux_پورټ_Compare_سېټ
#ضمن "portmux_impl.inc.h"
#تعریف_لغوه PORTMUX_AQUIRE_MUX_FN_NAME
#تعریف_لغوه PORTMUX_RELEASE_MUX_FN_NAME
#تعریف_لغوه PORTMUX_COMPARE_سېټ_FN_NAME


#إذا defined( CONFIG_SPIRAM_SUPPORT )

    #تعریف_کړه PORTMUX_AQUIRE_MUX_FN_NAME     v_پورټ_CPUAcquire_Mutex_Ints_Disabled_Extram
    #تعریف_کړه PORTMUX_RELEASE_MUX_FN_NAME    v_پورټ_CPURelease_Mutex_Ints_Disabled_Extram
    #تعریف_کړه PORTMUX_COMPARE_سېټ_FN_NAME    ux_پورټ_Compare_سېټ_Extram
    #ضمن "portmux_impl.inc.h"
    #تعریف_لغوه PORTMUX_AQUIRE_MUX_FN_NAME
    #تعریف_لغوه PORTMUX_RELEASE_MUX_FN_NAME
    #تعریف_لغوه PORTMUX_COMPARE_سېټ_FN_NAME

#د_که_پای


#که_تعریف_شوی CONFIG_FREERTOS_PORTMUX_DEBUG
    #تعریف_کړه PORTMUX_AQUIRE_MUX_FN_دلیلونه     پورټ_MUX_TYPE * mux, صحيح timeout_دورې, ثابت حرف * fnName, صحيح کرښه
    #تعریف_کړه PORTMUX_RELEASE_MUX_FN_دلیلونه    پورټ_MUX_TYPE * mux, ثابت حرف * fnName, صحيح کرښه
    #تعریف_کړه PORTMUX_AQUIRE_MUX_FN_CALL_دلیلونه( x )     x, timeout_دورې, fnName, کرښه
    #تعریف_کړه PORTMUX_RELEASE_MUX_FN_CALL_دلیلونه( x )    x, fnName, کرښه
#وإلا
    #تعریف_کړه PORTMUX_AQUIRE_MUX_FN_دلیلونه     پورټ_MUX_TYPE * mux, صحيح timeout_دورې
    #تعریف_کړه PORTMUX_RELEASE_MUX_FN_دلیلونه    پورټ_MUX_TYPE * mux
    #تعریف_کړه PORTMUX_AQUIRE_MUX_FN_CALL_دلیلونه( x )     x, timeout_دورې
    #تعریف_کړه PORTMUX_RELEASE_MUX_FN_CALL_دلیلونه( x )    x
#د_که_پای


ساكن مضمن bool __attribute__( ( always_inline ) ) v_پورټ_CPUAcquire_Mutex_Ints_Disabled( PORTMUX_AQUIRE_MUX_FN_دلیلونه )
{
    #إذا defined( CONFIG_SPIRAM_SUPPORT )
        إذا( esp_ptr_external_ram( mux ) )
        {
            أرجع v_پورټ_CPUAcquire_Mutex_Ints_Disabled_Extram( PORTMUX_AQUIRE_MUX_FN_CALL_دلیلونه( mux ) );
        }
    #د_که_پای
    أرجع v_پورټ_CPUAcquire_Mutex_Ints_Disabled_دننی( PORTMUX_AQUIRE_MUX_FN_CALL_دلیلونه( mux ) );
}


ساكن مضمن فراغ v_پورټ_CPURelease_Mutex_Ints_Disabled( PORTMUX_RELEASE_MUX_FN_دلیلونه )
{
    #إذا defined( CONFIG_SPIRAM_SUPPORT )
        إذا( esp_ptr_external_ram( mux ) )
        {
            v_پورټ_CPURelease_Mutex_Ints_Disabled_Extram( PORTMUX_RELEASE_MUX_FN_CALL_دلیلونه( mux ) );
            أرجع;
        }
    #د_که_پای
    v_پورټ_CPURelease_Mutex_Ints_Disabled_دننی( PORTMUX_RELEASE_MUX_FN_CALL_دلیلونه( mux ) );
}
