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

#అన్తర్భావ <stdbool.h>

#అన్తర్భావ "os_wrapper/mutex.h"

#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "semphr.h"
#అన్తర్భావ "mpu_wrappers.h"

#ఒకవేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 )

/*
 * In the static allocation, the RAM is required to hold the semaphore's
 * state.
 */
    StaticSemaphore_t x_Secure_Mutex_బఫరు;
#అయితే_ముగింపు

#ఒకవేళ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
    bool os_wrapper_is_kernel_started( శూన్య )
    {
        తిరిగి xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED;
    }
#అయితే_ముగింపు

శూన్య * os_wrapper_mutex_create( శూన్య )
{
    SemaphoreHandle_t xMutexHandle = ఖాళీ;

    #ఒకవేళ ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 )
        xMutexHandle = xSemaphoreCreateMutex();
    #లేదావేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 )
        xMutexHandle = xSemaphoreCreateMutexStatic( &x_Secure_Mutex_బఫరు );
    #అయితే_ముగింపు
    తిరిగి ( శూన్య * ) xMutexHandle;
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_acquire( శూన్య * handle,
                                   uint32_t timeout )
{
    పునాది_Type_t xRet;

    ఒకవేళ( !handle )
    {
        తిరిగి OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreTake( ( SemaphoreHandle_t ) handle,
                           ( timeout == OS_WRAPPER_WAIT_FOREVER ) ?
                           పోర్టు_MAX_DELAY : ( TickType_t ) timeout );

    ఒకవేళ( xRet != pdPASS )
    {
        తిరిగి OS_WRAPPER_ERROR;
    }
    లేకపోతే
    {
        తిరిగి OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_release( శూన్య * handle )
{
    పునాది_Type_t xRet;

    ఒకవేళ( !handle )
    {
        తిరిగి OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreGive( ( SemaphoreHandle_t ) handle );

    ఒకవేళ( xRet != pdPASS )
    {
        తిరిగి OS_WRAPPER_ERROR;
    }
    లేకపోతే
    {
        తిరిగి OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_delete( శూన్య * handle )
{
    vSemaphoreDelete( ( SemaphoreHandle_t ) handle );

    తిరిగి OS_WRAPPER_SUCCESS;
}
/*-----------------------------------------------------------*/
