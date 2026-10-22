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

#ضمن <stdbool.h>

#ضمن "os_wrapper/mutex.h"

#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "semphr.h"
#ضمن "mpu_wrappers.h"

#إذا ( config_SUPPORT_STATIC_تخصیص == 1 )

/*
 * In the static allocation, the RAM is required to hold the semaphore's
 * state.
 */
    StaticSemaphore_t x_Secure_Mutex_میانگیر;
#پایان_اگر

#إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
    bool os_wrapper_is_kernel_started( فراغ )
    {
        أرجع xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED;
    }
#پایان_اگر

فراغ * os_wrapper_mutex_create( فراغ )
{
    SemaphoreHandle_t xMutexHandle = عدم;

    #إذا ( config_SUPPORT_DYNAMIC_تخصیص == 1 )
        xMutexHandle = xSemaphoreCreateMutex();
    #وإلاإذا ( config_SUPPORT_STATIC_تخصیص == 1 )
        xMutexHandle = xSemaphoreCreateMutexStatic( &x_Secure_Mutex_میانگیر );
    #پایان_اگر
    أرجع ( فراغ * ) xMutexHandle;
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_acquire( فراغ * handle,
                                   uint32_t timeout )
{
    پایه_Type_t xRet;

    إذا( !handle )
    {
        أرجع OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreTake( ( SemaphoreHandle_t ) handle,
                           ( timeout == OS_WRAPPER_WAIT_FOREVER ) ?
                           پورت_MAX_DELAY : ( TickType_t ) timeout );

    إذا( xRet != pdPASS )
    {
        أرجع OS_WRAPPER_ERROR;
    }
    وإلا
    {
        أرجع OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_release( فراغ * handle )
{
    پایه_Type_t xRet;

    إذا( !handle )
    {
        أرجع OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreGive( ( SemaphoreHandle_t ) handle );

    إذا( xRet != pdPASS )
    {
        أرجع OS_WRAPPER_ERROR;
    }
    وإلا
    {
        أرجع OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_delete( فراغ * handle )
{
    vSemaphoreDelete( ( SemaphoreHandle_t ) handle );

    أرجع OS_WRAPPER_SUCCESS;
}
/*-----------------------------------------------------------*/
