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
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"
#অন্তর্ভাব "queue.h"
#অন্তর্ভাব "timers.h"
#অন্তর্ভাব "event_groups.h"
#অন্তর্ভাব "stream_buffer.h"
#অন্তর্ভাব "mpu_prototypes.h"
#অন্তর্ভাব "mpu_syscall_numbers.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#যদি ( configUSE_MPU_WRAPPERS_V1 == 0 )

#যদি ( INCLUDE_xTaskDelayUntil == 1 )

BaseType_t MPU_xTaskDelayUntil( TickType_t * ধ্রুবক pxPreviousWakeTime,
                                ধ্রুবক TickType_t xTimeIncrement ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskDelayUntil( TickType_t * ধ্রুবক pxPreviousWakeTime,
                                      ধ্রুবক TickType_t xTimeIncrement ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTaskDelayUntilImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTaskDelayUntil_Unpriv
MPU_xTaskDelayUntil_Priv
        b MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntil_Unpriv
        svc #SYSTEM_CALL_xTaskDelayUntil
}

#endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( INCLUDE_xTaskAbortDelay == 1 )

BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTaskAbortDelayImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTaskAbortDelay_Unpriv
MPU_xTaskAbortDelay_Priv
        b MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelay_Unpriv
        svc #SYSTEM_CALL_xTaskAbortDelay
}

#endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( INCLUDE_vTaskDelay == 1 )

