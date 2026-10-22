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
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"
#അന്തര്ഭാവ "queue.h"
#അന്തര്ഭാവ "timers.h"
#അന്തര്ഭാവ "event_groups.h"
#അന്തര്ഭാവ "stream_buffer.h"
#അന്തര്ഭാവ "mpu_prototypes.h"
#അന്തര്ഭാവ "mpu_syscall_numbers.h"
#അന്തര്ഭാവ "portmacro.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#എങ്കിൽ ( configENABLE_MPU == 1 )

    /*
     * Common single-SVC dispatch: wrappers do only one SVC.
     * The SVC handler decides whether to tail-call the implementation directly
     * (privileged) or set up full system-call state (unprivileged).
     */
    #define FREERTOS_MPU_SVC_DISPATCH( x_System_Call_സംഖ്യ )  \
        __asm അസ്ഥിര (                                    \
            "svc %0     \n"                                 \
            :                                               \
            : "i" ( x_System_Call_സംഖ്യ )                     \
            : "memory"                                      \
        );

    #എങ്കിൽ ( INCLUDE_xTaskDelayUntil == 1 )

        BaseType_t MPU_xTaskDelayUntil( TickType_t * സ്ഥിരം pxPreviousWakeTime,
                                        സ്ഥിരം TickType_t xTimeIncrement ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskDelayUntil( TickType_t * സ്ഥിരം pxPreviousWakeTime,
                                        സ്ഥിരം TickType_t xTimeIncrement ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskDelayUntil );
        }

    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskAbortDelay == 1 )

        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskAbortDelay );
        }

    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_vTaskDelay == 1 )

        ശൂന്യം MPU_vTaskDelay( സ്ഥിരം TickType_t xTicksToDelay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം MPU_vTaskDelay( സ്ഥിരം TickType_t xTicksToDelay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskDelay );
        }

    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGet( സ്ഥിരം TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskPriorityGet( സ്ഥിരം TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskPriorityGet );
        }

    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_eTaskGetState );
        }

    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TRACE_FACILITY == 1 )

        ശൂന്യം MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t x_Get_Free_അട്ടി_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം MPU_vTaskGetInfo( TaskHandle_t xTask,
                               TaskStatus_t * pxTaskStatus,
                               BaseType_t x_Get_Free_അട്ടി_Space,
                               eTaskState eState ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskGetInfo );
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ശൂന്യം ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ശൂന്യം ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetIdleTaskHandle );
        }

    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_vTaskSuspend == 1 )

        ശൂന്യം MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSuspend );
        }

