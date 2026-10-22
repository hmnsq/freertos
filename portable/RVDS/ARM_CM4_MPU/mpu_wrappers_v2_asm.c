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
#وصف_ڪريو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"
#ضمن "mpu_syscall_numbers.h"

#وصف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

#إذا ( INCLUDE_xTaskDelayUntil == 1 )

بنياد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_اڳيون_Wake_وقت,
                                ثابت TickType_t x_وقت_Increment ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_اڳيون_Wake_وقت,
                                      ثابت TickType_t x_وقت_Increment ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskDelayUntilImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_xTaskDelayUntil_Unpriv
MPU_xTaskDelayUntil_Priv
        b MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntil_Unpriv
        svc #SYSTEM_CALL_xTaskDelayUntil
}

#جيڪڏهن_پورو /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskAbortDelay == 1 )

بنياد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskAbortDelayImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_xTaskAbortDelay_Unpriv
MPU_xTaskAbortDelay_Priv
        b MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelay_Unpriv
        svc #SYSTEM_CALL_xTaskAbortDelay
}

#جيڪڏهن_پورو /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskDelay == 1 )

فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskDelayImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_vTaskDelay_Unpriv
MPU_vTaskDelay_Priv
        b MPU_vTaskDelayImpl
MPU_vTaskDelay_Unpriv
        svc #SYSTEM_CALL_vTaskDelay
}

#جيڪڏهن_پورو /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_ترجيح_Get == 1 )

UBaseType_t MPU_ux_Task_ترجيح_Get( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_ترجيح_Get( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_ترجيح_Get_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ux_Task_ترجيح_Get_Unpriv
MPU_ux_Task_ترجيح_Get_Priv
        b MPU_ux_Task_ترجيح_Get_Impl
MPU_ux_Task_ترجيح_Get_Unpriv
        svc #SYSTEM_CALL_uxTaskPriorityGet
}

#جيڪڏهن_پورو /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_eTaskGetStateImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_eTaskGetState_Unpriv
MPU_eTaskGetState_Priv
        b MPU_eTaskGetStateImpl
MPU_eTaskGetState_Unpriv
        svc #SYSTEM_CALL_eTaskGetState
}

#جيڪڏهن_پورو /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TRACE_FACILITY == 1 )

فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                       Task_حالت_t * px_Task_حالت,
                       بنياد_Type_t x_Get_Free_ڍير_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                             Task_حالت_t * px_Task_حالت,
                             بنياد_Type_t x_Get_Free_ڍير_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskGetInfoImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_vTaskGetInfo_Unpriv
MPU_vTaskGetInfo_Priv
        b MPU_vTaskGetInfoImpl
MPU_vTaskGetInfo_Unpriv
        svc #SYSTEM_CALL_vTaskGetInfo
}

#جيڪڏهن_پورو /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetIdleTaskHandleImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
MPU_xTaskGetIdleTaskHandle_Priv
        b MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
}

#جيڪڏهن_پورو /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskSuspend == 1 )

فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_منزل_Suspend ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_منزل_Suspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskSuspendImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_vTaskSuspend_Unpriv
MPU_vTaskSuspend_Priv
        b MPU_vTaskSuspendImpl
MPU_vTaskSuspend_Unpriv
        svc #SYSTEM_CALL_vTaskSuspend
}

#جيڪڏهن_پورو /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskSuspend == 1 )

