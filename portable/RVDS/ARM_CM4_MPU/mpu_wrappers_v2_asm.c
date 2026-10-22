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
#నిర్వచించు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "queue.h"
#అన్తర్భావ "timers.h"
#అన్తర్భావ "event_groups.h"
#అన్తర్భావ "stream_buffer.h"
#అన్తర్భావ "mpu_prototypes.h"
#అన్తర్భావ "mpu_syscall_numbers.h"

#నిర్వచనం_రద్దు MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_MPU_WRAPPERS_V1 == 0 )

#ఒకవేళ ( INCLUDE_xTaskDelayUntil == 1 )

పునాది_Type_t MPU_xTaskDelayUntil( TickType_t * స్థిరరాశి px_మునుపటి_Wake_సమయం,
                                స్థిరరాశి TickType_t x_సమయం_Increment ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_xTaskDelayUntil( TickType_t * స్థిరరాశి px_మునుపటి_Wake_సమయం,
                                      స్థిరరాశి TickType_t x_సమయం_Increment ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_xTaskDelayUntilImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_xTaskDelayUntil_Unpriv
MPU_xTaskDelayUntil_Priv
        b MPU_xTaskDelayUntilImpl
MPU_xTaskDelayUntil_Unpriv
        svc #SYSTEM_CALL_xTaskDelayUntil
}

#అయితే_ముగింపు /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( INCLUDE_xTaskAbortDelay == 1 )

పునాది_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_xTaskAbortDelayImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_xTaskAbortDelay_Unpriv
MPU_xTaskAbortDelay_Priv
        b MPU_xTaskAbortDelayImpl
MPU_xTaskAbortDelay_Unpriv
        svc #SYSTEM_CALL_xTaskAbortDelay
}

#అయితే_ముగింపు /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( INCLUDE_vTaskDelay == 1 )

