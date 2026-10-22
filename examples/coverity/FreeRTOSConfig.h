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

#جے_بنا_تعریف FREERTOS_CONFIG_H
#تعریف_کرو FREERTOS_CONFIG_H

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

#تعریف_کرو configCPU_CLOCK_HZ    ( ( بنانشانی لما ) 20000000 )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

#تعریف_کرو config_TICK_شرح_HZ                         ( 100U )
#تعریف_کرو configUSE_PREEMPTION                       1
#تعریف_کرو config_USE_ویلا_SLICING                     1
#تعریف_کرو config_USE_پورٹ_OPTIMISED_TASK_SELECTION    0
#تعریف_کرو configUSE_TICKLESS_IDLE                    1
#تعریف_کرو configMAX_PRIORITIES                       5U
#تعریف_کرو config_اقل_ڈھیر_ناپ                   128U
#تعریف_کرو configMAX_TASK_NAME_LEN                    4U
#تعریف_کرو config_TICK_TYPE_چوڑائی_وچ_بٹ              TICK_TYPE_چوڑائی_64_بٹ
#تعریف_کرو configIDLE_SHOULD_YIELD                    1
#تعریف_کرو configTASK_NOTIFICATION_ARRAY_ENTRIES      1U
#تعریف_کرو config_قطار_REGISTRY_ناپ                  0U
#تعریف_کرو configENABLE_BACKWARD_COMPATIBILITY        1
#تعریف_کرو config_عدد_THREAD_LOCAL_STORAGE_سوچکاں    0
#تعریف_کرو config_ڈھیر_ڈونگھائی_TYPE                     size_t
#تعریف_کرو config_سنیہا_بفر_لمائی_TYPE           size_t
#تعریف_کرو configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

#تعریف_کرو configUSE_TIMERS                1
#تعریف_کرو config_TIMER_TASK_ترجیح       ( configMAX_PRIORITIES - 1U )
#تعریف_کرو config_TIMER_TASK_ڈھیر_ڈونگھائی    config_اقل_ڈھیر_ناپ
#تعریف_کرو config_TIMER_قطار_لمائی        10U

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

#تعریف_کرو config_SUPPORT_STATIC_ونڈ              1
#تعریف_کرو config_SUPPORT_DYNAMIC_ونڈ             1
#تعریف_کرو config_کل_ڈھیر_ناپ                        4096U
#تعریف_کرو config_APPLICATION_ALLOCATED_ڈھیر             1
#تعریف_کرو config_ڈھیر_ونڈ_FROM_SEPARATE_ڈھیر    0
#تعریف_کرو config_USE_MINI_LIST_شے                     0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

#تعریف_کرو config_KERNEL_رکاوٹ_ترجیح          0U
#تعریف_کرو config_MAX_SYSCALL_رکاوٹ_ترجیح     0U
#تعریف_کرو config_MAX_API_CALL_رکاوٹ_ترجیح    0U

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#تعریف_کرو configUSE_IDLE_HOOK                   0
#تعریف_کرو configUSE_TICK_HOOK                   0
#تعریف_کرو configUSE_MALLOC_FAILED_HOOK          0
#تعریف_کرو configUSE_DAEMON_TASK_STARTUP_HOOK    0
#تعریف_کرو config_CHECK_FOR_ڈھیر_حد_توں_ودھ        0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#تعریف_کرو config_GENERATE_لگاتار_ویلا_STATS           0
#تعریف_کرو configUSE_TRACE_FACILITY                0
#تعریف_کرو configUSE_STATS_FORMATTING_FUNCTIONS    0
#تعریف_کرو config_KERNEL_PROVIDED_STATIC_حافظہ     1

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

#تعریف_کرو configUSE_TASK_NOTIFICATIONS           1
#تعریف_کرو configUSE_MUTEXES                      1
#تعریف_کرو configUSE_RECURSIVE_MUTEXES            1
#تعریف_کرو configUSE_COUNTING_SEMAPHORES          1
#تعریف_کرو config_USE_قطار_SETS                   1
#تعریف_کرو config_USE_APPLICATION_TASK_ٹیگ         1
#تعریف_کرو INCLUDE_v_Task_ترجیح_سیٹ               1
#تعریف_کرو INCLUDE_ux_Task_ترجیح_Get              1
#تعریف_کرو INCLUDE_vTaskDelete                    1
#تعریف_کرو INCLUDE_vTaskSuspend                   1
#تعریف_کرو INCLUDE_vTaskDelayUntil                1
#تعریف_کرو INCLUDE_vTaskDelay                     1
#تعریف_کرو INCLUDE_xTaskGetSchedulerState         1
#تعریف_کرو INCLUDE_xTaskGetCurrentTaskHandle      1
#تعریف_کرو INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark    1
#تعریف_کرو INCLUDE_xTaskGetIdleTaskHandle         1
#تعریف_کرو INCLUDE_eTaskGetState                  1
#تعریف_کرو INCLUDE_xTimerPendFunctionCall         1
#تعریف_کرو INCLUDE_xTaskAbortDelay                1
#تعریف_کرو INCLUDE_xTaskGetHandle                 1
#تعریف_کرو INCLUDE_xTaskResumeFromISR             1

#جے_انت /* FREERTOS_CONFIG_H */
