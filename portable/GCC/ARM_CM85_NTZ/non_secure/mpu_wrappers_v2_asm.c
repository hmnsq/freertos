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

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#यदि ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #यदि ( INCLUDE_xTaskDelayUntil == 1 )

        आधारः_Type_t MPU_xTaskDelayUntil( TickType_t * ध्रुव pxPreviousWakeTime,
                                        ध्रुव TickType_t xTimeIncrement ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xTaskDelayUntil( TickType_t * ध्रुव pxPreviousWakeTime,
                                        ध्रुव TickType_t xTimeIncrement ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskAbortDelay == 1 )

        आधारः_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskDelay == 1 )

        शून्य MPU_vTaskDelay( ध्रुव TickType_t x_Ticks_गन्तव्यम्_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_vTaskDelay( ध्रुव TickType_t x_Ticks_गन्तव्यम्_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_प्राथमिकता_Get == 1 )

        UBaseType_t MPU_ux_Task_प्राथमिकता_Get( ध्रुव TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_प्राथमिकता_Get( ध्रुव TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_ux_Task_प्राथमिकता_Get ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskSuspend == 1 )

        शून्य MPU_vTaskSuspend( TaskHandle_t x_Task_गन्तव्यम्_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_vTaskSuspend( TaskHandle_t x_Task_गन्तव्यम्_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskSuspend == 1 )

        शून्य MPU_vTaskResume( TaskHandle_t x_Task_गन्तव्यम्_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_vTaskResume( TaskHandle_t x_Task_गन्तव्यम्_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_गणनम्( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_गणनम्( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm चञ्चल
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
            : : "i" ( SYSTEM_CALL_x_Task_Get_Tick_गणनम् ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm चञ्चल
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
            : : "i" ( SYSTEM_CALL_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #यदि ( config_GENERATE_सततम्_TIME_STATS == 1 )

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_गणक( ध्रुव TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_गणक( ध्रुव TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_सततम्_Time_गणक ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_GENERATE_सततम्_TIME_STATS == 1 )

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_Percent( ध्रुव TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_Percent( ध्रुव TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_सततम्_Time_Percent ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_GENERATE_सततम्_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_Percent( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_Percent( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_सततम्_Time_Percent ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_GENERATE_सततम्_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_गणक( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_गणक( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_सततम्_Time_गणक ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )

        शून्य MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_v_Task_समुच्चयः_Application_Task_चिह्नकम् ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_चिह्नकम्( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_चिह्नकम्( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_Task_Get_Application_Task_चिह्नकम् ) : "memory"
            );
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
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_v_Task_समुच्चयः_Thread_Local_Storage_Pointer ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_अङ्कः_THREAD_LOCAL_STORAGE_सूचकाः != 0 )

        शून्य * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t x_Task_गन्तव्यम्_Query,
                                                       आधारः_Type_t x_सूचकांक ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t x_Task_गन्तव्यम्_Query,
                                                       आधारः_Type_t x_सूचकांक ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer ) : "memory"
            );
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
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_ux_Task_Get_राशिः_उच्चः_Water_Mark ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark2 == 1 )

        config_राशिः_गभीरता_TYPE MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_राशिः_गभीरता_TYPE MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_ux_Task_Get_राशिः_उच्चः_Water_Mark2 ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetSchedulerState == 1 )

        आधारः_Type_t MPU_xTaskGetSchedulerState( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xTaskGetSchedulerState( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    शून्य MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम् ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    शून्य MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम् ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm चञ्चल
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
            : : "i" ( SYSTEM_CALL_v_Task_समुच्चयः_Time_बहिर्गमनम्_State ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_x_Task_Check_For_Time_बहिर्गमनम्( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम्,
                                         TickType_t * ध्रुव px_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    आधारः_Type_t MPU_x_Task_Check_For_Time_बहिर्गमनम्( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम्,
                                         TickType_t * ध्रुव px_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm चञ्चल
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
            : : "i" ( SYSTEM_CALL_x_Task_Check_For_Time_बहिर्गमनम् ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        आधारः_Type_t MPU_x_Task_Generic_Notify_प्रविष्टिः( ध्रुव xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Task_Generic_Notify_प्रविष्टिः( ध्रुव xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        आधारः_Type_t MPU_x_Task_Generic_Notify_Wait_प्रविष्टिः( ध्रुव xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Task_Generic_Notify_Wait_प्रविष्टिः( ध्रुव xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        आधारः_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_ul_Task_Generic_Notify_मानम्_Clear ) : "memory"
            );
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
        __asm चञ्चल
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
            : : "i" ( SYSTEM_CALL_xQueueGenericSend ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Queue_Messages_प्रतीक्षा( ध्रुव QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Queue_Messages_प्रतीक्षा( ध्रुव QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm चञ्चल
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
            : : "i" ( SYSTEM_CALL_ux_Queue_Messages_प्रतीक्षा ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Queue_Spaces_उपलब्धम्( ध्रुव QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Queue_Spaces_उपलब्धम्( ध्रुव QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm चञ्चल
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
            : : "i" ( SYSTEM_CALL_ux_Queue_Spaces_उपलब्धम् ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                  शून्य * ध्रुव pv_बफर,
                                  TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    आधारः_Type_t MPU_xQueueReceive( QueueHandle_t xQueue,
                                  शून्य * ध्रुव pv_बफर,
                                  TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm चञ्चल
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
            : : "i" ( SYSTEM_CALL_xQueueReceive ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               शून्य * ध्रुव pv_बफर,
                               TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    आधारः_Type_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               शून्य * ध्रुव pv_बफर,
                               TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm चञ्चल
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
            : : "i" ( SYSTEM_CALL_xQueuePeek ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    आधारः_Type_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm चञ्चल
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
            : : "i" ( SYSTEM_CALL_xQueueSemaphoreTake ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_xQueueGetMutexHolder ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_RECURSIVE_MUTEXES == 1 )

        आधारः_Type_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_xQueueTakeMutexRecursive ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_RECURSIVE_MUTEXES == 1 )

        आधारः_Type_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_xQueueGiveMutexRecursive( QueueHandle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_xQueueGiveMutexRecursive ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )

        Queue_समुच्चयः_Member_Handle_t MPU_x_Queue_Select_From_समुच्चयः( Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः,
                                                        ध्रुव TickType_t x_Ticks_गन्तव्यम्_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Queue_समुच्चयः_Member_Handle_t MPU_x_Queue_Select_From_समुच्चयः( Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः,
                                                        ध्रुव TickType_t x_Ticks_गन्तव्यम्_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_Queue_Select_From_समुच्चयः ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )

        आधारः_Type_t MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः( Queue_समुच्चयः_Member_Handle_t xQueueOrSemaphore,
                                       Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः( Queue_समुच्चयः_Member_Handle_t xQueueOrSemaphore,
                                       Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_QUEUE_REGISTRY_आकार > 0 )

        शून्य MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry( QueueHandle_t xQueue,
                                      ध्रुव वर्ण * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry( QueueHandle_t xQueue,
                                      ध्रुव वर्ण * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_v_Queue_सङ्कलय_गन्तव्यम्_Registry ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_QUEUE_REGISTRY_आकार > 0 )

        शून्य MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_vQueueUnregisterQueue ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_QUEUE_REGISTRY_आकार > 0 )

        ध्रुव वर्ण * MPU_pcQueueGetName( QueueHandle_t xQueue ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ध्रुव वर्ण * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_pcQueueGetName ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        शून्य * MPU_pvTimerGetTimerID( ध्रुव TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य * MPU_pvTimerGetTimerID( ध्रुव TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        शून्य MPU_v_Timer_समुच्चयः_Timer_ID( TimerHandle_t xTimer,
                                   शून्य * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_v_Timer_समुच्चयः_Timer_ID( TimerHandle_t xTimer,
                                   शून्य * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_v_Timer_समुच्चयः_Timer_ID ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_x_Timer_Is_Timer_सक्रिय( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Timer_Is_Timer_सक्रिय( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_Timer_Is_Timer_सक्रिय ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( शून्य ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( शून्य ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_x_Timer_Generic_Command_From_Task_प्रविष्टिः( ध्रुव xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Timer_Generic_Command_From_Task_प्रविष्टिः( ध्रुव xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        ध्रुव वर्ण * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ध्रुव वर्ण * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        शून्य MPU_v_Timer_समुच्चयः_Reload_बहुलकम्( TimerHandle_t xTimer,
                                      ध्रुव आधारः_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_v_Timer_समुच्चयः_Reload_बहुलकम्( TimerHandle_t xTimer,
                                      ध्रुव आधारः_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_v_Timer_समुच्चयः_Reload_बहुलकम् ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_x_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_Timer_Get_Reload_बहुलकम् ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_ux_Timer_Get_Reload_बहुलकम् ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_xTimerGetExpiryTime ) : "memory"
            );
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Wait_द्वयङ्काः_प्रविष्टिः( ध्रुव x_Event_गणः_Wait_द्वयङ्काः_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Wait_द्वयङ्काः_प्रविष्टिः( ध्रुव x_Event_गणः_Wait_द्वयङ्काः_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_Event_गणः_Wait_द्वयङ्काः ) : "memory"
            );
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Clear_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                              ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Clear_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                              ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_Event_गणः_Clear_द्वयङ्काः ) : "memory"
            );
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                            ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_द्वयङ्काः_t MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                            ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_Event_गणः_समुच्चयः_द्वयङ्काः ) : "memory"
            );
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
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_Event_गणः_Sync ) : "memory"
            );
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_गणः_Get_सङ्ख्या( शून्य * x_Event_गणः ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_गणः_Get_सङ्ख्या( शून्य * x_Event_गणः ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_ux_Event_गणः_Get_सङ्ख्या ) : "memory"
            );
        }

    #यदि_अन्तः /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        शून्य MPU_v_Event_गणः_समुच्चयः_सङ्ख्या( शून्य * x_Event_गणः,
                                       UBaseType_t ux_Event_गणः_सङ्ख्या ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        शून्य MPU_v_Event_गणः_समुच्चयः_सङ्ख्या( शून्य * x_Event_गणः,
                                       UBaseType_t ux_Event_गणः_सङ्ख्या ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_v_Event_गणः_समुच्चयः_सङ्ख्या ) : "memory"
            );
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
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_प्रवाहः_बफर_Send ) : "memory"
            );
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
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_प्रवाहः_बफर_Receive ) : "memory"
            );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_पूर्णम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_पूर्णम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_प्रवाहः_बफर_Is_पूर्णम् ) : "memory"
            );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_रिक्तानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_रिक्तानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_प्रवाहः_बफर_Is_रिक्तानि ) : "memory"
            );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_प्रवाहः_बफर_Spaces_उपलब्धम् ) : "memory"
            );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम् ) : "memory"
            );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        आधारः_Type_t MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level ) : "memory"
            );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm चञ्चल
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
                : : "i" ( SYSTEM_CALL_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि ) : "memory"
            );
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#यदि_अन्तः /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
