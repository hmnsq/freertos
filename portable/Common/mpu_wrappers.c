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
#घोषणा MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "task.h"
#समावेश "queue.h"
#समावेश "timers.h"
#समावेश "event_groups.h"
#समावेश "stream_buffer.h"
#समावेश "mpu_prototypes.h"

#अघोषित MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#अगर ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #त्रुटि Access control list is not available with this MPU wrapper. Please set configENABLE_ACCESS_CONTROL_LIST to 0.
    #पूर्ण_अगर

    #अगर ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        BaseType_t MPU_xTaskCreate( TaskFunction_t pvTaskCode,
                                    स्थिर अक्षर * स्थिर pcName,
                                    स्थिर config_ढेर_DEPTH_TYPE ux_ढेर_Depth,
                                    व्योम * pvParameters,
                                    UBaseType_t uxPriority,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxPriority = uxPriority & ~( portPRIVILEGE_BIT );
                portMEMORY_BARRIER();

                xReturn = xTaskCreate( pvTaskCode, pcName, ux_ढेर_Depth, pvParameters, uxPriority, pxCreatedTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskCreate( pvTaskCode, pcName, ux_ढेर_Depth, pvParameters, uxPriority, pxCreatedTask );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_STATIC_ALLOCATION == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                            स्थिर अक्षर * स्थिर pcName,
                                            स्थिर config_ढेर_DEPTH_TYPE ux_ढेर_Depth,
                                            व्योम * स्थिर pvParameters,
                                            UBaseType_t uxPriority,
                                            ढेर_Type_t * स्थिर pux_ढेर_बफर,
                                            StaticTask_t * स्थिर px_Task_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxPriority = uxPriority & ~( portPRIVILEGE_BIT );
                portMEMORY_BARRIER();

                xReturn = xTaskCreateStatic( pxTaskCode, pcName, ux_ढेर_Depth, pvParameters, uxPriority, pux_ढेर_बफर, px_Task_बफर );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskCreateStatic( pxTaskCode, pcName, ux_ढेर_Depth, pvParameters, uxPriority, pux_ढेर_बफर, px_Task_बफर );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_vTaskDelete == 1 )
        व्योम MPU_vTaskDelete( TaskHandle_t pxTaskToDelete ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskDelete( pxTaskToDelete );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskDelete( pxTaskToDelete );
            }
        }
    #पूर्ण_अगर /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_xTaskDelayUntil == 1 )
        BaseType_t MPU_xTaskDelayUntil( TickType_t * स्थिर pxPreviousWakeTime,
                                        TickType_t xTimeIncrement ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_xTaskAbortDelay == 1 )
        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_vTaskDelay == 1 )
        व्योम MPU_vTaskDelay( TickType_t xTicksToDelay ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskDelay( xTicksToDelay );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskDelay( xTicksToDelay );
            }
        }
    #पूर्ण_अगर /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_uxTaskPriorityGet == 1 )
        UBaseType_t MPU_uxTaskPriorityGet( स्थिर TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskPriorityGet( pxTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                uxReturn = uxTaskPriorityGet( pxTask );
            }

            वापस uxReturn;
        }
    #पूर्ण_अगर /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_vTaskPrioritySet == 1 )
        व्योम MPU_vTaskPrioritySet( TaskHandle_t pxTask,
                                   UBaseType_t uxNewPriority ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskPrioritySet( pxTask, uxNewPriority );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskPrioritySet( pxTask, uxNewPriority );
            }
        }
    #पूर्ण_अगर /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                eReturn = eTaskGetState( pxTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                eReturn = eTaskGetState( pxTask );
            }

            वापस eReturn;
        }
    #पूर्ण_अगर /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TRACE_FACILITY == 1 )
        व्योम MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t x_Get_Free_ढेर_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_ढेर_Space, eState );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_ढेर_Space, eState );
            }
        }
    #पूर्ण_अगर /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( व्योम ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_vTaskSuspend == 1 )
        व्योम MPU_vTaskSuspend( TaskHandle_t pxTaskToSuspend ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSuspend( pxTaskToSuspend );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskSuspend( pxTaskToSuspend );
            }
        }
    #पूर्ण_अगर /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_vTaskSuspend == 1 )
        व्योम MPU_vTaskResume( TaskHandle_t pxTaskToResume ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskResume( pxTaskToResume );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskResume( pxTaskToResume );
            }
        }
    #पूर्ण_अगर /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    व्योम MPU_vTaskSuspendAll( व्योम ) /* FREERTOS_SYSTEM_CALL */
    {
        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vTaskSuspendAll();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskResumeAll( व्योम ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskResumeAll();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            xReturn = xTaskResumeAll();
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_गिनती( व्योम ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = x_Task_Get_Tick_गिनती();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            xReturn = x_Task_Get_Tick_गिनती();
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_संख्या_Of_Tasks( व्योम ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = ux_Task_Get_संख्या_Of_Tasks();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            uxReturn = ux_Task_Get_संख्या_Of_Tasks();
        }

        वापस uxReturn;
    }
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( स्थिर अक्षर * pcNameToQuery ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetHandle( pcNameToQuery );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGetHandle( pcNameToQuery );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        व्योम MPU_vTaskListTasks( अक्षर * pc_Write_बफर,
                                 माप_प्रकार ux_बफर_लंबाई ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskListTasks( pc_Write_बफर, ux_बफर_लंबाई );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskListTasks( pc_Write_बफर, ux_बफर_लंबाई );
            }
        }
    #पूर्ण_अगर /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        व्योम MPU_vTaskGetRunTimeStatistics( अक्षर * pc_Write_बफर,
                                            माप_प्रकार ux_बफर_लंबाई ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskGetRunTimeStatistics( pc_Write_बफर, ux_बफर_लंबाई );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskGetRunTimeStatistics( pc_Write_बफर, ux_बफर_लंबाई );
            }
        }
    #पूर्ण_अगर /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_RUN_TIME_गणक_TYPE MPU_ulTaskGetIdleRunTimePercent( व्योम ) /* FREERTOS_SYSTEM_CALL */
        {
            config_RUN_TIME_गणक_TYPE xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = ulTaskGetIdleRunTimePercent();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = ulTaskGetIdleRunTimePercent();
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_RUN_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_Run_Time_गणक( व्योम ) /* FREERTOS_SYSTEM_CALL */
        {
            config_RUN_TIME_गणक_TYPE xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = ul_Task_Get_Idle_Run_Time_गणक();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = ul_Task_Get_Idle_Run_Time_गणक();
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_APPLICATION_TASK_TAG == 1 )
        व्योम MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t px_Tag_मूल्य ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSetApplicationTaskTag( xTask, px_Tag_मूल्य );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskSetApplicationTaskTag( xTask, px_Tag_मूल्य );
            }
        }
    #पूर्ण_अगर /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_APPLICATION_TASK_TAG == 1 )
        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetApplicationTaskTag( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGetApplicationTaskTag( xTask );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( config_अंक_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        व्योम MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t x_सूचकांक,
                                                    व्योम * pv_मूल्य ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSetThreadLocalStoragePointer( xTaskToSet, x_सूचकांक, pv_मूल्य );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskSetThreadLocalStoragePointer( xTaskToSet, x_सूचकांक, pv_मूल्य );
            }
        }
    #पूर्ण_अगर /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #अगर ( config_अंक_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        व्योम * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t x_सूचकांक ) /* FREERTOS_SYSTEM_CALL */
        {
            व्योम * pvReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, x_सूचकांक );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, x_सूचकांक );
            }

            वापस pvReturn;
        }
    #पूर्ण_अगर /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_APPLICATION_TASK_TAG == 1 )
        BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     व्योम * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * pxTaskStatusArray,
                                              UBaseType_t ux_Array_आकार,
                                              config_RUN_TIME_गणक_TYPE * pul_योग_Run_Time ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, ux_Array_आकार, pul_योग_Run_Time );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, ux_Array_आकार, pul_योग_Run_Time );
            }

            वापस uxReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCatchUpTicks( TickType_t xTicksToCatchUp ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskCatchUpTicks( xTicksToCatchUp );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            xReturn = xTaskCatchUpTicks( xTicksToCatchUp );
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_ux_Task_Get_ढेर_ऊपरी_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_ढेर_ऊपरी_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = ux_Task_Get_ढेर_ऊपरी_Water_Mark( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                uxReturn = ux_Task_Get_ढेर_ऊपरी_Water_Mark( xTask );
            }

            वापस uxReturn;
        }
    #पूर्ण_अगर /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_ux_Task_Get_ढेर_ऊपरी_Water_Mark2 == 1 )
        config_ढेर_DEPTH_TYPE MPU_ux_Task_Get_ढेर_ऊपरी_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ढेर_DEPTH_TYPE uxReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = ux_Task_Get_ढेर_ऊपरी_Water_Mark2( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                uxReturn = ux_Task_Get_ढेर_ऊपरी_Water_Mark2( xTask );
            }

            वापस uxReturn;
        }
    #पूर्ण_अगर /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( व्योम ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_xTaskGetSchedulerState == 1 )
        BaseType_t MPU_xTaskGetSchedulerState( व्योम ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetSchedulerState();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGetSchedulerState();
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    व्योम MPU_vTaskSetTimeOutState( TimeOut_t * स्थिर pxTimeOut ) /* FREERTOS_SYSTEM_CALL */
    {
        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vTaskSetTimeOutState( pxTimeOut );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            vTaskSetTimeOutState( pxTimeOut );
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * स्थिर pxTimeOut,
                                         TickType_t * स्थिर pxTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                                           UBaseType_t ux_सूचकांक_To_Notify,
                                           uint32_t ul_मूल्य,
                                           eNotifyAction eAction,
                                           uint32_t * pul_Previous_Notification_मूल्य ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotify( xTaskToNotify, ux_सूचकांक_To_Notify, ul_मूल्य, eAction, pul_Previous_Notification_मूल्य );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGenericNotify( xTaskToNotify, ux_सूचकांक_To_Notify, ul_मूल्य, eAction, pul_Previous_Notification_मूल्य );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_सूचकांक_To_Wait_On,
                                               uint32_t ulBitsToClearOnEntry,
                                               uint32_t ulBitsToClearOnExit,
                                               uint32_t * pul_Notification_मूल्य,
                                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyWait( ux_सूचकांक_To_Wait_On, ulBitsToClearOnEntry, ulBitsToClearOnExit, pul_Notification_मूल्य, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGenericNotifyWait( ux_सूचकांक_To_Wait_On, ulBitsToClearOnEntry, ulBitsToClearOnExit, pul_Notification_मूल्य, xTicksToWait );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_सूचकांक_To_Wait_On,
                                              BaseType_t x_Clear_गिनती_On_Exit,
                                              TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( ux_सूचकांक_To_Wait_On, x_Clear_गिनती_On_Exit, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                ulReturn = ulTaskGenericNotifyTake( ux_सूचकांक_To_Wait_On, x_Clear_गिनती_On_Exit, xTicksToWait );
            }

            वापस ulReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_सूचकांक_To_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, ux_सूचकांक_To_Clear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, ux_सूचकांक_To_Clear );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_मूल्य_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_सूचकांक_To_Clear,
                                                    uint32_t ulBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ul_Task_Generic_Notify_मूल्य_Clear( xTask, ux_सूचकांक_To_Clear, ulBitsToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                ulReturn = ul_Task_Generic_Notify_मूल्य_Clear( xTask, ux_सूचकांक_To_Clear, ulBitsToClear );
            }

            वापस ulReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t ux_Queue_लंबाई,
                                               UBaseType_t ux_Item_आकार,
                                               uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreate( ux_Queue_लंबाई, ux_Item_आकार, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueGenericCreate( ux_Queue_लंबाई, ux_Item_आकार, ucQueueType );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_STATIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreateStatic( स्थिर UBaseType_t ux_Queue_लंबाई,
                                                     स्थिर UBaseType_t ux_Item_आकार,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     स्थिर uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreateStatic( ux_Queue_लंबाई, ux_Item_आकार, pucQueueStorage, pxStaticQueue, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueGenericCreateStatic( ux_Queue_लंबाई, ux_Item_आकार, pucQueueStorage, pxStaticQueue, ucQueueType );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericReset( QueueHandle_t pxQueue,
                                       BaseType_t xNewQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      स्थिर व्योम * स्थिर pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      BaseType_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaiting( स्थिर QueueHandle_t pxQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = uxQueueMessagesWaiting( pxQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            uxReturn = uxQueueMessagesWaiting( pxQueue );
        }

        वापस uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailable( स्थिर QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = uxQueueSpacesAvailable( xQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            uxReturn = uxQueueSpacesAvailable( xQueue );
        }

        वापस uxReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceive( QueueHandle_t pxQueue,
                                  व्योम * स्थिर pv_बफर,
                                  TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueReceive( pxQueue, pv_बफर, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueueReceive( pxQueue, pv_बफर, xTicksToWait );
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               व्योम * स्थिर pv_बफर,
                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueuePeek( xQueue, pv_बफर, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueuePeek( xQueue, pv_बफर, xTicksToWait );
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueSemaphoreTake( xQueue, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueueSemaphoreTake( xQueue, xTicksToWait );
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            व्योम * xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGetMutexHolder( xSemaphore );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueGetMutexHolder( xSemaphore );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutex( स्थिर uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateMutex( ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateMutex( ucQueueType );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutexStatic( स्थिर uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t ux_गिनती_मूल्य,
                                                         UBaseType_t ux_Initial_गिनती ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateCountingSemaphore( ux_गिनती_मूल्य, ux_Initial_गिनती );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateCountingSemaphore( ux_गिनती_मूल्य, ux_Initial_गिनती );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( स्थिर UBaseType_t ux_Max_गिनती,
                                                               स्थिर UBaseType_t ux_Initial_गिनती,
                                                               StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateCountingSemaphoreStatic( ux_Max_गिनती, ux_Initial_गिनती, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateCountingSemaphoreStatic( ux_Max_गिनती, ux_Initial_गिनती, pxStaticQueue );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xBlockTime ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGiveMutexRecursive( xMutex );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueGiveMutexRecursive( xMutex );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSet( UBaseType_t ux_Event_Queue_लंबाई ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSet( ux_Event_Queue_लंबाई );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateSet( ux_Event_Queue_लंबाई );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSetStatic( स्थिर UBaseType_t ux_Event_Queue_लंबाई,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSetStatic( ux_Event_Queue_लंबाई, pucQueueStorage, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateSetStatic( ux_Event_Queue_लंबाई, pucQueueStorage, pxStaticQueue );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_QUEUE_SETS == 1 )
        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        TickType_t xBlockTimeTicks ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetMemberHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueSelectFromSet( xQueueSet, xBlockTimeTicks );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueSelectFromSet( xQueueSet, xBlockTimeTicks );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueAddToSet( xQueueOrSemaphore, xQueueSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueAddToSet( xQueueOrSemaphore, xQueueSet );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                            QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueRemoveFromSet( xQueueOrSemaphore, xQueueSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueRemoveFromSet( xQueueOrSemaphore, xQueueSet );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर config_QUEUE_REGISTRY_आकार > 0
        व्योम MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      स्थिर अक्षर * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vQueueAddToRegistry( xQueue, pcName );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vQueueAddToRegistry( xQueue, pcName );
            }
        }
    #पूर्ण_अगर /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #अगर config_QUEUE_REGISTRY_आकार > 0
        व्योम MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vQueueUnregisterQueue( xQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vQueueUnregisterQueue( xQueue );
            }
        }
    #पूर्ण_अगर /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #अगर config_QUEUE_REGISTRY_आकार > 0
        स्थिर अक्षर * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            स्थिर अक्षर * pcReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pcReturn = pcQueueGetName( xQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                pcReturn = pcQueueGetName( xQueue );
            }

            वापस pcReturn;
        }
    #पूर्ण_अगर /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    व्योम MPU_vQueueDelete( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        अगर( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vQueueDelete( xQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            vQueueDelete( xQueue );
        }
    }
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )
        व्योम * MPU_pvTimerGetTimerID( स्थिर TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            व्योम * pvReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            वापस pvReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )
        व्योम MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   व्योम * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTimerSetTimerID( xTimer, pvNewID );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTimerSetTimerID( xTimer, pvNewID );
            }
        }
    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerIsTimerActive( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTimerIsTimerActive( xTimer );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( व्योम ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )
        व्योम MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      स्थिर BaseType_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTimerSetReloadMode( xTimer, xAutoReload );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTimerSetReloadMode( xTimer, xAutoReload );
            }
        }
    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTimerGetReloadMode( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                uxReturn = uxTimerGetReloadMode( xTimer );
            }

            वापस uxReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )
        स्थिर अक्षर * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            स्थिर अक्षर * pcReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            वापस pcReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetExpiryTime( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTimerGetExpiryTime( xTimer );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     स्थिर BaseType_t xCommandID,
                                                     स्थिर TickType_t x_Optional_मूल्य,
                                                     BaseType_t * स्थिर pxHigherPriorityTaskWoken,
                                                     स्थिर TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_मूल्य, pxHigherPriorityTaskWoken, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_मूल्य, pxHigherPriorityTaskWoken, xTicksToWait );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreate( व्योम ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupCreate();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xEventGroupCreate();
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreateStatic( StaticEventGroup_t * px_Event_Group_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupCreateStatic( px_Event_Group_बफर );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xEventGroupCreateStatic( px_Event_Group_बफर );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                             स्थिर EventBits_t uxBitsToWaitFor,
                                             स्थिर BaseType_t xClearOnExit,
                                             स्थिर BaseType_t xWaitForAllBits,
                                             TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupWaitBits( xEventGroup, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xEventGroupWaitBits( xEventGroup, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              स्थिर EventBits_t uxBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupClearBits( xEventGroup, uxBitsToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xEventGroupClearBits( xEventGroup, uxBitsToClear );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            स्थिर EventBits_t uxBitsToSet ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupSetBits( xEventGroup, uxBitsToSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xEventGroupSetBits( xEventGroup, uxBitsToSet );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         स्थिर EventBits_t uxBitsToSet,
                                         स्थिर EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupSync( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xEventGroupSync( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_EVENT_GROUPS == 1 )
        व्योम MPU_vEventGroupDelete( EventGroupHandle_t xEventGroup ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vEventGroupDelete( xEventGroup );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vEventGroupDelete( xEventGroup );
            }
        }
    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )
        माप_प्रकार MPU_x_Stream_बफर_Send( Stream_बफर_Handle_t x_Stream_बफर,
                                      स्थिर व्योम * pv_Tx_तथ्य,
                                      माप_प्रकार x_तथ्य_लंबाई_Bytes,
                                      TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            माप_प्रकार xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_बफर_Send( x_Stream_बफर, pv_Tx_तथ्य, x_तथ्य_लंबाई_Bytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Stream_बफर_Send( x_Stream_बफर, pv_Tx_तथ्य, x_तथ्य_लंबाई_Bytes, xTicksToWait );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )
        माप_प्रकार MPU_x_Stream_बफर_अग्र_Message_लंबाई_Bytes( Stream_बफर_Handle_t x_Stream_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            माप_प्रकार xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_बफर_अग्र_Message_लंबाई_Bytes( x_Stream_बफर );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Stream_बफर_अग्र_Message_लंबाई_Bytes( x_Stream_बफर );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )
        माप_प्रकार MPU_x_Stream_बफर_Receive( Stream_बफर_Handle_t x_Stream_बफर,
                                         व्योम * pv_Rx_तथ्य,
                                         माप_प्रकार x_बफर_लंबाई_Bytes,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            माप_प्रकार xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_बफर_Receive( x_Stream_बफर, pv_Rx_तथ्य, x_बफर_लंबाई_Bytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Stream_बफर_Receive( x_Stream_बफर, pv_Rx_तथ्य, x_बफर_लंबाई_Bytes, xTicksToWait );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )
        व्योम MPU_v_Stream_बफर_Delete( Stream_बफर_Handle_t x_Stream_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                v_Stream_बफर_Delete( x_Stream_बफर );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                v_Stream_बफर_Delete( x_Stream_बफर );
            }
        }
    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_x_Stream_बफर_Is_Full( Stream_बफर_Handle_t x_Stream_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_बफर_Is_Full( x_Stream_बफर );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Stream_बफर_Is_Full( x_Stream_बफर );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_x_Stream_बफर_Is_Empty( Stream_बफर_Handle_t x_Stream_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_बफर_Is_Empty( x_Stream_बफर );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Stream_बफर_Is_Empty( x_Stream_बफर );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_x_Stream_बफर_Reset( Stream_बफर_Handle_t x_Stream_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_बफर_Reset( x_Stream_बफर );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Stream_बफर_Reset( x_Stream_बफर );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )
        माप_प्रकार MPU_x_Stream_बफर_Spaces_Available( Stream_बफर_Handle_t x_Stream_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            माप_प्रकार xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = x_Stream_बफर_Spaces_Available( x_Stream_बफर );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Stream_बफर_Spaces_Available( x_Stream_बफर );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )
        माप_प्रकार MPU_x_Stream_बफर_Bytes_Available( Stream_बफर_Handle_t x_Stream_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            माप_प्रकार xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_बफर_Bytes_Available( x_Stream_बफर );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Stream_बफर_Bytes_Available( x_Stream_बफर );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_x_Stream_बफर_Set_Trigger_Level( Stream_बफर_Handle_t x_Stream_बफर,
                                                     माप_प्रकार xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            अगर( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = x_Stream_बफर_Set_Trigger_Level( x_Stream_बफर, xTriggerLevel );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Stream_बफर_Set_Trigger_Level( x_Stream_बफर, xTriggerLevel );
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
        Stream_बफर_Handle_t MPU_x_Stream_बफर_Generic_Create( माप_प्रकार x_बफर_आकार_Bytes,
                                                             माप_प्रकार xTriggerLevelBytes,
                                                             BaseType_t x_Stream_बफर_Type,
                                                             Stream_बफर_Callback_Function_t pxSendCompletedCallback,
                                                             Stream_बफर_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            Stream_बफर_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == शून्य ) &&
                          ( pxReceiveCompletedCallback == शून्य ) );

            अगर( ( pxSendCompletedCallback == शून्य ) &&
                ( pxReceiveCompletedCallback == शून्य ) )
            {
                अगर( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = x_Stream_बफर_Generic_Create( x_बफर_आकार_Bytes,
                                                          xTriggerLevelBytes,
                                                          x_Stream_बफर_Type,
                                                          शून्य,
                                                          शून्य );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                अन्यथा
                {
                    xReturn = x_Stream_बफर_Generic_Create( x_बफर_आकार_Bytes,
                                                          xTriggerLevelBytes,
                                                          x_Stream_बफर_Type,
                                                          शून्य,
                                                          शून्य );
                }
            }
            अन्यथा
            {
                trace_STREAM_बफर_CREATE_FAILED( x_Stream_बफर_Type );
                xReturn = शून्य;
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
        Stream_बफर_Handle_t MPU_x_Stream_बफर_Generic_Create_Static( माप_प्रकार x_बफर_आकार_Bytes,
                                                                   माप_प्रकार xTriggerLevelBytes,
                                                                   BaseType_t x_Stream_बफर_Type,
                                                                   uint8_t * स्थिर puc_Stream_बफर_Storage_Area,
                                                                   Static_Stream_बफर_t * स्थिर px_Static_Stream_बफर,
                                                                   Stream_बफर_Callback_Function_t pxSendCompletedCallback,
                                                                   Stream_बफर_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            Stream_बफर_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == शून्य ) &&
                          ( pxReceiveCompletedCallback == शून्य ) );

            अगर( ( pxSendCompletedCallback == शून्य ) &&
                ( pxReceiveCompletedCallback == शून्य ) )
            {
                अगर( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = x_Stream_बफर_Generic_Create_Static( x_बफर_आकार_Bytes,
                                                                xTriggerLevelBytes,
                                                                x_Stream_बफर_Type,
                                                                puc_Stream_बफर_Storage_Area,
                                                                px_Static_Stream_बफर,
                                                                शून्य,
                                                                शून्य );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                अन्यथा
                {
                    xReturn = x_Stream_बफर_Generic_Create_Static( x_बफर_आकार_Bytes,
                                                                xTriggerLevelBytes,
                                                                x_Stream_बफर_Type,
                                                                puc_Stream_बफर_Storage_Area,
                                                                px_Static_Stream_बफर,
                                                                शून्य,
                                                                शून्य );
                }
            }
            अन्यथा
            {
                trace_STREAM_बफर_CREATE_STATIC_FAILED( xReturn, x_Stream_बफर_Type );
                xReturn = शून्य;
            }

            वापस xReturn;
        }
    #पूर्ण_अगर /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
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

    #अगर configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #समावेश "application_defined_privileged_functions.h"
    #पूर्ण_अगर
/*-----------------------------------------------------------*/

#पूर्ण_अगर /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
