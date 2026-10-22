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
#परिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "queue.h"
#अन्तर्भाव "timers.h"
#अन्तर्भाव "event_groups.h"
#अन्तर्भाव "stream_buffer.h"
#अन्तर्भाव "mpu_prototypes.h"
#अन्तर्भाव "mpu_syscall_numbers.h"

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#यदि ( configUSE_MPU_WRAPPERS_V1 == 0 )

#यदि ( INCLUDE_xTaskDelayUntil == 1 )

आधारः_Type_t MPU_xTaskDelayUntil( TickType_t * ध्रुव pxPreviousWakeTime,
                                ध्रुव TickType_t xTimeIncrement ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_xTaskDelayUntil( TickType_t * ध्रुव pxPreviousWakeTime,
                                      ध्रुव TickType_t xTimeIncrement ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTaskDelayUntilImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTaskDelayUntil_Unpriv
MPU_xTaskDelayUntil_Priv
        b MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntil_Unpriv
        svc #SYSTEM_CALL_xTaskDelayUntil
}

#यदि_अन्तः /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( INCLUDE_xTaskAbortDelay == 1 )

आधारः_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTaskAbortDelayImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTaskAbortDelay_Unpriv
MPU_xTaskAbortDelay_Priv
        b MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelay_Unpriv
        svc #SYSTEM_CALL_xTaskAbortDelay
}

#यदि_अन्तः /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( INCLUDE_vTaskDelay == 1 )

