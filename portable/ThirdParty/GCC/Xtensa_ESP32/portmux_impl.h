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
#ಅನ್ತರ್ಭಾವ "soc/cpu.h"
#ಅನ್ತರ್ಭಾವ "portable.h"

/* XOR one core ID with this value to get the other core ID */
#ಆದರೆ ( ESP_IDF_ಆವೃತ್ತಿ < ESP_IDF_ಆವೃತ್ತಿ_VAL( 4, 2, 0 ) )
    #ವ್ಯಾಖ್ಯಾನಿಸು CORE_ID_XOR_ಅದಲುಬದಲು           ( CORE_ID_PRO ^ CORE_ID_APP )
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು CORE_ID_REGVAL_XOR_ಅದಲುಬದಲು    ( CORE_ID_REGVAL_PRO ^ CORE_ID_REGVAL_APP )
#ಆದರೆ_ಅಂತ್ಯ



/*Define the mux routines for use with muxes in internal RAM */
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_AQUIRE_MUX_FN_NAME     v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Ints_Disabled_ಆಂತರಿಕ
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_RELEASE_MUX_FN_NAME    v_ಪೋರ್ಟ್_CPURelease_Mutex_Ints_Disabled_ಆಂತರಿಕ
#ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_COMPARE_ಗಣ_FN_NAME    ux_ಪೋರ್ಟ್_Compare_ಗಣ
#ಅನ್ತರ್ಭಾವ "portmux_impl.inc.h"
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PORTMUX_AQUIRE_MUX_FN_NAME
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PORTMUX_RELEASE_MUX_FN_NAME
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PORTMUX_COMPARE_ಗಣ_FN_NAME


#ಆದರೆ defined( CONFIG_SPIRAM_SUPPORT )

    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_AQUIRE_MUX_FN_NAME     v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Ints_Disabled_Extram
    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_RELEASE_MUX_FN_NAME    v_ಪೋರ್ಟ್_CPURelease_Mutex_Ints_Disabled_Extram
    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_COMPARE_ಗಣ_FN_NAME    ux_ಪೋರ್ಟ್_Compare_ಗಣ_Extram
    #ಅನ್ತರ್ಭಾವ "portmux_impl.inc.h"
    #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PORTMUX_AQUIRE_MUX_FN_NAME
    #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PORTMUX_RELEASE_MUX_FN_NAME
    #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು PORTMUX_COMPARE_ಗಣ_FN_NAME

#ಆದರೆ_ಅಂತ್ಯ


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONFIG_FREERTOS_PORTMUX_DEBUG
    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_AQUIRE_MUX_FN_ವಾದಗಳು     ಪೋರ್ಟ್_MUX_TYPE * mux, ಪೂರ್ಣಾಂಕ timeout_ಚಕ್ರಗಳು, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * fnName, ಪೂರ್ಣಾಂಕ ಸಾಲು
    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_RELEASE_MUX_FN_ವಾದಗಳು    ಪೋರ್ಟ್_MUX_TYPE * mux, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * fnName, ಪೂರ್ಣಾಂಕ ಸಾಲು
    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_AQUIRE_MUX_FN_CALL_ವಾದಗಳು( x )     x, timeout_ಚಕ್ರಗಳು, fnName, ಸಾಲು
    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_RELEASE_MUX_FN_CALL_ವಾದಗಳು( x )    x, fnName, ಸಾಲು
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_AQUIRE_MUX_FN_ವಾದಗಳು     ಪೋರ್ಟ್_MUX_TYPE * mux, ಪೂರ್ಣಾಂಕ timeout_ಚಕ್ರಗಳು
    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_RELEASE_MUX_FN_ವಾದಗಳು    ಪೋರ್ಟ್_MUX_TYPE * mux
    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_AQUIRE_MUX_FN_CALL_ವಾದಗಳು( x )     x, timeout_ಚಕ್ರಗಳು
    #ವ್ಯಾಖ್ಯಾನಿಸು PORTMUX_RELEASE_MUX_FN_CALL_ವಾದಗಳು( x )    x
#ಆದರೆ_ಅಂತ್ಯ


ಸ್ಥಿರ ಸಾಲೊಳಗೆ bool __attribute__( ( always_inline ) ) v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Ints_Disabled( PORTMUX_AQUIRE_MUX_FN_ವಾದಗಳು )
{
    #ಆದರೆ defined( CONFIG_SPIRAM_SUPPORT )
        ಆದರೆ( esp_ptr_external_ram( mux ) )
        {
            ಹಿಂತಿರುಗಿ v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Ints_Disabled_Extram( PORTMUX_AQUIRE_MUX_FN_CALL_ವಾದಗಳು( mux ) );
        }
    #ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ v_ಪೋರ್ಟ್_CPUAcquire_Mutex_Ints_Disabled_ಆಂತರಿಕ( PORTMUX_AQUIRE_MUX_FN_CALL_ವಾದಗಳು( mux ) );
}


ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ v_ಪೋರ್ಟ್_CPURelease_Mutex_Ints_Disabled( PORTMUX_RELEASE_MUX_FN_ವಾದಗಳು )
{
    #ಆದರೆ defined( CONFIG_SPIRAM_SUPPORT )
        ಆದರೆ( esp_ptr_external_ram( mux ) )
        {
            v_ಪೋರ್ಟ್_CPURelease_Mutex_Ints_Disabled_Extram( PORTMUX_RELEASE_MUX_FN_CALL_ವಾದಗಳು( mux ) );
            ಹಿಂತಿರುಗಿ;
        }
    #ಆದರೆ_ಅಂತ್ಯ
    v_ಪೋರ್ಟ್_CPURelease_Mutex_Ints_Disabled_ಆಂತರಿಕ( PORTMUX_RELEASE_MUX_FN_CALL_ವಾದಗಳು( mux ) );
}
