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

#که_نه_تعریف_شوی FREERTOS_CONFIG_H
#تعریف_کړه FREERTOS_CONFIG_H

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

#تعریف_کړه configCPU_CLOCK_HZ    ( ( بینښه اوږد ) 20000000 )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

#تعریف_کړه config_TICK_شرح_HZ                         ( 100U )
#تعریف_کړه configUSE_PREEMPTION                       1
#تعریف_کړه config_USE_وخت_SLICING                     1
#تعریف_کړه config_USE_پورټ_OPTIMISED_TASK_SELECTION    0
#تعریف_کړه configUSE_TICKLESS_IDLE                    1
#تعریف_کړه configMAX_PRIORITIES                       5U
#تعریف_کړه config_اصغري_ډېری_اندازه                   128U
#تعریف_کړه configMAX_TASK_NAME_LEN                    4U
#تعریف_کړه config_TICK_TYPE_پلنوالی_دننه_بټونه              TICK_TYPE_پلنوالی_64_بټونه
#تعریف_کړه configIDLE_SHOULD_YIELD                    1
#تعریف_کړه configTASK_NOTIFICATION_ARRAY_ENTRIES      1U
#تعریف_کړه config_کتار_REGISTRY_اندازه                  0U
#تعریف_کړه configENABLE_BACKWARD_COMPATIBILITY        1
#تعریف_کړه config_عدد_THREAD_LOCAL_STORAGE_اشارې    0
#تعریف_کړه config_ډېری_ژوروالی_TYPE                     size_t
#تعریف_کړه config_پیغام_بفر_اوږدتیا_TYPE           size_t
#تعریف_کړه configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

#تعریف_کړه configUSE_TIMERS                1
#تعریف_کړه config_TIMER_TASK_لومړیتوب       ( configMAX_PRIORITIES - 1U )
#تعریف_کړه config_TIMER_TASK_ډېری_ژوروالی    config_اصغري_ډېری_اندازه
#تعریف_کړه config_TIMER_کتار_اوږدتیا        10U

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

#تعریف_کړه config_SUPPORT_STATIC_ویش              1
#تعریف_کړه config_SUPPORT_DYNAMIC_ویش             1
#تعریف_کړه config_ټول_ډېرۍ_اندازه                        4096U
#تعریف_کړه config_APPLICATION_ALLOCATED_ډېرۍ             1
#تعریف_کړه config_ډېری_ویش_FROM_SEPARATE_ډېرۍ    0
#تعریف_کړه config_USE_MINI_LIST_توکی                     0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

#تعریف_کړه config_KERNEL_مداخله_لومړیتوب          0U
#تعریف_کړه config_MAX_SYSCALL_مداخله_لومړیتوب     0U
#تعریف_کړه config_MAX_API_CALL_مداخله_لومړیتوب    0U

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#تعریف_کړه configUSE_IDLE_HOOK                   0
#تعریف_کړه configUSE_TICK_HOOK                   0
#تعریف_کړه configUSE_MALLOC_FAILED_HOOK          0
#تعریف_کړه configUSE_DAEMON_TASK_STARTUP_HOOK    0
#تعریف_کړه config_CHECK_FOR_ډېری_ډکېدنه        0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#تعریف_کړه config_GENERATE_پرلپسې_وخت_STATS           0
#تعریف_کړه configUSE_TRACE_FACILITY                0
#تعریف_کړه configUSE_STATS_FORMATTING_FUNCTIONS    0
#تعریف_کړه config_KERNEL_PROVIDED_STATIC_حافظه     1

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

#تعریف_کړه configUSE_TASK_NOTIFICATIONS           1
#تعریف_کړه configUSE_MUTEXES                      1
#تعریف_کړه configUSE_RECURSIVE_MUTEXES            1
#تعریف_کړه configUSE_COUNTING_SEMAPHORES          1
#تعریف_کړه config_USE_کتار_SETS                   1
#تعریف_کړه config_USE_APPLICATION_TASK_نښان         1
#تعریف_کړه INCLUDE_v_Task_لومړیتوب_سېټ               1
#تعریف_کړه INCLUDE_ux_Task_لومړیتوب_Get              1
#تعریف_کړه INCLUDE_vTaskDelete                    1
#تعریف_کړه INCLUDE_vTaskSuspend                   1
#تعریف_کړه INCLUDE_vTaskDelayUntil                1
#تعریف_کړه INCLUDE_vTaskDelay                     1
#تعریف_کړه INCLUDE_xTaskGetSchedulerState         1
#تعریف_کړه INCLUDE_xTaskGetCurrentTaskHandle      1
#تعریف_کړه INCLUDE_ux_Task_Get_ډېری_لوړ_Water_Mark    1
#تعریف_کړه INCLUDE_xTaskGetIdleTaskHandle         1
#تعریف_کړه INCLUDE_eTaskGetState                  1
#تعریف_کړه INCLUDE_xTimerPendFunctionCall         1
#تعریف_کړه INCLUDE_xTaskAbortDelay                1
#تعریف_کړه INCLUDE_xTaskGetHandle                 1
#تعریف_کړه INCLUDE_xTaskResumeFromISR             1

#د_که_پای /* FREERTOS_CONFIG_H */
