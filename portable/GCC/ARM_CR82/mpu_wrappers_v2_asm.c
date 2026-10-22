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
#ಅನ್ತರ್ಭಾವ "portmacro.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ಆದರೆ ( configENABLE_MPU == 1 )

    /*
     * Common single-SVC dispatch: wrappers do only one SVC.
     * The SVC handler decides whether to tail-call the implementation directly
     * (privileged) or set up full system-call state (unprivileged).
     */
    #ವ್ಯಾಖ್ಯಾನಿಸು FREERTOS_MPU_SVC_DISPATCH( x_System_Call_ಸಂಖ್ಯೆ )  \
        __asm ಅಸ್ಥಿರ (                                    \
            "svc %0     \n"                                 \
            :                                               \
            : "i" ( x_System_Call_ಸಂಖ್ಯೆ )                     \
            : "memory"                                      \
        );

    #ಆದರೆ ( INCLUDE_xTaskDelayUntil == 1 )

        ತಳ_Type_t MPU_xTaskDelayUntil( TickType_t * ಸ್ಥಿರಾಂಕ px_ಹಿಂದಿನ_Wake_ಸಮಯ,
                                        ಸ್ಥಿರಾಂಕ TickType_t x_ಸಮಯ_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_xTaskDelayUntil( TickType_t * ಸ್ಥಿರಾಂಕ px_ಹಿಂದಿನ_Wake_ಸಮಯ,
                                        ಸ್ಥಿರಾಂಕ TickType_t x_ಸಮಯ_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskDelayUntil );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskAbortDelay == 1 )

        ತಳ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskAbortDelay );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_vTaskDelay == 1 )

        ಶೂನ್ಯ MPU_vTaskDelay( ಸ್ಥಿರಾಂಕ TickType_t x_Ticks_ಗಮ್ಯ_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTaskDelay( ಸ್ಥಿರಾಂಕ TickType_t x_Ticks_ಗಮ್ಯ_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskDelay );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_ux_Task_ಆದ್ಯತೆ_Get == 1 )

        UBaseType_t MPU_ux_Task_ಆದ್ಯತೆ_Get( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_ಆದ್ಯತೆ_Get( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_ಆದ್ಯತೆ_Get );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_eTaskGetState );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TRACE_FACILITY == 1 )

        ಶೂನ್ಯ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_ಸ್ಥಿತಿ_t * px_Task_ಸ್ಥಿತಿ,
                               ತಳ_Type_t x_Get_Free_ರಾಶಿ_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_ಸ್ಥಿತಿ_t * px_Task_ಸ್ಥಿತಿ,
                               ತಳ_Type_t x_Get_Free_ರಾಶಿ_Space,
                               eTaskState eState ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskGetInfo );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetIdleTaskHandle );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_vTaskSuspend == 1 )

        ಶೂನ್ಯ MPU_vTaskSuspend( TaskHandle_t x_Task_ಗಮ್ಯ_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTaskSuspend( TaskHandle_t x_Task_ಗಮ್ಯ_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskSuspend );
        }

/*-----------------------------------------------------------*/

        ಶೂನ್ಯ MPU_vTaskResume( TaskHandle_t x_Task_ಗಮ್ಯ_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_vTaskResume( TaskHandle_t x_Task_ಗಮ್ಯ_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_vTaskResume );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Tick_ಎಣಿಕೆ );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks );
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 )

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_ಸತತ_ಸಮಯ_Counter );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 )

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_ಸತತ_ಸಮಯ_Percent );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent );
        }

