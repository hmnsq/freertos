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
#समावेश "soc/cpu.h"
#समावेश "portable.h"

/* XOR one core ID with this value to get the other core ID */
#अगर ( ESP_IDF_VERSION < ESP_IDF_VERSION_VAL( 4, 2, 0 ) )
    #घोषणा CORE_ID_XOR_SWAP           ( CORE_ID_PRO ^ CORE_ID_APP )
#अन्यथा
    #घोषणा CORE_ID_REGVAL_XOR_SWAP    ( CORE_ID_REGVAL_PRO ^ CORE_ID_REGVAL_APP )
#पूर्ण_अगर



/*Define the mux routines for use with muxes in internal RAM */
#घोषणा PORTMUX_AQUIRE_MUX_FN_NAME     vPortCPUAcquireMutexIntsDisabledInternal
#घोषणा PORTMUX_RELEASE_MUX_FN_NAME    vPortCPUReleaseMutexIntsDisabledInternal
#घोषणा PORTMUX_COMPARE_SET_FN_NAME    uxPortCompareSet
#समावेश "portmux_impl.inc.h"
#अघोषित PORTMUX_AQUIRE_MUX_FN_NAME
#अघोषित PORTMUX_RELEASE_MUX_FN_NAME
#अघोषित PORTMUX_COMPARE_SET_FN_NAME


#अगर defined( CONFIG_SPIRAM_SUPPORT )

    #घोषणा PORTMUX_AQUIRE_MUX_FN_NAME     vPortCPUAcquireMutexIntsDisabledExtram
    #घोषणा PORTMUX_RELEASE_MUX_FN_NAME    vPortCPUReleaseMutexIntsDisabledExtram
    #घोषणा PORTMUX_COMPARE_SET_FN_NAME    uxPortCompareSetExtram
    #समावेश "portmux_impl.inc.h"
    #अघोषित PORTMUX_AQUIRE_MUX_FN_NAME
    #अघोषित PORTMUX_RELEASE_MUX_FN_NAME
    #अघोषित PORTMUX_COMPARE_SET_FN_NAME

#पूर्ण_अगर


#अगर_घोषित CONFIG_FREERTOS_PORTMUX_DEBUG
    #घोषणा PORTMUX_AQUIRE_MUX_FN_ARGS     portMUX_TYPE * mux, पूर्णांक timeout_cycles, स्थिर अक्षर * fnName, पूर्णांक पंक्ति
    #घोषणा PORTMUX_RELEASE_MUX_FN_ARGS    portMUX_TYPE * mux, स्थिर अक्षर * fnName, पूर्णांक पंक्ति
    #घोषणा PORTMUX_AQUIRE_MUX_FN_CALL_ARGS( x )     x, timeout_cycles, fnName, पंक्ति
    #घोषणा PORTMUX_RELEASE_MUX_FN_CALL_ARGS( x )    x, fnName, पंक्ति
#अन्यथा
    #घोषणा PORTMUX_AQUIRE_MUX_FN_ARGS     portMUX_TYPE * mux, पूर्णांक timeout_cycles
    #घोषणा PORTMUX_RELEASE_MUX_FN_ARGS    portMUX_TYPE * mux
    #घोषणा PORTMUX_AQUIRE_MUX_FN_CALL_ARGS( x )     x, timeout_cycles
    #घोषणा PORTMUX_RELEASE_MUX_FN_CALL_ARGS( x )    x
#पूर्ण_अगर


अटल अंतरभूत bool __attribute__( ( always_inline ) ) vPortCPUAcquireMutexIntsDisabled( PORTMUX_AQUIRE_MUX_FN_ARGS )
{
    #अगर defined( CONFIG_SPIRAM_SUPPORT )
        अगर( esp_ptr_external_ram( mux ) )
        {
            वापस vPortCPUAcquireMutexIntsDisabledExtram( PORTMUX_AQUIRE_MUX_FN_CALL_ARGS( mux ) );
        }
    #पूर्ण_अगर
    वापस vPortCPUAcquireMutexIntsDisabledInternal( PORTMUX_AQUIRE_MUX_FN_CALL_ARGS( mux ) );
}


अटल अंतरभूत व्योम vPortCPUReleaseMutexIntsDisabled( PORTMUX_RELEASE_MUX_FN_ARGS )
{
    #अगर defined( CONFIG_SPIRAM_SUPPORT )
        अगर( esp_ptr_external_ram( mux ) )
        {
            vPortCPUReleaseMutexIntsDisabledExtram( PORTMUX_RELEASE_MUX_FN_CALL_ARGS( mux ) );
            वापस;
        }
    #पूर्ण_अगर
    vPortCPUReleaseMutexIntsDisabledInternal( PORTMUX_RELEASE_MUX_FN_CALL_ARGS( mux ) );
}
