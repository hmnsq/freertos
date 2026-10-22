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
#تعریف_کن MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"
#ضمن "mpu_syscall_numbers.h"

#لغو_تعریف MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

#إذا ( INCLUDE_xTaskDelayUntil == 1 )

پایه_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_قبلی_Wake_زمان,
                                ثابت TickType_t x_زمان_Increment ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_قبلی_Wake_زمان,
                                      ثابت TickType_t x_زمان_Increment ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskDelayUntilImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_xTaskDelayUntil_Unpriv
MPU_xTaskDelayUntil_Priv
        b MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntil_Unpriv
        svc #SYSTEM_CALL_xTaskDelayUntil
}

#پایان_اگر /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskAbortDelay == 1 )

پایه_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskAbortDelayImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_xTaskAbortDelay_Unpriv
MPU_xTaskAbortDelay_Priv
        b MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelay_Unpriv
        svc #SYSTEM_CALL_xTaskAbortDelay
}

#پایان_اگر /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskDelay == 1 )

فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskDelayImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_vTaskDelay_Unpriv
MPU_vTaskDelay_Priv
        b MPU_vTaskDelayImpl
MPU_vTaskDelay_Unpriv
        svc #SYSTEM_CALL_vTaskDelay
}

#پایان_اگر /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_اولویت_Get == 1 )

UBaseType_t MPU_ux_Task_اولویت_Get( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_اولویت_Get( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_اولویت_Get_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ux_Task_اولویت_Get_Unpriv
MPU_ux_Task_اولویت_Get_Priv
        b MPU_ux_Task_اولویت_Get_Impl
MPU_ux_Task_اولویت_Get_Unpriv
        svc #SYSTEM_CALL_uxTaskPriorityGet
}

#پایان_اگر /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_eTaskGetStateImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_eTaskGetState_Unpriv
MPU_eTaskGetState_Priv
        b MPU_eTaskGetStateImpl
MPU_eTaskGetState_Unpriv
        svc #SYSTEM_CALL_eTaskGetState
}

#پایان_اگر /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TRACE_FACILITY == 1 )

فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                       Task_وضعیت_t * px_Task_وضعیت,
                       پایه_Type_t x_Get_Free_پشته_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                             Task_وضعیت_t * px_Task_وضعیت,
                             پایه_Type_t x_Get_Free_پشته_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskGetInfoImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_vTaskGetInfo_Unpriv
MPU_vTaskGetInfo_Priv
        b MPU_vTaskGetInfoImpl
MPU_vTaskGetInfo_Unpriv
        svc #SYSTEM_CALL_vTaskGetInfo
}

#پایان_اگر /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetIdleTaskHandleImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
MPU_xTaskGetIdleTaskHandle_Priv
        b MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
}

#پایان_اگر /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskSuspend == 1 )

فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskSuspendImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_vTaskSuspend_Unpriv
MPU_vTaskSuspend_Priv
        b MPU_vTaskSuspendImpl
MPU_vTaskSuspend_Unpriv
        svc #SYSTEM_CALL_vTaskSuspend
}

#پایان_اگر /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskSuspend == 1 )

فراغ MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskResumeImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_vTaskResume_Unpriv
MPU_vTaskResume_Priv
        b MPU_vTaskResumeImpl
MPU_vTaskResume_Unpriv
        svc #SYSTEM_CALL_vTaskResume
}

#پایان_اگر /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_شمار( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_شمار( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Get_Tick_شمار_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_Task_Get_Tick_شمار_Unpriv
MPU_x_Task_Get_Tick_شمار_Priv
        b MPU_x_Task_Get_Tick_شمار_Impl
