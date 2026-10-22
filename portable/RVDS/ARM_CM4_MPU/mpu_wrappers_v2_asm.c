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
#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"
#ଅନ୍ତର୍ଭାଵ "queue.h"
#ଅନ୍ତର୍ଭାଵ "timers.h"
#ଅନ୍ତର୍ଭାଵ "event_groups.h"
#ଅନ୍ତର୍ଭାଵ "stream_buffer.h"
#ଅନ୍ତର୍ଭାଵ "mpu_prototypes.h"
#ଅନ୍ତର୍ଭାଵ "mpu_syscall_numbers.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_MPU_WRAPPERS_V1 == 0 )

#ଯଦି ( INCLUDE_xTaskDelayUntil == 1 )

BaseType_t MPU_xTaskDelayUntil( TickType_t * ଅଚଳ pxPreviousWakeTime,
                                ଅଚଳ TickType_t xTimeIncrement ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskDelayUntil( TickType_t * ଅଚଳ pxPreviousWakeTime,
                                      ଅଚଳ TickType_t xTimeIncrement ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTaskDelayUntilImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTaskDelayUntil_Unpriv
MPU_xTaskDelayUntil_Priv
        b MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntil_Unpriv
        svc #SYSTEM_CALL_xTaskDelayUntil
}

#endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( INCLUDE_xTaskAbortDelay == 1 )

BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTaskAbortDelayImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTaskAbortDelay_Unpriv
MPU_xTaskAbortDelay_Priv
        b MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelay_Unpriv
        svc #SYSTEM_CALL_xTaskAbortDelay
}

#endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( INCLUDE_vTaskDelay == 1 )

ଶୂନ୍ୟ MPU_vTaskDelay( ଅଚଳ TickType_t xTicksToDelay ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_vTaskDelay( ଅଚଳ TickType_t xTicksToDelay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_vTaskDelayImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_vTaskDelay_Unpriv
MPU_vTaskDelay_Priv
        b MPU_vTaskDelayImpl
MPU_vTaskDelay_Unpriv
        svc #SYSTEM_CALL_vTaskDelay
}

#endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( INCLUDE_uxTaskPriorityGet == 1 )

UBaseType_t MPU_uxTaskPriorityGet( ଅଚଳ TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskPriorityGet( ଅଚଳ TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_uxTaskPriorityGetImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_uxTaskPriorityGet_Unpriv
MPU_uxTaskPriorityGet_Priv
        b MPU_uxTaskPriorityGetImpl
MPU_uxTaskPriorityGet_Unpriv
        svc #SYSTEM_CALL_uxTaskPriorityGet
}

#endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_eTaskGetStateImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_eTaskGetState_Unpriv
MPU_eTaskGetState_Priv
        b MPU_eTaskGetStateImpl
MPU_eTaskGetState_Unpriv
        svc #SYSTEM_CALL_eTaskGetState
}

#endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TRACE_FACILITY == 1 )

ଶୂନ୍ୟ MPU_vTaskGetInfo( TaskHandle_t xTask,
                       TaskStatus_t * pxTaskStatus,
                       BaseType_t x_Get_Free_ଗଦା_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_vTaskGetInfo( TaskHandle_t xTask,
                             TaskStatus_t * pxTaskStatus,
                             BaseType_t x_Get_Free_ଗଦା_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_vTaskGetInfoImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_vTaskGetInfo_Unpriv
MPU_vTaskGetInfo_Priv
        b MPU_vTaskGetInfoImpl
MPU_vTaskGetInfo_Unpriv
        svc #SYSTEM_CALL_vTaskGetInfo
}

#endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( ଶୂନ୍ୟ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( ଶୂନ୍ୟ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTaskGetIdleTaskHandleImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
MPU_xTaskGetIdleTaskHandle_Priv
        b MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
}

#endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( INCLUDE_vTaskSuspend == 1 )

ଶୂନ୍ୟ MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_vTaskSuspendImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_vTaskSuspend_Unpriv
MPU_vTaskSuspend_Priv
        b MPU_vTaskSuspendImpl
MPU_vTaskSuspend_Unpriv
        svc #SYSTEM_CALL_vTaskSuspend
}

#endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( INCLUDE_vTaskSuspend == 1 )

ଶୂନ୍ୟ MPU_vTaskResume( TaskHandle_t xTaskToResume ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_vTaskResume( TaskHandle_t xTaskToResume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_vTaskResumeImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_vTaskResume_Unpriv
MPU_vTaskResume_Priv
        b MPU_vTaskResumeImpl
MPU_vTaskResume_Unpriv
        svc #SYSTEM_CALL_vTaskResume
}

#endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_ଗଣନା( ଶୂନ୍ୟ ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_ଗଣନା( ଶୂନ୍ୟ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_x_Task_Get_Tick_ଗଣନା_Impl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_x_Task_Get_Tick_ଗଣନା_Unpriv
MPU_x_Task_Get_Tick_ଗଣନା_Priv
        b MPU_x_Task_Get_Tick_ଗଣନା_Impl
MPU_x_Task_Get_Tick_ଗଣନା_Unpriv
        svc #SYSTEM_CALL_xTaskGetTickCount
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Task_Get_ସଂଖ୍ୟା_Of_Tasks( ଶୂନ୍ୟ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_ସଂଖ୍ୟା_Of_Tasks( ଶୂନ୍ୟ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_ux_Task_Get_ସଂଖ୍ୟା_Of_Tasks_Impl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_ux_Task_Get_ସଂଖ୍ୟା_Of_Tasks_Unpriv
MPU_ux_Task_Get_ସଂଖ୍ୟା_Of_Tasks_Priv
        b MPU_ux_Task_Get_ସଂଖ୍ୟା_Of_Tasks_Impl
MPU_ux_Task_Get_ସଂଖ୍ୟା_Of_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#ଯଦି ( configGENERATE_RUN_TIME_STATS == 1 )

configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounter( ଅଚଳ TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounter( ଅଚଳ TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_ulTaskGetRunTimeCounterImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_ulTaskGetRunTimeCounter_Unpriv
MPU_ulTaskGetRunTimeCounter_Priv
        b MPU_ulTaskGetRunTimeCounterImpl
MPU_ulTaskGetRunTimeCounter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configGENERATE_RUN_TIME_STATS == 1 )

configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercent( ଅଚଳ TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercent( ଅଚଳ TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_ulTaskGetRunTimePercentImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_ulTaskGetRunTimePercent_Unpriv
MPU_ulTaskGetRunTimePercent_Priv
        b MPU_ulTaskGetRunTimePercentImpl
MPU_ulTaskGetRunTimePercent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( ଶୂନ୍ୟ ) FREERTOS_SYSTEM_CALL;

__asm configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercent( ଶୂନ୍ୟ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_ulTaskGetIdleRunTimePercentImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_ulTaskGetIdleRunTimePercent_Unpriv
MPU_ulTaskGetIdleRunTimePercent_Priv
        b MPU_ulTaskGetIdleRunTimePercentImpl
MPU_ulTaskGetIdleRunTimePercent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#ଯଦି ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( ଶୂନ୍ୟ ) FREERTOS_SYSTEM_CALL;

__asm configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounter( ଶୂନ୍ୟ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_ulTaskGetIdleRunTimeCounterImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_ulTaskGetIdleRunTimeCounter_Unpriv
MPU_ulTaskGetIdleRunTimeCounter_Priv
        b MPU_ulTaskGetIdleRunTimeCounterImpl
MPU_ulTaskGetIdleRunTimeCounter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_APPLICATION_TASK_TAG == 1 )

ଶୂନ୍ୟ MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_vTaskSetApplicationTaskTagImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_vTaskSetApplicationTaskTag_Unpriv
MPU_vTaskSetApplicationTaskTag_Priv
        b MPU_vTaskSetApplicationTaskTagImpl
MPU_vTaskSetApplicationTaskTag_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_APPLICATION_TASK_TAG == 1 )

TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTaskGetApplicationTaskTagImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTaskGetApplicationTaskTag_Unpriv
MPU_xTaskGetApplicationTaskTag_Priv
        b MPU_xTaskGetApplicationTaskTagImpl
MPU_xTaskGetApplicationTaskTag_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( config_ଅଙ୍କ_THREAD_LOCAL_STORAGE_POINTERS != 0 )

ଶୂନ୍ୟ MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                            BaseType_t xIndex,
                                            ଶୂନ୍ୟ * pv_ମୂଲ୍ୟ ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                  BaseType_t xIndex,
                                                  ଶୂନ୍ୟ * pv_ମୂଲ୍ୟ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_vTaskSetThreadLocalStoragePointerImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_vTaskSetThreadLocalStoragePointer_Unpriv
MPU_vTaskSetThreadLocalStoragePointer_Priv
        b MPU_vTaskSetThreadLocalStoragePointerImpl
MPU_vTaskSetThreadLocalStoragePointer_Unpriv
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
}

#endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( config_ଅଙ୍କ_THREAD_LOCAL_STORAGE_POINTERS != 0 )

ଶୂନ୍ୟ * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                               BaseType_t xIndex ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                     BaseType_t xIndex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_pvTaskGetThreadLocalStoragePointerImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_pvTaskGetThreadLocalStoragePointer_Unpriv
MPU_pvTaskGetThreadLocalStoragePointer_Priv
        b MPU_pvTaskGetThreadLocalStoragePointerImpl
MPU_pvTaskGetThreadLocalStoragePointer_Unpriv
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
}

#endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * ଅଚଳ pxTaskStatusArray,
                                      ଅଚଳ UBaseType_t uxArraySize,
                                      configRUN_TIME_COUNTER_TYPE * ଅଚଳ pulTotalRunTime ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * ଅଚଳ pxTaskStatusArray,
                                            ଅଚଳ UBaseType_t uxArraySize,
                                            configRUN_TIME_COUNTER_TYPE * ଅଚଳ pulTotalRunTime ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_uxTaskGetSystemStateImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_uxTaskGetSystemState_Unpriv
MPU_uxTaskGetSystemState_Priv
        b MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemState_Unpriv
        svc #SYSTEM_CALL_uxTaskGetSystemState
}

#endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( INCLUDE_ux_Task_Get_ଗଦା_ଉପର_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark_Impl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark_Unpriv
MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark_Priv
        b MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark_Impl
MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
}

#endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( INCLUDE_ux_Task_Get_ଗଦା_ଉପର_Water_Mark2 == 1 )

config_ଗଦା_DEPTH_TYPE MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_ଗଦା_DEPTH_TYPE MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark2_Impl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark2_Unpriv
MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark2_Priv
        b MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark2_Impl
MPU_ux_Task_Get_ଗଦା_ଉପର_Water_Mark2_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
}

#endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ଶୂନ୍ୟ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ଶୂନ୍ୟ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTaskGetCurrentTaskHandleImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
MPU_xTaskGetCurrentTaskHandle_Priv
        b MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
}

#endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#ଯଦି ( INCLUDE_xTaskGetSchedulerState == 1 )

BaseType_t MPU_xTaskGetSchedulerState( ଶୂନ୍ୟ ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGetSchedulerState( ଶୂନ୍ୟ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTaskGetSchedulerStateImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTaskGetSchedulerState_Unpriv
MPU_xTaskGetSchedulerState_Priv
        b MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerState_Unpriv
        svc #SYSTEM_CALL_xTaskGetSchedulerState
}

#endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ MPU_vTaskSetTimeOutState( TimeOut_t * ଅଚଳ pxTimeOut ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_vTaskSetTimeOutState( TimeOut_t * ଅଚଳ pxTimeOut ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_vTaskSetTimeOutStateImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_vTaskSetTimeOutState_Unpriv
MPU_vTaskSetTimeOutState_Priv
        b MPU_vTaskSetTimeOutStateImpl
MPU_vTaskSetTimeOutState_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * ଅଚଳ pxTimeOut,
                                     TickType_t * ଅଚଳ pxTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * ଅଚଳ pxTimeOut,
                                     TickType_t * ଅଚଳ pxTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTaskCheckForTimeOutImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTaskCheckForTimeOut_Unpriv
MPU_xTaskCheckForTimeOut_Priv
        b MPU_xTaskCheckForTimeOutImpl
MPU_xTaskCheckForTimeOut_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TASK_NOTIFICATIONS == 1 )

