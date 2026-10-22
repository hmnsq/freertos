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
#وصف_ڪريو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"
#ضمن "mpu_syscall_numbers.h"

#وصف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )

        بنياد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_اڳيون_Wake_وقت,
                                        ثابت TickType_t x_وقت_Increment ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_اڳيون_Wake_وقت,
                                        ثابت TickType_t x_وقت_Increment ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTaskDelayUntilImpl                       \n"
                "     pop {pc}                                          \n"
                " MPU_xTaskDelayUntil_Unpriv:                           \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskDelayUntil ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )

        بنياد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTaskAbortDelayImpl                       \n"
                "     pop {pc}                                          \n"
                " MPU_xTaskAbortDelay_Unpriv:                           \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskAbortDelay ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )

        فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskDelay( ثابت TickType_t x_Ticks_منزل_Delay ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_vTaskDelayImpl                            \n"
                "     pop {pc}                                          \n"
                " MPU_vTaskDelay_Unpriv:                                \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskDelay ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_ترجيح_Get == 1 )

        UBaseType_t MPU_ux_Task_ترجيح_Get( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_ترجيح_Get( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_uxTaskPriorityGetImpl                     \n"
                "     pop {pc}                                          \n"
                " MPU_uxTaskPriorityGet_Unpriv:                         \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Task_ترجيح_Get ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
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
                "     push {lr}                                         \n"
                "     blx MPU_eTaskGetStateImpl                         \n"
                "     pop {pc}                                          \n"
                " MPU_eTaskGetState_Unpriv:                             \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_eTaskGetState ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               بنياد_Type_t x_Get_Free_ڍير_Space,
                               eTaskState eState ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               بنياد_Type_t x_Get_Free_ڍير_Space,
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
                "     push {lr}                                         \n"
                "     blx MPU_vTaskGetInfoImpl                          \n"
                "     pop {pc}                                          \n"
                " MPU_vTaskGetInfo_Unpriv:                              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskGetInfo ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TRACE_FACILITY == 1 ) */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTaskGetIdleTaskHandleImpl                \n"
                "     pop {pc}                                          \n"
                " MPU_xTaskGetIdleTaskHandle_Unpriv:                    \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGetIdleTaskHandle ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_منزل_Suspend ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskSuspend( TaskHandle_t x_Task_منزل_Suspend ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_vTaskSuspendImpl                          \n"
                "     pop {pc}                                          \n"
                " MPU_vTaskSuspend_Unpriv:                              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskSuspend ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskResume( TaskHandle_t x_Task_منزل_Resume ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_vTaskResume( TaskHandle_t x_Task_منزل_Resume ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_vTaskResumeImpl                           \n"
                "     pop {pc}                                          \n"
                " MPU_vTaskResume_Unpriv:                               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_vTaskResume ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ڳڻپ( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    TickType_t MPU_x_Task_Get_Tick_ڳڻپ( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xTaskGetTickCountImpl                     \n"
            "     pop {pc}                                          \n"
            " MPU_xTaskGetTickCount_Unpriv:                         \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_Task_Get_Tick_ڳڻپ ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_عدد_جو_Tasks( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_Task_Get_عدد_جو_Tasks( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_uxTaskGetNumberOfTasksImpl                \n"
            "     pop {pc}                                          \n"
            " MPU_uxTaskGetNumberOfTasks_Unpriv:                    \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_ux_Task_Get_عدد_جو_Tasks ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_لاڳيتو_وقت_STATS == 1 )

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Counter( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Counter( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_ulTaskGetRunTimeCounterImpl               \n"
                "     pop {pc}                                          \n"
                " MPU_ulTaskGetRunTimeCounter_Unpriv:                   \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_لاڳيتو_وقت_Counter ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_لاڳيتو_وقت_STATS == 1 )

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Percent( ثابت TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Percent( ثابت TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_ulTaskGetRunTimePercentImpl               \n"
                "     pop {pc}                                          \n"
                " MPU_ulTaskGetRunTimePercent_Unpriv:                   \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_لاڳيتو_وقت_Percent ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لاڳيتو_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_ulTaskGetIdleRunTimePercentImpl           \n"
                "     pop {pc}                                          \n"
                " MPU_ulTaskGetIdleRunTimePercent_Unpriv:               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_لاڳيتو_وقت_Percent ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لاڳيتو_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_ulTaskGetIdleRunTimeCounterImpl           \n"
                "     pop {pc}                                          \n"
                " MPU_ulTaskGetIdleRunTimeCounter_Unpriv:               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Get_Idle_لاڳيتو_وقت_Counter ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )

        فراغ MPU_v_Task_سيٽ_Application_Task_ٽيگ( TaskHandle_t xTask,
                                             TaskHookFunction_t pxHookFunction ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Task_سيٽ_Application_Task_ٽيگ( TaskHandle_t xTask,
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
                "     push {lr}                                         \n"
                "     blx MPU_vTaskSetApplicationTaskTagImpl            \n"
                "     pop {pc}                                          \n"
                " MPU_vTaskSetApplicationTaskTag_Unpriv:                \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Task_سيٽ_Application_Task_ٽيگ ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٽيگ( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٽيگ( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTaskGetApplicationTaskTagImpl            \n"
                "     pop {pc}                                          \n"
                " MPU_xTaskGetApplicationTaskTag_Unpriv:                \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Task_Get_Application_Task_ٽيگ ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_انگ_THREAD_LOCAL_STORAGE_اشارا != 0 )

        فراغ MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو( TaskHandle_t x_Task_منزل_سيٽ,
                                                    بنياد_Type_t x_اشاريو,
                                                    فراغ * pv_قدر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو( TaskHandle_t x_Task_منزل_سيٽ,
                                                    بنياد_Type_t x_اشاريو,
                                                    فراغ * pv_قدر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_vTaskSetThreadLocalStoragePointerImpl     \n"
                "     pop {pc}                                          \n"
                " MPU_vTaskSetThreadLocalStoragePointer_Unpriv:         \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Task_سيٽ_Thread_Local_Storage_اشارو ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_انگ_THREAD_LOCAL_STORAGE_اشارا != 0 )

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارو( TaskHandle_t x_Task_منزل_Query,
                                                       بنياد_Type_t x_اشاريو ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارو( TaskHandle_t x_Task_منزل_Query,
                                                       بنياد_Type_t x_اشاريو ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_pvTaskGetThreadLocalStoragePointerImpl    \n"
                "     pop {pc}                                          \n"
                " MPU_pvTaskGetThreadLocalStoragePointer_Unpriv:        \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pv_Task_Get_Thread_Local_Storage_اشارو ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                              ثابت UBaseType_t ux_Array_سائيز,
                                              config_لاڳيتو_وقت_COUNTER_TYPE * ثابت pul_ڪل_لاڳيتو_وقت ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * ثابت px_Task_حالت_Array,
                                              ثابت UBaseType_t ux_Array_سائيز,
                                              config_لاڳيتو_وقت_COUNTER_TYPE * ثابت pul_ڪل_لاڳيتو_وقت ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_uxTaskGetSystemStateImpl                  \n"
                "     pop {pc}                                          \n"
                " MPU_uxTaskGetSystemState_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_uxTaskGetSystemState ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڍير_مٿاهون_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_uxTaskGetStackHighWaterMarkImpl           \n"
                "     pop {pc}                                          \n"
                " MPU_uxTaskGetStackHighWaterMark_Unpriv:               \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Task_Get_ڍير_مٿاهون_Water_Mark ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڍير_مٿاهون_Water_Mark2 == 1 )

        config_ڍير_اونهائي_TYPE MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2( TaskHandle_t xTask ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        config_ڍير_اونهائي_TYPE MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2( TaskHandle_t xTask ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_uxTaskGetStackHighWaterMark2Impl          \n"
                "     pop {pc}                                          \n"
                " MPU_uxTaskGetStackHighWaterMark2_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Task_Get_ڍير_مٿاهون_Water_Mark2 ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTaskGetCurrentTaskHandleImpl             \n"
                "     pop {pc}                                          \n"
                " MPU_xTaskGetCurrentTaskHandle_Unpriv:                 \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGetCurrentTaskHandle ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

        بنياد_Type_t MPU_xTaskGetSchedulerState( فراغ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTaskGetSchedulerStateImpl                \n"
                "     pop {pc}                                          \n"
                " MPU_xTaskGetSchedulerState_Unpriv:                    \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGetSchedulerState ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_سيٽ_وقت_ٻاهريون_State( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    فراغ MPU_v_Task_سيٽ_وقت_ٻاهريون_State( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_vTaskSetTimeOutStateImpl                  \n"
            "     pop {pc}                                          \n"
            " MPU_vTaskSetTimeOutState_Unpriv:                      \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_v_Task_سيٽ_وقت_ٻاهريون_State ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_Task_Check_For_وقت_ٻاهريون( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون,
                                         TickType_t * ثابت px_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنياد_Type_t MPU_x_Task_Check_For_وقت_ٻاهريون( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون,
                                         TickType_t * ثابت px_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xTaskCheckForTimeOutImpl                  \n"
            "     pop {pc}                                          \n"
            " MPU_xTaskCheckForTimeOut_Unpriv:                      \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_Task_Check_For_وقت_ٻاهريون ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنياد_Type_t MPU_x_Task_Generic_Notify_داخلا( ثابت xTaskGenericNotifyParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_x_Task_Generic_Notify_داخلا( ثابت xTaskGenericNotifyParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTaskGenericNotifyImpl                    \n"
                "     pop {pc}                                          \n"
                " MPU_xTaskGenericNotify_Unpriv:                        \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGenericNotify ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنياد_Type_t MPU_x_Task_Generic_Notify_Wait_داخلا( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_x_Task_Generic_Notify_Wait_داخلا( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTaskGenericNotifyWaitImpl                \n"
                "     pop {pc}                                          \n"
                " MPU_xTaskGenericNotifyWait_Unpriv:                    \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGenericNotifyWait ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاريو_منزل_Wait_On,
                                              بنياد_Type_t x_Clear_ڳڻپ_On_Exit,
                                              TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاريو_منزل_Wait_On,
                                              بنياد_Type_t x_Clear_ڳڻپ_On_Exit,
                                              TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_ulTaskGenericNotifyTakeImpl               \n"
                "     pop {pc}                                          \n"
                " MPU_ulTaskGenericNotifyTake_Unpriv:                   \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ulTaskGenericNotifyTake ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنياد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_اشاريو_منزل_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_اشاريو_منزل_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTaskGenericNotifyStateClearImpl          \n"
                "     pop {pc}                                          \n"
                " MPU_xTaskGenericNotifyStateClear_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTaskGenericNotifyStateClear ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_اشاريو_منزل_Clear,
                                                    uint32_t ul_بٽ_منزل_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_اشاريو_منزل_Clear,
                                                    uint32_t ul_بٽ_منزل_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_ulTaskGenericNotifyValueClearImpl         \n"
                "     pop {pc}                                          \n"
                " MPU_ulTaskGenericNotifyValueClear_Unpriv:             \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ul_Task_Generic_Notify_قدر_Clear ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                      ثابت فراغ * ثابت pv_شي_منزل_قطار,
                                      TickType_t x_Ticks_منزل_Wait,
                                      ثابت بنياد_Type_t xCopyPosition ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنياد_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                      ثابت فراغ * ثابت pv_شي_منزل_قطار,
                                      TickType_t x_Ticks_منزل_Wait,
                                      ثابت بنياد_Type_t xCopyPosition ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xQueueGenericSendImpl                     \n"
            "     pop {pc}                                          \n"
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
            "     push {lr}                                         \n"
            "     blx MPU_uxQueueMessagesWaitingImpl                \n"
            "     pop {pc}                                          \n"
            " MPU_uxQueueMessagesWaiting_Unpriv:                    \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_ux_قطار_Messages_انتظار ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Spaces_موجود( ثابت قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    UBaseType_t MPU_ux_قطار_Spaces_موجود( ثابت قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_uxQueueSpacesAvailableImpl                \n"
            "     pop {pc}                                          \n"
            " MPU_uxQueueSpacesAvailable_Unpriv:                    \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_ux_قطار_Spaces_موجود ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                                  فراغ * ثابت pv_بفر,
                                  TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنياد_Type_t MPU_x_قطار_Receive( قطار_Handle_t x_قطار,
                                  فراغ * ثابت pv_بفر,
                                  TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xQueueReceiveImpl                         \n"
            "     pop {pc}                                          \n"
            " MPU_xQueueReceive_Unpriv:                             \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_قطار_Receive ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                               فراغ * ثابت pv_بفر,
                               TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنياد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                               فراغ * ثابت pv_بفر,
                               TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xQueuePeekImpl                            \n"
            "     pop {pc}                                          \n"
            " MPU_xQueuePeek_Unpriv:                                \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_قطار_Peek ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                        TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنياد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                        TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xQueueSemaphoreTakeImpl                   \n"
            "     pop {pc}                                          \n"
            " MPU_xQueueSemaphoreTake_Unpriv:                       \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_قطار_Semaphore_Take ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xQueueGetMutexHolderImpl                  \n"
                "     pop {pc}                                          \n"
                " MPU_xQueueGetMutexHolder_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_قطار_Get_Mutex_Holder ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنياد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                                 TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                                 TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xQueueTakeMutexRecursiveImpl              \n"
                "     pop {pc}                                          \n"
                " MPU_xQueueTakeMutexRecursive_Unpriv:                  \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_قطار_Take_Mutex_Recursive ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنياد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t pxMutex ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xQueueGiveMutexRecursiveImpl              \n"
                "     pop {pc}                                          \n"
                " MPU_xQueueGiveMutexRecursive_Unpriv:                  \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_قطار_Give_Mutex_Recursive ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        قطار_سيٽ_Member_Handle_t MPU_x_قطار_Select_From_سيٽ( قطار_سيٽ_Handle_t x_قطار_سيٽ,
                                                        ثابت TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        قطار_سيٽ_Member_Handle_t MPU_x_قطار_Select_From_سيٽ( قطار_سيٽ_Handle_t x_قطار_سيٽ,
                                                        ثابت TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xQueueSelectFromSetImpl                   \n"
                "     pop {pc}                                          \n"
                " MPU_xQueueSelectFromSet_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_قطار_Select_From_سيٽ ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        بنياد_Type_t MPU_x_قطار_جوڙيو_منزل_سيٽ( قطار_سيٽ_Member_Handle_t x_قطار_Or_Semaphore,
                                       قطار_سيٽ_Handle_t x_قطار_سيٽ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_x_قطار_جوڙيو_منزل_سيٽ( قطار_سيٽ_Member_Handle_t x_قطار_Or_Semaphore,
                                       قطار_سيٽ_Handle_t x_قطار_سيٽ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xQueueAddToSetImpl                        \n"
                "     pop {pc}                                          \n"
                " MPU_xQueueAddToSet_Unpriv:                            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_قطار_جوڙيو_منزل_سيٽ ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_قطار_REGISTRY_سائيز > 0 )

        فراغ MPU_v_قطار_جوڙيو_منزل_Registry( قطار_Handle_t x_قطار,
                                      ثابت حرف * pcName ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_قطار_جوڙيو_منزل_Registry( قطار_Handle_t x_قطار,
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
                "     push {lr}                                         \n"
                "     blx MPU_vQueueAddToRegistryImpl                   \n"
                "     pop {pc}                                          \n"
                " MPU_vQueueAddToRegistry_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_قطار_جوڙيو_منزل_Registry ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_قطار_REGISTRY_سائيز > 0 )

        فراغ MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_vQueueUnregisterQueueImpl                 \n"
                "     pop {pc}                                          \n"
                " MPU_vQueueUnregisterQueue_Unpriv:                     \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_قطار_Unregister_قطار ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_قطار_REGISTRY_سائيز > 0 )

        ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_pcQueueGetNameImpl                        \n"
                "     pop {pc}                                          \n"
                " MPU_pcQueueGetName_Unpriv:                            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pc_قطار_Get_Name ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configQUEUE_REGISTRY_SIZE > 0 ) */
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
                "     push {lr}                                         \n"
                "     blx MPU_pvTimerGetTimerIDImpl                     \n"
                "     pop {pc}                                          \n"
                " MPU_pvTimerGetTimerID_Unpriv:                         \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pvTimerGetTimerID ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سيٽ_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Timer_سيٽ_Timer_ID( TimerHandle_t xTimer,
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
                "     push {lr}                                         \n"
                "     blx MPU_vTimerSetTimerIDImpl                      \n"
                "     pop {pc}                                          \n"
                " MPU_vTimerSetTimerID_Unpriv:                          \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Timer_سيٽ_Timer_ID ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنياد_Type_t MPU_x_Timer_Is_Timer_سرگرم( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_x_Timer_Is_Timer_سرگرم( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTimerIsTimerActiveImpl                   \n"
                "     pop {pc}                                          \n"
                " MPU_xTimerIsTimerActive_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Timer_Is_Timer_سرگرم ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTimerGetTimerDaemonTaskHandleImpl        \n"
                "     pop {pc}                                          \n"
                " MPU_xTimerGetTimerDaemonTaskHandle_Unpriv:            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنياد_Type_t MPU_x_Timer_Generic_Command_From_Task_داخلا( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_x_Timer_Generic_Command_From_Task_داخلا( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTimerGenericCommandFromTaskImpl          \n"
                "     pop {pc}                                          \n"
                " MPU_xTimerGenericCommandFromTask_Unpriv:              \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTimerGenericCommandFromTask ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
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
                "     push {lr}                                         \n"
                "     blx MPU_pcTimerGetNameImpl                        \n"
                "     pop {pc}                                          \n"
                " MPU_pcTimerGetName_Unpriv:                            \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_pcTimerGetName ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سيٽ_Reload_گهڻائي( TimerHandle_t xTimer,
                                      ثابت بنياد_Type_t xAutoReload ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Timer_سيٽ_Reload_گهڻائي( TimerHandle_t xTimer,
                                      ثابت بنياد_Type_t xAutoReload ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_vTimerSetReloadModeImpl                   \n"
                "     pop {pc}                                          \n"
                " MPU_vTimerSetReloadMode_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Timer_سيٽ_Reload_گهڻائي ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنياد_Type_t MPU_x_Timer_Get_Reload_گهڻائي( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        بنياد_Type_t MPU_x_Timer_Get_Reload_گهڻائي( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTimerGetReloadModeImpl                   \n"
                "     pop {pc}                                          \n"
                " MPU_xTimerGetReloadMode_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Timer_Get_Reload_گهڻائي ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_گهڻائي( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Timer_Get_Reload_گهڻائي( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_uxTimerGetReloadModeImpl                  \n"
                "     pop {pc}                                          \n"
                " MPU_uxTimerGetReloadMode_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Timer_Get_Reload_گهڻائي ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTimerGetPeriodImpl                       \n"
                "     pop {pc}                                          \n"
                " MPU_xTimerGetPeriod_Unpriv:                           \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_xTimerGetPeriod ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_xTimerGetExpiryTimeImpl                   \n"
                "     pop {pc}                                          \n"
                " MPU_xTimerGetExpiryTime_Unpriv:                       \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_x_Timer_Get_Expiry_وقت ) : "memory"
            );
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    Event_بٽ_t MPU_x_Event_گروهه_Wait_بٽ_داخلا( ثابت x_Event_گروهه_Wait_بٽ_Params_t * pxParams ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    Event_بٽ_t MPU_x_Event_گروهه_Wait_بٽ_داخلا( ثابت x_Event_گروهه_Wait_بٽ_Params_t * pxParams ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xEventGroupWaitBitsImpl                   \n"
            "     pop {pc}                                          \n"
            " MPU_xEventGroupWaitBits_Unpriv:                       \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_Event_گروهه_Wait_بٽ ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    Event_بٽ_t MPU_x_Event_گروهه_Clear_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                          ثابت Event_بٽ_t ux_بٽ_منزل_Clear ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    Event_بٽ_t MPU_x_Event_گروهه_Clear_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                          ثابت Event_بٽ_t ux_بٽ_منزل_Clear ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xEventGroupClearBitsImpl                  \n"
            "     pop {pc}                                          \n"
            " MPU_xEventGroupClearBits_Unpriv:                      \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_Event_گروهه_Clear_بٽ ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    Event_بٽ_t MPU_x_Event_گروهه_سيٽ_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                        ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    Event_بٽ_t MPU_x_Event_گروهه_سيٽ_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                        ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xEventGroupSetBitsImpl                    \n"
            "     pop {pc}                                          \n"
            " MPU_xEventGroupSetBits_Unpriv:                        \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_Event_گروهه_سيٽ_بٽ ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    Event_بٽ_t MPU_x_Event_گروهه_Sync( Event_گروهه_Handle_t x_Event_گروهه,
                                     ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ,
                                     ثابت Event_بٽ_t ux_بٽ_منزل_Wait_For,
                                     TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    Event_بٽ_t MPU_x_Event_گروهه_Sync( Event_گروهه_Handle_t x_Event_گروهه,
                                     ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ,
                                     ثابت Event_بٽ_t ux_بٽ_منزل_Wait_For,
                                     TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xEventGroupSyncImpl                       \n"
            "     pop {pc}                                          \n"
            " MPU_xEventGroupSync_Unpriv:                           \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_Event_گروهه_Sync ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_ux_Event_گروهه_Get_عدد( فراغ * x_Event_گروهه ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        UBaseType_t MPU_ux_Event_گروهه_Get_عدد( فراغ * x_Event_گروهه ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_uxEventGroupGetNumberImpl                 \n"
                "     pop {pc}                                          \n"
                " MPU_uxEventGroupGetNumber_Unpriv:                     \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_ux_Event_گروهه_Get_عدد ) : "memory"
            );
        }

    #جيڪڏهن_پورو /*( configUSE_TRACE_FACILITY == 1 )*/
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        فراغ MPU_v_Event_گروهه_سيٽ_عدد( فراغ * x_Event_گروهه,
                                       UBaseType_t ux_Event_گروهه_عدد ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

        فراغ MPU_v_Event_گروهه_سيٽ_عدد( فراغ * x_Event_گروهه,
                                       UBaseType_t ux_Event_گروهه_عدد ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
                "     push {lr}                                         \n"
                "     blx MPU_vEventGroupSetNumberImpl                  \n"
                "     pop {pc}                                          \n"
                " MPU_vEventGroupSetNumber_Unpriv:                      \n"
                "     svc %0                                            \n"
                "                                                       \n"
                : : "i" ( SYSTEM_CALL_v_Event_گروهه_سيٽ_عدد ) : "memory"
            );
        }

    #جيڪڏهن_پورو /*( configUSE_TRACE_FACILITY == 1 )*/
/*-----------------------------------------------------------*/

    size_t MPU_x_وهڪرو_بفر_Send( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                  ثابت فراغ * pv_Tx_معلومات,
                                  size_t x_معلومات_ڊيگهائي_بائيٽون,
                                  TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    size_t MPU_x_وهڪرو_بفر_Send( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                  ثابت فراغ * pv_Tx_معلومات,
                                  size_t x_معلومات_ڊيگهائي_بائيٽون,
                                  TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xStreamBufferSendImpl                     \n"
            "     pop {pc}                                          \n"
            " MPU_xStreamBufferSend_Unpriv:                         \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_وهڪرو_بفر_Send ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    size_t MPU_x_وهڪرو_بفر_Receive( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                     فراغ * pv_Rx_معلومات,
                                     size_t x_بفر_ڊيگهائي_بائيٽون,
                                     TickType_t x_Ticks_منزل_Wait ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    size_t MPU_x_وهڪرو_بفر_Receive( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                     فراغ * pv_Rx_معلومات,
                                     size_t x_بفر_ڊيگهائي_بائيٽون,
                                     TickType_t x_Ticks_منزل_Wait ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xStreamBufferReceiveImpl                  \n"
            "     pop {pc}                                          \n"
            " MPU_xStreamBufferReceive_Unpriv:                      \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_وهڪرو_بفر_Receive ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_وهڪرو_بفر_Is_ڀريل( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنياد_Type_t MPU_x_وهڪرو_بفر_Is_ڀريل( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xStreamBufferIsFullImpl                   \n"
            "     pop {pc}                                          \n"
            " MPU_xStreamBufferIsFull_Unpriv:                       \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_وهڪرو_بفر_Is_ڀريل ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_وهڪرو_بفر_Is_خالي_جايون( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنياد_Type_t MPU_x_وهڪرو_بفر_Is_خالي_جايون( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xStreamBufferIsEmptyImpl                  \n"
            "     pop {pc}                                          \n"
            " MPU_xStreamBufferIsEmpty_Unpriv:                      \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_وهڪرو_بفر_Is_خالي_جايون ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    size_t MPU_x_وهڪرو_بفر_Spaces_موجود( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    size_t MPU_x_وهڪرو_بفر_Spaces_موجود( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xStreamBufferSpacesAvailableImpl          \n"
            "     pop {pc}                                          \n"
            " MPU_xStreamBufferSpacesAvailable_Unpriv:              \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_وهڪرو_بفر_Spaces_موجود ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    size_t MPU_x_وهڪرو_بفر_بائيٽون_موجود( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    size_t MPU_x_وهڪرو_بفر_بائيٽون_موجود( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xStreamBufferBytesAvailableImpl           \n"
            "     pop {pc}                                          \n"
            " MPU_xStreamBufferBytesAvailable_Unpriv:               \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_وهڪرو_بفر_بائيٽون_موجود ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                                 size_t xTriggerLevel ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    بنياد_Type_t MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
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
            "     push {lr}                                         \n"
            "     blx MPU_xStreamBufferSetTriggerLevelImpl          \n"
            "     pop {pc}                                          \n"
            " MPU_xStreamBufferSetTriggerLevel_Unpriv:              \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_وهڪرو_بفر_سيٽ_Trigger_Level ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

    size_t MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) __attribute__( ( naked ) ) FREERTOS_SYSTEM_CALL;

    size_t MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* __attribute__ (( naked )) FREERTOS_SYSTEM_CALL */
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
            "     push {lr}                                         \n"
            "     blx MPU_xStreamBufferNextMessageLengthBytesImpl   \n"
            "     pop {pc}                                          \n"
            " MPU_xStreamBufferNextMessageLengthBytes_Unpriv:       \n"
            "     svc %0                                            \n"
            "                                                       \n"
            : : "i" ( SYSTEM_CALL_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون ) : "memory"
        );
    }
/*-----------------------------------------------------------*/

#جيڪڏهن_پورو /* ( configENABLE_MPU == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) */