MPU_x_Task_Get_Tick_شمار_Unpriv
        svc #SYSTEM_CALL_xTaskGetTickCount
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Task_Get_عدد_از_Tasks( فراغ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_عدد_از_Tasks( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_عدد_از_Tasks_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ux_Task_Get_عدد_از_Tasks_Unpriv
MPU_ux_Task_Get_عدد_از_Tasks_Priv
        b MPU_ux_Task_Get_عدد_از_Tasks_Impl
MPU_ux_Task_Get_عدد_از_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#إذا ( config_GENERATE_پیاپی_زمان_STATS == 1 )

config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Counter( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Counter( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_پیاپی_زمان_Counter_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ul_Task_Get_پیاپی_زمان_Counter_Unpriv
MPU_ul_Task_Get_پیاپی_زمان_Counter_Priv
        b MPU_ul_Task_Get_پیاپی_زمان_Counter_Impl
MPU_ul_Task_Get_پیاپی_زمان_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_GENERATE_پیاپی_زمان_STATS == 1 )

config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Percent( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Percent( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_پیاپی_زمان_Percent_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ul_Task_Get_پیاپی_زمان_Percent_Unpriv
MPU_ul_Task_Get_پیاپی_زمان_Percent_Priv
        b MPU_ul_Task_Get_پیاپی_زمان_Percent_Impl
MPU_ul_Task_Get_پیاپی_زمان_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( config_GENERATE_پیاپی_زمان_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent( فراغ ) FREERTOS_SYSTEM_CALL;

__asm config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent_Unpriv
MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent_Priv
        b MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent_Impl
MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( config_GENERATE_پیاپی_زمان_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter( فراغ ) FREERTOS_SYSTEM_CALL;

__asm config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter_Unpriv
MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter_Priv
        b MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter_Impl
MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )

فراغ MPU_v_Task_مجموعه_Application_Task_برچسب( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_مجموعه_Application_Task_برچسب( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_مجموعه_Application_Task_برچسب_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_v_Task_مجموعه_Application_Task_برچسب_Unpriv
MPU_v_Task_مجموعه_Application_Task_برچسب_Priv
        b MPU_v_Task_مجموعه_Application_Task_برچسب_Impl
MPU_v_Task_مجموعه_Application_Task_برچسب_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#پایان_اگر /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )

TaskHookFunction_t MPU_x_Task_Get_Application_Task_برچسب( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_x_Task_Get_Application_Task_برچسب( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Get_Application_Task_برچسب_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_Task_Get_Application_Task_برچسب_Unpriv
MPU_x_Task_Get_Application_Task_برچسب_Priv
        b MPU_x_Task_Get_Application_Task_برچسب_Impl
MPU_x_Task_Get_Application_Task_برچسب_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#پایان_اگر /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها != 0 )

فراغ MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_مجموعه,
                                            پایه_Type_t x_شاخص,
                                            فراغ * pv_مقدار ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_مجموعه,
                                                  پایه_Type_t x_شاخص,
                                                  فراغ * pv_مقدار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر_Unpriv
MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر_Priv
        b MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر_Impl
MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر_Unpriv
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
}

#پایان_اگر /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها != 0 )

فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_Query,
                                               پایه_Type_t x_شاخص ) FREERTOS_SYSTEM_CALL;

__asm فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_Query,
                                                     پایه_Type_t x_شاخص ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر_Unpriv
MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر_Priv
        b MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر_Impl
MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر_Unpriv
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
}

#پایان_اگر /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( Task_وضعیت_t * ثابت px_Task_وضعیت_Array,
                                      ثابت UBaseType_t ux_Array_اندازه,
                                      config_پیاپی_زمان_COUNTER_TYPE * ثابت pul_مجموع_پیاپی_زمان ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( Task_وضعیت_t * ثابت px_Task_وضعیت_Array,
                                            ثابت UBaseType_t ux_Array_اندازه,
                                            config_پیاپی_زمان_COUNTER_TYPE * ثابت pul_مجموع_پیاپی_زمان ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_uxTaskGetSystemStateImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_uxTaskGetSystemState_Unpriv
MPU_uxTaskGetSystemState_Priv
        b MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemState_Unpriv
        svc #SYSTEM_CALL_uxTaskGetSystemState
}

#پایان_اگر /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_پشته_بالا_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_پشته_بالا_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_پشته_بالا_Water_Mark_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ux_Task_Get_پشته_بالا_Water_Mark_Unpriv
MPU_ux_Task_Get_پشته_بالا_Water_Mark_Priv
        b MPU_ux_Task_Get_پشته_بالا_Water_Mark_Impl
MPU_ux_Task_Get_پشته_بالا_Water_Mark_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
}

#پایان_اگر /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark2 == 1 )

config_پشته_عمق_TYPE MPU_ux_Task_Get_پشته_بالا_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_پشته_عمق_TYPE MPU_ux_Task_Get_پشته_بالا_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_پشته_بالا_Water_Mark2_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ux_Task_Get_پشته_بالا_Water_Mark2_Unpriv
MPU_ux_Task_Get_پشته_بالا_Water_Mark2_Priv
        b MPU_ux_Task_Get_پشته_بالا_Water_Mark2_Impl
MPU_ux_Task_Get_پشته_بالا_Water_Mark2_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
}

#پایان_اگر /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetCurrentTaskHandleImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
MPU_xTaskGetCurrentTaskHandle_Priv
        b MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
}

#پایان_اگر /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

پایه_Type_t MPU_xTaskGetSchedulerState( فراغ ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetSchedulerStateImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_xTaskGetSchedulerState_Unpriv
MPU_xTaskGetSchedulerState_Priv
        b MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerState_Unpriv
        svc #SYSTEM_CALL_xTaskGetSchedulerState
}

#پایان_اگر /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

فراغ MPU_v_Task_مجموعه_زمان_بیرون_State( زمان_بیرون_t * ثابت px_زمان_بیرون ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_مجموعه_زمان_بیرون_State( زمان_بیرون_t * ثابت px_زمان_بیرون ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_مجموعه_زمان_بیرون_State_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_v_Task_مجموعه_زمان_بیرون_State_Unpriv
MPU_v_Task_مجموعه_زمان_بیرون_State_Priv
        b MPU_v_Task_مجموعه_زمان_بیرون_State_Impl
MPU_v_Task_مجموعه_زمان_بیرون_State_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

پایه_Type_t MPU_x_Task_Check_For_زمان_بیرون( زمان_بیرون_t * ثابت px_زمان_بیرون,
                                     TickType_t * ثابت px_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_Task_Check_For_زمان_بیرون( زمان_بیرون_t * ثابت px_زمان_بیرون,
                                     TickType_t * ثابت px_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Check_For_زمان_بیرون_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_Task_Check_For_زمان_بیرون_Unpriv
MPU_x_Task_Check_For_زمان_بیرون_Priv
        b MPU_x_Task_Check_For_زمان_بیرون_Impl
MPU_x_Task_Check_For_زمان_بیرون_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

پایه_Type_t MPU_x_Task_Generic_Notify_مدخل( ثابت xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_Task_Generic_Notify_مدخل( ثابت xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_xTaskGenericNotify_Unpriv
MPU_xTaskGenericNotify_Priv
        b MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotify_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotify
}

#پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

پایه_Type_t MPU_x_Task_Generic_Notify_Wait_مدخل( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_Task_Generic_Notify_Wait_مدخل( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyWaitImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_xTaskGenericNotifyWait_Unpriv
MPU_xTaskGenericNotifyWait_Priv
        b MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWait_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
}

#پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_شاخص_مقصد_Wait_On,
                                      پایه_Type_t x_Clear_شمار_On_Exit,
                                      TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_شاخص_مقصد_Wait_On,
                                            پایه_Type_t x_Clear_شمار_On_Exit,
                                            TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ulTaskGenericNotifyTakeImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
MPU_ulTaskGenericNotifyTake_Priv
        b MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTake_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
}

#پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

پایه_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t ux_شاخص_مقصد_Clear ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t ux_شاخص_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyStateClearImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
MPU_xTaskGenericNotifyStateClear_Priv
        b MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClear_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
}

#پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_مقدار_Clear( TaskHandle_t xTask,
                                            UBaseType_t ux_شاخص_مقصد_Clear,
                                            uint32_t ul_بیتها_مقصد_Clear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_مقدار_Clear( TaskHandle_t xTask,
                                                  UBaseType_t ux_شاخص_مقصد_Clear,
                                                  uint32_t ul_بیتها_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Generic_Notify_مقدار_Clear_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ul_Task_Generic_Notify_مقدار_Clear_Unpriv
MPU_ul_Task_Generic_Notify_مقدار_Clear_Priv
        b MPU_ul_Task_Generic_Notify_مقدار_Clear_Impl
MPU_ul_Task_Generic_Notify_مقدار_Clear_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
}

#پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

پایه_Type_t MPU_x_صف_Generic_Send( صف_Handle_t x_صف,
                                  ثابت فراغ * ثابت pv_قلم_مقصد_صف,
                                  TickType_t x_Ticks_مقصد_Wait,
                                  ثابت پایه_Type_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_صف_Generic_Send( صف_Handle_t x_صف,
                                        ثابت فراغ * ثابت pv_قلم_مقصد_صف,
                                        TickType_t x_Ticks_مقصد_Wait,
                                        ثابت پایه_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_صف_Generic_Send_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_صف_Generic_Send_Unpriv
MPU_x_صف_Generic_Send_Priv
        b MPU_x_صف_Generic_Send_Impl
MPU_x_صف_Generic_Send_Unpriv
        svc #SYSTEM_CALL_xQueueGenericSend
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_صف_Messages_انتظار( ثابت صف_Handle_t x_صف ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_صف_Messages_انتظار( ثابت صف_Handle_t x_صف ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_صف_Messages_انتظار_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ux_صف_Messages_انتظار_Unpriv
MPU_ux_صف_Messages_انتظار_Priv
        b MPU_ux_صف_Messages_انتظار_Impl
MPU_ux_صف_Messages_انتظار_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_صف_Spaces_موجود( ثابت صف_Handle_t x_صف ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_صف_Spaces_موجود( ثابت صف_Handle_t x_صف ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_صف_Spaces_موجود_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ux_صف_Spaces_موجود_Unpriv
MPU_ux_صف_Spaces_موجود_Priv
        b MPU_ux_صف_Spaces_موجود_Impl
MPU_ux_صف_Spaces_موجود_Unpriv
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
}
/*-----------------------------------------------------------*/

پایه_Type_t MPU_x_صف_Receive( صف_Handle_t x_صف,
                              فراغ * ثابت pv_میانگیر,
                              TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_صف_Receive( صف_Handle_t x_صف,
                                    فراغ * ثابت pv_میانگیر,
                                    TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_صف_Receive_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_صف_Receive_Unpriv
MPU_x_صف_Receive_Priv
        b MPU_x_صف_Receive_Impl
MPU_x_صف_Receive_Unpriv
        svc #SYSTEM_CALL_xQueueReceive
}
/*-----------------------------------------------------------*/

پایه_Type_t MPU_x_صف_Peek( صف_Handle_t x_صف,
                           فراغ * ثابت pv_میانگیر,
                           TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_صف_Peek( صف_Handle_t x_صف,
                                 فراغ * ثابت pv_میانگیر,
                                 TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_صف_Peek_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_صف_Peek_Unpriv
MPU_x_صف_Peek_Priv
        b MPU_x_صف_Peek_Impl
MPU_x_صف_Peek_Unpriv
        svc #SYSTEM_CALL_xQueuePeek
}
/*-----------------------------------------------------------*/

پایه_Type_t MPU_x_صف_Semaphore_Take( صف_Handle_t x_صف,
                                    TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_صف_Semaphore_Take( صف_Handle_t x_صف,
                                          TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_صف_Semaphore_Take_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_صف_Semaphore_Take_Unpriv
MPU_x_صف_Semaphore_Take_Priv
        b MPU_x_صف_Semaphore_Take_Impl
MPU_x_صف_Semaphore_Take_Unpriv
        svc #SYSTEM_CALL_xQueueSemaphoreTake
}
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_x_صف_Get_Mutex_Holder( صف_Handle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_x_صف_Get_Mutex_Holder( صف_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_صف_Get_Mutex_Holder_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_صف_Get_Mutex_Holder_Unpriv
MPU_x_صف_Get_Mutex_Holder_Priv
        b MPU_x_صف_Get_Mutex_Holder_Impl
MPU_x_صف_Get_Mutex_Holder_Unpriv
        svc #SYSTEM_CALL_xQueueGetMutexHolder
}

#پایان_اگر /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

پایه_Type_t MPU_x_صف_Take_Mutex_Recursive( صف_Handle_t xMutex,
                                         TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_صف_Take_Mutex_Recursive( صف_Handle_t xMutex,
                                               TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_صف_Take_Mutex_Recursive_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_صف_Take_Mutex_Recursive_Unpriv
MPU_x_صف_Take_Mutex_Recursive_Priv
        b MPU_x_صف_Take_Mutex_Recursive_Impl
MPU_x_صف_Take_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
}

#پایان_اگر /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

پایه_Type_t MPU_x_صف_Give_Mutex_Recursive( صف_Handle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_صف_Give_Mutex_Recursive( صف_Handle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_صف_Give_Mutex_Recursive_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_صف_Give_Mutex_Recursive_Unpriv
MPU_x_صف_Give_Mutex_Recursive_Priv
        b MPU_x_صف_Give_Mutex_Recursive_Impl
MPU_x_صف_Give_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
}

#پایان_اگر /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_صف_SETS == 1 )

صف_مجموعه_Member_Handle_t MPU_x_صف_Select_From_مجموعه( صف_مجموعه_Handle_t x_صف_مجموعه,
                                                ثابت TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm صف_مجموعه_Member_Handle_t MPU_x_صف_Select_From_مجموعه( صف_مجموعه_Handle_t x_صف_مجموعه,
                                                      ثابت TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_صف_Select_From_مجموعه_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_صف_Select_From_مجموعه_Unpriv
MPU_x_صف_Select_From_مجموعه_Priv
        b MPU_x_صف_Select_From_مجموعه_Impl
MPU_x_صف_Select_From_مجموعه_Unpriv
        svc #SYSTEM_CALL_xQueueSelectFromSet
}

#پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_صف_SETS == 1 )

پایه_Type_t MPU_x_صف_جمع_کن_مقصد_مجموعه( صف_مجموعه_Member_Handle_t x_صف_Or_Semaphore,
                               صف_مجموعه_Handle_t x_صف_مجموعه ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_صف_جمع_کن_مقصد_مجموعه( صف_مجموعه_Member_Handle_t x_صف_Or_Semaphore,
                                     صف_مجموعه_Handle_t x_صف_مجموعه ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_صف_جمع_کن_مقصد_مجموعه_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_صف_جمع_کن_مقصد_مجموعه_Unpriv
MPU_x_صف_جمع_کن_مقصد_مجموعه_Priv
        b MPU_x_صف_جمع_کن_مقصد_مجموعه_Impl
MPU_x_صف_جمع_کن_مقصد_مجموعه_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_صف_REGISTRY_اندازه > 0 )

فراغ MPU_v_صف_جمع_کن_مقصد_Registry( صف_Handle_t x_صف,
                              ثابت حرف * pcName ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_صف_جمع_کن_مقصد_Registry( صف_Handle_t x_صف,
                                    ثابت حرف * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_صف_جمع_کن_مقصد_Registry_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_v_صف_جمع_کن_مقصد_Registry_Unpriv
MPU_v_صف_جمع_کن_مقصد_Registry_Priv
        b MPU_v_صف_جمع_کن_مقصد_Registry_Impl
MPU_v_صف_جمع_کن_مقصد_Registry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#پایان_اگر /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_صف_REGISTRY_اندازه > 0 )

فراغ MPU_v_صف_Unregister_صف( صف_Handle_t x_صف ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_صف_Unregister_صف( صف_Handle_t x_صف ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_صف_Unregister_صف_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_v_صف_Unregister_صف_Unpriv
MPU_v_صف_Unregister_صف_Priv
        b MPU_v_صف_Unregister_صف_Impl
MPU_v_صف_Unregister_صف_Unpriv
        svc #SYSTEM_CALL_vQueueUnregisterQueue
}

#پایان_اگر /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_صف_REGISTRY_اندازه > 0 )

ثابت حرف * MPU_pc_صف_Get_Name( صف_Handle_t x_صف ) FREERTOS_SYSTEM_CALL;

__asm ثابت حرف * MPU_pc_صف_Get_Name( صف_Handle_t x_صف ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pc_صف_Get_Name_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_pc_صف_Get_Name_Unpriv
MPU_pc_صف_Get_Name_Priv
        b MPU_pc_صف_Get_Name_Impl
MPU_pc_صف_Get_Name_Unpriv
        svc #SYSTEM_CALL_pcQueueGetName
}

#پایان_اگر /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pvTimerGetTimerIDImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_pvTimerGetTimerID_Unpriv
MPU_pvTimerGetTimerID_Priv
        b MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerID_Unpriv
        svc #SYSTEM_CALL_pvTimerGetTimerID
}

#پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ MPU_v_Timer_مجموعه_Timer_ID( TimerHandle_t xTimer,
                           فراغ * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Timer_مجموعه_Timer_ID( TimerHandle_t xTimer,
                                 فراغ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Timer_مجموعه_Timer_IDImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_v_Timer_مجموعه_Timer_ID_Unpriv
MPU_v_Timer_مجموعه_Timer_ID_Priv
        b MPU_v_Timer_مجموعه_Timer_IDImpl
MPU_v_Timer_مجموعه_Timer_ID_Unpriv
        svc #SYSTEM_CALL_vTimerSetTimerID
}

#پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

پایه_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Is_Timer_فعال_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_Timer_Is_Timer_فعال_Unpriv
MPU_x_Timer_Is_Timer_فعال_Priv
        b MPU_x_Timer_Is_Timer_فعال_Impl
MPU_x_Timer_Is_Timer_فعال_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGetTimerDaemonTaskHandleImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
MPU_xTimerGetTimerDaemonTaskHandle_Priv
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
}

#پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

پایه_Type_t MPU_x_Timer_Generic_Command_From_Task_مدخل( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_Timer_Generic_Command_From_Task_مدخل( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGenericCommandFromTaskImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
MPU_xTimerGenericCommandFromTask_Priv
        b MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTask_Unpriv
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
}

#پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pcTimerGetNameImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_pcTimerGetName_Unpriv
MPU_pcTimerGetName_Priv
        b MPU_pcTimerGetNameImpl
MPU_pcTimerGetName_Unpriv
        svc #SYSTEM_CALL_pcTimerGetName
}

#پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ MPU_v_Timer_مجموعه_Reload_نما( TimerHandle_t xTimer,
                              ثابت پایه_Type_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Timer_مجموعه_Reload_نما( TimerHandle_t xTimer,
                                    ثابت پایه_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Timer_مجموعه_Reload_نما_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_v_Timer_مجموعه_Reload_نما_Unpriv
MPU_v_Timer_مجموعه_Reload_نما_Priv
        b MPU_v_Timer_مجموعه_Reload_نما_Impl
MPU_v_Timer_مجموعه_Reload_نما_Unpriv
        svc #SYSTEM_CALL_vTimerSetReloadMode
}

#پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

پایه_Type_t MPU_x_Timer_Get_Reload_نما( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_Timer_Get_Reload_نما( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Get_Reload_نما_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_Timer_Get_Reload_نما_Unpriv
MPU_x_Timer_Get_Reload_نما_Priv
        b MPU_x_Timer_Get_Reload_نما_Impl
MPU_x_Timer_Get_Reload_نما_Unpriv
        svc #SYSTEM_CALL_xTimerGetReloadMode
}

#پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

UBaseType_t MPU_ux_Timer_Get_Reload_نما( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Timer_Get_Reload_نما( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Timer_Get_Reload_نما_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ux_Timer_Get_Reload_نما_Unpriv
MPU_ux_Timer_Get_Reload_نما_Priv
        b MPU_ux_Timer_Get_Reload_نما_Impl
MPU_ux_Timer_Get_Reload_نما_Unpriv
        svc #SYSTEM_CALL_uxTimerGetReloadMode
}

#پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGetPeriodImpl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_xTimerGetPeriod_Unpriv
MPU_xTimerGetPeriod_Priv
        b MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriod_Unpriv
        svc #SYSTEM_CALL_xTimerGetPeriod
}

#پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TickType_t MPU_x_Timer_Get_Expiry_زمان( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Timer_Get_Expiry_زمان( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Get_Expiry_زمان_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_Timer_Get_Expiry_زمان_Unpriv
MPU_x_Timer_Get_Expiry_زمان_Priv
        b MPU_x_Timer_Get_Expiry_زمان_Impl
MPU_x_Timer_Get_Expiry_زمان_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بیتها_t MPU_x_Event_گروه_Wait_بیتها_مدخل( ثابت x_Event_گروه_Wait_بیتها_Params_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm Event_بیتها_t MPU_x_Event_گروه_Wait_بیتها_مدخل( ثابت x_Event_گروه_Wait_بیتها_Params_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروه_Wait_بیتها_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_Event_گروه_Wait_بیتها_Unpriv
MPU_x_Event_گروه_Wait_بیتها_Priv
        b MPU_x_Event_گروه_Wait_بیتها_Impl
MPU_x_Event_گروه_Wait_بیتها_Unpriv
        svc #SYSTEM_CALL_xEventGroupWaitBits
}

#پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بیتها_t MPU_x_Event_گروه_Clear_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                      ثابت Event_بیتها_t ux_بیتها_مقصد_Clear ) FREERTOS_SYSTEM_CALL;

__asm Event_بیتها_t MPU_x_Event_گروه_Clear_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                            ثابت Event_بیتها_t ux_بیتها_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروه_Clear_بیتها_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_Event_گروه_Clear_بیتها_Unpriv
MPU_x_Event_گروه_Clear_بیتها_Priv
        b MPU_x_Event_گروه_Clear_بیتها_Impl
MPU_x_Event_گروه_Clear_بیتها_Unpriv
        svc #SYSTEM_CALL_xEventGroupClearBits
}

#پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بیتها_t MPU_x_Event_گروه_مجموعه_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                    ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه ) FREERTOS_SYSTEM_CALL;

__asm Event_بیتها_t MPU_x_Event_گروه_مجموعه_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                          ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروه_مجموعه_بیتها_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_Event_گروه_مجموعه_بیتها_Unpriv
MPU_x_Event_گروه_مجموعه_بیتها_Priv
        b MPU_x_Event_گروه_مجموعه_بیتها_Impl
MPU_x_Event_گروه_مجموعه_بیتها_Unpriv
        svc #SYSTEM_CALL_xEventGroupSetBits
}

#پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بیتها_t MPU_x_Event_گروه_Sync( Event_گروه_Handle_t x_Event_گروه,
                                 ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه,
                                 ثابت Event_بیتها_t ux_بیتها_مقصد_Wait_For,
                                 TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm Event_بیتها_t MPU_x_Event_گروه_Sync( Event_گروه_Handle_t x_Event_گروه,
                                       ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه,
                                       ثابت Event_بیتها_t ux_بیتها_مقصد_Wait_For,
                                       TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروه_Sync_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_Event_گروه_Sync_Unpriv
MPU_x_Event_گروه_Sync_Priv
        b MPU_x_Event_گروه_Sync_Impl
MPU_x_Event_گروه_Sync_Unpriv
        svc #SYSTEM_CALL_xEventGroupSync
}

#پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_گروه_Get_عدد( فراغ * x_Event_گروه ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_گروه_Get_عدد( فراغ * x_Event_گروه ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Event_گروه_Get_عدد_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_ux_Event_گروه_Get_عدد_Unpriv
MPU_ux_Event_گروه_Get_عدد_Priv
        b MPU_ux_Event_گروه_Get_عدد_Impl
MPU_ux_Event_گروه_Get_عدد_Unpriv
        svc #SYSTEM_CALL_uxEventGroupGetNumber
}

#پایان_اگر /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

فراغ MPU_v_Event_گروه_مجموعه_عدد( فراغ * x_Event_گروه,
                               UBaseType_t ux_Event_گروه_عدد ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Event_گروه_مجموعه_عدد( فراغ * x_Event_گروه,
                                     UBaseType_t ux_Event_گروه_عدد ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Event_گروه_مجموعه_عدد_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_v_Event_گروه_مجموعه_عدد_Unpriv
MPU_v_Event_گروه_مجموعه_عدد_Priv
        b MPU_v_Event_گروه_مجموعه_عدد_Impl
MPU_v_Event_گروه_مجموعه_عدد_Unpriv
        svc #SYSTEM_CALL_vEventGroupSetNumber
}

#پایان_اگر /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_جریان_BUFFERS == 1 )

size_t MPU_x_جریان_میانگیر_Send( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                              ثابت فراغ * pv_Tx_داده,
                              size_t x_داده_درازی_بایتها,
                              TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_جریان_میانگیر_Send( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                    ثابت فراغ * pv_Tx_داده,
                                    size_t x_داده_درازی_بایتها,
                                    TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_جریان_میانگیر_Send_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_جریان_میانگیر_Send_Unpriv
MPU_x_جریان_میانگیر_Send_Priv
        b MPU_x_جریان_میانگیر_Send_Impl
MPU_x_جریان_میانگیر_Send_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSend
}

#پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_جریان_BUFFERS == 1 )

size_t MPU_x_جریان_میانگیر_Receive( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                 فراغ * pv_Rx_داده,
                                 size_t x_میانگیر_درازی_بایتها,
                                 TickType_t x_Ticks_مقصد_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_جریان_میانگیر_Receive( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                       فراغ * pv_Rx_داده,
                                       size_t x_میانگیر_درازی_بایتها,
                                       TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_جریان_میانگیر_Receive_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_جریان_میانگیر_Receive_Unpriv
MPU_x_جریان_میانگیر_Receive_Priv
        b MPU_x_جریان_میانگیر_Receive_Impl
MPU_x_جریان_میانگیر_Receive_Unpriv
        svc #SYSTEM_CALL_xStreamBufferReceive
}

#پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_جریان_BUFFERS == 1 )

پایه_Type_t MPU_x_جریان_میانگیر_Is_پر( جریان_میانگیر_Handle_t x_جریان_میانگیر ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_جریان_میانگیر_Is_پر( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_جریان_میانگیر_Is_پر_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_جریان_میانگیر_Is_پر_Unpriv
MPU_x_جریان_میانگیر_Is_پر_Priv
        b MPU_x_جریان_میانگیر_Is_پر_Impl
MPU_x_جریان_میانگیر_Is_پر_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_جریان_BUFFERS == 1 )

پایه_Type_t MPU_x_جریان_میانگیر_Is_خالی( جریان_میانگیر_Handle_t x_جریان_میانگیر ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_جریان_میانگیر_Is_خالی( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_جریان_میانگیر_Is_خالی_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_جریان_میانگیر_Is_خالی_Unpriv
MPU_x_جریان_میانگیر_Is_خالی_Priv
        b MPU_x_جریان_میانگیر_Is_خالی_Impl
MPU_x_جریان_میانگیر_Is_خالی_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_جریان_BUFFERS == 1 )

size_t MPU_x_جریان_میانگیر_Spaces_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_جریان_میانگیر_Spaces_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_جریان_میانگیر_Spaces_موجود_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_جریان_میانگیر_Spaces_موجود_Unpriv
MPU_x_جریان_میانگیر_Spaces_موجود_Priv
        b MPU_x_جریان_میانگیر_Spaces_موجود_Impl
MPU_x_جریان_میانگیر_Spaces_موجود_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
}

#پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_جریان_BUFFERS == 1 )

size_t MPU_x_جریان_میانگیر_بایتها_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_جریان_میانگیر_بایتها_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_جریان_میانگیر_بایتها_موجود_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_جریان_میانگیر_بایتها_موجود_Unpriv
MPU_x_جریان_میانگیر_بایتها_موجود_Priv
        b MPU_x_جریان_میانگیر_بایتها_موجود_Impl
MPU_x_جریان_میانگیر_بایتها_موجود_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_جریان_BUFFERS == 1 )

پایه_Type_t MPU_x_جریان_میانگیر_مجموعه_Trigger_Level( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm پایه_Type_t MPU_x_جریان_میانگیر_مجموعه_Trigger_Level( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_جریان_میانگیر_مجموعه_Trigger_Level_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_جریان_میانگیر_مجموعه_Trigger_Level_Unpriv
MPU_x_جریان_میانگیر_مجموعه_Trigger_Level_Priv
        b MPU_x_جریان_میانگیر_مجموعه_Trigger_Level_Impl
MPU_x_جریان_میانگیر_مجموعه_Trigger_Level_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
}

#پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_جریان_BUFFERS == 1 )

size_t MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها( جریان_میانگیر_Handle_t x_جریان_میانگیر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها_Impl

    افزودن {r0}
    mrs r0, control
    tst r0, #1
    برداشت {r0}
    bne MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها_Unpriv
MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها_Priv
        b MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها_Impl
MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#پایان_اگر /* configUSE_MPU_WRAPPERS_V1 == 0 */
