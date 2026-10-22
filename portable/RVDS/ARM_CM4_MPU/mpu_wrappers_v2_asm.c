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
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"
#ضمن "mpu_syscall_numbers.h"

#تعریف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( configUSE_MPU_WRAPPERS_V1 == 0 )

#إذا ( INCLUDE_xTaskDelayUntil == 1 )

ادھار_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_ویلا,
                                ثابت TickType_t x_ویلا_Increment ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_ویلا,
                                      ثابت TickType_t x_ویلا_Increment ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskDelayUntilImpl

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

#جے_انت /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskAbortDelay == 1 )

ادھار_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskAbortDelayImpl

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

#جے_انت /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskDelay == 1 )

فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskDelayImpl

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

#جے_انت /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_ترجیح_Get == 1 )

UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_ترجیح_Get_Impl

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

#جے_انت /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_eTaskGetStateImpl

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

#جے_انت /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TRACE_FACILITY == 1 )

فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                       Task_حالت_t * px_Task_حالت,
                       ادھار_Type_t x_Get_Free_ڈھیر_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                             Task_حالت_t * px_Task_حالت,
                             ادھار_Type_t x_Get_Free_ڈھیر_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskGetInfoImpl

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

#جے_انت /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetIdleTaskHandleImpl

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

#جے_انت /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskSuspend == 1 )

فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_منزل_Suspend ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_منزل_Suspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskSuspendImpl

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

#جے_انت /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_vTaskSuspend == 1 )

