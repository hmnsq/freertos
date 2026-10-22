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
#تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "queue.h"
#شامل "timers.h"
#شامل "event_groups.h"
#شامل "stream_buffer.h"
#شامل "mpu_prototypes.h"
#شامل "mpu_syscall_numbers.h"

#تعریف_منسوخ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

#اگر ( INCLUDE_xTaskDelayUntil == 1 )

بنیاد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_وقت,
                                ثابت TickType_t x_وقت_Increment ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_وقت,
                                      ثابت TickType_t x_وقت_Increment ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_xTaskDelayUntilImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_xTaskDelayUntil_Unpriv
MPU_xTaskDelayUntil_Priv
        b MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntil_Unpriv
        svc #SYSTEM_CALL_xTaskDelayUntil
}

#اگر_ختم /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( INCLUDE_xTaskAbortDelay == 1 )

بنیاد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_xTaskAbortDelayImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_xTaskAbortDelay_Unpriv
MPU_xTaskAbortDelay_Priv
        b MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelay_Unpriv
        svc #SYSTEM_CALL_xTaskAbortDelay
}

#اگر_ختم /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( INCLUDE_vTaskDelay == 1 )

خالی MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_vTaskDelayImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_vTaskDelay_Unpriv
MPU_vTaskDelay_Priv
        b MPU_vTaskDelayImpl
MPU_vTaskDelay_Unpriv
        svc #SYSTEM_CALL_vTaskDelay
}

#اگر_ختم /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( INCLUDE_ux_Task_ترجیح_Get == 1 )

UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ux_Task_ترجیح_Get_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ux_Task_ترجیح_Get_Unpriv
MPU_ux_Task_ترجیح_Get_Priv
        b MPU_ux_Task_ترجیح_Get_Impl
MPU_ux_Task_ترجیح_Get_Unpriv
        svc #SYSTEM_CALL_uxTaskPriorityGet
}

#اگر_ختم /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_eTaskGetStateImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_eTaskGetState_Unpriv
MPU_eTaskGetState_Priv
        b MPU_eTaskGetStateImpl
MPU_eTaskGetState_Unpriv
        svc #SYSTEM_CALL_eTaskGetState
}

#اگر_ختم /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TRACE_FACILITY == 1 )

خالی MPU_vTaskGetInfo( TaskHandle_t xTask,
                       Task_حالت_t * px_Task_حالت,
                       بنیاد_Type_t x_Get_Free_ڈھیر_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_vTaskGetInfo( TaskHandle_t xTask,
                             Task_حالت_t * px_Task_حالت,
                             بنیاد_Type_t x_Get_Free_ڈھیر_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_vTaskGetInfoImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_vTaskGetInfo_Unpriv
MPU_vTaskGetInfo_Priv
        b MPU_vTaskGetInfoImpl
MPU_vTaskGetInfo_Unpriv
        svc #SYSTEM_CALL_vTaskGetInfo
}

#اگر_ختم /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( خالی ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( خالی ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_xTaskGetIdleTaskHandleImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
MPU_xTaskGetIdleTaskHandle_Priv
        b MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
}

#اگر_ختم /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( INCLUDE_vTaskSuspend == 1 )

خالی MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_vTaskSuspendImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_vTaskSuspend_Unpriv
MPU_vTaskSuspend_Priv
        b MPU_vTaskSuspendImpl
MPU_vTaskSuspend_Unpriv
        svc #SYSTEM_CALL_vTaskSuspend
}

#اگر_ختم /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( INCLUDE_vTaskSuspend == 1 )

خالی MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_vTaskResumeImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_vTaskResume_Unpriv
MPU_vTaskResume_Priv
        b MPU_vTaskResumeImpl
MPU_vTaskResume_Unpriv
        svc #SYSTEM_CALL_vTaskResume
}

