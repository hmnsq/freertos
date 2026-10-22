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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "queue.h"
#ಅನ್ತರ್ಭಾವ "timers.h"
#ಅನ್ತರ್ಭಾವ "event_groups.h"
#ಅನ್ತರ್ಭಾವ "stream_buffer.h"
#ಅನ್ತರ್ಭಾವ "mpu_prototypes.h"
#ಅನ್ತರ್ಭಾವ "mpu_syscall_numbers.h"
#ಅನ್ತರ್ಭಾವ "portmacro.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ಯದಿ ( configENABLE_MPU == 1 )

    /*
     * Common single-SVC dispatch: wrappers do only one SVC.
     * The SVC handler decides whether to tail-call the implementation directly
     * (privileged) or set up full system-call state (unprivileged).
     */
    #define FREERTOS_MPU_SVC_DISPATCH( x_System_Call_ಸಂಖ್ಯೆ )  \
        __asm ಚಞ್ಚಲ (                                    \
            "svc %0     \n"                                 \
            :                                               \
            : "i" ( x_System_Call_ಸಂಖ್ಯೆ )                     \
            : "memory"                                      \
        );

    #ಯದಿ ( INCLUDE_xTaskDelayUntil == 1 )

        BaseType_t MPU_xTaskDelayUntil( TickType_t * ಧ್ರುವ pxPreviousWakeTime,
                                        ಧ್ರುವ TickType_t xTimeIncrement ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskDelayUntil( TickType_t * ಧ್ರುವ pxPreviousWakeTime,
                                        ಧ್ರುವ TickType_t xTimeIncrement ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskDelayUntil );
        }

    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskAbortDelay == 1 )

        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskAbortDelay );
        }

    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_vTaskDelay == 1 )

        ಶೂನ್ಯ MPU_vTaskDelay( ಧ್ರುವ TickType_t xTicksToDelay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTaskDelay( ಧ್ರುವ TickType_t xTicksToDelay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskDelay );
        }

    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGet( ಧ್ರುವ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskPriorityGet( ಧ್ರುವ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskPriorityGet );
        }

    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_eTaskGetState );
        }

    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TRACE_FACILITY == 1 )

        ಶೂನ್ಯ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t x_Get_Free_ರಾಶಿ_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t x_Get_Free_ರಾಶಿ_Space,
                               eTaskState eState ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskGetInfo );
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetIdleTaskHandle );
        }

    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_vTaskSuspend == 1 )

        ಶೂನ್ಯ MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSuspend );
        }

/*-----------------------------------------------------------*/

        ಶೂನ್ಯ MPU_vTaskResume( TaskHandle_t xTaskToResume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTaskResume( TaskHandle_t xTaskToResume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskResume );
        }

    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Tick_ಎಣಿಕೆ );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_Of_Tasks( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_Of_Tasks( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ಸಂಖ್ಯೆ_Of_Tasks );
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( configGENERATE_RUN_TIME_STATS == 1 )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounter( ಧ್ರುವ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounter( ಧ್ರುವ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGetRunTimeCounter );
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configGENERATE_RUN_TIME_STATS == 1 )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercent( ಧ್ರುವ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercent( ಧ್ರುವ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGetRunTimePercent );
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGetIdleRunTimePercent );
        }

