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
#ضمن "portmacro.h"

#لغو_تعریف MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#إذا ( configENABLE_MPU == 1 )

    /*
     * Common single-SVC dispatch: wrappers do only one SVC.
     * The SVC handler decides whether to tail-call the implementation directly
     * (privileged) or set up full system-call state (unprivileged).
     */
    #تعریف_کن FREERTOS_MPU_SVC_DISPATCH( x_System_Call_عدد )  \
        __asm متطاير (                                    \
            "svc %0     \n"                                 \
            :                                               \
            : "i" ( x_System_Call_عدد )                     \
            : "memory"                                      \
        );

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )

        پایه_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_قبلی_Wake_زمان,
                                        ثابت TickType_t x_زمان_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_قبلی_Wake_زمان,
                                        ثابت TickType_t x_زمان_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskDelayUntil );
        }

    #پایان_اگر /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )

        پایه_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskAbortDelay );
        }

    #پایان_اگر /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )

        فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskDelay );
        }

    #پایان_اگر /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_اولویت_Get == 1 )

        UBaseType_t MPU_ux_Task_اولویت_Get( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_اولویت_Get( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_اولویت_Get );
        }

    #پایان_اگر /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_eTaskGetState );
        }

    #پایان_اگر /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_وضعیت_t * px_Task_وضعیت,
                               پایه_Type_t x_Get_Free_پشته_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_وضعیت_t * px_Task_وضعیت,
                               پایه_Type_t x_Get_Free_پشته_Space,
                               eTaskState eState ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskGetInfo );
        }

    #پایان_اگر /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetIdleTaskHandle );
        }

    #پایان_اگر /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSuspend );
        }

/*-----------------------------------------------------------*/

        فراغ MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskResume );
        }

    #پایان_اگر /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_شمار( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_شمار( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Tick_شمار );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_عدد_از_Tasks( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_عدد_از_Tasks( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_عدد_از_Tasks );
    }
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_پیاپی_زمان_STATS == 1 )

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Counter( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Counter( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_پیاپی_زمان_Counter );
        }

    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_پیاپی_زمان_STATS == 1 )

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Percent( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Percent( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_پیاپی_زمان_Percent );
        }

    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پیاپی_زمان_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_پیاپی_زمان_Percent );
        }

