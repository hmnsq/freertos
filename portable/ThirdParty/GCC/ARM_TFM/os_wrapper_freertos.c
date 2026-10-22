/*
 * Copyright 2019-2024,2026 Arm Limited and/or its affiliates <open-source-office@arm.com>
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

/*
 * This file contains the implementation of APIs which are defined in
 * \interface/include/os_wrapper/mutex.h by TF-M(tag: TF-Mv2.0.0).
 * The implementation is based on FreeRTOS mutex type semaphore.
 */

#ಅನ್ತರ್ಭಾವ <stdbool.h>

#ಅನ್ತರ್ಭಾವ "os_wrapper/mutex.h"

#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "semphr.h"
#ಅನ್ತರ್ಭಾವ "mpu_wrappers.h"

#ಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 )

/*
 * In the static allocation, the RAM is required to hold the semaphore's
 * state.
 */
    StaticSemaphore_t x_Secure_Mutex_ಬಫರ್;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
    bool os_wrapper_is_kernel_started( ಶೂನ್ಯ )
    {
        ಹಿಂತಿರುಗಿ xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED;
    }
#ಆದರೆ_ಅಂತ್ಯ

ಶೂನ್ಯ * os_wrapper_mutex_create( ಶೂನ್ಯ )
{
    SemaphoreHandle_t xMutexHandle = ಖಾಲಿ;

    #ಆದರೆ ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 )
        xMutexHandle = xSemaphoreCreateMutex();
    #ಅಥವಾಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 )
        xMutexHandle = xSemaphoreCreateMutexStatic( &x_Secure_Mutex_ಬಫರ್ );
    #ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ ( ಶೂನ್ಯ * ) xMutexHandle;
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_acquire( ಶೂನ್ಯ * handle,
                                   uint32_t timeout )
{
    ತಳ_Type_t xRet;

    ಆದರೆ( !handle )
    {
        ಹಿಂತಿರುಗಿ OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreTake( ( SemaphoreHandle_t ) handle,
                           ( timeout == OS_WRAPPER_WAIT_FOREVER ) ?
                           ಪೋರ್ಟ್_MAX_DELAY : ( TickType_t ) timeout );

    ಆದರೆ( xRet != pdPASS )
    {
        ಹಿಂತಿರುಗಿ OS_WRAPPER_ERROR;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        ಹಿಂತಿರುಗಿ OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_release( ಶೂನ್ಯ * handle )
{
    ತಳ_Type_t xRet;

    ಆದರೆ( !handle )
    {
        ಹಿಂತಿರುಗಿ OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreGive( ( SemaphoreHandle_t ) handle );

    ಆದರೆ( xRet != pdPASS )
    {
        ಹಿಂತಿರುಗಿ OS_WRAPPER_ERROR;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        ಹಿಂತಿರುಗಿ OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_delete( ಶೂನ್ಯ * handle )
{
    vSemaphoreDelete( ( SemaphoreHandle_t ) handle );

    ಹಿಂತಿರುಗಿ OS_WRAPPER_SUCCESS;
}
/*-----------------------------------------------------------*/