#اگر_ختم /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_گنتی( خالی ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_گنتی( خالی ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_Task_Get_Tick_گنتی_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Task_Get_Tick_گنتی_Unpriv
MPU_x_Task_Get_Tick_گنتی_Priv
        b MPU_x_Task_Get_Tick_گنتی_Impl
MPU_x_Task_Get_Tick_گنتی_Unpriv
        svc #SYSTEM_CALL_xTaskGetTickCount
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Task_Get_نمبر_کا_Tasks( خالی ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_نمبر_کا_Tasks( خالی ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ux_Task_Get_نمبر_کا_Tasks_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ux_Task_Get_نمبر_کا_Tasks_Unpriv
MPU_ux_Task_Get_نمبر_کا_Tasks_Priv
        b MPU_ux_Task_Get_نمبر_کا_Tasks_Impl
MPU_ux_Task_Get_نمبر_کا_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#اگر ( config_GENERATE_تسلسل_وقت_STATS == 1 )

config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_شمار( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_شمار( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ul_Task_Get_تسلسل_وقت_شمار_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ul_Task_Get_تسلسل_وقت_شمار_Unpriv
MPU_ul_Task_Get_تسلسل_وقت_شمار_Priv
        b MPU_ul_Task_Get_تسلسل_وقت_شمار_Impl
MPU_ul_Task_Get_تسلسل_وقت_شمار_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_GENERATE_تسلسل_وقت_STATS == 1 )

config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_Percent( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_Percent( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ul_Task_Get_تسلسل_وقت_Percent_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ul_Task_Get_تسلسل_وقت_Percent_Unpriv
MPU_ul_Task_Get_تسلسل_وقت_Percent_Priv
        b MPU_ul_Task_Get_تسلسل_وقت_Percent_Impl
MPU_ul_Task_Get_تسلسل_وقت_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( ( config_GENERATE_تسلسل_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent( خالی ) FREERTOS_SYSTEM_CALL;

__asm config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent( خالی ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent_Unpriv
MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent_Priv
        b MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent_Impl
MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#اگر ( ( config_GENERATE_تسلسل_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار( خالی ) FREERTOS_SYSTEM_CALL;

__asm config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار( خالی ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار_Unpriv
MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار_Priv
        b MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار_Impl
MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )

خالی MPU_v_Task_سیٹ_Application_Task_لیبل( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_v_Task_سیٹ_Application_Task_لیبل( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_v_Task_سیٹ_Application_Task_لیبل_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_v_Task_سیٹ_Application_Task_لیبل_Unpriv
MPU_v_Task_سیٹ_Application_Task_لیبل_Priv
        b MPU_v_Task_سیٹ_Application_Task_لیبل_Impl
MPU_v_Task_سیٹ_Application_Task_لیبل_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#اگر_ختم /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )

TaskHookFunction_t MPU_x_Task_Get_Application_Task_لیبل( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_x_Task_Get_Application_Task_لیبل( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_Task_Get_Application_Task_لیبل_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Task_Get_Application_Task_لیبل_Unpriv
MPU_x_Task_Get_Application_Task_لیبل_Priv
        b MPU_x_Task_Get_Application_Task_لیبل_Impl
MPU_x_Task_Get_Application_Task_لیبل_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#اگر_ختم /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_عدد_THREAD_LOCAL_STORAGE_اشارے != 0 )

خالی MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_سیٹ,
                                            بنیاد_Type_t x_اشاریہ,
                                            خالی * pv_قدر ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_سیٹ,
                                                  بنیاد_Type_t x_اشاریہ,
                                                  خالی * pv_قدر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Unpriv
MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Priv
        b MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Impl
MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Unpriv
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
}

#اگر_ختم /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#اگر ( config_عدد_THREAD_LOCAL_STORAGE_اشارے != 0 )

خالی * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_Query,
                                               بنیاد_Type_t x_اشاریہ ) FREERTOS_SYSTEM_CALL;

__asm خالی * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_Query,
                                                     بنیاد_Type_t x_اشاریہ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Unpriv
MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Priv
        b MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Impl
MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Unpriv
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
}

#اگر_ختم /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                      ثابت UBaseType_t ux_Array_سائز,
                                      config_تسلسل_وقت_شمار_TYPE * ثابت pul_کل_تسلسل_وقت ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                            ثابت UBaseType_t ux_Array_سائز,
                                            config_تسلسل_وقت_شمار_TYPE * ثابت pul_کل_تسلسل_وقت ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_uxTaskGetSystemStateImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_uxTaskGetSystemState_Unpriv
MPU_uxTaskGetSystemState_Priv
        b MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemState_Unpriv
        svc #SYSTEM_CALL_uxTaskGetSystemState
}

#اگر_ختم /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Unpriv
MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Priv
        b MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Impl
MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
}

#اگر_ختم /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark2 == 1 )

config_ڈھیر_گہرائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_ڈھیر_گہرائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Unpriv
MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Priv
        b MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Impl
MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
}

#اگر_ختم /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( خالی ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( خالی ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_xTaskGetCurrentTaskHandleImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
MPU_xTaskGetCurrentTaskHandle_Priv
        b MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
}

#اگر_ختم /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#اگر ( INCLUDE_xTaskGetSchedulerState == 1 )

بنیاد_Type_t MPU_xTaskGetSchedulerState( خالی ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_xTaskGetSchedulerState( خالی ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_xTaskGetSchedulerStateImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_xTaskGetSchedulerState_Unpriv
MPU_xTaskGetSchedulerState_Priv
        b MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerState_Unpriv
        svc #SYSTEM_CALL_xTaskGetSchedulerState
}

#اگر_ختم /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

خالی MPU_v_Task_سیٹ_وقت_برآمد_State( وقت_برآمد_t * ثابت px_وقت_برآمد ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_v_Task_سیٹ_وقت_برآمد_State( وقت_برآمد_t * ثابت px_وقت_برآمد ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_v_Task_سیٹ_وقت_برآمد_State_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_v_Task_سیٹ_وقت_برآمد_State_Unpriv
MPU_v_Task_سیٹ_وقت_برآمد_State_Priv
        b MPU_v_Task_سیٹ_وقت_برآمد_State_Impl
MPU_v_Task_سیٹ_وقت_برآمد_State_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

بنیاد_Type_t MPU_x_Task_Check_For_وقت_برآمد( وقت_برآمد_t * ثابت px_وقت_برآمد,
                                     TickType_t * ثابت px_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_Task_Check_For_وقت_برآمد( وقت_برآمد_t * ثابت px_وقت_برآمد,
                                     TickType_t * ثابت px_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_Task_Check_For_وقت_برآمد_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Task_Check_For_وقت_برآمد_Unpriv
MPU_x_Task_Check_For_وقت_برآمد_Priv
        b MPU_x_Task_Check_For_وقت_برآمد_Impl
MPU_x_Task_Check_For_وقت_برآمد_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

بنیاد_Type_t MPU_x_Task_Generic_Notify_اندراج( ثابت xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_Task_Generic_Notify_اندراج( ثابت xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_xTaskGenericNotifyImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_xTaskGenericNotify_Unpriv
MPU_xTaskGenericNotify_Priv
        b MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotify_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotify
}

#اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

بنیاد_Type_t MPU_x_Task_Generic_Notify_Wait_اندراج( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_Task_Generic_Notify_Wait_اندراج( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_xTaskGenericNotifyWaitImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_xTaskGenericNotifyWait_Unpriv
MPU_xTaskGenericNotifyWait_Priv
        b MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWait_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
}

#اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاریہ_مقصد_Wait_On,
                                      بنیاد_Type_t x_Clear_گنتی_On_Exit,
                                      TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاریہ_مقصد_Wait_On,
                                            بنیاد_Type_t x_Clear_گنتی_On_Exit,
                                            TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ulTaskGenericNotifyTakeImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
MPU_ulTaskGenericNotifyTake_Priv
        b MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTake_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
}

#اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

بنیاد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t ux_اشاریہ_مقصد_Clear ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t ux_اشاریہ_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_xTaskGenericNotifyStateClearImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
MPU_xTaskGenericNotifyStateClear_Priv
        b MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClear_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
}

#اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                            UBaseType_t ux_اشاریہ_مقصد_Clear,
                                            uint32_t ul_بٹ_مقصد_Clear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                  UBaseType_t ux_اشاریہ_مقصد_Clear,
                                                  uint32_t ul_بٹ_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ul_Task_Generic_Notify_قدر_Clear_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ul_Task_Generic_Notify_قدر_Clear_Unpriv
MPU_ul_Task_Generic_Notify_قدر_Clear_Priv
        b MPU_ul_Task_Generic_Notify_قدر_Clear_Impl
MPU_ul_Task_Generic_Notify_قدر_Clear_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
}

#اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

بنیاد_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                  ثابت خالی * ثابت pv_شے_مقصد_قطار,
                                  TickType_t x_Ticks_مقصد_Wait,
                                  ثابت بنیاد_Type_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                        ثابت خالی * ثابت pv_شے_مقصد_قطار,
                                        TickType_t x_Ticks_مقصد_Wait,
                                        ثابت بنیاد_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_قطار_Generic_Send_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
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
    خارجی MPU_ux_قطار_Messages_انتظار_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ux_قطار_Messages_انتظار_Unpriv
MPU_ux_قطار_Messages_انتظار_Priv
        b MPU_ux_قطار_Messages_انتظار_Impl
MPU_ux_قطار_Messages_انتظار_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ux_قطار_Spaces_دستیاب_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ux_قطار_Spaces_دستیاب_Unpriv
MPU_ux_قطار_Spaces_دستیاب_Priv
        b MPU_ux_قطار_Spaces_دستیاب_Impl
MPU_ux_قطار_Spaces_دستیاب_Unpriv
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
}
/*-----------------------------------------------------------*/

بنیاد_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                              خالی * ثابت pv_بفر,
                              TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                                    خالی * ثابت pv_بفر,
                                    TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_قطار_Receive_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_قطار_Receive_Unpriv
MPU_x_قطار_Receive_Priv
        b MPU_x_قطار_Receive_Impl
MPU_x_قطار_Receive_Unpriv
        svc #SYSTEM_CALL_xQueueReceive
}
/*-----------------------------------------------------------*/

بنیاد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                           خالی * ثابت pv_بفر,
                           TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                                 خالی * ثابت pv_بفر,
                                 TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_قطار_Peek_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_قطار_Peek_Unpriv
MPU_x_قطار_Peek_Priv
        b MPU_x_قطار_Peek_Impl
MPU_x_قطار_Peek_Unpriv
        svc #SYSTEM_CALL_xQueuePeek
}
/*-----------------------------------------------------------*/

بنیاد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                    TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                          TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_قطار_Semaphore_Take_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_قطار_Semaphore_Take_Unpriv
MPU_x_قطار_Semaphore_Take_Priv
        b MPU_x_قطار_Semaphore_Take_Impl
MPU_x_قطار_Semaphore_Take_Unpriv
        svc #SYSTEM_CALL_xQueueSemaphoreTake
}
/*-----------------------------------------------------------*/

#اگر ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_قطار_Get_Mutex_Holder_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_قطار_Get_Mutex_Holder_Unpriv
MPU_x_قطار_Get_Mutex_Holder_Priv
        b MPU_x_قطار_Get_Mutex_Holder_Impl
MPU_x_قطار_Get_Mutex_Holder_Unpriv
        svc #SYSTEM_CALL_xQueueGetMutexHolder
}

#اگر_ختم /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_RECURSIVE_MUTEXES == 1 )

بنیاد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                         TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                               TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_قطار_Take_Mutex_Recursive_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_قطار_Take_Mutex_Recursive_Unpriv
MPU_x_قطار_Take_Mutex_Recursive_Priv
        b MPU_x_قطار_Take_Mutex_Recursive_Impl
MPU_x_قطار_Take_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
}

#اگر_ختم /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_RECURSIVE_MUTEXES == 1 )

بنیاد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_قطار_Give_Mutex_Recursive_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_قطار_Give_Mutex_Recursive_Unpriv
MPU_x_قطار_Give_Mutex_Recursive_Priv
        b MPU_x_قطار_Give_Mutex_Recursive_Impl
MPU_x_قطار_Give_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
}

#اگر_ختم /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_قطار_SETS == 1 )

قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                ثابت TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                      ثابت TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_قطار_Select_From_سیٹ_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_قطار_Select_From_سیٹ_Unpriv
MPU_x_قطار_Select_From_سیٹ_Priv
        b MPU_x_قطار_Select_From_سیٹ_Impl
MPU_x_قطار_Select_From_سیٹ_Unpriv
        svc #SYSTEM_CALL_xQueueSelectFromSet
}

#اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_قطار_SETS == 1 )

بنیاد_Type_t MPU_x_قطار_جوڑو_مقصد_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                               قطار_سیٹ_Handle_t x_قطار_سیٹ ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_قطار_جوڑو_مقصد_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                     قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_قطار_جوڑو_مقصد_سیٹ_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_قطار_جوڑو_مقصد_سیٹ_Unpriv
MPU_x_قطار_جوڑو_مقصد_سیٹ_Priv
        b MPU_x_قطار_جوڑو_مقصد_سیٹ_Impl
MPU_x_قطار_جوڑو_مقصد_سیٹ_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_قطار_REGISTRY_سائز > 0 )