فراغ MPU_vTaskResume( TaskHandle_t x_Task_منزل_Resume ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_vTaskResume( TaskHandle_t x_Task_منزل_Resume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_vTaskResumeImpl

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

#جے_انت /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_گنتی( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_گنتی( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Get_Tick_گنتی_Impl

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

UBaseType_t MPU_ux_Task_Get_نمبر_دا_Tasks( فراغ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_نمبر_دا_Tasks( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_نمبر_دا_Tasks_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ux_Task_Get_نمبر_دا_Tasks_Unpriv
MPU_ux_Task_Get_نمبر_دا_Tasks_Priv
        b MPU_ux_Task_Get_نمبر_دا_Tasks_Impl
MPU_ux_Task_Get_نمبر_دا_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#إذا ( config_GENERATE_لگاتار_ویلا_STATS == 1 )

config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Counter( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Counter( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_لگاتار_ویلا_Counter_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ul_Task_Get_لگاتار_ویلا_Counter_Unpriv
MPU_ul_Task_Get_لگاتار_ویلا_Counter_Priv
        b MPU_ul_Task_Get_لگاتار_ویلا_Counter_Impl
MPU_ul_Task_Get_لگاتار_ویلا_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_GENERATE_لگاتار_ویلا_STATS == 1 )

config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Percent( ثابت TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Percent( ثابت TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_لگاتار_ویلا_Percent_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ul_Task_Get_لگاتار_ویلا_Percent_Unpriv
MPU_ul_Task_Get_لگاتار_ویلا_Percent_Priv
        b MPU_ul_Task_Get_لگاتار_ویلا_Percent_Impl
MPU_ul_Task_Get_لگاتار_ویلا_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( config_GENERATE_لگاتار_ویلا_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent( فراغ ) FREERTOS_SYSTEM_CALL;

__asm config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent_Unpriv
MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent_Priv
        b MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent_Impl
MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( config_GENERATE_لگاتار_ویلا_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter( فراغ ) FREERTOS_SYSTEM_CALL;

__asm config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter_Unpriv
MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter_Priv
        b MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter_Impl
MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )

فراغ MPU_v_Task_سیٹ_Application_Task_ٹیگ( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_سیٹ_Application_Task_ٹیگ( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_سیٹ_Application_Task_ٹیگ_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_v_Task_سیٹ_Application_Task_ٹیگ_Unpriv
MPU_v_Task_سیٹ_Application_Task_ٹیگ_Priv
        b MPU_v_Task_سیٹ_Application_Task_ٹیگ_Impl
MPU_v_Task_سیٹ_Application_Task_ٹیگ_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#جے_انت /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )

TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٹیگ( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٹیگ( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Get_Application_Task_ٹیگ_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Task_Get_Application_Task_ٹیگ_Unpriv
MPU_x_Task_Get_Application_Task_ٹیگ_Priv
        b MPU_x_Task_Get_Application_Task_ٹیگ_Impl
MPU_x_Task_Get_Application_Task_ٹیگ_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#جے_انت /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_عدد_THREAD_LOCAL_STORAGE_سوچکاں != 0 )

فراغ MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_منزل_سیٹ,
                                            ادھار_Type_t x_اشاریہ,
                                            فراغ * pv_قدر ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_منزل_سیٹ,
                                                  ادھار_Type_t x_اشاریہ,
                                                  فراغ * pv_قدر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Impl

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

#جے_انت /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_عدد_THREAD_LOCAL_STORAGE_سوچکاں != 0 )

فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_منزل_Query,
                                               ادھار_Type_t x_اشاریہ ) FREERTOS_SYSTEM_CALL;

__asm فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_منزل_Query,
                                                     ادھار_Type_t x_اشاریہ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Impl

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

#جے_انت /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                      ثابت UBaseType_t ux_Array_ناپ,
                                      config_لگاتار_ویلا_COUNTER_TYPE * ثابت pul_کل_لگاتار_ویلا ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                            ثابت UBaseType_t ux_Array_ناپ,
                                            config_لگاتار_ویلا_COUNTER_TYPE * ثابت pul_کل_لگاتار_ویلا ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_uxTaskGetSystemStateImpl

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

#جے_انت /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Impl

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

#جے_انت /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark2 == 1 )

config_ڈھیر_ڈونگھائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_ڈھیر_ڈونگھائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Impl

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

#جے_انت /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetCurrentTaskHandleImpl

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

#جے_انت /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

ادھار_Type_t MPU_xTaskGetSchedulerState( فراغ ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGetSchedulerStateImpl

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

#جے_انت /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

فراغ MPU_v_Task_سیٹ_ویلا_باہرلا_State( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Task_سیٹ_ویلا_باہرلا_State( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Task_سیٹ_ویلا_باہرلا_State_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_v_Task_سیٹ_ویلا_باہرلا_State_Unpriv
MPU_v_Task_سیٹ_ویلا_باہرلا_State_Priv
        b MPU_v_Task_سیٹ_ویلا_باہرلا_State_Impl
MPU_v_Task_سیٹ_ویلا_باہرلا_State_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

ادھار_Type_t MPU_x_Task_Check_For_ویلا_باہرلا( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا,
                                     TickType_t * ثابت px_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_Task_Check_For_ویلا_باہرلا( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا,
                                     TickType_t * ثابت px_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Task_Check_For_ویلا_باہرلا_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Task_Check_For_ویلا_باہرلا_Unpriv
MPU_x_Task_Check_For_ویلا_باہرلا_Priv
        b MPU_x_Task_Check_For_ویلا_باہرلا_Impl
MPU_x_Task_Check_For_ویلا_باہرلا_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

ادھار_Type_t MPU_x_Task_Generic_Notify_اندراج( ثابت xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_Task_Generic_Notify_اندراج( ثابت xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyImpl

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

#جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

ادھار_Type_t MPU_x_Task_Generic_Notify_Wait_اندراج( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_Task_Generic_Notify_Wait_اندراج( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyWaitImpl

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

#جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاریہ_منزل_Wait_On,
                                      ادھار_Type_t x_Clear_گنتی_On_Exit,
                                      TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاریہ_منزل_Wait_On,
                                            ادھار_Type_t x_Clear_گنتی_On_Exit,
                                            TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ulTaskGenericNotifyTakeImpl

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

#جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

ادھار_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t ux_اشاریہ_منزل_Clear ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t ux_اشاریہ_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTaskGenericNotifyStateClearImpl

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

#جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                            UBaseType_t ux_اشاریہ_منزل_Clear,
                                            uint32_t ul_بٹ_منزل_Clear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                  UBaseType_t ux_اشاریہ_منزل_Clear,
                                                  uint32_t ul_بٹ_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ul_Task_Generic_Notify_قدر_Clear_Impl

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

#جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

ادھار_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                  ثابت فراغ * ثابت pv_شے_منزل_قطار,
                                  TickType_t x_Ticks_منزل_Wait,
                                  ثابت ادھار_Type_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                        ثابت فراغ * ثابت pv_شے_منزل_قطار,
                                        TickType_t x_Ticks_منزل_Wait,
                                        ثابت ادھار_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Generic_Send_Impl

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

UBaseType_t MPU_ux_قطار_Messages_اڈیک( ثابت قطار_Handle_t x_قطار ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_قطار_Messages_اڈیک( ثابت قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_قطار_Messages_اڈیک_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_ux_قطار_Messages_اڈیک_Unpriv
MPU_ux_قطار_Messages_اڈیک_Priv
        b MPU_ux_قطار_Messages_اڈیک_Impl
MPU_ux_قطار_Messages_اڈیک_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_قطار_Spaces_دستیاب_Impl

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

ادھار_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                              فراغ * ثابت pv_بفر,
                              TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                                    فراغ * ثابت pv_بفر,
                                    TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Receive_Impl

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

ادھار_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                           فراغ * ثابت pv_بفر,
                           TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                                 فراغ * ثابت pv_بفر,
                                 TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Peek_Impl

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

ادھار_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                    TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                          TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Semaphore_Take_Impl

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

#إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Get_Mutex_Holder_Impl

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

#جے_انت /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

ادھار_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                         TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                               TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Take_Mutex_Recursive_Impl

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

#جے_انت /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

ادھار_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Give_Mutex_Recursive_Impl

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

#جے_انت /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_قطار_SETS == 1 )

قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                ثابت TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                      ثابت TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_Select_From_سیٹ_Impl

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

#جے_انت /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_قطار_SETS == 1 )

ادھار_Type_t MPU_x_قطار_جوڑو_منزل_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                               قطار_سیٹ_Handle_t x_قطار_سیٹ ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_قطار_جوڑو_منزل_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                     قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_قطار_جوڑو_منزل_سیٹ_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_قطار_جوڑو_منزل_سیٹ_Unpriv
MPU_x_قطار_جوڑو_منزل_سیٹ_Priv
        b MPU_x_قطار_جوڑو_منزل_سیٹ_Impl
MPU_x_قطار_جوڑو_منزل_سیٹ_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#جے_انت /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_قطار_REGISTRY_ناپ > 0 )

فراغ MPU_v_قطار_جوڑو_منزل_Registry( قطار_Handle_t x_قطار,
                              ثابت حرف * pcName ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_قطار_جوڑو_منزل_Registry( قطار_Handle_t x_قطار,
                                    ثابت حرف * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_قطار_جوڑو_منزل_Registry_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_v_قطار_جوڑو_منزل_Registry_Unpriv
MPU_v_قطار_جوڑو_منزل_Registry_Priv
        b MPU_v_قطار_جوڑو_منزل_Registry_Impl
MPU_v_قطار_جوڑو_منزل_Registry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#جے_انت /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_قطار_REGISTRY_ناپ > 0 )

فراغ MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_قطار_Unregister_قطار_Impl

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

#جے_انت /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( config_قطار_REGISTRY_ناپ > 0 )

ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) FREERTOS_SYSTEM_CALL;

__asm ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pc_قطار_Get_Name_Impl

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

#جے_انت /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pvTimerGetTimerIDImpl

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

#جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                           فراغ * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                                 فراغ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Timer_سیٹ_Timer_IDImpl

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

#جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

ادھار_Type_t MPU_x_Timer_Is_Timer_سرگرم( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_Timer_Is_Timer_سرگرم( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Is_Timer_سرگرم_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Timer_Is_Timer_سرگرم_Unpriv
MPU_x_Timer_Is_Timer_سرگرم_Priv
        b MPU_x_Timer_Is_Timer_سرگرم_Impl
MPU_x_Timer_Is_Timer_سرگرم_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGetTimerDaemonTaskHandleImpl

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

#جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

ادھار_Type_t MPU_x_Timer_Generic_Command_From_Task_اندراج( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_Timer_Generic_Command_From_Task_اندراج( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGenericCommandFromTaskImpl

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

#جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_pcTimerGetNameImpl

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

#جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

فراغ MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                              ثابت ادھار_Type_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                                    ثابت ادھار_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Timer_سیٹ_Reload_منوال_Impl

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

#جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

ادھار_Type_t MPU_x_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Get_Reload_منوال_Impl

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

#جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Timer_Get_Reload_منوال_Impl

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

#جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_xTimerGetPeriodImpl

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

#جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_TIMERS == 1 )

TickType_t MPU_x_Timer_Get_Expiry_ویلا( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Timer_Get_Expiry_ویلا( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Timer_Get_Expiry_ویلا_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_Timer_Get_Expiry_ویلا_Unpriv
MPU_x_Timer_Get_Expiry_ویلا_Priv
        b MPU_x_Timer_Get_Expiry_ویلا_Impl
MPU_x_Timer_Get_Expiry_ویلا_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_اندراج( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_اندراج( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروہ_Wait_بٹ_Impl

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

#جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                      ثابت Event_بٹ_t ux_بٹ_منزل_Clear ) FREERTOS_SYSTEM_CALL;

__asm Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                            ثابت Event_بٹ_t ux_بٹ_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروہ_Clear_بٹ_Impl

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

#جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                    ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ ) FREERTOS_SYSTEM_CALL;

__asm Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                          ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروہ_سیٹ_بٹ_Impl

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

#جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( configUSE_EVENT_GROUPS == 1 )

Event_بٹ_t MPU_x_Event_گروہ_Sync( Event_گروہ_Handle_t x_Event_گروہ,
                                 ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ,
                                 ثابت Event_بٹ_t ux_بٹ_منزل_Wait_For,
                                 TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm Event_بٹ_t MPU_x_Event_گروہ_Sync( Event_گروہ_Handle_t x_Event_گروہ,
                                       ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ,
                                       ثابت Event_بٹ_t ux_بٹ_منزل_Wait_For,
                                       TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_Event_گروہ_Sync_Impl

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

#جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_گروہ_Get_نمبر( فراغ * x_Event_گروہ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_گروہ_Get_نمبر( فراغ * x_Event_گروہ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_ux_Event_گروہ_Get_نمبر_Impl

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

#جے_انت /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

فراغ MPU_v_Event_گروہ_سیٹ_نمبر( فراغ * x_Event_گروہ,
                               UBaseType_t ux_Event_گروہ_نمبر ) FREERTOS_SYSTEM_CALL;

__asm فراغ MPU_v_Event_گروہ_سیٹ_نمبر( فراغ * x_Event_گروہ,
                                     UBaseType_t ux_Event_گروہ_نمبر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_v_Event_گروہ_سیٹ_نمبر_Impl

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

#جے_انت /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_دھارا_BUFFERS == 1 )

size_t MPU_x_دھارا_بفر_Send( دھارا_بفر_Handle_t x_دھارا_بفر,
                              ثابت فراغ * pv_Tx_انکڑے,
                              size_t x_انکڑے_لمائی_بائٹاں,
                              TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_دھارا_بفر_Send( دھارا_بفر_Handle_t x_دھارا_بفر,
                                    ثابت فراغ * pv_Tx_انکڑے,
                                    size_t x_انکڑے_لمائی_بائٹاں,
                                    TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_دھارا_بفر_Send_Impl

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

#جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_دھارا_BUFFERS == 1 )

size_t MPU_x_دھارا_بفر_Receive( دھارا_بفر_Handle_t x_دھارا_بفر,
                                 فراغ * pv_Rx_انکڑے,
                                 size_t x_بفر_لمائی_بائٹاں,
                                 TickType_t x_Ticks_منزل_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_دھارا_بفر_Receive( دھارا_بفر_Handle_t x_دھارا_بفر,
                                       فراغ * pv_Rx_انکڑے,
                                       size_t x_بفر_لمائی_بائٹاں,
                                       TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_دھارا_بفر_Receive_Impl

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

#جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_دھارا_BUFFERS == 1 )

ادھار_Type_t MPU_x_دھارا_بفر_Is_بھریا( دھارا_بفر_Handle_t x_دھارا_بفر ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_دھارا_بفر_Is_بھریا( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_دھارا_بفر_Is_بھریا_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_Is_بھریا_Unpriv
MPU_x_دھارا_بفر_Is_بھریا_Priv
        b MPU_x_دھارا_بفر_Is_بھریا_Impl
MPU_x_دھارا_بفر_Is_بھریا_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_دھارا_BUFFERS == 1 )

ادھار_Type_t MPU_x_دھارا_بفر_Is_خالی_تھاواں( دھارا_بفر_Handle_t x_دھارا_بفر ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_دھارا_بفر_Is_خالی_تھاواں( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_دھارا_بفر_Is_خالی_تھاواں_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_Is_خالی_تھاواں_Unpriv
MPU_x_دھارا_بفر_Is_خالی_تھاواں_Priv
        b MPU_x_دھارا_بفر_Is_خالی_تھاواں_Impl
MPU_x_دھارا_بفر_Is_خالی_تھاواں_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_دھارا_BUFFERS == 1 )

size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_دھارا_بفر_Spaces_دستیاب_Impl

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

#جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_دھارا_BUFFERS == 1 )

size_t MPU_x_دھارا_بفر_بائٹاں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_دھارا_بفر_بائٹاں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_دھارا_بفر_بائٹاں_دستیاب_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_بائٹاں_دستیاب_Unpriv
MPU_x_دھارا_بفر_بائٹاں_دستیاب_Priv
        b MPU_x_دھارا_بفر_بائٹاں_دستیاب_Impl
MPU_x_دھارا_بفر_بائٹاں_دستیاب_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_دھارا_BUFFERS == 1 )

ادھار_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm ادھار_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Impl

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

#جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#إذا ( config_USE_دھارا_BUFFERS == 1 )

size_t MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں( دھارا_بفر_Handle_t x_دھارا_بفر ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    خارجي MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں_Impl

    ڈالو {r0}
    mrs r0, control
    tst r0, #1
    نکالو {r0}
    bne MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں_Unpriv
MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں_Priv
        b MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں_Impl
MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#جے_انت /* configUSE_MPU_WRAPPERS_V1 == 0 */
