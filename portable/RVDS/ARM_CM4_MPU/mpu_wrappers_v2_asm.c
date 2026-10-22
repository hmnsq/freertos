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
#ವ್ಯಾಖ್ಯಾನಿಸು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "queue.h"
#ಅನ್ತರ್ಭಾವ "timers.h"
#ಅನ್ತರ್ಭಾವ "event_groups.h"
#ಅನ್ತರ್ಭಾವ "stream_buffer.h"
#ಅನ್ತರ್ಭಾವ "mpu_prototypes.h"
#ಅನ್ತರ್ಭಾವ "mpu_syscall_numbers.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_MPU_WRAPPERS_V1 == 0 )

#ಆದರೆ ( INCLUDE_xTaskDelayUntil == 1 )

ತಳ_Type_t MPU_xTaskDelayUntil( TickType_t * ಸ್ಥಿರಾಂಕ px_ಹಿಂದಿನ_Wake_ಸಮಯ,
                                ಸ್ಥಿರಾಂಕ TickType_t x_ಸಮಯ_Increment ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_xTaskDelayUntil( TickType_t * ಸ್ಥಿರಾಂಕ px_ಹಿಂದಿನ_Wake_ಸಮಯ,
                                      ಸ್ಥಿರಾಂಕ TickType_t x_ಸಮಯ_Increment ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_xTaskDelayUntilImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_xTaskDelayUntil_Unpriv
MPU_xTaskDelayUntil_Priv
        b MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntil_Unpriv
        svc #SYSTEM_CALL_xTaskDelayUntil
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( INCLUDE_xTaskAbortDelay == 1 )

ತಳ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_xTaskAbortDelayImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_xTaskAbortDelay_Unpriv
MPU_xTaskAbortDelay_Priv
        b MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelay_Unpriv
        svc #SYSTEM_CALL_xTaskAbortDelay
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( INCLUDE_vTaskDelay == 1 )

ಶೂನ್ಯ MPU_vTaskDelay( ಸ್ಥಿರಾಂಕ TickType_t x_Ticks_ಗಮ್ಯ_Delay ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_vTaskDelay( ಸ್ಥಿರಾಂಕ TickType_t x_Ticks_ಗಮ್ಯ_Delay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_vTaskDelayImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_vTaskDelay_Unpriv
MPU_vTaskDelay_Priv
        b MPU_vTaskDelayImpl
MPU_vTaskDelay_Unpriv
        svc #SYSTEM_CALL_vTaskDelay
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( INCLUDE_ux_Task_ಆದ್ಯತೆ_Get == 1 )

UBaseType_t MPU_ux_Task_ಆದ್ಯತೆ_Get( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_ಆದ್ಯತೆ_Get( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ux_Task_ಆದ್ಯತೆ_Get_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ux_Task_ಆದ್ಯತೆ_Get_Unpriv
MPU_ux_Task_ಆದ್ಯತೆ_Get_Priv
        b MPU_ux_Task_ಆದ್ಯತೆ_Get_Impl
MPU_ux_Task_ಆದ್ಯತೆ_Get_Unpriv
        svc #SYSTEM_CALL_uxTaskPriorityGet
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_eTaskGetStateImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_eTaskGetState_Unpriv
MPU_eTaskGetState_Priv
        b MPU_eTaskGetStateImpl
MPU_eTaskGetState_Unpriv
        svc #SYSTEM_CALL_eTaskGetState
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TRACE_FACILITY == 1 )

ಶೂನ್ಯ MPU_vTaskGetInfo( TaskHandle_t xTask,
                       Task_ಸ್ಥಿತಿ_t * px_Task_ಸ್ಥಿತಿ,
                       ತಳ_Type_t x_Get_Free_ರಾಶಿ_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_vTaskGetInfo( TaskHandle_t xTask,
                             Task_ಸ್ಥಿತಿ_t * px_Task_ಸ್ಥಿತಿ,
                             ತಳ_Type_t x_Get_Free_ರಾಶಿ_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_vTaskGetInfoImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_vTaskGetInfo_Unpriv
MPU_vTaskGetInfo_Priv
        b MPU_vTaskGetInfoImpl
MPU_vTaskGetInfo_Unpriv
        svc #SYSTEM_CALL_vTaskGetInfo
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_xTaskGetIdleTaskHandleImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
MPU_xTaskGetIdleTaskHandle_Priv
        b MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( INCLUDE_vTaskSuspend == 1 )

ಶೂನ್ಯ MPU_vTaskSuspend( TaskHandle_t x_Task_ಗಮ್ಯ_Suspend ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_vTaskSuspend( TaskHandle_t x_Task_ಗಮ್ಯ_Suspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_vTaskSuspendImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_vTaskSuspend_Unpriv
MPU_vTaskSuspend_Priv
        b MPU_vTaskSuspendImpl
MPU_vTaskSuspend_Unpriv
        svc #SYSTEM_CALL_vTaskSuspend
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( INCLUDE_vTaskSuspend == 1 )

ಶೂನ್ಯ MPU_vTaskResume( TaskHandle_t x_Task_ಗಮ್ಯ_Resume ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_vTaskResume( TaskHandle_t x_Task_ಗಮ್ಯ_Resume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_vTaskResumeImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_vTaskResume_Unpriv
MPU_vTaskResume_Priv
        b MPU_vTaskResumeImpl
MPU_vTaskResume_Unpriv
        svc #SYSTEM_CALL_vTaskResume
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_Task_Get_Tick_ಎಣಿಕೆ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_Task_Get_Tick_ಎಣಿಕೆ_Unpriv
MPU_x_Task_Get_Tick_ಎಣಿಕೆ_Priv
        b MPU_x_Task_Get_Tick_ಎಣಿಕೆ_Impl
MPU_x_Task_Get_Tick_ಎಣಿಕೆ_Unpriv
        svc #SYSTEM_CALL_xTaskGetTickCount
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks_Unpriv
MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks_Priv
        b MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks_Impl
MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 )

config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter_Unpriv
MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter_Priv
        b MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter_Impl
MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 )

config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent_Unpriv
MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent_Priv
        b MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent_Impl
MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;

__asm config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent_Unpriv
MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent_Priv
        b MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent_Impl
MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;

__asm config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter_Unpriv
MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter_Priv
        b MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter_Impl
MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )

ಶೂನ್ಯ MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್_Unpriv
MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್_Priv
        b MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್_Impl
MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )

TaskHookFunction_t MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್_Unpriv
MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್_Priv
        b MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್_Impl
MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_ಸೂಚಕಗಳು != 0 )

ಶೂನ್ಯ MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ( TaskHandle_t x_Task_ಗಮ್ಯ_ಗಣ,
                                            ತಳ_Type_t x_ಸೂಚ್ಯಂಕ,
                                            ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ( TaskHandle_t x_Task_ಗಮ್ಯ_ಗಣ,
                                                  ತಳ_Type_t x_ಸೂಚ್ಯಂಕ,
                                                  ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ_Unpriv
MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ_Priv
        b MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ_Impl
MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ_Unpriv
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_ಸೂಚಕಗಳು != 0 )

ಶೂನ್ಯ * MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ( TaskHandle_t x_Task_ಗಮ್ಯ_Query,
                                               ತಳ_Type_t x_ಸೂಚ್ಯಂಕ ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ * MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ( TaskHandle_t x_Task_ಗಮ್ಯ_Query,
                                                     ತಳ_Type_t x_ಸೂಚ್ಯಂಕ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ_Unpriv
MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ_Priv
        b MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ_Impl
MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ_Unpriv
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( Task_ಸ್ಥಿತಿ_t * ಸ್ಥಿರಾಂಕ px_Task_ಸ್ಥಿತಿ_Array,
                                      ಸ್ಥಿರಾಂಕ UBaseType_t ux_Array_ಗಾತ್ರ,
                                      config_ಸತತ_ಸಮಯ_COUNTER_TYPE * ಸ್ಥಿರಾಂಕ pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( Task_ಸ್ಥಿತಿ_t * ಸ್ಥಿರಾಂಕ px_Task_ಸ್ಥಿತಿ_Array,
                                            ಸ್ಥಿರಾಂಕ UBaseType_t ux_Array_ಗಾತ್ರ,
                                            config_ಸತತ_ಸಮಯ_COUNTER_TYPE * ಸ್ಥಿರಾಂಕ pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_uxTaskGetSystemStateImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_uxTaskGetSystemState_Unpriv
MPU_uxTaskGetSystemState_Priv
        b MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemState_Unpriv
        svc #SYSTEM_CALL_uxTaskGetSystemState
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark_Unpriv
MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark_Priv
        b MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark_Impl
MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2 == 1 )

config_ರಾಶಿ_ಆಳ_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_ರಾಶಿ_ಆಳ_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2_Unpriv
MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2_Priv
        b MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2_Impl
MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_xTaskGetCurrentTaskHandleImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
MPU_xTaskGetCurrentTaskHandle_Priv
        b MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( INCLUDE_xTaskGetSchedulerState == 1 )

ತಳ_Type_t MPU_xTaskGetSchedulerState( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_xTaskGetSchedulerState( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_xTaskGetSchedulerStateImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_xTaskGetSchedulerState_Unpriv
MPU_xTaskGetSchedulerState_Priv
        b MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerState_Unpriv
        svc #SYSTEM_CALL_xTaskGetSchedulerState
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

ಶೂನ್ಯ MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State_Unpriv
MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State_Priv
        b MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State_Impl
MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

ತಳ_Type_t MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು,
                                     TickType_t * ಸ್ಥಿರಾಂಕ px_Ticks_ಗಮ್ಯ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು,
                                     TickType_t * ಸ್ಥಿರಾಂಕ px_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು_Unpriv
MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು_Priv
        b MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು_Impl
MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

ತಳ_Type_t MPU_x_Task_Generic_Notify_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_Task_Generic_Notify_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_xTaskGenericNotifyImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_xTaskGenericNotify_Unpriv
MPU_xTaskGenericNotify_Priv
        b MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotify_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotify
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

ತಳ_Type_t MPU_x_Task_Generic_Notify_Wait_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_Task_Generic_Notify_Wait_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_xTaskGenericNotifyWaitImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_xTaskGenericNotifyWait_Unpriv
MPU_xTaskGenericNotifyWait_Priv
        b MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWait_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On,
                                      ತಳ_Type_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                      TickType_t x_Ticks_ಗಮ್ಯ_Wait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On,
                                            ತಳ_Type_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                            TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ulTaskGenericNotifyTakeImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
MPU_ulTaskGenericNotifyTake_Priv
        b MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTake_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

ತಳ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_xTaskGenericNotifyStateClearImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
MPU_xTaskGenericNotifyStateClear_Priv
        b MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClear_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( TaskHandle_t xTask,
                                            UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear,
                                            uint32_t ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( TaskHandle_t xTask,
                                                  UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear,
                                                  uint32_t ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear_Unpriv
MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear_Priv
        b MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear_Impl
MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

ತಳ_Type_t MPU_x_ಸರತಿ_Generic_Send( ಸರತಿ_Handle_t x_ಸರತಿ,
                                  ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ,
                                  TickType_t x_Ticks_ಗಮ್ಯ_Wait,
                                  ಸ್ಥಿರಾಂಕ ತಳ_Type_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_ಸರತಿ_Generic_Send( ಸರತಿ_Handle_t x_ಸರತಿ,
                                        ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ,
                                        TickType_t x_Ticks_ಗಮ್ಯ_Wait,
                                        ಸ್ಥಿರಾಂಕ ತಳ_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಸರತಿ_Generic_Send_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಸರತಿ_Generic_Send_Unpriv
MPU_x_ಸರತಿ_Generic_Send_Priv
        b MPU_x_ಸರತಿ_Generic_Send_Impl
MPU_x_ಸರತಿ_Generic_Send_Unpriv
        svc #SYSTEM_CALL_xQueueGenericSend
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ_Unpriv
MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ_Priv
        b MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ_Impl
MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ_Unpriv
MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ_Priv
        b MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ_Impl
MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ_Unpriv
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
}
/*-----------------------------------------------------------*/

ತಳ_Type_t MPU_x_ಸರತಿ_Receive( ಸರತಿ_Handle_t x_ಸರತಿ,
                              ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                              TickType_t x_Ticks_ಗಮ್ಯ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_ಸರತಿ_Receive( ಸರತಿ_Handle_t x_ಸರತಿ,
                                    ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                                    TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಸರತಿ_Receive_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಸರತಿ_Receive_Unpriv
MPU_x_ಸರತಿ_Receive_Priv
        b MPU_x_ಸರತಿ_Receive_Impl
MPU_x_ಸರತಿ_Receive_Unpriv
        svc #SYSTEM_CALL_xQueueReceive
}
/*-----------------------------------------------------------*/

ತಳ_Type_t MPU_x_ಸರತಿ_Peek( ಸರತಿ_Handle_t x_ಸರತಿ,
                           ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                           TickType_t x_Ticks_ಗಮ್ಯ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_ಸರತಿ_Peek( ಸರತಿ_Handle_t x_ಸರತಿ,
                                 ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                                 TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಸರತಿ_Peek_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಸರತಿ_Peek_Unpriv
MPU_x_ಸರತಿ_Peek_Priv
        b MPU_x_ಸರತಿ_Peek_Impl
MPU_x_ಸರತಿ_Peek_Unpriv
        svc #SYSTEM_CALL_xQueuePeek
}
/*-----------------------------------------------------------*/

ತಳ_Type_t MPU_x_ಸರತಿ_Semaphore_Take( ಸರತಿ_Handle_t x_ಸರತಿ,
                                    TickType_t x_Ticks_ಗಮ್ಯ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_ಸರತಿ_Semaphore_Take( ಸರತಿ_Handle_t x_ಸರತಿ,
                                          TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಸರತಿ_Semaphore_Take_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಸರತಿ_Semaphore_Take_Unpriv
MPU_x_ಸರತಿ_Semaphore_Take_Priv
        b MPU_x_ಸರತಿ_Semaphore_Take_Impl
MPU_x_ಸರತಿ_Semaphore_Take_Unpriv
        svc #SYSTEM_CALL_xQueueSemaphoreTake
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_x_ಸರತಿ_Get_Mutex_Holder( ಸರತಿ_Handle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_x_ಸರತಿ_Get_Mutex_Holder( ಸರತಿ_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಸರತಿ_Get_Mutex_Holder_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಸರತಿ_Get_Mutex_Holder_Unpriv
MPU_x_ಸರತಿ_Get_Mutex_Holder_Priv
        b MPU_x_ಸರತಿ_Get_Mutex_Holder_Impl
MPU_x_ಸರತಿ_Get_Mutex_Holder_Unpriv
        svc #SYSTEM_CALL_xQueueGetMutexHolder
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_RECURSIVE_MUTEXES == 1 )

ತಳ_Type_t MPU_x_ಸರತಿ_Take_Mutex_Recursive( ಸರತಿ_Handle_t xMutex,
                                         TickType_t x_Ticks_ಗಮ್ಯ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_ಸರತಿ_Take_Mutex_Recursive( ಸರತಿ_Handle_t xMutex,
                                               TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಸರತಿ_Take_Mutex_Recursive_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಸರತಿ_Take_Mutex_Recursive_Unpriv
MPU_x_ಸರತಿ_Take_Mutex_Recursive_Priv
        b MPU_x_ಸರತಿ_Take_Mutex_Recursive_Impl
MPU_x_ಸರತಿ_Take_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_RECURSIVE_MUTEXES == 1 )

ತಳ_Type_t MPU_x_ಸರತಿ_Give_Mutex_Recursive( ಸರತಿ_Handle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_ಸರತಿ_Give_Mutex_Recursive( ಸರತಿ_Handle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಸರತಿ_Give_Mutex_Recursive_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಸರತಿ_Give_Mutex_Recursive_Unpriv
MPU_x_ಸರತಿ_Give_Mutex_Recursive_Priv
        b MPU_x_ಸರತಿ_Give_Mutex_Recursive_Impl
MPU_x_ಸರತಿ_Give_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )

ಸರತಿ_ಗಣ_Member_Handle_t MPU_x_ಸರತಿ_Select_From_ಗಣ( ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ,
                                                ಸ್ಥಿರಾಂಕ TickType_t x_Ticks_ಗಮ್ಯ_Wait ) FREERTOS_SYSTEM_CALL;

__asm ಸರತಿ_ಗಣ_Member_Handle_t MPU_x_ಸರತಿ_Select_From_ಗಣ( ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ,
                                                      ಸ್ಥಿರಾಂಕ TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಸರತಿ_Select_From_ಗಣ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಸರತಿ_Select_From_ಗಣ_Unpriv
MPU_x_ಸರತಿ_Select_From_ಗಣ_Priv
        b MPU_x_ಸರತಿ_Select_From_ಗಣ_Impl
MPU_x_ಸರತಿ_Select_From_ಗಣ_Unpriv
        svc #SYSTEM_CALL_xQueueSelectFromSet
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )

ತಳ_Type_t MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ( ಸರತಿ_ಗಣ_Member_Handle_t x_ಸರತಿ_Or_Semaphore,
                               ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ( ಸರತಿ_ಗಣ_Member_Handle_t x_ಸರತಿ_Or_Semaphore,
                                     ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ_Unpriv
MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ_Priv
        b MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ_Impl
MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0 )

ಶೂನ್ಯ MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry( ಸರತಿ_Handle_t x_ಸರತಿ,
                              ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcName ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry( ಸರತಿ_Handle_t x_ಸರತಿ,
                                    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry_Unpriv
MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry_Priv
        b MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry_Impl
MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0 )

ಶೂನ್ಯ MPU_v_ಸರತಿ_Unregister_ಸರತಿ( ಸರತಿ_Handle_t x_ಸರತಿ ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_v_ಸರತಿ_Unregister_ಸರತಿ( ಸರತಿ_Handle_t x_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_v_ಸರತಿ_Unregister_ಸರತಿ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_v_ಸರತಿ_Unregister_ಸರತಿ_Unpriv
MPU_v_ಸರತಿ_Unregister_ಸರತಿ_Priv
        b MPU_v_ಸರತಿ_Unregister_ಸರತಿ_Impl
MPU_v_ಸರತಿ_Unregister_ಸರತಿ_Unpriv
        svc #SYSTEM_CALL_vQueueUnregisterQueue
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0 )

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pc_ಸರತಿ_Get_Name( ಸರತಿ_Handle_t x_ಸರತಿ ) FREERTOS_SYSTEM_CALL;

__asm ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pc_ಸರತಿ_Get_Name( ಸರತಿ_Handle_t x_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_pc_ಸರತಿ_Get_Name_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_pc_ಸರತಿ_Get_Name_Unpriv
MPU_pc_ಸರತಿ_Get_Name_Priv
        b MPU_pc_ಸರತಿ_Get_Name_Impl
MPU_pc_ಸರತಿ_Get_Name_Unpriv
        svc #SYSTEM_CALL_pcQueueGetName
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMERS == 1 )

ಶೂನ್ಯ * MPU_pvTimerGetTimerID( ಸ್ಥಿರಾಂಕ TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ * MPU_pvTimerGetTimerID( ಸ್ಥಿರಾಂಕ TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_pvTimerGetTimerIDImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_pvTimerGetTimerID_Unpriv
MPU_pvTimerGetTimerID_Priv
        b MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerID_Unpriv
        svc #SYSTEM_CALL_pvTimerGetTimerID
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMERS == 1 )

ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Timer_ID( TimerHandle_t xTimer,
                           ಶೂನ್ಯ * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Timer_ID( TimerHandle_t xTimer,
                                 ಶೂನ್ಯ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_v_Timer_ಗಣ_Timer_IDImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_v_Timer_ಗಣ_Timer_ID_Unpriv
MPU_v_Timer_ಗಣ_Timer_ID_Priv
        b MPU_v_Timer_ಗಣ_Timer_IDImpl
MPU_v_Timer_ಗಣ_Timer_ID_Unpriv
        svc #SYSTEM_CALL_vTimerSetTimerID
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMERS == 1 )

ತಳ_Type_t MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ_Unpriv
MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ_Priv
        b MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ_Impl
MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ಶೂನ್ಯ ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_xTimerGetTimerDaemonTaskHandleImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
MPU_xTimerGetTimerDaemonTaskHandle_Priv
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMERS == 1 )

ತಳ_Type_t MPU_x_Timer_Generic_Command_From_Task_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_Timer_Generic_Command_From_Task_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_xTimerGenericCommandFromTaskImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
MPU_xTimerGenericCommandFromTask_Priv
        b MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTask_Unpriv
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMERS == 1 )

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_pcTimerGetNameImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_pcTimerGetName_Unpriv
MPU_pcTimerGetName_Priv
        b MPU_pcTimerGetNameImpl
MPU_pcTimerGetName_Unpriv
        svc #SYSTEM_CALL_pcTimerGetName
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMERS == 1 )

ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ( TimerHandle_t xTimer,
                              ಸ್ಥಿರಾಂಕ ತಳ_Type_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ( TimerHandle_t xTimer,
                                    ಸ್ಥಿರಾಂಕ ತಳ_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ_Unpriv
MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ_Priv
        b MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ_Impl
MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ_Unpriv
        svc #SYSTEM_CALL_vTimerSetReloadMode
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMERS == 1 )

ತಳ_Type_t MPU_x_Timer_Get_Reload_ಬಹುಲಕ( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_Timer_Get_Reload_ಬಹುಲಕ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_Timer_Get_Reload_ಬಹುಲಕ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_Timer_Get_Reload_ಬಹುಲಕ_Unpriv
MPU_x_Timer_Get_Reload_ಬಹುಲಕ_Priv
        b MPU_x_Timer_Get_Reload_ಬಹುಲಕ_Impl
MPU_x_Timer_Get_Reload_ಬಹುಲಕ_Unpriv
        svc #SYSTEM_CALL_xTimerGetReloadMode
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMERS == 1 )

UBaseType_t MPU_ux_Timer_Get_Reload_ಬಹುಲಕ( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Timer_Get_Reload_ಬಹುಲಕ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ux_Timer_Get_Reload_ಬಹುಲಕ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ux_Timer_Get_Reload_ಬಹುಲಕ_Unpriv
MPU_ux_Timer_Get_Reload_ಬಹುಲಕ_Priv
        b MPU_ux_Timer_Get_Reload_ಬಹುಲಕ_Impl
MPU_ux_Timer_Get_Reload_ಬಹುಲಕ_Unpriv
        svc #SYSTEM_CALL_uxTimerGetReloadMode
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_xTimerGetPeriodImpl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_xTimerGetPeriod_Unpriv
MPU_xTimerGetPeriod_Priv
        b MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriod_Unpriv
        svc #SYSTEM_CALL_xTimerGetPeriod
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TIMERS == 1 )

TickType_t MPU_x_Timer_Get_Expiry_ಸಮಯ( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Timer_Get_Expiry_ಸಮಯ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_Timer_Get_Expiry_ಸಮಯ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_Timer_Get_Expiry_ಸಮಯ_Unpriv
MPU_x_Timer_Get_Expiry_ಸಮಯ_Priv
        b MPU_x_Timer_Get_Expiry_ಸಮಯ_Impl
MPU_x_Timer_Get_Expiry_ಸಮಯ_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_ನಮೂದು( ಸ್ಥಿರಾಂಕ x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Params_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_ನಮೂದು( ಸ್ಥಿರಾಂಕ x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Params_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Unpriv
MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Priv
        b MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Impl
MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Unpriv
        svc #SYSTEM_CALL_xEventGroupWaitBits
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                      ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) FREERTOS_SYSTEM_CALL;

__asm Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                            ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು_Unpriv
MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು_Priv
        b MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು_Impl
MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು_Unpriv
        svc #SYSTEM_CALL_xEventGroupClearBits
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                    ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ ) FREERTOS_SYSTEM_CALL;

__asm Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                          ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_Unpriv
MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_Priv
        b MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_Impl
MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_Unpriv
        svc #SYSTEM_CALL_xEventGroupSetBits
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Sync( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                 ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ,
                                 ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For,
                                 TickType_t x_Ticks_ಗಮ್ಯ_Wait ) FREERTOS_SYSTEM_CALL;

__asm Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Sync( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                       ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ,
                                       ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For,
                                       TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_Event_ಗುಂಪು_Sync_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_Event_ಗುಂಪು_Sync_Unpriv
MPU_x_Event_ಗುಂಪು_Sync_Priv
        b MPU_x_Event_ಗುಂಪು_Sync_Impl
MPU_x_Event_ಗುಂಪು_Sync_Unpriv
        svc #SYSTEM_CALL_xEventGroupSync
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * x_Event_ಗುಂಪು ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * x_Event_ಗುಂಪು ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ_Unpriv
MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ_Priv
        b MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ_Impl
MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ_Unpriv
        svc #SYSTEM_CALL_uxEventGroupGetNumber
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

ಶೂನ್ಯ MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * x_Event_ಗುಂಪು,
                               UBaseType_t ux_Event_ಗುಂಪು_ಸಂಖ್ಯೆ ) FREERTOS_SYSTEM_CALL;

__asm ಶೂನ್ಯ MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * x_Event_ಗುಂಪು,
                                     UBaseType_t ux_Event_ಗುಂಪು_ಸಂಖ್ಯೆ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ_Unpriv
MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ_Priv
        b MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ_Impl
MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ_Unpriv
        svc #SYSTEM_CALL_vEventGroupSetNumber
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

size_t MPU_x_ಹರಿವು_ಬಫರ್_Send( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                              ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_Tx_ದತ್ತಾಂಶ,
                              size_t x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                              TickType_t x_Ticks_ಗಮ್ಯ_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ಹರಿವು_ಬಫರ್_Send( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_Tx_ದತ್ತಾಂಶ,
                                    size_t x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                    TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಹರಿವು_ಬಫರ್_Send_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಹರಿವು_ಬಫರ್_Send_Unpriv
MPU_x_ಹರಿವು_ಬಫರ್_Send_Priv
        b MPU_x_ಹರಿವು_ಬಫರ್_Send_Impl
MPU_x_ಹರಿವು_ಬಫರ್_Send_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSend
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

size_t MPU_x_ಹರಿವು_ಬಫರ್_Receive( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                 ಶೂನ್ಯ * pv_Rx_ದತ್ತಾಂಶ,
                                 size_t x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                 TickType_t x_Ticks_ಗಮ್ಯ_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ಹರಿವು_ಬಫರ್_Receive( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                       ಶೂನ್ಯ * pv_Rx_ದತ್ತಾಂಶ,
                                       size_t x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                       TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಹರಿವು_ಬಫರ್_Receive_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಹರಿವು_ಬಫರ್_Receive_Unpriv
MPU_x_ಹರಿವು_ಬಫರ್_Receive_Priv
        b MPU_x_ಹರಿವು_ಬಫರ್_Receive_Impl
MPU_x_ಹರಿವು_ಬಫರ್_Receive_Unpriv
        svc #SYSTEM_CALL_xStreamBufferReceive
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ_Unpriv
MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ_Priv
        b MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ_Impl
MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು_Unpriv
MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು_Priv
        b MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು_Impl
MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

size_t MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ_Unpriv
MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ_Priv
        b MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ_Impl
MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

size_t MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ_Unpriv
MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ_Priv
        b MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ_Impl
MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level_Unpriv
MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level_Priv
        b MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level_Impl
MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

size_t MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    ಬಾಹ್ಯ MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು_Impl

    ತಳ್ಳು {r0}
    mrs r0, control
    tst r0, #1
    ತೆಗೆ_2 {r0}
    bne MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು_Unpriv
MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು_Priv
        b MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು_Impl
MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_MPU_WRAPPERS_V1 == 0 */
