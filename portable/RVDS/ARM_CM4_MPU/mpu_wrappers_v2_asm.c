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

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_MPU_WRAPPERS_V1 == 0 )

#എങ്കിൽ ( INCLUDE_xTaskDelayUntil == 1 )

BaseType_t MPU_xTaskDelayUntil( TickType_t * സ്ഥിരം pxPreviousWakeTime,
                                സ്ഥിരം TickType_t xTimeIncrement ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskDelayUntil( TickType_t * സ്ഥിരം pxPreviousWakeTime,
                                      സ്ഥിരം TickType_t xTimeIncrement ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTaskDelayUntilImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTaskDelayUntil_Unpriv
MPU_xTaskDelayUntil_Priv
        b MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntil_Unpriv
        svc #SYSTEM_CALL_xTaskDelayUntil
}

#endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( INCLUDE_xTaskAbortDelay == 1 )

BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTaskAbortDelayImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTaskAbortDelay_Unpriv
MPU_xTaskAbortDelay_Priv
        b MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelay_Unpriv
        svc #SYSTEM_CALL_xTaskAbortDelay
}

#endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( INCLUDE_vTaskDelay == 1 )

ശൂന്യം MPU_vTaskDelay( സ്ഥിരം TickType_t xTicksToDelay ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_vTaskDelay( സ്ഥിരം TickType_t xTicksToDelay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_vTaskDelayImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_vTaskDelay_Unpriv
MPU_vTaskDelay_Priv
        b MPU_vTaskDelayImpl
MPU_vTaskDelay_Unpriv
        svc #SYSTEM_CALL_vTaskDelay
}

#endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( INCLUDE_uxTaskPriorityGet == 1 )

UBaseType_t MPU_uxTaskPriorityGet( സ്ഥിരം TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskPriorityGet( സ്ഥിരം TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_uxTaskPriorityGetImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_uxTaskPriorityGet_Unpriv
MPU_uxTaskPriorityGet_Priv
        b MPU_uxTaskPriorityGetImpl
MPU_uxTaskPriorityGet_Unpriv
        svc #SYSTEM_CALL_uxTaskPriorityGet
}

#endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_eTaskGetStateImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_eTaskGetState_Unpriv
MPU_eTaskGetState_Priv
        b MPU_eTaskGetStateImpl
MPU_eTaskGetState_Unpriv
        svc #SYSTEM_CALL_eTaskGetState
}

#endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TRACE_FACILITY == 1 )

ശൂന്യം MPU_vTaskGetInfo( TaskHandle_t xTask,
                       TaskStatus_t * pxTaskStatus,
                       BaseType_t x_Get_Free_അട്ടി_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_vTaskGetInfo( TaskHandle_t xTask,
                             TaskStatus_t * pxTaskStatus,
                             BaseType_t x_Get_Free_അട്ടി_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_vTaskGetInfoImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_vTaskGetInfo_Unpriv
MPU_vTaskGetInfo_Priv
        b MPU_vTaskGetInfoImpl
MPU_vTaskGetInfo_Unpriv
        svc #SYSTEM_CALL_vTaskGetInfo
}

#endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( ശൂന്യം ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTaskGetIdleTaskHandleImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
MPU_xTaskGetIdleTaskHandle_Priv
        b MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
}

#endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( INCLUDE_vTaskSuspend == 1 )

ശൂന്യം MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_vTaskSuspendImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_vTaskSuspend_Unpriv
MPU_vTaskSuspend_Priv
        b MPU_vTaskSuspendImpl
MPU_vTaskSuspend_Unpriv
        svc #SYSTEM_CALL_vTaskSuspend
}

#endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( INCLUDE_vTaskSuspend == 1 )