/*-----------------------------------------------------------*/

        ശൂന്യം MPU_vTaskResume( TaskHandle_t xTaskToResume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം MPU_vTaskResume( TaskHandle_t xTaskToResume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskResume );
        }

    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_എണ്ണം( ശൂന്യം ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_എണ്ണം( ശൂന്യം ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Tick_എണ്ണം );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_സംഖ്യ_Of_Tasks( ശൂന്യം ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_സംഖ്യ_Of_Tasks( ശൂന്യം ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_സംഖ്യ_Of_Tasks );
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configGENERATE_RUN_TIME_STATS == 1 )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounter( സ്ഥിരം TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounter( സ്ഥിരം TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGetRunTimeCounter );
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configGENERATE_RUN_TIME_STATS == 1 )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercent( സ്ഥിരം TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercent( സ്ഥിരം TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGetRunTimePercent );
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( ശൂന്യം ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( ശൂന്യം ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGetIdleRunTimePercent );
        }

/*-----------------------------------------------------------*/

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( ശൂന്യം ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( ശൂന്യം ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGetIdleRunTimeCounter );
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )

        ശൂന്യം MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSetApplicationTaskTag );
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetApplicationTaskTag );
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( config_അക്കം_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        ശൂന്യം MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t xIndex,
                                                    ശൂന്യം * pv_മൂല്യം ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                    BaseType_t xIndex,
                                                    ശൂന്യം * pv_മൂല്യം ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSetThreadLocalStoragePointer );
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( config_അക്കം_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        ശൂന്യം * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t xIndex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                       BaseType_t xIndex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer );
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * സ്ഥിരം pxTaskStatusArray,
                                              സ്ഥിരം UBaseType_t uxArraySize,
                                              configRUN_TIME_COUNTER_TYPE * സ്ഥിരം pulTotalRunTime ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * സ്ഥിരം pxTaskStatusArray,
                                              സ്ഥിരം UBaseType_t uxArraySize,
                                              configRUN_TIME_COUNTER_TYPE * സ്ഥിരം pulTotalRunTime ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskGetSystemState );
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark );
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2 == 1 )

        config_അട്ടി_DEPTH_TYPE MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_അട്ടി_DEPTH_TYPE MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2 );
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ശൂന്യം ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ശൂന്യം ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetCurrentTaskHandle );
        }

    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskGetSchedulerState == 1 )

        BaseType_t MPU_xTaskGetSchedulerState( ശൂന്യം ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGetSchedulerState( ശൂന്യം ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetSchedulerState );
        }

    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ശൂന്യം MPU_vTaskSetTimeOutState( TimeOut_t * സ്ഥിരം pxTimeOut ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ശൂന്യം MPU_vTaskSetTimeOutState( TimeOut_t * സ്ഥിരം pxTimeOut ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSetTimeOutState );
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * സ്ഥിരം pxTimeOut,
                                         TickType_t * സ്ഥിരം pxTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * സ്ഥിരം pxTimeOut,
                                         TickType_t * സ്ഥിരം pxTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskCheckForTimeOut );
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyEntry( സ്ഥിരം xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGenericNotifyEntry( സ്ഥിരം xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotify );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyWaitEntry( സ്ഥിരം xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGenericNotifyWaitEntry( സ്ഥിരം xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyWait );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                              BaseType_t x_Clear_എണ്ണം_On_Exit,
                                              TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                              BaseType_t x_Clear_എണ്ണം_On_Exit,
                                              TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGenericNotifyTake );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t uxIndexToClear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t uxIndexToClear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyStateClear );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_മൂല്യം_Clear( TaskHandle_t xTask,
                                                    UBaseType_t uxIndexToClear,
                                                    uint32_t ulBitsToClear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_മൂല്യം_Clear( TaskHandle_t xTask,
                                                    UBaseType_t uxIndexToClear,
                                                    uint32_t ulBitsToClear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Generic_Notify_മൂല്യം_Clear );
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      സ്ഥിരം ശൂന്യം * സ്ഥിരം pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      സ്ഥിരം BaseType_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      സ്ഥിരം ശൂന്യം * സ്ഥിരം pvItemToQueue,
                                      TickType_t xTicksToWait,
                                      സ്ഥിരം BaseType_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGenericSend );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaiting( സ്ഥിരം QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_uxQueueMessagesWaiting( സ്ഥിരം QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxQueueMessagesWaiting );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailable( സ്ഥിരം QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_uxQueueSpacesAvailable( സ്ഥിരം QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxQueueSpacesAvailable );
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                  ശൂന്യം * സ്ഥിരം pvBuffer,
                                  TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                  ശൂന്യം * സ്ഥിരം pvBuffer,
                                  TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueReceive );
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               ശൂന്യം * സ്ഥിരം pvBuffer,
                               TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               ശൂന്യം * സ്ഥിരം pvBuffer,
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

    #എങ്കിൽ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGetMutexHolder );
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueTakeMutexRecursive );
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGiveMutexRecursive );
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        സ്ഥിരം TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                        സ്ഥിരം TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueSelectFromSet );
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                       QueueSetHandle_t xQueueSet ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueAddToSet );
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configQUEUE_REGISTRY_SIZE > 0 )

        ശൂന്യം MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      സ്ഥിരം അക്ഷരം * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                      സ്ഥിരം അക്ഷരം * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vQueueAddToRegistry );
        }

    #endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configQUEUE_REGISTRY_SIZE > 0 )

        ശൂന്യം MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vQueueUnregisterQueue );
        }

    #endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configQUEUE_REGISTRY_SIZE > 0 )

        സ്ഥിരം അക്ഷരം * MPU_pcQueueGetName( QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        സ്ഥിരം അക്ഷരം * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcQueueGetName );
        }

    #endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        ശൂന്യം * MPU_pvTimerGetTimerID( സ്ഥിരം TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം * MPU_pvTimerGetTimerID( സ്ഥിരം TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTimerGetTimerID );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        ശൂന്യം MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   ശൂന്യം * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                   ശൂന്യം * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTimerSetTimerID );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerIsTimerActive );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ശൂന്യം ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ശൂന്യം ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromTaskEntry( സ്ഥിരം xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTimerGenericCommandFromTaskEntry( സ്ഥിരം xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGenericCommandFromTask );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        സ്ഥിരം അക്ഷരം * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        സ്ഥിരം അക്ഷരം * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcTimerGetName );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        ശൂന്യം MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      സ്ഥിരം BaseType_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                      സ്ഥിരം BaseType_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTimerSetReloadMode );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetReloadMode );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTimerGetReloadMode );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetPeriod );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetExpiryTime );
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupWaitBitsEntry( സ്ഥിരം xEventGroupWaitBitsParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupWaitBitsEntry( സ്ഥിരം xEventGroupWaitBitsParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupWaitBits );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              സ്ഥിരം EventBits_t uxBitsToClear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                              സ്ഥിരം EventBits_t uxBitsToClear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupClearBits );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            സ്ഥിരം EventBits_t uxBitsToSet ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                            സ്ഥിരം EventBits_t uxBitsToSet ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupSetBits );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         സ്ഥിരം EventBits_t uxBitsToSet,
                                         സ്ഥിരം EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                         സ്ഥിരം EventBits_t uxBitsToSet,
                                         സ്ഥിരം EventBits_t uxBitsToWaitFor,
                                         TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xEventGroupSync );
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_Group_Get_സംഖ്യ( ശൂന്യം * xEventGroup ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_Group_Get_സംഖ്യ( ശൂന്യം * xEventGroup ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Event_Group_Get_സംഖ്യ );
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        ശൂന്യം MPU_v_Event_Group_Set_സംഖ്യ( ശൂന്യം * xEventGroup,
                                       UBaseType_t ux_Event_Group_സംഖ്യ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ശൂന്യം MPU_v_Event_Group_Set_സംഖ്യ( ശൂന്യം * xEventGroup,
                                       UBaseType_t ux_Event_Group_സംഖ്യ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Event_Group_Set_സംഖ്യ );
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                                      സ്ഥിരം ശൂന്യം * pvTxData,
                                      size_t xDataLengthBytes,
                                      TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                                      സ്ഥിരം ശൂന്യം * pvTxData,
                                      size_t xDataLengthBytes,
                                      TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferSend );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                         ശൂന്യം * pvRxData,
                                         size_t xBufferLengthBytes,
                                         TickType_t xTicksToWait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                         ശൂന്യം * pvRxData,
                                         size_t xBufferLengthBytes,
                                         TickType_t xTicksToWait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferReceive );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferIsFull );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferIsEmpty );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferSpacesAvailable );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferBytesAvailable );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferSetTriggerLevel );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xStreamBufferNextMessageLengthBytes );
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#endif /* ( configENABLE_MPU == 1 ) */
