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
#وصف_ڪريو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"

#وصف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( ( پورٽ_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #غلطي Access control list is not موجود with this MPU wrapper. Please سيٽ configENABLE_ACCESS_CONTROL_LIST منزل 0.
    #جيڪڏهن_پورو

    #إذا ( config_SUPPORT_DYNAMIC_ورهاست == 1 )
        بنياد_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_ڪوڊ,
                                    ثابت حرف * ثابت pcName,
                                    ثابت config_ڍير_اونهائي_TYPE ux_ڍير_اونهائي,
                                    فراغ * pvParameters,
                                    UBaseType_t ux_ترجيح,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                ux_ترجيح = ux_ترجيح & ~( پورٽ_PRIVILEGE_ٻٽو_انگ );
                پورٽ_يادگيري_BARRIER();

                xReturn = xTaskCreate( pv_Task_ڪوڊ, pcName, ux_ڍير_اونهائي, pvParameters, ux_ترجيح, pxCreatedTask );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCreate( pv_Task_ڪوڊ, pcName, ux_ڍير_اونهائي, pvParameters, ux_ترجيح, pxCreatedTask );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ورهاست == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_ڪوڊ,
                                            ثابت حرف * ثابت pcName,
                                            ثابت config_ڍير_اونهائي_TYPE ux_ڍير_اونهائي,
                                            فراغ * ثابت pvParameters,
                                            UBaseType_t ux_ترجيح,
                                            ڍير_Type_t * ثابت pux_ڍير_بفر,
                                            StaticTask_t * ثابت px_Task_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                ux_ترجيح = ux_ترجيح & ~( پورٽ_PRIVILEGE_ٻٽو_انگ );
                پورٽ_يادگيري_BARRIER();

                xReturn = xTaskCreateStatic( px_Task_ڪوڊ, pcName, ux_ڍير_اونهائي, pvParameters, ux_ترجيح, pux_ڍير_بفر, px_Task_بفر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCreateStatic( px_Task_ڪوڊ, pcName, ux_ڍير_اونهائي, pvParameters, ux_ترجيح, pux_ڍير_بفر, px_Task_بفر );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelete == 1 )
        فراغ MPU_vTaskDelete( TaskHandle_t px_Task_منزل_Delete ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                vTaskDelete( px_Task_منزل_Delete );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                vTaskDelete( px_Task_منزل_Delete );
            }
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )
        بنياد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_اڳيون_Wake_وقت,
                                        TickType_t x_وقت_Increment ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = xTaskDelayUntil( px_اڳيون_Wake_وقت, x_وقت_Increment );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskDelayUntil( px_اڳيون_Wake_وقت, x_وقت_Increment );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )
        بنياد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )
        فراغ MPU_vTaskDelay( TickType_t x_Ticks_منزل_Delay ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                vTaskDelay( x_Ticks_منزل_Delay );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                vTaskDelay( x_Ticks_منزل_Delay );
            }
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_ترجيح_Get == 1 )
        UBaseType_t MPU_ux_Task_ترجيح_Get( ثابت TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                uxReturn = ux_Task_ترجيح_Get( pxTask );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_ترجيح_Get( pxTask );
            }

            أرجع uxReturn;
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_v_Task_ترجيح_سيٽ == 1 )
        فراغ MPU_v_Task_ترجيح_سيٽ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ترجيح ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                v_Task_ترجيح_سيٽ( pxTask, ux_New_ترجيح );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                v_Task_ترجيح_سيٽ( pxTask, ux_New_ترجيح );
            }
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                eReturn = eTaskGetState( pxTask );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                eReturn = eTaskGetState( pxTask );
            }

            أرجع eReturn;
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )
        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               بنياد_Type_t x_Get_Free_ڍير_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ڍير_Space, eState );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ڍير_Space, eState );
            }
        }
    #جيڪڏهن_پورو /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )
        فراغ MPU_vTaskSuspend( TaskHandle_t px_Task_منزل_Suspend ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                vTaskSuspend( px_Task_منزل_Suspend );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                vTaskSuspend( px_Task_منزل_Suspend );
            }
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )
        فراغ MPU_vTaskResume( TaskHandle_t px_Task_منزل_Resume ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                vTaskResume( px_Task_منزل_Resume );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                vTaskResume( px_Task_منزل_Resume );
            }
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_vTaskSuspendAll( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            vTaskSuspendAll();
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_xTaskResumeAll( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        بنياد_Type_t xReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            xReturn = xTaskResumeAll();
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            xReturn = xTaskResumeAll();
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ڳڻپ( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            xReturn = x_Task_Get_Tick_ڳڻپ();
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Get_Tick_ڳڻپ();
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_عدد_جو_Tasks( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            uxReturn = ux_Task_Get_عدد_جو_Tasks();
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_Task_Get_عدد_جو_Tasks();
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( ثابت حرف * pc_Name_منزل_Query ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = xTaskGetHandle( pc_Name_منزل_Query );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetHandle( pc_Name_منزل_Query );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) )
        فراغ MPU_vTaskListTasks( حرف * pc_Write_بفر,
                                 size_t ux_بفر_ڊيگهائي ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                vTaskListTasks( pc_Write_بفر, ux_بفر_ڊيگهائي );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                vTaskListTasks( pc_Write_بفر, ux_بفر_ڊيگهائي );
            }
        }
    #جيڪڏهن_پورو /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لاڳيتو_وقت_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) )
        فراغ MPU_v_Task_Get_لاڳيتو_وقت_Statistics( حرف * pc_Write_بفر,
                                            size_t ux_بفر_ڊيگهائي ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                v_Task_Get_لاڳيتو_وقت_Statistics( pc_Write_بفر, ux_بفر_ڊيگهائي );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                v_Task_Get_لاڳيتو_وقت_Statistics( pc_Write_بفر, ux_بفر_ڊيگهائي );
            }
        }
    #جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لاڳيتو_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_لاڳيتو_وقت_COUNTER_TYPE xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = ul_Task_Get_Idle_لاڳيتو_وقت_Percent();
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = ul_Task_Get_Idle_لاڳيتو_وقت_Percent();
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لاڳيتو_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_لاڳيتو_وقت_COUNTER_TYPE xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = ul_Task_Get_Idle_لاڳيتو_وقت_Counter();
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = ul_Task_Get_Idle_لاڳيتو_وقت_Counter();
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )
        فراغ MPU_v_Task_سيٽ_Application_Task_ٽيگ( TaskHandle_t xTask,
                                             TaskHookFunction_t px_ٽيگ_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                v_Task_سيٽ_Application_Task_ٽيگ( xTask, px_ٽيگ_قدر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                v_Task_سيٽ_Application_Task_ٽيگ( xTask, px_ٽيگ_قدر );
            }
        }
    #جيڪڏهن_پورو /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )
        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٽيگ( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_Task_Get_Application_Task_ٽيگ( xTask );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_Task_Get_Application_Task_ٽيگ( xTask );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_انگ_THREAD_LOCAL_STORAGE_اشارا != 0 )
        فراغ MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو( TaskHandle_t x_Task_منزل_سيٽ,
                                                    بنياد_Type_t x_اشاريو,
                                                    فراغ * pv_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                v_Task_سيٽ_Thread_Local_Storage_اشارو( x_Task_منزل_سيٽ, x_اشاريو, pv_قدر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                v_Task_سيٽ_Thread_Local_Storage_اشارو( x_Task_منزل_سيٽ, x_اشاريو, pv_قدر );
            }
        }
    #جيڪڏهن_پورو /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_انگ_THREAD_LOCAL_STORAGE_اشارا != 0 )
        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارو( TaskHandle_t x_Task_منزل_Query,
                                                       بنياد_Type_t x_اشاريو ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * pvReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                pvReturn = pv_Task_Get_Thread_Local_Storage_اشارو( x_Task_منزل_Query, x_اشاريو );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_اشارو( x_Task_منزل_Query, x_اشاريو );
            }

            أرجع pvReturn;
        }
    #جيڪڏهن_پورو /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )
        بنياد_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     فراغ * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * px_Task_حالت_Array,
                                              UBaseType_t ux_Array_سائيز,
                                              config_لاڳيتو_وقت_COUNTER_TYPE * pul_ڪل_لاڳيتو_وقت ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_سائيز, pul_ڪل_لاڳيتو_وقت );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_سائيز, pul_ڪل_لاڳيتو_وقت );
            }

            أرجع uxReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_Task_Catch_مٿي_Ticks( TickType_t x_Ticks_منزل_Catch_مٿي ) /* FREERTOS_SYSTEM_CALL */
    {
        بنياد_Type_t xReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            xReturn = x_Task_Catch_مٿي_Ticks( x_Ticks_منزل_Catch_مٿي );
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Catch_مٿي_Ticks( x_Ticks_منزل_Catch_مٿي );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڍير_مٿاهون_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                uxReturn = ux_Task_Get_ڍير_مٿاهون_Water_Mark( xTask );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_Get_ڍير_مٿاهون_Water_Mark( xTask );
            }

            أرجع uxReturn;
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڍير_مٿاهون_Water_Mark2 == 1 )
        config_ڍير_اونهائي_TYPE MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ڍير_اونهائي_TYPE uxReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                uxReturn = ux_Task_Get_ڍير_مٿاهون_Water_Mark2( xTask );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_Get_ڍير_مٿاهون_Water_Mark2( xTask );
            }

            أرجع uxReturn;
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
        بنياد_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = xTaskGetSchedulerState();
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetSchedulerState();
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_سيٽ_وقت_ٻاهريون_State( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            v_Task_سيٽ_وقت_ٻاهريون_State( px_وقت_ٻاهريون );
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            v_Task_سيٽ_وقت_ٻاهريون_State( px_وقت_ٻاهريون );
        }
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_Task_Check_For_وقت_ٻاهريون( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون,
                                         TickType_t * ثابت px_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنياد_Type_t xReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            xReturn = x_Task_Check_For_وقت_ٻاهريون( px_وقت_ٻاهريون, px_Ticks_منزل_Wait );
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Check_For_وقت_ٻاهريون( px_وقت_ٻاهريون, px_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        بنياد_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_منزل_Notify,
                                           UBaseType_t ux_اشاريو_منزل_Notify,
                                           uint32_t ul_قدر,
                                           eNotifyAction eAction,
                                           uint32_t * pul_اڳيون_Notification_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = xTaskGenericNotify( x_Task_منزل_Notify, ux_اشاريو_منزل_Notify, ul_قدر, eAction, pul_اڳيون_Notification_قدر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotify( x_Task_منزل_Notify, ux_اشاريو_منزل_Notify, ul_قدر, eAction, pul_اڳيون_Notification_قدر );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        بنياد_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_اشاريو_منزل_Wait_On,
                                               uint32_t ul_بٽ_منزل_Clear_On_داخلا,
                                               uint32_t ul_بٽ_منزل_Clear_On_Exit,
                                               uint32_t * pul_Notification_قدر,
                                               TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = xTaskGenericNotifyWait( ux_اشاريو_منزل_Wait_On, ul_بٽ_منزل_Clear_On_داخلا, ul_بٽ_منزل_Clear_On_Exit, pul_Notification_قدر, x_Ticks_منزل_Wait );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotifyWait( ux_اشاريو_منزل_Wait_On, ul_بٽ_منزل_Clear_On_داخلا, ul_بٽ_منزل_Clear_On_Exit, pul_Notification_قدر, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاريو_منزل_Wait_On,
                                              بنياد_Type_t x_Clear_ڳڻپ_On_Exit,
                                              TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( ux_اشاريو_منزل_Wait_On, x_Clear_ڳڻپ_On_Exit, x_Ticks_منزل_Wait );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                ulReturn = ulTaskGenericNotifyTake( ux_اشاريو_منزل_Wait_On, x_Clear_ڳڻپ_On_Exit, x_Ticks_منزل_Wait );
            }

            أرجع ulReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        بنياد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_اشاريو_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, ux_اشاريو_منزل_Clear );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, ux_اشاريو_منزل_Clear );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_اشاريو_منزل_Clear,
                                                    uint32_t ul_بٽ_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                ulReturn = ul_Task_Generic_Notify_قدر_Clear( xTask, ux_اشاريو_منزل_Clear, ul_بٽ_منزل_Clear );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                ulReturn = ul_Task_Generic_Notify_قدر_Clear( xTask, ux_اشاريو_منزل_Clear, ul_بٽ_منزل_Clear );
            }

            أرجع ulReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ورهاست == 1 )
        قطار_Handle_t MPU_x_قطار_Generic_Create( UBaseType_t ux_قطار_ڊيگهائي,
                                               UBaseType_t ux_شي_سائيز,
                                               uint8_t uc_قطار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Generic_Create( ux_قطار_ڊيگهائي, ux_شي_سائيز, uc_قطار_Type );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Generic_Create( ux_قطار_ڊيگهائي, ux_شي_سائيز, uc_قطار_Type );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ورهاست == 1 )
        قطار_Handle_t MPU_x_قطار_Generic_Create_Static( ثابت UBaseType_t ux_قطار_ڊيگهائي,
                                                     ثابت UBaseType_t ux_شي_سائيز,
                                                     uint8_t * puc_قطار_Storage,
                                                     Static_قطار_t * px_Static_قطار,
                                                     ثابت uint8_t uc_قطار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Generic_Create_Static( ux_قطار_ڊيگهائي, ux_شي_سائيز, puc_قطار_Storage, px_Static_قطار, uc_قطار_Type );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Generic_Create_Static( ux_قطار_ڊيگهائي, ux_شي_سائيز, puc_قطار_Storage, px_Static_قطار, uc_قطار_Type );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Generic_Reset( قطار_Handle_t px_قطار,
                                       بنياد_Type_t x_New_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        بنياد_Type_t xReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            xReturn = x_قطار_Generic_Reset( px_قطار, x_New_قطار );
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            xReturn = x_قطار_Generic_Reset( px_قطار, x_New_قطار );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                      ثابت فراغ * ثابت pv_شي_منزل_قطار,
                                      TickType_t x_Ticks_منزل_Wait,
                                      بنياد_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        بنياد_Type_t xReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            xReturn = x_قطار_Generic_Send( x_قطار, pv_شي_منزل_قطار, x_Ticks_منزل_Wait, xCopyPosition );
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            xReturn = x_قطار_Generic_Send( x_قطار, pv_شي_منزل_قطار, x_Ticks_منزل_Wait, xCopyPosition );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_انتظار( ثابت قطار_Handle_t px_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            uxReturn = ux_قطار_Messages_انتظار( px_قطار );
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_قطار_Messages_انتظار( px_قطار );
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Spaces_موجود( ثابت قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            uxReturn = ux_قطار_Spaces_موجود( x_قطار );
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_قطار_Spaces_موجود( x_قطار );
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Receive( قطار_Handle_t px_قطار,
                                  فراغ * ثابت pv_بفر,
                                  TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنياد_Type_t xReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            xReturn = x_قطار_Receive( px_قطار, pv_بفر, x_Ticks_منزل_Wait );
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            xReturn = x_قطار_Receive( px_قطار, pv_بفر, x_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                               فراغ * ثابت pv_بفر,
                               TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنياد_Type_t xReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            xReturn = x_قطار_Peek( x_قطار, pv_بفر, x_Ticks_منزل_Wait );
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            xReturn = x_قطار_Peek( x_قطار, pv_بفر, x_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                        TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنياد_Type_t xReturn;

        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            xReturn = x_قطار_Semaphore_Take( x_قطار, x_Ticks_منزل_Wait );
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            xReturn = x_قطار_Semaphore_Take( x_قطار, x_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Get_Mutex_Holder( xSemaphore );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Get_Mutex_Holder( xSemaphore );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) )
        قطار_Handle_t MPU_x_قطار_Create_Mutex( ثابت uint8_t uc_قطار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Create_Mutex( uc_قطار_Type );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_Mutex( uc_قطار_Type );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_ورهاست == 1 ) )
        قطار_Handle_t MPU_x_قطار_Create_Mutex_Static( ثابت uint8_t uc_قطار_Type,
                                                   Static_قطار_t * px_Static_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Create_Mutex_Static( uc_قطار_Type, px_Static_قطار );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_Mutex_Static( uc_قطار_Type, px_Static_قطار );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) )
        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore( UBaseType_t ux_ڳڻپ_قدر,
                                                         UBaseType_t ux_Initial_ڳڻپ ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Create_Counting_Semaphore( ux_ڳڻپ_قدر, ux_Initial_ڳڻپ );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_Counting_Semaphore( ux_ڳڻپ_قدر, ux_Initial_ڳڻپ );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_ورهاست == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore_Static( ثابت UBaseType_t ux_Max_ڳڻپ,
                                                               ثابت UBaseType_t ux_Initial_ڳڻپ,
                                                               Static_قطار_t * px_Static_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Create_Counting_Semaphore_Static( ux_Max_ڳڻپ, ux_Initial_ڳڻپ, px_Static_قطار );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_Counting_Semaphore_Static( ux_Max_ڳڻپ, ux_Initial_ڳڻپ, px_Static_قطار );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
        بنياد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                                 TickType_t x_بلاڪ_وقت ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Take_Mutex_Recursive( xMutex, x_بلاڪ_وقت );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Take_Mutex_Recursive( xMutex, x_بلاڪ_وقت );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
        بنياد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Give_Mutex_Recursive( xMutex );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Give_Mutex_Recursive( xMutex );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) )
        قطار_سيٽ_Handle_t MPU_x_قطار_Create_سيٽ( UBaseType_t ux_Event_قطار_ڊيگهائي ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_سيٽ_Handle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Create_سيٽ( ux_Event_قطار_ڊيگهائي );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_سيٽ( ux_Event_قطار_ڊيگهائي );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_STATIC_ورهاست == 1 ) )
        قطار_سيٽ_Handle_t MPU_x_قطار_Create_سيٽ_Static( ثابت UBaseType_t ux_Event_قطار_ڊيگهائي,
                                                    uint8_t * puc_قطار_Storage,
                                                    Static_قطار_t * px_Static_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_سيٽ_Handle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Create_سيٽ_Static( ux_Event_قطار_ڊيگهائي, puc_قطار_Storage, px_Static_قطار );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_سيٽ_Static( ux_Event_قطار_ڊيگهائي, puc_قطار_Storage, px_Static_قطار );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )
        قطار_سيٽ_Member_Handle_t MPU_x_قطار_Select_From_سيٽ( قطار_سيٽ_Handle_t x_قطار_سيٽ,
                                                        TickType_t x_بلاڪ_وقت_Ticks ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_سيٽ_Member_Handle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Select_From_سيٽ( x_قطار_سيٽ, x_بلاڪ_وقت_Ticks );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Select_From_سيٽ( x_قطار_سيٽ, x_بلاڪ_وقت_Ticks );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )
        بنياد_Type_t MPU_x_قطار_جوڙيو_منزل_سيٽ( قطار_سيٽ_Member_Handle_t x_قطار_Or_Semaphore,
                                       قطار_سيٽ_Handle_t x_قطار_سيٽ ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_جوڙيو_منزل_سيٽ( x_قطار_Or_Semaphore, x_قطار_سيٽ );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_جوڙيو_منزل_سيٽ( x_قطار_Or_Semaphore, x_قطار_سيٽ );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )
        بنياد_Type_t MPU_x_قطار_Remove_From_سيٽ( قطار_سيٽ_Member_Handle_t x_قطار_Or_Semaphore,
                                            قطار_سيٽ_Handle_t x_قطار_سيٽ ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_قطار_Remove_From_سيٽ( x_قطار_Or_Semaphore, x_قطار_سيٽ );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Remove_From_سيٽ( x_قطار_Or_Semaphore, x_قطار_سيٽ );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_سائيز > 0
        فراغ MPU_v_قطار_جوڙيو_منزل_Registry( قطار_Handle_t x_قطار,
                                      ثابت حرف * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                v_قطار_جوڙيو_منزل_Registry( x_قطار, pcName );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                v_قطار_جوڙيو_منزل_Registry( x_قطار, pcName );
            }
        }
    #جيڪڏهن_پورو /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_سائيز > 0
        فراغ MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                v_قطار_Unregister_قطار( x_قطار );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                v_قطار_Unregister_قطار( x_قطار );
            }
        }
    #جيڪڏهن_پورو /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_سائيز > 0
        ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            ثابت حرف * pcReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                pcReturn = pc_قطار_Get_Name( x_قطار );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                pcReturn = pc_قطار_Get_Name( x_قطار );
            }

            أرجع pcReturn;
        }
    #جيڪڏهن_پورو /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    فراغ MPU_v_قطار_Delete( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٽ_RAISE_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();

            v_قطار_Delete( x_قطار );
            پورٽ_يادگيري_BARRIER();

            پورٽ_RESET_PRIVILEGE();
            پورٽ_يادگيري_BARRIER();
        }
        وإلا
        {
            v_قطار_Delete( x_قطار );
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * pvReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            أرجع pvReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ MPU_v_Timer_سيٽ_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                v_Timer_سيٽ_Timer_ID( xTimer, pvNewID );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                v_Timer_سيٽ_Timer_ID( xTimer, pvNewID );
            }
        }
    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        بنياد_Type_t MPU_x_Timer_Is_Timer_سرگرم( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_Timer_Is_Timer_سرگرم( xTimer );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_Timer_Is_Timer_سرگرم( xTimer );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ MPU_v_Timer_سيٽ_Reload_گهڻائي( TimerHandle_t xTimer,
                                      ثابت بنياد_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                v_Timer_سيٽ_Reload_گهڻائي( xTimer, xAutoReload );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                v_Timer_سيٽ_Reload_گهڻائي( xTimer, xAutoReload );
            }
        }
    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_ux_Timer_Get_Reload_گهڻائي( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                uxReturn = ux_Timer_Get_Reload_گهڻائي( xTimer );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Timer_Get_Reload_گهڻائي( xTimer );
            }

            أرجع uxReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ثابت حرف * pcReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            أرجع pcReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_Timer_Get_Expiry_وقت( xTimer );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_Timer_Get_Expiry_وقت( xTimer );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        بنياد_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ثابت بنياد_Type_t xCommandID,
                                                     ثابت TickType_t x_Optional_قدر,
                                                     بنياد_Type_t * ثابت px_Higher_ترجيح_Task_Woken,
                                                     ثابت TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_قدر, px_Higher_ترجيح_Task_Woken, x_Ticks_منزل_Wait );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_قدر, px_Higher_ترجيح_Task_Woken, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_گروهه_Handle_t MPU_x_Event_گروهه_Create( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_گروهه_Handle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_Event_گروهه_Create();
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروهه_Create();
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ورهاست == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_گروهه_Handle_t MPU_x_Event_گروهه_Create_Static( Static_Event_گروهه_t * px_Event_گروهه_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_گروهه_Handle_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_Event_گروهه_Create_Static( px_Event_گروهه_بفر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروهه_Create_Static( px_Event_گروهه_بفر );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بٽ_t MPU_x_Event_گروهه_Wait_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                             ثابت Event_بٽ_t ux_بٽ_منزل_Wait_For,
                                             ثابت بنياد_Type_t xClearOnExit,
                                             ثابت بنياد_Type_t x_Wait_For_All_بٽ,
                                             TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٽ_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_Event_گروهه_Wait_بٽ( x_Event_گروهه, ux_بٽ_منزل_Wait_For, xClearOnExit, x_Wait_For_All_بٽ, x_Ticks_منزل_Wait );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروهه_Wait_بٽ( x_Event_گروهه, ux_بٽ_منزل_Wait_For, xClearOnExit, x_Wait_For_All_بٽ, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بٽ_t MPU_x_Event_گروهه_Clear_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                              ثابت Event_بٽ_t ux_بٽ_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٽ_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_Event_گروهه_Clear_بٽ( x_Event_گروهه, ux_بٽ_منزل_Clear );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروهه_Clear_بٽ( x_Event_گروهه, ux_بٽ_منزل_Clear );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بٽ_t MPU_x_Event_گروهه_سيٽ_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                            ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٽ_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_Event_گروهه_سيٽ_بٽ( x_Event_گروهه, ux_بٽ_منزل_سيٽ );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروهه_سيٽ_بٽ( x_Event_گروهه, ux_بٽ_منزل_سيٽ );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بٽ_t MPU_x_Event_گروهه_Sync( Event_گروهه_Handle_t x_Event_گروهه,
                                         ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ,
                                         ثابت Event_بٽ_t ux_بٽ_منزل_Wait_For,
                                         TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٽ_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_Event_گروهه_Sync( x_Event_گروهه, ux_بٽ_منزل_سيٽ, ux_بٽ_منزل_Wait_For, x_Ticks_منزل_Wait );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروهه_Sync( x_Event_گروهه, ux_بٽ_منزل_سيٽ, ux_بٽ_منزل_Wait_For, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        فراغ MPU_v_Event_گروهه_Delete( Event_گروهه_Handle_t x_Event_گروهه ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                v_Event_گروهه_Delete( x_Event_گروهه );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                v_Event_گروهه_Delete( x_Event_گروهه );
            }
        }
    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
        size_t MPU_x_وهڪرو_بفر_Send( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                      ثابت فراغ * pv_Tx_معلومات,
                                      size_t x_معلومات_ڊيگهائي_بائيٽون,
                                      TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_وهڪرو_بفر_Send( x_وهڪرو_بفر, pv_Tx_معلومات, x_معلومات_ڊيگهائي_بائيٽون, x_Ticks_منزل_Wait );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_وهڪرو_بفر_Send( x_وهڪرو_بفر, pv_Tx_معلومات, x_معلومات_ڊيگهائي_بائيٽون, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
        size_t MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون( x_وهڪرو_بفر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون( x_وهڪرو_بفر );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
        size_t MPU_x_وهڪرو_بفر_Receive( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                         فراغ * pv_Rx_معلومات,
                                         size_t x_بفر_ڊيگهائي_بائيٽون,
                                         TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_وهڪرو_بفر_Receive( x_وهڪرو_بفر, pv_Rx_معلومات, x_بفر_ڊيگهائي_بائيٽون, x_Ticks_منزل_Wait );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_وهڪرو_بفر_Receive( x_وهڪرو_بفر, pv_Rx_معلومات, x_بفر_ڊيگهائي_بائيٽون, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
        فراغ MPU_v_وهڪرو_بفر_Delete( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                v_وهڪرو_بفر_Delete( x_وهڪرو_بفر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                v_وهڪرو_بفر_Delete( x_وهڪرو_بفر );
            }
        }
    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
        بنياد_Type_t MPU_x_وهڪرو_بفر_Is_ڀريل( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_وهڪرو_بفر_Is_ڀريل( x_وهڪرو_بفر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_وهڪرو_بفر_Is_ڀريل( x_وهڪرو_بفر );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
        بنياد_Type_t MPU_x_وهڪرو_بفر_Is_خالي_جايون( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_وهڪرو_بفر_Is_خالي_جايون( x_وهڪرو_بفر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_وهڪرو_بفر_Is_خالي_جايون( x_وهڪرو_بفر );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
        بنياد_Type_t MPU_x_وهڪرو_بفر_Reset( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_وهڪرو_بفر_Reset( x_وهڪرو_بفر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_وهڪرو_بفر_Reset( x_وهڪرو_بفر );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
        size_t MPU_x_وهڪرو_بفر_Spaces_موجود( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
                xReturn = x_وهڪرو_بفر_Spaces_موجود( x_وهڪرو_بفر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_وهڪرو_بفر_Spaces_موجود( x_وهڪرو_بفر );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
        size_t MPU_x_وهڪرو_بفر_بائيٽون_موجود( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_وهڪرو_بفر_بائيٽون_موجود( x_وهڪرو_بفر );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_وهڪرو_بفر_بائيٽون_موجود( x_وهڪرو_بفر );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
        بنياد_Type_t MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn;

            إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٽ_RAISE_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();

                xReturn = x_وهڪرو_بفر_سيٽ_Trigger_Level( x_وهڪرو_بفر, xTriggerLevel );
                پورٽ_يادگيري_BARRIER();

                پورٽ_RESET_PRIVILEGE();
                پورٽ_يادگيري_BARRIER();
            }
            وإلا
            {
                xReturn = x_وهڪرو_بفر_سيٽ_Trigger_Level( x_وهڪرو_بفر, xTriggerLevel );
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) && ( config_USE_وهڪرو_BUFFERS == 1 ) )
        وهڪرو_بفر_Handle_t MPU_x_وهڪرو_بفر_Generic_Create( size_t x_بفر_سائيز_بائيٽون,
                                                             size_t x_Trigger_Level_بائيٽون,
                                                             بنياد_Type_t x_وهڪرو_بفر_Type,
                                                             وهڪرو_بفر_Callback_Function_t pxSendCompletedCallback,
                                                             وهڪرو_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            وهڪرو_بفر_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
                {
                    پورٽ_RAISE_PRIVILEGE();
                    پورٽ_يادگيري_BARRIER();

                    xReturn = x_وهڪرو_بفر_Generic_Create( x_بفر_سائيز_بائيٽون,
                                                          x_Trigger_Level_بائيٽون,
                                                          x_وهڪرو_بفر_Type,
                                                          عدم,
                                                          عدم );
                    پورٽ_يادگيري_BARRIER();

                    پورٽ_RESET_PRIVILEGE();
                    پورٽ_يادگيري_BARRIER();
                }
                وإلا
                {
                    xReturn = x_وهڪرو_بفر_Generic_Create( x_بفر_سائيز_بائيٽون,
                                                          x_Trigger_Level_بائيٽون,
                                                          x_وهڪرو_بفر_Type,
                                                          عدم,
                                                          عدم );
                }
            }
            وإلا
            {
                trace_وهڪرو_بفر_CREATE_FAILED( x_وهڪرو_بفر_Type );
                xReturn = عدم;
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ورهاست == 1 ) && ( config_USE_وهڪرو_BUFFERS == 1 ) )
        وهڪرو_بفر_Handle_t MPU_x_وهڪرو_بفر_Generic_Create_Static( size_t x_بفر_سائيز_بائيٽون,
                                                                   size_t x_Trigger_Level_بائيٽون,
                                                                   بنياد_Type_t x_وهڪرو_بفر_Type,
                                                                   uint8_t * ثابت puc_وهڪرو_بفر_Storage_Area,
                                                                   Static_وهڪرو_بفر_t * ثابت px_Static_وهڪرو_بفر,
                                                                   وهڪرو_بفر_Callback_Function_t pxSendCompletedCallback,
                                                                   وهڪرو_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            وهڪرو_بفر_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                إذا( پورٽ_IS_PRIVILEGED() == pdFALSE )
                {
                    پورٽ_RAISE_PRIVILEGE();
                    پورٽ_يادگيري_BARRIER();

                    xReturn = x_وهڪرو_بفر_Generic_Create_Static( x_بفر_سائيز_بائيٽون,
                                                                x_Trigger_Level_بائيٽون,
                                                                x_وهڪرو_بفر_Type,
                                                                puc_وهڪرو_بفر_Storage_Area,
                                                                px_Static_وهڪرو_بفر,
                                                                عدم,
                                                                عدم );
                    پورٽ_يادگيري_BARRIER();

                    پورٽ_RESET_PRIVILEGE();
                    پورٽ_يادگيري_BARRIER();
                }
                وإلا
                {
                    xReturn = x_وهڪرو_بفر_Generic_Create_Static( x_بفر_سائيز_بائيٽون,
                                                                x_Trigger_Level_بائيٽون,
                                                                x_وهڪرو_بفر_Type,
                                                                puc_وهڪرو_بفر_Storage_Area,
                                                                px_Static_وهڪرو_بفر,
                                                                عدم,
                                                                عدم );
                }
            }
            وإلا
            {
                trace_وهڪرو_بفر_CREATE_STATIC_FAILED( xReturn, x_وهڪرو_بفر_Type );
                xReturn = عدم;
            }

            أرجع xReturn;
        }
    #جيڪڏهن_پورو /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
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
    #جيڪڏهن_پورو
/*-----------------------------------------------------------*/

#جيڪڏهن_پورو /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
