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
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"
#অন্তর্ভাব "queue.h"
#অন্তর্ভাব "timers.h"
#অন্তর্ভাব "event_groups.h"
#অন্তর্ভাব "stream_buffer.h"
#অন্তর্ভাব "mpu_prototypes.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#যদি ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #যদি ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #error Access control list is not available with this MPU wrapper. Please set configENABLE_ACCESS_CONTROL_LIST to 0.
    #endif

    #যদি ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        BaseType_t MPU_xTaskCreate( TaskFunction_t pvTaskCode,
                                    ধ্রুবক অক্ষর * ধ্রুবক pcName,
                                    ধ্রুবক config_স্তূপ_DEPTH_TYPE ux_স্তূপ_Depth,
                                    শূন্য * pvParameters,
                                    UBaseType_t uxPriority,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxPriority = uxPriority & ~( portPRIVILEGE_BIT );
                portMEMORY_BARRIER();

                xReturn = xTaskCreate( pvTaskCode, pcName, ux_স্তূপ_Depth, pvParameters, uxPriority, pxCreatedTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskCreate( pvTaskCode, pcName, ux_স্তূপ_Depth, pvParameters, uxPriority, pxCreatedTask );
            }

            ফেরত xReturn;
        }
    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_STATIC_ALLOCATION == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                            ধ্রুবক অক্ষর * ধ্রুবক pcName,
                                            ধ্রুবক config_স্তূপ_DEPTH_TYPE ux_স্তূপ_Depth,
                                            শূন্য * ধ্রুবক pvParameters,
                                            UBaseType_t uxPriority,
                                            স্তূপ_Type_t * ধ্রুবক pux_স্তূপ_বাফার,
                                            StaticTask_t * ধ্রুবক px_Task_বাফার ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxPriority = uxPriority & ~( portPRIVILEGE_BIT );
                portMEMORY_BARRIER();

                xReturn = xTaskCreateStatic( pxTaskCode, pcName, ux_স্তূপ_Depth, pvParameters, uxPriority, pux_স্তূপ_বাফার, px_Task_বাফার );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskCreateStatic( pxTaskCode, pcName, ux_স্তূপ_Depth, pvParameters, uxPriority, pux_স্তূপ_বাফার, px_Task_বাফার );
            }

            ফেরত xReturn;
        }
    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_vTaskDelete == 1 )
        শূন্য MPU_vTaskDelete( TaskHandle_t pxTaskToDelete ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskDelete( pxTaskToDelete );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTaskDelete( pxTaskToDelete );
            }
        }
    #endif /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskDelayUntil == 1 )
        BaseType_t MPU_xTaskDelayUntil( TickType_t * ধ্রুবক pxPreviousWakeTime,
                                        TickType_t xTimeIncrement ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
            }

            ফেরত xReturn;
        }
    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskAbortDelay == 1 )
        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            ফেরত xReturn;
        }
    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_vTaskDelay == 1 )
        শূন্য MPU_vTaskDelay( TickType_t xTicksToDelay ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskDelay( xTicksToDelay );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTaskDelay( xTicksToDelay );
            }
        }
    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_uxTaskPriorityGet == 1 )
        UBaseType_t MPU_uxTaskPriorityGet( ধ্রুবক TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskPriorityGet( pxTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                uxReturn = uxTaskPriorityGet( pxTask );
            }

            ফেরত uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_vTaskPrioritySet == 1 )
        শূন্য MPU_vTaskPrioritySet( TaskHandle_t pxTask,
                                   UBaseType_t uxNewPriority ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskPrioritySet( pxTask, uxNewPriority );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTaskPrioritySet( pxTask, uxNewPriority );
            }
        }
    #endif /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                eReturn = eTaskGetState( pxTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                eReturn = eTaskGetState( pxTask );
            }

            ফেরত eReturn;
        }
    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TRACE_FACILITY == 1 )
        শূন্য MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t x_Get_Free_স্তূপ_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_স্তূপ_Space, eState );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_স্তূপ_Space, eState );
            }
        }
    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( শূন্য ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            ফেরত xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_vTaskSuspend == 1 )
        শূন্য MPU_vTaskSuspend( TaskHandle_t pxTaskToSuspend ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSuspend( pxTaskToSuspend );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTaskSuspend( pxTaskToSuspend );
            }
        }
    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_vTaskSuspend == 1 )
        শূন্য MPU_vTaskResume( TaskHandle_t pxTaskToResume ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskResume( pxTaskToResume );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTaskResume( pxTaskToResume );
            }
        }
    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    শূন্য MPU_vTaskSuspendAll( শূন্য ) /* FREERTOS_SYSTEM_CALL */
    {
        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vTaskSuspendAll();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskResumeAll( শূন্য ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskResumeAll();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            xReturn = xTaskResumeAll();
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_গুনতি( শূন্য ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = x_Task_Get_Tick_গুনতি();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            xReturn = x_Task_Get_Tick_গুনতি();
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_সংখ্যা_Of_Tasks( শূন্য ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = ux_Task_Get_সংখ্যা_Of_Tasks();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            uxReturn = ux_Task_Get_সংখ্যা_Of_Tasks();
        }

        ফেরত uxReturn;
    }
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( ধ্রুবক অক্ষর * pcNameToQuery ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetHandle( pcNameToQuery );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskGetHandle( pcNameToQuery );
            }

            ফেরত xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        শূন্য MPU_vTaskListTasks( অক্ষর * pc_Write_বাফার,
                                 size_t ux_বাফার_দৈর্ঘ্য ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskListTasks( pc_Write_বাফার, ux_বাফার_দৈর্ঘ্য );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTaskListTasks( pc_Write_বাফার, ux_বাফার_দৈর্ঘ্য );
            }
        }
    #endif /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        শূন্য MPU_vTaskGetRunTimeStatistics( অক্ষর * pc_Write_বাফার,
                                            size_t ux_বাফার_দৈর্ঘ্য ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskGetRunTimeStatistics( pc_Write_বাফার, ux_বাফার_দৈর্ঘ্য );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTaskGetRunTimeStatistics( pc_Write_বাফার, ux_বাফার_দৈর্ঘ্য );
            }
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_RUN_TIME_গণক_TYPE MPU_ulTaskGetIdleRunTimePercent( শূন্য ) /* FREERTOS_SYSTEM_CALL */
        {
            config_RUN_TIME_গণক_TYPE xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = ulTaskGetIdleRunTimePercent();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = ulTaskGetIdleRunTimePercent();
            }

            ফেরত xReturn;
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Idle_Run_Time_গণক( শূন্য ) /* FREERTOS_SYSTEM_CALL */
        {
            config_RUN_TIME_গণক_TYPE xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = ul_Task_Get_Idle_Run_Time_গণক();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = ul_Task_Get_Idle_Run_Time_গণক();
            }

            ফেরত xReturn;
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_APPLICATION_TASK_TAG == 1 )
        শূন্য MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t px_Tag_মান ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSetApplicationTaskTag( xTask, px_Tag_মান );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTaskSetApplicationTaskTag( xTask, px_Tag_মান );
            }
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_APPLICATION_TASK_TAG == 1 )
        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetApplicationTaskTag( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskGetApplicationTaskTag( xTask );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( config_অঙ্ক_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        শূন্য MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t x_সূচক,
                                                    শূন্য * pv_মান ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSetThreadLocalStoragePointer( xTaskToSet, x_সূচক, pv_মান );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTaskSetThreadLocalStoragePointer( xTaskToSet, x_সূচক, pv_মান );
            }
        }
    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #যদি ( config_অঙ্ক_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        শূন্য * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t x_সূচক ) /* FREERTOS_SYSTEM_CALL */
        {
            শূন্য * pvReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, x_সূচক );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, x_সূচক );
            }

            ফেরত pvReturn;
        }
    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_APPLICATION_TASK_TAG == 1 )
        BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     শূন্য * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * pxTaskStatusArray,
                                              UBaseType_t ux_Array_আকার,
                                              config_RUN_TIME_গণক_TYPE * pul_যোগ_Run_Time ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, ux_Array_আকার, pul_যোগ_Run_Time );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, ux_Array_আকার, pul_যোগ_Run_Time );
            }

            ফেরত uxReturn;
        }
    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCatchUpTicks( TickType_t xTicksToCatchUp ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskCatchUpTicks( xTicksToCatchUp );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            xReturn = xTaskCatchUpTicks( xTicksToCatchUp );
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_ux_Task_Get_স্তূপ_উপরের_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = ux_Task_Get_স্তূপ_উপরের_Water_Mark( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                uxReturn = ux_Task_Get_স্তূপ_উপরের_Water_Mark( xTask );
            }

            ফেরত uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_ux_Task_Get_স্তূপ_উপরের_Water_Mark2 == 1 )
        config_স্তূপ_DEPTH_TYPE MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_স্তূপ_DEPTH_TYPE uxReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = ux_Task_Get_স্তূপ_উপরের_Water_Mark2( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                uxReturn = ux_Task_Get_স্তূপ_উপরের_Water_Mark2( xTask );
            }

            ফেরত uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( শূন্য ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            ফেরত xReturn;
        }
    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskGetSchedulerState == 1 )
        BaseType_t MPU_xTaskGetSchedulerState( শূন্য ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetSchedulerState();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskGetSchedulerState();
            }

            ফেরত xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    শূন্য MPU_vTaskSetTimeOutState( TimeOut_t * ধ্রুবক pxTimeOut ) /* FREERTOS_SYSTEM_CALL */
    {
        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vTaskSetTimeOutState( pxTimeOut );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            vTaskSetTimeOutState( pxTimeOut );
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * ধ্রুবক pxTimeOut,
                                         TickType_t * ধ্রুবক pxTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                                           UBaseType_t ux_সূচক_To_Notify,
                                           uint32_t ul_মান,
                                           eNotifyAction eAction,
                                           uint32_t * pul_Previous_Notification_মান ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotify( xTaskToNotify, ux_সূচক_To_Notify, ul_মান, eAction, pul_Previous_Notification_মান );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskGenericNotify( xTaskToNotify, ux_সূচক_To_Notify, ul_মান, eAction, pul_Previous_Notification_মান );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_সূচক_To_Wait_On,
                                               uint32_t ulBitsToClearOnEntry,
                                               uint32_t ulBitsToClearOnExit,
                                               uint32_t * pul_Notification_মান,
                                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyWait( ux_সূচক_To_Wait_On, ulBitsToClearOnEntry, ulBitsToClearOnExit, pul_Notification_মান, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskGenericNotifyWait( ux_সূচক_To_Wait_On, ulBitsToClearOnEntry, ulBitsToClearOnExit, pul_Notification_মান, xTicksToWait );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_সূচক_To_Wait_On,
                                              BaseType_t x_Clear_গুনতি_On_Exit,
                                              TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( ux_সূচক_To_Wait_On, x_Clear_গুনতি_On_Exit, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                ulReturn = ulTaskGenericNotifyTake( ux_সূচক_To_Wait_On, x_Clear_গুনতি_On_Exit, xTicksToWait );
            }

            ফেরত ulReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_সূচক_To_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, ux_সূচক_To_Clear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, ux_সূচক_To_Clear );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_মান_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_সূচক_To_Clear,
                                                    uint32_t ulBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ul_Task_Generic_Notify_মান_Clear( xTask, ux_সূচক_To_Clear, ulBitsToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                ulReturn = ul_Task_Generic_Notify_মান_Clear( xTask, ux_সূচক_To_Clear, ulBitsToClear );
            }

            ফেরত ulReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t ux_Queue_দৈর্ঘ্য,
                                               UBaseType_t ux_Item_আকার,
                                               uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreate( ux_Queue_দৈর্ঘ্য, ux_Item_আকার, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueGenericCreate( ux_Queue_দৈর্ঘ্য, ux_Item_আকার, ucQueueType );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_STATIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreateStatic( ধ্রুবক UBaseType_t ux_Queue_দৈর্ঘ্য,
                                                     ধ্রুবক UBaseType_t ux_Item_আকার,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     ধ্রুবক uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreateStatic( ux_Queue_দৈর্ঘ্য, ux_Item_আকার, pucQueueStorage, pxStaticQueue, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueGenericCreateStatic( ux_Queue_দৈর্ঘ্য, ux_Item_আকার, pucQueueStorage, pxStaticQueue, ucQueueType );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericReset( QueueHandle_t pxQueue,
                                       BaseType_t xNewQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      ধ্রুবক শূন্য * ধ্রুবক pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      BaseType_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaiting( ধ্রুবক QueueHandle_t pxQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = uxQueueMessagesWaiting( pxQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            uxReturn = uxQueueMessagesWaiting( pxQueue );
        }

        ফেরত uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailable( ধ্রুবক QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = uxQueueSpacesAvailable( xQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            uxReturn = uxQueueSpacesAvailable( xQueue );
        }

        ফেরত uxReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceive( QueueHandle_t pxQueue,
                                  শূন্য * ধ্রুবক pv_বাফার,
                                  TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueReceive( pxQueue, pv_বাফার, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            xReturn = xQueueReceive( pxQueue, pv_বাফার, xTicksToWait );
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               শূন্য * ধ্রুবক pv_বাফার,
                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueuePeek( xQueue, pv_বাফার, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            xReturn = xQueuePeek( xQueue, pv_বাফার, xTicksToWait );
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueSemaphoreTake( xQueue, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            xReturn = xQueueSemaphoreTake( xQueue, xTicksToWait );
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            শূন্য * xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGetMutexHolder( xSemaphore );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueGetMutexHolder( xSemaphore );
            }

            ফেরত xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutex( ধ্রুবক uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateMutex( ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueCreateMutex( ucQueueType );
            }

            ফেরত xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutexStatic( ধ্রুবক uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
            }

            ফেরত xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t ux_গুনতি_মান,
                                                         UBaseType_t ux_Initial_গুনতি ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateCountingSemaphore( ux_গুনতি_মান, ux_Initial_গুনতি );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueCreateCountingSemaphore( ux_গুনতি_মান, ux_Initial_গুনতি );
            }

            ফেরত xReturn;
        }
    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( ধ্রুবক UBaseType_t ux_Max_গুনতি,
                                                               ধ্রুবক UBaseType_t ux_Initial_গুনতি,
                                                               StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateCountingSemaphoreStatic( ux_Max_গুনতি, ux_Initial_গুনতি, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueCreateCountingSemaphoreStatic( ux_Max_গুনতি, ux_Initial_গুনতি, pxStaticQueue );
            }

            ফেরত xReturn;
        }
    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xBlockTime ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGiveMutexRecursive( xMutex );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueGiveMutexRecursive( xMutex );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSet( UBaseType_t ux_Event_Queue_দৈর্ঘ্য ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSet( ux_Event_Queue_দৈর্ঘ্য );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueCreateSet( ux_Event_Queue_দৈর্ঘ্য );
            }

            ফেরত xReturn;
        }
    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSetStatic( ধ্রুবক UBaseType_t ux_Event_Queue_দৈর্ঘ্য,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSetStatic( ux_Event_Queue_দৈর্ঘ্য, pucQueueStorage, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueCreateSetStatic( ux_Event_Queue_দৈর্ঘ্য, pucQueueStorage, pxStaticQueue );
            }

            ফেরত xReturn;
        }
    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_QUEUE_SETS == 1 )
        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        TickType_t xBlockTimeTicks ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetMemberHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueSelectFromSet( xQueueSet, xBlockTimeTicks );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueSelectFromSet( xQueueSet, xBlockTimeTicks );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueAddToSet( xQueueOrSemaphore, xQueueSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueAddToSet( xQueueOrSemaphore, xQueueSet );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                            QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueRemoveFromSet( xQueueOrSemaphore, xQueueSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xQueueRemoveFromSet( xQueueOrSemaphore, xQueueSet );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি config_QUEUE_REGISTRY_আকার > 0
        শূন্য MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      ধ্রুবক অক্ষর * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vQueueAddToRegistry( xQueue, pcName );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vQueueAddToRegistry( xQueue, pcName );
            }
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #যদি config_QUEUE_REGISTRY_আকার > 0
        শূন্য MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vQueueUnregisterQueue( xQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vQueueUnregisterQueue( xQueue );
            }
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #যদি config_QUEUE_REGISTRY_আকার > 0
        ধ্রুবক অক্ষর * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            ধ্রুবক অক্ষর * pcReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pcReturn = pcQueueGetName( xQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                pcReturn = pcQueueGetName( xQueue );
            }

            ফেরত pcReturn;
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    শূন্য MPU_vQueueDelete( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        যদি( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vQueueDelete( xQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        অন্যথা
        {
            vQueueDelete( xQueue );
        }
    }
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )
        শূন্য * MPU_pvTimerGetTimerID( ধ্রুবক TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            শূন্য * pvReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            ফেরত pvReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )
        শূন্য MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   শূন্য * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTimerSetTimerID( xTimer, pvNewID );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTimerSetTimerID( xTimer, pvNewID );
            }
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerIsTimerActive( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTimerIsTimerActive( xTimer );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( শূন্য ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )
        শূন্য MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      ধ্রুবক BaseType_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTimerSetReloadMode( xTimer, xAutoReload );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vTimerSetReloadMode( xTimer, xAutoReload );
            }
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTimerGetReloadMode( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                uxReturn = uxTimerGetReloadMode( xTimer );
            }

            ফেরত uxReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )
        ধ্রুবক অক্ষর * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ধ্রুবক অক্ষর * pcReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            ফেরত pcReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetExpiryTime( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTimerGetExpiryTime( xTimer );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ধ্রুবক BaseType_t xCommandID,
                                                     ধ্রুবক TickType_t x_Optional_মান,
                                                     BaseType_t * ধ্রুবক pxHigherPriorityTaskWoken,
                                                     ধ্রুবক TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_মান, pxHigherPriorityTaskWoken, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_মান, pxHigherPriorityTaskWoken, xTicksToWait );
            }

            ফেরত xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreate( শূন্য ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupCreate();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xEventGroupCreate();
            }

            ফেরত xReturn;
        }
    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreateStatic( StaticEventGroup_t * px_Event_Group_বাফার ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupCreateStatic( px_Event_Group_বাফার );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xEventGroupCreateStatic( px_Event_Group_বাফার );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                             ধ্রুবক EventBits_t uxBitsToWaitFor,
                                             ধ্রুবক BaseType_t xClearOnExit,
                                             ধ্রুবক BaseType_t xWaitForAllBits,
                                             TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupWaitBits( xEventGroup, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xEventGroupWaitBits( xEventGroup, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              ধ্রুবক EventBits_t uxBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupClearBits( xEventGroup, uxBitsToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xEventGroupClearBits( xEventGroup, uxBitsToClear );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            ধ্রুবক EventBits_t uxBitsToSet ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupSetBits( xEventGroup, uxBitsToSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xEventGroupSetBits( xEventGroup, uxBitsToSet );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         ধ্রুবক EventBits_t uxBitsToSet,
                                         ধ্রুবক EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupSync( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = xEventGroupSync( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )
        শূন্য MPU_vEventGroupDelete( EventGroupHandle_t xEventGroup ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vEventGroupDelete( xEventGroup );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                vEventGroupDelete( xEventGroup );
            }
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_x_Stream_বাফার_Send( Stream_বাফার_Handle_t x_Stream_বাফার,
                                      ধ্রুবক শূন্য * pv_Tx_তথ্য,
                                      size_t x_তথ্য_দৈর্ঘ্য_Bytes,
                                      TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_বাফার_Send( x_Stream_বাফার, pv_Tx_তথ্য, x_তথ্য_দৈর্ঘ্য_Bytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = x_Stream_বাফার_Send( x_Stream_বাফার, pv_Tx_তথ্য, x_তথ্য_দৈর্ঘ্য_Bytes, xTicksToWait );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes( x_Stream_বাফার );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes( x_Stream_বাফার );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_x_Stream_বাফার_Receive( Stream_বাফার_Handle_t x_Stream_বাফার,
                                         শূন্য * pv_Rx_তথ্য,
                                         size_t x_বাফার_দৈর্ঘ্য_Bytes,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_বাফার_Receive( x_Stream_বাফার, pv_Rx_তথ্য, x_বাফার_দৈর্ঘ্য_Bytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = x_Stream_বাফার_Receive( x_Stream_বাফার, pv_Rx_তথ্য, x_বাফার_দৈর্ঘ্য_Bytes, xTicksToWait );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )
        শূন্য MPU_v_Stream_বাফার_Delete( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
        {
            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                v_Stream_বাফার_Delete( x_Stream_বাফার );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                v_Stream_বাফার_Delete( x_Stream_বাফার );
            }
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_x_Stream_বাফার_Is_Full( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_বাফার_Is_Full( x_Stream_বাফার );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = x_Stream_বাফার_Is_Full( x_Stream_বাফার );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_x_Stream_বাফার_Is_Empty( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_বাফার_Is_Empty( x_Stream_বাফার );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = x_Stream_বাফার_Is_Empty( x_Stream_বাফার );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_x_Stream_বাফার_Reset( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_বাফার_Reset( x_Stream_বাফার );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = x_Stream_বাফার_Reset( x_Stream_বাফার );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_x_Stream_বাফার_Spaces_Available( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = x_Stream_বাফার_Spaces_Available( x_Stream_বাফার );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = x_Stream_বাফার_Spaces_Available( x_Stream_বাফার );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_x_Stream_বাফার_Bytes_Available( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_বাফার_Bytes_Available( x_Stream_বাফার );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = x_Stream_বাফার_Bytes_Available( x_Stream_বাফার );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_x_Stream_বাফার_Set_Trigger_Level( Stream_বাফার_Handle_t x_Stream_বাফার,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            যদি( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_বাফার_Set_Trigger_Level( x_Stream_বাফার, xTriggerLevel );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            অন্যথা
            {
                xReturn = x_Stream_বাফার_Set_Trigger_Level( x_Stream_বাফার, xTriggerLevel );
            }

            ফেরত xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
        Stream_বাফার_Handle_t MPU_x_Stream_বাফার_Generic_Create( size_t x_বাফার_আকার_Bytes,
                                                             size_t xTriggerLevelBytes,
                                                             BaseType_t x_Stream_বাফার_Type,
                                                             Stream_বাফার_Callback_Function_t pxSendCompletedCallback,
                                                             Stream_বাফার_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            Stream_বাফার_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ফাঁকা ) &&
                          ( pxReceiveCompletedCallback == ফাঁকা ) );

            যদি( ( pxSendCompletedCallback == ফাঁকা ) &&
                ( pxReceiveCompletedCallback == ফাঁকা ) )
            {
                যদি( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = x_Stream_বাফার_Generic_Create( x_বাফার_আকার_Bytes,
                                                          xTriggerLevelBytes,
                                                          x_Stream_বাফার_Type,
                                                          ফাঁকা,
                                                          ফাঁকা );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                অন্যথা
                {
                    xReturn = x_Stream_বাফার_Generic_Create( x_বাফার_আকার_Bytes,
                                                          xTriggerLevelBytes,
                                                          x_Stream_বাফার_Type,
                                                          ফাঁকা,
                                                          ফাঁকা );
                }
            }
            অন্যথা
            {
                trace_STREAM_বাফার_CREATE_FAILED( x_Stream_বাফার_Type );
                xReturn = ফাঁকা;
            }

            ফেরত xReturn;
        }
    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
        Stream_বাফার_Handle_t MPU_x_Stream_বাফার_Generic_Create_Static( size_t x_বাফার_আকার_Bytes,
                                                                   size_t xTriggerLevelBytes,
                                                                   BaseType_t x_Stream_বাফার_Type,
                                                                   uint8_t * ধ্রুবক puc_Stream_বাফার_Storage_Area,
                                                                   Static_Stream_বাফার_t * ধ্রুবক px_Static_Stream_বাফার,
                                                                   Stream_বাফার_Callback_Function_t pxSendCompletedCallback,
                                                                   Stream_বাফার_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            Stream_বাফার_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ফাঁকা ) &&
                          ( pxReceiveCompletedCallback == ফাঁকা ) );

            যদি( ( pxSendCompletedCallback == ফাঁকা ) &&
                ( pxReceiveCompletedCallback == ফাঁকা ) )
            {
                যদি( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = x_Stream_বাফার_Generic_Create_Static( x_বাফার_আকার_Bytes,
                                                                xTriggerLevelBytes,
                                                                x_Stream_বাফার_Type,
                                                                puc_Stream_বাফার_Storage_Area,
                                                                px_Static_Stream_বাফার,
                                                                ফাঁকা,
                                                                ফাঁকা );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                অন্যথা
                {
                    xReturn = x_Stream_বাফার_Generic_Create_Static( x_বাফার_আকার_Bytes,
                                                                xTriggerLevelBytes,
                                                                x_Stream_বাফার_Type,
                                                                puc_Stream_বাফার_Storage_Area,
                                                                px_Static_Stream_বাফার,
                                                                ফাঁকা,
                                                                ফাঁকা );
                }
            }
            অন্যথা
            {
                trace_STREAM_বাফার_CREATE_STATIC_FAILED( xReturn, x_Stream_বাফার_Type );
                xReturn = ফাঁকা;
            }

            ফেরত xReturn;
        }
    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
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

    #যদি configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #অন্তর্ভাব "application_defined_privileged_functions.h"
    #endif
/*-----------------------------------------------------------*/

#endif /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