/*-----------------------------------------------------------*/

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )

        ಶೂನ್ಯ MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Get_Application_Task_ಟ್ಯಾಗ್ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_ಸೂಚಕಗಳು != 0 )

        ಶೂನ್ಯ MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ( TaskHandle_t x_Task_ಗಮ್ಯ_ಗಣ,
                                                    ತಳ_Type_t x_ಸೂಚ್ಯಂಕ,
                                                    ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ( TaskHandle_t x_Task_ಗಮ್ಯ_ಗಣ,
                                                    ತಳ_Type_t x_ಸೂಚ್ಯಂಕ,
                                                    ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_ಸೂಚಕಗಳು != 0 )

        ಶೂನ್ಯ * MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ( TaskHandle_t x_Task_ಗಮ್ಯ_Query,
                                                       ತಳ_Type_t x_ಸೂಚ್ಯಂಕ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ * MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ( TaskHandle_t x_Task_ಗಮ್ಯ_Query,
                                                       ತಳ_Type_t x_ಸೂಚ್ಯಂಕ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( Task_ಸ್ಥಿತಿ_t * ಸ್ಥಿರಾಂಕ px_Task_ಸ್ಥಿತಿ_Array,
                                              ಸ್ಥಿರಾಂಕ UBaseType_t ux_Array_ಗಾತ್ರ,
                                              config_ಸತತ_ಸಮಯ_COUNTER_TYPE * ಸ್ಥಿರಾಂಕ pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( Task_ಸ್ಥಿತಿ_t * ಸ್ಥಿರಾಂಕ px_Task_ಸ್ಥಿತಿ_Array,
                                              ಸ್ಥಿರಾಂಕ UBaseType_t ux_Array_ಗಾತ್ರ,
                                              config_ಸತತ_ಸಮಯ_COUNTER_TYPE * ಸ್ಥಿರಾಂಕ pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_uxTaskGetSystemState );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2 == 1 )

        config_ರಾಶಿ_ಆಳ_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ರಾಶಿ_ಆಳ_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2 );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetCurrentTaskHandle );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskGetSchedulerState == 1 )

        ತಳ_Type_t MPU_xTaskGetSchedulerState( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_xTaskGetSchedulerState( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGetSchedulerState );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ಶೂನ್ಯ MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State );
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು,
                                         TickType_t * ಸ್ಥಿರಾಂಕ px_Ticks_ಗಮ್ಯ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ತಳ_Type_t MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು,
                                         TickType_t * ಸ್ಥಿರಾಂಕ px_Ticks_ಗಮ್ಯ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು );
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ತಳ_Type_t MPU_x_Task_Generic_Notify_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_x_Task_Generic_Notify_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotify );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ತಳ_Type_t MPU_x_Task_Generic_Notify_Wait_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_x_Task_Generic_Notify_Wait_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyWait );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On,
                                              ತಳ_Type_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                              TickType_t x_Ticks_ಗಮ್ಯ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On,
                                              ತಳ_Type_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                              TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ulTaskGenericNotifyTake );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ತಳ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTaskGenericNotifyStateClear );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear,
                                                    uint32_t ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear,
                                                    uint32_t ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Generic_Send( ಸರತಿ_Handle_t x_ಸರತಿ,
                                      ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ,
                                      TickType_t x_Ticks_ಗಮ್ಯ_Wait,
                                      ಸ್ಥಿರಾಂಕ ತಳ_Type_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ತಳ_Type_t MPU_x_ಸರತಿ_Generic_Send( ಸರತಿ_Handle_t x_ಸರತಿ,
                                      ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ,
                                      TickType_t x_Ticks_ಗಮ್ಯ_Wait,
                                      ಸ್ಥಿರಾಂಕ ತಳ_Type_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಸರತಿ_Generic_Send );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_ಸರತಿ_Spaces_ಲಭ್ಯ );
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Receive( ಸರತಿ_Handle_t x_ಸರತಿ,
                                  ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                                  TickType_t x_Ticks_ಗಮ್ಯ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ತಳ_Type_t MPU_x_ಸರತಿ_Receive( ಸರತಿ_Handle_t x_ಸರತಿ,
                                  ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                                  TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಸರತಿ_Receive );
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Peek( ಸರತಿ_Handle_t x_ಸರತಿ,
                               ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                               TickType_t x_Ticks_ಗಮ್ಯ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ತಳ_Type_t MPU_x_ಸರತಿ_Peek( ಸರತಿ_Handle_t x_ಸರತಿ,
                               ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                               TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಸರತಿ_Peek );
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Semaphore_Take( ಸರತಿ_Handle_t x_ಸರತಿ,
                                        TickType_t x_Ticks_ಗಮ್ಯ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ತಳ_Type_t MPU_x_ಸರತಿ_Semaphore_Take( ಸರತಿ_Handle_t x_ಸರತಿ,
                                        TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಸರತಿ_Semaphore_Take );
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_ಸರತಿ_Get_Mutex_Holder( ಸರತಿ_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_ಸರತಿ_Get_Mutex_Holder( ಸರತಿ_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಸರತಿ_Get_Mutex_Holder );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_RECURSIVE_MUTEXES == 1 )

        ತಳ_Type_t MPU_x_ಸರತಿ_Take_Mutex_Recursive( ಸರತಿ_Handle_t xMutex,
                                                 TickType_t x_Ticks_ಗಮ್ಯ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_x_ಸರತಿ_Take_Mutex_Recursive( ಸರತಿ_Handle_t xMutex,
                                                 TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಸರತಿ_Take_Mutex_Recursive );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_RECURSIVE_MUTEXES == 1 )

        ತಳ_Type_t MPU_x_ಸರತಿ_Give_Mutex_Recursive( ಸರತಿ_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_x_ಸರತಿ_Give_Mutex_Recursive( ಸರತಿ_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಸರತಿ_Give_Mutex_Recursive );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )

        ಸರತಿ_ಗಣ_Member_Handle_t MPU_x_ಸರತಿ_Select_From_ಗಣ( ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ,
                                                        ಸ್ಥಿರಾಂಕ TickType_t x_Ticks_ಗಮ್ಯ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಸರತಿ_ಗಣ_Member_Handle_t MPU_x_ಸರತಿ_Select_From_ಗಣ( ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ,
                                                        ಸ್ಥಿರಾಂಕ TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಸರತಿ_Select_From_ಗಣ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )

        ತಳ_Type_t MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ( ಸರತಿ_ಗಣ_Member_Handle_t x_ಸರತಿ_Or_Semaphore,
                                       ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ( ಸರತಿ_ಗಣ_Member_Handle_t x_ಸರತಿ_Or_Semaphore,
                                       ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0 )

        ಶೂನ್ಯ MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry( ಸರತಿ_Handle_t x_ಸರತಿ,
                                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry( ಸರತಿ_Handle_t x_ಸರತಿ,
                                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0 )

        ಶೂನ್ಯ MPU_v_ಸರತಿ_Unregister_ಸರತಿ( ಸರತಿ_Handle_t x_ಸರತಿ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_v_ಸರತಿ_Unregister_ಸರತಿ( ಸರತಿ_Handle_t x_ಸರತಿ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_ಸರತಿ_Unregister_ಸರತಿ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0 )

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pc_ಸರತಿ_Get_Name( ಸರತಿ_Handle_t x_ಸರತಿ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pc_ಸರತಿ_Get_Name( ಸರತಿ_Handle_t x_ಸರತಿ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pc_ಸರತಿ_Get_Name );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ * MPU_pvTimerGetTimerID( ಸ್ಥಿರಾಂಕ TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ * MPU_pvTimerGetTimerID( ಸ್ಥಿರಾಂಕ TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pvTimerGetTimerID );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Timer_ID( TimerHandle_t xTimer,
                                   ಶೂನ್ಯ * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Timer_ID( TimerHandle_t xTimer,
                                   ಶೂನ್ಯ * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_ಗಣ_Timer_ID );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ತಳ_Type_t MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Is_Timer_ಸಕ್ರಿಯ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ಶೂನ್ಯ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ಶೂನ್ಯ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ತಳ_Type_t MPU_x_Timer_Generic_Command_From_Task_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_x_Timer_Generic_Command_From_Task_ನಮೂದು( ಸ್ಥಿರಾಂಕ xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGenericCommandFromTask );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_pcTimerGetName );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ( TimerHandle_t xTimer,
                                      ಸ್ಥಿರಾಂಕ ತಳ_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ( TimerHandle_t xTimer,
                                      ಸ್ಥಿರಾಂಕ ತಳ_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Timer_ಗಣ_Reload_ಬಹುಲಕ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ತಳ_Type_t MPU_x_Timer_Get_Reload_ಬಹುಲಕ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_x_Timer_Get_Reload_ಬಹುಲಕ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Reload_ಬಹುಲಕ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_ಬಹುಲಕ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_ಬಹುಲಕ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Timer_Get_Reload_ಬಹುಲಕ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_xTimerGetPeriod );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_ಸಮಯ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_ಸಮಯ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Timer_Get_Expiry_ಸಮಯ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_ನಮೂದು( ಸ್ಥಿರಾಂಕ x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_ನಮೂದು( ಸ್ಥಿರಾಂಕ x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                              ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                              ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                            ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                            ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Sync( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                         ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ,
                                         ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For,
                                         TickType_t x_Ticks_ಗಮ್ಯ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Sync( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                         ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ,
                                         ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For,
                                         TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_Event_ಗುಂಪು_Sync );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * x_Event_ಗುಂಪು ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * x_Event_ಗುಂಪು ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        ಶೂನ್ಯ MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * x_Event_ಗುಂಪು,
                                       UBaseType_t ux_Event_ಗುಂಪು_ಸಂಖ್ಯೆ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ಶೂನ್ಯ MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ( ಶೂನ್ಯ * x_Event_ಗುಂಪು,
                                       UBaseType_t ux_Event_ಗುಂಪು_ಸಂಖ್ಯೆ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Send( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                      ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_Tx_ದತ್ತಾಂಶ,
                                      size_t x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                      TickType_t x_Ticks_ಗಮ್ಯ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Send( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                      ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_Tx_ದತ್ತಾಂಶ,
                                      size_t x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                      TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಹರಿವು_ಬಫರ್_Send );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Receive( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                         ಶೂನ್ಯ * pv_Rx_ದತ್ತಾಂಶ,
                                         size_t x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                         TickType_t x_Ticks_ಗಮ್ಯ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Receive( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                         ಶೂನ್ಯ * pv_Rx_ದತ್ತಾಂಶ,
                                         size_t x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                         TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಹರಿವು_ಬಫರ್_Receive );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        size_t MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        size_t MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            FREERTOS_MPU_SVC_DISPATCH( SYSTEM_CALL_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* ( configENABLE_MPU == 1 ) */
