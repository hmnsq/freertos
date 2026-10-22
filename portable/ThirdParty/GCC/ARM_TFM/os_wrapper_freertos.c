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

#அந்தர்பாவ <stdbool.h>

#அந்தர்பாவ "os_wrapper/mutex.h"

#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"
#அந்தர்பாவ "semphr.h"
#அந்தர்பாவ "mpu_wrappers.h"

#எனில் ( configSUPPORT_STATIC_ALLOCATION == 1 )

/*
 * In the static allocation, the RAM is required to hold the semaphore's
 * state.
 */
    StaticSemaphore_t xSecureMutexBuffer;
#endif

#எனில் ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
    bool os_wrapper_is_kernel_started( வெறுமை )
    {
        திரும்பு xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED;
    }
#endif

வெறுமை * os_wrapper_mutex_create( வெறுமை )
{
    SemaphoreHandle_t xMutexHandle = வெற்று;

    #எனில் ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        xMutexHandle = xSemaphoreCreateMutex();
    #அல்லதெனில் ( configSUPPORT_STATIC_ALLOCATION == 1 )
        xMutexHandle = xSemaphoreCreateMutexStatic( &xSecureMutexBuffer );
    #endif
    திரும்பு ( வெறுமை * ) xMutexHandle;
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_acquire( வெறுமை * handle,
                                   uint32_t timeout )
{
    BaseType_t xRet;

    எனில்( !handle )
    {
        திரும்பு OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreTake( ( SemaphoreHandle_t ) handle,
                           ( timeout == OS_WRAPPER_WAIT_FOREVER ) ?
                           portMAX_DELAY : ( TickType_t ) timeout );

    எனில்( xRet != pdPASS )
    {
        திரும்பு OS_WRAPPER_ERROR;
    }
    இல்லையெனில்
    {
        திரும்பு OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_release( வெறுமை * handle )
{
    BaseType_t xRet;

    எனில்( !handle )
    {
        திரும்பு OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreGive( ( SemaphoreHandle_t ) handle );

    எனில்( xRet != pdPASS )
    {
        திரும்பு OS_WRAPPER_ERROR;
    }
    இல்லையெனில்
    {
        திரும்பு OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_delete( வெறுமை * handle )
{
    vSemaphoreDelete( ( SemaphoreHandle_t ) handle );

    திரும்பு OS_WRAPPER_SUCCESS;
}
/*-----------------------------------------------------------*/