/*-----------------------------------------------------------*/

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_پیاپی_زمان_Counter );
        }

    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )

        فراغ MPU_v_Task_مجموعه_Application_Task_برچسب( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Task_مجموعه_Application_Task_برچسب( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_مجموعه_Application_Task_برچسب );
        }

    #پایان_اگر /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_برچسب( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_برچسب( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Application_Task_برچسب );
        }

    #پایان_اگر /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها != 0 )

        فراغ MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_مجموعه,
                                                    پایه_Type_t x_شاخص,
                                                    فراغ * pv_مقدار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_مجموعه,
                                                    پایه_Type_t x_شاخص,
                                                    فراغ * pv_مقدار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر );
        }

    #پایان_اگر /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها != 0 )

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_Query,
                                                       پایه_Type_t x_شاخص ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_Query,
                                                       پایه_Type_t x_شاخص ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_اشاره_گر );
        }

    #پایان_اگر /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( Task_وضعیت_t * ثابت px_Task_وضعیت_Array,
                                              ثابت UBaseType_t ux_Array_اندازه,
                                              config_پیاپی_زمان_COUNTER_TYPE * ثابت pul_مجموع_پیاپی_زمان ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( Task_وضعیت_t * ثابت px_Task_وضعیت_Array,
                                              ثابت UBaseType_t ux_Array_اندازه,
                                              config_پیاپی_زمان_COUNTER_TYPE * ثابت pul_مجموع_پیاپی_زمان ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskGetSystemState );
        }

    #پایان_اگر /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_پشته_بالا_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_پشته_بالا_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_پشته_بالا_Water_Mark );
        }

    #پایان_اگر /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark2 == 1 )

        config_پشته_عمق_TYPE MPU_ux_Task_Get_پشته_بالا_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پشته_عمق_TYPE MPU_ux_Task_Get_پشته_بالا_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_پشته_بالا_Water_Mark2 );
        }

    #پایان_اگر /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetCurrentTaskHandle );
        }

    #پایان_اگر /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

        پایه_Type_t MPU_xTaskGetSchedulerState( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetSchedulerState );
        }

    #پایان_اگر /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_مجموعه_زمان_بیرون_State( زمان_بیرون_t * ثابت px_زمان_بیرون ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    فراغ MPU_v_Task_مجموعه_زمان_بیرون_State( زمان_بیرون_t * ثابت px_زمان_بیرون ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_مجموعه_زمان_بیرون_State );
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_Task_Check_For_زمان_بیرون( زمان_بیرون_t * ثابت px_زمان_بیرون,
                                         TickType_t * ثابت px_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    پایه_Type_t MPU_x_Task_Check_For_زمان_بیرون( زمان_بیرون_t * ثابت px_زمان_بیرون,
                                         TickType_t * ثابت px_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Check_For_زمان_بیرون );
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        پایه_Type_t MPU_x_Task_Generic_Notify_مدخل( ثابت xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_Task_Generic_Notify_مدخل( ثابت xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotify );
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        پایه_Type_t MPU_x_Task_Generic_Notify_Wait_مدخل( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_Task_Generic_Notify_Wait_مدخل( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyWait );
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_شاخص_مقصد_Wait_On,
                                              پایه_Type_t x_Clear_شمار_On_Exit,
                                              TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_شاخص_مقصد_Wait_On,
                                              پایه_Type_t x_Clear_شمار_On_Exit,
                                              TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGenericNotifyTake );
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        پایه_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_شاخص_مقصد_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_شاخص_مقصد_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyStateClear );
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_مقدار_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_شاخص_مقصد_Clear,
                                                    uint32_t ul_بیتها_مقصد_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_مقدار_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_شاخص_مقصد_Clear,
                                                    uint32_t ul_بیتها_مقصد_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Generic_Notify_مقدار_Clear );
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Generic_Send( صف_Handle_t x_صف,
                                      ثابت فراغ * ثابت pv_قلم_مقصد_صف,
                                      TickType_t x_Ticks_مقصد_Wait,
                                      ثابت پایه_Type_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    پایه_Type_t MPU_x_صف_Generic_Send( صف_Handle_t x_صف,
                                      ثابت فراغ * ثابت pv_قلم_مقصد_صف,
                                      TickType_t x_Ticks_مقصد_Wait,
                                      ثابت پایه_Type_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_صف_Generic_Send );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_صف_Messages_انتظار( ثابت صف_Handle_t x_صف ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_صف_Messages_انتظار( ثابت صف_Handle_t x_صف ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_صف_Messages_انتظار );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_صف_Spaces_موجود( ثابت صف_Handle_t x_صف ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_صف_Spaces_موجود( ثابت صف_Handle_t x_صف ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_صف_Spaces_موجود );
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Receive( صف_Handle_t x_صف,
                                  فراغ * ثابت pv_میانگیر,
                                  TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    پایه_Type_t MPU_x_صف_Receive( صف_Handle_t x_صف,
                                  فراغ * ثابت pv_میانگیر,
                                  TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_صف_Receive );
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Peek( صف_Handle_t x_صف,
                               فراغ * ثابت pv_میانگیر,
                               TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    پایه_Type_t MPU_x_صف_Peek( صف_Handle_t x_صف,
                               فراغ * ثابت pv_میانگیر,
                               TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_صف_Peek );
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Semaphore_Take( صف_Handle_t x_صف,
                                        TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    پایه_Type_t MPU_x_صف_Semaphore_Take( صف_Handle_t x_صف,
                                        TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_صف_Semaphore_Take );
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_صف_Get_Mutex_Holder( صف_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_صف_Get_Mutex_Holder( صف_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_صف_Get_Mutex_Holder );
        }

    #پایان_اگر /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        پایه_Type_t MPU_x_صف_Take_Mutex_Recursive( صف_Handle_t xMutex,
                                                 TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_صف_Take_Mutex_Recursive( صف_Handle_t xMutex,
                                                 TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_صف_Take_Mutex_Recursive );
        }

    #پایان_اگر /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        پایه_Type_t MPU_x_صف_Give_Mutex_Recursive( صف_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_صف_Give_Mutex_Recursive( صف_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_صف_Give_Mutex_Recursive );
        }

    #پایان_اگر /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_صف_SETS == 1 )

        صف_مجموعه_Member_Handle_t MPU_x_صف_Select_From_مجموعه( صف_مجموعه_Handle_t x_صف_مجموعه,
                                                        ثابت TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        صف_مجموعه_Member_Handle_t MPU_x_صف_Select_From_مجموعه( صف_مجموعه_Handle_t x_صف_مجموعه,
                                                        ثابت TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_صف_Select_From_مجموعه );
        }

    #پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_صف_SETS == 1 )

        پایه_Type_t MPU_x_صف_جمع_کن_مقصد_مجموعه( صف_مجموعه_Member_Handle_t x_صف_Or_Semaphore,
                                       صف_مجموعه_Handle_t x_صف_مجموعه ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_صف_جمع_کن_مقصد_مجموعه( صف_مجموعه_Member_Handle_t x_صف_Or_Semaphore,
                                       صف_مجموعه_Handle_t x_صف_مجموعه ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_صف_جمع_کن_مقصد_مجموعه );
        }

    #پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_صف_REGISTRY_اندازه > 0 )

        فراغ MPU_v_صف_جمع_کن_مقصد_Registry( صف_Handle_t x_صف,
                                      ثابت حرف * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_صف_جمع_کن_مقصد_Registry( صف_Handle_t x_صف,
                                      ثابت حرف * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_صف_جمع_کن_مقصد_Registry );
        }

    #پایان_اگر /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_صف_REGISTRY_اندازه > 0 )

        فراغ MPU_v_صف_Unregister_صف( صف_Handle_t x_صف ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_صف_Unregister_صف( صف_Handle_t x_صف ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_صف_Unregister_صف );
        }

    #پایان_اگر /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_صف_REGISTRY_اندازه > 0 )

        ثابت حرف * MPU_pc_صف_Get_Name( صف_Handle_t x_صف ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pc_صف_Get_Name( صف_Handle_t x_صف ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pc_صف_Get_Name );
        }

    #پایان_اگر /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTimerGetTimerID );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_مجموعه_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Timer_مجموعه_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_مجموعه_Timer_ID );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Is_Timer_فعال );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_x_Timer_Generic_Command_From_Task_مدخل( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_Timer_Generic_Command_From_Task_مدخل( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGenericCommandFromTask );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcTimerGetName );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_مجموعه_Reload_نما( TimerHandle_t xTimer,
                                      ثابت پایه_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Timer_مجموعه_Reload_نما( TimerHandle_t xTimer,
                                      ثابت پایه_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_مجموعه_Reload_نما );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_x_Timer_Get_Reload_نما( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_Timer_Get_Reload_نما( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Reload_نما );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_نما( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_نما( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Timer_Get_Reload_نما );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetPeriod );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_زمان( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_زمان( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Expiry_زمان );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_Wait_بیتها_مدخل( ثابت x_Event_گروه_Wait_بیتها_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بیتها_t MPU_x_Event_گروه_Wait_بیتها_مدخل( ثابت x_Event_گروه_Wait_بیتها_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروه_Wait_بیتها );
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_Clear_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                              ثابت Event_بیتها_t ux_بیتها_مقصد_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بیتها_t MPU_x_Event_گروه_Clear_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                              ثابت Event_بیتها_t ux_بیتها_مقصد_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروه_Clear_بیتها );
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_مجموعه_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                            ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بیتها_t MPU_x_Event_گروه_مجموعه_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                            ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروه_مجموعه_بیتها );
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_Sync( Event_گروه_Handle_t x_Event_گروه,
                                         ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه,
                                         ثابت Event_بیتها_t ux_بیتها_مقصد_Wait_For,
                                         TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بیتها_t MPU_x_Event_گروه_Sync( Event_گروه_Handle_t x_Event_گروه,
                                         ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه,
                                         ثابت Event_بیتها_t ux_بیتها_مقصد_Wait_For,
                                         TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروه_Sync );
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_گروه_Get_عدد( فراغ * x_Event_گروه ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_گروه_Get_عدد( فراغ * x_Event_گروه ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Event_گروه_Get_عدد );
        }

    #پایان_اگر /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        فراغ MPU_v_Event_گروه_مجموعه_عدد( فراغ * x_Event_گروه,
                                       UBaseType_t ux_Event_گروه_عدد ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Event_گروه_مجموعه_عدد( فراغ * x_Event_گروه,
                                       UBaseType_t ux_Event_گروه_عدد ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Event_گروه_مجموعه_عدد );
        }

    #پایان_اگر /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_Send( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                      ثابت فراغ * pv_Tx_داده,
                                      size_t x_داده_درازی_بایتها,
                                      TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_جریان_میانگیر_Send( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                      ثابت فراغ * pv_Tx_داده,
                                      size_t x_داده_درازی_بایتها,
                                      TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_جریان_میانگیر_Send );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_Receive( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                         فراغ * pv_Rx_داده,
                                         size_t x_میانگیر_درازی_بایتها,
                                         TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_جریان_میانگیر_Receive( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                         فراغ * pv_Rx_داده,
                                         size_t x_میانگیر_درازی_بایتها,
                                         TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_جریان_میانگیر_Receive );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_Is_پر( جریان_میانگیر_Handle_t x_جریان_میانگیر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_جریان_میانگیر_Is_پر( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_جریان_میانگیر_Is_پر );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_Is_خالی( جریان_میانگیر_Handle_t x_جریان_میانگیر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_جریان_میانگیر_Is_خالی( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_جریان_میانگیر_Is_خالی );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_Spaces_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_جریان_میانگیر_Spaces_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_جریان_میانگیر_Spaces_موجود );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_بایتها_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_جریان_میانگیر_بایتها_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_جریان_میانگیر_بایتها_موجود );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_مجموعه_Trigger_Level( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_جریان_میانگیر_مجموعه_Trigger_Level( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_جریان_میانگیر_مجموعه_Trigger_Level );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها( جریان_میانگیر_Handle_t x_جریان_میانگیر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#پایان_اگر /* ( configENABLE_MPU == 1 ) */