فراغ MPU_vTaskResume( TaskHandle_t x_Task_منزل_Resume ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskResume( TaskHandle_t x_Task_منزل_Resume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskResumeImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_vTaskResume_Unpriv
MPU_vTaskResume_Priv
        b MPU_vTaskResumeImpl
MPU_vTaskResume_Unpriv
        svc #SYSTEM_CALL_vTaskResume
}

#جيڪڏهن_پورو /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_ڳڻپ( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_ڳڻپ( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Get_Tick_ڳڻپ_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_Task_Get_Tick_ڳڻپ_Unpriv
MPU_x_Task_Get_Tick_ڳڻپ_Priv
        b MPU_x_Task_Get_Tick_ڳڻپ_Impl
MPU_x_Task_Get_Tick_ڳڻپ_Unpriv
        svc #SYSTEM_CALL_xTaskGetTickCount
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Task_Get_عدد_جو_Tasks( فراغ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_عدد_جو_Tasks( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_عدد_جو_Tasks_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ux_Task_Get_عدد_جو_Tasks_Unpriv
MPU_ux_Task_Get_عدد_جو_Tasks_Priv
        b MPU_ux_Task_Get_عدد_جو_Tasks_Impl
MPU_ux_Task_Get_عدد_جو_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#إذا ( config_GENERATE_لاڳيتو_وقت_STATS == 1 )

config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Counter( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Counter( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_لاڳيتو_وقت_Counter_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ul_Task_Get_لاڳيتو_وقت_Counter_Unpriv
MPU_ul_Task_Get_لاڳيتو_وقت_Counter_Priv
        b MPU_ul_Task_Get_لاڳيتو_وقت_Counter_Impl
MPU_ul_Task_Get_لاڳيتو_وقت_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_GENERATE_لاڳيتو_وقت_STATS == 1 )

config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Percent( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Percent( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_لاڳيتو_وقت_Percent_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ul_Task_Get_لاڳيتو_وقت_Percent_Unpriv
MPU_ul_Task_Get_لاڳيتو_وقت_Percent_Priv
        b MPU_ul_Task_Get_لاڳيتو_وقت_Percent_Impl
MPU_ul_Task_Get_لاڳيتو_وقت_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( config_GENERATE_لاڳيتو_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent( فراغ ) FREERTOS_SYSTEM_CALL;

__asm config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent_Unpriv
MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent_Priv
        b MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent_Impl
MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( config_GENERATE_لاڳيتو_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter( فراغ ) FREERTOS_SYSTEM_CALL;

__asm config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter_Unpriv
MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter_Priv
        b MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter_Impl
MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )

فراغ MPU_v_Task_سيٽ_Application_Task_ٽيگ( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_سيٽ_Application_Task_ٽيگ( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_سيٽ_Application_Task_ٽيگ_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_v_Task_سيٽ_Application_Task_ٽيگ_Unpriv
MPU_v_Task_سيٽ_Application_Task_ٽيگ_Priv
        b MPU_v_Task_سيٽ_Application_Task_ٽيگ_Impl
MPU_v_Task_سيٽ_Application_Task_ٽيگ_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#جيڪڏهن_پورو /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )

TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٽيگ( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٽيگ( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Get_Application_Task_ٽيگ_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_Task_Get_Application_Task_ٽيگ_Unpriv
MPU_x_Task_Get_Application_Task_ٽيگ_Priv
        b MPU_x_Task_Get_Application_Task_ٽيگ_Impl
MPU_x_Task_Get_Application_Task_ٽيگ_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#جيڪڏهن_پورو /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_انگ_THREAD_LOCAL_STORAGE_اشارا != 0 )

فراغ MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو( TaskHandle_t x_Task_منزل_سيٽ,
                                            بنياد_Type_t x_اشاريو,
                                            فراغ * pv_قدر ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو( TaskHandle_t x_Task_منزل_سيٽ,
                                                  بنياد_Type_t x_اشاريو,
                                                  فراغ * pv_قدر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو_Unpriv
MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو_Priv
        b MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو_Impl
MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو_Unpriv
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
}

#جيڪڏهن_پورو /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_انگ_THREAD_LOCAL_STORAGE_اشارا != 0 )

فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارو( TaskHandle_t x_Task_منزل_Query,
                                               بنياد_Type_t x_اشاريو ) FREERTOS_SYSTEM_CALL;

__asm فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارو( TaskHandle_t x_Task_منزل_Query,
                                                     بنياد_Type_t x_اشاريو ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pv_Task_Get_Thread_Local_Storage_اشارو_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_pv_Task_Get_Thread_Local_Storage_اشارو_Unpriv
MPU_pv_Task_Get_Thread_Local_Storage_اشارو_Priv
        b MPU_pv_Task_Get_Thread_Local_Storage_اشارو_Impl
MPU_pv_Task_Get_Thread_Local_Storage_اشارو_Unpriv
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
}

#جيڪڏهن_پورو /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                      ثابت UBaseType_t ux_Array_سائيز,
                                      config_لاڳيتو_وقت_COUNTER_TYPE * ثابت pul_ڪل_لاڳيتو_وقت ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                            ثابت UBaseType_t ux_Array_سائيز,
                                            config_لاڳيتو_وقت_COUNTER_TYPE * ثابت pul_ڪل_لاڳيتو_وقت ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_uxTaskGetSystemStateImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_uxTaskGetSystemState_Unpriv
MPU_uxTaskGetSystemState_Priv
        b MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemState_Unpriv
        svc #SYSTEM_CALL_uxTaskGetSystemState
}

#جيڪڏهن_پورو /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_Get_ڍير_مٿاهون_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark_Unpriv
MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark_Priv
        b MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark_Impl
MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
}

#جيڪڏهن_پورو /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_Get_ڍير_مٿاهون_Water_Mark2 == 1 )

config_ڍير_اونهائي_TYPE MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_ڍير_اونهائي_TYPE MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2_Unpriv
MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2_Priv
        b MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2_Impl
MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
}

#جيڪڏهن_پورو /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetCurrentTaskHandleImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
MPU_xTaskGetCurrentTaskHandle_Priv
        b MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
}

#جيڪڏهن_پورو /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

بنياد_Type_t MPU_xTaskGetSchedulerState( فراغ ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetSchedulerStateImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_xTaskGetSchedulerState_Unpriv
MPU_xTaskGetSchedulerState_Priv
        b MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerState_Unpriv
        svc #SYSTEM_CALL_xTaskGetSchedulerState
}

#جيڪڏهن_پورو /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

فراغ MPU_v_Task_سيٽ_وقت_ٻاهريون_State( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_سيٽ_وقت_ٻاهريون_State( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_سيٽ_وقت_ٻاهريون_State_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_v_Task_سيٽ_وقت_ٻاهريون_State_Unpriv
MPU_v_Task_سيٽ_وقت_ٻاهريون_State_Priv
        b MPU_v_Task_سيٽ_وقت_ٻاهريون_State_Impl
MPU_v_Task_سيٽ_وقت_ٻاهريون_State_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

بنياد_Type_t MPU_x_Task_Check_For_وقت_ٻاهريون( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون,
                                     TickType_t * ثابت px_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_Task_Check_For_وقت_ٻاهريون( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون,
                                     TickType_t * ثابت px_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Check_For_وقت_ٻاهريون_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_Task_Check_For_وقت_ٻاهريون_Unpriv
MPU_x_Task_Check_For_وقت_ٻاهريون_Priv
        b MPU_x_Task_Check_For_وقت_ٻاهريون_Impl
MPU_x_Task_Check_For_وقت_ٻاهريون_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

بنياد_Type_t MPU_x_Task_Generic_Notify_داخلا( ثابت xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_Task_Generic_Notify_داخلا( ثابت xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_xTaskGenericNotify_Unpriv
MPU_xTaskGenericNotify_Priv
        b MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotify_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotify
}

#جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

بنياد_Type_t MPU_x_Task_Generic_Notify_Wait_داخلا( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_Task_Generic_Notify_Wait_داخلا( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyWaitImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_xTaskGenericNotifyWait_Unpriv
MPU_xTaskGenericNotifyWait_Priv
        b MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWait_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
}

#جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاريو_منزل_Wait_On,
                                      بنياد_Type_t x_Clear_ڳڻپ_On_Exit,
                                      TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاريو_منزل_Wait_On,
                                            بنياد_Type_t x_Clear_ڳڻپ_On_Exit,
                                            TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ulTaskGenericNotifyTakeImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
MPU_ulTaskGenericNotifyTake_Priv
        b MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTake_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
}

#جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

بنياد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t ux_اشاريو_منزل_Clear ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t ux_اشاريو_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyStateClearImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
MPU_xTaskGenericNotifyStateClear_Priv
        b MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClear_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
}

#جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                            UBaseType_t ux_اشاريو_منزل_Clear,
                                            uint32_t ul_بٽ_منزل_Clear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                  UBaseType_t ux_اشاريو_منزل_Clear,
                                                  uint32_t ul_بٽ_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Generic_Notify_قدر_Clear_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ul_Task_Generic_Notify_قدر_Clear_Unpriv
MPU_ul_Task_Generic_Notify_قدر_Clear_Priv
        b MPU_ul_Task_Generic_Notify_قدر_Clear_Impl
MPU_ul_Task_Generic_Notify_قدر_Clear_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
}

#جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

بنياد_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                  ثابت فراغ * ثابت pv_شي_منزل_قطار,
                                  TickType_t x_Ticks_منزل_Wait,
                                  ثابت بنياد_Type_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                        ثابت فراغ * ثابت pv_شي_منزل_قطار,
                                        TickType_t x_Ticks_منزل_Wait,
                                        ثابت بنياد_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Generic_Send_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_قطار_Generic_Send_Unpriv
MPU_x_قطار_Generic_Send_Priv
        b MPU_x_قطار_Generic_Send_Impl
MPU_x_قطار_Generic_Send_Unpriv
        svc #SYSTEM_CALL_xQueueGenericSend
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_قطار_Messages_انتظار( ثابت قطار_Handle_t x_قطار ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_قطار_Messages_انتظار( ثابت قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_قطار_Messages_انتظار_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ux_قطار_Messages_انتظار_Unpriv
MPU_ux_قطار_Messages_انتظار_Priv
        b MPU_ux_قطار_Messages_انتظار_Impl
MPU_ux_قطار_Messages_انتظار_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_قطار_Spaces_موجود( ثابت قطار_Handle_t x_قطار ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_قطار_Spaces_موجود( ثابت قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_قطار_Spaces_موجود_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ux_قطار_Spaces_موجود_Unpriv
MPU_ux_قطار_Spaces_موجود_Priv
        b MPU_ux_قطار_Spaces_موجود_Impl
MPU_ux_قطار_Spaces_موجود_Unpriv
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
}
/*-----------------------------------------------------------*/

بنياد_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                              فراغ * ثابت pv_بفر,
                              TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                                    فراغ * ثابت pv_بفر,
                                    TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Receive_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_قطار_Receive_Unpriv
MPU_x_قطار_Receive_Priv
        b MPU_x_قطار_Receive_Impl
MPU_x_قطار_Receive_Unpriv
        svc #SYSTEM_CALL_xQueueReceive
}
/*-----------------------------------------------------------*/

بنياد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                           فراغ * ثابت pv_بفر,
                           TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                                 فراغ * ثابت pv_بفر,
                                 TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Peek_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_قطار_Peek_Unpriv
MPU_x_قطار_Peek_Priv
        b MPU_x_قطار_Peek_Impl
MPU_x_قطار_Peek_Unpriv
        svc #SYSTEM_CALL_xQueuePeek
}
/*-----------------------------------------------------------*/

بنياد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                    TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                          TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Semaphore_Take_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_قطار_Semaphore_Take_Unpriv
MPU_x_قطار_Semaphore_Take_Priv
        b MPU_x_قطار_Semaphore_Take_Impl
MPU_x_قطار_Semaphore_Take_Unpriv
        svc #SYSTEM_CALL_xQueueSemaphoreTake
}
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Get_Mutex_Holder_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_قطار_Get_Mutex_Holder_Unpriv
MPU_x_قطار_Get_Mutex_Holder_Priv
        b MPU_x_قطار_Get_Mutex_Holder_Impl
MPU_x_قطار_Get_Mutex_Holder_Unpriv
        svc #SYSTEM_CALL_xQueueGetMutexHolder
}

#جيڪڏهن_پورو /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

بنياد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                         TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                               TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Take_Mutex_Recursive_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_قطار_Take_Mutex_Recursive_Unpriv
MPU_x_قطار_Take_Mutex_Recursive_Priv
        b MPU_x_قطار_Take_Mutex_Recursive_Impl
MPU_x_قطار_Take_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
}

#جيڪڏهن_پورو /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

بنياد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Give_Mutex_Recursive_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_قطار_Give_Mutex_Recursive_Unpriv
MPU_x_قطار_Give_Mutex_Recursive_Priv
        b MPU_x_قطار_Give_Mutex_Recursive_Impl
MPU_x_قطار_Give_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
}

#جيڪڏهن_پورو /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_قطار_SETS == 1 )

قطار_سيٽ_Member_Handle_t MPU_x_قطار_Select_From_سيٽ( قطار_سيٽ_Handle_t x_قطار_سيٽ,
                                                ثابت TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm قطار_سيٽ_Member_Handle_t MPU_x_قطار_Select_From_سيٽ( قطار_سيٽ_Handle_t x_قطار_سيٽ,
                                                      ثابت TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Select_From_سيٽ_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_قطار_Select_From_سيٽ_Unpriv
MPU_x_قطار_Select_From_سيٽ_Priv
        b MPU_x_قطار_Select_From_سيٽ_Impl
MPU_x_قطار_Select_From_سيٽ_Unpriv
        svc #SYSTEM_CALL_xQueueSelectFromSet
}

#جيڪڏهن_پورو /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_قطار_SETS == 1 )

بنياد_Type_t MPU_x_قطار_جوڙيو_منزل_سيٽ( قطار_سيٽ_Member_Handle_t x_قطار_Or_Semaphore,
                               قطار_سيٽ_Handle_t x_قطار_سيٽ ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_قطار_جوڙيو_منزل_سيٽ( قطار_سيٽ_Member_Handle_t x_قطار_Or_Semaphore,
                                     قطار_سيٽ_Handle_t x_قطار_سيٽ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_جوڙيو_منزل_سيٽ_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_قطار_جوڙيو_منزل_سيٽ_Unpriv
MPU_x_قطار_جوڙيو_منزل_سيٽ_Priv
        b MPU_x_قطار_جوڙيو_منزل_سيٽ_Impl
MPU_x_قطار_جوڙيو_منزل_سيٽ_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#جيڪڏهن_پورو /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_قطار_REGISTRY_سائيز > 0 )

فراغ MPU_v_قطار_جوڙيو_منزل_Registry( قطار_Handle_t x_قطار,
                              ثابت حرف * pcName ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_قطار_جوڙيو_منزل_Registry( قطار_Handle_t x_قطار,
                                    ثابت حرف * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_قطار_جوڙيو_منزل_Registry_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_v_قطار_جوڙيو_منزل_Registry_Unpriv
MPU_v_قطار_جوڙيو_منزل_Registry_Priv
        b MPU_v_قطار_جوڙيو_منزل_Registry_Impl
MPU_v_قطار_جوڙيو_منزل_Registry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#جيڪڏهن_پورو /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_قطار_REGISTRY_سائيز > 0 )

فراغ MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_قطار_Unregister_قطار_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_v_قطار_Unregister_قطار_Unpriv
MPU_v_قطار_Unregister_قطار_Priv
        b MPU_v_قطار_Unregister_قطار_Impl
MPU_v_قطار_Unregister_قطار_Unpriv
        svc #SYSTEM_CALL_vQueueUnregisterQueue
}

#جيڪڏهن_پورو /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_قطار_REGISTRY_سائيز > 0 )

ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) FREERTOS_SYSTEM_CALL;

__asm ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pc_قطار_Get_Name_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_pc_قطار_Get_Name_Unpriv
MPU_pc_قطار_Get_Name_Priv
        b MPU_pc_قطار_Get_Name_Impl
MPU_pc_قطار_Get_Name_Unpriv
        svc #SYSTEM_CALL_pcQueueGetName
}

#جيڪڏهن_پورو /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pvTimerGetTimerIDImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_pvTimerGetTimerID_Unpriv
MPU_pvTimerGetTimerID_Priv
        b MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerID_Unpriv
        svc #SYSTEM_CALL_pvTimerGetTimerID
}

#جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ MPU_v_Timer_سيٽ_Timer_ID( TimerHandle_t xTimer,
                           فراغ * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Timer_سيٽ_Timer_ID( TimerHandle_t xTimer,
                                 فراغ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Timer_سيٽ_Timer_IDImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_v_Timer_سيٽ_Timer_ID_Unpriv
MPU_v_Timer_سيٽ_Timer_ID_Priv
        b MPU_v_Timer_سيٽ_Timer_IDImpl
MPU_v_Timer_سيٽ_Timer_ID_Unpriv
        svc #SYSTEM_CALL_vTimerSetTimerID
}

#جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

بنياد_Type_t MPU_x_Timer_Is_Timer_سرگرم( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_Timer_Is_Timer_سرگرم( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Is_Timer_سرگرم_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_Timer_Is_Timer_سرگرم_Unpriv
MPU_x_Timer_Is_Timer_سرگرم_Priv
        b MPU_x_Timer_Is_Timer_سرگرم_Impl
MPU_x_Timer_Is_Timer_سرگرم_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGetTimerDaemonTaskHandleImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
MPU_xTimerGetTimerDaemonTaskHandle_Priv
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
}

#جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

بنياد_Type_t MPU_x_Timer_Generic_Command_From_Task_داخلا( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_Timer_Generic_Command_From_Task_داخلا( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGenericCommandFromTaskImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
MPU_xTimerGenericCommandFromTask_Priv
        b MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTask_Unpriv
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
}

#جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pcTimerGetNameImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_pcTimerGetName_Unpriv
MPU_pcTimerGetName_Priv
        b MPU_pcTimerGetNameImpl
MPU_pcTimerGetName_Unpriv
        svc #SYSTEM_CALL_pcTimerGetName
}

#جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ MPU_v_Timer_سيٽ_Reload_گهڻائي( TimerHandle_t xTimer,
                              ثابت بنياد_Type_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Timer_سيٽ_Reload_گهڻائي( TimerHandle_t xTimer,
                                    ثابت بنياد_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Timer_سيٽ_Reload_گهڻائي_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_v_Timer_سيٽ_Reload_گهڻائي_Unpriv
MPU_v_Timer_سيٽ_Reload_گهڻائي_Priv
        b MPU_v_Timer_سيٽ_Reload_گهڻائي_Impl
MPU_v_Timer_سيٽ_Reload_گهڻائي_Unpriv
        svc #SYSTEM_CALL_vTimerSetReloadMode
}

#جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

بنياد_Type_t MPU_x_Timer_Get_Reload_گهڻائي( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_Timer_Get_Reload_گهڻائي( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Get_Reload_گهڻائي_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_Timer_Get_Reload_گهڻائي_Unpriv
MPU_x_Timer_Get_Reload_گهڻائي_Priv
        b MPU_x_Timer_Get_Reload_گهڻائي_Impl
MPU_x_Timer_Get_Reload_گهڻائي_Unpriv
        svc #SYSTEM_CALL_xTimerGetReloadMode
}

#جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

UBaseType_t MPU_ux_Timer_Get_Reload_گهڻائي( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Timer_Get_Reload_گهڻائي( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Timer_Get_Reload_گهڻائي_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ux_Timer_Get_Reload_گهڻائي_Unpriv
MPU_ux_Timer_Get_Reload_گهڻائي_Priv
        b MPU_ux_Timer_Get_Reload_گهڻائي_Impl
MPU_ux_Timer_Get_Reload_گهڻائي_Unpriv
        svc #SYSTEM_CALL_uxTimerGetReloadMode
}

#جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGetPeriodImpl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_xTimerGetPeriod_Unpriv
MPU_xTimerGetPeriod_Priv
        b MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriod_Unpriv
        svc #SYSTEM_CALL_xTimerGetPeriod
}

#جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Get_Expiry_وقت_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_Timer_Get_Expiry_وقت_Unpriv
MPU_x_Timer_Get_Expiry_وقت_Priv
        b MPU_x_Timer_Get_Expiry_وقت_Impl
MPU_x_Timer_Get_Expiry_وقت_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بٽ_t MPU_x_Event_گروهه_Wait_بٽ_داخلا( ثابت x_Event_گروهه_Wait_بٽ_Params_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm Event_بٽ_t MPU_x_Event_گروهه_Wait_بٽ_داخلا( ثابت x_Event_گروهه_Wait_بٽ_Params_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروهه_Wait_بٽ_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_Event_گروهه_Wait_بٽ_Unpriv
MPU_x_Event_گروهه_Wait_بٽ_Priv
        b MPU_x_Event_گروهه_Wait_بٽ_Impl
MPU_x_Event_گروهه_Wait_بٽ_Unpriv
        svc #SYSTEM_CALL_xEventGroupWaitBits
}

#جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بٽ_t MPU_x_Event_گروهه_Clear_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                      ثابت Event_بٽ_t ux_بٽ_منزل_Clear ) FREERTOS_SYSTEM_CALL;

__asm Event_بٽ_t MPU_x_Event_گروهه_Clear_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                            ثابت Event_بٽ_t ux_بٽ_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروهه_Clear_بٽ_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_Event_گروهه_Clear_بٽ_Unpriv
MPU_x_Event_گروهه_Clear_بٽ_Priv
        b MPU_x_Event_گروهه_Clear_بٽ_Impl
MPU_x_Event_گروهه_Clear_بٽ_Unpriv
        svc #SYSTEM_CALL_xEventGroupClearBits
}

#جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بٽ_t MPU_x_Event_گروهه_سيٽ_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                    ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ ) FREERTOS_SYSTEM_CALL;

__asm Event_بٽ_t MPU_x_Event_گروهه_سيٽ_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                          ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروهه_سيٽ_بٽ_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_Event_گروهه_سيٽ_بٽ_Unpriv
MPU_x_Event_گروهه_سيٽ_بٽ_Priv
        b MPU_x_Event_گروهه_سيٽ_بٽ_Impl
MPU_x_Event_گروهه_سيٽ_بٽ_Unpriv
        svc #SYSTEM_CALL_xEventGroupSetBits
}

#جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بٽ_t MPU_x_Event_گروهه_Sync( Event_گروهه_Handle_t x_Event_گروهه,
                                 ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ,
                                 ثابت Event_بٽ_t ux_بٽ_منزل_Wait_For,
                                 TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm Event_بٽ_t MPU_x_Event_گروهه_Sync( Event_گروهه_Handle_t x_Event_گروهه,
                                       ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ,
                                       ثابت Event_بٽ_t ux_بٽ_منزل_Wait_For,
                                       TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروهه_Sync_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_Event_گروهه_Sync_Unpriv
MPU_x_Event_گروهه_Sync_Priv
        b MPU_x_Event_گروهه_Sync_Impl
MPU_x_Event_گروهه_Sync_Unpriv
        svc #SYSTEM_CALL_xEventGroupSync
}

#جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_گروهه_Get_عدد( فراغ * x_Event_گروهه ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_گروهه_Get_عدد( فراغ * x_Event_گروهه ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Event_گروهه_Get_عدد_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_ux_Event_گروهه_Get_عدد_Unpriv
MPU_ux_Event_گروهه_Get_عدد_Priv
        b MPU_ux_Event_گروهه_Get_عدد_Impl
MPU_ux_Event_گروهه_Get_عدد_Unpriv
        svc #SYSTEM_CALL_uxEventGroupGetNumber
}

#جيڪڏهن_پورو /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

فراغ MPU_v_Event_گروهه_سيٽ_عدد( فراغ * x_Event_گروهه,
                               UBaseType_t ux_Event_گروهه_عدد ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Event_گروهه_سيٽ_عدد( فراغ * x_Event_گروهه,
                                     UBaseType_t ux_Event_گروهه_عدد ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Event_گروهه_سيٽ_عدد_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_v_Event_گروهه_سيٽ_عدد_Unpriv
MPU_v_Event_گروهه_سيٽ_عدد_Priv
        b MPU_v_Event_گروهه_سيٽ_عدد_Impl
MPU_v_Event_گروهه_سيٽ_عدد_Unpriv
        svc #SYSTEM_CALL_vEventGroupSetNumber
}

#جيڪڏهن_پورو /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_وهڪرو_BUFFERS == 1 )

size_t MPU_x_وهڪرو_بفر_Send( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                              ثابت فراغ * pv_Tx_معلومات,
                              size_t x_معلومات_ڊيگهائي_بائيٽون,
                              TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_وهڪرو_بفر_Send( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                    ثابت فراغ * pv_Tx_معلومات,
                                    size_t x_معلومات_ڊيگهائي_بائيٽون,
                                    TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_وهڪرو_بفر_Send_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_وهڪرو_بفر_Send_Unpriv
MPU_x_وهڪرو_بفر_Send_Priv
        b MPU_x_وهڪرو_بفر_Send_Impl
MPU_x_وهڪرو_بفر_Send_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSend
}

#جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_وهڪرو_BUFFERS == 1 )

size_t MPU_x_وهڪرو_بفر_Receive( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                 فراغ * pv_Rx_معلومات,
                                 size_t x_بفر_ڊيگهائي_بائيٽون,
                                 TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_وهڪرو_بفر_Receive( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                       فراغ * pv_Rx_معلومات,
                                       size_t x_بفر_ڊيگهائي_بائيٽون,
                                       TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_وهڪرو_بفر_Receive_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_وهڪرو_بفر_Receive_Unpriv
MPU_x_وهڪرو_بفر_Receive_Priv
        b MPU_x_وهڪرو_بفر_Receive_Impl
MPU_x_وهڪرو_بفر_Receive_Unpriv
        svc #SYSTEM_CALL_xStreamBufferReceive
}

#جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_وهڪرو_BUFFERS == 1 )

بنياد_Type_t MPU_x_وهڪرو_بفر_Is_ڀريل( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_وهڪرو_بفر_Is_ڀريل( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_وهڪرو_بفر_Is_ڀريل_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_وهڪرو_بفر_Is_ڀريل_Unpriv
MPU_x_وهڪرو_بفر_Is_ڀريل_Priv
        b MPU_x_وهڪرو_بفر_Is_ڀريل_Impl
MPU_x_وهڪرو_بفر_Is_ڀريل_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_وهڪرو_BUFFERS == 1 )

بنياد_Type_t MPU_x_وهڪرو_بفر_Is_خالي_جايون( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_وهڪرو_بفر_Is_خالي_جايون( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_وهڪرو_بفر_Is_خالي_جايون_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_وهڪرو_بفر_Is_خالي_جايون_Unpriv
MPU_x_وهڪرو_بفر_Is_خالي_جايون_Priv
        b MPU_x_وهڪرو_بفر_Is_خالي_جايون_Impl
MPU_x_وهڪرو_بفر_Is_خالي_جايون_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_وهڪرو_BUFFERS == 1 )

size_t MPU_x_وهڪرو_بفر_Spaces_موجود( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_وهڪرو_بفر_Spaces_موجود( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_وهڪرو_بفر_Spaces_موجود_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_وهڪرو_بفر_Spaces_موجود_Unpriv
MPU_x_وهڪرو_بفر_Spaces_موجود_Priv
        b MPU_x_وهڪرو_بفر_Spaces_موجود_Impl
MPU_x_وهڪرو_بفر_Spaces_موجود_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
}

#جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_وهڪرو_BUFFERS == 1 )

size_t MPU_x_وهڪرو_بفر_بائيٽون_موجود( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_وهڪرو_بفر_بائيٽون_موجود( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_وهڪرو_بفر_بائيٽون_موجود_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_وهڪرو_بفر_بائيٽون_موجود_Unpriv
MPU_x_وهڪرو_بفر_بائيٽون_موجود_Priv
        b MPU_x_وهڪرو_بفر_بائيٽون_موجود_Impl
MPU_x_وهڪرو_بفر_بائيٽون_موجود_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_وهڪرو_BUFFERS == 1 )

بنياد_Type_t MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm بنياد_Type_t MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level_Unpriv
MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level_Priv
        b MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level_Impl
MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
}

#جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_وهڪرو_BUFFERS == 1 )

size_t MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون_Impl

    ڌڪو {r0}
    mrs r0, control
    tst r0, #1
    ڪڍو {r0}
    bne MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون_Unpriv
MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون_Priv
        b MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون_Impl
MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#جيڪڏهن_پورو /* configUSE_MPU_WRAPPERS_V1 == 0 */