शून्य MPU_vTaskDelay( ध्रुव TickType_t x_Ticks_गन्तव्यम्_Delay ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_vTaskDelay( ध्रुव TickType_t x_Ticks_गन्तव्यम्_Delay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_vTaskDelayImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_vTaskDelay_Unpriv
MPU_vTaskDelay_Priv
        b MPU_vTaskDelayImpl
MPU_vTaskDelay_Unpriv
        svc #SYSTEM_CALL_vTaskDelay
}

#यदि_अन्तः /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( INCLUDE_ux_Task_प्राथमिकता_Get == 1 )

UBaseType_t MPU_ux_Task_प्राथमिकता_Get( ध्रुव TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_प्राथमिकता_Get( ध्रुव TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ux_Task_प्राथमिकता_Get_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ux_Task_प्राथमिकता_Get_Unpriv
MPU_ux_Task_प्राथमिकता_Get_Priv
        b MPU_ux_Task_प्राथमिकता_Get_Impl
MPU_ux_Task_प्राथमिकता_Get_Unpriv
        svc #SYSTEM_CALL_uxTaskPriorityGet
}

#यदि_अन्तः /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_eTaskGetStateImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_eTaskGetState_Unpriv
MPU_eTaskGetState_Priv
        b MPU_eTaskGetStateImpl
MPU_eTaskGetState_Unpriv
        svc #SYSTEM_CALL_eTaskGetState
}

#यदि_अन्तः /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TRACE_FACILITY == 1 )

शून्य MPU_vTaskGetInfo( TaskHandle_t xTask,
                       Task_स्थितिः_t * px_Task_स्थितिः,
                       आधारः_Type_t x_Get_Free_राशिः_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_vTaskGetInfo( TaskHandle_t xTask,
                             Task_स्थितिः_t * px_Task_स्थितिः,
                             आधारः_Type_t x_Get_Free_राशिः_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_vTaskGetInfoImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_vTaskGetInfo_Unpriv
MPU_vTaskGetInfo_Priv
        b MPU_vTaskGetInfoImpl
MPU_vTaskGetInfo_Unpriv
        svc #SYSTEM_CALL_vTaskGetInfo
}

#यदि_अन्तः /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( शून्य ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( शून्य ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTaskGetIdleTaskHandleImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
MPU_xTaskGetIdleTaskHandle_Priv
        b MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
}

#यदि_अन्तः /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( INCLUDE_vTaskSuspend == 1 )

शून्य MPU_vTaskSuspend( TaskHandle_t x_Task_गन्तव्यम्_Suspend ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_vTaskSuspend( TaskHandle_t x_Task_गन्तव्यम्_Suspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_vTaskSuspendImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_vTaskSuspend_Unpriv
MPU_vTaskSuspend_Priv
        b MPU_vTaskSuspendImpl
MPU_vTaskSuspend_Unpriv
        svc #SYSTEM_CALL_vTaskSuspend
}

#यदि_अन्तः /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( INCLUDE_vTaskSuspend == 1 )

शून्य MPU_vTaskResume( TaskHandle_t x_Task_गन्तव्यम्_Resume ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_vTaskResume( TaskHandle_t x_Task_गन्तव्यम्_Resume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_vTaskResumeImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_vTaskResume_Unpriv
MPU_vTaskResume_Priv
        b MPU_vTaskResumeImpl
MPU_vTaskResume_Unpriv
        svc #SYSTEM_CALL_vTaskResume
}

#यदि_अन्तः /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_गणनम्( शून्य ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_गणनम्( शून्य ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_Task_Get_Tick_गणनम्_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_Task_Get_Tick_गणनम्_Unpriv
MPU_x_Task_Get_Tick_गणनम्_Priv
        b MPU_x_Task_Get_Tick_गणनम्_Impl
MPU_x_Task_Get_Tick_गणनम्_Unpriv
        svc #SYSTEM_CALL_xTaskGetTickCount
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks( शून्य ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks( शून्य ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks_Unpriv
MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks_Priv
        b MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks_Impl
MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#यदि ( config_GENERATE_सततम्_TIME_STATS == 1 )

config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_गणक( ध्रुव TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_गणक( ध्रुव TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ul_Task_Get_सततम्_Time_गणक_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ul_Task_Get_सततम्_Time_गणक_Unpriv
MPU_ul_Task_Get_सततम्_Time_गणक_Priv
        b MPU_ul_Task_Get_सततम्_Time_गणक_Impl
MPU_ul_Task_Get_सततम्_Time_गणक_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_GENERATE_सततम्_TIME_STATS == 1 )

config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_Percent( ध्रुव TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_Percent( ध्रुव TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ul_Task_Get_सततम्_Time_Percent_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ul_Task_Get_सततम्_Time_Percent_Unpriv
MPU_ul_Task_Get_सततम्_Time_Percent_Priv
        b MPU_ul_Task_Get_सततम्_Time_Percent_Impl
MPU_ul_Task_Get_सततम्_Time_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( ( config_GENERATE_सततम्_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_Percent( शून्य ) FREERTOS_SYSTEM_CALL;

__asm config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_Percent( शून्य ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ul_Task_Get_Idle_सततम्_Time_Percent_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ul_Task_Get_Idle_सततम्_Time_Percent_Unpriv
MPU_ul_Task_Get_Idle_सततम्_Time_Percent_Priv
        b MPU_ul_Task_Get_Idle_सततम्_Time_Percent_Impl
MPU_ul_Task_Get_Idle_सततम्_Time_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#यदि ( ( config_GENERATE_सततम्_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_गणक( शून्य ) FREERTOS_SYSTEM_CALL;

__asm config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_गणक( शून्य ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ul_Task_Get_Idle_सततम्_Time_गणक_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ul_Task_Get_Idle_सततम्_Time_गणक_Unpriv
MPU_ul_Task_Get_Idle_सततम्_Time_गणक_Priv
        b MPU_ul_Task_Get_Idle_सततम्_Time_गणक_Impl
MPU_ul_Task_Get_Idle_सततम्_Time_गणक_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )

शून्य MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्_Unpriv
MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्_Priv
        b MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्_Impl
MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#यदि_अन्तः /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )

TaskHookFunction_t MPU_x_Task_Get_Application_Task_चिह्नकम्( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_x_Task_Get_Application_Task_चिह्नकम्( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_Task_Get_Application_Task_चिह्नकम्_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_Task_Get_Application_Task_चिह्नकम्_Unpriv
MPU_x_Task_Get_Application_Task_चिह्नकम्_Priv
        b MPU_x_Task_Get_Application_Task_चिह्नकम्_Impl
MPU_x_Task_Get_Application_Task_चिह्नकम्_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#यदि_अन्तः /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_अङ्कः_THREAD_LOCAL_STORAGE_सूचकाः != 0 )

शून्य MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer( TaskHandle_t x_Task_गन्तव्यम्_समुच्चयः,
                                            आधारः_Type_t x_सूचकांक,
                                            शून्य * pv_मानम् ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer( TaskHandle_t x_Task_गन्तव्यम्_समुच्चयः,
                                                  आधारः_Type_t x_सूचकांक,
                                                  शून्य * pv_मानम् ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer_Unpriv
MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer_Priv
        b MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer_Impl
MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer_Unpriv
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
}

#यदि_अन्तः /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#यदि ( config_अङ्कः_THREAD_LOCAL_STORAGE_सूचकाः != 0 )

शून्य * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t x_Task_गन्तव्यम्_Query,
                                               आधारः_Type_t x_सूचकांक ) FREERTOS_SYSTEM_CALL;

__asm शून्य * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t x_Task_गन्तव्यम्_Query,
                                                     आधारः_Type_t x_सूचकांक ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_pvTaskGetThreadLocalStoragePointerImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_pvTaskGetThreadLocalStoragePointer_Unpriv
MPU_pvTaskGetThreadLocalStoragePointer_Priv
        b MPU_pvTaskGetThreadLocalStoragePointerImpl
MPU_pvTaskGetThreadLocalStoragePointer_Unpriv
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
}

#यदि_अन्तः /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( Task_स्थितिः_t * ध्रुव px_Task_स्थितिः_Array,
                                      ध्रुव UBaseType_t ux_Array_आकार,
                                      config_सततम्_TIME_गणक_TYPE * ध्रुव pul_योग_सततम्_Time ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( Task_स्थितिः_t * ध्रुव px_Task_स्थितिः_Array,
                                            ध्रुव UBaseType_t ux_Array_आकार,
                                            config_सततम्_TIME_गणक_TYPE * ध्रुव pul_योग_सततम्_Time ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_uxTaskGetSystemStateImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_uxTaskGetSystemState_Unpriv
MPU_uxTaskGetSystemState_Priv
        b MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemState_Unpriv
        svc #SYSTEM_CALL_uxTaskGetSystemState
}

#यदि_अन्तः /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark_Unpriv
MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark_Priv
        b MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark_Impl
MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
}

#यदि_अन्तः /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark2 == 1 )

config_राशिः_गभीरता_TYPE MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_राशिः_गभीरता_TYPE MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2_Unpriv
MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2_Priv
        b MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2_Impl
MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
}

#यदि_अन्तः /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( शून्य ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( शून्य ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTaskGetCurrentTaskHandleImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
MPU_xTaskGetCurrentTaskHandle_Priv
        b MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
}

#यदि_अन्तः /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#यदि ( INCLUDE_xTaskGetSchedulerState == 1 )

आधारः_Type_t MPU_xTaskGetSchedulerState( शून्य ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_xTaskGetSchedulerState( शून्य ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTaskGetSchedulerStateImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTaskGetSchedulerState_Unpriv
MPU_xTaskGetSchedulerState_Priv
        b MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerState_Unpriv
        svc #SYSTEM_CALL_xTaskGetSchedulerState
}

#यदि_अन्तः /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

शून्य MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम् ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम् ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State_Unpriv
MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State_Priv
        b MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State_Impl
MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

आधारः_Type_t MPU_x_Task_Check_For_Time_बहिर्गमनम्( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम्,
                                     TickType_t * ध्रुव px_Ticks_गन्तव्यम्_Wait ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_x_Task_Check_For_Time_बहिर्गमनम्( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम्,
                                     TickType_t * ध्रुव px_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_Task_Check_For_Time_बहिर्गमनम्_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_Task_Check_For_Time_बहिर्गमनम्_Unpriv
MPU_x_Task_Check_For_Time_बहिर्गमनम्_Priv
        b MPU_x_Task_Check_For_Time_बहिर्गमनम्_Impl
MPU_x_Task_Check_For_Time_बहिर्गमनम्_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

आधारः_Type_t MPU_x_Task_Generic_Notify_प्रविष्टिः( ध्रुव xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_x_Task_Generic_Notify_प्रविष्टिः( ध्रुव xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTaskGenericNotifyImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTaskGenericNotify_Unpriv
MPU_xTaskGenericNotify_Priv
        b MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotify_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotify
}

#यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

आधारः_Type_t MPU_x_Task_Generic_Notify_Wait_प्रविष्टिः( ध्रुव xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_x_Task_Generic_Notify_Wait_प्रविष्टिः( ध्रुव xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTaskGenericNotifyWaitImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTaskGenericNotifyWait_Unpriv
MPU_xTaskGenericNotifyWait_Priv
        b MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWait_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
}

#यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_सूचकांक_गन्तव्यम्_Wait_On,
                                      आधारः_Type_t x_Clear_गणनम्_On_Exit,
                                      TickType_t x_Ticks_गन्तव्यम्_Wait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_सूचकांक_गन्तव्यम्_Wait_On,
                                            आधारः_Type_t x_Clear_गणनम्_On_Exit,
                                            TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ulTaskGenericNotifyTakeImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
MPU_ulTaskGenericNotifyTake_Priv
        b MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTake_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
}

#यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

आधारः_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTaskGenericNotifyStateClearImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
MPU_xTaskGenericNotifyStateClear_Priv
        b MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClear_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
}

#यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_मानम्_Clear( TaskHandle_t xTask,
                                            UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear,
                                            uint32_t ul_द्वयङ्काः_गन्तव्यम्_Clear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_मानम्_Clear( TaskHandle_t xTask,
                                                  UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear,
                                                  uint32_t ul_द्वयङ्काः_गन्तव्यम्_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ul_Task_Generic_Notify_मानम्_Clear_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ul_Task_Generic_Notify_मानम्_Clear_Unpriv
MPU_ul_Task_Generic_Notify_मानम्_Clear_Priv
        b MPU_ul_Task_Generic_Notify_मानम्_Clear_Impl
MPU_ul_Task_Generic_Notify_मानम्_Clear_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
}

#यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

आधारः_Type_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                  ध्रुव शून्य * ध्रुव pv_Item_गन्तव्यम्_Queue,
                                  TickType_t x_Ticks_गन्तव्यम्_Wait,
                                  ध्रुव आधारः_Type_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                        ध्रुव शून्य * ध्रुव pv_Item_गन्तव्यम्_Queue,
                                        TickType_t x_Ticks_गन्तव्यम्_Wait,
                                        ध्रुव आधारः_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xQueueGenericSendImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xQueueGenericSend_Unpriv
MPU_xQueueGenericSend_Priv
        b MPU_xQueueGenericSendImpl
MPU_xQueueGenericSend_Unpriv
        svc #SYSTEM_CALL_xQueueGenericSend
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Queue_Messages_प्रतीक्षा( ध्रुव QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Queue_Messages_प्रतीक्षा( ध्रुव QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ux_Queue_Messages_प्रतीक्षा_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ux_Queue_Messages_प्रतीक्षा_Unpriv
MPU_ux_Queue_Messages_प्रतीक्षा_Priv
        b MPU_ux_Queue_Messages_प्रतीक्षा_Impl
MPU_ux_Queue_Messages_प्रतीक्षा_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Queue_Spaces_उपलब्धम्( ध्रुव QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Queue_Spaces_उपलब्धम्( ध्रुव QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ux_Queue_Spaces_उपलब्धम्_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ux_Queue_Spaces_उपलब्धम्_Unpriv
MPU_ux_Queue_Spaces_उपलब्धम्_Priv
        b MPU_ux_Queue_Spaces_उपलब्धम्_Impl
MPU_ux_Queue_Spaces_उपलब्धम्_Unpriv
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
}
/*-----------------------------------------------------------*/

आधारः_Type_t MPU_xQueueReceive( QueueHandle_t xQueue,
                              शून्य * ध्रुव pv_बफर,
                              TickType_t x_Ticks_गन्तव्यम्_Wait ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                    शून्य * ध्रुव pv_बफर,
                                    TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xQueueReceiveImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xQueueReceive_Unpriv
MPU_xQueueReceive_Priv
        b MPU_xQueueReceiveImpl
MPU_xQueueReceive_Unpriv
        svc #SYSTEM_CALL_xQueueReceive
}
/*-----------------------------------------------------------*/

आधारः_Type_t MPU_xQueuePeek( QueueHandle_t xQueue,
                           शून्य * ध्रुव pv_बफर,
                           TickType_t x_Ticks_गन्तव्यम्_Wait ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_xQueuePeek( QueueHandle_t xQueue,
                                 शून्य * ध्रुव pv_बफर,
                                 TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xQueuePeekImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xQueuePeek_Unpriv
MPU_xQueuePeek_Priv
        b MPU_xQueuePeekImpl
MPU_xQueuePeek_Unpriv
        svc #SYSTEM_CALL_xQueuePeek
}
/*-----------------------------------------------------------*/

आधारः_Type_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                    TickType_t x_Ticks_गन्तव्यम्_Wait ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                          TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xQueueSemaphoreTakeImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xQueueSemaphoreTake_Unpriv
MPU_xQueueSemaphoreTake_Priv
        b MPU_xQueueSemaphoreTakeImpl
MPU_xQueueSemaphoreTake_Unpriv
        svc #SYSTEM_CALL_xQueueSemaphoreTake
}
/*-----------------------------------------------------------*/

#यदि ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xQueueGetMutexHolderImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xQueueGetMutexHolder_Unpriv
MPU_xQueueGetMutexHolder_Priv
        b MPU_xQueueGetMutexHolderImpl
MPU_xQueueGetMutexHolder_Unpriv
        svc #SYSTEM_CALL_xQueueGetMutexHolder
}

#यदि_अन्तः /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_RECURSIVE_MUTEXES == 1 )

आधारः_Type_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                         TickType_t x_Ticks_गन्तव्यम्_Wait ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                               TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xQueueTakeMutexRecursiveImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xQueueTakeMutexRecursive_Unpriv
MPU_xQueueTakeMutexRecursive_Priv
        b MPU_xQueueTakeMutexRecursiveImpl
MPU_xQueueTakeMutexRecursive_Unpriv
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
}

#यदि_अन्तः /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_RECURSIVE_MUTEXES == 1 )

आधारः_Type_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xQueueGiveMutexRecursiveImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xQueueGiveMutexRecursive_Unpriv
MPU_xQueueGiveMutexRecursive_Priv
        b MPU_xQueueGiveMutexRecursiveImpl
MPU_xQueueGiveMutexRecursive_Unpriv
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
}

#यदि_अन्तः /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_QUEUE_SETS == 1 )

Queue_समुच्चयः_Member_Handle_t MPU_x_Queue_Select_From_समुच्चयः( Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः,
                                                ध्रुव TickType_t x_Ticks_गन्तव्यम्_Wait ) FREERTOS_SYSTEM_CALL;

__asm Queue_समुच्चयः_Member_Handle_t MPU_x_Queue_Select_From_समुच्चयः( Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः,
                                                      ध्रुव TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_Queue_Select_From_समुच्चयः_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_Queue_Select_From_समुच्चयः_Unpriv
MPU_x_Queue_Select_From_समुच्चयः_Priv
        b MPU_x_Queue_Select_From_समुच्चयः_Impl
MPU_x_Queue_Select_From_समुच्चयः_Unpriv
        svc #SYSTEM_CALL_xQueueSelectFromSet
}

#यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_QUEUE_SETS == 1 )

आधारः_Type_t MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः( Queue_समुच्चयः_Member_Handle_t xQueueOrSemaphore,
                               Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः( Queue_समुच्चयः_Member_Handle_t xQueueOrSemaphore,
                                     Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः_Unpriv
MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः_Priv
        b MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः_Impl
MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_QUEUE_REGISTRY_आकार > 0 )

शून्य MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry( QueueHandle_t xQueue,
                              ध्रुव वर्ण * pcName ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry( QueueHandle_t xQueue,
                                    ध्रुव वर्ण * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry_Unpriv
MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry_Priv
        b MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry_Impl
MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#यदि_अन्तः /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#यदि ( config_QUEUE_REGISTRY_आकार > 0 )

शून्य MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_vQueueUnregisterQueueImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_vQueueUnregisterQueue_Unpriv
MPU_vQueueUnregisterQueue_Priv
        b MPU_vQueueUnregisterQueueImpl
MPU_vQueueUnregisterQueue_Unpriv
        svc #SYSTEM_CALL_vQueueUnregisterQueue
}

#यदि_अन्तः /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#यदि ( config_QUEUE_REGISTRY_आकार > 0 )

ध्रुव वर्ण * MPU_pcQueueGetName( QueueHandle_t xQueue ) FREERTOS_SYSTEM_CALL;

__asm ध्रुव वर्ण * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_pcQueueGetNameImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_pcQueueGetName_Unpriv
MPU_pcQueueGetName_Priv
        b MPU_pcQueueGetNameImpl
MPU_pcQueueGetName_Unpriv
        svc #SYSTEM_CALL_pcQueueGetName
}

#यदि_अन्तः /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMERS == 1 )

शून्य * MPU_pvTimerGetTimerID( ध्रुव TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm शून्य * MPU_pvTimerGetTimerID( ध्रुव TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_pvTimerGetTimerIDImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_pvTimerGetTimerID_Unpriv
MPU_pvTimerGetTimerID_Priv
        b MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerID_Unpriv
        svc #SYSTEM_CALL_pvTimerGetTimerID
}

#यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMERS == 1 )

शून्य MPU_v_Timer_समुच्चयः_Timer_ID( TimerHandle_t xTimer,
                           शून्य * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_v_Timer_समुच्चयः_Timer_ID( TimerHandle_t xTimer,
                                 शून्य * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_v_Timer_समुच्चयः_Timer_IDImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_v_Timer_समुच्चयः_Timer_ID_Unpriv
MPU_v_Timer_समुच्चयः_Timer_ID_Priv
        b MPU_v_Timer_समुच्चयः_Timer_IDImpl
MPU_v_Timer_समुच्चयः_Timer_ID_Unpriv
        svc #SYSTEM_CALL_vTimerSetTimerID
}

#यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMERS == 1 )

आधारः_Type_t MPU_x_Timer_Is_Timer_सक्रिय( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_x_Timer_Is_Timer_सक्रिय( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_Timer_Is_Timer_सक्रिय_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_Timer_Is_Timer_सक्रिय_Unpriv
MPU_x_Timer_Is_Timer_सक्रिय_Priv
        b MPU_x_Timer_Is_Timer_सक्रिय_Impl
MPU_x_Timer_Is_Timer_सक्रिय_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( शून्य ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( शून्य ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTimerGetTimerDaemonTaskHandleImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
MPU_xTimerGetTimerDaemonTaskHandle_Priv
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
}

#यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMERS == 1 )

आधारः_Type_t MPU_x_Timer_Generic_Command_From_Task_प्रविष्टिः( ध्रुव xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_x_Timer_Generic_Command_From_Task_प्रविष्टिः( ध्रुव xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTimerGenericCommandFromTaskImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
MPU_xTimerGenericCommandFromTask_Priv
        b MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTask_Unpriv
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
}

#यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMERS == 1 )

ध्रुव वर्ण * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ध्रुव वर्ण * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_pcTimerGetNameImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_pcTimerGetName_Unpriv
MPU_pcTimerGetName_Priv
        b MPU_pcTimerGetNameImpl
MPU_pcTimerGetName_Unpriv
        svc #SYSTEM_CALL_pcTimerGetName
}

#यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMERS == 1 )

शून्य MPU_v_Timer_समुच्चयः_Reload_बहुलकम्( TimerHandle_t xTimer,
                              ध्रुव आधारः_Type_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_v_Timer_समुच्चयः_Reload_बहुलकम्( TimerHandle_t xTimer,
                                    ध्रुव आधारः_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_v_Timer_समुच्चयः_Reload_बहुलकम्_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_v_Timer_समुच्चयः_Reload_बहुलकम्_Unpriv
MPU_v_Timer_समुच्चयः_Reload_बहुलकम्_Priv
        b MPU_v_Timer_समुच्चयः_Reload_बहुलकम्_Impl
MPU_v_Timer_समुच्चयः_Reload_बहुलकम्_Unpriv
        svc #SYSTEM_CALL_vTimerSetReloadMode
}

#यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMERS == 1 )

आधारः_Type_t MPU_x_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_x_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_Timer_Get_Reload_बहुलकम्_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_Timer_Get_Reload_बहुलकम्_Unpriv
MPU_x_Timer_Get_Reload_बहुलकम्_Priv
        b MPU_x_Timer_Get_Reload_बहुलकम्_Impl
MPU_x_Timer_Get_Reload_बहुलकम्_Unpriv
        svc #SYSTEM_CALL_xTimerGetReloadMode
}

#यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMERS == 1 )

UBaseType_t MPU_ux_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ux_Timer_Get_Reload_बहुलकम्_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ux_Timer_Get_Reload_बहुलकम्_Unpriv
MPU_ux_Timer_Get_Reload_बहुलकम्_Priv
        b MPU_ux_Timer_Get_Reload_बहुलकम्_Impl
MPU_ux_Timer_Get_Reload_बहुलकम्_Unpriv
        svc #SYSTEM_CALL_uxTimerGetReloadMode
}

#यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTimerGetPeriodImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTimerGetPeriod_Unpriv
MPU_xTimerGetPeriod_Priv
        b MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriod_Unpriv
        svc #SYSTEM_CALL_xTimerGetPeriod
}

#यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_xTimerGetExpiryTimeImpl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_xTimerGetExpiryTime_Unpriv
MPU_xTimerGetExpiryTime_Priv
        b MPU_xTimerGetExpiryTimeImpl
MPU_xTimerGetExpiryTime_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_EVENT_GROUPS == 1 )

Event_द्वयङ्काः_t MPU_x_Event_गणः_Wait_द्वयङ्काः_प्रविष्टिः( ध्रुव x_Event_गणः_Wait_द्वयङ्काः_Params_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm Event_द्वयङ्काः_t MPU_x_Event_गणः_Wait_द्वयङ्काः_प्रविष्टिः( ध्रुव x_Event_गणः_Wait_द्वयङ्काः_Params_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_Event_गणः_Wait_द्वयङ्काः_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_Event_गणः_Wait_द्वयङ्काः_Unpriv
MPU_x_Event_गणः_Wait_द्वयङ्काः_Priv
        b MPU_x_Event_गणः_Wait_द्वयङ्काः_Impl
MPU_x_Event_गणः_Wait_द्वयङ्काः_Unpriv
        svc #SYSTEM_CALL_xEventGroupWaitBits
}

#यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_EVENT_GROUPS == 1 )

Event_द्वयङ्काः_t MPU_x_Event_गणः_Clear_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                      ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Clear ) FREERTOS_SYSTEM_CALL;

__asm Event_द्वयङ्काः_t MPU_x_Event_गणः_Clear_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                            ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_Event_गणः_Clear_द्वयङ्काः_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_Event_गणः_Clear_द्वयङ्काः_Unpriv
MPU_x_Event_गणः_Clear_द्वयङ्काः_Priv
        b MPU_x_Event_गणः_Clear_द्वयङ्काः_Impl
MPU_x_Event_गणः_Clear_द्वयङ्काः_Unpriv
        svc #SYSTEM_CALL_xEventGroupClearBits
}

#यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_EVENT_GROUPS == 1 )

Event_द्वयङ्काः_t MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                    ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः ) FREERTOS_SYSTEM_CALL;

__asm Event_द्वयङ्काः_t MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                          ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः_Unpriv
MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः_Priv
        b MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः_Impl
MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः_Unpriv
        svc #SYSTEM_CALL_xEventGroupSetBits
}

#यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( configUSE_EVENT_GROUPS == 1 )

Event_द्वयङ्काः_t MPU_x_Event_गणः_Sync( Event_गणः_Handle_t x_Event_गणः,
                                 ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः,
                                 ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Wait_For,
                                 TickType_t x_Ticks_गन्तव्यम्_Wait ) FREERTOS_SYSTEM_CALL;

__asm Event_द्वयङ्काः_t MPU_x_Event_गणः_Sync( Event_गणः_Handle_t x_Event_गणः,
                                       ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः,
                                       ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Wait_For,
                                       TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_Event_गणः_Sync_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_Event_गणः_Sync_Unpriv
MPU_x_Event_गणः_Sync_Priv
        b MPU_x_Event_गणः_Sync_Impl
MPU_x_Event_गणः_Sync_Unpriv
        svc #SYSTEM_CALL_xEventGroupSync
}

#यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_गणः_Get_सङ्ख्या( शून्य * x_Event_गणः ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_गणः_Get_सङ्ख्या( शून्य * x_Event_गणः ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_ux_Event_गणः_Get_सङ्ख्या_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_ux_Event_गणः_Get_सङ्ख्या_Unpriv
MPU_ux_Event_गणः_Get_सङ्ख्या_Priv
        b MPU_ux_Event_गणः_Get_सङ्ख्या_Impl
MPU_ux_Event_गणः_Get_सङ्ख्या_Unpriv
        svc #SYSTEM_CALL_uxEventGroupGetNumber
}

#यदि_अन्तः /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#यदि ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

शून्य MPU_v_Event_गणः_समुच्चयः_सङ्ख्या( शून्य * x_Event_गणः,
                               UBaseType_t ux_Event_गणः_सङ्ख्या ) FREERTOS_SYSTEM_CALL;

__asm शून्य MPU_v_Event_गणः_समुच्चयः_सङ्ख्या( शून्य * x_Event_गणः,
                                     UBaseType_t ux_Event_गणः_सङ्ख्या ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_v_Event_गणः_समुच्चयः_सङ्ख्या_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_v_Event_गणः_समुच्चयः_सङ्ख्या_Unpriv
MPU_v_Event_गणः_समुच्चयः_सङ्ख्या_Priv
        b MPU_v_Event_गणः_समुच्चयः_सङ्ख्या_Impl
MPU_v_Event_गणः_समुच्चयः_सङ्ख्या_Unpriv
        svc #SYSTEM_CALL_vEventGroupSetNumber
}

#यदि_अन्तः /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

size_t MPU_x_प्रवाहः_बफर_Send( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                              ध्रुव शून्य * pv_Tx_दत्त,
                              size_t x_दत्त_दीर्घता_अष्टकानि,
                              TickType_t x_Ticks_गन्तव्यम्_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_प्रवाहः_बफर_Send( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                    ध्रुव शून्य * pv_Tx_दत्त,
                                    size_t x_दत्त_दीर्घता_अष्टकानि,
                                    TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_प्रवाहः_बफर_Send_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_प्रवाहः_बफर_Send_Unpriv
MPU_x_प्रवाहः_बफर_Send_Priv
        b MPU_x_प्रवाहः_बफर_Send_Impl
MPU_x_प्रवाहः_बफर_Send_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSend
}

#यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

size_t MPU_x_प्रवाहः_बफर_Receive( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                 शून्य * pv_Rx_दत्त,
                                 size_t x_बफर_दीर्घता_अष्टकानि,
                                 TickType_t x_Ticks_गन्तव्यम्_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_प्रवाहः_बफर_Receive( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                       शून्य * pv_Rx_दत्त,
                                       size_t x_बफर_दीर्घता_अष्टकानि,
                                       TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_प्रवाहः_बफर_Receive_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_प्रवाहः_बफर_Receive_Unpriv
MPU_x_प्रवाहः_बफर_Receive_Priv
        b MPU_x_प्रवाहः_बफर_Receive_Impl
MPU_x_प्रवाहः_बफर_Receive_Unpriv
        svc #SYSTEM_CALL_xStreamBufferReceive
}

#यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_पूर्णम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_पूर्णम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_प्रवाहः_बफर_Is_पूर्णम्_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_प्रवाहः_बफर_Is_पूर्णम्_Unpriv
MPU_x_प्रवाहः_बफर_Is_पूर्णम्_Priv
        b MPU_x_प्रवाहः_बफर_Is_पूर्णम्_Impl
MPU_x_प्रवाहः_बफर_Is_पूर्णम्_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_रिक्तानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_रिक्तानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_प्रवाहः_बफर_Is_रिक्तानि_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_प्रवाहः_बफर_Is_रिक्तानि_Unpriv
MPU_x_प्रवाहः_बफर_Is_रिक्तानि_Priv
        b MPU_x_प्रवाहः_बफर_Is_रिक्तानि_Impl
MPU_x_प्रवाहः_बफर_Is_रिक्तानि_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

size_t MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्_Unpriv
MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्_Priv
        b MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्_Impl
MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
}

#यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

size_t MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्_Unpriv
MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्_Priv
        b MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्_Impl
MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

आधारः_Type_t MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm आधारः_Type_t MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level_Unpriv
MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level_Priv
        b MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level_Impl
MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
}

#यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

size_t MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    बाह्य MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि_Impl

    प्रक्षिप {r0}
    mrs r0, control
    tst r0, #1
    निष्कासय {r0}
    bne MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि_Unpriv
MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि_Priv
        b MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि_Impl
MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि_अन्तः /* configUSE_MPU_WRAPPERS_V1 == 0 */