శూన్య MPU_vTaskDelay( స్థిరరాశి TickType_t x_Ticks_గమ్యం_Delay ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_vTaskDelay( స్థిరరాశి TickType_t x_Ticks_గమ్యం_Delay ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_vTaskDelayImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_vTaskDelay_Unpriv
MPU_vTaskDelay_Priv
        b MPU_vTaskDelayImpl
MPU_vTaskDelay_Unpriv
        svc #SYSTEM_CALL_vTaskDelay
}

#అయితే_ముగింపు /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( INCLUDE_ux_Task_ప్రాధాన్యత_Get == 1 )

UBaseType_t MPU_ux_Task_ప్రాధాన్యత_Get( స్థిరరాశి TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_ప్రాధాన్యత_Get( స్థిరరాశి TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ux_Task_ప్రాధాన్యత_Get_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ux_Task_ప్రాధాన్యత_Get_Unpriv
MPU_ux_Task_ప్రాధాన్యత_Get_Priv
        b MPU_ux_Task_ప్రాధాన్యత_Get_Impl
MPU_ux_Task_ప్రాధాన్యత_Get_Unpriv
        svc #SYSTEM_CALL_uxTaskPriorityGet
}

#అయితే_ముగింపు /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( INCLUDE_eTaskGetState == 1 )

eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_eTaskGetStateImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_eTaskGetState_Unpriv
MPU_eTaskGetState_Priv
        b MPU_eTaskGetStateImpl
MPU_eTaskGetState_Unpriv
        svc #SYSTEM_CALL_eTaskGetState
}

#అయితే_ముగింపు /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )

శూన్య MPU_vTaskGetInfo( TaskHandle_t xTask,
                       Task_స్థితి_t * px_Task_స్థితి,
                       పునాది_Type_t x_Get_Free_దొంతర_Space,
                       eTaskState eState ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_vTaskGetInfo( TaskHandle_t xTask,
                             Task_స్థితి_t * px_Task_స్థితి,
                             పునాది_Type_t x_Get_Free_దొంతర_Space,
                             eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_vTaskGetInfoImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_vTaskGetInfo_Unpriv
MPU_vTaskGetInfo_Priv
        b MPU_vTaskGetInfoImpl
MPU_vTaskGetInfo_Unpriv
        svc #SYSTEM_CALL_vTaskGetInfo
}

#అయితే_ముగింపు /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

TaskHandle_t MPU_xTaskGetIdleTaskHandle( శూన్య ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetIdleTaskHandle( శూన్య ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_xTaskGetIdleTaskHandleImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_xTaskGetIdleTaskHandle_Unpriv
MPU_xTaskGetIdleTaskHandle_Priv
        b MPU_xTaskGetIdleTaskHandleImpl
MPU_xTaskGetIdleTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetIdleTaskHandle
}

#అయితే_ముగింపు /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( INCLUDE_vTaskSuspend == 1 )

శూన్య MPU_vTaskSuspend( TaskHandle_t x_Task_గమ్యం_Suspend ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_vTaskSuspend( TaskHandle_t x_Task_గమ్యం_Suspend ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_vTaskSuspendImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_vTaskSuspend_Unpriv
MPU_vTaskSuspend_Priv
        b MPU_vTaskSuspendImpl
MPU_vTaskSuspend_Unpriv
        svc #SYSTEM_CALL_vTaskSuspend
}

#అయితే_ముగింపు /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( INCLUDE_vTaskSuspend == 1 )

శూన్య MPU_vTaskResume( TaskHandle_t x_Task_గమ్యం_Resume ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_vTaskResume( TaskHandle_t x_Task_గమ్యం_Resume ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_vTaskResumeImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_vTaskResume_Unpriv
MPU_vTaskResume_Priv
        b MPU_vTaskResumeImpl
MPU_vTaskResume_Unpriv
        svc #SYSTEM_CALL_vTaskResume
}

#అయితే_ముగింపు /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

TickType_t MPU_x_Task_Get_Tick_లెక్క( శూన్య ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Task_Get_Tick_లెక్క( శూన్య ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_Task_Get_Tick_లెక్క_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_Task_Get_Tick_లెక్క_Unpriv
MPU_x_Task_Get_Tick_లెక్క_Priv
        b MPU_x_Task_Get_Tick_లెక్క_Impl
MPU_x_Task_Get_Tick_లెక్క_Unpriv
        svc #SYSTEM_CALL_xTaskGetTickCount
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks( శూన్య ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks( శూన్య ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks_Unpriv
MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks_Priv
        b MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks_Impl
MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks_Unpriv
        svc #SYSTEM_CALL_uxTaskGetNumberOfTasks
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 )

config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Counter( స్థిరరాశి TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Counter( స్థిరరాశి TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ul_Task_Get_నిరంతరం_సమయం_Counter_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ul_Task_Get_నిరంతరం_సమయం_Counter_Unpriv
MPU_ul_Task_Get_నిరంతరం_సమయం_Counter_Priv
        b MPU_ul_Task_Get_నిరంతరం_సమయం_Counter_Impl
MPU_ul_Task_Get_నిరంతరం_సమయం_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimeCounter
}

#అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 )

config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Percent( స్థిరరాశి TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Percent( స్థిరరాశి TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ul_Task_Get_నిరంతరం_సమయం_Percent_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ul_Task_Get_నిరంతరం_సమయం_Percent_Unpriv
MPU_ul_Task_Get_నిరంతరం_సమయం_Percent_Priv
        b MPU_ul_Task_Get_నిరంతరం_సమయం_Percent_Impl
MPU_ul_Task_Get_నిరంతరం_సమయం_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetRunTimePercent
}

#అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent( శూన్య ) FREERTOS_SYSTEM_CALL;

__asm config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent( శూన్య ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent_Unpriv
MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent_Priv
        b MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent_Impl
MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimePercent
}

#అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter( శూన్య ) FREERTOS_SYSTEM_CALL;

__asm config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter( శూన్య ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter_Unpriv
MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter_Priv
        b MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter_Impl
MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter_Unpriv
        svc #SYSTEM_CALL_ulTaskGetIdleRunTimeCounter
}

#అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )

శూన్య MPU_v_Task_సమితి_Application_Task_ట్యాగ్( TaskHandle_t xTask,
                                     TaskHookFunction_t pxHookFunction ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_v_Task_సమితి_Application_Task_ట్యాగ్( TaskHandle_t xTask,
                                           TaskHookFunction_t pxHookFunction ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_v_Task_సమితి_Application_Task_ట్యాగ్_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_v_Task_సమితి_Application_Task_ట్యాగ్_Unpriv
MPU_v_Task_సమితి_Application_Task_ట్యాగ్_Priv
        b MPU_v_Task_సమితి_Application_Task_ట్యాగ్_Impl
MPU_v_Task_సమితి_Application_Task_ట్యాగ్_Unpriv
        svc #SYSTEM_CALL_vTaskSetApplicationTaskTag
}

#అయితే_ముగింపు /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )

TaskHookFunction_t MPU_x_Task_Get_Application_Task_ట్యాగ్( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm TaskHookFunction_t MPU_x_Task_Get_Application_Task_ట్యాగ్( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_Task_Get_Application_Task_ట్యాగ్_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_Task_Get_Application_Task_ట్యాగ్_Unpriv
MPU_x_Task_Get_Application_Task_ట్యాగ్_Priv
        b MPU_x_Task_Get_Application_Task_ట్యాగ్_Impl
MPU_x_Task_Get_Application_Task_ట్యాగ్_Unpriv
        svc #SYSTEM_CALL_xTaskGetApplicationTaskTag
}

#అయితే_ముగింపు /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు != 0 )

శూన్య MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_సమితి,
                                            పునాది_Type_t x_సూచీ,
                                            శూన్య * pv_విలువ ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_సమితి,
                                                  పునాది_Type_t x_సూచీ,
                                                  శూన్య * pv_విలువ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక_Unpriv
MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక_Priv
        b MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక_Impl
MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక_Unpriv
        svc #SYSTEM_CALL_vTaskSetThreadLocalStoragePointer
}

#అయితే_ముగింపు /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు != 0 )

శూన్య * MPU_pv_Task_Get_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_Query,
                                               పునాది_Type_t x_సూచీ ) FREERTOS_SYSTEM_CALL;

__asm శూన్య * MPU_pv_Task_Get_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_Query,
                                                     పునాది_Type_t x_సూచీ ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_pv_Task_Get_Thread_Local_Storage_సూచిక_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_pv_Task_Get_Thread_Local_Storage_సూచిక_Unpriv
MPU_pv_Task_Get_Thread_Local_Storage_సూచిక_Priv
        b MPU_pv_Task_Get_Thread_Local_Storage_సూచిక_Impl
MPU_pv_Task_Get_Thread_Local_Storage_సూచిక_Unpriv
        svc #SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer
}

#అయితే_ముగింపు /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )

UBaseType_t MPU_uxTaskGetSystemState( Task_స్థితి_t * స్థిరరాశి px_Task_స్థితి_Array,
                                      స్థిరరాశి UBaseType_t ux_Array_కొలత,
                                      config_నిరంతరం_సమయం_COUNTER_TYPE * స్థిరరాశి pul_మొత్తం_నిరంతరం_సమయం ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_uxTaskGetSystemState( Task_స్థితి_t * స్థిరరాశి px_Task_స్థితి_Array,
                                            స్థిరరాశి UBaseType_t ux_Array_కొలత,
                                            config_నిరంతరం_సమయం_COUNTER_TYPE * స్థిరరాశి pul_మొత్తం_నిరంతరం_సమయం ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_uxTaskGetSystemStateImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_uxTaskGetSystemState_Unpriv
MPU_uxTaskGetSystemState_Priv
        b MPU_uxTaskGetSystemStateImpl
MPU_uxTaskGetSystemState_Unpriv
        svc #SYSTEM_CALL_uxTaskGetSystemState
}

#అయితే_ముగింపు /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark == 1 )

UBaseType_t MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark_Unpriv
MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark_Priv
        b MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark_Impl
MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark
}

#అయితే_ముగింపు /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2 == 1 )

config_దొంతర_లోతు_TYPE MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2( TaskHandle_t xTask ) FREERTOS_SYSTEM_CALL;

__asm config_దొంతర_లోతు_TYPE MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2_Unpriv
MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2_Priv
        b MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2_Impl
MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2_Unpriv
        svc #SYSTEM_CALL_uxTaskGetStackHighWaterMark2
}

#అయితే_ముగింపు /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

TaskHandle_t MPU_xTaskGetCurrentTaskHandle( శూన్య ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTaskGetCurrentTaskHandle( శూన్య ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_xTaskGetCurrentTaskHandleImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_xTaskGetCurrentTaskHandle_Unpriv
MPU_xTaskGetCurrentTaskHandle_Priv
        b MPU_xTaskGetCurrentTaskHandleImpl
MPU_xTaskGetCurrentTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTaskGetCurrentTaskHandle
}

#అయితే_ముగింపు /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( INCLUDE_xTaskGetSchedulerState == 1 )

పునాది_Type_t MPU_xTaskGetSchedulerState( శూన్య ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_xTaskGetSchedulerState( శూన్య ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_xTaskGetSchedulerStateImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_xTaskGetSchedulerState_Unpriv
MPU_xTaskGetSchedulerState_Priv
        b MPU_xTaskGetSchedulerStateImpl
MPU_xTaskGetSchedulerState_Unpriv
        svc #SYSTEM_CALL_xTaskGetSchedulerState
}

#అయితే_ముగింపు /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

శూన్య MPU_v_Task_సమితి_సమయం_బహిర్గతం_State( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_v_Task_సమితి_సమయం_బహిర్గతం_State( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_v_Task_సమితి_సమయం_బహిర్గతం_State_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_v_Task_సమితి_సమయం_బహిర్గతం_State_Unpriv
MPU_v_Task_సమితి_సమయం_బహిర్గతం_State_Priv
        b MPU_v_Task_సమితి_సమయం_బహిర్గతం_State_Impl
MPU_v_Task_సమితి_సమయం_బహిర్గతం_State_Unpriv
        svc #SYSTEM_CALL_vTaskSetTimeOutState
}
/*-----------------------------------------------------------*/

పునాది_Type_t MPU_x_Task_Check_For_సమయం_బహిర్గతం( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం,
                                     TickType_t * స్థిరరాశి px_Ticks_గమ్యం_Wait ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_Task_Check_For_సమయం_బహిర్గతం( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం,
                                     TickType_t * స్థిరరాశి px_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_Task_Check_For_సమయం_బహిర్గతం_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_Task_Check_For_సమయం_బహిర్గతం_Unpriv
MPU_x_Task_Check_For_సమయం_బహిర్గతం_Priv
        b MPU_x_Task_Check_For_సమయం_బహిర్గతం_Impl
MPU_x_Task_Check_For_సమయం_బహిర్గతం_Unpriv
        svc #SYSTEM_CALL_xTaskCheckForTimeOut
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

పునాది_Type_t MPU_x_Task_Generic_Notify_నమోదు( స్థిరరాశి xTaskGenericNotifyParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_Task_Generic_Notify_నమోదు( స్థిరరాశి xTaskGenericNotifyParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_xTaskGenericNotifyImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_xTaskGenericNotify_Unpriv
MPU_xTaskGenericNotify_Priv
        b MPU_xTaskGenericNotifyImpl
MPU_xTaskGenericNotify_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotify
}

#అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

పునాది_Type_t MPU_x_Task_Generic_Notify_Wait_నమోదు( స్థిరరాశి xTaskGenericNotifyWaitParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_Task_Generic_Notify_Wait_నమోదు( స్థిరరాశి xTaskGenericNotifyWaitParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_xTaskGenericNotifyWaitImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_xTaskGenericNotifyWait_Unpriv
MPU_xTaskGenericNotifyWait_Priv
        b MPU_xTaskGenericNotifyWaitImpl
MPU_xTaskGenericNotifyWait_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyWait
}

#అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_సూచీ_గమ్యం_Wait_On,
                                      పునాది_Type_t x_Clear_లెక్క_On_Exit,
                                      TickType_t x_Ticks_గమ్యం_Wait ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_సూచీ_గమ్యం_Wait_On,
                                            పునాది_Type_t x_Clear_లెక్క_On_Exit,
                                            TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ulTaskGenericNotifyTakeImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ulTaskGenericNotifyTake_Unpriv
MPU_ulTaskGenericNotifyTake_Priv
        b MPU_ulTaskGenericNotifyTakeImpl
MPU_ulTaskGenericNotifyTake_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyTake
}

#అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

పునాది_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                             UBaseType_t ux_సూచీ_గమ్యం_Clear ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                   UBaseType_t ux_సూచీ_గమ్యం_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_xTaskGenericNotifyStateClearImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_xTaskGenericNotifyStateClear_Unpriv
MPU_xTaskGenericNotifyStateClear_Priv
        b MPU_xTaskGenericNotifyStateClearImpl
MPU_xTaskGenericNotifyStateClear_Unpriv
        svc #SYSTEM_CALL_xTaskGenericNotifyStateClear
}

#అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

uint32_t MPU_ul_Task_Generic_Notify_విలువ_Clear( TaskHandle_t xTask,
                                            UBaseType_t ux_సూచీ_గమ్యం_Clear,
                                            uint32_t ul_బిట్లు_గమ్యం_Clear ) FREERTOS_SYSTEM_CALL;

__asm uint32_t MPU_ul_Task_Generic_Notify_విలువ_Clear( TaskHandle_t xTask,
                                                  UBaseType_t ux_సూచీ_గమ్యం_Clear,
                                                  uint32_t ul_బిట్లు_గమ్యం_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ul_Task_Generic_Notify_విలువ_Clear_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ul_Task_Generic_Notify_విలువ_Clear_Unpriv
MPU_ul_Task_Generic_Notify_విలువ_Clear_Priv
        b MPU_ul_Task_Generic_Notify_విలువ_Clear_Impl
MPU_ul_Task_Generic_Notify_విలువ_Clear_Unpriv
        svc #SYSTEM_CALL_ulTaskGenericNotifyValueClear
}

#అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

పునాది_Type_t MPU_x_వరుస_Generic_Send( వరుస_Handle_t x_వరుస,
                                  స్థిరరాశి శూన్య * స్థిరరాశి pv_అంశం_గమ్యం_వరుస,
                                  TickType_t x_Ticks_గమ్యం_Wait,
                                  స్థిరరాశి పునాది_Type_t xCopyPosition ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_వరుస_Generic_Send( వరుస_Handle_t x_వరుస,
                                        స్థిరరాశి శూన్య * స్థిరరాశి pv_అంశం_గమ్యం_వరుస,
                                        TickType_t x_Ticks_గమ్యం_Wait,
                                        స్థిరరాశి పునాది_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_వరుస_Generic_Send_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_వరుస_Generic_Send_Unpriv
MPU_x_వరుస_Generic_Send_Priv
        b MPU_x_వరుస_Generic_Send_Impl
MPU_x_వరుస_Generic_Send_Unpriv
        svc #SYSTEM_CALL_xQueueGenericSend
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_వరుస_Messages_నిరీక్షణ( స్థిరరాశి వరుస_Handle_t x_వరుస ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_వరుస_Messages_నిరీక్షణ( స్థిరరాశి వరుస_Handle_t x_వరుస ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ux_వరుస_Messages_నిరీక్షణ_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ux_వరుస_Messages_నిరీక్షణ_Unpriv
MPU_ux_వరుస_Messages_నిరీక్షణ_Priv
        b MPU_ux_వరుస_Messages_నిరీక్షణ_Impl
MPU_ux_వరుస_Messages_నిరీక్షణ_Unpriv
        svc #SYSTEM_CALL_uxQueueMessagesWaiting
}
/*-----------------------------------------------------------*/

UBaseType_t MPU_ux_వరుస_Spaces_అందుబాటు( స్థిరరాశి వరుస_Handle_t x_వరుస ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_వరుస_Spaces_అందుబాటు( స్థిరరాశి వరుస_Handle_t x_వరుస ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ux_వరుస_Spaces_అందుబాటు_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ux_వరుస_Spaces_అందుబాటు_Unpriv
MPU_ux_వరుస_Spaces_అందుబాటు_Priv
        b MPU_ux_వరుస_Spaces_అందుబాటు_Impl
MPU_ux_వరుస_Spaces_అందుబాటు_Unpriv
        svc #SYSTEM_CALL_uxQueueSpacesAvailable
}
/*-----------------------------------------------------------*/

పునాది_Type_t MPU_x_వరుస_Receive( వరుస_Handle_t x_వరుస,
                              శూన్య * స్థిరరాశి pv_బఫరు,
                              TickType_t x_Ticks_గమ్యం_Wait ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_వరుస_Receive( వరుస_Handle_t x_వరుస,
                                    శూన్య * స్థిరరాశి pv_బఫరు,
                                    TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_వరుస_Receive_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_వరుస_Receive_Unpriv
MPU_x_వరుస_Receive_Priv
        b MPU_x_వరుస_Receive_Impl
MPU_x_వరుస_Receive_Unpriv
        svc #SYSTEM_CALL_xQueueReceive
}
/*-----------------------------------------------------------*/

పునాది_Type_t MPU_x_వరుస_Peek( వరుస_Handle_t x_వరుస,
                           శూన్య * స్థిరరాశి pv_బఫరు,
                           TickType_t x_Ticks_గమ్యం_Wait ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_వరుస_Peek( వరుస_Handle_t x_వరుస,
                                 శూన్య * స్థిరరాశి pv_బఫరు,
                                 TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_వరుస_Peek_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_వరుస_Peek_Unpriv
MPU_x_వరుస_Peek_Priv
        b MPU_x_వరుస_Peek_Impl
MPU_x_వరుస_Peek_Unpriv
        svc #SYSTEM_CALL_xQueuePeek
}
/*-----------------------------------------------------------*/

పునాది_Type_t MPU_x_వరుస_Semaphore_Take( వరుస_Handle_t x_వరుస,
                                    TickType_t x_Ticks_గమ్యం_Wait ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_వరుస_Semaphore_Take( వరుస_Handle_t x_వరుస,
                                          TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_వరుస_Semaphore_Take_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_వరుస_Semaphore_Take_Unpriv
MPU_x_వరుస_Semaphore_Take_Priv
        b MPU_x_వరుస_Semaphore_Take_Impl
MPU_x_వరుస_Semaphore_Take_Unpriv
        svc #SYSTEM_CALL_xQueueSemaphoreTake
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

TaskHandle_t MPU_x_వరుస_Get_Mutex_Holder( వరుస_Handle_t xSemaphore ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_x_వరుస_Get_Mutex_Holder( వరుస_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_వరుస_Get_Mutex_Holder_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_వరుస_Get_Mutex_Holder_Unpriv
MPU_x_వరుస_Get_Mutex_Holder_Priv
        b MPU_x_వరుస_Get_Mutex_Holder_Impl
MPU_x_వరుస_Get_Mutex_Holder_Unpriv
        svc #SYSTEM_CALL_xQueueGetMutexHolder
}

#అయితే_ముగింపు /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_RECURSIVE_MUTEXES == 1 )

పునాది_Type_t MPU_x_వరుస_Take_Mutex_Recursive( వరుస_Handle_t xMutex,
                                         TickType_t x_Ticks_గమ్యం_Wait ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_వరుస_Take_Mutex_Recursive( వరుస_Handle_t xMutex,
                                               TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_వరుస_Take_Mutex_Recursive_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_వరుస_Take_Mutex_Recursive_Unpriv
MPU_x_వరుస_Take_Mutex_Recursive_Priv
        b MPU_x_వరుస_Take_Mutex_Recursive_Impl
MPU_x_వరుస_Take_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueTakeMutexRecursive
}

#అయితే_ముగింపు /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_RECURSIVE_MUTEXES == 1 )

పునాది_Type_t MPU_x_వరుస_Give_Mutex_Recursive( వరుస_Handle_t pxMutex ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_వరుస_Give_Mutex_Recursive( వరుస_Handle_t pxMutex ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_వరుస_Give_Mutex_Recursive_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_వరుస_Give_Mutex_Recursive_Unpriv
MPU_x_వరుస_Give_Mutex_Recursive_Priv
        b MPU_x_వరుస_Give_Mutex_Recursive_Impl
MPU_x_వరుస_Give_Mutex_Recursive_Unpriv
        svc #SYSTEM_CALL_xQueueGiveMutexRecursive
}

#అయితే_ముగింపు /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_వరుస_SETS == 1 )

వరుస_సమితి_Member_Handle_t MPU_x_వరుస_Select_From_సమితి( వరుస_సమితి_Handle_t x_వరుస_సమితి,
                                                స్థిరరాశి TickType_t x_Ticks_గమ్యం_Wait ) FREERTOS_SYSTEM_CALL;

__asm వరుస_సమితి_Member_Handle_t MPU_x_వరుస_Select_From_సమితి( వరుస_సమితి_Handle_t x_వరుస_సమితి,
                                                      స్థిరరాశి TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_వరుస_Select_From_సమితి_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_వరుస_Select_From_సమితి_Unpriv
MPU_x_వరుస_Select_From_సమితి_Priv
        b MPU_x_వరుస_Select_From_సమితి_Impl
MPU_x_వరుస_Select_From_సమితి_Unpriv
        svc #SYSTEM_CALL_xQueueSelectFromSet
}

#అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_వరుస_SETS == 1 )

పునాది_Type_t MPU_x_వరుస_కూడు_గమ్యం_సమితి( వరుస_సమితి_Member_Handle_t x_వరుస_Or_Semaphore,
                               వరుస_సమితి_Handle_t x_వరుస_సమితి ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_వరుస_కూడు_గమ్యం_సమితి( వరుస_సమితి_Member_Handle_t x_వరుస_Or_Semaphore,
                                     వరుస_సమితి_Handle_t x_వరుస_సమితి ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_వరుస_కూడు_గమ్యం_సమితి_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_వరుస_కూడు_గమ్యం_సమితి_Unpriv
MPU_x_వరుస_కూడు_గమ్యం_సమితి_Priv
        b MPU_x_వరుస_కూడు_గమ్యం_సమితి_Impl
MPU_x_వరుస_కూడు_గమ్యం_సమితి_Unpriv
        svc #SYSTEM_CALL_xQueueAddToSet
}

#అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_వరుస_REGISTRY_కొలత > 0 )

శూన్య MPU_v_వరుస_కూడు_గమ్యం_Registry( వరుస_Handle_t x_వరుస,
                              స్థిరరాశి అక్షరం * pcName ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_v_వరుస_కూడు_గమ్యం_Registry( వరుస_Handle_t x_వరుస,
                                    స్థిరరాశి అక్షరం * pcName ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_v_వరుస_కూడు_గమ్యం_Registry_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_v_వరుస_కూడు_గమ్యం_Registry_Unpriv
MPU_v_వరుస_కూడు_గమ్యం_Registry_Priv
        b MPU_v_వరుస_కూడు_గమ్యం_Registry_Impl
MPU_v_వరుస_కూడు_గమ్యం_Registry_Unpriv
        svc #SYSTEM_CALL_vQueueAddToRegistry
}

#అయితే_ముగింపు /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_వరుస_REGISTRY_కొలత > 0 )

శూన్య MPU_v_వరుస_Unregister_వరుస( వరుస_Handle_t x_వరుస ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_v_వరుస_Unregister_వరుస( వరుస_Handle_t x_వరుస ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_v_వరుస_Unregister_వరుస_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_v_వరుస_Unregister_వరుస_Unpriv
MPU_v_వరుస_Unregister_వరుస_Priv
        b MPU_v_వరుస_Unregister_వరుస_Impl
MPU_v_వరుస_Unregister_వరుస_Unpriv
        svc #SYSTEM_CALL_vQueueUnregisterQueue
}

#అయితే_ముగింపు /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_వరుస_REGISTRY_కొలత > 0 )

స్థిరరాశి అక్షరం * MPU_pc_వరుస_Get_Name( వరుస_Handle_t x_వరుస ) FREERTOS_SYSTEM_CALL;

__asm స్థిరరాశి అక్షరం * MPU_pc_వరుస_Get_Name( వరుస_Handle_t x_వరుస ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_pc_వరుస_Get_Name_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_pc_వరుస_Get_Name_Unpriv
MPU_pc_వరుస_Get_Name_Priv
        b MPU_pc_వరుస_Get_Name_Impl
MPU_pc_వరుస_Get_Name_Unpriv
        svc #SYSTEM_CALL_pcQueueGetName
}

#అయితే_ముగింపు /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMERS == 1 )

శూన్య * MPU_pvTimerGetTimerID( స్థిరరాశి TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm శూన్య * MPU_pvTimerGetTimerID( స్థిరరాశి TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_pvTimerGetTimerIDImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_pvTimerGetTimerID_Unpriv
MPU_pvTimerGetTimerID_Priv
        b MPU_pvTimerGetTimerIDImpl
MPU_pvTimerGetTimerID_Unpriv
        svc #SYSTEM_CALL_pvTimerGetTimerID
}

#అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMERS == 1 )

శూన్య MPU_v_Timer_సమితి_Timer_ID( TimerHandle_t xTimer,
                           శూన్య * pvNewID ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_v_Timer_సమితి_Timer_ID( TimerHandle_t xTimer,
                                 శూన్య * pvNewID ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_v_Timer_సమితి_Timer_IDImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_v_Timer_సమితి_Timer_ID_Unpriv
MPU_v_Timer_సమితి_Timer_ID_Priv
        b MPU_v_Timer_సమితి_Timer_IDImpl
MPU_v_Timer_సమితి_Timer_ID_Unpriv
        svc #SYSTEM_CALL_vTimerSetTimerID
}

#అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMERS == 1 )

పునాది_Type_t MPU_x_Timer_Is_Timer_చురుకైన( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_Timer_Is_Timer_చురుకైన( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_Timer_Is_Timer_చురుకైన_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_Timer_Is_Timer_చురుకైన_Unpriv
MPU_x_Timer_Is_Timer_చురుకైన_Priv
        b MPU_x_Timer_Is_Timer_చురుకైన_Impl
MPU_x_Timer_Is_Timer_చురుకైన_Unpriv
        svc #SYSTEM_CALL_xTimerIsTimerActive
}

#అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMERS == 1 )

TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( శూన్య ) FREERTOS_SYSTEM_CALL;

__asm TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( శూన్య ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_xTimerGetTimerDaemonTaskHandleImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
MPU_xTimerGetTimerDaemonTaskHandle_Priv
        b MPU_xTimerGetTimerDaemonTaskHandleImpl
MPU_xTimerGetTimerDaemonTaskHandle_Unpriv
        svc #SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle
}

#అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMERS == 1 )

పునాది_Type_t MPU_x_Timer_Generic_Command_From_Task_నమోదు( స్థిరరాశి xTimerGenericCommandFromTaskParams_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_Timer_Generic_Command_From_Task_నమోదు( స్థిరరాశి xTimerGenericCommandFromTaskParams_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_xTimerGenericCommandFromTaskImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_xTimerGenericCommandFromTask_Unpriv
MPU_xTimerGenericCommandFromTask_Priv
        b MPU_xTimerGenericCommandFromTaskImpl
MPU_xTimerGenericCommandFromTask_Unpriv
        svc #SYSTEM_CALL_xTimerGenericCommandFromTask
}

#అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMERS == 1 )

స్థిరరాశి అక్షరం * MPU_pcTimerGetName( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm స్థిరరాశి అక్షరం * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_pcTimerGetNameImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_pcTimerGetName_Unpriv
MPU_pcTimerGetName_Priv
        b MPU_pcTimerGetNameImpl
MPU_pcTimerGetName_Unpriv
        svc #SYSTEM_CALL_pcTimerGetName
}

#అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMERS == 1 )

శూన్య MPU_v_Timer_సమితి_Reload_బహుళకం( TimerHandle_t xTimer,
                              స్థిరరాశి పునాది_Type_t xAutoReload ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_v_Timer_సమితి_Reload_బహుళకం( TimerHandle_t xTimer,
                                    స్థిరరాశి పునాది_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_v_Timer_సమితి_Reload_బహుళకం_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_v_Timer_సమితి_Reload_బహుళకం_Unpriv
MPU_v_Timer_సమితి_Reload_బహుళకం_Priv
        b MPU_v_Timer_సమితి_Reload_బహుళకం_Impl
MPU_v_Timer_సమితి_Reload_బహుళకం_Unpriv
        svc #SYSTEM_CALL_vTimerSetReloadMode
}

#అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMERS == 1 )

పునాది_Type_t MPU_x_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_Timer_Get_Reload_బహుళకం_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_Timer_Get_Reload_బహుళకం_Unpriv
MPU_x_Timer_Get_Reload_బహుళకం_Priv
        b MPU_x_Timer_Get_Reload_బహుళకం_Impl
MPU_x_Timer_Get_Reload_బహుళకం_Unpriv
        svc #SYSTEM_CALL_xTimerGetReloadMode
}

#అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMERS == 1 )

UBaseType_t MPU_ux_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ux_Timer_Get_Reload_బహుళకం_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ux_Timer_Get_Reload_బహుళకం_Unpriv
MPU_ux_Timer_Get_Reload_బహుళకం_Priv
        b MPU_ux_Timer_Get_Reload_బహుళకం_Impl
MPU_ux_Timer_Get_Reload_బహుళకం_Unpriv
        svc #SYSTEM_CALL_uxTimerGetReloadMode
}

#అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMERS == 1 )

TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_xTimerGetPeriodImpl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_xTimerGetPeriod_Unpriv
MPU_xTimerGetPeriod_Priv
        b MPU_xTimerGetPeriodImpl
MPU_xTimerGetPeriod_Unpriv
        svc #SYSTEM_CALL_xTimerGetPeriod
}

#అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TIMERS == 1 )

TickType_t MPU_x_Timer_Get_Expiry_సమయం( TimerHandle_t xTimer ) FREERTOS_SYSTEM_CALL;

__asm TickType_t MPU_x_Timer_Get_Expiry_సమయం( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_Timer_Get_Expiry_సమయం_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_Timer_Get_Expiry_సమయం_Unpriv
MPU_x_Timer_Get_Expiry_సమయం_Priv
        b MPU_x_Timer_Get_Expiry_సమయం_Impl
MPU_x_Timer_Get_Expiry_సమయం_Unpriv
        svc #SYSTEM_CALL_xTimerGetExpiryTime
}

#అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

Event_బిట్లు_t MPU_x_Event_సమూహం_Wait_బిట్లు_నమోదు( స్థిరరాశి x_Event_సమూహం_Wait_బిట్లు_Params_t * pxParams ) FREERTOS_SYSTEM_CALL;

__asm Event_బిట్లు_t MPU_x_Event_సమూహం_Wait_బిట్లు_నమోదు( స్థిరరాశి x_Event_సమూహం_Wait_బిట్లు_Params_t * pxParams ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_Event_సమూహం_Wait_బిట్లు_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_Event_సమూహం_Wait_బిట్లు_Unpriv
MPU_x_Event_సమూహం_Wait_బిట్లు_Priv
        b MPU_x_Event_సమూహం_Wait_బిట్లు_Impl
MPU_x_Event_సమూహం_Wait_బిట్లు_Unpriv
        svc #SYSTEM_CALL_xEventGroupWaitBits
}

#అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

Event_బిట్లు_t MPU_x_Event_సమూహం_Clear_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                      స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Clear ) FREERTOS_SYSTEM_CALL;

__asm Event_బిట్లు_t MPU_x_Event_సమూహం_Clear_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                            స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Clear ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_Event_సమూహం_Clear_బిట్లు_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_Event_సమూహం_Clear_బిట్లు_Unpriv
MPU_x_Event_సమూహం_Clear_బిట్లు_Priv
        b MPU_x_Event_సమూహం_Clear_బిట్లు_Impl
MPU_x_Event_సమూహం_Clear_బిట్లు_Unpriv
        svc #SYSTEM_CALL_xEventGroupClearBits
}

#అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

Event_బిట్లు_t MPU_x_Event_సమూహం_సమితి_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                    స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి ) FREERTOS_SYSTEM_CALL;

__asm Event_బిట్లు_t MPU_x_Event_సమూహం_సమితి_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                          స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_Event_సమూహం_సమితి_బిట్లు_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_Event_సమూహం_సమితి_బిట్లు_Unpriv
MPU_x_Event_సమూహం_సమితి_బిట్లు_Priv
        b MPU_x_Event_సమూహం_సమితి_బిట్లు_Impl
MPU_x_Event_సమూహం_సమితి_బిట్లు_Unpriv
        svc #SYSTEM_CALL_xEventGroupSetBits
}

#అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

Event_బిట్లు_t MPU_x_Event_సమూహం_Sync( Event_సమూహం_Handle_t x_Event_సమూహం,
                                 స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి,
                                 స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Wait_For,
                                 TickType_t x_Ticks_గమ్యం_Wait ) FREERTOS_SYSTEM_CALL;

__asm Event_బిట్లు_t MPU_x_Event_సమూహం_Sync( Event_సమూహం_Handle_t x_Event_సమూహం,
                                       స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి,
                                       స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Wait_For,
                                       TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_Event_సమూహం_Sync_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_Event_సమూహం_Sync_Unpriv
MPU_x_Event_సమూహం_Sync_Priv
        b MPU_x_Event_సమూహం_Sync_Impl
MPU_x_Event_సమూహం_Sync_Unpriv
        svc #SYSTEM_CALL_xEventGroupSync
}

#అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

UBaseType_t MPU_ux_Event_సమూహం_Get_సంఖ్య( శూన్య * x_Event_సమూహం ) FREERTOS_SYSTEM_CALL;

__asm UBaseType_t MPU_ux_Event_సమూహం_Get_సంఖ్య( శూన్య * x_Event_సమూహం ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_ux_Event_సమూహం_Get_సంఖ్య_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_ux_Event_సమూహం_Get_సంఖ్య_Unpriv
MPU_ux_Event_సమూహం_Get_సంఖ్య_Priv
        b MPU_ux_Event_సమూహం_Get_సంఖ్య_Impl
MPU_ux_Event_సమూహం_Get_సంఖ్య_Unpriv
        svc #SYSTEM_CALL_uxEventGroupGetNumber
}

#అయితే_ముగింపు /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

శూన్య MPU_v_Event_సమూహం_సమితి_సంఖ్య( శూన్య * x_Event_సమూహం,
                               UBaseType_t ux_Event_సమూహం_సంఖ్య ) FREERTOS_SYSTEM_CALL;

__asm శూన్య MPU_v_Event_సమూహం_సమితి_సంఖ్య( శూన్య * x_Event_సమూహం,
                                     UBaseType_t ux_Event_సమూహం_సంఖ్య ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_v_Event_సమూహం_సమితి_సంఖ్య_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_v_Event_సమూహం_సమితి_సంఖ్య_Unpriv
MPU_v_Event_సమూహం_సమితి_సంఖ్య_Priv
        b MPU_v_Event_సమూహం_సమితి_సంఖ్య_Impl
MPU_v_Event_సమూహం_సమితి_సంఖ్య_Unpriv
        svc #SYSTEM_CALL_vEventGroupSetNumber
}

#అయితే_ముగింపు /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

size_t MPU_x_ప్రవాహం_బఫరు_Send( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                              స్థిరరాశి శూన్య * pv_Tx_దత్తాంశం,
                              size_t x_దత్తాంశం_నిడివి_బైట్లు,
                              TickType_t x_Ticks_గమ్యం_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ప్రవాహం_బఫరు_Send( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                    స్థిరరాశి శూన్య * pv_Tx_దత్తాంశం,
                                    size_t x_దత్తాంశం_నిడివి_బైట్లు,
                                    TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_ప్రవాహం_బఫరు_Send_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_ప్రవాహం_బఫరు_Send_Unpriv
MPU_x_ప్రవాహం_బఫరు_Send_Priv
        b MPU_x_ప్రవాహం_బఫరు_Send_Impl
MPU_x_ప్రవాహం_బఫరు_Send_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSend
}

#అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

size_t MPU_x_ప్రవాహం_బఫరు_Receive( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                 శూన్య * pv_Rx_దత్తాంశం,
                                 size_t x_బఫరు_నిడివి_బైట్లు,
                                 TickType_t x_Ticks_గమ్యం_Wait ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ప్రవాహం_బఫరు_Receive( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                       శూన్య * pv_Rx_దత్తాంశం,
                                       size_t x_బఫరు_నిడివి_బైట్లు,
                                       TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_ప్రవాహం_బఫరు_Receive_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_ప్రవాహం_బఫరు_Receive_Unpriv
MPU_x_ప్రవాహం_బఫరు_Receive_Priv
        b MPU_x_ప్రవాహం_బఫరు_Receive_Impl
MPU_x_ప్రవాహం_బఫరు_Receive_Unpriv
        svc #SYSTEM_CALL_xStreamBufferReceive
}

#అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_నిండిన( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_నిండిన( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_ప్రవాహం_బఫరు_Is_నిండిన_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_ప్రవాహం_బఫరు_Is_నిండిన_Unpriv
MPU_x_ప్రవాహం_బఫరు_Is_నిండిన_Priv
        b MPU_x_ప్రవాహం_బఫరు_Is_నిండిన_Impl
MPU_x_ప్రవాహం_బఫరు_Is_నిండిన_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsFull
}

#అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు_Unpriv
MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు_Priv
        b MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు_Impl
MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు_Unpriv
        svc #SYSTEM_CALL_xStreamBufferIsEmpty
}

#అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

size_t MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు_Unpriv
MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు_Priv
        b MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు_Impl
MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSpacesAvailable
}

#అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

size_t MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు_Unpriv
MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు_Priv
        b MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు_Impl
MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు_Unpriv
        svc #SYSTEM_CALL_xStreamBufferBytesAvailable
}

#అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                             size_t xTriggerLevel ) FREERTOS_SYSTEM_CALL;

__asm పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                                   size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level_Unpriv
MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level_Priv
        b MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level_Impl
MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level_Unpriv
        svc #SYSTEM_CALL_xStreamBufferSetTriggerLevel
}

#అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

size_t MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) FREERTOS_SYSTEM_CALL;

__asm size_t MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
{
    PRESERVE8
    బాహ్య MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు_Impl

    నెట్టు {r0}
    mrs r0, control
    tst r0, #1
    తీయి {r0}
    bne MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు_Unpriv
MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు_Priv
        b MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు_Impl
MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు_Unpriv
        svc #SYSTEM_CALL_xStreamBufferNextMessageLengthBytes
}

#అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* configUSE_MPU_WRAPPERS_V1 == 0 */
