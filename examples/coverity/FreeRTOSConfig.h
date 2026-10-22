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

#నిర్వచితం_కాకపోతే FREERTOS_CONFIG_H
#నిర్వచించు FREERTOS_CONFIG_H

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

#నిర్వచించు configCPU_CLOCK_HZ    ( ( గుర్తులేని దీర్ఘ ) 20000000 )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

#నిర్వచించు config_TICK_రేటు_HZ                         ( 100U )
#నిర్వచించు configUSE_PREEMPTION                       1
#నిర్వచించు config_USE_సమయం_SLICING                     1
#నిర్వచించు config_USE_పోర్టు_OPTIMISED_TASK_SELECTION    0
#నిర్వచించు configUSE_TICKLESS_IDLE                    1
#నిర్వచించు configMAX_PRIORITIES                       5U
#నిర్వచించు config_కనీస_దొంతర_కొలత                   128U
#నిర్వచించు configMAX_TASK_NAME_LEN                    4U
#నిర్వచించు config_TICK_TYPE_వెడల్పు_లోపల_బిట్లు              TICK_TYPE_వెడల్పు_64_బిట్లు
#నిర్వచించు configIDLE_SHOULD_YIELD                    1
#నిర్వచించు configTASK_NOTIFICATION_ARRAY_ENTRIES      1U
#నిర్వచించు config_వరుస_REGISTRY_కొలత                  0U
#నిర్వచించు configENABLE_BACKWARD_COMPATIBILITY        1
#నిర్వచించు config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు    0
#నిర్వచించు config_దొంతర_లోతు_TYPE                     size_t
#నిర్వచించు config_సందేశం_బఫరు_నిడివి_TYPE           size_t
#నిర్వచించు configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

#నిర్వచించు configUSE_TIMERS                1
#నిర్వచించు config_TIMER_TASK_ప్రాధాన్యత       ( configMAX_PRIORITIES - 1U )
#నిర్వచించు config_TIMER_TASK_దొంతర_లోతు    config_కనీస_దొంతర_కొలత
#నిర్వచించు config_TIMER_వరుస_నిడివి        10U

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

#నిర్వచించు config_SUPPORT_STATIC_కేటాయింపు              1
#నిర్వచించు config_SUPPORT_DYNAMIC_కేటాయింపు             1
#నిర్వచించు config_మొత్తం_కుప్ప_కొలత                        4096U
#నిర్వచించు config_APPLICATION_ALLOCATED_కుప్ప             1
#నిర్వచించు config_దొంతర_కేటాయింపు_FROM_SEPARATE_కుప్ప    0
#నిర్వచించు config_USE_MINI_LIST_అంశం                     0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

#నిర్వచించు config_KERNEL_అంతరాయం_ప్రాధాన్యత          0U
#నిర్వచించు config_MAX_SYSCALL_అంతరాయం_ప్రాధాన్యత     0U
#నిర్వచించు config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత    0U

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#నిర్వచించు configUSE_IDLE_HOOK                   0
#నిర్వచించు configUSE_TICK_HOOK                   0
#నిర్వచించు configUSE_MALLOC_FAILED_HOOK          0
#నిర్వచించు configUSE_DAEMON_TASK_STARTUP_HOOK    0
#నిర్వచించు config_CHECK_FOR_దొంతర_అధికప్రవాహం        0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#నిర్వచించు config_GENERATE_నిరంతరం_సమయం_STATS           0
#నిర్వచించు configUSE_TRACE_FACILITY                0
#నిర్వచించు configUSE_STATS_FORMATTING_FUNCTIONS    0
#నిర్వచించు config_KERNEL_PROVIDED_STATIC_జ్ఞాపకం     1

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

#నిర్వచించు configUSE_TASK_NOTIFICATIONS           1
#నిర్వచించు configUSE_MUTEXES                      1
#నిర్వచించు configUSE_RECURSIVE_MUTEXES            1
#నిర్వచించు configUSE_COUNTING_SEMAPHORES          1
#నిర్వచించు config_USE_వరుస_SETS                   1
#నిర్వచించు config_USE_APPLICATION_TASK_ట్యాగ్         1
#నిర్వచించు INCLUDE_v_Task_ప్రాధాన్యత_సమితి               1
#నిర్వచించు INCLUDE_ux_Task_ప్రాధాన్యత_Get              1
#నిర్వచించు INCLUDE_vTaskDelete                    1
#నిర్వచించు INCLUDE_vTaskSuspend                   1
#నిర్వచించు INCLUDE_vTaskDelayUntil                1
#నిర్వచించు INCLUDE_vTaskDelay                     1
#నిర్వచించు INCLUDE_xTaskGetSchedulerState         1
#నిర్వచించు INCLUDE_xTaskGetCurrentTaskHandle      1
#నిర్వచించు INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark    1
#నిర్వచించు INCLUDE_xTaskGetIdleTaskHandle         1
#నిర్వచించు INCLUDE_eTaskGetState                  1
#నిర్వచించు INCLUDE_xTimerPendFunctionCall         1
#నిర్వచించు INCLUDE_xTaskAbortDelay                1
#నిర్వచించు INCLUDE_xTaskGetHandle                 1
#నిర్వచించు INCLUDE_xTaskResumeFromISR             1

#అయితే_ముగింపు /* FREERTOS_CONFIG_H */
