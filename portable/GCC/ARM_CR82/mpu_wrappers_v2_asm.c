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
#ਅਨ੍ਤਰ੍ਭਾਵ "portmacro.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ਜੇ ( configENABLE_MPU == 1 )

    /*
     * Common single-SVC dispatch: wrappers do only one SVC.
     * The SVC handler decides whether to tail-call the implementation directly
     * (privileged) or set up full system-call state (unprivileged).
     */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FREERTOS_MPU_SVC_DISPATCH( x_System_Call_ਸੰਖਿਆ )  \
        __asm ਅਸਥਿਰ (                                    \
            "svc %0     \n"                                 \
            :                                               \
            : "i" ( x_System_Call_ਸੰਖਿਆ )                     \
            : "memory"                                      \
        );

    #ਜੇ ( INCLUDE_xTaskDelayUntil == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskDelayUntil( TickType_t * ਅਚਲ px_ਪਿਛਲਾ_Wake_ਸਮਾਂ,
                                        ਅਚਲ TickType_t x_ਸਮਾਂ_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_xTaskDelayUntil( TickType_t * ਅਚਲ px_ਪਿਛਲਾ_Wake_ਸਮਾਂ,
                                        ਅਚਲ TickType_t x_ਸਮਾਂ_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskDelayUntil );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskAbortDelay == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskAbortDelay );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskDelay == 1 )

        ਖਾਲੀ MPU_vTaskDelay( ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_vTaskDelay( ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskDelay );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_ਤਰਜੀਹ_Get == 1 )

        UBaseType_t MPU_ux_Task_ਤਰਜੀਹ_Get( ਅਚਲ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_ਤਰਜੀਹ_Get( ਅਚਲ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_ਤਰਜੀਹ_Get );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_eTaskGetState );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TRACE_FACILITY == 1 )

        ਖਾਲੀ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_ਸਥਿਤੀ_t * px_Task_ਸਥਿਤੀ,
                               ਅਧਾਰ_Type_t x_Get_Free_ਢੇਰ_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_ਸਥਿਤੀ_t * px_Task_ਸਥਿਤੀ,
                               ਅਧਾਰ_Type_t x_Get_Free_ਢੇਰ_Space,
                               eTaskState eState ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskGetInfo );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetIdleTaskHandle );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskSuspend == 1 )

        ਖਾਲੀ MPU_vTaskSuspend( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_vTaskSuspend( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSuspend );
        }

/*-----------------------------------------------------------*/

        ਖਾਲੀ MPU_vTaskResume( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_vTaskResume( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskResume );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ਗਿਣਤੀ( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_ਗਿਣਤੀ( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Tick_ਗਿਣਤੀ );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks );
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਅਚਲ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਅਚਲ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter );
        }

    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਅਚਲ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਅਚਲ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent );
        }

    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent );
        }