ശൂന്യം MPU_vTaskResume( TaskHandle_t xTaskToResume ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_vTaskResume( TaskHandle_t xTaskToResume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_vTaskResumeImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_vTaskResume_Unpriv
MPU_vTaskResume_Priv
        b MPU_vTaskResumeImpl
MPU_vTaskResume_Unpriv
        svc #SYSTEM_CALL_vTaskResume
}

#endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_എണ്ണം( ശൂന്യം ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_എണ്ണം( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_x_Task_Get_Tick_എണ്ണം_Impl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_x_Task_Get_Tick_എണ്ണം_Unpriv
MPU_x_Task_Get_Tick_എണ്ണം_Priv
        b MPU_x_Task_Get_Tick_എണ്ണം_Impl
MPU_x_Task_Get_Tick_എണ്ണം_Unpriv
        svc #SYSTEM_CALL_xTaskGetTickCount
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Task_Get_സംഖ്യ_Of_Tasks( ശൂന്യം ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_സംഖ്യ_Of_Tasks( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_ux_Task_Get_സംഖ്യ_Of_Tasks_Impl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_ux_Task_Get_സംഖ്യ_Of_Tasks_Unpriv
MPU_ux_Task_Get_സംഖ്യ_Of_Tasks_Priv
        b MPU_ux_Task_Get_സംഖ്യ_Of_Tasks_Impl
MPU_ux_Task_Get_സംഖ്യ_Of_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configGENERATE_RUN_TIME_STATS == 1 )

configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounter( സ്ഥിരം TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounter( സ്ഥിരം TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_ulTaskGetRunTimeCounterImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_ulTaskGetRunTimeCounter_Unpriv
MPU_ulTaskGetRunTimeCounter_Priv
        b MPU_ulTaskGetRunTimeCounterImpl
MPU_ulTaskGetRunTimeCounter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configGENERATE_RUN_TIME_STATS == 1 )

configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercent( സ്ഥിരം TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercent( സ്ഥിരം TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_ulTaskGetRunTimePercentImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_ulTaskGetRunTimePercent_Unpriv
MPU_ulTaskGetRunTimePercent_Priv
        b MPU_ulTaskGetRunTimePercentImpl
MPU_ulTaskGetRunTimePercent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( ശൂന്യം ) FREERTOS_SYSTEM_CALL;

__asm configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_ulTaskGetIdleRunTimePercentImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_ulTaskGetIdleRunTimePercent_Unpriv
MPU_ulTaskGetIdleRunTimePercent_Priv
        b MPU_ulTaskGetIdleRunTimePercentImpl
MPU_ulTaskGetIdleRunTimePercent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( ശൂന്യം ) FREERTOS_SYSTEM_CALL;

__asm configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_ulTaskGetIdleRunTimeCounterImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_ulTaskGetIdleRunTimeCounter_Unpriv
MPU_ulTaskGetIdleRunTimeCounter_Priv
        b MPU_ulTaskGetIdleRunTimeCounterImpl
MPU_ulTaskGetIdleRunTimeCounter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )

ശൂന്യം MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_vTaskSetApplicationTaskTagImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_vTaskSetApplicationTaskTag_Unpriv
MPU_vTaskSetApplicationTaskTag_Priv
        b MPU_vTaskSetApplicationTaskTagImpl
MPU_vTaskSetApplicationTaskTag_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )

TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTaskGetApplicationTaskTagImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTaskGetApplicationTaskTag_Unpriv
MPU_xTaskGetApplicationTaskTag_Priv
        b MPU_xTaskGetApplicationTaskTagImpl
MPU_xTaskGetApplicationTaskTag_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( config_അക്കം_THREAD_LOCAL_STORAGE_POINTERS != 0 )

ശൂന്യം MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                            BaseType_t xIndex,
                                            ശൂന്യം * pv_മൂല്യം ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                  BaseType_t xIndex,
                                                  ശൂന്യം * pv_മൂല്യം ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_vTaskSetThreadLocalStoragePointerImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_vTaskSetThreadLocalStoragePointer_Unpriv
MPU_vTaskSetThreadLocalStoragePointer_Priv
        b MPU_vTaskSetThreadLocalStoragePointerImpl
MPU_vTaskSetThreadLocalStoragePointer_Unpriv
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
}

#endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( config_അക്കം_THREAD_LOCAL_STORAGE_POINTERS != 0 )

ശൂന്യം * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                               BaseType_t xIndex ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                     BaseType_t xIndex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_pvTaskGetThreadLocalStoragePointerImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_pvTaskGetThreadLocalStoragePointer_Unpriv
MPU_pvTaskGetThreadLocalStoragePointer_Priv
        b MPU_pvTaskGetThreadLocalStoragePointerImpl
MPU_pvTaskGetThreadLocalStoragePointer_Unpriv
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
}

#endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * സ്ഥിരം pxTaskStatusArray,
                                      സ്ഥിരം UBaseType_t uxArraySize,
                                      configRUN_TIME_COUNTER_TYPE * സ്ഥിരം pulTotalRunTime ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * സ്ഥിരം pxTaskStatusArray,
                                            സ്ഥിരം UBaseType_t uxArraySize,
                                            configRUN_TIME_COUNTER_TYPE * സ്ഥിരം pulTotalRunTime ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_uxTaskGetSystemStateImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_uxTaskGetSystemState_Unpriv
MPU_uxTaskGetSystemState_Priv
        b MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemState_Unpriv
        svc #SYSTEM_CALL_uxTaskGetSystemState
}

#endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( INCLUDE_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark_Impl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark_Unpriv
MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark_Priv
        b MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark_Impl
MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
}

#endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( INCLUDE_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2 == 1 )

config_അട്ടി_DEPTH_TYPE MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_അട്ടി_DEPTH_TYPE MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2_Impl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2_Unpriv
MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2_Priv
        b MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2_Impl
MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
}

#endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ശൂന്യം ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTaskGetCurrentTaskHandleImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
MPU_xTaskGetCurrentTaskHandle_Priv
        b MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
}

#endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( INCLUDE_xTaskGetSchedulerState == 1 )

BaseType_t MPU_xTaskGetSchedulerState( ശൂന്യം ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGetSchedulerState( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTaskGetSchedulerStateImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTaskGetSchedulerState_Unpriv
MPU_xTaskGetSchedulerState_Priv
        b MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerState_Unpriv
        svc #SYSTEM_CALL_xTaskGetSchedulerState
}

#endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

ശൂന്യം MPU_vTaskSetTimeOutState( TimeOut_t * സ്ഥിരം pxTimeOut ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_vTaskSetTimeOutState( TimeOut_t * സ്ഥിരം pxTimeOut ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_vTaskSetTimeOutStateImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_vTaskSetTimeOutState_Unpriv
MPU_vTaskSetTimeOutState_Priv
        b MPU_vTaskSetTimeOutStateImpl
MPU_vTaskSetTimeOutState_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * സ്ഥിരം pxTimeOut,
                                     TickType_t * സ്ഥിരം pxTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * സ്ഥിരം pxTimeOut,
                                     TickType_t * സ്ഥിരം pxTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTaskCheckForTimeOutImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTaskCheckForTimeOut_Unpriv
MPU_xTaskCheckForTimeOut_Priv
        b MPU_xTaskCheckForTimeOutImpl
MPU_xTaskCheckForTimeOut_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

BaseType_t MPU_xTaskGenericNotifyEntry( സ്ഥിരം xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGenericNotifyEntry( സ്ഥിരം xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTaskGenericNotifyImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTaskGenericNotify_Unpriv
MPU_xTaskGenericNotify_Priv
        b MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotify_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotify
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

BaseType_t MPU_xTaskGenericNotifyWaitEntry( സ്ഥിരം xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGenericNotifyWaitEntry( സ്ഥിരം xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTaskGenericNotifyWaitImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTaskGenericNotifyWait_Unpriv
MPU_xTaskGenericNotifyWait_Priv
        b MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWait_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                      BaseType_t x_Clear_എണ്ണം_On_Exit,
                                      TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                            BaseType_t x_Clear_എണ്ണം_On_Exit,
                                            TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_ulTaskGenericNotifyTakeImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
MPU_ulTaskGenericNotifyTake_Priv
        b MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTake_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t uxIndexToClear ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t uxIndexToClear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTaskGenericNotifyStateClearImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
MPU_xTaskGenericNotifyStateClear_Priv
        b MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClear_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_മൂല്യം_Clear( TaskHandle_t xTask,
                                            UBaseType_t uxIndexToClear,
                                            uint32_t ulBitsToClear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_മൂല്യം_Clear( TaskHandle_t xTask,
                                                  UBaseType_t uxIndexToClear,
                                                  uint32_t ulBitsToClear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_ul_Task_Generic_Notify_മൂല്യം_Clear_Impl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_ul_Task_Generic_Notify_മൂല്യം_Clear_Unpriv
MPU_ul_Task_Generic_Notify_മൂല്യം_Clear_Priv
        b MPU_ul_Task_Generic_Notify_മൂല്യം_Clear_Impl
MPU_ul_Task_Generic_Notify_മൂല്യം_Clear_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                  സ്ഥിരം ശൂന്യം * സ്ഥിരം pvItemToQueue,
                                  TickType_t xTicksToWait,
                                  സ്ഥിരം BaseType_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                        സ്ഥിരം ശൂന്യം * സ്ഥിരം pvItemToQueue,
                                        TickType_t xTicksToWait,
                                        സ്ഥിരം BaseType_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xQueueGenericSendImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xQueueGenericSend_Unpriv
MPU_xQueueGenericSend_Priv
        b MPU_xQueueGenericSendImpl
MPU_xQueueGenericSend_Unpriv
        svc #SYSTEM_CALL_xQueueGenericSend
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_uxQueueMessagesWaiting( സ്ഥിരം QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxQueueMessagesWaiting( സ്ഥിരം QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_uxQueueMessagesWaitingImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_uxQueueMessagesWaiting_Unpriv
MPU_uxQueueMessagesWaiting_Priv
        b MPU_uxQueueMessagesWaitingImpl
MPU_uxQueueMessagesWaiting_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_uxQueueSpacesAvailable( സ്ഥിരം QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxQueueSpacesAvailable( സ്ഥിരം QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_uxQueueSpacesAvailableImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_uxQueueSpacesAvailable_Unpriv
MPU_uxQueueSpacesAvailable_Priv
        b MPU_uxQueueSpacesAvailableImpl
MPU_uxQueueSpacesAvailable_Unpriv
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
}
/*-----------------------------------------------------------*/

BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                              ശൂന്യം * സ്ഥിരം pvBuffer,
                              TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                    ശൂന്യം * സ്ഥിരം pvBuffer,
                                    TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xQueueReceiveImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xQueueReceive_Unpriv
MPU_xQueueReceive_Priv
        b MPU_xQueueReceiveImpl
MPU_xQueueReceive_Unpriv
        svc #SYSTEM_CALL_xQueueReceive
}
/*-----------------------------------------------------------*/

BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                           ശൂന്യം * സ്ഥിരം pvBuffer,
                           TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                                 ശൂന്യം * സ്ഥിരം pvBuffer,
                                 TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xQueuePeekImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xQueuePeek_Unpriv
MPU_xQueuePeek_Priv
        b MPU_xQueuePeekImpl
MPU_xQueuePeek_Unpriv
        svc #SYSTEM_CALL_xQueuePeek
}
/*-----------------------------------------------------------*/

BaseType_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                    TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                          TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xQueueSemaphoreTakeImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xQueueSemaphoreTake_Unpriv
MPU_xQueueSemaphoreTake_Priv
        b MPU_xQueueSemaphoreTakeImpl
MPU_xQueueSemaphoreTake_Unpriv
        svc #SYSTEM_CALL_xQueueSemaphoreTake
}
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xQueueGetMutexHolderImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xQueueGetMutexHolder_Unpriv
MPU_xQueueGetMutexHolder_Priv
        b MPU_xQueueGetMutexHolderImpl
MPU_xQueueGetMutexHolder_Unpriv
        svc #SYSTEM_CALL_xQueueGetMutexHolder
}

#endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_RECURSIVE_MUTEXES == 1 )

BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                         TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xQueueTakeMutexRecursiveImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xQueueTakeMutexRecursive_Unpriv
MPU_xQueueTakeMutexRecursive_Priv
        b MPU_xQueueTakeMutexRecursiveImpl
MPU_xQueueTakeMutexRecursive_Unpriv
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
}

#endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_RECURSIVE_MUTEXES == 1 )

BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xQueueGiveMutexRecursiveImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xQueueGiveMutexRecursive_Unpriv
MPU_xQueueGiveMutexRecursive_Priv
        b MPU_xQueueGiveMutexRecursiveImpl
MPU_xQueueGiveMutexRecursive_Unpriv
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
}

#endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )

QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                സ്ഥിരം TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                      സ്ഥിരം TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xQueueSelectFromSetImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xQueueSelectFromSet_Unpriv
MPU_xQueueSelectFromSet_Priv
        b MPU_xQueueSelectFromSetImpl
MPU_xQueueSelectFromSet_Unpriv
        svc #SYSTEM_CALL_xQueueSelectFromSet
}

#endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )

BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                               QueueSetHandle_t xQueueSet ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                     QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xQueueAddToSetImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xQueueAddToSet_Unpriv
MPU_xQueueAddToSet_Priv
        b MPU_xQueueAddToSetImpl
MPU_xQueueAddToSet_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configQUEUE_REGISTRY_SIZE > 0 )

ശൂന്യം MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                              സ്ഥിരം അക്ഷരം * pcName ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                    സ്ഥിരം അക്ഷരം * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_vQueueAddToRegistryImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_vQueueAddToRegistry_Unpriv
MPU_vQueueAddToRegistry_Priv
        b MPU_vQueueAddToRegistryImpl
MPU_vQueueAddToRegistry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configQUEUE_REGISTRY_SIZE > 0 )

ശൂന്യം MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_vQueueUnregisterQueueImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_vQueueUnregisterQueue_Unpriv
MPU_vQueueUnregisterQueue_Priv
        b MPU_vQueueUnregisterQueueImpl
MPU_vQueueUnregisterQueue_Unpriv
        svc #SYSTEM_CALL_vQueueUnregisterQueue
}

#endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configQUEUE_REGISTRY_SIZE > 0 )

സ്ഥിരം അക്ഷരം * MPU_pcQueueGetName( QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm സ്ഥിരം അക്ഷരം * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_pcQueueGetNameImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_pcQueueGetName_Unpriv
MPU_pcQueueGetName_Priv
        b MPU_pcQueueGetNameImpl
MPU_pcQueueGetName_Unpriv
        svc #SYSTEM_CALL_pcQueueGetName
}

#endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TIMERS == 1 )

ശൂന്യം * MPU_pvTimerGetTimerID( സ്ഥിരം TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം * MPU_pvTimerGetTimerID( സ്ഥിരം TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_pvTimerGetTimerIDImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_pvTimerGetTimerID_Unpriv
MPU_pvTimerGetTimerID_Priv
        b MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerID_Unpriv
        svc #SYSTEM_CALL_pvTimerGetTimerID
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TIMERS == 1 )

ശൂന്യം MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                           ശൂന്യം * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                 ശൂന്യം * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_vTimerSetTimerIDImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_vTimerSetTimerID_Unpriv
MPU_vTimerSetTimerID_Priv
        b MPU_vTimerSetTimerIDImpl
MPU_vTimerSetTimerID_Unpriv
        svc #SYSTEM_CALL_vTimerSetTimerID
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TIMERS == 1 )

BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTimerIsTimerActiveImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTimerIsTimerActive_Unpriv
MPU_xTimerIsTimerActive_Priv
        b MPU_xTimerIsTimerActiveImpl
MPU_xTimerIsTimerActive_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ശൂന്യം ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ശൂന്യം ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTimerGetTimerDaemonTaskHandleImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
MPU_xTimerGetTimerDaemonTaskHandle_Priv
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TIMERS == 1 )

BaseType_t MPU_xTimerGenericCommandFromTaskEntry( സ്ഥിരം xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTimerGenericCommandFromTaskEntry( സ്ഥിരം xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTimerGenericCommandFromTaskImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
MPU_xTimerGenericCommandFromTask_Priv
        b MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTask_Unpriv
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TIMERS == 1 )

സ്ഥിരം അക്ഷരം * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm സ്ഥിരം അക്ഷരം * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_pcTimerGetNameImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_pcTimerGetName_Unpriv
MPU_pcTimerGetName_Priv
        b MPU_pcTimerGetNameImpl
MPU_pcTimerGetName_Unpriv
        svc #SYSTEM_CALL_pcTimerGetName
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TIMERS == 1 )

ശൂന്യം MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                              സ്ഥിരം BaseType_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                    സ്ഥിരം BaseType_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_vTimerSetReloadModeImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_vTimerSetReloadMode_Unpriv
MPU_vTimerSetReloadMode_Priv
        b MPU_vTimerSetReloadModeImpl
MPU_vTimerSetReloadMode_Unpriv
        svc #SYSTEM_CALL_vTimerSetReloadMode
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TIMERS == 1 )

BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTimerGetReloadModeImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTimerGetReloadMode_Unpriv
MPU_xTimerGetReloadMode_Priv
        b MPU_xTimerGetReloadModeImpl
MPU_xTimerGetReloadMode_Unpriv
        svc #SYSTEM_CALL_xTimerGetReloadMode
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TIMERS == 1 )

UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_uxTimerGetReloadModeImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_uxTimerGetReloadMode_Unpriv
MPU_uxTimerGetReloadMode_Priv
        b MPU_uxTimerGetReloadModeImpl
MPU_uxTimerGetReloadMode_Unpriv
        svc #SYSTEM_CALL_uxTimerGetReloadMode
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTimerGetPeriodImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTimerGetPeriod_Unpriv
MPU_xTimerGetPeriod_Priv
        b MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriod_Unpriv
        svc #SYSTEM_CALL_xTimerGetPeriod
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xTimerGetExpiryTimeImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xTimerGetExpiryTime_Unpriv
MPU_xTimerGetExpiryTime_Priv
        b MPU_xTimerGetExpiryTimeImpl
MPU_xTimerGetExpiryTime_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupWaitBitsEntry( സ്ഥിരം xEventGroupWaitBitsParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupWaitBitsEntry( സ്ഥിരം xEventGroupWaitBitsParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xEventGroupWaitBitsImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xEventGroupWaitBits_Unpriv
MPU_xEventGroupWaitBits_Priv
        b MPU_xEventGroupWaitBitsImpl
MPU_xEventGroupWaitBits_Unpriv
        svc #SYSTEM_CALL_xEventGroupWaitBits
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                      സ്ഥിരം EventBits_t uxBitsToClear ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                            സ്ഥിരം EventBits_t uxBitsToClear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xEventGroupClearBitsImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xEventGroupClearBits_Unpriv
MPU_xEventGroupClearBits_Priv
        b MPU_xEventGroupClearBitsImpl
MPU_xEventGroupClearBits_Unpriv
        svc #SYSTEM_CALL_xEventGroupClearBits
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                    സ്ഥിരം EventBits_t uxBitsToSet ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                          സ്ഥിരം EventBits_t uxBitsToSet ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xEventGroupSetBitsImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xEventGroupSetBits_Unpriv
MPU_xEventGroupSetBits_Priv
        b MPU_xEventGroupSetBitsImpl
MPU_xEventGroupSetBits_Unpriv
        svc #SYSTEM_CALL_xEventGroupSetBits
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                 സ്ഥിരം EventBits_t uxBitsToSet,
                                 സ്ഥിരം EventBits_t uxBitsToWaitFor,
                                 TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                       സ്ഥിരം EventBits_t uxBitsToSet,
                                       സ്ഥിരം EventBits_t uxBitsToWaitFor,
                                       TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xEventGroupSyncImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xEventGroupSync_Unpriv
MPU_xEventGroupSync_Priv
        b MPU_xEventGroupSyncImpl
MPU_xEventGroupSync_Unpriv
        svc #SYSTEM_CALL_xEventGroupSync
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_Group_Get_സംഖ്യ( ശൂന്യം * xEventGroup ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_Group_Get_സംഖ്യ( ശൂന്യം * xEventGroup ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_ux_Event_Group_Get_സംഖ്യ_Impl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_ux_Event_Group_Get_സംഖ്യ_Unpriv
MPU_ux_Event_Group_Get_സംഖ്യ_Priv
        b MPU_ux_Event_Group_Get_സംഖ്യ_Impl
MPU_ux_Event_Group_Get_സംഖ്യ_Unpriv
        svc #SYSTEM_CALL_uxEventGroupGetNumber
}

#endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

ശൂന്യം MPU_v_Event_Group_Set_സംഖ്യ( ശൂന്യം * xEventGroup,
                               UBaseType_t ux_Event_Group_സംഖ്യ ) FREERTOS_SYSTEM_CALL;

__asm ശൂന്യം MPU_v_Event_Group_Set_സംഖ്യ( ശൂന്യം * xEventGroup,
                                     UBaseType_t ux_Event_Group_സംഖ്യ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_v_Event_Group_Set_സംഖ്യ_Impl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_v_Event_Group_Set_സംഖ്യ_Unpriv
MPU_v_Event_Group_Set_സംഖ്യ_Priv
        b MPU_v_Event_Group_Set_സംഖ്യ_Impl
MPU_v_Event_Group_Set_സംഖ്യ_Unpriv
        svc #SYSTEM_CALL_vEventGroupSetNumber
}

#endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                              സ്ഥിരം ശൂന്യം * pvTxData,
                              size_t xDataLengthBytes,
                              TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                                    സ്ഥിരം ശൂന്യം * pvTxData,
                                    size_t xDataLengthBytes,
                                    TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xStreamBufferSendImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xStreamBufferSend_Unpriv
MPU_xStreamBufferSend_Priv
        b MPU_xStreamBufferSendImpl
MPU_xStreamBufferSend_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSend
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                 ശൂന്യം * pvRxData,
                                 size_t xBufferLengthBytes,
                                 TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                       ശൂന്യം * pvRxData,
                                       size_t xBufferLengthBytes,
                                       TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xStreamBufferReceiveImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xStreamBufferReceive_Unpriv
MPU_xStreamBufferReceive_Priv
        b MPU_xStreamBufferReceiveImpl
MPU_xStreamBufferReceive_Unpriv
        svc #SYSTEM_CALL_xStreamBufferReceive
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xStreamBufferIsFullImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xStreamBufferIsFull_Unpriv
MPU_xStreamBufferIsFull_Priv
        b MPU_xStreamBufferIsFullImpl
MPU_xStreamBufferIsFull_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xStreamBufferIsEmptyImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xStreamBufferIsEmpty_Unpriv
MPU_xStreamBufferIsEmpty_Priv
        b MPU_xStreamBufferIsEmptyImpl
MPU_xStreamBufferIsEmpty_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xStreamBufferSpacesAvailableImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xStreamBufferSpacesAvailable_Unpriv
MPU_xStreamBufferSpacesAvailable_Priv
        b MPU_xStreamBufferSpacesAvailableImpl
MPU_xStreamBufferSpacesAvailable_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xStreamBufferBytesAvailableImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xStreamBufferBytesAvailable_Unpriv
MPU_xStreamBufferBytesAvailable_Priv
        b MPU_xStreamBufferBytesAvailableImpl
MPU_xStreamBufferBytesAvailable_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xStreamBufferSetTriggerLevelImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xStreamBufferSetTriggerLevel_Unpriv
MPU_xStreamBufferSetTriggerLevel_Priv
        b MPU_xStreamBufferSetTriggerLevelImpl
MPU_xStreamBufferSetTriggerLevel_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ബാഹ്യ MPU_xStreamBufferNextMessageLengthBytesImpl

    തള്ളുക {r0}
    mrs r0, control
    tst r0, #1
    എടുക്കുക {r0}
    bne MPU_xStreamBufferNextMessageLengthBytes_Unpriv
MPU_xStreamBufferNextMessageLengthBytes_Priv
        b MPU_xStreamBufferNextMessageLengthBytesImpl
MPU_xStreamBufferNextMessageLengthBytes_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#endif /* configUSE_MPU_WRAPPERS_V1 == 0 */
