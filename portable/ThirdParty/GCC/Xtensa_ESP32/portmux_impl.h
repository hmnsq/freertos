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
#إذا ( ESP_IDF_نسخو < ESP_IDF_نسخو_VAL( 4, 2, 0 ) )
    #وصف_ڪريو CORE_ID_XOR_مٽا_سٽا           ( CORE_ID_PRO ^ CORE_ID_APP )
#وإلا
    #وصف_ڪريو CORE_ID_REGVAL_XOR_مٽا_سٽا    ( CORE_ID_REGVAL_PRO ^ CORE_ID_REGVAL_APP )
#جيڪڏهن_پورو



/*Define the mux routines for use with muxes in internal RAM */
#وصف_ڪريو PORTMUX_AQUIRE_MUX_FN_NAME     v_پورٽ_CPUAcquire_Mutex_Ints_Disabled_اندروني
#وصف_ڪريو PORTMUX_RELEASE_MUX_FN_NAME    v_پورٽ_CPURelease_Mutex_Ints_Disabled_اندروني
#وصف_ڪريو PORTMUX_COMPARE_سيٽ_FN_NAME    ux_پورٽ_Compare_سيٽ
#ضمن "portmux_impl.inc.h"
#وصف_رد PORTMUX_AQUIRE_MUX_FN_NAME
#وصف_رد PORTMUX_RELEASE_MUX_FN_NAME
#وصف_رد PORTMUX_COMPARE_سيٽ_FN_NAME


#إذا defined( CONFIG_SPIRAM_SUPPORT )

    #وصف_ڪريو PORTMUX_AQUIRE_MUX_FN_NAME     v_پورٽ_CPUAcquire_Mutex_Ints_Disabled_Extram
    #وصف_ڪريو PORTMUX_RELEASE_MUX_FN_NAME    v_پورٽ_CPURelease_Mutex_Ints_Disabled_Extram
    #وصف_ڪريو PORTMUX_COMPARE_سيٽ_FN_NAME    ux_پورٽ_Compare_سيٽ_Extram
    #ضمن "portmux_impl.inc.h"
    #وصف_رد PORTMUX_AQUIRE_MUX_FN_NAME
    #وصف_رد PORTMUX_RELEASE_MUX_FN_NAME
    #وصف_رد PORTMUX_COMPARE_سيٽ_FN_NAME

#جيڪڏهن_پورو


#جيڪڏهن_وصف_ٿيل CONFIG_FREERTOS_PORTMUX_DEBUG
    #وصف_ڪريو PORTMUX_AQUIRE_MUX_FN_دليلون     پورٽ_MUX_TYPE * mux, صحيح timeout_چڪرن, ثابت حرف * fnName, صحيح سٽ
    #وصف_ڪريو PORTMUX_RELEASE_MUX_FN_دليلون    پورٽ_MUX_TYPE * mux, ثابت حرف * fnName, صحيح سٽ
    #وصف_ڪريو PORTMUX_AQUIRE_MUX_FN_CALL_دليلون( x )     x, timeout_چڪرن, fnName, سٽ
    #وصف_ڪريو PORTMUX_RELEASE_MUX_FN_CALL_دليلون( x )    x, fnName, سٽ
#وإلا
    #وصف_ڪريو PORTMUX_AQUIRE_MUX_FN_دليلون     پورٽ_MUX_TYPE * mux, صحيح timeout_چڪرن
    #وصف_ڪريو PORTMUX_RELEASE_MUX_FN_دليلون    پورٽ_MUX_TYPE * mux
    #وصف_ڪريو PORTMUX_AQUIRE_MUX_FN_CALL_دليلون( x )     x, timeout_چڪرن
    #وصف_ڪريو PORTMUX_RELEASE_MUX_FN_CALL_دليلون( x )    x
#جيڪڏهن_پورو


ساكن مضمن bool __attribute__( ( always_inline ) ) v_پورٽ_CPUAcquire_Mutex_Ints_Disabled( PORTMUX_AQUIRE_MUX_FN_دليلون )
{
    #إذا defined( CONFIG_SPIRAM_SUPPORT )
        إذا( esp_ptr_external_ram( mux ) )
        {
            أرجع v_پورٽ_CPUAcquire_Mutex_Ints_Disabled_Extram( PORTMUX_AQUIRE_MUX_FN_CALL_دليلون( mux ) );
        }
    #جيڪڏهن_پورو
    أرجع v_پورٽ_CPUAcquire_Mutex_Ints_Disabled_اندروني( PORTMUX_AQUIRE_MUX_FN_CALL_دليلون( mux ) );
}


ساكن مضمن فراغ v_پورٽ_CPURelease_Mutex_Ints_Disabled( PORTMUX_RELEASE_MUX_FN_دليلون )
{
    #إذا defined( CONFIG_SPIRAM_SUPPORT )
        إذا( esp_ptr_external_ram( mux ) )
        {
            v_پورٽ_CPURelease_Mutex_Ints_Disabled_Extram( PORTMUX_RELEASE_MUX_FN_CALL_دليلون( mux ) );
            أرجع;
        }
    #جيڪڏهن_پورو
    v_پورٽ_CPURelease_Mutex_Ints_Disabled_اندروني( PORTMUX_RELEASE_MUX_FN_CALL_دليلون( mux ) );
}