/*-----------------------------------------------------------*/

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter );
        }

    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )

        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ਟੈਗ( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ਟੈਗ( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Application_Task_ਟੈਗ );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ != 0 )

        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                                    ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ,
                                                    ਖਾਲੀ * pv_ਮੁੱਲ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                                    ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ,
                                                    ਖਾਲੀ * pv_ਮੁੱਲ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ );
        }

    #ਜੇ_ਅੰਤ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ != 0 )

        ਖਾਲੀ * MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Query,
                                                       ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ * MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Query,
                                                       ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ );
        }

    #ਜੇ_ਅੰਤ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( Task_ਸਥਿਤੀ_t * ਅਚਲ px_Task_ਸਥਿਤੀ_Array,
                                              ਅਚਲ UBaseType_t ux_Array_ਮਾਪ,
                                              config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE * ਅਚਲ pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( Task_ਸਥਿਤੀ_t * ਅਚਲ px_Task_ਸਥਿਤੀ_Array,
                                              ਅਚਲ UBaseType_t ux_Array_ਮਾਪ,
                                              config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE * ਅਚਲ pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskGetSystemState );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2 == 1 )

        config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2 );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetCurrentTaskHandle );
        }

    #ਜੇ_ਅੰਤ /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskGetSchedulerState == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskGetSchedulerState( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_xTaskGetSchedulerState( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetSchedulerState );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State );
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ,
                                         TickType_t * ਅਚਲ px_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ਅਧਾਰ_Type_t MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ,
                                         TickType_t * ਅਚਲ px_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ );
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotify );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_Wait_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_Wait_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyWait );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On,
                                              ਅਧਾਰ_Type_t x_Clear_ਗਿਣਤੀ_On_Exit,
                                              TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On,
                                              ਅਧਾਰ_Type_t x_Clear_ਗਿਣਤੀ_On_Exit,
                                              TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGenericNotifyTake );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyStateClear );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear,
                                                    uint32_t ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear,
                                                    uint32_t ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Generic_Notify_ਮੁੱਲ_Clear );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Generic_Send( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                      ਅਚਲ ਖਾਲੀ * ਅਚਲ pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ,
                                      TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait,
                                      ਅਚਲ ਅਧਾਰ_Type_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Generic_Send( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                      ਅਚਲ ਖਾਲੀ * ਅਚਲ pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ,
                                      TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait,
                                      ਅਚਲ ਅਧਾਰ_Type_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਕਤਾਰ_Generic_Send );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_ਕਤਾਰ_Messages_ਉਡੀਕ );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ );
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Receive( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                  ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                  TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Receive( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                  ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                  TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਕਤਾਰ_Receive );
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Peek( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                               ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                               TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Peek( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                               ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                               TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਕਤਾਰ_Peek );
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Semaphore_Take( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                        TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Semaphore_Take( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                        TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਕਤਾਰ_Semaphore_Take );
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_ਕਤਾਰ_Get_Mutex_Holder( ਕਤਾਰ_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_ਕਤਾਰ_Get_Mutex_Holder( ਕਤਾਰ_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਕਤਾਰ_Get_Mutex_Holder );
        }

    #ਜੇ_ਅੰਤ /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_RECURSIVE_MUTEXES == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Take_Mutex_Recursive( ਕਤਾਰ_Handle_t xMutex,
                                                 TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Take_Mutex_Recursive( ਕਤਾਰ_Handle_t xMutex,
                                                 TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਕਤਾਰ_Take_Mutex_Recursive );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_RECURSIVE_MUTEXES == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Give_Mutex_Recursive( ਕਤਾਰ_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Give_Mutex_Recursive( ਕਤਾਰ_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਕਤਾਰ_Give_Mutex_Recursive );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )

        ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ,
                                                        ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ,
                                                        ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਕਤਾਰ_Select_From_ਸੈੱਟ );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਕਤਾਰ_Or_Semaphore,
                                       ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਕਤਾਰ_Or_Semaphore,
                                       ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0 )

        ਖਾਲੀ MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                      ਅਚਲ ਅੱਖਰ * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                      ਅਚਲ ਅੱਖਰ * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry );
        }

    #ਜੇ_ਅੰਤ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0 )

        ਖਾਲੀ MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_ਕਤਾਰ_Unregister_ਕਤਾਰ );
        }

    #ਜੇ_ਅੰਤ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0 )

        ਅਚਲ ਅੱਖਰ * MPU_pc_ਕਤਾਰ_Get_Name( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਚਲ ਅੱਖਰ * MPU_pc_ਕਤਾਰ_Get_Name( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pc_ਕਤਾਰ_Get_Name );
        }

    #ਜੇ_ਅੰਤ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਖਾਲੀ * MPU_pvTimerGetTimerID( ਅਚਲ TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ * MPU_pvTimerGetTimerID( ਅਚਲ TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTimerGetTimerID );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Timer_ID( TimerHandle_t xTimer,
                                   ਖਾਲੀ * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Timer_ID( TimerHandle_t xTimer,
                                   ਖਾਲੀ * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_ਸੈੱਟ_Timer_ID );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Timer_Is_Timer_ਸਰਗਰਮ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_Timer_Is_Timer_ਸਰਗਰਮ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Is_Timer_ਸਰਗਰਮ );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Timer_Generic_Command_From_Task_ਇੰਦਰਾਜ( ਅਚਲ xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_Timer_Generic_Command_From_Task_ਇੰਦਰਾਜ( ਅਚਲ xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGenericCommandFromTask );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਚਲ ਅੱਖਰ * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਚਲ ਅੱਖਰ * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcTimerGetName );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer,
                                      ਅਚਲ ਅਧਾਰ_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer,
                                      ਅਚਲ ਅਧਾਰ_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Reload_ਬਹੁਲਕ );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Timer_Get_Reload_ਬਹੁਲਕ );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetPeriod );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_ਸਮਾਂ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_ਸਮਾਂ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Expiry_ਸਮਾਂ );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_ਇੰਦਰਾਜ( ਅਚਲ x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_ਇੰਦਰਾਜ( ਅਚਲ x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                              ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                              ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                            ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                            ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Sync( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                         ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                         ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For,
                                         TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Sync( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                         ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                         ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For,
                                         TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ਸਮੂਹ_Sync );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ );
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        ਖਾਲੀ MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ,
                                       UBaseType_t ux_Event_ਸਮੂਹ_ਸੰਖਿਆ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ,
                                       UBaseType_t ux_Event_ਸਮੂਹ_ਸੰਖਿਆ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ );
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Send( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                      ਅਚਲ ਖਾਲੀ * pv_Tx_ਅੰਕੜੇ,
                                      size_t x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                      TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Send( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                      ਅਚਲ ਖਾਲੀ * pv_Tx_ਅੰਕੜੇ,
                                      size_t x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                      TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_Send );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Receive( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                         ਖਾਲੀ * pv_Rx_ਅੰਕੜੇ,
                                         size_t x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                         TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Receive( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                         ਖਾਲੀ * pv_Rx_ਅੰਕੜੇ,
                                         size_t x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                         TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_Receive );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) */