/*-----------------------------------------------------------*/

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGetIdleRunTimeCounter );
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_APPLICATION_TASK_TAG == 1 )

        ಶೂನ್ಯ MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSetApplicationTaskTag );
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetApplicationTaskTag );
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        ಶೂನ್ಯ MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t xIndex,
                                                    ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t xIndex,
                                                    ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSetThreadLocalStoragePointer );
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        ಶೂನ್ಯ * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t xIndex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t xIndex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer );
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * ಧ್ರುವ pxTaskStatusArray,
                                              ಧ್ರುವ UBaseType_t uxArraySize,
                                              configRUN_TIME_COUNTER_TYPE * ಧ್ರುವ pulTotalRunTime ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * ಧ್ರುವ pxTaskStatusArray,
                                              ಧ್ರುವ UBaseType_t uxArraySize,
                                              configRUN_TIME_COUNTER_TYPE * ಧ್ರುವ pulTotalRunTime ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskGetSystemState );
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark );
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2 == 1 )

        config_ರಾಶಿ_DEPTH_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ರಾಶಿ_DEPTH_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2 );
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetCurrentTaskHandle );
        }

    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskGetSchedulerState == 1 )

        BaseType_t MPU_xTaskGetSchedulerState( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGetSchedulerState( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetSchedulerState );
        }

    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_vTaskSetTimeOutState( TimeOut_t * ಧ್ರುವ pxTimeOut ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ಶೂನ್ಯ MPU_vTaskSetTimeOutState( TimeOut_t * ಧ್ರುವ pxTimeOut ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSetTimeOutState );
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * ಧ್ರುವ pxTimeOut,
                                         TickType_t * ಧ್ರುವ pxTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * ಧ್ರುವ pxTimeOut,
                                         TickType_t * ಧ್ರುವ pxTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskCheckForTimeOut );
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyEntry( ಧ್ರುವ xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGenericNotifyEntry( ಧ್ರುವ xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotify );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyWaitEntry( ಧ್ರುವ xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGenericNotifyWaitEntry( ಧ್ರುವ xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyWait );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                              BaseType_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                              TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                              BaseType_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                              TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGenericNotifyTake );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t uxIndexToClear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t uxIndexToClear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyStateClear );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t uxIndexToClear,
                                                    uint32_t ulBitsToClear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t uxIndexToClear,
                                                    uint32_t ulBitsToClear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      ಧ್ರುವ ಶೂನ್ಯ * ಧ್ರುವ pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      ಧ್ರುವ BaseType_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      ಧ್ರುವ ಶೂನ್ಯ * ಧ್ರುವ pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      ಧ್ರುವ BaseType_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGenericSend );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaiting( ಧ್ರುವ QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_uxQueueMessagesWaiting( ಧ್ರುವ QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxQueueMessagesWaiting );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailable( ಧ್ರುವ QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_uxQueueSpacesAvailable( ಧ್ರುವ QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxQueueSpacesAvailable );
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                  ಶೂನ್ಯ * ಧ್ರುವ pvBuffer,
                                  TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                  ಶೂನ್ಯ * ಧ್ರುವ pvBuffer,
                                  TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueReceive );
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               ಶೂನ್ಯ * ಧ್ರುವ pvBuffer,
                               TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               ಶೂನ್ಯ * ಧ್ರುವ pvBuffer,
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

    #ಯದಿ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGetMutexHolder );
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueTakeMutexRecursive );
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGiveMutexRecursive );
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        ಧ್ರುವ TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        ಧ್ರುವ TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueSelectFromSet );
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueAddToSet );
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configQUEUE_REGISTRY_SIZE > 0 )

        ಶೂನ್ಯ MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      ಧ್ರುವ ವರ್ಣ * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      ಧ್ರುವ ವರ್ಣ * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vQueueAddToRegistry );
        }

    #endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configQUEUE_REGISTRY_SIZE > 0 )

        ಶೂನ್ಯ MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vQueueUnregisterQueue );
        }

    #endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configQUEUE_REGISTRY_SIZE > 0 )

        ಧ್ರುವ ವರ್ಣ * MPU_pcQueueGetName( QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಧ್ರುವ ವರ್ಣ * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcQueueGetName );
        }

    #endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ * MPU_pvTimerGetTimerID( ಧ್ರುವ TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ * MPU_pvTimerGetTimerID( ಧ್ರುವ TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTimerGetTimerID );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   ಶೂನ್ಯ * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   ಶೂನ್ಯ * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTimerSetTimerID );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerIsTimerActive );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromTaskEntry( ಧ್ರುವ xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTimerGenericCommandFromTaskEntry( ಧ್ರುವ xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGenericCommandFromTask );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        ಧ್ರುವ ವರ್ಣ * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಧ್ರುವ ವರ್ಣ * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcTimerGetName );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      ಧ್ರುವ BaseType_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      ಧ್ರುವ BaseType_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTimerSetReloadMode );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetReloadMode );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTimerGetReloadMode );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetPeriod );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetExpiryTime );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupWaitBitsEntry( ಧ್ರುವ xEventGroupWaitBitsParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupWaitBitsEntry( ಧ್ರುವ xEventGroupWaitBitsParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupWaitBits );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              ಧ್ರುವ EventBits_t uxBitsToClear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              ಧ್ರುವ EventBits_t uxBitsToClear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupClearBits );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            ಧ್ರುವ EventBits_t uxBitsToSet ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            ಧ್ರುವ EventBits_t uxBitsToSet ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupSetBits );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         ಧ್ರುವ EventBits_t uxBitsToSet,
                                         ಧ್ರುವ EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         ಧ್ರುವ EventBits_t uxBitsToSet,
                                         ಧ್ರುವ EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupSync );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_Group_Get_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * xEventGroup ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_Group_Get_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * xEventGroup ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Event_Group_Get_ಸಂಖ್ಯೆ );
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        ಶೂನ್ಯ MPU_v_Event_Group_Set_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * xEventGroup,
                                       UBaseType_t ux_Event_Group_ಸಂಖ್ಯೆ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_v_Event_Group_Set_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * xEventGroup,
                                       UBaseType_t ux_Event_Group_ಸಂಖ್ಯೆ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Event_Group_Set_ಸಂಖ್ಯೆ );
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                                      ಧ್ರುವ ಶೂನ್ಯ * pvTxData,
                                      size_t xDataLengthBytes,
                                      TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                                      ಧ್ರುವ ಶೂನ್ಯ * pvTxData,
                                      size_t xDataLengthBytes,
                                      TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferSend );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                         ಶೂನ್ಯ * pvRxData,
                                         size_t xBufferLengthBytes,
                                         TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                         ಶೂನ್ಯ * pvRxData,
                                         size_t xBufferLengthBytes,
                                         TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferReceive );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferIsFull );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferIsEmpty );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferSpacesAvailable );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferBytesAvailable );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferSetTriggerLevel );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferNextMessageLengthBytes );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#endif /* ( configENABLE_MPU == 1 ) */
