/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Copyright 2025 Arm Limited and/or its affiliates
 * <open-source-office@arm.com>
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
#అన్తర్భావ "portmacro.h"

#నిర్వచనం_రద్దు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ఒకవేళ ( configENABLE_MPU == 1 )

    /*
     * Common single-SVC dispatch: wrappers do only one SVC.
     * The SVC handler decides whether to tail-call the implementation directly
     * (privileged) or set up full system-call state (unprivileged).
     */
    #నిర్వచించు FREERTOS_MPU_SVC_DISPATCH( x_System_Call_సంఖ్య )  \
        __asm అస్థిర (                                    \
            "svc %0     \n"                                 \
            :                                               \
            : "i" ( x_System_Call_సంఖ్య )                     \
            : "memory"                                      \
        );

    #ఒకవేళ ( INCLUDE_xTaskDelayUntil == 1 )

        పునాది_Type_t MPU_xTaskDelayUntil( TickType_t * స్థిరరాశి px_మునుపటి_Wake_సమయం,
                                        స్థిరరాశి TickType_t x_సమయం_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_xTaskDelayUntil( TickType_t * స్థిరరాశి px_మునుపటి_Wake_సమయం,
                                        స్థిరరాశి TickType_t x_సమయం_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskDelayUntil );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskAbortDelay == 1 )

        పునాది_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskAbortDelay );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskDelay == 1 )

        శూన్య MPU_vTaskDelay( స్థిరరాశి TickType_t x_Ticks_గమ్యం_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_vTaskDelay( స్థిరరాశి TickType_t x_Ticks_గమ్యం_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskDelay );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_ప్రాధాన్యత_Get == 1 )

        UBaseType_t MPU_ux_Task_ప్రాధాన్యత_Get( స్థిరరాశి TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_ప్రాధాన్యత_Get( స్థిరరాశి TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_ప్రాధాన్యత_Get );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_eTaskGetState );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )

        శూన్య MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_స్థితి_t * px_Task_స్థితి,
                               పునాది_Type_t x_Get_Free_దొంతర_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_స్థితి_t * px_Task_స్థితి,
                               పునాది_Type_t x_Get_Free_దొంతర_Space,
                               eTaskState eState ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskGetInfo );
        }

    #అయితే_ముగింపు /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetIdleTaskHandle );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskSuspend == 1 )

        శూన్య MPU_vTaskSuspend( TaskHandle_t x_Task_గమ్యం_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_vTaskSuspend( TaskHandle_t x_Task_గమ్యం_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSuspend );
        }

/*-----------------------------------------------------------*/

        శూన్య MPU_vTaskResume( TaskHandle_t x_Task_గమ్యం_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_vTaskResume( TaskHandle_t x_Task_గమ్యం_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskResume );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_లెక్క( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_లెక్క( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Tick_లెక్క );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_సంఖ్య_యొక్క_Tasks );
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 )

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Counter( స్థిరరాశి TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Counter( స్థిరరాశి TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_నిరంతరం_సమయం_Counter );
        }

    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 )

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Percent( స్థిరరాశి TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Percent( స్థిరరాశి TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_నిరంతరం_సమయం_Percent );
        }

    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent );
        }

