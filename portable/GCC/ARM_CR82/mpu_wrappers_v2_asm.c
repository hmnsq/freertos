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
#شامل "portmacro.h"

#تعریف_منسوخ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#اگر ( configENABLE_MPU == 1 )

    /*
     * Common single-SVC dispatch: wrappers do only one SVC.
     * The SVC handler decides whether to tail-call the implementation directly
     * (privileged) or set up full system-call state (unprivileged).
     */
    #تعریف_کرو FREERTOS_MPU_SVC_DISPATCH( x_System_Call_نمبر )  \
        __asm متلون (                                    \
            "svc %0     \n"                                 \
            :                                               \
            : "i" ( x_System_Call_نمبر )                     \
            : "memory"                                      \
        );

    #اگر ( INCLUDE_xTaskDelayUntil == 1 )

        بنیاد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_وقت,
                                        ثابت TickType_t x_وقت_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_وقت,
                                        ثابت TickType_t x_وقت_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskDelayUntil );
        }

    #اگر_ختم /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskAbortDelay == 1 )

        بنیاد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskAbortDelay );
        }

    #اگر_ختم /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskDelay == 1 )

        خالی MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskDelay );
        }

    #اگر_ختم /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_ترجیح_Get == 1 )

        UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_ترجیح_Get );
        }

    #اگر_ختم /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_eTaskGetState );
        }

    #اگر_ختم /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TRACE_FACILITY == 1 )

        خالی MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               بنیاد_Type_t x_Get_Free_ڈھیر_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               بنیاد_Type_t x_Get_Free_ڈھیر_Space,
                               eTaskState eState ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskGetInfo );
        }

    #اگر_ختم /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetIdleTaskHandle );
        }

    #اگر_ختم /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskSuspend == 1 )

        خالی MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSuspend );
        }

/*-----------------------------------------------------------*/

        خالی MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskResume );
        }

    #اگر_ختم /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_گنتی( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_گنتی( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Tick_گنتی );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_نمبر_کا_Tasks( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_نمبر_کا_Tasks( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_نمبر_کا_Tasks );
    }
/*-----------------------------------------------------------*/

    #اگر ( config_GENERATE_تسلسل_وقت_STATS == 1 )

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_شمار( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_شمار( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_تسلسل_وقت_شمار );
        }

    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_GENERATE_تسلسل_وقت_STATS == 1 )

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_Percent( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_Percent( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_تسلسل_وقت_Percent );
        }

    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_GENERATE_تسلسل_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_تسلسل_وقت_Percent );
        }

