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

#جيڪڏهن_وصف_نه_ٿيل FREERTOS_CONFIG_H
#وصف_ڪريو FREERTOS_CONFIG_H

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

#وصف_ڪريو configCPU_CLOCK_HZ    ( ( بنانشان ڊگهو ) 20000000 )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

#وصف_ڪريو config_TICK_شرح_HZ                         ( 100U )
#وصف_ڪريو configUSE_PREEMPTION                       1
#وصف_ڪريو config_USE_وقت_SLICING                     1
#وصف_ڪريو config_USE_پورٽ_OPTIMISED_TASK_SELECTION    0
#وصف_ڪريو configUSE_TICKLESS_IDLE                    1
#وصف_ڪريو configMAX_PRIORITIES                       5U
#وصف_ڪريو config_گهٽتر_ڍير_سائيز                   128U
#وصف_ڪريو configMAX_TASK_NAME_LEN                    4U
#وصف_ڪريو config_TICK_TYPE_ويڪر_اندريون_بٽ              TICK_TYPE_ويڪر_64_بٽ
#وصف_ڪريو configIDLE_SHOULD_YIELD                    1
#وصف_ڪريو configTASK_NOTIFICATION_ARRAY_ENTRIES      1U
#وصف_ڪريو config_قطار_REGISTRY_سائيز                  0U
#وصف_ڪريو configENABLE_BACKWARD_COMPATIBILITY        1
#وصف_ڪريو config_انگ_THREAD_LOCAL_STORAGE_اشارا    0
#وصف_ڪريو config_ڍير_اونهائي_TYPE                     size_t
#وصف_ڪريو config_پيغام_بفر_ڊيگهائي_TYPE           size_t
#وصف_ڪريو configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

#وصف_ڪريو configUSE_TIMERS                1
#وصف_ڪريو config_TIMER_TASK_ترجيح       ( configMAX_PRIORITIES - 1U )
#وصف_ڪريو config_TIMER_TASK_ڍير_اونهائي    config_گهٽتر_ڍير_سائيز
#وصف_ڪريو config_TIMER_قطار_ڊيگهائي        10U

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

#وصف_ڪريو config_SUPPORT_STATIC_ورهاست              1
#وصف_ڪريو config_SUPPORT_DYNAMIC_ورهاست             1
#وصف_ڪريو config_ڪل_ڍير_سائيز                        4096U
#وصف_ڪريو config_APPLICATION_ALLOCATED_ڍير             1
#وصف_ڪريو config_ڍير_ورهاست_FROM_SEPARATE_ڍير    0
#وصف_ڪريو config_USE_MINI_LIST_شي                     0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

#وصف_ڪريو config_KERNEL_مداخلت_ترجيح          0U
#وصف_ڪريو config_MAX_SYSCALL_مداخلت_ترجيح     0U
#وصف_ڪريو config_MAX_API_CALL_مداخلت_ترجيح    0U

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#وصف_ڪريو configUSE_IDLE_HOOK                   0
#وصف_ڪريو configUSE_TICK_HOOK                   0
#وصف_ڪريو configUSE_MALLOC_FAILED_HOOK          0
#وصف_ڪريو configUSE_DAEMON_TASK_STARTUP_HOOK    0
#وصف_ڪريو config_CHECK_FOR_ڍير_حد_کان_مٿي        0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#وصف_ڪريو config_GENERATE_لاڳيتو_وقت_STATS           0
#وصف_ڪريو configUSE_TRACE_FACILITY                0
#وصف_ڪريو configUSE_STATS_FORMATTING_FUNCTIONS    0
#وصف_ڪريو config_KERNEL_PROVIDED_STATIC_يادگيري     1

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

#وصف_ڪريو configUSE_TASK_NOTIFICATIONS           1
#وصف_ڪريو configUSE_MUTEXES                      1
#وصف_ڪريو configUSE_RECURSIVE_MUTEXES            1
#وصف_ڪريو configUSE_COUNTING_SEMAPHORES          1
#وصف_ڪريو config_USE_قطار_SETS                   1
#وصف_ڪريو config_USE_APPLICATION_TASK_ٽيگ         1
#وصف_ڪريو INCLUDE_v_Task_ترجيح_سيٽ               1
#وصف_ڪريو INCLUDE_ux_Task_ترجيح_Get              1
#وصف_ڪريو INCLUDE_vTaskDelete                    1
#وصف_ڪريو INCLUDE_vTaskSuspend                   1
#وصف_ڪريو INCLUDE_vTaskDelayUntil                1
#وصف_ڪريو INCLUDE_vTaskDelay                     1
#وصف_ڪريو INCLUDE_xTaskGetSchedulerState         1
#وصف_ڪريو INCLUDE_xTaskGetCurrentTaskHandle      1
#وصف_ڪريو INCLUDE_ux_Task_Get_ڍير_مٿاهون_Water_Mark    1
#وصف_ڪريو INCLUDE_xTaskGetIdleTaskHandle         1
#وصف_ڪريو INCLUDE_eTaskGetState                  1
#وصف_ڪريو INCLUDE_xTimerPendFunctionCall         1
#وصف_ڪريو INCLUDE_xTaskAbortDelay                1
#وصف_ڪريو INCLUDE_xTaskGetHandle                 1
#وصف_ڪريو INCLUDE_xTaskResumeFromISR             1

#جيڪڏهن_پورو /* FREERTOS_CONFIG_H */
