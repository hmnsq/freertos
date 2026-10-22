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
#تعریف_کړه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"

#تعریف_لغوه MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( ( پورټ_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #تېروتنه Access control list is not شته with this MPU wrapper. Please سېټ configENABLE_ACCESS_CONTROL_LIST منزل 0.
    #د_که_پای

    #إذا ( config_SUPPORT_DYNAMIC_ویش == 1 )
        بنسټ_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_کوډ,
                                    ثابت حرف * ثابت pcName,
                                    ثابت config_ډېری_ژوروالی_TYPE ux_ډېری_ژوروالی,
                                    فراغ * pvParameters,
                                    UBaseType_t ux_لومړیتوب,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                ux_لومړیتوب = ux_لومړیتوب & ~( پورټ_PRIVILEGE_بټ );
                پورټ_حافظه_BARRIER();

                xReturn = xTaskCreate( pv_Task_کوډ, pcName, ux_ډېری_ژوروالی, pvParameters, ux_لومړیتوب, pxCreatedTask );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCreate( pv_Task_کوډ, pcName, ux_ډېری_ژوروالی, pvParameters, ux_لومړیتوب, pxCreatedTask );
            }

            أرجع xReturn;
        }
    #د_که_پای /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ویش == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_کوډ,
                                            ثابت حرف * ثابت pcName,
                                            ثابت config_ډېری_ژوروالی_TYPE ux_ډېری_ژوروالی,
                                            فراغ * ثابت pvParameters,
                                            UBaseType_t ux_لومړیتوب,
                                            ډېری_Type_t * ثابت pux_ډېری_بفر,
                                            StaticTask_t * ثابت px_Task_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                ux_لومړیتوب = ux_لومړیتوب & ~( پورټ_PRIVILEGE_بټ );
                پورټ_حافظه_BARRIER();

                xReturn = xTaskCreateStatic( px_Task_کوډ, pcName, ux_ډېری_ژوروالی, pvParameters, ux_لومړیتوب, pux_ډېری_بفر, px_Task_بفر );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCreateStatic( px_Task_کوډ, pcName, ux_ډېری_ژوروالی, pvParameters, ux_لومړیتوب, pux_ډېری_بفر, px_Task_بفر );
            }

            أرجع xReturn;
        }
    #د_که_پای /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelete == 1 )
        فراغ MPU_vTaskDelete( TaskHandle_t px_Task_منزل_Delete ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                vTaskDelete( px_Task_منزل_Delete );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskDelete( px_Task_منزل_Delete );
            }
        }
    #د_که_پای /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )
        بنسټ_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پخوانی_Wake_وخت,
                                        TickType_t x_وخت_Increment ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = xTaskDelayUntil( px_پخوانی_Wake_وخت, x_وخت_Increment );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskDelayUntil( px_پخوانی_Wake_وخت, x_وخت_Increment );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )
        بنسټ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )
        فراغ MPU_vTaskDelay( TickType_t x_Ticks_منزل_Delay ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                vTaskDelay( x_Ticks_منزل_Delay );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskDelay( x_Ticks_منزل_Delay );
            }
        }
    #د_که_پای /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_لومړیتوب_Get == 1 )
        UBaseType_t MPU_ux_Task_لومړیتوب_Get( ثابت TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                uxReturn = ux_Task_لومړیتوب_Get( pxTask );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_لومړیتوب_Get( pxTask );
            }

            أرجع uxReturn;
        }
    #د_که_پای /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_v_Task_لومړیتوب_سېټ == 1 )
        فراغ MPU_v_Task_لومړیتوب_سېټ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_لومړیتوب ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                v_Task_لومړیتوب_سېټ( pxTask, ux_New_لومړیتوب );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                v_Task_لومړیتوب_سېټ( pxTask, ux_New_لومړیتوب );
            }
        }
    #د_که_پای /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                eReturn = eTaskGetState( pxTask );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                eReturn = eTaskGetState( pxTask );
            }

            أرجع eReturn;
        }
    #د_که_پای /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )
        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               بنسټ_Type_t x_Get_Free_ډېری_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ډېری_Space, eState );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ډېری_Space, eState );
            }
        }
    #د_که_پای /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )
        فراغ MPU_vTaskSuspend( TaskHandle_t px_Task_منزل_Suspend ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                vTaskSuspend( px_Task_منزل_Suspend );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskSuspend( px_Task_منزل_Suspend );
            }
        }
    #د_که_پای /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )
        فراغ MPU_vTaskResume( TaskHandle_t px_Task_منزل_Resume ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                vTaskResume( px_Task_منزل_Resume );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskResume( px_Task_منزل_Resume );
            }
        }
    #د_که_پای /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_vTaskSuspendAll( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            vTaskSuspendAll();
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_xTaskResumeAll( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        بنسټ_Type_t xReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            xReturn = xTaskResumeAll();
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = xTaskResumeAll();
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_شمېر( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            xReturn = x_Task_Get_Tick_شمېر();
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Get_Tick_شمېر();
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_شمېره_د_Tasks( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            uxReturn = ux_Task_Get_شمېره_د_Tasks();
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_Task_Get_شمېره_د_Tasks();
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( ثابت حرف * pc_Name_منزل_Query ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = xTaskGetHandle( pc_Name_منزل_Query );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetHandle( pc_Name_منزل_Query );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_ویش == 1 ) )
        فراغ MPU_vTaskListTasks( حرف * pc_Write_بفر,
                                 size_t ux_بفر_اوږدتیا ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                vTaskListTasks( pc_Write_بفر, ux_بفر_اوږدتیا );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskListTasks( pc_Write_بفر, ux_بفر_اوږدتیا );
            }
        }
    #د_که_پای /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پرلپسې_وخت_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_ویش == 1 ) )
        فراغ MPU_v_Task_Get_پرلپسې_وخت_Statistics( حرف * pc_Write_بفر,
                                            size_t ux_بفر_اوږدتیا ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                v_Task_Get_پرلپسې_وخت_Statistics( pc_Write_بفر, ux_بفر_اوږدتیا );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                v_Task_Get_پرلپسې_وخت_Statistics( pc_Write_بفر, ux_بفر_اوږدتیا );
            }
        }
    #د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پرلپسې_وخت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_پرلپسې_وخت_COUNTER_TYPE xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = ul_Task_Get_Idle_پرلپسې_وخت_Percent();
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = ul_Task_Get_Idle_پرلپسې_وخت_Percent();
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پرلپسې_وخت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_پرلپسې_وخت_COUNTER_TYPE xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = ul_Task_Get_Idle_پرلپسې_وخت_Counter();
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = ul_Task_Get_Idle_پرلپسې_وخت_Counter();
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_نښان == 1 )
        فراغ MPU_v_Task_سېټ_Application_Task_نښان( TaskHandle_t xTask,
                                             TaskHookFunction_t px_نښان_ارزښت ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                v_Task_سېټ_Application_Task_نښان( xTask, px_نښان_ارزښت );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                v_Task_سېټ_Application_Task_نښان( xTask, px_نښان_ارزښت );
            }
        }
    #د_که_پای /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_نښان == 1 )
        TaskHookFunction_t MPU_x_Task_Get_Application_Task_نښان( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_Task_Get_Application_Task_نښان( xTask );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Task_Get_Application_Task_نښان( xTask );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_اشارې != 0 )
        فراغ MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر( TaskHandle_t x_Task_منزل_سېټ,
                                                    بنسټ_Type_t x_شاخص,
                                                    فراغ * pv_ارزښت ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                v_Task_سېټ_Thread_Local_Storage_اشاره_ګر( x_Task_منزل_سېټ, x_شاخص, pv_ارزښت );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                v_Task_سېټ_Thread_Local_Storage_اشاره_ګر( x_Task_منزل_سېټ, x_شاخص, pv_ارزښت );
            }
        }
    #د_که_پای /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_اشارې != 0 )
        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر( TaskHandle_t x_Task_منزل_Query,
                                                       بنسټ_Type_t x_شاخص ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * pvReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                pvReturn = pv_Task_Get_Thread_Local_Storage_اشاره_ګر( x_Task_منزل_Query, x_شاخص );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_اشاره_ګر( x_Task_منزل_Query, x_شاخص );
            }

            أرجع pvReturn;
        }
    #د_که_پای /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_نښان == 1 )
        بنسټ_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     فراغ * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * px_Task_حالت_Array,
                                              UBaseType_t ux_Array_اندازه,
                                              config_پرلپسې_وخت_COUNTER_TYPE * pul_ټول_پرلپسې_وخت ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_اندازه, pul_ټول_پرلپسې_وخت );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_اندازه, pul_ټول_پرلپسې_وخت );
            }

            أرجع uxReturn;
        }
    #د_که_پای /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_Task_Catch_پورته_Ticks( TickType_t x_Ticks_منزل_Catch_پورته ) /* FREERTOS_SYSTEM_CALL */
    {
        بنسټ_Type_t xReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            xReturn = x_Task_Catch_پورته_Ticks( x_Ticks_منزل_Catch_پورته );
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Catch_پورته_Ticks( x_Ticks_منزل_Catch_پورته );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ډېری_لوړ_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_ډېری_لوړ_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                uxReturn = ux_Task_Get_ډېری_لوړ_Water_Mark( xTask );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_Get_ډېری_لوړ_Water_Mark( xTask );
            }

            أرجع uxReturn;
        }
    #د_که_پای /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ډېری_لوړ_Water_Mark2 == 1 )
        config_ډېری_ژوروالی_TYPE MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ډېری_ژوروالی_TYPE uxReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                uxReturn = ux_Task_Get_ډېری_لوړ_Water_Mark2( xTask );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_Get_ډېری_لوړ_Water_Mark2( xTask );
            }

            أرجع uxReturn;
        }
    #د_که_پای /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
        بنسټ_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = xTaskGetSchedulerState();
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetSchedulerState();
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_سېټ_وخت_بهر_State( وخت_بهر_t * ثابت px_وخت_بهر ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            v_Task_سېټ_وخت_بهر_State( px_وخت_بهر );
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            v_Task_سېټ_وخت_بهر_State( px_وخت_بهر );
        }
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_Task_Check_For_وخت_بهر( وخت_بهر_t * ثابت px_وخت_بهر,
                                         TickType_t * ثابت px_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنسټ_Type_t xReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            xReturn = x_Task_Check_For_وخت_بهر( px_وخت_بهر, px_Ticks_منزل_Wait );
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Check_For_وخت_بهر( px_وخت_بهر, px_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        بنسټ_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_منزل_Notify,
                                           UBaseType_t ux_شاخص_منزل_Notify,
                                           uint32_t ul_ارزښت,
                                           eNotifyAction eAction,
                                           uint32_t * pul_پخوانی_Notification_ارزښت ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = xTaskGenericNotify( x_Task_منزل_Notify, ux_شاخص_منزل_Notify, ul_ارزښت, eAction, pul_پخوانی_Notification_ارزښت );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotify( x_Task_منزل_Notify, ux_شاخص_منزل_Notify, ul_ارزښت, eAction, pul_پخوانی_Notification_ارزښت );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        بنسټ_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_شاخص_منزل_Wait_On,
                                               uint32_t ul_بټونه_منزل_Clear_On_ثبت,
                                               uint32_t ul_بټونه_منزل_Clear_On_Exit,
                                               uint32_t * pul_Notification_ارزښت,
                                               TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = xTaskGenericNotifyWait( ux_شاخص_منزل_Wait_On, ul_بټونه_منزل_Clear_On_ثبت, ul_بټونه_منزل_Clear_On_Exit, pul_Notification_ارزښت, x_Ticks_منزل_Wait );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotifyWait( ux_شاخص_منزل_Wait_On, ul_بټونه_منزل_Clear_On_ثبت, ul_بټونه_منزل_Clear_On_Exit, pul_Notification_ارزښت, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_شاخص_منزل_Wait_On,
                                              بنسټ_Type_t x_Clear_شمېر_On_Exit,
                                              TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( ux_شاخص_منزل_Wait_On, x_Clear_شمېر_On_Exit, x_Ticks_منزل_Wait );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                ulReturn = ulTaskGenericNotifyTake( ux_شاخص_منزل_Wait_On, x_Clear_شمېر_On_Exit, x_Ticks_منزل_Wait );
            }

            أرجع ulReturn;
        }
    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        بنسټ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_شاخص_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, ux_شاخص_منزل_Clear );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, ux_شاخص_منزل_Clear );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_ارزښت_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_شاخص_منزل_Clear,
                                                    uint32_t ul_بټونه_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                ulReturn = ul_Task_Generic_Notify_ارزښت_Clear( xTask, ux_شاخص_منزل_Clear, ul_بټونه_منزل_Clear );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                ulReturn = ul_Task_Generic_Notify_ارزښت_Clear( xTask, ux_شاخص_منزل_Clear, ul_بټونه_منزل_Clear );
            }

            أرجع ulReturn;
        }
    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ویش == 1 )
        کتار_Handle_t MPU_x_کتار_Generic_Create( UBaseType_t ux_کتار_اوږدتیا,
                                               UBaseType_t ux_توکی_اندازه,
                                               uint8_t uc_کتار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            کتار_Handle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Generic_Create( ux_کتار_اوږدتیا, ux_توکی_اندازه, uc_کتار_Type );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Generic_Create( ux_کتار_اوږدتیا, ux_توکی_اندازه, uc_کتار_Type );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ویش == 1 )
        کتار_Handle_t MPU_x_کتار_Generic_Create_Static( ثابت UBaseType_t ux_کتار_اوږدتیا,
                                                     ثابت UBaseType_t ux_توکی_اندازه,
                                                     uint8_t * puc_کتار_Storage,
                                                     Static_کتار_t * px_Static_کتار,
                                                     ثابت uint8_t uc_کتار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            کتار_Handle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Generic_Create_Static( ux_کتار_اوږدتیا, ux_توکی_اندازه, puc_کتار_Storage, px_Static_کتار, uc_کتار_Type );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Generic_Create_Static( ux_کتار_اوږدتیا, ux_توکی_اندازه, puc_کتار_Storage, px_Static_کتار, uc_کتار_Type );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Generic_Reset( کتار_Handle_t px_کتار,
                                       بنسټ_Type_t x_New_کتار ) /* FREERTOS_SYSTEM_CALL */
    {
        بنسټ_Type_t xReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            xReturn = x_کتار_Generic_Reset( px_کتار, x_New_کتار );
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_کتار_Generic_Reset( px_کتار, x_New_کتار );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Generic_Send( کتار_Handle_t x_کتار,
                                      ثابت فراغ * ثابت pv_توکی_منزل_کتار,
                                      TickType_t x_Ticks_منزل_Wait,
                                      بنسټ_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        بنسټ_Type_t xReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            xReturn = x_کتار_Generic_Send( x_کتار, pv_توکی_منزل_کتار, x_Ticks_منزل_Wait, xCopyPosition );
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_کتار_Generic_Send( x_کتار, pv_توکی_منزل_کتار, x_Ticks_منزل_Wait, xCopyPosition );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_کتار_Messages_انتظار( ثابت کتار_Handle_t px_کتار ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            uxReturn = ux_کتار_Messages_انتظار( px_کتار );
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_کتار_Messages_انتظار( px_کتار );
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_کتار_Spaces_شته( ثابت کتار_Handle_t x_کتار ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            uxReturn = ux_کتار_Spaces_شته( x_کتار );
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_کتار_Spaces_شته( x_کتار );
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Receive( کتار_Handle_t px_کتار,
                                  فراغ * ثابت pv_بفر,
                                  TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنسټ_Type_t xReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            xReturn = x_کتار_Receive( px_کتار, pv_بفر, x_Ticks_منزل_Wait );
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_کتار_Receive( px_کتار, pv_بفر, x_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Peek( کتار_Handle_t x_کتار,
                               فراغ * ثابت pv_بفر,
                               TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنسټ_Type_t xReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            xReturn = x_کتار_Peek( x_کتار, pv_بفر, x_Ticks_منزل_Wait );
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_کتار_Peek( x_کتار, pv_بفر, x_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Semaphore_Take( کتار_Handle_t x_کتار,
                                        TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنسټ_Type_t xReturn;

        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            xReturn = x_کتار_Semaphore_Take( x_کتار, x_Ticks_منزل_Wait );
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_کتار_Semaphore_Take( x_کتار, x_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_x_کتار_Get_Mutex_Holder( کتار_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Get_Mutex_Holder( xSemaphore );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Get_Mutex_Holder( xSemaphore );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_ویش == 1 ) )
        کتار_Handle_t MPU_x_کتار_Create_Mutex( ثابت uint8_t uc_کتار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            کتار_Handle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Create_Mutex( uc_کتار_Type );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Create_Mutex( uc_کتار_Type );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_ویش == 1 ) )
        کتار_Handle_t MPU_x_کتار_Create_Mutex_Static( ثابت uint8_t uc_کتار_Type,
                                                   Static_کتار_t * px_Static_کتار ) /* FREERTOS_SYSTEM_CALL */
        {
            کتار_Handle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Create_Mutex_Static( uc_کتار_Type, px_Static_کتار );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Create_Mutex_Static( uc_کتار_Type, px_Static_کتار );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_ویش == 1 ) )
        کتار_Handle_t MPU_x_کتار_Create_Counting_Semaphore( UBaseType_t ux_شمېر_ارزښت,
                                                         UBaseType_t ux_Initial_شمېر ) /* FREERTOS_SYSTEM_CALL */
        {
            کتار_Handle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Create_Counting_Semaphore( ux_شمېر_ارزښت, ux_Initial_شمېر );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Create_Counting_Semaphore( ux_شمېر_ارزښت, ux_Initial_شمېر );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_ویش == 1 ) )

        کتار_Handle_t MPU_x_کتار_Create_Counting_Semaphore_Static( ثابت UBaseType_t ux_Max_شمېر,
                                                               ثابت UBaseType_t ux_Initial_شمېر,
                                                               Static_کتار_t * px_Static_کتار ) /* FREERTOS_SYSTEM_CALL */
        {
            کتار_Handle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Create_Counting_Semaphore_Static( ux_Max_شمېر, ux_Initial_شمېر, px_Static_کتار );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Create_Counting_Semaphore_Static( ux_Max_شمېر, ux_Initial_شمېر, px_Static_کتار );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
        بنسټ_Type_t MPU_x_کتار_Take_Mutex_Recursive( کتار_Handle_t xMutex,
                                                 TickType_t x_بلاک_وخت ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Take_Mutex_Recursive( xMutex, x_بلاک_وخت );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Take_Mutex_Recursive( xMutex, x_بلاک_وخت );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
        بنسټ_Type_t MPU_x_کتار_Give_Mutex_Recursive( کتار_Handle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Give_Mutex_Recursive( xMutex );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Give_Mutex_Recursive( xMutex );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_کتار_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_ویش == 1 ) )
        کتار_سېټ_Handle_t MPU_x_کتار_Create_سېټ( UBaseType_t ux_Event_کتار_اوږدتیا ) /* FREERTOS_SYSTEM_CALL */
        {
            کتار_سېټ_Handle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Create_سېټ( ux_Event_کتار_اوږدتیا );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Create_سېټ( ux_Event_کتار_اوږدتیا );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_کتار_SETS == 1 ) && ( config_SUPPORT_STATIC_ویش == 1 ) )
        کتار_سېټ_Handle_t MPU_x_کتار_Create_سېټ_Static( ثابت UBaseType_t ux_Event_کتار_اوږدتیا,
                                                    uint8_t * puc_کتار_Storage,
                                                    Static_کتار_t * px_Static_کتار ) /* FREERTOS_SYSTEM_CALL */
        {
            کتار_سېټ_Handle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Create_سېټ_Static( ux_Event_کتار_اوږدتیا, puc_کتار_Storage, px_Static_کتار );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Create_سېټ_Static( ux_Event_کتار_اوږدتیا, puc_کتار_Storage, px_Static_کتار );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_کتار_SETS == 1 )
        کتار_سېټ_Member_Handle_t MPU_x_کتار_Select_From_سېټ( کتار_سېټ_Handle_t x_کتار_سېټ,
                                                        TickType_t x_بلاک_وخت_Ticks ) /* FREERTOS_SYSTEM_CALL */
        {
            کتار_سېټ_Member_Handle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Select_From_سېټ( x_کتار_سېټ, x_بلاک_وخت_Ticks );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Select_From_سېټ( x_کتار_سېټ, x_بلاک_وخت_Ticks );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_کتار_SETS == 1 )
        بنسټ_Type_t MPU_x_کتار_جمع_کړه_منزل_سېټ( کتار_سېټ_Member_Handle_t x_کتار_Or_Semaphore,
                                       کتار_سېټ_Handle_t x_کتار_سېټ ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_جمع_کړه_منزل_سېټ( x_کتار_Or_Semaphore, x_کتار_سېټ );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_جمع_کړه_منزل_سېټ( x_کتار_Or_Semaphore, x_کتار_سېټ );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_کتار_SETS == 1 )
        بنسټ_Type_t MPU_x_کتار_Remove_From_سېټ( کتار_سېټ_Member_Handle_t x_کتار_Or_Semaphore,
                                            کتار_سېټ_Handle_t x_کتار_سېټ ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_کتار_Remove_From_سېټ( x_کتار_Or_Semaphore, x_کتار_سېټ );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_کتار_Remove_From_سېټ( x_کتار_Or_Semaphore, x_کتار_سېټ );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا config_کتار_REGISTRY_اندازه > 0
        فراغ MPU_v_کتار_جمع_کړه_منزل_Registry( کتار_Handle_t x_کتار,
                                      ثابت حرف * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                v_کتار_جمع_کړه_منزل_Registry( x_کتار, pcName );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                v_کتار_جمع_کړه_منزل_Registry( x_کتار, pcName );
            }
        }
    #د_که_پای /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_کتار_REGISTRY_اندازه > 0
        فراغ MPU_v_کتار_Unregister_کتار( کتار_Handle_t x_کتار ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                v_کتار_Unregister_کتار( x_کتار );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                v_کتار_Unregister_کتار( x_کتار );
            }
        }
    #د_که_پای /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_کتار_REGISTRY_اندازه > 0
        ثابت حرف * MPU_pc_کتار_Get_Name( کتار_Handle_t x_کتار ) /* FREERTOS_SYSTEM_CALL */
        {
            ثابت حرف * pcReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                pcReturn = pc_کتار_Get_Name( x_کتار );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                pcReturn = pc_کتار_Get_Name( x_کتار );
            }

            أرجع pcReturn;
        }
    #د_که_پای /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    فراغ MPU_v_کتار_Delete( کتار_Handle_t x_کتار ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
        {
            پورټ_RAISE_PRIVILEGE();
            پورټ_حافظه_BARRIER();

            v_کتار_Delete( x_کتار );
            پورټ_حافظه_BARRIER();

            پورټ_RESET_PRIVILEGE();
            پورټ_حافظه_BARRIER();
        }
        وإلا
        {
            v_کتار_Delete( x_کتار );
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * pvReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            أرجع pvReturn;
        }
    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ MPU_v_Timer_سېټ_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                v_Timer_سېټ_Timer_ID( xTimer, pvNewID );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                v_Timer_سېټ_Timer_ID( xTimer, pvNewID );
            }
        }
    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        بنسټ_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_Timer_Is_Timer_فعال( xTimer );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Timer_Is_Timer_فعال( xTimer );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ MPU_v_Timer_سېټ_Reload_ډېرپېښ( TimerHandle_t xTimer,
                                      ثابت بنسټ_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                v_Timer_سېټ_Reload_ډېرپېښ( xTimer, xAutoReload );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                v_Timer_سېټ_Reload_ډېرپېښ( xTimer, xAutoReload );
            }
        }
    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_ux_Timer_Get_Reload_ډېرپېښ( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                uxReturn = ux_Timer_Get_Reload_ډېرپېښ( xTimer );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Timer_Get_Reload_ډېرپېښ( xTimer );
            }

            أرجع uxReturn;
        }
    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ثابت حرف * pcReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            أرجع pcReturn;
        }
    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TickType_t MPU_x_Timer_Get_Expiry_وخت( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_Timer_Get_Expiry_وخت( xTimer );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Timer_Get_Expiry_وخت( xTimer );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        بنسټ_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ثابت بنسټ_Type_t xCommandID,
                                                     ثابت TickType_t x_Optional_ارزښت,
                                                     بنسټ_Type_t * ثابت px_Higher_لومړیتوب_Task_Woken,
                                                     ثابت TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_ارزښت, px_Higher_لومړیتوب_Task_Woken, x_Ticks_منزل_Wait );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_ارزښت, px_Higher_لومړیتوب_Task_Woken, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ویش == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_ډله_Handle_t MPU_x_Event_ډله_Create( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ډله_Handle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_Event_ډله_Create();
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_ډله_Create();
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ویش == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_ډله_Handle_t MPU_x_Event_ډله_Create_Static( Static_Event_ډله_t * px_Event_ډله_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ډله_Handle_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_Event_ډله_Create_Static( px_Event_ډله_بفر );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_ډله_Create_Static( px_Event_ډله_بفر );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بټونه_t MPU_x_Event_ډله_Wait_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                             ثابت Event_بټونه_t ux_بټونه_منزل_Wait_For,
                                             ثابت بنسټ_Type_t xClearOnExit,
                                             ثابت بنسټ_Type_t x_Wait_For_All_بټونه,
                                             TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بټونه_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_Event_ډله_Wait_بټونه( x_Event_ډله, ux_بټونه_منزل_Wait_For, xClearOnExit, x_Wait_For_All_بټونه, x_Ticks_منزل_Wait );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_ډله_Wait_بټونه( x_Event_ډله, ux_بټونه_منزل_Wait_For, xClearOnExit, x_Wait_For_All_بټونه, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بټونه_t MPU_x_Event_ډله_Clear_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                              ثابت Event_بټونه_t ux_بټونه_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بټونه_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_Event_ډله_Clear_بټونه( x_Event_ډله, ux_بټونه_منزل_Clear );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_ډله_Clear_بټونه( x_Event_ډله, ux_بټونه_منزل_Clear );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بټونه_t MPU_x_Event_ډله_سېټ_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                            ثابت Event_بټونه_t ux_بټونه_منزل_سېټ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بټونه_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_Event_ډله_سېټ_بټونه( x_Event_ډله, ux_بټونه_منزل_سېټ );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_ډله_سېټ_بټونه( x_Event_ډله, ux_بټونه_منزل_سېټ );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بټونه_t MPU_x_Event_ډله_Sync( Event_ډله_Handle_t x_Event_ډله,
                                         ثابت Event_بټونه_t ux_بټونه_منزل_سېټ,
                                         ثابت Event_بټونه_t ux_بټونه_منزل_Wait_For,
                                         TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بټونه_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_Event_ډله_Sync( x_Event_ډله, ux_بټونه_منزل_سېټ, ux_بټونه_منزل_Wait_For, x_Ticks_منزل_Wait );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_ډله_Sync( x_Event_ډله, ux_بټونه_منزل_سېټ, ux_بټونه_منزل_Wait_For, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        فراغ MPU_v_Event_ډله_Delete( Event_ډله_Handle_t x_Event_ډله ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                v_Event_ډله_Delete( x_Event_ډله );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                v_Event_ډله_Delete( x_Event_ډله );
            }
        }
    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )
        size_t MPU_x_بهیر_بفر_Send( بهیر_بفر_Handle_t x_بهیر_بفر,
                                      ثابت فراغ * pv_Tx_معلومات,
                                      size_t x_معلومات_اوږدتیا_بایټونه,
                                      TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_بهیر_بفر_Send( x_بهیر_بفر, pv_Tx_معلومات, x_معلومات_اوږدتیا_بایټونه, x_Ticks_منزل_Wait );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_بهیر_بفر_Send( x_بهیر_بفر, pv_Tx_معلومات, x_معلومات_اوږدتیا_بایټونه, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )
        size_t MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه( x_بهیر_بفر );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه( x_بهیر_بفر );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )
        size_t MPU_x_بهیر_بفر_Receive( بهیر_بفر_Handle_t x_بهیر_بفر,
                                         فراغ * pv_Rx_معلومات,
                                         size_t x_بفر_اوږدتیا_بایټونه,
                                         TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_بهیر_بفر_Receive( x_بهیر_بفر, pv_Rx_معلومات, x_بفر_اوږدتیا_بایټونه, x_Ticks_منزل_Wait );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_بهیر_بفر_Receive( x_بهیر_بفر, pv_Rx_معلومات, x_بفر_اوږدتیا_بایټونه, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )
        فراغ MPU_v_بهیر_بفر_Delete( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                v_بهیر_بفر_Delete( x_بهیر_بفر );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                v_بهیر_بفر_Delete( x_بهیر_بفر );
            }
        }
    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )
        بنسټ_Type_t MPU_x_بهیر_بفر_Is_ډک( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_بهیر_بفر_Is_ډک( x_بهیر_بفر );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_بهیر_بفر_Is_ډک( x_بهیر_بفر );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )
        بنسټ_Type_t MPU_x_بهیر_بفر_Is_تشه( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_بهیر_بفر_Is_تشه( x_بهیر_بفر );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_بهیر_بفر_Is_تشه( x_بهیر_بفر );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )
        بنسټ_Type_t MPU_x_بهیر_بفر_Reset( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_بهیر_بفر_Reset( x_بهیر_بفر );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_بهیر_بفر_Reset( x_بهیر_بفر );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )
        size_t MPU_x_بهیر_بفر_Spaces_شته( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();
                xReturn = x_بهیر_بفر_Spaces_شته( x_بهیر_بفر );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_بهیر_بفر_Spaces_شته( x_بهیر_بفر );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )
        size_t MPU_x_بهیر_بفر_بایټونه_شته( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_بهیر_بفر_بایټونه_شته( x_بهیر_بفر );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_بهیر_بفر_بایټونه_شته( x_بهیر_بفر );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )
        بنسټ_Type_t MPU_x_بهیر_بفر_سېټ_Trigger_Level( بهیر_بفر_Handle_t x_بهیر_بفر,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn;

            إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
            {
                پورټ_RAISE_PRIVILEGE();
                پورټ_حافظه_BARRIER();

                xReturn = x_بهیر_بفر_سېټ_Trigger_Level( x_بهیر_بفر, xTriggerLevel );
                پورټ_حافظه_BARRIER();

                پورټ_RESET_PRIVILEGE();
                پورټ_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_بهیر_بفر_سېټ_Trigger_Level( x_بهیر_بفر, xTriggerLevel );
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ویش == 1 ) && ( config_USE_بهیر_BUFFERS == 1 ) )
        بهیر_بفر_Handle_t MPU_x_بهیر_بفر_Generic_Create( size_t x_بفر_اندازه_بایټونه,
                                                             size_t x_Trigger_Level_بایټونه,
                                                             بنسټ_Type_t x_بهیر_بفر_Type,
                                                             بهیر_بفر_Callback_Function_t pxSendCompletedCallback,
                                                             بهیر_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            بهیر_بفر_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
                {
                    پورټ_RAISE_PRIVILEGE();
                    پورټ_حافظه_BARRIER();

                    xReturn = x_بهیر_بفر_Generic_Create( x_بفر_اندازه_بایټونه,
                                                          x_Trigger_Level_بایټونه,
                                                          x_بهیر_بفر_Type,
                                                          عدم,
                                                          عدم );
                    پورټ_حافظه_BARRIER();

                    پورټ_RESET_PRIVILEGE();
                    پورټ_حافظه_BARRIER();
                }
                وإلا
                {
                    xReturn = x_بهیر_بفر_Generic_Create( x_بفر_اندازه_بایټونه,
                                                          x_Trigger_Level_بایټونه,
                                                          x_بهیر_بفر_Type,
                                                          عدم,
                                                          عدم );
                }
            }
            وإلا
            {
                trace_بهیر_بفر_CREATE_FAILED( x_بهیر_بفر_Type );
                xReturn = عدم;
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ویش == 1 ) && ( config_USE_بهیر_BUFFERS == 1 ) )
        بهیر_بفر_Handle_t MPU_x_بهیر_بفر_Generic_Create_Static( size_t x_بفر_اندازه_بایټونه,
                                                                   size_t x_Trigger_Level_بایټونه,
                                                                   بنسټ_Type_t x_بهیر_بفر_Type,
                                                                   uint8_t * ثابت puc_بهیر_بفر_Storage_Area,
                                                                   Static_بهیر_بفر_t * ثابت px_Static_بهیر_بفر,
                                                                   بهیر_بفر_Callback_Function_t pxSendCompletedCallback,
                                                                   بهیر_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            بهیر_بفر_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                إذا( پورټ_IS_PRIVILEGED() == pdFALSE )
                {
                    پورټ_RAISE_PRIVILEGE();
                    پورټ_حافظه_BARRIER();

                    xReturn = x_بهیر_بفر_Generic_Create_Static( x_بفر_اندازه_بایټونه,
                                                                x_Trigger_Level_بایټونه,
                                                                x_بهیر_بفر_Type,
                                                                puc_بهیر_بفر_Storage_Area,
                                                                px_Static_بهیر_بفر,
                                                                عدم,
                                                                عدم );
                    پورټ_حافظه_BARRIER();

                    پورټ_RESET_PRIVILEGE();
                    پورټ_حافظه_BARRIER();
                }
                وإلا
                {
                    xReturn = x_بهیر_بفر_Generic_Create_Static( x_بفر_اندازه_بایټونه,
                                                                x_Trigger_Level_بایټونه,
                                                                x_بهیر_بفر_Type,
                                                                puc_بهیر_بفر_Storage_Area,
                                                                px_Static_بهیر_بفر,
                                                                عدم,
                                                                عدم );
                }
            }
            وإلا
            {
                trace_بهیر_بفر_CREATE_STATIC_FAILED( xReturn, x_بهیر_بفر_Type );
                xReturn = عدم;
            }

            أرجع xReturn;
        }
    #د_که_پای /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
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

    #إذا configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ضمن "application_defined_privileged_functions.h"
    #د_که_پای
/*-----------------------------------------------------------*/

#د_که_پای /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
