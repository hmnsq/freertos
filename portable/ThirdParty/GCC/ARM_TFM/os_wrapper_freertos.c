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

#ଅନ୍ତର୍ଭାଵ <stdbool.h>

#ଅନ୍ତର୍ଭାଵ "os_wrapper/mutex.h"

#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"
#ଅନ୍ତର୍ଭାଵ "semphr.h"
#ଅନ୍ତର୍ଭାଵ "mpu_wrappers.h"

#ଯଦି ( configSUPPORT_STATIC_ALLOCATION == 1 )

/*
 * In the static allocation, the RAM is required to hold the semaphore's
 * state.
 */
    StaticSemaphore_t xSecureMutexBuffer;
#endif

#ଯଦି ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
    bool os_wrapper_is_kernel_started( ଶୂନ୍ୟ )
    {
        ଫେରନ୍ତୁ xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED;
    }
#endif

ଶୂନ୍ୟ * os_wrapper_mutex_create( ଶୂନ୍ୟ )
{
    SemaphoreHandle_t xMutexHandle = ଖାଲି;

    #ଯଦି ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        xMutexHandle = xSemaphoreCreateMutex();
    #ନଚେତଯଦି ( configSUPPORT_STATIC_ALLOCATION == 1 )
        xMutexHandle = xSemaphoreCreateMutexStatic( &xSecureMutexBuffer );
    #endif
    ଫେରନ୍ତୁ ( ଶୂନ୍ୟ * ) xMutexHandle;
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_acquire( ଶୂନ୍ୟ * handle,
                                   uint32_t timeout )
{
    BaseType_t xRet;

    ଯଦି( !handle )
    {
        ଫେରନ୍ତୁ OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreTake( ( SemaphoreHandle_t ) handle,
                           ( timeout == OS_WRAPPER_WAIT_FOREVER ) ?
                           portMAX_DELAY : ( TickType_t ) timeout );

    ଯଦି( xRet != pdPASS )
    {
        ଫେରନ୍ତୁ OS_WRAPPER_ERROR;
    }
    ଅନ୍ୟଥା
    {
        ଫେରନ୍ତୁ OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_release( ଶୂନ୍ୟ * handle )
{
    BaseType_t xRet;

    ଯଦି( !handle )
    {
        ଫେରନ୍ତୁ OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreGive( ( SemaphoreHandle_t ) handle );

    ଯଦି( xRet != pdPASS )
    {
        ଫେରନ୍ତୁ OS_WRAPPER_ERROR;
    }
    ଅନ୍ୟଥା
    {
        ଫେରନ୍ତୁ OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_delete( ଶୂନ୍ୟ * handle )
{
    vSemaphoreDelete( ( SemaphoreHandle_t ) handle );

    ଫେରନ୍ତୁ OS_WRAPPER_SUCCESS;
}
/*-----------------------------------------------------------*/
