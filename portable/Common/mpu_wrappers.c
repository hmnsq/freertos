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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "queue.h"
#ಅನ್ತರ್ಭಾವ "timers.h"
#ಅನ್ತರ್ಭಾವ "event_groups.h"
#ಅನ್ತರ್ಭಾವ "stream_buffer.h"
#ಅನ್ತರ್ಭಾವ "mpu_prototypes.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ಯದಿ ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #ಯದಿ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #error Access control list is not available with this MPU wrapper. Please set configENABLE_ACCESS_CONTROL_LIST to 0.
    #endif

    #ಯದಿ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        BaseType_t MPU_xTaskCreate( TaskFunction_t pvTaskCode,
                                    ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ pcName,
                                    ಧ್ರುವ config_ರಾಶಿ_DEPTH_TYPE ux_ರಾಶಿ_Depth,
                                    ಶೂನ್ಯ * pvParameters,
                                    UBaseType_t uxPriority,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxPriority = uxPriority & ~( portPRIVILEGE_BIT );
                portMEMORY_BARRIER();

                xReturn = xTaskCreate( pvTaskCode, pcName, ux_ರಾಶಿ_Depth, pvParameters, uxPriority, pxCreatedTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskCreate( pvTaskCode, pcName, ux_ರಾಶಿ_Depth, pvParameters, uxPriority, pxCreatedTask );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_STATIC_ALLOCATION == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                            ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ pcName,
                                            ಧ್ರುವ config_ರಾಶಿ_DEPTH_TYPE ux_ರಾಶಿ_Depth,
                                            ಶೂನ್ಯ * ಧ್ರುವ pvParameters,
                                            UBaseType_t uxPriority,
                                            ರಾಶಿ_Type_t * ಧ್ರುವ pux_ರಾಶಿ_Buffer,
                                            StaticTask_t * ಧ್ರುವ pxTaskBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxPriority = uxPriority & ~( portPRIVILEGE_BIT );
                portMEMORY_BARRIER();

                xReturn = xTaskCreateStatic( pxTaskCode, pcName, ux_ರಾಶಿ_Depth, pvParameters, uxPriority, pux_ರಾಶಿ_Buffer, pxTaskBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskCreateStatic( pxTaskCode, pcName, ux_ರಾಶಿ_Depth, pvParameters, uxPriority, pux_ರಾಶಿ_Buffer, pxTaskBuffer );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_vTaskDelete == 1 )
        ಶೂನ್ಯ MPU_vTaskDelete( TaskHandle_t pxTaskToDelete ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskDelete( pxTaskToDelete );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTaskDelete( pxTaskToDelete );
            }
        }
    #endif /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskDelayUntil == 1 )
        BaseType_t MPU_xTaskDelayUntil( TickType_t * ಧ್ರುವ pxPreviousWakeTime,
                                        TickType_t xTimeIncrement ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskAbortDelay == 1 )
        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_vTaskDelay == 1 )
        ಶೂನ್ಯ MPU_vTaskDelay( TickType_t xTicksToDelay ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskDelay( xTicksToDelay );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTaskDelay( xTicksToDelay );
            }
        }
    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_uxTaskPriorityGet == 1 )
        UBaseType_t MPU_uxTaskPriorityGet( ಧ್ರುವ TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskPriorityGet( pxTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                uxReturn = uxTaskPriorityGet( pxTask );
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_vTaskPrioritySet == 1 )
        ಶೂನ್ಯ MPU_vTaskPrioritySet( TaskHandle_t pxTask,
                                   UBaseType_t uxNewPriority ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskPrioritySet( pxTask, uxNewPriority );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTaskPrioritySet( pxTask, uxNewPriority );
            }
        }
    #endif /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                eReturn = eTaskGetState( pxTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                eReturn = eTaskGetState( pxTask );
            }

            ಪ್ರತ್ಯಾಗಮ eReturn;
        }
    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TRACE_FACILITY == 1 )
        ಶೂನ್ಯ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t x_Get_Free_ರಾಶಿ_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_ರಾಶಿ_Space, eState );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_ರಾಶಿ_Space, eState );
            }
        }
    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_vTaskSuspend == 1 )
        ಶೂನ್ಯ MPU_vTaskSuspend( TaskHandle_t pxTaskToSuspend ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSuspend( pxTaskToSuspend );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTaskSuspend( pxTaskToSuspend );
            }
        }
    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_vTaskSuspend == 1 )
        ಶೂನ್ಯ MPU_vTaskResume( TaskHandle_t pxTaskToResume ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskResume( pxTaskToResume );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTaskResume( pxTaskToResume );
            }
        }
    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_vTaskSuspendAll( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
    {
        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vTaskSuspendAll();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskResumeAll( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskResumeAll();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            xReturn = xTaskResumeAll();
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = x_Task_Get_Tick_ಎಣಿಕೆ();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            xReturn = x_Task_Get_Tick_ಎಣಿಕೆ();
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_Of_Tasks( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = ux_Task_Get_ಸಂಖ್ಯೆ_Of_Tasks();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            uxReturn = ux_Task_Get_ಸಂಖ್ಯೆ_Of_Tasks();
        }

        ಪ್ರತ್ಯಾಗಮ uxReturn;
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( ಧ್ರುವ ವರ್ಣ * pcNameToQuery ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetHandle( pcNameToQuery );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskGetHandle( pcNameToQuery );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        ಶೂನ್ಯ MPU_vTaskListTasks( ವರ್ಣ * pcWriteBuffer,
                                 size_t uxBufferLength ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskListTasks( pcWriteBuffer, uxBufferLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTaskListTasks( pcWriteBuffer, uxBufferLength );
            }
        }
    #endif /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        ಶೂನ್ಯ MPU_vTaskGetRunTimeStatistics( ವರ್ಣ * pcWriteBuffer,
                                            size_t uxBufferLength ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskGetRunTimeStatistics( pcWriteBuffer, uxBufferLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTaskGetRunTimeStatistics( pcWriteBuffer, uxBufferLength );
            }
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = ulTaskGetIdleRunTimePercent();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = ulTaskGetIdleRunTimePercent();
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = ulTaskGetIdleRunTimeCounter();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = ulTaskGetIdleRunTimeCounter();
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_APPLICATION_TASK_TAG == 1 )
        ಶೂನ್ಯ MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t px_Tag_ಮೌಲ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSetApplicationTaskTag( xTask, px_Tag_ಮೌಲ್ಯ );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTaskSetApplicationTaskTag( xTask, px_Tag_ಮೌಲ್ಯ );
            }
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_APPLICATION_TASK_TAG == 1 )
        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetApplicationTaskTag( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskGetApplicationTaskTag( xTask );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        ಶೂನ್ಯ MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t xIndex,
                                                    ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSetThreadLocalStoragePointer( xTaskToSet, xIndex, pv_ಮೌಲ್ಯ );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTaskSetThreadLocalStoragePointer( xTaskToSet, xIndex, pv_ಮೌಲ್ಯ );
            }
        }
    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        ಶೂನ್ಯ * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t xIndex ) /* FREERTOS_SYSTEM_CALL */
        {
            ಶೂನ್ಯ * pvReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, xIndex );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, xIndex );
            }

            ಪ್ರತ್ಯಾಗಮ pvReturn;
        }
    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_APPLICATION_TASK_TAG == 1 )
        BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     ಶೂನ್ಯ * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * pxTaskStatusArray,
                                              UBaseType_t uxArraySize,
                                              configRUN_TIME_COUNTER_TYPE * pulTotalRunTime ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }
    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCatchUpTicks( TickType_t xTicksToCatchUp ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskCatchUpTicks( xTicksToCatchUp );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            xReturn = xTaskCatchUpTicks( xTicksToCatchUp );
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( xTask );
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2 == 1 )
        config_ರಾಶಿ_DEPTH_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ರಾಶಿ_DEPTH_TYPE uxReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( xTask );
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskGetSchedulerState == 1 )
        BaseType_t MPU_xTaskGetSchedulerState( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetSchedulerState();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskGetSchedulerState();
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_vTaskSetTimeOutState( TimeOut_t * ಧ್ರುವ pxTimeOut ) /* FREERTOS_SYSTEM_CALL */
    {
        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vTaskSetTimeOutState( pxTimeOut );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            vTaskSetTimeOutState( pxTimeOut );
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * ಧ್ರುವ pxTimeOut,
                                         TickType_t * ಧ್ರುವ pxTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                                           UBaseType_t uxIndexToNotify,
                                           uint32_t ul_ಮೌಲ್ಯ,
                                           eNotifyAction eAction,
                                           uint32_t * pul_Previous_Notification_ಮೌಲ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotify( xTaskToNotify, uxIndexToNotify, ul_ಮೌಲ್ಯ, eAction, pul_Previous_Notification_ಮೌಲ್ಯ );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskGenericNotify( xTaskToNotify, uxIndexToNotify, ul_ಮೌಲ್ಯ, eAction, pul_Previous_Notification_ಮೌಲ್ಯ );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyWait( UBaseType_t uxIndexToWaitOn,
                                               uint32_t ulBitsToClearOnEntry,
                                               uint32_t ulBitsToClearOnExit,
                                               uint32_t * pul_Notification_ಮೌಲ್ಯ,
                                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyWait( uxIndexToWaitOn, ulBitsToClearOnEntry, ulBitsToClearOnExit, pul_Notification_ಮೌಲ್ಯ, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskGenericNotifyWait( uxIndexToWaitOn, ulBitsToClearOnEntry, ulBitsToClearOnExit, pul_Notification_ಮೌಲ್ಯ, xTicksToWait );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                              BaseType_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                              TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( uxIndexToWaitOn, x_Clear_ಎಣಿಕೆ_On_Exit, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                ulReturn = ulTaskGenericNotifyTake( uxIndexToWaitOn, x_Clear_ಎಣಿಕೆ_On_Exit, xTicksToWait );
            }

            ಪ್ರತ್ಯಾಗಮ ulReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t uxIndexToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, uxIndexToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, uxIndexToClear );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t uxIndexToClear,
                                                    uint32_t ulBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( xTask, uxIndexToClear, ulBitsToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                ulReturn = ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( xTask, uxIndexToClear, ulBitsToClear );
            }

            ಪ್ರತ್ಯಾಗಮ ulReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t uxQueueLength,
                                               UBaseType_t uxItemSize,
                                               uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_STATIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreateStatic( ಧ್ರುವ UBaseType_t uxQueueLength,
                                                     ಧ್ರುವ UBaseType_t uxItemSize,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     ಧ್ರುವ uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueGenericCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericReset( QueueHandle_t pxQueue,
                                       BaseType_t xNewQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      ಧ್ರುವ ಶೂನ್ಯ * ಧ್ರುವ pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      BaseType_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaiting( ಧ್ರುವ QueueHandle_t pxQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = uxQueueMessagesWaiting( pxQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            uxReturn = uxQueueMessagesWaiting( pxQueue );
        }

        ಪ್ರತ್ಯಾಗಮ uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailable( ಧ್ರುವ QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = uxQueueSpacesAvailable( xQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            uxReturn = uxQueueSpacesAvailable( xQueue );
        }

        ಪ್ರತ್ಯಾಗಮ uxReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceive( QueueHandle_t pxQueue,
                                  ಶೂನ್ಯ * ಧ್ರುವ pvBuffer,
                                  TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueReceive( pxQueue, pvBuffer, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            xReturn = xQueueReceive( pxQueue, pvBuffer, xTicksToWait );
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               ಶೂನ್ಯ * ಧ್ರುವ pvBuffer,
                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueuePeek( xQueue, pvBuffer, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            xReturn = xQueuePeek( xQueue, pvBuffer, xTicksToWait );
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueSemaphoreTake( xQueue, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            xReturn = xQueueSemaphoreTake( xQueue, xTicksToWait );
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            ಶೂನ್ಯ * xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGetMutexHolder( xSemaphore );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueGetMutexHolder( xSemaphore );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutex( ಧ್ರುವ uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateMutex( ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueCreateMutex( ucQueueType );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutexStatic( ಧ್ರುವ uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t ux_ಎಣಿಕೆ_ಮೌಲ್ಯ,
                                                         UBaseType_t ux_Initial_ಎಣಿಕೆ ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateCountingSemaphore( ux_ಎಣಿಕೆ_ಮೌಲ್ಯ, ux_Initial_ಎಣಿಕೆ );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueCreateCountingSemaphore( ux_ಎಣಿಕೆ_ಮೌಲ್ಯ, ux_Initial_ಎಣಿಕೆ );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( ಧ್ರುವ UBaseType_t ux_Max_ಎಣಿಕೆ,
                                                               ಧ್ರುವ UBaseType_t ux_Initial_ಎಣಿಕೆ,
                                                               StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateCountingSemaphoreStatic( ux_Max_ಎಣಿಕೆ, ux_Initial_ಎಣಿಕೆ, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueCreateCountingSemaphoreStatic( ux_Max_ಎಣಿಕೆ, ux_Initial_ಎಣಿಕೆ, pxStaticQueue );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xBlockTime ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGiveMutexRecursive( xMutex );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueGiveMutexRecursive( xMutex );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSet( UBaseType_t uxEventQueueLength ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSet( uxEventQueueLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueCreateSet( uxEventQueueLength );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSetStatic( ಧ್ರುವ UBaseType_t uxEventQueueLength,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSetStatic( uxEventQueueLength, pucQueueStorage, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueCreateSetStatic( uxEventQueueLength, pucQueueStorage, pxStaticQueue );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_QUEUE_SETS == 1 )
        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        TickType_t xBlockTimeTicks ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetMemberHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueSelectFromSet( xQueueSet, xBlockTimeTicks );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueSelectFromSet( xQueueSet, xBlockTimeTicks );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueAddToSet( xQueueOrSemaphore, xQueueSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueAddToSet( xQueueOrSemaphore, xQueueSet );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                            QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueRemoveFromSet( xQueueOrSemaphore, xQueueSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xQueueRemoveFromSet( xQueueOrSemaphore, xQueueSet );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ configQUEUE_REGISTRY_SIZE > 0
        ಶೂನ್ಯ MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      ಧ್ರುವ ವರ್ಣ * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vQueueAddToRegistry( xQueue, pcName );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vQueueAddToRegistry( xQueue, pcName );
            }
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ಯದಿ configQUEUE_REGISTRY_SIZE > 0
        ಶೂನ್ಯ MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vQueueUnregisterQueue( xQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vQueueUnregisterQueue( xQueue );
            }
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ಯದಿ configQUEUE_REGISTRY_SIZE > 0
        ಧ್ರುವ ವರ್ಣ * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            ಧ್ರುವ ವರ್ಣ * pcReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pcReturn = pcQueueGetName( xQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                pcReturn = pcQueueGetName( xQueue );
            }

            ಪ್ರತ್ಯಾಗಮ pcReturn;
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_vQueueDelete( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vQueueDelete( xQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        ಅನ್ಯಥಾ
        {
            vQueueDelete( xQueue );
        }
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )
        ಶೂನ್ಯ * MPU_pvTimerGetTimerID( ಧ್ರುವ TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ಶೂನ್ಯ * pvReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            ಪ್ರತ್ಯಾಗಮ pvReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )
        ಶೂನ್ಯ MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   ಶೂನ್ಯ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTimerSetTimerID( xTimer, pvNewID );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTimerSetTimerID( xTimer, pvNewID );
            }
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerIsTimerActive( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTimerIsTimerActive( xTimer );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )
        ಶೂನ್ಯ MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      ಧ್ರುವ BaseType_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTimerSetReloadMode( xTimer, xAutoReload );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vTimerSetReloadMode( xTimer, xAutoReload );
            }
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTimerGetReloadMode( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                uxReturn = uxTimerGetReloadMode( xTimer );
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )
        ಧ್ರುವ ವರ್ಣ * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ಧ್ರುವ ವರ್ಣ * pcReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            ಪ್ರತ್ಯಾಗಮ pcReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetExpiryTime( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTimerGetExpiryTime( xTimer );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ಧ್ರುವ BaseType_t xCommandID,
                                                     ಧ್ರುವ TickType_t x_Optional_ಮೌಲ್ಯ,
                                                     BaseType_t * ಧ್ರುವ pxHigherPriorityTaskWoken,
                                                     ಧ್ರುವ TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_ಮೌಲ್ಯ, pxHigherPriorityTaskWoken, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_ಮೌಲ್ಯ, pxHigherPriorityTaskWoken, xTicksToWait );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreate( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupCreate();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xEventGroupCreate();
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreateStatic( StaticEventGroup_t * pxEventGroupBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupCreateStatic( pxEventGroupBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xEventGroupCreateStatic( pxEventGroupBuffer );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                             ಧ್ರುವ EventBits_t uxBitsToWaitFor,
                                             ಧ್ರುವ BaseType_t xClearOnExit,
                                             ಧ್ರುವ BaseType_t xWaitForAllBits,
                                             TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupWaitBits( xEventGroup, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xEventGroupWaitBits( xEventGroup, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              ಧ್ರುವ EventBits_t uxBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupClearBits( xEventGroup, uxBitsToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xEventGroupClearBits( xEventGroup, uxBitsToClear );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            ಧ್ರುವ EventBits_t uxBitsToSet ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupSetBits( xEventGroup, uxBitsToSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xEventGroupSetBits( xEventGroup, uxBitsToSet );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         ಧ್ರುವ EventBits_t uxBitsToSet,
                                         ಧ್ರುವ EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupSync( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xEventGroupSync( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )
        ಶೂನ್ಯ MPU_vEventGroupDelete( EventGroupHandle_t xEventGroup ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vEventGroupDelete( xEventGroup );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vEventGroupDelete( xEventGroup );
            }
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                                      ಧ್ರುವ ಶೂನ್ಯ * pvTxData,
                                      size_t xDataLengthBytes,
                                      TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferSend( xStreamBuffer, pvTxData, xDataLengthBytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xStreamBufferSend( xStreamBuffer, pvTxData, xDataLengthBytes, xTicksToWait );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferNextMessageLengthBytes( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xStreamBufferNextMessageLengthBytes( xStreamBuffer );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                         ಶೂನ್ಯ * pvRxData,
                                         size_t xBufferLengthBytes,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferReceive( xStreamBuffer, pvRxData, xBufferLengthBytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xStreamBufferReceive( xStreamBuffer, pvRxData, xBufferLengthBytes, xTicksToWait );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
        ಶೂನ್ಯ MPU_vStreamBufferDelete( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vStreamBufferDelete( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                vStreamBufferDelete( xStreamBuffer );
            }
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferIsFull( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xStreamBufferIsFull( xStreamBuffer );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferIsEmpty( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xStreamBufferIsEmpty( xStreamBuffer );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferReset( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferReset( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xStreamBufferReset( xStreamBuffer );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xStreamBufferSpacesAvailable( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xStreamBufferSpacesAvailable( xStreamBuffer );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferBytesAvailable( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xStreamBufferBytesAvailable( xStreamBuffer );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferSetTriggerLevel( xStreamBuffer, xTriggerLevel );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            ಅನ್ಯಥಾ
            {
                xReturn = xStreamBufferSetTriggerLevel( xStreamBuffer, xTriggerLevel );
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
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
            configASSERT( ( pxSendCompletedCallback == ರಿಕ್ತ ) &&
                          ( pxReceiveCompletedCallback == ರಿಕ್ತ ) );

            ಯದಿ( ( pxSendCompletedCallback == ರಿಕ್ತ ) &&
                ( pxReceiveCompletedCallback == ರಿಕ್ತ ) )
            {
                ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = xStreamBufferGenericCreate( xBufferSizeBytes,
                                                          xTriggerLevelBytes,
                                                          xStreamBufferType,
                                                          ರಿಕ್ತ,
                                                          ರಿಕ್ತ );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                ಅನ್ಯಥಾ
                {
                    xReturn = xStreamBufferGenericCreate( xBufferSizeBytes,
                                                          xTriggerLevelBytes,
                                                          xStreamBufferType,
                                                          ರಿಕ್ತ,
                                                          ರಿಕ್ತ );
                }
            }
            ಅನ್ಯಥಾ
            {
                traceSTREAM_BUFFER_CREATE_FAILED( xStreamBufferType );
                xReturn = ರಿಕ್ತ;
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }
    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
        StreamBufferHandle_t MPU_xStreamBufferGenericCreateStatic( size_t xBufferSizeBytes,
                                                                   size_t xTriggerLevelBytes,
                                                                   BaseType_t xStreamBufferType,
                                                                   uint8_t * ಧ್ರುವ pucStreamBufferStorageArea,
                                                                   StaticStreamBuffer_t * ಧ್ರುವ pxStaticStreamBuffer,
                                                                   StreamBufferCallbackFunction_t pxSendCompletedCallback,
                                                                   StreamBufferCallbackFunction_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            StreamBufferHandle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ರಿಕ್ತ ) &&
                          ( pxReceiveCompletedCallback == ರಿಕ್ತ ) );

            ಯದಿ( ( pxSendCompletedCallback == ರಿಕ್ತ ) &&
                ( pxReceiveCompletedCallback == ರಿಕ್ತ ) )
            {
                ಯದಿ( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = xStreamBufferGenericCreateStatic( xBufferSizeBytes,
                                                                xTriggerLevelBytes,
                                                                xStreamBufferType,
                                                                pucStreamBufferStorageArea,
                                                                pxStaticStreamBuffer,
                                                                ರಿಕ್ತ,
                                                                ರಿಕ್ತ );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                ಅನ್ಯಥಾ
                {
                    xReturn = xStreamBufferGenericCreateStatic( xBufferSizeBytes,
                                                                xTriggerLevelBytes,
                                                                xStreamBufferType,
                                                                pucStreamBufferStorageArea,
                                                                pxStaticStreamBuffer,
                                                                ರಿಕ್ತ,
                                                                ರಿಕ್ತ );
                }
            }
            ಅನ್ಯಥಾ
            {
                traceSTREAM_BUFFER_CREATE_STATIC_FAILED( xReturn, xStreamBufferType );
                xReturn = ರಿಕ್ತ;
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
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

    #ಯದಿ configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ಅನ್ತರ್ಭಾವ "application_defined_privileged_functions.h"
    #endif
/*-----------------------------------------------------------*/

#endif /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
