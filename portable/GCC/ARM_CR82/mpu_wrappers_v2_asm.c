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
#تعریف_کړه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

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

#تعریف_لغوه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#إذا ( configENABLE_MPU == 1 )

    /*
     * Common single-SVC dispatch: wrappers do only one SVC.
     * The SVC handler decides whether to tail-call the implementation directly
     * (privileged) or set up full system-call state (unprivileged).
     */
    #تعریف_کړه FREERTOS_MPU_SVC_DISPATCH( x_System_Call_شمېره )  \
        __asm متطاير (                                    \
            "svc %0     \n"                                 \
            :                                               \
            : "i" ( x_System_Call_شمېره )                     \
            : "memory"                                      \
        );

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )

        بنسټ_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پخوانی_Wake_وخت,
                                        ثابت TickType_t x_وخت_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پخوانی_Wake_وخت,
                                        ثابت TickType_t x_وخت_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskDelayUntil );
        }

    #د_که_پای /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )

        بنسټ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskAbortDelay );
        }

    #د_که_پای /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )

        فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskDelay );
        }

    #د_که_پای /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_لومړیتوب_Get == 1 )

        UBaseType_t MPU_ux_Task_لومړیتوب_Get( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_لومړیتوب_Get( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_لومړیتوب_Get );
        }

    #د_که_پای /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_eTaskGetState );
        }

    #د_که_پای /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               بنسټ_Type_t x_Get_Free_ډېری_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               بنسټ_Type_t x_Get_Free_ډېری_Space,
                               eTaskState eState ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskGetInfo );
        }

    #د_که_پای /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetIdleTaskHandle );
        }

    #د_که_پای /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_منزل_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_منزل_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSuspend );
        }

/*-----------------------------------------------------------*/

        فراغ MPU_vTaskResume( TaskHandle_t x_Task_منزل_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskResume( TaskHandle_t x_Task_منزل_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskResume );
        }

    #د_که_پای /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_شمېر( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_شمېر( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Tick_شمېر );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_شمېره_د_Tasks( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_شمېره_د_Tasks( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_شمېره_د_Tasks );
    }
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_پرلپسې_وخت_STATS == 1 )

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Counter( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Counter( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_پرلپسې_وخت_Counter );
        }

    #د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_پرلپسې_وخت_STATS == 1 )

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Percent( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Percent( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_پرلپسې_وخت_Percent );
        }

    #د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پرلپسې_وخت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_پرلپسې_وخت_Percent );
        }

