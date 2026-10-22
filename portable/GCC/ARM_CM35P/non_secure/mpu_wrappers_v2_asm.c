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

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ਜੇ ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ਜੇ ( INCLUDE_xTaskDelayUntil == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskDelayUntil( TickType_t * ਅਚਲ px_ਪਿਛਲਾ_Wake_ਸਮਾਂ,
                                        ਅਚਲ TickType_t x_ਸਮਾਂ_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_xTaskDelayUntil( TickType_t * ਅਚਲ px_ਪਿਛਲਾ_Wake_ਸਮਾਂ,
                                        ਅਚਲ TickType_t x_ਸਮਾਂ_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskAbortDelay == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskDelay == 1 )

        ਖਾਲੀ MPU_vTaskDelay( ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_vTaskDelay( ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_ਤਰਜੀਹ_Get == 1 )

        UBaseType_t MPU_ux_Task_ਤਰਜੀਹ_Get( ਅਚਲ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_ਤਰਜੀਹ_Get( ਅਚਲ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_ux_Task_ਤਰਜੀਹ_Get ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskSuspend == 1 )

        ਖਾਲੀ MPU_vTaskSuspend( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_vTaskSuspend( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskSuspend == 1 )

        ਖਾਲੀ MPU_vTaskResume( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_vTaskResume( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ਗਿਣਤੀ( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_ਗਿਣਤੀ( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm ਅਸਥਿਰ
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
            : : "i" ( SYSTEM_CALL_x_Task_Get_Tick_ਗਿਣਤੀ ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm ਅਸਥਿਰ
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
            : : "i" ( SYSTEM_CALL_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਅਚਲ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਅਚਲ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਅਚਲ TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਅਚਲ TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )

        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ਟੈਗ( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ਟੈਗ( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_Task_Get_Application_Task_ਟੈਗ ) : "memory"
            );
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
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ != 0 )

        ਖਾਲੀ * MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Query,
                                                       ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ * MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Query,
                                                       ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ ) : "memory"
            );
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
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2 == 1 )

        config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2 ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskGetSchedulerState == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskGetSchedulerState( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_xTaskGetSchedulerState( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm ਅਸਥਿਰ
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
            : : "i" ( SYSTEM_CALL_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ,
                                         TickType_t * ਅਚਲ px_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ਅਧਾਰ_Type_t MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ,
                                         TickType_t * ਅਚਲ px_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm ਅਸਥਿਰ
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
            : : "i" ( SYSTEM_CALL_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_Wait_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_Task_Generic_Notify_Wait_ਇੰਦਰਾਜ( ਅਚਲ xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_ul_Task_Generic_Notify_ਮੁੱਲ_Clear ) : "memory"
            );
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
        __asm ਅਸਥਿਰ
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
            : : "i" ( SYSTEM_CALL_x_ਕਤਾਰ_Generic_Send ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm ਅਸਥਿਰ
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
            : : "i" ( SYSTEM_CALL_ux_ਕਤਾਰ_Messages_ਉਡੀਕ ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm ਅਸਥਿਰ
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
            : : "i" ( SYSTEM_CALL_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Receive( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                  ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                  TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Receive( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                  ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                  TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm ਅਸਥਿਰ
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
            : : "i" ( SYSTEM_CALL_x_ਕਤਾਰ_Receive ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Peek( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                               ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                               TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Peek( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                               ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                               TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm ਅਸਥਿਰ
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
            : : "i" ( SYSTEM_CALL_x_ਕਤਾਰ_Peek ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Semaphore_Take( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                        TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Semaphore_Take( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                        TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm ਅਸਥਿਰ
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
            : : "i" ( SYSTEM_CALL_x_ਕਤਾਰ_Semaphore_Take ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_ਕਤਾਰ_Get_Mutex_Holder( ਕਤਾਰ_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_ਕਤਾਰ_Get_Mutex_Holder( ਕਤਾਰ_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਕਤਾਰ_Get_Mutex_Holder ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_RECURSIVE_MUTEXES == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Take_Mutex_Recursive( ਕਤਾਰ_Handle_t xMutex,
                                                 TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Take_Mutex_Recursive( ਕਤਾਰ_Handle_t xMutex,
                                                 TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਕਤਾਰ_Take_Mutex_Recursive ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_RECURSIVE_MUTEXES == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Give_Mutex_Recursive( ਕਤਾਰ_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Give_Mutex_Recursive( ਕਤਾਰ_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਕਤਾਰ_Give_Mutex_Recursive ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )

        ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ,
                                                        ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ,
                                                        ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਕਤਾਰ_Select_From_ਸੈੱਟ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਕਤਾਰ_Or_Semaphore,
                                       ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਕਤਾਰ_Or_Semaphore,
                                       ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0 )

        ਖਾਲੀ MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                      ਅਚਲ ਅੱਖਰ * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                      ਅਚਲ ਅੱਖਰ * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0 )

        ਖਾਲੀ MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_v_ਕਤਾਰ_Unregister_ਕਤਾਰ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0 )

        ਅਚਲ ਅੱਖਰ * MPU_pc_ਕਤਾਰ_Get_Name( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਚਲ ਅੱਖਰ * MPU_pc_ਕਤਾਰ_Get_Name( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_pc_ਕਤਾਰ_Get_Name ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਖਾਲੀ * MPU_pvTimerGetTimerID( ਅਚਲ TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ * MPU_pvTimerGetTimerID( ਅਚਲ TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Timer_ID( TimerHandle_t xTimer,
                                   ਖਾਲੀ * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Timer_ID( TimerHandle_t xTimer,
                                   ਖਾਲੀ * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_v_Timer_ਸੈੱਟ_Timer_ID ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Timer_Is_Timer_ਸਰਗਰਮ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_Timer_Is_Timer_ਸਰਗਰਮ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_Timer_Is_Timer_ਸਰਗਰਮ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ਖਾਲੀ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ਖਾਲੀ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Timer_Generic_Command_From_Task_ਇੰਦਰਾਜ( ਅਚਲ xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_Timer_Generic_Command_From_Task_ਇੰਦਰਾਜ( ਅਚਲ xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਚਲ ਅੱਖਰ * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਚਲ ਅੱਖਰ * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer,
                                      ਅਚਲ ਅਧਾਰ_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer,
                                      ਅਚਲ ਅਧਾਰ_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_Timer_Get_Reload_ਬਹੁਲਕ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_ux_Timer_Get_Reload_ਬਹੁਲਕ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_ਸਮਾਂ( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_ਸਮਾਂ( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_Timer_Get_Expiry_ਸਮਾਂ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_ਇੰਦਰਾਜ( ਅਚਲ x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_ਇੰਦਰਾਜ( ਅਚਲ x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                              ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                              ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                            ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                            ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ ) : "memory"
            );
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
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_Event_ਸਮੂਹ_Sync ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        ਖਾਲੀ MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ,
                                       UBaseType_t ux_Event_ਸਮੂਹ_ਸੰਖਿਆ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਖਾਲੀ MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ( ਖਾਲੀ * x_Event_ਸਮੂਹ,
                                       UBaseType_t ux_Event_ਸਮੂਹ_ਸੰਖਿਆ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ ) : "memory"
            );
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
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_Send ) : "memory"
            );
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
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_Receive ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm ਅਸਥਿਰ
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
                : : "i" ( SYSTEM_CALL_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ ) : "memory"
            );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
