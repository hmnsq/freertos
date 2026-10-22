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
#अन्तर्भाव "portmacro.h"

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#यदि ( configENABLE_MPU == 1 )

    /*
     * Common single-SVC dispatch: wrappers do only one SVC.
     * The SVC handler decides whether to tail-call the implementation directly
     * (privileged) or set up full system-call state (unprivileged).
     */
    #परिभाषय FREERTOS_MPU_SVC_DISPATCH( x_System_Call_सङ्ख्या )  \
        __asm चञ्चल (                                    \
            "svc %0     \n"                                 \
            :                                               \
            : "i" ( x_System_Call_सङ्ख्या )                     \
            : "memory"                                      \
        );

    #यदि ( INCLUDE_xTaskDelayUntil == 1 )

        आधारः_Type_t MPU_xTaskDelayUntil( TickType_t * ध्रुव pxPreviousWakeTime,
                                        ध्रुव TickType_t xTimeIncrement ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xTaskDelayUntil( TickType_t * ध्रुव pxPreviousWakeTime,
                                        ध्रुव TickType_t xTimeIncrement ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskDelayUntil );
        }

    #यदि_अन्तः /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskAbortDelay == 1 )

        आधारः_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskAbortDelay );
        }

    #यदि_अन्तः /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskDelay == 1 )

        शून्य MPU_vTaskDelay( ध्रुव TickType_t x_Ticks_गन्तव्यम्_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_vTaskDelay( ध्रुव TickType_t x_Ticks_गन्तव्यम्_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskDelay );
        }

    #यदि_अन्तः /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_प्राथमिकता_Get == 1 )

        UBaseType_t MPU_ux_Task_प्राथमिकता_Get( ध्रुव TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_प्राथमिकता_Get( ध्रुव TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_प्राथमिकता_Get );
        }

    #यदि_अन्तः /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_eTaskGetState );
        }

    #यदि_अन्तः /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TRACE_FACILITY == 1 )

        शून्य MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_स्थितिः_t * px_Task_स्थितिः,
                               आधारः_Type_t x_Get_Free_राशिः_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_स्थितिः_t * px_Task_स्थितिः,
                               आधारः_Type_t x_Get_Free_राशिः_Space,
                               eTaskState eState ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskGetInfo );
        }

    #यदि_अन्तः /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetIdleTaskHandle );
        }

    #यदि_अन्तः /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskSuspend == 1 )

        शून्य MPU_vTaskSuspend( TaskHandle_t x_Task_गन्तव्यम्_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_vTaskSuspend( TaskHandle_t x_Task_गन्तव्यम्_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSuspend );
        }

/*-----------------------------------------------------------*/

        शून्य MPU_vTaskResume( TaskHandle_t x_Task_गन्तव्यम्_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_vTaskResume( TaskHandle_t x_Task_गन्तव्यम्_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskResume );
        }

    #यदि_अन्तः /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_गणनम्( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_गणनम्( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Tick_गणनम् );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks );
    }
/*-----------------------------------------------------------*/

    #यदि ( config_GENERATE_सततम्_TIME_STATS == 1 )

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_गणक( ध्रुव TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_गणक( ध्रुव TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_सततम्_Time_गणक );
        }

    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_GENERATE_सततम्_TIME_STATS == 1 )

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_Percent( ध्रुव TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_Percent( ध्रुव TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_सततम्_Time_Percent );
        }

    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_GENERATE_सततम्_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_Percent( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_Percent( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_सततम्_Time_Percent );
        }

