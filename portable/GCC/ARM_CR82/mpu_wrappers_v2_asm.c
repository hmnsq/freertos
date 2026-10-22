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
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"
#ضمن "mpu_syscall_numbers.h"
#ضمن "portmacro.h"

#تعریف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#إذا ( configENABLE_MPU == 1 )

    /*
     * Common single-SVC dispatch: wrappers do only one SVC.
     * The SVC handler decides whether to tail-call the implementation directly
     * (privileged) or set up full system-call state (unprivileged).
     */
    #تعریف_کرو FREERTOS_MPU_SVC_DISPATCH( x_System_Call_نمبر )  \
        __asm متطاير (                                    \
            "svc %0     \n"                                 \
            :                                               \
            : "i" ( x_System_Call_نمبر )                     \
            : "memory"                                      \
        );

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )

        ادھار_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_ویلا,
                                        ثابت TickType_t x_ویلا_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_ویلا,
                                        ثابت TickType_t x_ویلا_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskDelayUntil );
        }

    #جے_انت /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )

        ادھار_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskAbortDelay );
        }

    #جے_انت /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )

        فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskDelay );
        }

    #جے_انت /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_ترجیح_Get == 1 )

        UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_ترجیح_Get );
        }

    #جے_انت /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_eTaskGetState );
        }

    #جے_انت /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               ادھار_Type_t x_Get_Free_ڈھیر_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               ادھار_Type_t x_Get_Free_ڈھیر_Space,
                               eTaskState eState ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskGetInfo );
        }

    #جے_انت /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetIdleTaskHandle );
        }

    #جے_انت /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
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

    #جے_انت /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_گنتی( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_گنتی( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Tick_گنتی );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_نمبر_دا_Tasks( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_نمبر_دا_Tasks( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_نمبر_دا_Tasks );
    }
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_لگاتار_ویلا_STATS == 1 )

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Counter( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Counter( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_لگاتار_ویلا_Counter );
        }

    #جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_لگاتار_ویلا_STATS == 1 )

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Percent( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Percent( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_لگاتار_ویلا_Percent );
        }

    #جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لگاتار_ویلا_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_لگاتار_ویلا_Percent );
        }

