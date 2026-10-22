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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ FREERTOS_CONFIG_H
#ವ್ಯಾಖ್ಯಾನಿಸು FREERTOS_CONFIG_H

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

#ವ್ಯಾಖ್ಯಾನಿಸು configCPU_CLOCK_HZ    ( ( ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ) 20000000 )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

#ವ್ಯಾಖ್ಯಾನಿಸು config_TICK_ದರ_HZ                         ( 100U )
#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_PREEMPTION                       1
#ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಸಮಯ_SLICING                     1
#ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION    0
#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_TICKLESS_IDLE                    1
#ವ್ಯಾಖ್ಯಾನಿಸು configMAX_PRIORITIES                       5U
#ವ್ಯಾಖ್ಯಾನಿಸು config_ಕನಿಷ್ಠತಮ_ರಾಶಿ_ಗಾತ್ರ                   128U
#ವ್ಯಾಖ್ಯಾನಿಸು configMAX_TASK_NAME_LEN                    4U
#ವ್ಯಾಖ್ಯಾನಿಸು config_TICK_TYPE_ಅಗಲ_ಒಳ_ಬಿಟ್ಟುಗಳು              TICK_TYPE_ಅಗಲ_64_ಬಿಟ್ಟುಗಳು
#ವ್ಯಾಖ್ಯಾನಿಸು configIDLE_SHOULD_YIELD                    1
#ವ್ಯಾಖ್ಯಾನಿಸು configTASK_NOTIFICATION_ARRAY_ENTRIES      1U
#ವ್ಯಾಖ್ಯಾನಿಸು config_ಸರತಿ_REGISTRY_ಗಾತ್ರ                  0U
#ವ್ಯಾಖ್ಯಾನಿಸು configENABLE_BACKWARD_COMPATIBILITY        1
#ವ್ಯಾಖ್ಯಾನಿಸು config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_ಸೂಚಕಗಳು    0
#ವ್ಯಾಖ್ಯಾನಿಸು config_ರಾಶಿ_ಆಳ_TYPE                     size_t
#ವ್ಯಾಖ್ಯಾನಿಸು config_ಸಂದೇಶ_ಬಫರ್_ಉದ್ದಳತೆ_TYPE           size_t
#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_NEWLIB_REENTRANT                 0

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_TIMERS                1
#ವ್ಯಾಖ್ಯಾನಿಸು config_TIMER_TASK_ಆದ್ಯತೆ       ( configMAX_PRIORITIES - 1U )
#ವ್ಯಾಖ್ಯಾನಿಸು config_TIMER_TASK_ರಾಶಿ_ಆಳ    config_ಕನಿಷ್ಠತಮ_ರಾಶಿ_ಗಾತ್ರ
#ವ್ಯಾಖ್ಯಾನಿಸು config_TIMER_ಸರತಿ_ಉದ್ದಳತೆ        10U

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

#ವ್ಯಾಖ್ಯಾನಿಸು config_SUPPORT_STATIC_ಹಂಚಿಕೆ              1
#ವ್ಯಾಖ್ಯಾನಿಸು config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ             1
#ವ್ಯಾಖ್ಯಾನಿಸು config_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ                        4096U
#ವ್ಯಾಖ್ಯಾನಿಸು config_APPLICATION_ALLOCATED_ರಾಶಿ             1
#ವ್ಯಾಖ್ಯಾನಿಸು config_ರಾಶಿ_ಹಂಚಿಕೆ_FROM_SEPARATE_ರಾಶಿ    0
#ವ್ಯಾಖ್ಯಾನಿಸು config_USE_MINI_LIST_ಅಂಶ                     0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

#ವ್ಯಾಖ್ಯಾನಿಸು config_KERNEL_ಅಡಚಣೆ_ಆದ್ಯತೆ          0U
#ವ್ಯಾಖ್ಯಾನಿಸು config_MAX_SYSCALL_ಅಡಚಣೆ_ಆದ್ಯತೆ     0U
#ವ್ಯಾಖ್ಯಾನಿಸು config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ    0U

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_IDLE_HOOK                   0
#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_TICK_HOOK                   0
#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_MALLOC_FAILED_HOOK          0
#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_DAEMON_TASK_STARTUP_HOOK    0
#ವ್ಯಾಖ್ಯಾನಿಸು config_CHECK_FOR_ರಾಶಿ_ಅತಿಪ್ರವಾಹ        0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#ವ್ಯಾಖ್ಯಾನಿಸು config_GENERATE_ಸತತ_ಸಮಯ_STATS           0
#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_TRACE_FACILITY                0
#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_STATS_FORMATTING_FUNCTIONS    0
#ವ್ಯಾಖ್ಯಾನಿಸು config_KERNEL_PROVIDED_STATIC_ಸ್ಮರಣೆ     1

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_TASK_NOTIFICATIONS           1
#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_MUTEXES                      1
#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_RECURSIVE_MUTEXES            1
#ವ್ಯಾಖ್ಯಾನಿಸು configUSE_COUNTING_SEMAPHORES          1
#ವ್ಯಾಖ್ಯಾನಿಸು config_USE_ಸರತಿ_SETS                   1
#ವ್ಯಾಖ್ಯಾನಿಸು config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್         1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_v_Task_ಆದ್ಯತೆ_ಗಣ               1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_ux_Task_ಆದ್ಯತೆ_Get              1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_vTaskDelete                    1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_vTaskSuspend                   1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_vTaskDelayUntil                1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_vTaskDelay                     1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_xTaskGetSchedulerState         1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_xTaskGetCurrentTaskHandle      1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark    1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_xTaskGetIdleTaskHandle         1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_eTaskGetState                  1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_xTimerPendFunctionCall         1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_xTaskAbortDelay                1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_xTaskGetHandle                 1
#ವ್ಯಾಖ್ಯಾನಿಸು INCLUDE_xTaskResumeFromISR             1

#ಆದರೆ_ಅಂತ್ಯ /* FREERTOS_CONFIG_H */
