/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2025 Arm Limited and/or its affiliates
 * <open-source-office@arm.com>
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
#অন্তর্ভাব "mpu_syscall_numbers.h"
#অন্তর্ভাব "portmacro.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#যদি ( configENABLE_MPU == 1 )

    /*
     * Common single-SVC dispatch: wrappers do only one SVC.
     * The SVC handler decides whether to tail-call the implementation directly
     * (privileged) or set up full system-call state (unprivileged).
     */
    #define FREERTOS_MPU_SVC_DISPATCH( x_System_Call_সংখ্যা )  \
        __asm অস্থির (                                    \
            "svc %0     \n"                                 \
            :                                               \
            : "i" ( x_System_Call_সংখ্যা )                     \
            : "memory"                                      \
        );

    #যদি ( INCLUDE_xTaskDelayUntil == 1 )

        BaseType_t MPU_xTaskDelayUntil( TickType_t * ধ্রুবক pxPreviousWakeTime,
                                        ধ্রুবক TickType_t xTimeIncrement ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskDelayUntil( TickType_t * ধ্রুবক pxPreviousWakeTime,
                                        ধ্রুবক TickType_t xTimeIncrement ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskDelayUntil );
        }

    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskAbortDelay == 1 )

        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskAbortDelay );
        }

    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_vTaskDelay == 1 )

        শূন্য MPU_vTaskDelay( ধ্রুবক TickType_t xTicksToDelay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য MPU_vTaskDelay( ধ্রুবক TickType_t xTicksToDelay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskDelay );
        }

    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGet( ধ্রুবক TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskPriorityGet( ধ্রুবক TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskPriorityGet );
        }

    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_eTaskGetState );
        }

    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TRACE_FACILITY == 1 )

        শূন্য MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t x_Get_Free_স্তূপ_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t x_Get_Free_স্তূপ_Space,
                               eTaskState eState ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskGetInfo );
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( শূন্য ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( শূন্য ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetIdleTaskHandle );
        }

    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_vTaskSuspend == 1 )

        শূন্য MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSuspend );
        }

