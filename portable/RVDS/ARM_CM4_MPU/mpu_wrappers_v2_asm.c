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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "queue.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "timers.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "event_groups.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stream_buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_prototypes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_syscall_numbers.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_MPU_WRAPPERS_V1 == 0 )

#ਜੇ ( INCLUDE_xTaskDelayUntil == 1 )

ਅਧਾਰ_Type_t MPU_xTaskDelayUntil( TickType_t * ਅਚਲ px_ਪਿਛਲਾ_Wake_ਸਮਾਂ,
                                ਅਚਲ TickType_t x_ਸਮਾਂ_Increment ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_xTaskDelayUntil( TickType_t * ਅਚਲ px_ਪਿਛਲਾ_Wake_ਸਮਾਂ,
                                      ਅਚਲ TickType_t x_ਸਮਾਂ_Increment ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_xTaskDelayUntilImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_xTaskDelayUntil_Unpriv
MPU_xTaskDelayUntil_Priv
        b MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntil_Unpriv
        svc #SYSTEM_CALL_xTaskDelayUntil
}

#ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( INCLUDE_xTaskAbortDelay == 1 )

ਅਧਾਰ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_xTaskAbortDelayImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_xTaskAbortDelay_Unpriv
MPU_xTaskAbortDelay_Priv
        b MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelay_Unpriv
        svc #SYSTEM_CALL_xTaskAbortDelay
}

#ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( INCLUDE_vTaskDelay == 1 )