خالی MPU_v_قطار_جوڑو_مقصد_Registry( قطار_Handle_t x_قطار,
                              ثابت حرف * pcName ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_v_قطار_جوڑو_مقصد_Registry( قطار_Handle_t x_قطار,
                                    ثابت حرف * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_v_قطار_جوڑو_مقصد_Registry_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_v_قطار_جوڑو_مقصد_Registry_Unpriv
MPU_v_قطار_جوڑو_مقصد_Registry_Priv
        b MPU_v_قطار_جوڑو_مقصد_Registry_Impl
MPU_v_قطار_جوڑو_مقصد_Registry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#اگر_ختم /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#اگر ( config_قطار_REGISTRY_سائز > 0 )

خالی MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_v_قطار_Unregister_قطار_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_v_قطار_Unregister_قطار_Unpriv
MPU_v_قطار_Unregister_قطار_Priv
        b MPU_v_قطار_Unregister_قطار_Impl
MPU_v_قطار_Unregister_قطار_Unpriv
        svc #SYSTEM_CALL_vQueueUnregisterQueue
}

#اگر_ختم /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#اگر ( config_قطار_REGISTRY_سائز > 0 )

ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) FREERTOS_SYSTEM_CALL;

__asm ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_pc_قطار_Get_Name_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_pc_قطار_Get_Name_Unpriv
MPU_pc_قطار_Get_Name_Priv
        b MPU_pc_قطار_Get_Name_Impl
