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

#അന്തര്ഭാവ <stdbool.h>

#അന്തര്ഭാവ "os_wrapper/mutex.h"

#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"
#അന്തര്ഭാവ "semphr.h"
#അന്തര്ഭാവ "mpu_wrappers.h"

#എങ്കിൽ ( configSUPPORT_STATIC_ALLOCATION == 1 )

/*
 * In the static allocation, the RAM is required to hold the semaphore's
 * state.
 */
    StaticSemaphore_t xSecureMutexBuffer;
#endif

#എങ്കിൽ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
    bool os_wrapper_is_kernel_started( ശൂന്യം )
    {
        തിരികെ xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED;
    }
#endif

ശൂന്യം * os_wrapper_mutex_create( ശൂന്യം )
{
    SemaphoreHandle_t xMutexHandle = ശൂന്യ;

    #എങ്കിൽ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        xMutexHandle = xSemaphoreCreateMutex();
    #അല്ലെങ്കിലെങ്കിൽ ( configSUPPORT_STATIC_ALLOCATION == 1 )
        xMutexHandle = xSemaphoreCreateMutexStatic( &xSecureMutexBuffer );
    #endif
    തിരികെ ( ശൂന്യം * ) xMutexHandle;
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_acquire( ശൂന്യം * handle,
                                   uint32_t timeout )
{
    BaseType_t xRet;

    എങ്കിൽ( !handle )
    {
        തിരികെ OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreTake( ( SemaphoreHandle_t ) handle,
                           ( timeout == OS_WRAPPER_WAIT_FOREVER ) ?
                           portMAX_DELAY : ( TickType_t ) timeout );

    എങ്കിൽ( xRet != pdPASS )
    {
        തിരികെ OS_WRAPPER_ERROR;
    }
    അല്ലെങ്കിൽ
    {
        തിരികെ OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_release( ശൂന്യം * handle )
{
    BaseType_t xRet;

    എങ്കിൽ( !handle )
    {
        തിരികെ OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreGive( ( SemaphoreHandle_t ) handle );

    എങ്കിൽ( xRet != pdPASS )
    {
        തിരികെ OS_WRAPPER_ERROR;
    }
    അല്ലെങ്കിൽ
    {
        തിരികെ OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_delete( ശൂന്യം * handle )
{
    vSemaphoreDelete( ( SemaphoreHandle_t ) handle );

    തിരികെ OS_WRAPPER_SUCCESS;
}
/*-----------------------------------------------------------*/