/*-----------------------------------------------------------*/

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter );
        }

    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )

        శూన్య MPU_v_Task_సమితి_Application_Task_ట్యాగ్( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_Task_సమితి_Application_Task_ట్యాగ్( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_సమితి_Application_Task_ట్యాగ్ );
        }

    #అయితే_ముగింపు /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ట్యాగ్( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ట్యాగ్( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Application_Task_ట్యాగ్ );
        }

    #అయితే_ముగింపు /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు != 0 )

        శూన్య MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_సమితి,
                                                    పునాది_Type_t x_సూచీ,
                                                    శూన్య * pv_విలువ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_సమితి,
                                                    పునాది_Type_t x_సూచీ,
                                                    శూన్య * pv_విలువ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_సమితి_Thread_Local_Storage_సూచిక );
        }

    #అయితే_ముగింపు /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు != 0 )

        శూన్య * MPU_pv_Task_Get_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_Query,
                                                       పునాది_Type_t x_సూచీ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య * MPU_pv_Task_Get_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_Query,
                                                       పునాది_Type_t x_సూచీ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_సూచిక );
        }

    #అయితే_ముగింపు /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( Task_స్థితి_t * స్థిరరాశి px_Task_స్థితి_Array,
                                              స్థిరరాశి UBaseType_t ux_Array_కొలత,
                                              config_నిరంతరం_సమయం_COUNTER_TYPE * స్థిరరాశి pul_మొత్తం_నిరంతరం_సమయం ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( Task_స్థితి_t * స్థిరరాశి px_Task_స్థితి_Array,
                                              స్థిరరాశి UBaseType_t ux_Array_కొలత,
                                              config_నిరంతరం_సమయం_COUNTER_TYPE * స్థిరరాశి pul_మొత్తం_నిరంతరం_సమయం ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskGetSystemState );
        }

    #అయితే_ముగింపు /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_దొంతర_ఎగువ_Water_Mark );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2 == 1 )

        config_దొంతర_లోతు_TYPE MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_దొంతర_లోతు_TYPE MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2 );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetCurrentTaskHandle );
        }

    #అయితే_ముగింపు /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskGetSchedulerState == 1 )

        పునాది_Type_t MPU_xTaskGetSchedulerState( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_xTaskGetSchedulerState( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetSchedulerState );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    శూన్య MPU_v_Task_సమితి_సమయం_బహిర్గతం_State( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    శూన్య MPU_v_Task_సమితి_సమయం_బహిర్గతం_State( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_సమితి_సమయం_బహిర్గతం_State );
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_Task_Check_For_సమయం_బహిర్గతం( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం,
                                         TickType_t * స్థిరరాశి px_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    పునాది_Type_t MPU_x_Task_Check_For_సమయం_బహిర్గతం( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం,
                                         TickType_t * స్థిరరాశి px_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Check_For_సమయం_బహిర్గతం );
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        పునాది_Type_t MPU_x_Task_Generic_Notify_నమోదు( స్థిరరాశి xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_Task_Generic_Notify_నమోదు( స్థిరరాశి xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotify );
        }

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        పునాది_Type_t MPU_x_Task_Generic_Notify_Wait_నమోదు( స్థిరరాశి xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_Task_Generic_Notify_Wait_నమోదు( స్థిరరాశి xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyWait );
        }

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_సూచీ_గమ్యం_Wait_On,
                                              పునాది_Type_t x_Clear_లెక్క_On_Exit,
                                              TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_సూచీ_గమ్యం_Wait_On,
                                              పునాది_Type_t x_Clear_లెక్క_On_Exit,
                                              TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGenericNotifyTake );
        }

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        పునాది_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_సూచీ_గమ్యం_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_సూచీ_గమ్యం_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyStateClear );
        }

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_విలువ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_సూచీ_గమ్యం_Clear,
                                                    uint32_t ul_బిట్లు_గమ్యం_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_విలువ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_సూచీ_గమ్యం_Clear,
                                                    uint32_t ul_బిట్లు_గమ్యం_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Generic_Notify_విలువ_Clear );
        }

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Generic_Send( వరుస_Handle_t x_వరుస,
                                      స్థిరరాశి శూన్య * స్థిరరాశి pv_అంశం_గమ్యం_వరుస,
                                      TickType_t x_Ticks_గమ్యం_Wait,
                                      స్థిరరాశి పునాది_Type_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    పునాది_Type_t MPU_x_వరుస_Generic_Send( వరుస_Handle_t x_వరుస,
                                      స్థిరరాశి శూన్య * స్థిరరాశి pv_అంశం_గమ్యం_వరుస,
                                      TickType_t x_Ticks_గమ్యం_Wait,
                                      స్థిరరాశి పునాది_Type_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_వరుస_Generic_Send );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_వరుస_Messages_నిరీక్షణ( స్థిరరాశి వరుస_Handle_t x_వరుస ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_వరుస_Messages_నిరీక్షణ( స్థిరరాశి వరుస_Handle_t x_వరుస ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_వరుస_Messages_నిరీక్షణ );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_వరుస_Spaces_అందుబాటు( స్థిరరాశి వరుస_Handle_t x_వరుస ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_వరుస_Spaces_అందుబాటు( స్థిరరాశి వరుస_Handle_t x_వరుస ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_వరుస_Spaces_అందుబాటు );
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Receive( వరుస_Handle_t x_వరుస,
                                  శూన్య * స్థిరరాశి pv_బఫరు,
                                  TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    పునాది_Type_t MPU_x_వరుస_Receive( వరుస_Handle_t x_వరుస,
                                  శూన్య * స్థిరరాశి pv_బఫరు,
                                  TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_వరుస_Receive );
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Peek( వరుస_Handle_t x_వరుస,
                               శూన్య * స్థిరరాశి pv_బఫరు,
                               TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    పునాది_Type_t MPU_x_వరుస_Peek( వరుస_Handle_t x_వరుస,
                               శూన్య * స్థిరరాశి pv_బఫరు,
                               TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_వరుస_Peek );
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Semaphore_Take( వరుస_Handle_t x_వరుస,
                                        TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    పునాది_Type_t MPU_x_వరుస_Semaphore_Take( వరుస_Handle_t x_వరుస,
                                        TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_వరుస_Semaphore_Take );
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_వరుస_Get_Mutex_Holder( వరుస_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_వరుస_Get_Mutex_Holder( వరుస_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_వరుస_Get_Mutex_Holder );
        }

    #అయితే_ముగింపు /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_RECURSIVE_MUTEXES == 1 )

        పునాది_Type_t MPU_x_వరుస_Take_Mutex_Recursive( వరుస_Handle_t xMutex,
                                                 TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_వరుస_Take_Mutex_Recursive( వరుస_Handle_t xMutex,
                                                 TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_వరుస_Take_Mutex_Recursive );
        }

    #అయితే_ముగింపు /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_RECURSIVE_MUTEXES == 1 )

        పునాది_Type_t MPU_x_వరుస_Give_Mutex_Recursive( వరుస_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_వరుస_Give_Mutex_Recursive( వరుస_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_వరుస_Give_Mutex_Recursive );
        }

    #అయితే_ముగింపు /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )

        వరుస_సమితి_Member_Handle_t MPU_x_వరుస_Select_From_సమితి( వరుస_సమితి_Handle_t x_వరుస_సమితి,
                                                        స్థిరరాశి TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        వరుస_సమితి_Member_Handle_t MPU_x_వరుస_Select_From_సమితి( వరుస_సమితి_Handle_t x_వరుస_సమితి,
                                                        స్థిరరాశి TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_వరుస_Select_From_సమితి );
        }

    #అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )

        పునాది_Type_t MPU_x_వరుస_కూడు_గమ్యం_సమితి( వరుస_సమితి_Member_Handle_t x_వరుస_Or_Semaphore,
                                       వరుస_సమితి_Handle_t x_వరుస_సమితి ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_వరుస_కూడు_గమ్యం_సమితి( వరుస_సమితి_Member_Handle_t x_వరుస_Or_Semaphore,
                                       వరుస_సమితి_Handle_t x_వరుస_సమితి ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_వరుస_కూడు_గమ్యం_సమితి );
        }

    #అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_వరుస_REGISTRY_కొలత > 0 )

        శూన్య MPU_v_వరుస_కూడు_గమ్యం_Registry( వరుస_Handle_t x_వరుస,
                                      స్థిరరాశి అక్షరం * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_వరుస_కూడు_గమ్యం_Registry( వరుస_Handle_t x_వరుస,
                                      స్థిరరాశి అక్షరం * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_వరుస_కూడు_గమ్యం_Registry );
        }

    #అయితే_ముగింపు /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_వరుస_REGISTRY_కొలత > 0 )

        శూన్య MPU_v_వరుస_Unregister_వరుస( వరుస_Handle_t x_వరుస ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_వరుస_Unregister_వరుస( వరుస_Handle_t x_వరుస ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_వరుస_Unregister_వరుస );
        }

    #అయితే_ముగింపు /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_వరుస_REGISTRY_కొలత > 0 )

        స్థిరరాశి అక్షరం * MPU_pc_వరుస_Get_Name( వరుస_Handle_t x_వరుస ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        స్థిరరాశి అక్షరం * MPU_pc_వరుస_Get_Name( వరుస_Handle_t x_వరుస ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pc_వరుస_Get_Name );
        }

    #అయితే_ముగింపు /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        శూన్య * MPU_pvTimerGetTimerID( స్థిరరాశి TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య * MPU_pvTimerGetTimerID( స్థిరరాశి TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTimerGetTimerID );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        శూన్య MPU_v_Timer_సమితి_Timer_ID( TimerHandle_t xTimer,
                                   శూన్య * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_Timer_సమితి_Timer_ID( TimerHandle_t xTimer,
                                   శూన్య * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_సమితి_Timer_ID );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_x_Timer_Is_Timer_చురుకైన( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_Timer_Is_Timer_చురుకైన( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Is_Timer_చురుకైన );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_x_Timer_Generic_Command_From_Task_నమోదు( స్థిరరాశి xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_Timer_Generic_Command_From_Task_నమోదు( స్థిరరాశి xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGenericCommandFromTask );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        స్థిరరాశి అక్షరం * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        స్థిరరాశి అక్షరం * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcTimerGetName );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        శూన్య MPU_v_Timer_సమితి_Reload_బహుళకం( TimerHandle_t xTimer,
                                      స్థిరరాశి పునాది_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_Timer_సమితి_Reload_బహుళకం( TimerHandle_t xTimer,
                                      స్థిరరాశి పునాది_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_సమితి_Reload_బహుళకం );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_x_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Reload_బహుళకం );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Timer_Get_Reload_బహుళకం );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetPeriod );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_సమయం( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_సమయం( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Expiry_సమయం );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_Wait_బిట్లు_నమోదు( స్థిరరాశి x_Event_సమూహం_Wait_బిట్లు_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_బిట్లు_t MPU_x_Event_సమూహం_Wait_బిట్లు_నమోదు( స్థిరరాశి x_Event_సమూహం_Wait_బిట్లు_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_సమూహం_Wait_బిట్లు );
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_Clear_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                              స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_బిట్లు_t MPU_x_Event_సమూహం_Clear_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                              స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_సమూహం_Clear_బిట్లు );
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_సమితి_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                            స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_బిట్లు_t MPU_x_Event_సమూహం_సమితి_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                            స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_సమూహం_సమితి_బిట్లు );
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_Sync( Event_సమూహం_Handle_t x_Event_సమూహం,
                                         స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి,
                                         స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Wait_For,
                                         TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_బిట్లు_t MPU_x_Event_సమూహం_Sync( Event_సమూహం_Handle_t x_Event_సమూహం,
                                         స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి,
                                         స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Wait_For,
                                         TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_సమూహం_Sync );
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_సమూహం_Get_సంఖ్య( శూన్య * x_Event_సమూహం ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_సమూహం_Get_సంఖ్య( శూన్య * x_Event_సమూహం ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Event_సమూహం_Get_సంఖ్య );
        }

    #అయితే_ముగింపు /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        శూన్య MPU_v_Event_సమూహం_సమితి_సంఖ్య( శూన్య * x_Event_సమూహం,
                                       UBaseType_t ux_Event_సమూహం_సంఖ్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_Event_సమూహం_సమితి_సంఖ్య( శూన్య * x_Event_సమూహం,
                                       UBaseType_t ux_Event_సమూహం_సంఖ్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Event_సమూహం_సమితి_సంఖ్య );
        }

    #అయితే_ముగింపు /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_Send( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                      స్థిరరాశి శూన్య * pv_Tx_దత్తాంశం,
                                      size_t x_దత్తాంశం_నిడివి_బైట్లు,
                                      TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ప్రవాహం_బఫరు_Send( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                      స్థిరరాశి శూన్య * pv_Tx_దత్తాంశం,
                                      size_t x_దత్తాంశం_నిడివి_బైట్లు,
                                      TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ప్రవాహం_బఫరు_Send );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_Receive( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                         శూన్య * pv_Rx_దత్తాంశం,
                                         size_t x_బఫరు_నిడివి_బైట్లు,
                                         TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ప్రవాహం_బఫరు_Receive( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                         శూన్య * pv_Rx_దత్తాంశం,
                                         size_t x_బఫరు_నిడివి_బైట్లు,
                                         TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ప్రవాహం_బఫరు_Receive );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_నిండిన( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_నిండిన( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ప్రవాహం_బఫరు_Is_నిండిన );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ప్రవాహం_బఫరు_Is_ఖాళీలు );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) */