MPU_pc_قطار_Get_Name_Unpriv
        svc #SYSTEM_CALL_pcQueueGetName
}

#اگر_ختم /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TIMERS == 1 )

خالی * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm خالی * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_pvTimerGetTimerIDImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_pvTimerGetTimerID_Unpriv
MPU_pvTimerGetTimerID_Priv
        b MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerID_Unpriv
        svc #SYSTEM_CALL_pvTimerGetTimerID
}

#اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TIMERS == 1 )

خالی MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                           خالی * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                                 خالی * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_v_Timer_سیٹ_Timer_IDImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_v_Timer_سیٹ_Timer_ID_Unpriv
MPU_v_Timer_سیٹ_Timer_ID_Priv
        b MPU_v_Timer_سیٹ_Timer_IDImpl
MPU_v_Timer_سیٹ_Timer_ID_Unpriv
        svc #SYSTEM_CALL_vTimerSetTimerID
}

#اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TIMERS == 1 )

بنیاد_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_Timer_Is_Timer_فعال_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Timer_Is_Timer_فعال_Unpriv
MPU_x_Timer_Is_Timer_فعال_Priv
        b MPU_x_Timer_Is_Timer_فعال_Impl
MPU_x_Timer_Is_Timer_فعال_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( خالی ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( خالی ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_xTimerGetTimerDaemonTaskHandleImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
MPU_xTimerGetTimerDaemonTaskHandle_Priv
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
}

#اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TIMERS == 1 )

بنیاد_Type_t MPU_x_Timer_Generic_Command_From_Task_اندراج( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_Timer_Generic_Command_From_Task_اندراج( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_xTimerGenericCommandFromTaskImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
MPU_xTimerGenericCommandFromTask_Priv
        b MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTask_Unpriv
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
}

#اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TIMERS == 1 )

ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_pcTimerGetNameImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_pcTimerGetName_Unpriv
MPU_pcTimerGetName_Priv
        b MPU_pcTimerGetNameImpl
MPU_pcTimerGetName_Unpriv
        svc #SYSTEM_CALL_pcTimerGetName
}

#اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TIMERS == 1 )

خالی MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                              ثابت بنیاد_Type_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                                    ثابت بنیاد_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_v_Timer_سیٹ_Reload_منوال_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_v_Timer_سیٹ_Reload_منوال_Unpriv
MPU_v_Timer_سیٹ_Reload_منوال_Priv
        b MPU_v_Timer_سیٹ_Reload_منوال_Impl
MPU_v_Timer_سیٹ_Reload_منوال_Unpriv
        svc #SYSTEM_CALL_vTimerSetReloadMode
}

#اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TIMERS == 1 )

بنیاد_Type_t MPU_x_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_Timer_Get_Reload_منوال_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Timer_Get_Reload_منوال_Unpriv
MPU_x_Timer_Get_Reload_منوال_Priv
        b MPU_x_Timer_Get_Reload_منوال_Impl
MPU_x_Timer_Get_Reload_منوال_Unpriv
        svc #SYSTEM_CALL_xTimerGetReloadMode
}

#اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TIMERS == 1 )

UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ux_Timer_Get_Reload_منوال_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ux_Timer_Get_Reload_منوال_Unpriv
MPU_ux_Timer_Get_Reload_منوال_Priv
        b MPU_ux_Timer_Get_Reload_منوال_Impl
MPU_ux_Timer_Get_Reload_منوال_Unpriv
        svc #SYSTEM_CALL_uxTimerGetReloadMode
}

#اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_xTimerGetPeriodImpl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_xTimerGetPeriod_Unpriv
MPU_xTimerGetPeriod_Priv
        b MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriod_Unpriv
        svc #SYSTEM_CALL_xTimerGetPeriod
}

#اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_TIMERS == 1 )

TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_Timer_Get_Expiry_وقت_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Timer_Get_Expiry_وقت_Unpriv
MPU_x_Timer_Get_Expiry_وقت_Priv
        b MPU_x_Timer_Get_Expiry_وقت_Impl
