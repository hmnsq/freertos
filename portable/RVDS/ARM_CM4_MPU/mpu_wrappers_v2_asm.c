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
#تعریف_کړه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"
#ضمن "mpu_syscall_numbers.h"

#تعریف_لغوه MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

#إذا ( INCLUDE_xTaskDelayUntil == 1 )

بنسټ_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پخوانی_Wake_وخت,
                                ثابت TickType_t x_وخت_Increment ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پخوانی_Wake_وخت,
                                      ثابت TickType_t x_وخت_Increment ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskDelayUntilImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_xTaskDelayUntil_Unpriv
MPU_xTaskDelayUntil_Priv
        b MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntil_Unpriv
        svc #SYSTEM_CALL_xTaskDelayUntil
}

#د_که_پای /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskAbortDelay == 1 )

بنسټ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskAbortDelayImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_xTaskAbortDelay_Unpriv
MPU_xTaskAbortDelay_Priv
        b MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelay_Unpriv
        svc #SYSTEM_CALL_xTaskAbortDelay
}

#د_که_پای /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskDelay == 1 )

فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskDelayImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_vTaskDelay_Unpriv
MPU_vTaskDelay_Priv
        b MPU_vTaskDelayImpl
MPU_vTaskDelay_Unpriv
        svc #SYSTEM_CALL_vTaskDelay
}

#د_که_پای /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_لومړیتوب_Get == 1 )

UBaseType_t MPU_ux_Task_لومړیتوب_Get( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_لومړیتوب_Get( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_لومړیتوب_Get_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ux_Task_لومړیتوب_Get_Unpriv
MPU_ux_Task_لومړیتوب_Get_Priv
        b MPU_ux_Task_لومړیتوب_Get_Impl
MPU_ux_Task_لومړیتوب_Get_Unpriv
        svc #SYSTEM_CALL_uxTaskPriorityGet
}

#د_که_پای /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_eTaskGetStateImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_eTaskGetState_Unpriv
MPU_eTaskGetState_Priv
        b MPU_eTaskGetStateImpl
MPU_eTaskGetState_Unpriv
        svc #SYSTEM_CALL_eTaskGetState
}

#د_که_پای /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TRACE_FACILITY == 1 )

فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                       Task_حالت_t * px_Task_حالت,
                       بنسټ_Type_t x_Get_Free_ډېری_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                             Task_حالت_t * px_Task_حالت,
                             بنسټ_Type_t x_Get_Free_ډېری_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskGetInfoImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_vTaskGetInfo_Unpriv
MPU_vTaskGetInfo_Priv
        b MPU_vTaskGetInfoImpl
MPU_vTaskGetInfo_Unpriv
        svc #SYSTEM_CALL_vTaskGetInfo
}

#د_که_پای /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetIdleTaskHandleImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
MPU_xTaskGetIdleTaskHandle_Priv
        b MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
}

#د_که_پای /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskSuspend == 1 )

فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_منزل_Suspend ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_منزل_Suspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskSuspendImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_vTaskSuspend_Unpriv
MPU_vTaskSuspend_Priv
        b MPU_vTaskSuspendImpl
MPU_vTaskSuspend_Unpriv
        svc #SYSTEM_CALL_vTaskSuspend
}

#د_که_پای /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskSuspend == 1 )