ਖਾਲੀ MPU_vTaskDelay( ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Delay ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_vTaskDelay( ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Delay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_vTaskDelayImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_vTaskDelay_Unpriv
MPU_vTaskDelay_Priv
        b MPU_vTaskDelayImpl
MPU_vTaskDelay_Unpriv
        svc #SYSTEM_CALL_vTaskDelay
}

#ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( INCLUDE_ux_Task_ਤਰਜੀਹ_Get == 1 )

UBaseType_t MPU_ux_Task_ਤਰਜੀਹ_Get( ਅਚਲ TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_ਤਰਜੀਹ_Get( ਅਚਲ TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ux_Task_ਤਰਜੀਹ_Get_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ux_Task_ਤਰਜੀਹ_Get_Unpriv
MPU_ux_Task_ਤਰਜੀਹ_Get_Priv
        b MPU_ux_Task_ਤਰਜੀਹ_Get_Impl
MPU_ux_Task_ਤਰਜੀਹ_Get_Unpriv
        svc #SYSTEM_CALL_uxTaskPriorityGet
}

#ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_eTaskGetStateImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_eTaskGetState_Unpriv
MPU_eTaskGetState_Priv
        b MPU_eTaskGetStateImpl
MPU_eTaskGetState_Unpriv
        svc #SYSTEM_CALL_eTaskGetState
}

#ਜੇ_ਅੰਤ /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TRACE_FACILITY == 1 )

ਖਾਲੀ MPU_vTaskGetInfo( TaskHandle_t xTask,
                       Task_ਸਥਿਤੀ_t * px_Task_ਸਥਿਤੀ,
                       ਅਧਾਰ_Type_t x_Get_Free_ਢੇਰ_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_vTaskGetInfo( TaskHandle_t xTask,
                             Task_ਸਥਿਤੀ_t * px_Task_ਸਥਿਤੀ,
                             ਅਧਾਰ_Type_t x_Get_Free_ਢੇਰ_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_vTaskGetInfoImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_vTaskGetInfo_Unpriv
MPU_vTaskGetInfo_Priv
        b MPU_vTaskGetInfoImpl
MPU_vTaskGetInfo_Unpriv
        svc #SYSTEM_CALL_vTaskGetInfo
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( ਖਾਲੀ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_xTaskGetIdleTaskHandleImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
MPU_xTaskGetIdleTaskHandle_Priv
        b MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
}

#ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( INCLUDE_vTaskSuspend == 1 )

ਖਾਲੀ MPU_vTaskSuspend( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Suspend ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_vTaskSuspend( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Suspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_vTaskSuspendImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_vTaskSuspend_Unpriv
MPU_vTaskSuspend_Priv
        b MPU_vTaskSuspendImpl
MPU_vTaskSuspend_Unpriv
        svc #SYSTEM_CALL_vTaskSuspend
}

#ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( INCLUDE_vTaskSuspend == 1 )

ਖਾਲੀ MPU_vTaskResume( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Resume ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_vTaskResume( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Resume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_vTaskResumeImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_vTaskResume_Unpriv
MPU_vTaskResume_Priv
        b MPU_vTaskResumeImpl
MPU_vTaskResume_Unpriv
        svc #SYSTEM_CALL_vTaskResume
}

#ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_ਗਿਣਤੀ( ਖਾਲੀ ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_ਗਿਣਤੀ( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_Task_Get_Tick_ਗਿਣਤੀ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_Task_Get_Tick_ਗਿਣਤੀ_Unpriv
MPU_x_Task_Get_Tick_ਗਿਣਤੀ_Priv
        b MPU_x_Task_Get_Tick_ਗਿਣਤੀ_Impl
MPU_x_Task_Get_Tick_ਗਿਣਤੀ_Unpriv
        svc #SYSTEM_CALL_xTaskGetTickCount
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks( ਖਾਲੀ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks_Unpriv
MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks_Priv
        b MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks_Impl
MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#ਜੇ ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )

config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਅਚਲ TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਅਚਲ TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Unpriv
MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Priv
        b MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Impl
MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )

config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਅਚਲ TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਅਚਲ TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Unpriv
MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Priv
        b MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Impl
MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਖਾਲੀ ) FREERTOS_SYSTEM_CALL;

__asm config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Unpriv
MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Priv
        b MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Impl
MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#ਜੇ ( ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਖਾਲੀ ) FREERTOS_SYSTEM_CALL;

__asm config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Unpriv
MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Priv
        b MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Impl
MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )

ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ_Unpriv
MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ_Priv
        b MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ_Impl
MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#ਜੇ_ਅੰਤ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )

TaskHookFunction_t MPU_x_Task_Get_Application_Task_ਟੈਗ( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_x_Task_Get_Application_Task_ਟੈਗ( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_Task_Get_Application_Task_ਟੈਗ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_Task_Get_Application_Task_ਟੈਗ_Unpriv
MPU_x_Task_Get_Application_Task_ਟੈਗ_Priv
        b MPU_x_Task_Get_Application_Task_ਟੈਗ_Impl
MPU_x_Task_Get_Application_Task_ਟੈਗ_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#ਜੇ_ਅੰਤ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ != 0 )

ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                            ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ,
                                            ਖਾਲੀ * pv_ਮੁੱਲ ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                                  ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ,
                                                  ਖਾਲੀ * pv_ਮੁੱਲ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ_Unpriv
MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ_Priv
        b MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ_Impl
MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ_Unpriv
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
}

#ਜੇ_ਅੰਤ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ != 0 )

ਖਾਲੀ * MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Query,
                                               ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ * MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Query,
                                                     ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ_Unpriv
MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ_Priv
        b MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ_Impl
MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ_Unpriv
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
}

#ਜੇ_ਅੰਤ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( Task_ਸਥਿਤੀ_t * ਅਚਲ px_Task_ਸਥਿਤੀ_Array,
                                      ਅਚਲ UBaseType_t ux_Array_ਮਾਪ,
                                      config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE * ਅਚਲ pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( Task_ਸਥਿਤੀ_t * ਅਚਲ px_Task_ਸਥਿਤੀ_Array,
                                            ਅਚਲ UBaseType_t ux_Array_ਮਾਪ,
                                            config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE * ਅਚਲ pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_uxTaskGetSystemStateImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_uxTaskGetSystemState_Unpriv
MPU_uxTaskGetSystemState_Priv
        b MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemState_Unpriv
        svc #SYSTEM_CALL_uxTaskGetSystemState
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark_Unpriv
MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark_Priv
        b MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark_Impl
MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
}

#ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2 == 1 )

config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2_Unpriv
MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2_Priv
        b MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2_Impl
MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
}

#ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ਖਾਲੀ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_xTaskGetCurrentTaskHandleImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
MPU_xTaskGetCurrentTaskHandle_Priv
        b MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
}

#ਜੇ_ਅੰਤ /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#ਜੇ ( INCLUDE_xTaskGetSchedulerState == 1 )

ਅਧਾਰ_Type_t MPU_xTaskGetSchedulerState( ਖਾਲੀ ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_xTaskGetSchedulerState( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_xTaskGetSchedulerStateImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_xTaskGetSchedulerState_Unpriv
MPU_xTaskGetSchedulerState_Priv
        b MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerState_Unpriv
        svc #SYSTEM_CALL_xTaskGetSchedulerState
}

#ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State_Unpriv
MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State_Priv
        b MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State_Impl
MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ,
                                     TickType_t * ਅਚਲ px_Ticks_ਮੰਜ਼ਿਲ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ,
                                     TickType_t * ਅਚਲ px_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ_Unpriv
MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ_Priv
        b MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ_Impl
MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_xTaskGenericNotifyImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_xTaskGenericNotify_Unpriv
MPU_xTaskGenericNotify_Priv
        b MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotify_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotify
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_Wait_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_Wait_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_xTaskGenericNotifyWaitImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_xTaskGenericNotifyWait_Unpriv
MPU_xTaskGenericNotifyWait_Priv
        b MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWait_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On,
                                      ਅਧਾਰ_Type_t x_Clear_ਗਿਣਤੀ_On_Exit,
                                      TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On,
                                            ਅਧਾਰ_Type_t x_Clear_ਗਿਣਤੀ_On_Exit,
                                            TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ulTaskGenericNotifyTakeImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
MPU_ulTaskGenericNotifyTake_Priv
        b MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTake_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_xTaskGenericNotifyStateClearImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
MPU_xTaskGenericNotifyStateClear_Priv
        b MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClear_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear( TaskHandle_t xTask,
                                            UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear,
                                            uint32_t ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear( TaskHandle_t xTask,
                                                  UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear,
                                                  uint32_t ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear_Unpriv
MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear_Priv
        b MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear_Impl
MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Generic_Send( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                  ਅਚਲ ਖਾਲੀ * ਅਚਲ pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ,
                                  TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait,
                                  ਅਚਲ ਅਧਾਰ_Type_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Generic_Send( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                        ਅਚਲ ਖਾਲੀ * ਅਚਲ pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ,
                                        TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait,
                                        ਅਚਲ ਅਧਾਰ_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਕਤਾਰ_Generic_Send_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਕਤਾਰ_Generic_Send_Unpriv
MPU_x_ਕਤਾਰ_Generic_Send_Priv
        b MPU_x_ਕਤਾਰ_Generic_Send_Impl
MPU_x_ਕਤਾਰ_Generic_Send_Unpriv
        svc #SYSTEM_CALL_xQueueGenericSend
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ_Unpriv
MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ_Priv
        b MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ_Impl
MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ_Unpriv
MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ_Priv
        b MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ_Impl
MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ_Unpriv
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Receive( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                              ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                              TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Receive( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                    ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                    TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਕਤਾਰ_Receive_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਕਤਾਰ_Receive_Unpriv
MPU_x_ਕਤਾਰ_Receive_Priv
        b MPU_x_ਕਤਾਰ_Receive_Impl
MPU_x_ਕਤਾਰ_Receive_Unpriv
        svc #SYSTEM_CALL_xQueueReceive
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Peek( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                           ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                           TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Peek( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                 ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                 TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਕਤਾਰ_Peek_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਕਤਾਰ_Peek_Unpriv
MPU_x_ਕਤਾਰ_Peek_Priv
        b MPU_x_ਕਤਾਰ_Peek_Impl
MPU_x_ਕਤਾਰ_Peek_Unpriv
        svc #SYSTEM_CALL_xQueuePeek
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Semaphore_Take( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                    TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Semaphore_Take( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                          TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਕਤਾਰ_Semaphore_Take_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਕਤਾਰ_Semaphore_Take_Unpriv
MPU_x_ਕਤਾਰ_Semaphore_Take_Priv
        b MPU_x_ਕਤਾਰ_Semaphore_Take_Impl
MPU_x_ਕਤਾਰ_Semaphore_Take_Unpriv
        svc #SYSTEM_CALL_xQueueSemaphoreTake
}
/*-----------------------------------------------------------*/

#ਜੇ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_x_ਕਤਾਰ_Get_Mutex_Holder( ਕਤਾਰ_Handle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_x_ਕਤਾਰ_Get_Mutex_Holder( ਕਤਾਰ_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਕਤਾਰ_Get_Mutex_Holder_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਕਤਾਰ_Get_Mutex_Holder_Unpriv
MPU_x_ਕਤਾਰ_Get_Mutex_Holder_Priv
        b MPU_x_ਕਤਾਰ_Get_Mutex_Holder_Impl
MPU_x_ਕਤਾਰ_Get_Mutex_Holder_Unpriv
        svc #SYSTEM_CALL_xQueueGetMutexHolder
}

#ਜੇ_ਅੰਤ /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_RECURSIVE_MUTEXES == 1 )

ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Take_Mutex_Recursive( ਕਤਾਰ_Handle_t xMutex,
                                         TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Take_Mutex_Recursive( ਕਤਾਰ_Handle_t xMutex,
                                               TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਕਤਾਰ_Take_Mutex_Recursive_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਕਤਾਰ_Take_Mutex_Recursive_Unpriv
MPU_x_ਕਤਾਰ_Take_Mutex_Recursive_Priv
        b MPU_x_ਕਤਾਰ_Take_Mutex_Recursive_Impl
MPU_x_ਕਤਾਰ_Take_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
}

#ਜੇ_ਅੰਤ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_RECURSIVE_MUTEXES == 1 )

ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Give_Mutex_Recursive( ਕਤਾਰ_Handle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Give_Mutex_Recursive( ਕਤਾਰ_Handle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਕਤਾਰ_Give_Mutex_Recursive_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਕਤਾਰ_Give_Mutex_Recursive_Unpriv
MPU_x_ਕਤਾਰ_Give_Mutex_Recursive_Priv
        b MPU_x_ਕਤਾਰ_Give_Mutex_Recursive_Impl
MPU_x_ਕਤਾਰ_Give_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
}

#ਜੇ_ਅੰਤ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )

ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ,
                                                ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ,
                                                      ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ_Unpriv
MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ_Priv
        b MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ_Impl
MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ_Unpriv
        svc #SYSTEM_CALL_xQueueSelectFromSet
}

#ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )

ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਕਤਾਰ_Or_Semaphore,
                               ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਕਤਾਰ_Or_Semaphore,
                                     ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ_Unpriv
MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ_Priv
        b MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ_Impl
MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0 )

ਖਾਲੀ MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                              ਅਚਲ ਅੱਖਰ * pcName ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                    ਅਚਲ ਅੱਖਰ * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry_Unpriv
MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry_Priv
        b MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry_Impl
MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#ਜੇ_ਅੰਤ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0 )

ਖਾਲੀ MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ_Unpriv
MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ_Priv
        b MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ_Impl
MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ_Unpriv
        svc #SYSTEM_CALL_vQueueUnregisterQueue
}

#ਜੇ_ਅੰਤ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0 )

ਅਚਲ ਅੱਖਰ * MPU_pc_ਕਤਾਰ_Get_Name( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) FREERTOS_SYSTEM_CALL;

__asm ਅਚਲ ਅੱਖਰ * MPU_pc_ਕਤਾਰ_Get_Name( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_pc_ਕਤਾਰ_Get_Name_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_pc_ਕਤਾਰ_Get_Name_Unpriv
MPU_pc_ਕਤਾਰ_Get_Name_Priv
        b MPU_pc_ਕਤਾਰ_Get_Name_Impl
MPU_pc_ਕਤਾਰ_Get_Name_Unpriv
        svc #SYSTEM_CALL_pcQueueGetName
}

#ਜੇ_ਅੰਤ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMERS == 1 )

ਖਾਲੀ * MPU_pvTimerGetTimerID( ਅਚਲ TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ * MPU_pvTimerGetTimerID( ਅਚਲ TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_pvTimerGetTimerIDImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_pvTimerGetTimerID_Unpriv
MPU_pvTimerGetTimerID_Priv
        b MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerID_Unpriv
        svc #SYSTEM_CALL_pvTimerGetTimerID
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMERS == 1 )

ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Timer_ID( TimerHandle_t xTimer,
                           ਖਾਲੀ * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Timer_ID( TimerHandle_t xTimer,
                                 ਖਾਲੀ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_v_Timer_ਸੈੱਟ_Timer_IDImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_v_Timer_ਸੈੱਟ_Timer_ID_Unpriv
MPU_v_Timer_ਸੈੱਟ_Timer_ID_Priv
        b MPU_v_Timer_ਸੈੱਟ_Timer_IDImpl
MPU_v_Timer_ਸੈੱਟ_Timer_ID_Unpriv
        svc #SYSTEM_CALL_vTimerSetTimerID
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMERS == 1 )

ਅਧਾਰ_Type_t MPU_x_Timer_Is_Timer_ਸਰਗਰਮ( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_Timer_Is_Timer_ਸਰਗਰਮ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_Timer_Is_Timer_ਸਰਗਰਮ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_Timer_Is_Timer_ਸਰਗਰਮ_Unpriv
MPU_x_Timer_Is_Timer_ਸਰਗਰਮ_Priv
        b MPU_x_Timer_Is_Timer_ਸਰਗਰਮ_Impl
MPU_x_Timer_Is_Timer_ਸਰਗਰਮ_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ਖਾਲੀ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ਖਾਲੀ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_xTimerGetTimerDaemonTaskHandleImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
MPU_xTimerGetTimerDaemonTaskHandle_Priv
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMERS == 1 )

ਅਧਾਰ_Type_t MPU_x_Timer_Generic_Command_From_Task_ਇੰਦਰਾਜ( ਅਚਲ xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_Timer_Generic_Command_From_Task_ਇੰਦਰਾਜ( ਅਚਲ xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_xTimerGenericCommandFromTaskImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
MPU_xTimerGenericCommandFromTask_Priv
        b MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTask_Unpriv
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMERS == 1 )

ਅਚਲ ਅੱਖਰ * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ਅਚਲ ਅੱਖਰ * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_pcTimerGetNameImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_pcTimerGetName_Unpriv
MPU_pcTimerGetName_Priv
        b MPU_pcTimerGetNameImpl
MPU_pcTimerGetName_Unpriv
        svc #SYSTEM_CALL_pcTimerGetName
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMERS == 1 )

ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer,
                              ਅਚਲ ਅਧਾਰ_Type_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer,
                                    ਅਚਲ ਅਧਾਰ_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ_Unpriv
MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ_Priv
        b MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ_Impl
MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ_Unpriv
        svc #SYSTEM_CALL_vTimerSetReloadMode
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMERS == 1 )

ਅਧਾਰ_Type_t MPU_x_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_Timer_Get_Reload_ਬਹੁਲਕ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_Timer_Get_Reload_ਬਹੁਲਕ_Unpriv
MPU_x_Timer_Get_Reload_ਬਹੁਲਕ_Priv
        b MPU_x_Timer_Get_Reload_ਬਹੁਲਕ_Impl
MPU_x_Timer_Get_Reload_ਬਹੁਲਕ_Unpriv
        svc #SYSTEM_CALL_xTimerGetReloadMode
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMERS == 1 )

UBaseType_t MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ_Unpriv
MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ_Priv
        b MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ_Impl
MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ_Unpriv
        svc #SYSTEM_CALL_uxTimerGetReloadMode
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_xTimerGetPeriodImpl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_xTimerGetPeriod_Unpriv
MPU_xTimerGetPeriod_Priv
        b MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriod_Unpriv
        svc #SYSTEM_CALL_xTimerGetPeriod
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TIMERS == 1 )

TickType_t MPU_x_Timer_Get_Expiry_ਸਮਾਂ( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Timer_Get_Expiry_ਸਮਾਂ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_Timer_Get_Expiry_ਸਮਾਂ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_Timer_Get_Expiry_ਸਮਾਂ_Unpriv
MPU_x_Timer_Get_Expiry_ਸਮਾਂ_Priv
        b MPU_x_Timer_Get_Expiry_ਸਮਾਂ_Impl
MPU_x_Timer_Get_Expiry_ਸਮਾਂ_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_EVENT_GROUPS == 1 )

Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_ਇੰਦਰਾਜ( ਅਚਲ x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Params_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_ਇੰਦਰਾਜ( ਅਚਲ x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Params_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Unpriv
MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Priv
        b MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Impl
MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Unpriv
        svc #SYSTEM_CALL_xEventGroupWaitBits
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_EVENT_GROUPS == 1 )

Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                      ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) FREERTOS_SYSTEM_CALL;

__asm Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                            ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ_Unpriv
MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ_Priv
        b MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ_Impl
MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ_Unpriv
        svc #SYSTEM_CALL_xEventGroupClearBits
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_EVENT_GROUPS == 1 )

Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                    ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ ) FREERTOS_SYSTEM_CALL;

__asm Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                          ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_Unpriv
MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_Priv
        b MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_Impl
MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_Unpriv
        svc #SYSTEM_CALL_xEventGroupSetBits
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_EVENT_GROUPS == 1 )

Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Sync( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                 ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                 ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For,
                                 TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) FREERTOS_SYSTEM_CALL;

__asm Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Sync( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                       ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                       ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For,
                                       TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_Event_ਸਮੂਹ_Sync_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_Event_ਸਮੂਹ_Sync_Unpriv
MPU_x_Event_ਸਮੂਹ_Sync_Priv
        b MPU_x_Event_ਸਮੂਹ_Sync_Impl
MPU_x_Event_ਸਮੂਹ_Sync_Unpriv
        svc #SYSTEM_CALL_xEventGroupSync
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ_Unpriv
MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ_Priv
        b MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ_Impl
MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ_Unpriv
        svc #SYSTEM_CALL_uxEventGroupGetNumber
}

#ਜੇ_ਅੰਤ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#ਜੇ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

ਖਾਲੀ MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ,
                               UBaseType_t ux_Event_ਸਮੂਹ_ਸੰਖਿਆ ) FREERTOS_SYSTEM_CALL;

__asm ਖਾਲੀ MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ,
                                     UBaseType_t ux_Event_ਸਮੂਹ_ਸੰਖਿਆ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ_Unpriv
MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ_Priv
        b MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ_Impl
MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ_Unpriv
        svc #SYSTEM_CALL_vEventGroupSetNumber
}

#ਜੇ_ਅੰਤ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Send( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                              ਅਚਲ ਖਾਲੀ * pv_Tx_ਅੰਕੜੇ,
                              size_t x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                              TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Send( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                    ਅਚਲ ਖਾਲੀ * pv_Tx_ਅੰਕੜੇ,
                                    size_t x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                    TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਧਾਰਾ_ਬਫਰ_Send_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਧਾਰਾ_ਬਫਰ_Send_Unpriv
MPU_x_ਧਾਰਾ_ਬਫਰ_Send_Priv
        b MPU_x_ਧਾਰਾ_ਬਫਰ_Send_Impl
MPU_x_ਧਾਰਾ_ਬਫਰ_Send_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSend
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Receive( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                 ਖਾਲੀ * pv_Rx_ਅੰਕੜੇ,
                                 size_t x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                 TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Receive( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                       ਖਾਲੀ * pv_Rx_ਅੰਕੜੇ,
                                       size_t x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                       TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਧਾਰਾ_ਬਫਰ_Receive_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਧਾਰਾ_ਬਫਰ_Receive_Unpriv
MPU_x_ਧਾਰਾ_ਬਫਰ_Receive_Priv
        b MPU_x_ਧਾਰਾ_ਬਫਰ_Receive_Impl
MPU_x_ਧਾਰਾ_ਬਫਰ_Receive_Unpriv
        svc #SYSTEM_CALL_xStreamBufferReceive
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ_Unpriv
MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ_Priv
        b MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ_Impl
MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ_Unpriv
MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ_Priv
        b MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ_Impl
MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ_Unpriv
MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ_Priv
        b MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ_Impl
MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ_Unpriv
MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ_Priv
        b MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ_Impl
MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level_Unpriv
MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level_Priv
        b MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level_Impl
MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ਬਾਹਰੀ MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ_Impl

    ਧੱਕੋ {r0}
    mrs r0, control
    tst r0, #1
    ਕੱਢੋ {r0}
    bne MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ_Unpriv
MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ_Priv
        b MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ_Impl
MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* configUSE_MPU_WRAPPERS_V1 == 0 */
