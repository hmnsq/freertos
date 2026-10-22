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

#ಯದಿ ( configSUPPORT_STATIC_ALLOCATION == 1 )

/*
 * In the static allocation, the RAM is required to hold the semaphore's
 * state.
 */
    StaticSemaphore_t xSecureMutexBuffer;
#endif

#ಯದಿ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
    bool os_wrapper_is_kernel_started( ಶೂನ್ಯ )
    {
        ಪ್ರತ್ಯಾಗಮ xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED;
    }
#endif

ಶೂನ್ಯ * os_wrapper_mutex_create( ಶೂನ್ಯ )
{
    SemaphoreHandle_t xMutexHandle = ರಿಕ್ತ;

    #ಯದಿ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        xMutexHandle = xSemaphoreCreateMutex();
    #ನೋಚೇದ್ಯದಿ ( configSUPPORT_STATIC_ALLOCATION == 1 )
        xMutexHandle = xSemaphoreCreateMutexStatic( &xSecureMutexBuffer );
    #endif
    ಪ್ರತ್ಯಾಗಮ ( ಶೂನ್ಯ * ) xMutexHandle;
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_acquire( ಶೂನ್ಯ * handle,
                                   uint32_t timeout )
{
    BaseType_t xRet;

    ಯದಿ( !handle )
    {
        ಪ್ರತ್ಯಾಗಮ OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreTake( ( SemaphoreHandle_t ) handle,
                           ( timeout == OS_WRAPPER_WAIT_FOREVER ) ?
                           portMAX_DELAY : ( TickType_t ) timeout );

    ಯದಿ( xRet != pdPASS )
    {
        ಪ್ರತ್ಯಾಗಮ OS_WRAPPER_ERROR;
    }
    ಅನ್ಯಥಾ
    {
        ಪ್ರತ್ಯಾಗಮ OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_release( ಶೂನ್ಯ * handle )
{
    BaseType_t xRet;

    ಯದಿ( !handle )
    {
        ಪ್ರತ್ಯಾಗಮ OS_WRAPPER_ERROR;
    }

    xRet = xSemaphoreGive( ( SemaphoreHandle_t ) handle );

    ಯದಿ( xRet != pdPASS )
    {
        ಪ್ರತ್ಯಾಗಮ OS_WRAPPER_ERROR;
    }
    ಅನ್ಯಥಾ
    {
        ಪ್ರತ್ಯಾಗಮ OS_WRAPPER_SUCCESS;
    }
}
/*-----------------------------------------------------------*/

uint32_t os_wrapper_mutex_delete( ಶೂನ್ಯ * handle )
{
    vSemaphoreDelete( ( SemaphoreHandle_t ) handle );

    ಪ್ರತ್ಯಾಗಮ OS_WRAPPER_SUCCESS;
}
/*-----------------------------------------------------------*/
