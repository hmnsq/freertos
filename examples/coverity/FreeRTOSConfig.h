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

#यदि_अपरिभाषितम् FREERTOS_CONFIG_H
#परिभाषय FREERTOS_CONFIG_H

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

#परिभाषय configCPU_CLOCK_HZ    ( ( अचिह्नित दीर्घ ) 20000000 )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

#परिभाषय config_TICK_दरः_HZ                         ( 100U )
#परिभाषय configUSE_PREEMPTION                       1
#परिभाषय configUSE_TIME_SLICING                     1
#परिभाषय config_USE_पत्तनम्_OPTIMISED_TASK_SELECTION    0
#परिभाषय configUSE_TICKLESS_IDLE                    1
#परिभाषय configMAX_PRIORITIES                       5U
#परिभाषय config_अल्पिष्ठम्_राशिः_आकार                   128U
#परिभाषय configMAX_TASK_NAME_LEN                    4U
#परिभाषय config_TICK_TYPE_विस्तारः_अन्तर्_द्वयङ्काः              TICK_TYPE_विस्तारः_64_द्वयङ्काः
#परिभाषय configIDLE_SHOULD_YIELD                    1
#परिभाषय configTASK_NOTIFICATION_ARRAY_ENTRIES      1U
#परिभाषय config_QUEUE_REGISTRY_आकार                  0U
#परिभाषय configENABLE_BACKWARD_COMPATIBILITY        1
#परिभाषय config_अङ्कः_THREAD_LOCAL_STORAGE_सूचकाः    0
#परिभाषय config_राशिः_गभीरता_TYPE                     size_t
#परिभाषय config_सन्देशः_बफर_दीर्घता_TYPE           size_t
#परिभाषय configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

#परिभाषय configUSE_TIMERS                1
#परिभाषय config_TIMER_TASK_प्राथमिकता       ( configMAX_PRIORITIES - 1U )
#परिभाषय config_TIMER_TASK_राशिः_गभीरता    config_अल्पिष्ठम्_राशिः_आकार
#परिभाषय config_TIMER_QUEUE_दीर्घता        10U

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

#परिभाषय config_SUPPORT_STATIC_आवण्टनम्              1
#परिभाषय config_SUPPORT_DYNAMIC_आवण्टनम्             1
#परिभाषय config_योग_HEAP_आकार                        4096U
#परिभाषय configAPPLICATION_ALLOCATED_HEAP             1
#परिभाषय config_राशिः_आवण्टनम्_FROM_SEPARATE_HEAP    0
#परिभाषय configUSE_MINI_LIST_ITEM                     0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

#परिभाषय config_KERNEL_व्यवधानम्_प्राथमिकता          0U
#परिभाषय config_MAX_SYSCALL_व्यवधानम्_प्राथमिकता     0U
#परिभाषय config_MAX_API_CALL_व्यवधानम्_प्राथमिकता    0U

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#परिभाषय configUSE_IDLE_HOOK                   0
#परिभाषय configUSE_TICK_HOOK                   0
#परिभाषय configUSE_MALLOC_FAILED_HOOK          0
#परिभाषय configUSE_DAEMON_TASK_STARTUP_HOOK    0
#परिभाषय config_CHECK_FOR_राशिः_अतिप्रवाहः        0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#परिभाषय config_GENERATE_सततम्_TIME_STATS           0
#परिभाषय configUSE_TRACE_FACILITY                0
#परिभाषय configUSE_STATS_FORMATTING_FUNCTIONS    0
#परिभाषय config_KERNEL_PROVIDED_STATIC_स्मृतिः     1

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

#परिभाषय configUSE_TASK_NOTIFICATIONS           1
#परिभाषय configUSE_MUTEXES                      1
#परिभाषय configUSE_RECURSIVE_MUTEXES            1
#परिभाषय configUSE_COUNTING_SEMAPHORES          1
#परिभाषय configUSE_QUEUE_SETS                   1
#परिभाषय config_USE_APPLICATION_TASK_चिह्नकम्         1
#परिभाषय INCLUDE_v_Task_प्राथमिकता_समुच्चयः               1
#परिभाषय INCLUDE_ux_Task_प्राथमिकता_Get              1
#परिभाषय INCLUDE_vTaskDelete                    1
#परिभाषय INCLUDE_vTaskSuspend                   1
#परिभाषय INCLUDE_vTaskDelayUntil                1
#परिभाषय INCLUDE_vTaskDelay                     1
#परिभाषय INCLUDE_xTaskGetSchedulerState         1
#परिभाषय INCLUDE_xTaskGetCurrentTaskHandle      1
#परिभाषय INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark    1
#परिभाषय INCLUDE_xTaskGetIdleTaskHandle         1
#परिभाषय INCLUDE_eTaskGetState                  1
#परिभाषय INCLUDE_xTimerPendFunctionCall         1
#परिभाषय INCLUDE_xTaskAbortDelay                1
#परिभाषय INCLUDE_xTaskGetHandle                 1
#परिभाषय INCLUDE_xTaskResumeFromISR             1

#यदि_अन्तः /* FREERTOS_CONFIG_H */
