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

#اگر_تعریف_نشده FREERTOS_CONFIG_H
#تعریف_کن FREERTOS_CONFIG_H

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

#تعریف_کن configCPU_CLOCK_HZ    ( ( بیعلامت دراز ) 20000000 )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

#تعریف_کن config_TICK_نرخ_HZ                         ( 100U )
#تعریف_کن configUSE_PREEMPTION                       1
#تعریف_کن config_USE_زمان_SLICING                     1
#تعریف_کن config_USE_پورت_OPTIMISED_TASK_SELECTION    0
#تعریف_کن configUSE_TICKLESS_IDLE                    1
#تعریف_کن configMAX_PRIORITIES                       5U
#تعریف_کن config_کمینه_پشته_اندازه                   128U
#تعریف_کن configMAX_TASK_NAME_LEN                    4U
#تعریف_کن config_TICK_TYPE_عرض_درون_بیتها              TICK_TYPE_عرض_64_بیتها
#تعریف_کن configIDLE_SHOULD_YIELD                    1
#تعریف_کن configTASK_NOTIFICATION_ARRAY_ENTRIES      1U
#تعریف_کن config_صف_REGISTRY_اندازه                  0U
#تعریف_کن configENABLE_BACKWARD_COMPATIBILITY        1
#تعریف_کن config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها    0
#تعریف_کن config_پشته_عمق_TYPE                     size_t
#تعریف_کن config_پیام_میانگیر_درازی_TYPE           size_t
#تعریف_کن configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

#تعریف_کن configUSE_TIMERS                1
#تعریف_کن config_TIMER_TASK_اولویت       ( configMAX_PRIORITIES - 1U )
#تعریف_کن config_TIMER_TASK_پشته_عمق    config_کمینه_پشته_اندازه
#تعریف_کن config_TIMER_صف_درازی        10U

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

#تعریف_کن config_SUPPORT_STATIC_تخصیص              1
#تعریف_کن config_SUPPORT_DYNAMIC_تخصیص             1
#تعریف_کن config_مجموع_انباشته_اندازه                        4096U
#تعریف_کن config_APPLICATION_ALLOCATED_انباشته             1
#تعریف_کن config_پشته_تخصیص_FROM_SEPARATE_انباشته    0
#تعریف_کن config_USE_MINI_LIST_قلم                     0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

#تعریف_کن config_KERNEL_وقفه_اولویت          0U
#تعریف_کن config_MAX_SYSCALL_وقفه_اولویت     0U
#تعریف_کن config_MAX_API_CALL_وقفه_اولویت    0U

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#تعریف_کن configUSE_IDLE_HOOK                   0
#تعریف_کن configUSE_TICK_HOOK                   0
#تعریف_کن configUSE_MALLOC_FAILED_HOOK          0
#تعریف_کن configUSE_DAEMON_TASK_STARTUP_HOOK    0
#تعریف_کن config_CHECK_FOR_پشته_سرریز        0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#تعریف_کن config_GENERATE_پیاپی_زمان_STATS           0
#تعریف_کن configUSE_TRACE_FACILITY                0
#تعریف_کن configUSE_STATS_FORMATTING_FUNCTIONS    0
#تعریف_کن config_KERNEL_PROVIDED_STATIC_حافظه     1

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

#تعریف_کن configUSE_TASK_NOTIFICATIONS           1
#تعریف_کن configUSE_MUTEXES                      1
#تعریف_کن configUSE_RECURSIVE_MUTEXES            1
#تعریف_کن configUSE_COUNTING_SEMAPHORES          1
#تعریف_کن config_USE_صف_SETS                   1
#تعریف_کن config_USE_APPLICATION_TASK_برچسب         1
#تعریف_کن INCLUDE_v_Task_اولویت_مجموعه               1
#تعریف_کن INCLUDE_ux_Task_اولویت_Get              1
#تعریف_کن INCLUDE_vTaskDelete                    1
#تعریف_کن INCLUDE_vTaskSuspend                   1
#تعریف_کن INCLUDE_vTaskDelayUntil                1
#تعریف_کن INCLUDE_vTaskDelay                     1
#تعریف_کن INCLUDE_xTaskGetSchedulerState         1
#تعریف_کن INCLUDE_xTaskGetCurrentTaskHandle      1
#تعریف_کن INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark    1
#تعریف_کن INCLUDE_xTaskGetIdleTaskHandle         1
#تعریف_کن INCLUDE_eTaskGetState                  1
#تعریف_کن INCLUDE_xTimerPendFunctionCall         1
#تعریف_کن INCLUDE_xTaskAbortDelay                1
#تعریف_کن INCLUDE_xTaskGetHandle                 1
#تعریف_کن INCLUDE_xTaskResumeFromISR             1

#پایان_اگر /* FREERTOS_CONFIG_H */
