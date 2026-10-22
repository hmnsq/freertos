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
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "queue.h"
#अन्तर्भाव "timers.h"
#अन्तर्भाव "event_groups.h"
#अन्तर्भाव "stream_buffer.h"
#अन्तर्भाव "mpu_prototypes.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#यदि ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #error Access control list is not available with this MPU wrapper. Please set configENABLE_ACCESS_CONTROL_LIST to 0.
    #endif

    #यदि ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        BaseType_t MPU_xTaskCreate( TaskFunction_t pvTaskCode,
                                    ध्रुव वर्ण * ध्रुव pcName,
                                    ध्रुव config_ढेर_DEPTH_TYPE ux_ढेर_Depth,
                                    शून्य * pvParameters,
                                    UBaseType_t uxPriority,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #यदि ( configSUPPORT_STATIC_ALLOCATION == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                            ध्रुव वर्ण * ध्रुव pcName,
                                            ध्रुव config_ढेर_DEPTH_TYPE ux_ढेर_Depth,
                                            शून्य * ध्रुव pvParameters,
                                            UBaseType_t uxPriority,
                                            ढेर_Type_t * ध्रुव pux_ढेर_Buffer,
                                            StaticTask_t * ध्रुव pxTaskBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxPriority = uxPriority & ~( portPRIVILEGE_BIT );
                portMEMORY_BARRIER();

                xReturn = xTaskCreateStatic( pxTaskCode, pcName, ux_ढेर_Depth, pvParameters, uxPriority, pux_ढेर_Buffer, pxTaskBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskCreateStatic( pxTaskCode, pcName, ux_ढेर_Depth, pvParameters, uxPriority, pux_ढेर_Buffer, pxTaskBuffer );
            }

            प्रत्यागम xReturn;
        }
    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskDelete == 1 )
        शून्य MPU_vTaskDelete( TaskHandle_t pxTaskToDelete ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskDelayUntil == 1 )
        BaseType_t MPU_xTaskDelayUntil( TickType_t * ध्रुव pxPreviousWakeTime,
                                        TickType_t xTimeIncrement ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskAbortDelay == 1 )
        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskDelay == 1 )
        शून्य MPU_vTaskDelay( TickType_t xTicksToDelay ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_uxTaskPriorityGet == 1 )
        UBaseType_t MPU_uxTaskPriorityGet( ध्रुव TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskPrioritySet == 1 )
        शून्य MPU_vTaskPrioritySet( TaskHandle_t pxTask,
                                   UBaseType_t uxNewPriority ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम eReturn;
        }
    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TRACE_FACILITY == 1 )
        शून्य MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t x_Get_Free_ढेर_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskSuspend == 1 )
        शून्य MPU_vTaskSuspend( TaskHandle_t pxTaskToSuspend ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskSuspend == 1 )
        शून्य MPU_vTaskResume( TaskHandle_t pxTaskToResume ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    शून्य MPU_vTaskSuspendAll( शून्य ) /* FREERTOS_SYSTEM_CALL */
    {
        यदि( portIS_PRIVILEGED() == pdFALSE )
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

    BaseType_t MPU_xTaskResumeAll( शून्य ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
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

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_गिनती( शून्य ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
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

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_संख्या_Of_Tasks( शून्य ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
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

        प्रत्यागम uxReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( ध्रुव वर्ण * pcNameToQuery ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        शून्य MPU_vTaskListTasks( वर्ण * pcWriteBuffer,
                                 size_t uxBufferLength ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskListTasks( pcWriteBuffer, uxBufferLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskListTasks( pcWriteBuffer, uxBufferLength );
            }
        }
    #endif /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        शून्य MPU_vTaskGetRunTimeStatistics( वर्ण * pcWriteBuffer,
                                            size_t uxBufferLength ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskGetRunTimeStatistics( pcWriteBuffer, uxBufferLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskGetRunTimeStatistics( pcWriteBuffer, uxBufferLength );
            }
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = ulTaskGetIdleRunTimeCounter();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = ulTaskGetIdleRunTimeCounter();
            }

            प्रत्यागम xReturn;
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_APPLICATION_TASK_TAG == 1 )
        शून्य MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t px_Tag_मूल्य ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_APPLICATION_TASK_TAG == 1 )
        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_अंक_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        शून्य MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t xIndex,
                                                    शून्य * pv_मूल्य ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSetThreadLocalStoragePointer( xTaskToSet, xIndex, pv_मूल्य );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vTaskSetThreadLocalStoragePointer( xTaskToSet, xIndex, pv_मूल्य );
            }
        }
    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_अंक_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        शून्य * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t xIndex ) /* FREERTOS_SYSTEM_CALL */
        {
            शून्य * pvReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, xIndex );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, xIndex );
            }

            प्रत्यागम pvReturn;
        }
    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_APPLICATION_TASK_TAG == 1 )
        BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     शून्य * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * pxTaskStatusArray,
                                              UBaseType_t uxArraySize,
                                              configRUN_TIME_COUNTER_TYPE * pulTotalRunTime ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
            }

            प्रत्यागम uxReturn;
        }
    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCatchUpTicks( TickType_t xTicksToCatchUp ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
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

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_Get_ढेर_ऊपरी_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_ढेर_ऊपरी_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_Get_ढेर_ऊपरी_Water_Mark2 == 1 )
        config_ढेर_DEPTH_TYPE MPU_ux_Task_Get_ढेर_ऊपरी_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ढेर_DEPTH_TYPE uxReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetSchedulerState == 1 )
        BaseType_t MPU_xTaskGetSchedulerState( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    शून्य MPU_vTaskSetTimeOutState( TimeOut_t * ध्रुव pxTimeOut ) /* FREERTOS_SYSTEM_CALL */
    {
        यदि( portIS_PRIVILEGED() == pdFALSE )
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

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * ध्रुव pxTimeOut,
                                         TickType_t * ध्रुव pxTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
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

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                                           UBaseType_t uxIndexToNotify,
                                           uint32_t ul_मूल्य,
                                           eNotifyAction eAction,
                                           uint32_t * pul_Previous_Notification_मूल्य ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotify( xTaskToNotify, uxIndexToNotify, ul_मूल्य, eAction, pul_Previous_Notification_मूल्य );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGenericNotify( xTaskToNotify, uxIndexToNotify, ul_मूल्य, eAction, pul_Previous_Notification_मूल्य );
            }

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyWait( UBaseType_t uxIndexToWaitOn,
                                               uint32_t ulBitsToClearOnEntry,
                                               uint32_t ulBitsToClearOnExit,
                                               uint32_t * pul_Notification_मूल्य,
                                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyWait( uxIndexToWaitOn, ulBitsToClearOnEntry, ulBitsToClearOnExit, pul_Notification_मूल्य, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGenericNotifyWait( uxIndexToWaitOn, ulBitsToClearOnEntry, ulBitsToClearOnExit, pul_Notification_मूल्य, xTicksToWait );
            }

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                              BaseType_t x_Clear_गिनती_On_Exit,
                                              TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( uxIndexToWaitOn, x_Clear_गिनती_On_Exit, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                ulReturn = ulTaskGenericNotifyTake( uxIndexToWaitOn, x_Clear_गिनती_On_Exit, xTicksToWait );
            }

            प्रत्यागम ulReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t uxIndexToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, uxIndexToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, uxIndexToClear );
            }

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_मूल्य_Clear( TaskHandle_t xTask,
                                                    UBaseType_t uxIndexToClear,
                                                    uint32_t ulBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ul_Task_Generic_Notify_मूल्य_Clear( xTask, uxIndexToClear, ulBitsToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                ulReturn = ul_Task_Generic_Notify_मूल्य_Clear( xTask, uxIndexToClear, ulBitsToClear );
            }

            प्रत्यागम ulReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t uxQueueLength,
                                               UBaseType_t uxItemSize,
                                               uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );
            }

            प्रत्यागम xReturn;
        }
    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configSUPPORT_STATIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreateStatic( ध्रुव UBaseType_t uxQueueLength,
                                                     ध्रुव UBaseType_t uxItemSize,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     ध्रुव uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueGenericCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType );
            }

            प्रत्यागम xReturn;
        }
    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericReset( QueueHandle_t pxQueue,
                                       BaseType_t xNewQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
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

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      ध्रुव शून्य * ध्रुव pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      BaseType_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
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

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaiting( ध्रुव QueueHandle_t pxQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
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

        प्रत्यागम uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailable( ध्रुव QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
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

        प्रत्यागम uxReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceive( QueueHandle_t pxQueue,
                                  शून्य * ध्रुव pvBuffer,
                                  TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueReceive( pxQueue, pvBuffer, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueueReceive( pxQueue, pvBuffer, xTicksToWait );
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               शून्य * ध्रुव pvBuffer,
                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueuePeek( xQueue, pvBuffer, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueuePeek( xQueue, pvBuffer, xTicksToWait );
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        यदि( portIS_PRIVILEGED() == pdFALSE )
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

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            शून्य * xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutex( ध्रुव uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutexStatic( ध्रुव uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t ux_गिनती_मूल्य,
                                                         UBaseType_t ux_Initial_गिनती ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( ध्रुव UBaseType_t ux_Max_गिनती,
                                                               ध्रुव UBaseType_t ux_Initial_गिनती,
                                                               StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xBlockTime ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSet( UBaseType_t uxEventQueueLength ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSet( uxEventQueueLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateSet( uxEventQueueLength );
            }

            प्रत्यागम xReturn;
        }
    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSetStatic( ध्रुव UBaseType_t uxEventQueueLength,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSetStatic( uxEventQueueLength, pucQueueStorage, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateSetStatic( uxEventQueueLength, pucQueueStorage, pxStaticQueue );
            }

            प्रत्यागम xReturn;
        }
    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )
        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        TickType_t xBlockTimeTicks ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetMemberHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                            QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि configQUEUE_REGISTRY_SIZE > 0
        शून्य MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      ध्रुव वर्ण * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #यदि configQUEUE_REGISTRY_SIZE > 0
        शून्य MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #यदि configQUEUE_REGISTRY_SIZE > 0
        ध्रुव वर्ण * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            ध्रुव वर्ण * pcReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम pcReturn;
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    शून्य MPU_vQueueDelete( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        यदि( portIS_PRIVILEGED() == pdFALSE )
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

    #यदि ( configUSE_TIMERS == 1 )
        शून्य * MPU_pvTimerGetTimerID( ध्रुव TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            शून्य * pvReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम pvReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        शून्य MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   शून्य * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        शून्य MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      ध्रुव BaseType_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम uxReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        ध्रुव वर्ण * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ध्रुव वर्ण * pcReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम pcReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ध्रुव BaseType_t xCommandID,
                                                     ध्रुव TickType_t x_Optional_मूल्य,
                                                     BaseType_t * ध्रुव pxHigherPriorityTaskWoken,
                                                     ध्रुव TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreate( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreateStatic( StaticEventGroup_t * pxEventGroupBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupCreateStatic( pxEventGroupBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xEventGroupCreateStatic( pxEventGroupBuffer );
            }

            प्रत्यागम xReturn;
        }
    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                             ध्रुव EventBits_t uxBitsToWaitFor,
                                             ध्रुव BaseType_t xClearOnExit,
                                             ध्रुव BaseType_t xWaitForAllBits,
                                             TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              ध्रुव EventBits_t uxBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            ध्रुव EventBits_t uxBitsToSet ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         ध्रुव EventBits_t uxBitsToSet,
                                         ध्रुव EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
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

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )
        शून्य MPU_vEventGroupDelete( EventGroupHandle_t xEventGroup ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
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
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                                      ध्रुव शून्य * pvTxData,
                                      size_t xDataLengthBytes,
                                      TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferSend( xStreamBuffer, pvTxData, xDataLengthBytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xStreamBufferSend( xStreamBuffer, pvTxData, xDataLengthBytes, xTicksToWait );
            }

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferNextMessageLengthBytes( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xStreamBufferNextMessageLengthBytes( xStreamBuffer );
            }

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                         शून्य * pvRxData,
                                         size_t xBufferLengthBytes,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferReceive( xStreamBuffer, pvRxData, xBufferLengthBytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xStreamBufferReceive( xStreamBuffer, pvRxData, xBufferLengthBytes, xTicksToWait );
            }

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_STREAM_BUFFERS == 1 )
        शून्य MPU_vStreamBufferDelete( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vStreamBufferDelete( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                vStreamBufferDelete( xStreamBuffer );
            }
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferIsFull( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xStreamBufferIsFull( xStreamBuffer );
            }

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferIsEmpty( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xStreamBufferIsEmpty( xStreamBuffer );
            }

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferReset( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferReset( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xStreamBufferReset( xStreamBuffer );
            }

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xStreamBufferSpacesAvailable( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xStreamBufferSpacesAvailable( xStreamBuffer );
            }

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferBytesAvailable( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xStreamBufferBytesAvailable( xStreamBuffer );
            }

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            यदि( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferSetTriggerLevel( xStreamBuffer, xTriggerLevel );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            अन्यथा
            {
                xReturn = xStreamBufferSetTriggerLevel( xStreamBuffer, xTriggerLevel );
            }

            प्रत्यागम xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
        StreamBufferHandle_t MPU_xStreamBufferGenericCreate( size_t xBufferSizeBytes,
                                                             size_t xTriggerLevelBytes,
                                                             BaseType_t xStreamBufferType,
                                                             StreamBufferCallbackFunction_t pxSendCompletedCallback,
                                                             StreamBufferCallbackFunction_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            StreamBufferHandle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == रिक्त ) &&
                          ( pxReceiveCompletedCallback == रिक्त ) );

            यदि( ( pxSendCompletedCallback == रिक्त ) &&
                ( pxReceiveCompletedCallback == रिक्त ) )
            {
                यदि( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = xStreamBufferGenericCreate( xBufferSizeBytes,
                                                          xTriggerLevelBytes,
                                                          xStreamBufferType,
                                                          रिक्त,
                                                          रिक्त );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                अन्यथा
                {
                    xReturn = xStreamBufferGenericCreate( xBufferSizeBytes,
                                                          xTriggerLevelBytes,
                                                          xStreamBufferType,
                                                          रिक्त,
                                                          रिक्त );
                }
            }
            अन्यथा
            {
                traceSTREAM_BUFFER_CREATE_FAILED( xStreamBufferType );
                xReturn = रिक्त;
            }

            प्रत्यागम xReturn;
        }
    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
        StreamBufferHandle_t MPU_xStreamBufferGenericCreateStatic( size_t xBufferSizeBytes,
                                                                   size_t xTriggerLevelBytes,
                                                                   BaseType_t xStreamBufferType,
                                                                   uint8_t * ध्रुव pucStreamBufferStorageArea,
                                                                   StaticStreamBuffer_t * ध्रुव pxStaticStreamBuffer,
                                                                   StreamBufferCallbackFunction_t pxSendCompletedCallback,
                                                                   StreamBufferCallbackFunction_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            StreamBufferHandle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == रिक्त ) &&
                          ( pxReceiveCompletedCallback == रिक्त ) );

            यदि( ( pxSendCompletedCallback == रिक्त ) &&
                ( pxReceiveCompletedCallback == रिक्त ) )
            {
                यदि( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = xStreamBufferGenericCreateStatic( xBufferSizeBytes,
                                                                xTriggerLevelBytes,
                                                                xStreamBufferType,
                                                                pucStreamBufferStorageArea,
                                                                pxStaticStreamBuffer,
                                                                रिक्त,
                                                                रिक्त );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                अन्यथा
                {
                    xReturn = xStreamBufferGenericCreateStatic( xBufferSizeBytes,
                                                                xTriggerLevelBytes,
                                                                xStreamBufferType,
                                                                pucStreamBufferStorageArea,
                                                                pxStaticStreamBuffer,
                                                                रिक्त,
                                                                रिक्त );
                }
            }
            अन्यथा
            {
                traceSTREAM_BUFFER_CREATE_STATIC_FAILED( xReturn, xStreamBufferType );
                xReturn = रिक्त;
            }

            प्रत्यागम xReturn;
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

    #यदि configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #अन्तर्भाव "application_defined_privileged_functions.h"
    #endif
/*-----------------------------------------------------------*/

#endif /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
