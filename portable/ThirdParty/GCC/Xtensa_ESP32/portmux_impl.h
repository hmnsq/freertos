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
#అన్తర్భావ "soc/cpu.h"
#అన్తర్భావ "portable.h"

/* XOR one core ID with this value to get the other core ID */
#ఒకవేళ ( ESP_IDF_సంస్కరణ < ESP_IDF_సంస్కరణ_VAL( 4, 2, 0 ) )
    #నిర్వచించు CORE_ID_XOR_మార్పిడి           ( CORE_ID_PRO ^ CORE_ID_APP )
#లేకపోతే
    #నిర్వచించు CORE_ID_REGVAL_XOR_మార్పిడి    ( CORE_ID_REGVAL_PRO ^ CORE_ID_REGVAL_APP )
#అయితే_ముగింపు



/*Define the mux routines for use with muxes in internal RAM */
#నిర్వచించు PORTMUX_AQUIRE_MUX_FN_NAME     v_పోర్టు_CPUAcquire_Mutex_Ints_Disabled_అంతర్గత
#నిర్వచించు PORTMUX_RELEASE_MUX_FN_NAME    v_పోర్టు_CPURelease_Mutex_Ints_Disabled_అంతర్గత
#నిర్వచించు PORTMUX_COMPARE_సమితి_FN_NAME    ux_పోర్టు_Compare_సమితి
#అన్తర్భావ "portmux_impl.inc.h"
#నిర్వచనం_రద్దు PORTMUX_AQUIRE_MUX_FN_NAME
#నిర్వచనం_రద్దు PORTMUX_RELEASE_MUX_FN_NAME
#నిర్వచనం_రద్దు PORTMUX_COMPARE_సమితి_FN_NAME


#ఒకవేళ defined( CONFIG_SPIRAM_SUPPORT )

    #నిర్వచించు PORTMUX_AQUIRE_MUX_FN_NAME     v_పోర్టు_CPUAcquire_Mutex_Ints_Disabled_Extram
    #నిర్వచించు PORTMUX_RELEASE_MUX_FN_NAME    v_పోర్టు_CPURelease_Mutex_Ints_Disabled_Extram
    #నిర్వచించు PORTMUX_COMPARE_సమితి_FN_NAME    ux_పోర్టు_Compare_సమితి_Extram
    #అన్తర్భావ "portmux_impl.inc.h"
    #నిర్వచనం_రద్దు PORTMUX_AQUIRE_MUX_FN_NAME
    #నిర్వచనం_రద్దు PORTMUX_RELEASE_MUX_FN_NAME
    #నిర్వచనం_రద్దు PORTMUX_COMPARE_సమితి_FN_NAME

#అయితే_ముగింపు


#నిర్వచితమైతే CONFIG_FREERTOS_PORTMUX_DEBUG
    #నిర్వచించు PORTMUX_AQUIRE_MUX_FN_వాదనలు     పోర్టు_MUX_TYPE * mux, పూర్ణాంకం timeout_చక్రాలు, స్థిరరాశి అక్షరం * fnName, పూర్ణాంకం పంక్తి
    #నిర్వచించు PORTMUX_RELEASE_MUX_FN_వాదనలు    పోర్టు_MUX_TYPE * mux, స్థిరరాశి అక్షరం * fnName, పూర్ణాంకం పంక్తి
    #నిర్వచించు PORTMUX_AQUIRE_MUX_FN_CALL_వాదనలు( x )     x, timeout_చక్రాలు, fnName, పంక్తి
    #నిర్వచించు PORTMUX_RELEASE_MUX_FN_CALL_వాదనలు( x )    x, fnName, పంక్తి
#లేకపోతే
    #నిర్వచించు PORTMUX_AQUIRE_MUX_FN_వాదనలు     పోర్టు_MUX_TYPE * mux, పూర్ణాంకం timeout_చక్రాలు
    #నిర్వచించు PORTMUX_RELEASE_MUX_FN_వాదనలు    పోర్టు_MUX_TYPE * mux
    #నిర్వచించు PORTMUX_AQUIRE_MUX_FN_CALL_వాదనలు( x )     x, timeout_చక్రాలు
    #నిర్వచించు PORTMUX_RELEASE_MUX_FN_CALL_వాదనలు( x )    x
#అయితే_ముగింపు


స్థిర అంతఃవరుస bool __attribute__( ( always_inline ) ) v_పోర్టు_CPUAcquire_Mutex_Ints_Disabled( PORTMUX_AQUIRE_MUX_FN_వాదనలు )
{
    #ఒకవేళ defined( CONFIG_SPIRAM_SUPPORT )
        ఒకవేళ( esp_ptr_external_ram( mux ) )
        {
            తిరిగి v_పోర్టు_CPUAcquire_Mutex_Ints_Disabled_Extram( PORTMUX_AQUIRE_MUX_FN_CALL_వాదనలు( mux ) );
        }
    #అయితే_ముగింపు
    తిరిగి v_పోర్టు_CPUAcquire_Mutex_Ints_Disabled_అంతర్గత( PORTMUX_AQUIRE_MUX_FN_CALL_వాదనలు( mux ) );
}


స్థిర అంతఃవరుస శూన్య v_పోర్టు_CPURelease_Mutex_Ints_Disabled( PORTMUX_RELEASE_MUX_FN_వాదనలు )
{
    #ఒకవేళ defined( CONFIG_SPIRAM_SUPPORT )
        ఒకవేళ( esp_ptr_external_ram( mux ) )
        {
            v_పోర్టు_CPURelease_Mutex_Ints_Disabled_Extram( PORTMUX_RELEASE_MUX_FN_CALL_వాదనలు( mux ) );
            తిరిగి;
        }
    #అయితే_ముగింపు
    v_పోర్టు_CPURelease_Mutex_Ints_Disabled_అంతర్గత( PORTMUX_RELEASE_MUX_FN_CALL_వాదనలు( mux ) );
}