BaseType_t MPU_xTaskGenericNotifyEntry( ଅଚଳ xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGenericNotifyEntry( ଅଚଳ xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTaskGenericNotifyImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTaskGenericNotify_Unpriv
MPU_xTaskGenericNotify_Priv
        b MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotify_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotify
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TASK_NOTIFICATIONS == 1 )

BaseType_t MPU_xTaskGenericNotifyWaitEntry( ଅଚଳ xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGenericNotifyWaitEntry( ଅଚଳ xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTaskGenericNotifyWaitImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTaskGenericNotifyWait_Unpriv
MPU_xTaskGenericNotifyWait_Priv
        b MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWait_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                      BaseType_t x_Clear_ଗଣନା_On_Exit,
                                      TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t uxIndexToWaitOn,
                                            BaseType_t x_Clear_ଗଣନା_On_Exit,
                                            TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_ulTaskGenericNotifyTakeImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
MPU_ulTaskGenericNotifyTake_Priv
        b MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTake_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TASK_NOTIFICATIONS == 1 )

BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t uxIndexToClear ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t uxIndexToClear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTaskGenericNotifyStateClearImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
MPU_xTaskGenericNotifyStateClear_Priv
        b MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClear_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_ମୂଲ୍ୟ_Clear( TaskHandle_t xTask,
                                            UBaseType_t uxIndexToClear,
                                            uint32_t ulBitsToClear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_ମୂଲ୍ୟ_Clear( TaskHandle_t xTask,
                                                  UBaseType_t uxIndexToClear,
                                                  uint32_t ulBitsToClear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_ul_Task_Generic_Notify_ମୂଲ୍ୟ_Clear_Impl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_ul_Task_Generic_Notify_ମୂଲ୍ୟ_Clear_Unpriv
MPU_ul_Task_Generic_Notify_ମୂଲ୍ୟ_Clear_Priv
        b MPU_ul_Task_Generic_Notify_ମୂଲ୍ୟ_Clear_Impl
MPU_ul_Task_Generic_Notify_ମୂଲ୍ୟ_Clear_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                  ଅଚଳ ଶୂନ୍ୟ * ଅଚଳ pvItemToQueue,
                                  TickType_t xTicksToWait,
                                  ଅଚଳ BaseType_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                        ଅଚଳ ଶୂନ୍ୟ * ଅଚଳ pvItemToQueue,
                                        TickType_t xTicksToWait,
                                        ଅଚଳ BaseType_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xQueueGenericSendImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xQueueGenericSend_Unpriv
MPU_xQueueGenericSend_Priv
        b MPU_xQueueGenericSendImpl
MPU_xQueueGenericSend_Unpriv
        svc #SYSTEM_CALL_xQueueGenericSend
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_uxQueueMessagesWaiting( ଅଚଳ QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxQueueMessagesWaiting( ଅଚଳ QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_uxQueueMessagesWaitingImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_uxQueueMessagesWaiting_Unpriv
MPU_uxQueueMessagesWaiting_Priv
        b MPU_uxQueueMessagesWaitingImpl
MPU_uxQueueMessagesWaiting_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_uxQueueSpacesAvailable( ଅଚଳ QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxQueueSpacesAvailable( ଅଚଳ QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_uxQueueSpacesAvailableImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_uxQueueSpacesAvailable_Unpriv
MPU_uxQueueSpacesAvailable_Priv
        b MPU_uxQueueSpacesAvailableImpl
MPU_uxQueueSpacesAvailable_Unpriv
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
}
/*-----------------------------------------------------------*/

BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                              ଶୂନ୍ୟ * ଅଚଳ pvBuffer,
                              TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                    ଶୂନ୍ୟ * ଅଚଳ pvBuffer,
                                    TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xQueueReceiveImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xQueueReceive_Unpriv
MPU_xQueueReceive_Priv
        b MPU_xQueueReceiveImpl
MPU_xQueueReceive_Unpriv
        svc #SYSTEM_CALL_xQueueReceive
}
/*-----------------------------------------------------------*/

BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                           ଶୂନ୍ୟ * ଅଚଳ pvBuffer,
                           TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                                 ଶୂନ୍ୟ * ଅଚଳ pvBuffer,
                                 TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xQueuePeekImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
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
    ବାହ୍ୟ MPU_xQueueSemaphoreTakeImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xQueueSemaphoreTake_Unpriv
MPU_xQueueSemaphoreTake_Priv
        b MPU_xQueueSemaphoreTakeImpl
MPU_xQueueSemaphoreTake_Unpriv
        svc #SYSTEM_CALL_xQueueSemaphoreTake
}
/*-----------------------------------------------------------*/

#ଯଦି ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xQueueGetMutexHolderImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xQueueGetMutexHolder_Unpriv
MPU_xQueueGetMutexHolder_Priv
        b MPU_xQueueGetMutexHolderImpl
MPU_xQueueGetMutexHolder_Unpriv
        svc #SYSTEM_CALL_xQueueGetMutexHolder
}

#endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_RECURSIVE_MUTEXES == 1 )

BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                         TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xQueueTakeMutexRecursiveImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xQueueTakeMutexRecursive_Unpriv
MPU_xQueueTakeMutexRecursive_Priv
        b MPU_xQueueTakeMutexRecursiveImpl
MPU_xQueueTakeMutexRecursive_Unpriv
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
}

#endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_RECURSIVE_MUTEXES == 1 )

BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xQueueGiveMutexRecursiveImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xQueueGiveMutexRecursive_Unpriv
MPU_xQueueGiveMutexRecursive_Priv
        b MPU_xQueueGiveMutexRecursiveImpl
MPU_xQueueGiveMutexRecursive_Unpriv
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
}

#endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_QUEUE_SETS == 1 )

QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                ଅଚଳ TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                      ଅଚଳ TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xQueueSelectFromSetImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xQueueSelectFromSet_Unpriv
MPU_xQueueSelectFromSet_Priv
        b MPU_xQueueSelectFromSetImpl
MPU_xQueueSelectFromSet_Unpriv
        svc #SYSTEM_CALL_xQueueSelectFromSet
}

#endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_QUEUE_SETS == 1 )

BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                               QueueSetHandle_t xQueueSet ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                     QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xQueueAddToSetImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xQueueAddToSet_Unpriv
MPU_xQueueAddToSet_Priv
        b MPU_xQueueAddToSetImpl
MPU_xQueueAddToSet_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configQUEUE_REGISTRY_SIZE > 0 )