فراغ MPU_vTaskResume( TaskHandle_t x_Task_منزل_Resume ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskResume( TaskHandle_t x_Task_منزل_Resume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskResumeImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_vTaskResume_Unpriv
MPU_vTaskResume_Priv
        b MPU_vTaskResumeImpl
MPU_vTaskResume_Unpriv
        svc #SYSTEM_CALL_vTaskResume
}

#د_که_پای /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_شمېر( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_شمېر( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Get_Tick_شمېر_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_Task_Get_Tick_شمېر_Unpriv
MPU_x_Task_Get_Tick_شمېر_Priv
        b MPU_x_Task_Get_Tick_شمېر_Impl
MPU_x_Task_Get_Tick_شمېر_Unpriv
        svc #SYSTEM_CALL_xTaskGetTickCount
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Task_Get_شمېره_د_Tasks( فراغ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_شمېره_د_Tasks( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_شمېره_د_Tasks_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ux_Task_Get_شمېره_د_Tasks_Unpriv
MPU_ux_Task_Get_شمېره_د_Tasks_Priv
        b MPU_ux_Task_Get_شمېره_د_Tasks_Impl
MPU_ux_Task_Get_شمېره_د_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#إذا ( config_GENERATE_پرلپسې_وخت_STATS == 1 )

config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Counter( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Counter( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_پرلپسې_وخت_Counter_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ul_Task_Get_پرلپسې_وخت_Counter_Unpriv
MPU_ul_Task_Get_پرلپسې_وخت_Counter_Priv
        b MPU_ul_Task_Get_پرلپسې_وخت_Counter_Impl
MPU_ul_Task_Get_پرلپسې_وخت_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_GENERATE_پرلپسې_وخت_STATS == 1 )

config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Percent( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Percent( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_پرلپسې_وخت_Percent_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ul_Task_Get_پرلپسې_وخت_Percent_Unpriv
MPU_ul_Task_Get_پرلپسې_وخت_Percent_Priv
        b MPU_ul_Task_Get_پرلپسې_وخت_Percent_Impl
MPU_ul_Task_Get_پرلپسې_وخت_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( config_GENERATE_پرلپسې_وخت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent( فراغ ) FREERTOS_SYSTEM_CALL;

__asm config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent_Unpriv
MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent_Priv
        b MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent_Impl
MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( config_GENERATE_پرلپسې_وخت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter( فراغ ) FREERTOS_SYSTEM_CALL;

__asm config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter_Unpriv
MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter_Priv
        b MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter_Impl
MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_APPLICATION_TASK_نښان == 1 )

فراغ MPU_v_Task_سېټ_Application_Task_نښان( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_سېټ_Application_Task_نښان( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_سېټ_Application_Task_نښان_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_v_Task_سېټ_Application_Task_نښان_Unpriv
MPU_v_Task_سېټ_Application_Task_نښان_Priv
        b MPU_v_Task_سېټ_Application_Task_نښان_Impl
MPU_v_Task_سېټ_Application_Task_نښان_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#د_که_پای /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_APPLICATION_TASK_نښان == 1 )

TaskHookFunction_t MPU_x_Task_Get_Application_Task_نښان( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_x_Task_Get_Application_Task_نښان( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Get_Application_Task_نښان_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_Task_Get_Application_Task_نښان_Unpriv
MPU_x_Task_Get_Application_Task_نښان_Priv
        b MPU_x_Task_Get_Application_Task_نښان_Impl
MPU_x_Task_Get_Application_Task_نښان_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#د_که_پای /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_عدد_THREAD_LOCAL_STORAGE_اشارې != 0 )

فراغ MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر( TaskHandle_t x_Task_منزل_سېټ,
                                            بنسټ_Type_t x_شاخص,
                                            فراغ * pv_ارزښت ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر( TaskHandle_t x_Task_منزل_سېټ,
                                                  بنسټ_Type_t x_شاخص,
                                                  فراغ * pv_ارزښت ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر_Unpriv
MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر_Priv
        b MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر_Impl
MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر_Unpriv
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
}

#د_که_پای /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_عدد_THREAD_LOCAL_STORAGE_اشارې != 0 )

فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر( TaskHandle_t x_Task_منزل_Query,
                                               بنسټ_Type_t x_شاخص ) FREERTOS_SYSTEM_CALL;

__asm فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر( TaskHandle_t x_Task_منزل_Query,
                                                     بنسټ_Type_t x_شاخص ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر_Unpriv
MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر_Priv
        b MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر_Impl
MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر_Unpriv
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
}

#د_که_پای /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                      ثابت UBaseType_t ux_Array_اندازه,
                                      config_پرلپسې_وخت_COUNTER_TYPE * ثابت pul_ټول_پرلپسې_وخت ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                            ثابت UBaseType_t ux_Array_اندازه,
                                            config_پرلپسې_وخت_COUNTER_TYPE * ثابت pul_ټول_پرلپسې_وخت ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_uxTaskGetSystemStateImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_uxTaskGetSystemState_Unpriv
MPU_uxTaskGetSystemState_Priv
        b MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemState_Unpriv
        svc #SYSTEM_CALL_uxTaskGetSystemState
}

#د_که_پای /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_Get_ډېری_لوړ_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_ډېری_لوړ_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_ډېری_لوړ_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_ډېری_لوړ_Water_Mark_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ux_Task_Get_ډېری_لوړ_Water_Mark_Unpriv
MPU_ux_Task_Get_ډېری_لوړ_Water_Mark_Priv
        b MPU_ux_Task_Get_ډېری_لوړ_Water_Mark_Impl
MPU_ux_Task_Get_ډېری_لوړ_Water_Mark_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
}

#د_که_پای /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_Get_ډېری_لوړ_Water_Mark2 == 1 )

config_ډېری_ژوروالی_TYPE MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_ډېری_ژوروالی_TYPE MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2_Unpriv
MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2_Priv
        b MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2_Impl
MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
}

#د_که_پای /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetCurrentTaskHandleImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
MPU_xTaskGetCurrentTaskHandle_Priv
        b MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
}

#د_که_پای /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

بنسټ_Type_t MPU_xTaskGetSchedulerState( فراغ ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetSchedulerStateImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_xTaskGetSchedulerState_Unpriv
MPU_xTaskGetSchedulerState_Priv
        b MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerState_Unpriv
        svc #SYSTEM_CALL_xTaskGetSchedulerState
}

#د_که_پای /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

فراغ MPU_v_Task_سېټ_وخت_بهر_State( وخت_بهر_t * ثابت px_وخت_بهر ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_سېټ_وخت_بهر_State( وخت_بهر_t * ثابت px_وخت_بهر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_سېټ_وخت_بهر_State_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_v_Task_سېټ_وخت_بهر_State_Unpriv
MPU_v_Task_سېټ_وخت_بهر_State_Priv
        b MPU_v_Task_سېټ_وخت_بهر_State_Impl
MPU_v_Task_سېټ_وخت_بهر_State_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

بنسټ_Type_t MPU_x_Task_Check_For_وخت_بهر( وخت_بهر_t * ثابت px_وخت_بهر,
                                     TickType_t * ثابت px_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_Task_Check_For_وخت_بهر( وخت_بهر_t * ثابت px_وخت_بهر,
                                     TickType_t * ثابت px_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Check_For_وخت_بهر_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_Task_Check_For_وخت_بهر_Unpriv
MPU_x_Task_Check_For_وخت_بهر_Priv
        b MPU_x_Task_Check_For_وخت_بهر_Impl
MPU_x_Task_Check_For_وخت_بهر_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

بنسټ_Type_t MPU_x_Task_Generic_Notify_ثبت( ثابت xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_Task_Generic_Notify_ثبت( ثابت xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_xTaskGenericNotify_Unpriv
MPU_xTaskGenericNotify_Priv
        b MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotify_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotify
}

#د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

بنسټ_Type_t MPU_x_Task_Generic_Notify_Wait_ثبت( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_Task_Generic_Notify_Wait_ثبت( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyWaitImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_xTaskGenericNotifyWait_Unpriv
MPU_xTaskGenericNotifyWait_Priv
        b MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWait_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
}

#د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_شاخص_منزل_Wait_On,
                                      بنسټ_Type_t x_Clear_شمېر_On_Exit,
                                      TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_شاخص_منزل_Wait_On,
                                            بنسټ_Type_t x_Clear_شمېر_On_Exit,
                                            TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ulTaskGenericNotifyTakeImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
MPU_ulTaskGenericNotifyTake_Priv
        b MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTake_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
}

#د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

بنسټ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t ux_شاخص_منزل_Clear ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t ux_شاخص_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyStateClearImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
MPU_xTaskGenericNotifyStateClear_Priv
        b MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClear_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
}

#د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_ارزښت_Clear( TaskHandle_t xTask,
                                            UBaseType_t ux_شاخص_منزل_Clear,
                                            uint32_t ul_بټونه_منزل_Clear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_ارزښت_Clear( TaskHandle_t xTask,
                                                  UBaseType_t ux_شاخص_منزل_Clear,
                                                  uint32_t ul_بټونه_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Generic_Notify_ارزښت_Clear_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ul_Task_Generic_Notify_ارزښت_Clear_Unpriv
MPU_ul_Task_Generic_Notify_ارزښت_Clear_Priv
        b MPU_ul_Task_Generic_Notify_ارزښت_Clear_Impl
MPU_ul_Task_Generic_Notify_ارزښت_Clear_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
}

#د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

بنسټ_Type_t MPU_x_کتار_Generic_Send( کتار_Handle_t x_کتار,
                                  ثابت فراغ * ثابت pv_توکی_منزل_کتار,
                                  TickType_t x_Ticks_منزل_Wait,
                                  ثابت بنسټ_Type_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_کتار_Generic_Send( کتار_Handle_t x_کتار,
                                        ثابت فراغ * ثابت pv_توکی_منزل_کتار,
                                        TickType_t x_Ticks_منزل_Wait,
                                        ثابت بنسټ_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_کتار_Generic_Send_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_کتار_Generic_Send_Unpriv
MPU_x_کتار_Generic_Send_Priv
        b MPU_x_کتار_Generic_Send_Impl
MPU_x_کتار_Generic_Send_Unpriv
        svc #SYSTEM_CALL_xQueueGenericSend
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_کتار_Messages_انتظار( ثابت کتار_Handle_t x_کتار ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_کتار_Messages_انتظار( ثابت کتار_Handle_t x_کتار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_کتار_Messages_انتظار_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ux_کتار_Messages_انتظار_Unpriv
MPU_ux_کتار_Messages_انتظار_Priv
        b MPU_ux_کتار_Messages_انتظار_Impl
MPU_ux_کتار_Messages_انتظار_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_کتار_Spaces_شته( ثابت کتار_Handle_t x_کتار ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_کتار_Spaces_شته( ثابت کتار_Handle_t x_کتار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_کتار_Spaces_شته_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ux_کتار_Spaces_شته_Unpriv
MPU_ux_کتار_Spaces_شته_Priv
        b MPU_ux_کتار_Spaces_شته_Impl
MPU_ux_کتار_Spaces_شته_Unpriv
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
}
/*-----------------------------------------------------------*/

بنسټ_Type_t MPU_x_کتار_Receive( کتار_Handle_t x_کتار,
                              فراغ * ثابت pv_بفر,
                              TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_کتار_Receive( کتار_Handle_t x_کتار,
                                    فراغ * ثابت pv_بفر,
                                    TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_کتار_Receive_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_کتار_Receive_Unpriv
MPU_x_کتار_Receive_Priv
        b MPU_x_کتار_Receive_Impl
MPU_x_کتار_Receive_Unpriv
        svc #SYSTEM_CALL_xQueueReceive
}
/*-----------------------------------------------------------*/

بنسټ_Type_t MPU_x_کتار_Peek( کتار_Handle_t x_کتار,
                           فراغ * ثابت pv_بفر,
                           TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_کتار_Peek( کتار_Handle_t x_کتار,
                                 فراغ * ثابت pv_بفر,
                                 TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_کتار_Peek_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_کتار_Peek_Unpriv
MPU_x_کتار_Peek_Priv
        b MPU_x_کتار_Peek_Impl
MPU_x_کتار_Peek_Unpriv
        svc #SYSTEM_CALL_xQueuePeek
}
/*-----------------------------------------------------------*/

بنسټ_Type_t MPU_x_کتار_Semaphore_Take( کتار_Handle_t x_کتار,
                                    TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_کتار_Semaphore_Take( کتار_Handle_t x_کتار,
                                          TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_کتار_Semaphore_Take_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_کتار_Semaphore_Take_Unpriv
MPU_x_کتار_Semaphore_Take_Priv
        b MPU_x_کتار_Semaphore_Take_Impl
MPU_x_کتار_Semaphore_Take_Unpriv
        svc #SYSTEM_CALL_xQueueSemaphoreTake
}
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_x_کتار_Get_Mutex_Holder( کتار_Handle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_x_کتار_Get_Mutex_Holder( کتار_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_کتار_Get_Mutex_Holder_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_کتار_Get_Mutex_Holder_Unpriv
MPU_x_کتار_Get_Mutex_Holder_Priv
        b MPU_x_کتار_Get_Mutex_Holder_Impl
MPU_x_کتار_Get_Mutex_Holder_Unpriv
        svc #SYSTEM_CALL_xQueueGetMutexHolder
}

#د_که_پای /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

بنسټ_Type_t MPU_x_کتار_Take_Mutex_Recursive( کتار_Handle_t xMutex,
                                         TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_کتار_Take_Mutex_Recursive( کتار_Handle_t xMutex,
                                               TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_کتار_Take_Mutex_Recursive_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_کتار_Take_Mutex_Recursive_Unpriv
MPU_x_کتار_Take_Mutex_Recursive_Priv
        b MPU_x_کتار_Take_Mutex_Recursive_Impl
MPU_x_کتار_Take_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
}

#د_که_پای /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

بنسټ_Type_t MPU_x_کتار_Give_Mutex_Recursive( کتار_Handle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_کتار_Give_Mutex_Recursive( کتار_Handle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_کتار_Give_Mutex_Recursive_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_کتار_Give_Mutex_Recursive_Unpriv
MPU_x_کتار_Give_Mutex_Recursive_Priv
        b MPU_x_کتار_Give_Mutex_Recursive_Impl
MPU_x_کتار_Give_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
}

#د_که_پای /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_کتار_SETS == 1 )

کتار_سېټ_Member_Handle_t MPU_x_کتار_Select_From_سېټ( کتار_سېټ_Handle_t x_کتار_سېټ,
                                                ثابت TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm کتار_سېټ_Member_Handle_t MPU_x_کتار_Select_From_سېټ( کتار_سېټ_Handle_t x_کتار_سېټ,
                                                      ثابت TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_کتار_Select_From_سېټ_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_کتار_Select_From_سېټ_Unpriv
MPU_x_کتار_Select_From_سېټ_Priv
        b MPU_x_کتار_Select_From_سېټ_Impl
MPU_x_کتار_Select_From_سېټ_Unpriv
        svc #SYSTEM_CALL_xQueueSelectFromSet
}

#د_که_پای /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_کتار_SETS == 1 )

بنسټ_Type_t MPU_x_کتار_جمع_کړه_منزل_سېټ( کتار_سېټ_Member_Handle_t x_کتار_Or_Semaphore,
                               کتار_سېټ_Handle_t x_کتار_سېټ ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_کتار_جمع_کړه_منزل_سېټ( کتار_سېټ_Member_Handle_t x_کتار_Or_Semaphore,
                                     کتار_سېټ_Handle_t x_کتار_سېټ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_کتار_جمع_کړه_منزل_سېټ_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_کتار_جمع_کړه_منزل_سېټ_Unpriv
MPU_x_کتار_جمع_کړه_منزل_سېټ_Priv
        b MPU_x_کتار_جمع_کړه_منزل_سېټ_Impl
MPU_x_کتار_جمع_کړه_منزل_سېټ_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#د_که_پای /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_کتار_REGISTRY_اندازه > 0 )

فراغ MPU_v_کتار_جمع_کړه_منزل_Registry( کتار_Handle_t x_کتار,
                              ثابت حرف * pcName ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_کتار_جمع_کړه_منزل_Registry( کتار_Handle_t x_کتار,
                                    ثابت حرف * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_کتار_جمع_کړه_منزل_Registry_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_v_کتار_جمع_کړه_منزل_Registry_Unpriv
MPU_v_کتار_جمع_کړه_منزل_Registry_Priv
        b MPU_v_کتار_جمع_کړه_منزل_Registry_Impl
MPU_v_کتار_جمع_کړه_منزل_Registry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#د_که_پای /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_کتار_REGISTRY_اندازه > 0 )

فراغ MPU_v_کتار_Unregister_کتار( کتار_Handle_t x_کتار ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_کتار_Unregister_کتار( کتار_Handle_t x_کتار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_کتار_Unregister_کتار_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_v_کتار_Unregister_کتار_Unpriv
MPU_v_کتار_Unregister_کتار_Priv
        b MPU_v_کتار_Unregister_کتار_Impl
MPU_v_کتار_Unregister_کتار_Unpriv
        svc #SYSTEM_CALL_vQueueUnregisterQueue
}

#د_که_پای /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_کتار_REGISTRY_اندازه > 0 )

ثابت حرف * MPU_pc_کتار_Get_Name( کتار_Handle_t x_کتار ) FREERTOS_SYSTEM_CALL;

__asm ثابت حرف * MPU_pc_کتار_Get_Name( کتار_Handle_t x_کتار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pc_کتار_Get_Name_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_pc_کتار_Get_Name_Unpriv
MPU_pc_کتار_Get_Name_Priv
        b MPU_pc_کتار_Get_Name_Impl
MPU_pc_کتار_Get_Name_Unpriv
        svc #SYSTEM_CALL_pcQueueGetName
}

#د_که_پای /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pvTimerGetTimerIDImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_pvTimerGetTimerID_Unpriv
MPU_pvTimerGetTimerID_Priv
        b MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerID_Unpriv
        svc #SYSTEM_CALL_pvTimerGetTimerID
}

#د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ MPU_v_Timer_سېټ_Timer_ID( TimerHandle_t xTimer,
                           فراغ * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Timer_سېټ_Timer_ID( TimerHandle_t xTimer,
                                 فراغ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Timer_سېټ_Timer_IDImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_v_Timer_سېټ_Timer_ID_Unpriv
MPU_v_Timer_سېټ_Timer_ID_Priv
        b MPU_v_Timer_سېټ_Timer_IDImpl
MPU_v_Timer_سېټ_Timer_ID_Unpriv
        svc #SYSTEM_CALL_vTimerSetTimerID
}

#د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

بنسټ_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Is_Timer_فعال_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_Timer_Is_Timer_فعال_Unpriv
MPU_x_Timer_Is_Timer_فعال_Priv
        b MPU_x_Timer_Is_Timer_فعال_Impl
MPU_x_Timer_Is_Timer_فعال_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGetTimerDaemonTaskHandleImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
MPU_xTimerGetTimerDaemonTaskHandle_Priv
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
}

#د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

بنسټ_Type_t MPU_x_Timer_Generic_Command_From_Task_ثبت( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_Timer_Generic_Command_From_Task_ثبت( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGenericCommandFromTaskImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
MPU_xTimerGenericCommandFromTask_Priv
        b MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTask_Unpriv
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
}

#د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pcTimerGetNameImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_pcTimerGetName_Unpriv
MPU_pcTimerGetName_Priv
        b MPU_pcTimerGetNameImpl
MPU_pcTimerGetName_Unpriv
        svc #SYSTEM_CALL_pcTimerGetName
}

#د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ MPU_v_Timer_سېټ_Reload_ډېرپېښ( TimerHandle_t xTimer,
                              ثابت بنسټ_Type_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Timer_سېټ_Reload_ډېرپېښ( TimerHandle_t xTimer,
                                    ثابت بنسټ_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Timer_سېټ_Reload_ډېرپېښ_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_v_Timer_سېټ_Reload_ډېرپېښ_Unpriv
MPU_v_Timer_سېټ_Reload_ډېرپېښ_Priv
        b MPU_v_Timer_سېټ_Reload_ډېرپېښ_Impl
MPU_v_Timer_سېټ_Reload_ډېرپېښ_Unpriv
        svc #SYSTEM_CALL_vTimerSetReloadMode
}

#د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

بنسټ_Type_t MPU_x_Timer_Get_Reload_ډېرپېښ( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_Timer_Get_Reload_ډېرپېښ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Get_Reload_ډېرپېښ_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_Timer_Get_Reload_ډېرپېښ_Unpriv
MPU_x_Timer_Get_Reload_ډېرپېښ_Priv
        b MPU_x_Timer_Get_Reload_ډېرپېښ_Impl
MPU_x_Timer_Get_Reload_ډېرپېښ_Unpriv
        svc #SYSTEM_CALL_xTimerGetReloadMode
}

#د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

UBaseType_t MPU_ux_Timer_Get_Reload_ډېرپېښ( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Timer_Get_Reload_ډېرپېښ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Timer_Get_Reload_ډېرپېښ_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ux_Timer_Get_Reload_ډېرپېښ_Unpriv
MPU_ux_Timer_Get_Reload_ډېرپېښ_Priv
        b MPU_ux_Timer_Get_Reload_ډېرپېښ_Impl
MPU_ux_Timer_Get_Reload_ډېرپېښ_Unpriv
        svc #SYSTEM_CALL_uxTimerGetReloadMode
}

#د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGetPeriodImpl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_xTimerGetPeriod_Unpriv
MPU_xTimerGetPeriod_Priv
        b MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriod_Unpriv
        svc #SYSTEM_CALL_xTimerGetPeriod
}

#د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TickType_t MPU_x_Timer_Get_Expiry_وخت( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Timer_Get_Expiry_وخت( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Get_Expiry_وخت_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_Timer_Get_Expiry_وخت_Unpriv
MPU_x_Timer_Get_Expiry_وخت_Priv
        b MPU_x_Timer_Get_Expiry_وخت_Impl
MPU_x_Timer_Get_Expiry_وخت_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بټونه_t MPU_x_Event_ډله_Wait_بټونه_ثبت( ثابت x_Event_ډله_Wait_بټونه_Params_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm Event_بټونه_t MPU_x_Event_ډله_Wait_بټونه_ثبت( ثابت x_Event_ډله_Wait_بټونه_Params_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_ډله_Wait_بټونه_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_Event_ډله_Wait_بټونه_Unpriv
MPU_x_Event_ډله_Wait_بټونه_Priv
        b MPU_x_Event_ډله_Wait_بټونه_Impl
MPU_x_Event_ډله_Wait_بټونه_Unpriv
        svc #SYSTEM_CALL_xEventGroupWaitBits
}

#د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بټونه_t MPU_x_Event_ډله_Clear_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                      ثابت Event_بټونه_t ux_بټونه_منزل_Clear ) FREERTOS_SYSTEM_CALL;

__asm Event_بټونه_t MPU_x_Event_ډله_Clear_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                            ثابت Event_بټونه_t ux_بټونه_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_ډله_Clear_بټونه_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_Event_ډله_Clear_بټونه_Unpriv
MPU_x_Event_ډله_Clear_بټونه_Priv
        b MPU_x_Event_ډله_Clear_بټونه_Impl
MPU_x_Event_ډله_Clear_بټونه_Unpriv
        svc #SYSTEM_CALL_xEventGroupClearBits
}

#د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بټونه_t MPU_x_Event_ډله_سېټ_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                    ثابت Event_بټونه_t ux_بټونه_منزل_سېټ ) FREERTOS_SYSTEM_CALL;

__asm Event_بټونه_t MPU_x_Event_ډله_سېټ_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                          ثابت Event_بټونه_t ux_بټونه_منزل_سېټ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_ډله_سېټ_بټونه_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_Event_ډله_سېټ_بټونه_Unpriv
MPU_x_Event_ډله_سېټ_بټونه_Priv
        b MPU_x_Event_ډله_سېټ_بټونه_Impl
MPU_x_Event_ډله_سېټ_بټونه_Unpriv
        svc #SYSTEM_CALL_xEventGroupSetBits
}

#د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بټونه_t MPU_x_Event_ډله_Sync( Event_ډله_Handle_t x_Event_ډله,
                                 ثابت Event_بټونه_t ux_بټونه_منزل_سېټ,
                                 ثابت Event_بټونه_t ux_بټونه_منزل_Wait_For,
                                 TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm Event_بټونه_t MPU_x_Event_ډله_Sync( Event_ډله_Handle_t x_Event_ډله,
                                       ثابت Event_بټونه_t ux_بټونه_منزل_سېټ,
                                       ثابت Event_بټونه_t ux_بټونه_منزل_Wait_For,
                                       TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_ډله_Sync_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_Event_ډله_Sync_Unpriv
MPU_x_Event_ډله_Sync_Priv
        b MPU_x_Event_ډله_Sync_Impl
MPU_x_Event_ډله_Sync_Unpriv
        svc #SYSTEM_CALL_xEventGroupSync
}

#د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_ډله_Get_شمېره( فراغ * x_Event_ډله ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_ډله_Get_شمېره( فراغ * x_Event_ډله ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Event_ډله_Get_شمېره_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_ux_Event_ډله_Get_شمېره_Unpriv
MPU_ux_Event_ډله_Get_شمېره_Priv
        b MPU_ux_Event_ډله_Get_شمېره_Impl
MPU_ux_Event_ډله_Get_شمېره_Unpriv
        svc #SYSTEM_CALL_uxEventGroupGetNumber
}

#د_که_پای /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

فراغ MPU_v_Event_ډله_سېټ_شمېره( فراغ * x_Event_ډله,
                               UBaseType_t ux_Event_ډله_شمېره ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Event_ډله_سېټ_شمېره( فراغ * x_Event_ډله,
                                     UBaseType_t ux_Event_ډله_شمېره ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Event_ډله_سېټ_شمېره_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_v_Event_ډله_سېټ_شمېره_Unpriv
MPU_v_Event_ډله_سېټ_شمېره_Priv
        b MPU_v_Event_ډله_سېټ_شمېره_Impl
MPU_v_Event_ډله_سېټ_شمېره_Unpriv
        svc #SYSTEM_CALL_vEventGroupSetNumber
}

#د_که_پای /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_بهیر_BUFFERS == 1 )

size_t MPU_x_بهیر_بفر_Send( بهیر_بفر_Handle_t x_بهیر_بفر,
                              ثابت فراغ * pv_Tx_معلومات,
                              size_t x_معلومات_اوږدتیا_بایټونه,
                              TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_بهیر_بفر_Send( بهیر_بفر_Handle_t x_بهیر_بفر,
                                    ثابت فراغ * pv_Tx_معلومات,
                                    size_t x_معلومات_اوږدتیا_بایټونه,
                                    TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_بهیر_بفر_Send_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_بهیر_بفر_Send_Unpriv
MPU_x_بهیر_بفر_Send_Priv
        b MPU_x_بهیر_بفر_Send_Impl
MPU_x_بهیر_بفر_Send_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSend
}

#د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_بهیر_BUFFERS == 1 )

size_t MPU_x_بهیر_بفر_Receive( بهیر_بفر_Handle_t x_بهیر_بفر,
                                 فراغ * pv_Rx_معلومات,
                                 size_t x_بفر_اوږدتیا_بایټونه,
                                 TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_بهیر_بفر_Receive( بهیر_بفر_Handle_t x_بهیر_بفر,
                                       فراغ * pv_Rx_معلومات,
                                       size_t x_بفر_اوږدتیا_بایټونه,
                                       TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_بهیر_بفر_Receive_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_بهیر_بفر_Receive_Unpriv
MPU_x_بهیر_بفر_Receive_Priv
        b MPU_x_بهیر_بفر_Receive_Impl
MPU_x_بهیر_بفر_Receive_Unpriv
        svc #SYSTEM_CALL_xStreamBufferReceive
}

#د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_بهیر_BUFFERS == 1 )

بنسټ_Type_t MPU_x_بهیر_بفر_Is_ډک( بهیر_بفر_Handle_t x_بهیر_بفر ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_بهیر_بفر_Is_ډک( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_بهیر_بفر_Is_ډک_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_بهیر_بفر_Is_ډک_Unpriv
MPU_x_بهیر_بفر_Is_ډک_Priv
        b MPU_x_بهیر_بفر_Is_ډک_Impl
MPU_x_بهیر_بفر_Is_ډک_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_بهیر_BUFFERS == 1 )

بنسټ_Type_t MPU_x_بهیر_بفر_Is_تشه( بهیر_بفر_Handle_t x_بهیر_بفر ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_بهیر_بفر_Is_تشه( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_بهیر_بفر_Is_تشه_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_بهیر_بفر_Is_تشه_Unpriv
MPU_x_بهیر_بفر_Is_تشه_Priv
        b MPU_x_بهیر_بفر_Is_تشه_Impl
MPU_x_بهیر_بفر_Is_تشه_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_بهیر_BUFFERS == 1 )

size_t MPU_x_بهیر_بفر_Spaces_شته( بهیر_بفر_Handle_t x_بهیر_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_بهیر_بفر_Spaces_شته( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_بهیر_بفر_Spaces_شته_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_بهیر_بفر_Spaces_شته_Unpriv
MPU_x_بهیر_بفر_Spaces_شته_Priv
        b MPU_x_بهیر_بفر_Spaces_شته_Impl
MPU_x_بهیر_بفر_Spaces_شته_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
}

#د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_بهیر_BUFFERS == 1 )

size_t MPU_x_بهیر_بفر_بایټونه_شته( بهیر_بفر_Handle_t x_بهیر_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_بهیر_بفر_بایټونه_شته( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_بهیر_بفر_بایټونه_شته_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_بهیر_بفر_بایټونه_شته_Unpriv
MPU_x_بهیر_بفر_بایټونه_شته_Priv
        b MPU_x_بهیر_بفر_بایټونه_شته_Impl
MPU_x_بهیر_بفر_بایټونه_شته_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_بهیر_BUFFERS == 1 )

بنسټ_Type_t MPU_x_بهیر_بفر_سېټ_Trigger_Level( بهیر_بفر_Handle_t x_بهیر_بفر,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm بنسټ_Type_t MPU_x_بهیر_بفر_سېټ_Trigger_Level( بهیر_بفر_Handle_t x_بهیر_بفر,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_بهیر_بفر_سېټ_Trigger_Level_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_بهیر_بفر_سېټ_Trigger_Level_Unpriv
MPU_x_بهیر_بفر_سېټ_Trigger_Level_Priv
        b MPU_x_بهیر_بفر_سېټ_Trigger_Level_Impl
MPU_x_بهیر_بفر_سېټ_Trigger_Level_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
}

#د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_بهیر_BUFFERS == 1 )

size_t MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه( بهیر_بفر_Handle_t x_بهیر_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه( بهیر_بفر_Handle_t x_بهیر_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه_Impl

    ټېل {r0}
    mrs r0, control
    tst r0, #1
    راوباسه {r0}
    bne MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه_Unpriv
MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه_Priv
        b MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه_Impl
MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#د_که_پای /* configUSE_MPU_WRAPPERS_V1 == 0 */
