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
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"
#അന്തര്ഭാവ "queue.h"
#അന്തര്ഭാവ "timers.h"
#അന്തര്ഭാവ "event_groups.h"
#അന്തര്ഭാവ "stream_buffer.h"
#അന്തര്ഭാവ "mpu_prototypes.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #എങ്കിൽ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #error Access control list is not available with this MPU wrapper. Please set configENABLE_ACCESS_CONTROL_LIST to 0.
    #endif

    #എങ്കിൽ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        BaseType_t MPU_xTaskCreate( TaskFunction_t pvTaskCode,
                                    സ്ഥിരം അക്ഷരം * സ്ഥിരം pcName,
                                    സ്ഥിരം config_അട്ടി_DEPTH_TYPE ux_അട്ടി_Depth,
                                    ശൂന്യം * pvParameters,
                                    UBaseType_t uxPriority,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxPriority = uxPriority & ~( portPRIVILEGE_BIT );
                portMEMORY_BARRIER();

                xReturn = xTaskCreate( pvTaskCode, pcName, ux_അട്ടി_Depth, pvParameters, uxPriority, pxCreatedTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskCreate( pvTaskCode, pcName, ux_അട്ടി_Depth, pvParameters, uxPriority, pxCreatedTask );
            }

            തിരികെ xReturn;
        }
    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_STATIC_ALLOCATION == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                            സ്ഥിരം അക്ഷരം * സ്ഥിരം pcName,
                                            സ്ഥിരം config_അട്ടി_DEPTH_TYPE ux_അട്ടി_Depth,
                                            ശൂന്യം * സ്ഥിരം pvParameters,
                                            UBaseType_t uxPriority,
                                            അട്ടി_Type_t * സ്ഥിരം pux_അട്ടി_Buffer,
                                            StaticTask_t * സ്ഥിരം pxTaskBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxPriority = uxPriority & ~( portPRIVILEGE_BIT );
                portMEMORY_BARRIER();

                xReturn = xTaskCreateStatic( pxTaskCode, pcName, ux_അട്ടി_Depth, pvParameters, uxPriority, pux_അട്ടി_Buffer, pxTaskBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskCreateStatic( pxTaskCode, pcName, ux_അട്ടി_Depth, pvParameters, uxPriority, pux_അട്ടി_Buffer, pxTaskBuffer );
            }

            തിരികെ xReturn;
        }
    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_vTaskDelete == 1 )
        ശൂന്യം MPU_vTaskDelete( TaskHandle_t pxTaskToDelete ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskDelete( pxTaskToDelete );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTaskDelete( pxTaskToDelete );
            }
        }
    #endif /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskDelayUntil == 1 )
        BaseType_t MPU_xTaskDelayUntil( TickType_t * സ്ഥിരം pxPreviousWakeTime,
                                        TickType_t xTimeIncrement ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskAbortDelay == 1 )
        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_vTaskDelay == 1 )
        ശൂന്യം MPU_vTaskDelay( TickType_t xTicksToDelay ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskDelay( xTicksToDelay );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTaskDelay( xTicksToDelay );
            }
        }
    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_uxTaskPriorityGet == 1 )
        UBaseType_t MPU_uxTaskPriorityGet( സ്ഥിരം TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskPriorityGet( pxTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                uxReturn = uxTaskPriorityGet( pxTask );
            }

            തിരികെ uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_vTaskPrioritySet == 1 )
        ശൂന്യം MPU_vTaskPrioritySet( TaskHandle_t pxTask,
                                   UBaseType_t uxNewPriority ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskPrioritySet( pxTask, uxNewPriority );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTaskPrioritySet( pxTask, uxNewPriority );
            }
        }
    #endif /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                eReturn = eTaskGetState( pxTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                eReturn = eTaskGetState( pxTask );
            }

            തിരികെ eReturn;
        }
    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TRACE_FACILITY == 1 )
        ശൂന്യം MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t x_Get_Free_അട്ടി_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_അട്ടി_Space, eState );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_അട്ടി_Space, eState );
            }
        }
    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            തിരികെ xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_vTaskSuspend == 1 )
        ശൂന്യം MPU_vTaskSuspend( TaskHandle_t pxTaskToSuspend ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSuspend( pxTaskToSuspend );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTaskSuspend( pxTaskToSuspend );
            }
        }
    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_vTaskSuspend == 1 )
        ശൂന്യം MPU_vTaskResume( TaskHandle_t pxTaskToResume ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskResume( pxTaskToResume );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTaskResume( pxTaskToResume );
            }
        }
    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    ശൂന്യം MPU_vTaskSuspendAll( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
    {
        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vTaskSuspendAll();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskResumeAll( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskResumeAll();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            xReturn = xTaskResumeAll();
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_എണ്ണം( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = x_Task_Get_Tick_എണ്ണം();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            xReturn = x_Task_Get_Tick_എണ്ണം();
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_സംഖ്യ_Of_Tasks( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = ux_Task_Get_സംഖ്യ_Of_Tasks();
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            uxReturn = ux_Task_Get_സംഖ്യ_Of_Tasks();
        }

        തിരികെ uxReturn;
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( സ്ഥിരം അക്ഷരം * pcNameToQuery ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetHandle( pcNameToQuery );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskGetHandle( pcNameToQuery );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        ശൂന്യം MPU_vTaskListTasks( അക്ഷരം * pcWriteBuffer,
                                 size_t uxBufferLength ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskListTasks( pcWriteBuffer, uxBufferLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTaskListTasks( pcWriteBuffer, uxBufferLength );
            }
        }
    #endif /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        ശൂന്യം MPU_vTaskGetRunTimeStatistics( അക്ഷരം * pcWriteBuffer,
                                            size_t uxBufferLength ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskGetRunTimeStatistics( pcWriteBuffer, uxBufferLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTaskGetRunTimeStatistics( pcWriteBuffer, uxBufferLength );
            }
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = ulTaskGetIdleRunTimePercent();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = ulTaskGetIdleRunTimePercent();
            }

            തിരികെ xReturn;
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = ulTaskGetIdleRunTimeCounter();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = ulTaskGetIdleRunTimeCounter();
            }

            തിരികെ xReturn;
        }
    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )
        ശൂന്യം MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t px_Tag_മൂല്യം ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSetApplicationTaskTag( xTask, px_Tag_മൂല്യം );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTaskSetApplicationTaskTag( xTask, px_Tag_മൂല്യം );
            }
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )
        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetApplicationTaskTag( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskGetApplicationTaskTag( xTask );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( config_അക്കം_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        ശൂന്യം MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t xIndex,
                                                    ശൂന്യം * pv_മൂല്യം ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTaskSetThreadLocalStoragePointer( xTaskToSet, xIndex, pv_മൂല്യം );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTaskSetThreadLocalStoragePointer( xTaskToSet, xIndex, pv_മൂല്യം );
            }
        }
    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( config_അക്കം_THREAD_LOCAL_STORAGE_POINTERS != 0 )
        ശൂന്യം * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t xIndex ) /* FREERTOS_SYSTEM_CALL */
        {
            ശൂന്യം * pvReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, xIndex );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, xIndex );
            }

            തിരികെ pvReturn;
        }
    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )
        BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     ശൂന്യം * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * pxTaskStatusArray,
                                              UBaseType_t uxArraySize,
                                              configRUN_TIME_COUNTER_TYPE * pulTotalRunTime ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                uxReturn = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
            }

            തിരികെ uxReturn;
        }
    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCatchUpTicks( TickType_t xTicksToCatchUp ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskCatchUpTicks( xTicksToCatchUp );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            xReturn = xTaskCatchUpTicks( xTicksToCatchUp );
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                uxReturn = ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark( xTask );
            }

            തിരികെ uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2 == 1 )
        config_അട്ടി_DEPTH_TYPE MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_അട്ടി_DEPTH_TYPE uxReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2( xTask );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                uxReturn = ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2( xTask );
            }

            തിരികെ uxReturn;
        }
    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            തിരികെ xReturn;
        }
    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskGetSchedulerState == 1 )
        BaseType_t MPU_xTaskGetSchedulerState( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGetSchedulerState();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskGetSchedulerState();
            }

            തിരികെ xReturn;
        }
    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ശൂന്യം MPU_vTaskSetTimeOutState( TimeOut_t * സ്ഥിരം pxTimeOut ) /* FREERTOS_SYSTEM_CALL */
    {
        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vTaskSetTimeOutState( pxTimeOut );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            vTaskSetTimeOutState( pxTimeOut );
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * സ്ഥിരം pxTimeOut,
                                         TickType_t * സ്ഥിരം pxTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                                           UBaseType_t uxIndexToNotify,
                                           uint32_t ul_മൂല്യം,
                                           eNotifyAction eAction,
                                           uint32_t * pul_Previous_Notification_മൂല്യം ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotify( xTaskToNotify, uxIndexToNotify, ul_മൂല്യം, eAction, pul_Previous_Notification_മൂല്യം );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskGenericNotify( xTaskToNotify, uxIndexToNotify, ul_മൂല്യം, eAction, pul_Previous_Notification_മൂല്യം );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyWait( UBaseType_t uxIndexToWaitOn,
                                               uint32_t ulBitsToClearOnEntry,
                                               uint32_t ulBitsToClearOnExit,
                                               uint32_t * pul_Notification_മൂല്യം,
                                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyWait( uxIndexToWaitOn, ulBitsToClearOnEntry, ulBitsToClearOnExit, pul_Notification_മൂല്യം, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskGenericNotifyWait( uxIndexToWaitOn, ulBitsToClearOnEntry, ulBitsToClearOnExit, pul_Notification_മൂല്യം, xTicksToWait );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                              BaseType_t x_Clear_എണ്ണം_On_Exit,
                                              TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( uxIndexToWaitOn, x_Clear_എണ്ണം_On_Exit, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                ulReturn = ulTaskGenericNotifyTake( uxIndexToWaitOn, x_Clear_എണ്ണം_On_Exit, xTicksToWait );
            }

            തിരികെ ulReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )
        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t uxIndexToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, uxIndexToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, uxIndexToClear );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_മൂല്യം_Clear( TaskHandle_t xTask,
                                                    UBaseType_t uxIndexToClear,
                                                    uint32_t ulBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                ulReturn = ul_Task_Generic_Notify_മൂല്യം_Clear( xTask, uxIndexToClear, ulBitsToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                ulReturn = ul_Task_Generic_Notify_മൂല്യം_Clear( xTask, uxIndexToClear, ulBitsToClear );
            }

            തിരികെ ulReturn;
        }
    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t uxQueueLength,
                                               UBaseType_t uxItemSize,
                                               uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_STATIC_ALLOCATION == 1 )
        QueueHandle_t MPU_xQueueGenericCreateStatic( സ്ഥിരം UBaseType_t uxQueueLength,
                                                     സ്ഥിരം UBaseType_t uxItemSize,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     സ്ഥിരം uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGenericCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueGenericCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericReset( QueueHandle_t pxQueue,
                                       BaseType_t xNewQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      സ്ഥിരം ശൂന്യം * സ്ഥിരം pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      BaseType_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            xReturn = xQueueGenericSend( xQueue, pvItemToQueue, xTicksToWait, xCopyPosition );
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaiting( സ്ഥിരം QueueHandle_t pxQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = uxQueueMessagesWaiting( pxQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            uxReturn = uxQueueMessagesWaiting( pxQueue );
        }

        തിരികെ uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailable( സ്ഥിരം QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            uxReturn = uxQueueSpacesAvailable( xQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            uxReturn = uxQueueSpacesAvailable( xQueue );
        }

        തിരികെ uxReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceive( QueueHandle_t pxQueue,
                                  ശൂന്യം * സ്ഥിരം pvBuffer,
                                  TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueReceive( pxQueue, pvBuffer, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            xReturn = xQueueReceive( pxQueue, pvBuffer, xTicksToWait );
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               ശൂന്യം * സ്ഥിരം pvBuffer,
                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueuePeek( xQueue, pvBuffer, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            xReturn = xQueuePeek( xQueue, pvBuffer, xTicksToWait );
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
    {
        BaseType_t xReturn;

        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            xReturn = xQueueSemaphoreTake( xQueue, xTicksToWait );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            xReturn = xQueueSemaphoreTake( xQueue, xTicksToWait );
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            ശൂന്യം * xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGetMutexHolder( xSemaphore );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueGetMutexHolder( xSemaphore );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutex( സ്ഥിരം uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateMutex( ucQueueType );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueCreateMutex( ucQueueType );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutexStatic( സ്ഥിരം uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t ux_എണ്ണം_മൂല്യം,
                                                         UBaseType_t ux_Initial_എണ്ണം ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateCountingSemaphore( ux_എണ്ണം_മൂല്യം, ux_Initial_എണ്ണം );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueCreateCountingSemaphore( ux_എണ്ണം_മൂല്യം, ux_Initial_എണ്ണം );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( സ്ഥിരം UBaseType_t ux_Max_എണ്ണം,
                                                               സ്ഥിരം UBaseType_t ux_Initial_എണ്ണം,
                                                               StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateCountingSemaphoreStatic( ux_Max_എണ്ണം, ux_Initial_എണ്ണം, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueCreateCountingSemaphoreStatic( ux_Max_എണ്ണം, ux_Initial_എണ്ണം, pxStaticQueue );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xBlockTime ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueTakeMutexRecursive( xMutex, xBlockTime );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_RECURSIVE_MUTEXES == 1 )
        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueGiveMutexRecursive( xMutex );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueGiveMutexRecursive( xMutex );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSet( UBaseType_t uxEventQueueLength ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSet( uxEventQueueLength );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueCreateSet( uxEventQueueLength );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )
        QueueSetHandle_t MPU_xQueueCreateSetStatic( സ്ഥിരം UBaseType_t uxEventQueueLength,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueCreateSetStatic( uxEventQueueLength, pucQueueStorage, pxStaticQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueCreateSetStatic( uxEventQueueLength, pucQueueStorage, pxStaticQueue );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )
        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        TickType_t xBlockTimeTicks ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueSetMemberHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueSelectFromSet( xQueueSet, xBlockTimeTicks );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueSelectFromSet( xQueueSet, xBlockTimeTicks );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueAddToSet( xQueueOrSemaphore, xQueueSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueAddToSet( xQueueOrSemaphore, xQueueSet );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )
        BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                            QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xQueueRemoveFromSet( xQueueOrSemaphore, xQueueSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xQueueRemoveFromSet( xQueueOrSemaphore, xQueueSet );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ configQUEUE_REGISTRY_SIZE > 0
        ശൂന്യം MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      സ്ഥിരം അക്ഷരം * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vQueueAddToRegistry( xQueue, pcName );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vQueueAddToRegistry( xQueue, pcName );
            }
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #എങ്കിൽ configQUEUE_REGISTRY_SIZE > 0
        ശൂന്യം MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vQueueUnregisterQueue( xQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vQueueUnregisterQueue( xQueue );
            }
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #എങ്കിൽ configQUEUE_REGISTRY_SIZE > 0
        സ്ഥിരം അക്ഷരം * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            സ്ഥിരം അക്ഷരം * pcReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pcReturn = pcQueueGetName( xQueue );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                pcReturn = pcQueueGetName( xQueue );
            }

            തിരികെ pcReturn;
        }
    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    ശൂന്യം MPU_vQueueDelete( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
        {
            portRAISE_PRIVILEGE();
            portMEMORY_BARRIER();

            vQueueDelete( xQueue );
            portMEMORY_BARRIER();

            portRESET_PRIVILEGE();
            portMEMORY_BARRIER();
        }
        അല്ലെങ്കിൽ
        {
            vQueueDelete( xQueue );
        }
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )
        ശൂന്യം * MPU_pvTimerGetTimerID( സ്ഥിരം TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ശൂന്യം * pvReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            തിരികെ pvReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )
        ശൂന്യം MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   ശൂന്യം * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTimerSetTimerID( xTimer, pvNewID );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTimerSetTimerID( xTimer, pvNewID );
            }
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerIsTimerActive( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTimerIsTimerActive( xTimer );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )
        ശൂന്യം MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      സ്ഥിരം BaseType_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vTimerSetReloadMode( xTimer, xAutoReload );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vTimerSetReloadMode( xTimer, xAutoReload );
            }
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                uxReturn = uxTimerGetReloadMode( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                uxReturn = uxTimerGetReloadMode( xTimer );
            }

            തിരികെ uxReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )
        സ്ഥിരം അക്ഷരം * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            സ്ഥിരം അക്ഷരം * pcReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            തിരികെ pcReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGetExpiryTime( xTimer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTimerGetExpiryTime( xTimer );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )
        BaseType_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     സ്ഥിരം BaseType_t xCommandID,
                                                     സ്ഥിരം TickType_t x_Optional_മൂല്യം,
                                                     BaseType_t * സ്ഥിരം pxHigherPriorityTaskWoken,
                                                     സ്ഥിരം TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_മൂല്യം, pxHigherPriorityTaskWoken, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_മൂല്യം, pxHigherPriorityTaskWoken, xTicksToWait );
            }

            തിരികെ xReturn;
        }
    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreate( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupCreate();
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xEventGroupCreate();
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        EventGroupHandle_t MPU_xEventGroupCreateStatic( StaticEventGroup_t * pxEventGroupBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            EventGroupHandle_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupCreateStatic( pxEventGroupBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xEventGroupCreateStatic( pxEventGroupBuffer );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                             സ്ഥിരം EventBits_t uxBitsToWaitFor,
                                             സ്ഥിരം BaseType_t xClearOnExit,
                                             സ്ഥിരം BaseType_t xWaitForAllBits,
                                             TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupWaitBits( xEventGroup, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xEventGroupWaitBits( xEventGroup, uxBitsToWaitFor, xClearOnExit, xWaitForAllBits, xTicksToWait );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              സ്ഥിരം EventBits_t uxBitsToClear ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupClearBits( xEventGroup, uxBitsToClear );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xEventGroupClearBits( xEventGroup, uxBitsToClear );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            സ്ഥിരം EventBits_t uxBitsToSet ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupSetBits( xEventGroup, uxBitsToSet );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xEventGroupSetBits( xEventGroup, uxBitsToSet );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )
        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         സ്ഥിരം EventBits_t uxBitsToSet,
                                         സ്ഥിരം EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xEventGroupSync( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xEventGroupSync( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )
        ശൂന്യം MPU_vEventGroupDelete( EventGroupHandle_t xEventGroup ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vEventGroupDelete( xEventGroup );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vEventGroupDelete( xEventGroup );
            }
        }
    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                                      സ്ഥിരം ശൂന്യം * pvTxData,
                                      size_t xDataLengthBytes,
                                      TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferSend( xStreamBuffer, pvTxData, xDataLengthBytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xStreamBufferSend( xStreamBuffer, pvTxData, xDataLengthBytes, xTicksToWait );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferNextMessageLengthBytes( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xStreamBufferNextMessageLengthBytes( xStreamBuffer );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                         ശൂന്യം * pvRxData,
                                         size_t xBufferLengthBytes,
                                         TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferReceive( xStreamBuffer, pvRxData, xBufferLengthBytes, xTicksToWait );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xStreamBufferReceive( xStreamBuffer, pvRxData, xBufferLengthBytes, xTicksToWait );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
        ശൂന്യം MPU_vStreamBufferDelete( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                vStreamBufferDelete( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                vStreamBufferDelete( xStreamBuffer );
            }
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferIsFull( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xStreamBufferIsFull( xStreamBuffer );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferIsEmpty( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xStreamBufferIsEmpty( xStreamBuffer );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferReset( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferReset( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xStreamBufferReset( xStreamBuffer );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();
                xReturn = xStreamBufferSpacesAvailable( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xStreamBufferSpacesAvailable( xStreamBuffer );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
        size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferBytesAvailable( xStreamBuffer );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xStreamBufferBytesAvailable( xStreamBuffer );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
        BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn;

            എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
            {
                portRAISE_PRIVILEGE();
                portMEMORY_BARRIER();

                xReturn = xStreamBufferSetTriggerLevel( xStreamBuffer, xTriggerLevel );
                portMEMORY_BARRIER();

                portRESET_PRIVILEGE();
                portMEMORY_BARRIER();
            }
            അല്ലെങ്കിൽ
            {
                xReturn = xStreamBufferSetTriggerLevel( xStreamBuffer, xTriggerLevel );
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
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
            configASSERT( ( pxSendCompletedCallback == ശൂന്യ ) &&
                          ( pxReceiveCompletedCallback == ശൂന്യ ) );

            എങ്കിൽ( ( pxSendCompletedCallback == ശൂന്യ ) &&
                ( pxReceiveCompletedCallback == ശൂന്യ ) )
            {
                എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = xStreamBufferGenericCreate( xBufferSizeBytes,
                                                          xTriggerLevelBytes,
                                                          xStreamBufferType,
                                                          ശൂന്യ,
                                                          ശൂന്യ );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                അല്ലെങ്കിൽ
                {
                    xReturn = xStreamBufferGenericCreate( xBufferSizeBytes,
                                                          xTriggerLevelBytes,
                                                          xStreamBufferType,
                                                          ശൂന്യ,
                                                          ശൂന്യ );
                }
            }
            അല്ലെങ്കിൽ
            {
                traceSTREAM_BUFFER_CREATE_FAILED( xStreamBufferType );
                xReturn = ശൂന്യ;
            }

            തിരികെ xReturn;
        }
    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )
        StreamBufferHandle_t MPU_xStreamBufferGenericCreateStatic( size_t xBufferSizeBytes,
                                                                   size_t xTriggerLevelBytes,
                                                                   BaseType_t xStreamBufferType,
                                                                   uint8_t * സ്ഥിരം pucStreamBufferStorageArea,
                                                                   StaticStreamBuffer_t * സ്ഥിരം pxStaticStreamBuffer,
                                                                   StreamBufferCallbackFunction_t pxSendCompletedCallback,
                                                                   StreamBufferCallbackFunction_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            StreamBufferHandle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ശൂന്യ ) &&
                          ( pxReceiveCompletedCallback == ശൂന്യ ) );

            എങ്കിൽ( ( pxSendCompletedCallback == ശൂന്യ ) &&
                ( pxReceiveCompletedCallback == ശൂന്യ ) )
            {
                എങ്കിൽ( portIS_PRIVILEGED() == pdFALSE )
                {
                    portRAISE_PRIVILEGE();
                    portMEMORY_BARRIER();

                    xReturn = xStreamBufferGenericCreateStatic( xBufferSizeBytes,
                                                                xTriggerLevelBytes,
                                                                xStreamBufferType,
                                                                pucStreamBufferStorageArea,
                                                                pxStaticStreamBuffer,
                                                                ശൂന്യ,
                                                                ശൂന്യ );
                    portMEMORY_BARRIER();

                    portRESET_PRIVILEGE();
                    portMEMORY_BARRIER();
                }
                അല്ലെങ്കിൽ
                {
                    xReturn = xStreamBufferGenericCreateStatic( xBufferSizeBytes,
                                                                xTriggerLevelBytes,
                                                                xStreamBufferType,
                                                                pucStreamBufferStorageArea,
                                                                pxStaticStreamBuffer,
                                                                ശൂന്യ,
                                                                ശൂന്യ );
                }
            }
            അല്ലെങ്കിൽ
            {
                traceSTREAM_BUFFER_CREATE_STATIC_FAILED( xReturn, xStreamBufferType );
                xReturn = ശൂന്യ;
            }

            തിരികെ xReturn;
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

    #എങ്കിൽ configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #അന്തര്ഭാവ "application_defined_privileged_functions.h"
    #endif
/*-----------------------------------------------------------*/

#endif /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