ଶୂନ୍ୟ MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                              ଅଚଳ ଅକ୍ଷର * pcName ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                    ଅଚଳ ଅକ୍ଷର * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_vQueueAddToRegistryImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_vQueueAddToRegistry_Unpriv
MPU_vQueueAddToRegistry_Priv
        b MPU_vQueueAddToRegistryImpl
MPU_vQueueAddToRegistry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configQUEUE_REGISTRY_SIZE > 0 )

ଶୂନ୍ୟ MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_vQueueUnregisterQueueImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_vQueueUnregisterQueue_Unpriv
MPU_vQueueUnregisterQueue_Priv
        b MPU_vQueueUnregisterQueueImpl
MPU_vQueueUnregisterQueue_Unpriv
        svc #SYSTEM_CALL_vQueueUnregisterQueue
}

#endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configQUEUE_REGISTRY_SIZE > 0 )

ଅଚଳ ଅକ୍ଷର * MPU_pcQueueGetName( QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm ଅଚଳ ଅକ୍ଷର * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_pcQueueGetNameImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_pcQueueGetName_Unpriv
MPU_pcQueueGetName_Priv
        b MPU_pcQueueGetNameImpl
MPU_pcQueueGetName_Unpriv
        svc #SYSTEM_CALL_pcQueueGetName
}

#endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TIMERS == 1 )

ଶୂନ୍ୟ * MPU_pvTimerGetTimerID( ଅଚଳ TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ * MPU_pvTimerGetTimerID( ଅଚଳ TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_pvTimerGetTimerIDImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_pvTimerGetTimerID_Unpriv
MPU_pvTimerGetTimerID_Priv
        b MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerID_Unpriv
        svc #SYSTEM_CALL_pvTimerGetTimerID
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TIMERS == 1 )

ଶୂନ୍ୟ MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                           ଶୂନ୍ୟ * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                 ଶୂନ୍ୟ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_vTimerSetTimerIDImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_vTimerSetTimerID_Unpriv
MPU_vTimerSetTimerID_Priv
        b MPU_vTimerSetTimerIDImpl
MPU_vTimerSetTimerID_Unpriv
        svc #SYSTEM_CALL_vTimerSetTimerID
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TIMERS == 1 )

BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTimerIsTimerActiveImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTimerIsTimerActive_Unpriv
MPU_xTimerIsTimerActive_Priv
        b MPU_xTimerIsTimerActiveImpl
MPU_xTimerIsTimerActive_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ଶୂନ୍ୟ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ଶୂନ୍ୟ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTimerGetTimerDaemonTaskHandleImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
MPU_xTimerGetTimerDaemonTaskHandle_Priv
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TIMERS == 1 )

BaseType_t MPU_xTimerGenericCommandFromTaskEntry( ଅଚଳ xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTimerGenericCommandFromTaskEntry( ଅଚଳ xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTimerGenericCommandFromTaskImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
MPU_xTimerGenericCommandFromTask_Priv
        b MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTask_Unpriv
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TIMERS == 1 )

ଅଚଳ ଅକ୍ଷର * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ଅଚଳ ଅକ୍ଷର * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_pcTimerGetNameImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_pcTimerGetName_Unpriv
MPU_pcTimerGetName_Priv
        b MPU_pcTimerGetNameImpl
MPU_pcTimerGetName_Unpriv
        svc #SYSTEM_CALL_pcTimerGetName
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TIMERS == 1 )

ଶୂନ୍ୟ MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                              ଅଚଳ BaseType_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                    ଅଚଳ BaseType_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_vTimerSetReloadModeImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_vTimerSetReloadMode_Unpriv
MPU_vTimerSetReloadMode_Priv
        b MPU_vTimerSetReloadModeImpl
MPU_vTimerSetReloadMode_Unpriv
        svc #SYSTEM_CALL_vTimerSetReloadMode
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TIMERS == 1 )

BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTimerGetReloadModeImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTimerGetReloadMode_Unpriv
MPU_xTimerGetReloadMode_Priv
        b MPU_xTimerGetReloadModeImpl
MPU_xTimerGetReloadMode_Unpriv
        svc #SYSTEM_CALL_xTimerGetReloadMode
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TIMERS == 1 )

UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_uxTimerGetReloadModeImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_uxTimerGetReloadMode_Unpriv
MPU_uxTimerGetReloadMode_Priv
        b MPU_uxTimerGetReloadModeImpl