MPU_x_Timer_Get_Expiry_وقت_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_EVENT_GROUPS == 1 )

Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_اندراج( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_اندراج( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_Event_گروہ_Wait_بٹ_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Event_گروہ_Wait_بٹ_Unpriv
MPU_x_Event_گروہ_Wait_بٹ_Priv
        b MPU_x_Event_گروہ_Wait_بٹ_Impl
MPU_x_Event_گروہ_Wait_بٹ_Unpriv
        svc #SYSTEM_CALL_xEventGroupWaitBits
}

#اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_EVENT_GROUPS == 1 )

Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                      ثابت Event_بٹ_t ux_بٹ_مقصد_Clear ) FREERTOS_SYSTEM_CALL;

__asm Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                            ثابت Event_بٹ_t ux_بٹ_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_Event_گروہ_Clear_بٹ_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Event_گروہ_Clear_بٹ_Unpriv
MPU_x_Event_گروہ_Clear_بٹ_Priv
        b MPU_x_Event_گروہ_Clear_بٹ_Impl
MPU_x_Event_گروہ_Clear_بٹ_Unpriv
        svc #SYSTEM_CALL_xEventGroupClearBits
}

#اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_EVENT_GROUPS == 1 )

Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                    ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ ) FREERTOS_SYSTEM_CALL;

