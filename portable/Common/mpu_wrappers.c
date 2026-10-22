/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*
 * Implementation of the wrapper functions used to raise the processor privilege
 * before calling a standard FreeRTOS API function.
 */

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "queue.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "timers.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "event_groups.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stream_buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_prototypes.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ਜੇ ( ( ਪੋਰਟ_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #ਗਲਤੀ Access control list is not ਉਪਲਬਧ with this MPU wrapper. Please ਸੈੱਟ configENABLE_ACCESS_CONTROL_LIST ਮੰਜ਼ਿਲ 0.
    #ਜੇ_ਅੰਤ

    #ਜੇ ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 )
        ਅਧਾਰ_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_ਕੋਡ,
                                    ਅਚਲ ਅੱਖਰ * ਅਚਲ pcName,
                                    ਅਚਲ config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ux_ਢੇਰ_ਡੂੰਘਾਈ,
                                    ਖਾਲੀ * pvParameters,
                                    UBaseType_t ux_ਤਰਜੀਹ,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ux_ਤਰਜੀਹ = ux_ਤਰਜੀਹ & ~( ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTaskCreate( pv_Task_ਕੋਡ, pcName, ux_ਢੇਰ_ਡੂੰਘਾਈ, pvParameters, ux_ਤਰਜੀਹ, pxCreatedTask );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskCreate( pv_Task_ਕੋਡ, pcName, ux_ਢੇਰ_ਡੂੰਘਾਈ, pvParameters, ux_ਤਰਜੀਹ, pxCreatedTask );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_ਕੋਡ,
                                            ਅਚਲ ਅੱਖਰ * ਅਚਲ pcName,
                                            ਅਚਲ config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ux_ਢੇਰ_ਡੂੰਘਾਈ,
                                            ਖਾਲੀ * ਅਚਲ pvParameters,
                                            UBaseType_t ux_ਤਰਜੀਹ,
                                            ਢੇਰ_Type_t * ਅਚਲ pux_ਢੇਰ_ਬਫਰ,
                                            StaticTask_t * ਅਚਲ px_Task_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ux_ਤਰਜੀਹ = ux_ਤਰਜੀਹ & ~( ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTaskCreateStatic( px_Task_ਕੋਡ, pcName, ux_ਢੇਰ_ਡੂੰਘਾਈ, pvParameters, ux_ਤਰਜੀਹ, pux_ਢੇਰ_ਬਫਰ, px_Task_ਬਫਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskCreateStatic( px_Task_ਕੋਡ, pcName, ux_ਢੇਰ_ਡੂੰਘਾਈ, pvParameters, ux_ਤਰਜੀਹ, pux_ਢੇਰ_ਬਫਰ, px_Task_ਬਫਰ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskDelete == 1 )
        ਖਾਲੀ MPU_vTaskDelete( TaskHandle_t px_Task_ਮੰਜ਼ਿਲ_Delete ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                vTaskDelete( px_Task_ਮੰਜ਼ਿਲ_Delete );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                vTaskDelete( px_Task_ਮੰਜ਼ਿਲ_Delete );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskDelayUntil == 1 )
        ਅਧਾਰ_Type_t MPU_xTaskDelayUntil( TickType_t * ਅਚਲ px_ਪਿਛਲਾ_Wake_ਸਮਾਂ,
                                        TickType_t x_ਸਮਾਂ_Increment ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTaskDelayUntil( px_ਪਿਛਲਾ_Wake_ਸਮਾਂ, x_ਸਮਾਂ_Increment );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskDelayUntil( px_ਪਿਛਲਾ_Wake_ਸਮਾਂ, x_ਸਮਾਂ_Increment );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskAbortDelay == 1 )
        ਅਧਾਰ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskDelay == 1 )
        ਖਾਲੀ MPU_vTaskDelay( TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Delay ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                vTaskDelay( x_Ticks_ਮੰਜ਼ਿਲ_Delay );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                vTaskDelay( x_Ticks_ਮੰਜ਼ਿਲ_Delay );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_ਤਰਜੀਹ_Get == 1 )
        UBaseType_t MPU_ux_Task_ਤਰਜੀਹ_Get( ਅਚਲ TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                uxReturn = ux_Task_ਤਰਜੀਹ_Get( pxTask );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                uxReturn = ux_Task_ਤਰਜੀਹ_Get( pxTask );
            }

            ਵਾਪਸ uxReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_v_Task_ਤਰਜੀਹ_ਸੈੱਟ == 1 )
        ਖਾਲੀ MPU_v_Task_ਤਰਜੀਹ_ਸੈੱਟ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ਤਰਜੀਹ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                v_Task_ਤਰਜੀਹ_ਸੈੱਟ( pxTask, ux_New_ਤਰਜੀਹ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                v_Task_ਤਰਜੀਹ_ਸੈੱਟ( pxTask, ux_New_ਤਰਜੀਹ );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                eReturn = eTaskGetState( pxTask );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                eReturn = eTaskGetState( pxTask );
            }

            ਵਾਪਸ eReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TRACE_FACILITY == 1 )
        ਖਾਲੀ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_ਸਥਿਤੀ_t * px_Task_ਸਥਿਤੀ,
                               ਅਧਾਰ_Type_t x_Get_Free_ਢੇਰ_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                vTaskGetInfo( xTask, px_Task_ਸਥਿਤੀ, x_Get_Free_ਢੇਰ_Space, eState );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                vTaskGetInfo( xTask, px_Task_ਸਥਿਤੀ, x_Get_Free_ਢੇਰ_Space, eState );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskSuspend == 1 )
        ਖਾਲੀ MPU_vTaskSuspend( TaskHandle_t px_Task_ਮੰਜ਼ਿਲ_Suspend ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                vTaskSuspend( px_Task_ਮੰਜ਼ਿਲ_Suspend );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                vTaskSuspend( px_Task_ਮੰਜ਼ਿਲ_Suspend );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskSuspend == 1 )
        ਖਾਲੀ MPU_vTaskResume( TaskHandle_t px_Task_ਮੰਜ਼ਿਲ_Resume ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                vTaskResume( px_Task_ਮੰਜ਼ਿਲ_Resume );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                vTaskResume( px_Task_ਮੰਜ਼ਿਲ_Resume );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    ਖਾਲੀ MPU_vTaskSuspendAll( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
    {
        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            vTaskSuspendAll();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_xTaskResumeAll( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
    {
        ਅਧਾਰ_Type_t xReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            xReturn = xTaskResumeAll();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            xReturn = xTaskResumeAll();
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ਗਿਣਤੀ( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            xReturn = x_Task_Get_Tick_ਗਿਣਤੀ();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            xReturn = x_Task_Get_Tick_ਗਿਣਤੀ();
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            uxReturn = ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            uxReturn = ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks();
        }

        ਵਾਪਸ uxReturn;
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( ਅਚਲ ਅੱਖਰ * pc_Name_ਮੰਜ਼ਿਲ_Query ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTaskGetHandle( pc_Name_ਮੰਜ਼ਿਲ_Query );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskGetHandle( pc_Name_ਮੰਜ਼ਿਲ_Query );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) )
        ਖਾਲੀ MPU_vTaskListTasks( ਅੱਖਰ * pc_Write_ਬਫਰ,
                                 size_t ux_ਬਫਰ_ਲੰਮਾਈ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                vTaskListTasks( pc_Write_ਬਫਰ, ux_ਬਫਰ_ਲੰਮਾਈ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                vTaskListTasks( pc_Write_ਬਫਰ, ux_ਬਫਰ_ਲੰਮਾਈ );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) )
        ਖਾਲੀ MPU_v_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Statistics( ਅੱਖਰ * pc_Write_ਬਫਰ,
                                            size_t ux_ਬਫਰ_ਲੰਮਾਈ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                v_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Statistics( pc_Write_ਬਫਰ, ux_ਬਫਰ_ਲੰਮਾਈ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                v_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Statistics( pc_Write_ਬਫਰ, ux_ਬਫਰ_ਲੰਮਾਈ );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent();
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter();
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )
        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( TaskHandle_t xTask,
                                             TaskHookFunction_t px_ਟੈਗ_ਮੁੱਲ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( xTask, px_ਟੈਗ_ਮੁੱਲ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( xTask, px_ਟੈਗ_ਮੁੱਲ );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )
        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ਟੈਗ( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_Task_Get_Application_Task_ਟੈਗ( xTask );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_Task_Get_Application_Task_ਟੈਗ( xTask );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ != 0 )
        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                                    ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ,
                                                    ਖਾਲੀ * pv_ਮੁੱਲ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ( x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ, x_ਸੂਚਕਾਂਕ, pv_ਮੁੱਲ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ( x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ, x_ਸੂਚਕਾਂਕ, pv_ਮੁੱਲ );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ != 0 )
        ਖਾਲੀ * MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Query,
                                                       ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਖਾਲੀ * pvReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                pvReturn = pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( x_Task_ਮੰਜ਼ਿਲ_Query, x_ਸੂਚਕਾਂਕ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( x_Task_ਮੰਜ਼ਿਲ_Query, x_ਸੂਚਕਾਂਕ );
            }

            ਵਾਪਸ pvReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )
        ਅਧਾਰ_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     ਖਾਲੀ * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( Task_ਸਥਿਤੀ_t * px_Task_ਸਥਿਤੀ_Array,
                                              UBaseType_t ux_Array_ਮਾਪ,
                                              config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE * pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                uxReturn = uxTaskGetSystemState( px_Task_ਸਥਿਤੀ_Array, ux_Array_ਮਾਪ, pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                uxReturn = uxTaskGetSystemState( px_Task_ਸਥਿਤੀ_Array, ux_Array_ਮਾਪ, pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ );
            }

            ਵਾਪਸ uxReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_Task_Catch_ਉੱਪਰ_Ticks( TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Catch_ਉੱਪਰ ) /* FREERTOS_SYSTEM_CALL */
    {
        ਅਧਾਰ_Type_t xReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            xReturn = x_Task_Catch_ਉੱਪਰ_Ticks( x_Ticks_ਮੰਜ਼ਿਲ_Catch_ਉੱਪਰ );
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            xReturn = x_Task_Catch_ਉੱਪਰ_Ticks( x_Ticks_ਮੰਜ਼ਿਲ_Catch_ਉੱਪਰ );
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                uxReturn = ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark( xTask );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                uxReturn = ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark( xTask );
            }

            ਵਾਪਸ uxReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2 == 1 )
        config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE uxReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                uxReturn = ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2( xTask );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                uxReturn = ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2( xTask );
            }

            ਵਾਪਸ uxReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskGetSchedulerState == 1 )
        ਅਧਾਰ_Type_t MPU_xTaskGetSchedulerState( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTaskGetSchedulerState();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskGetSchedulerState();
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ ) /* FREERTOS_SYSTEM_CALL */
    {
        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State( px_ਸਮਾਂ_ਬਾਹਰਲਾ );
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State( px_ਸਮਾਂ_ਬਾਹਰਲਾ );
        }
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ,
                                         TickType_t * ਅਚਲ px_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ਅਧਾਰ_Type_t xReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            xReturn = x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ( px_ਸਮਾਂ_ਬਾਹਰਲਾ, px_Ticks_ਮੰਜ਼ਿਲ_Wait );
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            xReturn = x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ( px_ਸਮਾਂ_ਬਾਹਰਲਾ, px_Ticks_ਮੰਜ਼ਿਲ_Wait );
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )
        ਅਧਾਰ_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Notify,
                                           UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify,
                                           uint32_t ul_ਮੁੱਲ,
                                           eNotifyAction eAction,
                                           uint32_t * pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTaskGenericNotify( x_Task_ਮੰਜ਼ਿਲ_Notify, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify, ul_ਮੁੱਲ, eAction, pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskGenericNotify( x_Task_ਮੰਜ਼ਿਲ_Notify, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify, ul_ਮੁੱਲ, eAction, pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )
        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On,
                                               uint32_t ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_ਇੰਦਰਾਜ,
                                               uint32_t ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_Exit,
                                               uint32_t * pul_Notification_ਮੁੱਲ,
                                               TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTaskGenericNotifyWait( ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On, ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_ਇੰਦਰਾਜ, ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_Exit, pul_Notification_ਮੁੱਲ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskGenericNotifyWait( ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On, ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_ਇੰਦਰਾਜ, ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_Exit, pul_Notification_ਮੁੱਲ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On,
                                              ਅਧਾਰ_Type_t x_Clear_ਗਿਣਤੀ_On_Exit,
                                              TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On, x_Clear_ਗਿਣਤੀ_On_Exit, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                ulReturn = ulTaskGenericNotifyTake( ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On, x_Clear_ਗਿਣਤੀ_On_Exit, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
            }

            ਵਾਪਸ ulReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )
        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear,
                                                    uint32_t ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ulReturn = ul_Task_Generic_Notify_ਮੁੱਲ_Clear( xTask, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear, ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                ulReturn = ul_Task_Generic_Notify_ਮੁੱਲ_Clear( xTask, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear, ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear );
            }

            ਵਾਪਸ ulReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 )
        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Generic_Create( UBaseType_t ux_ਕਤਾਰ_ਲੰਮਾਈ,
                                               UBaseType_t ux_ਵਸਤੂ_ਮਾਪ,
                                               uint8_t uc_ਕਤਾਰ_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            ਕਤਾਰ_Handle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Generic_Create( ux_ਕਤਾਰ_ਲੰਮਾਈ, ux_ਵਸਤੂ_ਮਾਪ, uc_ਕਤਾਰ_Type );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Generic_Create( ux_ਕਤਾਰ_ਲੰਮਾਈ, ux_ਵਸਤੂ_ਮਾਪ, uc_ਕਤਾਰ_Type );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 )
        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Generic_Create_Static( ਅਚਲ UBaseType_t ux_ਕਤਾਰ_ਲੰਮਾਈ,
                                                     ਅਚਲ UBaseType_t ux_ਵਸਤੂ_ਮਾਪ,
                                                     uint8_t * puc_ਕਤਾਰ_Storage,
                                                     Static_ਕਤਾਰ_t * px_Static_ਕਤਾਰ,
                                                     ਅਚਲ uint8_t uc_ਕਤਾਰ_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            ਕਤਾਰ_Handle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Generic_Create_Static( ux_ਕਤਾਰ_ਲੰਮਾਈ, ux_ਵਸਤੂ_ਮਾਪ, puc_ਕਤਾਰ_Storage, px_Static_ਕਤਾਰ, uc_ਕਤਾਰ_Type );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Generic_Create_Static( ux_ਕਤਾਰ_ਲੰਮਾਈ, ux_ਵਸਤੂ_ਮਾਪ, puc_ਕਤਾਰ_Storage, px_Static_ਕਤਾਰ, uc_ਕਤਾਰ_Type );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Generic_Reset( ਕਤਾਰ_Handle_t px_ਕਤਾਰ,
                                       ਅਧਾਰ_Type_t x_New_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
    {
        ਅਧਾਰ_Type_t xReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            xReturn = x_ਕਤਾਰ_Generic_Reset( px_ਕਤਾਰ, x_New_ਕਤਾਰ );
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            xReturn = x_ਕਤਾਰ_Generic_Reset( px_ਕਤਾਰ, x_New_ਕਤਾਰ );
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Generic_Send( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                      ਅਚਲ ਖਾਲੀ * ਅਚਲ pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ,
                                      TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait,
                                      ਅਧਾਰ_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        ਅਧਾਰ_Type_t xReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            xReturn = x_ਕਤਾਰ_Generic_Send( x_ਕਤਾਰ, pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ, x_Ticks_ਮੰਜ਼ਿਲ_Wait, xCopyPosition );
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            xReturn = x_ਕਤਾਰ_Generic_Send( x_ਕਤਾਰ, pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ, x_Ticks_ਮੰਜ਼ਿਲ_Wait, xCopyPosition );
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ( ਅਚਲ ਕਤਾਰ_Handle_t px_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            uxReturn = ux_ਕਤਾਰ_Messages_ਉਡੀਕ( px_ਕਤਾਰ );
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            uxReturn = ux_ਕਤਾਰ_Messages_ਉਡੀਕ( px_ਕਤਾਰ );
        }

        ਵਾਪਸ uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            uxReturn = ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ( x_ਕਤਾਰ );
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            uxReturn = ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ( x_ਕਤਾਰ );
        }

        ਵਾਪਸ uxReturn;
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Receive( ਕਤਾਰ_Handle_t px_ਕਤਾਰ,
                                  ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                  TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ਅਧਾਰ_Type_t xReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            xReturn = x_ਕਤਾਰ_Receive( px_ਕਤਾਰ, pv_ਬਫਰ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            xReturn = x_ਕਤਾਰ_Receive( px_ਕਤਾਰ, pv_ਬਫਰ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Peek( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                               ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                               TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ਅਧਾਰ_Type_t xReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            xReturn = x_ਕਤਾਰ_Peek( x_ਕਤਾਰ, pv_ਬਫਰ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            xReturn = x_ਕਤਾਰ_Peek( x_ਕਤਾਰ, pv_ਬਫਰ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Semaphore_Take( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                        TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ਅਧਾਰ_Type_t xReturn;

        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            xReturn = x_ਕਤਾਰ_Semaphore_Take( x_ਕਤਾਰ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            xReturn = x_ਕਤਾਰ_Semaphore_Take( x_ਕਤਾਰ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_x_ਕਤਾਰ_Get_Mutex_Holder( ਕਤਾਰ_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            ਖਾਲੀ * xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Get_Mutex_Holder( xSemaphore );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Get_Mutex_Holder( xSemaphore );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) )
        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Create_Mutex( ਅਚਲ uint8_t uc_ਕਤਾਰ_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            ਕਤਾਰ_Handle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Create_Mutex( uc_ਕਤਾਰ_Type );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Create_Mutex( uc_ਕਤਾਰ_Type );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) )
        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Create_Mutex_Static( ਅਚਲ uint8_t uc_ਕਤਾਰ_Type,
                                                   Static_ਕਤਾਰ_t * px_Static_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਕਤਾਰ_Handle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Create_Mutex_Static( uc_ਕਤਾਰ_Type, px_Static_ਕਤਾਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Create_Mutex_Static( uc_ਕਤਾਰ_Type, px_Static_ਕਤਾਰ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) )
        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Create_Counting_Semaphore( UBaseType_t ux_ਗਿਣਤੀ_ਮੁੱਲ,
                                                         UBaseType_t ux_Initial_ਗਿਣਤੀ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਕਤਾਰ_Handle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Create_Counting_Semaphore( ux_ਗਿਣਤੀ_ਮੁੱਲ, ux_Initial_ਗਿਣਤੀ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Create_Counting_Semaphore( ux_ਗਿਣਤੀ_ਮੁੱਲ, ux_Initial_ਗਿਣਤੀ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) )

        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Create_Counting_Semaphore_Static( ਅਚਲ UBaseType_t ux_Max_ਗਿਣਤੀ,
                                                               ਅਚਲ UBaseType_t ux_Initial_ਗਿਣਤੀ,
                                                               Static_ਕਤਾਰ_t * px_Static_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਕਤਾਰ_Handle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Create_Counting_Semaphore_Static( ux_Max_ਗਿਣਤੀ, ux_Initial_ਗਿਣਤੀ, px_Static_ਕਤਾਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Create_Counting_Semaphore_Static( ux_Max_ਗਿਣਤੀ, ux_Initial_ਗਿਣਤੀ, px_Static_ਕਤਾਰ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_RECURSIVE_MUTEXES == 1 )
        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Take_Mutex_Recursive( ਕਤਾਰ_Handle_t xMutex,
                                                 TickType_t x_ਖੰਡ_ਸਮਾਂ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Take_Mutex_Recursive( xMutex, x_ਖੰਡ_ਸਮਾਂ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Take_Mutex_Recursive( xMutex, x_ਖੰਡ_ਸਮਾਂ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_RECURSIVE_MUTEXES == 1 )
        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Give_Mutex_Recursive( ਕਤਾਰ_Handle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Give_Mutex_Recursive( xMutex );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Give_Mutex_Recursive( xMutex );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_USE_ਕਤਾਰ_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) )
        ਕਤਾਰ_ਸੈੱਟ_Handle_t MPU_x_ਕਤਾਰ_Create_ਸੈੱਟ( UBaseType_t ux_Event_ਕਤਾਰ_ਲੰਮਾਈ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਕਤਾਰ_ਸੈੱਟ_Handle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Create_ਸੈੱਟ( ux_Event_ਕਤਾਰ_ਲੰਮਾਈ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Create_ਸੈੱਟ( ux_Event_ਕਤਾਰ_ਲੰਮਾਈ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_USE_ਕਤਾਰ_SETS == 1 ) && ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) )
        ਕਤਾਰ_ਸੈੱਟ_Handle_t MPU_x_ਕਤਾਰ_Create_ਸੈੱਟ_Static( ਅਚਲ UBaseType_t ux_Event_ਕਤਾਰ_ਲੰਮਾਈ,
                                                    uint8_t * puc_ਕਤਾਰ_Storage,
                                                    Static_ਕਤਾਰ_t * px_Static_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਕਤਾਰ_ਸੈੱਟ_Handle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Create_ਸੈੱਟ_Static( ux_Event_ਕਤਾਰ_ਲੰਮਾਈ, puc_ਕਤਾਰ_Storage, px_Static_ਕਤਾਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Create_ਸੈੱਟ_Static( ux_Event_ਕਤਾਰ_ਲੰਮਾਈ, puc_ਕਤਾਰ_Storage, px_Static_ਕਤਾਰ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )
        ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ,
                                                        TickType_t x_ਖੰਡ_ਸਮਾਂ_Ticks ) /* FREERTOS_SYSTEM_CALL */
        {
            ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Select_From_ਸੈੱਟ( x_ਕਤਾਰ_ਸੈੱਟ, x_ਖੰਡ_ਸਮਾਂ_Ticks );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Select_From_ਸੈੱਟ( x_ਕਤਾਰ_ਸੈੱਟ, x_ਖੰਡ_ਸਮਾਂ_Ticks );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )
        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਕਤਾਰ_Or_Semaphore,
                                       ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ( x_ਕਤਾਰ_Or_Semaphore, x_ਕਤਾਰ_ਸੈੱਟ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ( x_ਕਤਾਰ_Or_Semaphore, x_ਕਤਾਰ_ਸੈੱਟ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )
        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Remove_From_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਕਤਾਰ_Or_Semaphore,
                                            ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਕਤਾਰ_Remove_From_ਸੈੱਟ( x_ਕਤਾਰ_Or_Semaphore, x_ਕਤਾਰ_ਸੈੱਟ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਕਤਾਰ_Remove_From_ਸੈੱਟ( x_ਕਤਾਰ_Or_Semaphore, x_ਕਤਾਰ_ਸੈੱਟ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0
        ਖਾਲੀ MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                      ਅਚਲ ਅੱਖਰ * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry( x_ਕਤਾਰ, pcName );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry( x_ਕਤਾਰ, pcName );
            }
        }
    #ਜੇ_ਅੰਤ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ਜੇ config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0
        ਖਾਲੀ MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                v_ਕਤਾਰ_Unregister_ਕਤਾਰ( x_ਕਤਾਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                v_ਕਤਾਰ_Unregister_ਕਤਾਰ( x_ਕਤਾਰ );
            }
        }
    #ਜੇ_ਅੰਤ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ਜੇ config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0
        ਅਚਲ ਅੱਖਰ * MPU_pc_ਕਤਾਰ_Get_Name( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਚਲ ਅੱਖਰ * pcReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                pcReturn = pc_ਕਤਾਰ_Get_Name( x_ਕਤਾਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                pcReturn = pc_ਕਤਾਰ_Get_Name( x_ਕਤਾਰ );
            }

            ਵਾਪਸ pcReturn;
        }
    #ਜੇ_ਅੰਤ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    ਖਾਲੀ MPU_v_ਕਤਾਰ_Delete( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
    {
        ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
        {
            ਪੋਰਟ_RAISE_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            v_ਕਤਾਰ_Delete( x_ਕਤਾਰ );
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

            ਪੋਰਟ_RESET_PRIVILEGE();
            ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
        }
        ਨਹੀਂਤਾਂ
        {
            v_ਕਤਾਰ_Delete( x_ਕਤਾਰ );
        }
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )
        ਖਾਲੀ * MPU_pvTimerGetTimerID( ਅਚਲ TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ਖਾਲੀ * pvReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            ਵਾਪਸ pvReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )
        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Timer_ID( TimerHandle_t xTimer,
                                   ਖਾਲੀ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                v_Timer_ਸੈੱਟ_Timer_ID( xTimer, pvNewID );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                v_Timer_ਸੈੱਟ_Timer_ID( xTimer, pvNewID );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )
        ਅਧਾਰ_Type_t MPU_x_Timer_Is_Timer_ਸਰਗਰਮ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_Timer_Is_Timer_ਸਰਗਰਮ( xTimer );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_Timer_Is_Timer_ਸਰਗਰਮ( xTimer );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )
        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer,
                                      ਅਚਲ ਅਧਾਰ_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ( xTimer, xAutoReload );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ( xTimer, xAutoReload );
            }
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                uxReturn = ux_Timer_Get_Reload_ਬਹੁਲਕ( xTimer );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                uxReturn = ux_Timer_Get_Reload_ਬਹੁਲਕ( xTimer );
            }

            ਵਾਪਸ uxReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )
        ਅਚਲ ਅੱਖਰ * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਚਲ ਅੱਖਰ * pcReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            ਵਾਪਸ pcReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )
        TickType_t MPU_x_Timer_Get_Expiry_ਸਮਾਂ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_Timer_Get_Expiry_ਸਮਾਂ( xTimer );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_Timer_Get_Expiry_ਸਮਾਂ( xTimer );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )
        ਅਧਾਰ_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ਅਚਲ ਅਧਾਰ_Type_t xCommandID,
                                                     ਅਚਲ TickType_t x_Optional_ਮੁੱਲ,
                                                     ਅਧਾਰ_Type_t * ਅਚਲ px_Higher_ਤਰਜੀਹ_Task_Woken,
                                                     ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_ਮੁੱਲ, px_Higher_ਤਰਜੀਹ_Task_Woken, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_ਮੁੱਲ, px_Higher_ਤਰਜੀਹ_Task_Woken, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_ਸਮੂਹ_Handle_t MPU_x_Event_ਸਮੂਹ_Create( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ਸਮੂਹ_Handle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_Event_ਸਮੂਹ_Create();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_Event_ਸਮੂਹ_Create();
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_ਸਮੂਹ_Handle_t MPU_x_Event_ਸਮੂਹ_Create_Static( Static_Event_ਸਮੂਹ_t * px_Event_ਸਮੂਹ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ਸਮੂਹ_Handle_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_Event_ਸਮੂਹ_Create_Static( px_Event_ਸਮੂਹ_ਬਫਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_Event_ਸਮੂਹ_Create_Static( px_Event_ਸਮੂਹ_ਬਫਰ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )
        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                             ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For,
                                             ਅਚਲ ਅਧਾਰ_Type_t xClearOnExit,
                                             ਅਚਲ ਅਧਾਰ_Type_t x_Wait_For_All_ਬਿੱਟ,
                                             TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ਬਿੱਟ_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ( x_Event_ਸਮੂਹ, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For, xClearOnExit, x_Wait_For_All_ਬਿੱਟ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ( x_Event_ਸਮੂਹ, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For, xClearOnExit, x_Wait_For_All_ਬਿੱਟ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )
        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                              ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ਬਿੱਟ_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ( x_Event_ਸਮੂਹ, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ( x_Event_ਸਮੂਹ, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )
        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                            ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ਬਿੱਟ_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ( x_Event_ਸਮੂਹ, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ( x_Event_ਸਮੂਹ, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )
        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Sync( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                         ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                         ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For,
                                         TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ਬਿੱਟ_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_Event_ਸਮੂਹ_Sync( x_Event_ਸਮੂਹ, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_Event_ਸਮੂਹ_Sync( x_Event_ਸਮੂਹ, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )
        ਖਾਲੀ MPU_v_Event_ਸਮੂਹ_Delete( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                v_Event_ਸਮੂਹ_Delete( x_Event_ਸਮੂਹ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                v_Event_ਸਮੂਹ_Delete( x_Event_ਸਮੂਹ );
            }
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Send( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                      ਅਚਲ ਖਾਲੀ * pv_Tx_ਅੰਕੜੇ,
                                      size_t x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                      TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਧਾਰਾ_ਬਫਰ_Send( x_ਧਾਰਾ_ਬਫਰ, pv_Tx_ਅੰਕੜੇ, x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਧਾਰਾ_ਬਫਰ_Send( x_ਧਾਰਾ_ਬਫਰ, pv_Tx_ਅੰਕੜੇ, x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ( x_ਧਾਰਾ_ਬਫਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ( x_ਧਾਰਾ_ਬਫਰ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Receive( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                         ਖਾਲੀ * pv_Rx_ਅੰਕੜੇ,
                                         size_t x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                         TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਧਾਰਾ_ਬਫਰ_Receive( x_ਧਾਰਾ_ਬਫਰ, pv_Rx_ਅੰਕੜੇ, x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਧਾਰਾ_ਬਫਰ_Receive( x_ਧਾਰਾ_ਬਫਰ, pv_Rx_ਅੰਕੜੇ, x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
        ਖਾਲੀ MPU_v_ਧਾਰਾ_ਬਫਰ_Delete( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                v_ਧਾਰਾ_ਬਫਰ_Delete( x_ਧਾਰਾ_ਬਫਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                v_ਧਾਰਾ_ਬਫਰ_Delete( x_ਧਾਰਾ_ਬਫਰ );
            }
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ( x_ਧਾਰਾ_ਬਫਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ( x_ਧਾਰਾ_ਬਫਰ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ( x_ਧਾਰਾ_ਬਫਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ( x_ਧਾਰਾ_ਬਫਰ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Reset( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਧਾਰਾ_ਬਫਰ_Reset( x_ਧਾਰਾ_ਬਫਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਧਾਰਾ_ਬਫਰ_Reset( x_ਧਾਰਾ_ਬਫਰ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
                xReturn = x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ( x_ਧਾਰਾ_ਬਫਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ( x_ਧਾਰਾ_ਬਫਰ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ( x_ਧਾਰਾ_ਬਫਰ );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ( x_ਧਾਰਾ_ਬਫਰ );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn;

            ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
            {
                ਪੋਰਟ_RAISE_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                xReturn = x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level( x_ਧਾਰਾ_ਬਫਰ, xTriggerLevel );
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                ਪੋਰਟ_RESET_PRIVILEGE();
                ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
            }
            ਨਹੀਂਤਾਂ
            {
                xReturn = x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level( x_ਧਾਰਾ_ਬਫਰ, xTriggerLevel );
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) && ( config_USE_ਧਾਰਾ_BUFFERS == 1 ) )
        ਧਾਰਾ_ਬਫਰ_Handle_t MPU_x_ਧਾਰਾ_ਬਫਰ_Generic_Create( size_t x_ਬਫਰ_ਮਾਪ_ਬਾਈਟਾਂ,
                                                             size_t x_Trigger_Level_ਬਾਈਟਾਂ,
                                                             ਅਧਾਰ_Type_t x_ਧਾਰਾ_ਬਫਰ_Type,
                                                             ਧਾਰਾ_ਬਫਰ_Callback_Function_t pxSendCompletedCallback,
                                                             ਧਾਰਾ_ਬਫਰ_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            ਧਾਰਾ_ਬਫਰ_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ਨਿਰਾ ) &&
                          ( pxReceiveCompletedCallback == ਨਿਰਾ ) );

            ਜੇ( ( pxSendCompletedCallback == ਨਿਰਾ ) &&
                ( pxReceiveCompletedCallback == ਨਿਰਾ ) )
            {
                ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
                {
                    ਪੋਰਟ_RAISE_PRIVILEGE();
                    ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                    xReturn = x_ਧਾਰਾ_ਬਫਰ_Generic_Create( x_ਬਫਰ_ਮਾਪ_ਬਾਈਟਾਂ,
                                                          x_Trigger_Level_ਬਾਈਟਾਂ,
                                                          x_ਧਾਰਾ_ਬਫਰ_Type,
                                                          ਨਿਰਾ,
                                                          ਨਿਰਾ );
                    ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                    ਪੋਰਟ_RESET_PRIVILEGE();
                    ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
                }
                ਨਹੀਂਤਾਂ
                {
                    xReturn = x_ਧਾਰਾ_ਬਫਰ_Generic_Create( x_ਬਫਰ_ਮਾਪ_ਬਾਈਟਾਂ,
                                                          x_Trigger_Level_ਬਾਈਟਾਂ,
                                                          x_ਧਾਰਾ_ਬਫਰ_Type,
                                                          ਨਿਰਾ,
                                                          ਨਿਰਾ );
                }
            }
            ਨਹੀਂਤਾਂ
            {
                trace_ਧਾਰਾ_ਬਫਰ_CREATE_FAILED( x_ਧਾਰਾ_ਬਫਰ_Type );
                xReturn = ਨਿਰਾ;
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) && ( config_USE_ਧਾਰਾ_BUFFERS == 1 ) )
        ਧਾਰਾ_ਬਫਰ_Handle_t MPU_x_ਧਾਰਾ_ਬਫਰ_Generic_Create_Static( size_t x_ਬਫਰ_ਮਾਪ_ਬਾਈਟਾਂ,
                                                                   size_t x_Trigger_Level_ਬਾਈਟਾਂ,
                                                                   ਅਧਾਰ_Type_t x_ਧਾਰਾ_ਬਫਰ_Type,
                                                                   uint8_t * ਅਚਲ puc_ਧਾਰਾ_ਬਫਰ_Storage_Area,
                                                                   Static_ਧਾਰਾ_ਬਫਰ_t * ਅਚਲ px_Static_ਧਾਰਾ_ਬਫਰ,
                                                                   ਧਾਰਾ_ਬਫਰ_Callback_Function_t pxSendCompletedCallback,
                                                                   ਧਾਰਾ_ਬਫਰ_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            ਧਾਰਾ_ਬਫਰ_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ਨਿਰਾ ) &&
                          ( pxReceiveCompletedCallback == ਨਿਰਾ ) );

            ਜੇ( ( pxSendCompletedCallback == ਨਿਰਾ ) &&
                ( pxReceiveCompletedCallback == ਨਿਰਾ ) )
            {
                ਜੇ( ਪੋਰਟ_IS_PRIVILEGED() == pdFALSE )
                {
                    ਪੋਰਟ_RAISE_PRIVILEGE();
                    ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                    xReturn = x_ਧਾਰਾ_ਬਫਰ_Generic_Create_Static( x_ਬਫਰ_ਮਾਪ_ਬਾਈਟਾਂ,
                                                                x_Trigger_Level_ਬਾਈਟਾਂ,
                                                                x_ਧਾਰਾ_ਬਫਰ_Type,
                                                                puc_ਧਾਰਾ_ਬਫਰ_Storage_Area,
                                                                px_Static_ਧਾਰਾ_ਬਫਰ,
                                                                ਨਿਰਾ,
                                                                ਨਿਰਾ );
                    ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();

                    ਪੋਰਟ_RESET_PRIVILEGE();
                    ਪੋਰਟ_ਸਮ੍ਰਿਤੀ_BARRIER();
                }
                ਨਹੀਂਤਾਂ
                {
                    xReturn = x_ਧਾਰਾ_ਬਫਰ_Generic_Create_Static( x_ਬਫਰ_ਮਾਪ_ਬਾਈਟਾਂ,
                                                                x_Trigger_Level_ਬਾਈਟਾਂ,
                                                                x_ਧਾਰਾ_ਬਫਰ_Type,
                                                                puc_ਧਾਰਾ_ਬਫਰ_Storage_Area,
                                                                px_Static_ਧਾਰਾ_ਬਫਰ,
                                                                ਨਿਰਾ,
                                                                ਨਿਰਾ );
                }
            }
            ਨਹੀਂਤਾਂ
            {
                trace_ਧਾਰਾ_ਬਫਰ_CREATE_STATIC_FAILED( xReturn, x_ਧਾਰਾ_ਬਫਰ_Type );
                xReturn = ਨਿਰਾ;
            }

            ਵਾਪਸ xReturn;
        }
    #ਜੇ_ਅੰਤ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/


/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h.  The functions
 * must take the same format as those above whereby the privilege state on exit
 * equals the privilege state on entry.  For example:
 *
 * void MPU_FunctionName( [parameters ] ) FREERTOS_SYSTEM_CALL;
 * void MPU_FunctionName( [parameters ] )
 * {
 *      if( portIS_PRIVILEGED() == pdFALSE )
 *      {
 *          portRAISE_PRIVILEGE();
 *          portMEMORY_BARRIER();
 *
 *          FunctionName( [parameters ] );
 *          portMEMORY_BARRIER();
 *
 *          portRESET_PRIVILEGE();
 *          portMEMORY_BARRIER();
 *      }
 *      else
 *      {
 *          FunctionName( [parameters ] );
 *      }
 * }
 */

    #ਜੇ configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ਅਨ੍ਤਰ੍ਭਾਵ "application_defined_privileged_functions.h"
    #ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
