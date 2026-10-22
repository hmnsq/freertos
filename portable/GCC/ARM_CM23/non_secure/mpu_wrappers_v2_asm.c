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

#لغو_تعریف MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )

        پایه_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_قبلی_Wake_زمان,
                                        ثابت TickType_t x_زمان_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_قبلی_Wake_زمان,
                                        ثابت TickType_t x_زمان_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskDelayUntilImpl                       \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTaskDelayUntil_Unpriv                        \n"
                " MPU_xTaskDelayUntil_Priv:                             \n"
                "     b MPU_xTaskDelayUntilImpl                         \n"
                " MPU_xTaskDelayUntil_Unpriv:                           \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskDelayUntil ) : "memory"
            );
        }

    #پایان_اگر /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )

        پایه_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskAbortDelayImpl                       \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTaskAbortDelay_Unpriv                        \n"
                " MPU_xTaskAbortDelay_Priv:                             \n"
                "     b MPU_xTaskAbortDelayImpl                         \n"
                " MPU_xTaskAbortDelay_Unpriv:                           \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskAbortDelay ) : "memory"
            );
        }

    #پایان_اگر /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )

        فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_مقصد_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskDelayImpl                            \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_vTaskDelay_Unpriv                             \n"
                " MPU_vTaskDelay_Priv:                                  \n"
                "     b MPU_vTaskDelayImpl                              \n"
                " MPU_vTaskDelay_Unpriv:                                \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskDelay ) : "memory"
            );
        }

    #پایان_اگر /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_اولویت_Get == 1 )

        UBaseType_t MPU_ux_Task_اولویت_Get( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_اولویت_Get( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxTaskPriorityGetImpl                     \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_uxTaskPriorityGet_Unpriv                      \n"
                " MPU_uxTaskPriorityGet_Priv:                           \n"
                "     b MPU_uxTaskPriorityGetImpl                       \n"
                " MPU_uxTaskPriorityGet_Unpriv:                         \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Task_اولویت_Get ) : "memory"
            );
        }

    #پایان_اگر /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        eTaskState MPU_eTaskGetState( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_eTaskGetStateImpl                         \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_eTaskGetState_Unpriv                          \n"
                " MPU_eTaskGetState_Priv:                               \n"
                "     b MPU_eTaskGetStateImpl                           \n"
                " MPU_eTaskGetState_Unpriv:                             \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_eTaskGetState ) : "memory"
            );
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
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskGetInfoImpl                          \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_vTaskGetInfo_Unpriv                           \n"
                " MPU_vTaskGetInfo_Priv:                                \n"
                "     b MPU_vTaskGetInfoImpl                            \n"
                " MPU_vTaskGetInfo_Unpriv:                              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskGetInfo ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGetIdleTaskHandleImpl                \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTaskGetIdleTaskHandle_Unpriv                 \n"
                " MPU_xTaskGetIdleTaskHandle_Priv:                      \n"
                "     b MPU_xTaskGetIdleTaskHandleImpl                  \n"
                " MPU_xTaskGetIdleTaskHandle_Unpriv:                    \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGetIdleTaskHandle ) : "memory"
            );
        }

    #پایان_اگر /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_مقصد_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskSuspendImpl                          \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_vTaskSuspend_Unpriv                           \n"
                " MPU_vTaskSuspend_Priv:                                \n"
                "     b MPU_vTaskSuspendImpl                            \n"
                " MPU_vTaskSuspend_Unpriv:                              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskSuspend ) : "memory"
            );
        }

    #پایان_اگر /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskResume( TaskHandle_t x_Task_مقصد_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskResumeImpl                           \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_vTaskResume_Unpriv                            \n"
                " MPU_vTaskResume_Priv:                                 \n"
                "     b MPU_vTaskResumeImpl                             \n"
                " MPU_vTaskResume_Unpriv:                               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskResume ) : "memory"
            );
        }

    #پایان_اگر /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_شمار( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_شمار( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متطاير
        (
            " .syntax unified                                       \n"
            " .extern MPU_xTaskGetTickCountImpl                     \n"
            "                                                       \n"
            " push {r0, r1}                                         \n"
            " mrs r0, control                                       \n"
            " movs r1, #1                                           \n"
            " tst r0, r1                                            \n"
            " pop {r0, r1}                                          \n"
            " bne MPU_xTaskGetTickCount_Unpriv                      \n"
            " MPU_xTaskGetTickCount_Priv:                           \n"
            "     b MPU_xTaskGetTickCountImpl                       \n"
            " MPU_xTaskGetTickCount_Unpriv:                         \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_Task_Get_Tick_شمار ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_عدد_از_Tasks( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_عدد_از_Tasks( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متطاير
        (
            " .syntax unified                                       \n"
            " .extern MPU_uxTaskGetNumberOfTasksImpl                \n"
            "                                                       \n"
            " push {r0, r1}                                         \n"
            " mrs r0, control                                       \n"
            " movs r1, #1                                           \n"
            " tst r0, r1                                            \n"
            " pop {r0, r1}                                          \n"
            " bne MPU_uxTaskGetNumberOfTasks_Unpriv                 \n"
            " MPU_uxTaskGetNumberOfTasks_Priv:                      \n"
            "     b MPU_uxTaskGetNumberOfTasksImpl                  \n"
            " MPU_uxTaskGetNumberOfTasks_Unpriv:                    \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_ux_Task_Get_عدد_از_Tasks ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_پیاپی_زمان_STATS == 1 )

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Counter( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Counter( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGetRunTimeCounterImpl               \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_ulTaskGetRunTimeCounter_Unpriv                \n"
                " MPU_ulTaskGetRunTimeCounter_Priv:                     \n"
                "     b MPU_ulTaskGetRunTimeCounterImpl                 \n"
                " MPU_ulTaskGetRunTimeCounter_Unpriv:                   \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_پیاپی_زمان_Counter ) : "memory"
            );
        }

    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_پیاپی_زمان_STATS == 1 )

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Percent( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Percent( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGetRunTimePercentImpl               \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_ulTaskGetRunTimePercent_Unpriv                \n"
                " MPU_ulTaskGetRunTimePercent_Priv:                     \n"
                "     b MPU_ulTaskGetRunTimePercentImpl                 \n"
                " MPU_ulTaskGetRunTimePercent_Unpriv:                   \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_پیاپی_زمان_Percent ) : "memory"
            );
        }

    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پیاپی_زمان_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGetIdleRunTimePercentImpl           \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_ulTaskGetIdleRunTimePercent_Unpriv            \n"
                " MPU_ulTaskGetIdleRunTimePercent_Priv:                 \n"
                "     b MPU_ulTaskGetIdleRunTimePercentImpl             \n"
                " MPU_ulTaskGetIdleRunTimePercent_Unpriv:               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_پیاپی_زمان_Percent ) : "memory"
            );
        }

    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پیاپی_زمان_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGetIdleRunTimeCounterImpl           \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_ulTaskGetIdleRunTimeCounter_Unpriv            \n"
                " MPU_ulTaskGetIdleRunTimeCounter_Priv:                 \n"
                "     b MPU_ulTaskGetIdleRunTimeCounterImpl             \n"
                " MPU_ulTaskGetIdleRunTimeCounter_Unpriv:               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_پیاپی_زمان_Counter ) : "memory"
            );
        }

    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )

        فراغ MPU_v_Task_مجموعه_Application_Task_برچسب( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Task_مجموعه_Application_Task_برچسب( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskSetApplicationTaskTagImpl            \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_vTaskSetApplicationTaskTag_Unpriv             \n"
                " MPU_vTaskSetApplicationTaskTag_Priv:                  \n"
                "     b MPU_vTaskSetApplicationTaskTagImpl              \n"
                " MPU_vTaskSetApplicationTaskTag_Unpriv:                \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Task_مجموعه_Application_Task_برچسب ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_برچسب( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_برچسب( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGetApplicationTaskTagImpl            \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTaskGetApplicationTaskTag_Unpriv             \n"
                " MPU_xTaskGetApplicationTaskTag_Priv:                  \n"
                "     b MPU_xTaskGetApplicationTaskTagImpl              \n"
                " MPU_xTaskGetApplicationTaskTag_Unpriv:                \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Task_Get_Application_Task_برچسب ) : "memory"
            );
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
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTaskSetThreadLocalStoragePointerImpl     \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_vTaskSetThreadLocalStoragePointer_Unpriv      \n"
                " MPU_vTaskSetThreadLocalStoragePointer_Priv:           \n"
                "     b MPU_vTaskSetThreadLocalStoragePointerImpl       \n"
                " MPU_vTaskSetThreadLocalStoragePointer_Unpriv:         \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر ) : "memory"
            );
        }

    #پایان_اگر /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها != 0 )

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_Query,
                                                       پایه_Type_t x_شاخص ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_Query,
                                                       پایه_Type_t x_شاخص ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_pvTaskGetThreadLocalStoragePointerImpl    \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_pvTaskGetThreadLocalStoragePointer_Unpriv     \n"
                " MPU_pvTaskGetThreadLocalStoragePointer_Priv:          \n"
                "     b MPU_pvTaskGetThreadLocalStoragePointerImpl      \n"
                " MPU_pvTaskGetThreadLocalStoragePointer_Unpriv:        \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_اشاره_گر ) : "memory"
            );
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
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxTaskGetSystemStateImpl                  \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_uxTaskGetSystemState_Unpriv                   \n"
                " MPU_uxTaskGetSystemState_Priv:                        \n"
                "     b MPU_uxTaskGetSystemStateImpl                    \n"
                " MPU_uxTaskGetSystemState_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_uxTaskGetSystemState ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_پشته_بالا_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_پشته_بالا_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxTaskGetStackHighWaterMarkImpl           \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_uxTaskGetStackHighWaterMark_Unpriv            \n"
                " MPU_uxTaskGetStackHighWaterMark_Priv:                 \n"
                "     b MPU_uxTaskGetStackHighWaterMarkImpl             \n"
                " MPU_uxTaskGetStackHighWaterMark_Unpriv:               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Task_Get_پشته_بالا_Water_Mark ) : "memory"
            );
        }

    #پایان_اگر /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark2 == 1 )

        config_پشته_عمق_TYPE MPU_ux_Task_Get_پشته_بالا_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_پشته_عمق_TYPE MPU_ux_Task_Get_پشته_بالا_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxTaskGetStackHighWaterMark2Impl          \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_uxTaskGetStackHighWaterMark2_Unpriv           \n"
                " MPU_uxTaskGetStackHighWaterMark2_Priv:                \n"
                "     b MPU_uxTaskGetStackHighWaterMark2Impl            \n"
                " MPU_uxTaskGetStackHighWaterMark2_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Task_Get_پشته_بالا_Water_Mark2 ) : "memory"
            );
        }

    #پایان_اگر /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGetCurrentTaskHandleImpl             \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTaskGetCurrentTaskHandle_Unpriv              \n"
                " MPU_xTaskGetCurrentTaskHandle_Priv:                   \n"
                "     b MPU_xTaskGetCurrentTaskHandleImpl               \n"
                " MPU_xTaskGetCurrentTaskHandle_Unpriv:                 \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGetCurrentTaskHandle ) : "memory"
            );
        }

    #پایان_اگر /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

        پایه_Type_t MPU_xTaskGetSchedulerState( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGetSchedulerStateImpl                \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTaskGetSchedulerState_Unpriv                 \n"
                " MPU_xTaskGetSchedulerState_Priv:                      \n"
                "     b MPU_xTaskGetSchedulerStateImpl                  \n"
                " MPU_xTaskGetSchedulerState_Unpriv:                    \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGetSchedulerState ) : "memory"
            );
        }

    #پایان_اگر /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_مجموعه_زمان_بیرون_State( زمان_بیرون_t * ثابت px_زمان_بیرون ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    فراغ MPU_v_Task_مجموعه_زمان_بیرون_State( زمان_بیرون_t * ثابت px_زمان_بیرون ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متطاير
        (
            " .syntax unified                                       \n"
            " .extern MPU_vTaskSetTimeOutStateImpl                  \n"
            "                                                       \n"
            " push {r0, r1}                                         \n"
            " mrs r0, control                                       \n"
            " movs r1, #1                                           \n"
            " tst r0, r1                                            \n"
            " pop {r0, r1}                                          \n"
            " bne MPU_vTaskSetTimeOutState_Unpriv                   \n"
            " MPU_vTaskSetTimeOutState_Priv:                        \n"
            "     b MPU_vTaskSetTimeOutStateImpl                    \n"
            " MPU_vTaskSetTimeOutState_Unpriv:                      \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_v_Task_مجموعه_زمان_بیرون_State ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_Task_Check_For_زمان_بیرون( زمان_بیرون_t * ثابت px_زمان_بیرون,
                                         TickType_t * ثابت px_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    پایه_Type_t MPU_x_Task_Check_For_زمان_بیرون( زمان_بیرون_t * ثابت px_زمان_بیرون,
                                         TickType_t * ثابت px_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متطاير
        (
            " .syntax unified                                       \n"
            " .extern MPU_xTaskCheckForTimeOutImpl                  \n"
            "                                                       \n"
            " push {r0, r1}                                         \n"
            " mrs r0, control                                       \n"
            " movs r1, #1                                           \n"
            " tst r0, r1                                            \n"
            " pop {r0, r1}                                          \n"
            " bne MPU_xTaskCheckForTimeOut_Unpriv                   \n"
            " MPU_xTaskCheckForTimeOut_Priv:                        \n"
            "     b MPU_xTaskCheckForTimeOutImpl                    \n"
            " MPU_xTaskCheckForTimeOut_Unpriv:                      \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_Task_Check_For_زمان_بیرون ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        پایه_Type_t MPU_x_Task_Generic_Notify_مدخل( ثابت xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_Task_Generic_Notify_مدخل( ثابت xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGenericNotifyImpl                    \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTaskGenericNotify_Unpriv                     \n"
                " MPU_xTaskGenericNotify_Priv:                          \n"
                "     b MPU_xTaskGenericNotifyImpl                      \n"
                " MPU_xTaskGenericNotify_Unpriv:                        \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGenericNotify ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        پایه_Type_t MPU_x_Task_Generic_Notify_Wait_مدخل( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_Task_Generic_Notify_Wait_مدخل( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGenericNotifyWaitImpl                \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTaskGenericNotifyWait_Unpriv                 \n"
                " MPU_xTaskGenericNotifyWait_Priv:                      \n"
                "     b MPU_xTaskGenericNotifyWaitImpl                  \n"
                " MPU_xTaskGenericNotifyWait_Unpriv:                    \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGenericNotifyWait ) : "memory"
            );
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
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGenericNotifyTakeImpl               \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_ulTaskGenericNotifyTake_Unpriv                \n"
                " MPU_ulTaskGenericNotifyTake_Priv:                     \n"
                "     b MPU_ulTaskGenericNotifyTakeImpl                 \n"
                " MPU_ulTaskGenericNotifyTake_Unpriv:                   \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ulTaskGenericNotifyTake ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        پایه_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_شاخص_مقصد_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_شاخص_مقصد_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTaskGenericNotifyStateClearImpl          \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTaskGenericNotifyStateClear_Unpriv           \n"
                " MPU_xTaskGenericNotifyStateClear_Priv:                \n"
                "     b MPU_xTaskGenericNotifyStateClearImpl            \n"
                " MPU_xTaskGenericNotifyStateClear_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGenericNotifyStateClear ) : "memory"
            );
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
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_ulTaskGenericNotifyValueClearImpl         \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_ulTaskGenericNotifyValueClear_Unpriv          \n"
                " MPU_ulTaskGenericNotifyValueClear_Priv:               \n"
                "     b MPU_ulTaskGenericNotifyValueClearImpl           \n"
                " MPU_ulTaskGenericNotifyValueClear_Unpriv:             \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Generic_Notify_مقدار_Clear ) : "memory"
            );
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
        __asm متطاير
        (
            " .syntax unified                                       \n"
            " .extern MPU_xQueueGenericSendImpl                     \n"
            "                                                       \n"
            " push {r0, r1}                                         \n"
            " mrs r0, control                                       \n"
            " movs r1, #1                                           \n"
            " tst r0, r1                                            \n"
            " pop {r0, r1}                                          \n"
            " bne MPU_xQueueGenericSend_Unpriv                      \n"
            " MPU_xQueueGenericSend_Priv:                           \n"
            "     b MPU_xQueueGenericSendImpl                       \n"
            " MPU_xQueueGenericSend_Unpriv:                         \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_صف_Generic_Send ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_صف_Messages_انتظار( ثابت صف_Handle_t x_صف ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_صف_Messages_انتظار( ثابت صف_Handle_t x_صف ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متطاير
        (
            " .syntax unified                                       \n"
            " .extern MPU_uxQueueMessagesWaitingImpl                \n"
            "                                                       \n"
            " push {r0, r1}                                         \n"
            " mrs r0, control                                       \n"
            " movs r1, #1                                           \n"
            " tst r0, r1                                            \n"
            " pop {r0, r1}                                          \n"
            " bne MPU_uxQueueMessagesWaiting_Unpriv                 \n"
            " MPU_uxQueueMessagesWaiting_Priv:                      \n"
            "     b MPU_uxQueueMessagesWaitingImpl                  \n"
            " MPU_uxQueueMessagesWaiting_Unpriv:                    \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_ux_صف_Messages_انتظار ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_صف_Spaces_موجود( ثابت صف_Handle_t x_صف ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_صف_Spaces_موجود( ثابت صف_Handle_t x_صف ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متطاير
        (
            " .syntax unified                                       \n"
            " .extern MPU_uxQueueSpacesAvailableImpl                \n"
            "                                                       \n"
            " push {r0, r1}                                         \n"
            " mrs r0, control                                       \n"
            " movs r1, #1                                           \n"
            " tst r0, r1                                            \n"
            " pop {r0, r1}                                          \n"
            " bne MPU_uxQueueSpacesAvailable_Unpriv                 \n"
            " MPU_uxQueueSpacesAvailable_Priv:                      \n"
            "     b MPU_uxQueueSpacesAvailableImpl                  \n"
            " MPU_uxQueueSpacesAvailable_Unpriv:                    \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_ux_صف_Spaces_موجود ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Receive( صف_Handle_t x_صف,
                                  فراغ * ثابت pv_میانگیر,
                                  TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    پایه_Type_t MPU_x_صف_Receive( صف_Handle_t x_صف,
                                  فراغ * ثابت pv_میانگیر,
                                  TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متطاير
        (
            " .syntax unified                                       \n"
            " .extern MPU_xQueueReceiveImpl                         \n"
            "                                                       \n"
            " push {r0, r1}                                         \n"
            " mrs r0, control                                       \n"
            " movs r1, #1                                           \n"
            " tst r0, r1                                            \n"
            " pop {r0, r1}                                          \n"
            " bne MPU_xQueueReceive_Unpriv                          \n"
            " MPU_xQueueReceive_Priv:                               \n"
            "     b MPU_xQueueReceiveImpl                           \n"
            " MPU_xQueueReceive_Unpriv:                             \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_صف_Receive ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Peek( صف_Handle_t x_صف,
                               فراغ * ثابت pv_میانگیر,
                               TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    پایه_Type_t MPU_x_صف_Peek( صف_Handle_t x_صف,
                               فراغ * ثابت pv_میانگیر,
                               TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متطاير
        (
            " .syntax unified                                       \n"
            " .extern MPU_xQueuePeekImpl                            \n"
            "                                                       \n"
            " push {r0, r1}                                         \n"
            " mrs r0, control                                       \n"
            " movs r1, #1                                           \n"
            " tst r0, r1                                            \n"
            " pop {r0, r1}                                          \n"
            " bne MPU_xQueuePeek_Unpriv                             \n"
            " MPU_xQueuePeek_Priv:                                  \n"
            "     b MPU_xQueuePeekImpl                              \n"
            " MPU_xQueuePeek_Unpriv:                                \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_صف_Peek ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Semaphore_Take( صف_Handle_t x_صف,
                                        TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    پایه_Type_t MPU_x_صف_Semaphore_Take( صف_Handle_t x_صف,
                                        TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
    {
        __asm متطاير
        (
            " .syntax unified                                       \n"
            " .extern MPU_xQueueSemaphoreTakeImpl                   \n"
            "                                                       \n"
            " push {r0, r1}                                         \n"
            " mrs r0, control                                       \n"
            " movs r1, #1                                           \n"
            " tst r0, r1                                            \n"
            " pop {r0, r1}                                          \n"
            " bne MPU_xQueueSemaphoreTake_Unpriv                    \n"
            " MPU_xQueueSemaphoreTake_Priv:                         \n"
            "     b MPU_xQueueSemaphoreTakeImpl                     \n"
            " MPU_xQueueSemaphoreTake_Unpriv:                       \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_صف_Semaphore_Take ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_صف_Get_Mutex_Holder( صف_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_صف_Get_Mutex_Holder( صف_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xQueueGetMutexHolderImpl                  \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xQueueGetMutexHolder_Unpriv                   \n"
                " MPU_xQueueGetMutexHolder_Priv:                        \n"
                "     b MPU_xQueueGetMutexHolderImpl                    \n"
                " MPU_xQueueGetMutexHolder_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_صف_Get_Mutex_Holder ) : "memory"
            );
        }

    #پایان_اگر /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        پایه_Type_t MPU_x_صف_Take_Mutex_Recursive( صف_Handle_t xMutex,
                                                 TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_صف_Take_Mutex_Recursive( صف_Handle_t xMutex,
                                                 TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xQueueTakeMutexRecursiveImpl              \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xQueueTakeMutexRecursive_Unpriv               \n"
                " MPU_xQueueTakeMutexRecursive_Priv:                    \n"
                "     b MPU_xQueueTakeMutexRecursiveImpl                \n"
                " MPU_xQueueTakeMutexRecursive_Unpriv:                  \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_صف_Take_Mutex_Recursive ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        پایه_Type_t MPU_x_صف_Give_Mutex_Recursive( صف_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_صف_Give_Mutex_Recursive( صف_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xQueueGiveMutexRecursiveImpl              \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xQueueGiveMutexRecursive_Unpriv               \n"
                " MPU_xQueueGiveMutexRecursive_Priv:                    \n"
                "     b MPU_xQueueGiveMutexRecursiveImpl                \n"
                " MPU_xQueueGiveMutexRecursive_Unpriv:                  \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_صف_Give_Mutex_Recursive ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_صف_SETS == 1 )

        صف_مجموعه_Member_Handle_t MPU_x_صف_Select_From_مجموعه( صف_مجموعه_Handle_t x_صف_مجموعه,
                                                        ثابت TickType_t x_Ticks_مقصد_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        صف_مجموعه_Member_Handle_t MPU_x_صف_Select_From_مجموعه( صف_مجموعه_Handle_t x_صف_مجموعه,
                                                        ثابت TickType_t x_Ticks_مقصد_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xQueueSelectFromSetImpl                   \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xQueueSelectFromSet_Unpriv                    \n"
                " MPU_xQueueSelectFromSet_Priv:                         \n"
                "     b MPU_xQueueSelectFromSetImpl                     \n"
                " MPU_xQueueSelectFromSet_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_صف_Select_From_مجموعه ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_صف_SETS == 1 )

        پایه_Type_t MPU_x_صف_جمع_کن_مقصد_مجموعه( صف_مجموعه_Member_Handle_t x_صف_Or_Semaphore,
                                       صف_مجموعه_Handle_t x_صف_مجموعه ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_صف_جمع_کن_مقصد_مجموعه( صف_مجموعه_Member_Handle_t x_صف_Or_Semaphore,
                                       صف_مجموعه_Handle_t x_صف_مجموعه ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xQueueAddToSetImpl                        \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xQueueAddToSet_Unpriv                         \n"
                " MPU_xQueueAddToSet_Priv:                              \n"
                "     b MPU_xQueueAddToSetImpl                          \n"
                " MPU_xQueueAddToSet_Unpriv:                            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_صف_جمع_کن_مقصد_مجموعه ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_صف_REGISTRY_اندازه > 0 )

        فراغ MPU_v_صف_جمع_کن_مقصد_Registry( صف_Handle_t x_صف,
                                      ثابت حرف * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_صف_جمع_کن_مقصد_Registry( صف_Handle_t x_صف,
                                      ثابت حرف * pcName ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_vQueueAddToRegistryImpl                   \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_vQueueAddToRegistry_Unpriv                    \n"
                " MPU_vQueueAddToRegistry_Priv:                         \n"
                "     b MPU_vQueueAddToRegistryImpl                     \n"
                " MPU_vQueueAddToRegistry_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_صف_جمع_کن_مقصد_Registry ) : "memory"
            );
        }

    #پایان_اگر /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_صف_REGISTRY_اندازه > 0 )

        فراغ MPU_v_صف_Unregister_صف( صف_Handle_t x_صف ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_صف_Unregister_صف( صف_Handle_t x_صف ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_vQueueUnregisterQueueImpl                 \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_vQueueUnregisterQueue_Unpriv                  \n"
                " MPU_vQueueUnregisterQueue_Priv:                       \n"
                "     b MPU_vQueueUnregisterQueueImpl                   \n"
                " MPU_vQueueUnregisterQueue_Unpriv:                     \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_صف_Unregister_صف ) : "memory"
            );
        }

    #پایان_اگر /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_صف_REGISTRY_اندازه > 0 )

        ثابت حرف * MPU_pc_صف_Get_Name( صف_Handle_t x_صف ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pc_صف_Get_Name( صف_Handle_t x_صف ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_pcQueueGetNameImpl                        \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_pcQueueGetName_Unpriv                         \n"
                " MPU_pcQueueGetName_Priv:                              \n"
                "     b MPU_pcQueueGetNameImpl                          \n"
                " MPU_pcQueueGetName_Unpriv:                            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pc_صف_Get_Name ) : "memory"
            );
        }

    #پایان_اگر /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_pvTimerGetTimerIDImpl                     \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_pvTimerGetTimerID_Unpriv                      \n"
                " MPU_pvTimerGetTimerID_Priv:                           \n"
                "     b MPU_pvTimerGetTimerIDImpl                       \n"
                " MPU_pvTimerGetTimerID_Unpriv:                         \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pvTimerGetTimerID ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_مجموعه_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Timer_مجموعه_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTimerSetTimerIDImpl                      \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_vTimerSetTimerID_Unpriv                       \n"
                " MPU_vTimerSetTimerID_Priv:                            \n"
                "     b MPU_vTimerSetTimerIDImpl                        \n"
                " MPU_vTimerSetTimerID_Unpriv:                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Timer_مجموعه_Timer_ID ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerIsTimerActiveImpl                   \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTimerIsTimerActive_Unpriv                    \n"
                " MPU_xTimerIsTimerActive_Priv:                         \n"
                "     b MPU_xTimerIsTimerActiveImpl                     \n"
                " MPU_xTimerIsTimerActive_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Timer_Is_Timer_فعال ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerGetTimerDaemonTaskHandleImpl        \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTimerGetTimerDaemonTaskHandle_Unpriv         \n"
                " MPU_xTimerGetTimerDaemonTaskHandle_Priv:              \n"
                "     b MPU_xTimerGetTimerDaemonTaskHandleImpl          \n"
                " MPU_xTimerGetTimerDaemonTaskHandle_Unpriv:            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_x_Timer_Generic_Command_From_Task_مدخل( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_Timer_Generic_Command_From_Task_مدخل( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerGenericCommandFromTaskImpl          \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTimerGenericCommandFromTask_Unpriv           \n"
                " MPU_xTimerGenericCommandFromTask_Priv:                \n"
                "     b MPU_xTimerGenericCommandFromTaskImpl            \n"
                " MPU_xTimerGenericCommandFromTask_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTimerGenericCommandFromTask ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_pcTimerGetNameImpl                        \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_pcTimerGetName_Unpriv                         \n"
                " MPU_pcTimerGetName_Priv:                              \n"
                "     b MPU_pcTimerGetNameImpl                          \n"
                " MPU_pcTimerGetName_Unpriv:                            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pcTimerGetName ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_مجموعه_Reload_نما( TimerHandle_t xTimer,
                                      ثابت پایه_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Timer_مجموعه_Reload_نما( TimerHandle_t xTimer,
                                      ثابت پایه_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_vTimerSetReloadModeImpl                   \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_vTimerSetReloadMode_Unpriv                    \n"
                " MPU_vTimerSetReloadMode_Priv:                         \n"
                "     b MPU_vTimerSetReloadModeImpl                     \n"
                " MPU_vTimerSetReloadMode_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Timer_مجموعه_Reload_نما ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_x_Timer_Get_Reload_نما( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_Timer_Get_Reload_نما( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerGetReloadModeImpl                   \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTimerGetReloadMode_Unpriv                    \n"
                " MPU_xTimerGetReloadMode_Priv:                         \n"
                "     b MPU_xTimerGetReloadModeImpl                     \n"
                " MPU_xTimerGetReloadMode_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Timer_Get_Reload_نما ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_نما( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_نما( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxTimerGetReloadModeImpl                  \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_uxTimerGetReloadMode_Unpriv                   \n"
                " MPU_uxTimerGetReloadMode_Priv:                        \n"
                "     b MPU_uxTimerGetReloadModeImpl                    \n"
                " MPU_uxTimerGetReloadMode_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Timer_Get_Reload_نما ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerGetPeriodImpl                       \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTimerGetPeriod_Unpriv                        \n"
                " MPU_xTimerGetPeriod_Priv:                             \n"
                "     b MPU_xTimerGetPeriodImpl                         \n"
                " MPU_xTimerGetPeriod_Unpriv:                           \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTimerGetPeriod ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_زمان( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_زمان( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xTimerGetExpiryTimeImpl                   \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xTimerGetExpiryTime_Unpriv                    \n"
                " MPU_xTimerGetExpiryTime_Priv:                         \n"
                "     b MPU_xTimerGetExpiryTimeImpl                     \n"
                " MPU_xTimerGetExpiryTime_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Timer_Get_Expiry_زمان ) : "memory"
            );
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_Wait_بیتها_مدخل( ثابت x_Event_گروه_Wait_بیتها_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بیتها_t MPU_x_Event_گروه_Wait_بیتها_مدخل( ثابت x_Event_گروه_Wait_بیتها_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupWaitBitsImpl                   \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xEventGroupWaitBits_Unpriv                    \n"
                " MPU_xEventGroupWaitBits_Priv:                         \n"
                "     b MPU_xEventGroupWaitBitsImpl                     \n"
                " MPU_xEventGroupWaitBits_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_گروه_Wait_بیتها ) : "memory"
            );
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_Clear_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                              ثابت Event_بیتها_t ux_بیتها_مقصد_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بیتها_t MPU_x_Event_گروه_Clear_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                              ثابت Event_بیتها_t ux_بیتها_مقصد_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupClearBitsImpl                  \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xEventGroupClearBits_Unpriv                   \n"
                " MPU_xEventGroupClearBits_Priv:                        \n"
                "     b MPU_xEventGroupClearBitsImpl                    \n"
                " MPU_xEventGroupClearBits_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_گروه_Clear_بیتها ) : "memory"
            );
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_مجموعه_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                            ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        Event_بیتها_t MPU_x_Event_گروه_مجموعه_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                            ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupSetBitsImpl                    \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xEventGroupSetBits_Unpriv                     \n"
                " MPU_xEventGroupSetBits_Priv:                          \n"
                "     b MPU_xEventGroupSetBitsImpl                      \n"
                " MPU_xEventGroupSetBits_Unpriv:                        \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_گروه_مجموعه_بیتها ) : "memory"
            );
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
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xEventGroupSyncImpl                       \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xEventGroupSync_Unpriv                        \n"
                " MPU_xEventGroupSync_Priv:                             \n"
                "     b MPU_xEventGroupSyncImpl                         \n"
                " MPU_xEventGroupSync_Unpriv:                           \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Event_گروه_Sync ) : "memory"
            );
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_گروه_Get_عدد( فراغ * x_Event_گروه ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_گروه_Get_عدد( فراغ * x_Event_گروه ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_uxEventGroupGetNumberImpl                 \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_uxEventGroupGetNumber_Unpriv                  \n"
                " MPU_uxEventGroupGetNumber_Priv:                       \n"
                "     b MPU_uxEventGroupGetNumberImpl                   \n"
                " MPU_uxEventGroupGetNumber_Unpriv:                     \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Event_گروه_Get_عدد ) : "memory"
            );
        }

    #پایان_اگر /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        فراغ MPU_v_Event_گروه_مجموعه_عدد( فراغ * x_Event_گروه,
                                       UBaseType_t ux_Event_گروه_عدد ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Event_گروه_مجموعه_عدد( فراغ * x_Event_گروه,
                                       UBaseType_t ux_Event_گروه_عدد ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_vEventGroupSetNumberImpl                  \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_vEventGroupSetNumber_Unpriv                   \n"
                " MPU_vEventGroupSetNumber_Priv:                        \n"
                "     b MPU_vEventGroupSetNumberImpl                    \n"
                " MPU_vEventGroupSetNumber_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Event_گروه_مجموعه_عدد ) : "memory"
            );
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
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferSendImpl                     \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xStreamBufferSend_Unpriv                      \n"
                " MPU_xStreamBufferSend_Priv:                           \n"
                "     b MPU_xStreamBufferSendImpl                       \n"
                " MPU_xStreamBufferSend_Unpriv:                         \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_جریان_میانگیر_Send ) : "memory"
            );
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
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferReceiveImpl                  \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xStreamBufferReceive_Unpriv                   \n"
                " MPU_xStreamBufferReceive_Priv:                        \n"
                "     b MPU_xStreamBufferReceiveImpl                    \n"
                " MPU_xStreamBufferReceive_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_جریان_میانگیر_Receive ) : "memory"
            );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_Is_پر( جریان_میانگیر_Handle_t x_جریان_میانگیر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_جریان_میانگیر_Is_پر( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferIsFullImpl                   \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xStreamBufferIsFull_Unpriv                    \n"
                " MPU_xStreamBufferIsFull_Priv:                         \n"
                "     b MPU_xStreamBufferIsFullImpl                     \n"
                " MPU_xStreamBufferIsFull_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_جریان_میانگیر_Is_پر ) : "memory"
            );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_Is_خالی( جریان_میانگیر_Handle_t x_جریان_میانگیر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_جریان_میانگیر_Is_خالی( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferIsEmptyImpl                  \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xStreamBufferIsEmpty_Unpriv                   \n"
                " MPU_xStreamBufferIsEmpty_Priv:                        \n"
                "     b MPU_xStreamBufferIsEmptyImpl                    \n"
                " MPU_xStreamBufferIsEmpty_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_جریان_میانگیر_Is_خالی ) : "memory"
            );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_Spaces_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_جریان_میانگیر_Spaces_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferSpacesAvailableImpl          \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xStreamBufferSpacesAvailable_Unpriv           \n"
                " MPU_xStreamBufferSpacesAvailable_Priv:                \n"
                "     b MPU_xStreamBufferSpacesAvailableImpl            \n"
                " MPU_xStreamBufferSpacesAvailable_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_جریان_میانگیر_Spaces_موجود ) : "memory"
            );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_بایتها_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_جریان_میانگیر_بایتها_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferBytesAvailableImpl           \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xStreamBufferBytesAvailable_Unpriv            \n"
                " MPU_xStreamBufferBytesAvailable_Priv:                 \n"
                "     b MPU_xStreamBufferBytesAvailableImpl             \n"
                " MPU_xStreamBufferBytesAvailable_Unpriv:               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_جریان_میانگیر_بایتها_موجود ) : "memory"
            );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_مجموعه_Trigger_Level( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                                     size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        پایه_Type_t MPU_x_جریان_میانگیر_مجموعه_Trigger_Level( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                                     size_t xTriggerLevel ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferSetTriggerLevelImpl          \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xStreamBufferSetTriggerLevel_Unpriv           \n"
                " MPU_xStreamBufferSetTriggerLevel_Priv:                \n"
                "     b MPU_xStreamBufferSetTriggerLevelImpl            \n"
                " MPU_xStreamBufferSetTriggerLevel_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_جریان_میانگیر_مجموعه_Trigger_Level ) : "memory"
            );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها( جریان_میانگیر_Handle_t x_جریان_میانگیر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        size_t MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
        {
            __asm متطاير
            (
                " .syntax unified                                       \n"
                " .extern MPU_xStreamBufferNextMessageLengthBytesImpl   \n"
                "                                                       \n"
                " push {r0, r1}                                         \n"
                " mrs r0, control                                       \n"
                " movs r1, #1                                           \n"
                " tst r0, r1                                            \n"
                " pop {r0, r1}                                          \n"
                " bne MPU_xStreamBufferNextMessageLengthBytes_Unpriv    \n"
                " MPU_xStreamBufferNextMessageLengthBytes_Priv:         \n"
                "     b MPU_xStreamBufferNextMessageLengthBytesImpl     \n"
                " MPU_xStreamBufferNextMessageLengthBytes_Unpriv:       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها ) : "memory"
            );
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

#پایان_اگر /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