__asm Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                          ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_Event_گروہ_سیٹ_بٹ_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Event_گروہ_سیٹ_بٹ_Unpriv
MPU_x_Event_گروہ_سیٹ_بٹ_Priv
        b MPU_x_Event_گروہ_سیٹ_بٹ_Impl
MPU_x_Event_گروہ_سیٹ_بٹ_Unpriv
        svc #SYSTEM_CALL_xEventGroupSetBits
}

#اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( configUSE_EVENT_GROUPS == 1 )

Event_بٹ_t MPU_x_Event_گروہ_Sync( Event_گروہ_Handle_t x_Event_گروہ,
                                 ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ,
                                 ثابت Event_بٹ_t ux_بٹ_مقصد_Wait_For,
                                 TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm Event_بٹ_t MPU_x_Event_گروہ_Sync( Event_گروہ_Handle_t x_Event_گروہ,
                                       ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ,
                                       ثابت Event_بٹ_t ux_بٹ_مقصد_Wait_For,
                                       TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_Event_گروہ_Sync_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Event_گروہ_Sync_Unpriv
MPU_x_Event_گروہ_Sync_Priv
        b MPU_x_Event_گروہ_Sync_Impl
MPU_x_Event_گروہ_Sync_Unpriv
        svc #SYSTEM_CALL_xEventGroupSync
}

#اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_گروہ_Get_نمبر( خالی * x_Event_گروہ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_گروہ_Get_نمبر( خالی * x_Event_گروہ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_ux_Event_گروہ_Get_نمبر_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ux_Event_گروہ_Get_نمبر_Unpriv
MPU_ux_Event_گروہ_Get_نمبر_Priv
        b MPU_ux_Event_گروہ_Get_نمبر_Impl
MPU_ux_Event_گروہ_Get_نمبر_Unpriv
        svc #SYSTEM_CALL_uxEventGroupGetNumber
}

#اگر_ختم /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#اگر ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

خالی MPU_v_Event_گروہ_سیٹ_نمبر( خالی * x_Event_گروہ,
                               UBaseType_t ux_Event_گروہ_نمبر ) FREERTOS_SYSTEM_CALL;

__asm خالی MPU_v_Event_گروہ_سیٹ_نمبر( خالی * x_Event_گروہ,
                                     UBaseType_t ux_Event_گروہ_نمبر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_v_Event_گروہ_سیٹ_نمبر_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_v_Event_گروہ_سیٹ_نمبر_Unpriv
MPU_v_Event_گروہ_سیٹ_نمبر_Priv
        b MPU_v_Event_گروہ_سیٹ_نمبر_Impl
MPU_v_Event_گروہ_سیٹ_نمبر_Unpriv
        svc #SYSTEM_CALL_vEventGroupSetNumber
}

#اگر_ختم /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_دھارا_BUFFERS == 1 )