/*-----------------------------------------------------------*/

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_تسلسل_وقت_شمار );
        }

    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )

        خالی MPU_v_Task_سیٹ_Application_Task_لیبل( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_Task_سیٹ_Application_Task_لیبل( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_سیٹ_Application_Task_لیبل );
        }

    #اگر_ختم /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_لیبل( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_لیبل( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Application_Task_لیبل );
        }

    #اگر_ختم /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_عدد_THREAD_LOCAL_STORAGE_اشارے != 0 )

        خالی MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_سیٹ,
                                                    بنیاد_Type_t x_اشاریہ,
                                                    خالی * pv_قدر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_سیٹ,
                                                    بنیاد_Type_t x_اشاریہ,
                                                    خالی * pv_قدر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر );
        }

    #اگر_ختم /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_عدد_THREAD_LOCAL_STORAGE_اشارے != 0 )

        خالی * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_Query,
                                                       بنیاد_Type_t x_اشاریہ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_Query,
                                                       بنیاد_Type_t x_اشاریہ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_اشارہ_گر );
        }

    #اگر_ختم /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                              ثابت UBaseType_t ux_Array_سائز,
                                              config_تسلسل_وقت_شمار_TYPE * ثابت pul_کل_تسلسل_وقت ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                              ثابت UBaseType_t ux_Array_سائز,
                                              config_تسلسل_وقت_شمار_TYPE * ثابت pul_کل_تسلسل_وقت ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskGetSystemState );
        }

    #اگر_ختم /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ڈھیر_بلند_Water_Mark );
        }

    #اگر_ختم /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark2 == 1 )

        config_ڈھیر_گہرائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ڈھیر_گہرائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ڈھیر_بلند_Water_Mark2 );
        }

    #اگر_ختم /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetCurrentTaskHandle );
        }

    #اگر_ختم /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskGetSchedulerState == 1 )

        بنیاد_Type_t MPU_xTaskGetSchedulerState( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_xTaskGetSchedulerState( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetSchedulerState );
        }

    #اگر_ختم /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    خالی MPU_v_Task_سیٹ_وقت_برآمد_State( وقت_برآمد_t * ثابت px_وقت_برآمد ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    خالی MPU_v_Task_سیٹ_وقت_برآمد_State( وقت_برآمد_t * ثابت px_وقت_برآمد ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_سیٹ_وقت_برآمد_State );
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_Task_Check_For_وقت_برآمد( وقت_برآمد_t * ثابت px_وقت_برآمد,
                                         TickType_t * ثابت px_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنیاد_Type_t MPU_x_Task_Check_For_وقت_برآمد( وقت_برآمد_t * ثابت px_وقت_برآمد,
                                         TickType_t * ثابت px_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Check_For_وقت_برآمد );
    }
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنیاد_Type_t MPU_x_Task_Generic_Notify_اندراج( ثابت xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_Task_Generic_Notify_اندراج( ثابت xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotify );
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنیاد_Type_t MPU_x_Task_Generic_Notify_Wait_اندراج( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_Task_Generic_Notify_Wait_اندراج( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyWait );
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاریہ_مقصد_Wait_On,
                                              بنیاد_Type_t x_Clear_گنتی_On_Exit,
                                              TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاریہ_مقصد_Wait_On,
                                              بنیاد_Type_t x_Clear_گنتی_On_Exit,
                                              TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGenericNotifyTake );
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنیاد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_اشاریہ_مقصد_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_اشاریہ_مقصد_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyStateClear );
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_اشاریہ_مقصد_Clear,
                                                    uint32_t ul_بٹ_مقصد_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_اشاریہ_مقصد_Clear,
                                                    uint32_t ul_بٹ_مقصد_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Generic_Notify_قدر_Clear );
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                      ثابت خالی * ثابت pv_شے_مقصد_قطار,
                                      TickType_t x_Ticks_مقصد_Wait,
                                      ثابت بنیاد_Type_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنیاد_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                      ثابت خالی * ثابت pv_شے_مقصد_قطار,
                                      TickType_t x_Ticks_مقصد_Wait,
                                      ثابت بنیاد_Type_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Generic_Send );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_انتظار( ثابت قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_قطار_Messages_انتظار( ثابت قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_قطار_Messages_انتظار );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_قطار_Spaces_دستیاب );
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                                  خالی * ثابت pv_بفر,
                                  TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنیاد_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                                  خالی * ثابت pv_بفر,
                                  TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Receive );
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                               خالی * ثابت pv_بفر,
                               TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنیاد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                               خالی * ثابت pv_بفر,
                               TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Peek );
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                        TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنیاد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                        TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Semaphore_Take );
    }
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Get_Mutex_Holder );
        }

    #اگر_ختم /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنیاد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                                 TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                                 TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Take_Mutex_Recursive );
        }

    #اگر_ختم /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنیاد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Give_Mutex_Recursive );
        }

    #اگر_ختم /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_قطار_SETS == 1 )

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                        ثابت TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                        ثابت TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Select_From_سیٹ );
        }

    #اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_قطار_SETS == 1 )

        بنیاد_Type_t MPU_x_قطار_جوڑو_مقصد_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                       قطار_سیٹ_Handle_t x_قطار_سیٹ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_قطار_جوڑو_مقصد_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                       قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_جوڑو_مقصد_سیٹ );
        }

    #اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_قطار_REGISTRY_سائز > 0 )

        خالی MPU_v_قطار_جوڑو_مقصد_Registry( قطار_Handle_t x_قطار,
                                      ثابت حرف * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_قطار_جوڑو_مقصد_Registry( قطار_Handle_t x_قطار,
                                      ثابت حرف * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_قطار_جوڑو_مقصد_Registry );
        }

    #اگر_ختم /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_قطار_REGISTRY_سائز > 0 )

        خالی MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_قطار_Unregister_قطار );
        }

    #اگر_ختم /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_قطار_REGISTRY_سائز > 0 )

        ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pc_قطار_Get_Name );
        }

    #اگر_ختم /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        خالی * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTimerGetTimerID );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        خالی MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                                   خالی * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                                   خالی * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_سیٹ_Timer_ID );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Is_Timer_فعال );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_x_Timer_Generic_Command_From_Task_اندراج( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_Timer_Generic_Command_From_Task_اندراج( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGenericCommandFromTask );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcTimerGetName );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        خالی MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                                      ثابت بنیاد_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                                      ثابت بنیاد_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_سیٹ_Reload_منوال );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_x_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Reload_منوال );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Timer_Get_Reload_منوال );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetPeriod );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Expiry_وقت );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_اندراج( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_اندراج( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروہ_Wait_بٹ );
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                              ثابت Event_بٹ_t ux_بٹ_مقصد_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                              ثابت Event_بٹ_t ux_بٹ_مقصد_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروہ_Clear_بٹ );
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                            ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                            ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروہ_سیٹ_بٹ );
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Sync( Event_گروہ_Handle_t x_Event_گروہ,
                                         ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ,
                                         ثابت Event_بٹ_t ux_بٹ_مقصد_Wait_For,
                                         TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بٹ_t MPU_x_Event_گروہ_Sync( Event_گروہ_Handle_t x_Event_گروہ,
                                         ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ,
                                         ثابت Event_بٹ_t ux_بٹ_مقصد_Wait_For,
                                         TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروہ_Sync );
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_گروہ_Get_نمبر( خالی * x_Event_گروہ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_گروہ_Get_نمبر( خالی * x_Event_گروہ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Event_گروہ_Get_نمبر );
        }

    #اگر_ختم /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        خالی MPU_v_Event_گروہ_سیٹ_نمبر( خالی * x_Event_گروہ,
                                       UBaseType_t ux_Event_گروہ_نمبر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_Event_گروہ_سیٹ_نمبر( خالی * x_Event_گروہ,
                                       UBaseType_t ux_Event_گروہ_نمبر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Event_گروہ_سیٹ_نمبر );
        }

    #اگر_ختم /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Send( دھارا_بفر_Handle_t x_دھارا_بفر,
                                      ثابت خالی * pv_Tx_ڈیٹا,
                                      size_t x_ڈیٹا_لمبائی_بائٹیں,
                                      TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_Send( دھارا_بفر_Handle_t x_دھارا_بفر,
                                      ثابت خالی * pv_Tx_ڈیٹا,
                                      size_t x_ڈیٹا_لمبائی_بائٹیں,
                                      TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_Send );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Receive( دھارا_بفر_Handle_t x_دھارا_بفر,
                                         خالی * pv_Rx_ڈیٹا,
                                         size_t x_بفر_لمبائی_بائٹیں,
                                         TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_Receive( دھارا_بفر_Handle_t x_دھارا_بفر,
                                         خالی * pv_Rx_ڈیٹا,
                                         size_t x_بفر_لمبائی_بائٹیں,
                                         TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_Receive );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_بھرا( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_بھرا( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_Is_بھرا );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_خالی_خانے( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_خالی_خانے( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_Is_خالی_خانے );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_Spaces_دستیاب );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_بائٹیں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_بائٹیں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_بائٹیں_دستیاب );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_سیٹ_Trigger_Level );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر_ختم /* ( configENABLE_MPU == 1 ) */