শূন্য MPU_vTaskDelay( ধ্রুবক TickType_t xTicksToDelay ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_vTaskDelay( ধ্রুবক TickType_t xTicksToDelay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_vTaskDelayImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_vTaskDelay_Unpriv
MPU_vTaskDelay_Priv
        b MPU_vTaskDelayImpl
MPU_vTaskDelay_Unpriv
        svc #SYSTEM_CALL_vTaskDelay
}

#endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( INCLUDE_uxTaskPriorityGet == 1 )

UBaseType_t MPU_uxTaskPriorityGet( ধ্রুবক TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskPriorityGet( ধ্রুবক TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_uxTaskPriorityGetImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_uxTaskPriorityGet_Unpriv
MPU_uxTaskPriorityGet_Priv
        b MPU_uxTaskPriorityGetImpl
MPU_uxTaskPriorityGet_Unpriv
        svc #SYSTEM_CALL_uxTaskPriorityGet
}

#endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_eTaskGetStateImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_eTaskGetState_Unpriv
MPU_eTaskGetState_Priv
        b MPU_eTaskGetStateImpl
MPU_eTaskGetState_Unpriv
        svc #SYSTEM_CALL_eTaskGetState
}

#endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TRACE_FACILITY == 1 )

শূন্য MPU_vTaskGetInfo( TaskHandle_t xTask,
                       TaskStatus_t * pxTaskStatus,
                       BaseType_t x_Get_Free_স্তূপ_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_vTaskGetInfo( TaskHandle_t xTask,
                             TaskStatus_t * pxTaskStatus,
                             BaseType_t x_Get_Free_স্তূপ_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_vTaskGetInfoImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_vTaskGetInfo_Unpriv
MPU_vTaskGetInfo_Priv
        b MPU_vTaskGetInfoImpl
MPU_vTaskGetInfo_Unpriv
        svc #SYSTEM_CALL_vTaskGetInfo
}

#endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( শূন্য ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( শূন্য ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTaskGetIdleTaskHandleImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
MPU_xTaskGetIdleTaskHandle_Priv
        b MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
}

#endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( INCLUDE_vTaskSuspend == 1 )

শূন্য MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_vTaskSuspend( TaskHandle_t xTaskToSuspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_vTaskSuspendImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_vTaskSuspend_Unpriv
MPU_vTaskSuspend_Priv
        b MPU_vTaskSuspendImpl
MPU_vTaskSuspend_Unpriv
        svc #SYSTEM_CALL_vTaskSuspend
}

#endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( INCLUDE_vTaskSuspend == 1 )

শূন্য MPU_vTaskResume( TaskHandle_t xTaskToResume ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_vTaskResume( TaskHandle_t xTaskToResume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_vTaskResumeImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_vTaskResume_Unpriv
MPU_vTaskResume_Priv
        b MPU_vTaskResumeImpl
MPU_vTaskResume_Unpriv
        svc #SYSTEM_CALL_vTaskResume
}

#endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_গুনতি( শূন্য ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_গুনতি( শূন্য ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_x_Task_Get_Tick_গুনতি_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_x_Task_Get_Tick_গুনতি_Unpriv
MPU_x_Task_Get_Tick_গুনতি_Priv
        b MPU_x_Task_Get_Tick_গুনতি_Impl
MPU_x_Task_Get_Tick_গুনতি_Unpriv
        svc #SYSTEM_CALL_xTaskGetTickCount
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Task_Get_সংখ্যা_Of_Tasks( শূন্য ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_সংখ্যা_Of_Tasks( শূন্য ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_ux_Task_Get_সংখ্যা_Of_Tasks_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_ux_Task_Get_সংখ্যা_Of_Tasks_Unpriv
MPU_ux_Task_Get_সংখ্যা_Of_Tasks_Priv
        b MPU_ux_Task_Get_সংখ্যা_Of_Tasks_Impl
MPU_ux_Task_Get_সংখ্যা_Of_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#যদি ( configGENERATE_RUN_TIME_STATS == 1 )

config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Run_Time_গণক( ধ্রুবক TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Run_Time_গণক( ধ্রুবক TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_ul_Task_Get_Run_Time_গণক_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_ul_Task_Get_Run_Time_গণক_Unpriv
MPU_ul_Task_Get_Run_Time_গণক_Priv
        b MPU_ul_Task_Get_Run_Time_গণক_Impl
MPU_ul_Task_Get_Run_Time_গণক_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configGENERATE_RUN_TIME_STATS == 1 )

config_RUN_TIME_গণক_TYPE MPU_ulTaskGetRunTimePercent( ধ্রুবক TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_RUN_TIME_গণক_TYPE MPU_ulTaskGetRunTimePercent( ধ্রুবক TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_ulTaskGetRunTimePercentImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_ulTaskGetRunTimePercent_Unpriv
MPU_ulTaskGetRunTimePercent_Priv
        b MPU_ulTaskGetRunTimePercentImpl
MPU_ulTaskGetRunTimePercent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_RUN_TIME_গণক_TYPE MPU_ulTaskGetIdleRunTimePercent( শূন্য ) FREERTOS_SYSTEM_CALL;

__asm config_RUN_TIME_গণক_TYPE MPU_ulTaskGetIdleRunTimePercent( শূন্য ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_ulTaskGetIdleRunTimePercentImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_ulTaskGetIdleRunTimePercent_Unpriv
MPU_ulTaskGetIdleRunTimePercent_Priv
        b MPU_ulTaskGetIdleRunTimePercentImpl
MPU_ulTaskGetIdleRunTimePercent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#যদি ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Idle_Run_Time_গণক( শূন্য ) FREERTOS_SYSTEM_CALL;

__asm config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Idle_Run_Time_গণক( শূন্য ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_ul_Task_Get_Idle_Run_Time_গণক_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_ul_Task_Get_Idle_Run_Time_গণক_Unpriv
MPU_ul_Task_Get_Idle_Run_Time_গণক_Priv
        b MPU_ul_Task_Get_Idle_Run_Time_গণক_Impl
MPU_ul_Task_Get_Idle_Run_Time_গণক_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_APPLICATION_TASK_TAG == 1 )

শূন্য MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_vTaskSetApplicationTaskTag( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_vTaskSetApplicationTaskTagImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_vTaskSetApplicationTaskTag_Unpriv
MPU_vTaskSetApplicationTaskTag_Priv
        b MPU_vTaskSetApplicationTaskTagImpl
MPU_vTaskSetApplicationTaskTag_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_APPLICATION_TASK_TAG == 1 )

TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_xTaskGetApplicationTaskTag( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTaskGetApplicationTaskTagImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTaskGetApplicationTaskTag_Unpriv
MPU_xTaskGetApplicationTaskTag_Priv
        b MPU_xTaskGetApplicationTaskTagImpl
MPU_xTaskGetApplicationTaskTag_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( config_অঙ্ক_THREAD_LOCAL_STORAGE_POINTERS != 0 )

শূন্য MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                            BaseType_t x_সূচক,
                                            শূন্য * pv_মান ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_vTaskSetThreadLocalStoragePointer( TaskHandle_t xTaskToSet,
                                                  BaseType_t x_সূচক,
                                                  শূন্য * pv_মান ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_vTaskSetThreadLocalStoragePointerImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_vTaskSetThreadLocalStoragePointer_Unpriv
MPU_vTaskSetThreadLocalStoragePointer_Priv
        b MPU_vTaskSetThreadLocalStoragePointerImpl
MPU_vTaskSetThreadLocalStoragePointer_Unpriv
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
}

#endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#যদি ( config_অঙ্ক_THREAD_LOCAL_STORAGE_POINTERS != 0 )

শূন্য * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                               BaseType_t x_সূচক ) FREERTOS_SYSTEM_CALL;

__asm শূন্য * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t xTaskToQuery,
                                                     BaseType_t x_সূচক ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_pvTaskGetThreadLocalStoragePointerImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_pvTaskGetThreadLocalStoragePointer_Unpriv
MPU_pvTaskGetThreadLocalStoragePointer_Priv
        b MPU_pvTaskGetThreadLocalStoragePointerImpl
MPU_pvTaskGetThreadLocalStoragePointer_Unpriv
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
}

#endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * ধ্রুবক pxTaskStatusArray,
                                      ধ্রুবক UBaseType_t ux_Array_আকার,
                                      config_RUN_TIME_গণক_TYPE * ধ্রুবক pul_যোগ_Run_Time ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( TaskStatus_t * ধ্রুবক pxTaskStatusArray,
                                            ধ্রুবক UBaseType_t ux_Array_আকার,
                                            config_RUN_TIME_গণক_TYPE * ধ্রুবক pul_যোগ_Run_Time ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_uxTaskGetSystemStateImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_uxTaskGetSystemState_Unpriv
MPU_uxTaskGetSystemState_Priv
        b MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemState_Unpriv
        svc #SYSTEM_CALL_uxTaskGetSystemState
}

#endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( INCLUDE_ux_Task_Get_স্তূপ_উপরের_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark_Unpriv
MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark_Priv
        b MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark_Impl
MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
}

#endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( INCLUDE_ux_Task_Get_স্তূপ_উপরের_Water_Mark2 == 1 )

config_স্তূপ_DEPTH_TYPE MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_স্তূপ_DEPTH_TYPE MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2_Unpriv
MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2_Priv
        b MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2_Impl
MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
}

#endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( শূন্য ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( শূন্য ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTaskGetCurrentTaskHandleImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
MPU_xTaskGetCurrentTaskHandle_Priv
        b MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
}

#endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#যদি ( INCLUDE_xTaskGetSchedulerState == 1 )

BaseType_t MPU_xTaskGetSchedulerState( শূন্য ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGetSchedulerState( শূন্য ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTaskGetSchedulerStateImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTaskGetSchedulerState_Unpriv
MPU_xTaskGetSchedulerState_Priv
        b MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerState_Unpriv
        svc #SYSTEM_CALL_xTaskGetSchedulerState
}

#endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

শূন্য MPU_vTaskSetTimeOutState( TimeOut_t * ধ্রুবক pxTimeOut ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_vTaskSetTimeOutState( TimeOut_t * ধ্রুবক pxTimeOut ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_vTaskSetTimeOutStateImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_vTaskSetTimeOutState_Unpriv
MPU_vTaskSetTimeOutState_Priv
        b MPU_vTaskSetTimeOutStateImpl
MPU_vTaskSetTimeOutState_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * ধ্রুবক pxTimeOut,
                                     TickType_t * ধ্রুবক pxTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskCheckForTimeOut( TimeOut_t * ধ্রুবক pxTimeOut,
                                     TickType_t * ধ্রুবক pxTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTaskCheckForTimeOutImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTaskCheckForTimeOut_Unpriv
MPU_xTaskCheckForTimeOut_Priv
        b MPU_xTaskCheckForTimeOutImpl
MPU_xTaskCheckForTimeOut_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

BaseType_t MPU_xTaskGenericNotifyEntry( ধ্রুবক xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGenericNotifyEntry( ধ্রুবক xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTaskGenericNotifyImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTaskGenericNotify_Unpriv
MPU_xTaskGenericNotify_Priv
        b MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotify_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotify
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

BaseType_t MPU_xTaskGenericNotifyWaitEntry( ধ্রুবক xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGenericNotifyWaitEntry( ধ্রুবক xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTaskGenericNotifyWaitImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTaskGenericNotifyWait_Unpriv
MPU_xTaskGenericNotifyWait_Priv
        b MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWait_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_সূচক_To_Wait_On,
                                      BaseType_t x_Clear_গুনতি_On_Exit,
                                      TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_সূচক_To_Wait_On,
                                            BaseType_t x_Clear_গুনতি_On_Exit,
                                            TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_ulTaskGenericNotifyTakeImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
MPU_ulTaskGenericNotifyTake_Priv
        b MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTake_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t ux_সূচক_To_Clear ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t ux_সূচক_To_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTaskGenericNotifyStateClearImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
MPU_xTaskGenericNotifyStateClear_Priv
        b MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClear_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_মান_Clear( TaskHandle_t xTask,
                                            UBaseType_t ux_সূচক_To_Clear,
                                            uint32_t ulBitsToClear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_মান_Clear( TaskHandle_t xTask,
                                                  UBaseType_t ux_সূচক_To_Clear,
                                                  uint32_t ulBitsToClear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_ul_Task_Generic_Notify_মান_Clear_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_ul_Task_Generic_Notify_মান_Clear_Unpriv
MPU_ul_Task_Generic_Notify_মান_Clear_Priv
        b MPU_ul_Task_Generic_Notify_মান_Clear_Impl
MPU_ul_Task_Generic_Notify_মান_Clear_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
}

#endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                  ধ্রুবক শূন্য * ধ্রুবক pvItemToQueue,
                                  TickType_t xTicksToWait,
                                  ধ্রুবক BaseType_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                        ধ্রুবক শূন্য * ধ্রুবক pvItemToQueue,
                                        TickType_t xTicksToWait,
                                        ধ্রুবক BaseType_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xQueueGenericSendImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xQueueGenericSend_Unpriv
MPU_xQueueGenericSend_Priv
        b MPU_xQueueGenericSendImpl
MPU_xQueueGenericSend_Unpriv
        svc #SYSTEM_CALL_xQueueGenericSend
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_uxQueueMessagesWaiting( ধ্রুবক QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxQueueMessagesWaiting( ধ্রুবক QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_uxQueueMessagesWaitingImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_uxQueueMessagesWaiting_Unpriv
MPU_uxQueueMessagesWaiting_Priv
        b MPU_uxQueueMessagesWaitingImpl
MPU_uxQueueMessagesWaiting_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_uxQueueSpacesAvailable( ধ্রুবক QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxQueueSpacesAvailable( ধ্রুবক QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_uxQueueSpacesAvailableImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_uxQueueSpacesAvailable_Unpriv
MPU_uxQueueSpacesAvailable_Priv
        b MPU_uxQueueSpacesAvailableImpl
MPU_uxQueueSpacesAvailable_Unpriv
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
}
/*-----------------------------------------------------------*/

BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                              শূন্য * ধ্রুবক pv_বাফার,
                              TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                    শূন্য * ধ্রুবক pv_বাফার,
                                    TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xQueueReceiveImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xQueueReceive_Unpriv
MPU_xQueueReceive_Priv
        b MPU_xQueueReceiveImpl
MPU_xQueueReceive_Unpriv
        svc #SYSTEM_CALL_xQueueReceive
}
/*-----------------------------------------------------------*/

BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                           শূন্য * ধ্রুবক pv_বাফার,
                           TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueuePeek( QueueHandle_t xQueue,
                                 শূন্য * ধ্রুবক pv_বাফার,
                                 TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xQueuePeekImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
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
    বাহ্যিক MPU_xQueueSemaphoreTakeImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xQueueSemaphoreTake_Unpriv
MPU_xQueueSemaphoreTake_Priv
        b MPU_xQueueSemaphoreTakeImpl
MPU_xQueueSemaphoreTake_Unpriv
        svc #SYSTEM_CALL_xQueueSemaphoreTake
}
/*-----------------------------------------------------------*/

#যদি ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xQueueGetMutexHolderImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xQueueGetMutexHolder_Unpriv
MPU_xQueueGetMutexHolder_Priv
        b MPU_xQueueGetMutexHolderImpl
MPU_xQueueGetMutexHolder_Unpriv
        svc #SYSTEM_CALL_xQueueGetMutexHolder
}

#endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_RECURSIVE_MUTEXES == 1 )

BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                         TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                               TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xQueueTakeMutexRecursiveImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xQueueTakeMutexRecursive_Unpriv
MPU_xQueueTakeMutexRecursive_Priv
        b MPU_xQueueTakeMutexRecursiveImpl
MPU_xQueueTakeMutexRecursive_Unpriv
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
}

#endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_RECURSIVE_MUTEXES == 1 )

BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xQueueGiveMutexRecursiveImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xQueueGiveMutexRecursive_Unpriv
MPU_xQueueGiveMutexRecursive_Priv
        b MPU_xQueueGiveMutexRecursiveImpl
MPU_xQueueGiveMutexRecursive_Unpriv
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
}

#endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_QUEUE_SETS == 1 )

QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                ধ্রুবক TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm QueueSetMemberHandle_t MPU_xQueueSelectFromSet( QueueSetHandle_t xQueueSet,
                                                      ধ্রুবক TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xQueueSelectFromSetImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xQueueSelectFromSet_Unpriv
MPU_xQueueSelectFromSet_Priv
        b MPU_xQueueSelectFromSetImpl
MPU_xQueueSelectFromSet_Unpriv
        svc #SYSTEM_CALL_xQueueSelectFromSet
}

#endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_QUEUE_SETS == 1 )

BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                               QueueSetHandle_t xQueueSet ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xQueueAddToSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                     QueueSetHandle_t xQueueSet ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xQueueAddToSetImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xQueueAddToSet_Unpriv
MPU_xQueueAddToSet_Priv
        b MPU_xQueueAddToSetImpl
MPU_xQueueAddToSet_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( config_QUEUE_REGISTRY_আকার > 0 )

শূন্য MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                              ধ্রুবক অক্ষর * pcName ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_vQueueAddToRegistry( QueueHandle_t xQueue,
                                    ধ্রুবক অক্ষর * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_vQueueAddToRegistryImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_vQueueAddToRegistry_Unpriv
MPU_vQueueAddToRegistry_Priv
        b MPU_vQueueAddToRegistryImpl
MPU_vQueueAddToRegistry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#যদি ( config_QUEUE_REGISTRY_আকার > 0 )

শূন্য MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_vQueueUnregisterQueueImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_vQueueUnregisterQueue_Unpriv
MPU_vQueueUnregisterQueue_Priv
        b MPU_vQueueUnregisterQueueImpl
MPU_vQueueUnregisterQueue_Unpriv
        svc #SYSTEM_CALL_vQueueUnregisterQueue
}

#endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#যদি ( config_QUEUE_REGISTRY_আকার > 0 )

ধ্রুবক অক্ষর * MPU_pcQueueGetName( QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm ধ্রুবক অক্ষর * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_pcQueueGetNameImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_pcQueueGetName_Unpriv
MPU_pcQueueGetName_Priv
        b MPU_pcQueueGetNameImpl
MPU_pcQueueGetName_Unpriv
        svc #SYSTEM_CALL_pcQueueGetName
}

#endif /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TIMERS == 1 )

শূন্য * MPU_pvTimerGetTimerID( ধ্রুবক TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm শূন্য * MPU_pvTimerGetTimerID( ধ্রুবক TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_pvTimerGetTimerIDImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_pvTimerGetTimerID_Unpriv
MPU_pvTimerGetTimerID_Priv
        b MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerID_Unpriv
        svc #SYSTEM_CALL_pvTimerGetTimerID
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TIMERS == 1 )

শূন্য MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                           শূন্য * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_vTimerSetTimerID( TimerHandle_t xTimer,
                                 শূন্য * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_vTimerSetTimerIDImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_vTimerSetTimerID_Unpriv
MPU_vTimerSetTimerID_Priv
        b MPU_vTimerSetTimerIDImpl
MPU_vTimerSetTimerID_Unpriv
        svc #SYSTEM_CALL_vTimerSetTimerID
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TIMERS == 1 )

BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTimerIsTimerActive( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTimerIsTimerActiveImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTimerIsTimerActive_Unpriv
MPU_xTimerIsTimerActive_Priv
        b MPU_xTimerIsTimerActiveImpl
MPU_xTimerIsTimerActive_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( শূন্য ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( শূন্য ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTimerGetTimerDaemonTaskHandleImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
MPU_xTimerGetTimerDaemonTaskHandle_Priv
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TIMERS == 1 )

BaseType_t MPU_xTimerGenericCommandFromTaskEntry( ধ্রুবক xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTimerGenericCommandFromTaskEntry( ধ্রুবক xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTimerGenericCommandFromTaskImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
MPU_xTimerGenericCommandFromTask_Priv
        b MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTask_Unpriv
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TIMERS == 1 )

ধ্রুবক অক্ষর * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ধ্রুবক অক্ষর * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_pcTimerGetNameImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_pcTimerGetName_Unpriv
MPU_pcTimerGetName_Priv
        b MPU_pcTimerGetNameImpl
MPU_pcTimerGetName_Unpriv
        svc #SYSTEM_CALL_pcTimerGetName
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TIMERS == 1 )

শূন্য MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                              ধ্রুবক BaseType_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_vTimerSetReloadMode( TimerHandle_t xTimer,
                                    ধ্রুবক BaseType_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_vTimerSetReloadModeImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_vTimerSetReloadMode_Unpriv
MPU_vTimerSetReloadMode_Priv
        b MPU_vTimerSetReloadModeImpl
MPU_vTimerSetReloadMode_Unpriv
        svc #SYSTEM_CALL_vTimerSetReloadMode
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TIMERS == 1 )

BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_xTimerGetReloadMode( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTimerGetReloadModeImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTimerGetReloadMode_Unpriv
MPU_xTimerGetReloadMode_Priv
        b MPU_xTimerGetReloadModeImpl
MPU_xTimerGetReloadMode_Unpriv
        svc #SYSTEM_CALL_xTimerGetReloadMode
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TIMERS == 1 )

UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTimerGetReloadMode( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_uxTimerGetReloadModeImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_uxTimerGetReloadMode_Unpriv
MPU_uxTimerGetReloadMode_Priv
        b MPU_uxTimerGetReloadModeImpl
MPU_uxTimerGetReloadMode_Unpriv
        svc #SYSTEM_CALL_uxTimerGetReloadMode
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTimerGetPeriodImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTimerGetPeriod_Unpriv
MPU_xTimerGetPeriod_Priv
        b MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriod_Unpriv
        svc #SYSTEM_CALL_xTimerGetPeriod
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xTimerGetExpiryTimeImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xTimerGetExpiryTime_Unpriv
MPU_xTimerGetExpiryTime_Priv
        b MPU_xTimerGetExpiryTimeImpl
MPU_xTimerGetExpiryTime_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupWaitBitsEntry( ধ্রুবক xEventGroupWaitBitsParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupWaitBitsEntry( ধ্রুবক xEventGroupWaitBitsParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xEventGroupWaitBitsImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xEventGroupWaitBits_Unpriv
MPU_xEventGroupWaitBits_Priv
        b MPU_xEventGroupWaitBitsImpl
MPU_xEventGroupWaitBits_Unpriv
        svc #SYSTEM_CALL_xEventGroupWaitBits
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                      ধ্রুবক EventBits_t uxBitsToClear ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupClearBits( EventGroupHandle_t xEventGroup,
                                            ধ্রুবক EventBits_t uxBitsToClear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xEventGroupClearBitsImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xEventGroupClearBits_Unpriv
MPU_xEventGroupClearBits_Priv
        b MPU_xEventGroupClearBitsImpl
MPU_xEventGroupClearBits_Unpriv
        svc #SYSTEM_CALL_xEventGroupClearBits
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                    ধ্রুবক EventBits_t uxBitsToSet ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupSetBits( EventGroupHandle_t xEventGroup,
                                          ধ্রুবক EventBits_t uxBitsToSet ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xEventGroupSetBitsImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xEventGroupSetBits_Unpriv
MPU_xEventGroupSetBits_Priv
        b MPU_xEventGroupSetBitsImpl
MPU_xEventGroupSetBits_Unpriv
        svc #SYSTEM_CALL_xEventGroupSetBits
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_EVENT_GROUPS == 1 )

EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                 ধ্রুবক EventBits_t uxBitsToSet,
                                 ধ্রুবক EventBits_t uxBitsToWaitFor,
                                 TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm EventBits_t MPU_xEventGroupSync( EventGroupHandle_t xEventGroup,
                                       ধ্রুবক EventBits_t uxBitsToSet,
                                       ধ্রুবক EventBits_t uxBitsToWaitFor,
                                       TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_xEventGroupSyncImpl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_xEventGroupSync_Unpriv
MPU_xEventGroupSync_Priv
        b MPU_xEventGroupSyncImpl
MPU_xEventGroupSync_Unpriv
        svc #SYSTEM_CALL_xEventGroupSync
}

#endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_Group_Get_সংখ্যা( শূন্য * xEventGroup ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_Group_Get_সংখ্যা( শূন্য * xEventGroup ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_ux_Event_Group_Get_সংখ্যা_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_ux_Event_Group_Get_সংখ্যা_Unpriv
MPU_ux_Event_Group_Get_সংখ্যা_Priv
        b MPU_ux_Event_Group_Get_সংখ্যা_Impl
MPU_ux_Event_Group_Get_সংখ্যা_Unpriv
        svc #SYSTEM_CALL_uxEventGroupGetNumber
}

#endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#যদি ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

শূন্য MPU_v_Event_Group_Set_সংখ্যা( শূন্য * xEventGroup,
                               UBaseType_t ux_Event_Group_সংখ্যা ) FREERTOS_SYSTEM_CALL;

__asm শূন্য MPU_v_Event_Group_Set_সংখ্যা( শূন্য * xEventGroup,
                                     UBaseType_t ux_Event_Group_সংখ্যা ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_v_Event_Group_Set_সংখ্যা_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_v_Event_Group_Set_সংখ্যা_Unpriv
MPU_v_Event_Group_Set_সংখ্যা_Priv
        b MPU_v_Event_Group_Set_সংখ্যা_Impl
MPU_v_Event_Group_Set_সংখ্যা_Unpriv
        svc #SYSTEM_CALL_vEventGroupSetNumber
}

#endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_x_Stream_বাফার_Send( Stream_বাফার_Handle_t x_Stream_বাফার,
                              ধ্রুবক শূন্য * pv_Tx_তথ্য,
                              size_t x_তথ্য_দৈর্ঘ্য_Bytes,
                              TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_Stream_বাফার_Send( Stream_বাফার_Handle_t x_Stream_বাফার,
                                    ধ্রুবক শূন্য * pv_Tx_তথ্য,
                                    size_t x_তথ্য_দৈর্ঘ্য_Bytes,
                                    TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_x_Stream_বাফার_Send_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_x_Stream_বাফার_Send_Unpriv
MPU_x_Stream_বাফার_Send_Priv
        b MPU_x_Stream_বাফার_Send_Impl
MPU_x_Stream_বাফার_Send_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSend
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_x_Stream_বাফার_Receive( Stream_বাফার_Handle_t x_Stream_বাফার,
                                 শূন্য * pv_Rx_তথ্য,
                                 size_t x_বাফার_দৈর্ঘ্য_Bytes,
                                 TickType_t xTicksToWait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_Stream_বাফার_Receive( Stream_বাফার_Handle_t x_Stream_বাফার,
                                       শূন্য * pv_Rx_তথ্য,
                                       size_t x_বাফার_দৈর্ঘ্য_Bytes,
                                       TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_x_Stream_বাফার_Receive_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_x_Stream_বাফার_Receive_Unpriv
MPU_x_Stream_বাফার_Receive_Priv
        b MPU_x_Stream_বাফার_Receive_Impl
MPU_x_Stream_বাফার_Receive_Unpriv
        svc #SYSTEM_CALL_xStreamBufferReceive
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_STREAM_BUFFERS == 1 )

BaseType_t MPU_x_Stream_বাফার_Is_Full( Stream_বাফার_Handle_t x_Stream_বাফার ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_x_Stream_বাফার_Is_Full( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_x_Stream_বাফার_Is_Full_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_x_Stream_বাফার_Is_Full_Unpriv
MPU_x_Stream_বাফার_Is_Full_Priv
        b MPU_x_Stream_বাফার_Is_Full_Impl
MPU_x_Stream_বাফার_Is_Full_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_STREAM_BUFFERS == 1 )

BaseType_t MPU_x_Stream_বাফার_Is_Empty( Stream_বাফার_Handle_t x_Stream_বাফার ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_x_Stream_বাফার_Is_Empty( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_x_Stream_বাফার_Is_Empty_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_x_Stream_বাফার_Is_Empty_Unpriv
MPU_x_Stream_বাফার_Is_Empty_Priv
        b MPU_x_Stream_বাফার_Is_Empty_Impl
MPU_x_Stream_বাফার_Is_Empty_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_x_Stream_বাফার_Spaces_Available( Stream_বাফার_Handle_t x_Stream_বাফার ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_Stream_বাফার_Spaces_Available( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_x_Stream_বাফার_Spaces_Available_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_x_Stream_বাফার_Spaces_Available_Unpriv
MPU_x_Stream_বাফার_Spaces_Available_Priv
        b MPU_x_Stream_বাফার_Spaces_Available_Impl
MPU_x_Stream_বাফার_Spaces_Available_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_x_Stream_বাফার_Bytes_Available( Stream_বাফার_Handle_t x_Stream_বাফার ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_Stream_বাফার_Bytes_Available( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_x_Stream_বাফার_Bytes_Available_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_x_Stream_বাফার_Bytes_Available_Unpriv
MPU_x_Stream_বাফার_Bytes_Available_Priv
        b MPU_x_Stream_বাফার_Bytes_Available_Impl
MPU_x_Stream_বাফার_Bytes_Available_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_STREAM_BUFFERS == 1 )

BaseType_t MPU_x_Stream_বাফার_Set_Trigger_Level( Stream_বাফার_Handle_t x_Stream_বাফার,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm BaseType_t MPU_x_Stream_বাফার_Set_Trigger_Level( Stream_বাফার_Handle_t x_Stream_বাফার,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_x_Stream_বাফার_Set_Trigger_Level_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_x_Stream_বাফার_Set_Trigger_Level_Unpriv
MPU_x_Stream_বাফার_Set_Trigger_Level_Priv
        b MPU_x_Stream_বাফার_Set_Trigger_Level_Impl
MPU_x_Stream_বাফার_Set_Trigger_Level_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#যদি ( configUSE_STREAM_BUFFERS == 1 )

size_t MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes( Stream_বাফার_Handle_t x_Stream_বাফার ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes( Stream_বাফার_Handle_t x_Stream_বাফার ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    বাহ্যিক MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes_Impl

    ঠেলো {r0}
    mrs r0, control
    tst r0, #1
    বের_করো {r0}
    bne MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes_Unpriv
MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes_Priv
        b MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes_Impl
MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#endif /* configUSE_MPU_WRAPPERS_V1 == 0 */