size_t MPU_x_دھارا_بفر_Send( دھارا_بفر_Handle_t x_دھارا_بفر,
                              ثابت خالی * pv_Tx_ڈیٹا,
                              size_t x_ڈیٹا_لمبائی_بائٹیں,
                              TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_دھارا_بفر_Send( دھارا_بفر_Handle_t x_دھارا_بفر,
                                    ثابت خالی * pv_Tx_ڈیٹا,
                                    size_t x_ڈیٹا_لمبائی_بائٹیں,
                                    TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_دھارا_بفر_Send_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_Send_Unpriv
MPU_x_دھارا_بفر_Send_Priv
        b MPU_x_دھارا_بفر_Send_Impl
MPU_x_دھارا_بفر_Send_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSend
}

#اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_دھارا_BUFFERS == 1 )

size_t MPU_x_دھارا_بفر_Receive( دھارا_بفر_Handle_t x_دھارا_بفر,
                                 خالی * pv_Rx_ڈیٹا,
                                 size_t x_بفر_لمبائی_بائٹیں,
                                 TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_دھارا_بفر_Receive( دھارا_بفر_Handle_t x_دھارا_بفر,
                                       خالی * pv_Rx_ڈیٹا,
                                       size_t x_بفر_لمبائی_بائٹیں,
                                       TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_دھارا_بفر_Receive_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_Receive_Unpriv
MPU_x_دھارا_بفر_Receive_Priv
        b MPU_x_دھارا_بفر_Receive_Impl
MPU_x_دھارا_بفر_Receive_Unpriv
        svc #SYSTEM_CALL_xStreamBufferReceive
}

#اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_دھارا_BUFFERS == 1 )

بنیاد_Type_t MPU_x_دھارا_بفر_Is_بھرا( دھارا_بفر_Handle_t x_دھارا_بفر ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_دھارا_بفر_Is_بھرا( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_دھارا_بفر_Is_بھرا_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_Is_بھرا_Unpriv
MPU_x_دھارا_بفر_Is_بھرا_Priv
        b MPU_x_دھارا_بفر_Is_بھرا_Impl
MPU_x_دھارا_بفر_Is_بھرا_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_دھارا_BUFFERS == 1 )

بنیاد_Type_t MPU_x_دھارا_بفر_Is_خالی_خانے( دھارا_بفر_Handle_t x_دھارا_بفر ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_دھارا_بفر_Is_خالی_خانے( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_دھارا_بفر_Is_خالی_خانے_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_Is_خالی_خانے_Unpriv
MPU_x_دھارا_بفر_Is_خالی_خانے_Priv
        b MPU_x_دھارا_بفر_Is_خالی_خانے_Impl
MPU_x_دھارا_بفر_Is_خالی_خانے_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_دھارا_BUFFERS == 1 )

size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_دھارا_بفر_Spaces_دستیاب_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_Spaces_دستیاب_Unpriv
MPU_x_دھارا_بفر_Spaces_دستیاب_Priv
        b MPU_x_دھارا_بفر_Spaces_دستیاب_Impl
MPU_x_دھارا_بفر_Spaces_دستیاب_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
}

#اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_دھارا_BUFFERS == 1 )

size_t MPU_x_دھارا_بفر_بائٹیں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_دھارا_بفر_بائٹیں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_دھارا_بفر_بائٹیں_دستیاب_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_بائٹیں_دستیاب_Unpriv
MPU_x_دھارا_بفر_بائٹیں_دستیاب_Priv
        b MPU_x_دھارا_بفر_بائٹیں_دستیاب_Impl
MPU_x_دھارا_بفر_بائٹیں_دستیاب_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_دھارا_BUFFERS == 1 )

بنیاد_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm بنیاد_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Unpriv
MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Priv
        b MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Impl
MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
}

#اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر ( config_USE_دھارا_BUFFERS == 1 )

size_t MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں( دھارا_بفر_Handle_t x_دھارا_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجی MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں_Unpriv
MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں_Priv
        b MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں_Impl
MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر_ختم /* configUSE_MPU_WRAPPERS_V1 == 0 */