MPU_uxTimerGetReloadMode_Unpriv
        svc #SYSTEM_CALL_uxTimerGetReloadMode
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTimerGetPeriodImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTimerGetPeriod_Unpriv
MPU_xTimerGetPeriod_Priv
        b MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriod_Unpriv
        svc #SYSTEM_CALL_xTimerGetPeriod
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xTimerGetExpiryTimeImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xTimerGetExpiryTime_Unpriv
MPU_xTimerGetExpiryTime_Priv
        b MPU_xTimerGetExpiryTimeImpl
MPU_xTimerGetExpiryTime_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupWaitBitsEntry( ଅଚଳ xEventGroupWaitBitsParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupWaitBitsEntry( ଅଚଳ xEventGroupWaitBitsParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xEventGroupWaitBitsImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xEventGroupWaitBits_Unpriv
MPU_xEventGroupWaitBits_Priv
        b MPU_xEventGroupWaitBitsImpl
MPU_xEventGroupWaitBits_Unpriv
        svc #SYSTEM_CALL_xEventGroupWaitBits
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                      ଅଚଳ EventBits_t uxBitsToClear ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                            ଅଚଳ EventBits_t uxBitsToClear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xEventGroupClearBitsImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xEventGroupClearBits_Unpriv
MPU_xEventGroupClearBits_Priv
        b MPU_xEventGroupClearBitsImpl
MPU_xEventGroupClearBits_Unpriv
        svc #SYSTEM_CALL_xEventGroupClearBits
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                    ଅଚଳ EventBits_t uxBitsToSet ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                          ଅଚଳ EventBits_t uxBitsToSet ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xEventGroupSetBitsImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xEventGroupSetBits_Unpriv
MPU_xEventGroupSetBits_Priv
        b MPU_xEventGroupSetBitsImpl
MPU_xEventGroupSetBits_Unpriv
        svc #SYSTEM_CALL_xEventGroupSetBits
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                 ଅଚଳ EventBits_t uxBitsToSet,
                                 ଅଚଳ EventBits_t uxBitsToWaitFor,
                                 TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                       ଅଚଳ EventBits_t uxBitsToSet,
                                       ଅଚଳ EventBits_t uxBitsToWaitFor,
                                       TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xEventGroupSyncImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xEventGroupSync_Unpriv
MPU_xEventGroupSync_Priv
        b MPU_xEventGroupSyncImpl
MPU_xEventGroupSync_Unpriv
        svc #SYSTEM_CALL_xEventGroupSync
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_Group_Get_ସଂଖ୍ୟା( ଶୂନ୍ୟ * xEventGroup ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_Group_Get_ସଂଖ୍ୟା( ଶୂନ୍ୟ * xEventGroup ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_ux_Event_Group_Get_ସଂଖ୍ୟା_Impl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_ux_Event_Group_Get_ସଂଖ୍ୟା_Unpriv
MPU_ux_Event_Group_Get_ସଂଖ୍ୟା_Priv
        b MPU_ux_Event_Group_Get_ସଂଖ୍ୟା_Impl
MPU_ux_Event_Group_Get_ସଂଖ୍ୟା_Unpriv
        svc #SYSTEM_CALL_uxEventGroupGetNumber
}

#endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#ଯଦି ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

ଶୂନ୍ୟ MPU_v_Event_Group_Set_ସଂଖ୍ୟା( ଶୂନ୍ୟ * xEventGroup,
                               UBaseType_t ux_Event_Group_ସଂଖ୍ୟା ) FREERTOS_SYSTEM_CALL;

__asm ଶୂନ୍ୟ MPU_v_Event_Group_Set_ସଂଖ୍ୟା( ଶୂନ୍ୟ * xEventGroup,
                                     UBaseType_t ux_Event_Group_ସଂଖ୍ୟା ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_v_Event_Group_Set_ସଂଖ୍ୟା_Impl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_v_Event_Group_Set_ସଂଖ୍ୟା_Unpriv
MPU_v_Event_Group_Set_ସଂଖ୍ୟା_Priv
        b MPU_v_Event_Group_Set_ସଂଖ୍ୟା_Impl
MPU_v_Event_Group_Set_ସଂଖ୍ୟା_Unpriv
        svc #SYSTEM_CALL_vEventGroupSetNumber
}

#endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                              ଅଚଳ ଶୂନ୍ୟ * pvTxData,
                              size_t xDataLengthBytes,
                              TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_xStreamBufferSend( StreamBufferHandle_t xStreamBuffer,
                                    ଅଚଳ ଶୂନ୍ୟ * pvTxData,
                                    size_t xDataLengthBytes,
                                    TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xStreamBufferSendImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xStreamBufferSend_Unpriv
MPU_xStreamBufferSend_Priv
        b MPU_xStreamBufferSendImpl
MPU_xStreamBufferSend_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSend
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                 ଶୂନ୍ୟ * pvRxData,
                                 size_t xBufferLengthBytes,
                                 TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_xStreamBufferReceive( StreamBufferHandle_t xStreamBuffer,
                                       ଶୂନ୍ୟ * pvRxData,
                                       size_t xBufferLengthBytes,
                                       TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xStreamBufferReceiveImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xStreamBufferReceive_Unpriv
MPU_xStreamBufferReceive_Priv
        b MPU_xStreamBufferReceiveImpl
MPU_xStreamBufferReceive_Unpriv
        svc #SYSTEM_CALL_xStreamBufferReceive
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_STREAM_BUFFERS == 1 )

BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xStreamBufferIsFull( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xStreamBufferIsFullImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xStreamBufferIsFull_Unpriv
MPU_xStreamBufferIsFull_Priv
        b MPU_xStreamBufferIsFullImpl
MPU_xStreamBufferIsFull_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_STREAM_BUFFERS == 1 )

BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xStreamBufferIsEmpty( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xStreamBufferIsEmptyImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xStreamBufferIsEmpty_Unpriv
MPU_xStreamBufferIsEmpty_Priv
        b MPU_xStreamBufferIsEmptyImpl
MPU_xStreamBufferIsEmpty_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_xStreamBufferSpacesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xStreamBufferSpacesAvailableImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xStreamBufferSpacesAvailable_Unpriv
MPU_xStreamBufferSpacesAvailable_Priv
        b MPU_xStreamBufferSpacesAvailableImpl
MPU_xStreamBufferSpacesAvailable_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_xStreamBufferBytesAvailable( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xStreamBufferBytesAvailableImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xStreamBufferBytesAvailable_Unpriv
MPU_xStreamBufferBytesAvailable_Priv
        b MPU_xStreamBufferBytesAvailableImpl
MPU_xStreamBufferBytesAvailable_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_STREAM_BUFFERS == 1 )

BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xStreamBufferSetTriggerLevel( StreamBufferHandle_t xStreamBuffer,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xStreamBufferSetTriggerLevelImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xStreamBufferSetTriggerLevel_Unpriv
MPU_xStreamBufferSetTriggerLevel_Priv
        b MPU_xStreamBufferSetTriggerLevelImpl
MPU_xStreamBufferSetTriggerLevel_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ଯଦି ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_xStreamBufferNextMessageLengthBytes( StreamBufferHandle_t xStreamBuffer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ବାହ୍ୟ MPU_xStreamBufferNextMessageLengthBytesImpl

    ଠେଲ {r0}
    mrs r0, control
    tst r0, #1
    କାଢ଼ {r0}
    bne MPU_xStreamBufferNextMessageLengthBytes_Unpriv
MPU_xStreamBufferNextMessageLengthBytes_Priv
        b MPU_xStreamBufferNextMessageLengthBytesImpl
MPU_xStreamBufferNextMessageLengthBytes_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#endif /* configUSE_MPU_WRAPPERS_V1 == 0 */
