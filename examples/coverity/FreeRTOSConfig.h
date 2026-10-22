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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ FREERTOS_CONFIG_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FREERTOS_CONFIG_H

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configCPU_CLOCK_HZ    ( ( ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ) 20000000 )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_TICK_ਦਰ_HZ                         ( 100U )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_PREEMPTION                       1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਸਮਾਂ_SLICING                     1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION    0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_TICKLESS_IDLE                    1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configMAX_PRIORITIES                       5U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਨਿਊਨਤਮ_ਢੇਰ_ਮਾਪ                   128U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configMAX_TASK_NAME_LEN                    4U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_TICK_TYPE_ਚੌੜਾਈ_ਵਿੱਚ_ਬਿੱਟ              TICK_TYPE_ਚੌੜਾਈ_64_ਬਿੱਟ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configIDLE_SHOULD_YIELD                    1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configTASK_NOTIFICATION_ARRAY_ENTRIES      1U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਕਤਾਰ_REGISTRY_ਮਾਪ                  0U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configENABLE_BACKWARD_COMPATIBILITY        1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ    0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE                     size_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਸੁਨੇਹਾ_ਬਫਰ_ਲੰਮਾਈ_TYPE           size_t
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_TIMERS                1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_TIMER_TASK_ਤਰਜੀਹ       ( configMAX_PRIORITIES - 1U )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_TIMER_TASK_ਢੇਰ_ਡੂੰਘਾਈ    config_ਨਿਊਨਤਮ_ਢੇਰ_ਮਾਪ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_TIMER_ਕਤਾਰ_ਲੰਮਾਈ        10U

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_SUPPORT_STATIC_ਵੰਡ              1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_SUPPORT_DYNAMIC_ਵੰਡ             1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਕੁੱਲ_ਢੇਰ_ਮਾਪ                        4096U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_APPLICATION_ALLOCATED_ਢੇਰ             1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਢੇਰ_ਵੰਡ_FROM_SEPARATE_ਢੇਰ    0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_MINI_LIST_ਵਸਤੂ                     0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_KERNEL_ਰੁਕਾਵਟ_ਤਰਜੀਹ          0U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_MAX_SYSCALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ     0U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ    0U

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_IDLE_HOOK                   0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_TICK_HOOK                   0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_MALLOC_FAILED_HOOK          0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_DAEMON_TASK_STARTUP_HOOK    0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_CHECK_FOR_ਢੇਰ_ਉਛਾਲ        0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS           0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_TRACE_FACILITY                0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_STATS_FORMATTING_FUNCTIONS    0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_KERNEL_PROVIDED_STATIC_ਸਮ੍ਰਿਤੀ     1

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_TASK_NOTIFICATIONS           1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_MUTEXES                      1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_RECURSIVE_MUTEXES            1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ configUSE_COUNTING_SEMAPHORES          1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_ਕਤਾਰ_SETS                   1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_USE_APPLICATION_TASK_ਟੈਗ         1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_v_Task_ਤਰਜੀਹ_ਸੈੱਟ               1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_ux_Task_ਤਰਜੀਹ_Get              1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_vTaskDelete                    1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_vTaskSuspend                   1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_vTaskDelayUntil                1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_vTaskDelay                     1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_xTaskGetSchedulerState         1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_xTaskGetCurrentTaskHandle      1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark    1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_xTaskGetIdleTaskHandle         1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_eTaskGetState                  1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_xTimerPendFunctionCall         1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_xTaskAbortDelay                1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_xTaskGetHandle                 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_xTaskResumeFromISR             1

#ਜੇ_ਅੰਤ /* FREERTOS_CONFIG_H */
