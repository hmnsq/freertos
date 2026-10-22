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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"
#include "stream_buffer.h"
#include "mpu_prototypes.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#nếu ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #nếu ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #error Access control list is not available with this MPU wrapper. Please set configENABLE_ACCESS_CONTROL_LIST to 0.
    #endif

    #nếu ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        BaseType_t MPU_xTaskCreate( TaskFunction_t pvTaskCode,
                                    const char * const pcName,
                                    const configSTACK_DEPTH_TYPE uxStackDepth,
                                    void * pvParameters,
                                    UBaseType_t uxPriority,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxPriority = uxPriority & ~( portPRIVILEGE_BIT );
                portMEMORY_BARRIER();

                xReturn = xTaskCreate( pvTaskCode, pcName, uxStackDepth, pvParameters, uxPriority, pxCreatedTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskCreate( pvTaskCode, pcName, uxStackDepth, pvParameters, uxPriority, pxCreatedTask );
            }

            trả_về xReturn;
        }
    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #nếu ( configSUPPORT_STATIC_ALLOCATION == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                            const char * const pcName,
                                            const configSTACK_DEPTH_TYPE uxStackDepth,
                                            void * const pvParameters,
                                            UBaseType_t uxPriority,
                                            StackType_t * const puxStackBuffer,
                                            StaticTask_t * const pxTaskBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxPriority = uxPriority & ~( portPRIVILEGE_BIT );
                portMEMORY_BARRIER();

                xReturn = xTaskCreateStatic( pxTaskCode, pcName, uxStackDepth, pvParameters, uxPriority, puxStackBuffer, pxTaskBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskCreateStatic( pxTaskCode, pcName, uxStackDepth, pvParameters, uxPriority, puxStackBuffer, pxTaskBuffer );
            }

            trả_về xReturn;
        }
    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_vTaskDelete == 1 )
        void MPU_vTaskDelete( TaskHandle_t pxTaskToDelete ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskDelete( pxTaskToDelete );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTaskDelete( pxTaskToDelete );
            }
        }
    #endif /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_xTaskDelayUntil == 1 )
        BaseType_t MPU_xTaskDelayUntil( TickType_t * const pxPreviousWakeTime,
                                        TickType_t xTimeIncrement ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
            }

            trả_về xReturn;
        }
    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_xTaskAbortDelay == 1 )
        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            trả_về xReturn;
        }
    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_vTaskDelay == 1 )
        void MPU_vTaskDelay( TickType_t xTicksToDelay ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskDelay( xTicksToDelay );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTaskDelay( xTicksToDelay );
            }
        }
    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_uxTaskPriorityGet == 1 )
        UBaseType_t MPU_uxTaskPriorityGet( const TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskPriorityGet( pxTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                uxReturn = uxTaskPriorityGet( pxTask );
            }

            trả_về uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_vTaskPrioritySet == 1 )
        void MPU_vTaskPrioritySet( TaskHandle_t pxTask,
                                   UBaseType_t uxNewPriority ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskPrioritySet( pxTask, uxNewPriority );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTaskPrioritySet( pxTask, uxNewPriority );
            }
        }
    #endif /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                eReturn = eTaskGetState( pxTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                eReturn = eTaskGetState( pxTask );
            }

            trả_về eReturn;
        }
    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TRACE_FACILITY == 1 )
        void MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t xGetFreeStackSpace,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskGetInfo( xTask, pxTaskStatus, xGetFreeStackSpace, eState );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTaskGetInfo( xTask, pxTaskStatus, xGetFreeStackSpace, eState );
            }
        }
    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( void ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            trả_về xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_vTaskSuspend == 1 )
        void MPU_vTaskSuspend( TaskHandle_t pxTaskToSuspend ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSuspend( pxTaskToSuspend );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTaskSuspend( pxTaskToSuspend );
            }
        }
    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_vTaskSuspend == 1 )
        void MPU_vTaskResume( TaskHandle_t pxTaskToResume ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskResume( pxTaskToResume );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTaskResume( pxTaskToResume );
            }
        }
    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    void MPU_vTaskSuspendAll( void ) /* FREERTOS_SYSTEM_CALL */
    {
        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vTaskSuspendAll();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskResumeAll( void ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskResumeAll();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            xReturn = xTaskResumeAll();
        }

        trả_về xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_xTaskGetTickCount( void ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskGetTickCount();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            xReturn = xTaskGetTickCount();
        }

        trả_về xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxTaskGetNumberOfTasks( void ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = uxTaskGetNumberOfTasks();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            uxReturn = uxTaskGetNumberOfTasks();
        }

        trả_về uxReturn;
    }
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( const char * pcNameToQuery ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetHandle( pcNameToQuery );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskGetHandle( pcNameToQuery );
            }

            trả_về xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        void MPU_vTaskListTasks( char * pcWriteBuffer,
                                 size_t uxBufferLength ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskListTasks( pcWriteBuffer, uxBufferLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTaskListTasks( pcWriteBuffer, uxBufferLength );
            }
        }
    #endif /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        void MPU_vTaskGetRunTimeStatistics( char * pcWriteBuffer,
                                            size_t uxBufferLength ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskGetRunTimeStatistics( pcWriteBuffer, uxBufferLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTaskGetRunTimeStatistics( pcWriteBuffer, uxBufferLength );
            }
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( void ) /* FREERTOS_SYSTEM_CALL */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = ulTaskGetIdleRunTimePercent();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = ulTaskGetIdleRunTimePercent();
            }

            trả_về xReturn;
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( void ) /* FREERTOS_SYSTEM_CALL */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = ulTaskGetIdleRunTimeCounter();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = ulTaskGetIdleRunTimeCounter();
            }

            trả_về xReturn;
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_APPLICATION_TASK_TAG == 1 )
        void MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t pxTagValue ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSetApplicationTaskTag( xTask, pxTagValue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTaskSetApplicationTaskTag( xTask, pxTagValue );
            }
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_APPLICATION_TASK_TAG == 1 )
        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetApplicationTaskTag( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskGetApplicationTaskTag( xTask );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        void MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t xIndex,
                                                    void * pvValue ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSetThreadLocalStoragePointer( xTaskToSet, xIndex, pvValue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTaskSetThreadLocalStoragePointer( xTaskToSet, xIndex, pvValue );
            }
        }
    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #nếu ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        void * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t xIndex ) /* FREERTOS_SYSTEM_CALL */
        {
            void * pvReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, xIndex );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, xIndex );
            }

            trả_về pvReturn;
        }
    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_APPLICATION_TASK_TAG == 1 )
        BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     void * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * pxTaskStatusArray,
                                              UBaseType_t uxArraySize,
                                              configRUN_TIME_COUNTER_TYPE * pulTotalRunTime ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
            }

            trả_về uxReturn;
        }
    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCatchUpTicks( TickType_t xTicksToCatchUp ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskCatchUpTicks( xTicksToCatchUp );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            xReturn = xTaskCatchUpTicks( xTicksToCatchUp );
        }

        trả_về xReturn;
    }
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_uxTaskGetStackHighWaterMark == 1 )
        UBaseType_t MPU_uxTaskGetStackHighWaterMark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskGetStackHighWaterMark( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                uxReturn = uxTaskGetStackHighWaterMark( xTask );
            }

            trả_về uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 )
        configSTACK_DEPTH_TYPE MPU_uxTaskGetStackHighWaterMark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            configSTACK_DEPTH_TYPE uxReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskGetStackHighWaterMark2( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                uxReturn = uxTaskGetStackHighWaterMark2( xTask );
            }

            trả_về uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( void ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            trả_về xReturn;
        }
    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( INCLUDE_xTaskGetSchedulerState == 1 )
        BaseType_t MPU_xTaskGetSchedulerState( void ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetSchedulerState();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskGetSchedulerState();
            }

            trả_về xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    void MPU_vTaskSetTimeOutState( TimeOut_t * const pxTimeOut ) /* FREERTOS_SYSTEM_CALL */
    {
        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vTaskSetTimeOutState( pxTimeOut );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            vTaskSetTimeOutState( pxTimeOut );
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * const pxTimeOut,
                                         TickType_t * const pxTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
        }

        trả_về xReturn;
    }
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                                           UBaseType_t uxIndexToNotify,
                                           uint32_t ulValue,
                                           eNotifyAction eAction,
                                           uint32_t * pulPreviousNotificationValue ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotify( xTaskToNotify, uxIndexToNotify, ulValue, eAction, pulPreviousNotificationValue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskGenericNotify( xTaskToNotify, uxIndexToNotify, ulValue, eAction, pulPreviousNotificationValue );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyWait( UBaseType_t uxIndexToWaitOn,
                                               uint32_t ulBitsToClearOnEntry,
                                               uint32_t ulBitsToClearOnExit,
                                               uint32_t * pulNotificationValue,
                                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyWait( uxIndexToWaitOn, ulBitsToClearOnEntry, ulBitsToClearOnExit, pulNotificationValue, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskGenericNotifyWait( uxIndexToWaitOn, ulBitsToClearOnEntry, ulBitsToClearOnExit, pulNotificationValue, xTicksToWait );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                              BaseType_t xClearCountOnExit,
                                              TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( uxIndexToWaitOn, xClearCountOnExit, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                ulReturn = ulTaskGenericNotifyTake( uxIndexToWaitOn, xClearCountOnExit, xTicksToWait );
            }

            trả_về ulReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t uxIndexToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, uxIndexToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, uxIndexToClear );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyValueClear( TaskHandle_t xTask,
                                                    UBaseType_t uxIndexToClear,
                                                    uint32_t ulBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ulTaskGenericNotifyValueClear( xTask, uxIndexToClear, ulBitsToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                ulReturn = ulTaskGenericNotifyValueClear( xTask, uxIndexToClear, ulBitsToClear );
            }

            trả_về ulReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t uxQueueLength,
                                               UBaseType_t uxItemSize,
                                               uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );
            }

            trả_về xReturn;
        }
    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configSUPPORT_STATIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreateStatic( const UBaseType_t uxQueueLength,
                                                     const UBaseType_t uxItemSize,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     const uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueGenericCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType );
            }

            trả_về xReturn;
        }
    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericReset( QueueHandle_t pxQueue,
                                       BaseType_t xNewQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
        }

        trả_về xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      const void * const pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      BaseType_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
        }

        trả_về xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaiting( const QueueHandle_t pxQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = uxQueueMessagesWaiting( pxQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            uxReturn = uxQueueMessagesWaiting( pxQueue );
        }

        trả_về uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailable( const QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = uxQueueSpacesAvailable( xQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            uxReturn = uxQueueSpacesAvailable( xQueue );
        }

        trả_về uxReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceive( QueueHandle_t pxQueue,
                                  void * const pvBuffer,
                                  TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueReceive( pxQueue, pvBuffer, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            xReturn = xQueueReceive( pxQueue, pvBuffer, xTicksToWait );
        }

        trả_về xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               void * const pvBuffer,
                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueuePeek( xQueue, pvBuffer, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            xReturn = xQueuePeek( xQueue, pvBuffer, xTicksToWait );
        }

        trả_về xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueSemaphoreTake( xQueue, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            xReturn = xQueueSemaphoreTake( xQueue, xTicksToWait );
        }

        trả_về xReturn;
    }
/*-----------------------------------------------------------*/

    #nếu ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            void * xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGetMutexHolder( xSemaphore );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueGetMutexHolder( xSemaphore );
            }

            trả_về xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutex( const uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateMutex( ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueCreateMutex( ucQueueType );
            }

            trả_về xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutexStatic( const uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
            }

            trả_về xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t uxCountValue,
                                                         UBaseType_t uxInitialCount ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateCountingSemaphore( uxCountValue, uxInitialCount );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueCreateCountingSemaphore( uxCountValue, uxInitialCount );
            }

            trả_về xReturn;
        }
    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( const UBaseType_t uxMaxCount,
                                                               const UBaseType_t uxInitialCount,
                                                               StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateCountingSemaphoreStatic( uxMaxCount, uxInitialCount, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueCreateCountingSemaphoreStatic( uxMaxCount, uxInitialCount, pxStaticQueue );
            }

            trả_về xReturn;
        }
    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xBlockTime ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGiveMutexRecursive( xMutex );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueGiveMutexRecursive( xMutex );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSet( UBaseType_t uxEventQueueLength ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSet( uxEventQueueLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueCreateSet( uxEventQueueLength );
            }

            trả_về xReturn;
        }
    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSetStatic( const UBaseType_t uxEventQueueLength,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSetStatic( uxEventQueueLength, pucQueueStorage, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueCreateSetStatic( uxEventQueueLength, pucQueueStorage, pxStaticQueue );
            }

            trả_về xReturn;
        }
    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_QUEUE_SETS == 1 )
        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        TickType_t xBlockTimeTicks ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetMemberHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueSelectFromSet( xQueueSet, xBlockTimeTicks );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueSelectFromSet( xQueueSet, xBlockTimeTicks );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueAddToSet( xQueueOrSemaphore, xQueueSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueAddToSet( xQueueOrSemaphore, xQueueSet );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                            QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueRemoveFromSet( xQueueOrSemaphore, xQueueSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xQueueRemoveFromSet( xQueueOrSemaphore, xQueueSet );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu configQUEUE_REGISTRY_SIZE > 0
        void MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      const char * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vQueueAddToRegistry( xQueue, pcName );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vQueueAddToRegistry( xQueue, pcName );
            }
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #nếu configQUEUE_REGISTRY_SIZE > 0
        void MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vQueueUnregisterQueue( xQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vQueueUnregisterQueue( xQueue );
            }
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #nếu configQUEUE_REGISTRY_SIZE > 0
        const char * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            const char * pcReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pcReturn = pcQueueGetName( xQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                pcReturn = pcQueueGetName( xQueue );
            }

            trả_về pcReturn;
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    void MPU_vQueueDelete( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        nếu( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vQueueDelete( xQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        không_thì
        {
            vQueueDelete( xQueue );
        }
    }
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TIMERS == 1 )
        void * MPU_pvTimerGetTimerID( const TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            void * pvReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            trả_về pvReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TIMERS == 1 )
        void MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   void * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTimerSetTimerID( xTimer, pvNewID );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTimerSetTimerID( xTimer, pvNewID );
            }
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerIsTimerActive( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTimerIsTimerActive( xTimer );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( void ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TIMERS == 1 )
        void MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      const BaseType_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTimerSetReloadMode( xTimer, xAutoReload );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vTimerSetReloadMode( xTimer, xAutoReload );
            }
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTimerGetReloadMode( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                uxReturn = uxTimerGetReloadMode( xTimer );
            }

            trả_về uxReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TIMERS == 1 )
        const char * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            const char * pcReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            trả_về pcReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetExpiryTime( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTimerGetExpiryTime( xTimer );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     const BaseType_t xCommandID,
                                                     const TickType_t xOptionalValue,
                                                     BaseType_t * const pxHigherPriorityTaskWoken,
                                                     const TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, xOptionalValue, pxHigherPriorityTaskWoken, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, xOptionalValue, pxHigherPriorityTaskWoken, xTicksToWait );
            }

            trả_về xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreate( void ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupCreate();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xEventGroupCreate();
            }

            trả_về xReturn;
        }
    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreateStatic( StaticEventGroup_t * pxEventGroupBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupCreateStatic( pxEventGroupBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xEventGroupCreateStatic( pxEventGroupBuffer );
            }

            trả_về xReturn;
        }
    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                             const EventBits_t uxBitsToWaitFor,
                                             const BaseType_t xClearOnExit,
                                             const BaseType_t xWaitForAllBits,
                                             TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupWaitBits( xEventGroup, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xEventGroupWaitBits( xEventGroup, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              const EventBits_t uxBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupClearBits( xEventGroup, uxBitsToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xEventGroupClearBits( xEventGroup, uxBitsToClear );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            const EventBits_t uxBitsToSet ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupSetBits( xEventGroup, uxBitsToSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xEventGroupSetBits( xEventGroup, uxBitsToSet );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         const EventBits_t uxBitsToSet,
                                         const EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupSync( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xEventGroupSync( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_EVENT_GROUPS == 1 )
        void MPU_vEventGroupDelete( EventGroupHandle_t xEventGroup ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vEventGroupDelete( xEventGroup );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vEventGroupDelete( xEventGroup );
            }
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                                      const void * pvTxData,
                                      size_t xDataLengthBytes,
                                      TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferSend( xStreamBuffer, pvTxData, xDataLengthBytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xStreamBufferSend( xStreamBuffer, pvTxData, xDataLengthBytes, xTicksToWait );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferNextMessageLengthBytes( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xStreamBufferNextMessageLengthBytes( xStreamBuffer );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                         void * pvRxData,
                                         size_t xBufferLengthBytes,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferReceive( xStreamBuffer, pvRxData, xBufferLengthBytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xStreamBufferReceive( xStreamBuffer, pvRxData, xBufferLengthBytes, xTicksToWait );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_STREAM_BUFFERS == 1 )
        void MPU_vStreamBufferDelete( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vStreamBufferDelete( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                vStreamBufferDelete( xStreamBuffer );
            }
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferIsFull( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xStreamBufferIsFull( xStreamBuffer );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferIsEmpty( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xStreamBufferIsEmpty( xStreamBuffer );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferReset( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferReset( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xStreamBufferReset( xStreamBuffer );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xStreamBufferSpacesAvailable( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xStreamBufferSpacesAvailable( xStreamBuffer );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferBytesAvailable( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xStreamBufferBytesAvailable( xStreamBuffer );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            nếu( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferSetTriggerLevel( xStreamBuffer, xTriggerLevel );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            không_thì
            {
                xReturn = xStreamBufferSetTriggerLevel( xStreamBuffer, xTriggerLevel );
            }

            trả_về xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
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
            configASSERT( ( pxSendCompletedCallback == NULL ) &&
                          ( pxReceiveCompletedCallback == NULL ) );

            nếu( ( pxSendCompletedCallback == NULL ) &&
                ( pxReceiveCompletedCallback == NULL ) )
            {
                nếu( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = xStreamBufferGenericCreate( xBufferSizeBytes,
                                                          xTriggerLevelBytes,
                                                          xStreamBufferType,
                                                          NULL,
                                                          NULL );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                không_thì
                {
                    xReturn = xStreamBufferGenericCreate( xBufferSizeBytes,
                                                          xTriggerLevelBytes,
                                                          xStreamBufferType,
                                                          NULL,
                                                          NULL );
                }
            }
            không_thì
            {
                traceSTREAM_BUFFER_CREATE_FAILED( xStreamBufferType );
                xReturn = NULL;
            }

            trả_về xReturn;
        }
    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #nếu ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
        StreamBufferHandle_t MPU_xStreamBufferGenericCreateStatic( size_t xBufferSizeBytes,
                                                                   size_t xTriggerLevelBytes,
                                                                   BaseType_t xStreamBufferType,
                                                                   uint8_t * const pucStreamBufferStorageArea,
                                                                   StaticStreamBuffer_t * const pxStaticStreamBuffer,
                                                                   StreamBufferCallbackFunction_t pxSendCompletedCallback,
                                                                   StreamBufferCallbackFunction_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            StreamBufferHandle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == NULL ) &&
                          ( pxReceiveCompletedCallback == NULL ) );

            nếu( ( pxSendCompletedCallback == NULL ) &&
                ( pxReceiveCompletedCallback == NULL ) )
            {
                nếu( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = xStreamBufferGenericCreateStatic( xBufferSizeBytes,
                                                                xTriggerLevelBytes,
                                                                xStreamBufferType,
                                                                pucStreamBufferStorageArea,
                                                                pxStaticStreamBuffer,
                                                                NULL,
                                                                NULL );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                không_thì
                {
                    xReturn = xStreamBufferGenericCreateStatic( xBufferSizeBytes,
                                                                xTriggerLevelBytes,
                                                                xStreamBufferType,
                                                                pucStreamBufferStorageArea,
                                                                pxStaticStreamBuffer,
                                                                NULL,
                                                                NULL );
                }
            }
            không_thì
            {
                traceSTREAM_BUFFER_CREATE_STATIC_FAILED( xReturn, xStreamBufferType );
                xReturn = NULL;
            }

            trả_về xReturn;
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

    #nếu configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #include "application_defined_privileged_functions.h"
    #endif
/*-----------------------------------------------------------*/

#endif /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