/*-----------------------------------------------------------*/

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_پرلپسې_وخت_Counter );
        }

    #د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_نښان == 1 )

        فراغ MPU_v_Task_سېټ_Application_Task_نښان( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Task_سېټ_Application_Task_نښان( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_سېټ_Application_Task_نښان );
        }

    #د_که_پای /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_نښان == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_نښان( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_نښان( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Application_Task_نښان );
        }

    #د_که_پای /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_اشارې != 0 )

        فراغ MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر( TaskHandle_t x_Task_منزل_سېټ,
                                                    بنسټ_Type_t x_شاخص,
                                                    فراغ * pv_ارزښت ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر( TaskHandle_t x_Task_منزل_سېټ,
                                                    بنسټ_Type_t x_شاخص,
                                                    فراغ * pv_ارزښت ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر );
        }

    #د_که_پای /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_اشارې != 0 )

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر( TaskHandle_t x_Task_منزل_Query,
                                                       بنسټ_Type_t x_شاخص ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر( TaskHandle_t x_Task_منزل_Query,
                                                       بنسټ_Type_t x_شاخص ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_اشاره_ګر );
        }

    #د_که_پای /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                              ثابت UBaseType_t ux_Array_اندازه,
                                              config_پرلپسې_وخت_COUNTER_TYPE * ثابت pul_ټول_پرلپسې_وخت ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                              ثابت UBaseType_t ux_Array_اندازه,
                                              config_پرلپسې_وخت_COUNTER_TYPE * ثابت pul_ټول_پرلپسې_وخت ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskGetSystemState );
        }

    #د_که_پای /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ډېری_لوړ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ډېری_لوړ_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_ډېری_لوړ_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ډېری_لوړ_Water_Mark );
        }

    #د_که_پای /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ډېری_لوړ_Water_Mark2 == 1 )

        config_ډېری_ژوروالی_TYPE MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ډېری_ژوروالی_TYPE MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ډېری_لوړ_Water_Mark2 );
        }

    #د_که_پای /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetCurrentTaskHandle );
        }

    #د_که_پای /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

        بنسټ_Type_t MPU_xTaskGetSchedulerState( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetSchedulerState );
        }

    #د_که_پای /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_سېټ_وخت_بهر_State( وخت_بهر_t * ثابت px_وخت_بهر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    فراغ MPU_v_Task_سېټ_وخت_بهر_State( وخت_بهر_t * ثابت px_وخت_بهر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_سېټ_وخت_بهر_State );
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_Task_Check_For_وخت_بهر( وخت_بهر_t * ثابت px_وخت_بهر,
                                         TickType_t * ثابت px_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنسټ_Type_t MPU_x_Task_Check_For_وخت_بهر( وخت_بهر_t * ثابت px_وخت_بهر,
                                         TickType_t * ثابت px_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Check_For_وخت_بهر );
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنسټ_Type_t MPU_x_Task_Generic_Notify_ثبت( ثابت xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_x_Task_Generic_Notify_ثبت( ثابت xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotify );
        }

    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنسټ_Type_t MPU_x_Task_Generic_Notify_Wait_ثبت( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_x_Task_Generic_Notify_Wait_ثبت( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyWait );
        }

    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_شاخص_منزل_Wait_On,
                                              بنسټ_Type_t x_Clear_شمېر_On_Exit,
                                              TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_شاخص_منزل_Wait_On,
                                              بنسټ_Type_t x_Clear_شمېر_On_Exit,
                                              TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGenericNotifyTake );
        }

    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنسټ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_شاخص_منزل_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_شاخص_منزل_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyStateClear );
        }

    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_ارزښت_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_شاخص_منزل_Clear,
                                                    uint32_t ul_بټونه_منزل_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_ارزښت_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_شاخص_منزل_Clear,
                                                    uint32_t ul_بټونه_منزل_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Generic_Notify_ارزښت_Clear );
        }

    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Generic_Send( کتار_Handle_t x_کتار,
                                      ثابت فراغ * ثابت pv_توکی_منزل_کتار,
                                      TickType_t x_Ticks_منزل_Wait,
                                      ثابت بنسټ_Type_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنسټ_Type_t MPU_x_کتار_Generic_Send( کتار_Handle_t x_کتار,
                                      ثابت فراغ * ثابت pv_توکی_منزل_کتار,
                                      TickType_t x_Ticks_منزل_Wait,
                                      ثابت بنسټ_Type_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_کتار_Generic_Send );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_کتار_Messages_انتظار( ثابت کتار_Handle_t x_کتار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_کتار_Messages_انتظار( ثابت کتار_Handle_t x_کتار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_کتار_Messages_انتظار );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_کتار_Spaces_شته( ثابت کتار_Handle_t x_کتار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_کتار_Spaces_شته( ثابت کتار_Handle_t x_کتار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_کتار_Spaces_شته );
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Receive( کتار_Handle_t x_کتار,
                                  فراغ * ثابت pv_بفر,
                                  TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنسټ_Type_t MPU_x_کتار_Receive( کتار_Handle_t x_کتار,
                                  فراغ * ثابت pv_بفر,
                                  TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_کتار_Receive );
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Peek( کتار_Handle_t x_کتار,
                               فراغ * ثابت pv_بفر,
                               TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنسټ_Type_t MPU_x_کتار_Peek( کتار_Handle_t x_کتار,
                               فراغ * ثابت pv_بفر,
                               TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_کتار_Peek );
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Semaphore_Take( کتار_Handle_t x_کتار,
                                        TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنسټ_Type_t MPU_x_کتار_Semaphore_Take( کتار_Handle_t x_کتار,
                                        TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_کتار_Semaphore_Take );
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_کتار_Get_Mutex_Holder( کتار_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_کتار_Get_Mutex_Holder( کتار_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_کتار_Get_Mutex_Holder );
        }

    #د_که_پای /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنسټ_Type_t MPU_x_کتار_Take_Mutex_Recursive( کتار_Handle_t xMutex,
                                                 TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_x_کتار_Take_Mutex_Recursive( کتار_Handle_t xMutex,
                                                 TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_کتار_Take_Mutex_Recursive );
        }

    #د_که_پای /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنسټ_Type_t MPU_x_کتار_Give_Mutex_Recursive( کتار_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_x_کتار_Give_Mutex_Recursive( کتار_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_کتار_Give_Mutex_Recursive );
        }

    #د_که_پای /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_کتار_SETS == 1 )

        کتار_سېټ_Member_Handle_t MPU_x_کتار_Select_From_سېټ( کتار_سېټ_Handle_t x_کتار_سېټ,
                                                        ثابت TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        کتار_سېټ_Member_Handle_t MPU_x_کتار_Select_From_سېټ( کتار_سېټ_Handle_t x_کتار_سېټ,
                                                        ثابت TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_کتار_Select_From_سېټ );
        }

    #د_که_پای /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_کتار_SETS == 1 )

        بنسټ_Type_t MPU_x_کتار_جمع_کړه_منزل_سېټ( کتار_سېټ_Member_Handle_t x_کتار_Or_Semaphore,
                                       کتار_سېټ_Handle_t x_کتار_سېټ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_x_کتار_جمع_کړه_منزل_سېټ( کتار_سېټ_Member_Handle_t x_کتار_Or_Semaphore,
                                       کتار_سېټ_Handle_t x_کتار_سېټ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_کتار_جمع_کړه_منزل_سېټ );
        }

    #د_که_پای /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_کتار_REGISTRY_اندازه > 0 )

        فراغ MPU_v_کتار_جمع_کړه_منزل_Registry( کتار_Handle_t x_کتار,
                                      ثابت حرف * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_کتار_جمع_کړه_منزل_Registry( کتار_Handle_t x_کتار,
                                      ثابت حرف * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_کتار_جمع_کړه_منزل_Registry );
        }

    #د_که_پای /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_کتار_REGISTRY_اندازه > 0 )

        فراغ MPU_v_کتار_Unregister_کتار( کتار_Handle_t x_کتار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_کتار_Unregister_کتار( کتار_Handle_t x_کتار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_کتار_Unregister_کتار );
        }

    #د_که_پای /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_کتار_REGISTRY_اندازه > 0 )

        ثابت حرف * MPU_pc_کتار_Get_Name( کتار_Handle_t x_کتار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pc_کتار_Get_Name( کتار_Handle_t x_کتار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pc_کتار_Get_Name );
        }

    #د_که_پای /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTimerGetTimerID );
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سېټ_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Timer_سېټ_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_سېټ_Timer_ID );
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنسټ_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Is_Timer_فعال );
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle );
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنسټ_Type_t MPU_x_Timer_Generic_Command_From_Task_ثبت( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_x_Timer_Generic_Command_From_Task_ثبت( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGenericCommandFromTask );
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcTimerGetName );
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سېټ_Reload_ډېرپېښ( TimerHandle_t xTimer,
                                      ثابت بنسټ_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Timer_سېټ_Reload_ډېرپېښ( TimerHandle_t xTimer,
                                      ثابت بنسټ_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_سېټ_Reload_ډېرپېښ );
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنسټ_Type_t MPU_x_Timer_Get_Reload_ډېرپېښ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_x_Timer_Get_Reload_ډېرپېښ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Reload_ډېرپېښ );
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_ډېرپېښ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_ډېرپېښ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Timer_Get_Reload_ډېرپېښ );
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetPeriod );
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_وخت( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_وخت( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Expiry_وخت );
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بټونه_t MPU_x_Event_ډله_Wait_بټونه_ثبت( ثابت x_Event_ډله_Wait_بټونه_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بټونه_t MPU_x_Event_ډله_Wait_بټونه_ثبت( ثابت x_Event_ډله_Wait_بټونه_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ډله_Wait_بټونه );
        }

    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بټونه_t MPU_x_Event_ډله_Clear_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                              ثابت Event_بټونه_t ux_بټونه_منزل_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بټونه_t MPU_x_Event_ډله_Clear_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                              ثابت Event_بټونه_t ux_بټونه_منزل_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ډله_Clear_بټونه );
        }

    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بټونه_t MPU_x_Event_ډله_سېټ_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                            ثابت Event_بټونه_t ux_بټونه_منزل_سېټ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بټونه_t MPU_x_Event_ډله_سېټ_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                            ثابت Event_بټونه_t ux_بټونه_منزل_سېټ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ډله_سېټ_بټونه );
        }

    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بټونه_t MPU_x_Event_ډله_Sync( Event_ډله_Handle_t x_Event_ډله,
                                         ثابت Event_بټونه_t ux_بټونه_منزل_سېټ,
                                         ثابت Event_بټونه_t ux_بټونه_منزل_Wait_For,
                                         TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بټونه_t MPU_x_Event_ډله_Sync( Event_ډله_Handle_t x_Event_ډله,
                                         ثابت Event_بټونه_t ux_بټونه_منزل_سېټ,
                                         ثابت Event_بټونه_t ux_بټونه_منزل_Wait_For,
                                         TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ډله_Sync );
        }

    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_ډله_Get_شمېره( فراغ * x_Event_ډله ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_ډله_Get_شمېره( فراغ * x_Event_ډله ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Event_ډله_Get_شمېره );
        }

    #د_که_پای /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        فراغ MPU_v_Event_ډله_سېټ_شمېره( فراغ * x_Event_ډله,
                                       UBaseType_t ux_Event_ډله_شمېره ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Event_ډله_سېټ_شمېره( فراغ * x_Event_ډله,
                                       UBaseType_t ux_Event_ډله_شمېره ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Event_ډله_سېټ_شمېره );
        }

    #د_که_پای /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        size_t MPU_x_بهیر_بفر_Send( بهیر_بفر_Handle_t x_بهیر_بفر,
                                      ثابت فراغ * pv_Tx_معلومات,
                                      size_t x_معلومات_اوږدتیا_بایټونه,
                                      TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_بهیر_بفر_Send( بهیر_بفر_Handle_t x_بهیر_بفر,
                                      ثابت فراغ * pv_Tx_معلومات,
                                      size_t x_معلومات_اوږدتیا_بایټونه,
                                      TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_بهیر_بفر_Send );
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        size_t MPU_x_بهیر_بفر_Receive( بهیر_بفر_Handle_t x_بهیر_بفر,
                                         فراغ * pv_Rx_معلومات,
                                         size_t x_بفر_اوږدتیا_بایټونه,
                                         TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_بهیر_بفر_Receive( بهیر_بفر_Handle_t x_بهیر_بفر,
                                         فراغ * pv_Rx_معلومات,
                                         size_t x_بفر_اوږدتیا_بایټونه,
                                         TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_بهیر_بفر_Receive );
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        بنسټ_Type_t MPU_x_بهیر_بفر_Is_ډک( بهیر_بفر_Handle_t x_بهیر_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_x_بهیر_بفر_Is_ډک( بهیر_بفر_Handle_t x_بهیر_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_بهیر_بفر_Is_ډک );
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        بنسټ_Type_t MPU_x_بهیر_بفر_Is_تشه( بهیر_بفر_Handle_t x_بهیر_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_x_بهیر_بفر_Is_تشه( بهیر_بفر_Handle_t x_بهیر_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_بهیر_بفر_Is_تشه );
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        size_t MPU_x_بهیر_بفر_Spaces_شته( بهیر_بفر_Handle_t x_بهیر_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_بهیر_بفر_Spaces_شته( بهیر_بفر_Handle_t x_بهیر_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_بهیر_بفر_Spaces_شته );
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        size_t MPU_x_بهیر_بفر_بایټونه_شته( بهیر_بفر_Handle_t x_بهیر_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_بهیر_بفر_بایټونه_شته( بهیر_بفر_Handle_t x_بهیر_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_بهیر_بفر_بایټونه_شته );
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        بنسټ_Type_t MPU_x_بهیر_بفر_سېټ_Trigger_Level( بهیر_بفر_Handle_t x_بهیر_بفر,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنسټ_Type_t MPU_x_بهیر_بفر_سېټ_Trigger_Level( بهیر_بفر_Handle_t x_بهیر_بفر,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_بهیر_بفر_سېټ_Trigger_Level );
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        size_t MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه( بهیر_بفر_Handle_t x_بهیر_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه( بهیر_بفر_Handle_t x_بهیر_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه );
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#د_که_پای /* ( configENABLE_MPU == 1 ) */
