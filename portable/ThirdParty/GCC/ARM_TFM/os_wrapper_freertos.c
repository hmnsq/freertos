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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdbool.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "os_wrapper/mutex.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "semphr.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_wrappers.h"

#ਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 )

/*
 * In the static allocation, the RAM is required to hold the semaphore's
 * state.
 */
    StaticSemaphore_t x_Secure_Mutex_ਬਫਰ;
#ਜੇ_ਅੰਤ

#ਜੇ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
    bool os_wrapper_is_kernel_started( ਖਾਲੀ )
    {
        ਵਾਪਸ xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED;
    }
#ਜੇ_ਅੰਤ

ਖਾਲੀ * os_wrapper_mutex_create( ਖਾਲੀ )
{
    SemaphoreHandle_t xMutexHandle = ਨਿਰਾ;

    #ਜੇ ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 )
        xMutexHandle = xSemaphoreCreateMutex();
    #ਜਾਂਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 )
        xMutexHandle = xSemaphoreCreateMutexStatic( &x_Secure_Mutex_ਬਫਰ );
    #ਜੇ_ਅੰਤ
    ਵਾਪਸ ( ਖਾਲੀ * ) xMutexHandle;
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_acquire( ਖਾਲੀ * handle,
                                   uint32_t timeout )
{
    ਅਧਾਰ_Type_t xRet;

    ਜੇ( !handle )
    {
        ਵਾਪਸ OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreTake( ( SemaphoreHandle_t ) handle,
                           ( timeout == OS_WRAPPER_WAIT_FOREVER ) ?
                           ਪੋਰਟ_MAX_DELAY : ( TickType_t ) timeout );

    ਜੇ( xRet != pdPASS )
    {
        ਵਾਪਸ OS_WRAPPER_ERROR;
    }
    ਨਹੀਂਤਾਂ
    {
        ਵਾਪਸ OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_release( ਖਾਲੀ * handle )
{
    ਅਧਾਰ_Type_t xRet;

    ਜੇ( !handle )
    {
        ਵਾਪਸ OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreGive( ( SemaphoreHandle_t ) handle );

    ਜੇ( xRet != pdPASS )
    {
        ਵਾਪਸ OS_WRAPPER_ERROR;
    }
    ਨਹੀਂਤਾਂ
    {
        ਵਾਪਸ OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_delete( ਖਾਲੀ * handle )
{
    vSemaphoreDelete( ( SemaphoreHandle_t ) handle );

    ਵਾਪਸ OS_WRAPPER_SUCCESS;
}
/*-----------------------------------------------------------*/
