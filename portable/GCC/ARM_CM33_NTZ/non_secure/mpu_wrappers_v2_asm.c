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

#ఒకవేళ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ఒకవేళ ( INCLUDE_xTaskDelayUntil == 1 )

        పునాది_Type_t MPU_xTaskDelayUntil( TickType_t * స్థిరరాశి px_మునుపటి_Wake_సమయం,
                                        స్థిరరాశి TickType_t x_సమయం_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_xTaskDelayUntil( TickType_t * స్థిరరాశి px_మునుపటి_Wake_సమయం,
                                        స్థిరరాశి TickType_t x_సమయం_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskAbortDelay == 1 )

        పునాది_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskDelay == 1 )

        శూన్య MPU_vTaskDelay( స్థిరరాశి TickType_t x_Ticks_గమ్యం_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_vTaskDelay( స్థిరరాశి TickType_t x_Ticks_గమ్యం_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_ప్రాధాన్యత_Get == 1 )

        UBaseType_t MPU_ux_Task_ప్రాధాన్యత_Get( స్థిరరాశి TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_ప్రాధాన్యత_Get( స్థిరరాశి TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_ux_Task_ప్రాధాన్యత_Get ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskSuspend == 1 )

        శూన్య MPU_vTaskSuspend( TaskHandle_t x_Task_గమ్యం_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_vTaskSuspend( TaskHandle_t x_Task_గమ్యం_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskSuspend == 1 )

        శూన్య MPU_vTaskResume( TaskHandle_t x_Task_గమ్యం_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_vTaskResume( TaskHandle_t x_Task_గమ్యం_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_లెక్క( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_లెక్క( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm అస్థిర
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
            : : "i" ( SYSTEM_CALL_x_Task_Get_Tick_లెక్క ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm అస్థిర
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
            : : "i" ( SYSTEM_CALL_ux_Task_Get_సంఖ్య_యొక్క_Tasks ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 )

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Counter( స్థిరరాశి TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Counter( స్థిరరాశి TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_నిరంతరం_సమయం_Counter ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 )

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Percent( స్థిరరాశి TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Percent( స్థిరరాశి TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_నిరంతరం_సమయం_Percent ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )

        శూన్య MPU_v_Task_సమితి_Application_Task_ట్యాగ్( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_Task_సమితి_Application_Task_ట్యాగ్( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_v_Task_సమితి_Application_Task_ట్యాగ్ ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ట్యాగ్( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ట్యాగ్( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_x_Task_Get_Application_Task_ట్యాగ్ ) : "memory"
            );
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
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_v_Task_సమితి_Thread_Local_Storage_సూచిక ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు != 0 )

        శూన్య * MPU_pv_Task_Get_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_Query,
                                                       పునాది_Type_t x_సూచీ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య * MPU_pv_Task_Get_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_Query,
                                                       పునాది_Type_t x_సూచీ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_సూచిక ) : "memory"
            );
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
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_ux_Task_Get_దొంతర_ఎగువ_Water_Mark ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2 == 1 )

        config_దొంతర_లోతు_TYPE MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_దొంతర_లోతు_TYPE MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2 ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskGetSchedulerState == 1 )

        పునాది_Type_t MPU_xTaskGetSchedulerState( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_xTaskGetSchedulerState( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    శూన్య MPU_v_Task_సమితి_సమయం_బహిర్గతం_State( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    శూన్య MPU_v_Task_సమితి_సమయం_బహిర్గతం_State( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm అస్థిర
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
            : : "i" ( SYSTEM_CALL_v_Task_సమితి_సమయం_బహిర్గతం_State ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_Task_Check_For_సమయం_బహిర్గతం( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం,
                                         TickType_t * స్థిరరాశి px_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    పునాది_Type_t MPU_x_Task_Check_For_సమయం_బహిర్గతం( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం,
                                         TickType_t * స్థిరరాశి px_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm అస్థిర
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
            : : "i" ( SYSTEM_CALL_x_Task_Check_For_సమయం_బహిర్గతం ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        పునాది_Type_t MPU_x_Task_Generic_Notify_నమోదు( స్థిరరాశి xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_Task_Generic_Notify_నమోదు( స్థిరరాశి xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        పునాది_Type_t MPU_x_Task_Generic_Notify_Wait_నమోదు( స్థిరరాశి xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_Task_Generic_Notify_Wait_నమోదు( స్థిరరాశి xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        పునాది_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_సూచీ_గమ్యం_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_సూచీ_గమ్యం_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_ul_Task_Generic_Notify_విలువ_Clear ) : "memory"
            );
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
        __asm అస్థిర
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
            : : "i" ( SYSTEM_CALL_x_వరుస_Generic_Send ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_వరుస_Messages_నిరీక్షణ( స్థిరరాశి వరుస_Handle_t x_వరుస ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_వరుస_Messages_నిరీక్షణ( స్థిరరాశి వరుస_Handle_t x_వరుస ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm అస్థిర
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
            : : "i" ( SYSTEM_CALL_ux_వరుస_Messages_నిరీక్షణ ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_వరుస_Spaces_అందుబాటు( స్థిరరాశి వరుస_Handle_t x_వరుస ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_వరుస_Spaces_అందుబాటు( స్థిరరాశి వరుస_Handle_t x_వరుస ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm అస్థిర
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
            : : "i" ( SYSTEM_CALL_ux_వరుస_Spaces_అందుబాటు ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Receive( వరుస_Handle_t x_వరుస,
                                  శూన్య * స్థిరరాశి pv_బఫరు,
                                  TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    పునాది_Type_t MPU_x_వరుస_Receive( వరుస_Handle_t x_వరుస,
                                  శూన్య * స్థిరరాశి pv_బఫరు,
                                  TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm అస్థిర
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
            : : "i" ( SYSTEM_CALL_x_వరుస_Receive ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Peek( వరుస_Handle_t x_వరుస,
                               శూన్య * స్థిరరాశి pv_బఫరు,
                               TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    పునాది_Type_t MPU_x_వరుస_Peek( వరుస_Handle_t x_వరుస,
                               శూన్య * స్థిరరాశి pv_బఫరు,
                               TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm అస్థిర
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
            : : "i" ( SYSTEM_CALL_x_వరుస_Peek ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Semaphore_Take( వరుస_Handle_t x_వరుస,
                                        TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    పునాది_Type_t MPU_x_వరుస_Semaphore_Take( వరుస_Handle_t x_వరుస,
                                        TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm అస్థిర
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
            : : "i" ( SYSTEM_CALL_x_వరుస_Semaphore_Take ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_వరుస_Get_Mutex_Holder( వరుస_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_వరుస_Get_Mutex_Holder( వరుస_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_x_వరుస_Get_Mutex_Holder ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_RECURSIVE_MUTEXES == 1 )

        పునాది_Type_t MPU_x_వరుస_Take_Mutex_Recursive( వరుస_Handle_t xMutex,
                                                 TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_వరుస_Take_Mutex_Recursive( వరుస_Handle_t xMutex,
                                                 TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_x_వరుస_Take_Mutex_Recursive ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_RECURSIVE_MUTEXES == 1 )

        పునాది_Type_t MPU_x_వరుస_Give_Mutex_Recursive( వరుస_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_వరుస_Give_Mutex_Recursive( వరుస_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_x_వరుస_Give_Mutex_Recursive ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )

        వరుస_సమితి_Member_Handle_t MPU_x_వరుస_Select_From_సమితి( వరుస_సమితి_Handle_t x_వరుస_సమితి,
                                                        స్థిరరాశి TickType_t x_Ticks_గమ్యం_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        వరుస_సమితి_Member_Handle_t MPU_x_వరుస_Select_From_సమితి( వరుస_సమితి_Handle_t x_వరుస_సమితి,
                                                        స్థిరరాశి TickType_t x_Ticks_గమ్యం_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_x_వరుస_Select_From_సమితి ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )

        పునాది_Type_t MPU_x_వరుస_కూడు_గమ్యం_సమితి( వరుస_సమితి_Member_Handle_t x_వరుస_Or_Semaphore,
                                       వరుస_సమితి_Handle_t x_వరుస_సమితి ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_వరుస_కూడు_గమ్యం_సమితి( వరుస_సమితి_Member_Handle_t x_వరుస_Or_Semaphore,
                                       వరుస_సమితి_Handle_t x_వరుస_సమితి ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_x_వరుస_కూడు_గమ్యం_సమితి ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_వరుస_REGISTRY_కొలత > 0 )

        శూన్య MPU_v_వరుస_కూడు_గమ్యం_Registry( వరుస_Handle_t x_వరుస,
                                      స్థిరరాశి అక్షరం * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_వరుస_కూడు_గమ్యం_Registry( వరుస_Handle_t x_వరుస,
                                      స్థిరరాశి అక్షరం * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_v_వరుస_కూడు_గమ్యం_Registry ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_వరుస_REGISTRY_కొలత > 0 )

        శూన్య MPU_v_వరుస_Unregister_వరుస( వరుస_Handle_t x_వరుస ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_వరుస_Unregister_వరుస( వరుస_Handle_t x_వరుస ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_v_వరుస_Unregister_వరుస ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_వరుస_REGISTRY_కొలత > 0 )

        స్థిరరాశి అక్షరం * MPU_pc_వరుస_Get_Name( వరుస_Handle_t x_వరుస ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        స్థిరరాశి అక్షరం * MPU_pc_వరుస_Get_Name( వరుస_Handle_t x_వరుస ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_pc_వరుస_Get_Name ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        శూన్య * MPU_pvTimerGetTimerID( స్థిరరాశి TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య * MPU_pvTimerGetTimerID( స్థిరరాశి TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        శూన్య MPU_v_Timer_సమితి_Timer_ID( TimerHandle_t xTimer,
                                   శూన్య * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_Timer_సమితి_Timer_ID( TimerHandle_t xTimer,
                                   శూన్య * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_v_Timer_సమితి_Timer_ID ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_x_Timer_Is_Timer_చురుకైన( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_Timer_Is_Timer_చురుకైన( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_x_Timer_Is_Timer_చురుకైన ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( శూన్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( శూన్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_x_Timer_Generic_Command_From_Task_నమోదు( స్థిరరాశి xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_Timer_Generic_Command_From_Task_నమోదు( స్థిరరాశి xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        స్థిరరాశి అక్షరం * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        స్థిరరాశి అక్షరం * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        శూన్య MPU_v_Timer_సమితి_Reload_బహుళకం( TimerHandle_t xTimer,
                                      స్థిరరాశి పునాది_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_Timer_సమితి_Reload_బహుళకం( TimerHandle_t xTimer,
                                      స్థిరరాశి పునాది_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_v_Timer_సమితి_Reload_బహుళకం ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_x_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_x_Timer_Get_Reload_బహుళకం ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_ux_Timer_Get_Reload_బహుళకం ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_సమయం( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_సమయం( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_x_Timer_Get_Expiry_సమయం ) : "memory"
            );
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_Wait_బిట్లు_నమోదు( స్థిరరాశి x_Event_సమూహం_Wait_బిట్లు_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_బిట్లు_t MPU_x_Event_సమూహం_Wait_బిట్లు_నమోదు( స్థిరరాశి x_Event_సమూహం_Wait_బిట్లు_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupWaitBitsImpl                   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xEventGroupWaitBits_Unpriv                    \n"
                " MPU_xEventGroupWaitBits_Priv:                         \n"
                "     b MPU_xEventGroupWaitBitsImpl                     \n"
                " MPU_xEventGroupWaitBits_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_సమూహం_Wait_బిట్లు ) : "memory"
            );
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_Clear_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                              స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_బిట్లు_t MPU_x_Event_సమూహం_Clear_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                              స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupClearBitsImpl                  \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xEventGroupClearBits_Unpriv                   \n"
                " MPU_xEventGroupClearBits_Priv:                        \n"
                "     b MPU_xEventGroupClearBitsImpl                    \n"
                " MPU_xEventGroupClearBits_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_సమూహం_Clear_బిట్లు ) : "memory"
            );
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_సమితి_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                            స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_బిట్లు_t MPU_x_Event_సమూహం_సమితి_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                            స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupSetBitsImpl                    \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xEventGroupSetBits_Unpriv                     \n"
                " MPU_xEventGroupSetBits_Priv:                          \n"
                "     b MPU_xEventGroupSetBitsImpl                      \n"
                " MPU_xEventGroupSetBits_Unpriv:                        \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_సమూహం_సమితి_బిట్లు ) : "memory"
            );
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
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupSyncImpl                       \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xEventGroupSync_Unpriv                        \n"
                " MPU_xEventGroupSync_Priv:                             \n"
                "     b MPU_xEventGroupSyncImpl                         \n"
                " MPU_xEventGroupSync_Unpriv:                           \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_సమూహం_Sync ) : "memory"
            );
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_సమూహం_Get_సంఖ్య( శూన్య * x_Event_సమూహం ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_సమూహం_Get_సంఖ్య( శూన్య * x_Event_సమూహం ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_ux_Event_సమూహం_Get_సంఖ్య ) : "memory"
            );
        }

    #అయితే_ముగింపు /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        శూన్య MPU_v_Event_సమూహం_సమితి_సంఖ్య( శూన్య * x_Event_సమూహం,
                                       UBaseType_t ux_Event_సమూహం_సంఖ్య ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        శూన్య MPU_v_Event_సమూహం_సమితి_సంఖ్య( శూన్య * x_Event_సమూహం,
                                       UBaseType_t ux_Event_సమూహం_సంఖ్య ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
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
                : : "i" ( SYSTEM_CALL_v_Event_సమూహం_సమితి_సంఖ్య ) : "memory"
            );
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
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferSendImpl                     \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xStreamBufferSend_Unpriv                      \n"
                " MPU_xStreamBufferSend_Priv:                           \n"
                "     b MPU_xStreamBufferSendImpl                       \n"
                " MPU_xStreamBufferSend_Unpriv:                         \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_ప్రవాహం_బఫరు_Send ) : "memory"
            );
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
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferReceiveImpl                  \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xStreamBufferReceive_Unpriv                   \n"
                " MPU_xStreamBufferReceive_Priv:                        \n"
                "     b MPU_xStreamBufferReceiveImpl                    \n"
                " MPU_xStreamBufferReceive_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_ప్రవాహం_బఫరు_Receive ) : "memory"
            );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_నిండిన( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_నిండిన( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferIsFullImpl                   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xStreamBufferIsFull_Unpriv                    \n"
                " MPU_xStreamBufferIsFull_Priv:                         \n"
                "     b MPU_xStreamBufferIsFullImpl                     \n"
                " MPU_xStreamBufferIsFull_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_ప్రవాహం_బఫరు_Is_నిండిన ) : "memory"
            );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferIsEmptyImpl                  \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xStreamBufferIsEmpty_Unpriv                   \n"
                " MPU_xStreamBufferIsEmpty_Priv:                        \n"
                "     b MPU_xStreamBufferIsEmptyImpl                    \n"
                " MPU_xStreamBufferIsEmpty_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_ప్రవాహం_బఫరు_Is_ఖాళీలు ) : "memory"
            );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferSpacesAvailableImpl          \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xStreamBufferSpacesAvailable_Unpriv           \n"
                " MPU_xStreamBufferSpacesAvailable_Priv:                \n"
                "     b MPU_xStreamBufferSpacesAvailableImpl            \n"
                " MPU_xStreamBufferSpacesAvailable_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు ) : "memory"
            );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferBytesAvailableImpl           \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xStreamBufferBytesAvailable_Unpriv            \n"
                " MPU_xStreamBufferBytesAvailable_Priv:                 \n"
                "     b MPU_xStreamBufferBytesAvailableImpl             \n"
                " MPU_xStreamBufferBytesAvailable_Unpriv:               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు ) : "memory"
            );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferSetTriggerLevelImpl          \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xStreamBufferSetTriggerLevel_Unpriv           \n"
                " MPU_xStreamBufferSetTriggerLevel_Priv:                \n"
                "     b MPU_xStreamBufferSetTriggerLevelImpl            \n"
                " MPU_xStreamBufferSetTriggerLevel_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level ) : "memory"
            );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm అస్థిర
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferNextMessageLengthBytesImpl   \n"
                "                                                       \n"
                " push {r0}                                             \n"
                " mrs r0, control                                       \n"
                " tst r0, #1                                            \n"
                " pop {r0}                                              \n"
                " bne MPU_xStreamBufferNextMessageLengthBytes_Unpriv    \n"
                " MPU_xStreamBufferNextMessageLengthBytes_Priv:         \n"
                "     b MPU_xStreamBufferNextMessageLengthBytesImpl     \n"
                " MPU_xStreamBufferNextMessageLengthBytes_Unpriv:       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు ) : "memory"
            );
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
