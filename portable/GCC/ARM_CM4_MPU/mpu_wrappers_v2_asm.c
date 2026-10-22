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

#تعریف_منسوخ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#اگر ( configUSE_MPU_WRAPPERS_V1 == 0 )

    #اگر ( INCLUDE_xTaskDelayUntil == 1 )

        بنیاد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_وقت,
                                        ثابت TickType_t x_وقت_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_وقت,
                                        ثابت TickType_t x_وقت_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskDelayUntilImpl                       \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTaskDelayUntil_Unpriv                        \n"
                " MPU_xTaskDelayUntil_Priv:                             \n"
                "     b MPU_xTaskDelayUntilImpl                         \n"
                " MPU_xTaskDelayUntil_Unpriv:                           \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskDelayUntil ) : "memory"
            );
        }

    #اگر_ختم /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskAbortDelay == 1 )

        بنیاد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskAbortDelayImpl                       \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTaskAbortDelay_Unpriv                        \n"
                " MPU_xTaskAbortDelay_Priv:                             \n"
                "     b MPU_xTaskAbortDelayImpl                         \n"
                " MPU_xTaskAbortDelay_Unpriv:                           \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskAbortDelay ) : "memory"
            );
        }

    #اگر_ختم /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskDelay == 1 )

        خالی MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskDelayImpl                            \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_vTaskDelay_Unpriv                             \n"
                " MPU_vTaskDelay_Priv:                                  \n"
                "     b MPU_vTaskDelayImpl                              \n"
                " MPU_vTaskDelay_Unpriv:                                \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskDelay ) : "memory"
            );
        }

    #اگر_ختم /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_ترجیح_Get == 1 )

        UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxTaskPriorityGetImpl                     \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_uxTaskPriorityGet_Unpriv                      \n"
                " MPU_uxTaskPriorityGet_Priv:                           \n"
                "     b MPU_uxTaskPriorityGetImpl                       \n"
                " MPU_uxTaskPriorityGet_Unpriv:                         \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Task_ترجیح_Get ) : "memory"
            );
        }

    #اگر_ختم /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_eTaskGetStateImpl                         \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_eTaskGetState_Unpriv                          \n"
                " MPU_eTaskGetState_Priv:                               \n"
                "     b MPU_eTaskGetStateImpl                           \n"
                " MPU_eTaskGetState_Unpriv:                             \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_eTaskGetState ) : "memory"
            );
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
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskGetInfoImpl                          \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_vTaskGetInfo_Unpriv                           \n"
                " MPU_vTaskGetInfo_Priv:                                \n"
                "     b MPU_vTaskGetInfoImpl                            \n"
                " MPU_vTaskGetInfo_Unpriv:                              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskGetInfo ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGetIdleTaskHandleImpl                \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTaskGetIdleTaskHandle_Unpriv                 \n"
                " MPU_xTaskGetIdleTaskHandle_Priv:                      \n"
                "     b MPU_xTaskGetIdleTaskHandleImpl                  \n"
                " MPU_xTaskGetIdleTaskHandle_Unpriv:                    \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGetIdleTaskHandle ) : "memory"
            );
        }

    #اگر_ختم /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskSuspend == 1 )

        خالی MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskSuspendImpl                          \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_vTaskSuspend_Unpriv                           \n"
                " MPU_vTaskSuspend_Priv:                                \n"
                "     b MPU_vTaskSuspendImpl                            \n"
                " MPU_vTaskSuspend_Unpriv:                              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskSuspend ) : "memory"
            );
        }

    #اگر_ختم /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskSuspend == 1 )

        خالی MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskResumeImpl                           \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_vTaskResume_Unpriv                            \n"
                " MPU_vTaskResume_Priv:                                 \n"
                "     b MPU_vTaskResumeImpl                             \n"
                " MPU_vTaskResume_Unpriv:                               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskResume ) : "memory"
            );
        }

    #اگر_ختم /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_گنتی( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_گنتی( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متلون
        (
            " .syntax unified                                       \n"
            " .extern MPU_xTaskGetTickCountImpl                     \n"
            "                                                       \n"
            " push {r0}                                             \n"
            " mrs r0, control                                       \n"
            " tst r0, #1                                            \n"
            " pop {r0}                                              \n"
            " bne MPU_xTaskGetTickCount_Unpriv                      \n"
            " MPU_xTaskGetTickCount_Priv:                           \n"
            "     b MPU_xTaskGetTickCountImpl                       \n"
            " MPU_xTaskGetTickCount_Unpriv:                         \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_Task_Get_Tick_گنتی ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_نمبر_کا_Tasks( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_نمبر_کا_Tasks( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متلون
        (
            " .syntax unified                                       \n"
            " .extern MPU_uxTaskGetNumberOfTasksImpl                \n"
            "                                                       \n"
            " push {r0}                                             \n"
            " mrs r0, control                                       \n"
            " tst r0, #1                                            \n"
            " pop {r0}                                              \n"
            " bne MPU_uxTaskGetNumberOfTasks_Unpriv                 \n"
            " MPU_uxTaskGetNumberOfTasks_Priv:                      \n"
            "     b MPU_uxTaskGetNumberOfTasksImpl                  \n"
            " MPU_uxTaskGetNumberOfTasks_Unpriv:                    \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_ux_Task_Get_نمبر_کا_Tasks ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #اگر ( config_GENERATE_تسلسل_وقت_STATS == 1 )

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_شمار( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_شمار( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGetRunTimeCounterImpl               \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_ulTaskGetRunTimeCounter_Unpriv                \n"
                " MPU_ulTaskGetRunTimeCounter_Priv:                     \n"
                "     b MPU_ulTaskGetRunTimeCounterImpl                 \n"
                " MPU_ulTaskGetRunTimeCounter_Unpriv:                   \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_تسلسل_وقت_شمار ) : "memory"
            );
        }

    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_GENERATE_تسلسل_وقت_STATS == 1 )

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_Percent( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_Percent( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGetRunTimePercentImpl               \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_ulTaskGetRunTimePercent_Unpriv                \n"
                " MPU_ulTaskGetRunTimePercent_Priv:                     \n"
                "     b MPU_ulTaskGetRunTimePercentImpl                 \n"
                " MPU_ulTaskGetRunTimePercent_Unpriv:                   \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_تسلسل_وقت_Percent ) : "memory"
            );
        }

    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_GENERATE_تسلسل_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGetIdleRunTimePercentImpl           \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_ulTaskGetIdleRunTimePercent_Unpriv            \n"
                " MPU_ulTaskGetIdleRunTimePercent_Priv:                 \n"
                "     b MPU_ulTaskGetIdleRunTimePercentImpl             \n"
                " MPU_ulTaskGetIdleRunTimePercent_Unpriv:               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_تسلسل_وقت_Percent ) : "memory"
            );
        }

    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_GENERATE_تسلسل_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGetIdleRunTimeCounterImpl           \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_ulTaskGetIdleRunTimeCounter_Unpriv            \n"
                " MPU_ulTaskGetIdleRunTimeCounter_Priv:                 \n"
                "     b MPU_ulTaskGetIdleRunTimeCounterImpl             \n"
                " MPU_ulTaskGetIdleRunTimeCounter_Unpriv:               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_تسلسل_وقت_شمار ) : "memory"
            );
        }

    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )

        خالی MPU_v_Task_سیٹ_Application_Task_لیبل( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_Task_سیٹ_Application_Task_لیبل( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskSetApplicationTaskTagImpl            \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_vTaskSetApplicationTaskTag_Unpriv             \n"
                " MPU_vTaskSetApplicationTaskTag_Priv:                  \n"
                "     b MPU_vTaskSetApplicationTaskTagImpl              \n"
                " MPU_vTaskSetApplicationTaskTag_Unpriv:                \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Task_سیٹ_Application_Task_لیبل ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_لیبل( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_لیبل( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGetApplicationTaskTagImpl            \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTaskGetApplicationTaskTag_Unpriv             \n"
                " MPU_xTaskGetApplicationTaskTag_Priv:                  \n"
                "     b MPU_xTaskGetApplicationTaskTagImpl              \n"
                " MPU_xTaskGetApplicationTaskTag_Unpriv:                \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Task_Get_Application_Task_لیبل ) : "memory"
            );
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
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskSetThreadLocalStoragePointerImpl     \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_vTaskSetThreadLocalStoragePointer_Unpriv      \n"
                " MPU_vTaskSetThreadLocalStoragePointer_Priv:           \n"
                "     b MPU_vTaskSetThreadLocalStoragePointerImpl       \n"
                " MPU_vTaskSetThreadLocalStoragePointer_Unpriv:         \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر ) : "memory"
            );
        }

    #اگر_ختم /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_عدد_THREAD_LOCAL_STORAGE_اشارے != 0 )

        خالی * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_Query,
                                                       بنیاد_Type_t x_اشاریہ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_Query,
                                                       بنیاد_Type_t x_اشاریہ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_pvTaskGetThreadLocalStoragePointerImpl    \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_pvTaskGetThreadLocalStoragePointer_Unpriv     \n"
                " MPU_pvTaskGetThreadLocalStoragePointer_Priv:          \n"
                "     b MPU_pvTaskGetThreadLocalStoragePointerImpl      \n"
                " MPU_pvTaskGetThreadLocalStoragePointer_Unpriv:        \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_اشارہ_گر ) : "memory"
            );
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
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxTaskGetSystemStateImpl                  \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_uxTaskGetSystemState_Unpriv                   \n"
                " MPU_uxTaskGetSystemState_Priv:                        \n"
                "     b MPU_uxTaskGetSystemStateImpl                    \n"
                " MPU_uxTaskGetSystemState_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_uxTaskGetSystemState ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxTaskGetStackHighWaterMarkImpl           \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_uxTaskGetStackHighWaterMark_Unpriv            \n"
                " MPU_uxTaskGetStackHighWaterMark_Priv:                 \n"
                "     b MPU_uxTaskGetStackHighWaterMarkImpl             \n"
                " MPU_uxTaskGetStackHighWaterMark_Unpriv:               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Task_Get_ڈھیر_بلند_Water_Mark ) : "memory"
            );
        }

    #اگر_ختم /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark2 == 1 )

        config_ڈھیر_گہرائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ڈھیر_گہرائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxTaskGetStackHighWaterMark2Impl          \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_uxTaskGetStackHighWaterMark2_Unpriv           \n"
                " MPU_uxTaskGetStackHighWaterMark2_Priv:                \n"
                "     b MPU_uxTaskGetStackHighWaterMark2Impl            \n"
                " MPU_uxTaskGetStackHighWaterMark2_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Task_Get_ڈھیر_بلند_Water_Mark2 ) : "memory"
            );
        }

    #اگر_ختم /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGetCurrentTaskHandleImpl             \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTaskGetCurrentTaskHandle_Unpriv              \n"
                " MPU_xTaskGetCurrentTaskHandle_Priv:                   \n"
                "     b MPU_xTaskGetCurrentTaskHandleImpl               \n"
                " MPU_xTaskGetCurrentTaskHandle_Unpriv:                 \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGetCurrentTaskHandle ) : "memory"
            );
        }

    #اگر_ختم /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskGetSchedulerState == 1 )

        بنیاد_Type_t MPU_xTaskGetSchedulerState( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_xTaskGetSchedulerState( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGetSchedulerStateImpl                \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTaskGetSchedulerState_Unpriv                 \n"
                " MPU_xTaskGetSchedulerState_Priv:                      \n"
                "     b MPU_xTaskGetSchedulerStateImpl                  \n"
                " MPU_xTaskGetSchedulerState_Unpriv:                    \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGetSchedulerState ) : "memory"
            );
        }

    #اگر_ختم /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    خالی MPU_v_Task_سیٹ_وقت_برآمد_State( وقت_برآمد_t * ثابت px_وقت_برآمد ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    خالی MPU_v_Task_سیٹ_وقت_برآمد_State( وقت_برآمد_t * ثابت px_وقت_برآمد ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متلون
        (
            " .syntax unified                                       \n"
            " .extern MPU_vTaskSetTimeOutStateImpl                  \n"
            "                                                       \n"
            " push {r0}                                             \n"
            " mrs r0, control                                       \n"
            " tst r0, #1                                            \n"
            " pop {r0}                                              \n"
            " bne MPU_vTaskSetTimeOutState_Unpriv                   \n"
            " MPU_vTaskSetTimeOutState_Priv:                        \n"
            "     b MPU_vTaskSetTimeOutStateImpl                    \n"
            " MPU_vTaskSetTimeOutState_Unpriv:                      \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_v_Task_سیٹ_وقت_برآمد_State ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_Task_Check_For_وقت_برآمد( وقت_برآمد_t * ثابت px_وقت_برآمد,
                                         TickType_t * ثابت px_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنیاد_Type_t MPU_x_Task_Check_For_وقت_برآمد( وقت_برآمد_t * ثابت px_وقت_برآمد,
                                         TickType_t * ثابت px_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متلون
        (
            " .syntax unified                                       \n"
            " .extern MPU_xTaskCheckForTimeOutImpl                  \n"
            "                                                       \n"
            " push {r0}                                             \n"
            " mrs r0, control                                       \n"
            " tst r0, #1                                            \n"
            " pop {r0}                                              \n"
            " bne MPU_xTaskCheckForTimeOut_Unpriv                   \n"
            " MPU_xTaskCheckForTimeOut_Priv:                        \n"
            "     b MPU_xTaskCheckForTimeOutImpl                    \n"
            " MPU_xTaskCheckForTimeOut_Unpriv:                      \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_Task_Check_For_وقت_برآمد ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنیاد_Type_t MPU_x_Task_Generic_Notify_اندراج( ثابت xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_Task_Generic_Notify_اندراج( ثابت xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGenericNotifyImpl                    \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTaskGenericNotify_Unpriv                     \n"
                " MPU_xTaskGenericNotify_Priv:                          \n"
                "     b MPU_xTaskGenericNotifyImpl                      \n"
                " MPU_xTaskGenericNotify_Unpriv:                        \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGenericNotify ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنیاد_Type_t MPU_x_Task_Generic_Notify_Wait_اندراج( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_Task_Generic_Notify_Wait_اندراج( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGenericNotifyWaitImpl                \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTaskGenericNotifyWait_Unpriv                 \n"
                " MPU_xTaskGenericNotifyWait_Priv:                      \n"
                "     b MPU_xTaskGenericNotifyWaitImpl                  \n"
                " MPU_xTaskGenericNotifyWait_Unpriv:                    \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGenericNotifyWait ) : "memory"
            );
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
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGenericNotifyTakeImpl               \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_ulTaskGenericNotifyTake_Unpriv                \n"
                " MPU_ulTaskGenericNotifyTake_Priv:                     \n"
                "     b MPU_ulTaskGenericNotifyTakeImpl                 \n"
                " MPU_ulTaskGenericNotifyTake_Unpriv:                   \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ulTaskGenericNotifyTake ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنیاد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_اشاریہ_مقصد_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_اشاریہ_مقصد_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGenericNotifyStateClearImpl          \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTaskGenericNotifyStateClear_Unpriv           \n"
                " MPU_xTaskGenericNotifyStateClear_Priv:                \n"
                "     b MPU_xTaskGenericNotifyStateClearImpl            \n"
                " MPU_xTaskGenericNotifyStateClear_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGenericNotifyStateClear ) : "memory"
            );
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
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGenericNotifyValueClearImpl         \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_ulTaskGenericNotifyValueClear_Unpriv          \n"
                " MPU_ulTaskGenericNotifyValueClear_Priv:               \n"
                "     b MPU_ulTaskGenericNotifyValueClearImpl           \n"
                " MPU_ulTaskGenericNotifyValueClear_Unpriv:             \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Generic_Notify_قدر_Clear ) : "memory"
            );
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
        __asm متلون
        (
            " .syntax unified                                       \n"
            " .extern MPU_xQueueGenericSendImpl                     \n"
            "                                                       \n"
            " push {r0}                                             \n"
            " mrs r0, control                                       \n"
            " tst r0, #1                                            \n"
            " pop {r0}                                              \n"
            " bne MPU_xQueueGenericSend_Unpriv                      \n"
            " MPU_xQueueGenericSend_Priv:                           \n"
            "     b MPU_xQueueGenericSendImpl                       \n"
            " MPU_xQueueGenericSend_Unpriv:                         \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_قطار_Generic_Send ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_انتظار( ثابت قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_قطار_Messages_انتظار( ثابت قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متلون
        (
            " .syntax unified                                       \n"
            " .extern MPU_uxQueueMessagesWaitingImpl                \n"
            "                                                       \n"
            " push {r0}                                             \n"
            " mrs r0, control                                       \n"
            " tst r0, #1                                            \n"
            " pop {r0}                                              \n"
            " bne MPU_uxQueueMessagesWaiting_Unpriv                 \n"
            " MPU_uxQueueMessagesWaiting_Priv:                      \n"
            "     b MPU_uxQueueMessagesWaitingImpl                  \n"
            " MPU_uxQueueMessagesWaiting_Unpriv:                    \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_ux_قطار_Messages_انتظار ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متلون
        (
            " .syntax unified                                       \n"
            " .extern MPU_uxQueueSpacesAvailableImpl                \n"
            "                                                       \n"
            " push {r0}                                             \n"
            " mrs r0, control                                       \n"
            " tst r0, #1                                            \n"
            " pop {r0}                                              \n"
            " bne MPU_uxQueueSpacesAvailable_Unpriv                 \n"
            " MPU_uxQueueSpacesAvailable_Priv:                      \n"
            "     b MPU_uxQueueSpacesAvailableImpl                  \n"
            " MPU_uxQueueSpacesAvailable_Unpriv:                    \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_ux_قطار_Spaces_دستیاب ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                                  خالی * ثابت pv_بفر,
                                  TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنیاد_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                                  خالی * ثابت pv_بفر,
                                  TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متلون
        (
            " .syntax unified                                       \n"
            " .extern MPU_xQueueReceiveImpl                         \n"
            "                                                       \n"
            " push {r0}                                             \n"
            " mrs r0, control                                       \n"
            " tst r0, #1                                            \n"
            " pop {r0}                                              \n"
            " bne MPU_xQueueReceive_Unpriv                          \n"
            " MPU_xQueueReceive_Priv:                               \n"
            "     b MPU_xQueueReceiveImpl                           \n"
            " MPU_xQueueReceive_Unpriv:                             \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_قطار_Receive ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                               خالی * ثابت pv_بفر,
                               TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنیاد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                               خالی * ثابت pv_بفر,
                               TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متلون
        (
            " .syntax unified                                       \n"
            " .extern MPU_xQueuePeekImpl                            \n"
            "                                                       \n"
            " push {r0}                                             \n"
            " mrs r0, control                                       \n"
            " tst r0, #1                                            \n"
            " pop {r0}                                              \n"
            " bne MPU_xQueuePeek_Unpriv                             \n"
            " MPU_xQueuePeek_Priv:                                  \n"
            "     b MPU_xQueuePeekImpl                              \n"
            " MPU_xQueuePeek_Unpriv:                                \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_قطار_Peek ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                        TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنیاد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                        TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متلون
        (
            " .syntax unified                                       \n"
            " .extern MPU_xQueueSemaphoreTakeImpl                   \n"
            "                                                       \n"
            " push {r0}                                             \n"
            " mrs r0, control                                       \n"
            " tst r0, #1                                            \n"
            " pop {r0}                                              \n"
            " bne MPU_xQueueSemaphoreTake_Unpriv                    \n"
            " MPU_xQueueSemaphoreTake_Priv:                         \n"
            "     b MPU_xQueueSemaphoreTakeImpl                     \n"
            " MPU_xQueueSemaphoreTake_Unpriv:                       \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_قطار_Semaphore_Take ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xQueueGetMutexHolderImpl                  \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xQueueGetMutexHolder_Unpriv                   \n"
                " MPU_xQueueGetMutexHolder_Priv:                        \n"
                "     b MPU_xQueueGetMutexHolderImpl                    \n"
                " MPU_xQueueGetMutexHolder_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_قطار_Get_Mutex_Holder ) : "memory"
            );
        }

    #اگر_ختم /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنیاد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                                 TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                                 TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xQueueTakeMutexRecursiveImpl              \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xQueueTakeMutexRecursive_Unpriv               \n"
                " MPU_xQueueTakeMutexRecursive_Priv:                    \n"
                "     b MPU_xQueueTakeMutexRecursiveImpl                \n"
                " MPU_xQueueTakeMutexRecursive_Unpriv:                  \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_قطار_Take_Mutex_Recursive ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنیاد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xQueueGiveMutexRecursiveImpl              \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xQueueGiveMutexRecursive_Unpriv               \n"
                " MPU_xQueueGiveMutexRecursive_Priv:                    \n"
                "     b MPU_xQueueGiveMutexRecursiveImpl                \n"
                " MPU_xQueueGiveMutexRecursive_Unpriv:                  \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_قطار_Give_Mutex_Recursive ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_قطار_SETS == 1 )

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                        ثابت TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                        ثابت TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xQueueSelectFromSetImpl                   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xQueueSelectFromSet_Unpriv                    \n"
                " MPU_xQueueSelectFromSet_Priv:                         \n"
                "     b MPU_xQueueSelectFromSetImpl                     \n"
                " MPU_xQueueSelectFromSet_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_قطار_Select_From_سیٹ ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_قطار_SETS == 1 )

        بنیاد_Type_t MPU_x_قطار_جوڑو_مقصد_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                       قطار_سیٹ_Handle_t x_قطار_سیٹ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_قطار_جوڑو_مقصد_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                       قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xQueueAddToSetImpl                        \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xQueueAddToSet_Unpriv                         \n"
                " MPU_xQueueAddToSet_Priv:                              \n"
                "     b MPU_xQueueAddToSetImpl                          \n"
                " MPU_xQueueAddToSet_Unpriv:                            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_قطار_جوڑو_مقصد_سیٹ ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_قطار_REGISTRY_سائز > 0 )

        خالی MPU_v_قطار_جوڑو_مقصد_Registry( قطار_Handle_t x_قطار,
                                      ثابت حرف * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_قطار_جوڑو_مقصد_Registry( قطار_Handle_t x_قطار,
                                      ثابت حرف * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_vQueueAddToRegistryImpl                   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_vQueueAddToRegistry_Unpriv                    \n"
                " MPU_vQueueAddToRegistry_Priv:                         \n"
                "     b MPU_vQueueAddToRegistryImpl                     \n"
                " MPU_vQueueAddToRegistry_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_قطار_جوڑو_مقصد_Registry ) : "memory"
            );
        }

    #اگر_ختم /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_قطار_REGISTRY_سائز > 0 )

        خالی MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_vQueueUnregisterQueueImpl                 \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_vQueueUnregisterQueue_Unpriv                  \n"
                " MPU_vQueueUnregisterQueue_Priv:                       \n"
                "     b MPU_vQueueUnregisterQueueImpl                   \n"
                " MPU_vQueueUnregisterQueue_Unpriv:                     \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_قطار_Unregister_قطار ) : "memory"
            );
        }

    #اگر_ختم /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_قطار_REGISTRY_سائز > 0 )

        ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_pcQueueGetNameImpl                        \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_pcQueueGetName_Unpriv                         \n"
                " MPU_pcQueueGetName_Priv:                              \n"
                "     b MPU_pcQueueGetNameImpl                          \n"
                " MPU_pcQueueGetName_Unpriv:                            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pc_قطار_Get_Name ) : "memory"
            );
        }

    #اگر_ختم /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        خالی * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_pvTimerGetTimerIDImpl                     \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_pvTimerGetTimerID_Unpriv                      \n"
                " MPU_pvTimerGetTimerID_Priv:                           \n"
                "     b MPU_pvTimerGetTimerIDImpl                       \n"
                " MPU_pvTimerGetTimerID_Unpriv:                         \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pvTimerGetTimerID ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        خالی MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                                   خالی * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                                   خالی * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTimerSetTimerIDImpl                      \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_vTimerSetTimerID_Unpriv                       \n"
                " MPU_vTimerSetTimerID_Priv:                            \n"
                "     b MPU_vTimerSetTimerIDImpl                        \n"
                " MPU_vTimerSetTimerID_Unpriv:                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Timer_سیٹ_Timer_ID ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerIsTimerActiveImpl                   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTimerIsTimerActive_Unpriv                    \n"
                " MPU_xTimerIsTimerActive_Priv:                         \n"
                "     b MPU_xTimerIsTimerActiveImpl                     \n"
                " MPU_xTimerIsTimerActive_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Timer_Is_Timer_فعال ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( خالی ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( خالی ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerGetTimerDaemonTaskHandleImpl        \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv         \n"
                " MPU_xTimerGetTimerDaemonTaskHandle_Priv:              \n"
                "     b MPU_xTimerGetTimerDaemonTaskHandleImpl          \n"
                " MPU_xTimerGetTimerDaemonTaskHandle_Unpriv:            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_x_Timer_Generic_Command_From_Task_اندراج( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_Timer_Generic_Command_From_Task_اندراج( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerGenericCommandFromTaskImpl          \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTimerGenericCommandFromTask_Unpriv           \n"
                " MPU_xTimerGenericCommandFromTask_Priv:                \n"
                "     b MPU_xTimerGenericCommandFromTaskImpl            \n"
                " MPU_xTimerGenericCommandFromTask_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTimerGenericCommandFromTask ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_pcTimerGetNameImpl                        \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_pcTimerGetName_Unpriv                         \n"
                " MPU_pcTimerGetName_Priv:                              \n"
                "     b MPU_pcTimerGetNameImpl                          \n"
                " MPU_pcTimerGetName_Unpriv:                            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pcTimerGetName ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        خالی MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                                      ثابت بنیاد_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                                      ثابت بنیاد_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTimerSetReloadModeImpl                   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_vTimerSetReloadMode_Unpriv                    \n"
                " MPU_vTimerSetReloadMode_Priv:                         \n"
                "     b MPU_vTimerSetReloadModeImpl                     \n"
                " MPU_vTimerSetReloadMode_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Timer_سیٹ_Reload_منوال ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_x_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerGetReloadModeImpl                   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTimerGetReloadMode_Unpriv                    \n"
                " MPU_xTimerGetReloadMode_Priv:                         \n"
                "     b MPU_xTimerGetReloadModeImpl                     \n"
                " MPU_xTimerGetReloadMode_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Timer_Get_Reload_منوال ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxTimerGetReloadModeImpl                  \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_uxTimerGetReloadMode_Unpriv                   \n"
                " MPU_uxTimerGetReloadMode_Priv:                        \n"
                "     b MPU_uxTimerGetReloadModeImpl                    \n"
                " MPU_uxTimerGetReloadMode_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Timer_Get_Reload_منوال ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerGetPeriodImpl                       \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTimerGetPeriod_Unpriv                        \n"
                " MPU_xTimerGetPeriod_Priv:                             \n"
                "     b MPU_xTimerGetPeriodImpl                         \n"
                " MPU_xTimerGetPeriod_Unpriv:                           \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTimerGetPeriod ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerGetExpiryTimeImpl                   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xTimerGetExpiryTime_Unpriv                    \n"
                " MPU_xTimerGetExpiryTime_Priv:                         \n"
                "     b MPU_xTimerGetExpiryTimeImpl                     \n"
                " MPU_xTimerGetExpiryTime_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Timer_Get_Expiry_وقت ) : "memory"
            );
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_اندراج( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_اندراج( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupWaitBitsImpl                   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xEventGroupWaitBits_Unpriv                    \n"
                " MPU_xEventGroupWaitBits_Priv:                         \n"
                "     pop {r0}                                          \n"
                "     b MPU_xEventGroupWaitBitsImpl                     \n"
                " MPU_xEventGroupWaitBits_Unpriv:                       \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_گروہ_Wait_بٹ ) : "memory"
            );
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                              ثابت Event_بٹ_t ux_بٹ_مقصد_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                              ثابت Event_بٹ_t ux_بٹ_مقصد_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupClearBitsImpl                  \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xEventGroupClearBits_Unpriv                   \n"
                " MPU_xEventGroupClearBits_Priv:                        \n"
                "     pop {r0}                                          \n"
                "     b MPU_xEventGroupClearBitsImpl                    \n"
                " MPU_xEventGroupClearBits_Unpriv:                      \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_گروہ_Clear_بٹ ) : "memory"
            );
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                            ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                            ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupSetBitsImpl                    \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xEventGroupSetBits_Unpriv                     \n"
                " MPU_xEventGroupSetBits_Priv:                          \n"
                "     pop {r0}                                          \n"
                "     b MPU_xEventGroupSetBitsImpl                      \n"
                " MPU_xEventGroupSetBits_Unpriv:                        \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_گروہ_سیٹ_بٹ ) : "memory"
            );
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
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupSyncImpl                       \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xEventGroupSync_Unpriv                        \n"
                " MPU_xEventGroupSync_Priv:                             \n"
                "     pop {r0}                                          \n"
                "     b MPU_xEventGroupSyncImpl                         \n"
                " MPU_xEventGroupSync_Unpriv:                           \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_گروہ_Sync ) : "memory"
            );
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_گروہ_Get_نمبر( خالی * x_Event_گروہ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_گروہ_Get_نمبر( خالی * x_Event_گروہ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxEventGroupGetNumberImpl                 \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_uxEventGroupGetNumber_Unpriv                  \n"
                " MPU_uxEventGroupGetNumber_Priv:                       \n"
                "     b MPU_uxEventGroupGetNumberImpl                   \n"
                " MPU_uxEventGroupGetNumber_Unpriv:                     \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Event_گروہ_Get_نمبر ) : "memory"
            );
        }

    #اگر_ختم /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        خالی MPU_v_Event_گروہ_سیٹ_نمبر( خالی * x_Event_گروہ,
                                       UBaseType_t ux_Event_گروہ_نمبر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        خالی MPU_v_Event_گروہ_سیٹ_نمبر( خالی * x_Event_گروہ,
                                       UBaseType_t ux_Event_گروہ_نمبر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_vEventGroupSetNumberImpl                  \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_vEventGroupSetNumber_Unpriv                   \n"
                " MPU_vEventGroupSetNumber_Priv:                        \n"
                "     b MPU_vEventGroupSetNumberImpl                    \n"
                " MPU_vEventGroupSetNumber_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Event_گروہ_سیٹ_نمبر ) : "memory"
            );
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
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferSendImpl                     \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xStreamBufferSend_Unpriv                      \n"
                " MPU_xStreamBufferSend_Priv:                           \n"
                "     pop {r0}                                          \n"
                "     b MPU_xStreamBufferSendImpl                       \n"
                " MPU_xStreamBufferSend_Unpriv:                         \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_دھارا_بفر_Send ) : "memory"
            );
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
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferReceiveImpl                  \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xStreamBufferReceive_Unpriv                   \n"
                " MPU_xStreamBufferReceive_Priv:                        \n"
                "     pop {r0}                                          \n"
                "     b MPU_xStreamBufferReceiveImpl                    \n"
                " MPU_xStreamBufferReceive_Unpriv:                      \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_دھارا_بفر_Receive ) : "memory"
            );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_بھرا( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_بھرا( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferIsFullImpl                   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xStreamBufferIsFull_Unpriv                    \n"
                " MPU_xStreamBufferIsFull_Priv:                         \n"
                "     pop {r0}                                          \n"
                "     b MPU_xStreamBufferIsFullImpl                     \n"
                " MPU_xStreamBufferIsFull_Unpriv:                       \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_دھارا_بفر_Is_بھرا ) : "memory"
            );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_خالی_خانے( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_خالی_خانے( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferIsEmptyImpl                  \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xStreamBufferIsEmpty_Unpriv                   \n"
                " MPU_xStreamBufferIsEmpty_Priv:                        \n"
                "     pop {r0}                                          \n"
                "     b MPU_xStreamBufferIsEmptyImpl                    \n"
                " MPU_xStreamBufferIsEmpty_Unpriv:                      \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_دھارا_بفر_Is_خالی_خانے ) : "memory"
            );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferSpacesAvailableImpl          \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xStreamBufferSpacesAvailable_Unpriv           \n"
                " MPU_xStreamBufferSpacesAvailable_Priv:                \n"
                "     pop {r0}                                          \n"
                "     b MPU_xStreamBufferSpacesAvailableImpl            \n"
                " MPU_xStreamBufferSpacesAvailable_Unpriv:              \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_دھارا_بفر_Spaces_دستیاب ) : "memory"
            );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_بائٹیں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_بائٹیں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferBytesAvailableImpl           \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xStreamBufferBytesAvailable_Unpriv            \n"
                " MPU_xStreamBufferBytesAvailable_Priv:                 \n"
                "     pop {r0}                                          \n"
                "     b MPU_xStreamBufferBytesAvailableImpl             \n"
                " MPU_xStreamBufferBytesAvailable_Unpriv:               \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_دھارا_بفر_بائٹیں_دستیاب ) : "memory"
            );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنیاد_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferSetTriggerLevelImpl          \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xStreamBufferSetTriggerLevel_Unpriv           \n"
                " MPU_xStreamBufferSetTriggerLevel_Priv:                \n"
                "     pop {r0}                                          \n"
                "     b MPU_xStreamBufferSetTriggerLevelImpl            \n"
                " MPU_xStreamBufferSetTriggerLevel_Unpriv:              \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_دھارا_بفر_سیٹ_Trigger_Level ) : "memory"
            );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں( دھارا_بفر_Handle_t x_دھارا_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں( دھارا_بفر_Handle_t x_دھارا_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متلون
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferNextMessageLengthBytesImpl   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " bne MPU_xStreamBufferNextMessageLengthBytes_Unpriv    \n"
                " MPU_xStreamBufferNextMessageLengthBytes_Priv:         \n"
                "     pop {r0}                                          \n"
                "     b MPU_xStreamBufferNextMessageLengthBytesImpl     \n"
                " MPU_xStreamBufferNextMessageLengthBytes_Unpriv:       \n"
                "     pop {r0}                                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں ) : "memory"
            );
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#اگر_ختم /* configUSE_MPU_WRAPPERS_V1 == 0 */