/*-----------------------------------------------------------*/

        শূন্য MPU_vTaskResume( TaskHandle_t xTaskToResume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য MPU_vTaskResume( TaskHandle_t xTaskToResume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskResume );
        }

    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_গুনতি( শূন্য ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_গুনতি( শূন্য ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Tick_গুনতি );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_সংখ্যা_Of_Tasks( শূন্য ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_সংখ্যা_Of_Tasks( শূন্য ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_সংখ্যা_Of_Tasks );
    }
/*-----------------------------------------------------------*/

    #যদি ( configGENERATE_RUN_TIME_STATS == 1 )

        config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Run_Time_গণক( ধ্রুবক TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Run_Time_গণক( ধ্রুবক TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Run_Time_গণক );
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configGENERATE_RUN_TIME_STATS == 1 )

        config_RUN_TIME_গণক_TYPE MPU_ulTaskGetRunTimePercent( ধ্রুবক TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_RUN_TIME_গণক_TYPE MPU_ulTaskGetRunTimePercent( ধ্রুবক TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGetRunTimePercent );
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_RUN_TIME_গণক_TYPE MPU_ulTaskGetIdleRunTimePercent( শূন্য ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_RUN_TIME_গণক_TYPE MPU_ulTaskGetIdleRunTimePercent( শূন্য ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGetIdleRunTimePercent );
        }

/*-----------------------------------------------------------*/

        config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Idle_Run_Time_গণক( শূন্য ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Idle_Run_Time_গণক( শূন্য ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_Run_Time_গণক );
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_APPLICATION_TASK_TAG == 1 )

        শূন্য MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSetApplicationTaskTag );
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetApplicationTaskTag );
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( config_অঙ্ক_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        শূন্য MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t x_সূচক,
                                                    শূন্য * pv_মান ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t x_সূচক,
                                                    শূন্য * pv_মান ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSetThreadLocalStoragePointer );
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #যদি ( config_অঙ্ক_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        শূন্য * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t x_সূচক ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t x_সূচক ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer );
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * ধ্রুবক pxTaskStatusArray,
                                              ধ্রুবক UBaseType_t ux_Array_আকার,
                                              config_RUN_TIME_গণক_TYPE * ধ্রুবক pul_যোগ_Run_Time ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * ধ্রুবক pxTaskStatusArray,
                                              ধ্রুবক UBaseType_t ux_Array_আকার,
                                              config_RUN_TIME_গণক_TYPE * ধ্রুবক pul_যোগ_Run_Time ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskGetSystemState );
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_ux_Task_Get_স্তূপ_উপরের_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_স্তূপ_উপরের_Water_Mark );
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_ux_Task_Get_স্তূপ_উপরের_Water_Mark2 == 1 )

        config_স্তূপ_DEPTH_TYPE MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_স্তূপ_DEPTH_TYPE MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_স্তূপ_উপরের_Water_Mark2 );
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( শূন্য ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( শূন্য ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetCurrentTaskHandle );
        }

    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskGetSchedulerState == 1 )

        BaseType_t MPU_xTaskGetSchedulerState( শূন্য ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGetSchedulerState( শূন্য ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetSchedulerState );
        }

    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    শূন্য MPU_vTaskSetTimeOutState( TimeOut_t * ধ্রুবক pxTimeOut ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    শূন্য MPU_vTaskSetTimeOutState( TimeOut_t * ধ্রুবক pxTimeOut ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSetTimeOutState );
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * ধ্রুবক pxTimeOut,
                                         TickType_t * ধ্রুবক pxTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * ধ্রুবক pxTimeOut,
                                         TickType_t * ধ্রুবক pxTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskCheckForTimeOut );
    }
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyEntry( ধ্রুবক xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGenericNotifyEntry( ধ্রুবক xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotify );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyWaitEntry( ধ্রুবক xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGenericNotifyWaitEntry( ধ্রুবক xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyWait );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_সূচক_To_Wait_On,
                                              BaseType_t x_Clear_গুনতি_On_Exit,
                                              TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_সূচক_To_Wait_On,
                                              BaseType_t x_Clear_গুনতি_On_Exit,
                                              TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGenericNotifyTake );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_সূচক_To_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_সূচক_To_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyStateClear );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_মান_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_সূচক_To_Clear,
                                                    uint32_t ulBitsToClear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_মান_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_সূচক_To_Clear,
                                                    uint32_t ulBitsToClear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Generic_Notify_মান_Clear );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      ধ্রুবক শূন্য * ধ্রুবক pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      ধ্রুবক BaseType_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      ধ্রুবক শূন্য * ধ্রুবক pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      ধ্রুবক BaseType_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGenericSend );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaiting( ধ্রুবক QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_uxQueueMessagesWaiting( ধ্রুবক QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxQueueMessagesWaiting );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailable( ধ্রুবক QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_uxQueueSpacesAvailable( ধ্রুবক QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxQueueSpacesAvailable );
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                  শূন্য * ধ্রুবক pv_বাফার,
                                  TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                  শূন্য * ধ্রুবক pv_বাফার,
                                  TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueReceive );
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               শূন্য * ধ্রুবক pv_বাফার,
                               TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               শূন্য * ধ্রুবক pv_বাফার,
                               TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueuePeek );
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueSemaphoreTake );
    }
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGetMutexHolder );
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueTakeMutexRecursive );
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGiveMutexRecursive );
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        ধ্রুবক TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        ধ্রুবক TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueSelectFromSet );
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueAddToSet );
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( config_QUEUE_REGISTRY_আকার > 0 )

        শূন্য MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      ধ্রুবক অক্ষর * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      ধ্রুবক অক্ষর * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vQueueAddToRegistry );
        }

    #endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #যদি ( config_QUEUE_REGISTRY_আকার > 0 )

        শূন্য MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vQueueUnregisterQueue );
        }

    #endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #যদি ( config_QUEUE_REGISTRY_আকার > 0 )

        ধ্রুবক অক্ষর * MPU_pcQueueGetName( QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ধ্রুবক অক্ষর * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcQueueGetName );
        }

    #endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        শূন্য * MPU_pvTimerGetTimerID( ধ্রুবক TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য * MPU_pvTimerGetTimerID( ধ্রুবক TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTimerGetTimerID );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        শূন্য MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   শূন্য * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   শূন্য * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTimerSetTimerID );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerIsTimerActive );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( শূন্য ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( শূন্য ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromTaskEntry( ধ্রুবক xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTimerGenericCommandFromTaskEntry( ধ্রুবক xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGenericCommandFromTask );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        ধ্রুবক অক্ষর * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ধ্রুবক অক্ষর * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcTimerGetName );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        শূন্য MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      ধ্রুবক BaseType_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      ধ্রুবক BaseType_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTimerSetReloadMode );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetReloadMode );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTimerGetReloadMode );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetPeriod );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetExpiryTime );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupWaitBitsEntry( ধ্রুবক xEventGroupWaitBitsParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupWaitBitsEntry( ধ্রুবক xEventGroupWaitBitsParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupWaitBits );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              ধ্রুবক EventBits_t uxBitsToClear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              ধ্রুবক EventBits_t uxBitsToClear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupClearBits );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            ধ্রুবক EventBits_t uxBitsToSet ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            ধ্রুবক EventBits_t uxBitsToSet ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupSetBits );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         ধ্রুবক EventBits_t uxBitsToSet,
                                         ধ্রুবক EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         ধ্রুবক EventBits_t uxBitsToSet,
                                         ধ্রুবক EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupSync );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_Group_Get_সংখ্যা( শূন্য * xEventGroup ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_Group_Get_সংখ্যা( শূন্য * xEventGroup ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Event_Group_Get_সংখ্যা );
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        শূন্য MPU_v_Event_Group_Set_সংখ্যা( শূন্য * xEventGroup,
                                       UBaseType_t ux_Event_Group_সংখ্যা ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        শূন্য MPU_v_Event_Group_Set_সংখ্যা( শূন্য * xEventGroup,
                                       UBaseType_t ux_Event_Group_সংখ্যা ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Event_Group_Set_সংখ্যা );
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_x_Stream_বাফার_Send( Stream_বাফার_Handle_t x_Stream_বাফার,
                                      ধ্রুবক শূন্য * pv_Tx_তথ্য,
                                      size_t x_তথ্য_দৈর্ঘ্য_Bytes,
                                      TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_Stream_বাফার_Send( Stream_বাফার_Handle_t x_Stream_বাফার,
                                      ধ্রুবক শূন্য * pv_Tx_তথ্য,
                                      size_t x_তথ্য_দৈর্ঘ্য_Bytes,
                                      TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Stream_বাফার_Send );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_x_Stream_বাফার_Receive( Stream_বাফার_Handle_t x_Stream_বাফার,
                                         শূন্য * pv_Rx_তথ্য,
                                         size_t x_বাফার_দৈর্ঘ্য_Bytes,
                                         TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_Stream_বাফার_Receive( Stream_বাফার_Handle_t x_Stream_বাফার,
                                         শূন্য * pv_Rx_তথ্য,
                                         size_t x_বাফার_দৈর্ঘ্য_Bytes,
                                         TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Stream_বাফার_Receive );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_বাফার_Is_Full( Stream_বাফার_Handle_t x_Stream_বাফার ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_x_Stream_বাফার_Is_Full( Stream_বাফার_Handle_t x_Stream_বাফার ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Stream_বাফার_Is_Full );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_বাফার_Is_Empty( Stream_বাফার_Handle_t x_Stream_বাফার ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_x_Stream_বাফার_Is_Empty( Stream_বাফার_Handle_t x_Stream_বাফার ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Stream_বাফার_Is_Empty );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_x_Stream_বাফার_Spaces_Available( Stream_বাফার_Handle_t x_Stream_বাফার ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_Stream_বাফার_Spaces_Available( Stream_বাফার_Handle_t x_Stream_বাফার ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Stream_বাফার_Spaces_Available );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_x_Stream_বাফার_Bytes_Available( Stream_বাফার_Handle_t x_Stream_বাফার ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_Stream_বাফার_Bytes_Available( Stream_বাফার_Handle_t x_Stream_বাফার ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Stream_বাফার_Bytes_Available );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_বাফার_Set_Trigger_Level( Stream_বাফার_Handle_t x_Stream_বাফার,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_x_Stream_বাফার_Set_Trigger_Level( Stream_বাফার_Handle_t x_Stream_বাফার,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Stream_বাফার_Set_Trigger_Level );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes( Stream_বাফার_Handle_t x_Stream_বাফার ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes( Stream_বাফার_Handle_t x_Stream_বাফার ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#endif /* ( configENABLE_MPU == 1 ) */