/*-----------------------------------------------------------*/

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_गणक( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_गणक( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_सततम्_Time_गणक );
        }

    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )

        शून्य MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_समुच्चयः_Application_Task_चिह्नकम् );
        }

    #यदि_अन्तः /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_चिह्नकम्( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_चिह्नकम्( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Application_Task_चिह्नकम् );
        }

    #यदि_अन्तः /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_अङ्कः_THREAD_LOCAL_STORAGE_सूचकाः != 0 )

        शून्य MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer( TaskHandle_t x_Task_गन्तव्यम्_समुच्चयः,
                                                    आधारः_Type_t x_सूचकांक,
                                                    शून्य * pv_मानम् ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer( TaskHandle_t x_Task_गन्तव्यम्_समुच्चयः,
                                                    आधारः_Type_t x_सूचकांक,
                                                    शून्य * pv_मानम् ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_समुच्चयः_Thread_Local_Storage_Pointer );
        }

    #यदि_अन्तः /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_अङ्कः_THREAD_LOCAL_STORAGE_सूचकाः != 0 )

        शून्य * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t x_Task_गन्तव्यम्_Query,
                                                       आधारः_Type_t x_सूचकांक ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t x_Task_गन्तव्यम्_Query,
                                                       आधारः_Type_t x_सूचकांक ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer );
        }

    #यदि_अन्तः /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( Task_स्थितिः_t * ध्रुव px_Task_स्थितिः_Array,
                                              ध्रुव UBaseType_t ux_Array_आकार,
                                              config_सततम्_TIME_गणक_TYPE * ध्रुव pul_योग_सततम्_Time ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( Task_स्थितिः_t * ध्रुव px_Task_स्थितिः_Array,
                                              ध्रुव UBaseType_t ux_Array_आकार,
                                              config_सततम्_TIME_गणक_TYPE * ध्रुव pul_योग_सततम्_Time ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskGetSystemState );
        }

    #यदि_अन्तः /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_राशिः_उच्चः_Water_Mark );
        }

    #यदि_अन्तः /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark2 == 1 )

        config_राशिः_गभीरता_TYPE MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_राशिः_गभीरता_TYPE MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_राशिः_उच्चः_Water_Mark2 );
        }

    #यदि_अन्तः /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetCurrentTaskHandle );
        }

    #यदि_अन्तः /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetSchedulerState == 1 )

        आधारः_Type_t MPU_xTaskGetSchedulerState( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xTaskGetSchedulerState( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetSchedulerState );
        }

    #यदि_अन्तः /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    शून्य MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम् ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    शून्य MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम् ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_समुच्चयः_Time_बहिर्गमनम्_State );
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_x_Task_Check_For_Time_बहिर्गमनम्( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम्,
                                         TickType_t * ध्रुव px_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    आधारः_Type_t MPU_x_Task_Check_For_Time_बहिर्गमनम्( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम्,
                                         TickType_t * ध्रुव px_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Check_For_Time_बहिर्गमनम् );
    }
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        आधारः_Type_t MPU_x_Task_Generic_Notify_प्रविष्टिः( ध्रुव xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Task_Generic_Notify_प्रविष्टिः( ध्रुव xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotify );
        }

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        आधारः_Type_t MPU_x_Task_Generic_Notify_Wait_प्रविष्टिः( ध्रुव xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Task_Generic_Notify_Wait_प्रविष्टिः( ध्रुव xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyWait );
        }

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_सूचकांक_गन्तव्यम्_Wait_On,
                                              आधारः_Type_t x_Clear_गणनम्_On_Exit,
                                              TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_सूचकांक_गन्तव्यम्_Wait_On,
                                              आधारः_Type_t x_Clear_गणनम्_On_Exit,
                                              TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGenericNotifyTake );
        }

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        आधारः_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyStateClear );
        }

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_मानम्_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear,
                                                    uint32_t ul_द्वयङ्काः_गन्तव्यम्_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_मानम्_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear,
                                                    uint32_t ul_द्वयङ्काः_गन्तव्यम्_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Generic_Notify_मानम्_Clear );
        }

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      ध्रुव शून्य * ध्रुव pv_Item_गन्तव्यम्_Queue,
                                      TickType_t x_Ticks_गन्तव्यम्_Wait,
                                      ध्रुव आधारः_Type_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    आधारः_Type_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      ध्रुव शून्य * ध्रुव pv_Item_गन्तव्यम्_Queue,
                                      TickType_t x_Ticks_गन्तव्यम्_Wait,
                                      ध्रुव आधारः_Type_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGenericSend );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Queue_Messages_प्रतीक्षा( ध्रुव QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Queue_Messages_प्रतीक्षा( ध्रुव QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Queue_Messages_प्रतीक्षा );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Queue_Spaces_उपलब्धम्( ध्रुव QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Queue_Spaces_उपलब्धम्( ध्रुव QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Queue_Spaces_उपलब्धम् );
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                  शून्य * ध्रुव pv_बफर,
                                  TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    आधारः_Type_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                  शून्य * ध्रुव pv_बफर,
                                  TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueReceive );
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               शून्य * ध्रुव pv_बफर,
                               TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    आधारः_Type_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               शून्य * ध्रुव pv_बफर,
                               TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueuePeek );
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    आधारः_Type_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueSemaphoreTake );
    }
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGetMutexHolder );
        }

    #यदि_अन्तः /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_RECURSIVE_MUTEXES == 1 )

        आधारः_Type_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueTakeMutexRecursive );
        }

    #यदि_अन्तः /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_RECURSIVE_MUTEXES == 1 )

        आधारः_Type_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xQueueGiveMutexRecursive );
        }

    #यदि_अन्तः /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )

        Queue_समुच्चयः_Member_Handle_t MPU_x_Queue_Select_From_समुच्चयः( Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः,
                                                        ध्रुव TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Queue_समुच्चयः_Member_Handle_t MPU_x_Queue_Select_From_समुच्चयः( Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः,
                                                        ध्रुव TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Queue_Select_From_समुच्चयः );
        }

    #यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )

        आधारः_Type_t MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः( Queue_समुच्चयः_Member_Handle_t xQueueOrSemaphore,
                                       Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः( Queue_समुच्चयः_Member_Handle_t xQueueOrSemaphore,
                                       Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः );
        }

    #यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_QUEUE_REGISTRY_आकार > 0 )

        शून्य MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry( QueueHandle_t xQueue,
                                      ध्रुव वर्ण * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry( QueueHandle_t xQueue,
                                      ध्रुव वर्ण * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Queue_सङ्कलय_गन्तव्यम्_Registry );
        }

    #यदि_अन्तः /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_QUEUE_REGISTRY_आकार > 0 )

        शून्य MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vQueueUnregisterQueue );
        }

    #यदि_अन्तः /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_QUEUE_REGISTRY_आकार > 0 )

        ध्रुव वर्ण * MPU_pcQueueGetName( QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ध्रुव वर्ण * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcQueueGetName );
        }

    #यदि_अन्तः /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        शून्य * MPU_pvTimerGetTimerID( ध्रुव TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य * MPU_pvTimerGetTimerID( ध्रुव TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTimerGetTimerID );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        शून्य MPU_v_Timer_समुच्चयः_Timer_ID( TimerHandle_t xTimer,
                                   शून्य * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_v_Timer_समुच्चयः_Timer_ID( TimerHandle_t xTimer,
                                   शून्य * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_समुच्चयः_Timer_ID );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_x_Timer_Is_Timer_सक्रिय( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Timer_Is_Timer_सक्रिय( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Is_Timer_सक्रिय );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_x_Timer_Generic_Command_From_Task_प्रविष्टिः( ध्रुव xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Timer_Generic_Command_From_Task_प्रविष्टिः( ध्रुव xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGenericCommandFromTask );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        ध्रुव वर्ण * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ध्रुव वर्ण * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcTimerGetName );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        शून्य MPU_v_Timer_समुच्चयः_Reload_बहुलकम्( TimerHandle_t xTimer,
                                      ध्रुव आधारः_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_v_Timer_समुच्चयः_Reload_बहुलकम्( TimerHandle_t xTimer,
                                      ध्रुव आधारः_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_समुच्चयः_Reload_बहुलकम् );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_x_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Reload_बहुलकम् );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Timer_Get_Reload_बहुलकम् );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetPeriod );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetExpiryTime );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Wait_द्वयङ्काः_प्रविष्टिः( ध्रुव x_Event_गणः_Wait_द्वयङ्काः_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Wait_द्वयङ्काः_प्रविष्टिः( ध्रुव x_Event_गणः_Wait_द्वयङ्काः_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_गणः_Wait_द्वयङ्काः );
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Clear_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                              ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Clear_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                              ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_गणः_Clear_द्वयङ्काः );
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                            ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_द्वयङ्काः_t MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                            ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_गणः_समुच्चयः_द्वयङ्काः );
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Sync( Event_गणः_Handle_t x_Event_गणः,
                                         ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः,
                                         ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Wait_For,
                                         TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Sync( Event_गणः_Handle_t x_Event_गणः,
                                         ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः,
                                         ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Wait_For,
                                         TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_गणः_Sync );
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_गणः_Get_सङ्ख्या( शून्य * x_Event_गणः ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_गणः_Get_सङ्ख्या( शून्य * x_Event_गणः ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Event_गणः_Get_सङ्ख्या );
        }

    #यदि_अन्तः /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        शून्य MPU_v_Event_गणः_समुच्चयः_सङ्ख्या( शून्य * x_Event_गणः,
                                       UBaseType_t ux_Event_गणः_सङ्ख्या ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_v_Event_गणः_समुच्चयः_सङ्ख्या( शून्य * x_Event_गणः,
                                       UBaseType_t ux_Event_गणः_सङ्ख्या ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Event_गणः_समुच्चयः_सङ्ख्या );
        }

    #यदि_अन्तः /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_Send( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                      ध्रुव शून्य * pv_Tx_दत्त,
                                      size_t x_दत्त_दीर्घता_अष्टकानि,
                                      TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_प्रवाहः_बफर_Send( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                      ध्रुव शून्य * pv_Tx_दत्त,
                                      size_t x_दत्त_दीर्घता_अष्टकानि,
                                      TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_प्रवाहः_बफर_Send );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_Receive( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                         शून्य * pv_Rx_दत्त,
                                         size_t x_बफर_दीर्घता_अष्टकानि,
                                         TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_प्रवाहः_बफर_Receive( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                         शून्य * pv_Rx_दत्त,
                                         size_t x_बफर_दीर्घता_अष्टकानि,
                                         TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_प्रवाहः_बफर_Receive );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_पूर्णम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_पूर्णम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_प्रवाहः_बफर_Is_पूर्णम् );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_रिक्तानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_रिक्तानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_प्रवाहः_बफर_Is_रिक्तानि );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_प्रवाहः_बफर_Spaces_उपलब्धम् );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम् );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) */