/*-----------------------------------------------------------*/

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_لگاتار_ویلا_Counter );
        }

    #جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )

        فراغ MPU_v_Task_سیٹ_Application_Task_ٹیگ( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Task_سیٹ_Application_Task_ٹیگ( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_سیٹ_Application_Task_ٹیگ );
        }

    #جے_انت /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٹیگ( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٹیگ( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Application_Task_ٹیگ );
        }

    #جے_انت /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_سوچکاں != 0 )

        فراغ MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_منزل_سیٹ,
                                                    ادھار_Type_t x_اشاریہ,
                                                    فراغ * pv_قدر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_منزل_سیٹ,
                                                    ادھار_Type_t x_اشاریہ,
                                                    فراغ * pv_قدر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر );
        }

    #جے_انت /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_سوچکاں != 0 )

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_منزل_Query,
                                                       ادھار_Type_t x_اشاریہ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_منزل_Query,
                                                       ادھار_Type_t x_اشاریہ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_اشارہ_گر );
        }

    #جے_انت /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                              ثابت UBaseType_t ux_Array_ناپ,
                                              config_لگاتار_ویلا_COUNTER_TYPE * ثابت pul_کل_لگاتار_ویلا ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                              ثابت UBaseType_t ux_Array_ناپ,
                                              config_لگاتار_ویلا_COUNTER_TYPE * ثابت pul_کل_لگاتار_ویلا ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskGetSystemState );
        }

    #جے_انت /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ڈھیر_بلند_Water_Mark );
        }

    #جے_انت /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark2 == 1 )

        config_ڈھیر_ڈونگھائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ڈھیر_ڈونگھائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ڈھیر_بلند_Water_Mark2 );
        }

    #جے_انت /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetCurrentTaskHandle );
        }

    #جے_انت /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

        ادھار_Type_t MPU_xTaskGetSchedulerState( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetSchedulerState );
        }

    #جے_انت /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_سیٹ_ویلا_باہرلا_State( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    فراغ MPU_v_Task_سیٹ_ویلا_باہرلا_State( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_سیٹ_ویلا_باہرلا_State );
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_Task_Check_For_ویلا_باہرلا( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا,
                                         TickType_t * ثابت px_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ادھار_Type_t MPU_x_Task_Check_For_ویلا_باہرلا( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا,
                                         TickType_t * ثابت px_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Check_For_ویلا_باہرلا );
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        ادھار_Type_t MPU_x_Task_Generic_Notify_اندراج( ثابت xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_x_Task_Generic_Notify_اندراج( ثابت xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotify );
        }

    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        ادھار_Type_t MPU_x_Task_Generic_Notify_Wait_اندراج( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_x_Task_Generic_Notify_Wait_اندراج( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyWait );
        }

    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاریہ_منزل_Wait_On,
                                              ادھار_Type_t x_Clear_گنتی_On_Exit,
                                              TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاریہ_منزل_Wait_On,
                                              ادھار_Type_t x_Clear_گنتی_On_Exit,
                                              TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGenericNotifyTake );
        }

    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        ادھار_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_اشاریہ_منزل_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_اشاریہ_منزل_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyStateClear );
        }

    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_اشاریہ_منزل_Clear,
                                                    uint32_t ul_بٹ_منزل_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_اشاریہ_منزل_Clear,
                                                    uint32_t ul_بٹ_منزل_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Generic_Notify_قدر_Clear );
        }

    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                      ثابت فراغ * ثابت pv_شے_منزل_قطار,
                                      TickType_t x_Ticks_منزل_Wait,
                                      ثابت ادھار_Type_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ادھار_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                      ثابت فراغ * ثابت pv_شے_منزل_قطار,
                                      TickType_t x_Ticks_منزل_Wait,
                                      ثابت ادھار_Type_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Generic_Send );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_اڈیک( ثابت قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_قطار_Messages_اڈیک( ثابت قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_قطار_Messages_اڈیک );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_قطار_Spaces_دستیاب );
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                                  فراغ * ثابت pv_بفر,
                                  TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ادھار_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                                  فراغ * ثابت pv_بفر,
                                  TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Receive );
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                               فراغ * ثابت pv_بفر,
                               TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ادھار_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                               فراغ * ثابت pv_بفر,
                               TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Peek );
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                        TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ادھار_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                        TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Semaphore_Take );
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Get_Mutex_Holder );
        }

    #جے_انت /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        ادھار_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                                 TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                                 TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Take_Mutex_Recursive );
        }

    #جے_انت /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        ادھار_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Give_Mutex_Recursive );
        }

    #جے_انت /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                        ثابت TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                        ثابت TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_Select_From_سیٹ );
        }

    #جے_انت /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        ادھار_Type_t MPU_x_قطار_جوڑو_منزل_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                       قطار_سیٹ_Handle_t x_قطار_سیٹ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_x_قطار_جوڑو_منزل_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                       قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_قطار_جوڑو_منزل_سیٹ );
        }

    #جے_انت /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_قطار_REGISTRY_ناپ > 0 )

        فراغ MPU_v_قطار_جوڑو_منزل_Registry( قطار_Handle_t x_قطار,
                                      ثابت حرف * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_قطار_جوڑو_منزل_Registry( قطار_Handle_t x_قطار,
                                      ثابت حرف * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_قطار_جوڑو_منزل_Registry );
        }

    #جے_انت /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_قطار_REGISTRY_ناپ > 0 )

        فراغ MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_قطار_Unregister_قطار );
        }

    #جے_انت /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_قطار_REGISTRY_ناپ > 0 )

        ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pc_قطار_Get_Name );
        }

    #جے_انت /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTimerGetTimerID );
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_سیٹ_Timer_ID );
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ادھار_Type_t MPU_x_Timer_Is_Timer_سرگرم( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_x_Timer_Is_Timer_سرگرم( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Is_Timer_سرگرم );
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle );
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ادھار_Type_t MPU_x_Timer_Generic_Command_From_Task_اندراج( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_x_Timer_Generic_Command_From_Task_اندراج( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGenericCommandFromTask );
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcTimerGetName );
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                                      ثابت ادھار_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                                      ثابت ادھار_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_سیٹ_Reload_منوال );
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ادھار_Type_t MPU_x_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_x_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Reload_منوال );
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Timer_Get_Reload_منوال );
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetPeriod );
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_ویلا( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_ویلا( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Expiry_ویلا );
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_اندراج( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_اندراج( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروہ_Wait_بٹ );
        }

    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                              ثابت Event_بٹ_t ux_بٹ_منزل_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                              ثابت Event_بٹ_t ux_بٹ_منزل_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروہ_Clear_بٹ );
        }

    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                            ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                            ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروہ_سیٹ_بٹ );
        }

    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Sync( Event_گروہ_Handle_t x_Event_گروہ,
                                         ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ,
                                         ثابت Event_بٹ_t ux_بٹ_منزل_Wait_For,
                                         TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بٹ_t MPU_x_Event_گروہ_Sync( Event_گروہ_Handle_t x_Event_گروہ,
                                         ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ,
                                         ثابت Event_بٹ_t ux_بٹ_منزل_Wait_For,
                                         TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_گروہ_Sync );
        }

    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_گروہ_Get_نمبر( فراغ * x_Event_گروہ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_گروہ_Get_نمبر( فراغ * x_Event_گروہ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Event_گروہ_Get_نمبر );
        }

    #جے_انت /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        فراغ MPU_v_Event_گروہ_سیٹ_نمبر( فراغ * x_Event_گروہ,
                                       UBaseType_t ux_Event_گروہ_نمبر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Event_گروہ_سیٹ_نمبر( فراغ * x_Event_گروہ,
                                       UBaseType_t ux_Event_گروہ_نمبر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Event_گروہ_سیٹ_نمبر );
        }

    #جے_انت /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Send( دھارا_بفر_Handle_t x_دھارا_بفر,
                                      ثابت فراغ * pv_Tx_انکڑے,
                                      size_t x_انکڑے_لمائی_بائٹاں,
                                      TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_Send( دھارا_بفر_Handle_t x_دھارا_بفر,
                                      ثابت فراغ * pv_Tx_انکڑے,
                                      size_t x_انکڑے_لمائی_بائٹاں,
                                      TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_Send );
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Receive( دھارا_بفر_Handle_t x_دھارا_بفر,
                                         فراغ * pv_Rx_انکڑے,
                                         size_t x_بفر_لمائی_بائٹاں,
                                         TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_Receive( دھارا_بفر_Handle_t x_دھارا_بفر,
                                         فراغ * pv_Rx_انکڑے,
                                         size_t x_بفر_لمائی_بائٹاں,
                                         TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_Receive );
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        ادھار_Type_t MPU_x_دھارا_بفر_Is_بھریا( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_x_دھارا_بفر_Is_بھریا( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_Is_بھریا );
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        ادھار_Type_t MPU_x_دھارا_بفر_Is_خالی_تھاواں( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_x_دھارا_بفر_Is_خالی_تھاواں( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_Is_خالی_تھاواں );
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_Spaces_دستیاب );
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_بائٹاں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_بائٹاں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_بائٹاں_دستیاب );
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        ادھار_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ادھار_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_سیٹ_Trigger_Level );
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں );
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#جے_انت /* ( configENABLE_MPU == 1 ) */
