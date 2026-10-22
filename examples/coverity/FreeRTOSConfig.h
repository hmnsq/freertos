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

#अगर_अघोषित FREERTOS_CONFIG_H
#घोषणा FREERTOS_CONFIG_H

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

#घोषणा configCPU_CLOCK_HZ    ( ( अचिन्हित दीर्घ ) 20000000 )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

#घोषणा configTICK_RATE_HZ                         ( 100U )
#घोषणा configUSE_PREEMPTION                       1
#घोषणा configUSE_TIME_SLICING                     1
#घोषणा configUSE_PORT_OPTIMISED_TASK_SELECTION    0
#घोषणा configUSE_TICKLESS_IDLE                    1
#घोषणा configMAX_PRIORITIES                       5U
#घोषणा config_MINIMAL_ढेर_आकार                   128U
#घोषणा configMAX_TASK_NAME_LEN                    4U
#घोषणा configTICK_TYPE_WIDTH_IN_BITS              TICK_TYPE_WIDTH_64_BITS
#घोषणा configIDLE_SHOULD_YIELD                    1
#घोषणा configTASK_NOTIFICATION_ARRAY_ENTRIES      1U
#घोषणा config_QUEUE_REGISTRY_आकार                  0U
#घोषणा configENABLE_BACKWARD_COMPATIBILITY        1
#घोषणा config_अंक_THREAD_LOCAL_STORAGE_POINTERS    0
#घोषणा config_ढेर_DEPTH_TYPE                     माप_प्रकार
#घोषणा config_MESSAGE_बफर_लंबाई_TYPE           माप_प्रकार
#घोषणा configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

#घोषणा configUSE_TIMERS                1
#घोषणा configTIMER_TASK_PRIORITY       ( configMAX_PRIORITIES - 1U )
#घोषणा config_TIMER_TASK_ढेर_DEPTH    config_MINIMAL_ढेर_आकार
#घोषणा config_TIMER_QUEUE_लंबाई        10U

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

#घोषणा configSUPPORT_STATIC_ALLOCATION              1
#घोषणा configSUPPORT_DYNAMIC_ALLOCATION             1
#घोषणा config_योग_HEAP_आकार                        4096U
#घोषणा configAPPLICATION_ALLOCATED_HEAP             1
#घोषणा config_ढेर_ALLOCATION_FROM_SEPARATE_HEAP    0
#घोषणा configUSE_MINI_LIST_ITEM                     0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

#घोषणा configKERNEL_INTERRUPT_PRIORITY          0U
#घोषणा configMAX_SYSCALL_INTERRUPT_PRIORITY     0U
#घोषणा configMAX_API_CALL_INTERRUPT_PRIORITY    0U

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#घोषणा configUSE_IDLE_HOOK                   0
#घोषणा configUSE_TICK_HOOK                   0
#घोषणा configUSE_MALLOC_FAILED_HOOK          0
#घोषणा configUSE_DAEMON_TASK_STARTUP_HOOK    0
#घोषणा config_CHECK_FOR_ढेर_OVERFLOW        0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#घोषणा configGENERATE_RUN_TIME_STATS           0
#घोषणा configUSE_TRACE_FACILITY                0
#घोषणा configUSE_STATS_FORMATTING_FUNCTIONS    0
#घोषणा configKERNEL_PROVIDED_STATIC_MEMORY     1

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

#घोषणा configUSE_TASK_NOTIFICATIONS           1
#घोषणा configUSE_MUTEXES                      1
#घोषणा configUSE_RECURSIVE_MUTEXES            1
#घोषणा configUSE_COUNTING_SEMAPHORES          1
#घोषणा configUSE_QUEUE_SETS                   1
#घोषणा configUSE_APPLICATION_TASK_TAG         1
#घोषणा INCLUDE_vTaskPrioritySet               1
#घोषणा INCLUDE_uxTaskPriorityGet              1
#घोषणा INCLUDE_vTaskDelete                    1
#घोषणा INCLUDE_vTaskSuspend                   1
#घोषणा INCLUDE_vTaskDelayUntil                1
#घोषणा INCLUDE_vTaskDelay                     1
#घोषणा INCLUDE_xTaskGetSchedulerState         1
#घोषणा INCLUDE_xTaskGetCurrentTaskHandle      1
#घोषणा INCLUDE_ux_Task_Get_ढेर_ऊपरी_Water_Mark    1
#घोषणा INCLUDE_xTaskGetIdleTaskHandle         1
#घोषणा INCLUDE_eTaskGetState                  1
#घोषणा INCLUDE_xTimerPendFunctionCall         1
#घोषणा INCLUDE_xTaskAbortDelay                1
#घोषणा INCLUDE_xTaskGetHandle                 1
#घोषणा INCLUDE_xTaskResumeFromISR             1

#पूर्ण_अगर /* FREERTOS_CONFIG_H */
