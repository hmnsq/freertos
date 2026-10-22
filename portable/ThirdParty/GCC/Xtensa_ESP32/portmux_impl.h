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
#अन्तर्भाव "soc/cpu.h"
#अन्तर्भाव "portable.h"

/* XOR one core ID with this value to get the other core ID */
#यदि ( ESP_IDF_संस्करणम् < ESP_IDF_संस्करणम्_VAL( 4, 2, 0 ) )
    #परिभाषय CORE_ID_XOR_SWAP           ( CORE_ID_PRO ^ CORE_ID_APP )
#अन्यथा
    #परिभाषय CORE_ID_REGVAL_XOR_SWAP    ( CORE_ID_REGVAL_PRO ^ CORE_ID_REGVAL_APP )
#यदि_अन्तः



/*Define the mux routines for use with muxes in internal RAM */
#परिभाषय PORTMUX_AQUIRE_MUX_FN_NAME     v_पत्तनम्_CPUAcquire_Mutex_Ints_Disabled_आन्तरिकम्
#परिभाषय PORTMUX_RELEASE_MUX_FN_NAME    v_पत्तनम्_CPURelease_Mutex_Ints_Disabled_आन्तरिकम्
#परिभाषय PORTMUX_COMPARE_समुच्चयः_FN_NAME    ux_पत्तनम्_Compare_समुच्चयः
#अन्तर्भाव "portmux_impl.inc.h"
#अपरिभाषय PORTMUX_AQUIRE_MUX_FN_NAME
#अपरिभाषय PORTMUX_RELEASE_MUX_FN_NAME
#अपरिभाषय PORTMUX_COMPARE_समुच्चयः_FN_NAME


#यदि defined( CONFIG_SPIRAM_SUPPORT )

    #परिभाषय PORTMUX_AQUIRE_MUX_FN_NAME     v_पत्तनम्_CPUAcquire_Mutex_Ints_Disabled_Extram
    #परिभाषय PORTMUX_RELEASE_MUX_FN_NAME    v_पत्तनम्_CPURelease_Mutex_Ints_Disabled_Extram
    #परिभाषय PORTMUX_COMPARE_समुच्चयः_FN_NAME    ux_पत्तनम्_Compare_समुच्चयः_Extram
    #अन्तर्भाव "portmux_impl.inc.h"
    #अपरिभाषय PORTMUX_AQUIRE_MUX_FN_NAME
    #अपरिभाषय PORTMUX_RELEASE_MUX_FN_NAME
    #अपरिभाषय PORTMUX_COMPARE_समुच्चयः_FN_NAME

#यदि_अन्तः


#यदि_परिभाषितम् CONFIG_FREERTOS_PORTMUX_DEBUG
    #परिभाषय PORTMUX_AQUIRE_MUX_FN_तर्काः     पत्तनम्_MUX_TYPE * mux, पूर्णाङ्क timeout_आवृत्तयः, ध्रुव वर्ण * fnName, पूर्णाङ्क पङ्क्तिः
    #परिभाषय PORTMUX_RELEASE_MUX_FN_तर्काः    पत्तनम्_MUX_TYPE * mux, ध्रुव वर्ण * fnName, पूर्णाङ्क पङ्क्तिः
    #परिभाषय PORTMUX_AQUIRE_MUX_FN_CALL_तर्काः( x )     x, timeout_आवृत्तयः, fnName, पङ्क्तिः
    #परिभाषय PORTMUX_RELEASE_MUX_FN_CALL_तर्काः( x )    x, fnName, पङ्क्तिः
#अन्यथा
    #परिभाषय PORTMUX_AQUIRE_MUX_FN_तर्काः     पत्तनम्_MUX_TYPE * mux, पूर्णाङ्क timeout_आवृत्तयः
    #परिभाषय PORTMUX_RELEASE_MUX_FN_तर्काः    पत्तनम्_MUX_TYPE * mux
    #परिभाषय PORTMUX_AQUIRE_MUX_FN_CALL_तर्काः( x )     x, timeout_आवृत्तयः
    #परिभाषय PORTMUX_RELEASE_MUX_FN_CALL_तर्काः( x )    x
#यदि_अन्तः


स्थिर अन्तःस्थ bool __attribute__( ( always_inline ) ) v_पत्तनम्_CPUAcquire_Mutex_Ints_Disabled( PORTMUX_AQUIRE_MUX_FN_तर्काः )
{
    #यदि defined( CONFIG_SPIRAM_SUPPORT )
        यदि( esp_ptr_external_ram( mux ) )
        {
            प्रत्यागम v_पत्तनम्_CPUAcquire_Mutex_Ints_Disabled_Extram( PORTMUX_AQUIRE_MUX_FN_CALL_तर्काः( mux ) );
        }
    #यदि_अन्तः
    प्रत्यागम v_पत्तनम्_CPUAcquire_Mutex_Ints_Disabled_आन्तरिकम्( PORTMUX_AQUIRE_MUX_FN_CALL_तर्काः( mux ) );
}


स्थिर अन्तःस्थ शून्य v_पत्तनम्_CPURelease_Mutex_Ints_Disabled( PORTMUX_RELEASE_MUX_FN_तर्काः )
{
    #यदि defined( CONFIG_SPIRAM_SUPPORT )
        यदि( esp_ptr_external_ram( mux ) )
        {
            v_पत्तनम्_CPURelease_Mutex_Ints_Disabled_Extram( PORTMUX_RELEASE_MUX_FN_CALL_तर्काः( mux ) );
            प्रत्यागम;
        }
    #यदि_अन्तः
    v_पत्तनम्_CPURelease_Mutex_Ints_Disabled_आन्तरिकम्( PORTMUX_RELEASE_MUX_FN_CALL_तर्काः( mux ) );
}
